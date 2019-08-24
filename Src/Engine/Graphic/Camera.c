#include "Camera.h"

void camera_ViewProjection(Camera* cam) {
	static vec3 pos;

	cam->front[0] = cos(glm_rad(cam->rotation[0])) * cos(glm_rad(cam->rotation[1]));
	cam->front[1] = sin(glm_rad(cam->rotation[0]));
	cam->front[2] = cos(glm_rad(cam->rotation[0])) * sin(glm_rad(cam->rotation[1]));
	glm_normalize(cam->front);



	glm_look(cam->position, cam->front, cam->up, cam->view);

}

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