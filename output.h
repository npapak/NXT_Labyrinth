#ifndef   _OUTPUT_H_
#define   _OUTPUT_H_

#include <stdconst.h>

#define	  MAX_SPEED_FW (70)
#define	  MAX_SPEED_RW (-MAX_SPEED_FW)

void      OutputInit(void);
void      OutputExit(void);
void      OutputSetSpeed (UBYTE MotorNr, SBYTE Speed);

#endif
