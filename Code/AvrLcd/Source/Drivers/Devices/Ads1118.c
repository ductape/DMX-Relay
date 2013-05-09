/** \file Ads1118.h
    \brief Hardware driver for the ADS1118 ADC with temperature sensor

    \details Abstracts the hardware specifics for the TI ADS1118 analog
             to digital converter with internal temperature sensor and
             internal voltage reference.
 */
#include <ProjectTypes.h>
#include <Ads1118.h>
#include <SpiMaster.h>
#include <avr/interrupt.h>
#include <Gpio.h>


/**** LOCAL DEFINITIONS ****/

/** Stores all of the register settings for the ADS1118 configuration register */
typedef enum AdsRegConfig
{
    AdsRegConfig_SS = 0x8000,
    AdsRegConfig__START_SINGLE_SHOT = AdsRegConfig_SS,
    AdsRegConfig_MUX2 = 0x4000,
    AdsRegConfig_MUX1 = 0x2000,
    AdsRegConfig_MUX0 = 0x1000,
    AdsRegConfig_MUX_0 = 0x0000,
    AdsRegConfig_MUX_1 = AdsRegConfig_MUX0,
    AdsRegConfig_MUX_2 = AdsRegConfig_MUX1,
    AdsRegConfig_MUX_3 = AdsRegConfig_MUX0 | AdsRegConfig_MUX1,
    AdsRegConfig_MUX_4 = AdsRegConfig_MUX2,
    AdsRegConfig_MUX_5 = AdsRegConfig_MUX2 | AdsRegConfig_MUX0,
    AdsRegConfig_MUX_6 = AdsRegConfig_MUX2 | AdsRegConfig_MUX1,
    AdsRegConfig_MUX_7 = AdsRegConfig_MUX2 | AdsRegConfig_MUX1 | AdsRegConfig_MUX0,
    AdsRegConfig__AINp_AIN0_AINn_AIN1 = AdsRegConfig_MUX_0,
    AdsRegConfig__AINp_AIN0_AINn_AIN3 = AdsRegConfig_MUX_1,
    AdsRegConfig__AINp_AIN1_AINn_AIN3 = AdsRegConfig_MUX_2,
    AdsRegConfig__AINp_AIN2_AINn_AIN3 = AdsRegConfig_MUX_3,
    AdsRegConfig__AINp_AIN0_AINn_GND  = AdsRegConfig_MUX_4,
    AdsRegConfig__AINp_AIN1_AINn_GND  = AdsRegConfig_MUX_5,
    AdsRegConfig__AINp_AIN2_AINn_GND  = AdsRegConfig_MUX_6,
    AdsRegConfig__AINp_AIN3_AINn_GND  = AdsRegConfig_MUX_7,
    AdsRegConfig_PGA2 = 0x0800,
    AdsRegConfig_PGA1 = 0x0400,
    AdsRegConfig_PGA0 = 0x0200,
    AdsRegConfig_PGA_0 = 0x0000,
    AdsRegConfig_PGA_1 = AdsRegConfig_PGA0,
    AdsRegConfig_PGA_2 = AdsRegConfig_PGA1,
    AdsRegConfig_PGA_3 = AdsRegConfig_PGA1 | AdsRegConfig_PGA0,
    AdsRegConfig_PGA_4 = AdsRegConfig_PGA2,
    AdsRegConfig_PGA_5 = AdsRegConfig_PGA2 | AdsRegConfig_PGA0,
    AdsRegConfig_PGA_6 = AdsRegConfig_PGA2 | AdsRegConfig_PGA1,
    AdsRegConfig_PGA_7 = AdsRegConfig_PGA2 | AdsRegConfig_PGA1 | AdsRegConfig_PGA0,
    AdsRegConfig__FS_6114 = AdsRegConfig_PGA_0,
    AdsRegConfig__FS_4096 = AdsRegConfig_PGA_1,
    AdsRegConfig__FS_2048 = AdsRegConfig_PGA_2,
    AdsRegConfig__FS_1024 = AdsRegConfig_PGA_3,
    AdsRegConfig__FS_0512 = AdsRegConfig_PGA_4,
    AdsRegConfig__FS_0256 = AdsRegConfig_PGA_5,
    AdsRegConfig_MODE = 0x0100,
    AdsRegConfig__SINGLE_SHOT_MODE = AdsRegConfig_MODE,
    AdsRegConfig_DR2 = 0x0080,
    AdsRegConfig_DR1 = 0x0040,
    AdsRegConfig_DR0 = 0x0020,
    AdsRegConfig_DR_0 = 0x0000,
    AdsRegConfig_DR_1 = AdsRegConfig_DR0,
    AdsRegConfig_DR_2 = AdsRegConfig_DR1,
    AdsRegConfig_DR_3 = AdsRegConfig_DR1 | AdsRegConfig_DR0,
    AdsRegConfig_DR_4 = AdsRegConfig_DR2,
    AdsRegConfig_DR_5 = AdsRegConfig_DR2 | AdsRegConfig_DR0,
    AdsRegConfig_DR_6 = AdsRegConfig_DR2 | AdsRegConfig_DR1,
    AdsRegConfig_DR_7 = AdsRegConfig_DR2 | AdsRegConfig_DR1 | AdsRegConfig_DR0,
    AdsRegConfig__DR_008SPS = AdsRegConfig_DR_0,
    AdsRegConfig__DR_016SPS = AdsRegConfig_DR_1,
    AdsRegConfig__DR_032SPS = AdsRegConfig_DR_2,
    AdsRegConfig__DR_064SPS = AdsRegConfig_DR_3,
    AdsRegConfig__DR_128SPS = AdsRegConfig_DR_4,
    AdsRegConfig__DR_250SPS = AdsRegConfig_DR_5,
    AdsRegConfig__DR_475SPS = AdsRegConfig_DR_6,
    AdsRegConfig__DR_860SPS = AdsRegConfig_DR_7,
    AdsRegConfig_TS_MODE = 0x0010,
    AdsRegConfig__TEMPERATURE_MODE = AdsRegConfig_TS_MODE,
    AdsRegConfig_PULLUP_EN = 0x0008,
    AdsRegConfig_NOP = 0x0002
} AdsRegConfig_t;

/** Defines the variable type to store the register bits in */
typedef uint16_t AdsRegister; 

/**** LOCAL CONSTANTS ****/

/**** LOCAL VARIABLES ****/
static AdsRegister _configReg;
static TemperatureDataCallback _tempCallback = NULL;
static AdcDataCallback _adcCallback = NULL;

/**** LOCAL FUNCTION PROTOTYPES ****/
static uint16_t _TransferReg(
        AdsRegister regWrite);
static void _ReadSensor(void); 

/**** LOCAL FUNCTIONS ****/

/* initialize the ADS1118 */
void Ads1118_Init(void)
{
    /* disable the device SPI transfer */
    SET_THERM_SS;

    /* initialize the config register */
    _configReg = (AdsRegConfig__AINp_AIN2_AINn_AIN3 | AdsRegConfig__FS_0256 | AdsRegConfig__DR_008SPS);

    /* use the NOP to save the reg write */
    _TransferReg(_configReg | AdsRegConfig_NOP);
}

void Ads1118_Config(
		const AdsConfig_t *config)
{
	_configReg = 0u;
	_configReg |= ((AdsRegister)(config->inputSetting)) * AdsRegConfig_MUX0;
	_configReg |= ((AdsRegister)(config->fsRange)) * AdsRegConfig_PGA0;
	_configReg |= ((AdsRegister)(config->dataRate)) * AdsRegConfig_DR0;
	_configReg |= ((AdsRegister)(config->pullupEnable)) * AdsRegConfig_PULLUP_EN;
	_configReg |= ((AdsRegister)(AdsRegConfig_MODE));			
}
		
void Ads1118_RegisterTempISR( void* callback)
{
	_tempCallback = callback; 
}

void Ads1118_ClearTempISR(void)
{
	_tempCallback = NULL;
}

void Ads1118_RegisterAdcISR( void* callback)
{
	_adcCallback = callback;
}

void Ads1118_ClearAdcISR(void)
{
	_adcCallback = NULL;
}

void Ads1118_Start(void)
{
	/* send config + start sample + nop */
	/* Set DRDY (MISO) as input */
	/* enable PCINT4 */
}

void Ads1118_Stop(void)
{
	/* disable PCINT4 */
}

/** Writes and reads a register from the ADS1118 */
static uint16_t _TransferReg(
        AdsRegister regWrite)
{
    uint16_t regRead;

    CLEAR_THERM_SS;
    regRead = (uint16_t)SpiMaster_Transfer((uint8_t)(regWrite>>8u));
    regRead = (uint16_t)(regRead<<8u);
    regRead += (uint16_t)SpiMaster_Transfer((uint8_t)(regWrite));
    SET_THERM_SS;

    return regRead;
}

static void _ReadSensor(void)
{
	/* call SPI to read the sensor data */
	/* Change between temp/adc if necessary */
	/* start next sample conversion */
	/* call proper callback with data */
	/* re-enable PCINT4 for the next sample */
}

ISR(PCINT0_vect)
{
	/* disable PCINT4 */
	/* post event for handling read sensor */
}