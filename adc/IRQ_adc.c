/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_adc.c
** Last modified Date:  20184-12-30
** Last Version:        V1.00
** Descriptions:        functions to manage A/D interrupts
** Correlated files:    adc.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/

#include "lpc17xx.h"
#include "adc.h"
#include "../led/led.h"
#include "../timer/timer.h"

uint16_t AD_current;
uint16_t AD_last = 0xFF; /* Last converted value               */


/**
 * @brief A/D IRQ: Executed when A/D Conversion is ready (signal from ADC peripheral)
 *
 */
void ADC_IRQHandler(void)
{
	consumer_t consumer;

	AD_current = ((LPC_ADC->ADGDR >> 4) & 0xFFF); /* Read Conversion Result             */
	if (AD_current != AD_last)
	{
		if ((consumer = ADC_get_consumer()) != NULL) {
			consumer((void *)AD_current);
		}
		

		AD_last = AD_current;
	}
}
