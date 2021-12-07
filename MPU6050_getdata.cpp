/*
 * @Author: Alexis
 * @Date: 2021-12-01 17:41
 * @Description: MPU6050 Data solution
 * @FilePath:
 */


 #include "I2Cdev.h"
 #include "MPU6050.h"
 #include "MPU6050_getdata.h"
 #include <stdio.h>
 #include <math.h>

 MPU6050 accelgyro;
 MPU6050_getdata MPU6050Getdata;

bool MPU6050_getdata::MPU6050_dveInit(void)
{
  Wire.begin();
  uint8_t chip_id = 0x00;
  uint8_t cout;
  do
  {
    chip_id = accelgyro.getDeviceID();
    Serial.print("MPU6050_chip_id: ");
    Serial.println(chip_id);
    delay(10);
    cout += 1;
    if (cout > 10)
    {
      return true;
    }
  } while (chip_id == 0X00 || chip_id == 0XFF); //Ensure that the slave device is online（Wait forcibly to get the ID）
  accelgyro.initialize();
  // unsigned short times = 100; //Sampling times
  // for (int i = 0; i < times; i++)
  // {
  //   gz = accelgyro.getRotationZ();
  //   gzo += gz;
  // }
  // gzo /= times; //Calculate gyroscope offset
  return false;
}

bool MPU6050_getdata::MPU6050_calibration(void)
{
  unsigned short times = 100; //Sampling times
  for (int i = 0; i < times; i++)
  {
    gz = accelgyro.getRotationZ();
    gzo += gz;
  }
  gzo /= times; //Calculate gyroscope offset

  // gzo = accelgyro.getRotationZ();
  return false;
}
