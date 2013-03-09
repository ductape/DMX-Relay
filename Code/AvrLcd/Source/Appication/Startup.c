/**
    \file Startup.h
    \brief Runs once to perform a startup procedure.

    \details The Startup module will run once and perform any special functions that need to be ran at startup
             such as a special startup sequence to display information to the user.
*/

#include <ProjectTypes.h>
#include "Startup.h"
#include "Cpu.h"
#include <util/delay.h>
#include "Gpio.h"
#include <LcdController.h>
#include <avr/io.h>

/**** LOCAL DEFINITIONS ****/
#define delay _delay_ms(250)

/**** LOCAL VARIABLES ****/

/**** LOCAL FUNCTION PROTOTYPES ****/

/**** LOCAL FUNCTION DEFINITIONS ****/
/** Runs a startup script */
void RunStartup( void )
{
    bool success;
    success = LcdControl_WriteString("  Richie's EGT");
    success = LcdControl_SetCursorLocation(1, 0);
    success = LcdControl_WriteString("     sensor");
    _delay_ms(3000);
    success = LcdControl_ClearDisplay();
}