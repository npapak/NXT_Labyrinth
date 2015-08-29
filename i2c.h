#ifndef   _I2C_H
#define   _I2C_H

#include <stdconst.h>


#define MAX_SEND_DATA 		100
#define MAX_RECEIVE_DATA	100
#define piir (*AT91C_PITC_PIIR & AT91C_PITC_CPIV)
#define TIMEOUT         2100

enum power_t {
  NORMAL_OP = 0x0000,
  POWERDOWN = 0x5A00,
  REPROGRAM = 0xA55A
};

extern ULONG     I2CTimerValue;
void I2CInit(void);
void I2CExit(void);
void I2CTransfer(void);
__ramfunc  void I2cHandler(void);
void I2CCtrl(enum power_t);
inline I2cSetTime(void);

#endif
