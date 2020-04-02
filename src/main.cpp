#include <assert.h>
#include <iostream>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "Shader.h"

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

// GL Error Callback
void GLAPIENTRY OpenGlMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
									  const GLchar* message, const void* userParam)
{
	fprintf(stdout, "[!] GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
			(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity, message);
}

void GLFWMessageCallback(int code, const char* message)
{
	std::cout << "[!] GLFW CALLBACK (Error Code " << code << "): " << message << std::endl;
}

int main()
{
#pragma region Initialization

	// GLFW Setup
	glfwSetErrorCallback(GLFWMessageCallback);

	if (!glfwInit()) {
		std::cout << "ERROR! Failed to initialize GLFW" << std::endl;
		return -1;
	}

	// Disable Window Resizing
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a window
	GLFWwindow* window;
	window = glfwCreateWindow(WIDTH, HEIGHT, "Pong", 0, 0);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	// Make the window the current context.
	glfwMakeContextCurrent(window);

	// Set Vsync.
	glfwSwapInterval(1);

	// Init Glad.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		return -1;
	}

	// Error Handling
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(OpenGlMessageCallback, 0);

	// Print debug information
	std::cout << glGetString(GL_VENDOR) << std::endl;
	std::cout << glGetString(GL_RENDERER) << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;
	std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

#pragma endregion

	// The rectangle
	// 3	2
	//
	// 0	1

	float vertices[] = {
		-0.5f, -0.5f, //
		0.5f,  -0.5f, //
		0.5f,  0.5f,  //
		-0.5f, 0.5f,  //
	};

	unsigned int indices[] = {
		0, 1, 2, //
		2, 3, 0	 //
	};

	// Set the viewport size (equal to the window)
	glViewport(0, 0, WIDTH, HEIGHT);

	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Vertex buffer and array
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * 4, vertices, GL_STATIC_DRAW);

	// Vertex attributes
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0); // TODO: Try to use 0 in stride

	// Index Buffer
	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 3 * 2, indices, GL_STATIC_DRAW);

	// Shader
	ShaderSources src	= ParseShader("res/Basic.shader");
	unsigned int shader = CreateShader(src.VertexSource, src.FragmentSource);
	glUseProgram(shader);

	// Set Uniform
	int location = glGetUniformLocation(shader, "u_Color");
	assert(location != -1);
	glUniform4f(location, 1.0f, 1.0f, 1.0f, 1.0f);

	// Game Loop
	while (!glfwWindowShouldClose(window)) {
		// Clear the screen
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Render to the screen
		glfwSwapBuffers(window);

		// Get Input And Events
		glfwPollEvents();
	}

	// Clean up
	glfwDestroyWindow(window);
	glfwTerminate();

	// End of program
	std::cout << "Press Any Key To Continue: " << std::endl;
	getchar();
	return 0;
}