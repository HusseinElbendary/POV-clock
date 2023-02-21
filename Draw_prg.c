/*
 * Draw_prg.c
 *
 *  Created on: Nov 7, 2019
 *      Author: Na
 */

#include "Std_types.h"
#include "Bit_math.h"

#include "Dio_int.h"

#include "Led_int.h"
#include "Draw_int.h"
#include "Draw_priv.h"

u16 Draw_u8Image[360/Draw_u8Angle_Res];



void Draw_vidClockInit(Time_Type time)
{

	/*puts the clock shapes onto the Image array to be drawn
	*  shapes are  The outer and inner circle
	*  			   The hour marks
	*  			   The hour arrow
	*  			   The Minute Arrow
	*
	*for example 7:15:13
	*bec the minutes are odd , all sec degress are lit up and
	* we close 6 ever sec.
	*								x	X
	*							x  ooo OOO OOO ooo
						   x   oOO        0        OOo
						x  oOO            0            OOo
					  x oOO    0                     0    OOo
					x oOO                                   OOo
				  x oOO                                       OOo
				 x oOO  0                                   0  OOo
				x oOO                                           OOo x
			   x oOO                                             OOo x
			   x oOO                      0                      OOo x
			   x oOO 0 0                0   0 0 0 0 0 0 0    0 0 OOo x
			   x oOO                    0 0                      OOo x
			   x oOO                   0                         OOo x
				x oOO                 0                         OOo x
				 x oOO  0            0                      0  OOo x
				  x oOO                                       OOo x
					x oOO                                   OOo x
					  x oO     0                     0    OOo x
						x  oOO            0            OOo x
							x  oOO        0        OOo x
								x  ooo OOO OOO ooo x
	 *								x   X   X   x
	 *
	 *
	 *
	 *
	 *
	 *
	 */

	u16 i;
	s16 secound_angle;

	/*
	 * adds the outer and inner circle
	 */
	for(i=0;i<360/Draw_u8Angle_Res;i++)
	{
		Draw_u8Image[i]=0b0100000001;
	}

	/*
	 * adds hour lines
	 */
	Draw_vidAddLine(0b0111000000,0);
	Draw_vidAddLine(0b0111000000,90);
	Draw_vidAddLine(0b0111000000,180);
	Draw_vidAddLine(0b0111000000,270);

	Draw_vidAddLine(0b0110000000,30);
	Draw_vidAddLine(0b0110000000,60);
	Draw_vidAddLine(0b0110000000,120);
	Draw_vidAddLine(0b0110000000,150);
	Draw_vidAddLine(0b0110000000,210);
	Draw_vidAddLine(0b0110000000,240);
	Draw_vidAddLine(0b0110000000,300);
	Draw_vidAddLine(0b0110000000,330);

	/*
	 * calculating the angle based on the Time_Type
	 * Each sec is 6 degs
	 * Each min is 6 degs plus extra 1 deg for every 10 sec
	 * Each hour is 30 degs plus 2 deg for each min
	 * if the hour is == 12 , then it is 0 deg plus 2 deg for each min
	 */
	secound_angle=time.Secounds*6;

	/*
	 * add hour and minute arrows
	 * and adding the outer circle representing the secounds
	 *
	 */
	if(time.Minutes%2)
		{
		/*
		 * if minutes are odd, then every sec we turn off degrees
		 * so we need to initialize the clock by turning on the remaining degrees
		 * check the commented example
		 */

		for(i=secound_angle;i<360;i+=Draw_u8Angle_Res)
		{
			Draw_vidAddLine(0b1000000000,i);
		}

		}
	else
	{
		/*
		 * if minutes are even, then every sec we turn on degrees
		 * so we need to initialize the clock by turning off the previous degrees
		 * just to make sure they are off
		 */
		for(i=0;i<=secound_angle;i+=Draw_u8Angle_Res)
		{
			Draw_vidDeleteLine(0b1000000000,i);
		}
	}

	Draw_vidMinArrow(time);
	Draw_vidHourArrow(time);
}
void Draw_vidAddLine(u16 pattern ,u16 Angle)
{
	/*
	 * adds the given pattern to the existing image at certain angle
	 */
	if(360==Angle)
	{
		Angle=0;
	}
		Draw_u8Image[Angle/Draw_u8Angle_Res]|=pattern;
}
void Draw_vidDeleteLine(u16 pattern ,u16 Angle)
{
	/*
	 * removes the given pattern to the existing image at certain angle
	 */
	if(360==Angle)
	{
		Angle=0;
	}

	Draw_u8Image[Angle/Draw_u8Angle_Res]&=(~pattern);
}
void Draw_vidDrawImage(u16 Angle)
{
	/*
	 * switch on LEDs according to the pattern at the given angle
	 */
	Led_vidSwitch(Draw_u8Image[Angle/Draw_u8Angle_Res]);
}
void Draw_vidMinArrow(Time_Type time)
{
	/*
	 * draws the minute arrow and deletes the old arrow
	 * it saves the angle of the current arrow to be able to deleted next round
	 * calculating the angle based on the Time
	 * Each min is 6 degs plus extra 1 deg for every 10 sec
	 */
	static u16 PrevAngle=0;
	u16 minute_angle;
	minute_angle=time.Minutes*6+(time.Secounds/(10*Draw_u8Angle_Res));


	Draw_vidDeleteLine(0b0000011110,PrevAngle);
	Draw_vidAddLine(0b0000011111,minute_angle);
	PrevAngle=minute_angle;

}
void Draw_vidHourArrow(Time_Type time)
{
	/*
	 * draws the hour arrow and deletes the old arrow
	 * it saves the angle of the current arrow to be able to deleted next round
	 * calculating the angle based on the Time
	 * Each hour is 30 degs plus 2 deg for each min
	 * if the hour is == 12 , then it is 0 deg plus 2 deg for each min
	 */
	static u16 PrevAngle=0;
	u16 hour_angle;
	if(12==time.Hours)
	{
		hour_angle=(time.Minutes/(2*Draw_u8Angle_Res));
	}
	else
	{
	hour_angle=time.Hours*30+(time.Minutes/(2*Draw_u8Angle_Res));
	}


	Draw_vidDeleteLine(0b0000000110,PrevAngle);
	Draw_vidAddLine(0b0000000111,hour_angle);
	PrevAngle=hour_angle;
}
void Draw_vidSecoundCircle(Time_Type time)
{
	u8 i;
	u16 secound_angle;
	secound_angle=time.Secounds*6;
	if(360==secound_angle)
	{
		secound_angle=0;
	}
	/*
	 * if the minutes are even then all secounds are not lit , and we light one every sec
	 */
	if(time.Minutes%2)
	{
	/*
	 *If the minutes are odd then all seconds are lit up and every sec we close one
	 *each second is 6 degrees, we close all of the 6 degrees
	 */
		for(i=0;i<6;i+=Draw_u8Angle_Res)
		{
			Draw_vidDeleteLine(0b1000000000,secound_angle-i);
		}
	}
	else
	{
		/*
		 *If the minutes are even then all seconds are not lit up,
		 *and every sec we light one up
		 *each second is 6 degrees, we light all of the 6 degrees
		 */
		for(i=0;i<6;i+=Draw_u8Angle_Res)
		{
			Draw_vidAddLine(0b1000000000,secound_angle-i);
		}

	}

}
