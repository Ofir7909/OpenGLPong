#pragma once;

#include <string>

unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
unsigned int CompileShader(unsigned int type, const std::string& shader);
