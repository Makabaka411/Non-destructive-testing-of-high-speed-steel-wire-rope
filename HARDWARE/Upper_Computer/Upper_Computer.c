#include "include.h"

// ������������
int16_t select_Channel = 0; // ��ǰ�����Ͳɼ���ͨ����8��ͨ��(0-7)
uint32_t freq = 0; // ���ļ���Ƶ�ʣ���λΪHz
uint16_t gain = 0; // �źŷ�������

// ���ǰ�������ñ�־λ
int8_t FreqIsSet = 0;    // ����Ƶ�����ñ�־λ
int8_t GainIsSet = 0;    // �����������ñ�־λ
int8_t ZeroCalIsSet = 0; // ����У׼���ñ�־λ

// �洢��ֵ����λ�Ĳɼ�ֵ��ת��ֵ
int16_t amplitude_Acquisition = 0;  // ��ֵ�Ĳɼ�ֵ
int16_t phase_Acquisition = 0;      // ��λ�Ĳɼ�ֵ
int16_t amplitude_Conversion = 0;   // ��ֵת�����ֵ
int16_t phase_Conversion = 0;       // ��λת�����ֵ

// �����˲������ݴ洢
const int16_t save_Count = 20; // �������ݵĸ���
int16_t save_AmplitudeArr[save_Count];
int16_t save_PhaseArr[save_Count];

// �Լ��ֵ����У0
uint16_t cal_Num = 0;
int16_t calibrationIsSet = 0;     //У��
int16_t calibration_Amplitude[8] = {0};
int16_t calibration_Phase[8] = {0};


// �Ƿ������ݸ���λ����־λ
int8_t b_Snedto_PC = 0;
uint8_t b_DiapWay = 0;

int32_t delay_us1 = 25000;

// �洢8��ͨ���ĵ�ǰ��λֵ
int16_t presrnt_Phase[8] = {0};


// �洢��ǰ����һ��������λ��ֵ
int16_t distanceArr[2] = {0, 0};

// ���������е�Ȧ��
int32_t turn = 0;

void Choice_Freq(uint8_t freq_Name);
void Set_Freq(uint32_t temp_Fre);
void Choice_Gain(uint8_t gain_Name);

/**********************************************************************************************************
��������Recv_Instruction
�������ܣ�������λ�����͵ĶԼ��ǰ�������õ�ָ��
�����������
�����������
����˵����Ŀǰֻ�����˼���Ƶ�ʣ��źŷŴ�����
**********************************************************************************************************/
void Recv_Instruction(void)
{
	while (1)
	{
			
		if(USART_RX_STA & 0x8000)
		{
				
			Choice_Freq(USART_RX_BUF[0]);
			Choice_Gain(USART_RX_BUF[1]);
					
			USART_RX_STA = 0;
		}
		
		// �ж�ָ���Ƿ�������ȷ
		if (FreqIsSet == 1 && GainIsSet == 1)
		{
			USART_RX_STA = 0;
			//printf(" bbb\r\n" );
			break;
		}
	}
}




/**********************************************************************************************************
��������Choice_Freq
�������ܣ�ѡ�����ü���Ƶ��
�����������õĺ����嵥��
���ñ������ĺ����嵥��
���������freq_Name-Ƶ�����õı�ţ���Ҫ����λ�������ν�
���������
����˵����
*********************************************************************************************************/
void Choice_Freq(uint8_t freq_Name)
{
	// �Խ��յ�ָ����н���
	switch(freq_Name)
	{
		case 0x00:
		{
			freq = 5000;
//			Set_Freq(freq); // ���ü���Ƶ��
			FreqIsSet = 1;
			break;
		}
		case 0x01:
		{
			freq = 10000;
//			Set_Freq(freq);
			FreqIsSet = 1;
			break;
		}	
		case 0x02:
		{
			freq = 20000;
//			Set_Freq(freq);
			FreqIsSet = 1;
			break;
		}	
		case 0x03:
		{
			freq = 40000;
//			Set_Freq(freq);
			FreqIsSet = 1;
			break;
		}
		case 0x04:
		{
			freq = 60000;
//			Set_Freq(freq);
			FreqIsSet = 1;
			break;
		}	
		default:
		{
			break;
		}
	}
}

/**********************************************************************************************************
��������Set_Freq
�������ܣ����ü���Ƶ��
�����������õĺ����嵥��
���ñ������ĺ����嵥��Choice_Freq��
���������temp_Fre-Ƶ��ֵ����λHz
�����������
����˵����
*********************************************************************************************************/
//void Set_Freq(uint32_t temp_Fre)
//{
//	Write_frequence(0,temp_Fre);
//	Write_frequence(1,temp_Fre);
//	Write_frequence(2,temp_Fre);
//	Write_frequence(3,temp_Fre);
//}

/**********************************************************************************************************
��������Choice_Gain
�������ܣ�ѡ�����ü���źŵ�����
�����������õĺ����嵥��
���ñ������ĺ����嵥��Recv_Instruction��
���������
���������
����˵����
*********************************************************************************************************/
void Choice_Gain(uint8_t gain_Name)
{
	// �Խ��յ�ָ����н���
	switch (gain_Name)
	{
		case 0x10:
		{
			gain = 1;
			GainIsSet = 1;
			break;
		}
		case 0x11:
		{
			gain = 2;
			GainIsSet = 1;
			break;
		}
		case 0x12:
		{
			gain = 5;
			GainIsSet = 1;
			break;
		}
		case 0x13:
		{
			gain = 10;
			GainIsSet = 1;
		}
	}
}

/************************************************
��������
�������ܣ���AD7607������ֵ��Чת��Ϊ��Ӧ�ĵ�ѹֵ
�����������õĺ����嵥��AD7606_ReadAdc��
���ñ������ĺ����嵥��
���������
���������
����˵����
************************************************/
void Signalto_Voltage()
{
	// ADC�ĵ�7�͵�8��ͨ���ֱ�ɼ���ֵ����λ��Ϣ
	amplitude_Acquisition = AD7606_ReadAdc(6);	
	phase_Acquisition = AD7606_ReadAdc(7);
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) == 0)
	{
		amplitude_Conversion = gain * amplitude_Acquisition * 5000 / 32767;
		phase_Conversion = gain * phase_Acquisition * 5000 / 32767;
	}
	else
	{
		amplitude_Conversion = gain * amplitude_Acquisition * 10000 / 32767;
		phase_Conversion = gain * phase_Acquisition * 10000 / 32767;
	}
		
}


/************************************************
��������Phase_Mean_Filtering
�������ܣ��Բɼ�����λ�����˲�
�����������õĺ����嵥��
���ñ������ĺ����嵥��
���������
���������
����˵����
************************************************/
void Phase_Mean_Filtering()
{
	int16_t i;
	int32_t sum = 0; // �������ݵ��ۼ�
	
	for (i = 0; i < save_Count; i++)
	{
		// AD7606�ɼ����ݲ�����
		AD7606_Scan();
	
		// ��ȡ��Ӧͨ�������ݲ�ת����ʵ�ʵ�ѹֵ
		Signalto_Voltage();
		
		save_PhaseArr[i] = phase_Conversion; // �����ȡ����λ��ѹ
		
		sum += save_PhaseArr[i]; // �����ݽ����ۼ�
	}
	
	presrnt_Phase[select_Channel] = (uint16_t)sum / save_Count; // ��þ�ֵ��ѹ
	
}

/************************************************
��������
�������ܣ����ֵ����У0
�����������õĺ����嵥��
���ñ������ĺ����嵥��AD7606_ReadAdc��
���������
���������
����˵����
************************************************/
void Calibration_Zero()
{
	// �ɼ����ٸ������У0
	int16_t cal_Count = 100;
	
	// cal_Count�����ֵ���ܺ�
	int32_t cal_sum = 0;
	
	int i;
	
	for (i = 0; i < cal_Count; i++)
	{
		// �źŲɼ�
		AD7606_Scan();

		// ��ȡ��Ӧͨ�������ݲ�ת����ʵ�ʵ�ѹֵ
		Signalto_Voltage();
		
		cal_sum += phase_Conversion;
	}
	
	// ���У0ʱ��Ҫ��ȥ����
	calibration_Phase[select_Channel] = (int16_t)(cal_sum / cal_Count);
}


/************************************************
��������System_Reset()
�������ܣ�ϵͳ��λ����
�����������õĺ����嵥��
���ñ������ĺ����嵥��AD7606_ReadAdc��
���������
���������
����˵����
************************************************/
void System_Reset()
{
	/// ������������
	select_Channel = 0; // ��ǰ�����Ͳɼ���ͨ����8��ͨ��(0-7)
	freq = 0; // ���ļ���Ƶ�ʣ���λΪHz
	gain = 0; // �źŷ�������


	/// ���ǰ�������ñ�־λ
	FreqIsSet = 0; // ����Ƶ�����ñ�־λ
	GainIsSet = 0; // �����������ñ�־λ
	ZeroCalIsSet = 0; // ����У׼���ñ�־λ

	// �洢��ֵ����λ�Ĳɼ�ֵ��ת��ֵ
	amplitude_Acquisition = 0; // ��ֵ�Ĳɼ�ֵ
	phase_Acquisition = 0; // ��λ�Ĳɼ�ֵ
	amplitude_Conversion = 0; // ��ֵת�����ֵ
	phase_Conversion = 0; // ��λת�����ֵ
	
	// ���������е�Ȧ��
	turn = 0;
	
	/// �洢��ǰ����һ��������λ��ֵ
	distanceArr[0] = 0;
	distanceArr[1] = 0;
	
	/// �Լ��ֵ����У0
	cal_Num = 0;
	calibrationIsSet = 0;	
	
	b_Snedto_PC = 0;
	
	b_DiapWay = 0;
}

/************************************************
��������Sendto_Usart_1
�������ܣ��򴮿�1��������
�����������õĺ����嵥��USART_SendData��
���ñ������ĺ����嵥��
���������t-ռ1���ֽڵ�16������
�����������
����˵����
************************************************/
void Sendto_Usart_1(unsigned char t)
{
	USART_SendData(USART1, t);         //�򴮿�1��������
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET); // �ȴ����ͽ���
}


/************************************************
��������Send_FullDatato_Pc()
�������ܣ�����һ�����������ݸ���λ��
�����������õĺ����嵥��
���ñ������ĺ����嵥��
���������
���������
����˵����
************************************************/
void Send_FullDatato_Pc()
{	
	// ����֡ͷ
	Sendto_Usart_1(0xAA);
	Sendto_Usart_1(0xBB);	
	

	
	Sendto_Usart_1(presrnt_Phase[0] >> 8);
	Sendto_Usart_1(presrnt_Phase[0]);
	
	Sendto_Usart_1(presrnt_Phase[6] >> 8);
	Sendto_Usart_1(presrnt_Phase[6]);
	
	Sendto_Usart_1(presrnt_Phase[4] >> 8);
	Sendto_Usart_1(presrnt_Phase[4]);
	
	Sendto_Usart_1(presrnt_Phase[2] >> 8);
	Sendto_Usart_1(presrnt_Phase[2]);
	
	Sendto_Usart_1(presrnt_Phase[7] >> 8);
	Sendto_Usart_1(presrnt_Phase[7]);
	
	Sendto_Usart_1(presrnt_Phase[5] >> 8);
	Sendto_Usart_1(presrnt_Phase[5]);
	
	Sendto_Usart_1(presrnt_Phase[3] >> 8);
	Sendto_Usart_1(presrnt_Phase[3]);
	
	Sendto_Usart_1(presrnt_Phase[1] >> 8);
	Sendto_Usart_1(presrnt_Phase[1]);
	
	// ���ͱ�����λ��ֵ
	Sendto_Usart_1(distanceArr[1] >> 8);
	Sendto_Usart_1(distanceArr[1]);
	
	// ����֡β

	Sendto_Usart_1(0xAA);
	Sendto_Usart_1(0xBB);	
}


/************************************************
��������
�������ܣ���ʽ��������ѭ��
�����������õĺ����嵥��
���ñ������ĺ����嵥��AD7606_ReadAdc��
���������
���������
����˵����
************************************************/
void Detection_Cycle()
{
	while (1)
	{
		// ����Ӧͨ�������Ž�������
		
		
		//Select_Channel();
		
		// ǿ���ӳ٣�̫����
		while (delay_us1 > 0)
		{
			delay_us1--;
		}
		
		delay_us1 = 25000;
		
		// �ж��Ƿ��´�ָ��
		
		if(USART_RX_STA&0x8000)
		{
			// �ж��Ƿ��·�У��ָ��
			if (USART_RX_BUF[2] == 0x20)
			{
				// ִ��У0����
				calibrationIsSet = 1;
				
				USART_RX_STA = 0;
			}
			
			// �ж��Ƿ��·���λָ��
			if (USART_RX_BUF[3] == 0x30)
			{
				// ���и�λ����
				System_Reset();
				
				USART_RX_STA = 0;
				// �������ѭ��
				break;
			}
			
			// �ж��Ƿ��·���������ָ��
			if (USART_RX_BUF[4] == 0x40)
			{
				b_Snedto_PC = 1;
			}
			else if (USART_RX_BUF[4] == 0x41)
			{
				b_Snedto_PC = 0;
			}
			
			// �ж��Ƿ��·���ʾ��ʽָ��
			if (USART_RX_BUF[5] == 0x50)
			{
				b_DiapWay = 0;
			}
			else if (USART_RX_BUF[5] == 0x51)
			{
				b_DiapWay = 1;
			}
			
			USART_RX_STA = 0;
		}
		
		/// ���źŽ���У0
		if (calibrationIsSet & 1)
		{
			Calibration_Zero();
			
			// У0����++
			cal_Num++;
			
			// �ж��Ƿ�ÿ��ͨ��������У0
			if (cal_Num == 8)
			{
				// ��8��ͨ����У0���
				calibrationIsSet = 0;
				// У0������0���Է����´�У0
				cal_Num = 0;
			}			
		}
			
		// ����λ�źŽ��о�ֵ�˲�
		Phase_Mean_Filtering();
		
		presrnt_Phase[select_Channel] -= calibration_Phase[select_Channel];
		
		if (presrnt_Phase[select_Channel] < 0)
		{
			presrnt_Phase[select_Channel] = -presrnt_Phase[select_Channel];
		}	
		
//		// ����źŸ���С��3��ֱ��ǿ��Ϊ0
//		if ( presrnt_Phase[select_Channel] <= 3)
//		{
//			presrnt_Phase[select_Channel] = 0;
//		}
		
				
		// �л�����ͨ��
		select_Channel++;
		
		// һ���������л�ͨ�����
		if (select_Channel == 8)
		{
			// ��ȡ��ǰ������λ��ֵ
			
			
			
			
			
			//AD7606_DispDistance();




			
			
			// �жϼ�ⰴť�Ƿ��
			if (b_Snedto_PC == 1)
			{
				// �ж���ʾ��ʽ
				if (b_DiapWay == 0)
				{
					// ��һ�����������ݷ��͸���λ��
					Send_FullDatato_Pc();
				}
				else 
				{
					if (distanceArr[1] != distanceArr[0])
					{
						// ��һ�����������ݷ��͸���λ��
						Send_FullDatato_Pc();
					}
				}
			}
			
			// �ѵ�ǰ��λ��ֵ������һ�ε�ֵ
			distanceArr[0] = distanceArr[1];
			
			// ���ͨ�����´�0��ʼ
			select_Channel = 0;
		}
		
	}
}
