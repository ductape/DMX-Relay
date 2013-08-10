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

/************* LOCAL FUNCTION DECLARATIONS *******************/

static void _FindIndexTemperature(
        int16_t temperature,
        ConversionData_t *data,
        TemperatureUnit_t units);
static void _FindIndexVoltage(
        int16_t voltage,
        ConversionData_t *data,
        TemperatureUnit_t units);
static int16_t _VoltageToTemperature(
        int16_t voltage,
        const ConversionData_t *data);
static int16_t _TemperatureToVoltage(
        int16_t temperature,
        const ConversionData_t *data);

/*********** PUBLIC FUNCTION DEFINITIONS ********************/

/**
    Converts a raw ADC count to a temperature in specified units.

    \param[in] rawAdc - the raw ADC count to convert to temperature
    \param[in] cjComp - the cold junction compensation factor in Celsius
    \returns the temperature of the ADC in Fahrenheit
*/
int16_t ThermConvert_Convert(
        int16_t rawAdc,
        int16_t cjComp,
        TemperatureUnit_t units)
{
    int16_t temperature;
    int16_t voltage;
    #ifdef _USE_COLD_JUNCTION_COMP
        _FindIndexTemperature(cjComp, &_convDataComp, TemperatureUnit_Celsius);
        voltage = _TemperatureToVoltage(cjComp, &_convDataComp);
        voltage += rawAdc;
    #else
        voltage = rawAdc;
    #endif
    _FindIndexVoltage(voltage, &_convDataVolt, units);
    temperature = _VoltageToTemperature(voltage, &_convDataVolt);
    return temperature;
}

/*************** LOCAL FUNCTION DEFINITIONS **************************/

/**
    Finds the nearest range in the lookup table that includes the
    temperature and loads the lookup table data into the data structure.

    \param[in] temperature - temperature (in Celsius) to convert
    \param[out] data - the conversion data structure to put the lookup data in
*/
static void _FindIndexTemperature(
        int16_t temperature,
        ConversionData_t *data,
        TemperatureUnit_t units)
{
    uint8_t counter;
    const ThermoPair_t *thermoTable;

    if (units == TemperatureUnit_Fahrenheit)
    {
        thermoTable = thermoTableDegF;
    }
    else
    {
        thermoTable = thermoTableDegC;
    }

    for (counter = 1u; counter < (THERMOCOUPLE_TABLE_SIZE); ++counter)
    {
        if ((temperature >= thermoTable[counter - 1u].temperature) &&
            (temperature <= thermoTable[counter].temperature))
            {
                break;
            }
    }

    data->high.temperature = thermoTable[counter].temperature;
    data->high.voltage     = thermoTable[counter].voltage;
    data->low.temperature  = thermoTable[counter - 1u].temperature;
    data->low.voltage      = thermoTable[counter - 1u].voltage;
}

/**
    Finds the nearest range in the lookup table that includes the
    voltage and loads the lookup table data into the data structure.

    \param[in] voltage - the voltage to convert to temperature units
    \param[out] data - the conversion data structure to put the lookup data in
*/
static void _FindIndexVoltage(
        int16_t voltage,
        ConversionData_t *data,
        TemperatureUnit_t units)
{
    uint8_t counter;
    const ThermoPair_t *thermoTable;

    if (units == TemperatureUnit_Fahrenheit)
    {
        thermoTable = thermoTableDegF;
    }
    else
    {
        thermoTable = thermoTableDegC;
    }

    for (counter = 1u; counter < (THERMOCOUPLE_TABLE_SIZE); ++counter)
    {
        if ((voltage >= thermoTable[counter - 1u].voltage) &&
            (voltage <= thermoTable[counter].voltage))
        {
            break;
        }
    }

    data->high.temperature = thermoTable[counter].temperature;
    data->high.voltage     = thermoTable[counter].voltage;
    data->low.temperature  = thermoTable[counter - 1u].temperature;
    data->low.voltage      = thermoTable[counter - 1u].voltage;
}

/**
    Converts a voltage to temperature based on the data in the conversion structure

    \note The units of the result are based on the units of the data in the
          data structure. I.e. if the data is from a Fahrenheit table, the temperature
          result will be in Fahrenheit.

    \param[in] voltage - the voltage of the thermocouple
    \param[in] data - the data points to interpolate between for the voltage
    \returns the temperature interpolated between the data points
*/
static int16_t _VoltageToTemperature(
        int16_t voltage,
        const ConversionData_t *data)
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

/**
    Converts a temperature to a voltage based on the data in the conversion structure

    \note The units of the result are based on the units of the data in the
          data structure.  I.e. If the temperature is in Fahrenheit, the data should be from
          a Fahrenheit table.

    \param[in] temperature - the temperature to convert
    \param[in] data - the data points to interpolate between for the temperature
    \returns the voltage interpolated between the data points
*/
static int16_t _TemperatureToVoltage(
        int16_t temperature,
        const ConversionData_t *data)
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

