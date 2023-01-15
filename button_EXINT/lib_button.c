
#include "button.h"
#include "lpc17xx.h"
#include "../led/led.h"
#include "../timer/timer.h"

callable_t button_callable_table[3] = {NULL};

static uint8_t debounce_timer = 0;

/**
 * @brief  Function that initializes all Buttons
 */
void BUTTON_init(uint32_t priority)
{

	LPC_PINCON->PINSEL4 |= (1 << 20); /* External interrupt 0 pin selection */
	LPC_GPIO2->FIODIR &= ~(1 << 10);  /* PORT2.10 defined as input          */

	LPC_PINCON->PINSEL4 |= (1 << 22); /* External interrupt 0 pin selection */
	LPC_GPIO2->FIODIR &= ~(1 << 11);  /* PORT2.11 defined as input          */
	LPC_PINCON->PINSEL4 |= (1 << 24); /* External interrupt 0 pin selection */
	LPC_GPIO2->FIODIR &= ~(1 << 12);  /* PORT2.12 defined as input          */

	LPC_SC->EXTMODE = 0x7;

	NVIC_EnableIRQ(EINT2_IRQn);				/* enable irq in nvic                 */
	NVIC_SetPriority(EINT2_IRQn, priority); /* priority, the lower the better     */
	NVIC_EnableIRQ(EINT1_IRQn);				/* enable irq in nvic                 */
	NVIC_SetPriority(EINT1_IRQn, priority);
	NVIC_EnableIRQ(EINT0_IRQn);				/* enable irq in nvic                 */
	NVIC_SetPriority(EINT0_IRQn, priority); /* decreasing priority	from EINT2->0	 */
}

void int0_callable(void) 
{
	if ((LPC_GPIO2->FIOPIN & (1 << 10)) != 0) { /* checks if p2.10 is released					*/
		LPC_PINCON->PINSEL4 |= (0x01 << 20);			/* enable p2.10 EINT0 									*/
		TIMER_match_reg(debounce_timer, MATCH0, CONTROL_NULL, 0, false);
	}
}

void key1_callable(void) 
{
	if ((LPC_GPIO2->FIOPIN & (1 << 11)) != 0) { /* checks if p2.11 is released					*/
		LPC_PINCON->PINSEL4 |= (0x01 << 22);			/* enable p2.11 EINT1 									*/
		TIMER_match_reg(debounce_timer, MATCH1, CONTROL_NULL, 0, false);
	}
}

void key2_callable(void) 
{
	if ((LPC_GPIO2->FIOPIN & (1 << 12)) != 0) { /* checks if p2.12 is released					*/
		LPC_PINCON->PINSEL4 |= (0x01 << 24);			/* enable p2.10 EINT2 									*/
		TIMER_match_reg(debounce_timer, MATCH2, CONTROL_NULL, 0, false);
	}
}

/**
 * @brief enables doubouncing on a specific button, considering a timer. Once a timer is used for a button all
 * other button should be set on the same timer.
 * 
 * @param timer timer to set the dobouncing
 * @param button button to do a debouncing on
 */
void BUTTON_enable_debouncing(uint8_t timer, uint8_t button)
{
	uint8_t match;
	callable_t callable;
	uint32_t milliseconds = 50;
	uint32_t time_interval = milliseconds * TIMER_CLK / 1000;

	switch (button) {
		case INT0:
			LPC_PINCON->PINSEL4 &= ~(0x03 << 20);		/* reset p2.10 */
			callable = int0_callable;
			match = MATCH0;
			break;
		case KEY1:
			LPC_PINCON->PINSEL4 &= ~(0x03 << 22); 	/* reset p2.11 */
			callable = key1_callable;
			match = MATCH1;
			break;
		case KEY2:
			LPC_PINCON->PINSEL4 &= ~(0x03 << 24); 	/* reset p2.12 */
			callable = key2_callable;
			match = MATCH2;
			break;
		default:
			// Throw an error
			return;
	}
	
	debounce_timer = timer;
	TIMER_match_reg(timer, match, CONTROL_INTERRUPT, time_interval, true);
	TIMER_set_callable(timer, match, callable);
}


void BUTTON_disable_debouncing(uint8_t timer, uint8_t button)
{
	uint8_t mr;
	switch (button) {
	case INT0:
		mr = MATCH0;
		break;
	case KEY1:
		mr = MATCH1;
		break;
	case KEY2:
		mr = MATCH2;
		break;
	default:
		return;
	}

	TIMER_match_reg(timer, mr, CONTROL_NULL, 0, false);
}



void BUTTON_set_on_click_listener(uint8_t button, callable_t callable)
{
	button_callable_table[button] = callable;
}

callable_t BUTTON_get_on_click_listener(uint8_t button)
{
	return button_callable_table[button];
}
