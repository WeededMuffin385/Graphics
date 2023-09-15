module;
#include "Sandcore.Graphics.OpenGL.hpp"
export module Sandcore.Graphics.Mesh;

import std;
import Sandcore.Graphics.Mesh.Vertex;

const bool debug = true;

export namespace Sandcore {
	template<typename ...Args>
	class Mesh {
	public:
		using Index = std::uint32_t;
		using Vertex = Sandcore::Vertex<Args...>;

		std::vector<Index> indices;
		std::vector<Vertex> vertices;
	private:

		GLuint VAO;
		GLuint VBO;
		GLuint EBO;
	};
}