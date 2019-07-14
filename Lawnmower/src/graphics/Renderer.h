#pragma once

#include "TexturedSprite.h"
#include "Sprite.h"
#include <vector>

class Renderer {
private:
	std::vector<Sprite> m_Sprites;
	std::vector<TexturedSprite> m_TexSprites;
public:
	Renderer();

	void Clear(float x, float y, float z);

	void Submit(const Sprite sprite);
	void Submit(const TexturedSprite sprite);

	void Draw();
};