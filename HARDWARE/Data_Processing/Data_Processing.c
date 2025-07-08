#include "include.h"


float R_Calibrate[32] = {0};       //У��ʵ����ѹ��ʼֵ���
float I_Calibrate[32] = {0};       //У���鲿��ѹ��ʼֵ���
float R_Sum[32] = {0};             //��Ŷ��ADC�ɼ��ĵ�ѹʵ���ź�ֵ
float I_Sum[32] = {0};             //��Ŷ��ADC�ɼ��ĵ�ѹ�鲿�ź�ֵ
float R_Average[32] = {0};         //��Ŷ��ADC�ɼ���ƽ���ĵ�ѹʵ���ź�ֵ
float I_Average[32] = {0};         //��Ŷ��ADC�ɼ���ƽ���ĵ�ѹ�鲿�ź�ֵ
float Amplitude[32] = {0};         //��ͨ�����迹��ѹ��ֵ
float Phase[32] = {0};             //��ͨ�����迹��ѹ��λ
float R[32]={0};                   //���ADC�ɼ��ĵ�ѹʵ���ź�ֵ
float I[32]={0};                   //���ADC�ɼ��ĵ�ѹ�鲿�ź�ֵ
char ClearFlag = 0;                //У���־λ
char EigenvalueFlag = 0;           //�ϴ�����ֵѡ���־λ




/**********************************************************************************************************
*	�� �� ��: Calibrate
*	����˵��: ������ͨ���ĳ�ʼ���ݶ��룬�Ա��һ������У�����
*	��    �Σ���
*	�� �� ֵ: ��
**********************************************************************************************************/
void Calibrate(void)
{
	char i = 0;
	
	for(i = 0; i <= 31; i++)
	{
		Select_Channel();                         //ģ�⿪�ؽ���ͨ����ѡ��
	    Data_Acquisition(select_Channel,20);      //ͨ�����ݲɼ�
        R_Calibrate[select_Channel] = R_Average[select_Channel];
	    I_Calibrate[select_Channel] = I_Average[select_Channel];
		
        if(select_Channel>=31)
		 {
			select_Channel = 0;
		  }
		else
		 {
			select_Channel++;
		  }
			
	}
}


/**********************************************************************************************************
*	�� �� ��: Data_Acquisition
*	����˵��: ��ȡ��ʱͨ��������ֵ
*	��    �Σ�channel ѡͨ��ͨ����       time  ��ֵ�˲��Ĵ���
*	�� �� ֵ: ��
**********************************************************************************************************/
void Data_Acquisition(int16_t channel,int16_t time)
{
	char i = 0;
	delay_ms(10);              //ͨ��ѡͨ����Ҫ�������һ������ʱ���������ݲɼ�����ִ���
	
	R_Sum[channel] = 0;
	I_Sum[channel] = 0;
	
	for(i = 0; i < time; i++)
	{
		AD7606_Scan();         //AD7606�����ݵĲɼ�	 
		AD7606_Mak();          //AD7606�Բɼ������ݽ���ת����ת��Ϊ��ѹֵ
		R_Sum[channel] = R_Sum[channel] + s_volt[6];
		I_Sum[channel] = I_Sum[channel] + s_volt[7];		  
	}

    R_Average[channel] = R_Sum[channel] / time;
	I_Average[channel] = I_Sum[channel] / time;

}


/**********************************************************************************************************
*	�� �� ��: Amplitude_Calculation
*	����˵��: ͨ����ѹʵ�����鲿�������ѹ�ķ�ֵ
*	��    �Σ���
*	�� �� ֵ: ��
**********************************************************************************************************/

void Amplitude_Calculation(float R1,float I1)
{
	Amplitude[select_Channel] = sqrt((double)(R1*R1+I1*I1));
}


/**********************************************************************************************************
*	�� �� ��: Phase_Calculation
*	����˵��: ͨ����ѹʵ�����鲿�������ѹ����λ
*	��    �Σ���
*	�� �� ֵ: ��
**********************************************************************************************************/

void Phase_Calculation(float R1,float I1,float R2,float I2)
{
	Phase[select_Channel] = atan2(R1,I1) * 180 / PI - atan2(R2,I2) * 180 / PI;
}


/**********************************************************************************************************
*	�� �� ��: Feature_Extraction
*	����˵��: ��ȡ���յĵ�ѹʵ���鲿��ֵ����λ
*	��    �Σ���
*	�� �� ֵ: ��
**********************************************************************************************************/

void Feature_Extraction(void)
{
	 R[select_Channel] = R_Average[select_Channel] - R_Calibrate[select_Channel];   //���迹�仯��ѹ��ʵ�� 
	 I[select_Channel] = I_Average[select_Channel] - I_Calibrate[select_Channel];	 //���迹�仯��ѹ���鲿  
	 R[select_Channel] = R[select_Channel] < 0 ?  (R[select_Channel] = -R[select_Channel]) :  (R[select_Channel] = R[select_Channel]); 
	 I[select_Channel] = I[select_Channel] < 0 ?  (I[select_Channel] = -I[select_Channel]) :  (I[select_Channel] = I[select_Channel]); 
	 Amplitude_Calculation(R[select_Channel],I[select_Channel]);    //���迹�仯��ѹ�ķ�ֵ   Amplitude[32]
	 Phase_Calculation(R_Average[select_Channel],I_Average[select_Channel],R_Calibrate[select_Channel],I_Calibrate[select_Channel]);        //���迹�仯��ѹ����λ   Phase[32]
}


/**********************************************************************************************************
*	�� �� ��: Instruction_receiving
*	����˵��: ��λ������ָ��Ľ�����ת������
*	��    �Σ���
*	�� �� ֵ: ��
**********************************************************************************************************/

void Instruction_receiving(void)
{
	if(USART_RX_STA&0x8000)
		{					   
			USART_RX_STA=0;
			
			switch (USART_RX_BUF[0])
			{
				case 0:
				  ClearFlag = 1;
				  break;
				case 1:
				  EigenvalueFlag = 1;
				  break;
				case 2:
				  EigenvalueFlag = 2;
				  break;
				case 3:
				  EigenvalueFlag = 3;
				  break;
				case 4:
				  EigenvalueFlag = 4;
				  break;
				default:
				  break;
			}			
		}

}


