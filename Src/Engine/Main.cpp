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
RenderComponent rc;

 void Start() {
	// plane=BuildMesh(indices, vertices, POSITION_FLAG | COLOR_FLAG | UV_FLAG,SIZEVEC(indices),SIZEVEC(vertices));
	 
	 plane = NEW(Mesh);
	 plane->index = indices;
	 plane->vertex = vertices;
	 plane->flag = POSITION_FLAG | COLOR_FLAG | UV_FLAG;
	 plane->indexCount = SIZEVEC(indices);
	 plane->vertexCount = SIZEVEC(vertices);
	 calculateVertexSize(plane);
	 
	 

	 GLuint vao= genVAO(plane);
	 texture = LoadTexture("Assets/Images/Rat.png", GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
	
	 rc.Vao = vao;
	 rc.Shader = DefaultShader;
	 rc.Texture = texture->id;
	 rc.IndexCount = plane->indexCount;
	
	 AddComponent(&rc);
}

 void Update() {
	 RendTree();
}