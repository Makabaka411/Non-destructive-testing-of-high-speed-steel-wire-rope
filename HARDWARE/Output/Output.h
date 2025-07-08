#ifndef _Output_H_
#define _Output_H_


#include "include.h"


extern float OutData[4];
unsigned short CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT);
void OutPut_Data(void); 

#endif


