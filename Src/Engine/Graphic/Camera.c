#include "Camera.h"


void camera_UpdateView(Camera* cam) {
	

	//cam->front[0] = cos(glm_rad(cam->rotation[0])) * cos(glm_rad(cam->rotation[1]));
	//cam->front[1] = sin(glm_rad(cam->rotation[0]));
	//cam->front[2] = cos(glm_rad(cam->rotation[0])) * sin(glm_rad(cam->rotation[1]));
	//glm_normalize(cam->front);
	glm_look(cam->position, cam->front, cam->up, cam->view);
}

void camera_CreateCamera(Camera* cam, vec3 position) {
	
	cam->position[0] = position[0];
	cam->position[1] = position[1];
	cam->position[2] = position[2];
	cam->rotation[0] = 0;
	cam->rotation[1] = 0;
	cam->rotation[2] = 0;
	cam->up[0] = 0;
	cam->up[1] = 1;
	cam->up[2] = 0;
	cam->front[0] = 0;
	cam->front[1] = 0;
	cam->front[2] = -1;

	glm_look(cam->position, cam->front, cam->up, cam->view);
}

void camera_Translate(Camera* cam, vec3 direction) {
	cam->position[2] -= direction[2];
	
	vec3 x_axis = { 0,0,0 };
	glm_cross(cam->front, cam->up, x_axis);
	x_axis[0] *= direction[0];
	x_axis[1] *= direction[0];
	x_axis[2] *= direction[0];
	glm_normalize(x_axis);

	cam->position[0] += x_axis[0];
	cam->position[1] += x_axis[1];
	cam->position[2] += x_axis[2];
}