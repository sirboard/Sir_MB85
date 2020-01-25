#ifndef _SIR_SPI_FRAM_H_
#define _SIR_SPI_FRAM_H_

#include <Arduino.h>
#include <SPI.h>

// Status register
#define WPEN       0x80
#define BP1        0x08
#define BP0        0x04
#define WEL        0x02

// OP-CODE
#define WREN       0x06
#define WRDI       0x04
#define RDSR       0x05
#define WRSR       0x01
#define READ       0x03
#define WRITE      0x02
#define RDID       0x9F
#define SLEEP      0xB9

#define MAN_ID_0   0x04
#define MAN_ID_1   0x7f

#define PROD_ID_0  0x0302
#define PROD_ID_1  0x7f7f


class Sir_SPI_FRAM {
private:
  uint8_t _nAddressSizeBytes, _cs;
  SPIClass *_spi;
  SPISettings spiSettings;

public:
  Sir_SPI_FRAM(int8_t, SPIClass *);

  boolean init(uint8_t, unit16_t);

  uint8_t getStatus(void);
  void setStatus(uint8_t);

  void writeByte();
  uint8_t readByte();

  void setStatus(uint8_t);
  uint8_t getStatus();

  void write(uint32_t, const uint8_t *, size_t);
  void read(uint32_t, const uint8_t *, size_t);

  void writeEnable(bool);

  uint8_t readByte(uint32_t);
  void writeByte(uint32_t, uint8_t);

  void writeAddress(uint32_t);

  uint8_t getAddressSize(); 

  void getDeviceID(uint8_t *, uint16_t *);

  void erase();
};
