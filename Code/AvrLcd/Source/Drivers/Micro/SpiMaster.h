/** \file SpiMaster.h
    \brief Hardware driver for the SPI master port

    \details Abstracts the hardware specifics for the SPI Master
             full duplex port
 */


#ifndef SPIMASTER_H_
#define SPIMASTER_H_

/**** PUBLIC DEFINITIONS ****/

/**** PUBLIC CONSTANTS ******/

/**** PUBLIC FUNCTIONS ******/
void    SpiMaster_Init(void);

uint8_t SpiMaster_Transfer(
                  uint8_t writeByte);

void    SpiMaster_TransferArray(
                  uint8_t readBytes[],
            const uint8_t writeBytes[],
                  uint8_t numberBytes);

#endif /* SPIMASTER_H_ */