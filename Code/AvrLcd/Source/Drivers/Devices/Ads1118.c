/** \file Ads1118.h
    \brief Hardware driver for the ADS1118 ADC with temperature sensor

    \details Abstracts the hardware specifics for the TI ADS1118 analog
             to digital converter with internal temperature sensor and
             internal voltage reference.
 */
#include <ProjectTypes.h>
#include <Ads1118.h>
#include <SpiMaster.h>
#include <Gpio.h>


/**** LOCAL DEFINITIONS ****/

/** Stores all of the register settings for the ADS1118 configuration register */
typedef enum AdsConfig
{
    AdsConfig_SS = 0x8000,
    AdsConfig__START_SINGLE_SHOT = AdsConfig_SS,
    AdsConfig_MUX2 = 0x4000,
    AdsConfig_MUX1 = 0x2000,
    AdsConfig_MUX0 = 0x1000,
    AdsConfig_MUX_0 = 0x0000,
    AdsConfig_MUX_1 = AdsConfig_MUX0,
    AdsConfig_MUX_2 = AdsConfig_MUX1,
    AdsConfig_MUX_3 = AdsConfig_MUX0 | AdsConfig_MUX1,
    AdsConfig_MUX_4 = AdsConfig_MUX2,
    AdsConfig_MUX_5 = AdsConfig_MUX2 | AdsConfig_MUX0,
    AdsConfig_MUX_6 = AdsConfig_MUX2 | AdsConfig_MUX1,
    AdsConfig_MUX_7 = AdsConfig_MUX2 | AdsConfig_MUX1 | AdsConfig_MUX0,
    AdsConfig__AINp_AIN0_AINn_AIN1 = AdsConfig_MUX_0,
    AdsConfig__AINp_AIN0_AINn_AIN3 = AdsConfig_MUX_1,
    AdsConfig__AINp_AIN1_AINn_AIN3 = AdsConfig_MUX_2,
    AdsConfig__AINp_AIN2_AINn_AIN3 = AdsConfig_MUX_3,
    AdsConfig__AINp_AIN0_AINn_GND  = AdsConfig_MUX_4,
    AdsConfig__AINp_AIN1_AINn_GND  = AdsConfig_MUX_5,
    AdsConfig__AINp_AIN2_AINn_GND  = AdsConfig_MUX_6,
    AdsConfig__AINp_AIN3_AINn_GND  = AdsConfig_MUX_7,
    AdsConfig_PGA2 = 0x0800,
    AdsConfig_PGA1 = 0x0400,
    AdsConfig_PGA0 = 0x0200,
    AdsConfig_PGA_0 = 0x0000,
    AdsConfig_PGA_1 = AdsConfig_PGA0,
    AdsConfig_PGA_2 = AdsConfig_PGA1,
    AdsConfig_PGA_3 = AdsConfig_PGA1 | AdsConfig_PGA0,
    AdsConfig_PGA_4 = AdsConfig_PGA2,
    AdsConfig_PGA_5 = AdsConfig_PGA2 | AdsConfig_PGA0,
    AdsConfig_PGA_6 = AdsConfig_PGA2 | AdsConfig_PGA1,
    AdsConfig_PGA_7 = AdsConfig_PGA2 | AdsConfig_PGA1 | AdsConfig_PGA0,
    AdsConfig__FS_6114 = AdsConfig_PGA_0,
    AdsConfig__FS_4096 = AdsConfig_PGA_1,
    AdsConfig__FS_2048 = AdsConfig_PGA_2,
    AdsConfig__FS_1024 = AdsConfig_PGA_3,
    AdsConfig__FS_0512 = AdsConfig_PGA_4,
    AdsConfig__FS_0256 = AdsConfig_PGA_5,
    AdsConfig_MODE = 0x0100,
    AdsConfig__SINGLE_SHOT_MODE = AdsConfig_MODE,
    AdsConfig_DR2 = 0x0080,
    AdsConfig_DR1 = 0x0040,
    AdsConfig_DR0 = 0x0020,
    AdsConfig_DR_0 = 0x0000,
    AdsConfig_DR_1 = AdsConfig_DR0,
    AdsConfig_DR_2 = AdsConfig_DR1,
    AdsConfig_DR_3 = AdsConfig_DR1 | AdsConfig_DR0,
    AdsConfig_DR_4 = AdsConfig_DR2,
    AdsConfig_DR_5 = AdsConfig_DR2 | AdsConfig_DR0,
    AdsConfig_DR_6 = AdsConfig_DR2 | AdsConfig_DR1,
    AdsConfig_DR_7 = AdsConfig_DR2 | AdsConfig_DR1 | AdsConfig_DR0,
    AdsConfig__DR_008SPS = AdsConfig_DR_0,
    AdsConfig__DR_016SPS = AdsConfig_DR_1,
    AdsConfig__DR_032SPS = AdsConfig_DR_2,
    AdsConfig__DR_064SPS = AdsConfig_DR_3,
    AdsConfig__DR_128SPS = AdsConfig_DR_4,
    AdsConfig__DR_250SPS = AdsConfig_DR_5,
    AdsConfig__DR_475SPS = AdsConfig_DR_6,
    AdsConfig__DR_860SPS = AdsConfig_DR_7,
    AdsConfig_TS_MODE = 0x0010,
    AdsConfig__TEMPERATURE_MODE = AdsConfig_TS_MODE,
    AdsConfig_PULLUP_EN = 0x0008,
    AdsConfig_NOP = 0x0002
} AdsConfig_t;

/**** LOCAL CONSTANTS ****/

/**** LOCAL VARIABLES ****/
static uint16_t _configReg;

/**** LOCAL FUNCTION PROTOTYPES ****/
uint16_t _TransferReg(
        uint16_t regWrite);

/**** LOCAL FUNCTIONS ****/

/* initialize the ADS1118 */
void Ads1118_Init(void)
{
    /* disable the device SPI transfer */
    SET_THERM_SS;

    /* initialize the config register */
    _configReg = (AdsConfig__AINp_AIN2_AINn_AIN3 | AdsConfig__FS_0256 | AdsConfig__DR_008SPS);

    /* use the NOP to save the reg write */
    _TransferReg(_configReg | AdsConfig_NOP);
}


void Ads1118_Read(
        uint16_t *thermocouple,
        uint16_t *coldJunction)
{
    /* TODO: spg - how do you read temperature and the thermocouple
             at the "same" time? Does there need to be a delay between
             switching between temperature and ADC configs? */
}



/** Writes and reads a register from the ADS1118 */
uint16_t _TransferReg(
        uint16_t regWrite)
{
    uint16_t regRead;

    CLEAR_THERM_SS;
    regRead = (uint16_t)SpiMaster_Transfer((uint8_t)(regWrite>>8u));
    regRead = (uint16_t)(regRead<<8u);
    regRead += (uint16_t)SpiMaster_Transfer((uint8_t)(regWrite));
    SET_THERM_SS;

    return regRead;
}