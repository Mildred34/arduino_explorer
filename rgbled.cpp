/*
 * @Author: Alexis
 * @Date: 2021-12-01 17:41
 * @Description:
 * @FilePath:
 */

#include "rgbled.h"
void DeviceDriverSet_RBGLED::DeviceDriverSet_RBGLED_Init(uint8_t set_Brightness)
{
  FastLED.addLeds<NEOPIXEL, PIN_RBGLED>(leds, NUM_LEDS);
  FastLED.setBrightness(set_Brightness);
}
