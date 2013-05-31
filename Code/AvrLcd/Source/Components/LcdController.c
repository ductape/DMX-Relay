/** \file LcdController.c
    \brief Provides high level functions for controlling the LCD

    \details Provides the high level functions for controlling the character LCD.
 */
#include <ProjectTypes.h>
#include <Lcd.h>
#include <LcdController.h>
#include <CircularBuffer.h>
#include <string.h>
#include <EventQueue.h>
#include <Cpu.h>
#include <util/delay.h>

/**** LOCAL DEFINITIONS ****/
#define LCD_BUFFER_LENGTH   (32u)

/**** LOCAL VARIABLES ****/

#ifndef NO_BUFFERING
uint8_t _bufferData[LCD_BUFFER_LENGTH];

static CircularBuffer_t _buffer =
{
    0u,
    0u,
    0u,
    LCD_BUFFER_LENGTH,
    _bufferData
};
#endif

/**** LOCAL CONSTANTS ****/

/**** LOCAL FUNCTION PROTOTYPES ****/

/**** LOCAL FUNCTIONS ****/
void LcdControl_Init(void)
{
    Lcd_Init();
}

bool LcdControl_WriteString(const char* string)
{
    bool success = false;
    uint8_t strlength;
    uint8_t index;

    strlength = strlen(string);
#ifndef NO_BUFFERING
    if (strlength < (_buffer.bufferSize - _buffer.numberInBuffer))
    {
        for (index = 0u; index < strlength; ++index)
        {
            success = CircularBuffer_Add(string[index], &_buffer);
            if (success == false)
            {
                break;
            }
        }
    }

    if (success)
    {
        EnqueueEvent(EventType_LCD);
    }
#else
    for (index = 0u; index < strlength; ++index)
    {
        Lcd_WriteCharacter(string[index]);
        _delay_ms(1);
    }
    success = true;
#endif
    return success;
}

bool LcdControl_SetCursorLocation(LcdRows_t row, LcdColumns_t column)
{
    bool success = false;
    uint8_t address;

    if ((row < LcdControl_Dimensions.rows) &&
        (column < LcdControl_Dimensions.columns))
    {
        if (row == 0u)
        {
            address = column;
        }
        else
        {
            address = LINE2_START_ADDRESS + column;
        }

        success = Lcd_SetDdramAddress(address);
    }

    return success;
}

bool LcdControl_ClearDisplay(void)
{
    bool success = false;
    success = Lcd_SetConfig(LcdConfOption_CLR_DISP);
    return success;
}

void LcdControl_ProcessLcd(void)
{
    uint8_t character;
    bool success;
#ifndef NO_BUFFERING
    if (_buffer.numberInBuffer > 0)
    {
        success = CircularBuffer_Get(&character, &_buffer);
        if (success)
        {
            success = Lcd_WriteCharacter(character);

            if (_buffer.numberInBuffer > 0)
            {
                EnqueueEvent(EventType_LCD);
            }
        }
    }
#endif
}