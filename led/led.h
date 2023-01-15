																			 /*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           timer.h
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        Prototypes of functions included in the lib_led, funct_led .c files
** Correlated files:    lib_led.c, funct_led.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#ifndef LED_H
#define LED_H


#include <stdint.h>
#include <stdbool.h>

#include "../defines/defines.h"


#define LED_NUM     8                   /* Number of user LEDs                */

typedef struct {
	uint32_t match0;
	uint32_t match1;
} led_bright_t;


/* lib_led */

void LED_init(void);
void LED_deinit(void);

/* funct_led */

void LED_On (unsigned int num);
void LED_Off (unsigned int num);
void LED_Out(unsigned int value);
void LED_OnAll(void);
void LED_OffAll(void);
void LED_OnNum(unsigned int num, uint32_t mask);


void set_led_brightness(uint32_t led, uint32_t mr0, uint32_t mr1);
void set_led_brightness_micro(uint32_t led, uint32_t micro_mr0, uint32_t micro_mr1);
led_bright_t *get_led_brighness(uint32_t led);




#endif
