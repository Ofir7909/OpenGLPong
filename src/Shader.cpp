#include "Shader.h"

#include <iostream>

#include <glad/glad.h>

unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();

	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	int result;
	glGetProgramiv(program, GL_VALIDATE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

		char* message = (char*)alloca(length);
		glGetProgramInfoLog(program, length, &length, message);

		std::cout << "[!] Failed to link shader!" << std::endl;
		std::cout << message << std::endl;
		glDeleteProgram(program);

		return 0;
	}

	// Clean up
	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

unsigned int CompileShader(unsigned int type, const std::string& shaderSource)
{
	unsigned int id = glCreateShader(type);
	const char* src = shaderSource.c_str();
	glShaderSource(id, 1, &src, 0);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

		char* message = (char*)alloca(length);
		glGetShaderInfoLog(id, length, &length, message);

		std::cout << "[!] Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!"
				  << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);

		return 0;
	}

	return id;
}