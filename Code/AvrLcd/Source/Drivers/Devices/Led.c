/**
    \file Led.c
    \brief The Led Driver module controls system Leds
    \details The Led module will maintain and controls the state of an LED and run through specific blink patterns.
*/
#include "ProjectTypes.h"
#include "Led.h"
#include "Gpio.h"

/**** PUBLIC VARIABLES ****/

/**** LOCAL DEFINES ****/
#define STEPS_IN_BYTE 7u

/**** LOCAL CONSTANTS ****/

/**** LOCAL VARIABLES ****/
static volatile uint8_t _ledPatterns[Led_Last]    = { 0u };
static volatile uint8_t _ledIndexNumber[Led_Last] = { STEPS_IN_BYTE };
static volatile bool    _ledRepeating[Led_Last]   = { false };

/**** LOCAL FUNCTION DECLARATIONS ****/
void _SetLed(Led_t led);
void _ClearLed(Led_t led);
/**** FUNCTION DEFINITIONS ****/
void ProcessLeds( void )
{
	volatile uint8_t counter;

	for(counter = 0; counter < (Led_Last); counter++)
	{
        if (_ledPatterns[counter] & ( 1 << _ledIndexNumber[counter]))
		{
			_SetLed(counter);
		}
		else
		{
			_ClearLed(counter);
		}

		if ((--(_ledIndexNumber[counter])) == 0)
		{
			_ledIndexNumber[counter] = STEPS_IN_BYTE;

			if (_ledRepeating[counter] == false)
			{
				_ledPatterns[counter] = LedPattern_Off;
			}
		}
	}

}

void SetLedPattern( LedPattern_t ledPattern,
                    Led_t led,
                    bool repeating )
{
	_ledPatterns[led]    = ledPattern;
	_ledRepeating[led]   = repeating;
	_ledIndexNumber[led] = STEPS_IN_BYTE;
}

void ClearLed( Led_t led )
{
	_ledPatterns[led]  = LedPattern_Off;
	_ledRepeating[led] = false;
}

void _SetLed(Led_t led)
{
	switch(led)
	{
		case Led_0:
			break;

		case Led_1:
			break;

		case Led_2:
			break;

		case Led_3:
			break;

		case Led_4:
			break;

		case Led_5:
			break;

		case Led_6:
			break;

		case Led_7:
			break;

		case Led_8:
			break;

		case Led_9:
			break;

		case Led_10:
			break;

		default:
		    break;
	}
}

void _ClearLed(Led_t led)
{
		switch(led)
	{
		case Led_0:
			break;

		case Led_1:
			break;

		case Led_2:
			break;

		case Led_3:
			break;

		case Led_4:
			break;

		case Led_5:
			break;

		case Led_6:
			break;

		case Led_7:
			break;

		case Led_8:
			break;

		case Led_9:
			break;

		case Led_10:
			break;

		default:
		    break;
	}
}
