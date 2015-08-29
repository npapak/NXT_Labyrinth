/**
 * @file aic.c
 * @brief Implementation of AIC protocol
 * @author Nikos Papakonstantinou <npapak@gmail.com>
 * @version v1.0
 * @date 2015-08-29
 */
#include "aic.h"

void AICInit(void)
{
	int i;
	for(i = 0; i < 32; i++)
	{
		AICInterruptDisable(i);
	}
}

void AICInterruptEnable(int which, void (*handler)(void))
{
	//assert(which >= 0 && which <= 31);
	AT91C_AIC_SMR[which] = AT91C_AIC_SRCTYPE_HIGH_LEVEL|AT91C_AIC_PRIOR_HIGHEST;
// 	AT91C_AIC_SMR[which] = ( which == AT91C_ID_SSC ? AT91C_AIC_SRCTYPE_HIGH_LEVEL|AT91C_AIC_PRIOR_HIGHEST : AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE|AT91C_AIC_PRIOR_LOWEST );
	AT91C_AIC_SVR[which] = handler;
	*AT91C_AIC_IECR = (1L << which);
}



void AICInterruptDisable(int which)
{
	//assert(which >= 0 && which <= 31);
	*AT91C_AIC_IDCR = (1L << which);
}
