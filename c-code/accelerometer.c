#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "interface.h"
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <stdlib.h>
#include "accelerometer.h"

void WriteReg(unsigned char reg, unsigned char val) {
  unsigned char buf[2];
  uint32_t *gpio;
  int fd,retval;
  
  gpio = SetupGPIO();
  fd = SetupSPI(gpio,8,3);
  buf[0] = reg&0x3f;
  buf[1] = val;
  struct spi_ioc_transfer transfer = {
    .tx_buf = (unsigned long)buf,
    .rx_buf = (unsigned long)buf,
    .len = 2,
    .delay_usecs = 0,
    .speed_hz = 1000000,
    .bits_per_word = 8,
    .tx_nbits = 1,
    .rx_nbits = 1
  };

  retval = ioctl(fd,SPI_IOC_MESSAGE(1),&transfer);

  RelinquishSPI(gpio,fd);
  CleanupGPIO(gpio);    
}

unsigned char ReadReg(unsigned char reg) {
  unsigned char buf[2];
  uint32_t *gpio;
  int fd,retval;
  
  gpio = SetupGPIO();
  fd = SetupSPI(gpio,8,3);
  buf[0] = (reg&0x3f)|0x80;
  buf[1] = '\0';
  struct spi_ioc_transfer transfer = {
    .tx_buf = (unsigned long)buf,
    .rx_buf = (unsigned long)buf,
    .len = 2,
    .delay_usecs = 0,
    .speed_hz = 1000000,
    .bits_per_word = 8,
    .tx_nbits = 1,
    .rx_nbits = 1
  };

  retval = ioctl(fd,SPI_IOC_MESSAGE(1),&transfer);

  RelinquishSPI(gpio,fd);
  CleanupGPIO(gpio);
  return(buf[1]);
}

void ReadAccelerations(float accelerations[3]) {
  unsigned char buf[7];
  uint32_t *gpio;
  int fd,retval;
  int temp;

  gpio = SetupGPIO();
  fd = SetupSPI(gpio,8,3);
  buf[0] = 0xf2;
  struct spi_ioc_transfer transfer = {
    .tx_buf = (unsigned long)buf,
    .rx_buf = (unsigned long)buf,
    .len = 7,
    .delay_usecs = 0,
    .speed_hz = 1000000,
    .bits_per_word = 8,
    .tx_nbits = 1,
    .rx_nbits = 1
  };

  retval = ioctl(fd,SPI_IOC_MESSAGE(1),&transfer);

  RelinquishSPI(gpio,fd);
  CleanupGPIO(gpio);

  temp = (buf[2]<<8)+buf[1];
  if (temp >= 32768) temp -= 65536;
  accelerations[0] = temp/2048.0;

  temp = (buf[4]<<8)+buf[3];
  if (temp >= 32768) temp -= 65536;
  accelerations[1] = temp/2048.0;

  temp = (buf[6]<<8)+buf[5];
  if (temp >= 32768) temp -= 65536;
  accelerations[2] = temp/2048.0;

}

