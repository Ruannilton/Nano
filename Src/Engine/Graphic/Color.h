#ifndef NANO_COLOR
#define NANO_COLOR

#include "../Utils.h"
#define C_RED 0
#define C_GREEN 1
#define C_BLUE 2
#define C_ALPHA 3

typedef union
{
	vec4 arr;
	struct 
	{
		float Red, Green, Blue, Alpha;
	};
	struct
	{
		float R, G, B, A;
	};
} Color;

#define setColor(R,G,B,A,COLOR) COLOR.Red = R;COLOR.Green = G;COLOR.Blue = B;COLOR.Alpha =A; 



#endif // !NANO_COLOR





