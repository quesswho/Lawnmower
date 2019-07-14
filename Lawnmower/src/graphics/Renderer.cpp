#include "Renderer.h"
#include <GL/glew.h>
Renderer::Renderer()
{
	//Enable transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::Clear(float x, float y, float z)
{
	glClearColor(x,y,z,1.0);
}

void Renderer::Submit(const Sprite sprite)
{
	m_Sprites.push_back(sprite);
}

void Renderer::Submit(const TexturedSprite texsprite)
{
	m_TexSprites.push_back(texsprite);
}

void Renderer::Draw()
{
	while (!m_Sprites.empty())
	{
		Sprite sprite = m_Sprites.back();
		sprite.Bind();
		glDrawElements(GL_TRIANGLES, sprite.getIndexCount(), GL_UNSIGNED_INT, 0);
		m_Sprites.pop_back();
	}

	while (!m_TexSprites.empty())
	{
		TexturedSprite sprite = m_TexSprites.back();
		sprite.Bind();
		glDrawElements(GL_TRIANGLES, sprite.getIndexCount(), GL_UNSIGNED_INT, 0);
		m_TexSprites.pop_back();
	}
}