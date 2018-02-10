#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

int main(void) {
  int ret;
  char buf[4] = {0xde,0xad,0xbe,0xef};
  wiringPiSetupGpio();
  wiringPiSPISetup(0,10000000);
  pinMode(25,OUTPUT);
  digitalWrite(25,!digitalRead(25));

  ret = wiringPiSPIDataRW(0,buf,4);
  printf("%d [%02x %02x %02x %02x]\n",ret,buf[0],buf[1],buf[2],buf[3]);
  
  return(0);
}
