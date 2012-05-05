/**
    \file PushButton.c
    \brief The push button modules manages the push buttons.

    \details The push button module will the button presses and send button press signals to the application.
*/

#include <stdbool.h>
#include <avr/io.h>
#include "PushButton.h"
#include <Gpio.h>

/**** PUBLIC VARIABLES ****/
uint8_t PushButtons = PushButton_None;
uint8_t PushButtonsPressed = PushButton_None;
uint8_t PushButtonsReleased = PushButton_None;

/**** LOCAL DEFINITIONS ****/

/**** LOCAL VARIABLES ****/
/** Declare local variables to hold the previous button state information for debouncing */
static volatile uint8_t _previousPushButtons = 0x00;

/**** LOCAL FUNCTION PROTOTYPES ****/

/**** LOCAL FUNCTION DEFINITIONS ****/
/**
    Check the status of the push buttons
*/
void CheckPushbuttons(void)
{
    volatile uint8_t currentPushButtons = PushButton_None;

    /* get the current state of the push buttons */
	currentPushButtons |= READ_BUTTON0 ? PushButton_0 : PushButton_None;
	currentPushButtons |= READ_BUTTON1 ? PushButton_1 : PushButton_None;
	currentPushButtons |= READ_BUTTON2 ? PushButton_2 : PushButton_None;
	currentPushButtons |= READ_BUTTON3 ? PushButton_3 : PushButton_None;

    /* if the button state has changed and the current state is pressed, then the button was just pressed */
    PushButtonsPressed = (currentPushButtons ^ _previousPushButtons) & currentPushButtons;
    /* if the button was pressed, store the current state as pressed. Only changing this on press and release
       ensures that the button state is always in agreement with the debouncing */
	PushButtons |= PushButtonsPressed;

	/* if the button state has changed and the previous state is pressed, then the button was just released */
	PushButtonsReleased = (currentPushButtons ^ _previousPushButtons) & _previousPushButtons;
	/* if the button was released, store the current state as released. Only changing this on press and release
       ensures that the button state is always in agreement with the debouncing */
	PushButtons &= ~PushButtonsReleased;

	/* store the current state as the previous for next time */
	_previousPushButtons = currentPushButtons;
}