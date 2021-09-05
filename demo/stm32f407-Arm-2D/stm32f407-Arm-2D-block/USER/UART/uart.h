#ifndef __USART1_H
#define __USART1_H
#include "stdio.h"	
#include "common.h" 

//////////////////////////////////////////////////////////////////////////////////	 

#define USART1_REC_NUM  			255  	//�����������ֽ��� 200
extern u8 uart_byte_count;          //uart_byte_countҪС��USART_REC_LEN
extern u8 receive_str[USART1_REC_NUM];  

extern UART_HandleTypeDef UART1_Handler; //UART���
#define RXBUFFERSIZE   1 //�����С
extern u8 aRxBuffer[RXBUFFERSIZE];//HAL��USART����Buffer
extern u8 UART1_reciveStr[USART1_REC_NUM];    
extern u8 UART1_reciveOk;

void uart1_sendStr(char *data);
void uart1_init(u32 bound);
void uart1SendChars(u8 *str, u16 strlen);

#endif


