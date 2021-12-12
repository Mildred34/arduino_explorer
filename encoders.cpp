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

  pinMode(PIN_Encoder_R, INPUT_PULLUP);
  pinMode(PIN_Encoder_L, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(PIN_Encoder_R), DeviceDriverSet_Encoder_pulseR, RISING);
  attachInterrupt(digitalPinToInterrupt(PIN_Encoder_L), DeviceDriverSet_Encoder_pulseL, RISING);
}

int DeviceDriverSet_Encoder::DeviceDriverSet_Encoder_ReadR(void)
{
  int encoderR = digitalRead(PIN_Encoder_R);
  return encoderR;
}

int DeviceDriverSet_Encoder::DeviceDriverSet_Encoder_ReadL(void)
{
  int encoderL = digitalRead(PIN_Encoder_L);
  return encoderL;
}

void DeviceDriverSet_Encoder::DeviceDriverSet_Encoder_checkDirection(){
/* Le if est utile si on fait l'encodeur en quadrature en utilisant un deuxième aimant */
  Dir = 1;
}

void DeviceDriverSet_Encoder::DeviceDriverSet_Encoder_pulseR(){
  DeviceDriverSet_Encoder_checkDirection();
  countR += Dir;
}

void DeviceDriverSet_Encoder::DeviceDriverSet_Encoder_pulseL(){
  countL += Dir;
}
