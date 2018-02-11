#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "interface.h"
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

void WriteBits(uint16_t pixelColors[3][16][6]);
void InsertChannelAtOffset(char *buf, uint16_t data, uint16_t bitOffset);

int main(int argc, char *argv[]) {
  uint16_t pixelColors[3][16][6];
  for (int col = 0;col<16;col++) {
    for (int row = 0;row<6;row++) {
      pixelColors[0][col][row] = (col%2)<<(row+6);
      pixelColors[1][col][row] = ((col>>1)%2)<<(row+6);
      pixelColors[1][col][row] = ((col>>2)%2)<<(row+6);
    }
  }
  WriteBits(pixelColors);

  return(0);

}

void InsertChannelAtOffset(char *buf, uint16_t data, uint16_t bitOffset) {
uint16_t byteOffset,bitStart;
  uint32_t *writePtr;
  byteOffset = bitOffset/8;
  bitStart = bitOffset%8;
  //  printf("%d+%d\n",byteOffset,bitStart);
  //  writePtr = (uint32_t *)(buf+byteOffset);
  //  *writePtr = (data >> 4)<<(20-bitStart);
  buf[byteOffset] |= data>>(8+bitStart);
  buf[byteOffset+1] |= (data>>bitStart)&(0x100-1<<(3-bitStart));
  return;
}
  
// Order of pixelColors array is
// [R=0,G=1,B=2]
// [Left=0 to right =15]
// [Bottom=0 to top = 5]

void WriteBits(uint16_t pixelColors[3][16][6]) {
  char *buf;
  uint32_t *gpio;
  int fd,retval;

  buf = (char *)calloc(434,1);
  
  buf[433]=2;

  InsertChannelAtOffset(buf,pixelColors[0][0][0],450);
  InsertChannelAtOffset(buf,pixelColors[0][0][1],438);
  InsertChannelAtOffset(buf,pixelColors[0][0][2],426);
  InsertChannelAtOffset(buf,pixelColors[0][0][3],414);
  InsertChannelAtOffset(buf,pixelColors[0][0][4],402);
  InsertChannelAtOffset(buf,pixelColors[0][0][5],390);
  InsertChannelAtOffset(buf,pixelColors[0][1][0],522);
  InsertChannelAtOffset(buf,pixelColors[0][1][1],510);
  InsertChannelAtOffset(buf,pixelColors[0][1][2],498);
  InsertChannelAtOffset(buf,pixelColors[0][1][3],486);
  InsertChannelAtOffset(buf,pixelColors[0][1][4],474);
  InsertChannelAtOffset(buf,pixelColors[0][1][5],462);
  InsertChannelAtOffset(buf,pixelColors[0][2][0],594);
  InsertChannelAtOffset(buf,pixelColors[0][2][1],582);
  InsertChannelAtOffset(buf,pixelColors[0][2][2],570);
  InsertChannelAtOffset(buf,pixelColors[0][2][3],558);
  InsertChannelAtOffset(buf,pixelColors[0][2][4],546);
  InsertChannelAtOffset(buf,pixelColors[0][2][5],534);
  InsertChannelAtOffset(buf,pixelColors[0][3][0],666);
  InsertChannelAtOffset(buf,pixelColors[0][3][1],654);
  InsertChannelAtOffset(buf,pixelColors[0][3][2],642);
  InsertChannelAtOffset(buf,pixelColors[0][3][3],630);
  InsertChannelAtOffset(buf,pixelColors[0][3][4],618);
  InsertChannelAtOffset(buf,pixelColors[0][3][5],606);
  InsertChannelAtOffset(buf,pixelColors[0][4][0],738);
  InsertChannelAtOffset(buf,pixelColors[0][4][1],726);
  InsertChannelAtOffset(buf,pixelColors[0][4][2],714);
  InsertChannelAtOffset(buf,pixelColors[0][4][3],702);
  InsertChannelAtOffset(buf,pixelColors[0][4][4],690);
  InsertChannelAtOffset(buf,pixelColors[0][4][5],678);
  InsertChannelAtOffset(buf,pixelColors[0][5][0],1608);
  InsertChannelAtOffset(buf,pixelColors[0][5][1],1596);
  InsertChannelAtOffset(buf,pixelColors[0][5][2],1584);
  InsertChannelAtOffset(buf,pixelColors[0][5][3],1572);
  InsertChannelAtOffset(buf,pixelColors[0][5][4],762);
  InsertChannelAtOffset(buf,pixelColors[0][5][5],750);
  InsertChannelAtOffset(buf,pixelColors[0][6][0],1656);
  InsertChannelAtOffset(buf,pixelColors[0][6][1],1644);
  InsertChannelAtOffset(buf,pixelColors[0][6][2],1632);
  InsertChannelAtOffset(buf,pixelColors[0][6][3],1620);
  InsertChannelAtOffset(buf,pixelColors[0][6][4],1560);
  InsertChannelAtOffset(buf,pixelColors[0][6][5],1548);
  InsertChannelAtOffset(buf,pixelColors[0][7][0],1728);
  InsertChannelAtOffset(buf,pixelColors[0][7][1],1716);
  InsertChannelAtOffset(buf,pixelColors[0][7][2],1704);
  InsertChannelAtOffset(buf,pixelColors[0][7][3],1692);
  InsertChannelAtOffset(buf,pixelColors[0][7][4],1680);
  InsertChannelAtOffset(buf,pixelColors[0][7][5],1668);
  InsertChannelAtOffset(buf,pixelColors[0][8][0],1800);
  InsertChannelAtOffset(buf,pixelColors[0][8][1],1788);
  InsertChannelAtOffset(buf,pixelColors[0][8][2],1776);
  InsertChannelAtOffset(buf,pixelColors[0][8][3],1764);
  InsertChannelAtOffset(buf,pixelColors[0][8][4],1752);
  InsertChannelAtOffset(buf,pixelColors[0][8][5],1740);
  InsertChannelAtOffset(buf,pixelColors[0][9][0],1812);
  InsertChannelAtOffset(buf,pixelColors[0][9][1],1824);
  InsertChannelAtOffset(buf,pixelColors[0][9][2],1836);
  InsertChannelAtOffset(buf,pixelColors[0][9][3],1848);
  InsertChannelAtOffset(buf,pixelColors[0][9][4],1872);
  InsertChannelAtOffset(buf,pixelColors[0][9][5],1860);
  InsertChannelAtOffset(buf,pixelColors[0][10][0],2766);
  InsertChannelAtOffset(buf,pixelColors[0][10][1],2754);
  InsertChannelAtOffset(buf,pixelColors[0][10][2],1884);
  InsertChannelAtOffset(buf,pixelColors[0][10][3],1896);
  InsertChannelAtOffset(buf,pixelColors[0][10][4],1908);
  InsertChannelAtOffset(buf,pixelColors[0][10][5],1920);
  InsertChannelAtOffset(buf,pixelColors[0][11][0],2790);
  InsertChannelAtOffset(buf,pixelColors[0][11][1],2778);
  InsertChannelAtOffset(buf,pixelColors[0][11][2],2742);
  InsertChannelAtOffset(buf,pixelColors[0][11][3],2730);
  InsertChannelAtOffset(buf,pixelColors[0][11][4],2718);
  InsertChannelAtOffset(buf,pixelColors[0][11][5],2706);
  InsertChannelAtOffset(buf,pixelColors[0][12][0],2862);
  InsertChannelAtOffset(buf,pixelColors[0][12][1],2850);
  InsertChannelAtOffset(buf,pixelColors[0][12][2],2838);
  InsertChannelAtOffset(buf,pixelColors[0][12][3],2826);
  InsertChannelAtOffset(buf,pixelColors[0][12][4],2814);
  InsertChannelAtOffset(buf,pixelColors[0][12][5],2802);
  InsertChannelAtOffset(buf,pixelColors[0][13][0],2934);
  InsertChannelAtOffset(buf,pixelColors[0][13][1],2922);
  InsertChannelAtOffset(buf,pixelColors[0][13][2],2910);
  InsertChannelAtOffset(buf,pixelColors[0][13][3],2898);
  InsertChannelAtOffset(buf,pixelColors[0][13][4],2874);
  InsertChannelAtOffset(buf,pixelColors[0][13][5],2886);
  InsertChannelAtOffset(buf,pixelColors[0][14][0],3006);
  InsertChannelAtOffset(buf,pixelColors[0][14][1],2994);
  InsertChannelAtOffset(buf,pixelColors[0][14][2],2982);
  InsertChannelAtOffset(buf,pixelColors[0][14][3],2970);
  InsertChannelAtOffset(buf,pixelColors[0][14][4],2958);
  InsertChannelAtOffset(buf,pixelColors[0][14][5],2946);
  InsertChannelAtOffset(buf,pixelColors[0][15][0],3078);
  InsertChannelAtOffset(buf,pixelColors[0][15][1],3066);
  InsertChannelAtOffset(buf,pixelColors[0][15][2],3054);
  InsertChannelAtOffset(buf,pixelColors[0][15][3],3018);
  InsertChannelAtOffset(buf,pixelColors[0][15][4],3030);
  InsertChannelAtOffset(buf,pixelColors[0][15][5],3042);
  InsertChannelAtOffset(buf,pixelColors[1][0][0],64);
  InsertChannelAtOffset(buf,pixelColors[1][0][1],52);
  InsertChannelAtOffset(buf,pixelColors[1][0][2],40);
  InsertChannelAtOffset(buf,pixelColors[1][0][3],28);
  InsertChannelAtOffset(buf,pixelColors[1][0][4],16);
  InsertChannelAtOffset(buf,pixelColors[1][0][5],4);
  InsertChannelAtOffset(buf,pixelColors[1][1][0],124);
  InsertChannelAtOffset(buf,pixelColors[1][1][1],136);
  InsertChannelAtOffset(buf,pixelColors[1][1][2],148);
  InsertChannelAtOffset(buf,pixelColors[1][1][3],160);
  InsertChannelAtOffset(buf,pixelColors[1][1][4],172);
  InsertChannelAtOffset(buf,pixelColors[1][1][5],184);
  InsertChannelAtOffset(buf,pixelColors[1][2][0],364);
  InsertChannelAtOffset(buf,pixelColors[1][2][1],376);
  InsertChannelAtOffset(buf,pixelColors[1][2][2],76);
  InsertChannelAtOffset(buf,pixelColors[1][2][3],88);
  InsertChannelAtOffset(buf,pixelColors[1][2][4],100);
  InsertChannelAtOffset(buf,pixelColors[1][2][5],112);
  InsertChannelAtOffset(buf,pixelColors[1][3][0],352);
  InsertChannelAtOffset(buf,pixelColors[1][3][1],340);
  InsertChannelAtOffset(buf,pixelColors[1][3][2],328);
  InsertChannelAtOffset(buf,pixelColors[1][3][3],316);
  InsertChannelAtOffset(buf,pixelColors[1][3][4],304);
  InsertChannelAtOffset(buf,pixelColors[1][3][5],292);
  InsertChannelAtOffset(buf,pixelColors[1][4][0],280);
  InsertChannelAtOffset(buf,pixelColors[1][4][1],268);
  InsertChannelAtOffset(buf,pixelColors[1][4][2],256);
  InsertChannelAtOffset(buf,pixelColors[1][4][3],244);
  InsertChannelAtOffset(buf,pixelColors[1][4][4],232);
  InsertChannelAtOffset(buf,pixelColors[1][4][5],220);
  InsertChannelAtOffset(buf,pixelColors[1][5][0],1174);
  InsertChannelAtOffset(buf,pixelColors[1][5][1],1222);
  InsertChannelAtOffset(buf,pixelColors[1][5][2],1186);
  InsertChannelAtOffset(buf,pixelColors[1][5][3],1162);
  InsertChannelAtOffset(buf,pixelColors[1][5][4],208);
  InsertChannelAtOffset(buf,pixelColors[1][5][5],196);
  InsertChannelAtOffset(buf,pixelColors[1][6][0],1210);
  InsertChannelAtOffset(buf,pixelColors[1][6][1],1198);
  InsertChannelAtOffset(buf,pixelColors[1][6][2],1306);
  InsertChannelAtOffset(buf,pixelColors[1][6][3],1318);
  InsertChannelAtOffset(buf,pixelColors[1][6][4],1330);
  InsertChannelAtOffset(buf,pixelColors[1][6][5],1342);
  InsertChannelAtOffset(buf,pixelColors[1][7][0],1294);
  InsertChannelAtOffset(buf,pixelColors[1][7][1],1282);
  InsertChannelAtOffset(buf,pixelColors[1][7][2],1270);
  InsertChannelAtOffset(buf,pixelColors[1][7][3],1258);
  InsertChannelAtOffset(buf,pixelColors[1][7][4],1246);
  InsertChannelAtOffset(buf,pixelColors[1][7][5],1234);
  InsertChannelAtOffset(buf,pixelColors[1][8][0],1510);
  InsertChannelAtOffset(buf,pixelColors[1][8][1],1498);
  InsertChannelAtOffset(buf,pixelColors[1][8][2],1486);
  InsertChannelAtOffset(buf,pixelColors[1][8][3],1474);
  InsertChannelAtOffset(buf,pixelColors[1][8][4],1462);
  InsertChannelAtOffset(buf,pixelColors[1][8][5],1450);
  InsertChannelAtOffset(buf,pixelColors[1][9][0],1438);
  InsertChannelAtOffset(buf,pixelColors[1][9][1],1426);
  InsertChannelAtOffset(buf,pixelColors[1][9][2],1402);
  InsertChannelAtOffset(buf,pixelColors[1][9][3],1378);
  InsertChannelAtOffset(buf,pixelColors[1][9][4],1366);
  InsertChannelAtOffset(buf,pixelColors[1][9][5],1354);
  InsertChannelAtOffset(buf,pixelColors[1][10][0],2356);
  InsertChannelAtOffset(buf,pixelColors[1][10][1],2380);
  InsertChannelAtOffset(buf,pixelColors[1][10][2],1414);
  InsertChannelAtOffset(buf,pixelColors[1][10][3],1390);
  InsertChannelAtOffset(buf,pixelColors[1][10][4],1522);
  InsertChannelAtOffset(buf,pixelColors[1][10][5],1534);
  InsertChannelAtOffset(buf,pixelColors[1][11][0],2488);
  InsertChannelAtOffset(buf,pixelColors[1][11][1],2464);
  InsertChannelAtOffset(buf,pixelColors[1][11][2],2368);
  InsertChannelAtOffset(buf,pixelColors[1][11][3],2344);
  InsertChannelAtOffset(buf,pixelColors[1][11][4],2332);
  InsertChannelAtOffset(buf,pixelColors[1][11][5],2320);
  InsertChannelAtOffset(buf,pixelColors[1][12][0],2680);
  InsertChannelAtOffset(buf,pixelColors[1][12][1],2692);
  InsertChannelAtOffset(buf,pixelColors[1][12][2],2500);
  InsertChannelAtOffset(buf,pixelColors[1][12][3],2476);
  InsertChannelAtOffset(buf,pixelColors[1][12][4],2452);
  InsertChannelAtOffset(buf,pixelColors[1][12][5],2440);
  InsertChannelAtOffset(buf,pixelColors[1][13][0],2656);
  InsertChannelAtOffset(buf,pixelColors[1][13][1],2668);
  InsertChannelAtOffset(buf,pixelColors[1][13][2],2428);
  InsertChannelAtOffset(buf,pixelColors[1][13][3],2416);
  InsertChannelAtOffset(buf,pixelColors[1][13][4],2404);
  InsertChannelAtOffset(buf,pixelColors[1][13][5],2392);
  InsertChannelAtOffset(buf,pixelColors[1][14][0],2644);
  InsertChannelAtOffset(buf,pixelColors[1][14][1],2584);
  InsertChannelAtOffset(buf,pixelColors[1][14][2],2632);
  InsertChannelAtOffset(buf,pixelColors[1][14][3],2620);
  InsertChannelAtOffset(buf,pixelColors[1][14][4],2608);
  InsertChannelAtOffset(buf,pixelColors[1][14][5],2596);
  InsertChannelAtOffset(buf,pixelColors[1][15][0],2572);
  InsertChannelAtOffset(buf,pixelColors[1][15][1],2524);
  InsertChannelAtOffset(buf,pixelColors[1][15][2],2560);
  InsertChannelAtOffset(buf,pixelColors[1][15][3],2548);
  InsertChannelAtOffset(buf,pixelColors[1][15][4],2536);
  InsertChannelAtOffset(buf,pixelColors[1][15][5],2512);
  InsertChannelAtOffset(buf,pixelColors[2][0][0],980);
  InsertChannelAtOffset(buf,pixelColors[2][0][1],992);
  InsertChannelAtOffset(buf,pixelColors[2][0][2],1148);
  InsertChannelAtOffset(buf,pixelColors[2][0][3],788);
  InsertChannelAtOffset(buf,pixelColors[2][0][4],944);
  InsertChannelAtOffset(buf,pixelColors[2][0][5],932);
  InsertChannelAtOffset(buf,pixelColors[2][1][0],968);
  InsertChannelAtOffset(buf,pixelColors[2][1][1],1004);
  InsertChannelAtOffset(buf,pixelColors[2][1][2],1136);
  InsertChannelAtOffset(buf,pixelColors[2][1][3],800);
  InsertChannelAtOffset(buf,pixelColors[2][1][4],824);
  InsertChannelAtOffset(buf,pixelColors[2][1][5],956);
  InsertChannelAtOffset(buf,pixelColors[2][2][0],1016);
  InsertChannelAtOffset(buf,pixelColors[2][2][1],1028);
  InsertChannelAtOffset(buf,pixelColors[2][2][2],1088);
  InsertChannelAtOffset(buf,pixelColors[2][2][3],836);
  InsertChannelAtOffset(buf,pixelColors[2][2][4],812);
  InsertChannelAtOffset(buf,pixelColors[2][2][5],896);
  InsertChannelAtOffset(buf,pixelColors[2][3][0],1040);
  InsertChannelAtOffset(buf,pixelColors[2][3][1],1052);
  InsertChannelAtOffset(buf,pixelColors[2][3][2],1124);
  InsertChannelAtOffset(buf,pixelColors[2][3][3],860);
  InsertChannelAtOffset(buf,pixelColors[2][3][4],908);
  InsertChannelAtOffset(buf,pixelColors[2][3][5],884);
  InsertChannelAtOffset(buf,pixelColors[2][4][0],1064);
  InsertChannelAtOffset(buf,pixelColors[2][4][1],1076);
  InsertChannelAtOffset(buf,pixelColors[2][4][2],1112);
  InsertChannelAtOffset(buf,pixelColors[2][4][3],848);
  InsertChannelAtOffset(buf,pixelColors[2][4][4],776);
  InsertChannelAtOffset(buf,pixelColors[2][4][5],920);
  InsertChannelAtOffset(buf,pixelColors[2][5][0],2138);
  InsertChannelAtOffset(buf,pixelColors[2][5][1],2150);
  InsertChannelAtOffset(buf,pixelColors[2][5][2],2306);
  InsertChannelAtOffset(buf,pixelColors[2][5][3],1934);
  InsertChannelAtOffset(buf,pixelColors[2][5][4],872);
  InsertChannelAtOffset(buf,pixelColors[2][5][5],1100);
  InsertChannelAtOffset(buf,pixelColors[2][6][0],2126);
  InsertChannelAtOffset(buf,pixelColors[2][6][1],2162);
  InsertChannelAtOffset(buf,pixelColors[2][6][2],2294);
  InsertChannelAtOffset(buf,pixelColors[2][6][3],1970);
  InsertChannelAtOffset(buf,pixelColors[2][6][4],1946);
  InsertChannelAtOffset(buf,pixelColors[2][6][5],1958);
  InsertChannelAtOffset(buf,pixelColors[2][7][0],2174);
  InsertChannelAtOffset(buf,pixelColors[2][7][1],2186);
  InsertChannelAtOffset(buf,pixelColors[2][7][2],2258);
  InsertChannelAtOffset(buf,pixelColors[2][7][3],2090);
  InsertChannelAtOffset(buf,pixelColors[2][7][4],2102);
  InsertChannelAtOffset(buf,pixelColors[2][7][5],2018);
  InsertChannelAtOffset(buf,pixelColors[2][8][0],2198);
  InsertChannelAtOffset(buf,pixelColors[2][8][1],2210);
  InsertChannelAtOffset(buf,pixelColors[2][8][2],2282);
  InsertChannelAtOffset(buf,pixelColors[2][8][3],2078);
  InsertChannelAtOffset(buf,pixelColors[2][8][4],2114);
  InsertChannelAtOffset(buf,pixelColors[2][8][5],1994);
  InsertChannelAtOffset(buf,pixelColors[2][9][0],2222);
  InsertChannelAtOffset(buf,pixelColors[2][9][1],2246);
  InsertChannelAtOffset(buf,pixelColors[2][9][2],2270);
  InsertChannelAtOffset(buf,pixelColors[2][9][3],2066);
  InsertChannelAtOffset(buf,pixelColors[2][9][4],2042);
  InsertChannelAtOffset(buf,pixelColors[2][9][5],1982);
  InsertChannelAtOffset(buf,pixelColors[2][10][0],3296);
  InsertChannelAtOffset(buf,pixelColors[2][10][1],3308);
  InsertChannelAtOffset(buf,pixelColors[2][10][2],2234);
  InsertChannelAtOffset(buf,pixelColors[2][10][3],2030);
  InsertChannelAtOffset(buf,pixelColors[2][10][4],2006);
  InsertChannelAtOffset(buf,pixelColors[2][10][5],2054);
  InsertChannelAtOffset(buf,pixelColors[2][11][0],3284);
  InsertChannelAtOffset(buf,pixelColors[2][11][1],3320);
  InsertChannelAtOffset(buf,pixelColors[2][11][2],3260);
  InsertChannelAtOffset(buf,pixelColors[2][11][3],3092);
  InsertChannelAtOffset(buf,pixelColors[2][11][4],3440);
  InsertChannelAtOffset(buf,pixelColors[2][11][5],3416);
  InsertChannelAtOffset(buf,pixelColors[2][12][0],3332);
  InsertChannelAtOffset(buf,pixelColors[2][12][1],3344);
  InsertChannelAtOffset(buf,pixelColors[2][12][2],3272);
  InsertChannelAtOffset(buf,pixelColors[2][12][3],3104);
  InsertChannelAtOffset(buf,pixelColors[2][12][4],3164);
  InsertChannelAtOffset(buf,pixelColors[2][12][5],3452);
  InsertChannelAtOffset(buf,pixelColors[2][13][0],3356);
  InsertChannelAtOffset(buf,pixelColors[2][13][1],3368);
  InsertChannelAtOffset(buf,pixelColors[2][13][2],3212);
  InsertChannelAtOffset(buf,pixelColors[2][13][3],3188);
  InsertChannelAtOffset(buf,pixelColors[2][13][4],3128);
  InsertChannelAtOffset(buf,pixelColors[2][13][5],3428);
  InsertChannelAtOffset(buf,pixelColors[2][14][0],3380);
  InsertChannelAtOffset(buf,pixelColors[2][14][1],3200);
  InsertChannelAtOffset(buf,pixelColors[2][14][2],3224);
  InsertChannelAtOffset(buf,pixelColors[2][14][3],3116);
  InsertChannelAtOffset(buf,pixelColors[2][14][4],3236);
  InsertChannelAtOffset(buf,pixelColors[2][14][5],3464);
  InsertChannelAtOffset(buf,pixelColors[2][15][0],3392);
  InsertChannelAtOffset(buf,pixelColors[2][15][1],3404);
  InsertChannelAtOffset(buf,pixelColors[2][15][2],3248);
  InsertChannelAtOffset(buf,pixelColors[2][15][3],3140);
  InsertChannelAtOffset(buf,pixelColors[2][15][4],3176);
  InsertChannelAtOffset(buf,pixelColors[2][15][5],3152);

  gpio = SetupGPIO();
  fd = SetupSPI(gpio,0);

  struct spi_ioc_transfer transfer = {
    .tx_buf = (unsigned long)buf,
    .rx_buf = (unsigned long)buf,
    .len = 434,
    .delay_usecs = 0,
    .speed_hz = 1000000,
    .bits_per_word = 8,
    .tx_nbits = 1,
    .rx_nbits = 1
  };

  retval = ioctl(fd,SPI_IOC_MESSAGE(1),&transfer);

  RelinquishSPI(gpio,fd);
  CleanupGPIO(gpio);  
  free(buf);

  return;
}
