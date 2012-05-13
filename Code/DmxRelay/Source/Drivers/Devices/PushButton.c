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

/**** LOCAL FUNCTION PROTOTYPES ****/

/**** LOCAL FUNCTION DEFINITIONS ****/
/**
    Check the status of the push buttons
*/
void CheckPushButtons(void)
{
    volatile uint8_t currentPushButtons = PushButton_None;

    /* get the current state of the push buttons */
	currentPushButtons |= READ_BUTTON0 ? PushButton_0 : PushButton_None;
	currentPushButtons |= READ_BUTTON1 ? PushButton_1 : PushButton_None;
	currentPushButtons |= READ_BUTTON2 ? PushButton_2 : PushButton_None;
	currentPushButtons |= READ_BUTTON3 ? PushButton_3 : PushButton_None;

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

