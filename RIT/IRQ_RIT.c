/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <stdbool.h>
#include <stdint.h>

#include "lpc17xx.h"
#include "RIT.h"
#include "../joystick/joystick.h"



/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void RIT_IRQHandler(void)
{
	callable_t callable;
	
	// If the callback is not null invoke it.
	if ((callable = RIT_get_callable()) != NULL) {
		callable();
	}

	LPC_RIT->RICTRL |= 0x1; /* clear interrupt flag */
	return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
