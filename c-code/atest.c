#include "accelerometer.h"
#include <stdio.h>

int main(void) {
  printf("0x1e=%02x\n",ReadReg(0x1e));
  WriteReg(0x1e,0x00);
  printf("0x1e=%02x\n",ReadReg(0x1e));
  float a[3];
  ReadAccelerations(a);
  printf("(%f, %f, %f)\n",a[0],a[1],a[2]);
  return 0;
}
