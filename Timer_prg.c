
#include "Std_types.h"
#include "Bit_math.h"

#include "Interrupt_int.h"

#include "Timer_int.h"
#include "Timer_priv.h"



void Timer_vidTimer0Init(void)
{
	/*
	 * NORMAL mode
	 */
	TCCR0.COM0=0;
	TCCR0.COM1=0;
	TCCR0.WGM0=0;
	TCCR0.WGM1=0;
	/*
	 * Pre-Scaler x8
	 */
	TCCR2.CS0=0;
	TCCR2.CS1=1;
	TCCR2.CS2=0;
	/*
	 * enable Timer OverFlow interrupt
	 */
	TIMSK.TOIE0;
}
void Timer_vidTimer2Init(void)
{
	/*
	 * NORMAL mode
	 */
	TCCR2.COM0=0;
	TCCR2.COM1=0;
	TCCR2.WGM0=0;
	TCCR2.WGM1=0;
	/*
	 * Pre-Scaler x8
	 */
	TCCR2.CS0=0;
	TCCR2.CS1=1;
	TCCR2.CS2=0;
	/*
	 * enable Timer OverFlow interrupt
	 */
	TIMSK.TOIE2;
}


void Timer_vidSetTCNT0(u8 val)
{
	TCNT0.Data=val;
}
void Timer_vidSetTCNT2(u8 val )
{
	TCNT2.Data=val;
}
