#include "interface.h"
#include <stdio.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#define BUFLEN 8

int main(void) {
  uint32_t *gpio;
  int fd,ret;
  uint8_t txBuf[BUFLEN] = {0x9f, 0xad, 0xbe, 0xef};
  uint8_t rxBuf[BUFLEN];
  int k;

  gpio = SetupGPIO();
  fd = SetupSPI(gpio,0);

  struct spi_ioc_transfer transfer = {
    .tx_buf = (unsigned long)txBuf,
    .rx_buf = (unsigned long)rxBuf,
    .len = BUFLEN,
    .delay_usecs = 0,
    .speed_hz = 10000000,
    .bits_per_word = 8,
    .tx_nbits = 1,
    .rx_nbits = 1
  };
  ret = ioctl(fd,SPI_IOC_MESSAGE(1),&transfer);
  RelinquishSPI(gpio,fd);
  CleanupGPIO(gpio);
  for (k=0;k<BUFLEN;k++) {
    if (k%4==0) printf(" ");
    printf("%02x",rxBuf[k]);
    if (k%16==15) printf("\n");
  }
  printf("\n");
  
}
