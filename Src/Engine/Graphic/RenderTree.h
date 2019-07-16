#ifndef NANO_RENDER_TREE
#define NANO_RENDER_TREE

#include "../GL.h"
typedef struct {
	unsigned int Shader;
	unsigned int Texture;
	unsigned int Id;
	unsigned int IndexCount;
	GLuint Vao = -1;
	mat4 Model = GLM_MAT4_IDENTITY_INIT;
}RenderComponent;

typedef struct ModelList {
	ModelList* prox;
	ModelList* end;
	mat4* value;
	unsigned int id;
};

typedef struct TextureList {
	TextureList* prox;
	TextureList* end;
	GLuint value = -1;
	ModelList* modelList;
	unsigned int id;
};

typedef struct VaoList {
	VaoList* prox;
	VaoList* end;
	GLuint value = -1;
	TextureList* textureList;
	unsigned int id;
	unsigned int indexCount;
};

typedef struct ShaderList {
	ShaderList* prox;
	ShaderList* end;
	GLuint value = -1;
	VaoList* vaoList;
	unsigned int id;
};

typedef struct {
	ShaderList* shaderList;
	int ShaderCount = 0;
	int VaoCount = 0;
	int TextureCount = 0;
	int ModelCount = 0;
}RenderTree;

RenderTree* render;

void AddModel(TextureList* tl, mat4* model) {
	ModelList* last = tl->modelList->end->prox;
	last = NEW(ModelList);
	last->id = tl->id;
	last->prox = NULL;
	last->value = model;
	tl->modelList->end = last;
}
void AddTexture(VaoList* vl, unsigned int* value, mat4* model) {
	TextureList* tl = vl->textureList;
	while (*value != tl->value && tl->prox != NULL)
	{
		tl = tl->prox;
	}

	if (*value == tl->value) {
		tl->id = vl->id;
		AddModel(tl, model);
	}
	else
	{
		tl->prox = NEW(TextureList);
		tl->prox->id = vl->id;
		AddModel(tl->prox, model);
	}
}
void AddVao(ShaderList* sl, unsigned int* value, unsigned int* texValue, unsigned int indexCount, mat4* model) {
	VaoList* vl = sl->vaoList;
	while (*value != vl->value && vl->prox != NULL) {
		vl = vl->prox;
	}

	if (*value == vl->value) { //se este vao ja existir
		vl->id = sl->id;
		AddTexture(vl, texValue, model);
	}
	else
	{
		vl->prox = NEW(VaoList);
		vl->prox->id = sl->id;
		AddTexture(vl->prox, texValue, model);
	}
}
void AddComponent(RenderComponent* comp) {

	if (render->shaderList == NULL) {
		ModelList* ml = NEW(ModelList);
		ml->prox = 0;
		ml->value = &comp->Model;
		ml->id = comp->Id;

		TextureList* tl = NEW(TextureList);
		tl->prox = 0;
		tl->value = comp->Texture;
		tl->modelList = ml;
		tl->id = comp->Id;

		VaoList* vl = NEW(VaoList);
		vl->prox = 0;
		vl->value = comp->Vao;
		vl->textureList = tl;
		vl->id = comp->Id;
		vl->indexCount = comp->IndexCount;

		ShaderList* sl = NEW(ShaderList);
		sl->prox = 0;
		sl->value = comp->Shader;
		sl->vaoList = vl;
		sl->id = comp->Id;

		render->shaderList = sl;
	}

	//caso n seja vazia
	ShaderList* sl = render->shaderList;
	while (comp->Shader != sl->value && sl->prox != NULL) {
		sl = sl->prox;
	}

	if (comp->Shader == sl->value) {
		sl->id = comp->Id;
		AddVao(sl, &comp->Vao, &comp->Texture, comp->IndexCount, &comp->Model);
	}
	else
	{
		sl->prox = NEW(ShaderList);
		sl->prox->id = comp->Id;
		AddVao(sl->prox, &comp->Vao, &comp->Texture, comp->IndexCount, &comp->Model);
	}
}



#endif // !NANO_RENDER_TREE
