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
	EventType_64ms,
	EventType_1s,
	EventType_Last
} EventType_t;

/* define an event structure to hold event data */
typedef struct Event
{
	EventType_t eventType;
	uint8_t eventData;
} Event_t;

bool EnqueueEvent(const Event_t *event);
bool DequeueEvent(Event_t *event);

bool EventQueueFull(void);
bool EventQueueEmpty(void);
#endif /* EVENTQUEUE_H_ */