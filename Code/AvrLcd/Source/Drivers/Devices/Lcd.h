/**
    \file Lcd.h
    \brief The header file for the LCD driver
    \details The LCD module will control the output to a 16x2 character LCD
*/


#ifndef LCD_H_
#define LCD_H_


/**** PUBLIC DEFINITIONS ****/

/** Defines all of the possible configuration options to set */
typedef enum LcdConfOption
{
    LcdConfOption_INVALID   = -1,
    LcdConfOption_FIRST     = 0u,
    LcdConfOption_CLR_DISP  = LcdConfOption_FIRST,
    LcdConfOption_GO_HOME,
    LcdConfOption_CURSOR_LEFT,
    LcdConfOption_CURSOR_RIGHT,
    LcdConfOption_SHIFT_LEFT,
    LcdConfOption_SHIFT_RIGHT,
    LcdConfOption_DISPLAY_ENABLE,
    LcdConfOption_DISPLAY_DISABLE,
    LcdConfOption_CURSOR_ON,
    LcdConfOption_CURSOR_OFF,
    LcdConfOption_CURSOR_BLINK_ON,
    LcdConfOption_CURSOR_BLINK_OFF,
    LcdConfOption_CURSOR_LEFT_NO_WRITE,
    LcdConfOption_CURSOR_RIGHT_NO_WRITE,
    LcdConfOption_SHIFT_LEFT_NO_WRITE,
    LcdConfOption_SHIFT_RIGHT_NO_WRITE
} LcdConfOption_t;

#define LINE1_START_ADDRESS     (0x00u)
#define LINE2_START_ADDRESS     (0x40u)

/**** PUBLIC FUNCTIONS ******/
void Lcd_Init(void);
bool Lcd_WriteCharacter(uint8_t character);
bool Lcd_SetConfig(LcdConfOption_t option);
bool Lcd_SetDdramAddress(uint8_t address);


#endif /* LCD_H_ */