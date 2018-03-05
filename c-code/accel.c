#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "interface.h"
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  unsigned char buf[64];
  uint32_t *gpio;
  int fd,retval;
  char tempStr[3];
  char *inStr;
  int k,m,n;
  
  gpio = SetupGPIO();
  fd = SetupSPI(gpio,8,3);

  if (argc<2) return 0;
  inStr = argv[1];
  for (k=m=n=0; inStr[k];k++) {
    if (isxdigit(inStr[k])) {
      tempStr[m++] = inStr[k];
      if (m>=2) {
	buf[n++] = (unsigned char)strtoul(tempStr,NULL,16);
	m = 0;
      }
    }
  }
		
    
  struct spi_ioc_transfer transfer = {
    .tx_buf = (unsigned long)buf,
    .rx_buf = (unsigned long)buf,
    .len = n,
    .delay_usecs = 0,
    .speed_hz = 1000000,
    .bits_per_word = 8,
    .tx_nbits = 1,
    .rx_nbits = 1
  };

  retval = ioctl(fd,SPI_IOC_MESSAGE(1),&transfer);

  for (int k=0;k<n-1;k++)
    printf("%02x ",buf[k+1]);
  printf("\n");
  
  RelinquishSPI(gpio,fd);
  CleanupGPIO(gpio);  

  return 0;
}
