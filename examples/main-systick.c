/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/06/06
* Description        : Main program body.
*******************************************************************************/
#include "debug.h"
#include <limits.h>

#define SYSTICK_CTLR_INIT  (1 << 5)
#define SYSTICK_CTLR_MODE  (1 << 4)
#define SYSTICK_CTLR_STRE  (1 << 3)
#define SYSTICK_CTLR_STCLK (1 << 2)
#define SYSTICK_CTLR_STIE  (1 << 1)
#define SYSTICK_CTLR_STE   (1 << 0)

/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Return         : None
*******************************************************************************/
int main(void)
{
	Delay_Init();
	USART_Printf_Init(115200);
	printf("SystemClk:%d\n",SystemCoreClock);
        SysTick->CMP = ULLONG_MAX;
        SysTick->CTLR = SYSTICK_CTLR_INIT | SYSTICK_CTLR_STCLK | SYSTICK_CTLR_STE;

	while(1) {
	  printf("t=%08lx%08lx\n", (unsigned long)((SysTick->CNT) >> 32), (unsigned long)SysTick->CNT);
          for(uint32_t i = 0; i < SystemCoreClock/5; i++) {
          }
        }
}







