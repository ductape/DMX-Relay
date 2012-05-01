/**
    \file PushButton.h
    \brief The header file for the push button module.

    \details The push button module will the button presses and send button press signals to the application.
*/


#ifndef PUSHBUTTON_H_
#define PUSHBUTTON_H_

/**** PUBLIC DEFINITIONS ****/

/**** PUBLIC VARIABLES ****/
static volatile bool pb0_pressed = false;
static volatile bool pb1_pressed = false;
static volatile bool pb2_pressed = false;
static volatile bool pb3_pressed = false;

static volatile bool pb0_released = false;
static volatile bool pb1_released = false;
static volatile bool pb2_released = false;
static volatile bool pb3_released = false;

static volatile bool pb0_state = false;
static volatile bool pb1_state = false;
static volatile bool pb2_state = false;
static volatile bool pb3_state = false;

/**** PUBLIC FUNCTION PROTOTYPES ****/
void CheckPushButtons( void );


#endif /* PUSHBUTTON_H_ */