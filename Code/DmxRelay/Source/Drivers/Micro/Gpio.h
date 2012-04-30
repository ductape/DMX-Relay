/*
 * Gpio.h
 *
 * Created: 2/21/2012 8:47:58 PM
 *  Author: Shaun
 */


#ifndef GPIO_H_
#define GPIO_H_


/**** DEFINES ****/
#define LED0        (1<<PIND7)
#define SET_LED0    PORTD |= LED0
#define CLEAR_LED0  PORTD &= ~LED0
#define TOGGLE_LED0 PIND = LED0

#define LED1		(1<<PIND4)
#define SET_LED1	PORTD |= LED1
#define CLEAR_LED1	PORTD &= ~LED1
#define TOGGLE_LED1 PIND = LED1

#define LED2        (1<<PINB6)
#define SET_LED2	PORTB |= LED2
#define CLEAR_LED2	PORTB &= ~LED2
#define TOGGLE_LED2 PINB = LED2

#define LED3        (1<<PINB7)
#define SET_LED3	PORTB |= LED3
#define CLEAR_LED3	PORTB &= ~LED3
#define TOGGLE_LED3 PINB = LED3

#define LED4        (1<<PIND5)
#define SET_LED4	PORTD |= LED4
#define CLEAR_LED4	PORTD &= ~LED4
#define TOGGLE_LED4 PIND = LED4

#define LED5        (1<<PIND6)
#define SET_LED5	PORTD |= LED5
#define CLEAR_LED5	PORTD &= ~LED5
#define TOGGLE_LED5 PIND = LED5

#define LED6        (1<<PINB2)
#define SET_LED6	PORTB |= LED6
#define CLEAR_LED6	PORTB &= ~LED6
#define TOGGLE_LED6 PINB = LED6

#define LED7        (1<<PINB1)
#define SET_LED7	PORTB |= LED7
#define CLEAR_LED7	PORTB &= ~LED7
#define TOGGLE_LED7 PINB = LED7;

#define LED8        (1<<PINB0)
#define SET_LED8	PORTB |= LED8
#define CLEAR_LED8	PORTB &= ~LED8
#define TOGGLE_LED8 PINB = LED8;

#define LED9        (1<<PIND2)
#define SET_LED9	PORTD |= LED9
#define CLEAR_LED9	PORTD &= ~LED9
#define TOGGLE_LED9 PIND = LED9;

#define LED10        (1<<PIND3)
#define SET_LED10    PORTD |= LED10
#define CLEAR_LED10  PORTD &= ~LED10
#define TOGGLE_LED10 PIND = LED10;


#define BUTTON0         (1<<PINC0)
#define READ_BUTTON0    ((PINC & BUTTON0) == false)

#define BUTTON1         (1<<PINC1)
#define READ_BUTTON1    ((PINC & BUTTON1) == false)

#define BUTTON2         (1<<PINC2)
#define READ_BUTTON2    ((PINC & BUTTON2) == false)

#define BUTTON3         (1<<PINC3)
#define READ_BUTTON3    ((PINC & BUTTON3) == false)

/**** DECLARATIONS ****/
void GpioInit(void);

#endif /* GPIO_H_ */