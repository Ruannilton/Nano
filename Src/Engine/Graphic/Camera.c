#include "Camera.h"


void camera_UpdateView(Camera* cam) {
	

	cam->front[0] = (float)(cos(glm_rad(cam->rotation[0])) * cos(glm_rad(cam->rotation[1])));
	cam->front[1] = (float)(sin(glm_rad(cam->rotation[1])));
	cam->front[2] = (float)(sin(glm_rad(cam->rotation[0])) * cos(glm_rad(cam->rotation[1])));
	glm_normalize(cam->front);
	glm_look(cam->position, cam->front, cam->up, cam->view);
}

void camera_Zoom(Camera* cam, double delta) {
	if (cam->fov >= cam->min_fov && cam->fov <= cam->max_fov) {
		cam->fov -= (float)delta;
		
		if (cam->fov < cam->min_fov) cam->fov = cam->min_fov;
		if (cam->fov > cam->max_fov) cam->fov = cam->max_fov;

		glm_perspective(glm_rad(cam->fov), cam->aspectRatio, cam->zNear, cam->zFar, cam->projection);
	}
}

void camera_CreateCamera(Camera* cam, vec3 position) {
	
	cam->position[0] = position[0];
	cam->position[1] = position[1];
	cam->position[2] = position[2];

	cam->up[0] = 0;
	cam->up[1] = 1;
	cam->up[2] = 0;

	cam->front[0] = 0;
	cam->front[1] = 0;
	cam->front[2] = -1;


	cam->rotation[0] = 270;
	cam->rotation[1] = 0;
	cam->rotation[2] = 0;
	
	cam->max_fov = 70;
	cam->min_fov = 1;
	cam->fov = 45;
	cam->zNear = 0.1f;
	cam->zNear = 1000.0f;
	cam-> max_y_angle = 89.0f;
	cam-> min_y_angle = -89.0f;

	glm_look(cam->position, cam->front, cam->up, cam->view);
}

void camera_Translate(Camera* cam, vec3 direction) {
	// Z axis
	vec3 za;
	glm_vec3_mul_s(cam->front, direction[2], za);
	glm_vec3_add(za, cam->position, cam->position);

	// X axis
	vec3 cross;
	glm_cross(cam->front, cam->up, cross);
	glm_normalize(cross);
	glm_vec3_mul_s(cross, direction[0], cross);
	glm_vec3_add(cross, cam->position, cam->position);

	glm_look(cam->position, cam->front, cam->up, cam->view);
}



void camera_Rotate(Camera* cam, vec3 direction) {
	cam->rotation[0] += direction[0];
	cam->rotation[1] += direction[1];
	cam->rotation[2] += direction[2];

	if (cam->rotation[1] > cam->max_y_angle) cam->rotation[1] = cam->max_y_angle;
	if (cam->rotation[1] < cam->min_y_angle) cam->rotation[1] = cam->min_y_angle;
}
