#ifndef _SIR_SPI_FRAM_H_
#define _SIR_SPI_FRAM_H_

#include <Arduino.h>
#include <SPI.h>

 #DEFINE WREN_CMD 0b0110  
 #DEFINE WRDI_CMD 0b0100  
 #DEFINE RDSR_CMD 0b0101  
 #DEFINE WRSR_CMD 0b0001  
 #DEFINE RDID_CMD 0b10011111  
 #DEFINE READ_CMD 0b0011  
 #DEFINE WRITE_CMD 0b0010  

class Sir_SPI_FRAM {
private:

public:
  Sir_SPI_FRAM();

  boolean init(uint8_t);

};
