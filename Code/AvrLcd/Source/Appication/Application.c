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
#include <ThermocoupleController.h>
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

/** Defines how long a push button should be pressed before accelerating
    the increment/decrement. */
#define PUSH_BUTTON_COUNT_THRESHOLD    (125u)
#define PUSH_BUTTON_COUNT_FAST_THRESHOLD    (254u)

/**** LOCAL CONSTANTS ****/

/**** LOCAL VARIABLES ****/
static Event_t _eventToProcess =
    {
        .eventType = EventType_Invalid,
        .eventCallback = NULL
    };
static int16_t _targetTemp = 37;
static Temperature_t _temperature;

/**** LOCAL FUNCTION DECLARATIONS ****/
void _UpdateTemperature(void);
static inline void _HandlePushButtonUp(void);
static inline void _HandlePushButtonDown(void);
static inline void _HandlePushButtonLeft(void);
static inline void _HandlePushButtonRight(void);

/**** FUNCTION DEFINITIONS ****/

void ProcessEvents(void)
{
    volatile bool receivedEvent = false;
    uint8_t buttonPressed;
    uint16_t pwmDuty;
	static int16_t EEMEM nonVolTargetTemp = 521l;
	static uint16_t EEMEM nonVolPwmDuty = PWM_MAX_DUTY;
	static bool everyOther40ms;

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
				/* Only update the non-volatile memory if the push buttons aren't pressed to
				   keep from updating the memory too much */
				if (PushButtonState() == 0)
				{
					/* if the target temperature has changed, update the non-volatile stored value */
					eeprom_update_word((uint16_t*)&nonVolTargetTemp, (uint16_t)_targetTemp);
					/* if the duty cycle has changed, update the non-volatile stored value */
					pwmDuty = Pwm_GetDuty();
					eeprom_update_word(&nonVolPwmDuty, pwmDuty);
				}
                ThermocoupleController_Read(&_temperature);
                TOGGLE_THERM_SS;
                break;

            case EventType_200ms:
				ProcessLeds();
                _UpdateTemperature();

				if (PushButtonCount(PushButton_UP) > PUSH_BUTTON_COUNT_THRESHOLD)
				{
					_HandlePushButtonUp();
				}

				if (PushButtonCount(PushButton_DOWN) > PUSH_BUTTON_COUNT_THRESHOLD)
				{
					_HandlePushButtonDown();
				}
				break;

            case EventType_40ms:
				everyOther40ms = !everyOther40ms;

				if (everyOther40ms)
				{
					if (PushButtonCount(PushButton_LEFT) > PUSH_BUTTON_COUNT_FAST_THRESHOLD)
					{
						_HandlePushButtonLeft();
					}

					if (PushButtonCount(PushButton_RIGHT) > PUSH_BUTTON_COUNT_FAST_THRESHOLD)
					{
						_HandlePushButtonRight();
					}
				}
                break;

            case EventType_8ms:
                CheckPushButtons();
                buttonPressed = PushButtonsPressed();
                if(buttonPressed & PushButton_UP)
				{
					_HandlePushButtonUp();
				}
				else if(buttonPressed & PushButton_DOWN)
				{
					_HandlePushButtonDown();
				}

                if(buttonPressed & PushButton_RIGHT & PushButton_LEFT)
                {

                }
                else if(buttonPressed & PushButton_LEFT)
                {
					_HandlePushButtonLeft();
                }
                else if(buttonPressed & PushButton_RIGHT)
                {
					_HandlePushButtonRight();
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
    snprintf(line1, LCD_COLUMNS, "T:%5d°F A:%5d°F", _temperature.temp1, _temperature.ambient);
    snprintf(line2, LCD_COLUMNS, "Target:%5d°F", _targetTemp);

    /* print the string */
    success = LcdControl_SetCursorLocation(0, 0);
    success = LcdControl_WriteString(line1);
    success = LcdControl_SetCursorLocation(1, 0);
    success = LcdControl_WriteString(line2);
}

static inline void _HandlePushButtonUp(void)
{
	uint16_t pwmDuty;
	pwmDuty = Pwm_GetDuty();
	pwmDuty = pwmDuty ? (pwmDuty << 1u) : 1u;
	Pwm_SetDuty(pwmDuty);
}

static inline void _HandlePushButtonDown(void)
{
	uint16_t pwmDuty;
	pwmDuty = Pwm_GetDuty() >> 1u;
	Pwm_SetDuty(pwmDuty);
}

static inline void _HandlePushButtonLeft(void)
{
	--_targetTemp;
}

static inline void _HandlePushButtonRight(void)
{
	++_targetTemp;
}