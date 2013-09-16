//***************************************************************************
// A P P L I C A T I O N   N O T E   F O R   T H E   A V R   F A M I L Y
//
// Number               : AVR151
// File Name            : "avr151_Master.c"
// Title                : Setup and Use The SPI
// Date                 : 00.09.20
// Version              : 1.0
// Target MCU           : Any AVR with SPI
//
// DESCRIPTION
// This Application note shows how to enable and use the on-board SPI of the 
// AVR's inSlave- and in Slave-Mode. 
//
// This file contains the code of all the examples. To switch between the examples
// you will have to enable the call of the corresponding routines.
// (see the main program at the bottom) 
//
// Modified 2004-10-25 RAA
//
//**************************************************************************

#include "inavr.h"
#include "ioavr.h"

#define  Error   0x01
#define  Success 0x02
char     TransmitState = 0x00;
char*    TextString    = "AVR communicating via the SPI"+0x00;


// Interrupt Routine Slave Mode (interrupt controlled)
#pragma vector=SPI_STC_vect
__interrupt void ISR_SPI (void)
{
        if (SPDR != *TextString)                // Check for transmission errors
        {
                TransmitState = Error;  
                SPCR &= ~(1<<SPIE);             // Disable SPI interrupts
        }
        else 
        {
                TextString++;                   // Set Pointer on next Character
                if (*TextString == 0)           // Check for end of String
                {
                        TransmitState = Success;
                        SPCR &= ~(1<<SPIE);     // Disable SPI interrupts
                }
        }
}

// Intialization Routine Slave Mode (polling)
void Init_Slave (void)
{
        volatile char IOReg;
        // Set PB6(MISO) as output 
        DDRB    = (1<<PB6);
        // Enable SPI in Slave Mode with SCK = CK/4
        SPCR    = (1<<SPE);
        IOReg   = SPSR;                         // Clear SPIF bit in SPSR
        IOReg   = SPDR;
        DDRD	= 0xFF;	                // Set Port D as output
}

// Intialization RoutineSlave Mode (interrupt controlled)
void Init_Slave_IntContr (void)
{
        volatile char IOReg;
        // Set PB6(MISO) as output 
        DDRB    = (1<<PB6);
        // Enable SPI Interrupt and SPI in Slave Mode with SCK = CK/4
        SPCR  = (1<<SPIE)|(1<<SPE);
        IOReg   = SPSR;                         // Clear SPIF bit in SPSR
        IOReg   = SPDR;
        DDRD	= 0xFF;	                // Set Port D as output
        __enable_interrupt();                                 // Enable global interrupts
}



// Receive Routine Slave Mode (interrupt controlled)
void Slave_Receive_IntContr (void)
{
        while (1)
        {
                switch (TransmitState)
                {       // Output Transmit status on Port D
                        case 0x00:    PORTD = 0x00;
                        break;
                        case Error:   PORTD = 0xF0;
                        break;
                        case Success: PORTD = 0xAA;
                        break;
                }
        }
                
}

// Receive Routine Slave Mode (polling)
void Slave_Receive (void)
{
        // Repeat while end of String not reached and no Error occured
        while   ((*TextString != 0) && (TransmitState != Error))
        {
                while (!(SPSR & (1<<SPIF)));    // Wait until Char is received
                                                // Check if Char (Byte) is received correctly 
                if (SPDR  != *TextString) TransmitState = Error;
                TextString++;                   // Set Pointer on next Character
        }
        // output result transmission status on Port D 
        if (TransmitState == Error) PORTD = 0xF0;
        else PORTD = 0xAA;
        while (1);
}


void main (void)
{
                // Enable next two lines for Example 1
         Init_Slave();
         Slave_Receive();
                // Enable next two lines for Example 2
         // Init_Slave_IntContr();
         // Slave_Receive_IntContr();
}

