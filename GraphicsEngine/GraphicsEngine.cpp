#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Gizmos.h>
#include "Application.h"
#include "Camera.h"
#include <Shader.h>
#include "Mesh.h"

#pragma warning( push )
#pragma warning( disable : 4201 )
#pragma warning( disable : 4310 )
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#pragma warning ( pop )


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

		aie::Gizmos::create(10000, 10000, 10000, 10000);

		//Create simple camera transforms
		m_viewMatrix = glm::lookAt(vec3(10), vec3(0), vec3(0, 1, 0));

		m_camera.SetHasSetProjectionMatrix(true);
		m_camera.SetProjectionMatrix(glm::perspective(glm::pi<float>() * 0.25f, (float)getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.f));


		//Load shaders
		m_shader.loadShader(aie::eShaderStage::VERTEX, "./shader/simple.vert");
		m_shader.loadShader(aie::eShaderStage::FRAGMENT, "./shader/simple.frag");

		//Error checking
		if (m_shader.link() == false)
		{
			printf("Shader Error: %s\n", m_shader.getLastError()); 
			return false;
		}

		m_quadMesh.initialiseQuad();

		//Make the quad 10 units wide 
		m_quadTransform = { 10,0,0,0, 0,10,0,0, 0,0,10,0, 0,0,0,1 };

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
		//Update perspective in case window resized
		m_camera.SetProjectionMatrix(glm::perspective(glm::pi<float>() * 0.25f, (float)getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.f));

		//Bind shader
		m_shader.bind();

		//Bind transform
		auto pvm = m_camera.GetProjectionMatrix() * m_viewMatrix * m_quadTransform;
		m_shader.bindUniform("ProjectionViewModel", pvm);

		//Draw quad
		m_quadMesh.draw();

		//Draw 3D Gizmos
		aie::Gizmos::draw(m_camera.GetProjectionMatrix() * m_viewMatrix);

		//Draw 2D gizmos using an orthogonal projection matrix
		aie::Gizmos::draw2D((float)getWindowWidth(), (float)getWindowHeight());
	}

	virtual void onShutdown() override
	{
		aie::Gizmos::destroy();
	}

private:
	Camera m_camera;
	aie::ShaderProgram m_shader;
	Mesh m_quadMesh;
	glm::mat4 m_quadTransform;
	glm::mat4 m_viewMatrix;
};


int main()
{
	DemoApplication app;
	

    return app.Run("Graphics", 1280, 720, false, "config.ini");
}

