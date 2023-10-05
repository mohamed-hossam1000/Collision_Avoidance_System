 /******************************************************************************
 *
 * Project : Collision Avoidance System
 *
 * File Name: MCU_1.c
 *
 * Description: measure the distance using Ultrasonic sensor HC-SR04 and send it
 * 				to MCU_2 via UART
 *
 * Author: Mohamed Hossam
 *
 *******************************************************************************/
#include"ultrasonic.h"
#include"uart.h"
#include<avr/io.h>
#include<util/delay.h>

#define SAFE_DISTANCE	51
#define MCU2_READY		0x45

int main()
{
	uint16 distance;
	/* UART configuration and initialization */
	UART_configType uartConfig;
	uartConfig.baudRate 		= 9600;
	uartConfig.character_size 	= EIGHT_BITS;
	uartConfig.parity 			= DISABLED;
	uartConfig.stop_bits 		= ONE_BIT;
	UART_init(&uartConfig);

	Ultrasonic_init();
	/* global interrupt enable */
	SREG |= (1<<7);
	/* wait until MCU_2 ready to start communication */
	while(UART_receiveByte() != MCU2_READY);

	for(;;)
	{
		/* read sensor distance */
		distance = Ultrasonic_readDistance();
		/* send state to MCU_2 */
		if(distance >= SAFE_DISTANCE)
		{
			UART_sendByte(SAFE_DISTANCE);
		}
		else
		{
			UART_sendByte((uint8)distance);
		}
		_delay_ms(60);
	}
}
