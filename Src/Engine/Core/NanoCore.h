#ifndef NANO_CORE
#define NANO_CORE

#include "../Utils.h"
#include "NanoIO.h"
#include "NanoInput.h"

typedef struct {
	GLFWwindow* window;
	char* title;
	char* progam_path;
	unsigned int windowWidht, windowHeight;
	unsigned int run;
}Nano;

UNIQUE Nano* NanoApplication;
UNIQUE float delta_time = 0;
UNIQUE double last_time = 0;
UNIQUE double current_time = 0;

extern void Setup();
extern void Loader();
extern void Start();
extern void Update();
extern void Cleanup();


Nano* Nano_Create();

void framebufferSizeCallback(GLFWwindow* window, int width, int height);

void TimeUpdate();

void Nano_SetupOpenGL(Nano* NanoApplication);

void Nano_Delete(Nano* nano);

#endif // !NANO_CORE
