#ifndef __ADC_H
#define	__ADC_H

#include "stm32f4xx.h"
#include "sys.h" 

#define RHEOSTAT_NOFCHANEL      16


/*=====================通道0 IO======================*/
// PA0 
// ADC IO宏定义
#define RHEOSTAT_ADC_GPIO_PORT0    GPIOA
#define RHEOSTAT_ADC_GPIO_PIN0     GPIO_Pin_0
#define RHEOSTAT_ADC_GPIO_CLK0     RCC_AHB1Periph_GPIOA
#define RHEOSTAT_ADC_CHANNEL0      ADC_Channel_0
/*=====================通道1 IO======================*/
// PA1 
// ADC IO宏定义
#define RHEOSTAT_ADC_GPIO_PORT1    GPIOA
#define RHEOSTAT_ADC_GPIO_PIN1     GPIO_Pin_1
#define RHEOSTAT_ADC_GPIO_CLK1     RCC_AHB1Periph_GPIOA
#define RHEOSTAT_ADC_CHANNEL1      ADC_Channel_1
/*=====================通道2 IO======================*/
// PA2 
// ADC IO宏定义
#define RHEOSTAT_ADC_GPIO_PORT2    GPIOA
#define RHEOSTAT_ADC_GPIO_PIN2     GPIO_Pin_2
#define RHEOSTAT_ADC_GPIO_CLK2     RCC_AHB1Periph_GPIOA
#define RHEOSTAT_ADC_CHANNEL2      ADC_Channel_2
/*=====================通道3 IO======================*/
// PA3 
// ADC IO宏定义
#define RHEOSTAT_ADC_GPIO_PORT3    GPIOA
#define RHEOSTAT_ADC_GPIO_PIN3     GPIO_Pin_3
#define RHEOSTAT_ADC_GPIO_CLK3     RCC_AHB1Periph_GPIOA
#define RHEOSTAT_ADC_CHANNEL3      ADC_Channel_3
/*=====================通道4 IO======================*/
// PA4 
// ADC IO宏定义
#define RHEOSTAT_ADC_GPIO_PORT4    GPIOA
#define RHEOSTAT_ADC_GPIO_PIN4     GPIO_Pin_4
#define RHEOSTAT_ADC_GPIO_CLK4     RCC_AHB1Periph_GPIOA
#define RHEOSTAT_ADC_CHANNEL4      ADC_Channel_4
/*=====================通道5 IO======================*/
// PA5 
// ADC IO宏定义
#define RHEOSTAT_ADC_GPIO_PORT5    GPIOA
#define RHEOSTAT_ADC_GPIO_PIN5     GPIO_Pin_5
#define RHEOSTAT_ADC_GPIO_CLK5     RCC_AHB1Periph_GPIOA
#define RHEOSTAT_ADC_CHANNEL5      ADC_Channel_5
/*=====================通道6 IO======================*/
// PA6 
// ADC IO宏定义
#define RHEOSTAT_ADC_GPIO_PORT6    GPIOA
#define RHEOSTAT_ADC_GPIO_PIN6     GPIO_Pin_6
#define RHEOSTAT_ADC_GPIO_CLK6     RCC_AHB1Periph_GPIOA
#define RHEOSTAT_ADC_CHANNEL6      ADC_Channel_6
/*=====================通道7 IO======================*/
// PA7 
// ADC IO宏定义
#define RHEOSTAT_ADC_GPIO_PORT7    GPIOA
#define RHEOSTAT_ADC_GPIO_PIN7     GPIO_Pin_7
#define RHEOSTAT_ADC_GPIO_CLK7     RCC_AHB1Periph_GPIOA
#define RHEOSTAT_ADC_CHANNEL7      ADC_Channel_7
/*=====================通道8 IO ======================*/
// PB0 
// ADC IO宏定义
#define RHEOSTAT_ADC_GPIO_PORT8    GPIOB
#define RHEOSTAT_ADC_GPIO_PIN8     GPIO_Pin_0
#define RHEOSTAT_ADC_GPIO_CLK8     RCC_AHB1Periph_GPIOB
#define RHEOSTAT_ADC_CHANNEL8      ADC_Channel_8
/*=====================通道9 IO ======================*/
// PB1 
// ADC IO宏定义
#define RHEOSTAT_ADC_GPIO_PORT9    GPIOB
#define RHEOSTAT_ADC_GPIO_PIN9     GPIO_Pin_1
#define RHEOSTAT_ADC_GPIO_CLK9     RCC_AHB1Periph_GPIOB
#define RHEOSTAT_ADC_CHANNEL9      ADC_Channel_9
/*=====================通道10 IO======================*/
// PC0 
// ADC IO宏定义
#define RHEOSTAT_ADC_GPIO_PORT10   GPIOC
#define RHEOSTAT_ADC_GPIO_PIN10    GPIO_Pin_0
#define RHEOSTAT_ADC_GPIO_CLK10    RCC_AHB1Periph_GPIOC
#define RHEOSTAT_ADC_CHANNEL10     ADC_Channel_10
/*=====================通道11 IO======================*/
// PC1 
// ADC IO宏定义
#define RHEOSTAT_ADC_GPIO_PORT11   GPIOC
#define RHEOSTAT_ADC_GPIO_PIN11    GPIO_Pin_1
#define RHEOSTAT_ADC_GPIO_CLK11    RCC_AHB1Periph_GPIOC
#define RHEOSTAT_ADC_CHANNEL11     ADC_Channel_11
/*=====================通道12 IO======================*/
// PC2 
// ADC IO宏定义
#define RHEOSTAT_ADC_GPIO_PORT12   GPIOC
#define RHEOSTAT_ADC_GPIO_PIN12    GPIO_Pin_2
#define RHEOSTAT_ADC_GPIO_CLK12    RCC_AHB1Periph_GPIOC
#define RHEOSTAT_ADC_CHANNEL12     ADC_Channel_12
/*=====================通道13 IO======================*/
// PC3 
// ADC IO宏定义
#define RHEOSTAT_ADC_GPIO_PORT13   GPIOC
#define RHEOSTAT_ADC_GPIO_PIN13    GPIO_Pin_3
#define RHEOSTAT_ADC_GPIO_CLK13    RCC_AHB1Periph_GPIOC
#define RHEOSTAT_ADC_CHANNEL13     ADC_Channel_13
/*=====================通道14 IO======================*/
// PC4 
// ADC IO宏定义
#define RHEOSTAT_ADC_GPIO_PORT14   GPIOC
#define RHEOSTAT_ADC_GPIO_PIN14    GPIO_Pin_4
#define RHEOSTAT_ADC_GPIO_CLK14    RCC_AHB1Periph_GPIOC
#define RHEOSTAT_ADC_CHANNEL14     ADC_Channel_14
/*=====================通道15 IO======================*/
// PC5 
// ADC IO宏定义
#define RHEOSTAT_ADC_GPIO_PORT15   GPIOC
#define RHEOSTAT_ADC_GPIO_PIN15    GPIO_Pin_5
#define RHEOSTAT_ADC_GPIO_CLK15    RCC_AHB1Periph_GPIOC
#define RHEOSTAT_ADC_CHANNEL15     ADC_Channel_15


// ADC 序号宏定义
#define RHEOSTAT_ADC              ADC1
#define RHEOSTAT_ADC_CLK          RCC_APB2Periph_ADC1
// ADC DR寄存器宏定义，ADC转换后的数字值则存放在这里
#define RHEOSTAT_ADC_DR_ADDR    ((u32)ADC1+0x4c)


// ADC DMA 通道宏定义，这里我们使用DMA传输
#define RHEOSTAT_ADC_DMA_CLK      RCC_AHB1Periph_DMA2
#define RHEOSTAT_ADC_DMA_CHANNEL  DMA_Channel_0
#define RHEOSTAT_ADC_DMA_STREAM   DMA2_Stream0

void Rheostat_Init(void);
#endif /* __BSP_ADC_H */

