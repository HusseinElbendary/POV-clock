/*
 * Timer_priv.h
 *
 *  Created on: Nov 15, 2019
 *      Author: Na
 */

#ifndef TIMER_PRIV_H_
#define TIMER_PRIV_H_


typedef union
{
	struct
	{
		u8 CS0:1;
		u8 CS1:1;
		u8 CS2:1;
		u8 WGM1:1;
		u8 COM0:1;
		u8 COM1:1;
		u8 WGM0:1;
		u8 FOC:1;
	};
	u8 Data;
}TCCR_REG;

typedef union
{
	struct
	{
		u8 Bit0:1;
		u8 Bit1:1;
		u8 Bit2:1;
		u8 Bit3:1;
		u8 Bit4:1;
		u8 Bit5:1;
		u8 Bit6:1;
		u8 Bit7:1;
	};
	u8 Data;
}OCR_REG;
typedef union
{
	struct
	{
		u8 Bit0:1;
		u8 Bit1:1;
		u8 Bit2:1;
		u8 Bit3:1;
		u8 Bit4:1;
		u8 Bit5:1;
		u8 Bit6:1;
		u8 Bit7:1;
	};
	u8 Data;
}TCNT_REG;

typedef union
{
	struct
	{
		u8 TOIE0:1;
		u8 OCIE0:1;
		u8 TOIE1:1;
		u8 OCIE1:1;
		u8 OCIE1A:1;
		u8 TICE1:1;
		u8 TOIE2:1;
		u8 OCIE2:1;
	};
	u8 Data;
}TIMSK_REG;

typedef union
{
	struct
	{
		u8 TOV0:1;
		u8 OCF0:1;
		u8 TOV1:1;
		u8 OVF1B:1;
		u8 OCF1A:1;
		u8 ICF1:1;
		u8 TOV2:1;
		u8 OCF2:1;
	};
	u8 Data;
}TIFR_REG;

#define TCCR0 ( * ((volatile TCCR_REG*)  0x53))
#define TCCR2 ( * ((volatile TCCR_REG*)  0x45))
#define OCR0  ( * ((volatile OCR_REG*)   0x5C))
#define OCR2  ( * ((volatile OCR_REG*)   0x43))
#define TCNT0 ( * ((volatile TCNT_REG*)  0x52))
#define TCNT2 ( * ((volatile TCNT_REG*)  0x44))

#define TIMSK ( * ((volatile TIMSK_REG*) 0x59))
#define TIFR  ( * ((volatile TIFR_REG*)  0x58))


#endif /* TIMER_PRIV_H_ */
