#ifndef NANO_ENGINE
#define NANO_ENGINE

#include "Utils.h"
#include "Core/NanoCore.h"
#include "Graphic/NanoRender.h"



UNIQUE Nano* NanoApplication;
UNIQUE float delta_time = 0;
UNIQUE double last_time = 0;
UNIQUE double current_time = 0;

extern void Start();
extern void Update();


void framebufferSizeCallback(GLFWwindow* window, int width, int height);

void TimeUpdate();

void SetupOpenGL(Nano* NanoApplication);

#endif // !NANO_ENGINE



