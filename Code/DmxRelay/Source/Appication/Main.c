/**
    \file Main.c
    \brief The main file for the DMX Relay control project

    \details The DMX relay control project is based on an Atmel ATmega168A
             and will accept a DMX signal as serial input and output the
             DMX channel on relays.
*/

#define NUM_CHAN 9
#define START_CHAN 1

/* define PC_MODE to enable terminal simulation
   of the DMX signals. */
//#define PC_MODE

/* define debug to print the output to the terminal */
//#define DEBUG

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "Serial.h"
#include "Cpu.h"
#include "Gpio.h"
#include "Timer.h"

uint8_t ShiftCharacter(uint8_t character)
{
	uint8_t newValue;
	switch(character)
	{
		case 0x0D:  // carriage return
			newValue = 0x0A; // use line feed (with implicit CR
			break;

		default:
			newValue = character + 1;
			break;
	}

	return newValue;
}

/** RxData is a structure that will hold the information received from the serial port. */
typedef struct
{
	volatile bool received;         /** ??? */
	volatile uint8_t statusByte;    /** The status byte with error codes from the UART */
	uint8_t data;                   /** The actual data recieved from the UART */
} RxData;

RxData rxData;
volatile uint8_t rx;

ISR(USART_RX_vect)
{
	rxData.received = true;
	rxData.statusByte = UCSR0A;
	rxData.data = UDR0;
}

int main (void)
{
	CpuConfig();
	GpioInit();
	TimerInit();
	SerialInit();
	sei();

	volatile int16_t channel = 0; // the active dmx channel
	uint8_t dmxChannel[NUM_CHAN];

	while (1) {

		if (rxData.received)
		{
            rx = rxData.data;
			rxData.received= false;
            channel++;

            #ifdef DEBUG
            //SerialWriteByte(rx);
            #endif

			if( rxData.statusByte & (1<<FE0))
			{
                /* reset the channel counter on frame error */
				channel = -1;
                #ifdef DEBUG
				SerialWriteString("reset\n");
                #endif
			}
			else
			{
                #ifdef DEBUG
				SerialWriteString("chan=");
				SerialPrintInt(channel);
				SerialWriteString(", lev=");
				SerialPrintInt(rx);
				SerialWriteString("\n");
                #endif

                #ifdef PC_MODE
                if(rx > 96)
                #else
                if(rx > 128)
                #endif
                {
                    switch(channel)
                    {
                        case 0:
                            SET_LED0;
                            break;
                        case 1:
                            SET_LED1;
                            break;
                        case 2:
                            SET_LED2;
                            break;
                        case 3:
                            SET_LED3;
                            break;
                        case 4:
                            SET_LED4;
                            break;
                        case 5:
                            SET_LED5;
                            break;
                        case 6:
                            SET_LED6;
                            break;
                        case 7:
                            SET_LED7;
                            break;
                        case 8:
                            SET_LED8;
                            break;
                        default:
                            break;
                    }
                }
                else
                {
                    switch(channel)
                    {
                        case 0:
                            CLEAR_LED0;
                            break;
                        case 1:
                            CLEAR_LED1;
                            break;
                        case 2:
                            CLEAR_LED2;
                            break;
                        case 3:
                            CLEAR_LED3;
                            break;
                        case 4:
                            CLEAR_LED4;
                            break;
                        case 5:
                            CLEAR_LED5;
                            break;
                        case 6:
                            CLEAR_LED6;
                            break;
                        case 7:
                            CLEAR_LED7;
                            break;
                        case 8:
                            CLEAR_LED8;
                            break;
                        default:
                            break;
                    }
                }

				#ifdef PC_MODE
				if( channel >= NUM_CHAN )
				{
					channel = 0;
				}
				#endif
			}
		}

	}
	return 0;
}
