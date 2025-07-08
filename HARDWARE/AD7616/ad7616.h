#ifndef __AD7616_H
#define __AD7616_H

#include "sys.h"
#include "delay.h"
#include "usart.h"


#define Range_10V 0x0000
#define Range_5V 0x00AA
#define Range_2V5 0x0055

/* 复位引脚 */
#define RESET PFout(12)
#define RESET_GPIO_PORT GPIOF
#define RESET_GPIO_PIN GPIO_Pin_12
#define RESET_GPIO_CLK RCC_AHB1Periph_GPIOF

/* 通道序列器使能输入，软件模式接地 */
#define SEQEN PFout(0)
#define SEQEN_GPIO_PORT GPIOF
#define SEQEN_GPIO_PIN GPIO_Pin_0
#define SEQEN_GPIO_CLK RCC_AHB1Periph_GPIOF

/* HW_RNGSEL=00，软件模式；01，硬件模式 ±2.5V；10，硬件模式 ±5V；11，硬件模式±10V */
#define RNGSEL1 PFout(1)
#define RNGSEL1_GPIO_PORT GPIOF
#define RNGSEL1_GPIO_PIN GPIO_Pin_1
#define RNGSEL1_GPIO_CLK RCC_AHB1Periph_GPIOF

/* HW_RNGSEL=00，软件模式；01，硬件模式 ±2.5V；10，硬件模式 ±5V；11，硬件模式±10V */
#define RNGSEL0 PFout(2)
#define RNGSEL0_GPIO_PORT GPIOF
#define RNGSEL0_GPIO_PIN GPIO_Pin_2
#define RNGSEL0_GPIO_CLK RCC_AHB1Periph_GPIOF

/* 低电平：并行 ； 高电平：串行 */
#define SER PFout(3)
#define SER_GPIO_PORT GPIOF
#define SER_GPIO_PIN GPIO_Pin_3
#define SER_GPIO_CLK RCC_AHB1Periph_GPIOF

/* 串行接地 */
#define D0 PFout(4)
#define D0_GPIO_PORT GPIOF
#define D0_GPIO_PIN GPIO_Pin_4
#define D0_GPIO_CLK RCC_AHB1Periph_GPIOF

/* 串行接地 */
#define D1 PDout(10)
#define D1_GPIO_PORT GPIOD
#define D1_GPIO_PIN GPIO_Pin_10
#define D1_GPIO_CLK RCC_AHB1Periph_GPIOD

/* 串行接地 */
#define D2 PDout(9)
#define D2_GPIO_PORT GPIOD
#define D2_GPIO_PIN GPIO_Pin_9
#define D2_GPIO_CLK RCC_AHB1Periph_GPIOD

/* 串行接地 */
#define D3 PDout(8)
#define D3_GPIO_PORT GPIOD
#define D3_GPIO_PIN GPIO_Pin_8
#define D3_GPIO_CLK RCC_AHB1Periph_GPIOD

/* 串行模式下，高电平：输出在 SDOA 与 SDOB 上 ； 低电平：输出在 SDOA上 */
#define D4 PDout(14)
#define D4_GPIO_PORT GPIOD
#define D4_GPIO_PIN GPIO_Pin_14
#define D4_GPIO_CLK RCC_AHB1Periph_GPIOD

/* 串行模式下：高电平：有 CRC 字 ；低电平：无 CRC 字 */
#define D5 PEout(15)
#define D5_GPIO_PORT GPIOE
#define D5_GPIO_PIN GPIO_Pin_15
#define D5_GPIO_CLK RCC_AHB1Periph_GPIOE

/* 串行接地 */
#define D6 PDout(15)
#define D6_GPIO_PORT GPIOD
#define D6_GPIO_PIN GPIO_Pin_15
#define D6_GPIO_CLK RCC_AHB1Periph_GPIOD

/* 串行接地 */
#define D7 PEout(7)
#define D7_GPIO_PORT GPIOE
#define D7_GPIO_PIN GPIO_Pin_7
#define D7_GPIO_CLK RCC_AHB1Periph_GPIOE

/* 串行接地 */
#define D8 PEout(8)
#define D8_GPIO_PORT GPIOE
#define D8_GPIO_PIN GPIO_Pin_8
#define D8_GPIO_CLK RCC_AHB1Periph_GPIOE

/* 串行接地 */
#define D9 PEout(9)
#define D9_GPIO_PORT GPIOE
#define D9_GPIO_PIN GPIO_Pin_9
#define D9_GPIO_CLK RCC_AHB1Periph_GPIOE

/* 串行模式，为SPI的输出接口 */
#define D10 PEout(14)
#define D10_GPIO_PORT GPIOE
#define D10_GPIO_PIN GPIO_Pin_14
#define D10_GPIO_CLK RCC_AHB1Periph_GPIOE

/* D11/SDOB，串行输出数据 B */
#define SDOB PEin(13)
#define SDOB_GPIO_PORT GPIOE
#define SDOB_GPIO_PIN GPIO_Pin_13
#define SDOB_GPIO_CLK RCC_AHB1Periph_GPIOE

/* D12/SDOA，串行输出数据 A */
#define SDOA PEin(12)
#define SDOA_GPIO_PORT GPIOE
#define SDOA_GPIO_PIN GPIO_Pin_12
#define SDOA_GPIO_CLK RCC_AHB1Periph_GPIOE

/* D13/OS0，串行模式过采样选择；软件串行接地 */
#define OS0 PEout(10)
#define OS0_GPIO_PORT GPIOE
#define OS0_GPIO_PIN GPIO_Pin_10
#define OS0_GPIO_CLK RCC_AHB1Periph_GPIOE

/* D14/OS1，串行模式过采样选择；软件串行接地 */
#define OS1 PEout(11)
#define OS1_GPIO_PORT GPIOE
#define OS1_GPIO_PIN GPIO_Pin_11
#define OS1_GPIO_CLK RCC_AHB1Periph_GPIOE

/* D15/OS2，串行模式过采样选择；软件串行接地 */
#define OS2 PFout(13)
#define OS2_GPIO_PORT GPIOF
#define OS2_GPIO_PIN GPIO_Pin_13
#define OS2_GPIO_CLK RCC_AHB1Periph_GPIOF

/* 软件串行接地 */
#define WR PDout(13)
#define WR_GPIO_PORT GPIOD
#define WR_GPIO_PIN GPIO_Pin_13
#define WR_GPIO_CLK RCC_AHB1Periph_GPIOD

/* 时钟线 */
#define SCK PDout(12)
#define SCK_GPIO_PORT GPIOD
#define SCK_GPIO_PIN GPIO_Pin_12
#define SCK_GPIO_CLK RCC_AHB1Periph_GPIOD

/* 片选，低电平有效 */
#define CS PDout(11)
#define CS_GPIO_PORT GPIOD
#define CS_GPIO_PIN GPIO_Pin_11
#define CS_GPIO_CLK RCC_AHB1Periph_GPIOD

/* 软件模式接地 */
#define CH0 PFout(5)
#define CH0_GPIO_PORT GPIOF
#define CH0_GPIO_PIN GPIO_Pin_5
#define CH0_GPIO_CLK RCC_AHB1Periph_GPIOF

/* 软件模式接地 */
#define CH1 PBout(13)
#define CH1_GPIO_PORT GPIOB
#define CH1_GPIO_PIN GPIO_Pin_13
#define CH1_GPIO_CLK RCC_AHB1Periph_GPIOB

/* 软件模式接地 */
#define CH2 PBout(12)
#define CH2_GPIO_PORT GPIOB
#define CH2_GPIO_PIN GPIO_Pin_12
#define CH2_GPIO_CLK RCC_AHB1Periph_GPIOB

/* 数据必须在BUSY为高电平时进行读取 */
#define BUSY PFin(6)
#define BUSY_GPIO_PORT GPIOF
#define BUSY_GPIO_PIN GPIO_Pin_6
#define BUSY_GPIO_CLK RCC_AHB1Periph_GPIOF

/* CONVST从低电平到高电平时开始转换(会进行一对通道的转换) */
#define CONVST PFout(7)
#define CONVST_GPIO_PORT GPIOF
#define CONVST_GPIO_PIN GPIO_Pin_7
#define CONVST_GPIO_CLK RCC_AHB1Periph_GPIOF

void AD7616_Init(void);
void AD7616_State_Init(void);
void AD7616_Reset(void);
void AD7616_Start_Convst(void);
void AD7616_SPI_Read(int16_t *CHA_Data, int16_t *CHB_Data);
void AD7616_Read_Data(void);
void AD7616_Write_Data(uint16_t txdata);
void AD7616_Mask(void);

#endif
