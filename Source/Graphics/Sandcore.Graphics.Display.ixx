export module Sandcore.Graphics.Display;

import Sandcore.Graphics.Window;
import Sandcore.Graphics.Canvas;

export namespace Sandcore {
	class Display : public Canvas, public Window {
	public:
		Display(int width, int height, const char* title, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr) : Window(width, height, title, monitor, share) {}
	};
}