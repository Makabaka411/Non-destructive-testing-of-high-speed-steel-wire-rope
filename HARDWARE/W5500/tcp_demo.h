#ifndef __TCP_DEMO_H
#define __TCP_DEMO_H
#include "types.h"
#include "include.h"


#define BUFFER_SIZE    16


extern uint8 buff[2048];	
extern uint8 Tx_Buffer[4096];
extern float D[BUFFER_SIZE];
extern int AD7616_ConvertedValue[17];
extern int i;
void do_tcp_server(void);//TCP Server回环演示函数
void do_tcp_client(void);//TCP Clinet回环演示函数

	
#endif 

