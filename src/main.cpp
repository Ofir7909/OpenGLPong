#include <assert.h>
#include <iostream>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "Renderer.h"

int main()
{
	{
		Renderer renderer;
		renderer.init();

		// The rectangle
		// 3	2
		//
		// 0	1

		float vertices[] = {
			-0.5f, -0.5f, //
			0.5f,  -0.5f, //
			0.5f,  0.5f,  //
			-0.5f, 0.5f,  //
		};

		unsigned int indices[] = {
			0, 1, 2, //
			2, 3, 0	 //
		};

		// Vertex Array and buffer
		VertexArray va;
		VertexBuffer vb(vertices, sizeof(float) * 2 * 4);

		VertexBufferLayout layout;
		layout.Push<float>(2);

		va.AddBuffer(vb, layout);

		// Index Buffer
		IndexBuffer ib(indices, 3 * 2);

		// Shader
		Shader shader("res/Basic.shader");

		va.Unbind();
		vb.Unbind();
		ib.Unbind();
		shader.Unbind();

		// Game Loop
		while (renderer.IsRunning()) {
			// Clear the screen
			renderer.Clear();

			shader.Bind();
			shader.SetUniform4f("u_Color", 1.f, 0.f, 0.f, 1.f);

			renderer.Draw(va, ib);

			renderer.Render();
		}
	}

	// End of program
	std::cout << "Press Any Key To Continue: " << std::endl;
	getchar();
	return 0;
}