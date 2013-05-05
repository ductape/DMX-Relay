/**
    \file PushButton.c
    \brief The push button modules manages the push buttons.

    \details The push button module will the button presses and send button press signals to the application.
*/

#include "ProjectTypes.h"
#include "PushButton.h"
#include <Gpio.h>

/**** PUBLIC VARIABLES ****/
/**** LOCAL DEFINITIONS ****/

/**** LOCAL VARIABLES ****/
/** Declare local variables to hold the previous button state information for debouncing */
static volatile uint8_t _previousPushButtons = 0x00;

/** Stores the current "pressed" state of the push buttons. */
static volatile uint8_t _pushButtons;

/** Stores when the buttons have been pressed. */
static volatile uint8_t _pushButtonsPressed;

/** Stores when the buttons have been released. */
static volatile uint8_t _pushButtonsReleased;

/* Stores the count for how long each push button has
   been pressed */
static uint8_t _pushButtonCount[NUM_PUSH_BUTTONS] = 
{
	0u,
	0u,
	0u,
	0u
}; 

/**** LOCAL FUNCTION PROTOTYPES ****/

/**** LOCAL FUNCTION DEFINITIONS ****/
/**
    Check the status of the push buttons
*/
void CheckPushButtons(void)
{
	uint8_t counter;
	PushButton_t button;
    volatile uint8_t currentPushButtons = PushButton_None;

    /* get the current state of the push buttons */
	currentPushButtons |= READ_BUTTON0 ? PushButton_DOWN : PushButton_None;
	currentPushButtons |= READ_BUTTON1 ? PushButton_LEFT : PushButton_None;
	currentPushButtons |= READ_BUTTON2 ? PushButton_RIGHT : PushButton_None;
	currentPushButtons |= READ_BUTTON3 ? PushButton_UP : PushButton_None;

    /* if the button state has changed and the current state is pressed, then the button was just pressed */
    _pushButtonsPressed = (currentPushButtons ^ _previousPushButtons) & currentPushButtons;
    /* if the button was pressed, store the current state as pressed. Only changing this on press and release
       ensures that the button state is always in agreement with the debouncing */
	_pushButtons |= _pushButtonsPressed;

	/* if the button state has changed and the previous state is pressed, then the button was just released */
	_pushButtonsReleased = (currentPushButtons ^ _previousPushButtons) & _previousPushButtons;
	/* if the button was released, store the current state as released. Only changing this on press and release
       ensures that the button state is always in agreement with the debouncing */
	_pushButtons &= ~_pushButtonsReleased;

	/* store the current state as the previous for next time */
	_previousPushButtons = currentPushButtons;
	
	/* update the button pressed counters */
	for(counter = 0u; counter < NUM_PUSH_BUTTONS; ++counter)
	{
		button = (PushButton_t)(1<<counter);
		if (button & _pushButtons)
		{
			if(_pushButtonCount[counter] < UINT8_MAX)
			{
				++_pushButtonCount[counter];
			}
		}
		else
		{
			_pushButtonCount[counter] = 0u;
		}
		
	}
}

uint8_t PushButtonsPressed( void)
{
    return _pushButtonsPressed;
}

uint8_t PushButtonsReleased( void )
{
    return _pushButtonsReleased;
}

uint8_t PushButtonState( void )
{
    return _pushButtons;
}

uint8_t PushButtonCount(PushButton_t button)
{
	uint8_t buttonCount = 0u;
	uint8_t counter = UINT8_MAX;
	
	/* Start the counter at UINT8_MAX (255) so that it is equivilent to
	   -1, so the first button (0x01) will increment counter once and
	   counter = 0. This also guarantees that if Button_NONE (0x00) is 
	   passed in, we will not try to read from the array */
	while (button)
	{
		button >>= 1; 
		++counter;
	}
	
	if (counter < NUM_PUSH_BUTTONS)
	{
		buttonCount = _pushButtonCount[counter];
	}
	
	return buttonCount;
}