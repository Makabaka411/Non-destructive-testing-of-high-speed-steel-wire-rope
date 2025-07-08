#ifndef __SPI_H
#define __SPI_H

#include "include.h"

#define SPI_SCK_GPIO_PORT GPIOA
#define SPI_SCK_GPIO_PIN GPIO_Pin_5
#define SPI_SCK_GPIO_PIN_SOURCE GPIO_PinSource5

#define SPI_MISO_GPIO_PORT GPIOA
#define SPI_MISO_GPIO_PIN GPIO_Pin_6
#define SPI_MISO_GPIO_PIN_SOURCE GPIO_PinSource6

#define SPI_MOSI_GPIO_PORT GPIOA
#define SPI_MOSI_GPIO_PIN GPIO_Pin_7
#define SPI_MOSI_GPIO_PIN_SOURCE GPIO_PinSource7

void SPI1_Init(void);
void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler);
u8 SPI1_ReadWriteByte(u8 TxData);
u8 SPI1_ReadByte(void);
void SPI1_WriteByte(u8 TxData);
void SPI1_ReadBurst(u8 *pBuffer, u16 len);
void SPI1_WriteBurst(u8* pBuffer, u16 len);

#endif
