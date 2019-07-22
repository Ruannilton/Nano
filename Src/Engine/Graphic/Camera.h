#ifndef NANO_CAMERA
#define NANO_CAMERA

#include "../GL.h"
#include <string.h>

typedef struct {
	vec3 position,front, up;
	mat4 projection;
}Camera;

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
}

__inline void camera_SetCameraPerspective(float fov, float aspectRation,float zNear, float zFar,Camera* cam) {
	glm_perspective(fov, aspectRation, zNear, zFar, cam->projection);
}

__inline void camera_SetCameraOrtho(float x0, float y0, float x1, float y1, float zNear, float zFar, Camera* cam) {
	glm_ortho(x0, y0, x1, y1, zNear, zFar, cam->projection);
}

void camera_ViewProjection(Camera* cam,mat4* view) {
	 static vec3 pos;
	 glm_cross(cam->front, cam->up, pos);
	 glm_normalize(pos);
	 pos[0] *= -cam->position[0];
	 pos[2] = cam->position[2];

	 glm_look(pos, cam->front, cam->up, *view);
	
}
#endif // !NANO_CAMERA
