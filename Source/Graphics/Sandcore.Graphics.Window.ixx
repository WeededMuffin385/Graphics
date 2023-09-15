module;
#include "Sandcore.Graphics.OpenGL.hpp"
export module Sandcore.Graphics.Window;

import std;
import Sandcore.Graphics.Window.Events;
import Sandcore.Graphics.Image;


export namespace Sandcore {
	bool glfw = glfwInit();

	class Window {
	public:
		Window(int width, int height, const char* title, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr) {
			create(width, height, title, monitor, share);
		}
		
		~Window() {
			destroy();
		}

		Window(const Window& other) = delete;
		Window(Window&& other) = delete;

		void operator=(const Window& other) = delete;
		void operator=(Window&& other) = delete;

		void create(int width, int height, const char* title, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr) {
			window = glfwCreateWindow(width, height, title, monitor, share);
			if (!window) throw std::exception("Unable to create window");
			Events::setWindowCallbacks(window);

			glfwMakeContextCurrent(window);
			glewExperimental = GL_TRUE;
			glewInit();
		}

		void destroy() {
			Events::erase(window);
			if (window) glfwDestroyWindow(window);
		}

		bool pollEvent(Event& event) {
			return Events::pollEvent(window, event);
		}

		void display() {
			glfwSwapBuffers(window);
		}

		bool isOpen() {
			return !glfwWindowShouldClose(window);
		}

		auto getSize() {
			struct {
				int width;
				int height;
			} size{};

			glfwGetWindowSize(window, &size.width, &size.height);
			return size;
		}

		auto getCursor() {
			struct {
				double x;
				double y;
			} position{};

			glfwGetCursorPos(window, &position.x, &position.y);
			return position;
		}

		auto getIcon(Image& image) {
			GLFWimage icon{
				.width = image.getWidth(),
				.height = image.getHeight(),
				.pixels = (std::uint8_t*)(image.getData())
			};

			glfwSetWindowIcon(window, 1, &icon);
		}

	private:
		GLFWwindow* window;
	};
}