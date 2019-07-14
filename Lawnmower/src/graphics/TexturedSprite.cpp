#include "TexturedSprite.h"

TexturedSprite::TexturedSprite(glm::vec2 position, glm::vec2 size, Texture texture, Shader shader)
	: m_Shader(shader), m_Texture(texture)
{

	float vertices[] = {
		size.x + position.x, size.y + position.y, 0.0f,
		size.x + position.x, -size.y + position.y, 0.0f,
		-size.x + position.x, -size.y + position.y, 0.0f,
		-size.x + position.x, size.y + position.y, 0.0f,
	};

	float texCoords[] = {
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f
	};

	unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3
	};

	m_VertexArray.reset(new VertexArray());
	m_VertexArray->Bind();

	m_VertexBuffer.reset(new VertexBuffer(vertices, sizeof(vertices)));
	m_texCoords.reset(new VertexBuffer(texCoords, sizeof(texCoords)));
	m_IndexBuffer.reset(new IndexBuffer(indices, sizeof(indices)));

	m_VertexArray->AddVertexBuffer(m_VertexBuffer, 0);
	m_VertexArray->AddTextureBuffer(m_texCoords, 2);
	m_VertexArray->SetIndexBuffer(m_IndexBuffer);
	m_Shader.Bind();
	m_Shader.setUniform1i("texture1", 0);
	texture.Unbind();
}

void TexturedSprite::Bind() const
{
	m_VertexArray->Bind();
	m_Shader.Bind();
	m_Texture.Bind();
}

void TexturedSprite::Unbind() const
{
	m_VertexArray->Unbind();
	m_Shader.Unbind();
	m_Texture.Unbind();
}