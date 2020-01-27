#ifndef NANO_CAMERA
#define NANO_CAMERA

#include "GL.h"
#include <string.h>

typedef struct {
	vec3 position, front, up, rotation;

	float max_y_angle;
	float min_y_angle;
	float max_fov;
	float min_fov;
	float fov;
	float aspectRatio;
	float zNear;
	float zFar;

	mat4 projection;
	mat4 view;
}Camera;



__inline void camera_SetCameraPerspective(float fov, float aspectRatio,float zNear, float zFar,Camera* cam) {
	cam->fov = fov;
	cam->aspectRatio = aspectRatio;
	cam->zNear = zNear;
	cam->zFar = zFar;
	glm_perspective(glm_rad(fov), aspectRatio, zNear, zFar, cam->projection);
}

__inline void camera_SetCameraOrtho(float x0, float y0, float x1, float y1, float zNear, float zFar, Camera* cam) {
	glm_ortho(x0, y0, x1, y1, zNear, zFar, cam->projection);
}

void camera_Zoom(Camera* cam, double delta);
void camera_UpdateView(Camera* cam);
void camera_CreateCamera(Camera* cam, vec3 position);
void camera_Translate(Camera* cam, vec3 direction);
void camera_Rotate(Camera* cam, vec3 direction);


#endif