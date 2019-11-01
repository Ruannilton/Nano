#ifndef NANO_CAMERA
#define NANO_CAMERA

#include "GL.h"
#include <string.h>

typedef struct {
	vec3 position;
	vec3 front;
	vec3 up;

	vec3 rotation;

	mat4 projection;
	mat4 view;
}Camera;



__inline void camera_SetCameraPerspective(float fov, float aspectRation,float zNear, float zFar,Camera* cam) {
	glm_perspective(fov, aspectRation, zNear, zFar, cam->projection);
}

__inline void camera_SetCameraOrtho(float x0, float y0, float x1, float y1, float zNear, float zFar, Camera* cam) {
	glm_ortho(x0, y0, x1, y1, zNear, zFar, cam->projection);
}

void camera_UpdateView(Camera* cam);
void camera_CreateCamera(Camera* cam, vec3 position);
void camera_Translate(Camera* cam, vec3 direction);
#endif