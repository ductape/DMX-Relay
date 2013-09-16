/** \file SpiMaster.h
    \brief Hardware driver for the SPI master port

    \details Abstracts the hardware specifics for the SPI Master
             full duplex port
 */
#include <ProjectTypes.h>
#include <SpiMaster.h>
#include <avr/io.h>


/**** LOCAL DEFINITIONS ****/

/**** LOCAL CONSTANTS ****/


/**** LOCAL VARIABLES ****/


/**** LOCAL FUNCTION PROTOTYPES ****/


/**** LOCAL FUNCTIONS ****/

/* initialize the SPI Master port */
void SpiMaster_Init(void)
{
    volatile uint8_t IOReg;

    #if 0
    /* GPIO should already be initialized in gpio.h */
    /* Enable SPI, Master, clock rate fcpu/4
        MSB first, CPOL idle low, sample falling/trailing */
    SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0) | (1<<CPHA);
    #else
    // set PB2(/SS), PB3(MOSI), PB5(SCK) as output
    DDRB  |= (1<<PB2)|(1<<PB3)|(1<<PB5);
    // enable SPI in Master Mode with SCK = CK/4
    SPCR    = (1<<SPE)|(1<<MSTR);
    IOReg   = SPSR;                     // clear SPIF bit in SPSR
    IOReg   = SPDR;
    #endif
}

uint8_t SpiMaster_Transfer(
            uint8_t writeByte)
{
    uint8_t readByte;

    /* start transmission */
    SPDR = writeByte;

    /* wait for transmission complete */
    while (!(SPSR & (1<<SPIF)));

    /* read the returned value */
    readByte = SPDR;
    return readByte;
}