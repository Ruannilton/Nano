#include "Camera.h"


void camera_UpdateView(Camera* cam) {
	
	cam->front.x = (float)(cos(glm_rad(cam->rotation.x)) * cos(glm_rad(cam->rotation.y)));
	cam->front.y = (float)(sin(glm_rad(cam->rotation.y)));
	cam->front.z = (float)(sin(glm_rad(cam->rotation.x)) * cos(glm_rad(cam->rotation.y)));
	glm_normalize(cam->front.arr);
	glm_look(cam->position.arr, cam->front.arr, cam->up.arr, cam->view);
}

void camera_Zoom(Camera* cam, double delta) {
	if (cam->fov >= cam->min_fov && cam->fov <= cam->max_fov) {
		cam->fov -= (float)delta;
		
		if (cam->fov < cam->min_fov) cam->fov = cam->min_fov;
		if (cam->fov > cam->max_fov) cam->fov = cam->max_fov;

		glm_perspective(glm_rad(cam->fov), cam->aspectRatio, cam->zNear, cam->zFar, cam->projection);
	}
}

void camera_SeekMouse(Camera* cam) {
	Vec3 mouse_mov = { (float)mouse_delta_x, (float)mouse_delta_y, 0 };
	camera_Rotate(cam, mouse_mov);
	if (mouse_delta_scroll_y != 0) {
		camera_Zoom(cam, mouse_delta_scroll_y);
	}
}

void camera_CreateCamera(Camera* cam, Vec3 position) {

    cam->position = position;
	cam->up = (Vec3){0,1,0};
	cam->front = (Vec3){ 0,0,-1 };
	cam->rotation = (Vec3){ 270,0,0 };

	cam->max_fov = 70;
	cam->min_fov = 1;
	cam->fov = 45;
	cam->zNear = 0.1f;
	cam->zFar = 1000.0f;
	cam-> max_y_angle = 89.0f;
	cam-> min_y_angle = -89.0f;
	cam->aspectRatio = 800.0f / 600.0f;

	glm_look(cam->position.arr, cam->front.arr , cam->up.arr, cam->view);
}

void camera_Translate(Camera* cam, Vec3 direction) {
	// Z axis
	vec3 za;
	glm_vec3_mul_s(cam->front.arr, direction.y, za);
	glm_vec3_add(za, cam->position.arr, cam->position.arr);

	// X axis
	vec3 cross;
	glm_cross(cam->front.arr, cam->up.arr, cross);
	glm_normalize(cross);
	glm_vec3_mul_s(cross, direction.x, cross);
	glm_vec3_add(cross, cam->position.arr, cam->position.arr);

	glm_look(cam->position.arr, cam->front.arr, cam->up.arr, cam->view);
}



void camera_Rotate(Camera* cam, Vec3 direction) {
	Vec3Sum(cam->rotation, direction);
	if (cam->rotation.y > cam->max_y_angle) cam->rotation.y = cam->max_y_angle;
	if (cam->rotation.y < cam->min_y_angle) cam->rotation.y = cam->min_y_angle;
}
