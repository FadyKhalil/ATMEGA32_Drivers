/*
 * Gie.c
 *
 *  Created on: May 1, 2022
 *      Author: fady
 */



#include "../../Service/UTILITIES/Std_types.h"
#include "avr/io.h"
#include "Gie.h"

void Gie_vidEnable(void)
{
	// Enable the General Interrupt
	SREG |= (1 << 7);

}

void Gie_vidDisable(void)
{
	// Enable the General Interrupt
	SREG &= ~(1 << 7);

}
