#include <stdio.h>
#include <fcntl.h>
#include <stdint.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

static uint32_t mode;
static uint8_t bits;
static uint32_t speed;
static uint16_t delay;
static uint8_t txBuf[8] = {0x03,0x00,0x00,0x00};
static uint8_t rxBuf[8];


int main(int argc, char *argv[]) {
  int ret,fd;

  fd = open("/dev/spidev0.1", O_RDWR);

  if (fd<0) printf("Error opening device:%d\n",fd);

  mode = SPI_MODE_0;
  ret = ioctl(fd,SPI_IOC_WR_MODE32, &mode);
  printf("%d %d %d\n",mode,ret,errno);

  bits = 8;
  ret = ioctl(fd,SPI_IOC_WR_BITS_PER_WORD, &bits);
  printf("%d %d %d\n",bits,ret,errno);

  speed=10000000;
  ret = ioctl(fd,SPI_IOC_WR_MAX_SPEED_HZ, &speed);
  printf("%d %d %d\n",speed,ret,errno);

  struct spi_ioc_transfer transfer = {
    .tx_buf = (unsigned long)txBuf,
    .rx_buf = (unsigned long)rxBuf,
    .len = 8,
    .delay_usecs = 0,
    .speed_hz = 10000000,
    .bits_per_word = 8,
    .tx_nbits = 1,
    .rx_nbits = 1
  };
  do {
    ret = ioctl(fd,SPI_IOC_MESSAGE(1),&transfer);
  } while (rxBuf[0] == 0xde);

  printf("[%02x %02x %02x %02x] %d %d\n",rxBuf[4],rxBuf[5],rxBuf[6],rxBuf[7],ret,errno); 
  
  
  
  close(fd);
  return(0);
}
