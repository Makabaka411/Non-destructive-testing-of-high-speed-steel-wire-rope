#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//定时器 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/6/16
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
#define TIM4_ENCODER_MODE                        TIM_EncoderMode_TI12//TIM_EncoderMode_TI1  TIM_EncoderMode_TI1 单相单边沿计数，2倍 
                                                                    //TIM_EncoderMode_TI12                     双相双边沿计数，4倍

void Encoder_Init(void);
int16_t Encoder_Get(void);

#endif
