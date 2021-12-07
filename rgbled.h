/*
 * @Author: Alexis
 * @Date: 2021-12-01 17:41
 * @Description:
 * @FilePath:
 */
#ifndef _RGBLED_H_
#define _RGBLED_H_
#include <Arduino.h>
#include "FastLED.h"

class DeviceDriverSet_RBGLED
{
public:
  void DeviceDriverSet_RBGLED_Init(uint8_t set_Brightness);
public:
private:
#define PIN_RBGLED 4
#define NUM_LEDS 1
public:
  CRGB leds[NUM_LEDS];
};



extern DeviceDriverSet_RBGLED AppRBG_LED;
#endif
