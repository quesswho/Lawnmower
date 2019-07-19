#include <iostream>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/transform.hpp>
#include <time.h>
#include <algorithm>
#include <Windows.h>

#include "graphics/Window.h"
#include "graphics/Shader.h"
#include "graphics/renderer/Renderer.h"
#include "graphics/Sprite.h"
#include "graphics/TexturedSprite.h"

#define AI 0

#define GRID_SIZE 50
#define GRID_GAP 2.01/GRID_SIZE
#define LAWNMOWER_SIZE GRID_GAP/2-GRID_GAP/100
#define LAWNMOWER_OFFSET GRID_GAP/2


void move(glm::vec2 direction);
void cut(glm::vec2 pos);

glm::mat4x4 mat4(1.0f);

bool iscut[GRID_SIZE*GRID_SIZE] = { 0 };
glm::vec2 pos(0, 0); //bottom, left
std::vector<Sprite*> grid;

int main() {
	srand(time(NULL));

	Window window(720, 720, "Lawnmower");
	

	Renderer renderer(GRID_SIZE*GRID_SIZE);
	renderer.Clear(0.1, 0.4, 0.5);

	Shader BasicShader("res/shader/basic.vs", "res/shader/basic.fs");
	Shader TextureShader("res/shader/texture.vs", "res/shader/texture.fs");

	Texture lawnmowerTexture("res/texture/LawnMower.png");
	TexturedSprite lawnmower(glm::vec3(-1 + LAWNMOWER_OFFSET, -1 + LAWNMOWER_OFFSET, 0.0), glm::vec2(LAWNMOWER_SIZE, LAWNMOWER_SIZE), lawnmowerTexture, TextureShader);

	for (double y = -1; y <= 1.00; y += GRID_GAP)
	{
		for (double x = -1; x <= 1.00; x += GRID_GAP)
		{

			grid.push_back(new Sprite(glm::vec2(x, y), glm::vec2(GRID_GAP, GRID_GAP), glm::vec3(0.0, ((0.2f - 0.1f) * ((float)rand() / RAND_MAX)) + 0.1f, 0.0)));
		}
	}
	cut(pos);

	#if AI
	glm::vec2 botDir;
	bool ai = false;
	#endif

	while (window.Running())
	{
		window.Clear();
#if !AI
		if (window.m_keys[GLFW_KEY_RIGHT] >= 1) {
			move(glm::vec2(1, 0));
			Sleep(100);
		}
		if (window.m_keys[GLFW_KEY_LEFT]) {
			move(glm::vec2(-1, 0));
			Sleep(100);
		}
		if (window.m_keys[GLFW_KEY_UP]) {
			move(glm::vec2(0, 1));
			Sleep(100);
		}
		if (window.m_keys[GLFW_KEY_DOWN]) {
			move(glm::vec2(0, -1));
			Sleep(100);
		}
#else
		if (window.m_keys[GLFW_KEY_X])
			ai = true;
		if (window.m_keys[GLFW_KEY_C])
			ai = false;
		if (ai)
		{
			if (!iscut[(int)((pos.x + 1) + (pos.y) * GRID_SIZE)] && pos.x+1!=GRID_SIZE)
				botDir = glm::vec2(1.0, 0.0);
			else if(!iscut[(int)((pos.x) + (pos.y+1) * GRID_SIZE)] && pos.y + 1 != GRID_SIZE)
				botDir = glm::vec2(0.0, 1.0);
			else if (!iscut[(int)((pos.x + -1) + (pos.y) * GRID_SIZE)])
				botDir = glm::vec2(-1.0, 0.0);
			else if (!iscut[(int)((pos.x) + (pos.y + -1) * GRID_SIZE)])
				botDir = glm::vec2(0.0, -1.0);
			else
				botDir = glm::vec2(0.0, 0.0);
			move(botDir);
			//Sleep(1);
		}
#endif
		TextureShader.setUniformMat4x4("model_matrix", mat4);
		BasicShader.Bind();

		renderer.Begin();
		for (int i = 0; i < grid.size(); i++)
		{
			renderer.Submit(grid[i]);
		}
		renderer.Submit(lawnmower);
		renderer.End();

		renderer.Draw();

		window.Update();
	}
	
	window.~Window();

	return 0;
}

void move(glm::vec2 move)
{
	glm::vec2 newPos = pos + move;

	//collision testing
	if (newPos.x >= GRID_SIZE)
		return;
	if (newPos.x < 0)
		return;
	if (newPos.y >= GRID_SIZE)
		return;
	if (newPos.y < 0)
		return;

	pos = newPos;
	mat4 *= glm::translate(glm::vec3(move *= GRID_GAP, 0.0));
	cut(pos);
}

void cut(glm::vec2 pos)
{
	int arraypos = (int)((pos.x) + (pos.y) * GRID_SIZE);
	iscut[arraypos] = true;
	std::vector<Sprite*> temp;
	int i = 0;
	while (temp.size() != grid.size())
	{
		if (temp.size() != arraypos)
		{
			temp.push_back(grid.at(i));
		}
		else {
			temp.push_back(new Sprite(grid.at(i)->getPosition(), glm::vec2(GRID_GAP, GRID_GAP), glm::vec4(0.0, ((0.8f - 0.7f) * ((float)rand() / RAND_MAX)) + 0.7f, 0.0,0.0)));
		}
		i++;
	}
	grid = temp;
}

