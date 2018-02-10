#include <stdio.h>
#include <ctype.h>
#include "interface.h"
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#define PORT 0
#define SPEED 1000000

int main(int argc, char *argv[]) {
  FILE * fPtr = stdin;
  char inStr[1025];
  char buf[256];
  char tempStr[3];
  char *inPtr;
  int retval,fd;
  uint32_t *gpio;
  int k,m,n;
  uint8_t portNum = PORT;

  if (argc>1)
    portNum = atoi(argv[1]);
  
  //wiringPiSetupGpio();
  //wiringPiSPISetup(PORT,SPEED);
  //setSPIAddr(portNum);
  gpio = SetupGPIO();
  fd = SetupSPI(gpio,portNum);
  struct spi_ioc_transfer transfer = {
    .tx_buf = (unsigned long)buf,
    .rx_buf = (unsigned long)buf,
    .len = 257,
    .delay_usecs = 0,
    .speed_hz = SPEED,
    .bits_per_word = 8,
    .tx_nbits = 1,
    .rx_nbits = 1
  };

  tempStr[2] = '\0';
  while(!feof(fPtr)) {
    //Read a line of input characters and proceed if we didn't hit EOF
    if(fgets(inStr,1025,fPtr)) {
      
      //Translate valid pairs of hex characters in the input into bytes to send
      for (k=m=n=0; inStr[k];k++) {
	if (isxdigit(inStr[k])) {
	  tempStr[m++] = inStr[k];
	  if (m>=2) {
	    buf[n++] = (unsigned char)strtoul(tempStr,NULL,16);
	    m = 0;
	  }
	}
      }
      // Dump the return values back to stdout
      if (n>0) {
	
	//	retval = wiringPiSPIDataRW(PORT,buf,n);
	transfer.len = n;
	retval = ioctl(fd,SPI_IOC_MESSAGE(1),&transfer);
	for (k=0;k<n;k++) {
	  printf("%02x",buf[k]);
	  if (k%32==31)
	    printf("\n");
	  else if (k%2==1)
	    printf(" ");
	}
	printf("\n");
	fflush(stdout);
      }
    }
  }
  RelinquishSPI(gpio,fd);
  CleanupGPIO(gpio);  
  return(0);

}
