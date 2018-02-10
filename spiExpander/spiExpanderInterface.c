#include "spiExpanderInterface.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

static uint32_t mode = SPI_MODE_0;
static uint8_t bits = 8;
static uint32_t speed = 16000000;

int SPIRW(int addr, uint8_t* txBuf, uint8_t *rxBuf, uint32_t len) {

  int fd, retval;
  addr = addr & 0xf;

  activateSPIBus();
  
  if (addr&0x8) {
    fd = open("/dev/spidev0.1",O_RDWR);
  } else {
    fd = open("/dev/spidev0.0",O_RDWR);
  }
  if (fd<0) perror("Failed to open device!\n");

  if (ioctl(fd,SPI_IOC_WR_MODE32, &mode)) fprintf(stderr,"Failed to set SPI mode!\n");
  if (ioctl(fd,SPI_IOC_WR_BITS_PER_WORD, &bits)) fprintf(stderr,"Failed to set SPI bits-per-word!\n");
  if (ioctl(fd,SPI_IOC_WR_MAX_SPEED, &speed)) fprintf(stderr,"Failed to set SPI speed!\n");

  struct spi_ioc_transfer transfer = {
    .tx_buf = (unsigned long)txBuf,
    .rx_buf = (unsigned long)rxBuf,
    .len = len,
    .delay_usecs = 0,
    .speed_hz = speed,
    .bits_per_word = bits,
    .tx_nbits = 1,
    .rx_nbits = 1
  };

  setSPIAddr(addr);


  
  close(fd);
  relinquishSPIBus();  // Hi-z the bus pins in case the FPGA needs to be master so it can read it's flash

  return(0);
}

void activateSPIBus(void){
  // Set mode bits for pins 7-11 to 0b100 (ALT0)
  gpio[0] = (gpio[0] & 0xc01fffff) | 0x24800000;
  gpio[1] = (gpio[1] & 0xffffffc0) | 0x00000024;
  // Set mode bits for pins 22-25 to 0b001 (OUTPUT)
  gpio[2] = (gpio[2] & 0xfffc003f) | 0x00009240;  
}

void setSPIAddr(uint32_t addr) {  
  gpio[7] |= (addr&0x7)<<23;
  gpio[10]|= ((~addr)&0x7)<<23;
}

void setProgb(uint32_t bit) {
  if (bit)
    gpio[7]  |= 1<<22;
  else
    gpio[10] |= 1<<22;
}
