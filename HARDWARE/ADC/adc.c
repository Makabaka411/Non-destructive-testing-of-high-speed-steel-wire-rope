#include "adc.h"

__IO uint16_t ADC_ConvertedValue[RHEOSTAT_NOFCHANEL]={0};

static void Rheostat_ADC_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	

	/*=====================ͨ��0======================*/	
	// ʹ�� GPIO ʱ��
	RCC_AHB1PeriphClockCmd(RHEOSTAT_ADC_GPIO_CLK0,ENABLE);		
	// ���� IO
  GPIO_InitStructure.GPIO_Pin = RHEOSTAT_ADC_GPIO_PIN0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  //������������	
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(RHEOSTAT_ADC_GPIO_PORT0, &GPIO_InitStructure);
	/*=====================ͨ��1======================*/	
	// ʹ�� GPIO ʱ��
	RCC_AHB1PeriphClockCmd(RHEOSTAT_ADC_GPIO_CLK1,ENABLE);		
	// ���� IO
  GPIO_InitStructure.GPIO_Pin = RHEOSTAT_ADC_GPIO_PIN1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  //������������	
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(RHEOSTAT_ADC_GPIO_PORT1, &GPIO_InitStructure);

	/*=====================ͨ��2======================*/
	// ʹ�� GPIO ʱ��
	RCC_AHB1PeriphClockCmd(RHEOSTAT_ADC_GPIO_CLK2,ENABLE);		
	// ���� IO
  GPIO_InitStructure.GPIO_Pin = RHEOSTAT_ADC_GPIO_PIN2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  //������������	
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(RHEOSTAT_ADC_GPIO_PORT2, &GPIO_InitStructure);	

	/*=====================ͨ��3=======================*/
	// ʹ�� GPIO ʱ��
	RCC_AHB1PeriphClockCmd(RHEOSTAT_ADC_GPIO_CLK3,ENABLE);		
	// ���� IO
  GPIO_InitStructure.GPIO_Pin = RHEOSTAT_ADC_GPIO_PIN3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  //������������	
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(RHEOSTAT_ADC_GPIO_PORT3, &GPIO_InitStructure);
	/*=====================ͨ��4=======================*/
	// ʹ�� GPIO ʱ��
	RCC_AHB1PeriphClockCmd(RHEOSTAT_ADC_GPIO_CLK4,ENABLE);		
	// ���� IO
  GPIO_InitStructure.GPIO_Pin = RHEOSTAT_ADC_GPIO_PIN4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  //������������	
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(RHEOSTAT_ADC_GPIO_PORT4, &GPIO_InitStructure);
	/*=====================ͨ��5=======================*/
	// ʹ�� GPIO ʱ��
	RCC_AHB1PeriphClockCmd(RHEOSTAT_ADC_GPIO_CLK5,ENABLE);		
	// ���� IO
  GPIO_InitStructure.GPIO_Pin = RHEOSTAT_ADC_GPIO_PIN5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  //������������	
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(RHEOSTAT_ADC_GPIO_PORT5, &GPIO_InitStructure);
	/*=====================ͨ��6=======================*/
	// ʹ�� GPIO ʱ��
	RCC_AHB1PeriphClockCmd(RHEOSTAT_ADC_GPIO_CLK6,ENABLE);		
	// ���� IO
  GPIO_InitStructure.GPIO_Pin = RHEOSTAT_ADC_GPIO_PIN6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  //������������	
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(RHEOSTAT_ADC_GPIO_PORT6, &GPIO_InitStructure);
	/*=====================ͨ��7=======================*/
	// ʹ�� GPIO ʱ��
	RCC_AHB1PeriphClockCmd(RHEOSTAT_ADC_GPIO_CLK7,ENABLE);		
	// ���� IO
  GPIO_InitStructure.GPIO_Pin = RHEOSTAT_ADC_GPIO_PIN7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  //������������	
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(RHEOSTAT_ADC_GPIO_PORT7, &GPIO_InitStructure);
	/*=====================ͨ��8=======================*/
	// ʹ�� GPIO ʱ��
	RCC_AHB1PeriphClockCmd(RHEOSTAT_ADC_GPIO_CLK8,ENABLE);		
	// ���� IO
  GPIO_InitStructure.GPIO_Pin = RHEOSTAT_ADC_GPIO_PIN8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  //������������	
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(RHEOSTAT_ADC_GPIO_PORT8, &GPIO_InitStructure);
	/*=====================ͨ��9=======================*/
	// ʹ�� GPIO ʱ��
	RCC_AHB1PeriphClockCmd(RHEOSTAT_ADC_GPIO_CLK9,ENABLE);		
	// ���� IO
  GPIO_InitStructure.GPIO_Pin = RHEOSTAT_ADC_GPIO_PIN9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  //������������	
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(RHEOSTAT_ADC_GPIO_PORT9, &GPIO_InitStructure);
	/*=====================ͨ��10======================*/
	// ʹ�� GPIO ʱ��
	RCC_AHB1PeriphClockCmd(RHEOSTAT_ADC_GPIO_CLK10,ENABLE);		
	// ���� IO
  GPIO_InitStructure.GPIO_Pin = RHEOSTAT_ADC_GPIO_PIN10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  //������������	
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(RHEOSTAT_ADC_GPIO_PORT10, &GPIO_InitStructure);
	/*=====================ͨ��11=======================*/
	// ʹ�� GPIO ʱ��
	RCC_AHB1PeriphClockCmd(RHEOSTAT_ADC_GPIO_CLK11,ENABLE);		
	// ���� IO
  GPIO_InitStructure.GPIO_Pin = RHEOSTAT_ADC_GPIO_PIN11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  //������������	
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(RHEOSTAT_ADC_GPIO_PORT11, &GPIO_InitStructure);
	/*=====================ͨ��12======================*/
	// ʹ�� GPIO ʱ��
	RCC_AHB1PeriphClockCmd(RHEOSTAT_ADC_GPIO_CLK12,ENABLE);		
	// ���� IO
  GPIO_InitStructure.GPIO_Pin = RHEOSTAT_ADC_GPIO_PIN12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  //������������	
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(RHEOSTAT_ADC_GPIO_PORT12, &GPIO_InitStructure);
	/*=====================ͨ��13======================*/
	// ʹ�� GPIO ʱ��
	RCC_AHB1PeriphClockCmd(RHEOSTAT_ADC_GPIO_CLK13,ENABLE);		
	// ���� IO
  GPIO_InitStructure.GPIO_Pin = RHEOSTAT_ADC_GPIO_PIN13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  //������������	
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(RHEOSTAT_ADC_GPIO_PORT13, &GPIO_InitStructure);
	/*=====================ͨ��14======================*/
	// ʹ�� GPIO ʱ��
	RCC_AHB1PeriphClockCmd(RHEOSTAT_ADC_GPIO_CLK14,ENABLE);		
	// ���� IO
  GPIO_InitStructure.GPIO_Pin = RHEOSTAT_ADC_GPIO_PIN14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  //������������	
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(RHEOSTAT_ADC_GPIO_PORT14, &GPIO_InitStructure);
	/*=====================ͨ��15======================*/
	// ʹ�� GPIO ʱ��
	RCC_AHB1PeriphClockCmd(RHEOSTAT_ADC_GPIO_CLK15,ENABLE);		
	// ���� IO
  GPIO_InitStructure.GPIO_Pin = RHEOSTAT_ADC_GPIO_PIN15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  //������������	
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(RHEOSTAT_ADC_GPIO_PORT15, &GPIO_InitStructure);
}

static void Rheostat_ADC_Mode_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
	
  // ------------------DMA Init �ṹ����� ��ʼ��--------------------------
  // ADC1ʹ��DMA2��������0��ͨ��0��������ֲ�̶�����
  // ����DMAʱ��
  RCC_AHB1PeriphClockCmd(RHEOSTAT_ADC_DMA_CLK, ENABLE); 
	// �����ַΪ��ADC ���ݼĴ�����ַ
	DMA_InitStructure.DMA_PeripheralBaseAddr = RHEOSTAT_ADC_DR_ADDR;	
  // �洢����ַ��ʵ���Ͼ���һ���ڲ�SRAM�ı���	
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)ADC_ConvertedValue;  
  // ���ݴ��䷽��Ϊ���赽�洢��	
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;	
	// ��������СΪ��ָһ�δ����������
	DMA_InitStructure.DMA_BufferSize = RHEOSTAT_NOFCHANEL;	
	// ����Ĵ���ֻ��һ������ַ���õ���
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  // �洢����ַ�̶�
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; 
  // // �������ݴ�СΪ���֣��������ֽ� 
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; 
  //	�洢�����ݴ�СҲΪ���֣����������ݴ�С��ͬ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;	
	// ѭ������ģʽ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  // DMA ����ͨ�����ȼ�Ϊ�ߣ���ʹ��һ��DMAͨ��ʱ�����ȼ����ò�Ӱ��
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  // ��ֹDMA FIFO	��ʹ��ֱ��ģʽ
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;  
  // FIFO ��С��FIFOģʽ��ֹʱ�������������	
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;  
	// ѡ�� DMA ͨ����ͨ������������
  DMA_InitStructure.DMA_Channel = RHEOSTAT_ADC_DMA_CHANNEL; 
  //��ʼ��DMA�������൱��һ����Ĺܵ����ܵ������кܶ�ͨ��
	DMA_Init(RHEOSTAT_ADC_DMA_STREAM, &DMA_InitStructure);
	// ʹ��DMA��
  DMA_Cmd(RHEOSTAT_ADC_DMA_STREAM, ENABLE);
	
	// ����ADCʱ��
	RCC_APB2PeriphClockCmd(RHEOSTAT_ADC_CLK , ENABLE);
  // -------------------ADC Common �ṹ�� ���� ��ʼ��------------------------
	// ����ADCģʽ
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
  // ʱ��Ϊfpclk x��Ƶ	
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;
  // ��ֹDMAֱ�ӷ���ģʽ	
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
  // ����ʱ����	
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;  
  ADC_CommonInit(&ADC_CommonInitStructure);
	
  // -------------------ADC Init �ṹ�� ���� ��ʼ��--------------------------
	ADC_StructInit(&ADC_InitStructure);
  // ADC �ֱ���
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  // ɨ��ģʽ����ͨ���ɼ���Ҫ	
  ADC_InitStructure.ADC_ScanConvMode = ENABLE; 
  // ����ת��	
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 
  //��ֹ�ⲿ���ش���
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  //�ⲿ����ͨ����������ʹ�������������ֵ��㸳ֵ����
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
  //�����Ҷ���	
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  //ת��ͨ�� 1��
  ADC_InitStructure.ADC_NbrOfConversion = RHEOSTAT_NOFCHANEL;                                    
  ADC_Init(RHEOSTAT_ADC, &ADC_InitStructure);
  //---------------------------------------------------------------------------
	
  // ���� ADC ͨ��ת��˳��Ͳ���ʱ������
  ADC_RegularChannelConfig(RHEOSTAT_ADC, RHEOSTAT_ADC_CHANNEL0, 1, 
	                         ADC_SampleTime_480Cycles);
  ADC_RegularChannelConfig(RHEOSTAT_ADC, RHEOSTAT_ADC_CHANNEL1, 2, 
	                         ADC_SampleTime_480Cycles); 
  ADC_RegularChannelConfig(RHEOSTAT_ADC, RHEOSTAT_ADC_CHANNEL2, 3, 
	                         ADC_SampleTime_480Cycles); 
  ADC_RegularChannelConfig(RHEOSTAT_ADC, RHEOSTAT_ADC_CHANNEL3, 4, 
	                         ADC_SampleTime_480Cycles); 
  ADC_RegularChannelConfig(RHEOSTAT_ADC, RHEOSTAT_ADC_CHANNEL4, 5, 
	                         ADC_SampleTime_480Cycles); 
  ADC_RegularChannelConfig(RHEOSTAT_ADC, RHEOSTAT_ADC_CHANNEL5, 6, 
	                         ADC_SampleTime_480Cycles); 
  ADC_RegularChannelConfig(RHEOSTAT_ADC, RHEOSTAT_ADC_CHANNEL6, 7, 
	                         ADC_SampleTime_480Cycles); 
  ADC_RegularChannelConfig(RHEOSTAT_ADC, RHEOSTAT_ADC_CHANNEL7, 8, 
	                         ADC_SampleTime_480Cycles); 
  ADC_RegularChannelConfig(RHEOSTAT_ADC, RHEOSTAT_ADC_CHANNEL8, 9, 
	                         ADC_SampleTime_480Cycles); 
  ADC_RegularChannelConfig(RHEOSTAT_ADC, RHEOSTAT_ADC_CHANNEL9, 10, 
	                         ADC_SampleTime_480Cycles); 
  ADC_RegularChannelConfig(RHEOSTAT_ADC, RHEOSTAT_ADC_CHANNEL10, 11, 
	                         ADC_SampleTime_480Cycles); 
  ADC_RegularChannelConfig(RHEOSTAT_ADC, RHEOSTAT_ADC_CHANNEL11, 12, 
	                         ADC_SampleTime_480Cycles); 
  ADC_RegularChannelConfig(RHEOSTAT_ADC, RHEOSTAT_ADC_CHANNEL12, 13, 
	                         ADC_SampleTime_480Cycles); 
  ADC_RegularChannelConfig(RHEOSTAT_ADC, RHEOSTAT_ADC_CHANNEL13, 14, 
	                         ADC_SampleTime_480Cycles); 
  ADC_RegularChannelConfig(RHEOSTAT_ADC, RHEOSTAT_ADC_CHANNEL14, 15, 
	                         ADC_SampleTime_480Cycles); 
  ADC_RegularChannelConfig(RHEOSTAT_ADC, RHEOSTAT_ADC_CHANNEL15, 16, 
	                         ADC_SampleTime_480Cycles); 

  // ʹ��DMA���� after last transfer (Single-ADC mode)
  ADC_DMARequestAfterLastTransferCmd(RHEOSTAT_ADC, ENABLE);
  // ʹ��ADC DMA
  ADC_DMACmd(RHEOSTAT_ADC, ENABLE);
	
	// ʹ��ADC
  ADC_Cmd(RHEOSTAT_ADC, ENABLE);  
  //��ʼadcת�����������
  ADC_SoftwareStartConv(RHEOSTAT_ADC);
}

void Rheostat_Init(void)
{
	Rheostat_ADC_GPIO_Config();
	Rheostat_ADC_Mode_Config();
}

