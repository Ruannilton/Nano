#ifndef NANO_MONITOR
#define NANO_MONITOR

#include "../Utils.h"

typedef struct {
	string name;
	GLFWmonitor* monitor_ptr;
	GLFWvidmode* modes;
	GLFWvidmode current_mode;
	uint mode_count;
}Monitor;

#endif