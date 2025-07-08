#include "include.h"


float R_Calibrate[32] = {0};       //校零实部电压初始值存放
float I_Calibrate[32] = {0};       //校零虚部电压初始值存放
float R_Sum[32] = {0};             //存放多次ADC采集的电压实部信号值
float I_Sum[32] = {0};             //存放多次ADC采集的电压虚部信号值
float R_Average[32] = {0};         //存放多次ADC采集后平均的电压实部信号值
float I_Average[32] = {0};         //存放多次ADC采集后平均的电压虚部信号值
float Amplitude[32] = {0};         //各通道的阻抗电压幅值
float Phase[32] = {0};             //各通道的阻抗电压相位
float R[32]={0};                   //存放ADC采集的电压实部信号值
float I[32]={0};                   //存放ADC采集的电压虚部信号值
char ClearFlag = 0;                //校零标志位
char EigenvalueFlag = 0;           //上传特征值选择标志位




/**********************************************************************************************************
*	函 数 名: Calibrate
*	功能说明: 将所有通道的初始数据读入，以便后一步进行校零操作
*	形    参：无
*	返 回 值: 无
**********************************************************************************************************/
void Calibrate(void)
{
	char i = 0;
	
	for(i = 0; i <= 31; i++)
	{
		Select_Channel();                         //模拟开关进行通道的选择
	    Data_Acquisition(select_Channel,20);      //通道数据采集
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
*	函 数 名: Data_Acquisition
*	功能说明: 读取此时通道的数据值
*	形    参：channel 选通的通道数       time  均值滤波的次数
*	返 回 值: 无
**********************************************************************************************************/
void Data_Acquisition(int16_t channel,int16_t time)
{
	char i = 0;
	delay_ms(10);              //通道选通后需要对其进行一定的延时，否则数据采集会出现错乱
	
	R_Sum[channel] = 0;
	I_Sum[channel] = 0;
	
	for(i = 0; i < time; i++)
	{
		AD7606_Scan();         //AD7606对数据的采集	 
		AD7606_Mak();          //AD7606对采集的数据进行转换，转换为电压值
		R_Sum[channel] = R_Sum[channel] + s_volt[6];
		I_Sum[channel] = I_Sum[channel] + s_volt[7];		  
	}

    R_Average[channel] = R_Sum[channel] / time;
	I_Average[channel] = I_Sum[channel] / time;

}


/**********************************************************************************************************
*	函 数 名: Amplitude_Calculation
*	功能说明: 通过电压实部和虚部计算出电压的幅值
*	形    参：无
*	返 回 值: 无
**********************************************************************************************************/

void Amplitude_Calculation(float R1,float I1)
{
	Amplitude[select_Channel] = sqrt((double)(R1*R1+I1*I1));
}


/**********************************************************************************************************
*	函 数 名: Phase_Calculation
*	功能说明: 通过电压实部和虚部计算出电压的相位
*	形    参：无
*	返 回 值: 无
**********************************************************************************************************/

void Phase_Calculation(float R1,float I1,float R2,float I2)
{
	Phase[select_Channel] = atan2(R1,I1) * 180 / PI - atan2(R2,I2) * 180 / PI;
}


/**********************************************************************************************************
*	函 数 名: Feature_Extraction
*	功能说明: 求取最终的电压实部虚部幅值和相位
*	形    参：无
*	返 回 值: 无
**********************************************************************************************************/

void Feature_Extraction(void)
{
	 R[select_Channel] = R_Average[select_Channel] - R_Calibrate[select_Channel];   //求阻抗变化电压的实部 
	 I[select_Channel] = I_Average[select_Channel] - I_Calibrate[select_Channel];	 //求阻抗变化电压的虚部  
	 R[select_Channel] = R[select_Channel] < 0 ?  (R[select_Channel] = -R[select_Channel]) :  (R[select_Channel] = R[select_Channel]); 
	 I[select_Channel] = I[select_Channel] < 0 ?  (I[select_Channel] = -I[select_Channel]) :  (I[select_Channel] = I[select_Channel]); 
	 Amplitude_Calculation(R[select_Channel],I[select_Channel]);    //求阻抗变化电压的幅值   Amplitude[32]
	 Phase_Calculation(R_Average[select_Channel],I_Average[select_Channel],R_Calibrate[select_Channel],I_Calibrate[select_Channel]);        //求阻抗变化电压的相位   Phase[32]
}


/**********************************************************************************************************
*	函 数 名: Instruction_receiving
*	功能说明: 上位机传输指令的接受雨转换函数
*	形    参：无
*	返 回 值: 无
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


