/**
 * @file button.c
 * @brief Implementation of button actions
 * @author Nikos Papakonstantinou <npapak@gmail.com>
 * @version v1.0
 * @date 2015-08-29
 */
#include "button.h"
#include "arm2avr.h"
#include "i2c.h"

void   ButtonInit(void){
	IoFromAvr.Buttons = BUTTON_NONE;
}

void   ButtonExit(void){
	return;
}

enum button_t ButtonRead(void){
	UWORD value = IoFromAvr.Buttons;

	if( value == 0 )
		return BUTTON_NONE;
	else if( value>0x3E4 && value<0x40F )
		return BUTTON_EXIT;
	else if( value>0x7F0 && value<0x80F )
		return BUTTON_ENTER;
	else if( value>0x187 && value<0x1A6 )
		return BUTTON_RIGHT;
	else if( value>0x070 && value<0x08F )
		return BUTTON_LEFT;
	else if( value>0xBF0 && value<0xC0E )
		return BUTTON_ENTER | BUTTON_EXIT;
	else if( value>0x3C9 && value<0x3E4 )
		return BUTTON_RIGHT | BUTTON_EXIT;
	else if( value>0x985 && value<0x9A5 )
		return BUTTON_RIGHT | BUTTON_ENTER;
	else if( value>0x3A0 && value<0x3C8 )
		return BUTTON_LEFT | BUTTON_EXIT;
	else if( value>0x86E && value<0x87F )
		return BUTTON_LEFT | BUTTON_ENTER;
	else if( value>0x0A4 && value<0x0C8 )
		return BUTTON_LEFT | BUTTON_RIGHT;
	else if( value>0xBC0 && value<0xBEF )
		return BUTTON_RIGHT | BUTTON_ENTER | BUTTON_EXIT;
	else if( value>0xB80 && value<0xBBF )
		return BUTTON_LEFT  | BUTTON_ENTER | BUTTON_EXIT;
	else if( value>0x360 && value<0x3A0 )
		return BUTTON_LEFT | BUTTON_RIGHT | BUTTON_EXIT;
	else if( value>0x8A6 && value<0x8BF )
		return BUTTON_LEFT | BUTTON_RIGHT | BUTTON_ENTER;
	else if( value>0xB50 && value<0xB7F )
		return BUTTON_LEFT | BUTTON_RIGHT | BUTTON_ENTER | BUTTON_EXIT;
	else
		return BUTTON_NONE;
}
