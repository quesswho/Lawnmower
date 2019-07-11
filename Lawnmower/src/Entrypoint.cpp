#include <iostream>
#include <glm/vec2.hpp>
#include <time.h>

#include "graphics/Window.h"
#include "graphics/Shader.h"
#include "graphics/Renderer.h"

#define GRID_SIZE 10
#define GRID_GAP 2.0/GRID_SIZE

int main() {
	srand(time(NULL));

	Window window(720, 720, "Lawnmower");
	
	Renderer renderer;
	Shader shader("res/shaders/basic.vs", "res/shaders/basic.fs");

	renderer.Clear(0.1, 0.4, 0.5);
	
	Sprite sprite(glm::vec2(0.1,0.1), glm::vec2(1,1), glm::vec3(0.2,0.9,0.3));

	std::vector<Sprite> grid;

	for (float y = -1; y < 1.00; y += GRID_GAP)
	{
		for (float x = -1; x < 1.00; x += GRID_GAP)
		{
			grid.push_back(Sprite(glm::vec2(x, y), glm::vec2(GRID_GAP, GRID_GAP), glm::vec3(0.0, ((1.0f - 0.7f) * ((float)rand() / RAND_MAX)) + 0.7f, 0.0)));
		}
	}

	while (window.Running())
	{
		window.Clear();

		for (int i = 0; i < grid.size(); i++)
		{
			renderer.Submit(grid[i]);
		}
		
		//renderer.Submit(sprite);


		shader.Bind();
		renderer.Draw();

		window.Update();
	}
	
	window.~Window();

	return 0;
}