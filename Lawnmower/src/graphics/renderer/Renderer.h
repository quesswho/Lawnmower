#pragma once

#include "graphics/TexturedSprite.h"
#include "graphics/Sprite.h"
#include "Buffer.h"
#include <vector>

struct PointData {
	glm::vec3 vertex;
	glm::vec4 color;
};

class Renderer {
public:
	Renderer(unsigned int bufferSize);
	~Renderer();

	void Clear(const float x, const float y, const float z);

	void Begin();
	void Submit(const Sprite* sprite);
	void Submit(const TexturedSprite sprite);
	void End();

	void Draw();
private:
	std::shared_ptr<VertexArray> m_Buffer;
	std::shared_ptr<VertexBuffer> m_VertexBuffer;
	IndexBuffer* m_IndexBuffer;
	unsigned int m_IndexCount;
	PointData* m_Points;
	std::vector<TexturedSprite> m_TexSprites;
};