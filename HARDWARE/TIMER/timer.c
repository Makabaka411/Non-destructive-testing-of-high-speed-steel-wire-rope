#include "timer.h"
//#include "led.h"
#include "usart.h"

int circle_count=0;
int flagEncoder=0;

void Encoder_Init(void)
{
	GPIO_InitTypeDef         GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	TIM_ICInitTypeDef        TIM_ICInitStructure;
  NVIC_InitTypeDef         NVIC_InitStructure;
	
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);


  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_TIM4);         //GPIOx����Ϊ��ʱ��
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_TIM4);         //GPIOx����Ϊ��ʱ��
	
	/*- ������������������ PB->6  PB->7 -*/
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6 | GPIO_Pin_7;         
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;                //��������һ��������һ�±�֤��ƽȷ��     
	GPIO_Init(GPIOB, &GPIO_InitStructure);                           

	/*- TIM4������ģʽ���� -*/
	TIM_DeInit(TIM4);
	TIM_TimeBaseStructure.TIM_Period = 1 ;//TIM4_Encoder_Line_Number*TIM4_Encoder_Line_Multiple-1;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);              
                 
	TIM_EncoderInterfaceConfig(TIM4, TIM4_ENCODER_MODE, TIM_ICPolarity_Rising ,TIM_ICPolarity_Rising);	//���ñ�����ģʽ����Դ�ͼ���
  
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;                                  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;    
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;                   
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                               
	NVIC_Init(&NVIC_InitStructure);
	
	
	/*��������������ж�*/
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	
  TIM_SetCounter(TIM4, 0);
  TIM_Cmd(TIM4, ENABLE);   //������ʱ��
}

int16_t Encoder_Get(void)
{
//		int16_t Temp;
//		Temp = circle_count;
//		circle_count = 0;
		return circle_count;
		
}

void TIM4_IRQHandler(void)   
{
    flagEncoder=1;

	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  
	{
    if((TIM4->CR1>>4 & 0x01)==0) //DIR==0 
        circle_count++; 
    else if((TIM4->CR1>>4 & 0x01)==1)//DIR==1 
        circle_count--; 
   }
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	
}

