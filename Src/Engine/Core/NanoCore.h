#ifndef NANO_CORE
#define NANO_CORE

#include "../Utils.h"
#include "NanoIO.h"
#include "NanoInput.h"
#include "../Architecture/Monitor.h"
#include "../DataStructures/dynamic_vector.h"

typedef struct {
	GLFWwindow* window;
	Monitor* main_monitor;
	Vector monitors;
	char* title;
	char* progam_path;
	unsigned int window_widht, window_height;
	unsigned int run;
	unsigned int multisamples_level;
}Nano;

UNIQUE Nano* nano;
UNIQUE uint fullScreen = 0;
UNIQUE float delta_time = 0;
UNIQUE double last_time = 0;
UNIQUE double current_time = 0;

extern void Setup();
extern void Loader();
extern void Start();
extern void Update();
extern void Cleanup();


void framebufferSizeCallback(GLFWwindow* window, int width, int height);

void monitorChangeCallback(GLFWmonitor* monitor, int event);

void TimeUpdate();

void Nano_Create();

void Nano_CreateWindow();

void Nano_SetWindowSize(uint widht, uint height);

void Nano_TogleFullScreen();

void Nano_SetupOpenGL();

void Nano_Delete();

void Nano_UpdateMonitors();

void Show_Info();

#endif // !NANO_CORE
