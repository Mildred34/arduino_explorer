/*
 * @Author: Alexis
 * @Date: 2021-12-01 17:41
 * @Description:
 * @FilePath:
 */
#ifndef _SERVOM_H_
#define _SERVOM_H_
#include <Servo.h>
#include <Arduino.h>
#include <avr/wdt.h>

class DeviceDriverSet_Servo
{
public:
  void DeviceDriverSet_Servo_Init(unsigned int Position_angle);

private:
#define PIN_Servo_z 10
};

extern DeviceDriverSet_Servo AppServo;
#endif
