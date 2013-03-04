/**
    \file Lcd.h
    \brief The header file for the LCD driver
    \details The LCD module will control the output to a 16x2 character LCD
*/
#include "ProjectTypes.h"
#include "Lcd.h"
#include "Gpio.h"
#include <Cpu.h>
#include <util/delay.h>

/**** PUBLIC VARIABLES ****/

/**** LOCAL DEFINES ****/
#define DDRAM_ADDRESS_MAX   (0b01111111)
#define DDRAM_OPCODE        (0b10000000)
#define CGRAM_ADDRESS_MAX   (0b00111111)
#define CGRAM_OPCODE        (0b01000000)

/**** LOCAL CONSTANTS ****/

/**** LOCAL VARIABLES ****/

/**** LOCAL FUNCTION DECLARATIONS ****/
static void _WriteChar(bool control, uint8_t character);
static uint8_t _ReadChar(bool control, uint8_t address);

/**** FUNCTION DEFINITIONS ****/


bool Lcd_WriteCharacter(uint8_t character)
{
    _WriteChar(false, character);
    return true;
}

bool Lcd_SetConfig(LcdConfOption_t option)
{
    uint8_t character;
    bool success = true;

    switch(option)
    {
        case LcdConfOption_CLR_DISP:
            character = 0b00000001;
            break;

        case LcdConfOption_GO_HOME:
            character = 0b00000010;
            break;

        case LcdConfOption_CURSOR_LEFT:
            character = 0b00000100;
            break;

        case LcdConfOption_CURSOR_RIGHT:
            character = 0b00000101;
            break;

        case LcdConfOption_SHIFT_LEFT:
            character = 0b00000110;
            break;

        case LcdConfOption_SHIFT_RIGHT:
            character = 0b00000111;
            break;

        default:
            success = false;
            break;
    }

    if (success)
    {
        _WriteChar(true, character);
    }

    return success;
}

bool Lcd_SetDdramAddress(uint8_t address)
{
    _WriteChar(true, (DDRAM_OPCODE & (DDRAM_ADDRESS_MAX & address)));
    return true;
}

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