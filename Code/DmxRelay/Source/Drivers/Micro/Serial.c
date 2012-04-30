/*
 * Serial.c
 *
 * Created: 2/19/2012 8:35:50 PM
 *  Author: Shaun
 */ 

/** INCLUDES */
#include <avr/io.h>
#include "Serial.h"

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

void SerialWriteByte( uint8_t byte )
{
	while ( !(UCSR0A & (1 << UDRE0)) )
	{
	}
	UDR0 = byte;
}
void SerialWriteString( uint8_t* string )
{
	uint8_t* stringPtr = string; 
	
	while( *stringPtr != '\0')
	{
		SerialWriteByte(*stringPtr); 
		stringPtr++; 
	}
}

void SerialPrintInt(int16_t number)
{
	uint8_t* valueToWrite[7]; //maximum size of a 16 bit integer + sign + \c
	itoa(number, &valueToWrite, 10); 
	SerialWriteString(valueToWrite); 
	
}