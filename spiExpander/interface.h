#include <stdint.h>

#define INPUT 0
#define OUTPUT 1
#define ALT0 4

#define SPI_MOSI 10
#define SPI_MISO 9
#define SPI_SCLK 11
#define SPI_CSB0 8
#define SPI_CSB1 7

#define MUXSEL0 25
#define MUXSEL1 24
#define MUXSEL2 23
#define MA742_PROGB 22

uint32_t *SetupGPIO(void);
void CleanupGPIO(uint32_t *);
int SetupSPI(uint32_t *gpio, uint8_t addr);
void RelinquishSPI(uint32_t *gpio, int fd);
void SetPinMode(uint32_t *gpio, uint8_t pin, uint8_t mode);
void SetPin(uint32_t *gpio, uint8_t pin);
void ClearPin(uint32_t *gpio, uint8_t pin);
void WritePin(uint32_t *gpio, uint8_t pin, int value);