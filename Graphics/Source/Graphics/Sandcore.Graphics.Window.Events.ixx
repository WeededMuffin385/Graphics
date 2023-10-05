module;
#include "Sandcore.Graphics.OpenGL.hpp"
export module Sandcore.Graphics.Window.Events;

import std;

export namespace Sandcore::Graphics {
	struct Event {
		enum class Type {
			Cursor,
			Scroll,
			Mouse,
			Key,
			Window
		};

		Type type;

		union {
			struct {
				double x;
				double y;
			} cursor;

			struct {
				double x;
				double y;
			} scroll;

			struct {
				int button;
				int action;
				int mode;
			} mouse;

			struct {
				int key;
				int scancode;
				int action;
				int mode;
			} key;

			struct {
				int width;
				int height;
			} window;
		};
	};

	class Events {
	public:
		static bool pollEvent(GLFWwindow* window, Event& event) {
			glfwPollEvents();
			if (events[window].empty()) return false;
			event = events[window].front();
			events[window].pop();
			return true;
		}

		static void setWindowCallbacks(GLFWwindow* window) {
			glfwSetCursorPosCallback(window, cursor_position_callback);
			glfwSetScrollCallback(window, scroll_callback);
			glfwSetMouseButtonCallback(window, mouse_button_callback);
			glfwSetKeyCallback(window, key_callback);
			glfwSetWindowSizeCallback(window, window_size_callback);
			glfwSetWindowRefreshCallback(window, window_refresh_callback);
		}

		static void erase(GLFWwindow* window) {
			events.erase(window);
		}

	private:
		static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mode);
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
		static void window_size_callback(GLFWwindow* window, int width, int height);
		static void window_refresh_callback(GLFWwindow* window);

		static inline std::unordered_map<GLFWwindow*, std::queue<Event>> events;
	};
}