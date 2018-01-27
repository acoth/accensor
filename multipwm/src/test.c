
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#define REG_BLOCK_ADDR			0x10000000
#define REGISTER_CTRL0_OFFSET		0x180
#define REGISTER_DATA0_OFFSET		0x188
#define REGISTER_DSET0_OFFSET		0x18c
#define REGISTER_DCLR0_OFFSET		0x190
#define DO 0
#define D1 1
#define D2 2
#define D3 3
#define D4 4
#define D5 5
#define D6 6
#define D7 11
#define D8 12
#define DCLK 13
#define MASK 0xc087f

unsigned long int *SetupMM();

int main(int argc, char *argv[]) {
	unsigned long int *regAddr;
	int val;
	uint32_t data[32] = {	0x40871,
				0x0087B,
				0x40812,
				0x0000D,
				0x00042,
				0x00862,
0x4003C,
0x00010,
0x00030,
0x40006,
0x0083C,
0x00869,
0x0087B,
0x00875,
0x0086E,
0x40059,
0x4083A,
0x00037,
0x4083A,
0x40842,
0x4082F,
0x4080A,
0x4083B,
0x4003C,
0x40003,
0x4083F,
0x00862,
0x4006F,
0x4001C,
0x00852,
0x00022,
0x4005F};
	if (argc<2) {
		printf("No value supplied! %d\n",data);	
		return(1);
	}
	val = atoi(argv[1]);
	regAddr = SetupMM();
	*(regAddr+REGISTER_CTRL0_OFFSET) = MASK;
	while(1){
		for(int k=0;k<32;k++){
			*(regAddr+REGISTER_DSET0_OFFSET) = data[k]|0x80000;
			*(regAddr+REGISTER_DCLR0_OFFSET) = (~data[k])|0x80000;
		}
	}
	return 0;
}

unsigned long int *SetupMM(void) {
	unsigned long int *regAddr;
	int m_mfd;
	
	m_mfd = open("/dev/mem",O_RDWR);
	
	
	regAddr = (unsigned long int *)mmap(	NULL,
						1024,
						PROT_READ|PROT_WRITE,
						MAP_FILE|MAP_SHARED,
						m_mfd,
						REG_BLOCK_ADDR);
	close(m_mfd);
	return(regAddr);
}
