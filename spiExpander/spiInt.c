#include "interface.h"
#include <stdio.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>


int main(int argc, char *argv[]) {
  uint32_t *gpio;
  int fd,ret,length;
  uint8_t *buf;
  uint8_t addr;

  int k;
  if (argc!=3) {
    fprintf(stderr,"Fatal Error: must have two input args!\n");
    return(-1);
  }

  addr = strtol(argv[1],16);
  // Guaranteed long enough space (too long if there are any non hex chars)
  buf = (uint8_t *)malloc(strlen(argv[2])/2);
  
  gpio = SetupGPIO();
  fd = SetupSPI(gpio,0);

  struct spi_ioc_transfer transfer = {
    .tx_buf = (unsigned long)buf,
    .rx_buf = (unsigned long)buf,
    .len = ret,
    .delay_usecs = 0,
    .speed_hz = 10000000,
    .bits_per_word = 8,
    .tx_nbits = 1,
    .rx_nbits = 1
  };
  ret = ioctl(fd,SPI_IOC_MESSAGE(1),&transfer);
  RelinquishSPI(gpio,fd);
  CleanupGPIO(gpio);
  for (k=0;k<ret;k++) {
    if (k%4==0) printf(" ");
    printf("%02x",buf[k]);
    if (k%16==15) printf("\n");
  }
  printf("\n");
  free(buf);
  return(0);
}
