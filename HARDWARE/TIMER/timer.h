#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//��ʱ�� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/6/16
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
#define TIM4_ENCODER_MODE                        TIM_EncoderMode_TI12//TIM_EncoderMode_TI1  TIM_EncoderMode_TI1 ���൥���ؼ�����2�� 
                                                                    //TIM_EncoderMode_TI12                     ˫��˫���ؼ�����4��

void Encoder_Init(void);
int16_t Encoder_Get(void);

#endif
