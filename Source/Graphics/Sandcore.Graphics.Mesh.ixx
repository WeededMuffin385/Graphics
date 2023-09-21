module;
#include "Sandcore.Graphics.OpenGL.hpp"
export module Sandcore.Graphics.Mesh;

import std;
import Sandcore.Graphics.Mesh.Vertex;

export namespace Sandcore {
	template<typename ...Args>
	class Mesh {
	public:
		Mesh() {
			glCreateVertexArrays(1, &VAO);
			Vertex::setAttributeDescriptions(VAO);
		}

		~Mesh() {
			glDeleteBuffers(1, &VBO);
			glDeleteBuffers(1, &EBO);
			glDeleteVertexArrays(1, &VAO);
		}

		void draw() {
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
		}

		void clear() {
			indices.clear();
			vertices.clear();
		}

		void update() {
			glDeleteBuffers(1, &VBO);
			glDeleteBuffers(1, &EBO);

			glCreateBuffers(1, &VBO);
			glCreateBuffers(1, &EBO);

			glVertexArrayVertexBuffer(VAO, 0, VBO, 0, sizeof(Vertex));
			glVertexArrayElementBuffer(VAO, EBO);

			glNamedBufferStorage(EBO, sizeof(Index) * indices.size(), indices.data(), GL_DYNAMIC_STORAGE_BIT);
			glNamedBufferStorage(VBO, sizeof(Vertex) * vertices.size(), vertices.data(), GL_DYNAMIC_STORAGE_BIT);
		}

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