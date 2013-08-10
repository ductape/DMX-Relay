/*
 * ThermocoupleConversion.h
 *
 * Created: 4/28/2013 8:13:50 PM
 *  Author: Shaun
 */


#ifndef THERMOCOUPLECONVERSION_H_
#define THERMOCOUPLECONVERSION_H_

#include <Temperature.h>

/** Defines a structure that holds all of the information necessary to
    linearly interpolate a thermocouple temperature */
typedef struct ThermConv
{
	int16_t rawAdc; /** The raw ADC conversion from the thermocouple */
	int16_t cjComp; /** The temperature of the cold junction to compensate for (in Celsius) */
} ThermConv_t;

int16_t ThermConvert_Convert(
        int16_t rawAdc,
        int16_t cjComp,
        TemperatureUnit_t units);

#endif /* THERMOCOUPLECONVERSION_H_ */