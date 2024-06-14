/*
 * ultrasonic.h
 *
 *  Created on: Oct 11, 2022
 *      Author: Mahmoud Reda
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
#include"gpio.h"
#include"common_macros.h"
#include"std_types.h"
//define the trigger and echo pin of ultrasonic
#define Ultrasonic_trigger_PORT_ID  PORTB_ID
#define Ultrasonic_trigger_PIN_ID   PIN5_ID
#define Ultrasonic_ECHO_PORT_ID  PORTD_ID
#define Ultrasonic_ECHO_PIN_ID   PIN6_ID
 extern volatile uint8 g_edgeCount;
 /*Ultrasonic_init
  * description: the fun is responsible for initialize ultra sonic
  * also initialize icu with specific characteristics
  * also call the call back function
  * to start working and send 8 pulses to MC
  *input: void
  * return void
  */
void Ultrasonic_init(void);
/*Ultrasonic_Trigger
 * description: the fun is responsible for send trigger to ultra sonic
 * to start working and send 8 pulses to MC
 *input: void
 * return void
 */
void Ultrasonic_Trigger(void);
/*Ultrasonic_readDistance
 * description: the fun is responsible for reading the distance
 *input: void
 * return distance measured by ultra sonic
 */
uint16 Ultrasonic_readDistance(void);
/*Ultrasonic_edgeProcessing
 * description: the fun is responsible for count the high period sent from echo pin to
 * calculate the time which signal take to go to target and return
 *input: void
 * return void
 */
void Ultrasonic_edgeProcessing(void);

#endif /* ULTRASONIC_H_ */
