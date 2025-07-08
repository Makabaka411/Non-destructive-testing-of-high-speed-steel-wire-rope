#ifndef _Upper_Computer_H_
#define _Upper_Computer_H_

#include "include.h"

extern void Recv_Instruction(void);
void Set_Freq(uint32_t temp_Fre);
void Choice_Gain(uint8_t gain_Name);
void Detection_Cycle(void);

extern int16_t select_Channel;


#endif
