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
#include "../Architecture/Scene.h"

#define SHADER_POS_LOC 0
#define SHADER_COLOR_LOC 1
#define SHADER_TEX_LOC 2
#define SHADER_NORM_LOC 3
#define SHADER_MODEL_LOC 4
#define SHADER_VIEW_LOC 5
#define SHADER_PROJ_LOC 6


UNIQUE Scene* current_scene;
UNIQUE Camera* current_camera;
UNIQUE uint window_widht;
UNIQUE uint window_height;



void Renderer_Init();

void Renderer_SetScene(Scene* scn);


inline RenderComponent Renderer_AddComponent(uint shader, uint mesh) {
	return Scene_Add_Render_Component(current_scene, shader, mesh);
}



void RenderScene();

#endif // !NANO_RENDER


