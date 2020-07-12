#include "ShaderUtility.h"
#include <iostream>
using std::cout;
using std::endl;
#include <fstream>
#include <sstream>
using std::ifstream;
using std::string;


/**
* Reads the contents of a file and returns them as a std::string.

* @param path - The path to the file. If the file is placed on the
*				same folder as Shader, just pass the name of the file
*				(ex. "Shader.vs"). Else if the the file is placed
*				somewhere outside the folder, you will have to provide
*				the full path name.
* @return code - The contents/code inside the file packaged as a string.
*/
std::string utl::readFileContents(std::string const& path)
{
	string code;
	ifstream file;

	// apply throw exceptions to ifstream
	file.exceptions(ifstream::failbit | ifstream::badbit);

	try
	{
		file.open(path);
		std::stringstream contentStream;

		// read shader file contents into string
		contentStream << file.rdbuf();
		file.close();
		code = contentStream.str();
	}
	catch (ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ @" + path << endl;
	}

	return code;
}


/**
*
*/
void utl::createShader(GLuint& shader, GLenum shaderType, std::string const& code)
{
	// for compability with GLchar *const*
	char const* codePtr = code.c_str();

	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &codePtr, nullptr);
	glCompileShader(shader);

	// shader compile errors
	int success = 0;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	}
}


/**
*
*/
void utl::createShaderProgram(GLuint const& id, std::initializer_list<GLuint> shaders)
{
	for (auto shader : shaders)
	{
		glAttachShader(id, shader);
	}
	glLinkProgram(id);

	// check compile errors
	int success = 0;
	char infoLog[512];
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(id, 512, nullptr, infoLog);
		cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
	}
}