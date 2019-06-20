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

 void Start() {
	 plane=BuildMesh(indices, vertices, POSITION_FLAG | COLOR_FLAG | UV_FLAG,SIZEVEC(indices),SIZEVEC(vertices));
}

 void Update() {
	 
}