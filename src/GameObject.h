#pragma once

#include <glm/glm.hpp>
#include <vector>

class GameObject
{
  public:
	GameObject(const glm::vec3& pos, const glm::vec3& scale);
	~GameObject();

	// Position getter and setter
	inline const glm::vec2& GetPosition() const { return m_Position; }
	inline void SetPosition(const glm::vec3& position) { m_Position = position; }

	// Scale getter and setter
	inline const glm::vec2& GetScale() const { return m_Scale; }
	inline void SetScale(const glm::vec3& scale) { m_Scale = scale; }

	// Pure Virutal Functions
	virtual void Draw()	  = 0;
	virtual void Update() = 0;

	inline static std::vector<GameObject*>::iterator begin() { return m_GameObjects.begin(); }
	inline static std::vector<GameObject*>::iterator end() { return m_GameObjects.end(); }

	static void DrawAll();
	static void UpdateAll();
	static void DeleteAll();

  protected:
	glm::vec3 m_Position;
	glm::vec3 m_Scale;

  private:
	static std::vector<GameObject*> m_GameObjects;
};