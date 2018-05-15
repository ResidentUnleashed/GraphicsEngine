#include "Application.h"



Application::~Application()
{
}

int Application::Run(const char* title, int width, int height, bool fullscreen, const char* configFilePath)
{
	//Set up the sucessful check
	auto successful = initialise(title, width, height, fullscreen);

	if (!successful)
	{
		return -1;
	}
	else if (!onStartup())
	{
		shutdown();
		return -2;
	}

	//Run game loop
	gameLoop();
	

	//Shutdown
	onShutdown();
	shutdown();

	return 0;
}

bool Application::initialise(const char* title, int width, int height, bool fullscreen)
{
	if (glfwInit() == false) /* If it hasn't initialised, return -1 */
		return -1;

	//Get the monitor and check if fullscreen
	GLFWmonitor* monitor = nullptr;
	if (fullscreen)
	{
		monitor = glfwGetPrimaryMonitor();
	}

	//Create the window
	m_window = glfwCreateWindow(width, height, title, monitor, nullptr);

	if (m_window == nullptr)
	{
		//Terminate process
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_window);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
		return false;
	}

	//Initialise variables
	m_windowWidth = width;
	m_windowHeight = height;
	m_previousFrameTime = m_applicationStartTime;

	return true;
}

void Application::gameLoop()
{
	while (m_isRunning)
	{
		//Create deltatime by getting the time in nanoseconds and converting it to seconds
		auto now = std::chrono::high_resolution_clock::now();
		m_dt = (float)(now - m_previousFrameTime).count();
	
        m_previousFrameTime = now;

		////Elapsed time is equal to current time - start time
		//auto elapsedTime = now - m_applicationStartTime;
		//m_elapsedTime = std::chrono::duration<float>(elapsedTime).count;

		//Update and render
		update();
		render();

		//Buffer and process
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
}

void Application::shutdown()
{
	//Destroy the window and terminate
	glfwDestroyWindow(m_window);
	glfwTerminate();
}
