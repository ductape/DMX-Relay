/*
 * Timer.c
 *
 * Created: 4/18/2012 9:12:43 PM
 *  Author: Shaun
 */

#include "ProjectTypes.h"
#include "Timer.h"
#include <avr/interrupt.h>
#include "EventQueue.h"

/**** LOCAL DEFINITIONS ****/

/** Defines the number of timer ticks (interrupts) per 40 ms */
#define TICKS_PER_40MS 5u

/** Defines the number of timer ticks (interrupts) per 200 ms */
#define TICKS_PER_200MS 25u

/** Defines the number of timer ticks (interrupts) per 1 s */
#define TICKS_PER_1S 0u

/**** LOCAL CONSTANTS ****/

/**** LOCAL VARIABLES ****/
/** Is set each time that the timer ticks. */
static volatile bool ticked = false;

/** Keeps count of the number of timer ticks */
static volatile uint8_t tickCount = 0u;
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
	   set the clock divider to be clock/256
	   giving a 31.250KHz period with at 8MHz clock
	*/
	TCCR0B = 0x04;

	/* Set the compare to give a 8 msec tick
	   0x7D = 125 and 125 / 15625 = 0.008 seconds
	*/
	//OCR0A = 0x7D;
	OCR0A = 250u;

	/* Enable interrupts for the Timer 0 output
	   compare A match
	*/
	TIMSK0 = 0x02;
}

void ProcessTick(void)
{
	if (ticked)
	{
		/* clear the tick flag */
		ticked = false;
		
        /* with an 8ms tick, enqueue an event every tick */
        EnqueueEvent(EventType_8ms);

	    if ((tickCount % TICKS_PER_40MS) == 0)
	    {
            EnqueueEvent(EventType_40ms);
	    }

	    if ((tickCount % TICKS_PER_200MS) == 0)
	    {
            EnqueueEvent(EventType_200ms);
	    }

        /* no modulo here because the tick counter rolls over at 1s */
        if (tickCount == TICKS_PER_1S)
	    {
		    EnqueueEvent(EventType_1s);
	    }

        /* reset the tick counter at 125 so that it resets once per second */
	    if(++tickCount >= 125)
	    {
		    tickCount = 0u;
	    }
	}
}

ISR(TIMER0_COMPA_vect)
{
    ticked = true;
}