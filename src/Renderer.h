#pragma once

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Color.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

#include "Math.h"

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

class Renderer
{
  public:
	~Renderer();

	static Renderer& Get();

	void init();
	void Clear() const;
	void Draw(const VertexArray& va, const IndexBuffer& ib) const;
	void Render() const;
	void Update();

	inline void SetDrawingColor(const Color& color) { m_DrawingColor = color; }

	// Primitive shapes
	void DrawRect(const glm::vec2& position, const glm::vec2& scale);
	void DrawCircle(const glm::vec2& position, const glm::vec2& scale);

	inline GLFWwindow* GetWindow() const { return m_Window; }

	inline bool IsRunning() const { return !glfwWindowShouldClose(m_Window); }

  private:
	Renderer();

  private:
	static Renderer* s_Instance;
	GLFWwindow* m_Window;

	Color m_DrawingColor;
};