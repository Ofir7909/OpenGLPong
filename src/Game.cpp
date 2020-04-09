#include "Game.h"

#include "Ball.h"
#include "Paddle.h"

void Game::ResetGame()
{
	GameObject::DeleteAll();

	new Paddle(glm::vec3(-15.0f, 0.0f, 0.0f), glm::vec3(.5f, 5.0f, 0.0f));
	new Paddle(glm::vec3(15.0f, 0.0f, 0.0f), glm::vec3(.5f, 5.0f, 0.0f));
	Ball* ball = new Ball(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.9f));
	ball->SetSpeed(10.0f);
}
