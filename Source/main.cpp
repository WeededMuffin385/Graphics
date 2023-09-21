#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
import std;

import Sandcore.Graphics.Window;
import Sandcore.Graphics.Mesh;
import Sandcore.Graphics.Mesh.Vertex;
import Sandcore.Graphics.Shader;
import Sandcore.Graphics.Debug;
import Sandcore.Graphics.Display;
import Sandcore.Graphics.Camera;

import glm;

using namespace Sandcore;

int main() {
	Sandcore::Display window(1920, 1080, "Hello there");
	debugInit();

	Mesh<glm::vec3> mesh;
	mesh.vertices = {
		{{-0.5f, -0.5f, 0.0f}},
		{{ 0.5f, -0.5f, 0.0f}},
		{{ 0.0f,  0.5f, 0.0f}}
	};

	mesh.indices = {
		0, 1, 2
	};

	mesh.update();

	Camera camera;
	Sandcore::Program program;
	program.load("C:/Users/Mi/Documents/GitHub/Graphics/Userdata/triangle");

	Sandcore::Event event;
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
		}

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		auto [width, height] = window.getSize();

		camera.mouseInput(window);
		camera.keyboardInput(window);

		program.set("view", camera.getViewMatrix());
		program.set("proj", camera.getProjMatrix(width, height));
		program.set("model", glm::gtc::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)));

		window.setViewport(width, height);


		window.draw(mesh, program);
		window.display();
	}
}