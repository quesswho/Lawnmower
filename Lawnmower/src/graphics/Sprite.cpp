#include "Sprite.h"
#include <iostream>

Sprite::Sprite(glm::vec2 position, glm::vec2 size, glm::vec3 f_colors, Shader shader)
	: m_Shader(shader)
{

	float vertices[] = {
		size.x  + position.x, size.y  + position.y, 0.0f,
		size.x  + position.x, -size.y + position.y, 0.0f,
		-size.x + position.x, -size.y + position.y, 0.0f,
		-size.x + position.x, size.y  + position.y, 0.0f,
	};

	float colors[] = {
		f_colors.x, f_colors.y, f_colors.z,
		f_colors.x, f_colors.y, f_colors.z,
		f_colors.x, f_colors.y, f_colors.z,
		f_colors.x, f_colors.y, f_colors.z,
		f_colors.x, f_colors.y, f_colors.z,
		f_colors.x, f_colors.y, f_colors.z,
	};

	unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3
	};

	m_VertexArray.reset(new VertexArray());
	m_VertexArray->Bind();

	m_VertexBuffer.reset(new VertexBuffer(vertices, sizeof(vertices)));
	m_ColorBuffer.reset(new VertexBuffer(colors, sizeof(colors)));
	m_IndexBuffer.reset(new IndexBuffer(indices, sizeof(indices)));

	m_VertexArray->AddVertexBuffer(m_VertexBuffer, 0);
	m_VertexArray->AddVertexBuffer(m_ColorBuffer, 1);
	m_VertexArray->SetIndexBuffer(m_IndexBuffer);
}

Sprite::~Sprite()
{}


void Sprite::Bind() const
{
	m_VertexArray->Bind();
	m_Shader.Bind();
}

void Sprite::Unbind() const
{
	m_VertexArray->Unbind();
	m_Shader.Unbind();
}