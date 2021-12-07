/*
 * @Author: Alexis
 * @Date: 2021-12-01 17:41
 * @Description:
 * @FilePath:
 */
#include "voltage.h"

void DeviceDriverSet_Voltage::DeviceDriverSet_Voltage_Init(void)
{
  pinMode(PIN_Voltage, INPUT);
  //analogReference(INTERNAL);
}

float DeviceDriverSet_Voltage::DeviceDriverSet_Voltage_getAnalogue(void)
{
  //float Voltage = ((analogRead(PIN_Voltage) * 5.00 / 1024) * 7.67); //7.66666=((10 + 1.50) / 1.50)
  float Voltage = (analogRead(PIN_Voltage) * 0.0375);
  Voltage = Voltage + (Voltage * 0.08); //Compensation 8%
  //return (analogRead(PIN_Voltage) * 5.00 / 1024) * ((10 + 1.50) / 1.50); //Read voltage value
  return Voltage;
}
