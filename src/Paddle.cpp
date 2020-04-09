#include "Paddle.h"

#include "Renderer.h"

#include "Time.h"

Paddle::Paddle(const glm::vec3& pos, const glm::vec3& scale): GameObject(pos, scale)
{
}

void Paddle::Draw()
{
	Renderer::Get().SetDrawingColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
	Renderer::Get().DrawRect(m_Position, m_Scale);
}

void Paddle::Update()
{
	glm::vec3 velocity = glm::vec3(0.0f);
	if (glfwGetKey(Renderer::Get().GetWindow(), GLFW_KEY_UP))
		velocity = glm::vec3(0.0f, m_Speed, 0.0f);
	else if (glfwGetKey(Renderer::Get().GetWindow(), GLFW_KEY_DOWN))
		velocity = glm::vec3(0.0f, -m_Speed, 0.0f);

	m_Position += velocity * Time::Get().deltaTime;
}
