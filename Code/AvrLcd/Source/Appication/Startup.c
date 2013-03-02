/**
    \file Startup.h
    \brief Runs once to perform a startup procedure.

    \details The Startup module will run once and perform any special functions that need to be ran at startup
             such as a special startup sequence to display information to the user.
*/

#include "Startup.h"
#include "Cpu.h"
#include <util/delay.h>
#include "Gpio.h"
#include <avr/io.h>

/**** LOCAL DEFINITIONS ****/
#define delay _delay_ms(250)

/**** LOCAL VARIABLES ****/

/**** LOCAL FUNCTION PROTOTYPES ****/

/**** LOCAL FUNCTION DEFINITIONS ****/
/** Runs a startup script */
void RunStartup( void )
{
    SET_LED0; 
	delay; 
	
	CLEAR_LED0; 
	SET_LED1; 
	delay; 
	
	CLEAR_LED1; 
	SET_LED2; 
	delay; 
	
	CLEAR_LED2; 
	SET_LED3; 
	delay; 
	
	CLEAR_LED3; 
	SET_LED4; 
	delay; 
	
	CLEAR_LED4; 
	SET_LED5; 
	delay; 
	
	CLEAR_LED5; 
	SET_LED6; 
	delay; 
	
	CLEAR_LED6; 
	SET_LED7; 
	delay; 
	
	CLEAR_LED7; 
	SET_LED8; 
	delay; 
	
	CLEAR_LED8; 
	SET_LED9; 
	delay; 
	
	CLEAR_LED9; 
	SET_LED10; 
	delay; 
	
	CLEAR_LED10; 
	delay; 
	
	SET_LED0; 
	SET_LED1; 
	SET_LED2; 
	SET_LED3; 
	SET_LED4; 
	SET_LED5; 
	SET_LED6; 
	SET_LED7; 
	SET_LED8; 
	SET_LED9; 
	SET_LED10; 
	delay; 
	
	CLEAR_LED0; 
	CLEAR_LED1; 
	CLEAR_LED2; 
	CLEAR_LED3; 
	CLEAR_LED4; 
	CLEAR_LED5; 
	CLEAR_LED6; 
	CLEAR_LED7; 
	CLEAR_LED8; 
	CLEAR_LED9; 
	CLEAR_LED10; 
	delay; 
}