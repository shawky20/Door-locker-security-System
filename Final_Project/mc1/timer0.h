 /******************************************************************************
 *
 * Module: External EEPROM
 *
 * File Name: external_eeprom.c
 *
 * Description: header file for timer0
 *
 * Author: Shawky Abo El-Ela
 *
 *******************************************************************************/

#ifndef TIMER0_H_
#define TIMER0_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

typedef enum{
	NORMAL,CTC=2
}TIMER0_Mode;

typedef enum{
	STOP,NO_PRESCALER,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}TIMER0_Prescaler;

typedef struct{
	TIMER0_Mode mode; /* initial mode*/
	uint8 initial_value;
	uint8 comp_value;
	TIMER0_Prescaler prescaler;
}TIMER0_ConfigType;

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/*
 * Description: initializing TIMER0 in normal mode or overflow mode
 * depends on what the user choose
 */

void TIMER0_init(const TIMER0_ConfigType * config);

/*
 * Description: Function to set the Call Back function address.
 */

void TIMER0_setCallBack(void(*a_ptr)(void));

/*
 * Description: Function to disable the Timer0
 */
void TIMER0_DeInit(void);


#endif /* TIMER0_H_ */
