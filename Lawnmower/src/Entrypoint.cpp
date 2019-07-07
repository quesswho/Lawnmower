#include "graphics/Window.h"

int main() {
	Window window(1080, 720, "Lawnmower");

	while (window.Running())
	{
		window.Clear();
		window.Update();
	}
	window.~Window();

	return 0;
}