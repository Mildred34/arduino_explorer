/*
 * @Author: Alexis
 * @Date: 2021-12-01 17:41
 * @Description:
 * @FilePath:
 */
#include "servom.h"

Servo myservo; // create servo object to control a servo

/**
 * [voiddelay_xxx description]
 * @param  _ms  délai en ms
 *
 */
static void
delay_xxx(uint16_t _ms)
{
  wdt_reset();
  for (unsigned long i = 0; i < _ms; i++)
  {
    delay(1);
  }
}

/**
 * [DeviceDriverSet_Servo::DeviceDriverSet_Servo_Init Initialisation
 * des pins du servo moteur et de sa position initiale]
 * @param Position_angle  Angle de départ du servo
 */
void DeviceDriverSet_Servo::DeviceDriverSet_Servo_Init(unsigned int Position_angle)
{
  myservo.attach(PIN_Servo_z, 500, 2400); //500: 0 degree  2400: 180 degree
  myservo.attach(PIN_Servo_z);
  myservo.write(Position_angle); //sets the servo position according to the 90（middle）
  delay_xxx(500);

  myservo.detach();
}
