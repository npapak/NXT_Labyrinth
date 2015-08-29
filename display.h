#ifndef   DISPLAY
#define   DISPLAY

#include <stdconst.h>

#define   DISPLAY_HEIGHT      64        // Y pixels
#define   DISPLAY_WIDTH       100       // X pixels

void      DisplayInit(void);
void      DisplayOn(UBYTE On);
void      DisplayExit(void);
UBYTE     DisplayUpdateAsync(void);
void      DisplayUpdateSync(void);
void      DisplaySetPixel(UBYTE X,UBYTE Y);
void      DisplayClrPixel(UBYTE X,UBYTE Y);
void      DisplayLineX(UBYTE X1,UBYTE X2,UBYTE Y);
void      DisplayLineY(UBYTE X,UBYTE Y1,UBYTE Y2);
void      DisplayErase(void);
void      DisplayChar(UBYTE On,UBYTE X,UBYTE Y,UBYTE Char);
void      DisplayNum(UBYTE On,UBYTE X,UBYTE Y,UWORD Num);
void      DisplayString(UBYTE X,UBYTE Y,UBYTE *pString);


#endif
