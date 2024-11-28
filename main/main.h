#pragma once
#include <stdint.h>
#include <stdbool.h>

// #define CAPS

 #ifdef CAPS

    // #define EXAMPLE_ESP_WIFI_SSID      "CAPS"
    // #define EXAMPLE_ESP_WIFI_PASS      "caps!schulz-wifi"
    #define EXAMPLE_ESP_WIFI_SSID      "CAPS-Seminar-Room"
    #define EXAMPLE_ESP_WIFI_PASS      "caps-schulz-seminar-room-wifi"
    #define SNTP_SERVER_NAME           "ntp1.in.tum.de"
    #define MQTT_BROKER                "131.159.84.119" //caps-seminar-room

#else

    #define EXAMPLE_ESP_WIFI_SSID      "FRITZ!Box 7430 MU"
    #define EXAMPLE_ESP_WIFI_PASS      "91779037909666514286"
    #define SNTP_SERVER_NAME           "time.google.com"
    #define MQTT_BROKER                "192.168.178.177" 

#endif

#define MAC_GOLD    {0xEC, 0x62, 0x60, 0xBC, 0xE8, 0x04}    //living room
#define MAC_GREEN1  {0x94, 0xB9, 0x7E, 0x41, 0xFF, 0xF4}    //lavatory  
#define MAC_GREEN2  {0x94, 0xB9, 0x7E, 0x56, 0x1A, 0xBC}    //corridor

extern char *device_id, *device_topic, *device_key;

#define DEVICE_ID_CORRIDOR          "2"
#define DEVICE_TOPIC_CORRIDOR       "1/2/data"
#define DEVICE_KEY_CORRIDOR         "eyJhbGciOiJSUzI1NiIsInR5cCI6IkpXVCJ9.eyJpYXQiOjE3MzE2NzY5MTUsImlzcyI6ImlvdHBsYXRmb3JtIiwic3ViIjoiMS8yIn0.INlykZekva8aZ7VUqX7o9Bq3MQ-oYrlZKUyhaRS47WH5iOMHh9QQoWsuF86oULw5BczVKIlZiTn4FMQjXd7kHrn2cAOZb37brZqAXqL-lrOQ7b36fPuvh-Qb7jFx46sgMml-bzD6NwrVOhzWElc2mY9nCD3YYsJAOqdQWnriXRCwM4Slv3zUGvO7aaZKTaCVCdgzQSe_DVuUELiDQAc8eBygJaS9dkbNvpJGw6ICObFPMsecDL933aR1z-9DglDgcEcU3aFxpOSdsvCwM0am_3QwFwpeIeKEZ9vARcDwcD4acEj2LUJhR9OBRrTmR956l4YS5TuDcCXZ_Tsj0BTx7f_oEmbmjpg09gvtog7KOFu_XTDbg6uLCOzjZFccdpu1w0QHTcD4pdAv3jf8RNxS5FEnRpoIc_WPRlY_DH-7fJhmdl34sMPQ_sqrVuh945BZ0mzSJo0OW3nf3AZVUTI7p7A2hD-FKN3pNX3-oK2vDURdBjVSioZ2OEDwht_EueRzZ1pY3KK-V4atWlbjumDW21V6wld7mYjhOTSV68FsYkY40C1o6BoMxkMPqrKq_25ZMp881blCHL9oV8quIyX_4FyQka6iUwtHM2fNvANva5ZSruXaf7817ZHB18xFvGETbG0XtpvfKQAfiQJTKj0A5q4Ibba71Ipn7Gqs3V5-xWw"

#define DEVICE_ID_LAVATORY          "3"
#define DEVICE_TOPIC_LAVATORY       "1/3/data"
#define DEVICE_KEY_LAVATORY         "eyJhbGciOiJSUzI1NiIsInR5cCI6IkpXVCJ9.eyJpYXQiOjE3MzAyOTc4NjAsImlzcyI6ImlvdHBsYXRmb3JtIiwic3ViIjoiMS8zIn0.IwS2igDdMOKicyjjdMgAMRTfeFOkKqQroN0c24YNUhQ_mjxpXRNyp4eB7pZ01tmYHmiB4jvZdbJZgmPoHTr-HDwHaZGxMcx1PJN_QL71YvikBxs3LkakhKIt3kwGnh8As2sBvSa1NYFc36ZkbGGSPpodrJT5Tc60fWBLjTThrNED9MTXgfKrVc341q6xAG0HHdR0-DbNQwzwor918O5WEg4mOPFvDACyUTbBm8iJhRoBYuFR1EdWurBuFmwjD-Il0JOwTWGny66Whg_5AI5oEpaHAfPZLm69KSYL6zIAWISIHkKc--DBchHVmOCacPW3VZewHnw94OmOfpX1rSVfaCZUzNyH4jhqSfNpgt8-NTtEkzpooKNZYPX8ol77Kbg43P-A1osp5lT5HdviMT3xP35L_lajpxJALekYye2xi1TStmvi1mY8n3wgMrFUIHqs8eVeh1T-6ZeSOyJLfc5197bcTv-rTsELkhvf5LYGVAjnu5-OZiFcZ0tEDyQbcoUJ6c1cuzlACWR7_KJVauSkWmSxQ04ljBXuEp-CBb77luFzapNCgAQs5rAXCIi4vmboPR04Jfq23mXj_NnondEHlSsJgjOXq3YbVEqv-9sdxcXsMfEcCwMfaUW4U3OWbAVh1irtYQLIdJdY7Nn4E2Ft-RCx_Jg-Hu1aawoaSUNVh8U"

#define DEVICE_ID_LIVINGROOM        "4"
#define DEVICE_TOPIC_LIVINGROOM     "1/4/data"
#define DEVICE_KEY_LIVINGROOM       "eyJhbGciOiJSUzI1NiIsInR5cCI6IkpXVCJ9.eyJpYXQiOjE3MzE2NzY3ODAsImlzcyI6ImlvdHBsYXRmb3JtIiwic3ViIjoiMS80In0.wSgl6XoZCJ8CxyTXXlvJXdPu_7RWkJdt-HXm7Mc9ZeALiVmdbxfUQYZZOv8aB3yDpZsGvJpO5EYzCFINx2vunCaM5yB5vUod1DyqKo70GayO2-s27GstQRdQagjjJhJYm0-69DHXoRth6eIGRCeDy0yr2SDsrqCtz2UjG5wDjiawKuqti0qlAD0Kwyw86V9J69o4LJX8qfVMvrqDGF4-t5h7kf-gf48BiO_x-aPmh97mjJUCoce62YTKd7aJtoaeXjbyqTWuP31zvxyhu4oMnf6BhPHDJylotosR6CqI06T3utrGR8TF51xgSSFaSXjAx-ahHA0TcddcqmI4Le8TPxI1Vfgl9t5oysm_1MJ66lc565s8PsbKpHD24kJDjN-21N-ErFNbOoAtuhvaJ3UscSI7UuTY9OWR1pnb8GEhTVxQXar5aiGG9Us2mVPUr9I3G0gizA2wOjHBNCbQNCpyFQTlRtYenB9EWjvvueK0KxzdUDH4_f5wBvLMia_ZwtpdL20xAn7x5xBA9DuDRox8R5tGAx_X7u8G1f2wRTyoCuCiTOGSJfxGn4R6RKIyntomXr_2MPyyhoDoqbBXytGO-jr3JXYswKRYvh8RuBrXxem7nbpdpD2aFklDKksK46ejFZoa63ceV2w6S7Qe1kkDkqlxR3aad3WsOFPdMXATtDI"

#define PIR_PIN         27 
#define DOOR_PIN        13
#define PIR_BED_PIN     13

#define PIN_MASK        ((1ULL<<PIR_PIN)|(1ULL<<DOOR_PIN))
#define PIR_PIN_MASK    ((1ULL<<PIR_PIN)|(1ULL<<PIR_BED_PIN))

void print_mac_address(const uint8_t *mac);
void device_config(const uint8_t *mac);
void configPM(bool als);
