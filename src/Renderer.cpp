#include "Renderer.h"

#include <iostream>

#include <glad/glad.h>

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

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void Renderer::init()
{
	// GLFW Setup
	glfwSetErrorCallback(GLFWMessageCallback);

	if (!glfwInit()) {
		std::cout << "ERROR! Failed to initialize GLFW" << std::endl;
		assert(false);
		return;
	}

	// Disable Window Resizing
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a window
	m_Window = glfwCreateWindow(WIDTH, HEIGHT, "Pong", 0, 0);
	if (!m_Window) {
		glfwTerminate();
		assert(false);
		return;
	}

	// Make the window the current context.
	glfwMakeContextCurrent(m_Window);

	// Set Vsync.
	glfwSwapInterval(1);

	// Init Glad.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		assert(false);
		return;
	}

	// Error Handling
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(OpenGlMessageCallback, 0);

	// Print debug information
	std::cout << glGetString(GL_VENDOR) << std::endl;
	std::cout << glGetString(GL_RENDERER) << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;
	std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	// Set the viewport size (equal to the window)
	glViewport(0, 0, WIDTH, HEIGHT);
}

void Renderer::Clear() const
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// Will need to take in a material some day.
void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib) const
{
	va.Bind();
	ib.Bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Render() const
{
	// Render to the screen
	glfwSwapBuffers(m_Window);

	// Get Input And Events
	glfwPollEvents();
}
