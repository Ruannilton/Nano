#ifndef NANO_RENDER_ENGINE
#define NANO_RENDER_ENGINE

#include "Color.h"
#include "Shader.h"
#include "RenderTree.h"
#include "../Core/NanoIO.h"

Color BackGroundColor{ 0, 0.5f, 1, 1 };
Shader DefaultShader;
uint window_widht;
uint window_height;

mat4 Camera = GLM_MAT4_IDENTITY_INIT;
mat4 projection = GLM_MAT4_IDENTITY_INIT;

void initRenderSystem() {
	
	glm_perspective(45.0f, 840 / 600, 0.1f, 1000.0f, projection);
	glm_translate(Camera, vec3{ 0,0,-5 });
	render = NEW(RenderTree);
	render->shaderList = NULL;
	render->ModelCount = 0;
	render->ShaderCount = 0;
	render->TextureCount = 0;
	render->VaoCount = 0;
}

void RendTree() {
	ShaderList* sl = render->shaderList;
	VaoList* vao = NULL;
	TextureList* tex = NULL;
	ModelList* model = NULL;

	while (sl != NULL)
	{


		glUseProgram(sl->value);
		glUniformMatrix4fv(glGetUniformLocation(sl->value, "projection"), 1, GL_FALSE, projection[0]);
		glUniformMatrix4fv(glGetUniformLocation(sl->value, "view"), 1, GL_FALSE, Camera[0]);
		vao = sl->vaoList;
		int indexC = 0;
		
		
		while (vao != NULL)
		{
			glBindVertexArray(vao->value);

			tex = vao->textureList;
			indexC = vao->indexCount;
		
			while (tex != NULL)
			{

				glBindTexture(GL_TEXTURE_2D, tex->value);
				model = tex->modelList;

				while (model != NULL)
				{

					glUniformMatrix4fv(glGetUniformLocation(sl->value, "model"), 1, GL_FALSE, **(model->value));
					glDrawElements(GL_TRIANGLES, indexC, GL_UNSIGNED_INT, 0);

					model = model->prox;
				}
				tex = tex->prox;
			}
			vao = vao->prox;
		}
		sl = sl->prox;

	}

}

#endif // !NANO_RENDER_ENGINE