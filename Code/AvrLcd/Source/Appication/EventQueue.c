/** \file EventQueue.h
    \brief The application's event queue

    \details Defines and stores the events for the application to process
 */

#include "ProjectTypes.h"
#include "EventQueue.h"
#include <Util/atomic.h>

/**** PUBLIC VARIABLES ****/

/**** LOCAL DEFINITIONS ****/

/** Define the size of the queue. Define it 1 larger than needed because the
    queue can only be filled to size - 1 */
#define QUEUE_SIZE 11u

/**** LOCAL VARIABLES ****/
static Event_t  _queue[QUEUE_SIZE];
static uint8_t  _start             = 0u;
static uint8_t  _end               = 0u;
static uint8_t  _numberInQueue     = 0u;

/**** LOCAL FUNCTION DECLARATIONS ****/

/**** FUNCTION DEFINITIONS ****/

/** What happens if this is called from an ISR while its being
    called from application space? */
bool EnqueueEvent(EventType_t eventType)
{
	bool couldBeAdded = false;

    ATOMIC_BLOCK(ATOMIC_FORCEON)
    {
	    if (EventQueueFull() == false)
	    {
            _queue[_end].eventType = eventType;
	        _queue[_end].eventCallback = NULL;

	        if (++_end >= QUEUE_SIZE)
	        {
		        _end = 0;
	        }
	        _numberInQueue++;
		    couldBeAdded = true;
	    }
    }
	return couldBeAdded;
}

/** Dequeues events from the event queue and returns the
    event data for processing.  
    
    \NOTE never call this from an interrupt! As long
    as this function is never called from an interrupt
    atomic operations are not necessary 
*/
bool DequeueEvent(Event_t *event)
{
	bool couldBeRemoved = false;

	if (EventQueueEmpty() == false)
	{
		event->eventType = _queue[_start].eventType;
		event->eventCallback = _queue[_start].eventCallback;

		if (++_start >= QUEUE_SIZE)
		{
			_start = 0;
		}
		_numberInQueue--;
		couldBeRemoved = true;
	}

	return couldBeRemoved;
}

/** Adds an event with an event callback to be processed. 
*/
bool EnqueCallback(EventCallback_t callback)
{
    bool couldBeAdded = false;

    ATOMIC_BLOCK(ATOMIC_FORCEON)
    {
        if (EventQueueFull() == false)
        {
            _queue[_end].eventType = EventType_Invalid;
            _queue[_end].eventCallback = callback;

            if (++_end >= QUEUE_SIZE)
            {
                _end = 0;
            }
            _numberInQueue++;
            couldBeAdded = true;
        }
    }
    return couldBeAdded;    
}

/** The queue is full when there are SIZE - 1 elements. If there were
    SIZE elements the start would overlap the end and overwrite the
    event there.
*/
bool EventQueueFull(void)
{
    return _numberInQueue >= (QUEUE_SIZE - 1);
}

bool EventQueueEmpty(void)
{
	return _numberInQueue == 0;
}

