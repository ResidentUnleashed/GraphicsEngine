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

class DemoApplication : public Application
{
	virtual bool onStartup() override
	{
		auto major = ogl_GetMajorVersion();
		auto minor = ogl_GetMinorVersion();
		printf("GL: %i.%i\n", major, minor);

		aie::Gizmos::create(100, 100, 100, 100);

		return true;
	}

	virtual void update() override
	{
		if (glfwWindowShouldClose(getWindow()))
		{
			SetIsRunning(false);
		}

		glClearColor(0.25f, 0.25f, 0.25f, 1);
		glEnable(GL_DEPTH_TEST); // enables the depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		aie::Gizmos::clear();
		aie::Gizmos::addTransform(glm::mat4(1));
		vec4 white(1);
		vec4 black(0, 0, 0, 1);
		for (int i = 0; i < 21; ++i)
		{
			aie::Gizmos::addLine(vec3(-10 + i, 0, 10), vec3(-10 + i, 0, -10), i == 10 ? white : black);
			aie::Gizmos::addLine(vec3(10, 0, -10 + i), vec3(-10, 0, -10 + i), i == 10 ? white : black);
		}
	}

	virtual void render() override
	{
		mat4 view = glm::lookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
		mat4 projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);

		aie::Gizmos::draw(projection* view);
	}

	virtual void onShutdown() override
	{
		aie::Gizmos::destroy();
	}

};


int main()
{
	DemoApplication app;
	

    return app.Run("Graphics", 1280, 720, false, "config.ini");
}

