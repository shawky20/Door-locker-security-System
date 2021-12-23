 /******************************************************************************
 *
 * Module: Common - Macros
 *
 * File Name: Common_Macros.h
 *
 * Description: header file for buzzer
 *
 * Author:  Shawky Abo El-Ela
 *
 *******************************************************************************/
#ifndef BUZZER_H_
#define BUZZER_H_

#include "std_types.h"


/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

#define BUZZER_PORT_ID PORTD_ID
#define BUZZER_PIN_ID  PIN2_ID


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


/*
 * Description :
 * set the direction of the BUZZER pin
 */

void BUZZER_init();

/*
 * Description :
 * turn on the buzzer
 */

void BUZZER_on(void);

/*
 * Description :
 * turn off the buzzer
 */
void BUZZER_off(void);

#endif /* BUZZER_H_ */
