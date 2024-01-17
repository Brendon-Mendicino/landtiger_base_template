#ifndef SOUND_H
#define SOUND_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../defines/defines.h"
#include "../adc/adc.h" 
#include "../timer/timer.h"
#include "../adc/adc.h"

#define MAX_VOLUME   (4)


typedef struct note_t {
    uint16_t note;
    uint16_t freq;
} note_t;



void SOUND_set_volume(uint32_t volume);

uint32_t SOUND_get_volume(void);

void SOUND_death(void);

void SOUND_click(void);

void SOUND_eating(void);

void SOUND_cuddles(void);



#endif
