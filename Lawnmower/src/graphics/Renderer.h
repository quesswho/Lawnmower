#pragma once

#include "Sprite.h"
#include <vector>

class Renderer {
private:
	std::vector<Sprite> m_Sprites;
public:
	Renderer();

	void Clear(float x, float y, float z);

	void Submit(const Sprite sprite);

	void Draw();
};