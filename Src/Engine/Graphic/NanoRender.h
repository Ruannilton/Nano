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


UNIQUE Color BackGroundColor;
UNIQUE Shader DefaultShader;
UNIQUE uint window_widht;
UNIQUE uint window_height;
UNIQUE Camera currentCamera;

void initRenderSystem();
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void RenderScene();

#endif // !NANO_RENDER


