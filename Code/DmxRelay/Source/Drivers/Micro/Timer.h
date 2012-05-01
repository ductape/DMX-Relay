/*
 * Timer.h
 *
 * Created: 4/18/2012 9:12:24 PM
 *  Author: Shaun
 */


#ifndef TIMER_H_
#define TIMER_H_

/**** PUBLIC DEFINITIONS ****/

/**** PUBLIC VARIABLES ****/
static volatile bool newTick = false;
static volatile uint8_t tickCount = 0;

/**** DECLARATIONS ****/
void TimerInit(void);



#endif /* TIMER_H_ */