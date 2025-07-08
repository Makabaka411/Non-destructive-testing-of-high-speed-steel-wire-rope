#include "include.h"

extern uint16_t ADC_ConvertedValue[];
extern uint16_t ADC_ConvertedValueLocal[];

extern uint8 buff[];				                              	         /*����һ��2KB�Ļ���*/
extern uint8 Tx_Buffer[];                                           //����һ��8λ�ķ��ͻ�����
//extern uint8_t timer_interrupt_flag;
extern int s_volt_a[8];
extern int s_volt_b[8];
int AD7616_ConvertedValue[17];
extern int circle_count;
extern int flagEncoder;
int len;


int main(void)
{	
	//ģ���ʼ��	
  LED_Init();
//  u8 count = 0;
	Encoder_Init();        //��������ʼ��

	SystemInit();          //ϵͳʱ�ӳ�ʼ��
	uart_init(115200);     //����1��ʼ��������������Ϊ115200
	delay_init(168);       //��ʱ������ʼ��  84	
  AD7616_Init();          //AD7616��ʼ��

  InitW5500();           //W5500��ʼ��

  printf("INT ok");

  while(1)
 {	
  AD7616_Read_Data();
  AD7616_Mask();
  len = Encoder_Get()*3.1415926*70/1200;
  
  for (int i = 0; i < 8; i++)
  {
    AD7616_ConvertedValue[i] = s_volt_a[i];
  }
  for (int i = 0; i < 8; i++)
  {
    AD7616_ConvertedValue[8+i] = s_volt_b[i];
  }
  AD7616_ConvertedValue[16] = len;


//      if (flagEncoder==1)
//     {
//     
//      for (int i = 0; i < 17 ; i++)
//      {
//        printf("%d,",AD7616_ConvertedValue[i]);
//      }
//      
//      printf("\r\n");

//      //����AD7616�ɼ����
//      flagEncoder=0; // �����־λ
//     
//      }


//      if (flagEncoder==1)
//     {
//      printf("%d,",circle_count);
//      
//      printf("\r\n");
//      //���Ա������������
//      flagEncoder=0; // �����־λ
//     
//      }
  
   
	 if(getSn_SR(SOCK_TCPS) == SOCK_CLOSED)
	 {
		 socket(SOCK_TCPS ,Sn_MR_TCP,local_port,Sn_MR_ND);	        /*��socket*/
	 }
	 else if(getSn_SR(SOCK_TCPS) == SOCK_INIT)
	 {
		 listen(SOCK_TCPS);												                /*socket��������*/
	 }
	 else if(getSn_SR(SOCK_TCPS) == SOCK_ESTABLISHED)
   {
//		  delay_ms(500);  
	 		Tx_Buffer[0]=0xAA;
			Tx_Buffer[1]=0xBB;
	    for (i = 2; i < 2+17*2; i+=2) 
			{
        int index = i / 2 - 1;
        Tx_Buffer[i] =((short int)(AD7616_ConvertedValue[index]))>>8;
				Tx_Buffer[i+1] =(short int)(AD7616_ConvertedValue[index]);
      }
			Tx_Buffer[2+17*2]=0xBB;
			Tx_Buffer[3+17*2]=0xAA;
      if (flagEncoder==1)
     {
//       printf("encoder ok");
       send(SOCK_TCPS,Tx_Buffer,4+17*2);									              /*��Client��������*/
       flagEncoder=0; // �����־λ
     
      }
   }





 }




//		ADC_ConvertedValueLocal[0] =(int)((float) ADC_ConvertedValue[0] / 4096 * 3300);
//		ADC_ConvertedValueLocal[1] =(int)((float) ADC_ConvertedValue[1] / 4096 * 3300);
//		ADC_ConvertedValueLocal[2] =(int)((float) ADC_ConvertedValue[2] / 4096 * 3300);
//		ADC_ConvertedValueLocal[3] =(int)((float) ADC_ConvertedValue[3] / 4096 * 3300);
//		ADC_ConvertedValueLocal[4] =(int)((float) ADC_ConvertedValue[4] / 4096 * 3300);
//		ADC_ConvertedValueLocal[5] =(int)((float) ADC_ConvertedValue[5] / 4096 * 3300);
//		ADC_ConvertedValueLocal[6] =(int)((float) ADC_ConvertedValue[6] / 4096 * 3300);
//		ADC_ConvertedValueLocal[7] =(int)((float) ADC_ConvertedValue[7] / 4096 * 3300);
//		ADC_ConvertedValueLocal[8] =(int)((float) ADC_ConvertedValue[8] / 4096 * 3300);
//		ADC_ConvertedValueLocal[9] =(int)((float) ADC_ConvertedValue[9] / 4096 * 3300);
//		ADC_ConvertedValueLocal[10] =(int)((float) ADC_ConvertedValue[10] / 4096 * 3300);
//		ADC_ConvertedValueLocal[11] =(int)((float) ADC_ConvertedValue[11] / 4096 * 3300);
//		ADC_ConvertedValueLocal[12] =(int)((float) ADC_ConvertedValue[12] / 4096 * 3300);
//		ADC_ConvertedValueLocal[13] =(int)((float) ADC_ConvertedValue[13] / 4096 * 3300);
//		ADC_ConvertedValueLocal[14] =(int)((float) ADC_ConvertedValue[14] / 4096 * 3300);
//		ADC_ConvertedValueLocal[15] =(int)((float) ADC_ConvertedValue[15] / 4096 * 3300);

//		printf("%4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d\r\n",
//    ADC_ConvertedValueLocal[0],ADC_ConvertedValueLocal[1],ADC_ConvertedValueLocal[2],ADC_ConvertedValueLocal[3],
//    ADC_ConvertedValueLocal[4],ADC_ConvertedValueLocal[5],ADC_ConvertedValueLocal[6],ADC_ConvertedValueLocal[7],
//    ADC_ConvertedValueLocal[8],ADC_ConvertedValueLocal[9],ADC_ConvertedValueLocal[10],ADC_ConvertedValueLocal[11],
//    ADC_ConvertedValueLocal[12],ADC_ConvertedValueLocal[13],ADC_ConvertedValueLocal[14],ADC_ConvertedValueLocal[15]);
    //����ADC�ɼ����
    
    
                   
		
//		
//	 Instruction_receiving();   //��λ��ָ����պ���
//	 
//	  if(ClearFlag == 1)
//	   {
//		  ClearFlag = 0;	  
//		  Calibrate();                          //У�㺯��	  
//	   }	  
//	  Select_Channel();                         //ģ�⿪�ؽ���ͨ����ѡ��
//	  Data_Acquisition(select_Channel,10);      //ͨ�����ݲɼ����������Ϊѡ�е�ͨ�����Լ����ٸ����ݽ��о�ֵ�˲���
//	  Feature_Extraction();                     //��ȡ���յĵ�ѹʵ���鲿��ֵ����λ
//	 		   
//	  if(select_Channel >= 31)                  //����ͨ���ɼ��������λ���ϴ�����
//		{
//			Mode_selection(EigenvalueFlag); 
//		}
//			
//	  select_Channel++;                //ͨ���л�
//		
//	  if(select_Channel>=32)    //32
//	   {
//			select_Channel = 16;
//	    }
//	  else
//	   {
//			select_Channel = select_Channel;
//		}
 }
