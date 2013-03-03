/**
    \file CircularBuffer.h
    \brief The header file for the Circular Buffer

    \details The circular buffer provides a way to store a buffer of information that can be
             appended and read from asynchronously.
*/


#ifndef CIRCULARBUFFER_H_
#define CIRCULARBUFFER_H_

typedef struct CircularBuffer
{
    uint8_t start;
    uint8_t end;
    uint8_t numberInBuffer;
    const uint8_t  bufferSize;
    uint8_t *buffer;
} CircularBuffer_t;

bool CircularBuffer_Add(uint8_t  value, CircularBuffer_t *buffer);
bool CircularBuffer_Get(uint8_t *value, CircularBuffer_t *buffer);


#endif /* CIRCULARBUFFER_H_ */