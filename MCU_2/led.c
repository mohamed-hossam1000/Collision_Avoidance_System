 /******************************************************************************
 *
 * Module: LED
 *
 * File Name: LED.c
 *
 * Description: Source file for the LED driver
 *
 * Author: Mohamed Hossam
 *
 *******************************************************************************/

#include"led.h"
#include"gpio.h"

void LED_init()
{
	GPIO_setupPinDirection(LED_PORT_ID, LED_PIN_ID, PIN_OUTPUT);
	GPIO_writePin(LED_PORT_ID, LED_PIN_ID, LOGIC_LOW);
}

void LED_on()
{
	GPIO_writePin(LED_PORT_ID, LED_PIN_ID, LOGIC_HIGH);
}

void LED_off()
{
	GPIO_writePin(LED_PORT_ID, LED_PIN_ID, LOGIC_LOW);
}

void LED_toggle()
{
	GPIO_togglePin(LED_PORT_ID, LED_PIN_ID);
}


