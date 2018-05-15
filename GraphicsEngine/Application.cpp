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
		auto timeTaken = now - m_previousFrameTime;
		m_dt = std::chrono::duration<float>(timeTaken).count;
        m_previousFrameTime = now;

		//Elapsed time is equal to current time - start time
		auto elapsedTime = now - m_applicationStartTime;
		m_elapsedTime = std::chrono::duration<float>(elapsedTime).count;

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


