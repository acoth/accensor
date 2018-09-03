#include <stdint.h>

#define INPUT 0
#define OUTPUT 1
#define ALT0 4

#define SPI_MOSI 10
#define SPI_MISO 9
#define SPI_SCLK 11
#define SPI_CSB0 8
#define SPI_CSB1 7

#define INTXL1 22
#define INTXL2 27

uint32_t *SetupGPIO(void);
void CleanupGPIO(uint32_t *);
int SetupSPI(uint32_t *gpio, uint8_t addr,char mode);
void RelinquishSPI(uint32_t *gpio, int fd);
void SetPinMode(uint32_t *gpio, uint8_t pin, uint8_t mode);
void SetPin(uint32_t *gpio, uint8_t pin);
void ClearPin(uint32_t *gpio, uint8_t pin);
void WritePin(uint32_t *gpio, uint8_t pin, int value);
uint32_t ReadPin(uint32_t *gpio,uint8_t pin);
uint32_t ReadLowPins(uint32_t *gpio);
