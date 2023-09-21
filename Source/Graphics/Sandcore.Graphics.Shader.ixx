module;
#include "Sandcore.Graphics.OpenGL.hpp"
export module Sandcore.Graphics.Shader;

import std;
import glm;


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
			glDeleteShader(shader);
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
			clear();
		}

		Program(Program&& other) {
			program = other.program;
			other.program = 0;
		}

		Program& operator=(Program&& other) {
			if (this != &other) {
				clear();
				program = other.program;
				other.program = 0;
			}

			return *this;
		}

		Program(const Program& other) = delete;
		Program& operator=(const Program& other) = delete;

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

		void use() {
			glUseProgram(program);
		}

		template<typename T> void set(std::string name, T value) {
			glUseProgram(program);
			auto location = getLocation(name);
			SetHelper<T>::value(location, value);
		}

		template<> void set<glm::vec3>(std::string name, glm::vec3 value) {
			glUseProgram(program);
			auto location = getLocation(name);
			SetHelper<glm::vec3>::value(location, 1, glm::gtc::value_ptr(value));
		}

		template<> void set<glm::mat4>(std::string name, glm::mat4 value) {
			glUseProgram(program);
			auto location = getLocation(name);
			SetHelper<glm::mat4>::value(location, 1, GL_FALSE, glm::value_ptr(value));
		}

	private:
		template<typename T> struct SetHelper {};
		template<> struct SetHelper<int> { static inline auto& value = glUniform1i; };
		template<> struct SetHelper<float> { static inline auto& value = glUniform1f; };
		template<> struct SetHelper<glm::vec3> { static inline auto& value = glUniform3fv; };
		template<> struct SetHelper<glm::mat4> { static inline auto& value = glUniformMatrix4fv; };

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

		GLint getLocation(std::string name) { 
			return glGetUniformLocation(program, name.c_str()); 
		}

		void clear() {
			glDeleteProgram(program);
		}

		GLuint program;
	};
}