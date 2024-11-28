#pragma once
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_event.h"

void start_mqtt(void);
void sendPIReventToMQTT(const char* direction);
void sendPIR_BEDeventToMQTT(const char* roomID);
void sendBatteryStatusToMQTT(void);
void sendDOOReventToMQTT(void);