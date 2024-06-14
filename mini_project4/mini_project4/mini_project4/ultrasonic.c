/*
 * ultrasonic.c
 *
 *  Created on: Oct 11, 2022
 *      Author: Mahmoud Reda
 */
#include"ultrasonic.h"
#include"icu.h"
#include"common_macros.h"
#include"std_types.h"
#include"gpio.h"
#include<util\delay.h>
#include<avr/interrupt.h>
Icu_ConfigType Icu_Config = {F_CPU_8,RISING};
volatile uint8 g_edgeCount = 0;
uint16 g_distance = 0;
uint16 time=0;

/*Ultrasonic_Trigger
 * description: the fun is responsible for send trigger to ultra sonic
 * to start working and send 8 pulses to MC
 *input: void
 * return void
 */

void Ultrasonic_Trigger(void)
{
	/*send trigger during the pin by applying 1 to the
	 * pin for 10 microsecond and then applying zero
	 * */
	GPIO_writePin(Ultrasonic_trigger_PORT_ID,Ultrasonic_trigger_PIN_ID,LOGIC_HIGH);
_delay_us(10);
GPIO_writePin(Ultrasonic_trigger_PORT_ID,Ultrasonic_trigger_PIN_ID,LOGIC_LOW);
}
/*Ultrasonic_readDistance
 * description: the fun is responsible for reading the distance
 *input: void
 * return distance measured by ultra sonic
 */
uint16 Ultrasonic_readDistance(void)
{
	Ultrasonic_Trigger();
	//Ultrasonic_edgeProcessing();
	//while(g_edgeCount != 0){}
	//346*Time of High(ECHO)𝑃𝑢𝑙𝑠𝑒*100/2
//	= (TIMER value) / 57.8 cm
	//as the speed of sound on proteus=346 m/sec
	g_distance=(time / 57.8);

	return g_distance;

}
/*Ultrasonic_edgeProcessing
 * description: the fun is responsible for count the high period sent from echo pin to
 * calculate the time which signal take to go to target and return
 *input: void
 * return void
 */
void Ultrasonic_edgeProcessing(void)
{
	g_edgeCount++;
	if(g_edgeCount == 1)
	{
		/*
		 * Clear the timer counter register to start measurements from the
		 * first detected rising edge
		 */
		Icu_clearTimerValue();
		/* Detect falling edge */
		Icu_setEdgeDetectionType(FALLING);
	}
	else if(g_edgeCount == 2)
	{time=Icu_getInputCaptureValue();

	Icu_setEdgeDetectionType(RISING);
				g_edgeCount = 0;
	}
}
/*Ultrasonic_init
 * description: the fun is responsible for initialize ultra sonic
 * also initialize icu with specific characteristics
 * also call the call back function
 * to start working and send 8 pulses to MC
 *input: void
 * return void
 */
void Ultrasonic_init(void)
{GPIO_setupPinDirection(Ultrasonic_trigger_PORT_ID,Ultrasonic_trigger_PIN_ID, PIN_OUTPUT);
GPIO_setupPinDirection(Ultrasonic_ECHO_PORT_ID,Ultrasonic_ECHO_PIN_ID, PIN_INPUT);
	Icu_init(&Icu_Config);
	Icu_setCallBack(Ultrasonic_edgeProcessing);

}

