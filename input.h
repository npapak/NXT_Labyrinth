#ifndef   _INPUT_H
#define   _INPUT_H

#include <stdconst.h>

enum input_states_t{
    NO_VALUE,
    TOUCH_PRESSED,
    TOUCH_NOTPRESSED,
    MIC_LOUD,
    MIC_QUIET,
    LIGHT_RED,
    LIGHT_GREEN,
    LIGHT_BLUE,
    LIGHT_WHITE,
    LIGHT_BLACK
};

void InputInit(void);
void InputExit(void);
enum input_states_t InputGetSensorValue(UBYTE port);

#endif
