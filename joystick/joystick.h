/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           joystick.h
** Last modified Date:  2018-12-30
** Last Version:        V1.00
** Descriptions:        Prototypes of functions included in the lib_joystick, funct_joystick .c files
** Correlated files:    lib_joystick.c, funct_joystick.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#ifndef JOYSTICK_H
#define JOYSTICK_H


#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../defines/defines.h"

#define DIRECTIONS    (5)

#define J_SEL           (0)
#define J_UP            (1)
#define J_DOWN          (2)
#define J_RIGHT         (3)
#define J_LEFT          (4)


typedef struct joystick_enab_t {
	bool sel_enab    :1;
	bool sel_runned  :1;
	bool down_enab   :1;
	bool down_runned :1;
	bool left_enab   :1;
	bool left_runned :1;
	bool right_enab  :1;
	bool right_runned:1;
	bool up_enab     :1;
	bool up_runned   :1;
} joystick_enab_t;



/* lib_joystick */

void JOY_init(bool single_press);

void JOY_run_directions(void);

void JOY_set_callable(uint32_t direction, callable_t callable);

callable_t JOY_get_callable(uint32_t direction);


#endif
