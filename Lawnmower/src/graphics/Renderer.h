#pragma once

#include "Buffer.h"
#include <vector>

class Renderer {
private:
	std::vector<std::shared_ptr<VertexArray>> m_Sprites;
public:
	Renderer();

	void Clear() const;

	void Begin();
	void End();
	void Submit(const std::shared_ptr<VertexArray>& vertexArray);

	void Draw();
};