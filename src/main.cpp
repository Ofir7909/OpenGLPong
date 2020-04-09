#include <assert.h>
#include <iostream>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "Game.h"
#include "Renderer.h"
#include "Time.h"

// GameObjects
#include "Ball.h"
#include "Paddle.h"

Paddle* playerPaddle;

// The Play area is	40x30 with 0,0 being the center.

// (-20,15)								(20,15)
//
//
//
//
//
// (-20,-15)							(20,-15)

int main()
{
	{
		Renderer renderer = Renderer::Get();

		Game game;
		game.ResetGame();

		// Game Loop
		while (renderer.IsRunning()) {
			Time::UpdateTime();
			Time::PrintTime();
			// Clear the screen
			renderer.Clear();

			// Call the update and draw functions of all the game objects.
			GameObject::UpdateAll();
			GameObject::DrawAll();

			// Get input and render to the screen.
			renderer.Update();
			renderer.Render();

			if (glfwGetKey(Renderer::Get().GetWindow(), GLFW_KEY_R))
				game.ResetGame();
		}
	}

	// End of program
	std::cout << "Press Any Key To Continue: " << std::endl;
	std::cin.get();
	return 0;
}