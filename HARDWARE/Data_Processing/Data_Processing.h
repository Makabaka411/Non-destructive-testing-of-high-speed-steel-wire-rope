#ifndef _Data_Processing_H_
#define _Data_Processing_H_

#include "include.h"

#define PI 3.14159265


extern float R_Calibrate[32];       //У��ʵ����ѹ��ʼֵ���
extern float I_Calibrate[32];       //У���鲿��ѹ��ʼֵ���
extern float R_Average[32];         //��Ŷ��ADC�ɼ���ƽ���ĵ�ѹʵ���ź�ֵ
extern float I_Average[32];         //��Ŷ��ADC�ɼ���ƽ���ĵ�ѹ�鲿�ź�ֵ
extern float Amplitude[32];         //��ͨ�����迹��ѹ��ֵ
extern float Phase[32];             //��ͨ�����迹��ѹ��λ
extern float R[32];                 //���ADC�ɼ��ĵ�ѹʵ���ź�ֵ
extern float I[32];
extern char ClearFlag;              //У���־λ
extern char EigenvalueFlag;         //�ϴ�����ֵѡ���־λ

void Calibrate(void);
void Data_Acquisition(int16_t channel,int16_t time);
void Amplitude_Calculation(float R1,float I1);
void Phase_Calculation(float R1,float I1,float R2,float I2);
void Feature_Extraction(void);
void Instruction_receiving(void);



#endif

