#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include <glad/glad.h>

Shader::Shader(const std::string& filepath): m_FilePath(filepath)
{
	m_RendererID = CreateShader(filepath);
	glUseProgram(m_RendererID);
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

void Shader::Bind() const
{
	glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

// Gets a filepath to a shader. and return the ID for the shader program.
unsigned int Shader::CreateShader(const std::string& filepath)
{
	ShaderSources src = ParseShader(filepath);

	unsigned int program = glCreateProgram();

	unsigned int vs = CompileSubShader(GL_VERTEX_SHADER, src.VertexSource);
	unsigned int fs = CompileSubShader(GL_FRAGMENT_SHADER, src.FragmentSource);

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

unsigned int Shader::CompileSubShader(unsigned int type, const std::string& shaderSource)
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

ShaderSources Shader::ParseShader(const std::string& filepath)
{
	enum class ShaderType
	{
		NONE	 = -1,
		VERTEX	 = 0,
		FRAGMENT = 1
	};

	std::ifstream stream(filepath);
	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (std::getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {
				type = ShaderType::FRAGMENT;
			}
			else {
				std::cout << "[!] Failed to parse the shader" << std::endl;
			}
		}
		else {
			if (type == ShaderType::NONE) {
				continue;
			}

			ss[(int)type] << line << '\n';
		}
	}
	return {ss[0].str(), ss[1].str()};
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
		return m_UniformLocationCache[name];
	}

	int location = glGetUniformLocation(m_RendererID, name.c_str());
	if (location == -1) {
		std::cout << "[!] Couldn't Find uniform " << name << std::endl;
	}
	m_UniformLocationCache[name] = location;

	return location;
}
