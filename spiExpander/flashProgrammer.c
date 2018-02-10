#include <stdio.h>
#include <stdint.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include "spiExpander.h"

#define PORT 1
#define SPEED 10000000

void sectorErase(uint16_t page);
void waitForWIP(void);
void setWriteEnable(void);

int main(void) {
  FILE * fPtr = stdin;
  char buf[257];
  int retval,count,fd;
  uint16_t page;
  wiringPiSetupGpio();
  activateSPI();
  fd = wiringPiSPISetup(PORT,SPEED);
  printf("fd=%d\n",fd);
  setSPIAddr(MA742_FLASH);
  pinMode(MA742_PROGB,OUTPUT);
  digitalWrite(MA742_PROGB,0);
  buf[0] = 0x9f;
  buf[1] = 0x00;
  buf[2] = 0x00;
  buf[3] = 0x00;
  retval = wiringPiSPIDataRW(PORT,buf,4);
  printf("Flash ID reads back as %02x %02x %02x %02x\n",buf[0],buf[1],buf[2],buf[3]);
  page = 0;
  while(!feof(fPtr) && page<8192) {
    if (0==page%256) {
      printf("Erasing sector %d... ",page/256);
      fflush(stdout);
      sectorErase(page);
      printf("and writing it...\n");
      fflush(stdout);
    }
    count = fread(buf+1,1,256,stdin);
    if (count>0) {
      setWriteEnable();
      buf[0] = 0x02;
      retval = wiringPiSPIDataRW(PORT,buf,count);
      waitForWIP();
    }
    page++;
  }
  close(fd);
  relinquishSPI();
  digitalWrite(MA742_PROGB,1);
  return(0);
}


void setWriteEnable(void) {
  char buf[1] = {0x06};
  int retval;
  retval = wiringPiSPIDataRW(PORT,buf,1);
}

void sectorErase(uint16_t page) {
  char buf[4]={0xd8,0x00,0x00,0x00};
  int retval;
  buf[1] = page/256;
  retval = wiringPiSPIDataRW(PORT,buf,4);
  waitForWIP();

}

void waitForWIP(void) {
  int retval;
  char c;
  do {
    usleep(100);
    c = 0x05;
    retval = wiringPiSPIDataRW(PORT,&c,1);
  } while (c & 0x01);
}
