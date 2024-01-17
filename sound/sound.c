#include "sound.h"
#include <math.h>

#define S_C (523)
#define S_B (494)
#define S_A (440)
#define S_G (392)
#define S_F (349)
#define S_E (330)
#define S_D (294)
#define S_C2 (262)

#define S_E1 (S_E * 2)


#define S_TIMER (TIMER1)
#define S_MATCH (MATCH0)

#define SIN_VAL (45)

#define BASE_TIME (TIMER_CLK / 2)
#define BASE_SIN_TIME (TIMER_CLK / SIN_VAL)

const uint16_t sin_wave[MAX_VOLUME][SIN_VAL] = {
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{100, 113, 127, 140, 152, 164, 174, 182, 189, 195, 198, 199, 199, 197, 192, 186, 178, 169, 158, 146, 134, 120, 106, 93, 79, 65, 53, 41, 30, 21, 13, 7, 2, 0, 0, 1, 4, 10, 17, 25, 35, 47, 59, 72, 86},
{370, 421, 471, 520, 566, 607, 644, 676, 702, 721, 734, 739, 737, 729, 713, 690, 661, 627, 587, 543, 496, 446, 395, 344, 293, 243, 196, 152, 112, 78, 49, 26, 10, 2, 0, 5, 18, 37, 63, 95, 132, 173, 219, 268, 318},
{500, 637, 703, 764, 821, 871, 914, 949, 975, 992, 999, 997, 985, 963, 933, 894, 847, 793, 734, 671, 603, 534, 465, 396, 328, 265, 206, 152, 105, 66, 36, 14, 2, 0, 7, 24, 50, 85, 128, 178, 235, 296, 362, 430},
};


/********************/
/* SONGS */

#define DEATH_LEN (14)
#define CLICK_LEN (1)
#define EATING_LEN (6)
#define CUDDLES_LEN (19)

note_t death[DEATH_LEN] = {
	{S_E1, 0},
	{S_C,  2},
	{S_A,  2},
	{S_C2, 0},
	{S_C,  2},
	{S_A,  2},
	{S_C2, 0},
	{S_B,  0},
	{S_C,  1},
	{S_D,  1},
	{S_E1, 1},
	{S_C,  1},
	{S_A,  1},
	{S_A,  0},
};

note_t click[CLICK_LEN] = {
	{S_A, 3},
};

note_t eating[EATING_LEN] = {
	{S_C,  1},
	{S_A,  2},
	{S_C,  1},
	{S_B,  1},
	{S_F,  2},
	{S_D,  2},
};

// Tetris song
note_t cuddles[CUDDLES_LEN] = {
	{S_E1, 0},
	{S_B,  1},
	{S_C,  1},
	{S_D,  0},
	{S_C,  1},
	{S_B,  1},
	{S_A,  1},
	{S_A,  1},
	{S_C,  1},
	{S_E1, 0},
	{S_D,  1},
	{S_C,  1},
	{S_B,  0},
	{S_C,  1},
	{S_D,  1},
	{S_E1, 1},
	{S_C,  1},
	{S_A,  1},
	{S_A,  0},
};


/* SONGS */
/*******************/


/*******************/
/* STATE VARIABLES */ 

uint32_t sound_volume = 0;
uint32_t sin_time = 0;
uint32_t curr_note = 0;
uint32_t curr_exec = 0;
note_t *song = NULL;
uint32_t song_len = 0;

/* STATE VARIABLES */ 
/*******************/



void song_call(void)
{
	if (sin_time >= SIN_VAL)
	{
		sin_time = 0;
	}

	// A full note "0" has to last 0.5 seconds
	if (curr_exec >= (song[curr_note].note >> song[curr_note].freq) * SIN_VAL / 2 / DIV_SCALE)
	{
		curr_exec = 0;
		curr_note++;
		
		if (curr_note == song_len)
		{
			curr_note = 0;
			TIMER_disable(S_TIMER);
			TIMER_reset(S_TIMER);
		}
		
		TIMER_match_reg(
			S_TIMER,
			S_MATCH,
			CONTROL_INTERRUPT | CONTROL_RESET,
			div(BASE_SIN_TIME, song[curr_note].note).quot,
			false
		);
	}
	
	curr_exec++;

	DAC_set_output(sin_wave[sound_volume][sin_time++]);
}

void setup_new_song(note_t *_song, uint32_t _song_len)
{
	TIMER_reset(S_TIMER);
	sin_time = 0;
	curr_note = 0;
	curr_exec = 0;
	song = _song;
	song_len = _song_len;
	TIMER_match_reg(S_TIMER, S_MATCH, CONTROL_INTERRUPT | CONTROL_RESET, div(BASE_SIN_TIME, song[0].note).quot, false);
	TIMER_set_callable(S_TIMER, S_MATCH, song_call);
	TIMER_enable(S_TIMER);
}





void SOUND_set_volume(uint32_t volume)
{
	sound_volume = volume;
}

uint32_t SOUND_get_volume(void)
{
	return sound_volume;
}

void SOUND_death(void)
{
	setup_new_song(death, DEATH_LEN);
}

void SOUND_click(void)
{
	setup_new_song(click, CLICK_LEN);
}

void SOUND_eating(void)
{
	setup_new_song(eating, EATING_LEN);
}

void SOUND_cuddles(void)
{
	setup_new_song(cuddles, CUDDLES_LEN);
}
