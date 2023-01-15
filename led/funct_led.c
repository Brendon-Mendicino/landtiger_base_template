/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           funct_led.h
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        High level led management functions
** Correlated files:    lib_led.c, funct_led.c
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/

#include "lpc17xx.h"
#include "led.h"
#include "../timer/timer.h"

const unsigned long led_mask[] = {1UL << 0, 1UL << 1, 1UL << 2, 1UL << 3, 1UL << 4, 1UL << 5, 1UL << 6, 1UL << 7};

volatile led_bright_t led_brightness[LED_NUM];

volatile uint32_t bright_selected_led;

extern unsigned char led_value;

/*----------------------------------------------------------------------------
  Function that turns on requested LED
 *----------------------------------------------------------------------------*/
void LED_On(unsigned int num)
{

	LPC_GPIO2->FIOPIN |= led_mask[num];
	led_value = LPC_GPIO2->FIOPIN;
}

void LED_OnAll(void)
{
	int i;
	for (i = 0; i < LED_NUM; i++)
	{
		LED_On(i);
	}
}

void LED_OffAll(void)
{
	int i;
	for (i = 0; i < LED_NUM; i++)
	{
		LED_Off(i);
	}
}

void LED_OnNum(unsigned int num, uint32_t mask)
{
	int i;
	for (i = 0; i < LED_NUM; i++)
	{
		if ((mask & (1 << i)) != 0) {
			continue;
		}

		if (num & ((1) << i))
			LED_On(i);
		else
			LED_Off(i);
	}
}
/*----------------------------------------------------------------------------
  Function that turns off requested LED
 *----------------------------------------------------------------------------*/
void LED_Off(unsigned int num)
{

	LPC_GPIO2->FIOPIN &= ~led_mask[num];
	led_value = LPC_GPIO2->FIOPIN;
}

/*----------------------------------------------------------------------------
  Function that outputs value to LEDs
 *----------------------------------------------------------------------------*/
void LED_Out(unsigned int value)
{
	int i;

	for (i = 0; i < LED_NUM; i++)
	{
		if (value & (1 << i))
		{
			LED_On(i);
		}
		else
		{
			LED_Off(i);
		}
	}
	led_value = LPC_GPIO2->FIOPIN;
}

void led_match0_callable(void)
{
	LED_Off(bright_selected_led);
}

void led_match1_callable(void)
{
	LED_On(bright_selected_led);
}

void set_led_brightness(uint32_t led, uint32_t mr0, uint32_t mr1)
{
	led_brightness[led].match0 = mr0;
	led_brightness[led].match1 = mr1;

	TIMER_set_callable(TIMER1, MATCH0, led_match0_callable);
	TIMER_set_callable(TIMER1, MATCH1, led_match1_callable);

	TIMER_match_reg(TIMER1, MATCH0, CONTROL_INTERRUPT, led_brightness[led].match0, false);
	TIMER_match_reg(TIMER1, MATCH1, CONTROL_INTERRUPT | CONTROL_RESET, led_brightness[led].match1, false);

	TIMER_enable(TIMER1);
}

void set_led_brightness_micro(uint32_t led, uint32_t micro_mr0, uint32_t micro_mr1)
{
	bright_selected_led = led;
	led_brightness[led].match0 = TIMER_CLK / 1000000 * micro_mr0;
	led_brightness[led].match1 = TIMER_CLK / 1000000 * micro_mr1;

	TIMER_set_callable(TIMER1, MATCH0, led_match0_callable);
	TIMER_set_callable(TIMER1, MATCH1, led_match1_callable);

	TIMER_match_reg(TIMER1, MATCH0, CONTROL_INTERRUPT, led_brightness[led].match0, false);
	TIMER_match_reg(TIMER1, MATCH1, CONTROL_INTERRUPT | CONTROL_RESET, led_brightness[led].match1, false);

	TIMER_enable(TIMER1);
}

led_bright_t *get_led_brighness(uint32_t led)
{
	return (led_bright_t *)&led_brightness[led];
}
