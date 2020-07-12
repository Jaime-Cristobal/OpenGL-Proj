#pragma once

#include "Shader.h"
#include <glad/glad.h>
#include <vector>
#include <string>

namespace crt
{
	class Triangle
	{
	private:
		std::vector<GLfloat> vertices;
		std::vector<std::string> textures;
		GLuint vbo, vao;
		glm::mat4 model;

		void genAttrib();

	public:
		Triangle();
		void loadTexture(GLuint& texture, std::string const& path,
			GLuint const& wrapperMode, GLuint const& filterMode);
		void setTexturesToShader(Shader& shader) const;
		void render(Shader& shader);
		void dispose();
	};
}