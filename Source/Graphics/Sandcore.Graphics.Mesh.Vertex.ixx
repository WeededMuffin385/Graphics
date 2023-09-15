module;
#include "Sandcore.Graphics.OpenGL.hpp"
export module Sandcore.Graphics.Mesh.Vertex;

import std;

const bool debug = true;

export namespace Sandcore {
	template<typename ...Args>
	class Vertex {
	public:
		Vertex(Args...args) {
			constructorHelper(args...);
		}

		template<std::size_t N>
		auto& get() {
			return get<N, 0, Args...>();
		}

		static void setAttributeDescriptions(GLuint VAO) {
			setAttributeDescriptionHelper<0, 0, Args...>(VAO);
		}
	private:
		static inline constexpr std::size_t Types = (sizeof...(Args));
		static inline constexpr std::size_t Bytes = (sizeof(Args) + ...);

		std::uint8_t data[Bytes];

		template<std::size_t N = 0, std::size_t P = 0, typename T, typename ...Args>
		auto& get() {
			if constexpr (N == 0) return (T&)(data[P]); else {
				return get<N - 1, P + sizeof(T), Args...>();
			}
		}

		template<std::size_t N = 0, std::size_t P = 0, typename T, typename ...Args>
		void constructorHelper(T arg, Args ...args) {
			constructorHelper<N + 0, P + 0>(arg);
			constructorHelper<N + 1, P + sizeof(T)>(args...);
		}

		template<std::size_t N = 0, std::size_t P = 0, typename T>
		void constructorHelper(T arg) {
			(T&)(data[P]) = arg;
		}

		template <std::size_t N = 0, std::size_t P = 0, typename T, typename ...Args>
		static void setAttributeDescriptionHelper(GLuint VAO) {
			if constexpr (debug) {
				std::print("N: {} | T: {}\n", N, typeid(T).name());
			} else {
				glEnableVertexArrayAttrib(VAO, N);
				glVertexArrayAttribFormat(VAO, N, sizeof(T) / sizeof(GLfloat), GL_FLOAT, GL_FALSE, P);
				glVertexArrayAttribBinding(VAO, N, 0);
			}

			if constexpr (N != (Types - 1)) setAttributeDescriptionHelper<N + 1, P + sizeof(T), Args...>(VAO);
		}
	};
}