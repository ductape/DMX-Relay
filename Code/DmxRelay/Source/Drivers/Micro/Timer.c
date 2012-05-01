/*
 * Timer.c
 *
 * Created: 4/18/2012 9:12:43 PM
 *  Author: Shaun
 */

#include <avr/io.h>
#include <stdbool.h>
#include "Timer.h"
#include <avr/interrupt.h>
#include "Gpio.h"

void TimerInit(void)
{
	/* Timer 0A and 0B set to normal (no pin change)
	   mode of operation CTC (reset after output
	   compare match)
	*/
	TCCR0A = 0x02;

	/* Don't set any of the force compare bits and
	   set the clock divider to be clock/1024
	   giving a 15.625KHz period with at 16MHz clock
	*/
	TCCR0B = 0x05;

	/* Set the compare to give a 8 msec tick
	   0x7D = 125 and 125 / 15625 = 0.008 seconds
	*/
	OCR0A = 0x7D;

	/* Enable interrupts for the Timer 0 output
	   compare A match
	*/
	TIMSK0 = 0x02;
}

ISR(TIMER0_COMPA_vect)
{
    newTick = true;

	/* For 8 msec tick, 1sec = 125
	   ticks so reset every 2 seconds
	*/
	if( ++tickCount > 250 )
	{
		tickCount = 0;
	}

	if (tickCount % 62 == 0)
	{
		TOGGLE_LED0;
	}
}