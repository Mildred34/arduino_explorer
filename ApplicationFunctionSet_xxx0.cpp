/*
 * @Author: Alexis
 * @Date: 2021-10-01 17:13
 * @LastEditors: Alexis
 * @Description: Factory for modules
 * @FilePath:
 */

#include <avr/wdt.h>
#include <stdio.h>
#include <string.h>
#include "ApplicationFunctionSet_xxx0.h"
#include "motors.h"
#include "servom.h"
#include "MPU6050_getdata.h"
#include "rgbled.h"
#include "voltage.h"
#include "ultrasonic.h"
#include "encoders.h"

/* Flags de debug */
#define _Test_DeviceDriverSet_Voltage 0
#define _Test_SerialPort 1

ApplicationFunctionSet Application_FunctionSet;

MPU6050_getdata AppMPU6050getdata;
DeviceDriverSet_RBGLED AppRBG_LED;
DeviceDriverSet_Voltage AppVoltage;
DeviceDriverSet_Motor AppMotor;
DeviceDriverSet_Encoder AppEncoder;
DeviceDriverSet_ULTRASONIC AppULTRASONIC;
DeviceDriverSet_Servo AppServo;

/**
 * [booleanfunction_xxx description]
 * @param  x  long
 * @param  s  long
 * @param  e  long
 * @return         return true if x is between s and e false otherwise
 */
static boolean
function_xxx(long x, long s, long e) //f(x)
{
  if (s <= x && x <= e)
    return true;
  else
    return false;
}

void ApplicationFunctionSet::ApplicationFunctionSet_Init(void)
{
  bool res_error = true;
  Serial.begin(9600); // Sets the data rate in bits per second (baud) for serial data transmission.
  AppVoltage.DeviceDriverSet_Voltage_Init(); // Pin A3 en input (power module)
  AppMotor.DeviceDriverSet_Motor_Init(); // Init motors pins
  AppEncoder.DeviceDriverSet_Encoder_Init(); // Init encoders pins
  AppServo.DeviceDriverSet_Servo_Init(90); // Init Servo pins
  AppRBG_LED.DeviceDriverSet_RBGLED_Init(20); // rgb led init
  AppULTRASONIC.DeviceDriverSet_ULTRASONIC_Init(); // ultrasonic sensor init
  res_error = AppMPU6050getdata.MPU6050_dveInit(); // Imu init pin
  AppMPU6050getdata.MPU6050_calibration(); // Imu calibration

  // while (Serial.read() >= 0)
  // {
  //   /*Clear serial port buffer...*/
  // }
  //
}

/**
 * [ApplicationFunctionSet::ApplicationFunctionSet_SensorDataUpdate description]
 * Robot car update sensors' data:Partial update (selective update)
 */
void ApplicationFunctionSet::ApplicationFunctionSet_SensorDataUpdate(void)
{

  // AppMotor.DeviceDriverSet_Motor_Test();
  { /*Battery voltage status update*/
    static unsigned long VoltageData_time = 0;
    static int VoltageData_number = 1;
    if (millis() - VoltageData_time > 10) //read and update the data per 10ms
    {
      VoltageData_time = millis();
      VoltageData_V = AppVoltage.DeviceDriverSet_Voltage_getAnalogue();

      #if _Test_DeviceDriverSet_Voltage
      Wire.begin();
      Serial.print("Tension: ");
      Serial.println(VoltageData_V);
      #endif

      if (VoltageData_V < VoltageDetection)
      {
        VoltageData_number++;
        if (VoltageData_number == 500) //Continuity to judge the latest voltage value multiple
        {
          VoltageDetectionStatus = true;
          VoltageData_number = 0;
        }
      }
      else
      {
        VoltageDetectionStatus = false;
      }
    }
  }

}

/* motor speed  0-250 */
// TO DO
void ApplicationFunctionSet::CMD_MotorControl_xxx0(void)
{
  static boolean MotorControl = false;
  static uint8_t is_MotorSpeed_A = 0;
  static uint8_t is_MotorSpeed_B = 0;

  if (Application_SmartRobotCarxxx0.Functional_Mode == CMD_MotorControl)
  {
    MotorControl = true;
    if (0 == CMD_is_MotorDirection)
    {
      ApplicationFunctionSet_SmartRobotCarMotionControl(stop_it, 0);
    }
    else
    {
      switch (CMD_is_MotorSelection) //motor selection
      {
      case 0:
      {
        is_MotorSpeed_A = CMD_is_MotorSpeed;
        is_MotorSpeed_B = CMD_is_MotorSpeed;
        if (1 == CMD_is_MotorDirection)
        { //turn forward
          AppMotor.DeviceDriverSet_Motor_control(/*direction_A*/ direction_just, /*speed_A*/ is_MotorSpeed_A,
                                                 /*direction_B*/ direction_just, /*speed_B*/ is_MotorSpeed_B,
                                                 /*controlED*/ control_enable); //Motor control
        }
        else if (2 == CMD_is_MotorDirection)
        { //turn backward
          AppMotor.DeviceDriverSet_Motor_control(/*direction_A*/ direction_back, /*speed_A*/ is_MotorSpeed_A,
                                                 /*direction_B*/ direction_back, /*speed_B*/ is_MotorSpeed_B,
                                                 /*controlED*/ control_enable); //Motor control
        }
        else
        {
          return;
        }
      }
      break;
      case 1:
      {
        is_MotorSpeed_A = CMD_is_MotorSpeed;
        if (1 == CMD_is_MotorDirection)
        { //turn forward
          AppMotor.DeviceDriverSet_Motor_control(/*direction_A*/ direction_just, /*speed_A*/ is_MotorSpeed_A,
                                                 /*direction_B*/ direction_void, /*speed_B*/ is_MotorSpeed_B,
                                                 /*controlED*/ control_enable); //Motor control
        }
        else if (2 == CMD_is_MotorDirection)
        { //turn backward
          AppMotor.DeviceDriverSet_Motor_control(/*direction_A*/ direction_back, /*speed_A*/ is_MotorSpeed_A,
                                                 /*direction_B*/ direction_void, /*speed_B*/ is_MotorSpeed_B,
                                                 /*controlED*/ control_enable); //Motor control
        }
        else
        {
          return;
        }
      }
      break;
      case 2:
      {
        is_MotorSpeed_B = CMD_is_MotorSpeed;
        if (1 == CMD_is_MotorDirection)
        { //turn forward
          AppMotor.DeviceDriverSet_Motor_control(/*direction_A*/ direction_void, /*speed_A*/ is_MotorSpeed_A,
                                                 /*direction_B*/ direction_just, /*speed_B*/ is_MotorSpeed_B,
                                                 /*controlED*/ control_enable); //Motor control
        }
        else if (2 == CMD_is_MotorDirection)
        { //turn backward
          AppMotor.DeviceDriverSet_Motor_control(/*direction_A*/ direction_void, /*speed_A*/ is_MotorSpeed_A,
                                                 /*direction_B*/ direction_back, /*speed_B*/ is_MotorSpeed_B,
                                                 /*controlED*/ control_enable); //Motor control
        }
        else
        {
          return;
        }
      }
      break;
      default:
        break;
      }
    }
  }
  else
  {
    if (MotorControl == true)
    {
      MotorControl = false;
      is_MotorSpeed_A = 0;
      is_MotorSpeed_B = 0;
    }
  }
}

/*Data analysis on serial port*/
void ApplicationFunctionSet::ApplicationFunctionSet_SerialPortDataAnalysis(void)
{
  int c = 0;
  if (Serial.available() > 0)
  {
      c = Serial.readString().toInt();
  }

  if (c != 0) //Data frame tail check
  {
      const char *ptr;
      int control_mode_N = c;

      #if _Test_SerialPort
          Serial.println(control_mode_N,DEC);
      #endif

      if(control_mode_N != 0)
      {
        switch (control_mode_N)
        {
        case 1: /* Speed to 250 */
          Right_motors=250;
          Left_motors=250;

          break;

        case 2: /* Speed to 0 */
          Right_motors=0;
          Left_motors=0;

          break;

        case 3: /* Speed to 125 */
          Right_motors=125;
          Left_motors=125;

          break;
        default:
          break;
        }
    }
    else
    {
      #if _Test_SerialPort
          Serial.println(c);
      #endif
    }
  }

}
