#include "Renderer.h"

#include <iostream>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

// GL Error Callback
void GLAPIENTRY OpenGlMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
									  const GLchar* message, const void* userParam)
{
	fprintf(stdout, "[!] GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
			(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity, message);
}

// GLFW Error Callback
void GLFWMessageCallback(int code, const char* message)
{
	std::cout << "[!] GLFW CALLBACK (Error Code " << code << "): " << message << std::endl;
}