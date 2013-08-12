/**
    \file ThermocoupleController.c
    \brief Controls the settings for the thermocouple readings

    \details Manages the settings for and interactions with the  thermocouple
             interface.
 */

#include "ThermocoupleController.h"
#include <ThermocoupleConversion.h>
#include <Ads1118.h>

/**** LOCAL DEFINITIONS ****/

/** Defines the number of times the sample type should be sampled */
#define NUM_SAMPLES    (2u)

/**** LOCAL CONSTANTS ****/

/**** LOCAL VARIABLES ****/

/** Tracks the settings for the ADS1118 */
static AdsConfig_t _adsConfig =
    {
        .dataRate = AdsDataRate_8SPS,
        .fsRange = AdsPga_0p256,
        .inputSetting = AdsMux_AINp_AIN2_AINn_AIN3,
        .pullupEnable = true,
        .sampleTemperature = true
    };

/** Tracks the current temperature and units */
static Temperature_t _temperature =
    {
        .ambient = 0,
        .temp1 = 0,
        .temp2 = 0,
        .units = TemperatureUnit_Fahrenheit
    };

/** Stores the raw data from the ADS1118 */
static ThermConv_t _rawData =
    {
        .cjComp = 0,
        .rawAdc = 0
    };

/** Stores the number of times the current mode has been sampled */
static uint16_t _samples = 0u;

/**** LOCAL FUNCTION PROTOTYPES ****/
static bool _ReadSensor(void);

/**** LOCAL FUNCTIONS ****/

void ThermocoupleController_Init(void)
{
    Ads1118_Init();
    Ads1118_Config(&_adsConfig);
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
    bool newTemperature;

    newTemperature = _ReadSensor();
    if (newTemperature)
    {
        _temperature.ambient = Ads1118_Cj2Celsius(_rawData.cjComp);
        _temperature.temp1 = ThermConvert_Convert(_rawData.rawAdc, _temperature.ambient, _temperature.units);

        temperature->ambient = _temperature.ambient;
        temperature->temp1   = _temperature.temp1;
        temperature->temp2   = _temperature.temp2;
        temperature->units   = _temperature.units;
    }

    return newTemperature;
}

/** Read the thermocouple sensor and update the settings for
    the next reading */
static bool _ReadSensor(void)
{
    uint16_t result;
    bool success = true;

    success = Ads1118_Read(&result);

    if (_adsConfig.sampleTemperature)
    {
        _rawData.cjComp = result;
        if (++_samples >= NUM_SAMPLES)
        {
            _samples = 0u;
            _adsConfig.sampleTemperature = false;
            Ads1118_Config(&_adsConfig);
        }
    }
    else
    {
        _rawData.rawAdc = result;
        if (++_samples >= NUM_SAMPLES)
        {
            _samples = 0u;
            _adsConfig.sampleTemperature = true;
            Ads1118_Config(&_adsConfig);
        }
    }

    return success;
}