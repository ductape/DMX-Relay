/** \file Uart.h
    \brief Module for the hardware UART driver

    \details Defines the configuration and accessor functions for the serial UART port
 */

/** INCLUDES */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "Uart.h"

/**** LOCAL DEFINITIONS ****/

/**** LOCAL VARIABLES ****/
static RxData_t _rxData = { 0x00, 0x00 };
static volatile bool _dataReady = false;

/**** LOCAL FUNCTION PROTOTYPES ****/

/**** LOCAL FUNCTIONS ****/

/** Initialize the UART port.

    Initialize the UART port to run at 250Kbaud based on an 8MHz system clock
    8 data bits, no parity, 2 stop bits asynchronous serial.
*/
void SerialInit(void)
{

	/* set the TX pin to be an output */
	DDRD |= (1<<PIND1);
	/* set the RX pin to be an input */
	DDRD &= ~(1<<PIND0);

	/* Set the baud rate register ((F_CPU / BAUD / 16) - 1) */
	/* UBRR0L = 0x0C (12) at 4800 baud, 1MHz CPU works */
	/* UBRR0L = 0xCF (207) at 2400 baud, 8MHz CPU works */
	/* UBRR0L = 0x67 (103) at 4800 baud, 8MHz CPU works */
	/* UBRR0L = 0x33 (51) at 9600 baud, 8MHz CPU works */
	UBRR0H = 0x00;
	UBRR0L = 0x01; // (1) 250000 baud @ 8MHz

	/* UMSEL01 | UMSEL00 | UPM01 | UPM00 | USBS0 | UCSZ01 | UCSZ00 | UCPOL0 -> UCSR0C
	     7          6        5       4       3       2        1        0
		 7:6 - USART Mode (00=Async, 01=Sync, 10=reserved, 11=SPIM)
		 5:4 - Parity (00=disabled, 01=reserved, 10=Even, 11=Odd)
		 3   - Stop Bit (0=1bit, 1=2bits)
		 2:1 - Character Size (00=5bit, 01=6bit, 10=7bit, 11=8bit) [see UCSZ02 in UCSR0B for 9 bit]
	*/
	UCSR0C = 0x0E; // Asynchronous 8N2

	/* enable USART */
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

	#ifdef RECEIVE_INTERRUPT
	/* enable interrupts on received bytes */
	UCSR0B |= (1 << RXCIE0);
	#endif
}


bool SerialReadByte( RxData_t *rxData )
{
	volatile bool byteAvailable = false;

	if( _dataReady )
	{
		_dataReady = false;
		rxData->data = _rxData.data;
		rxData->statusByte = _rxData.statusByte;
		byteAvailable = true;
	}

	return byteAvailable;
}

void SerialWriteByte( uint8_t byte )
{
	while ( !(UCSR0A & (1 << UDRE0)) )
	{
	}
	UDR0 = byte;
}

void SerialWriteChar( char character )
{
	while ( !(UCSR0A & (1 << UDRE0)) )
	{
	}
	UDR0 = character;
}

void SerialWriteString( char* string )
{
	char* stringPtr = string;

	while( *stringPtr != '\0')
	{
		SerialWriteChar(*stringPtr);
		stringPtr++;
	}
}

void SerialWriteHexByte( uint8_t byte )
{
	static const char const hexString[17] = "0123456789ABCDEF";
    volatile uint8_t nibble = 0;

	/* mask off the upper nibble */
	nibble = (uint8_t)((byte >> 4) & 0x0F);
	SerialWriteChar(hexString[nibble]);

	/* now the lower nibble */
	nibble = (uint8_t)(byte & 0x0F);
	SerialWriteChar(hexString[nibble]);
}

ISR( USART_RX_vect )
{
	_dataReady = true;
	_rxData.statusByte = UCSR0A;
	_rxData.data = UDR0;
}