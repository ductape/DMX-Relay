/**
    \file Main.c
    \brief The main file for the AVR LCD project

    \details The AVR LCD application will use an AVR microcontroller to drive a 16x2
             character LCD display.
*/
#include "ProjectTypes.h"
#include <avr/interrupt.h>
#include "Cpu.h"
#include "Gpio.h"
#include "Timer.h"
#include "Startup.h"
#include "Application.h"
#include <LcdController.h>

/**** LOCAL DEFINITIONS ****/

/**** LOCAL VARIABLES ****/



/**** LOCAL FUNCTIONS ****/
int main (void)
{
	CpuConfig();
	GpioInit();
	TimerInit();
    LcdControl_Init();

    RunStartup();

	sei();

	while (1)
	{
        ProcessEvents();
	}
	return 0;
}
