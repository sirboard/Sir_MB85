#include <stdlib.h>
#include <math.h>

#include "Sir_I2C_FRAM.h"


Sir_I2C_FRAM::Sir_I2C_FRAM(void);


bool Sir_I2C_FRAM::init(uint8_t addr) 
{
  i2c_address = addr;
  Wire.begin();
  
  uint16_t manufacturerID, productID;
  getDeviceID(&manufacturerID, &productID);
  
  if (manufacturerID != 0x00A) return false;
  if (productID != 0x510)      return false;

  return true;
}

void Sir_I2C_FRAM::write(uint16_t addr, uint8_t value)
{
  Wire.beginTransmission(addr);

  Wire.write(addr >> 8);
  Wire.write(addr & 0xFF);
  Wire.write(value);

  Wire.endTransmission();
}

uint8_t Sir_I2C_FRAM::read(uint16_t addr)
{
  Wire.beginTransmission(i2c_address);

  Wire.write(addr >> 8);
  Wire.write(addr & 0xFF);
  Wire.endTransmission();

  Wire.requestFrom(i2c_address, (uint8_t)1);
  
  return Wire.read();
}

void Sir_I2C_FRAM::getDeviceID(uint16_t *manufacturerID, uint16_t *productID)
{
  uint8_t temp[3] = { 0, 0, 0 };
  
  Wire.beginTransmission(SLAVE_ID >> 1);
  Wire.write(i2c_address << 1);
  Wire.endTransmission(false);

  Wire.requestFrom(SLAVE_ID >> 1, 3);
  temp[0] = Wire.read();
  temp[1] = Wire.read();
  temp[2] = Wire.read();

  *manufacturerID = (a[0] << 4) + (a[1]  >> 4);
  *productID = ((a[1] & 0x0F) << 8) + a[2];
}