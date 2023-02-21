/*
 * Led_prg.c
 *
 *  Created on: Nov 7, 2019
 *      Author: Na
 */

#include "Std_types.h"
#include "Bit_math.h"

#include "Dio_int.h"

#include "Led_int.h"

void Led_vidInit(void)
{
	Dio_vidSetPinDir(LED_u8LED_1,DIO_u8OUTPUT);
	Dio_vidSetPinDir(LED_u8LED_2,DIO_u8OUTPUT);
	Dio_vidSetPinDir(LED_u8LED_3,DIO_u8OUTPUT);
	Dio_vidSetPinDir(LED_u8LED_4,DIO_u8OUTPUT);
	Dio_vidSetPinDir(LED_u8LED_5,DIO_u8OUTPUT);
	Dio_vidSetPinDir(LED_u8LED_6,DIO_u8OUTPUT);
	Dio_vidSetPinDir(LED_u8LED_7,DIO_u8OUTPUT);
	Dio_vidSetPinDir(LED_u8LED_8,DIO_u8OUTPUT);
	Dio_vidSetPinDir(LED_u8LED_9,DIO_u8OUTPUT);
	Dio_vidSetPinDir(LED_u8LED_10,DIO_u8OUTPUT);

	Dio_vidSetPinVal(LED_u8LED_1,DIO_u8LOW);
	Dio_vidSetPinVal(LED_u8LED_2,DIO_u8LOW);
	Dio_vidSetPinVal(LED_u8LED_3,DIO_u8LOW);
	Dio_vidSetPinVal(LED_u8LED_4,DIO_u8LOW);
	Dio_vidSetPinVal(LED_u8LED_5,DIO_u8LOW);
	Dio_vidSetPinVal(LED_u8LED_6,DIO_u8LOW);
	Dio_vidSetPinVal(LED_u8LED_7,DIO_u8LOW);
	Dio_vidSetPinVal(LED_u8LED_8,DIO_u8LOW);
	Dio_vidSetPinVal(LED_u8LED_9,DIO_u8LOW);
	Dio_vidSetPinVal(LED_u8LED_10,DIO_u8LOW);

}
/*
void Led_vidLedOn(u16 Led_ID)
{
if(Led_ID==LED_u8LED_1)
{
	Dio_vidSetPinVal(LED_u8LED_1,DIO_u8HIGH);
}
else if(Led_ID==LED_u8LED_2)
{
	Dio_vidSetPinVal(LED_u8LED_2,DIO_u8HIGH);
}
else if(Led_ID==LED_u8LED_3)
{
	Dio_vidSetPinVal(LED_u8LED_3,DIO_u8HIGH);
}
else if(Led_ID==LED_u8LED_4)
{
	Dio_vidSetPinVal(LED_u8LED_4,DIO_u8HIGH);
}
else if(Led_ID==LED_u8LED_5)
{
	Dio_vidSetPinVal(LED_u8LED_5,DIO_u8HIGH);
}
else if(Led_ID==LED_u8LED_6)
{
	Dio_vidSetPinVal(LED_u8LED_6,DIO_u8HIGH);
}
else if(Led_ID==LED_u8LED_7)
{
	Dio_vidSetPinVal(LED_u8LED_7,DIO_u8HIGH);
}
else if(Led_ID==LED_u8LED_8)
{
	Dio_vidSetPinVal(LED_u8LED_8,DIO_u8HIGH);
}
else if(Led_ID==LED_u8LED_9)
{
	Dio_vidSetPinVal(LED_u8LED_9,DIO_u8HIGH);
}
else if(Led_ID==LED_u8LED_10)
{
	Dio_vidSetPinVal(LED_u8LED_10,DIO_u8HIGH);
}

*/
}
void Led_vidSwitch(u16 pattern)
{
	u8 LED_IDarr[]={LED_u8LED_1,LED_u8LED_2,LED_u8LED_3,LED_u8LED_4,LED_u8LED_5,
			LED_u8LED_6,LED_u8LED_7,LED_u8LED_8,LED_u8LED_9,LED_u8LED_10};
	u8 i;
	for(i=0;i<10;i++)
	{
		if (1==(pattern>>i)%2)
		{
			Dio_vidSetPinVal(LED_IDarr[i],DIO_u8HIGH);
		}
		else
		{
			Dio_vidSetPinVal(LED_IDarr[i],DIO_u8LOW);
		}
	}
}
