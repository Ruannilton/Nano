#ifndef NANO_COLOR
#define NANO_COLOR

#include "../GL.h"
#define C_RED 0
#define C_GREEN 1
#define C_BLUE 2
#define C_ALPHA 3

typedef vec4 Color;

#define chColor(R,G,B,A,COLOR) COLOR[C_RED] = R;COLOR[C_GREEN] = G;COLOR[C_BLUE] = B;COLOR[C_ALPHA] =A; 


#endif // !NANO_COLOR
