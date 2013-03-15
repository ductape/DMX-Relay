/**
    \file Application.c
    \brief The header file for the Application module.

    \details The Application module will manage the application features of the project.
*/

#include "ProjectTypes.h"
#include "Application.h"
#include "EventQueue.h"
#include "Gpio.h"
#include "Timer.h"
#include "PushButton.h"
#include "Led.h"
#include <LcdController.h>
#include <Pwm.h>
#include <string.h>
#include <stdio.h>
#include <Cpu.h>
#include <util/delay.h>

/**** PUBLIC VARIABLES ****/

/**** LOCAL DEFINES ****/
/** Defines the amount to increment the brightness by */
#define BRIGHTNESS_CHANGE   (PWM_MAX_DUTY/8)
/**** LOCAL CONSTANTS ****/

/**** LOCAL VARIABLES ****/
Event_t _eventToProcess = {EventType_Invalid, 0u};
int16_t _targetTemp = 37;

/**** LOCAL FUNCTION DECLARATIONS ****/
void _UpdateTemperature(void);

/**** FUNCTION DEFINITIONS ****/

void ProcessEvents(void)
{
    volatile bool receivedEvent = false;
    uint16_t pwmDuty;
    uint8_t buttonPressed;

    /* process the timer ticks */
	ProcessTick();

	/* check if there is an event to process */
    receivedEvent = DequeueEvent(&_eventToProcess);

    if (receivedEvent)
    {
        switch(_eventToProcess.eventType)
        {
            case EventType_1s:
                _UpdateTemperature();
                break;

            case EventType_200ms:
				ProcessLeds();
			    break;

            case EventType_40ms:
                break;

            case EventType_8ms:
                CheckPushButtons();
                buttonPressed = PushButtonsPressed();
                if(buttonPressed & PushButton_UP)
				{
                    pwmDuty = Pwm_GetDuty();
					Pwm_SetDuty(pwmDuty ? (pwmDuty << 1u) : 1u);
				}
				else if(buttonPressed & PushButton_DOWN)
				{
					Pwm_SetDuty(Pwm_GetDuty() >> 1u);
				}

                if(buttonPressed & PushButton_RIGHT & PushButton_LEFT)
                {

                }
                else if(buttonPressed & PushButton_LEFT)
                {
                    --_targetTemp;
                }
                else if(buttonPressed & PushButton_RIGHT)
                {
                    ++_targetTemp;
                }
                break;

            case EventType_LCD:
                LcdControl_ProcessLcd();
                break;

            default:
                break;
        }
    }
}

void _UpdateTemperature(void)
{
    bool success;
    int16_t temp;
    static uint8_t line1[LCD_COLUMNS];
    static uint8_t line2[LCD_COLUMNS];

    /* get the temperature */
    temp = -37;

    /* stick the temperature in a string */
    snprintf(line1, LCD_COLUMNS, "Temp:  %5d", temp);
    snprintf(line2, LCD_COLUMNS, "Target:%5d", _targetTemp);

    /* print the string */
    success = LcdControl_SetCursorLocation(0, 0);
    success = LcdControl_WriteString(line1);
    success = LcdControl_SetCursorLocation(1, 0);
    success = LcdControl_WriteString(line2);
}
