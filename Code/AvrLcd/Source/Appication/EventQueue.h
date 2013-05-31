/** \file EventQueue.h
    \brief Header file for the application's event queue

    \details Defines and stores the events for the application to process
 */


#ifndef EVENTQUEUE_H_
#define EVENTQUEUE_H_


/**** PUBLIC DEFINITIONS ****/

/** Define the event types that can be generated and processed */
typedef enum EventType
{
	EventType_Invalid = -1,
	EventType_First   = 0,
    EventType_8ms     = EventType_First,
	EventType_40ms,
	EventType_200ms,
	EventType_1s,
    EventType_LCD,
	EventType_Last
} EventType_t;

/** Defines an event callback */
typedef void (*EventCallback_t)(void);

/* define an event structure to hold event data */
typedef struct Event
{
	EventType_t eventType;
	EventCallback_t eventCallback;
} Event_t;

/**** PUBLIC FUNCTIONS ****/
bool EnqueueEvent(EventType_t eventType);
bool DequeueEvent(Event_t *event);

bool EnqueCallback(EventCallback_t callback); 

bool EventQueueFull(void);
bool EventQueueEmpty(void);
#endif /* EVENTQUEUE_H_ */