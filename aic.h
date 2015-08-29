#ifndef   AIC
#define   AIC

#include "AT91SAM7S256.h"
#include <stdconst.h>
//#include <assert.h>

void      AICInit(void);
void      AICInterruptEnable(int which, void (*handler)(void));
void      AICInterruptDisable(int which);

#endif
