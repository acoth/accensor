#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "interface.h"
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#define PIXEL 0
#define DOT_CORRECTION 1
#define ENABLE 2
#define DISABLE 0


void WriteDisplay(uint16_t pixelColors[288]);
void StuffPacket(char *buf, uint16_t pixel[288], char c);

int main(int argc, char *argv[]) {
  uint16_t pixelColors[288];
  uint16_t dim=1;
  int up = 1;
  while (1) {
    dim = up ? dim+1 : dim-1;
    if (dim>99) up = 0;
    if (dim<1) up = 1;
    
    for (int col = 0;col<16;col++) {
      for (int row = 0;row<6;row++) {
	pixelColors[col*6+row] = dim*((col%2)<<(row));
	pixelColors[96+col*6+row] = dim*(((col>>1)%2)<<(row));
	pixelColors[192+col*6+row] = dim*(((col>>2)%2)<<(row));
      }
    }
    WriteDisplay(pixelColors);
    usleep(10000);
  }
    
  return(0);
}

  
// Order of pixelColors array is
// [R=0,G=1,B=2]
// [Left=0 to right =15]
// [Bottom=0 to top = 5]

void WriteDisplay(uint16_t pixelColors[288]) {
  char buf[435];
  uint32_t *gpio;
  int fd,retval;

  StuffPacket(buf,pixelColors,PIXEL|ENABLE);
  gpio = SetupGPIO();
  fd = SetupSPI(gpio,0);

  struct spi_ioc_transfer transfer = {
    .tx_buf = (unsigned long)buf,
    .rx_buf = (unsigned long)buf,
    .len = 435,
    .delay_usecs = 0,
    .speed_hz = 1000000,
    .bits_per_word = 8,
    .tx_nbits = 1,
    .rx_nbits = 1
  };

  retval = ioctl(fd,SPI_IOC_MESSAGE(1),&transfer);

  RelinquishSPI(gpio,fd);
  CleanupGPIO(gpio);  

  return;
}


void StuffPacket(char *buf, uint16_t pixel[288], char c) {
  c = c & 0x03;
  buf[0] = ((pixel[101]>>10)) & 0xff;
  buf[1] = ((pixel[101]>>2)) & 0xff;
  buf[2] = ((pixel[101]<<6) | (pixel[100]>>6)) & 0xff;
  buf[3] = ((pixel[100]<<2) | (pixel[99]>>10)) & 0xff;
  buf[4] = ((pixel[99]>>2)) & 0xff;
  buf[5] = ((pixel[99]<<6) | (pixel[98]>>6)) & 0xff;
  buf[6] = ((pixel[98]<<2) | (pixel[97]>>10)) & 0xff;
  buf[7] = ((pixel[97]>>2)) & 0xff;
  buf[8] = ((pixel[97]<<6) | (pixel[96]>>6)) & 0xff;
  buf[9] = ((pixel[96]<<2) | (pixel[110]>>10)) & 0xff;
  buf[10] = ((pixel[110]>>2)) & 0xff;
  buf[11] = ((pixel[110]<<6) | (pixel[111]>>6)) & 0xff;
  buf[12] = ((pixel[111]<<2) | (pixel[112]>>10)) & 0xff;
  buf[13] = ((pixel[112]>>2)) & 0xff;
  buf[14] = ((pixel[112]<<6) | (pixel[113]>>6)) & 0xff;
  buf[15] = ((pixel[113]<<2) | (pixel[102]>>10)) & 0xff;
  buf[16] = ((pixel[102]>>2)) & 0xff;
  buf[17] = ((pixel[102]<<6) | (pixel[103]>>6)) & 0xff;
  buf[18] = ((pixel[103]<<2) | (pixel[104]>>10)) & 0xff;
  buf[19] = ((pixel[104]>>2)) & 0xff;
  buf[20] = ((pixel[104]<<6) | (pixel[105]>>6)) & 0xff;
  buf[21] = ((pixel[105]<<2) | (pixel[106]>>10)) & 0xff;
  buf[22] = ((pixel[106]>>2)) & 0xff;
  buf[23] = ((pixel[106]<<6) | (pixel[107]>>6)) & 0xff;
  buf[24] = ((pixel[107]<<2) | (pixel[131]>>10)) & 0xff;
  buf[25] = ((pixel[131]>>2)) & 0xff;
  buf[26] = ((pixel[131]<<6) | (pixel[130]>>6)) & 0xff;
  buf[27] = ((pixel[130]<<2) | (pixel[125]>>10)) & 0xff;
  buf[28] = ((pixel[125]>>2)) & 0xff;
  buf[29] = ((pixel[125]<<6) | (pixel[124]>>6)) & 0xff;
  buf[30] = ((pixel[124]<<2) | (pixel[123]>>10)) & 0xff;
  buf[31] = ((pixel[123]>>2)) & 0xff;
  buf[32] = ((pixel[123]<<6) | (pixel[122]>>6)) & 0xff;
  buf[33] = ((pixel[122]<<2) | (pixel[121]>>10)) & 0xff;
  buf[34] = ((pixel[121]>>2)) & 0xff;
  buf[35] = ((pixel[121]<<6) | (pixel[120]>>6)) & 0xff;
  buf[36] = ((pixel[120]<<2) | (pixel[119]>>10)) & 0xff;
  buf[37] = ((pixel[119]>>2)) & 0xff;
  buf[38] = ((pixel[119]<<6) | (pixel[118]>>6)) & 0xff;
  buf[39] = ((pixel[118]<<2) | (pixel[117]>>10)) & 0xff;
  buf[40] = ((pixel[117]>>2)) & 0xff;
  buf[41] = ((pixel[117]<<6) | (pixel[116]>>6)) & 0xff;
  buf[42] = ((pixel[116]<<2) | (pixel[115]>>10)) & 0xff;
  buf[43] = ((pixel[115]>>2)) & 0xff;
  buf[44] = ((pixel[115]<<6) | (pixel[114]>>6)) & 0xff;
  buf[45] = ((pixel[114]<<2) | (pixel[108]>>10)) & 0xff;
  buf[46] = ((pixel[108]>>2)) & 0xff;
  buf[47] = ((pixel[108]<<6) | (pixel[109]>>6)) & 0xff;
  buf[48] = ((pixel[109]<<2) | c ) & 0xff;
  buf[49] = ((pixel[5]>>4)) & 0xff;
  buf[50] = ((pixel[5]<<4) | (pixel[4]>>8)) & 0xff;
  buf[51] = (pixel[4]) & 0xff;
  buf[52] = ((pixel[3]>>4)) & 0xff;
  buf[53] = ((pixel[3]<<4) | (pixel[2]>>8)) & 0xff;
  buf[54] = (pixel[2]) & 0xff;
  buf[55] = ((pixel[1]>>4)) & 0xff;
  buf[56] = ((pixel[1]<<4) | (pixel[0]>>8)) & 0xff;
  buf[57] = (pixel[0]) & 0xff;
  buf[58] = ((pixel[11]>>4)) & 0xff;
  buf[59] = ((pixel[11]<<4) | (pixel[10]>>8)) & 0xff;
  buf[60] = (pixel[10]) & 0xff;
  buf[61] = ((pixel[9]>>4)) & 0xff;
  buf[62] = ((pixel[9]<<4) | (pixel[8]>>8)) & 0xff;
  buf[63] = (pixel[8]) & 0xff;
  buf[64] = ((pixel[7]>>4)) & 0xff;
  buf[65] = ((pixel[7]<<4) | (pixel[6]>>8)) & 0xff;
  buf[66] = (pixel[6]) & 0xff;
  buf[67] = ((pixel[17]>>4)) & 0xff;
  buf[68] = ((pixel[17]<<4) | (pixel[16]>>8)) & 0xff;
  buf[69] = (pixel[16]) & 0xff;
  buf[70] = ((pixel[15]>>4)) & 0xff;
  buf[71] = ((pixel[15]<<4) | (pixel[14]>>8)) & 0xff;
  buf[72] = (pixel[14]) & 0xff;
  buf[73] = ((pixel[13]>>4)) & 0xff;
  buf[74] = ((pixel[13]<<4) | (pixel[12]>>8)) & 0xff;
  buf[75] = (pixel[12]) & 0xff;
  buf[76] = ((pixel[23]>>4)) & 0xff;
  buf[77] = ((pixel[23]<<4) | (pixel[22]>>8)) & 0xff;
  buf[78] = (pixel[22]) & 0xff;
  buf[79] = ((pixel[21]>>4)) & 0xff;
  buf[80] = ((pixel[21]<<4) | (pixel[20]>>8)) & 0xff;
  buf[81] = (pixel[20]) & 0xff;
  buf[82] = ((pixel[19]>>4)) & 0xff;
  buf[83] = ((pixel[19]<<4) | (pixel[18]>>8)) & 0xff;
  buf[84] = (pixel[18]) & 0xff;
  buf[85] = ((pixel[29]>>4)) & 0xff;
  buf[86] = ((pixel[29]<<4) | (pixel[28]>>8)) & 0xff;
  buf[87] = (pixel[28]) & 0xff;
  buf[88] = ((pixel[27]>>4)) & 0xff;
  buf[89] = ((pixel[27]<<4) | (pixel[26]>>8)) & 0xff;
  buf[90] = (pixel[26]) & 0xff;
  buf[91] = ((pixel[25]>>4)) & 0xff;
  buf[92] = ((pixel[25]<<4) | (pixel[24]>>8)) & 0xff;
  buf[93] = (pixel[24]) & 0xff;
  buf[94] = ((pixel[35]>>4)) & 0xff;
  buf[95] = ((pixel[35]<<4) | (pixel[34]>>8)) & 0xff;
  buf[96] = (pixel[34]) & 0xff;
  buf[97] = ((pixel[220]>>6) | (c << 6)) & 0xff;
  buf[98] = ((pixel[220]<<2) | (pixel[195]>>10)) & 0xff;
  buf[99] = ((pixel[195]>>2)) & 0xff;
  buf[100] = ((pixel[195]<<6) | (pixel[201]>>6)) & 0xff;
  buf[101] = ((pixel[201]<<2) | (pixel[208]>>10)) & 0xff;
  buf[102] = ((pixel[208]>>2)) & 0xff;
  buf[103] = ((pixel[208]<<6) | (pixel[202]>>6)) & 0xff;
  buf[104] = ((pixel[202]<<2) | (pixel[207]>>10)) & 0xff;
  buf[105] = ((pixel[207]>>2)) & 0xff;
  buf[106] = ((pixel[207]<<6) | (pixel[219]>>6)) & 0xff;
  buf[107] = ((pixel[219]<<2) | (pixel[213]>>10)) & 0xff;
  buf[108] = ((pixel[213]>>2)) & 0xff;
  buf[109] = ((pixel[213]<<6) | (pixel[226]>>6)) & 0xff;
  buf[110] = ((pixel[226]<<2) | (pixel[215]>>10)) & 0xff;
  buf[111] = ((pixel[215]>>2)) & 0xff;
  buf[112] = ((pixel[215]<<6) | (pixel[209]>>6)) & 0xff;
  buf[113] = ((pixel[209]<<2) | (pixel[214]>>10)) & 0xff;
  buf[114] = ((pixel[214]>>2)) & 0xff;
  buf[115] = ((pixel[214]<<6) | (pixel[221]>>6)) & 0xff;
  buf[116] = ((pixel[221]<<2) | (pixel[197]>>10)) & 0xff;
  buf[117] = ((pixel[197]>>2)) & 0xff;
  buf[118] = ((pixel[197]<<6) | (pixel[196]>>6)) & 0xff;
  buf[119] = ((pixel[196]<<2) | (pixel[203]>>10)) & 0xff;
  buf[120] = ((pixel[203]>>2)) & 0xff;
  buf[121] = ((pixel[203]<<6) | (pixel[198]>>6)) & 0xff;
  buf[122] = ((pixel[198]<<2) | (pixel[192]>>10)) & 0xff;
  buf[123] = ((pixel[192]>>2)) & 0xff;
  buf[124] = ((pixel[192]<<6) | (pixel[193]>>6)) & 0xff;
  buf[125] = ((pixel[193]<<2) | (pixel[199]>>10)) & 0xff;
  buf[126] = ((pixel[199]>>2)) & 0xff;
  buf[127] = ((pixel[199]<<6) | (pixel[204]>>6)) & 0xff;
  buf[128] = ((pixel[204]<<2) | (pixel[205]>>10)) & 0xff;
  buf[129] = ((pixel[205]>>2)) & 0xff;
  buf[130] = ((pixel[205]<<6) | (pixel[210]>>6)) & 0xff;
  buf[131] = ((pixel[210]<<2) | (pixel[211]>>10)) & 0xff;
  buf[132] = ((pixel[211]>>2)) & 0xff;
  buf[133] = ((pixel[211]<<6) | (pixel[216]>>6)) & 0xff;
  buf[134] = ((pixel[216]<<2) | (pixel[217]>>10)) & 0xff;
  buf[135] = ((pixel[217]>>2)) & 0xff;
  buf[136] = ((pixel[217]<<6) | (pixel[206]>>6)) & 0xff;
  buf[137] = ((pixel[206]<<2) | (pixel[227]>>10)) & 0xff;
  buf[138] = ((pixel[227]>>2)) & 0xff;
  buf[139] = ((pixel[227]<<6) | (pixel[218]>>6)) & 0xff;
  buf[140] = ((pixel[218]<<2) | (pixel[212]>>10)) & 0xff;
  buf[141] = ((pixel[212]>>2)) & 0xff;
  buf[142] = ((pixel[212]<<6) | (pixel[200]>>6)) & 0xff;
  buf[143] = ((pixel[200]<<2) | (pixel[194]>>10)) & 0xff;
  buf[144] = ((pixel[194]>>2)) & 0xff;
  buf[145] = ((pixel[194]<<6) | (pixel[129]>>8) | (c << 4)) & 0xff;
  buf[146] = (pixel[129]) & 0xff;
  buf[147] = ((pixel[126]>>4)) & 0xff;
  buf[148] = ((pixel[126]<<4) | (pixel[128]>>8)) & 0xff;
  buf[149] = (pixel[128]) & 0xff;
  buf[150] = ((pixel[133]>>4)) & 0xff;
  buf[151] = ((pixel[133]<<4) | (pixel[132]>>8)) & 0xff;
  buf[152] = (pixel[132]) & 0xff;
  buf[153] = ((pixel[127]>>4)) & 0xff;
  buf[154] = ((pixel[127]<<4) | (pixel[143]>>8)) & 0xff;
  buf[155] = (pixel[143]) & 0xff;
  buf[156] = ((pixel[142]>>4)) & 0xff;
  buf[157] = ((pixel[142]<<4) | (pixel[141]>>8)) & 0xff;
  buf[158] = (pixel[141]) & 0xff;
  buf[159] = ((pixel[140]>>4)) & 0xff;
  buf[160] = ((pixel[140]<<4) | (pixel[139]>>8)) & 0xff;
  buf[161] = (pixel[139]) & 0xff;
  buf[162] = ((pixel[138]>>4)) & 0xff;
  buf[163] = ((pixel[138]<<4) | (pixel[134]>>8)) & 0xff;
  buf[164] = (pixel[134]) & 0xff;
  buf[165] = ((pixel[135]>>4)) & 0xff;
  buf[166] = ((pixel[135]<<4) | (pixel[136]>>8)) & 0xff;
  buf[167] = (pixel[136]) & 0xff;
  buf[168] = ((pixel[137]>>4)) & 0xff;
  buf[169] = ((pixel[137]<<4) | (pixel[155]>>8)) & 0xff;
  buf[170] = (pixel[155]) & 0xff;
  buf[171] = ((pixel[154]>>4)) & 0xff;
  buf[172] = ((pixel[154]<<4) | (pixel[153]>>8)) & 0xff;
  buf[173] = (pixel[153]) & 0xff;
  buf[174] = ((pixel[159]>>4)) & 0xff;
  buf[175] = ((pixel[159]<<4) | (pixel[152]>>8)) & 0xff;
  buf[176] = (pixel[152]) & 0xff;
  buf[177] = ((pixel[158]>>4)) & 0xff;
  buf[178] = ((pixel[158]<<4) | (pixel[151]>>8)) & 0xff;
  buf[179] = (pixel[151]) & 0xff;
  buf[180] = ((pixel[150]>>4)) & 0xff;
  buf[181] = ((pixel[150]<<4) | (pixel[149]>>8)) & 0xff;
  buf[182] = (pixel[149]) & 0xff;
  buf[183] = ((pixel[148]>>4)) & 0xff;
  buf[184] = ((pixel[148]<<4) | (pixel[147]>>8)) & 0xff;
  buf[185] = (pixel[147]) & 0xff;
  buf[186] = ((pixel[146]>>4)) & 0xff;
  buf[187] = ((pixel[146]<<4) | (pixel[145]>>8)) & 0xff;
  buf[188] = (pixel[145]) & 0xff;
  buf[189] = ((pixel[144]>>4)) & 0xff;
  buf[190] = ((pixel[144]<<4) | (pixel[160]>>8)) & 0xff;
  buf[191] = (pixel[160]) & 0xff;
  buf[192] = ((pixel[161]>>4)) & 0xff;
  buf[193] = ((pixel[161]<<4) | (pixel[41]>>10) | (c << 2)) & 0xff;
  buf[194] = ((pixel[41]>>2)) & 0xff;
  buf[195] = ((pixel[41]<<6) | (pixel[40]>>6)) & 0xff;
  buf[196] = ((pixel[40]<<2) | (pixel[33]>>10)) & 0xff;
  buf[197] = ((pixel[33]>>2)) & 0xff;
  buf[198] = ((pixel[33]<<6) | (pixel[32]>>6)) & 0xff;
  buf[199] = ((pixel[32]<<2) | (pixel[31]>>10)) & 0xff;
  buf[200] = ((pixel[31]>>2)) & 0xff;
  buf[201] = ((pixel[31]<<6) | (pixel[30]>>6)) & 0xff;
  buf[202] = ((pixel[30]<<2) | (pixel[39]>>10)) & 0xff;
  buf[203] = ((pixel[39]>>2)) & 0xff;
  buf[204] = ((pixel[39]<<6) | (pixel[38]>>6)) & 0xff;
  buf[205] = ((pixel[38]<<2) | (pixel[37]>>10)) & 0xff;
  buf[206] = ((pixel[37]>>2)) & 0xff;
  buf[207] = ((pixel[37]<<6) | (pixel[36]>>6)) & 0xff;
  buf[208] = ((pixel[36]<<2) | (pixel[47]>>10)) & 0xff;
  buf[209] = ((pixel[47]>>2)) & 0xff;
  buf[210] = ((pixel[47]<<6) | (pixel[46]>>6)) & 0xff;
  buf[211] = ((pixel[46]<<2) | (pixel[45]>>10)) & 0xff;
  buf[212] = ((pixel[45]>>2)) & 0xff;
  buf[213] = ((pixel[45]<<6) | (pixel[44]>>6)) & 0xff;
  buf[214] = ((pixel[44]<<2) | (pixel[43]>>10)) & 0xff;
  buf[215] = ((pixel[43]>>2)) & 0xff;
  buf[216] = ((pixel[43]<<6) | (pixel[42]>>6)) & 0xff;
  buf[217] = ((pixel[42]<<2) | (pixel[53]>>10)) & 0xff;
  buf[218] = ((pixel[53]>>2)) & 0xff;
  buf[219] = ((pixel[53]<<6) | (pixel[52]>>6)) & 0xff;
  buf[220] = ((pixel[52]<<2) | (pixel[51]>>10)) & 0xff;
  buf[221] = ((pixel[51]>>2)) & 0xff;
  buf[222] = ((pixel[51]<<6) | (pixel[50]>>6)) & 0xff;
  buf[223] = ((pixel[50]<<2) | (pixel[49]>>10)) & 0xff;
  buf[224] = ((pixel[49]>>2)) & 0xff;
  buf[225] = ((pixel[49]<<6) | (pixel[48]>>6)) & 0xff;
  buf[226] = ((pixel[48]<<2) | (pixel[54]>>10)) & 0xff;
  buf[227] = ((pixel[54]>>2)) & 0xff;
  buf[228] = ((pixel[54]<<6) | (pixel[55]>>6)) & 0xff;
  buf[229] = ((pixel[55]<<2) | (pixel[56]>>10)) & 0xff;
  buf[230] = ((pixel[56]>>2)) & 0xff;
  buf[231] = ((pixel[56]<<6) | (pixel[57]>>6)) & 0xff;
  buf[232] = ((pixel[57]<<2) | (pixel[59]>>10)) & 0xff;
  buf[233] = ((pixel[59]>>2)) & 0xff;
  buf[234] = ((pixel[59]<<6) | (pixel[58]>>6)) & 0xff;
  buf[235] = ((pixel[58]<<2) | (pixel[62]>>10)) & 0xff;
  buf[236] = ((pixel[62]>>2)) & 0xff;
  buf[237] = ((pixel[62]<<6) | (pixel[63]>>6)) & 0xff;
  buf[238] = ((pixel[63]<<2) | (pixel[64]>>10)) & 0xff;
  buf[239] = ((pixel[64]>>2)) & 0xff;
  buf[240] = ((pixel[64]<<6) | (pixel[65]>>6)) & 0xff;
  buf[241] = ((pixel[65]<<2) | c) & 0xff;
  buf[242] = ((pixel[225]>>4)) & 0xff;
  buf[243] = ((pixel[225]<<4) | (pixel[232]>>8)) & 0xff;
  buf[244] = (pixel[232]) & 0xff;
  buf[245] = ((pixel[233]>>4)) & 0xff;
  buf[246] = ((pixel[233]<<4) | (pixel[231]>>8)) & 0xff;
  buf[247] = (pixel[231]) & 0xff;
  buf[248] = ((pixel[251]>>4)) & 0xff;
  buf[249] = ((pixel[251]<<4) | (pixel[245]>>8)) & 0xff;
  buf[250] = (pixel[245]) & 0xff;
  buf[251] = ((pixel[256]>>4)) & 0xff;
  buf[252] = ((pixel[256]<<4) | (pixel[239]>>8)) & 0xff;
  buf[253] = (pixel[239]) & 0xff;
  buf[254] = ((pixel[255]>>4)) & 0xff;
  buf[255] = ((pixel[255]<<4) | (pixel[250]>>8)) & 0xff;
  buf[256] = (pixel[250]) & 0xff;
  buf[257] = ((pixel[257]>>4)) & 0xff;
  buf[258] = ((pixel[257]<<4) | (pixel[249]>>8)) & 0xff;
  buf[259] = (pixel[249]) & 0xff;
  buf[260] = ((pixel[243]>>4)) & 0xff;
  buf[261] = ((pixel[243]<<4) | (pixel[237]>>8)) & 0xff;
  buf[262] = (pixel[237]) & 0xff;
  buf[263] = ((pixel[238]>>4)) & 0xff;
  buf[264] = ((pixel[238]<<4) | (pixel[244]>>8)) & 0xff;
  buf[265] = (pixel[244]) & 0xff;
  buf[266] = ((pixel[228]>>4)) & 0xff;
  buf[267] = ((pixel[228]<<4) | (pixel[222]>>8)) & 0xff;
  buf[268] = (pixel[222]) & 0xff;
  buf[269] = ((pixel[223]>>4)) & 0xff;
  buf[270] = ((pixel[223]<<4) | (pixel[229]>>8)) & 0xff;
  buf[271] = (pixel[229]) & 0xff;
  buf[272] = ((pixel[234]>>4)) & 0xff;
  buf[273] = ((pixel[234]<<4) | (pixel[235]>>8)) & 0xff;
  buf[274] = (pixel[235]) & 0xff;
  buf[275] = ((pixel[240]>>4)) & 0xff;
  buf[276] = ((pixel[240]<<4) | (pixel[241]>>8)) & 0xff;
  buf[277] = (pixel[241]) & 0xff;
  buf[278] = ((pixel[246]>>4)) & 0xff;
  buf[279] = ((pixel[246]<<4) | (pixel[254]>>8)) & 0xff;
  buf[280] = (pixel[254]) & 0xff;
  buf[281] = ((pixel[247]>>4)) & 0xff;
  buf[282] = ((pixel[247]<<4) | (pixel[236]>>8)) & 0xff;
  buf[283] = (pixel[236]) & 0xff;
  buf[284] = ((pixel[248]>>4)) & 0xff;
  buf[285] = ((pixel[248]<<4) | (pixel[242]>>8)) & 0xff;
  buf[286] = (pixel[242]) & 0xff;
  buf[287] = ((pixel[230]>>4)) & 0xff;
  buf[288] = ((pixel[230]<<4) | (pixel[224]>>8)) & 0xff;
  buf[289] = (pixel[224]) & 0xff;
  buf[290] = ((pixel[167]>>6) | (c << 6)) & 0xff;
  buf[291] = ((pixel[167]<<2) | (pixel[166]>>10)) & 0xff;
  buf[292] = ((pixel[166]>>2)) & 0xff;
  buf[293] = ((pixel[166]<<6) | (pixel[165]>>6)) & 0xff;
  buf[294] = ((pixel[165]<<2) | (pixel[156]>>10)) & 0xff;
  buf[295] = ((pixel[156]>>2)) & 0xff;
  buf[296] = ((pixel[156]<<6) | (pixel[164]>>6)) & 0xff;
  buf[297] = ((pixel[164]<<2) | (pixel[157]>>10)) & 0xff;
  buf[298] = ((pixel[157]>>2)) & 0xff;
  buf[299] = ((pixel[157]<<6) | (pixel[179]>>6)) & 0xff;
  buf[300] = ((pixel[179]<<2) | (pixel[178]>>10)) & 0xff;
  buf[301] = ((pixel[178]>>2)) & 0xff;
  buf[302] = ((pixel[178]<<6) | (pixel[177]>>6)) & 0xff;
  buf[303] = ((pixel[177]<<2) | (pixel[176]>>10)) & 0xff;
  buf[304] = ((pixel[176]>>2)) & 0xff;
  buf[305] = ((pixel[176]<<6) | (pixel[173]>>6)) & 0xff;
  buf[306] = ((pixel[173]<<2) | (pixel[172]>>10)) & 0xff;
  buf[307] = ((pixel[172]>>2)) & 0xff;
  buf[308] = ((pixel[172]<<6) | (pixel[163]>>6)) & 0xff;
  buf[309] = ((pixel[163]<<2) | (pixel[171]>>10)) & 0xff;
  buf[310] = ((pixel[171]>>2)) & 0xff;
  buf[311] = ((pixel[171]<<6) | (pixel[162]>>6)) & 0xff;
  buf[312] = ((pixel[162]<<2) | (pixel[170]>>10)) & 0xff;
  buf[313] = ((pixel[170]>>2)) & 0xff;
  buf[314] = ((pixel[170]<<6) | (pixel[191]>>6)) & 0xff;
  buf[315] = ((pixel[191]<<2) | (pixel[187]>>10)) & 0xff;
  buf[316] = ((pixel[187]>>2)) & 0xff;
  buf[317] = ((pixel[187]<<6) | (pixel[190]>>6)) & 0xff;
  buf[318] = ((pixel[190]<<2) | (pixel[189]>>10)) & 0xff;
  buf[319] = ((pixel[189]>>2)) & 0xff;
  buf[320] = ((pixel[189]<<6) | (pixel[188]>>6)) & 0xff;
  buf[321] = ((pixel[188]<<2) | (pixel[186]>>10)) & 0xff;
  buf[322] = ((pixel[186]>>2)) & 0xff;
  buf[323] = ((pixel[186]<<6) | (pixel[181]>>6)) & 0xff;
  buf[324] = ((pixel[181]<<2) | (pixel[185]>>10)) & 0xff;
  buf[325] = ((pixel[185]>>2)) & 0xff;
  buf[326] = ((pixel[185]<<6) | (pixel[184]>>6)) & 0xff;
  buf[327] = ((pixel[184]<<2) | (pixel[183]>>10)) & 0xff;
  buf[328] = ((pixel[183]>>2)) & 0xff;
  buf[329] = ((pixel[183]<<6) | (pixel[182]>>6)) & 0xff;
  buf[330] = ((pixel[182]<<2) | (pixel[180]>>10)) & 0xff;
  buf[331] = ((pixel[180]>>2)) & 0xff;
  buf[332] = ((pixel[180]<<6) | (pixel[174]>>6)) & 0xff;
  buf[333] = ((pixel[174]<<2) | (pixel[175]>>10)) & 0xff;
  buf[334] = ((pixel[175]>>2)) & 0xff;
  buf[335] = ((pixel[175]<<6) | (pixel[168]>>6)) & 0xff;
  buf[336] = ((pixel[168]<<2) | (pixel[169]>>10)) & 0xff;
  buf[337] = ((pixel[169]>>2)) & 0xff;
  buf[338] = ((pixel[169]<<6) | (pixel[71]>>8) | (c<<4)) & 0xff;
  buf[339] = (pixel[71]) & 0xff;
  buf[340] = ((pixel[70]>>4)) & 0xff;
  buf[341] = ((pixel[70]<<4) | (pixel[69]>>8)) & 0xff;
  buf[342] = (pixel[69]) & 0xff;
  buf[343] = ((pixel[68]>>4)) & 0xff;
  buf[344] = ((pixel[68]<<4) | (pixel[61]>>8)) & 0xff;
  buf[345] = (pixel[61]) & 0xff;
  buf[346] = ((pixel[60]>>4)) & 0xff;
  buf[347] = ((pixel[60]<<4) | (pixel[67]>>8)) & 0xff;
  buf[348] = (pixel[67]) & 0xff;
  buf[349] = ((pixel[66]>>4)) & 0xff;
  buf[350] = ((pixel[66]<<4) | (pixel[77]>>8)) & 0xff;
  buf[351] = (pixel[77]) & 0xff;
  buf[352] = ((pixel[76]>>4)) & 0xff;
  buf[353] = ((pixel[76]<<4) | (pixel[75]>>8)) & 0xff;
  buf[354] = (pixel[75]) & 0xff;
  buf[355] = ((pixel[74]>>4)) & 0xff;
  buf[356] = ((pixel[74]<<4) | (pixel[73]>>8)) & 0xff;
  buf[357] = (pixel[73]) & 0xff;
  buf[358] = ((pixel[72]>>4)) & 0xff;
  buf[359] = ((pixel[72]<<4) | (pixel[82]>>8)) & 0xff;
  buf[360] = (pixel[82]) & 0xff;
  buf[361] = ((pixel[83]>>4)) & 0xff;
  buf[362] = ((pixel[83]<<4) | (pixel[81]>>8)) & 0xff;
  buf[363] = (pixel[81]) & 0xff;
  buf[364] = ((pixel[80]>>4)) & 0xff;
  buf[365] = ((pixel[80]<<4) | (pixel[79]>>8)) & 0xff;
  buf[366] = (pixel[79]) & 0xff;
  buf[367] = ((pixel[78]>>4)) & 0xff;
  buf[368] = ((pixel[78]<<4) | (pixel[89]>>8)) & 0xff;
  buf[369] = (pixel[89]) & 0xff;
  buf[370] = ((pixel[88]>>4)) & 0xff;
  buf[371] = ((pixel[88]<<4) | (pixel[87]>>8)) & 0xff;
  buf[372] = (pixel[87]) & 0xff;
  buf[373] = ((pixel[86]>>4)) & 0xff;
  buf[374] = ((pixel[86]<<4) | (pixel[85]>>8)) & 0xff;
  buf[375] = (pixel[85]) & 0xff;
  buf[376] = ((pixel[84]>>4)) & 0xff;
  buf[377] = ((pixel[84]<<4) | (pixel[93]>>8)) & 0xff;
  buf[378] = (pixel[93]) & 0xff;
  buf[379] = ((pixel[94]>>4)) & 0xff;
  buf[380] = ((pixel[94]<<4) | (pixel[95]>>8)) & 0xff;
  buf[381] = (pixel[95]) & 0xff;
  buf[382] = ((pixel[92]>>4)) & 0xff;
  buf[383] = ((pixel[92]<<4) | (pixel[91]>>8)) & 0xff;
  buf[384] = (pixel[91]) & 0xff;
  buf[385] = ((pixel[90]>>4)) & 0xff;
  buf[386] = ((pixel[90]<<4) | (pixel[261]>>10) | (c<<2)) & 0xff;
  buf[387] = ((pixel[261]>>2)) & 0xff;
  buf[388] = ((pixel[261]<<6) | (pixel[267]>>6)) & 0xff;
  buf[389] = ((pixel[267]<<2) | (pixel[279]>>10)) & 0xff;
  buf[390] = ((pixel[279]>>2)) & 0xff;
  buf[391] = ((pixel[279]<<6) | (pixel[274]>>6)) & 0xff;
  buf[392] = ((pixel[274]<<2) | (pixel[285]>>10)) & 0xff;
  buf[393] = ((pixel[285]>>2)) & 0xff;
  buf[394] = ((pixel[285]<<6) | (pixel[287]>>6)) & 0xff;
  buf[395] = ((pixel[287]<<2) | (pixel[268]>>10)) & 0xff;
  buf[396] = ((pixel[268]>>2)) & 0xff;
  buf[397] = ((pixel[268]<<6) | (pixel[286]>>6)) & 0xff;
  buf[398] = ((pixel[286]<<2) | (pixel[273]>>10)) & 0xff;
  buf[399] = ((pixel[273]>>2)) & 0xff;
  buf[400] = ((pixel[273]<<6) | (pixel[277]>>6)) & 0xff;
  buf[401] = ((pixel[277]<<2) | (pixel[272]>>10)) & 0xff;
  buf[402] = ((pixel[272]>>2)) & 0xff;
  buf[403] = ((pixel[272]<<6) | (pixel[278]>>6)) & 0xff;
  buf[404] = ((pixel[278]<<2) | (pixel[280]>>10)) & 0xff;
  buf[405] = ((pixel[280]>>2)) & 0xff;
  buf[406] = ((pixel[280]<<6) | (pixel[284]>>6)) & 0xff;
  buf[407] = ((pixel[284]<<2) | (pixel[260]>>10)) & 0xff;
  buf[408] = ((pixel[260]>>2)) & 0xff;
  buf[409] = ((pixel[260]<<6) | (pixel[266]>>6)) & 0xff;
  buf[410] = ((pixel[266]<<2) | (pixel[258]>>10)) & 0xff;
  buf[411] = ((pixel[258]>>2)) & 0xff;
  buf[412] = ((pixel[258]<<6) | (pixel[252]>>6)) & 0xff;
  buf[413] = ((pixel[252]<<2) | (pixel[253]>>10)) & 0xff;
  buf[414] = ((pixel[253]>>2)) & 0xff;
  buf[415] = ((pixel[253]<<6) | (pixel[259]>>6)) & 0xff;
  buf[416] = ((pixel[259]<<2) | (pixel[264]>>10)) & 0xff;
  buf[417] = ((pixel[264]>>2)) & 0xff;
  buf[418] = ((pixel[264]<<6) | (pixel[265]>>6)) & 0xff;
  buf[419] = ((pixel[265]<<2) | (pixel[270]>>10)) & 0xff;
  buf[420] = ((pixel[270]>>2)) & 0xff;
  buf[421] = ((pixel[270]<<6) | (pixel[271]>>6)) & 0xff;
  buf[422] = ((pixel[271]<<2) | (pixel[276]>>10)) & 0xff;
  buf[423] = ((pixel[276]>>2)) & 0xff;
  buf[424] = ((pixel[276]<<6) | (pixel[282]>>6)) & 0xff;
  buf[425] = ((pixel[282]<<2) | (pixel[283]>>10)) & 0xff;
  buf[426] = ((pixel[283]>>2)) & 0xff;
  buf[427] = ((pixel[283]<<6) | (pixel[263]>>6)) & 0xff;
  buf[428] = ((pixel[263]<<2) | (pixel[275]>>10)) & 0xff;
  buf[429] = ((pixel[275]>>2)) & 0xff;
  buf[430] = ((pixel[275]<<6) | (pixel[262]>>6)) & 0xff;
  buf[431] = ((pixel[262]<<2) | (pixel[269]>>10)) & 0xff;
  buf[432] = ((pixel[269]>>2)) & 0xff;
  buf[433] = ((pixel[269]<<6) | (pixel[281]>>6)) & 0xff;
  buf[434] = ((pixel[281]<<2) | c) & 0xff;
  return;
}
