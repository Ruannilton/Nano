#ifndef NANO_RENDER
#define NANO_RENDER

#include "Color.h"
#include "Camera.h"
#include "RenderTree.h"
#include "Shader/Shader.h"

#include "../Core/NanoIO.h"
#include "../Components/RenderComponent.h"
#include "..//Storage/DataStructures/RenderList.h"

#define UNIFORM_MODEL_LOCATION 5
#define UNIFORM_VIEW_LOCATION 6
#define UNIFORM_PROJECTION_LOCATION 7

Color BackGroundColor{ 0, 0.5f, 1, 1 };
NanoShader DefaultShader;
uint window_widht;
uint window_height;


RenderTree* staticSceneTree = 0;
RenderList* staticRenderList = 0;
RenderComponent* renders[256];
Camera currentCamera;
mat4 view;
int index_renders = 0;

void initRenderSystem() {
	glViewport(0, 0, window_widht, window_height);
	vec3 pos = { 0,0,0 };
	camera_CreateCamera(&currentCamera, pos);
	camera_SetCameraPerspective(glm_rad(70.0f), ((float)window_widht) / window_height, 0.1f, 1000.0f, &currentCamera);
	staticSceneTree = RenderTree_Create();
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void AddRenderComponent(RenderComponent* cmp) {
	RenderList_Add(&staticRenderList,cmp);
}


__inline void RenderStaticTree() {
	ShaderNode* shader = staticSceneTree->shaderList;
	MeshNode* mesh = 0;
	TextureNode* tex = 0;
	TransformNode* transf = 0;

	register GLuint shaderV = 0;
	register GLuint modelLoc = 0;
	
	while (shader != 0)
	{
		shaderV = shader->value;
		glUseProgram(shaderV);
		glUniformMatrix4fv(glGetUniformLocation(shaderV, "projection"), 1, GL_FALSE, currentCamera.projection[0]);
		glUniformMatrix4fv(glGetUniformLocation(shaderV, "view"), 1, GL_FALSE, view[0]);
		modelLoc = glGetUniformLocation(shaderV, "model");
		mesh = shader->meshChild;
		while (mesh !=0)
		{
			glBindVertexArray(mesh->value);
			tex = mesh->textChild;
			
			while (tex != 0) {
				glBindTexture(shaderV, tex->value);
				transf = tex->transfChild;
			
				while (transf !=0)
				{
					glUniformMatrix4fv(modelLoc, 1, GL_FALSE, *(transf->value));
					glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_INT, 0);
					transf = transf->prox;
				}
				tex = tex->prox;
			}
			mesh = mesh->prox;
		}
		shader = shader->prox;

	}

}

__inline void RenderVector() {
	int i = 0;
	mat4 view;
	camera_ViewProjection(&currentCamera,&view);
	
	for (; i < index_renders; i++) {
		
		glUseProgram(renders[i]->Shader);
		glUniformMatrix4fv(glGetUniformLocation(renders[i]->Shader, "projection"), 1, GL_FALSE, currentCamera.projection[0]);
		glUniformMatrix4fv(glGetUniformLocation(renders[i]->Shader, "view"), 1, GL_FALSE, view[0]);
		glUniformMatrix4fv(glGetUniformLocation(renders[i]->Shader, "model"), 1, GL_FALSE, *(renders[i]->Model));

		glBindVertexArray(renders[i]->Vao);		
		glBindTexture(renders[i]->Shader, renders[i]->Texture);
		glDrawElements(GL_TRIANGLES, renders[i]->IndexCount, GL_UNSIGNED_INT, 0);
		
	}
}

__inline void RenderStaticList() {
	RenderNode* node = staticRenderList;

	while (node != 0) {
		Components* renders = node->renders;
		glUseProgram(node->ShaderID);
		glUniformMatrix4fv(UNIFORM_PROJECTION_LOCATION, 1, GL_FALSE, currentCamera.projection[0]);
		glUniformMatrix4fv(UNIFORM_VIEW_LOCATION, 1, GL_FALSE, view[0]);
		
		if(DefaultShader.OnUse!=0)DefaultShader.OnUse();
		
		while (renders != 0) {
			glUniformMatrix4fv(UNIFORM_MODEL_LOCATION, 1, GL_FALSE, *(renders->comp->Model));
			glBindVertexArray(renders->comp->Vao);
			glBindTexture(node->ShaderID, renders->comp->Texture);
			glDrawElements(GL_TRIANGLES, renders->comp->IndexCount, GL_UNSIGNED_INT, 0);
			renders = renders->prox;
		}
		node = node->prox;
	}

}

void RenderScene() {
	
	camera_ViewProjection(&currentCamera,&view);
	RenderStaticList();
}

#endif // !NANO_RENDER_ENGINE