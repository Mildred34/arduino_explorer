/*
 * @Author: Alexis
 * @Date: 2021-12-01 17:41
 * @Description:
 * @FilePath:
 */
#ifndef _VOLTAGE_H_
#define _VOLTAGE_H_
#include <Arduino.h>

/*Voltage Detection*/
class DeviceDriverSet_Voltage
{
public:
  void DeviceDriverSet_Voltage_Init(void);
  float DeviceDriverSet_Voltage_getAnalogue(void);
private:
#define PIN_Voltage A3
};


extern DeviceDriverSet_Voltage AppVoltage;
#endif
