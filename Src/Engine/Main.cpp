#include "NanoEngine.h"

#define _00 0.0f,0.0f
#define _01 0.0f,1.0f
#define _10 1.0f,0.0f
#define _11 1.0f,1.0f

float vertices[] = {
	-0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  _00,  //0
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  _10,  //1
	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  _11,  //2
	-0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  _01   //3
};

unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3
};

Mesh* plane;
Texture* texture;
 void Start() {
	 plane=BuildMesh(indices, vertices, POSITION_FLAG | COLOR_FLAG | UV_FLAG,SIZEVEC(indices),SIZEVEC(vertices));
	 GLuint vao= genVAO(plane);
	 texture = LoadTexture("Assets/Images/Rat.png", GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
	 printf("Height: %d\nWidht: %d \n", texture->height, texture->widht);
	
	
	 ShaderList* sl = NEW(ShaderList);
	 sl->left = NULL;
	 sl->right = NULL;
	 sl->value = 1;
	 sl->child = NULL;
	 
	 ShaderList* sl1 = NEW(ShaderList);
	 sl1->left = NULL;
	 sl1->right = NULL;
	 sl1->value = 2;
	 sl1->child = NULL;
	 
	 ShaderList* sl2 = NEW(ShaderList);
	 sl2->left = NULL;
	 sl2->right = NULL;
	 sl2->value = 3;
	 sl2->child = NULL;
	 
	 AddShader(sl);
	 AddShader(sl1);
	 AddShader(sl2);

	 VaoList* vl = NEW(VaoList);
	 vl->child = NULL;
	 vl->left = NULL;
	 vl->right = NULL;
	 vl->value = vao;

	 AddVAO(sl1, vl);
	 printf("ShaderCount: %d \n", count_no(ShaderList)(renderTree.shaderList));
	 printf("VaoCount: %d \n", count_no(VaoList)(sl1->child));
}

 void Update() {
	
}