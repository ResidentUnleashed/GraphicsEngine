#include "Application.h"



Application::Application()
{
}


Application::~Application()
{
}

int Application::Run(const char* title, int width, int height, bool fullscreen, const char* configFilePath)
{
	return 0;
}



//int Application::createWindow(const char* title, int width, int height)
//{
//	if (glfwInit() == false) /* If it hasn't initialised, return -1*/
//		return -1;
//
//
//	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
//
//	if (window == nullptr)
//	{
//		glfwTerminate();
//		return -2;
//	}
//
//	glfwMakeContextCurrent(window);
//
//
//	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
//	{
//		glfwDestroyWindow(window);
//		glfwTerminate();
//		return -3;
//	}
//
//	aie::Gizmos::create(100, 100, 100, 100);
//	mat4 view = glm::lookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
//	mat4 projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);
//
//
//	auto major = ogl_GetMajorVersion();
//	auto minor = ogl_GetMinorVersion();
//	printf("GL: %i.%i\n", major, minor);
//
//	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
//	{
//		glClearColor(0.25f, 0.25f, 0.25f, 1);
//		glEnable(GL_DEPTH_TEST); // enables the depth buffer
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		aie::Gizmos::clear();
//		aie::Gizmos::addTransform(glm::mat4(1));
//		vec4 white(1);
//		vec4 black(0, 0, 0, 1);
//		for (int i = 0; i < 21; ++i)
//		{
//			aie::Gizmos::addLine(vec3(-10 + i, 0, 10), vec3(-10 + i, 0, -10), i == 10 ? white : black);
//			aie::Gizmos::addLine(vec3(10, 0, -10 + i), vec3(-10, 0, -10 + i), i == 10 ? white : black);
//		}
//
//		aie::Gizmos::draw(projection* view);
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	aie::Gizmos::destroy();
//	glfwDestroyWindow(window);
//	glfwTerminate();
//}


