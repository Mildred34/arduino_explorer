/*
 * @Author: Alexis
 * @Date: 2021-12-01 17:41
 * @Description:
 * @FilePath:
 */
#ifndef _ULTRASONIC_H_
#define _ULTRASONIC_H_
#include <Arduino.h>

/*ULTRASONIC*/
class DeviceDriverSet_ULTRASONIC
{
public:
  void DeviceDriverSet_ULTRASONIC_Init(void);

private:
#define TRIG_PIN 13      // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN 12      // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
};


extern DeviceDriverSet_ULTRASONIC AppULTRASONIC;
#endif
