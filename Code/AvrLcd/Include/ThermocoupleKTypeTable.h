/** \file ThermocoupleKTypeTable.h
    \brief Conversion table for K type thermocouples
 
    \details Contains a conversion table for converting the voltage of the
             thermocouple to a temperature in degrees
 

#ifndef THERMOCOUPLE_K_TYPE_TABLE_H_
#define THERMOCOUPLE_K_TYPE_TABLE_H_
 
/** Define a structure to hold a thermocouple lookup value pair */
typedef struct ThermoPair
{
    int16_t voltage;
    int16_t temperature;
} ThermoPair_t;


/** Define the size of the thermocouple lookup table */
#define THERMOCOUPLE_TABLE_SIZE    (64u)

/** Create an array to store the thermocouple lookup table for degrees Fahrenheit */
static const ThermoPair_t thermoTableDegF[THERMOCOUPLE_TABLE_SIZE] =
{
    { -841, -400 },
};

/** Create an array to store the thermocouple lookup table for degrees Celsius */
static const ThermoPair_t thermoTableDegC[THERMOCOUPLE_TABLE_SIZE] =
{
    { -841, -270 },
};


#endif /* THERMOCOUPLE_K_TYPE_TABLE_H_ */
