/*
 * Cpu.c
 *
 * Created: 2/19/2012 8:55:49 PM
 *  Author: Shaun
 */ 

#include "Cpu.h"
#include <avr/io.h>
/**
	\brief Sets the clock divider on the CPU clock
	
	Sets the clock divider to 0, so if the internal
	oscillator is used, the CPU frequency is 8MHz. 
*/
void CpuConfig( void )
{
	CLKPR = (1 << CLKPCE); // set the clock prescale enable bit; 
	CLKPR = 0x00; // set the divider to 1
}