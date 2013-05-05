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
#include <ThermocoupleConversion.h>
#include <LcdController.h>
#include <Pwm.h>
#include <string.h>
#include <stdio.h>
#include <Cpu.h>
#include <util/delay.h>
#include <avr/eeprom.h>

/**** PUBLIC VARIABLES ****/

/**** LOCAL DEFINES ****/
/** Defines the amount to increment the brightness by */
#define BRIGHTNESS_CHANGE   (PWM_MAX_DUTY/8)
/**** LOCAL CONSTANTS ****/

/**** LOCAL VARIABLES ****/
static Event_t _eventToProcess = {EventType_Invalid, 0u};
static int16_t _targetTemp = 37;
static int16_t _actualTemperature = -37;

/**** LOCAL FUNCTION DECLARATIONS ****/
void _UpdateTemperature(void);

/**** FUNCTION DEFINITIONS ****/

void ProcessEvents(void)
{
    volatile bool receivedEvent = false;
    uint8_t buttonPressed;
    uint16_t pwmDuty;
	static int16_t adcCount = -826;
	static int16_t EEMEM nonVolTargetTemp = 521l; 
	static uint16_t EEMEM nonVolPwmDuty = PWM_MAX_DUTY; 
	
	/* Initialize the EEPROM memories */
	static bool firstTime = true; 
	if (firstTime)
	{
		firstTime = false; 
		_targetTemp = (int16_t)eeprom_read_word((uint16_t*)&nonVolTargetTemp);
		pwmDuty = eeprom_read_word(&nonVolPwmDuty);
		Pwm_SetDuty(pwmDuty); 
	}

    /* process the timer ticks */
	ProcessTick();

	/* check if there is an event to process */
    receivedEvent = DequeueEvent(&_eventToProcess);

    if (receivedEvent)
    {
        switch(_eventToProcess.eventType)
        {
            case EventType_1s:
				_actualTemperature = ThermConvert_Fahrenheit(adcCount++, 50);
				if (adcCount > 7026)
				{
					adcCount = -826; 
				}					 
				
				/* if the target temperature has changed, update the non-volatile stored value */
				eeprom_update_word((uint16_t*)&nonVolTargetTemp, (uint16_t)_targetTemp);
				/* if the duty cycle has changed, update the non-volatile stored value */
				pwmDuty = Pwm_GetDuty(); 
				eeprom_update_word(&nonVolPwmDuty, pwmDuty);
                break;

            case EventType_200ms:
				ProcessLeds();
                _UpdateTemperature();
			    break;

            case EventType_40ms:
                break;

            case EventType_8ms:
                CheckPushButtons();
                buttonPressed = PushButtonsPressed();
                if(buttonPressed & PushButton_UP)
				{
                    pwmDuty = Pwm_GetDuty();
					pwmDuty = pwmDuty ? (pwmDuty << 1u) : 1u;
					Pwm_SetDuty(pwmDuty);
				}
				else if(buttonPressed & PushButton_DOWN)
				{
					pwmDuty = Pwm_GetDuty() >> 1u;
					Pwm_SetDuty(pwmDuty);
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
    static char_t line1[LCD_COLUMNS];
    static char_t line2[LCD_COLUMNS];

    /* stick the temperature in a string */
    snprintf(line1, LCD_COLUMNS, "Temp:  %5d°F", _actualTemperature);
    snprintf(line2, LCD_COLUMNS, "Target:%5d°F", _targetTemp);

    /* print the string */
    success = LcdControl_SetCursorLocation(0, 0);
    success = LcdControl_WriteString(line1);
    success = LcdControl_SetCursorLocation(1, 0);
    success = LcdControl_WriteString(line2);
}
