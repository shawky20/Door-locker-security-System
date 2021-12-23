 /******************************************************************************
 *
 * Module: External EEPROM
 *
 * File Name: external_eeprom.c
 *
 * Description: header file for  microcontroller2
 *
 * Author: Shawky Abo El-Ela
 *
 *******************************************************************************/
#ifndef MC2_H_
#define MC2_H_


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define PASS_SIZE 5
#define ready  1


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*  Function Description
 *  receive the password from microcontroller1*/
void recieve_pass(uint8 r_pass[PASS_SIZE]);

/*  Function Description
 *  save the pass in the eeprom */
void store_pass(void);

/* Function Description
 * read the password from the eeprom*/
void return_pass(uint8 re_pass[PASS_SIZE]);

/* Function Description
 * check if the two passwords match */
uint8 match(uint8 p[PASS_SIZE], uint8 p2[PASS_SIZE]);


/* Function Description
 * check if the 2 passwords are the same and store them in the eeprom */
void pass_matching(void);

/* Function Description
 * check if the confirmation password and password stored in the eeprom are matching */
void pass_matching2(void);

/* Function Description
 * call back function that increase the tick every call*/
void timer_tick(void);

/* Function Description
 * wait until specified time in seconds */
void wait(uint32 seconds);

/* Function Description
 * the operations the dc motor will make when match happens
 * */
void dc_motor_operations(void);

/* Function Description
 * the operations the buzzer will make when mismatch happens
 * */
void buzzer_operations(void);




#endif /* MC2_H_ */
