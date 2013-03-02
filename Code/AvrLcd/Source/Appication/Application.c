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

/**** PUBLIC VARIABLES ****/

/**** LOCAL DEFINES ****/

/**** LOCAL CONSTANTS ****/

/**** LOCAL VARIABLES ****/
Event_t _eventToProcess = {EventType_Invalid, 0u};
/**** LOCAL FUNCTION DECLARATIONS ****/

/**** FUNCTION DEFINITIONS ****/

void ProcessEvents(void)
{
    volatile bool receivedEvent = false;

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
                if(PushButtonsPressed() & PushButton_0)
				{
					SetLedPattern(LedPattern_BlinkThrice, Led_10, false);
				}
				if(PushButtonsReleased() & PushButton_0)
				{
					SetLedPattern(LedPattern_BlinkThrice, Led_9, false);
				}
                break;

            default:
                break;
        }
    }
}

