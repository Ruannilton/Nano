#pragma once

#include "GL.h"
#include <string.h>

typedef struct {
	vec3 position,rotation,front, up;
	mat4 projection;
}Camera;

void camera_CreateCamera(Camera* cam, vec3 position) {	
	cam->position[0] = position[0];
	cam->position[1] = position[1];
	cam->position[2] = position[2];
	cam->rotation[0] = 80;
	cam->rotation[1] = 15;
	cam->rotation[2] = 0;
	cam->up[0] = 0;
	cam->up[1] = 1;
	cam->up[2] = 0;
	cam->front[0] = 0;
	cam->front[1] = 0;
	cam->front[2] = -1;
}

__inline void camera_SetCameraPerspective(float fov, float aspectRation,float zNear, float zFar,Camera* cam) {
	glm_perspective(fov, aspectRation, zNear, zFar, cam->projection);
}

__inline void camera_SetCameraOrtho(float x0, float y0, float x1, float y1, float zNear, float zFar, Camera* cam) {
	glm_ortho(x0, y0, x1, y1, zNear, zFar, cam->projection);
}

void camera_ViewProjection(Camera* cam,mat4* view) {
	 static vec3 pos;

	 cam->front[0] = cos(glm_rad(cam->rotation[0])) * cos(glm_rad(cam->rotation[1]));
	 cam->front[1] = sin(glm_rad(cam->rotation[0]));
	 cam->front[2] = cos(glm_rad(cam->rotation[0])) * sin(glm_rad(cam->rotation[1]));
	 glm_normalize(cam->front);
	 
	 

	 glm_look(cam->position, cam->front, cam->up, *view);
	
}

