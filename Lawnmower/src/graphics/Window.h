#pragma once

#include <Windows.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
private:
	const char* m_title;
	GLFWwindow* m_window;
public:
	unsigned int m_height, m_width;
	Window(unsigned int height, unsigned int width, const char* title);
	~Window();

	void Clear();
	void Update();

	bool Running();
private:
	bool init();
};