/**
    \file CircularBuffer.h
    \brief Rotating buffer of information.

    \details The circular buffer provides a way to store a buffer of information that can be
             appended and read from asynchronously. Also called a ring buffer.
*/

#include <ProjectTypes.h>
#include <CircularBuffer.h>

/**** PUBLIC VARIABLES ****/

/**** LOCAL DEFINES ****/

/**** LOCAL CONSTANTS ****/

/**** LOCAL VARIABLES ****/

/**** LOCAL FUNCTION DECLARATIONS ****/

/**** FUNCTION DEFINITIONS ****/

bool CircularBuffer_Add(uint8_t  value, CircularBuffer_t *buffer)
{
    bool couldBeAdded = false;

    if (buffer->numberInBuffer < (buffer->bufferSize - 1u))
    {
        buffer->buffer[buffer->end] = value;
        if (++(buffer->end) >= buffer->bufferSize)
        {
            buffer->end = 0u;
        }
        ++(buffer->numberInBuffer);
        couldBeAdded = true;
    }

    return couldBeAdded;
}

bool CircularBuffer_Get(uint8_t *value, CircularBuffer_t *buffer)
{
    bool couldBeRemoved = false;

    if (buffer->numberInBuffer > 0u)
    {
        *value = buffer->buffer[buffer->start];

        if (++(buffer->start) >= buffer->bufferSize)
        {
            buffer->start = 0u;
        }
        --(buffer->numberInBuffer);
        couldBeRemoved = true;
    }

    return couldBeRemoved;
}

bool CircularBuffer_Peek(uint8_t *value, CircularBuffer_t *buffer)
{
    bool couldBeRemoved = false;

    if (buffer->numberInBuffer > 0u)
    {
        *value = buffer->buffer[buffer->start];
        couldBeRemoved = true;
    }

    return couldBeRemoved;
}