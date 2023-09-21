module;
#include "Sandcore.Graphics.OpenGL.hpp"
export module Sandcore.Graphics.Camera;

import std;
import glm;
import Sandcore.System.Clock;
import Sandcore.Graphics.Window;

export namespace Sandcore {
	class Camera {
	public:
		Camera() {

		}

		glm::mat4 getViewMatrix() {
			return glm::gtc::lookAt(position, position + front, up);
		}
		glm::mat4 getProjMatrix(int width, int height) {
			return glm::gtc::infinitePerspective(glm::radians(zoom), (double)width / (double)height, (double)0.1);
		}

		void setFirst() {
			first = true;
		}

		void mouseInput(Window& window) {
			if (first) {
				auto mouse = window.getCursor();
				lastx = mouse.x;
				lasty = mouse.y;
				first = false;
			}

			double posx;
			double posy;

			auto mouse = window.getCursor();

			double offsetx = mouse.x - lastx;
			double offsety = lasty - mouse.y;

			lastx = mouse.x;
			lasty = mouse.y;

			offsetx *= sensitivity;
			offsety *= sensitivity;

			yaw += offsetx;
			pitch += offsety;

			if (true) {
				if (pitch > 90.0f)
					pitch = 90.0f;
				if (pitch < -90.0f)
					pitch = -90.0f;
			}

			updateVectors();
		}
		void keyboardInput(Window& window) {
			static Clock clock;
			clock.restart();

			double velocity = speed * clock.getElapsedTime();

			if (window.getKey(GLFW_KEY_LEFT_SHIFT)) velocity *= 2;

			if (window.getKey(GLFW_KEY_W)) position += front * (float)velocity;
			if (window.getKey(GLFW_KEY_S)) position -= front * (float)velocity;
			if (window.getKey(GLFW_KEY_A)) position += right * (float)velocity;
			if (window.getKey(GLFW_KEY_D)) position -= right * (float)velocity;

			if (window.getKey(GLFW_KEY_SPACE)) position.z += velocity * 2;
			if (window.getKey(GLFW_KEY_LEFT_CONTROL)) position.z -= velocity;
		}
	protected:
		void updateVectors() {
			front.x = std::sin(glm::gtc::radians(yaw)) * std::cos(glm::gtc::radians(pitch));
			front.y = std::cos(glm::gtc::radians(yaw)) * std::cos(glm::gtc::radians(pitch));
			front.z = std::sin(glm::gtc::radians(pitch));

			front = glm::normalize(front);
			right = glm::normalize(glm::cross(worldUp, front));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
			up = glm::normalize(glm::cross(front, right));
			glm::cross(front, right);
		}

		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 front    = glm::vec3(-1.0f, 0.0f, 0.0f);
		glm::vec3 up       = glm::vec3(0.0f, 0.0f, 1.0f);
		glm::vec3 right    = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 worldUp  = up;

		double yaw = -90.0f;
		double pitch = 0.0f;

		double speed = 5.f;
		double sensitivity = 0.1f;
		double zoom = 45.f;

		bool first = true;

		double lastx;
		double lasty;
	};
}