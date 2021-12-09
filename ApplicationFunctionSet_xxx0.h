/*
 * @Author: Alexis
 * @Date: 2021-10-01 17:13
 * @LastEditTime: 2020-12-29 16:04:05
 * @LastEditors: Alexis
 * @Description: Factory for modules
 * @FilePath:
 */
#ifndef _ApplicationFunctionSet_xxx0_H_
#define _ApplicationFunctionSet_xxx0_H_

#include <Arduino.h>
#include <stdlib.h>
#include "motors.h"

class ApplicationFunctionSet
{
public:
  void ApplicationFunctionSet_Init(void);
  void ApplicationFunctionSet_SensorDataUpdate(void);
  void ApplicationFunctionSet_SerialPortDataAnalysis(void);
  void encoders_value(void) const;

public: /* Motors */
  void CMD_MotorControl_xxx0();

private:
  /*Sensor Raw Value*/
  volatile float VoltageData_V;        //Battery Voltage Value

  /*Sensor Status*/
  boolean VoltageDetectionStatus = false;

public:
  /*Sensor Threshold Setting*/
  const float VoltageDetection = 7.00;

public: /* Motors */
  motor_selection CMD_is_MotorSelection;
  motor_direction CMD_is_MotorDirection;
  uint8_t CMD_is_MotorSpeed;
  uint32_t CMD_is_MotorTimer;

  /* Motor speed Value */
  int Right_motors = 0;
  int Left_motors = 0;


};

extern ApplicationFunctionSet Application_FunctionSet;
#endif
