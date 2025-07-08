/**
******************************************************************************
* @file    			bsp_spi_flash.c                                              *
* @author  			WisIOE Software Team                                         *
* @version 			V1.2																												 *		
* @date    			2017-11-01																								   *
* @brief 				SPI Flash 应用函数                                           *					
******************************************************************************
* @company  		深圳炜世科技有限公司                                         *
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
  * @brief  使能SPI时钟
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
  * @brief  配置指定SPI的引脚
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
	//PB12->CS,初始化片选输出引脚
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_SetBits(GPIOA,GPIO_Pin_15);
}


/**
  * @brief  根据外部SPI设备配置SPI相关参数
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
  * @brief  写1字节数据到SPI总线
  * @param  TxData 写到总线的数据
  * @retval None
  */
u8 SPI_WriteByte(uint8_t TxData)
{				 
	while((SPI1->SR&SPI_I2S_FLAG_TXE)==0);	//等待发送区空		  
	SPI1->DR=TxData;	 	  									//发送一个byte 
	while((SPI1->SR&SPI_I2S_FLAG_RXNE)==0); //等待接收完一个byte  
	return SPI1->DR;		
}
/**
  * @brief  从SPI总线读取1字节数据
  * @retval 读到的数据
  */
uint8_t SPI_ReadByte(void)
{			 
	while((SPI1->SR&SPI_I2S_FLAG_TXE)==0);	//等待发送区空			  
	SPI1->DR=0xFF;	 	  										//发送一个空数据产生输入数据的时钟 
	while((SPI1->SR&SPI_I2S_FLAG_RXNE)==0); //等待接收完一个byte  
	return SPI1->DR;  						    
}


///**
//*@brief		W5500片选信号设置函数
//*@param		val: 为“0”表示片选端口为低，为“1”表示片选端口为高
//*@return	无
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
//*@brief		设置W5500的片选端口SCSn为低
//*@param		无
//*@return	无
//*/
//void iinchip_csoff(void)
//{
//	wiz_cs(LOW);
//}

///**
//*@brief		设置W5500的片选端口SCSn为高
//*@param		无
//*@return	无
//*/
//void iinchip_cson(void)
//{	
//   wiz_cs(HIGH);
//}
///**
//*@brief		向W5500写入len字节数据
//*@param		addrbsb: 写入数据的地址
//*@param   buf：写入字符串
//*@param   len：字符串长度
//*@return	len：返回字符串长度
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
//*@brief		从W5500读出len字节数据
//*@param		addrbsb: 读取数据的地址
//*@param 	buf：存放读取数据
//*@param		len：字符串长度
//*@return	len：返回字符串长度
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
//*@brief		STM32 SPI1读写8位数据
//*@param		dat：写入的8位数据
//*@return	无
//*/
//uint8  IINCHIP_SpiSendData(uint8 dat)
//{
//   return(SPI_WriteByte(dat));
//}




