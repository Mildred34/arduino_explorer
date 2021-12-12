/*
 * @Author: Alexis
 * @Date: 2021-12-01 17:41
 * @Description:
 * @FilePath:
 */


#ifndef _ENCODERS_H_
#define _ENCODERS_H_

#include <Arduino.h>

/* ENCODERS */
class DeviceDriverSet_Encoder
{
public:
  void DeviceDriverSet_Encoder_Init(void);
  int DeviceDriverSet_Encoder_ReadR(void);
  int DeviceDriverSet_Encoder_ReadL(void);
#if _Test_DeviceDriverSet
  // void DeviceDriverSet_Encoder_Test(void);
#endif
  // void DeviceDriverSet_Encoder_read();
  static void DeviceDriverSet_Encoder_checkDirection();
  static void DeviceDriverSet_Encoder_pulseR();
  static void DeviceDriverSet_Encoder_pulseL();
private:
//TB6612
#define PIN_Encoder_R 11
#define PIN_Encoder_L A2

public:
static volatile int countR;
static volatile int countL;

static int Dir;  // 1 = CW
              // 0 = Stationary
              // -1 = CCW
};

extern DeviceDriverSet_Encoder AppEncoder;

#endif
