#pragma once
#include "renderer/Buffer.h"
#include "Texture/Texture.h"
#include "Shader.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

class Sprite {
public:
	Sprite(glm::vec2 position, glm::vec2 size, glm::vec3 colors, Shader shader);
	~Sprite();

	void Bind() const;
	void Unbind() const;
	

	unsigned int inline getIndexCount() { return m_IndexBuffer->getCount(); }

	glm::vec2 m_Position;
	Shader m_Shader;

private:
	std::shared_ptr<VertexArray> m_VertexArray;
	std::shared_ptr<VertexBuffer> m_VertexBuffer;
	std::shared_ptr<VertexBuffer> m_ColorBuffer;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;
};