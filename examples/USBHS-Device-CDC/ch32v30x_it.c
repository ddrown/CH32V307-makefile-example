/********************************** (C) COPYRIGHT *******************************
* File Name          : ch32v30x_it.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/06/06
* Description        : Main Interrupt Service Routines.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/
#include "ch32v30x_it.h"
#include "UART.h"

void TIM2_IRQHandler( )__attribute__((naked));

void TIM2_IRQHandler() {
    __asm volatile ("call TIM2_IRQHandler_real; mret");
}

/*********************************************************************
 * @fn      TIM2_IRQHandler
 *
 * @brief   This function handles TIM2 exception.
 *
 * @return  none
 */
__attribute__((used)) void TIM2_IRQHandler_real( void )
{
    /* Test IO */
    static uint8_t tog;
    tog ? (GPIOA->BSHR = GPIO_Pin_15):(GPIOA->BCR = GPIO_Pin_15);
    tog ^= 1;
    /* uart timeout counts */
    Uart.Rx_TimeOut++;
    Uart.USB_Up_TimeOut++;

    /* clear status */
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}
