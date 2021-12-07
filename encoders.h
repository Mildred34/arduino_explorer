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
#if _Test_DeviceDriverSet
  // void DeviceDriverSet_Encoder_Test(void);
#endif
  // void DeviceDriverSet_Encoder_read();
private:
//TB6612
#define PIN_Encoder_R 11
#define PIN_Encoder_L A0
};

extern DeviceDriverSet_Encoder AppEncoder;

#endif
