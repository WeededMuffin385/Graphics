module;
#include "Sandcore.Graphics.OpenGL.hpp"
export module Sandcore.Graphics.Canvas;

import std;
import Sandcore.Graphics.Shader;

export namespace Sandcore {
	template<typename T>
	concept Drawable = requires(T value) {
		value.draw();
	};

	class Canvas {
	public:
		Canvas(GLuint FBO = 0) : FBO(FBO) {}
		~Canvas() { }

		template<Drawable T>
		void draw(T& drawable, Program& program) {
			bind();
			program.use();
			drawable.draw();
		}

		void clear() {
			glClearNamedFramebufferfv(FBO, GL_COLOR, 0, color);
			glClearNamedFramebufferfv(FBO, GL_DEPTH, 0, &depth);
		}

		void setViewport(int width, int height, int left = 0, int top = 0) {
			bind();
			glViewport(left, top, width, height);
		}

		void bind() {
			glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		}

	protected:

		GLuint FBO = 0;
		GLfloat color[4]{ 0, 0, 0, 0 };
		GLfloat depth = 1.0;
	};
}