#include <stdio.h>
#include <stdint.h>
#include "interface.h"
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#define ADDR 8
#define SPEED 16000000

void SectorErase(int fd, uint16_t page);
void WaitForWIP(int fd);
void SetWriteEnable(int fd);

int main(int argc, char *argv[]) {
  FILE * fPtr = stdin;
  uint8_t buf[260];
  int retval,count,fd;
  uint32_t *gpio;
  uint16_t page;

  struct spi_ioc_transfer transfer = {
    .tx_buf = (unsigned long)buf,
    .rx_buf = (unsigned long)buf,
    .len = 260,
    .delay_usecs = 0,
    .speed_hz = SPEED,
    .bits_per_word = 8,
    .tx_nbits = 1,
    .rx_nbits = 1
  };
  
  gpio = SetupGPIO();
  fd = SetupSPI(gpio,ADDR);
  SetPinMode(gpio,MA742_PROGB,OUTPUT);
  ClearPin(gpio,MA742_PROGB);
  usleep(10000);  //Pause 10ms for pin to actually go low
  buf[0] = 0x9f;
  buf[1] = 0x00;
  buf[2] = 0x00;
  buf[3] = 0x00;
  transfer.len = 4;
  retval = ioctl(fd,SPI_IOC_MESSAGE(1),&transfer);
  
  printf("Flash ID reads back as %02x %02x %02x %02x\n",buf[0],buf[1],buf[2],buf[3]);
  page = 0;
  while(!feof(fPtr) && page<8192 && argc<2) {
    if (0==page%256) {
      printf("Erasing sector %d... ",page/256);
      fflush(stdout);
      SectorErase(fd,page);
      printf("and writing it...\n");
      fflush(stdout);
    }
    count = fread(buf+4,1,256,stdin);
    if (count>0) {
      SetWriteEnable(fd);
      WaitForWIP(fd);

      buf[0] = 0x02;
      buf[1] = page/256;
      buf[2] = page%256;
      buf[3] = 0x00;
      transfer.len = count+4;
      retval = ioctl(fd,SPI_IOC_MESSAGE(1),&transfer);
      WaitForWIP(fd);
    }
    page++;
  }
  printf("Done!  Allowing FPGA to load...\n");
  close(fd);
  RelinquishSPI(gpio,fd);
  SetPin(gpio,MA742_PROGB);
  usleep(10000);
  CleanupGPIO(gpio);
  return(0);
}


void SetWriteEnable(int fd) {
  uint8_t buf[1] = {0x06};
  int retval;
  struct spi_ioc_transfer transfer = {
    .tx_buf = (unsigned long)buf,
    .rx_buf = (unsigned long)buf,
    .len = 1,
    .delay_usecs = 0,
    .speed_hz = SPEED,
    .bits_per_word = 8,
    .tx_nbits = 1,
    .rx_nbits = 1
  };
  retval = ioctl(fd,SPI_IOC_MESSAGE(1),&transfer);
}

void SectorErase(int fd, uint16_t page) {
  uint8_t buf[4]={0xd8,0x00,0x00,0x00};
  int retval;
  buf[1] = page/256;
  struct spi_ioc_transfer transfer = {
    .tx_buf = (unsigned long)buf,
    .rx_buf = (unsigned long)buf,
    .len = 4,
    .delay_usecs = 0,
    .speed_hz = SPEED,
    .bits_per_word = 8,
    .tx_nbits = 1,
    .rx_nbits = 1
  };
  SetWriteEnable(fd);
  retval = ioctl(fd,SPI_IOC_MESSAGE(1),&transfer);
  WaitForWIP(fd);
}

void WaitForWIP(int fd) {
  int retval;
  uint8_t b[2] = {0x05,0x00};
  uint8_t c[2];
  struct spi_ioc_transfer transfer = {
    .tx_buf = (unsigned long)b,
    .rx_buf = (unsigned long)c,
    .len = 2,
    .delay_usecs = 0,
    .speed_hz = SPEED,
    .bits_per_word = 8,
    .tx_nbits = 1,
    .rx_nbits = 1
  };
  do {
    retval = ioctl(fd,SPI_IOC_MESSAGE(1),&transfer);
    usleep(100);
  } while (c[1] & 0x01);
}
