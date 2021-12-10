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

/*Movement Direction Control List*/
enum SmartRobotCarMotionControl
{
  Forward,       //(1)
  Backward,      //(2)
  Left,          //(3)
  Right,         //(4)
  LeftForward,   //(5)
  LeftBackward,  //(6)
  RightForward,  //(7)
  RightBackward, //(8)
  stop_it        //(9)
};

// Static function
static void ApplicationFunctionSet_SmartRobotCarLinearMotionControl(SmartRobotCarMotionControl direction, uint8_t directionRecord, uint8_t speed, uint8_t Kp, uint8_t UpperLimit);
static void ApplicationFunctionSet_SmartRobotCarMotionControl(SmartRobotCarMotionControl direction, uint8_t is_speed);

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
  // AppServo.DeviceDriverSet_Servo_Init(90); // Init Servo pins
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

/**
 * [ApplicationFunctionSet::ApplicationFunctionSet_SerialPortDataAnalysis description]
 * Data analysis on serial port
 * Switch speed with the serial port:
 * 1 = max speed
 * 2 = 0 speed
 * 3 = half speed
 */
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


/*
  Movement Direction Control:
  Input parameters:     1# direction:Forward（1）、Backward（2）、 Left（3）、Right（4）、LeftForward（5）、LeftBackward（6）、RightForward（7）RightBackward（8）
                        2# speed(0--255)
*/
static void ApplicationFunctionSet_SmartRobotCarMotionControl(SmartRobotCarMotionControl direction, uint8_t is_speed)
{
  ApplicationFunctionSet Application_FunctionSet;
  static uint8_t directionRecord = 0;
  uint8_t Kp, UpperLimit;
  uint8_t speed = is_speed;
  //Control mode that requires straight line movement adjustment（Car will has movement offset easily in the below mode，the movement cannot achieve the effect of a relatively straight direction
  //so it needs to add control adjustment）
  Kp = 2;
  UpperLimit = 180;

  switch (direction)
  {
  case /* constant-expression */
      Forward:
      //When moving forward, enter the direction and position approach control loop processing
      ApplicationFunctionSet_SmartRobotCarLinearMotionControl(Forward, directionRecord, speed, Kp, UpperLimit);
      directionRecord = 1;
    break;
  case /* constant-expression */ Backward:
    /* code */
    //When moving backward, enter the direction and position approach control loop processing
      ApplicationFunctionSet_SmartRobotCarLinearMotionControl(Backward, directionRecord, speed, Kp, UpperLimit);
      directionRecord = 2;
    break;
  case /* constant-expression */ Left:
    /* code */
    directionRecord = 3;
    AppMotor.DeviceDriverSet_Motor_control(/*direction_A*/ direction_forw, /*speed_A*/ speed,
                                           /*direction_B*/ direction_back, /*speed_B*/ speed, /*controlED*/ control_enable); //Motor control
    break;
  case /* constant-expression */ Right:
    /* code */
    directionRecord = 4;
    AppMotor.DeviceDriverSet_Motor_control(/*direction_A*/ direction_back, /*speed_A*/ speed,
                                           /*direction_B*/ direction_forw, /*speed_B*/ speed, /*controlED*/ control_enable); //Motor control
    break;
  case /* constant-expression */ LeftForward:
    /* code */
    directionRecord = 5;
    AppMotor.DeviceDriverSet_Motor_control(/*direction_A*/ direction_forw, /*speed_A*/ speed,
                                           /*direction_B*/ direction_forw, /*speed_B*/ speed / 2, /*controlED*/ control_enable); //Motor control
    break;
  case /* constant-expression */ LeftBackward:
    /* code */
    directionRecord = 6;
    AppMotor.DeviceDriverSet_Motor_control(/*direction_A*/ direction_back, /*speed_A*/ speed,
                                           /*direction_B*/ direction_back, /*speed_B*/ speed / 2, /*controlED*/ control_enable); //Motor control
    break;
  case /* constant-expression */ RightForward:
    /* code */
    directionRecord = 7;
    AppMotor.DeviceDriverSet_Motor_control(/*direction_A*/ direction_forw, /*speed_A*/ speed / 2,
                                           /*direction_B*/ direction_forw, /*speed_B*/ speed, /*controlED*/ control_enable); //Motor control
    break;
  case /* constant-expression */ RightBackward:
    /* code */
    directionRecord = 8;
    AppMotor.DeviceDriverSet_Motor_control(/*direction_A*/ direction_back, /*speed_A*/ speed / 2,
                                           /*direction_B*/ direction_back, /*speed_B*/ speed, /*controlED*/ control_enable); //Motor control
    break;
  case /* constant-expression */ stop_it:
    /* code */
    directionRecord = 9;
    AppMotor.DeviceDriverSet_Motor_control(/*direction_A*/ direction_void, /*speed_A*/ 0,
                                           /*direction_B*/ direction_void, /*speed_B*/ 0, /*controlED*/ control_enable); //Motor control

    break;
  default:
    directionRecord = 10;
    break;
  }
}

/*
  Straight line movement control：For dual-drive motors, due to frequent motor coefficient deviations and many external interference factors,
  it is difficult for the car to achieve relative Straight line movement. For this reason, the feedback of the yaw control loop is added.
  direction：only forward/backward
  directionRecord：Used to update the direction and position data (Yaw value) when entering the function for the first time.
  speed：the speed range is 0~255
  Kp：Position error proportional constant（The feedback of improving location resuming status，will be modified according to different mode），improve damping control.
  UpperLimit：Maximum output upper limit control
*/
static void ApplicationFunctionSet_SmartRobotCarLinearMotionControl(SmartRobotCarMotionControl direction, uint8_t directionRecord, uint8_t speed, uint8_t Kp, uint8_t UpperLimit)
{
  static float Yaw; //Yaw
  static float yaw_So = 0;
  static uint8_t en = 110;
  static unsigned long is_time;
  if (en != directionRecord || millis() - is_time > 10)
  {
    AppMotor.DeviceDriverSet_Motor_control(/*direction_A*/ direction_void, /*speed_A*/ 0,
                                           /*direction_B*/ direction_void, /*speed_B*/ 0, /*controlED*/ control_enable); //Motor control
    AppMPU6050getdata.MPU6050_dveGetEulerAngles(&Yaw);
    is_time = millis();
  }
  //if (en != directionRecord)
  if (en != directionRecord)
  {
    en = directionRecord;
    yaw_So = Yaw;
  }
  //Add proportional constant Kp to increase rebound effect
  int R = (Yaw - yaw_So) * Kp + speed;
  if (R > UpperLimit)
  {
    R = UpperLimit;
  }
  else if (R < 10)
  {
    R = 10;
  }
  int L = (yaw_So - Yaw) * Kp + speed;
  if (L > UpperLimit)
  {
    L = UpperLimit;
  }
  else if (L < 10)
  {
    L = 10;
  }
  if (direction == Forward) //Forward
  {
    AppMotor.DeviceDriverSet_Motor_control(/*direction_A*/ direction_forw, /*speed_A*/ R,
                                           /*direction_B*/ direction_forw, /*speed_B*/ L, /*controlED*/ control_enable);
  }
  else if (direction == Backward) //Backward
  {
    AppMotor.DeviceDriverSet_Motor_control(/*direction_A*/ direction_back, /*speed_A*/ L,
                                           /*direction_B*/ direction_back, /*speed_B*/ R, /*controlED*/ control_enable);
  }
}


void ApplicationFunctionSet::CMD_MotorControl_xxx0()
{
  AppMotor.DeviceDriverSet_Motor_control(/*direction_A*/ direction_forw, /*speed_A*/ Right_motors,
                                         /*direction_B*/ direction_forw, /*speed_B*/ Left_motors, /*controlED*/ control_enable);
}

//////////////
/* Encoders */
//////////////
void ApplicationFunctionSet::encoders_value() const
{
  #if _Test_DeviceDriverSet_Encoders
  //Serial.print(digitalRead(encoderA));      // uncomment to see squarewave output
  // Serial.print('\t');
  //Serial.print(digitalRead(encoderB)+2);    // +2 shifts output B up so both A and B are visible
  // Serial.print('\t');
  //Serial.print(Dir);
  // Serial.print('\t');
  Serial.print("Encoder Right: ");
  Serial.print(AppEncoder.DeviceDriverSet_Encoder_ReadR());
  Serial.print("\t count:");
  Serial.print(AppEncoder.countR);
  Serial.print("\t Dir:");
  Serial.print(AppEncoder.Dir);
  Serial.println();
  Serial.print("Encoder Left: ");
  Serial.print(AppEncoder.DeviceDriverSet_Encoder_ReadL());
  Serial.print("\t count:");
  Serial.print(AppEncoder.countL);
  Serial.print("\t Dir:");
  Serial.print(AppEncoder.Dir);
  Serial.println();
  #endif
}
