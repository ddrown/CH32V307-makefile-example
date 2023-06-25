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
   Random number generator routine:
  Generate a 32-bit random number and print it through the serial port (PA9).

*/

#include "debug.h"
#include "ch32v30x_rng.h"

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    u32 random = 0;

    SystemCoreClockUpdate();
    USART_Printf_Init(115200);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_RNG, ENABLE);
    RNG_Cmd(ENABLE);

    while(1)
    {
        while(RNG_GetFlagStatus(RNG_FLAG_DRDY)==RESET) { }
        random=RNG_GetRandomNumber();
        printf("%c%c%c%c",(random>>24) & 0xff, (random>>16) & 0xff, (random>>8) & 0xff, random & 0xff);
    }
}

