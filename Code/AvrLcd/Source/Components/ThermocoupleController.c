/**
	\file ThermocoupleController.c
	\brief Controls the settings for the thermocouple readings
	
	\details Manages the settings for and interactions with the  thermocouple
	         interface. 
 */ 

#include "ThermocoupleController.h"
#include <ThermocoupleKTypeTable.h>
#include <Ads1118.h>

/**** LOCAL DEFINITIONS ****/

/**** LOCAL CONSTANTS ****/

/**** LOCAL VARIABLES ****/

/** Tracks the settings for the ADS1118 */
static AdsConfig_t _adsConfig; 

/** Tracks the current temperature and units */
static Temperature_t _temperature; 

/**** LOCAL FUNCTION PROTOTYPES ****/

/**** LOCAL FUNCTIONS ****/

void ThermocoupleController_Init(void)
{
	Ads1118_Init();
}

void ThermocoupleController_SetTempUnits(TemperatureUnit_t units)
{
	_temperature.units = units;
}

TemperatureUnit_t ThermocoupleController_GetTempUnits(void)
{
	return _temperature.units; 
}

bool ThermocoupleController_Read(Temperature_t *temperature)
{
	
}