#include <iostream>
#include "graphics/Window.h"
#include "graphics/Shader.h"
#include "graphics/Buffer.h"
#include "graphics/Renderer.h"

int main() {
	Window window(1080, 720, "Lawnmower");
	
	Renderer renderer;
	Shader shader("res/shaders/test.vs", "res/shaders/test.fs");
	


	glClearColor(0.1, 0.4, 0.5, 1.0);

	float vertices[] = {
		0.1f,  0.1f, 0.0f,
		0.1f, -0.1f, 0.0f,
		-0.1f, -0.1f, 0.0f,
		-0.1f,  0.1f, 0.0f
	};

	unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3
	};
	
	std::shared_ptr<VertexArray> vertexArray;
	vertexArray.reset(new VertexArray());

	vertexArray->Bind();

	std::shared_ptr<VertexBuffer> vertexBuffer;
	vertexBuffer.reset(new VertexBuffer(vertices, sizeof(vertices)));

	std::shared_ptr<IndexBuffer> indexBuffer;
	indexBuffer.reset(new IndexBuffer(indices, sizeof(indices)));

	vertexArray->AddVertexBuffer(vertexBuffer);
	vertexArray->SetIndexBuffer(indexBuffer);

	renderer.Submit(vertexArray);

	while (window.Running())
	{
		window.Clear();

		shader.Bind();
		renderer.Draw();
		/*vertexArray->Bind();
		glDrawElements(GL_TRIANGLES, indexBuffer->getCount(), GL_UNSIGNED_INT, 0);
		vertexArray->Unbind();*/

		window.Update();
	}
	
	vertexBuffer->~VertexBuffer();
	indexBuffer->~IndexBuffer();

	window.~Window();

	return 0;
}