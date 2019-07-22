#ifndef NANO_RENDER_TREE
#define NANO_RENDER_TREE

#include "../GL.h"

typedef struct {
	GLuint Shader;
	GLuint Texture;
	GLuint Vao;
	unsigned int Id;
	unsigned int IndexCount;                                                                          
	mat4 Model = GLM_MAT4_IDENTITY_INIT;
}RenderComponent;

typedef struct ModelList {
	ModelList* prox;	
	mat4* value;
	
	unsigned int id;
};

typedef struct TextureList {
	TextureList* prox;
	ModelList* modelList;

	GLuint value = -1;
	
	unsigned int id;
};

typedef struct VaoList {
	VaoList* prox;
	TextureList* textureList;

	GLuint value = -1;
	
	unsigned int id;
	unsigned int indexCount;
};

typedef struct ShaderList {
	ShaderList* prox;
	VaoList* vaoList;

	GLuint value = -1;
	
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


#endif // !NANO_RENDER_TREE
