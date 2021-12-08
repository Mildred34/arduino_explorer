/*
 * @Author: Alexis
 * @Date: 2021-10-01 17:13
 * @LastEditors: Alexis
 * @Description: Factory for modules
 * @FilePath:
 */

#include <avr/wdt.h>
#include "ApplicationFunctionSet_xxx0.h"

void setup()
{
  // put your setup code here, to run once:
  Application_FunctionSet.ApplicationFunctionSet_Init();

  // Watchdog timer
  wdt_enable(WDTO_2S);
}

void loop()
{
  //put your main code here, to run repeatedly :
  wdt_reset();

  /* Update sensors value */
  Application_FunctionSet.ApplicationFunctionSet_SensorDataUpdate();

  /* Update command */
  Application_FunctionSet.ApplicationFunctionSet_SerialPortDataAnalysis();

  /* Motors Control */
  Application_FunctionSet.CMD_MotorControl_xxx0();

}
