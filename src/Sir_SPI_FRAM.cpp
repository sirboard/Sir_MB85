#include <math.h>
#include <stdlib.h>

#include "Sir_SPI_FRAM.h"


Sir_SPI_FRAM::Sir_SPI_FRAM(int8_t cs, SPIClass *spi) {
  _cs = cs;
  _initialized = false;
  *_spi = *spi;
}

boolean Sir_SPI_FRAM::init(uint8_t sizeAddress) {
  if (_cs == -1) {
    return false;
  }

  setAddressSize(nAddressSizeBytes);

  pinMode(_cs, OUTPUT);
  digitalWrite(_cs, HIGH);

  _spi->begin();
  spiSettings = SPISettings(20000000, MSBFIRST, SPI_MODE0); 

  uint8_t manufID;
  uint16_t prodID;
  getDeviceID(&manufID, &prodID);

  if (manufID != 0x04 && manufID != 0x7f) {
    return false;
  }
  if (prodID != 0x0302 && prodID != 0x7f7f) {
    return false;
  }

  _initialized = true;

  return true;
}