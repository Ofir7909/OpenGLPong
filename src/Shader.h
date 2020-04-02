#pragma once;

#include <string>

struct ShaderSources
{
	std::string VertexSource;
	std::string FragmentSource;
};

unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
unsigned int CompileShader(unsigned int type, const std::string& shader);
ShaderSources ParseShader(const std::string& filepath);
