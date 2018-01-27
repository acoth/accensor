
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

unsigned long int *SetupMM();

int main(int argc, char *argv[]) {
	unsigned long int *regAddr;
	int val;
	if (argc<2) {
		printf("No value supplied!\n");
		return(1);
	}
	val = atoi(argv[1]);
	regAddr = SetupMM();
	*(regAddr+REGISTER_CTRL0_OFFSET) = 1;
//	if (val) {
	while(1){
		*(regAddr+REGISTER_DSET0_OFFSET) = 1;
//	} else {
		*(regAddr+REGISTER_DCLR0_OFFSET) = 1;
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
