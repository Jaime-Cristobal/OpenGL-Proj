#pragma once

#include "DestroyGLFW.h"
#include <glad/glad.h>
#include <string>
#include <memory>

class Launcher
{
private:
	typedef std::unique_ptr<GLFWwindow, DestroyGLFW> SmartGLFWwindow;
	SmartGLFWwindow window;
	const unsigned int winWidth;
	const unsigned int winHeight;
	const std::string title;

	void start() const;

public:
	Launcher();
	void render() const;
	void run() const;
};

void frameBufferSizeCallback(GLFWwindow* const window, int const width, int const height);
void processInput(GLFWwindow* const window);