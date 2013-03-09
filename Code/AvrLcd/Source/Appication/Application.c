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

/**** PUBLIC VARIABLES ****/

/**** LOCAL DEFINES ****/
/** Defines the amount to increment the brightness by */
#define BRIGHTNESS_CHANGE   (PWM_MAX_DUTY/8)
/**** LOCAL CONSTANTS ****/

/**** LOCAL VARIABLES ****/
Event_t _eventToProcess = {EventType_Invalid, 0u};
/**** LOCAL FUNCTION DECLARATIONS ****/

/**** FUNCTION DEFINITIONS ****/

void ProcessEvents(void)
{
    volatile bool receivedEvent = false;
    uint16_t pwmDuty;

    /* process the timer ticks */
	ProcessTick();

	/* check if there is an event to process */
    receivedEvent = DequeueEvent(&_eventToProcess);

    if (receivedEvent)
    {
        switch(_eventToProcess.eventType)
        {
            case EventType_1s:
                break;

            case EventType_200ms:
				ProcessLeds();
			    break;

            case EventType_40ms:
                break;

            case EventType_8ms:
                CheckPushButtons();
                if(PushButtonsPressed() & PushButton_UP)
				{
                    pwmDuty = Pwm_GetDuty();
                    if ((pwmDuty + BRIGHTNESS_CHANGE) > PWM_MAX_DUTY)
                    {
                        pwmDuty = PWM_MAX_DUTY;
                    }
                    else
                    {
                        pwmDuty += BRIGHTNESS_CHANGE;
                    }
					Pwm_SetDuty(pwmDuty);
				}
				if(PushButtonsPressed() & PushButton_DOWN)
				{
                    pwmDuty = Pwm_GetDuty();
                    if (pwmDuty < BRIGHTNESS_CHANGE)
                    {
                        pwmDuty = 0u;
                    }
                    else
                    {
                        pwmDuty -= BRIGHTNESS_CHANGE;
                    }
					Pwm_SetDuty(pwmDuty);
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

