#include "Launcher.h"
#include <iostream>
using std::cout;
using std::endl;


Launcher::Launcher() : winWidth(800), winHeight(600), title("OpenGL Proj")
{
	// glfw: initialize and configuration
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window.reset(glfwCreateWindow(winWidth, winHeight, title.c_str(), nullptr, nullptr));

	start();
}


/**
* This sets the GLFW context and callback buffer to our window pointer. If any errors
* are present, we simply output a message on the console, release the window memory,
* and return back to main.
*/
void Launcher::start() const
{
	if (!window)
	{
		cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window.get());
	glfwSetFramebufferSizeCallback(window.get(), frameBufferSizeCallback);

	// glad: Load all OpenGL functions
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return;
	}

	glEnable(GL_DEPTH_TEST);
}


void Launcher::run() const
{
	while (!glfwWindowShouldClose(window.get()))
	{
		processInput(window.get());

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window.get());
		glfwPollEvents();

		render();
	}
}


void Launcher::render() const
{

}


void frameBufferSizeCallback(GLFWwindow* const window, int const width, int const height)
{
	glViewport(0, 0, width, height);
}


void processInput(GLFWwindow* const window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}