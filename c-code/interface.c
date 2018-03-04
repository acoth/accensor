#define BASE_ADDR 0x00200000
#define BLOCK_SIZE 4096


#include "interface.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

uint32_t *SetupGPIO(void) {
  int fd;
  uint32_t *gpio;
  fd = open("/dev/gpiomem",O_RDWR |O_SYNC | O_CLOEXEC );
  gpio = (uint32_t *)mmap(0,BLOCK_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, BASE_ADDR);
  close(fd);
  return(gpio);
}

void CleanupGPIO(uint32_t *gpio) {
  munmap(gpio,BLOCK_SIZE);
}

int SetupSPI(uint32_t *gpio,uint8_t addr,char mode) {
  int fd;
  SetPinMode(gpio,SPI_MOSI,ALT0);
  SetPinMode(gpio,SPI_MISO,ALT0);
  SetPinMode(gpio,SPI_SCLK,ALT0);
  SetPinMode(gpio,SPI_CSB0,OUTPUT);
  SetPinMode(gpio,SPI_CSB1,OUTPUT);

  SetPinMode(gpio,MUXSEL0,OUTPUT);
  SetPinMode(gpio,MUXSEL1,OUTPUT);
  SetPinMode(gpio,MUXSEL2,OUTPUT);

  WritePin(gpio,MUXSEL2,addr&0x04);
  WritePin(gpio,MUXSEL1,addr&0x02);
  WritePin(gpio,MUXSEL0,addr&0x01);
  //  WritePin(gpio,SPI_CSB0,0);
  
  if (addr&0x08)
    fd = open("/dev/spidev0.1",O_RDWR);
  else
    fd = open("/dev/spidev0.0",O_RDWR);

  //  mode = SPI_MODE_1;
  uint32_t speed = 30000000; 
  ioctl(fd,SPI_IOC_WR_MODE,&mode);
  ioctl(fd,SPI_IOC_WR_MAX_SPEED_HZ,&speed); 
  return(fd);
}

void RelinquishSPI(uint32_t *gpio,int fd) {
  close(fd);
  SetPinMode(gpio,SPI_MOSI,INPUT);
  SetPinMode(gpio,SPI_MISO,INPUT);
  SetPinMode(gpio,SPI_SCLK,INPUT);
  SetPinMode(gpio,SPI_CSB0,INPUT);
  SetPinMode(gpio,SPI_CSB1,INPUT);
}

void SetPinMode(uint32_t *gpio,uint8_t pin, uint8_t mode) {
  uint32_t mask;
  mask = 0x07<<(3*(pin%10));
  mode = (mode & 0x07);
  gpio[pin/10] &= (~mask);
  gpio[pin/10] |= mode << (3*(pin%10));
}

void SetPin(uint32_t *gpio,uint8_t pin) {
  gpio[7+pin/32] = 1 << pin%32;
}

void ClearPin(uint32_t *gpio,uint8_t pin) {
  gpio[10+pin/32] = 1 << pin%32;
}

void WritePin(uint32_t *gpio,uint8_t pin, int value) {
  if (value)
    SetPin(gpio,pin);
  else
    ClearPin(gpio,pin);
}
