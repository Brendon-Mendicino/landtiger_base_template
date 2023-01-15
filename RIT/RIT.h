/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           RIT.h
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        Prototypes of functions included in the lib_RIT, funct_RIT, IRQ_RIT .c files
** Correlated files:    lib_RIT.c, funct_RIT.c, IRQ_RIT.c
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#ifndef __RIT_H
#define __RIT_H

#include <stdint.h>
#include <stdlib.h>

#include "../defines/defines.h"

extern uint32_t RIT_init( uint32_t RITInterval, uint32_t priority );

extern void RIT_enable( void );

extern void RIT_disable( void );

extern void RIT_reset( void );

extern void RIT_set_callable(callable_t callable);

extern callable_t RIT_get_callable(void);

extern void RIT_IRQHandler (void);

#endif /* end __RIT_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
