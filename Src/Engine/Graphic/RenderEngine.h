#ifndef NANO_RENDER_ENGINE
#define NANO_RENDER_ENGINE

#include "Color.h"
#include "Shader.h"
#include "RenderTree.h"
#include "../Core/NanoIO.h"

Color BackGroundColor{ 1, 1, 1, 1 };
Shader DefaultShader;
uint window_widht;
uint window_height;

mat4 Camera = GLM_MAT4_IDENTITY_INIT;
mat4 projection = GLM_MAT4_IDENTITY_INIT;



#endif // !NANO_RENDER_ENGINE