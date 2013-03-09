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


/** Defines the different register options */
typedef enum LcdReg
{
    LcdReg_CLEAR_DISPLAY = 0x01, /** Clears the display data and resets all of the settings */
    LcdReg_RETURN_HOME   = 0x02, /** Returns the cursor to the home position */
    LcdReg_ENTRY_MODE    = 0x04, /** Sets the moving direction of the cursor and the display */
    LcdReg_DISP_ON_OFF   = 0x08, /** Sets the display/cursor/blink ON/OFF options */
    LcdReg_SHIFT_SETTING = 0x10, /** Controls the shift setting during "search" TODO: what is this used for? */
    LcdReg_FUNCTION_SET  = 0x20, /** Control the display function settings 4/8-bit, 1/2-line, and 5x8/5x11 mode */
    LcdReg_CGRAM_ADDR    = 0x40,
    LcdReg_DDRAM_ADDR    = 0x80
} LcdReg_t;

/** Register Settings for the Entry Mode register */
typedef enum RegEntryMode
{
    RegEntryMode_INC_RIGHT = 0x02,
    RegEntryMode_DEC_LEFT  = 0x00,
    RegEntryMode_SHIFT_ON  = 0x01,
    RegEntryMode_SHIFT_OFF = 0x00
} RegEntryMode_t;

/** Register settings for the display on/off register */
typedef enum RegDisp
{
    RegDisp_DISPLAY_ON  = 0x04,
    RegDisp_DISPLAY_OFF = 0x00,
    RegDisp_CURSOR_ON   = 0x02,
    RegDisp_CURSOR_OFF  = 0x00,
    RegDisp_BLINK_ON    = 0x01,
    RegDisp_BLINK_OFF   = 0x00
} RegDisp_t;

/** Register settings for the Shift Setting register */
typedef enum RegShift
{
    RegShift_SHIFT_CURSOR_LEFT  = 0x00,
    RegShift_SHIFT_CURSOR_RIGHT = 0x01,
    RegShift_SHIFT_DISP_LEFT    = 0x02,
    RegShift_SHIFT_DISP_RIGHT   = 0x03
} RegShift_t;

/** Register settings for the function set register */
typedef enum RegFunction
{
    RegFunction_BUS_BIT_8    = 0x10,
    RegFunction_BUS_BIT_4    = 0x00,
    RegFunction_DISP_LINES_1 = 0x00,
    RegFunction_DISP_LINES_2 = 0x08,
    RegFunction_CHAR_5X8     = 0x00,
    RegFunction_CHAR_5x11    = 0x04
} RegFunction_t;

/**** LOCAL CONSTANTS ****/

/**** LOCAL VARIABLES ****/

/**** LOCAL FUNCTION DECLARATIONS ****/
static void _WriteChar(bool control, uint8_t character);
static uint8_t _ReadChar(bool control, uint8_t address);

/**** FUNCTION DEFINITIONS ****/

void Lcd_Init(void)
{
    _delay_ms(15u); /** let the LCD boot up */
    _WriteChar(true, (LcdReg_FUNCTION_SET | RegFunction_BUS_BIT_8 | RegFunction_DISP_LINES_2 | RegFunction_CHAR_5X8));
    _delay_ms(5u);  /** let the settings get applied */
    _WriteChar(true, (LcdReg_DISP_ON_OFF | RegDisp_DISPLAY_ON | RegDisp_CURSOR_OFF | RegDisp_BLINK_OFF));
    _delay_ms(1u);
    _WriteChar(true, (LcdReg_ENTRY_MODE | RegEntryMode_INC_RIGHT | RegEntryMode_SHIFT_OFF));
    _delay_ms(1u);
    _WriteChar(true, (LcdReg_CLEAR_DISPLAY));
    _delay_ms(3u);
}

bool Lcd_WriteCharacter(uint8_t character)
{
    _WriteChar(false, character);
    return true;
}

bool Lcd_SetConfig(LcdConfOption_t option)
{
    uint8_t character;
    bool success = true;

    /* TODO: change these to the ENUM settings */
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