/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           joystick.h
** Last modified Date:  2018-12-30
** Last Version:        V1.00
** Descriptions:        Atomic joystick init functions
** Correlated files:    lib_joystick.c, funct_joystick.c
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/

#include "lpc17xx.h"
#include "joystick.h"


bool single_press = false;

callable_t callable_table[DIRECTIONS] = {NULL};

/**
 * @brief Initialized joystick
 * 
 * @param single_press if true and the button is kept pressed the callback will run only once,
 * if false the callback will run until the button gets lifted.
 */
void JOY_init(bool l_single_press)
{
	/* SELECT functionality */
	LPC_PINCON->PINSEL3 &= ~(3 << 18); // PIN mode GPIO (00b value per P1.25)
	LPC_GPIO1->FIODIR &= ~(1 << 25);   // P1.25 Input (joysticks on PORT1 defined as Input)

	/* J_DOWN functionality */
	LPC_PINCON->PINSEL3 &= ~(3 << 20); // PIN mode GPIO (00b value per P1.26)
	LPC_GPIO1->FIODIR &= ~(1 << 26);   // P1.26 Input (joysticks on PORT1 defined as Input)

	/* LEFT functionality */
	LPC_PINCON->PINSEL0 &= ~(0x3 << 22); // P1.27 mode GPIO
	LPC_GPIO1->FIODIR &= ~(1 << 27);	 // P1.27 Input

	/* RIGHT functionality */
	LPC_PINCON->PINSEL3 &= ~(0x3 << 24); // P1.28 mode GPIO
	LPC_GPIO1->FIODIR &= ~(1 << 28);	 // P1.28 Input

	/* J_UP functionality */
	LPC_PINCON->PINSEL3 &= ~(0x3 << 26); // P1.29 mode GPIO
	LPC_GPIO1->FIODIR &= ~(1 << 29);	 // P1.29 Input

	single_press = l_single_press;
}

/**
 * @brief check if the button of the joystick is pressed
 * and also act as a debouncer.
 * 
 * @param j_state 
 */
void check_for_joystick_pressed(joystick_enab_t *j_state) 
{
	uint32_t FIOPIN = LPC_GPIO1->FIOPIN;
	
	/* joystick pressed */
	j_state->sel_enab   = (FIOPIN & (1 << 25)) == 0 ? true : false; 
	j_state->down_enab  = (FIOPIN & (1 << 26)) == 0 ? true : false;
	j_state->left_enab  = (FIOPIN & (1 << 27)) == 0 ? true : false;
	j_state->right_enab = (FIOPIN & (1 << 28)) == 0 ? true : false;
	j_state->up_enab    = (FIOPIN & (1 << 29)) == 0 ? true : false;

	/* single push control */
	j_state->sel_runned   = (j_state->sel_enab   == false && j_state->sel_runned   == true) ? false : j_state->sel_runned   ; 
	j_state->down_runned  = (j_state->down_enab  == false && j_state->down_runned  == true) ? false : j_state->down_runned  ;
	j_state->left_runned  = (j_state->left_enab  == false && j_state->left_runned  == true) ? false : j_state->left_runned  ;
	j_state->right_runned = (j_state->right_enab == false && j_state->right_runned == true) ? false : j_state->right_runned ;
	j_state->up_runned    = (j_state->up_enab    == false && j_state->up_runned    == true) ? false : j_state->up_runned    ;
}


/**
 * @brief Check if a direction has to run a "callable" and if it doues runs it.
 * Works best if used in a timer loop.
 * 
 */
void JOY_run_directions(void)
{
	static joystick_enab_t j_state = {
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false
	};

	callable_t callable;

	check_for_joystick_pressed(&j_state);

	/* SELECT */
	if (j_state.sel_enab && (!j_state.sel_runned || !single_press))
	{
		j_state.sel_runned = true;

		if ((callable = JOY_get_callable(J_SEL)) != NULL) {
			callable();
		}
	}

	/* LEFT */
	if (j_state.left_enab && (!j_state.left_runned || !single_press))
	{
		j_state.left_runned = true;

		if ((callable = JOY_get_callable(J_LEFT)) != NULL) {
			callable();
		}
	}

	/* RIGHT */
	if (j_state.right_enab && (!j_state.right_runned || !single_press))
	{
		j_state.right_runned = true;

		if ((callable = JOY_get_callable(J_RIGHT)) != NULL) {
			callable();
		}
	}

	/* J_DOWN */
	if (j_state.down_enab && (!j_state.sel_runned || !single_press))
	{
		j_state.sel_runned = true;

		if ((callable = JOY_get_callable(J_DOWN)) != NULL) {
			callable();
		}
	}

	/* J_UP */
	if (j_state.up_enab && (!j_state.up_runned || !single_press))
	{
		j_state.up_runned = true;

		if ((callable = JOY_get_callable(J_UP)) != NULL) {
			callable();
		}
	}
}

void JOY_set_callable(uint32_t direction, callable_t callable)
{
	callable_table[direction] = callable;
}

callable_t JOY_get_callable(uint32_t direction)
{
	return callable_table[direction];
}
