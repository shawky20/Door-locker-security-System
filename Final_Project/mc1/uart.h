 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Shawky abo el-ela
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

/*this enum made to choose number of data tobe sent in UART*/
typedef enum{
	FIVE,SIX,SEVEN,EIGHT,RESERVED1,RESERVED2,RESERVED3,NINE
}UART_CharacterSize;


typedef enum{
	DISABLED,RESERVED_1,ENABLE_EVEN,ENABLE_ODD
}UART_ParityMode; /* to choose which parity mode */

typedef enum{
	ONE,TWO
}UART_StopBit; /*to choose how much number of stop bits  */

typedef enum{
	SYNC_MASTER_MODE=1,ASYNC_DOUBLE_MODE=4,ASYNC_NORMAL_MODE=8
}UART_BitRate; /* to choose the suitable BAUD RATE*/

typedef struct{
	UART_CharacterSize  CharacterSize;
	UART_ParityMode    ParityMode;
	UART_StopBit       StopBit;
	UART_BitRate     BitRate;
}UART_ConfigType;



/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(uint32 baud_rate,UART_ConfigType * ConfigType);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
