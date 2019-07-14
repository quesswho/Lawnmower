#include <iostream>
#include <glm/vec2.hpp>
#include <time.h>

#include "graphics/Window.h"
#include "graphics/Shader.h"
#include "graphics/Renderer.h"
#include "graphics/TexturedSprite.h"
//#include "util/FileUtils.h"

#define GRID_SIZE 8
#define GRID_GAP 2.0/GRID_SIZE
#define LAWNMOWER_SIZE GRID_GAP/2-GRID_GAP/10
#define LAWNMOWER_OFFSET GRID_GAP/2

int main() {
	srand(time(NULL));

	Window window(720, 720, "Lawnmower");
	
	Renderer renderer;
	Shader BasicShader("res/shader/basic.vs", "res/shader/basic.fs");
	Shader TextureShader("res/shader/texture.vs", "res/shader/texture.fs");

	renderer.Clear(0.1, 0.4, 0.5);
	
	Texture lawnmowerTexture("res/texture/LawnMower.png");
	TexturedSprite lawnmower(glm::vec2(-1 + LAWNMOWER_OFFSET, 0 + LAWNMOWER_OFFSET), glm::vec2(LAWNMOWER_SIZE, LAWNMOWER_SIZE), lawnmowerTexture, TextureShader);

	bool iscut[GRID_SIZE*GRID_SIZE] = { 0 };

	std::vector<Sprite> grid;

	int i = 0;
	for (float y = -1; y < 1.00; y += GRID_GAP)
	{
		for (float x = -1; x < 1.00; x += GRID_GAP)
		{

			grid.push_back(Sprite(glm::vec2(x, y), glm::vec2(GRID_GAP, GRID_GAP), glm::vec3(0.0, ((0.2f - 0.1f) * ((float)rand() / RAND_MAX)) + 0.1f, 0.0), BasicShader));
			i++;
		}
	}

	while (window.Running())
	{
		window.Clear();

		renderer.Submit(lawnmower);
		for (int i = 0; i < grid.size(); i++)
		{
			renderer.Submit(grid[i]);
		}

		renderer.Draw();

		window.Update();
	}
	
	window.~Window();

	return 0;
}