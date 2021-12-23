 /******************************************************************************
 *
 * Module: External EEPROM
 *
 * File Name: external_eeprom.c
 *
 * Description: source file for timer0
 *
 * Author: Shawky Abo El-Ela
 *
 *******************************************************************************/
#include "timer0.h"
#include "avr/io.h"
#include "avr/interrupt.h"
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;


/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(TIMER0_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}

}

ISR(TIMER0_COMP_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}

}


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description: initializing TIMER0 in normal mode or overflow mode
 * depends on what the user choose
 */

void TIMER0_init(const TIMER0_ConfigType * config){

	TCNT0 = config->initial_value;
	/*
	 * non PWM mode
	 * */
	TCCR0 = (1<<FOC0);
	TCCR0 = (TCCR0&~(0x07)) | (config->prescaler);
	 /* if the mode was Compare mode */
    if (config->mode == CTC){
		TCCR0 |= (1 << WGM01);
		TIMSK |= (1<< OCIE0);
		OCR0 = config->comp_value;
    }
    /* if the mode was Normal mode */
    else{
    	TIMSK |= (1<< TOIE0);
    }

}

/*
 * Description: Function to set the Call Back function address.
 */
void TIMER0_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}

/*
 * Description: Function to disable the Timer0
 */
void TIMER0_DeInit(void)
{
	/* Clear All Timer0 Registers */
	TCCR0 = 0;
	TCNT0 = 0;
    OCR0 =0 ;
    TIMSK = 0;

}
