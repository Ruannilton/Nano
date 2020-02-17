#ifndef NANO_CAMERA
#define NANO_CAMERA

#include "../Utils.h"
#include "../Core/NanoCore.h"
#include <string.h>

typedef struct {
	Vec3 position, front, up, rotation;

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
	uint projection_changed;
}Camera;



__inline void Camera_SetCameraPerspective(float fov, float aspectRatio,float zNear, float zFar,Camera* cam) {
	cam->fov = fov;
	cam->aspectRatio = aspectRatio;
	cam->zNear = zNear;
	cam->zFar = zFar;
	cam->projection_changed = 1;
	glm_perspective(glm_rad(fov), aspectRatio, zNear, zFar, cam->projection);
}

__inline void Camera_SetCameraOrtho(float x0, float y0, float x1, float y1, float zNear, float zFar, Camera* cam) {
	glm_ortho(x0, y0, x1, y1, zNear, zFar, cam->projection);
	cam->projection_changed = 1;
}

void Camera_SeekMouse(Camera* cam);
void Camera_Zoom(Camera* cam, double delta);
void Camera_UpdateView(Camera* cam);
void Camera_CreateCamera(Camera* cam, Vec3 position);
void Camera_SetPosition(Camera* cam, Vec3 position);
void Camera_Translate(Camera* cam, Vec3 direction);
void Camera_Rotate(Camera* cam, Vec3 direction);


#endif