/*
 * Draw_int.h
 *
 *  Created on: Nov 7, 2019
 *      Author: Na
 */

#ifndef DRAW_INT_H_
#define DRAW_INT_H_

typedef struct
{
	u8 Secounds;
	u8 Minutes;
	u8 Hours;
}Time_Type;
void Draw_vidAddLine(u16 pattern ,u16 Angle);
void Draw_vidDeleteLine(u16 pattern ,u16 Angle);
void Draw_vidDrawImage(u16 Angle);
//void Draw_vidAddChar(u16 pattern[],u16 StartAngle);
//void Draw_vidAddCircle(u16 R, u16 StartAngle, u16 EndAngle);
void Draw_vidMinArrow(Time_Type CurrentTime);
void Draw_vidHourArrow(Time_Type CurrentTime);
void Draw_vidSecoundCircle(Time_Type CurrentTime);
void Draw_vidClockInit(Time_Type CurrentTime);
#endif /* DRAW_INT_H_ */
