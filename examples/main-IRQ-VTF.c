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
  VTF IRQ interrupt routine:
   This example is used to demonstrate VTF IRQ
*/
#include "debug.h"

/* Global define */


/* Global Variable */ 
uint32_t time=0;

// 11 cycles = VTF + hardware stack interrupt (bugs!)
// 14 cycles = hardware stack interrupt (bugs!)
// 14 cycles = VTF + hardware stack interrupt workaround
// 16 cycles = hardware stack interrupt workaround
// 46 cycles = VTF + software stack interrupt
// 48 cycles = software stack interrupt
#define USE_HARDWARE_STACK_INTERRUPT 0
#define USE_VTF_INTERRUPT 1

#if USE_HARDWARE_STACK_INTERRUPT == 1
void SysTick_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
#elif USE_HARDWARE_STACK_INTERRUPT == 2
void SysTick_Handler(void) __attribute__((naked));
#else
void SysTick_Handler(void) __attribute__((interrupt()));
#endif


/*********************************************************************
 * @fn      Interrupt_VTF_Init
 *
 * @brief   Initializes VTF.
 *
 * @return  none
 */
void Interrupt_VTF_Init(void)
{
    NVIC_EnableIRQ(SysTicK_IRQn);
#if USE_VTF_INTERRUPT == 1 
    SetVTFIRQ((u32)SysTick_Handler,SysTicK_IRQn,0,ENABLE);
#endif
}

/*********************************************************************
 * @fn      Systick_Init
 *
 * @brief   Initializes Systick.
 *
 * @return  none
 */
void Systick_Init(void)
{
    SysTick->SR=0;
    SysTick->CNT=0;
    SysTick->CMP=0x20;
    SysTick->CTLR=0x7;
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
	USART_Printf_Init(115200);
	SystemCoreClockUpdate();
	printf("SystemClk:%d\r\n",SystemCoreClock);
	printf("Interrupt VTF Test\r\n");

	Interrupt_VTF_Init();
	Systick_Init();
    while(1)
   {

   }
}

#if USE_HARDWARE_STACK_INTERRUPT == 2
void SysTick_Handler() {
  __asm volatile ("call SysTick_Handler_real; mret");
}
#endif

/*********************************************************************
 * @fn      SysTick_Handler
 *
 * @brief   This function handles SysTick exception.
 *
 * @return  none
 */
#if USE_HARDWARE_STACK_INTERRUPT == 2
__attribute__ ((used)) void SysTick_Handler_real(void)
#else
void SysTick_Handler(void)
#endif
{
    time=SysTick->CNT;
    SysTick->CTLR=0;
    SysTick->SR=0;
    printf("delta time:%d\r\n",time-0x20);
}


