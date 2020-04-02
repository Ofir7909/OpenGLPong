#include <assert.h>
#include <iostream>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "IndexBuffer.h"
#include "Renderer.h"
#include "Shader.h"
#include "VertexBuffer.h"

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
	{
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

		// Vertex Array
		unsigned int vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// Vertex buffer
		VertexBuffer vb(vertices, sizeof(float) * 2 * 4);

		// Vertex attributes
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0); // TODO: Try to use 0 in stride

		// Index Buffer
		IndexBuffer ib(indices, 3 * 2);

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
	}

	// Clean up
	glfwDestroyWindow(window);
	glfwTerminate();

	// End of program
	std::cout << "Press Any Key To Continue: " << std::endl;
	getchar();
	return 0;
}