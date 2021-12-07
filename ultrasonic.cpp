/*
 * @Author: Alexis
 * @Date: 2021-12-01 17:41
 * @Description:
 * @FilePath:
 */

#include "ultrasonic.h"

 /*ULTRASONIC*/
 //#include <NewPing.h>
 // NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
 void DeviceDriverSet_ULTRASONIC::DeviceDriverSet_ULTRASONIC_Init(void)
 {
   pinMode(ECHO_PIN, INPUT); //Ultrasonic module initialization
   pinMode(TRIG_PIN, OUTPUT);
 }
