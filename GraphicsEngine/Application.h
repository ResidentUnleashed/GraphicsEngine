#pragma once
#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Gizmos.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
using glm::vec3;
using glm::vec4;
using glm::mat4;

class Application
{
public:
	Application();
	~Application();

	void Run(const char* title, int width, int height);

private:

	int createWindow(const char* title, int width, int height);
	bool startup();
	void shutdown();
	void update(float deltaTime);
	void draw();

	GLFWwindow * window;

};

