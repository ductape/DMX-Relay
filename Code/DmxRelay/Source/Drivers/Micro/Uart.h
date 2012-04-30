/*
 * Utilities.h
 *
 * Created: 2/19/2012 8:33:12 PM
 *  Author: Shaun
 */ 


#ifndef UTILITIES_H_
#define UTILITIES_H_

#define RECEIVE_INTERRUPT

void SerialInit(void); 
void SerialWriteByte( uint8_t byte ); 
void SerialWriteString( uint8_t* string ); 
void SerialPrintInt(int16_t number); 




#endif /* UTILITIES_H_ */