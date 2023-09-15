#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
import std;

import Sandcore.Graphics.Window;
import Sandcore.Graphics.Mesh;
import Sandcore.Graphics.Mesh.Vertex;

using namespace Sandcore;

int main() {
	Mesh<int, float, double> x;

	x.vertices.emplace_back(1, 3.25, 22);

	auto a = x.vertices[0].get<0>();
	auto b = x.vertices[0].get<1>();
	auto c = x.vertices[0].get<2>();


	std::println("Hello world | a: {} | b: {} | c: {}", a, b, c);



	/*
	Sandcore::Window window(1920, 1080, "Hello there");
	Sandcore::Event event;

	while (window.isOpen()) while (window.pollEvent(event));
	*/
}