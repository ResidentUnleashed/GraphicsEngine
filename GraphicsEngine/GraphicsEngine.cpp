#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Gizmos.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Application.h"


using glm::vec3;
using glm::vec4;
using glm::mat4;


int main()
{
	Application* app = new Application();
	app->Run("Graphics", 1280, 720);


    return 0;
}

