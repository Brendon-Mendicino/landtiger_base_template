#include "lpc17xx.h"
#include "adc.h"


consumer_t adc_consumer = NULL;

/*----------------------------------------------------------------------------
  Function that initializes ADC
 *----------------------------------------------------------------------------*/
void ADC_init(uint32_t priority)
{
	LPC_PINCON->PINSEL3 |= (3UL << 30); /* P1.31 is AD0.5                     */

	LPC_SC->PCONP |= (1 << 12); /* Enable power to ADC block          */

	LPC_ADC->ADCR = (1 << 5) | /* select AD0.5 pin                   */
					(4 << 8) | /* ADC clock is 25MHz/5               */
					(1 << 21); /* enable ADC                         */

	LPC_ADC->ADINTEN = (1 << 8); /* global enable interrupt            */

	NVIC_EnableIRQ(ADC_IRQn); /* enable ADC Interrupt               */
	NVIC_SetPriority(ADC_IRQn, priority);
}

void DAC_init(void)
{
	// page 117
	LPC_PINCON->PINSEL1 |= (1 << 21);  /* enable AOUT on P0.26 */
	LPC_PINCON->PINSEL1 &= ~(1 << 20); /* enable AOUT on P0.26 */
	LPC_GPIO0->FIODIR |= (1 << 26);	   /* P0.26 defined as input */
}

/**
 * @brief set the output of the DA converter
 * 
 * @param value is at most a 10 bit value
 */
void DAC_set_output(uint16_t value)
{
	// Cut off any bit greater than the 10th.
	// LPC_DAC->DACR = ((uint32_t)value & (~(0) << 10)) << 6;
	LPC_DAC->DACR = (uint32_t)value << 6;
}

void ADC_start_conversion(void)
{
	LPC_ADC->ADCR |= (1 << 24); /* Start A/D Conversion 				*/
}

/**
 * @brief set the consumer of the adc conversion
 * 
 * @param consumer takes a uint16_t paramenter as input
 */
void ADC_set_consumer(consumer_t consumer)
{
	adc_consumer = consumer;
}

consumer_t ADC_get_consumer(void)
{
	return adc_consumer;
}
