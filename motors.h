/*
 * @Author: Alexis
 * @Date: 2021-12-01 17:41
 * @Description:
 * @FilePath:
 */

#ifndef _MOTORS_H_
#define _MOTORS_H_

#include <Arduino.h>

typedef enum motor_direction
{
direction_void = 0,
direction_back = 1,
direction_forw = 2
} motor_direction;

typedef enum motor_selection
{
selection_left = 0,
selection_right = 1,
selection_all = 2
} motor_selection;

class DeviceDriverSet_Motor
{
public:
  void DeviceDriverSet_Motor_Init(void);
  void DeviceDriverSet_Motor_CMD(void);
  void DeviceDriverSet_Motor_control(motor_direction direction_RIGHT, uint8_t speed_RIGHT, //Group A motor parameters
                                                            motor_direction direction_LEFT, uint8_t speed_LEFT, //Group B motor parameters
                                                            boolean controlED                     //AB enable setting (true)
                                                          );

private:
//TB6612
// Left motors
#define PIN_Motor_BIN_1 8
#define PIN_Motor_PWMB 6

// Right motors
#define PIN_Motor_PWMA 5
#define PIN_Motor_AIN_1 7

#define PIN_Motor_STBY 3

public:
#define speed_Max 255

#define Duration_enable true
#define Duration_disable false
#define control_enable true
#define control_disable false
};

extern DeviceDriverSet_Motor AppMotor;

#endif
