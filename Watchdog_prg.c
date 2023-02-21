/*
 * Watchdog_prg.c
 *
 *  Created on: Oct 26, 2019
 *      Author: Na
 */

#include "Std_types.h"
#include "Bit_math.h"
#include "Watchdog_int.h"
#include "Watchdog_priv.h"
void Wdg_vidInit(void)
{
	SET_BIT(WDTCR,2);
	CLEAR_BIT(WDTCR,1);
	CLEAR_BIT(WDTCR,0);

	SET_BIT(WDTCR,3);
}

void Wdg_vidRefresh(void)
{
	asm("WDR");
}
