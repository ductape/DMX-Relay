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

/**** PUBLIC VARIABLES ****/

/**** LOCAL DEFINES ****/

/**** LOCAL CONSTANTS ****/

/**** LOCAL VARIABLES ****/
Event_t eventToProcess = {EventType_Invalid, 0u};
/**** LOCAL FUNCTION DECLARATIONS ****/

/**** FUNCTION DEFINITIONS ****/

void ProcessEvents(void)
{
    volatile bool receivedEvent = false;

    /* process the timer ticks */
	ProcessTick();

	/* check if there is an event to process */
    receivedEvent = DequeueEvent(&eventToProcess);

    if (receivedEvent)
    {
        switch(eventToProcess.eventType)
        {
            case EventType_1s:
                break;

            case EventType_200ms:
			    TOGGLE_LED0;
			    break;

            case EventType_40ms:
                break;

            case EventType_8ms:
                break;

            default:
                break;
        }
    }
}

