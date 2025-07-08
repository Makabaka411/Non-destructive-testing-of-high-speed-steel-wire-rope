#include "led.h"


void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitSturct;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    GPIO_InitSturct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitSturct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitSturct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitSturct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitSturct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOF, &GPIO_InitSturct);

    GPIO_SetBits(GPIOF, GPIO_Pin_9 | GPIO_Pin_10);
}

