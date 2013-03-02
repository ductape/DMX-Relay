/**
    \file Lcd.h
    \brief The header file for the LCD driver
    \details The LCD module will control the output to a 16x2 character LCD
*/
#include "ProjectTypes.h"
#include "Lcd.h"
#include "Gpio.h"
#include <Cpu.h>
#include <avr/delay.h>

/**** PUBLIC VARIABLES ****/

/**** LOCAL DEFINES ****/
#define CLEAR_DISPLAY   ((uint8_t)(0x01))
#define RETURN_HOME     ((uint8_t)(0x02))

/**** LOCAL CONSTANTS ****/

/**** LOCAL VARIABLES ****/

/**** LOCAL FUNCTION DECLARATIONS ****/
static void _WriteChar(bool control, uint8_t character);
static uint8_t _ReadChar(bool control, uint8_t address);

/**** FUNCTION DEFINITIONS ****/



static void _WriteChar(bool control, uint8_t character)
{
    CLEAR_LCD_E;
    if (control)
    {
        CLEAR_LCD_RS;
    }
    else
    {
        SET_LCD_RS;
    }
    CLEAR_LCD_RnW;
    _delay_us(1u);
    SET_LCD_E;
    SET_LCD_DB(character);
    _delay_us(1u);
    CLEAR_LCD_E;
}

static uint8_t _ReadChar(bool control, uint8_t address)
{
    uint8_t character;

    SET_LCD_DB_AS_INPUT;
    CLEAR_LCD_E;
    if (control)
    {
        CLEAR_LCD_RS;
    }
    else
    {
        SET_LCD_RS;
    }
    SET_LCD_RnW;
    _delay_us(1u);
    SET_LCD_E;
    _delay_us(1u);
    character = GET_LCD_DB;
    CLEAR_LCD_E;
    SET_LCD_DB_AS_OUTPUT;
    return character;
}