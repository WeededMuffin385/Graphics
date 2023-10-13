module;
#include "Sandcore.Graphics.OpenGL.hpp"
export module Sandcore.Graphics.Mesh.Vertex;

import std;
import Sandcore.Graphics.Debug;

export namespace Sandcore::Graphics {
	template<typename ...Args>
	class Vertex {
	public:
		Vertex(Args...args) {
			constructorHelper(args...);
		}

		template<std::size_t N>
		auto& get() {
			using Get = Get<N>;
			return reinterpret_cast<Get::Type&>(data[Get::Offset]);
		}

		static void setAttributeDescriptions(GLuint VAO) {
			setAttributeDescriptionHelper<0, 0, Args...>(VAO);
		}
	private:
		static constexpr std::size_t Types = (sizeof...(Args));
		static constexpr std::size_t Bytes = (sizeof(Args) + ...);

		std::byte data[Bytes];

		template<std::size_t N, std::size_t P, typename T, typename ...Args>
		struct GetHelper {
			using GetHelperNext = GetHelper<N - 1, P + sizeof(T), Args...>;

			using Type = GetHelperNext::Type;
			static constexpr std::size_t Offset = GetHelperNext::Offset;
		};

		template<std::size_t P, typename T, typename ...Args>
		struct GetHelper<0, P, T, Args...> {
			using Type = T;
			static constexpr std::size_t Offset = P;
		};

		template<std::size_t N>
		using Get = GetHelper<N, 0, Args...>;


		template<std::size_t P = 0, typename T, typename ...Args>
		void constructorHelper(T arg, Args ...args) {
			constructorHelper<P>(arg);
			constructorHelper<P + sizeof(T)>(args...);
		}

		template<std::size_t P = 0, typename T>
		void constructorHelper(T arg) {
			(T&)(data[P]) = arg;
		}

		template <std::size_t N = 0, std::size_t P = 0, typename T, typename ...Args>
		static void setAttributeDescriptionHelper(GLuint VAO) {
			if constexpr (debug) {
				std::println("[Vertex Debug] N: {} | T: {}", N, typeid(T).name());
			} else {
				glEnableVertexArrayAttrib(VAO, N);
				glVertexArrayAttribFormat(VAO, N, sizeof(T) / sizeof(GLfloat), GL_FLOAT, GL_FALSE, P);
				glVertexArrayAttribBinding(VAO, N, 0);
			}

			if constexpr (N != Types - 1) setAttributeDescriptionHelper<N + 1, P + sizeof(T), Args...>(VAO);
		}
	};
}