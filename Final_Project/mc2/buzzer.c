 /******************************************************************************
 *
 * Module: Common - Macros
 *
 * File Name: Common_Macros.h
 *
 * Description: source file for buzzer
 *
 * Author:  Shawky Abo El-Ela
 *
 *******************************************************************************/

#include "buzzer.h"
#include "gpio.h"


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * set the direction of the BUZZER pin
 */
void BUZZER_init(){
	GPIO_setupPinDirection(BUZZER_PORT_ID , BUZZER_PIN_ID, PIN_OUTPUT);
	/*initialy OFF */
	GPIO_writePin(BUZZER_PORT_ID , BUZZER_PIN_ID,LOGIC_LOW);
}

/*
 * Description :
 * turn on the buzzer
 */
void BUZZER_on(void){
	GPIO_writePin(BUZZER_PORT_ID ,BUZZER_PIN_ID,LOGIC_HIGH);
}

/*
 * Description :
 * turn off the buzzer
 */
void BUZZER_off(void){
	GPIO_writePin(BUZZER_PORT_ID , BUZZER_PIN_ID,LOGIC_LOW);
}

