/*
 * main.c
 *
 *  Created on: Nov 7, 2019
 *      Author: Na
 */

#include "Std_types.h"
#include "Dio_int.h"

#include "Timer_int.h"
#include "Interrupt_int.h"

#include "Led_int.h"
#include "Draw_int.h"
#include "Watchdog_int.h"



/*
 ************************DEFINES**********************************
 */
#define u8Num_of_Tasks 3
#define u8Motor_PIN DIO_u8PIN_31


/*
 *************************RTOS DECLARATIONS*********************************
 */
typedef struct
{
	u32  FirstDelay;
	u32  Periodicity;
	u8 	 State;
	void (*pfCode)(void);
}Task_Type;

Task_Type DrawImage;
void DrawImage_Code(void);/*turns on the pattern of LED at current angle*/


Task_Type UpdateImage;
void UpdateImage_Code(void);/*updates the Image every sec that passes*/

Task_Type Wdg_Mng;
void Wdg_Mng_Code(void);


Task_Type * TaskArr[u8Num_of_Tasks];

void Rto_vidScheduler(void);
void Rto_vidStartOS(void);

/*
 * ****************************VARIABLE AND FUNCTION DECLARATIONS***********************************
 */
void INT0_ISR(void);
void Timer0_ISR(void);
void Timer2_ISR(void);


void Timer_u16TimeElapsed_Init(void);
/*
 * enables timer2 to be able to calculate the time elapsed
 */


u16 Timer_u16TimeElapsed(void);
/*returns the time passed
 * used to calculated how long does one turn take
 */

u16 Timer2_u16TICKCount=0;
/*
 * Timer2_u16TICKCount is used to count how many ticks (100 micro-sec )have passed
 */

u16 Current_Angle=0;

Time_Type time;

/*
 * **********************************************************************
 */

int main(void)
{
	/*initialize tasks*/
	TaskArr[0]=&DrawImage;
	TaskArr[1]=&UpdateImage;
	TaskArr[2]=&Wdg_Mng;


	DrawImage.FirstDelay=0;
	DrawImage.Periodicity=0;
	DrawImage.State=1;//running
	DrawImage.pfCode=DrawImage_Code;


	UpdateImage.FirstDelay=0;
	UpdateImage.Periodicity=10000;
	UpdateImage.State=1;//running
	UpdateImage.pfCode=UpdateImage_Code;

	Wdg_Mng.FirstDelay=0;
	Wdg_Mng.Periodicity=200;
	Wdg_Mng.State=1;//running
	Wdg_Mng.pfCode=Wdg_Mng_Code;




	time.Secounds=0;
	time.Minutes=15;
	time.Hours=7;
	/* read the time and initialize it
	 * fix tis part after getting a clock
	 */

	Led_vidInit();
	Draw_vidClockInit(time);
	/*draws the basic clock and adds the time to it*/


	Interrupt_vidInt0_Enable();
	Interrupt_vidSetISR(INTERRUPT_u8ID_INT0,INT0_ISR);
	/*
	 * Interrupt input int0 enabled
	 */


	Dio_vidSetPinDir(u8Motor_PIN,DIO_u8OUTPUT);
	Dio_vidSetPinVal(u8Motor_PIN,DIO_u8HIGH);
	/* Motor enable*/



	Wdg_vidInit();
	Timer_u16TimeElapsed_Init();
	Rto_vidStartOS();
	while(1)
	{

	}

	return 0;
}

void INT0_ISR(void)
{
	/*
	 * input interrupt triggered by the hall sensor every one cycle
	 * used to calculate how many ticks it takes to complete 1 cycle
	 * and to rest the current position  to 0
	 */
	u16 Rotation_Time;
	Rotation_Time=Timer_u16TimeElapsed();
	/* returns how many ticks needed to complete one cycle
	 * each tick is 100 micro-sec
	 */
	DrawImage.Periodicity=Rotation_Time/360;
	Current_Angle=0;// change this depending on where is the hall switch
}

void Timer0_ISR(void)
{
	/*
	 * Timer used to run the RTOS Scheduler
	 * This block of code will run every 1 tick =100 micro-sec
	 * pre-scaler is 8
	 */
	Timer_vidSetTCNT0(156);/* rests the timer0 to the start value*/
	Interrupt_vidEnable();/*allow nested-interrupts to happen*/
	Rto_vidScheduler();


}

void Timer2_ISR(void)
{
	/*used for TimeElasped function
	 *this block runs every 1 tick=100 micro-sec
	 */
	Timer2_u16TICKCount++;
	Timer_vidSetTCNT2(156);//start value
}


void DrawImage_Code(void)
{
	/*
	 * draws turns on the Leds of the current position
	 *
	 */
	Draw_vidDrawImage(Current_Angle);
	Current_Angle++;
	if(360<=Current_Angle)
	{
		Current_Angle=0;
	}
}
void UpdateImage_Code(void)
{
	/*
	 * this block will run every 1 sec
	 * updates the time instead of reading it from the RTC IC every sec
	 * and updates the image that needs to be drawn
	 */
	time.Secounds++;
	if(60==time.Secounds)
	{
		time.Secounds=0;
		time.Minutes++;
	}
	if(60==time.Minutes)
	{
		time.Minutes=0;
		time.Hours++;
	}
	if(13==time.Hours)
	{
		time.Hours=1;
	}
	Draw_vidSecoundCircle(time);
	Draw_vidMinArrow(time);
	Draw_vidHourArrow(time);
}
void Rto_vidScheduler(void)
{
	u8 TaskCounter;

	for(TaskCounter=0;TaskCounter<u8Num_of_Tasks;TaskCounter++)
	{
		if(TaskArr[TaskCounter]->FirstDelay==0)
		{
			if(TaskArr[TaskCounter]->State==1)
			{
				TaskArr[TaskCounter]->pfCode();
				TaskArr[TaskCounter]->FirstDelay=TaskArr[TaskCounter]->Periodicity-1;// period is the time between two starts , the -1 is for the time taken by the code running
			}
		}
		else
		{
			TaskArr[TaskCounter]->FirstDelay--;
		}
	}
}

void Rto_vidStartOS(void)
{

	/*
	 * initialize Timer0:
	 * 				Normal mood , Pre-scaler x8 , overflow interrupt enabled
	 */
	Timer_vidTimer0Init();


	/*
	 * load timer 0 with 156 to get 100 micro-sec for each overflow
	 */
	Timer_vidSetTCNT0(156);

	/*
	 *Sets the ISR for Timer0 Overflow interrupt
	 */

	Interrupt_vidSetISR(INTERRUPT_u8ID_TIMER0_OV,Timer0_ISR);
	/*
	 * enable global interrupt
	 */
	Interrupt_vidEnable();

}
void Timer_u16TimeElapsed_Init(void)
{


	/*
	 * initialize Timer2:
	 * 				Normal mood , Pre-scaler x8 , overflow interrupt enabled
	 */
	Timer_vidTimer2Init();


	/*
	 * load timer 2 with 156 to get 100 micro-sec for each overflow
	 */
	Timer_vidSetTCNT2(156);

	/*
	 * sets the ISR for timer2 overflow Interrupt
	 */

	Interrupt_vidSetISR(INTERRUPT_u8ID_TIMER2_OV,Timer2_ISR);

	/*
	 * enable global interrupt
	 */
	Interrupt_vidEnable();

}
u16 Timer_u16TimeElapsed(void)
{
	/*
	 * returns how many ticks have passed since last time this function was called
	 *
	 */
	u16 TimeElapsed=0;
	TimeElapsed=Timer2_u16TICKCount;

	Timer2_u16TICKCount=0;/*resets both the over flow counter and the Timer2 value*/
	Timer_vidSetTCNT2(156);

	return TimeElapsed;
}

void Wdg_Mng_Code(void)
{
	Wdg_vidRefresh();
}
