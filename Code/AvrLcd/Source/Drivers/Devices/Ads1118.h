/** \file Ads1118.h
    \brief Hardware driver for the ADS1118 ADC with temperature sensor

    \details Abstracts the hardware specifics for the TI ADS1118 analog
             to digital converter with internal temperature sensor and
             internal voltage reference.
 */


#ifndef ADS1118_H_
#define ADS1118_H_

#include <ProjectTypes.h>

/**** PUBLIC DEFINITIONS ****/

/** Defines the input connection configuration for the ADS1118 chip */
typedef enum AdsMux
{
	AdsMux_INVALID = -1,
	AdsMux_FIRST   = 0u,
	AdsMux_AINp_AIN0_AINn_AIN1 = AdsMux_FIRST,	/** Differential, analog input 0 is positive and analog input 1 is negative */
	AdsMux_AINp_AIN0_AINn_AIN3,					/** Differential, analog input 0 is positive and analog input 3 is negative */
	AdsMux_AINp_AIN1_AINn_AIN3,					/** Differential, analog input 1 is positive and analog input 3 is negative */
	AdsMux_AINp_AIN2_AINn_AIN3,					/** Differential, analog input 2 is positive and analog input 3 is negative */
	AdsMux_AINp_AIN0_AINn_GND,					/** Single ended, analog input 0 is positive and ground is negative */
	AdsMux_AINp_AIN1_AINn_GND,					/** Single ended, analog input 1 is positive and ground is negative */
	AdsMux_AINp_AIN2_AINn_GND,					/** Single ended, analog input 2 is positive and ground is negative */
	AdsMux_AINp_AIN3_AINn_GND,					/** Single ended, analog input 3 is positive and ground is negative */
	AdsMux_LAST
} AdsMux_t;

/** Defines the input voltage sensing range of the ADS1118 programmable gain amplifier */
typedef enum AdsPga
{
	AdsPga_INVALID = -1,
	AdsPga_FIRST   = 0u,
	AdsPga_6p144   = AdsPga_FIRST,	/** Input voltage range is ±6.144V */
	AdsPga_4p096,					/** Input voltage range is ±4.096V */
	AdsPga_2p048,					/** Input voltage range is ±2.048V */
	AdsPga_1p024,					/** Input voltage range is ±1.024V */
	AdsPga_0p512,					/** Input voltage range is ±0.512V */
	AdsPga_0p256,					/** Input voltage range is ±0.256V */
	AdsPga_LAST
} AdsPga_t;

/** Defines the data rate options of the ADS1118 */
typedef enum AdsDataRate
{
	AdsDataRate_INVALID = -1,
	AdsDataRate_FIRST   = 0u,
	AdsDataRate_8SPS  = AdsDataRate_FIRST,	/** The sample rate will be 8Hz   */
	AdsDataRate_16SPS,						/** The sample rate will be 16Hz  */
	AdsDataRate_32SPS,						/** The sample rate will be 32Hz  */
	AdsDataRate_64SPS,						/** The sample rate will be 64Hz  */
	AdsDataRate_128SPS,						/** The sample rate will be 128Hz */
	AdsDataRate_250SPS,						/** The sample rate will be 250Hz */
	AdsDataRate_475SPS,						/** The sample rate will be 475Hz */
	AdsDataRate_860SPS,						/** The sample rate will be 860Hz */
	AdsDataRate_LAST
} AdsDataRate_t;

/** Defines a structure that stores all of the configuration settings of for the
    ADS1118 */
typedef struct AdsConfig
{
	AdsMux_t inputSetting;	/** Selects which input pins to sample */
	AdsPga_t fsRange;		/** Selects what voltage range the signal will be in */
	AdsDataRate_t dataRate;	/** Selects what rate to sample the signal at */
	bool pullupEnable;		/** Selects if the ADS1118 uses its internal pullup on the Data Out/nData Ready pin */
	bool sampleTemperature; /** Selects if the temperature should also be read, i.e. for cold junction temperature compensation */
} AdsConfig_t;

/**** PUBLIC CONSTANTS ******/

/**** PUBLIC FUNCTIONS ******/
void Ads1118_Init(void);
void Ads1118_Config(
		const AdsConfig_t *config);
				
bool Ads1118_Read(uint16_t *result); 

#endif /* ADS1118_H_ */