#ifndef NANO_RENDER_TREE
#define NANO_RENDER_TREE

#include "../GL.h"
#include "..//Components/RenderComponent.h"


struct _TransformNode{
	struct _TransformNode* prox;
	mat4 value;
	unsigned int id;
};

typedef struct _TransformNode TransformNode;

struct _TextureNode {
	struct _TextureNode* prox;
	TransformNode* transfChild;
	GLuint value = -1;
	unsigned int id;
};

typedef struct _TextureNode TextureNode;

struct _MeshNode {
	struct _MeshNode* prox;
	TextureNode* textChild;
	GLuint value = -1;
	unsigned int id;
	unsigned int indexCount;
};

typedef struct _MeshNode MeshNode;

struct _ShaderNode {
	struct _ShaderNode* prox;
	MeshNode* meshChild;
	GLuint value = -1;
	unsigned int id;
};

typedef struct _ShaderNode ShaderNode;

typedef struct {
	ShaderNode* shaderList;
	int ShaderCount = 0;
	int VaoCount = 0;
	int TextureCount = 0;
	int ModelCount = 0;
}RenderTree;


RenderTree* RenderTree_Create() {
	RenderTree* rt = NEW(RenderTree);
	rt->shaderList = 0;
	return rt;
}

ShaderNode* AddShader(ShaderNode** node,GLuint value) {
	
	DEBUG("Ponteiro em %u\n", node);
	
	if (*node == NULL) {
		*node = NEW(ShaderNode);
		(*node)->value = value;
		(*node)->id = value;
		(*node)->prox = NULL;
		(*node)->meshChild = NULL;
		return (*node);
	}

	ShaderNode** current = node;
	
	DEBUG("NODE ID %d, PASSED ID %d", (*current)->id, value);
		while (*current != NULL)
		{
			if ((*current)->id == value) {
				DEBUG("SHADER %d JA EXISTE",value);
				return (*current);
			}
			*current = (*current)->prox;
		}
	
	*current = NEW(ShaderNode);
	(*current)->value = value;
	(*current)->id = value;
	(*current)->prox = NULL;
	(*current)->meshChild = NULL;
	
	return (*current);
}

MeshNode* AddMesh(MeshNode** node, GLuint value) {
	MeshNode** current = node;
	if (*current != NULL) {
		while (*current != NULL)
		{
			if ((*current)->id == value) {
				DEBUG("MESH %d JA EXIST",value);
				return (*current);
			}
			(*current) = (*current)->prox;
		}
	}
	(*current) = NEW(MeshNode);
	(*current)->value = value;
	(*current)->id = value;
	(*current)->prox = NULL;
	(*current)->textChild = NULL;
	return (*current);
}

TextureNode* AddTexture(TextureNode** node, GLuint value) {
	TextureNode** current = node;
	if (*current != NULL) {
		while (*current != NULL)
		{
			if ((*current)->id == value) {
				DEBUG("TEXTURE %d JA EXISTE",value);
				return (*current);
			}
			(*current) = (*current)->prox;
		}
	}
	(*current) = NEW(TextureNode);
	(*current)->value = value;
	(*current)->id = value;
	(*current)->prox = NULL;
	(*current)->transfChild = NULL;
	return (*current);
}

void AddTransform(TransformNode** node,mat4 value,GLuint meshID) {
	TransformNode** current = node;
	if ((*current) != NULL) {
		while ((*current) !=NULL)
		{
			if ((*current)->id == meshID) {
				DEBUG("TRANSFORM %d JA EXISTE",meshID);
				return;
			}
			(*current) = (*current)->prox;
		}
	}
	*current = NEW(TransformNode);
	memcpy((*current)->value, value,sizeof(mat4));
	(*current)->id = meshID;
	(*current)->prox = NULL;
}

void RenderTree_AddRenderComponent(RenderTree* rt,RenderComponent* rc) {
	ShaderNode* shader = AddShader(&rt->shaderList, rc->Shader);
	MeshNode* mesh     = AddMesh(&shader->meshChild, rc->Vao);
	TextureNode* tex   = AddTexture(&mesh->textChild, rc->Texture);
	AddTransform(&tex->transfChild, rc->Model,rc->Vao);
}


#endif // !NANO_RENDER_TREE
