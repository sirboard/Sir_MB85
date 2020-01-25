#ifndef _SIR_I2C_FRAM_H_
#define _SIR_I2C_FRAM_H_

#include <Arduino.h>
#include <Wire.h>

#define DEFAULT_ADDRESS     0x50
#define SLAVE_ID            0xF8

#define MANUFACTURER_ID     0x00A
#define PRODUCT_ID          0x510


class Sir_I2C_FRAM {
 private:
  uint8_t i2c_address;
  boolean initialised;

 public:
  Sir_I2C_FRAM();
  
  boolean  init();
  void     write (uint16_t, uint8_t);
  uint8_t  read  (uint16_t);
  void     getDeviceID(uint16_t *, uint16_t *);
};

#endif