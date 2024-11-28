#include "main.h"

#include <stdio.h>
#include <string.h>

#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "gauge.h"
#include "mqtt.h"
#include "nvs_flash.h"
#include "sntp.h"
#include "wifi.h"
#include "esp_sleep.h"
#include "esp_mac.h"
#include "esp_pm.h"

char *device_id = NULL, *device_topic = NULL, *device_key = NULL;

bool corridor = false;
bool lavatory = false;
bool livingroom = false;

uint8_t mac_gold[6]   = MAC_GOLD;
uint8_t mac_green1[6] = MAC_GREEN1;
uint8_t mac_green2[6] = MAC_GREEN2;

int count = 0;

void IRAM_ATTR handlePIRevent(void *arg) {
  count++;
  ets_printf("Got PIR event %d\n", count);
}

void app_main() {
  uint64_t wakeup_mask = esp_sleep_get_ext1_wakeup_status();
  ESP_LOGI("progress", "Wakeup status mask: %llu", wakeup_mask);

  uint8_t mac[6];
  ESP_ERROR_CHECK(esp_read_mac(mac, ESP_MAC_WIFI_STA));

  ESP_LOGI("progress", "Device MAC Address:");
  print_mac_address(mac);

  device_config(mac);
  configPM(false);

  ESP_LOGI("progress", "[APP] Free memory: %d bytes", esp_get_free_heap_size());
  ESP_LOGI("progress", "[APP] IDF version: %s", esp_get_idf_version());

  esp_log_level_set("*", ESP_LOG_ERROR);
  esp_log_level_set("mqtt", ESP_LOG_INFO);
  esp_log_level_set("progress", ESP_LOG_INFO);
  esp_log_level_set("gauge", ESP_LOG_INFO);

  if(livingroom){getRSOC();}

  esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);

  ESP_LOGI("progress", "Starting Wifi");
  start_wifi();

  ESP_LOGI("progress", "Starting Clock");
  start_clock();

  ESP_LOGI("progress", "Starting MQTT");
  start_mqtt();

  ESP_LOGI("progress", "Sending battery status to MQTT");
  sendBatteryStatusToMQTT();

  if(corridor){
    ESP_LOGI("progress", "Sending event to MQTT");
    if ((wakeup_mask & (1ULL << PIR_PIN)) != 0) {
      ESP_LOGI("progress", "PIR detected");
      sendPIReventToMQTT("corridor");
    }
    if ((wakeup_mask & (1ULL << DOOR_PIN)) != 0) {
      ESP_LOGI("progress", "DOOR detected");
      sendDOOReventToMQTT();
    }
    ESP_ERROR_CHECK(gpio_set_direction(PIR_PIN, GPIO_MODE_INPUT));
    ESP_ERROR_CHECK(gpio_set_direction(DOOR_PIN, GPIO_MODE_INPUT));
    ESP_ERROR_CHECK(rtc_gpio_pulldown_en(PIR_PIN));
    ESP_ERROR_CHECK(rtc_gpio_pulldown_en(DOOR_PIN));
    
    ESP_LOGI("progress", "Installing wakeup");
    while (gpio_get_level(PIR_PIN)==1){
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    while (gpio_get_level(DOOR_PIN)==1){
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    ESP_ERROR_CHECK(esp_sleep_enable_ext1_wakeup(PIN_MASK, ESP_EXT1_WAKEUP_ANY_HIGH));
  }

  if(lavatory){
    ESP_LOGI("progress", "Sending event to MQTT");
    ESP_LOGI("progress", "PIR detected");
    sendPIReventToMQTT("lavatory");

    ESP_ERROR_CHECK(gpio_set_direction(PIR_PIN, GPIO_MODE_INPUT));
    ESP_ERROR_CHECK(rtc_gpio_pulldown_en(PIR_PIN));

    ESP_LOGI("progress", "Installing wakeup");
    while (gpio_get_level(PIR_PIN)==1){
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    ESP_ERROR_CHECK(esp_sleep_enable_ext0_wakeup(PIR_PIN, 1));
  }

  if(livingroom){
    ESP_LOGI("progress", "Sending PIR event to MQTT");
    if ((wakeup_mask & (1ULL << PIR_PIN)) != 0) {
        ESP_LOGI("progress", "PIR_PIN detected");
        sendPIReventToMQTT("Table");
    }
    if ((wakeup_mask & (1ULL << PIR_BED_PIN)) != 0) {
        ESP_LOGI("progress", "PIR_BED_PIN detected");
        sendPIR_BEDeventToMQTT("Bed");
    }
    ESP_ERROR_CHECK(gpio_set_direction(PIR_PIN, GPIO_MODE_INPUT));
    ESP_ERROR_CHECK(gpio_set_direction(PIR_BED_PIN, GPIO_MODE_INPUT));
    ESP_ERROR_CHECK(rtc_gpio_pulldown_en(PIR_PIN));
    ESP_ERROR_CHECK(rtc_gpio_pulldown_en(PIR_BED_PIN));

    ESP_LOGI("progress", "Installing wakeup");
    while (gpio_get_level(PIR_PIN)==1|| gpio_get_level(PIR_BED_PIN) == 1){
      vTaskDelay(pdMS_TO_TICKS(1000));
    }
    ESP_ERROR_CHECK(esp_sleep_enable_ext1_wakeup(PIR_PIN_MASK, ESP_EXT1_WAKEUP_ANY_HIGH));
  }

  esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_TIMER);
  configPM(false);
  ESP_LOGI("progress", "Going to sleep");
  esp_deep_sleep_start();
}

//——————————————————————Function——————————————————————//
void print_mac_address(const uint8_t *mac) {
  ESP_LOGI("progress", "MAC Address: %02X:%02X:%02X:%02X:%02X:%02X",
            mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

void device_config(const uint8_t *mac){
  if (memcmp(mac, mac_gold, sizeof(mac_gold)) == 0) {
    livingroom = true;
    device_id = DEVICE_ID_LIVINGROOM;
    device_topic = DEVICE_TOPIC_LIVINGROOM;
    device_key = DEVICE_KEY_LIVINGROOM;
    ESP_LOGI("progress", "livingroom: %d", livingroom);
  } else if (memcmp(mac, mac_green1, sizeof(mac_green1)) == 0) {
    lavatory = true ;
    device_id = DEVICE_ID_LAVATORY;
    device_topic = DEVICE_TOPIC_LAVATORY;
    device_key = DEVICE_KEY_LAVATORY;
    ESP_LOGI("progress", "lavatory: %d", lavatory);
  } else if (memcmp(mac, mac_green2, sizeof(mac_green2)) == 0) {
    corridor = true;
    device_id = DEVICE_ID_CORRIDOR;
    device_topic = DEVICE_TOPIC_CORRIDOR;
    device_key = DEVICE_KEY_CORRIDOR;
    ESP_LOGI("progress", "corridor: %d", corridor);
  } else {
    ESP_LOGI("progress","Unknow Device");
    device_id = "unknown_id";
    device_topic = "unknown_topic";
    device_key = "unknown_key";
  }
  ESP_LOGI("progress", "Device ID: %s", device_id);
  ESP_LOGI("progress", "Device Topic: %s", device_topic);
}

void configPM(bool als){
 esp_pm_config_esp32_t pm_config = {
 .max_freq_mhz = 160,
 .min_freq_mhz = 160, //DFS, enable in menucofig in Power Management
 .light_sleep_enable = als //automatic light sleep, enable via menuconfig in FreeRTOS
 };
 ESP_LOGI("progress", "Configuring Power Management with max_freq=%d, min_freq=%d, light_sleep=%s",
         pm_config.max_freq_mhz, pm_config.min_freq_mhz, pm_config.light_sleep_enable ? "true" : "false");
 ESP_ERROR_CHECK(esp_pm_configure(&pm_config));
} 