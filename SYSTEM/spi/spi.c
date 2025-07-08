/**
******************************************************************************
* @file    			bsp_spi_flash.c                                              *
* @author  			WisIOE Software Team                                         *
* @version 			V1.2																												 *		
* @date    			2017-11-01																								   *
* @brief 				SPI Flash Ӧ�ú���                                           *					
******************************************************************************
* @company  		��������Ƽ����޹�˾                                         *
* @website  		www.wisioe.com																							 *	 				
* @forum        www.w5500.cn																								 *		
* @qqGroup      383035001																										 * 
******************************************************************************
*/
#include "spi.h"
#include "stdio.h"
#include "types.h"


#define Dummy_Byte  0xFF
/*******************************************************************************
* Function Name  : SPI_FLASH_Init                                              *
* Description    : Initializes the peripherals used by the SPI FLASH driver.   *
* Input          : None                                                        *
* Output         : None                                                        *
* Return         : None                                                        *
********************************************************************************/




/**
  * @brief  ʹ��SPIʱ��
  * @retval None
  */
static void SPI_RCC_Configuration(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7,  GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
}

/**
  * @brief  ����ָ��SPI������
  * @retval None
  */
static void SPI_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	//PB3->SCK,PB4->MISO,PB5->MOSI		 					 
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_DOWN;  	
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	//PB12->CS,��ʼ��Ƭѡ�������
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_SetBits(GPIOA,GPIO_Pin_15);
}


/**
  * @brief  �����ⲿSPI�豸����SPI��ز���
  * @retval None
  */

void SPI_Configuration(void)
{
	SPI_InitTypeDef SPI_InitStruct;
	SPI_RCC_Configuration();
	SPI_GPIO_Configuration();
	
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	SPI_InitStruct.SPI_Direction= SPI_Direction_2Lines_FullDuplex;
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStruct.SPI_CRCPolynomial = 7;
	SPI_Init(SPI1,&SPI_InitStruct);
	
	SPI_Cmd(SPI1, ENABLE);
}


/**
  * @brief  д1�ֽ����ݵ�SPI����
  * @param  TxData д�����ߵ�����
  * @retval None
  */
u8 SPI_WriteByte(uint8_t TxData)
{				 
	while((SPI1->SR&SPI_I2S_FLAG_TXE)==0);	//�ȴ���������		  
	SPI1->DR=TxData;	 	  									//����һ��byte 
	while((SPI1->SR&SPI_I2S_FLAG_RXNE)==0); //�ȴ�������һ��byte  
	return SPI1->DR;		
}
/**
  * @brief  ��SPI���߶�ȡ1�ֽ�����
  * @retval ����������
  */
uint8_t SPI_ReadByte(void)
{			 
	while((SPI1->SR&SPI_I2S_FLAG_TXE)==0);	//�ȴ���������			  
	SPI1->DR=0xFF;	 	  										//����һ�������ݲ����������ݵ�ʱ�� 
	while((SPI1->SR&SPI_I2S_FLAG_RXNE)==0); //�ȴ�������һ��byte  
	return SPI1->DR;  						    
}


///**
//*@brief		W5500Ƭѡ�ź����ú���
//*@param		val: Ϊ��0����ʾƬѡ�˿�Ϊ�ͣ�Ϊ��1����ʾƬѡ�˿�Ϊ��
//*@return	��
//*/
//void wiz_cs(uint8_t val)
//{
//		if (val == LOW) 
//		{
//			GPIO_ResetBits(GPIOA, GPIO_Pin_15); 
//		}
//		else if (val == HIGH)
//		{
//			GPIO_SetBits(GPIOA, GPIO_Pin_15); 
//		}
//	
//}


///**
//*@brief		����W5500��Ƭѡ�˿�SCSnΪ��
//*@param		��
//*@return	��
//*/
//void iinchip_csoff(void)
//{
//	wiz_cs(LOW);
//}

///**
//*@brief		����W5500��Ƭѡ�˿�SCSnΪ��
//*@param		��
//*@return	��
//*/
//void iinchip_cson(void)
//{	
//   wiz_cs(HIGH);
//}
///**
//*@brief		��W5500д��len�ֽ�����
//*@param		addrbsb: д�����ݵĵ�ַ
//*@param   buf��д���ַ���
//*@param   len���ַ�������
//*@return	len�������ַ�������
//*/
//u16 wiz_write_buf(u32 addrbsb,u8* buf,u16 len)
//{
//   u16 idx = 0;
//   if(len == 0) 
//		 printf("Unexpected2 length 0\r\n");
//   iinchip_csoff();                               
//   SPI_WriteByte( (addrbsb & 0x00FF0000)>>16);
//   SPI_WriteByte( (addrbsb & 0x0000FF00)>> 8);
//   SPI_WriteByte( (addrbsb & 0x000000F8) + 4); 
//   for(idx = 0; idx < len; idx++)
//   {
//     SPI_WriteByte(buf[idx]);
//   }
//   iinchip_cson();                           
//   return len;  
//}

///**
//*@brief		��W5500����len�ֽ�����
//*@param		addrbsb: ��ȡ���ݵĵ�ַ
//*@param 	buf����Ŷ�ȡ����
//*@param		len���ַ�������
//*@return	len�������ַ�������
//*/
//u16 wiz_read_buf(u32 addrbsb, u8* buf,u16 len)
//{
//  u16 idx = 0;
//  if(len == 0)
//  {
//    printf("Unexpected2 length 0\r\n");
//  }
//  iinchip_csoff();                                
//  SPI_WriteByte( (addrbsb & 0x00FF0000)>>16);
//  SPI_WriteByte( (addrbsb & 0x0000FF00)>> 8);
//  SPI_WriteByte( (addrbsb & 0x000000F8));    
//  for(idx = 0; idx < len; idx++)                   
//  {
//    buf[idx] = SPI_WriteByte(0x00);
//  }
//  iinchip_cson();                                  
//  return len;
//}

///**
//*@brief		STM32 SPI1��д8λ����
//*@param		dat��д���8λ����
//*@return	��
//*/
//uint8  IINCHIP_SpiSendData(uint8 dat)
//{
//   return(SPI_WriteByte(dat));
//}




