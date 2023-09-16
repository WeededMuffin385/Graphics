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
			return (GetType<N, Args...>&)(data[GetOffset<N>]);
		}

		static void setAttributeDescriptions(GLuint VAO) {
			setAttributeDescriptionHelper<0, 0, Args...>(VAO);
		}
	private:
		static inline constexpr std::size_t Types = (sizeof...(Args));
		static inline constexpr std::size_t Bytes = (sizeof(Args) + ...);

		std::uint8_t data[Bytes];



		template<std::size_t N, std::size_t P, typename T, typename ...Args>
		struct GetOffsetHelper {
			static inline constexpr std::size_t Value = GetOffsetHelper<N - 1, P + sizeof(T), Args...>::Value;
		};

		template<std::size_t P, typename T, typename ...Args>
		struct GetOffsetHelper<0, P, T, Args...> {
			static inline constexpr std::size_t Value = P;
		};

		template<std::size_t N> 
		static inline constexpr std::size_t GetOffset = GetOffsetHelper<N, 0, Args...>::Value;



		template <std::size_t N, typename T, typename... Args>
		struct GetTypeHelper {
			using Type = typename GetTypeHelper<N - 1, Args...>::Type;
		};

		template <typename T, typename... Args>
		struct GetTypeHelper<0, T, Args...> {
			using Type = T;
		};

		template <std::size_t N, typename... Args> 
		using GetType = GetTypeHelper<N, Args...>::Type;



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