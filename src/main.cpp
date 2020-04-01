#include <iostream>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "Shader.h"

#define WIDTH  800
#define HEIGHT 600

// GL Error Callback
void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
								const GLchar* message, const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
			(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity, message);
}

int main()
{
	// GLFW Setup

	if (!glfwInit()) {
		std::cout << "ERROR! Failed to initialize GLFW" << std::endl;
		return -1;
	}

	// Disable Window Resizing
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a window
	GLFWwindow* window;
	window = glfwCreateWindow(WIDTH, HEIGHT, "Pong", 0, 0);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	// Make the window the current context.
	glfwMakeContextCurrent(window);

	// Init Glad.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		return -1;
	}

	// Error Handling
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);

	// Set the viewport size (equal to the window)
	glViewport(0, 0, WIDTH, HEIGHT);

	// The rectangle
	// 3	2
	//
	// 0	1

	// Vertex buffer
	float vertices[] = {
		-0.5f, -0.5f, //
		0.5f,  -0.5f, //
		0.5f,  0.5f,  //
		-0.5f, 0.5f,  //
	};

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, vertices, GL_STATIC_DRAW);

	// Vertex attributes
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0); // TODO: Try to use 0 in stride

	// Shader
	const std::string vertexShader = "#version 330 core\n"
									 "\n"
									 "layout(location = 0) in vec4 position;\n"
									 "\n"
									 "void main(){\n"
									 "	gl_Position = position;\n"
									 "}\n";

	const std::string fragmentShader = "#version 330 core\n"
									   "\n"
									   "layout(location = 0) out vec4 color;\n"
									   "\n"
									   "void main(){\n"
									   "	color = vec4(1.0, 1.0, 1.0, 1.0);\n"
									   "}\n";

	unsigned int shader = CreateShader(vertexShader, fragmentShader);
	glUseProgram(shader);

	// Game Loop
	while (!glfwWindowShouldClose(window)) {
		// Clear the screen
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

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