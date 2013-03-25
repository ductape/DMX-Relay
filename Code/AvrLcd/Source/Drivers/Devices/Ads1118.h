/** \file Ads1118.h
    \brief Hardware driver for the ADS1118 ADC with temperature sensor

    \details Abstracts the hardware specifics for the TI ADS1118 analog
             to digital converter with internal temperature sensor and
             internal voltage reference.
 */


#ifndef ADS1118_H_
#define ADS1118_H_

/**** PUBLIC DEFINITIONS ****/

/**** PUBLIC CONSTANTS ******/

/**** PUBLIC FUNCTIONS ******/
void    Ads1118_Init(void);
void    Ads1118_Read(
            uint16_t *thermocouple,
            uint16_t *coldJunction);



#endif /* ADS1118_H_ */