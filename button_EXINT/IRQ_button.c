#include <stdint.h>
#include <stdlib.h>
#include "button.h"
#include "lpc17xx.h"

#include "../led/led.h"
#include "../timer/timer.h"

#define DEBOUNCE_TIMER (TIMER0)

void EINT0_IRQHandler(void) /* INT0														 */
{
	callable_t callable;
	BUTTON_enable_debouncing(DEBOUNCE_TIMER, INT0);

	if ((callable = BUTTON_get_on_click_listener(INT0)) != NULL)
	{
		callable();
	}

	LPC_SC->EXTINT &= (1 << 0); /* clear pending interrupt         */
}

void EINT1_IRQHandler(void) /* KEY1														 */
{
	callable_t callable;
	BUTTON_enable_debouncing(DEBOUNCE_TIMER, KEY1);

	if ((callable = BUTTON_get_on_click_listener(KEY1)) != NULL)
	{
		callable();
	}

	LPC_SC->EXTINT &= (1 << 1); /* clear pending interrupt         */
}

void EINT2_IRQHandler(void) /* KEY2														 */
{
	callable_t callable;
	BUTTON_enable_debouncing(DEBOUNCE_TIMER, KEY2);

	if ((callable = BUTTON_get_on_click_listener(KEY2)) != NULL)
	{
		callable();
	}

	LPC_SC->EXTINT &= (1 << 2); /* clear pending interrupt         */
}
