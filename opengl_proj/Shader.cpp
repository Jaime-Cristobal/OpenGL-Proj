#include "Shader.h"
using crt::Shader;
#include "ShaderUtility.h"
using std::string;
using utl::readFileContents;
using utl::createShader;
using utl::createShaderProgram;


Shader::Shader(string const& vertexPath, string const& fragmentPath)
{
	string vertexCode = readFileContents(vertexPath);
	string fragmentCode = readFileContents(fragmentPath);
	
	// shader initialization
	GLuint vertex, fragment;
	createShader(vertex, GL_VERTEX_SHADER, vertexCode);
	createShader(fragment, GL_FRAGMENT_SHADER, fragmentCode);

	// shader program initialization
	id = glCreateProgram();
	createShaderProgram(id, { vertex, fragment });

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}


void Shader::use()
{
	glUseProgram(id);
}


void Shader::setBool(std::string const& name, bool value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), static_cast<int>(value));
}


void Shader::setFloat(std::string const& name, float value) const
{
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}


void Shader::setInt(std::string const& name, int value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}


void Shader::setColor(std::string const& name, float red, float green, 
	float blue, float alpha) const
{
	glUniform4f(glGetUniformLocation(id, name.c_str()), red, green, blue, alpha);
}


void Shader::setMat4(std::string const& name, glm::mat4 const& matrix) const
{
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
}