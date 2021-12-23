 /******************************************************************************
 *
 * Module: External EEPROM
 *
 * File Name: external_eeprom.c
 *
 * Description: main function and the other functions for  microcontroller2
 *
 * Author: Shawky Abo El-Ela
 *
 *******************************************************************************/


#include "buzzer.h"
#include "uart.h"
#include "dc_motor.h"
#include "twi.h"
#include "external_eeprom.h"
#include "timer0.h"
#include "util/delay.h"
#include "avr/io.h"
#include "gpio.h"
#include "mc2.h"


/*******************************************************************************
 *                              Global variables                                 *
 *******************************************************************************/

uint8 g_flag=0;  /*this flag will equal 1 if the pass to open door is right*/
uint32 g_tick = 0; /*the ticks the timer will count */
uint8 pass[PASS_SIZE]={0},re_pass[PASS_SIZE]={0},
      confirm_pass1[PASS_SIZE]={0}, confirm_pass2[PASS_SIZE]={0};/* password stored in eeprom*/

/*******************************************************************************
 *                              MAIN Function                                  *
 *******************************************************************************/

int main(void){

	SREG  |= (1<<7);

	I2c_ConfigType config2 = {400,0x00000001};
	/* Initialize the TWI/I2C Driver */
	TWI_init(&config2);

	BUZZER_init();

	UART_ConfigType config={EIGHT,DISABLED,ONE_1,ASYNC_NORMAL_MODE};
	UART_init(9600, &config);

	DcMotor_Init();



	while(1){

	//	do{
			pass_matching();
	//	}while(g_flag2);
		/* iterate until the password is right*/
		do{
			pass_matching2();

			if(UART_recieveByte()){
				if(UART_recieveByte()){
					dc_motor_operations();
				}
				else{
					buzzer_operations();
				}
			}
		}while(!g_flag);

	}
}


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*  Function Description
 *  receive the password from microcontroller1*/
void recieve_pass(uint8 r_pass[PASS_SIZE]){
	for (int var = 0; var < PASS_SIZE; ++var) {
		r_pass[var]=UART_recieveByte();
	}
}

/*  Function Description
 *  save the pass in the eeprom */
void store_pass(void){
	for (int var = 0; var < PASS_SIZE; ++var) {
		EEPROM_writeByte((0x0311+var), pass[var]);
		_delay_ms(100);
	}
}

/* Function Description
 * read the password from the eeprom*/
void return_pass(uint8 re_pass[PASS_SIZE]){
	for (int var = 0; var < PASS_SIZE; ++var) {
		EEPROM_readByte((0x0311+var), &re_pass[var]);
		_delay_ms(200);
	}
}

/* Function Description
 * check if the two passwords match */
uint8 match(uint8 p[PASS_SIZE], uint8 p2[PASS_SIZE]){
	uint8 flag = 1; /* assume they match */
	for (int var = 0; var < PASS_SIZE; ++var) {
		if(p[var]!=p2[var]){
			flag = 0;
		}
	}

	return flag;
}

/* Function Description
 * check if the 2 passwords are the same and store them in the eeprom for displaystep1 */
void pass_matching(void){
	do{
		recieve_pass(pass);
		_delay_ms(50);
		recieve_pass(re_pass);

		if(match(pass,re_pass)){
			store_pass();

			UART_sendByte(ready);/*to confirm they match*/
		}
		else{
			UART_sendByte(!ready);
		}
	}while(!match(pass,re_pass));

}

/* Function Description
 * check if the confirmation password and password stored in the eeprom are matching */
void pass_matching2(void){

	    /*for loop
	     * to loop 3 times if the user entered the pass wrong and it will beak if it was right */
		for (int var = 0; var < 3; ++var) {
			recieve_pass(confirm_pass1);
			_delay_ms(50);
			return_pass(confirm_pass2);

			/*if confirm at any time will break the loop*/
			if(match(confirm_pass1,confirm_pass2)){
				UART_sendByte(ready);
				_delay_ms(50);
				g_flag = 1;
				break;

			}
			else{
				UART_sendByte(!ready);
				_delay_ms(50);
			}
		}

}

/* Function Description
 * call back function that increase the tick every call*/
void timer_tick(void){
	g_tick++;
}

/* Function Description
 * wait until specified time in seconds */
void wait(uint32 seconds){

	g_tick = 0;
	uint32 tick = seconds*31;/*the seconds multiplied in the number of ticks to complete 1 second */
	TIMER0_ConfigType config = {NORMAL,0,250,F_CPU1024};
	TIMER0_init(&config);

	TIMER0_setCallBack(timer_tick);

	while(g_tick  < tick);

	TIMER0_DeInit();
}

/* Function Description
 * the operations the dc motor will make when match happens
 * */
void dc_motor_operations(void){

	DcMotor_Rotate(DC_MOTOR_CW);
	wait(15);
	DcMotor_Rotate(DC_MOTOR_STOP);
	wait(3);
	DcMotor_Rotate(DC_MOTOR_ACW);
	wait(15);
	DcMotor_Rotate(DC_MOTOR_STOP);

}


/* Function Description
 * the operations the buzzer will make when mismatch happens
 * */
void buzzer_operations(void){
	BUZZER_on();
	wait(60); /* 60 seconds */
	BUZZER_off();

}
