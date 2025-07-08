#include "include.h"


float OutData[4] = { 0 };




	 //虚拟示波器测试代码
//	  OutData[0] = I[0];
//	  OutData[1] = I[1];
//	  OutData[2] = I[3];
//	  OutData[3] = I[4];
//	  OutPut_Data();






unsigned short CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT)
{
    unsigned short CRC_Temp;
    unsigned char i,j;
    CRC_Temp = 0xffff;

  for (i=0;i<CRC_CNT; i++)
  {
        CRC_Temp ^= Buf[i];        //每位取反
        for (j=0;j<8;j++)
        {
            if (CRC_Temp & 0x01)
                CRC_Temp = (CRC_Temp >>1 ) ^ 0xa001;
            else
                CRC_Temp = CRC_Temp >> 1;
        }
    }
    return(CRC_Temp);
}





void OutPut_Data(void)
{
	  int temp[4] = {0};
	  unsigned int temp1[4] = {0};
	  unsigned char databuf[10] = {0};
	  unsigned char i;
	  unsigned short CRC16 = 0;
	  for(i=0;i<4;i++)
	   {

	    temp[i]  = (int)OutData[i];  //OutData为发送的数据
	    temp1[i] = (unsigned int)temp[i];

	   }

	  for(i=0;i<4;i++)
	  {
	    databuf[i*2]   = (unsigned char)(temp1[i]%256);
	    databuf[i*2+1] = (unsigned char)(temp1[i]/256);
	  }

	  CRC16 = CRC_CHECK(databuf,8);
	  databuf[8] = CRC16%256;
	  databuf[9] = CRC16/256;

	  for(i=0;i<10;i++)
	  {
	    USART_SendData(USART1, databuf[i]);
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET); // 等待发送结束
	  }


}
