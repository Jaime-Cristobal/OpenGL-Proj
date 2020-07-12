#pragma once

#include <string>
#include <glad/glad.h>


namespace utl
{
	std::string readFileContents(std::string const& path);
	void createShader(GLuint& shader, GLenum shaderType, std::string const& code);
	void createShaderProgram(GLuint const& id, std::initializer_list<GLuint> shaders);
};