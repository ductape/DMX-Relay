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

/**** LOCAL DEFINITIONS ****/
#define LCD_BUFFER_LENGTH   (32u)

/**** LOCAL VARIABLES ****/
uint8_t _bufferData[LCD_BUFFER_LENGTH];

static CircularBuffer_t _buffer =
{
    0u,
    0u,
    0u,
    LCD_BUFFER_LENGTH,
    _bufferData
};

/**** LOCAL FUNCTION PROTOTYPES ****/

/**** LOCAL FUNCTIONS ****/

bool LcdControl_WriteString(const char* string)
{
    bool success = false;
    uint8_t strlength;
    uint8_t index;

    strlength = strlen(string);

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

    return success;
}

bool LcdControl_SetCursorLocation(uint8_t character, uint8_t line)
{
    bool success = false;
    return success;
}

bool LcdControl_ClearDisplay(void)
{
    bool success = false;
    return success;
}

void LcdControl_ProcessLcd(void)
{
    static const Event_t event =
    {
        EventType_LCD,
        0u
    };
    uint8_t character;
    bool success;

    if (_buffer.numberInBuffer > 0)
    {
        success = CircularBuffer_Get(&character, &_buffer);
        if (success)
        {
            success = Lcd_WriteCharacter(character);

            if (_buffer.numberInBuffer > 0)
            {
                EnqueueEvent(&event);
            }
        }
    }
}