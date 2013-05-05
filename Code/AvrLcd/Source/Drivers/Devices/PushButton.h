/**
    \file PushButton.h
    \brief The header file for the push button module.

    \details The push button module will the button presses and send button press signals to the application.
*/


#ifndef PUSHBUTTON_H_
#define PUSHBUTTON_H_

/**** PUBLIC DEFINITIONS ****/

/** Defines a bit-flag enumeration for the
    possible push buttons. */
typedef enum PushButton
{
	PushButton_None = 0x00,
	PushButton_DOWN    = 0x01,
	PushButton_LEFT    = 0x02,
	PushButton_RIGHT    = 0x04,
	PushButton_UP    = 0x08
} PushButton_t;

/** Defines the number of buttons declared in PushButton_t */
#define NUM_PUSH_BUTTONS    (4u)

/**** PUBLIC VARIABLES ****/

/**** PUBLIC FUNCTION PROTOTYPES ****/
void CheckPushButtons( void );
uint8_t PushButtonsPressed( void);
uint8_t PushButtonsReleased( void );
uint8_t PushButtonState( void );
uint8_t PushButtonCount(PushButton_t button);

#endif /* PUSHBUTTON_H_ */