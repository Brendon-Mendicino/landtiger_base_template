/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           lib_timer.h
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        atomic functions to be used by higher sw levels
** Correlated files:    lib_timer.c, funct_timer.c, IRQ_timer.c
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <stdlib.h>

#include "lpc17xx.h"
#include "timer.h"




// Defines a structure to hold the callable for every
// combination of (timer, matchReg)
callable_t callableTable[TIMER_TOT][MATCH_TOT] = {
	{NULL}
};

// Defines the mathReg initial values, in case of an interrupt and there are no plans on
// resetting the timer, the values can be updated
uint32_t match_reg_update_val[TIMER_TOT][MATCH_TOT] = {
	{0}
};

// Contains the enabled timers
bool enabled_timers[TIMER_TOT] = {false};



/**
 * @brief intializes the timer and enables the interrupt with the priority
 * 
 * @param timer_num timer id
 * @param Prescaler timer prescaler
 * @return uint32_t return 0 if the timer was intialized, 1 if failed
 */
uint32_t TIMER_init ( uint8_t timer_num, uint32_t priority, uint32_t Prescaler )
{
	if ( timer_num == TIMER0 ) {
		LPC_TIM0->PR = Prescaler;

		NVIC_EnableIRQ(TIMER0_IRQn);
		NVIC_SetPriority(TIMER0_IRQn, priority);		/* more priority than buttons */
		return (0);
	}
	else if ( timer_num == TIMER1 ) {
		LPC_TIM1->PR = Prescaler;

		NVIC_EnableIRQ(TIMER1_IRQn);
		NVIC_SetPriority(TIMER1_IRQn, priority);		/* more priority than buttons */
		return (0);
	}
	else if ( timer_num == TIMER2 ) {
		LPC_TIM2->PR = Prescaler;
		
		NVIC_EnableIRQ(TIMER2_IRQn);
		NVIC_SetPriority(TIMER2_IRQn, priority);		/* more priority than buttons */
		return (0);
	}
	else if ( timer_num == TIMER3 ) {
		LPC_TIM3->PR = Prescaler;

		NVIC_EnableIRQ(TIMER3_IRQn);
		NVIC_SetPriority(TIMER3_IRQn, priority);		/* more priority than buttons */
		return (0);
	}
	return (1);
}

/**
 * @brief enable the timer (heardware), remember to activate the interrupt
 * 
 * @param timer_num timer to enable
 */
void TIMER_enable( uint8_t timer_num )
{
	enabled_timers[timer_num] = true;
	
	if ( timer_num == 0 )
	{
		LPC_TIM0->TCR = 1;
	}
	else if(timer_num == 1)
	{
		LPC_TIM1->TCR = 1;
	}
	else if(timer_num == 2)
	{
		LPC_TIM2->TCR = 1;
	}	
	else if (timer_num == TIMER3)
	{
		LPC_TIM3->TCR = 1;
	}
  return;
}


/**
 * @brief disabels respective timer (hardware)
 * 
 * @param timer_num 
 */
void TIMER_disable( uint8_t timer_num )
{
	enabled_timers[timer_num] = false;
	
	if ( timer_num == 0 )
	{
		LPC_TIM0->TCR = 0;
	}
	else if(timer_num == 1)
	{
		LPC_TIM1->TCR = 0;
	}
	else if(timer_num == 2)
	{
		LPC_TIM2->TCR = 0;
	}
	else if (timer_num == TIMER3)
	{
		LPC_TIM3->TCR = 0;
	}
  return;
}

/**
 * @brief reset the timer, the timer remains reset until an enable function is called on it.
 * 
 * @param timer_num timer to reset
 */
void TIMER_reset( uint8_t timer_num )
{
	uint32_t regVal;

	if ( timer_num == 0 )
	{
		regVal = LPC_TIM0->TCR;
		regVal |= 0x02;
		LPC_TIM0->TCR = regVal;
	}
	else if (timer_num == 1)
	{
		regVal = LPC_TIM1->TCR;
		regVal |= 0x02;
		LPC_TIM1->TCR = regVal;
	}
	else if (timer_num == 2)
	{
		regVal = LPC_TIM2->TCR;
		regVal |= 0x02;
		LPC_TIM2->TCR = regVal;
	}
	else if (timer_num == 3)
	{
		regVal = LPC_TIM3->TCR;
		regVal |= 0x02;
		LPC_TIM3->TCR = regVal;
	}
	return;
}

/**
 * @brief set the parameters of a match register
 *
 * @param timer_num match register timer
 * @param MatchReg match register
 * @param SRImatchReg match register staus, configurable using the CONTROL_* macros
 * @param TimerInterval match register value, every "value" that the timer clock reaches an interrupt is thrown
 * @param add_TC when initializing the TimerInterval, add the current value of the TC and keep adding the initial value to the MR
 */
void TIMER_match_reg(uint8_t timer_num, uint8_t MatchReg, uint8_t SRImatchReg, uint32_t TimerInterval, bool add_TC)
{
	LPC_TIM_TypeDef *TIM;
	volatile uint32_t *MR;
	uint32_t shift_val;

	switch (timer_num)
	{
	case TIMER0:
		TIM = LPC_TIM0;
		break;
	case TIMER1:
		TIM = LPC_TIM1;
		break;
	case TIMER2:
		TIM = LPC_TIM2;
		break;
	case TIMER3:
		TIM = LPC_TIM3;
		break;
	default:
		return;
	}

	switch (MatchReg)
	{
	case MATCH0:
		MR = &(TIM->MR0);
		shift_val = 3 * 0;
		break;
	case MATCH1:
		MR = &TIM->MR1;
		shift_val = 3 * 1;
		break;
	case MATCH2:
		MR = &TIM->MR2;
		shift_val = 3 * 2;
		break;
	case MATCH3:
		MR = &TIM->MR3;
		shift_val = 3 * 3;
		break;
	default:
		return;
	}

	match_reg_update_val[timer_num][MatchReg] = (add_TC) ? TimerInterval : 0;
	*MR = ((add_TC) ? TIM->TC : 0) + TimerInterval; /* set the timeInterval summed to the current TimerCounter 	*/
	TIM->MCR &= ~(0x7 << shift_val);				/* reset the MCR flags */
	TIM->MCR |= SRImatchReg << shift_val;			/* set the SRI flags of the current match register					*/
}

/**
 * @brief same as TIMER_match_reg but, allows to enter millis instead of the real value
 * 
 * @param timer 
 * @param match_reg 
 * @param SRI_match_reg 
 * @param millis 
 * @param add_TC 
 */
void TIMER_match_reg_millis(uint8_t timer, uint8_t match_reg, uint8_t SRI_match_reg, uint32_t millis, bool add_TC)
{
	uint32_t time_interval = millis * (TIMER_CLK / 1000);
	TIMER_match_reg(timer, match_reg, SRI_match_reg, time_interval, add_TC);
}


void TIMER_set_callable(uint8_t timer, uint8_t matchReg, callable_t callable)
{
	callableTable[timer][matchReg] = callable;
}

callable_t TIMER_get_callable(uint8_t timer, uint8_t matchReg)
{
	return callableTable[timer][matchReg];
}

uint32_t TIMER_get_match_reg_update_val(uint8_t timer, uint8_t matchReg)
{
	return match_reg_update_val[timer][matchReg];
}


/******************************************************************************
**                            End Of File
******************************************************************************/
