/*
 * Dio_priv.h
 *
 *  Created on: Nov 14, 2019
 *      Author: Na
 */

#ifndef DIO_PRIV_H_
#define DIO_PRIV_H_

#define DDRA ( * ((volatile u8*)  0x3A))
#define DDRB ( * ((volatile u8*)  0x38))
#define DDRC ( * ((volatile u8*)  0x34))
#define DDRD ( * ((volatile u8*)  0x31))

#define PORTA ( * ((volatile u8*)  0x3B))
#define PORTB ( * ((volatile u8*)  0x38))
#define PORTC ( * ((volatile u8*)  0x35))
#define PORTD ( * ((volatile u8*)  0x32))

#define PINA ( * ((volatile u8*)  0x39))
#define PINB ( * ((volatile u8*)  0x36))
#define PINC ( * ((volatile u8*)  0x33))
#define PIND ( * ((volatile u8*)  0x30))



#endif /* DIO_PRIV_H_ */
