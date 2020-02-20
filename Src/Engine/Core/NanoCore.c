#include "NanoCore.h"

void Nano_Create() {
	if (!glfwInit()) {
		DEBUG("Error Glfw Init");
		return NULL;
	}

    nano = NEW(Nano);
	
	Nano_UpdateMonitors(nano);

	nano->window_widht = nano->main_monitor->current_mode.width;
	nano->window_height = nano->main_monitor->current_mode.height;
	nano->window = 0;
	nano->run = 1;
	nano->title = (char*)malloc(sizeof(char) * 12);
	nano->progam_path = (char*)malloc(sizeof(char) * FILENAME_MAX);
	nano->multisamples_level = 2;
	nano->progam_path = GetCurrentDir(nano->progam_path, sizeof(char) * FILENAME_MAX);
	if(nano->title) strcpy(nano->title, "Nano Engine");
	
}

void Nano_UpdateMonitors() {
	uint count = 0;
	GLFWmonitor** moni = glfwGetMonitors(&count);
	nano->monitors = Vector_Create(Monitor, count);
	if (!moni) {
		DEBUG_C(ANSI_RED, "Monitor not founded");
	}
	else {
		int i;
		for (i = 0; i < count; i++) {
			Monitor* m = Vector_Push(Monitor, &nano->monitors, NULL);
			m->name = glfwGetMonitorName(moni[i]);
			m->monitor_ptr = moni[i];
			m->modes = glfwGetVideoModes(moni[i], &(m->mode_count));
			m->current_mode = *glfwGetVideoMode(moni[i]);
		}
		nano->main_monitor = Vector_Get(Monitor, &nano->monitors, 0);
	}

}

void Nano_CreateWindow() {
	glfwWindowHint(GLFW_SAMPLES, nano->multisamples_level);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RED_BITS, nano->main_monitor->current_mode.redBits);
	glfwWindowHint(GLFW_GREEN_BITS, nano->main_monitor->current_mode.greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, nano->main_monitor->current_mode.blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, nano->main_monitor->current_mode.refreshRate);
	glfwSwapInterval(1);

	nano->window = glfwCreateWindow(nano->window_widht, nano->window_height, nano->title, NULL, NULL);
	glViewport(0, 0, nano->window_widht, nano->window_height);

	glfwMakeContextCurrent(nano->window);

	if (glewInit() != GLEW_OK) DEBUG("Error Init Glew");
}

void Nano_Delete() {
	if (!nano) return;
	free(nano);
}

void TimeUpdate() {
	current_time = glfwGetTime();
	delta_time = (float)(current_time - last_time);
	last_time = current_time;
}

void monitorChangeCallback(GLFWmonitor* monitor, int event) {
	string name = glfwGetMonitorName(monitor);
	if (event == GLFW_CONNECTED)
	{
		DEBUG_C(ANSI_LIGHT_GREEN, "Monitor %s connected!",name);
	}
	else if (event == GLFW_DISCONNECTED)
	{
		DEBUG_C(ANSI_RED, "Monitor %s disconnected!",name);
	}
	Nano_UpdateMonitors(nano);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	nano->window_widht = width;
	nano->window_height = height;
	glViewport(0, 0, width, height);
}

void Nano_SetWindowSize(uint width, uint height) {
	nano->window_widht = width;
	nano->window_height = height;
	if (nano->window) {
		glfwSetWindowSize(nano->window, width, height);
	}
}

void Nano_TogleFullScreen() {
	if (!fullScreen) {
		glfwSetWindowMonitor(nano->window, nano->main_monitor->monitor_ptr, 0, 0, nano->main_monitor->current_mode.width, nano->main_monitor->current_mode.height, nano->main_monitor->current_mode.refreshRate);
		fullScreen = 1;
	}
	else {
		fullScreen = 0;
		glfwSetWindowMonitor(nano->window, NULL, 0, 30, nano->window_widht, nano->window_height-30, nano->main_monitor->current_mode.refreshRate);
	}
}

void Nano_SetupOpenGL() {
	
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwSetInputMode(nano->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetKeyCallback(nano->window, Keyboard_Callback);
	glfwSetCursorPosCallback(nano->window, Mouse_PosCallback);
	glfwSetScrollCallback(nano->window, Mouse_ScrollCallback);
	glfwSetMouseButtonCallback(nano->window, Mouse_ButtonCallback);
	glfwSetFramebufferSizeCallback(nano->window, framebufferSizeCallback);
	glfwSetMonitorCallback(monitorChangeCallback);
	Input_BindContext(nano->window);
}

void Show_Info() {
	string vendor = glGetString(GL_VENDOR);
	string renderer = glGetString(GL_RENDERER);
	
	DEBUG_C(ANSI_BLUE,"Program path: %s\n", nano->progam_path);
	DEBUG_C(ANSI_BLUE, "%s %s", vendor, renderer);
	DEBUG_C(ANSI_BLUE, "\nMonitors:");
	
	Vec_Iterator iter_moni = Vec_Iterator_Get(&nano->monitors);

	while (Vec_Iterator_Next(&iter_moni)) {
		Monitor* m = iter_moni.data;
		DEBUG_C(ANSI_BLUE, "%s", m->name);
	}
	DEBUG_C(ANSI_BLUE, "\nCurrent monitor:");
	DEBUG_C(ANSI_BLUE, "Name: %s\nRefreseh Rate: %d Hz\nColor Bits: %d %d %d", nano->main_monitor->name, nano->main_monitor->current_mode.refreshRate, nano->main_monitor->current_mode.redBits, nano->main_monitor->current_mode.greenBits, nano->main_monitor->current_mode.blueBits);

	DEBUG("");
}

