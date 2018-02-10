#include "spiExpander.h"
#include <wiringPi.h>

#define FSEL_ALT0 4

void setSPIAddr(portNums addr) {
  pinMode(SPI_EXPANDER_PINA2,OUTPUT);
  pinMode(SPI_EXPANDER_PINA1,OUTPUT);
  pinMode(SPI_EXPANDER_PINA0,OUTPUT);
  digitalWrite(SPI_EXPANDER_PINA2,addr&0x04U);
  digitalWrite(SPI_EXPANDER_PINA1,addr&0x02U);
  digitalWrite(SPI_EXPANDER_PINA0,addr&0x01U);
}

void activateSPI(void) {
  pinModeAlt(SPI_MOSI,FSEL_ALT0);
  pinModeAlt(SPI_MISO,FSEL_ALT0);
  pinModeAlt(SPI_SCLK,FSEL_ALT0);
  pinModeAlt(SPI_CE0 ,FSEL_ALT0);
  pinModeAlt(SPI_CE1 ,FSEL_ALT0);
}

void relinquishSPI(void) {
  pinMode(SPI_MOSI,INPUT);
  pinMode(SPI_MISO,INPUT);
  pinMode(SPI_SCLK,INPUT);
  pinMode(SPI_CE0 ,INPUT);
  pinMode(SPI_CE1 ,INPUT);
}
