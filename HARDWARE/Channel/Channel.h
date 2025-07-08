#ifndef _Channel_H_
#define _Channel_H_

#include "include.h"

void HC4051_Init(void);
void Select_Channel(void);


#define E1_ENABLE 	GPIO_ResetBits(GPIOA,GPIO_Pin_1 )
#define E1_DISABLE 	GPIO_SetBits(GPIOA,GPIO_Pin_1 )

#define E2_ENABLE 	GPIO_ResetBits(GPIOG,GPIO_Pin_11 )
#define E2_DISABLE 	GPIO_SetBits(GPIOG,GPIO_Pin_11 )

#define S10 	PDout(6)
#define S11 	PDout(7)
#define S12 	PEout(5)
#define S13 	PEout(6)

#define S20 	PGout(6)
#define S21 	PGout(7)
#define S22 	PGout(8)
#define S23 	PGout(9)




void CD74HC4067_Init(void);
void Select_Channel(void);
void Mode_selection(char mode); 

extern int16_t select_Channel;

#endif

