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

/**** PUBLIC FUNCTION PROTOTYPES ****/
void CheckPushButtons( void );
uint8_t PushButtonsPressed( void);
uint8_t PushButtonsReleased( void );
uint8_t PushButtonState( void );

#endif /* PUSHBUTTON_H_ */