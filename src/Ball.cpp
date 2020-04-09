#include "Ball.h"

#include "Random.h"
#include "Renderer.h"
#include "Time.h"

#include <iostream>

Ball::Ball(const glm::vec3& pos, const glm::vec3& scale): GameObject(pos, scale)
{
	// direction is a random vec2 in the range (-1,-0.5) to (1,0.5)
	glm::vec2 direction = glm::vec2(Random::RandFloat() * 2.0f - 1.0f, Random::RandFloat() * 1.8f - 1.0f);
	m_Direction			= glm::normalize(glm::vec3(direction, 0.0f));
}

void Ball::Draw()
{
	Renderer::Get().SetDrawingColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
	Renderer::Get().DrawCircle(m_Position, m_Scale);
}

void Ball::Update()
{
	m_Position = m_Position + m_Direction * m_Speed * Time::Get().deltaTime;
}