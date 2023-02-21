/*
 * Interrupt_prg.c
 *
 *  Created on: Nov 14, 2019
 *      Author: Na
 */

#include "Std_types.h"
#include "Bit_math.h"
#include "Dio_int.h"

#include <avr/interrupt.h>
#include "Interrupt_int.h"

void (*Arr[3])(void);

void Interrupt_vidEnable(void)
{
	/*
	 * enable interrupts
	 */
	SET_BIT(SREG,7);//GIE is in SREG bit 7
}

void Interrupt_vidInt0_Enable(void)
{
	/*
	 * sets up the pin to input pull-up mode
	 * and sets the input interrupt INT0 to LOW level trigger
	 */
	Dio_vidSetPinDir(DIO_u8PIN_26,DIO_u8INPUT);
	Dio_vidSetPinVal(DIO_u8PIN_26,DIO_u8HIGH);

	SET_BIT(GICR,6);//PIE of INT0 is in GICR bit 6
	CLEAR_BIT(MCUCR,0);//clear ISC00 in MCUCR to have LOW level interrupt
	CLEAR_BIT(MCUCR,1);
}

void Interrupt_vidSetISR(u8 ID, void (*pCode)(void))
{
	if(ID==INTERRUPT_u8ID_TIMER0_OV)
	{
		Arr[0]=pCode;
	}
	else if(ID== INTERRUPT_u8ID_TIMER2_OV)
	{
		Arr[1]=pCode;
	}
	else if(ID==INTERRUPT_u8ID_INT0)
	{
		Arr[2]=pCode;
	}
}
/*
 * ******************* ISR**************************
 */

ISR(INT0_vect)
{
	Arr[2]();
}
ISR(TIMER2_OVF_vect)
{
	Arr[1]();
}
ISR(TIMER0_OVF_vect)
{
	Arr[0]();
}
