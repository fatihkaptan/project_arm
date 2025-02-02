#ifndef _SPI_H
#define _SPI_H


typedef enum {
  SPI_1,
  SPI_2,
} SPI_t;

void HSPI_Start(SPI_t nSPI, int mode);

unsigned char HSPI_Data(SPI_t nSPI, unsigned char val);

#endif
