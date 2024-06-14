/*
 * main.c
 *
 *  Created on: Oct 12, 2022
 *      Author: Mahmoud Reda
 */
#include"lcd.h"
#include"icu.h"
#include"ultrasonic.h"
#include<avr\io.h>
#include<util\delay.h>
#include <avr/interrupt.h>
volatile uint8 g_edgeCount;
uint8 number=0;
//uint8 flag=0;

int main()
{
	//	Icu_ConfigType Icu_Config = {F_CPU_8,RISING};
	//first activate global interrupt
	SREG|=(1<<7);
	//initialize lcd and ultrasonic
	LCD_init();
	Ultrasonic_init();
	LCD_displayString("Distance=     cm");
	while(1)
	{
		//store value of the distance returned from the fun in a var and then print it on lcd
		number = Ultrasonic_readDistance();
		LCD_moveCursor(0, 10);
		LCD_intgerToString(number);
		if(number<100)
			LCD_displayCharacter(' ');
		//delay between each value of distance and other to help the
		//ultrasonic and icu to re-calculate the new value
		_delay_ms(100);

	}

}

