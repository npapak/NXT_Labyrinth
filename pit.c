/**
 * @file pit.c
 * @brief Implementation of PIT protocol
 * @author Nikos Papakonstantinou <npapak@gmail.com>
 * @version v1.0
 * @date 2015-08-29
 */
#include "pit.h"


void      PITEnable(void)
{
	*AT91C_PITC_PIMR |= AT91C_PITC_PITEN;
}
void      PITDisable(void)
{
	*AT91C_PITC_PIMR &= (0xFEFFFFFF);
}

ULONG     PITRead(void)
{
	return *AT91C_PITC_PIIR & AT91C_PITC_CPIV;
}

ULONG     PITReadReset(void)
{
	return *AT91C_PITC_PIVR & AT91C_PITC_CPIV;
}

void      PITInterruptEnable(ULONG period, void (*handler)(void))
{
	*AT91C_PITC_PIMR |= AT91C_PITC_PITIEN;
	*AT91C_PITC_PIMR |= period;
	AICInterruptEnable(AT91C_ID_SYS,handler);
}

void      PITInterruptDisable(void)
{
	*AT91C_PITC_PIMR &= (0xFDFFFFFF);
	AICInterruptDisable(AT91C_ID_SYS);
}

void      PITAckInterrupt(void)
{
	if( (*AT91C_PITC_PISR ) == 1)
		PITReadReset();
}

/*UWORD	  PITTicks2ms(ULONG ticks)
{
	return (UWORD)(ticks / 3000);
}

UWORD	  PITTicks2s(ULONG ticks)
{
	return (UWORD)(ticks / 1000000);
}

void 	  spindelayms(ULONG ms)
{

}
*/
