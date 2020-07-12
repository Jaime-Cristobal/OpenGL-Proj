/**
* 
*/

#pragma once

#include <GLFW/glfw3.h>
#include <iostream>

struct DestroyGLFW
{
	void operator()(GLFWwindow* ptr) { std::cout << "destroying glfw" << std::endl; glfwDestroyWindow(ptr); }
};