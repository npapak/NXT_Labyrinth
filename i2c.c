/**
 * @file i2c.c
 * @brief Implementation of I2C protocol
 * @author Nikos Papakonstantinou <npapak@gmail.com>
 * @version v1.0
 * @date 2015-08-29
 */
#include "AT91SAM7S256.h"
#include  <stdconst.h>
#include  <string.h>
#include  <assert.h>
#include  "i2c.h"
#include  "arm2avr.h"
#include  "pit.h"
#include  "aic.h"


#define BYTES_TO_TX     sizeof(IOTOAVR)
#define BYTES_TO_RX     sizeof(IOFROMAVR)
#define TIMEOUT         2100
#define I2CClk          400000L
#define TIME400KHz      (((OSC/16L)/(I2CClk * 2)) + 1)
#define CLDIV           (((OSC/I2CClk)/2)-3)
#define DEVICE_ADR      0x01
#define COPYRIGHTSTRING "Let's samba nxt arm in arm, (c)LEGO System A/S"
#define COPYRIGHTSTRINGLENGTH 46
const   UBYTE CopyrightStr[] = {"\xCC"COPYRIGHTSTRING};
#define MAX(x,y) (((x)>(y))?(x):(y))
#define piir (*AT91C_PITC_PIIR & AT91C_PITC_CPIV)
#define pimr (*AT91C_PITC_PIMR & AT91C_PITC_CPIV)
#define DISABLEI2cIrqs *AT91C_TWI_IDR = 0x000001C7

// send/receive state machine variables
static enum state_t{
	Rx,
	Tx,
	Init,
	wTx,
	wRx
};

static int firstTime = 1;
static enum state_t volatile State;
ULONG     I2CTimerValue;
IOTOAVR IoToAvr;
IOFROMAVR IoFromAvr;
UBYTE Gout_buf[100];
UBYTE Gin_buf[100];
ULONG total_bytes;
ULONG cnt;

UBYTE checksum(UBYTE* buf,UBYTE len){
	int i;
	UBYTE checkSum = 0;
	for(i=0; i<len; ++i){
		checkSum += buf[i];
	}
	return ~checkSum;
}

inline I2cSetTime(void) {
  I2CTimerValue = piir;
}

inline int I2cCheckTimeout(void) {
		  if (TIMEOUT < ((piir - I2CTimerValue) & AT91C_PITC_CPIV))
                  {
		    return TRUE;
                  }
		  else
                  {
		    return FALSE;
		  }
}

__ramfunc  void I2cHandler(void){
	if( (*AT91C_TWI_SR & AT91C_TWI_TXRDY)!=0  && State==wTx ){

	*AT91C_TWI_THR = Gout_buf[cnt];
	++cnt;
	if( cnt==total_bytes ){
	    State = Rx;
	    *AT91C_TWI_IDR |= AT91C_TWI_TXRDY;
	    //AICInterruptDisable(9); // disable TWI interrupts
	    return;
	}
	if( cnt==total_bytes-1 ){ // last byte
	    *AT91C_TWI_CR  = AT91C_TWI_STOP;
	}
	}
	else if( (*AT91C_TWI_SR & AT91C_TWI_RXRDY)!=0 && State==wRx ){

	Gin_buf[cnt] = *AT91C_TWI_RHR;
	++cnt;
	if( cnt==total_bytes ){
		memcpy( &IoFromAvr, Gin_buf, sizeof(IoFromAvr));
		State = Tx;
		*AT91C_TWI_IDR |= AT91C_TWI_RXRDY;
		//AICInterruptDisable(9);
		return;
	}
	else if( cnt==total_bytes-1 ){
		*AT91C_TWI_CR = AT91C_TWI_STOP;
	}
	}
}


void DataTxInit(UBYTE *buf, UBYTE len) {
	cnt = 0;
	total_bytes = len + 1;
	memcpy(Gout_buf, buf, len);
	Gout_buf[len] = checksum(buf, len);

	*AT91C_TWI_MMR = (DEVICE_ADR << 16) | (0x00 << 12);
	*AT91C_TWI_CR  = AT91C_TWI_MSEN | AT91C_TWI_START;
	*AT91C_TWI_IER |= AT91C_TWI_TXRDY;
	AICInterruptEnable(9, I2cHandler);
	return;
}

void DataRxInit(UBYTE *buf, UBYTE len){
	cnt = 0;
	total_bytes = len + 1;
	*AT91C_TWI_MMR = ( (DEVICE_ADR << 16) | (0x01 << 12) );
	*AT91C_TWI_CR  = AT91C_TWI_MSEN | AT91C_TWI_START;
	*AT91C_TWI_IER |= AT91C_TWI_RXRDY;
	AICInterruptEnable(9, I2cHandler);

	return;
}

void I2CTransfer(void) {
	
// 	DisplayString(0, 40, "Mpika");
// 	DisplayUpdateSync();
	
	if(firstTime){
		State = wTx;
		firstTime = 0;
		DataTxInit( (UBYTE*)CopyrightStr, sizeof(CopyrightStr));
// 		I2cSetTime();
	}
// 	if(I2cCheckTimeout()){
		if(State == Tx){
			State = wTx;
			DataTxInit( (UBYTE*)&IoToAvr, sizeof(IoToAvr) );
		}
		else if(State == Rx){
			State = wRx;
			DataRxInit( (UBYTE*)&IoFromAvr, sizeof(IoFromAvr) );
		}
// 		I2cSetTime();
// 	}
	return;
}

void I2CCtrl(enum power_t p) {
	IoToAvr.Power = p;
	return;
}

#define WAITClk(t) {\
ULONG pit = piir + (t);\
if (pit >= pimr) pit -= pimr;\
	while (piir < pit){;}\
		}

void I2CInit(void){
	//
	// disable I2C on PIO
	// this is called also during an error, so interrupts etc may be enabled
	//
	*AT91C_AIC_IDCR = (1L<<AT91C_ID_TWI);			/* disable AIC irq  */
	DISABLEI2cIrqs;                      			/* disable TWI irq  */
	*AT91C_PMC_PCER  = (1L<<AT91C_ID_TWI);		/* enable TWI Clock */
	*AT91C_PIOA_OER  = AT91C_PA4_TWCK;  		  	/* SCL is output    */
	*AT91C_PIOA_ODR  = AT91C_PA3_TWD;			/* SDA is input     */
	*AT91C_PIOA_MDER = (AT91C_PA4_TWCK | AT91C_PA3_TWD);  /* open drain       */
	*AT91C_PIOA_PPUDR = (AT91C_PA4_TWCK | AT91C_PA3_TWD); /* no pull up       */
	//
	// synch I2C clocks using PIO
	// generate a 400KHz pulse on SCK and wait until both SCK and SDA are high,
	// which means the slave ticks with this clock
	//
	*AT91C_PIOA_PER  = (AT91C_PA4_TWCK | AT91C_PA3_TWD); /* enable PIO control for these pins */
	while(((*AT91C_PIOA_PDSR & AT91C_PA3_TWD) == 0) || ((*AT91C_PIOA_PDSR & AT91C_PA4_TWCK) == 0)){
		*AT91C_PIOA_CODR = AT91C_PA4_TWCK; /* drive SCL Low  */
		WAITClk(TIME400KHz);
		*AT91C_PIOA_SODR = AT91C_PA4_TWCK; /* drive SCL High */
		WAITClk(TIME400KHz);
	}
	//
	// init I2C on PIO
	//
	*AT91C_TWI_CR    =  AT91C_TWI_SWRST;			/* this has to happen before the rest */
	*AT91C_PIOA_PDR   = (AT91C_PA4_TWCK | AT91C_PA3_TWD); /* disable PIO control for these pins */
	*AT91C_PIOA_ASR   = (AT91C_PA4_TWCK | AT91C_PA3_TWD); /* select peripheral A = TWI */
	*AT91C_TWI_CWGR   = (CLDIV | (CLDIV << 8));           /* 400KHz clock    */
	*AT91C_AIC_ICCR   = (1L<<AT91C_ID_TWI);               /* clear AIC irq   */
	AT91C_AIC_SVR[AT91C_ID_TWI] = (unsigned int)I2cHandler;
	AT91C_AIC_SMR[AT91C_ID_TWI] = ((AT91C_AIC_PRIOR_HIGHEST) | (AT91C_AIC_SRCTYPE_INT_EDGE_TRIGGERED));
	*AT91C_AIC_IECR   = (1L<<AT91C_ID_TWI);               /* Enables AIC irq */

	IoToAvr.Power     = 0;

	State = Init;

	return;
}

void I2CExit(void) {
	DISABLEI2cIrqs;
	*AT91C_AIC_IDCR   = (1L<<AT91C_ID_TWI);               /* Disable AIC irq  */
	*AT91C_AIC_ICCR   = (1L<<AT91C_ID_TWI);               /* Clear AIC irq    */
	*AT91C_PMC_PCDR   = (1L<<AT91C_ID_TWI);               /* Disable clock    */
	*AT91C_PIOA_MDER  = (AT91C_PA4_TWCK | AT91C_PA3_TWD); /* Open drain       */
	*AT91C_PIOA_PPUDR = (AT91C_PA4_TWCK | AT91C_PA3_TWD); /* no pull up       */
	*AT91C_PIOA_PER   = (AT91C_PA4_TWCK | AT91C_PA3_TWD); /* Disable peripheal*/
}
