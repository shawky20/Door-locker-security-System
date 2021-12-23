 /******************************************************************************
 *
 * Module: External EEPROM
 *
 * File Name: external_eeprom.c
 *
 * Description: header file for  microcontroller1
 *
 * Author: Shawky Abo El-Ela
 *
 *******************************************************************************/

#ifndef MC1_H_
#define MC1_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define PASS_SIZE 5
#define ready  1

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/* Function Description
 * Get_pass function will take the presses keys from the keypad
 * and store them to be compared later  */
void Get_pass(uint8 pass[PASS_SIZE]);

/* Function Description
 * to send the pass to the other microcontroller*/
void send_pass(uint8 s_pass[PASS_SIZE]);

/* Function Description
 *  display step1 procedures and make it re-enter the pass if wrong
 * and send the password to MC2*/
void display_step1(void);

/* Function Description
 * check if the user pass is write */
uint8 check_pass(void);

/* Function Description
 *  display step2 procedures and make it re-enter the pass if wrong
 * and send the password to MC2*/
void display_step2(void);

/* Function Description
 * call back function that increase the tick every call*/
void timer_tick(void);

/* Function Description
 * wait until specified time in seconds */
void wait(uint32 seconds);

/* Function Description
 * error message when mismatch happens 3 times*/
void error_message(void);

/* Function Description
 * opening message when match happens */
void opening_message(void);

#endif /* MC1_H_ */
