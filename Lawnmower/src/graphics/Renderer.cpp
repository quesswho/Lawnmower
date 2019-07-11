#include "Renderer.h"
#include <GL/glew.h>
Renderer::Renderer()
{
	//setup camera
}

void Renderer::Clear(float x, float y, float z)
{
	glClearColor(x,y,z,1.0);
}

void Renderer::Submit(const Sprite sprite)
{
	m_Sprites.push_back(sprite);
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
}