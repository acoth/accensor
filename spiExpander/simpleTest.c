#include <stdio.h>
#include <unistd.h>
#include "interface.h"
#include <stdlib.h>

#define LENGTH 386
#define R 0x200
#define G 0x400
#define B 0x400
#define WAIT 1

void ClockBit(uint32_t *gpio,int b) {
  //  printf("%d",b);
  WritePin(gpio,SPI_MOSI,b);
  usleep(WAIT);
  WritePin(gpio,SPI_SCLK,1);
  usleep(WAIT);
  WritePin(gpio,SPI_SCLK,0);
}

int main (int argc, char *argv[]) {

  uint32_t *gpio;
  //  int WAIT = 1000;
  unsigned int cv[3]={256,256,256};
  int bv;
  if (argc>1)
    cv[0] = atoi(argv[1]);
  if (argc>3){
    cv[1] = atoi(argv[2]);
    cv[2] = atoi(argv[3]);
  }
  //  WAIT = atoi(argv[1]);
  
  gpio = SetupGPIO();
  SetPinMode(gpio,SPI_MOSI,OUTPUT);
  SetPinMode(gpio,SPI_SCLK,OUTPUT);
  SetPinMode(gpio,SPI_CSB0,OUTPUT);
  SetPinMode(gpio,SPI_CSB1,OUTPUT);
  SetPinMode(gpio,SPI_MISO,INPUT);
  WritePin(gpio,SPI_SCLK,0);
  WritePin(gpio,SPI_CSB0,0);
  WritePin(gpio,SPI_CSB1,1);

  for (int sec=0;sec<3;sec++) {
    for (int color=0;color<3;color++) {
      //      cv=R;
      for (int led=0;led<32;led++) {
	//	printf("%d,%d,%d\n",sec,color,led);
	for (int b=11;b>=0;b--) {
	  ClockBit(gpio,cv[color]&(1U<<b)?1:0);
	}
      }
      
      ClockBit(gpio,1);
      ClockBit(gpio,argc>4);
      //  printf("\n");
     }
  }

  usleep(WAIT);
  WritePin(gpio,SPI_CSB0,1);
  usleep(WAIT);
  WritePin(gpio,SPI_CSB0,0);
 
  CleanupGPIO(gpio);
  return 0;
}
