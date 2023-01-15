#ifndef ADC_H
#define ADC_H

#include <stdint.h>
#include <stdlib.h>

#include "../defines/defines.h"

#define MAX_ADGDR_VALUE     (0xFFF)

void ADC_init (uint32_t priority);
void ADC_start_conversion (void);

void DAC_init(void);

void DAC_set_output(uint16_t value);

void ADC_set_consumer(consumer_t consumer);

consumer_t ADC_get_consumer(void);

void ADC_IRQHandler(void);

#endif
