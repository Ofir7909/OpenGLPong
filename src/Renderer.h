#pragma once

#include <glad/glad.h>

#define WIDTH  800
#define HEIGHT 600

#ifndef OPENGL_VERSION_MAJOR
#define OPENGL_VERSION_MAJOR 4
#endif
#ifndef OPENGL_VERSION_MINOR
#define OPENGL_VERSION_MINOR 6
#endif
#ifndef OPENGL_VERSION_PROFILE
#define OPENGL_VERSION_PROFILE "core"
#endif

void OpenGlMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
						   const GLchar* message, const void* userParam);

void GLFWMessageCallback(int code, const char* message);