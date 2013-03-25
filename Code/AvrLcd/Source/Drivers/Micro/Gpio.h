/*
 * Gpio.h
 *
 * Created: 2/21/2012 8:47:58 PM
 *  Author: Shaun
 */


#ifndef GPIO_H_
#define GPIO_H_

#include <avr/io.h>

/**** DEFINES ****/

/* LCD */
#define SET_LCD_DB(arg)             PORTD = ((uint8_t)(arg));
#define GET_LCD_DB              ((uint8_t)(PIND))
#define SET_LCD_DB_AS_INPUT     DDRD = 0x00;
#define SET_LCD_DB_AS_OUTPUT    DDRD = 0xff;

#define LCD_DB0        (1<<PIND0)
#define SET_LCD_DB0    PORTD |= LCD_DB0
#define CLEAR_LCD_DB0  PORTD &= ~LCD_DB0
#define TOGGLE_LCD_DB0 PIND = LCD_DB0

#define LCD_DB1        (1<<PIND1)
#define SET_LCD_DB1    PORTD |= LCD_DB1
#define CLEAR_LCD_DB1  PORTD &= ~LCD_DB1
#define TOGGLE_LCD_DB1 PIND = LCD_DB1

#define LCD_DB2        (1<<PIND2)
#define SET_LCD_DB2    PORTD |= LCD_DB2
#define CLEAR_LCD_DB2  PORTD &= ~LCD_DB2
#define TOGGLE_LCD_DB2 PIND = LCD_DB2

#define LCD_DB3        (1<<PIND3)
#define SET_LCD_DB3    PORTD |= LCD_DB3
#define CLEAR_LCD_DB3  PORTD &= ~LCD_DB3
#define TOGGLE_LCD_DB3 PIND = LCD_DB3

#define LCD_DB4        (1<<PIND4)
#define SET_LCD_DB4    PORTD |= LCD_DB4
#define CLEAR_LCD_DB4  PORTD &= ~LCD_DB4
#define TOGGLE_LCD_DB4 PIND = LCD_DB4

#define LCD_DB5        (1<<PIND5)
#define SET_LCD_DB5    PORTD |= LCD_DB5
#define CLEAR_LCD_DB5  PORTD &= ~LCD_DB5
#define TOGGLE_LCD_DB5 PIND = LCD_DB5

#define LCD_DB6        (1<<PIND6)
#define SET_LCD_DB6    PORTD |= LCD_DB6
#define CLEAR_LCD_DB6  PORTD &= ~LCD_DB6
#define TOGGLE_LCD_DB6 PIND = LCD_DB6

#define LCD_DB7                 (1<<PIND7)
#define SET_LCD_DB7             PORTD |= LCD_DB7
#define CLEAR_LCD_DB7           PORTD &= ~LCD_DB7
#define TOGGLE_LCD_DB7          PIND = LCD_DB7
#define GET_LCD_DB7             ((PIND & LCD_DB7) == true)
#define SET_LCD_DB7_AS_OUTPUT   DDRD |= LCD_DB7
#define SET_LCD_DB7_AS_INPUT    DDRD &= ~(LCD_DB7)

#define LCD_E        (1<<PINB0)
#define SET_LCD_E    PORTB |= LCD_E
#define CLEAR_LCD_E  PORTB &= ~LCD_E
#define TOGGLE_LCD_E PINB = LCD_E

#define LCD_RS        (1<<PINC0)
#define SET_LCD_RS    PORTC |= LCD_RS
#define CLEAR_LCD_RS  PORTC &= ~LCD_RS
#define TOGGLE_LCD_RS PINC = LCD_RS

#define LCD_RnW        (1<<PINC1)
#define SET_LCD_RnW    PORTC |= LCD_RnW
#define CLEAR_LCD_RnW  PORTC &= ~LCD_RnW
#define TOGGLE_LCD_RnW PINC = LCD_RnW

#define LCD_BRIGHTNESS        (1<<PINB1)
#define SET_LCD_BRIGHTNESS    PORTB |= LCD_BRIGHTNESS
#define CLEAR_LCD_BRIGHTNESS  PORTB &= ~LCD_BRIGHTNESS
#define TOGGLE_LCD_BRIGHTNESS PINB = LCD_BRIGHTNESS

/* THERMAL */
#define THERM_SS        (1<<PINB2)
#define SET_THERM_SS    PORTB |= THERM_SS
#define CLEAR_THERM_SS  PORTB &= ~THERM_SS
#define TOGGLE_THERM_SS PINB = THERM_SS

#define THERM_MOSI        (1<<PINB3)
#define SET_THERM_MOSI    PORTB |= THERM_MOSI
#define CLEAR_THERM_MOSI  PORTB &= ~THERM_MOSI
#define TOGGLE_THERM_MOSI PINB = THERM_MOSI

#define THERM_MISO        (1<<PINB4)
#define SET_THERM_MISO    PORTB |= THERM_MISO
#define CLEAR_THERM_MISO  PORTB &= ~THERM_MISO
#define TOGGLE_THERM_MISO PINB = THERM_MISO

#define THERM_SCK        (1<<PINB5)
#define SET_THERM_SCK    PORTB |= THERM_SCK
#define CLEAR_THERM_SCK  PORTB &= ~THERM_SCK
#define TOGGLE_THERM_SCK PINB = THERM_SCK

/* PUSH BUTTONS */
#define BUTTON0         (1<<PINC2)
#define READ_BUTTON0    ((PINC & BUTTON0) == false)

#define BUTTON1         (1<<PINC3)
#define READ_BUTTON1    ((PINC & BUTTON1) == false)

#define BUTTON2         (1<<PINC4)
#define READ_BUTTON2    ((PINC & BUTTON2) == false)

#define BUTTON3         (1<<PINC5)
#define READ_BUTTON3    ((PINC & BUTTON3) == false)

/**** DECLARATIONS ****/
void GpioInit(void);

#endif /* GPIO_H_ */