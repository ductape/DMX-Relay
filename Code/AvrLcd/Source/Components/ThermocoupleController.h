/**
	\file ThermocoupleController.h
	\brief Controls the settings for the thermocouple readings
	
	\details Manages the settings for and interactions with the  thermocouple
	         interface. 
 */ 


#ifndef THERMOCOUPLECONTROLLER_H_
#define THERMOCOUPLECONTROLLER_H_

#include <ProjectTypes.h>

/**** PUBLIC DEFINITIONS ****/

typedef enum TemperatureUnit
{
	TemperatureUnit_Celsius,
	TemperatureUnit_Fahrenheit
} TemperatureUnit_t;

typedef struct Temperature
{
	int16_t ambient;
	int16_t temp1;
	int16_t temp2;
	TemperatureUnit_t units;
} Temperature_t;

/**** PUBLIC CONSTANTS ******/

/**** PUBLIC FUNCTIONS ******/


void ThermocoupleController_Init(void); 

void ThermocoupleController_SetTempUnits(TemperatureUnit_t units); 
TemperatureUnit_t ThermocoupleController_GetTempUnits(void); 

bool ThermocoupleController_Read(Temperature_t *temperature); 



#endif /* THERMOCOUPLECONTROLLER_H_ */