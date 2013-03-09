/** \file Pwm.h
    \brief Allows for setting the PWM output

    \details Abstracts the hardware specifics for the PWM driver
 */



#ifndef PWM_H_
#define PWM_H_


/**** PUBLIC DEFINITIONS ****/
#define USE_TIMER_1

/** Defines the maximum value allowable for the PWM output */
#define PWM_MAX_DUTY    (1023u)

/**** PUBLIC CONSTANTS ******/

/**** PUBLIC FUNCTIONS ******/
void Pwm_Init(void);
void Pwm_SetDuty(uint16_t duty);
uint16_t Pwm_GetDuty(void);


#endif /* PWM_H_ */