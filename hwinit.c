/**
 * @file hwinit.c
 * @brief Hardware Initialization
 * @author Nikos Papakonstantinou <npapak@gmail.com>
 * @version v1.0
 * @date 2015-08-29
 */
#include "AT91SAM7S256.h"
#include "hwinit.h"

void HardwareInit(void){
  *AT91C_RSTC_RMR = 0xA5000401;         // configure reset controller mode register
  *AT91C_PMC_PCER = (1L<<AT91C_ID_PIOA);// enable peripheral clock for PIO
}
