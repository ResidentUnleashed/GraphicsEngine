#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Gizmos.h>
#include "Application.h"
#include "Camera.h"
#include <Shader.h>
#include "Mesh.h"
#include "OBJMesh.h"
#include "RenderTarget.h"

#pragma warning( push )
#pragma warning( disable : 4201 )
#pragma warning( disable : 4310 )
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#pragma warning ( pop )


using glm::vec3;
using glm::vec4;
using glm::mat4;


//TODO:
//Move into demo app class (.h and .cpp)
//Ask Matt about bind

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
		m_camera.SetProjectionMatrix(glm::perspective(glm::pi<float>() * 0.25f, (float)getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.0f));

		
		//Load shaders
		m_normalMapShader.loadShader(aie::eShaderStage::VERTEX, "./shader/normalmap.vert");
		m_normalMapShader.loadShader(aie::eShaderStage::FRAGMENT, "./shader/normalmap.frag");

		m_phongShader.loadShader(aie::eShaderStage::VERTEX, "./shader/phong.vert");
		m_phongShader.loadShader(aie::eShaderStage::FRAGMENT, "./shader/phong.frag");

		m_texturedShader.loadShader(aie::eShaderStage::VERTEX, "./shader/textured.vert");
		m_texturedShader.loadShader(aie::eShaderStage::FRAGMENT, "./shader/textured.frag");

		//Error checking
		if (m_normalMapShader.link() == false)
		{
			printf("Shader Error: %s\n", m_normalMapShader.getLastError());
			return false;
		}

		if (m_texturedShader.link() == false)
		{
			printf("Shader Error: %s\n", m_texturedShader.getLastError());
			return false;
		}

		if (m_phongShader.link() == false)
		{
			printf("Shader Error: %s\n", m_phongShader.getLastError());
			return false;
		}

		if (m_spearMesh.load("./models/soulspear/soulspear.obj", true, true) == false) 
		{
			printf("Spear Mesh Error!\n");
			return false;
		}

		if (m_dragonMesh.load("./models/dragon.obj") == false) 
		{
			printf("Dragon Mesh Error!\n");
			return false;
		}

		if (m_bunnyMesh.load("./models/bunny.obj") == false)
		{
			printf("Bunny Mesh Error!\n");
			return false;
		}


		if (m_renderTarget.initialise(1, getWindowWidth(), getWindowHeight()) == false)
		{
			printf("Render target error!\n");
			return false;
		}
		if (m_gridTexture.load("./textures/numbered_grid.tga") == false) {
			printf("Failed to load texture!\n");
			return false;
		}
		
		m_light.diffuse = { 5.0f, 0.8f, 5 };
		m_light.specular = { 0, 1, 1 };
		m_ambientLight = { 0.25f, 0.25f, 0.25f };

		m_light01.diffuse = { 0.1, 5, 0.6f };
		m_light01.specular = { 1, 1, 0 };

		m_light02.diffuse = { 3.0f, 0, 5 };
		m_light02.specular = { 1, 0, 1 };

		m_spearLight.diffuse = { 1, 1, 1 }; 
		m_spearLight.specular = { 1, 1, 0 };



		//Create a simple quad
		m_quadMesh.initialiseQuad();

		//Define a scale matrix for the quad
		m_quadTransform = {
			20,0,0,0,
			0,20,0,0,
			0,0,20,0,
			0,0,0,1
		};


		m_spearTransform = { 1.0f,0,0,0, 0,1.0f,0,0, 0,0,1.0f,0, 0,0,0,1 };

		//.5 of actual size
		m_dragonTransform = { 0.5f,0,0,0, 0,0.5f,0,0, 0,0,0.5f,0, -5,0,3,1 };

		//.5 of actual size
		m_bunnyTransform = { 0.5f,0,0,0, 0,0.5f,0,0, 0,0,0.5f,0, 5,0,-3,1 };

		return true;
	}

	virtual void update() override
	{
		//GL active stuff
		if (glfwWindowShouldClose(getWindow()))
		{
			SetIsRunning(false);
		}

		glClearColor(0.25f, 0.25f, 0.25f, 1);
		glEnable(GL_DEPTH_TEST); // enables the depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		float time = glfwGetTime();

		//Rotate lights
		m_light.direction = glm::normalize(vec3(glm::cos(time * 8), glm::sin(time * 8), 0));
		m_light01.direction = glm::normalize(vec3(glm::cos(time * 3), glm::sin(time * 3), 0));
		m_light02.direction = glm::normalize(vec3(glm::cos(time * -8), glm::sin(time * -8), 0));
		m_spearLight.direction = glm::normalize(vec3(glm::cos(time * 2), glm::sin(time * 2), 0));


		////Grid drawing stuff
		//aie::Gizmos::clear();
		//aie::Gizmos::addTransform(glm::mat4(1));
		//vec4 white(1);
		//vec4 black(0, 0, 0, 1);
		//for (int i = 0; i < 21; ++i)
		//{
		//	aie::Gizmos::addLine(vec3(-10 + i, 0, 10), vec3(-10 + i, 0, -10), i == 10 ? white : black);
		//	aie::Gizmos::addLine(vec3(10, 0, -10 + i), vec3(-10, 0, -10 + i), i == 10 ? white : black);
		//}
	}

	virtual void render() override
	{
		//Bind our render target 
		//m_renderTarget.bind();


		//Update perspective in case window resized
		m_camera.SetProjectionMatrix(glm::perspective(glm::pi<float>() * 0.25f, (float)getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.f));

		//Bind shader
		m_normalMapShader.bind();
		
		m_normalMapShader.bindUniform("cameraPosition", vec3(glm::inverse(m_viewMatrix)[3]));
		m_normalMapShader.bindUniform("Ia", m_ambientLight);
		m_normalMapShader.bindUniform("Id", m_spearLight.diffuse);
		m_normalMapShader.bindUniform("Is", m_spearLight.specular);
		//Bind light
		m_normalMapShader.bindUniform("lightDirection", m_spearLight.direction);
		
		//Bind transform
		auto pvm2 = m_camera.GetProjectionMatrix() * m_viewMatrix * m_spearTransform;
		m_normalMapShader.bindUniform("ProjectionViewModel", pvm2);
		
		//Bind transforms for lighting
		glm::mat3 mat = glm::inverseTranspose(glm::mat3(m_spearTransform));
		m_normalMapShader.bindUniform("NormalMatrix", mat);

		//Draw spear
		m_spearMesh.draw();

		//Draw scene with a light
		m_phongShader.bind();

		m_phongShader.bindUniform("specularPower", 1);

		//Ambient 
		m_phongShader.bindUniform("Ia", m_ambientLight);

		//Diffuse
		m_phongShader.bindUniform("Id", m_light.diffuse);
		m_phongShader.bindUniform("Id2", m_light01.diffuse);

		//Specular
		m_phongShader.bindUniform("Is", m_light.specular);
		m_phongShader.bindUniform("Is2", m_light01.specular);

		//Direction
		m_phongShader.bindUniform("LightDirection", m_light.direction);
		m_phongShader.bindUniform("LightDirection2", m_light01.direction);



		//Bind transform
		auto pvm01 = m_camera.GetProjectionMatrix() * m_viewMatrix * m_bunnyTransform;
		m_phongShader.bindUniform("ProjectionViewModel", pvm01);

		//Bind transforms for lighting
		m_phongShader.bindUniform("ModelMatrix", m_bunnyTransform);
		m_phongShader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_bunnyTransform)));

		m_bunnyMesh.draw();


		//Ambient 
		m_phongShader.bindUniform("Ia", m_ambientLight);

		//Diffuse
		m_phongShader.bindUniform("Id", m_light.diffuse);
		m_phongShader.bindUniform("Id", m_light01.diffuse);
		m_phongShader.bindUniform("Id", m_light02.diffuse);
		
		//Specular
		m_phongShader.bindUniform("Is", m_light.specular);
		m_phongShader.bindUniform("Is", m_light01.specular);
		m_phongShader.bindUniform("Is", m_light02.specular);

		//Direction
		m_phongShader.bindUniform("LightDirection", m_light.direction);
		m_phongShader.bindUniform("LightDirection", m_light01.direction);
		m_phongShader.bindUniform("LightDirection", m_light02.direction);


		
		//Bind transform
		auto pvm = m_camera.GetProjectionMatrix() * m_viewMatrix * m_dragonTransform;
        m_phongShader.bindUniform("ProjectionViewModel", pvm);

		//Bind transforms for lighting
		m_phongShader.bindUniform("ModelMatrix", m_dragonTransform);
		m_phongShader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_dragonTransform)));
		
		m_dragonMesh.draw();

		m_texturedShader.bind();

		// bind transform
		auto pvm1 = m_camera.GetProjectionMatrix() * m_viewMatrix * m_quadTransform;
		m_texturedShader.bindUniform("ProjectionViewModel", pvm1);
		// bind texture location
		m_texturedShader.bindUniform("diffuseTexture", 0);
		// bind texture to specified location
		m_gridTexture.bind(0);
		// draw quad
		m_quadMesh.draw();

		//Unbind target to return to backbuffer
		//m_renderTarget.unbind();
		//m_renderTarget.getTarget(0).bind(0);



		

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
	aie::ShaderProgram m_normalMapShader;
	aie::ShaderProgram m_phongShader;
	aie::ShaderProgram m_texturedShader;
	Mesh m_quadMesh;
	glm::mat4 m_quadTransform;
	glm::mat4 m_viewMatrix;
	aie::Texture m_gridTexture;

	glm::mat4 m_spearTransform;
	aie::OBJMesh m_spearMesh;

	glm::mat4 m_dragonTransform;
	aie::OBJMesh m_dragonMesh;

	glm::mat4 m_bunnyTransform;
	aie::OBJMesh m_bunnyMesh;

	struct Light
	{
		glm::vec3 direction;
		glm::vec3 diffuse;
		glm::vec3 specular;

	};

	Light m_light;
	glm::vec3 m_ambientLight;
	aie::RenderTarget m_renderTarget;

	Light m_light01;
	Light m_light02;
	Light m_spearLight;
};


int main()
{
	DemoApplication app;
	
    return app.Run("Graphics", 1280, 720, false, "config.ini");
}

