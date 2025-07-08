#ifndef __LED_H
#define __LED_H

#include "./sys.h"

#define LED0 PFout(9)
#define LED1 PFout(10)

// #define LED0(x)                                 \
//     do                                          \
//     {                                           \
//         x ? GPIO_ResetBits(GPIOF, GPIO_Pin_9) : \
//         GPIO_SetBits(GPIOF, GPIO_Pin_9);        \
//     } while (0);

// #define LED1(x)                                  \
//     do                                           \
//     {                                            \
//         x ? GPIO_ResetBits(GPIOF, GPIO_Pin_10) : \
//         GPIO_SetBits(GPIOF, GPIO_Pin_10);        \
//     } while (0);

#define LED0_TOGGLE() do {GPIO_ToggleBits(GPIOF, GPIO_Pin_9);} while(0)
#define LED1_TOGGLE() do {GPIO_ToggleBits(GPIOF, GPIO_Pin_10);} while(0)

void LED_Init(void);

#endif
