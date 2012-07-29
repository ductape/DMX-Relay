/*
 * Gpio.c
 *
 * Created: 2/21/2012 8:48:21 PM
 *  Author: Shaun
 */

#include "Gpio.h"
#include <avr/io.h>

void GpioInit(void)
{
	/* configure the outputs */
	DDRD |= LED0 | LED1 | LED4 | LED5 | LED9 | LED10 | POWER_LED_ON;
	DDRB |= LED2 | LED3 | LED6 | LED7 | LED8;

	/* ensure all the outputs are off */
	PORTD &= ~(LED0 | LED1 | LED4 | LED5 | LED9 | LED10);
	PORTB &= ~(LED2 | LED3 | LED6 | LED7 | LED8);

    /* enable the power led on */
    SET_POWER_LED_ON;

    /* configure the inputs */
    DDRC &= ~(BUTTON0 | BUTTON1 | BUTTON2 | BUTTON3);
}