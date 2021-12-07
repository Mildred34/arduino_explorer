/*
 * @Author: Alexis
 * @Date: 2021-12-01 17:41
 * @Description:
 * @FilePath:
 */
#include "encoders.h"

void DeviceDriverSet_Encoder::DeviceDriverSet_Encoder_Init()
{
  pinMode(PIN_Encoder_R, INPUT);
  pinMode(PIN_Encoder_L, INPUT);
}
