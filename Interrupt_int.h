/*
 * Interrupt_int.h
 *
 *  Created on: Nov 14, 2019
 *      Author: Na
 */

#ifndef INTERRUPT_INT_H_
#define INTERRUPT_INT_H_

#define INTERRUPT_u8ID_TIMER0_OV 0
#define INTERRUPT_u8ID_TIMER2_OV 1
#define INTERRUPT_u8ID_INT0      2

void Interrupt_vidEnable(void);
void Interrupt_vidInt0_Enable(void);
void Interrupt_vidSetISR(u8 ID, void (*pCode)(void));

#endif /* INTERRUPT_INT_H_ */
