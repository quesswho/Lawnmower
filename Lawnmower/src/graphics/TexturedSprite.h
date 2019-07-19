#pragma once
#include <glm/vec2.hpp>

#include "renderer/Buffer.h"
#include "Texture/Texture.h"
#include "Shader.h"

class TexturedSprite {
public:
	TexturedSprite(const glm::vec3 position, const glm::vec2 size, const Texture texture, Shader shader);
	~TexturedSprite() {}

	void Bind() const;
	void Unbind() const;

	const unsigned int inline getIndexCount() const { return m_IndexBuffer->getCount(); }
private:
	std::shared_ptr<VertexArray> m_VertexArray;
	std::shared_ptr<VertexBuffer> m_VertexBuffer;
	std::shared_ptr<VertexBuffer> m_TexCoords;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;
	Shader m_Shader;
	const Texture m_Texture;
};