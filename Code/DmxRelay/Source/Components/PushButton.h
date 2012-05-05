/**
    \file PushButton.h
    \brief The header file for the push button module.

    \details The push button module will the button presses and send button press signals to the application.
*/


#ifndef PUSHBUTTON_H_
#define PUSHBUTTON_H_

/**** PUBLIC DEFINITIONS ****/
typedef enum PushButton
{
	PushButton_None = 0x00,
	PushButton_0    = 0x01,
	PushButton_1    = 0x02,
	PushButton_2    = 0x04,
	PushButton_3    = 0x08
} PushButton_t;

/**** PUBLIC VARIABLES ****/

/** Stores the current "pressed" state of the push buttons. Never write to this
    variable outside of this module. */
extern uint8_t PushButtons;

/** Stores when the buttons have been pressed. Always clear this variable after
    reading it so that the press will be unlatched */
extern uint8_t PushButtonsPressed;

/** Stores when the buttons have been released. Always clear this variable after
    reading it so that the release will be unlatched */
extern uint8_t PushButtonsReleased;

/**** PUBLIC FUNCTION PROTOTYPES ****/
void CheckPushButtons( void );


#endif /* PUSHBUTTON_H_ */