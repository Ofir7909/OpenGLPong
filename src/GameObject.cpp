#include "GameObject.h"

std::vector<GameObject*> GameObject::m_GameObjects;

GameObject::GameObject(const glm::vec3& pos, const glm::vec3& scale): m_Position(pos), m_Scale(scale)
{
	m_GameObjects.push_back(this);
}

GameObject::~GameObject()
{
}

void GameObject::DrawAll()
{
	for (auto iter = GameObject::begin(); iter != GameObject::end(); iter++) {
		GameObject& go = **iter;
		go.Draw();
	}
}

void GameObject::UpdateAll()
{
	for (auto iter = GameObject::begin(); iter != GameObject::end(); iter++) {
		GameObject& go = **iter;
		go.Update();
	}
}

void GameObject::DeleteAll()
{
	for (auto iter = GameObject::begin(); iter != GameObject::end(); iter++) { delete *iter; }

	m_GameObjects.clear();
}
