#pragma once
#include <glm/vec2.hpp>

#include "Buffer.h"
#include "Texture/Texture.h"
#include "Shader.h"

class TexturedSprite {
public:
	TexturedSprite(glm::vec2 position, glm::vec2 size, Texture texture, Shader shader);
	~TexturedSprite() {}

	void Bind() const;
	void Unbind() const;

	unsigned int inline getIndexCount() { return m_IndexBuffer->getCount(); }
private:
	std::shared_ptr<VertexArray> m_VertexArray;
	std::shared_ptr<VertexBuffer> m_VertexBuffer;
	std::shared_ptr<VertexBuffer> m_texCoords;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;
	Shader m_Shader;
	Texture m_Texture;
};