/*
 * @Author: Alexis
 * @Date: 2021-12-01 17:41
 * @Description:
 * @FilePath:
 */

#ifndef _MOTORS_H_
#define _MOTORS_H_

#include <Arduino.h>

class DeviceDriverSet_Motor
{
public:
  void DeviceDriverSet_Motor_Init(void);
  
private:
//TB6612
#define PIN_Motor_PWMA 5
#define PIN_Motor_PWMB 6
#define PIN_Motor_BIN_1 8
#define PIN_Motor_AIN_1 7
#define PIN_Motor_STBY 3
public:
#define speed_Max 255
#define direction_just true
#define direction_back false
#define direction_void 3

#define Duration_enable true
#define Duration_disable false
#define control_enable true
#define control_disable false
};

extern DeviceDriverSet_Motor AppMotor;

#endif
