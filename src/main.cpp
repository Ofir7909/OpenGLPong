#include <cstdio>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#define WIDTH  800
#define HEIGHT 600

int main()
{
	// GLFW Setup

	if (!glfwInit()) {
		printf("ERROR! Failed to initialize GLFW\n");
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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
		printf("Failed to initialize OpenGL context\n");
		return -1;
	}

	// Set the viewport size (equal to the window)
	glViewport(0, 0, WIDTH, HEIGHT);

	// Game Loop
	while (!glfwWindowShouldClose(window)) {
		// Clear the screen
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render to the screen
		glfwSwapBuffers(window);

		// Get Input And Events
		glfwPollEvents();
	}

	// Clean up
	glfwDestroyWindow(window);
	glfwTerminate();

	// End of program
	printf("Press Any Key To Continue: ");
	getchar();
	return 0;
}