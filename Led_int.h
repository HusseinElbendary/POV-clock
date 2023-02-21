/*
 * Led_int.h
 *
 *  Created on: Nov 7, 2019
 *      Author: Na
 */

#ifndef LED_INT_H_
#define LED_INT_H_

#define LED_u8LED_1 DIO_u8PIN_0
#define LED_u8LED_2 DIO_u8PIN_1
#define LED_u8LED_3 DIO_u8PIN_2
#define LED_u8LED_4 DIO_u8PIN_3
#define LED_u8LED_5 DIO_u8PIN_4
#define LED_u8LED_6 DIO_u8PIN_5
#define LED_u8LED_7 DIO_u8PIN_6
#define LED_u8LED_8 DIO_u8PIN_7
#define LED_u8LED_9 DIO_u8PIN_8
#define LED_u8LED_10 DIO_u8PIN_9

void Led_vidInit(void);
void Led_vidLedOn(u16 Led_ID);
void Led_vidSwitch(u16 pattern);

#endif /* LED_INT_H_ */
