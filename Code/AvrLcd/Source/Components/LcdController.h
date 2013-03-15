/** \file LcdController.h
    \brief Provides high level functions for controlling the LCD

    \details Provides the high level functions for controlling the character LCD.
 */


#ifndef LCDCONTROLLER_H_
#define LCDCONTROLLER_H_


/**** PUBLIC DEFINITIONS ****/

#if 1 /* sets if the LCD display buffers characters or not */
#define NO_BUFFERING
#endif
/** Define the dimensions of the character LCD */
typedef uint8_t LcdRows_t;
typedef uint8_t LcdColumns_t;

typedef struct LcdDimension
{
    LcdRows_t rows;
    LcdColumns_t columns;
} LcdDimension_t;

/** Define the size of the LCD */
#define LCD_COLUMNS     ( 16u )
#define LCD_ROWS        ( 2u  )

/**** PUBLIC CONSTANTS ******/
static const LcdDimension_t LcdControl_Dimensions =
{
    2u,
    16u
};

/**** PUBLIC FUNCTIONS ******/
void LcdControl_Init(void);
bool LcdControl_WriteString(const char* string);
bool LcdControl_SetCursorLocation(LcdRows_t row, LcdColumns_t column);
bool LcdControl_ClearDisplay(void);

void LcdControl_ProcessLcd(void);

#endif /* LCDCONTROLLER_H_ */