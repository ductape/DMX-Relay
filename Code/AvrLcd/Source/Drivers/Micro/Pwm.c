/** \file Pwm.c
    \brief Allows for setting the PWM output

    \details Abstracts the hardware specifics for the PWM driver
 */
#include <ProjectTypes.h>
#include <Pwm.h>


/**** LOCAL DEFINITIONS ****/

/**** LOCAL CONSTANTS ****/


/**** LOCAL VARIABLES ****/


/**** LOCAL FUNCTION PROTOTYPES ****/


/**** LOCAL FUNCTIONS ****/

/** Initializes the PWM output */
void Pwm_Init(void)
{
#ifdef USE_TIMER_1
    /* Set output to clear on compare match, 10-bit FAST PWM, OC1A */
    TCCR1A = 0b10000011;
    /* Set to output clear on compare match, 10-bit FAST PWM, OC1A, CLK/1 source */
    TCCR1B = 0b00001001;
    /* Use almost 100% duty */
    OCR1A = PWM_MAX_DUTY;
#endif
}

void Pwm_SetDuty(uint16_t duty)
{
#ifdef USE_TIMER_1
    if (duty > PWM_MAX_DUTY)
    {
        duty = PWM_MAX_DUTY;
    }
    OCR1A = duty;
#endif
}

uint16_t Pwm_GetDuty(void)
{
#ifdef USE_TIMER_1
    return OCR1A;
#endif
}