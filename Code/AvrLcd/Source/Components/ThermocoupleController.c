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
        .units = TemperatureUnit_Celsius
    };

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
    bool newTemperatureAvailable = false;

    temperature->ambient = _temperature.ambient;
    temperature->temp1   = _temperature.temp1;
    temperature->temp2   = _temperature.temp2;
    temperature->units   = _temperature.units;

    return newTemperatureAvailable;
}

/** Read the thermocouple sensor and update the settings for
    the next reading */
static bool _ReadSensor(void)
{
    bool success;
    uint16_t result;

    success = Ads1118_Read(&result);

    return success;
}