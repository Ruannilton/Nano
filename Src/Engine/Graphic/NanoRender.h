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
#include "Lights/Light.h"

#define SHADER_POS_LOC 0
#define SHADER_COLOR_LOC 1
#define SHADER_TEX_LOC 2
#define SHADER_NORM_LOC 3
#define SHADER_MODEL_LOC 4
#define SHADER_VIEW_LOC 5
#define SHADER_PROJ_LOC 6


UNIQUE PointLight pointLight;
UNIQUE DirectionalLight directionalLight;
UNIQUE SpotLight spotLight;

UNIQUE uint window_widht;
UNIQUE uint window_height;
UNIQUE uint render_list_count = 0;

UNIQUE Shader DefaultShader;
UNIQUE Camera currentCamera;
UNIQUE Color BackGroundColor;
UNIQUE RenderComponent* render_list[128];

void initRenderSystem();
void AddToRender(RenderComponent* r);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void RenderScene();

#endif // !NANO_RENDER


