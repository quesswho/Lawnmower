#pragma once

#include <Windows.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
enum Action { KEY_RELEASE, KEY_PRESS, KEY_REPEAT };

class Window {
private:
	const char* m_title;
	GLFWwindow* m_window;
public:
	Action m_keys[512];
	unsigned int m_height, m_width;
	Window(unsigned int height, unsigned int width, const char* title);
	~Window();

	void Clear();
	void Update();

	bool Running();
private:
	bool init();
};