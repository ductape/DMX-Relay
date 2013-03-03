/** \file LcdController.h
    \brief Provides high level functions for controlling the LCD

    \details Provides the high level functions for controlling the character LCD.
 */


#ifndef LCDCONTROLLER_H_
#define LCDCONTROLLER_H_


/**** PUBLIC DEFINITIONS ****/

/** Define the dimensions of the character LCD */
typedef uint8_t LcdRows_t;
typedef uint8_t LcdColumns_t;

typedef struct LcdDimension
{
    LcdRows_t rows;
    LcdColumns_t columns;
} LcdDimension_t;

/**** PUBLIC CONSTANTS ******/
static const LcdDimension_t LcdControl_Dimensions =
{
    2u,
    16u
};

/**** PUBLIC FUNCTIONS ******/
bool LcdControl_WriteString(const char* string);
bool LcdControl_SetCursorLocation(uint8_t character, uint8_t line);
bool LcdControl_ClearDisplay(void);

void LcdControl_ProcessLcd(void);

#endif /* LCDCONTROLLER_H_ */