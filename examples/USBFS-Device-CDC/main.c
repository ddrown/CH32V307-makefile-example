/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/06/06
* Description        : Main program body.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/

/*
 *@Note
 *Example routine to emulate a simulate USB-CDC Device, USE USART2(PA2/PA3);
 *Please note: This code uses the default serial port 1 for debugging,
 *if you need to modify the debugging serial port, please do not use USART2
*/

#include "UART.h"
#include "debug.h"

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
	SystemCoreClockUpdate( );
	Delay_Init( );
	USART_Printf_Init( 115200 );
		
	printf( "SystemClk:%d\r\n",SystemCoreClock );
	printf( "Simulate USB-CDC Device running on USBFS Controller\r\n" );

	RCC_Configuration( );
	
	/* Tim2 init */
	TIM2_Init( );

	/* Usart2 init */
	UART2_Init( 1, DEF_UARTx_BAUDRATE, DEF_UARTx_STOPBIT, DEF_UARTx_PARITY );

	/* USB20 device init */
	USBFS_RCC_Init( );
	USBFS_Device_Init( ENABLE );

  uint16_t last_tim2 = 0;
	uint16_t print_tim2 = 0;
	while(1)
	{
		if(last_tim2 != TIM2->CNT) {
			Uart.Rx_TimeOut++;
			Uart.USB_Up_TimeOut++;
			last_tim2 = TIM2->CNT;
		}

		UART2_DataRx_Deal( );
		UART2_DataTx_Deal( );

		if((uint16_t)(TIM2->CNT - print_tim2) > 10000) {
			USB_Print_stats();
			print_tim2 = TIM2->CNT;
		}
	}
}
