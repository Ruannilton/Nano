#ifndef NANO_RENDER
#define NANO_RENDER

#include "..//Utils.h"
#include "..//Core/NanoIO.h"
#include "Color.h"
#include "Camera.h"
#include "Material.h"
#include "Mesh.h"
#include "Shader.h"
#include "RenderComponent.h"

#define SHADER_POS_LOC 0
#define SHADER_COLOR_LOC 1
#define SHADER_TEX_LOC 2
#define SHADER_NORM_LOC 3
#define SHADER_MODEL_LOC 4
#define SHADER_VIEW_LOC 5
#define SHADER_PROJ_LOC 6

UNIQUE Color BackGroundColor;
UNIQUE Color AmbientLight;
UNIQUE float AmbientIntensity;
UNIQUE Shader DefaultShader;
UNIQUE uint window_widht;
UNIQUE uint window_height;
UNIQUE Camera currentCamera;
UNIQUE RenderComponent render[5];

void initRenderSystem();
void AddToRender(RenderComponent* r);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void RenderScene();

#endif // !NANO_RENDER


