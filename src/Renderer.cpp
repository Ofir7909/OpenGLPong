#include "Renderer.h"

#include <iostream>
#include <memory>

#include <glad/glad.h>

#include "GameObject.h"

#include <glm/gtc/matrix_transform.hpp>

Renderer* Renderer::s_Instance = nullptr;

static std::unique_ptr<VertexArray> SquareVA  = nullptr;
static std::unique_ptr<VertexBuffer> SquareVB = nullptr;
static std::unique_ptr<IndexBuffer> SquareIB  = nullptr;
static std::unique_ptr<Shader> BasicShader	  = nullptr;
static std::unique_ptr<Shader> CircleShader	  = nullptr;

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

Renderer::Renderer(): m_DrawingColor(1.0f, 1.0f, 1.0f, 1.0f)
{
}

Renderer::~Renderer()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

Renderer& Renderer::Get()
{
	if (!s_Instance) {
		s_Instance = new Renderer();
		s_Instance->init();
	}

	return *s_Instance;
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
	glfwSwapInterval(0);

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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Init Primitive shapes

	// The rectangle
	// 3	2
	//
	// 0	1

	float SquareVertices[] = {
		-0.5f, -0.5f, //
		0.5f,  -0.5f, //
		0.5f,  0.5f,  //
		-0.5f, 0.5f,  //
	};

	unsigned int SquareIndices[] = {
		0, 1, 2, //
		2, 3, 0	 //
	};

	SquareVA	 = std::make_unique<VertexArray>();
	SquareVB	 = std::make_unique<VertexBuffer>(SquareVertices, sizeof(float) * 2 * 4);
	SquareIB	 = std::make_unique<IndexBuffer>(SquareIndices, 3 * 2);
	BasicShader	 = std::make_unique<Shader>("res/Basic.shader");
	CircleShader = std::make_unique<Shader>("res/Circle.shader");

	VertexBufferLayout SquareLayout;
	SquareLayout.Push<float>(2);

	SquareVA->AddBuffer(*SquareVB, SquareLayout);
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
}

void Renderer::Update()
{
	// Get Input And Events
	glfwPollEvents();
}

void Renderer::DrawRect(const glm::vec2& position, const glm::vec2& scale)
{
	// MVP Matrix
	glm::mat4 projection = glm::ortho(-20.0f, 20.0f, -15.0f, 15.0f, -1.0f, 1.0f);

	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
	model			= glm::scale(model, glm::vec3(scale, 0.0f));

	glm::mat4 mvpMat = projection * view * model;

	BasicShader->Bind();
	BasicShader->SetUniform4f("u_Color", m_DrawingColor.r, m_DrawingColor.g, m_DrawingColor.b, m_DrawingColor.a);
	BasicShader->SetUniformMat4f("u_MVP", mvpMat);

	this->Draw(*SquareVA, *SquareIB);
}

void Renderer::DrawCircle(const glm::vec2& position, const glm::vec2& scale)
{
	// MVP Matrix
	glm::mat4 projection = glm::ortho(-20.0f, 20.0f, -15.0f, 15.0f, -1.0f, 1.0f);

	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
	model			= glm::scale(model, glm::vec3(scale, 0.0f));

	glm::mat4 mvpMat = projection * view * model;

	CircleShader->Bind();
	CircleShader->SetUniform4f("u_Color", m_DrawingColor.r, m_DrawingColor.g, m_DrawingColor.b, m_DrawingColor.a);
	CircleShader->SetUniformMat4f("u_MVP", mvpMat);

	this->Draw(*SquareVA, *SquareIB);
}
