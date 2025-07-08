#include "include.h"

int16_t select_Channel = 0; // 当前激励和采集的通道，8个通道(0-7)

void CD74HC4067_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE |  RCC_AHB1Periph_GPIOG, ENABLE);//使能时钟

	//模拟开关1使能端初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;                                         
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;           
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;       
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;             
  GPIO_Init(GPIOA, &GPIO_InitStructure);                   
	
	//模拟开关1配置端口端初始化    S10-PD6    S11-PD7    S12-PE5    S13-PE6
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;                                            
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;           
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;       
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;             
  GPIO_Init(GPIOD, &GPIO_InitStructure);                   
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;                                     
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	
	//模拟开关1配置端口端初始化    E2-PG11   S20-PG6    S21-PG7    S22-PG8    S23-PG9	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_11 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;                                      
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
		
}




//void Select_Channel(void)
//{
//	// 判断给哪个通道激励和采集

//		
//		if(select_Channel <=15)
//		{
//			E1_ENABLE;
//			E2_DISABLE;
//			switch(select_Channel)
//			{					
//				case 0:
//				{				
//					S10 = 0;
//					S11 = 0;
//					S12 = 0;
//					S13 = 0;
//					break;				
//				}
//				case 1:
//				{				
//					S10 = 1;
//					S11 = 0;
//					S12 = 0;
//					S13 = 0;	
//					break;				
//				}
//				case 2:
//				{				
//					S10 = 0;
//					S11 = 1;
//					S12 = 0;
//					S13 = 0;	
//					break;				
//				}
//				case 3:
//				{				
//					S10 = 1;
//					S11 = 1;
//					S12 = 0;
//					S13 = 0;
//					break;				
//				}
//				case 4:
//				{				
//					S10 = 0;
//					S11 = 0;
//					S12 = 1;
//					S13 = 0;
//					break;				
//				}
//				case 5:
//				{				
//					S10 = 1;
//					S11 = 0;
//					S12 = 1;
//					S13 = 0;
//					break;				
//				}
//				case 6:
//				{				
//					S10 = 0;
//					S11 = 1;
//					S12 = 1;
//					S13 = 0;	
//					break;				
//				}
//				case 7:
//				{				
//					S10 = 1;
//					S11 = 1;
//					S12 = 1;
//					S13 = 0;
//					break;				
//				}
//				case 8:
//				{				
//					S10 = 0;
//					S11 = 0;
//					S12 = 0;
//					S13 = 1;
//					break;				
//				}
//				case 9:
//				{				
//					S10 = 1;
//					S11 = 0;
//					S12 = 0;
//					S13 = 1;
//					break;				
//				}
//				case 10:
//				{				
//					S10 = 0;
//					S11 = 1;
//					S12 = 0;
//					S13 = 1;	
//					break;				
//				}
//				case 11:
//				{				
//					S10 = 1;
//					S11 = 1;
//					S12 = 0;
//					S13 = 1;
//					break;				
//				}
//				case 12:
//				{				
//					S10 = 0;
//					S11 = 0;
//					S12 = 1;
//					S13 = 1;
//					break;				
//				}
//				case 13:
//				{				
//					S10 = 1;
//					S11 = 0;
//					S12 = 1;
//					S13 = 1;	
//					break;				
//				}
//				case 14:
//				{				
//					S10 = 0;
//					S11 = 1;
//					S12 = 1;
//					S13 = 1;
//					break;				
//				}
//				case 15:
//				{				
//					S10 = 1;
//					S11 = 1;
//					S12 = 1;
//					S13 = 1;
//					break;				
//				}
//				default:
//				{
//					break;
//				}
//			}	
//		}		
//		else
//		{
//			E2_ENABLE;
//			E1_DISABLE;
//			switch(select_Channel)
//			 {
//				case 16:
//				{				
//					S20 = 0;
//					S21 = 0;
//					S22 = 0;
//					S23 = 0;
//					break;				
//				}
//				case 17:
//				{				
//					S20 = 1;
//					S21 = 0;
//					S22 = 0;
//					S23 = 0;
//					break;				
//				}
//				case 18:
//				{				
//					S20 = 0;
//					S21 = 1;
//					S22 = 0;
//					S23 = 0;
//					break;				
//				}
//				case 19:
//				{				
//					S20 = 1;
//					S21 = 1;
//					S22 = 0;
//					S23 = 0;	
//					break;				
//				}
//				case 20:
//				{				
//					S20 = 0;
//					S21 = 0;
//					S22 = 1;
//					S23 = 0;	
//					break;				
//				}
//				case 21:
//				{				
//					S20 = 1;
//					S21 = 0;
//					S22 = 1;
//					S23 = 0;	
//					break;				
//				}
//				case 22:
//				{				
//					S20 = 0;
//					S21 = 1;
//					S22 = 1;
//					S23 = 0;
//					break;				
//				}
//				case 23:
//				{				
//					S20 = 1;
//					S21 = 1;
//					S22 = 1;
//					S23 = 0;	
//					break;				
//				}
//				case 24:
//				{				
//					S20 = 0;
//					S21 = 0;
//					S22 = 0;
//					S23 = 1;	
//					break;				
//				}
//				case 25:
//				{				
//					S20 = 1;
//					S21 = 0;
//					S22 = 0;
//					S23 = 1;	
//					break;				
//				}
//				case 26:
//				{				
//					S20 = 0;
//					S21 = 1;
//					S22 = 0;
//					S23 = 1;	
//					break;				
//				}
//				case 27:
//				{				
//					S20 = 1;
//					S21 = 1;
//					S22 = 0;
//					S23 = 1;
//					break;				
//				}
//				case 28:
//				{				
//					S20 = 0;
//					S21 = 0;
//					S22 = 1;
//					S23 = 1;
//					break;				
//				}
//				case 29:
//				{				
//					S20 = 1;
//					S21 = 0;
//					S22 = 1;
//					S23 = 1;
//					break;				
//				}
//				case 30:
//				{				
//					S20 = 0;
//					S21 = 1;
//					S22 = 1;
//					S23 = 1;
//					break;				
//				}
//				case 31:
//				{				
//					S20 = 1;
//					S21 = 1;
//					S22 = 1;
//					S23 = 1;
//					break;				
//				}
//			  default:
//				{
//					break;
//				}
//			}
//		}

//					
//}




void Select_Channel(void)
{
	// 判断给哪个通道激励和采集

		
		if(select_Channel <=15)
		{
			E1_ENABLE;
			E2_DISABLE;
			switch(select_Channel)
			{					
				case 0:
				{				
					S10 = 1;
					S11 = 0;
					S12 = 0;
					S13 = 0;
					break;				
				}
				case 1:
				{				
					S10 = 0;
					S11 = 0;
					S12 = 0;
					S13 = 0;	
					break;				
				}
				case 2:
				{				
					S10 = 1;
					S11 = 1;
					S12 = 0;
					S13 = 0;	
					break;				
				}
				case 3:
				{				
					S10 = 0;
					S11 = 1;
					S12 = 0;
					S13 = 0;
					break;				
				}
				case 4:
				{				
					S10 = 1;
					S11 = 0;
					S12 = 1;
					S13 = 0;
					break;				
				}
				case 5:
				{				
					S10 = 0;
					S11 = 0;
					S12 = 1;
					S13 = 0;
					break;				
				}
				case 6:
				{				
					S10 = 1;
					S11 = 1;
					S12 = 1;
					S13 = 0;	
					break;				
				}
				case 7:
				{				
					S10 = 0;
					S11 = 1;
					S12 = 1;
					S13 = 0;
					break;				
				}
				case 8:
				{				
					S10 = 1;
					S11 = 0;
					S12 = 0;
					S13 = 1;
					break;				
				}
				case 9:
				{				
					S10 = 0;
					S11 = 0;
					S12 = 0;
					S13 = 1;
					break;				
				}
				case 10:
				{				
					S10 = 1;
					S11 = 1;
					S12 = 0;
					S13 = 1;	
					break;				
				}
				case 11:
				{				
					S10 = 0;
					S11 = 1;
					S12 = 0;
					S13 = 1;
					break;				
				}
				case 12:
				{				
					S10 = 1;
					S11 = 0;
					S12 = 1;
					S13 = 1;
					break;				
				}
				case 13:
				{				
					S10 = 0;
					S11 = 0;
					S12 = 1;
					S13 = 1;	
					break;				
				}
				case 14:
				{				
					S10 = 1;
					S11 = 1;
					S12 = 1;
					S13 = 1;
					break;				
				}
				case 15:
				{				
					S10 = 0;
					S11 = 1;
					S12 = 1;
					S13 = 1;
					break;				
				}
				default:
				{
					break;
				}
			}	
		}		
		else
		{
			E2_ENABLE;
			E1_DISABLE;
			switch(select_Channel)
			 {
				case 16:
				{				
					S20 = 1;
					S21 = 0;
					S22 = 0;
					S23 = 0;
					break;				
				}
				case 17:
				{				
					S20 = 0;
					S21 = 0;
					S22 = 0;
					S23 = 0;
					break;				
				}
				case 18:
				{				
					S20 = 1;
					S21 = 1;
					S22 = 0;
					S23 = 0;
					break;				
				}
				case 19:
				{				
					S20 = 0;
					S21 = 1;
					S22 = 0;
					S23 = 0;	
					break;				
				}
				case 20:
				{				
					S20 = 1;
					S21 = 0;
					S22 = 1;
					S23 = 0;	
					break;				
				}
				case 21:
				{				
					S20 = 0;
					S21 = 0;
					S22 = 1;
					S23 = 0;	
					break;				
				}
				case 22:
				{				
					S20 = 1;
					S21 = 1;
					S22 = 1;
					S23 = 0;
					break;				
				}
				case 23:
				{				
					S20 = 0;
					S21 = 1;
					S22 = 1;
					S23 = 0;	
					break;				
				}
				case 24:
				{				
					S20 = 1;
					S21 = 0;
					S22 = 0;
					S23 = 1;	
					break;				
				}
				case 25:
				{				
					S20 = 0;
					S21 = 0;
					S22 = 0;
					S23 = 1;	
					break;				
				}
				case 26:
				{				
					S20 = 1;
					S21 = 1;
					S22 = 0;
					S23 = 1;	
					break;				
				}
				case 27:
				{				
					S20 = 0;
					S21 = 1;
					S22 = 0;
					S23 = 1;
					break;				
				}
				case 28:
				{				
					S20 = 1;
					S21 = 0;
					S22 = 1;
					S23 = 1;
					break;				
				}
				case 29:
				{				
					S20 = 0;
					S21 = 0;
					S22 = 1;
					S23 = 1;
					break;				
				}
				case 30:
				{				
					S20 = 1;
					S21 = 1;
					S22 = 1;
					S23 = 1;
					break;				
				}
				case 31:
				{				
					S20 = 0;
					S21 = 1;
					S22 = 1;
					S23 = 1;
					break;				
				}
			  default:
				{
					break;
				}
			}
		}

					
}






void Mode_selection(char mode) 
{
	 switch (mode)
			{
			case 1:
				printf("$%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d;",
				(int)(I[31]),(int)(I[16]),(int)(I[30]),(int)(I[17]),(int)(I[29]),(int)(I[19]),(int)(I[28]),(int)(I[19]),
				(int)(I[27]),(int)(I[20]),(int)(I[26]),(int)(I[21]),(int)(I[25]),(int)(I[22]),(int)(I[24]),(int)(I[23]));			  
				break;
			case 2:
        printf("$%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d;",
				(int)(R[31]),(int)(R[16]),(int)(R[30]),(int)(R[17]),(int)(R[29]),(int)(R[18]),(int)(R[28]),(int)(R[19]),
				(int)(R[27]),(int)(R[20]),(int)(R[26]),(int)(R[21]),(int)(R[25]),(int)(R[22]),(int)(R[24]),(int)(R[23]));
                 break;					
			case 3:
				printf("$%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d;",
				(int)(Amplitude[31]),(int)(Amplitude[16]),(int)(Amplitude[30]),(int)(Amplitude[17]),(int)(Amplitude[29]),(int)(Amplitude[18]),(int)(Amplitude[28]),(int)(Amplitude[19]),
				(int)(Amplitude[27]),(int)(Amplitude[20]),(int)(Amplitude[26]),(int)(Amplitude[21]),(int)(Amplitude[25]),(int)(Amplitude[22]),(int)(Amplitude[24]),(int)(Amplitude[23]));
//				printf("$%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d;",
//				(int)(Amplitude[30]),(int)(Amplitude[1]),(int)(Amplitude[31]),(int)(Amplitude[0]),(int)(Amplitude[28]),(int)(Amplitude[3]),(int)(Amplitude[29]),(int)(Amplitude[2]),
//				(int)(Amplitude[26]),(int)(Amplitude[5]),(int)(Amplitude[27]),(int)(Amplitude[4]),(int)(Amplitude[24]),(int)(Amplitude[7]),(int)(Amplitude[25]),(int)(Amplitude[6]),
//				(int)(Amplitude[22]),(int)(Amplitude[9]),(int)(Amplitude[23]),(int)(Amplitude[8]),(int)(Amplitude[20]),(int)(Amplitude[11]),(int)(Amplitude[21]),(int)(Amplitude[10]),
//				(int)(Amplitude[18]),(int)(Amplitude[13]),(int)(Amplitude[19]),(int)(Amplitude[12]),(int)(Amplitude[16]),(int)(Amplitude[15]),(int)(Amplitude[17]),(int)(Amplitude[14]));		  
			    break;
			case 4:
				printf("$%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d;",
				(int)(Phase[31]),(int)(Phase[16]),(int)(Phase[30]),(int)(Phase[17]),(int)(Phase[29]),(int)(Phase[18]),(int)(Phase[28]),(int)(Phase[19]),
				(int)(Phase[27]),(int)(Phase[20]),(int)(Phase[26]),(int)(Phase[21]),(int)(Phase[25]),(int)(Phase[22]),(int)(Phase[24]),(int)(Phase[23]));
//				printf("$%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d;",
//				(int)(Phase[30]),(int)(Phase[1]),(int)(Phase[31]),(int)(Phase[0]),(int)(Phase[28]),(int)(Phase[3]),(int)(Phase[29]),(int)(Phase[2]),
//				(int)(Phase[26]),(int)(Phase[5]),(int)(Phase[27]),(int)(Phase[4]),(int)(Phase[24]),(int)(Phase[7]),(int)(Phase[25]),(int)(Phase[6]),
//				(int)(Phase[22]),(int)(Phase[9]),(int)(Phase[23]),(int)(Phase[8]),(int)(Phase[20]),(int)(Phase[11]),(int)(Phase[21]),(int)(Phase[10]),
//				(int)(Phase[18]),(int)(Phase[13]),(int)(Phase[19]),(int)(Phase[12]),(int)(Phase[16]),(int)(Phase[15]),(int)(Phase[17]),(int)(Phase[14]));			  
			    break;
			default:
//                printf("$%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d;",
//				(int)(I[31]),(int)(I[0]),(int)(I[30]),(int)(I[1]),(int)(I[29]),(int)(I[2]),(int)(I[28]),(int)(I[3]),
//				(int)(I[27]),(int)(I[4]),(int)(I[26]),(int)(I[5]),(int)(I[25]),(int)(I[6]),(int)(I[24]),(int)(I[7]),
//				(int)(I[23]),(int)(I[8]),(int)(I[22]),(int)(I[9]),(int)(I[21]),(int)(I[10]),(int)(I[20]),(int)(I[11]),
//				(int)(I[19]),(int)(I[12]),(int)(I[18]),(int)(I[13]),(int)(I[17]),(int)(I[14]),(int)(I[16]),(int)(I[15]));	
//			    printf("$%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d;",
//		    	(int)(I[30]),(int)(I[31]),(int)(I[28]),(int)(I[29]),(int)(I[26]),(int)(I[27]),(int)(I[24]),(int)(I[25]),
//			    (int)(I[22]),(int)(I[23]),(int)(I[20]),(int)(I[21]),(int)(I[18]),(int)(I[19]),(int)(I[16]),(int)(I[17]));
			    printf("$%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d;",
		    	(int)(I[31]),(int)(I[30]),(int)(I[29]),(int)(I[28]),(int)(I[27]),(int)(I[26]),(int)(I[25]),(int)(I[24]),
			    (int)(I[23]),(int)(I[22]),(int)(I[21]),(int)(I[20]),(int)(I[19]),(int)(I[18]),(int)(I[17]),(int)(I[16]));
			    break;			  
			}
}
