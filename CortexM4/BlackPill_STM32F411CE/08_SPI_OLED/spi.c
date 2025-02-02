#include "io.h"
#include "system.h"
#include "stm32f4xx_spi.h"
#include "spi.h"
//Software SPI


//Hardware SPI

static SPI_TypeDef *_pSPI[] = {
  SPI1,
  SPI2
};

void HSPI_Start(SPI_t nSPI, int mode)
{
  SPI_TypeDef *pSPI = _pSPI[nSPI];
  SPI_InitTypeDef spiInit;
  
  
  if (nSPI == SPI_1) {
    // 1) SPI clock aktif olacak
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
    
    // 2) SPI u�lar� yap�land�r�lacak
    IO_Init(IOP_SPI1_SCK, IO_MODE_ALTERNATE);
    IO_Init(IOP_SPI1_MISO, IO_MODE_ALTERNATE);
    IO_Init(IOP_SPI1_MOSI, IO_MODE_ALTERNATE);
    
    // GPIO Mux ayarlar�
    //GPIO_PinAFConfig(GPIOA, 5, GPIO_AF_SPI1);
    GPIO_PinAFConfig(GPIO_Ports[_ios[IOP_SPI1_SCK].port], _ios[IOP_SPI1_SCK].pin, GPIO_AF_SPI1);
    GPIO_PinAFConfig(GPIO_Ports[_ios[IOP_SPI1_MISO].port], _ios[IOP_SPI1_MISO].pin, GPIO_AF_SPI1);
    GPIO_PinAFConfig(GPIO_Ports[_ios[IOP_SPI1_MOSI].port], _ios[IOP_SPI1_MOSI].pin, GPIO_AF_SPI1);
  }
  else if (nSPI == SPI_2) {
    // 1) SPI clock aktif olacak
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

    // 2) SPI u�lar� yap�land�r�lacak
    IO_Init(IOP_SPI2_SCK, IO_MODE_ALTERNATE);
    IO_Init(IOP_SPI2_MISO, IO_MODE_ALTERNATE);
    IO_Init(IOP_SPI2_MOSI, IO_MODE_ALTERNATE);

    // GPIO Mux ayarlar�
    GPIO_PinAFConfig(GPIO_Ports[_ios[IOP_SPI2_SCK].port], _ios[IOP_SPI2_SCK].pin, GPIO_AF_SPI2);
    GPIO_PinAFConfig(GPIO_Ports[_ios[IOP_SPI2_MISO].port], _ios[IOP_SPI2_MISO].pin, GPIO_AF_SPI2);
    GPIO_PinAFConfig(GPIO_Ports[_ios[IOP_SPI2_MOSI].port], _ios[IOP_SPI2_MOSI].pin, GPIO_AF_SPI2);
  }
  
  // 3) SPI parametreleri yap�land�r�lacak
  spiInit.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
  spiInit.SPI_CPOL = (mode & 2) ? SPI_CPOL_High : SPI_CPOL_Low; 
  spiInit.SPI_CPHA = (mode & 1) ? SPI_CPHA_2Edge : SPI_CPHA_1Edge;
  spiInit.SPI_DataSize = SPI_DataSize_8b;
  spiInit.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  spiInit.SPI_FirstBit = SPI_FirstBit_MSB;
  spiInit.SPI_Mode = SPI_Mode_Master;
  spiInit.SPI_NSS = SPI_NSS_Soft;
  
  SPI_Init(pSPI, &spiInit);
  
  // 4) SPI �evresel birimi ba�lat�lacak
  SPI_Cmd(pSPI, ENABLE);
}

unsigned char HSPI_Data(SPI_t nSPI, unsigned char val)
{
  SPI_TypeDef *pSPI = _pSPI[nSPI];
//SPI transmit buffer bos mu?
  while (!SPI_I2S_GetFlagStatus(pSPI, SPI_I2S_FLAG_TXE)) ;
  
  SPI_I2S_SendData(pSPI, val);
//SPI data geldi mi?
  while (!SPI_I2S_GetFlagStatus(pSPI, SPI_I2S_FLAG_RXNE)) ;
  
  val = SPI_I2S_ReceiveData(pSPI);
  return val;
}