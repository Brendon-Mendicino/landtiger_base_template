#ifndef BUTTON_H
#define BUTTON_H


#include <stdlib.h>
#include <stdint.h>

#include "../defines/defines.h"


#define INT0		(0)				/* p2.10 */
#define KEY1		(1)   		/* p2.11 */
#define KEY2		(2)				/* p2.12 */


#define MAX_LEN (100)


void BUTTON_init(uint32_t priority);

/* lib_button.c */
void BUTTON_enable_debouncing(uint8_t timer, uint8_t button);
void BUTTON_disable_debouncing(uint8_t timer, uint8_t button);

void BUTTON_set_on_click_listener(uint8_t button, callable_t callable);
callable_t BUTTON_get_on_click_listener(uint8_t button);

	
void EINT0_IRQHandler(void);
void EINT1_IRQHandler(void);
void EINT2_IRQHandler(void);

		
#endif
