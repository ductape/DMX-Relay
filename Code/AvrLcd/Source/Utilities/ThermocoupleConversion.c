/*
 * ThermocoupleConversion.c
 *
 * Created: 5/2/2013 8:54:27 PM
 *  Author: Shaun
 */ 

#include <ProjectTypes.h>
#include <ThermocoupleConversion.h>
#include <ThermocoupleKTypeTable.h>

#define _USE_COLD_JUNCTION_COMP

typedef struct ConversionData
{
	ThermoPair_t high; 
	ThermoPair_t low; 
} ConversionData_t;


static ConversionData_t _convDataComp = 
{
	{0u, 0u},
	{0u, 0u}
};

static ConversionData_t _convDataVolt =
{
	{0u, 0u},
	{0u, 0u}
};

static void _FindIndexTemperature(int16_t temperature, ConversionData_t *data);
static void _FindIndexVoltage(int16_t voltage, ConversionData_t *data); 
static int16_t _VoltageToTemperature(int16_t voltage, const ConversionData_t *data);
static int16_t _TemperatureToVoltage(int16_t temperature, const ConversionData_t *data); 

int16_t ThermConvert_Fahrenheit(const ThermConv_t *conv)
{
	int16_t temperature; 
	int16_t voltage; 
	#ifdef _USE_COLD_JUNCTION_COMP
		_FindIndexTemperature(conv->cjComp, &_convDataComp); 
		voltage = _TemperatureToVoltage(conv->cjComp, &_convDataComp); 
		voltage += conv->rawAdc;
	#else
		voltage = conv->rawAdc;
	#endif
	_FindIndexVoltage(voltage, &_convDataVolt); 
	temperature = _VoltageToTemperature(voltage, &_convDataVolt); 
	return temperature; 
}


int16_t ThermConvert_Celsius(const ThermConv_t *conv)
{
	int16_t temperature = 0; 
	
	/* TODO: implement a Celsius handler. */	
	
	return temperature; 
}

static void _FindIndexTemperature(int16_t temperature, ConversionData_t *data)
{
	uint8_t counter; 
	
	for (counter = 1u; counter < (THERMOCOUPLE_TABLE_SIZE); ++counter)
	{
		if ((temperature >= thermoTableDegF[counter - 1u].temperature) &&
		    (temperature <= thermoTableDegF[counter].temperature))
			{
				break; 
			}
	}
	
	data->high.temperature = thermoTableDegF[counter].temperature; 
	data->high.voltage     = thermoTableDegF[counter].voltage;
	data->low.temperature  = thermoTableDegF[counter - 1u].temperature;
	data->low.voltage      = thermoTableDegF[counter - 1u].voltage;
}

static void _FindIndexVoltage(int16_t voltage, ConversionData_t *data)
{
	uint8_t counter;
	
	for (counter = 1u; counter < (THERMOCOUPLE_TABLE_SIZE); ++counter)
	{
		if ((voltage >= thermoTableDegF[counter - 1u].voltage) &&
			(voltage <= thermoTableDegF[counter].voltage))
		{
			break;
		}
	}
	
	data->high.temperature = thermoTableDegF[counter].temperature;
	data->high.voltage     = thermoTableDegF[counter].voltage;
	data->low.temperature  = thermoTableDegF[counter - 1u].temperature;
	data->low.voltage      = thermoTableDegF[counter - 1u].voltage;
}


static int16_t _VoltageToTemperature(int16_t voltage, const ConversionData_t *data)
{
	int16_t temperature; 
	int32_t numerator; 
	int32_t denominator; 
	
	numerator = (voltage - data->low.voltage) * (data->high.temperature - data->low.temperature); 
	denominator = data->high.voltage - data->low.voltage; 
	temperature = (int16_t)(numerator/denominator);
	temperature += data->low.temperature;
	
	return temperature; 
}

static int16_t _TemperatureToVoltage(int16_t temperature, const ConversionData_t *data)
{
	int16_t voltage; 
	int32_t numerator; 
	int32_t denominator; 
	
	numerator = (temperature - data->low.temperature) * (data->high.voltage - data->low.voltage); 
	denominator = data->high.temperature - data->low.temperature; 
	voltage = (int16_t)(numerator/denominator);
	voltage += data->low.voltage;
	
	return voltage;
}