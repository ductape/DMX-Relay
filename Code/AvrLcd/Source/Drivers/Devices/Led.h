/**
    \file Led.h
    \brief The header file for the Led Driver module
    \details The Led module will maintain and controll the state of an LED and run through specific blink patterns.
*/


#ifndef LED_H_
#define LED_H_

typedef enum LedPattern
{
	LedPattern_Off        = 0x00,
	LedPatteron_On        = 0xFF,
	LedPattern_BlinkOnce  = 0x80,
	LedPattern_BlinkTwice = 0xA0,
	LedPattern_BlinkThrice = 0xA8,
	LedPattern_BlinkAll   = 0xAA
} LedPattern_t;

typedef enum Led
{
	Led_First = 0,
	Led_0     = Led_First,
	Led_1,
	Led_2,
	Led_3,
	Led_4,
	Led_5,
	Led_6,
	Led_7,
	Led_8,
	Led_9,
	Led_10,
	Led_Last
} Led_t;

void ProcessLeds( void );
void SetLedPattern( LedPattern_t ledPattern,
                    Led_t led,
                    bool repeating );
void ClearLed( Led_t led );



#endif /* LED_H_ */