/**
 * @file led.c
 * @brief Implementation of led actions
 * @author Nikos Papakonstantinou <npapak@gmail.com>
 * @version v1.0
 * @date 2015-08-29
 */
#include <stdconst.h>
#include "AT91SAM7S256.h"
#include "led.h"

#define DIGIA0 (23) // Port 1 pin 5 (yellow)
#define DIGIA1 (18) // Port 1 pin 6 (blue)
#define DIGIB0 (28) // Port 2 pin 5
#define DIGIB1 (19) // Port 2 pin 6
#define DIGIC0 (29) // Port 3 pin 5
#define DIGIC1 (20) // Port 3 pin 6
#define DIGID0 (30) // Port 4 pin 5
#define DIGID1 (2)  // Port 4 pin 6

void LED(UBYTE port, UBYTE state) {
        ULONG lport;
        switch(port){
        case 0: lport = (1<<DIGIA0); break;
        case 1: lport = (1<<DIGIB0); break;
        case 2: lport = (1<<DIGIC0); break;
        case 3: lport = (1<<DIGID0); break;
        default: lport = (1<<DIGID0); break;
        }
        *AT91C_PIOA_PER = lport;
        *AT91C_PIOA_OER = lport;
        if(state == 0) /* turn off */ { *AT91C_PIOA_CODR = lport;}  /* port x pin y at 0.0 v (enable this line OR the next)*/
        else /* turn on */ {*AT91C_PIOA_SODR = lport;} /* port x pin y (blue) at 3.25-3.27 v (GND is on pin 2 (black)) */
}

void LedSwitchOn(UBYTE port){ LED(port, 1); }
void LedSwitchOff(UBYTE port){ LED(port, 0); }
