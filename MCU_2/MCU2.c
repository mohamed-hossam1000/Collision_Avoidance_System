 /******************************************************************************
 *
 * Project : Collision Avoidance System
 *
 * File Name: MCU_2.c
 *
 * Description: Receive the measured distance from MCU_1 via UART and warn the
 * 				driver when collision is detected
 *
 * Author: Mohamed Hossam
 *
 *******************************************************************************/
#include"uart.h"
#include"gpio.h"
#include"timer1.h"
#include"buzzer.h"
#include"led.h"
#include<avr/io.h>

#define SAFE_DISTANCE	51
#define MCU2_READY		0x45

void timerTick();
uint8 volatile g_ledTicks = 0;
uint8 volatile g_buzzerTicks = 0;

uint8 g_distance;

int main()
{
	Timer1_ConfigType timerConfig;
	/* UART configuration and initialization */
	UART_configType uartConfig;
	uartConfig.baudRate 		= 9600;
	uartConfig.character_size 	= EIGHT_BITS;
	uartConfig.parity 			= DISABLED;
	uartConfig.stop_bits 		= ONE_BIT;
	UART_init(&uartConfig);
	/* Timer1 configuration without initialization
	 * timer configured to give interrupt every 10ms with F_CPU = 8MHz */
	timerConfig.mode 		  = COMPARE;
	timerConfig.initial_value = 0;
	timerConfig.prescaler 	  = F_CPU_8;
	timerConfig.compare_value = 10000;
	Timer1_setCallBack(timerTick);
	/* Initialize buzzer and led */
	Buzzer_init();
	LED_init();
	/* Enable global interrupt */
	SREG |= (1<<7);
	/* send ready status to MCU_1 */
	UART_sendByte(MCU2_READY);

	for(;;)
	{
		g_distance = UART_receiveByte();
		if(g_distance == SAFE_DISTANCE)
		{
			LED_off();
			Buzzer_off();
			Timer1_deInit();
		}
		else
		{
			/* When distance decreases to a dangerous level initialize the timer
			 * The timer will handle the buzzer and led */
			Timer1_init(&timerConfig);
		}
	}
}

/*
 * Description:
 * a call back function for timer1 interrupt handler
 * toggles the led every half second (1 interrupt = 10ms)
 * toggles the buzzer every (10 * distance)ms
 */
void timerTick()
{
	g_ledTicks++;
	g_buzzerTicks++;
	if(g_ledTicks == 50)
	{
		LED_toggle();
		g_ledTicks = 0;
	}
	if(g_buzzerTicks == g_distance)
	{
		Buzzer_toggle();
		g_buzzerTicks = 0;
	}
}
