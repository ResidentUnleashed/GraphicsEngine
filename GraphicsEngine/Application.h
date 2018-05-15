#pragma once
#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <chrono>

#pragma warning( push )
#pragma warning( disable : 4201 )
#pragma warning( disable : 4310 )
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#pragma warning ( pop )

class Application
{
public:

	//Deconstructor
	virtual ~Application();

	//Functions for children to call
	virtual bool onStartup() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void onShutdown() = 0;


	//Run the application
	int Run(const char* title, int width, int height, bool fullscreen, const char* configFilePath = "");

	//Sets up the application by creating a window and also setting up children
	bool initialise(const char* title, int width, int height, bool fullscreen);

	//Creates the main game loop
	void gameLoop();

	//Shutdown the application window
	void shutdown();



	//Getters
	GLFWwindow* getWindow() { return m_window; }
	int getWindowWidth() { return m_windowWidth; }
	int getWindowHeight() { return m_windowHeight; }
	bool getFullScreen() { return m_isFullScreen; }
	bool getIsRunning() { return m_isRunning; }
	float getDeltaTime() { return m_dt; }
	float getElapsedTime() { return m_elapsedTime; }

	//Setters
	void SetIsRunning(bool value) { m_isRunning = value; }

protected:



private:

	GLFWwindow* m_window; /* The applications window */
	int m_windowWidth = 1280;
	int m_windowHeight = 720;
	bool m_isFullScreen = false;
	bool m_isRunning = true;
	float m_dt = 0.0f; /* DeltaTime */
	float m_elapsedTime = 0.0f;
	std::chrono::high_resolution_clock::time_point m_previousFrameTime; /* Previous frame time */
	std::chrono::high_resolution_clock::time_point m_applicationStartTime; /* Start time for the application */
};

