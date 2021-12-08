/*
 * @Author: Alexis
 * @Date: 2021-12-01 17:41
 * @Description: MPU6050 Data solution
 * @FilePath:
 */
#ifndef _MPU6050_getdata_H_
#define _MPU6050_getdata_H_
#include <Arduino.h>
#include "Wire.h"

class MPU6050_getdata
{
public:
  bool MPU6050_dveInit(void);
  bool MPU6050_calibration(void);
  bool MPU6050_dveGetEulerAngles(float *Yaw);
  
public:
  //int16_t ax, ay, az, gx, gy, gz;
  int16_t gz;
  //float pith, roll, yaw;
  unsigned long now, lastTime = 0;
  float dt;      //Derivative time
  float agz = 0; //Angle variable
  long gzo = 0;  //Gyro offset
};

extern MPU6050_getdata MPU6050Getdata;
#endif
