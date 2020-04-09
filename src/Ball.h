#pragma once

#include "GameObject.h"

class Ball : public GameObject
{
  public:
	Ball(const glm::vec3& pos = glm::vec3(0.0f), const glm::vec3& scale = glm::vec3(1.0f));
	// Inherited via GameObject
	virtual void Draw() override;
	virtual void Update() override;

	inline float GetSpeed() const { return m_Speed; }
	inline void SetSpeed(float speed) { m_Speed = speed; }

  private:
	float m_Speed = 5.0f;
	glm::vec3 m_Direction;
};