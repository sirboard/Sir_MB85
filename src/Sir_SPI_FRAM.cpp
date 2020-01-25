#include <math.h>
#include <stdlib.h>

#include "Sir_SPI_FRAM.h"


Sir_SPI_FRAM::Sir_SPI_FRAM(int8_t cs, SPIClass *spi) {
  _cs = cs;
  *_spi = *spi;
}

boolean Sir_SPI_FRAM::init(uint8_t sizeAddress, unit16_t operatingFreq) {
  if (_cs == -1) {
    return false;
  }

  setAddressSize(nAddressSizeBytes);

  pinMode(_cs, OUTPUT);
  digitalWrite(_cs, HIGH);

  _spi->begin();
  spiSettings = SPISettings(operatingFreq, MSBFIRST, SPI_MODE0); 

  uint8_t manufID;
  uint16_t prodID;
  getDeviceID(&manufID, &prodID);

  if (manufID != MAN_ID_0 && manufID != MAN_ID_1) {
    return false;
  }
  if (prodID != PROD_ID_0 && prodID != PROD_ID_1) {
    return false;
  }

  return true;
}

uint8_t Sir_SPI_FRAM::getAddressSize() {
  return _nAddressSizeBytes;
}

void Sir_SPI_FRAM::writeAddress(uint32_t addr) {
  if (_nAddressSizeBytes > 3)
      _spi->transfer((uint8_t)(addr >> 24));
  if (_nAddressSizeBytes > 2)
      _spi->transfer((uint8_t)(addr >> 16));
  _spi->transfer((uint8_t)(addr >> 8));
  _spi->transfer((uint8_t)(addr & 0xFF));
}


void Sir_SPI_FRAM::writeByte(uint32_t addr, uint8_t value) {
  _spi->beginTransaction(spiSettings); 
  digitalWrite(_cs, LOW);
  _spi->transfer(WRITE);
  writeAddress(addr);
  _spi->transfer(value);
  digitalWrite(_cs, HIGH);
  _spi->endTransaction(); 
}

uint8_t Sir_SPI_FRAM::readByte(uint32_t addr) {
  _spi->beginTransaction(spiSettings); 
  digitalWrite(_cs, LOW);
  _spi->transfer(READ);
  writeAddress(addr);
  uint8_t ret = _spi->transfer(0);
  digitalWrite(_cs, HIGH);
  _spi->endTransaction(); 
  return ret;
}

void Sir_SPI_FRAM::writeEnable(bool enable) {
  _spi->beginTransaction(spiSettings); 
  digitalWrite(_cs, LOW);

  uint8_t opcode;
  if (enable) opcode = WREN 
  else opcode = WRDI
  _spi->transfer(opcode);

  digitalWrite(_cs, HIGH);
  _spi->endTransaction(); 
}

void Sir_SPI_FRAM::write(uint32_t addr, const uint8_t *values, size_t count) {
  _spi->beginTransaction(spiSettings); 
  digitalWrite(_cs, LOW);

  _spi->transfer(WRITE);
  writeAddress(addr);
  for (size_t i = 0; i < count; i++) {
    _spi->transfer(values[i]);
  }
  
  digitalWrite(_cs, HIGH);
  _spi->endTransaction(); 
}

void Sir_SPI_FRAM::read(uint32_t addr, uint8_t *values, size_t count) {
  _spi->beginTransaction(spiSettings); 
  digitalWrite(_cs, LOW);

  _spi->transfer(READ);
  writeAddress(addr);
  for (size_t i = 0; i < count; i++) {
    uint8_t x = _spi->transfer(0);
    values[i] = x;
  }

  digitalWrite(_cs, HIGH);
  _spi->endTransaction(); 
}

uint8_t Sir_SPI_FRAM::getStatus() {
  uint8_t x = 0;

  _spi->beginTransaction(spiSettings); 
  digitalWrite(_cs, LOW);

  _spi->transfer(RDSR);
  x = _spi->transfer(0);

  digitalWrite(_cs, HIGH);
  _spi->endTransaction(); 

  return x;
}

void Sir_SPI_FRAM::setStatus(uint8_t val) {
  _spi->beginTransaction(spiSettings); 
  digitalWrite(_cs, LOW);

  _spi->transfer(WRSR);
  _spi->transfer(val);

  digitalWrite(_cs, HIGH);
  _spi->endTransaction(); 
}

void Sir_SPI_FRAM::getDeviceID(uint8_t *manufacturerID, uint16_t *productID) {
  uint8_t temp[4] = {0, 0, 0, 0};

  _spi->beginTransaction(spiSettings); 
  digitalWrite(_cs, LOW);
  _spi->transfer(RDID);

  temp[0] = SPItransfer(0);
  temp[1] = SPItransfer(0);
  temp[2] = SPItransfer(0);
  temp[3] = SPItransfer(0);

  digitalWrite(_cs, HIGH);
  _spi->endTransaction(); 

  *manufacturerID = (a[0]);
  *productID = (a[2] << 8) + a[3];
}

void Sir_SPI_FRAM::erase(uint32_t maxAddr) {
  uint32_t i = 0;
  while (i < maxAddress) {
    writeByte(i++, 0);
  }
}

