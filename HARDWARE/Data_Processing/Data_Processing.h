#ifndef _Data_Processing_H_
#define _Data_Processing_H_

#include "include.h"

#define PI 3.14159265


extern float R_Calibrate[32];       //校零实部电压初始值存放
extern float I_Calibrate[32];       //校零虚部电压初始值存放
extern float R_Average[32];         //存放多次ADC采集后平均的电压实部信号值
extern float I_Average[32];         //存放多次ADC采集后平均的电压虚部信号值
extern float Amplitude[32];         //各通道的阻抗电压幅值
extern float Phase[32];             //各通道的阻抗电压相位
extern float R[32];                 //存放ADC采集的电压实部信号值
extern float I[32];
extern char ClearFlag;              //校零标志位
extern char EigenvalueFlag;         //上传特征值选择标志位

void Calibrate(void);
void Data_Acquisition(int16_t channel,int16_t time);
void Amplitude_Calculation(float R1,float I1);
void Phase_Calculation(float R1,float I1,float R2,float I2);
void Feature_Extraction(void);
void Instruction_receiving(void);



#endif

