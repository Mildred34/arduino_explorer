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
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt16.h>

class ApplicationFunctionSet
{
public:
  ApplicationFunctionSet(void);
  void ApplicationFunctionSet_Init(void);
  void ApplicationFunctionSet_SensorDataUpdate(void);
  void ApplicationFunctionSet_SerialPortDataAnalysis(void);


public: /* Encoders */
  void encoders_value(void) const;

public: /* Motors */
  void CMD_MotorControl_xxx0();

public: /*ROS*/

  void ros_loop(void);

private: /* Battery */
  /*Sensor Raw Value*/
  volatile float VoltageData_V;        //Battery Voltage Value

  /*Sensor Status*/
  boolean VoltageDetectionStatus = false;

public: /* Battery */
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


public: /*ROS */
  ros::NodeHandle node_handle;
  std_msgs::String button_msg;
  ros::Publisher button_publisher;

};

extern ApplicationFunctionSet Application_FunctionSet;
#endif
