module;
#include "Sandcore.Graphics.OpenGL.hpp"
export module Sandcore;

import std;

export namespace Sandcore {
	class Shader {
	public:
		enum Type {
			Vertex = GL_VERTEX_SHADER,
			Fragment = GL_FRAGMENT_SHADER
		};

		Shader(Type type) {
			shader = glCreateShader(type);
		}

		~Shader() {
			glDeleteShader(type);
		}

		void load(std::filesystem::path path) {
			if (not std::filesystem::exists(path)) {
				throw std::exception("No shaders in current path");
			}

			auto source = (std::stringstream() << std::ifstream(path).rdbuf()).str();
			auto raw = source.c_str();
			glShaderSource(shader, 1, &raw, nullptr);
			glCompileShader(shader);
			status();
		}

		auto get() const {
			return shader;
		}

	private:
		void status() {
			GLint success;
			GLchar log[512];

			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shader, 512, nullptr, log);
				switch (type) {
					case Type::Vertex:
						std::println("Compile error: vertex shader. {}!", log);
						break;
					case Type::Fragment:
						std::println("Compile error: fragment shader. {}!", log);
						break;
				}
				throw std::exception("Bad shader!");
			}
		}

		Type type;
		GLuint shader;
	};

	class Program {
	public:
		Program() {
			program = glCreateProgram();
		}

		~Program() {
			glDeleteProgram(program);
		}

		void load(std::filesystem::path path) {
			std::filesystem::path vertPath;
			std::filesystem::path fragPath;

			for (auto& file : std::filesystem::directory_iterator(path)) {
				auto extension = file.path().extension();

				if (extension == ".vert") vertPath = file.path();
				if (extension == ".frag") fragPath = file.path();
			}

			Shader vertShader(Shader::Type::Vertex);
			Shader fragShader(Shader::Type::Fragment);

			vertShader.load(vertPath);
			fragShader.load(fragPath);

			glAttachShader(program, vertShader.get());
			glAttachShader(program, fragShader.get());
			glLinkProgram(program);
			status();

		}

		template<typename T> struct SetHelper{};
		template<> struct SetHelper<int> { static inline auto value = glUniform1i; };
		template<> struct SetHelper<float> { static inline auto value = glUniform1f; };

		template<typename T> void set(std::string name, T value) {
			glUseProgram(program);
			auto location = glGetUniformLocation(program, name.c_str());
			SetHelper<T>::value(location, value);
		}
	private:
		void status() {
			GLint success;
			GLchar log[512];

			glGetProgramiv(program, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(program, 512, nullptr, log);
				std::println("Link error: program. {}!", log);
				throw std::exception("Bad program!");
			}
		}


		GLuint program;
	};
}