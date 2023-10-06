module;
#include <GLFW/glfw3.h>
export module Sandcore.Graphics.Window.Events : Implementation;

import std;
import Sandcore.Graphics.Window.Events;

export namespace Sandcore::Graphics {
	void Events::cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
		Event event = {
			.type = Event::Type::Cursor,
			.cursor = {
				.x = xpos,
				.y = ypos
			}
		};

		events[window].push(event);
	}

	void  Events::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
		Event event = {
			.type = Event::Type::Scroll,
			.scroll = {
				.x = xoffset,
				.y = yoffset
			}
		};

		events[window].push(event);
	}

	void Events::mouse_button_callback(GLFWwindow* window, int button, int action, int mode) {
		Event event = {
			.type = Event::Type::Mouse,
			.mouse = {
				.button = button,
				.action = action,
				.mode = mode
			}
		};

		events[window].push(event);
	}

	void Events::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
		Event event = {
			.type = Event::Type::Key,
			.key = {
				.key = key,
				.scancode = scancode,
				.action = action,
				.mode = mode
			}
		};

		events[window].push(event);
	}

	void Events::window_size_callback(GLFWwindow* window, int width, int height) {
		Event event = {
			.type = Event::Type::Window,
			.window = {
				.width = width,
				.height = height,
			}
		};

		events[window].push(event);
	}

	void Events::window_refresh_callback(GLFWwindow* window) {
		std::println("Refreshed");
		if (refreshes.contains(window)) refreshes[window]();
	}
}