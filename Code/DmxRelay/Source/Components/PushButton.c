/**
    \file PushButton.c
    \brief The push button modules manages the push buttons.

    \details The push button module will the button presses and send button press signals to the application.
*/

#include <stdbool.h>
#include "PushButton.h"
#include <Gpio.h>
#include <avr/io.h>

/**** LOCAL DEFINITIONS ****/

/**** LOCAL VARIABLES ****/
/** Declare local variables to hold the previous button state information for debouncing */
static volatile bool _pb0_previous = false;
static volatile bool _pb1_previous = false;
static volatile bool _pb2_previous = false;
static volatile bool _pb3_previous = false;

/**** LOCAL FUNCTION PROTOTYPES ****/
bool _IsPressed(bool current, bool previous);
bool _IsReleased(bool current, bool previous);

/**** LOCAL FUNCTION DEFINITIONS ****/
/**
    Check the status of the push buttons
*/
void CheckPushbuttons(void)
{
    volatile bool pb0 = READ_BUTTON0;
	volatile bool pb1 = READ_BUTTON1;
	volatile bool pb2 = READ_BUTTON2;
	volatile bool pb3 = READ_BUTTON3;

    pb0_pressed = _IsPressed(pb0, _pb0_previous); 
	if (pb0_pressed)
	{
		pb0_state = true; 
	}		
	pb1_pressed = _IsPressed(pb1, _pb1_previous); 
	if (pb1_pressed)
	{
		pb1_state = true; 
	}
	pb2_pressed = _IsPressed(pb2, _pb2_previous); 
	if (pb2_pressed)
	{
		pb2_state = true; 
	}
	pb3_pressed = _IsPressed(pb3, _pb3_previous); 
    if (pb3_pressed)
	{
		pb3_state = true; 
	}
	
	pb0_released = _IsReleased(pb0, _pb0_previous); 
	if (pb0_released)
	{
		pb0_state = false; 
	}		
	pb1_released = _IsReleased(pb1, _pb1_previous); 
	if (pb1_released)
	{
		pb1_state = false; 
	}
	pb2_released = _IsReleased(pb2, _pb2_previous); 
	if (pb2_released)
	{
		pb2_state = false; 
	}
	pb3_released = _IsReleased(pb3, _pb3_previous); 
    if (pb3_released)
	{
		pb3_state = false; 
	}	
	
	_pb0_previous = pb0;
	_pb1_previous = pb1;
	_pb2_previous = pb2;
	_pb3_previous = pb3;
}

bool _IsPressed(bool current, bool previous)
{
	bool isPressed = false;

	if ((current == true) && (previous == false))
	{
		isPressed = true;
	}

	return isPressed;
}

bool _IsReleased(bool current, bool previous)
{
	bool isReleased = false;

	if ((current == false) && (previous == true))
	{
		isReleased = true;
	}

	return isReleased;
}