/*
 * @Author: Alexis
 * @Date: 2021-12-01 17:41
 * @Description:
 * @FilePath:
 */
#include "encoders.h"

volatile int DeviceDriverSet_Encoder::countR = 0;
volatile int DeviceDriverSet_Encoder::countL = 0;
int DeviceDriverSet_Encoder::Dir = 0;

void DeviceDriverSet_Encoder::DeviceDriverSet_Encoder_Init()
{

  pinMode(PIN_Encoder_R, INPUT);
  pinMode(PIN_Encoder_L, INPUT);

  attachInterrupt(digitalPinToInterrupt(PIN_Encoder_R), DeviceDriverSet_Encoder_pulseR, RISING);
  attachInterrupt(digitalPinToInterrupt(PIN_Encoder_L), DeviceDriverSet_Encoder_pulseL, RISING);
}

float DeviceDriverSet_Encoder::DeviceDriverSet_Encoder_ReadR(void)
{
  float encoderR = digitalRead(PIN_Encoder_R);
  return encoderR;
}

float DeviceDriverSet_Encoder::DeviceDriverSet_Encoder_ReadL(void)
{
  float encoderL = digitalRead(PIN_Encoder_L);
  return encoderL;
}

void DeviceDriverSet_Encoder::DeviceDriverSet_Encoder_checkDirection(){
  if(digitalRead(PIN_Encoder_L) ==  HIGH){
    Dir = 1;
  }
  else{
    Dir = -1;
  }
}

void DeviceDriverSet_Encoder::DeviceDriverSet_Encoder_pulseR(){
  DeviceDriverSet_Encoder_checkDirection();
  countR += Dir;
}

void DeviceDriverSet_Encoder::DeviceDriverSet_Encoder_pulseL(){
  countL += Dir;
}
