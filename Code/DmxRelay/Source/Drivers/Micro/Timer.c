/*
 * Timer.c
 *
 * Created: 4/18/2012 9:12:43 PM
 *  Author: Shaun
 */

#include "ProjectTypes.h"
#include "Timer.h"
#include <avr/interrupt.h>
#include "Gpio.h"
#include "EventQueue.h"

/**** LOCAL DEFINITIONS ****/

/** Defines the number of timer ticks (interrupts) per 64 ms */
#define TICKS_PER_64MS 8u

/** Defines the number of timer ticks (interrupts per 1 s */
#define TICKS_PER_1S 125u

/**** LOCAL CONSTANTS ****/
static const Event_t EVENT_8MS  = {EventType_8ms,  0u};
static const Event_t EVENT_64MS = {EventType_64ms, 0u};
static const Event_t EVENT_1S   = {EventType_1s,   0u};

/**** LOCAL VARIABLES ****/

/**** LOCAL FUNCTION DECLARATIONS ****/

/**** FUNCTION DEFINITIONS ****/

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
	static uint8_t tickCount = 0u;
	static uint8_t last64ms  = 0u;
	static uint8_t last1s    = 0u;

    EnqueueEvent(&EVENT_8MS);

	/* For 8 msec tick, 1sec = 125 ticks */
	if ((tickCount - last64ms) % TICKS_PER_64MS)
	{
        EnqueueEvent(&EVENT_64MS);
		last64ms = tickCount;
	}

    if ((tickCount - last1s) % TICKS_PER_1S)
	{
		EnqueueEvent(&EVENT_1S);
		last1s = tickCount;
	}

	if (tickCount % 62 == 0)
	{
		TOGGLE_LED0;
	}
	
	tickCount++; 
}