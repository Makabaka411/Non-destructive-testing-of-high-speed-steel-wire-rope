 /**
******************************************************************************
* @file    			tcp_demo.c                                                   *
* @author  			WisIOE Software Team                                         *
* @version 			V1.2																												 *	
******************************************************************************
* @company  		深圳炜世科技有限公司                                         *
* @website  		www.wisioe.com																							 *	 				
* @forum        www.w5500.cn																								 *		
* @qqGroup      383035001																										 * 
******************************************************************************
*/ 

#include "include.h"

uint8 buff[2048];				                              	         /*定义一个2KB的缓存*/
uint8 Tx_Buffer[4096];                                           //定义一个8位的发送缓存区
//float D[BUFFER_SIZE]={31,41,555,61,2,3,5,6,7,1,6,3,1,4,5,5};
extern int AD7616_ConvertedValue[17];

int i;

/**
*@brief		TCP Server回环演示函数。
*@param		无
*@return	无
*/
void do_tcp_server(void)
{	
	uint16 len=0;  
	switch(getSn_SR(SOCK_TCPS))											            	/*获取socket的状态*/
	{
		case SOCK_CLOSED:													                  /*socket处于关闭状态*/
			socket(SOCK_TCPS ,Sn_MR_TCP,local_port,Sn_MR_ND);	        /*打开socket*/
		  break;     
    
		case SOCK_INIT:														                  /*socket已初始化状态*/
			listen(SOCK_TCPS);												                /*socket建立监听*/
		  break;
		
		case SOCK_ESTABLISHED:												              /*socket处于连接建立状态*/
		
			if(getSn_IR(SOCK_TCPS) & Sn_IR_CON)
			{
				setSn_IR(SOCK_TCPS, Sn_IR_CON);								          /*清除接收中断标志位*/
			}
			len=getSn_RX_RSR(SOCK_TCPS);									            /*定义len为已接收数据的长度*/
			if(len>0)
			{
			recv(SOCK_TCPS,buff,len);								              	/*接收来自Client的数据*/
			buff[len]=0x00; 											                  /*添加字符串结束符*/
			printf("%s\r\n",buff);
			Tx_Buffer[0]=0xAA;
			Tx_Buffer[1]=0xBB;
	    for (i = 2; i < 2+16*2; i+=2) 
			{
        Tx_Buffer[i] =((short int)(AD7616_ConvertedValue[i/2-1]))>>8;
				Tx_Buffer[i+1] =(short int)(AD7616_ConvertedValue[i/2-1]);
      }
			Tx_Buffer[2+16*2]=0xBB;
			Tx_Buffer[3+16*2]=0xAA;
			
			
		  send(SOCK_TCPS,Tx_Buffer,4+16*2);									              /*向Client发送数据*/
			
			
		  }
		  break;
		
		case SOCK_CLOSE_WAIT:												                /*socket处于等待关闭状态*/
			close(SOCK_TCPS);
		  break;
	}
}

/**
*@brief		TCP Client回环演示函数。
*@param		无
*@return	无
*/
void do_tcp_client(void)
{	
   uint16 len=0;	

	switch(getSn_SR(SOCK_TCPC))								  				         /*获取socket的状态*/
	{
		case SOCK_CLOSED:											        		         /*socket处于关闭状态*/
			socket(SOCK_TCPC,Sn_MR_TCP,local_port++,Sn_MR_ND);
		  break;
		
		case SOCK_INIT:													        	         /*socket处于初始化状态*/
			connect(SOCK_TCPC,remote_ip,remote_port);                /*socket连接服务器*/ 
		  break;
		
		case SOCK_ESTABLISHED: 												             /*socket处于连接建立状态*/
			if(getSn_IR(SOCK_TCPC) & Sn_IR_CON)
			{
				setSn_IR(SOCK_TCPC, Sn_IR_CON); 							         /*清除接收中断标志位*/
			}
		
			len=getSn_RX_RSR(SOCK_TCPC); 								  	         /*定义len为已接收数据的长度*/
			if(len>0)
			{
				recv(SOCK_TCPC,buff,len); 							   		         /*接收来自Server的数据*/
				buff[len]=0x00;  											                 /*添加字符串结束符*/
				printf("%s\r\n",buff);
				send(SOCK_TCPC,buff,len);								     	         /*向Server发送数据*/
			}		  
		  break;
			
		case SOCK_CLOSE_WAIT: 											    	         /*socket处于等待关闭状态*/
			close(SOCK_TCPC);
		  break;

	}
}







