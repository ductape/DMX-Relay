/** \file Uart.h
    \brief Header file for the hardware UART driver

    \details Defines the configuration and accessor functions for the serial UART port
 */


#ifndef UTILITIES_H_
#define UTILITIES_H_

/**** PUBLIC DEFINITIONS ****/
#define RECEIVE_INTERRUPT

/** Structure to hold the received UART information */
typedef struct RxData
{
	volatile uint8_t data;
	volatile uint8_t statusByte;
} 	RxData_t;

/**** PUBLIC FUNCTION PROTOTYPES ****/
void SerialInit(void);

bool SerialReadByte( RxData_t *rxData );

void SerialWriteByte( uint8_t byte );
void SerialWriteChar( char character);
void SerialWriteString( char* string );
void SerialWriteHexByte( uint8_t byte );




#endif /* UTILITIES_H_ */