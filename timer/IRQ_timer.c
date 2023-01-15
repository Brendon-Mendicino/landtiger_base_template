/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "timer.h"
#include "../led/led.h"



void run_mr(uint8_t timer, uint8_t match, volatile uint32_t *MR, volatile uint32_t *TC)
{
	callable_t callable;

	*MR += TIMER_get_match_reg_update_val(timer, match);

	if  ((callable = TIMER_get_callable(timer, match)) != NULL) {
		callable();
	}

	// In case the callback exceded the time
	if (*MR < *TC) {
		*MR = *TC + 20;
	}
}



/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER0_IRQHandler (void)
{
	LPC_TIM_TypeDef *LPC_TIM = LPC_TIM0;
	uint8_t TIMER = TIMER0;
	
	/* Match register 0 interrupt service routine */
	if (LPC_TIM->IR & 01)
	{
		run_mr(TIMER, MATCH0, &LPC_TIM->MR0, &LPC_TIM->TC);
		
		LPC_TIM->IR = 1;			/* clear interrupt flag */
	}
	/* Match register 1 interrupt service routine */
	else if(LPC_TIM->IR & 02)
	{
		run_mr(TIMER, MATCH1, &LPC_TIM->MR1, &LPC_TIM->TC);
		
		LPC_TIM->IR =  2 ;			/* clear interrupt flag */	
	}
	/* Match register 2 interrupt service routine */
	else if(LPC_TIM->IR & 4)
	{
		run_mr(TIMER, MATCH2, &LPC_TIM->MR2, &LPC_TIM->TC);
		
		LPC_TIM->IR =  4 ;			/* clear interrupt flag */	
	}
		/* Match register 3 interrupt service routine */
	else if(LPC_TIM->IR & 8)
	{
		run_mr(TIMER, MATCH3, &LPC_TIM->MR3, &LPC_TIM->TC);
	 
		LPC_TIM->IR =  8 ;			/* clear interrupt flag */	
	}
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{
	LPC_TIM_TypeDef *LPC_TIM = LPC_TIM1;
	uint8_t TIMER = TIMER1;
	
	/* Match register 0 interrupt service routine */
	if (LPC_TIM->IR & 01)
	{
		run_mr(TIMER, MATCH0, &LPC_TIM->MR0, &LPC_TIM->TC);
		
		LPC_TIM->IR = 1;			/* clear interrupt flag */
	}
		/* Match register 1 interrupt service routine */
	else if(LPC_TIM->IR & 02)
	{
		run_mr(TIMER, MATCH1, &LPC_TIM->MR1, &LPC_TIM->TC);
		
		LPC_TIM->IR =  2 ;			/* clear interrupt flag */	
	}
	/* Match register 2 interrupt service routine */
	else if(LPC_TIM->IR & 4)
	{
		run_mr(TIMER, MATCH2, &LPC_TIM->MR2, &LPC_TIM->TC);
		
		LPC_TIM->IR =  4 ;			/* clear interrupt flag */	
	}
		/* Match register 3 interrupt service routine */
	else if(LPC_TIM->IR & 8)
	{
		run_mr(TIMER, MATCH3, &LPC_TIM->MR3, &LPC_TIM->TC);
	 
		LPC_TIM->IR =  8 ;			/* clear interrupt flag */	
	}
}

/******************************************************************************
** Function name:		Timer2_IRQHandler
**
** Descriptions:		Timer/Counter 2 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER2_IRQHandler (void)
{
	LPC_TIM_TypeDef *LPC_TIM = LPC_TIM2;
	uint8_t TIMER = TIMER2;
	
	/* Match register 0 interrupt service routine */
	if (LPC_TIM->IR & 01)
	{
		run_mr(TIMER, MATCH0, &LPC_TIM->MR0, &LPC_TIM->TC);
		
		LPC_TIM->IR = 1;			/* clear interrupt flag */
	}
		/* Match register 1 interrupt service routine */
	else if(LPC_TIM->IR & 02)
	{
		run_mr(TIMER, MATCH1, &LPC_TIM->MR1, &LPC_TIM->TC);
		
		LPC_TIM->IR =  2 ;			/* clear interrupt flag */	
	}
	/* Match register 2 interrupt service routine */
	else if(LPC_TIM->IR & 4)
	{
		run_mr(TIMER, MATCH2, &LPC_TIM->MR2, &LPC_TIM->TC);
		
		LPC_TIM->IR =  4 ;			/* clear interrupt flag */	
	}
		/* Match register 3 interrupt service routine */
	else if(LPC_TIM->IR & 8)
	{
		run_mr(TIMER, MATCH3, &LPC_TIM->MR3, &LPC_TIM->TC);
	 
		LPC_TIM->IR =  8 ;			/* clear interrupt flag */	
	}
}


void TIMER3_IRQHandler (void)
{
	LPC_TIM_TypeDef *LPC_TIM = LPC_TIM3;
	uint8_t TIMER = TIMER3;
	
	/* Match register 0 interrupt service routine */
	if (LPC_TIM->IR & 01)
	{
		run_mr(TIMER, MATCH0, &LPC_TIM->MR0, &LPC_TIM->TC);
		
		LPC_TIM->IR = 1;			/* clear interrupt flag */
	}
		/* Match register 1 interrupt service routine */
	else if(LPC_TIM->IR & 02)
	{
		run_mr(TIMER, MATCH1, &LPC_TIM->MR1, &LPC_TIM->TC);
		
		LPC_TIM->IR =  2 ;			/* clear interrupt flag */	
	}
	/* Match register 2 interrupt service routine */
	else if(LPC_TIM->IR & 4)
	{
		run_mr(TIMER, MATCH2, &LPC_TIM->MR2, &LPC_TIM->TC);
		
		LPC_TIM->IR =  4 ;			/* clear interrupt flag */	
	}
		/* Match register 3 interrupt service routine */
	else if(LPC_TIM->IR & 8)
	{
		run_mr(TIMER, MATCH3, &LPC_TIM->MR3, &LPC_TIM->TC);
	 
		LPC_TIM->IR =  8 ;			/* clear interrupt flag */	
	}
}



/******************************************************************************
**                            End Of File
******************************************************************************/
