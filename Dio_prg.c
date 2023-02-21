/*
 * Dio_prg.c
 *
 *  Created on: Aug 17, 2019
 *      Author: Na
 */

#include "Std_types.h"
#include "Bit_math.h"

#include "Dio_int.h"
#include "Dio_priv.h"

void Dio_vidSetPinDir(u8 Pin,u8 Dir)
{
	/*
	 * Dir: 0= input,1=output
	 * Pin: from 0 to 31
	 */

	u8 Loc_u8Port;
	u8 Loc_u8Pin;

	Loc_u8Port=Pin/8;
	Loc_u8Pin=Pin%8;
	switch(Loc_u8Port)
	{
	case 0:
	{
		if(Dir==0)
		{
			CLEAR_BIT(DDRA,Loc_u8Pin);

		}
		else
		{
			SET_BIT(DDRA,Loc_u8Pin);
		}
		break;
	}
	case 1:
		{
			if(Dir==0)
			{
				CLEAR_BIT(DDRB,Loc_u8Pin);
			}
			else
			{
				SET_BIT(DDRB,Loc_u8Pin);
			}
			break;
		}
	case 2:
		{
			if(Dir==0)
			{
				CLEAR_BIT(DDRC,Loc_u8Pin);
			}
			else
			{
				SET_BIT(DDRC,Loc_u8Pin);
			}
			break;
		}
	case 3:
		{
			if(Dir==0)
			{
				CLEAR_BIT(DDRD,Loc_u8Pin);
			}
			else
			{
				SET_BIT(DDRD,Loc_u8Pin);
			}
			break;
		}

	}
}

void Dio_vidSetPinVal(u8 Pin,u8 Val)
{
	/*
	 * Val: 0= low,1=high
	 * Pin: from 0 to 31
	 */

	u8 Loc_u8Port;
	u8 Loc_u8Pin;

	Loc_u8Port=Pin/8;
	Loc_u8Pin=Pin%8;
	switch(Loc_u8Port)
	{
		case 0:
		{
			if(Val==0)
			{
				CLEAR_BIT(PORTA,Loc_u8Pin);
			}
			else
			{
				SET_BIT(PORTA,Loc_u8Pin);
			}
			break;
		}
		case 1:
			{
				if(Val==0)
				{
					CLEAR_BIT(PORTB,Loc_u8Pin);
				}
				else
				{
					SET_BIT(PORTB,Loc_u8Pin);
				}
				break;
			}
		case 2:
			{
				if(Val==0)
				{
					CLEAR_BIT(PORTC,Loc_u8Pin);
				}
				else
				{
					SET_BIT(PORTC,Loc_u8Pin);
				}
				break;
			}
		case 3:
			{
				if(Val==0)
				{
					CLEAR_BIT(PORTD,Loc_u8Pin);
				}
				else
				{
					SET_BIT(PORTD,Loc_u8Pin);
				}
				break;
			}

		}
}

u8 Dio_u8GetPinVal(u8 Pin)
{
	u8 Loc_u8Port;
	u8 Loc_u8Pin;
	u8 Loc_u8PinVal;
	Loc_u8Port=Pin/8;
	Loc_u8Pin=Pin%8;
	switch(Loc_u8Port)
	{
		case 0:
		{
			Loc_u8PinVal= GET_BIT(PINA,Loc_u8Pin);
			break;
		}
		case 1:
		{
			Loc_u8PinVal= GET_BIT(PINB,Loc_u8Pin);
			break;
		}
		case 2:
		{
			Loc_u8PinVal=GET_BIT(PINC,Loc_u8Pin);
			break;
		}
		case 3:
		{
			Loc_u8PinVal= GET_BIT(PIND,Loc_u8Pin);
			break;
		}
	}
return Loc_u8PinVal;
}

void Dio_vidTglPin(u8 Pin)
{
	u8 Loc_u8Port;
	u8 Loc_u8Pin;
	Loc_u8Port=Pin/8;
	Loc_u8Pin=Pin%8;
	switch(Loc_u8Port)
	{
		case 0:
		{
			TOGGLE_BIT(PORTA,Loc_u8Pin);
			break;
		}
		case 1:
		{
			TOGGLE_BIT(PORTB,Loc_u8Pin);
			break;
		}
		case 2:
		{
			TOGGLE_BIT(PORTC,Loc_u8Pin);
			break;
		}
		case 3:
		{
			TOGGLE_BIT(PORTD,Loc_u8Pin);
			break;
		}

	}

}
