#include "include.h"

void SPI1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    SPI_InitTypeDef SPI_InitStruct;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE); /*APB2为84MHz*/

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = SPI_SCK_GPIO_PIN | SPI_MISO_GPIO_PIN | SPI_MOSI_GPIO_PIN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_PinAFConfig(SPI_SCK_GPIO_PORT, SPI_SCK_GPIO_PIN_SOURCE, GPIO_AF_SPI1);
    GPIO_PinAFConfig(SPI_MISO_GPIO_PORT, SPI_MISO_GPIO_PIN_SOURCE, GPIO_AF_SPI1);
    GPIO_PinAFConfig(SPI_MOSI_GPIO_PORT, SPI_MOSI_GPIO_PIN_SOURCE, GPIO_AF_SPI1);

    RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, ENABLE);  /*复位 SPI1*/
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, DISABLE); /*停止复位 SPI1*/

    SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStruct.SPI_CRCPolynomial = 7;
    SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex; /*全双工*/
    SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;                 /*高位*/
    SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
    SPI_InitStruct.SPI_NSS = SPI_NSS_Soft; /*NSS信号由软件控制*/
    SPI_Init(SPI1, &SPI_InitStruct);

    SPI_Cmd(SPI1, ENABLE);

    SPI1_ReadWriteByte(0XFF);
}

void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler)
{
    assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
    SPI_Cmd(SPI1, DISABLE);
    SPI1->CR1 &= 0XFFC7;
    SPI1->CR1 |= SPI_BaudRatePrescaler;
    SPI_Cmd(SPI1, ENABLE);
}

u8 SPI1_ReadWriteByte(u8 TxData)
{
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
    {
    }
    SPI_I2S_SendData(SPI1, TxData);
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)
    {
    }
    return SPI_I2S_ReceiveData(SPI1);
}

u8 SPI1_ReadByte(void)
{
    return SPI1_ReadWriteByte(0XAA);
}

void SPI1_WriteByte(u8 TxData)
{
    SPI1_ReadWriteByte(TxData);
}

void SPI1_ReadBurst(u8 *pBuffer, u16 len)
{
    while (len-- > 0)
    {
        *pBuffer++ = SPI1_ReadWriteByte(0XAA);
    }
}

void SPI1_WriteBurst(u8* pBuffer, u16 len)
{
    while (len-- > 0)
    {
        SPI1_ReadWriteByte(*pBuffer++);
    }
}
