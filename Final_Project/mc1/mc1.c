 /******************************************************************************
 *
 * Module: External EEPROM
 *
 * File Name: external_eeprom.c
 *
 * Description: main function and the other functions for microcontroller1
 *
 * Author: Shawky Abo El-Ela
 *
 *******************************************************************************/

#include "keypad.h"
#include "lcd.h"
#include "uart.h"
#include "timer0.h"
#include "avr/io.h"
#include "util/delay.h"
#include "mc1.h"

/*******************************************************************************
 *                              Global variables                                 *
 *******************************************************************************/

uint8 g_flag=0; /*this flag will equal 1 if the pass to open door is right*/
uint32 g_tick = 0; /*the ticks the timer will count */
uint8 key = -1,key2;
uint8 pass1[PASS_SIZE],pass2[PASS_SIZE],confirm_pass[PASS_SIZE],confirm_pass2[PASS_SIZE];


/*******************************************************************************
 *                              MAIN Function                                  *
 *******************************************************************************/


int main(void){

	SREG  |= (1<<7);

	LCD_init();

	UART_ConfigType config={EIGHT,DISABLED,ONE,ASYNC_NORMAL_MODE};
	UART_init(9600, &config);

	while(1){
		//do{
			display_step1();
		//}while(g_flag2);

		/* iterate until the password is right*/
		do{
			display_step2();
		}while(!g_flag);

		}

}


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/* Function Description
 * Get_pass function will take the presses keys from the keypad
 * and store them to be compared later  */
void Get_pass(uint8 pass[PASS_SIZE]){
	/* loop for 6 times take the enter with us */
	for (uint8 i = 0; i < (PASS_SIZE+1); ++i) {

		key= KEYPAD_getPressedKey();

		if(key != -1){
			_delay_ms(1500);
			if (i==5 && key == 13){/*after insert the pass must press enter */
				return;
			}
			if(key >=0 && key <= 9 && i != 5){
				pass[i]= key;
				LCD_displayString("*");
			}

		}
		_delay_ms(1500);
	}

}

/* Function Description
 * to send the pass to the other microcontroller*/
void send_pass(uint8 s_pass[PASS_SIZE]){
	for (int var = 0; var < PASS_SIZE; ++var) {
		UART_sendByte(s_pass[var]);
	}
}


/* Function Description
 *  display step1 procedures and make it re-enter the pass if wrong
 * and send the password to MC2*/
void display_step1(void){
	do{
		LCD_clearScreen();
		LCD_moveCursor(0, 0);/* to be in first line*/
		LCD_displayString("enter password: " );
		LCD_moveCursor(1, 0);
		Get_pass(pass1);

		send_pass(pass1);

		/* to clear the previous password*/
		LCD_moveCursor(1, 0);
		LCD_displayString("        ");

		LCD_moveCursor(0, 0);
		LCD_displayString("reenter password:");
		LCD_moveCursor(1, 0);
		Get_pass(pass2);

		send_pass(pass2);

		/* to clear the previous password*/
		LCD_moveCursor(1, 0);
		LCD_displayString("       ");


	}while(!UART_recieveByte());


}

/* Function Description
 * check if the user pass is write */
uint8 check_pass(void){

	uint8 flag = 0; /*to indicate if the pass matching or mismatching*/
	uint8 recieve=0;

    /*for loop
     * to loop 3 times if the user entered the pass wrong and it will beak if it was right
     */

	for (int var = 0; var < 3; ++var) {

		_delay_ms(100);
		LCD_clearScreen();
		LCD_displayString("enter password:");
		LCD_moveCursor(1, 0);
		Get_pass(confirm_pass);

		_delay_ms(50);
		send_pass(confirm_pass);
		_delay_ms(50);


		recieve = UART_recieveByte();
		_delay_ms(50);

		/*at any time the password was right break the loop*/
		if(recieve){
			flag = 1;
			break;
		}
	}

	   return flag;
}

/* Function Description
 *  display step2 procedures and make it re-enter the pass if wrong
 * and send the password to MC2*/
void display_step2(void){

	LCD_clearScreen();
	LCD_moveCursor(0, 0);
	LCD_displayString("+:open door");

	LCD_moveCursor(1, 0);
	LCD_displayString("-:change pass");

	key2 = KEYPAD_getPressedKey();
	_delay_ms(3000);

	/*open door*/
	if(key2 == '+'){
			if(check_pass()){
				UART_sendByte(ready);/* to recognize it is open door operations*/
				_delay_ms(50);
;				UART_sendByte(ready); /*ready to do Dc-motor operations*/
				opening_message();
				g_flag = 1;
			}
			else{
				UART_sendByte(ready);/* to recognize it is open door operations*/
				_delay_ms(50);
				UART_sendByte(!ready);  /*ready to do buzzer operations*/
				error_message();

		    }
	}

	/*change password*/
	if(key2=='-'){
		LCD_clearScreen();
		LCD_displayString("Firstly enter");
		LCD_displayStringRowColumn(1, 0, "Old pass");

		_delay_ms(5000);

		if(check_pass()){
			UART_sendByte(!ready);/* to recognize it is change pass operations operations*/
			_delay_ms(50);
			LCD_clearScreen();
			LCD_displayString("enter your ");
			LCD_moveCursor(1, 0);
			LCD_displayString("new password");
			_delay_ms(5000);
			g_flag = 1;


		}
		else{
			UART_sendByte(ready);/* to recognize it is change pass operations*/
			_delay_ms(50);
			UART_sendByte(!ready); /*ready to do buzzer operations*/
			error_message();

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
	TIMER0_ConfigType config = {NORMAL,0,250,F_CPU_1024};
	TIMER0_init(&config);

	TIMER0_setCallBack(timer_tick);

	while(g_tick  < tick);

	TIMER0_DeInit();
}

/* Function Description
 * error message when mismatch happens 3 times*/
void error_message(void){
	LCD_clearScreen();
	LCD_displayString("Incorrect pass");
	wait(60); /* 60 seconds */
}

/* Function Description
 * opening message when match happens */
void opening_message(void){
	LCD_clearScreen();
	LCD_displayString("Opening door...");
	wait(33); /* 33 seconds until the motor stops*/
}

