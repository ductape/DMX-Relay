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
    /* configure LCD */
	DDRD |= LCD_DB0 | LCD_DB1 | LCD_DB2 | LCD_DB3 | LCD_DB4 | LCD_DB5 | LCD_DB6 | LCD_DB7;
	DDRB |= LCD_BRIGHTNESS | LCD_E;
    DDRC |= LCD_RS | LCD_RnW;

    /* configure THERMAL */
    DDRB |= THERM_SS | THERM_MOSI | THERM_SCK;
    DDRB &= ~(THERM_MISO);

    /* configure the pushbuttons */
    DDRC &= ~(BUTTON0 | BUTTON1 | BUTTON2 | BUTTON3);

	/* ensure all the outputs are off */
	PORTD = 0x00;
	PORTC = 0x00;
    PORTB = 0x00;
    
    /* Turn on LCD backlight */
    SET_LCD_BRIGHTNESS; 
}