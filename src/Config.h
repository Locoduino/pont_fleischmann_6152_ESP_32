/*
   Config.h

*/



#ifndef Config_h
#define Config_h


#include <Arduino.h>

#define DEBUG

#define CONFIG 1

#if CONFIG == 1
#define WIFI_SSID              "xxxxxxxxxxxxxxx"
#define WIFI_PSW               "XXXXXXXXXXXXXXX"

#elif CONFIG == 2
#define WIFI_SSID              "yyyyyyyyyyyyyyy"
#define WIFI_PSW               "YYYYYYYYYYYYYYY"

#elif CONFIG == 3
#define WIFI_SSID              "zzzzzzzzzzzzzzz"
#define WIFI_PSW               "ZZZZZZZZZZZZZZZ"

#endif

#define MDNS_NAME              "fleischmann_6152"


#define OTAName                "fleischmann_6152"           
#define OTAPassword            "AAAAAAAAAAAAAAAA"


// parametres pour configuration du pont
#define VITESSE_ROTATION    255
#define LUMIERE_CABINE      HIGH

#define BAUD_RATE            115200

// ! GPIO 34, 35, 36, 39 input only

#define PIN_A_IN1            GPIO_NUM_5                   // GPIO5
#define PIN_A_IN2            GPIO_NUM_18                  // GPIO18
#define PIN_B_IN1            GPIO_NUM_19                  // GPIO19

#define HALL_1               GPIO_NUM_34                  // GPIO34
#define HALL_2               GPIO_NUM_35                  // GPIO35

#define FEUX                 GPIO_NUM_4                   // GPI04
#define FEUX_H               gpio_set_level(FEUX, HIGH)
#define FEUX_L               gpio_set_level(FEUX, LOW)
#define REL_POLARITE_DCC     GPIO_NUM_23                  // GPI023
#define CABINE               GPIO_NUM_22                  // GPI022
#define CABINE_H             gpio_set_level(CABINE, HIGH)
#define CABINE_L             gpio_set_level(CABINE, LOW)


extern bool calculMillis (unsigned long previousMillis, unsigned long interval);

#endif
