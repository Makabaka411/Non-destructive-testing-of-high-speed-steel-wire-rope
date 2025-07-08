 /**
******************************************************************************
* @file    			tcp_demo.c                                                   *
* @author  			WisIOE Software Team                                         *
* @version 			V1.2																												 *	
******************************************************************************
* @company  		��������Ƽ����޹�˾                                         *
* @website  		www.wisioe.com																							 *	 				
* @forum        www.w5500.cn																								 *		
* @qqGroup      383035001																										 * 
******************************************************************************
*/ 

#include "include.h"

uint8 buff[2048];				                              	         /*����һ��2KB�Ļ���*/
uint8 Tx_Buffer[4096];                                           //����һ��8λ�ķ��ͻ�����
//float D[BUFFER_SIZE]={31,41,555,61,2,3,5,6,7,1,6,3,1,4,5,5};
extern int AD7616_ConvertedValue[17];

int i;

/**
*@brief		TCP Server�ػ���ʾ������
*@param		��
*@return	��
*/
void do_tcp_server(void)
{	
	uint16 len=0;  
	switch(getSn_SR(SOCK_TCPS))											            	/*��ȡsocket��״̬*/
	{
		case SOCK_CLOSED:													                  /*socket���ڹر�״̬*/
			socket(SOCK_TCPS ,Sn_MR_TCP,local_port,Sn_MR_ND);	        /*��socket*/
		  break;     
    
		case SOCK_INIT:														                  /*socket�ѳ�ʼ��״̬*/
			listen(SOCK_TCPS);												                /*socket��������*/
		  break;
		
		case SOCK_ESTABLISHED:												              /*socket�������ӽ���״̬*/
		
			if(getSn_IR(SOCK_TCPS) & Sn_IR_CON)
			{
				setSn_IR(SOCK_TCPS, Sn_IR_CON);								          /*��������жϱ�־λ*/
			}
			len=getSn_RX_RSR(SOCK_TCPS);									            /*����lenΪ�ѽ������ݵĳ���*/
			if(len>0)
			{
			recv(SOCK_TCPS,buff,len);								              	/*��������Client������*/
			buff[len]=0x00; 											                  /*����ַ���������*/
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
			
			
		  send(SOCK_TCPS,Tx_Buffer,4+16*2);									              /*��Client��������*/
			
			
		  }
		  break;
		
		case SOCK_CLOSE_WAIT:												                /*socket���ڵȴ��ر�״̬*/
			close(SOCK_TCPS);
		  break;
	}
}

/**
*@brief		TCP Client�ػ���ʾ������
*@param		��
*@return	��
*/
void do_tcp_client(void)
{	
   uint16 len=0;	

	switch(getSn_SR(SOCK_TCPC))								  				         /*��ȡsocket��״̬*/
	{
		case SOCK_CLOSED:											        		         /*socket���ڹر�״̬*/
			socket(SOCK_TCPC,Sn_MR_TCP,local_port++,Sn_MR_ND);
		  break;
		
		case SOCK_INIT:													        	         /*socket���ڳ�ʼ��״̬*/
			connect(SOCK_TCPC,remote_ip,remote_port);                /*socket���ӷ�����*/ 
		  break;
		
		case SOCK_ESTABLISHED: 												             /*socket�������ӽ���״̬*/
			if(getSn_IR(SOCK_TCPC) & Sn_IR_CON)
			{
				setSn_IR(SOCK_TCPC, Sn_IR_CON); 							         /*��������жϱ�־λ*/
			}
		
			len=getSn_RX_RSR(SOCK_TCPC); 								  	         /*����lenΪ�ѽ������ݵĳ���*/
			if(len>0)
			{
				recv(SOCK_TCPC,buff,len); 							   		         /*��������Server������*/
				buff[len]=0x00;  											                 /*����ַ���������*/
				printf("%s\r\n",buff);
				send(SOCK_TCPC,buff,len);								     	         /*��Server��������*/
			}		  
		  break;
			
		case SOCK_CLOSE_WAIT: 											    	         /*socket���ڵȴ��ر�״̬*/
			close(SOCK_TCPC);
		  break;

	}
}







