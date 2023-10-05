module;
#include "Sandcore.Graphics.OpenGL.hpp"
export module Sandcore.Graphics.Canvas;

import std;
import Sandcore.Graphics.Shader;
import Sandcore.Graphics.Texture;

export namespace Sandcore::Graphics {
	template<typename T>
	concept Drawable = requires(T value) {
		value.draw();
	};

	class Canvas {
	public:
		Canvas(GLuint FBO = 0) : FBO(FBO) {}
		~Canvas() {}

		template<Drawable T>
		void draw(T& drawable, Program& program) {
			bind();
			program.use();
			drawable.draw();
		}

		template<Drawable T>
		void draw(T& drawable, Program& program, Texture& texture) {
			bind();
			program.use();
			texture.bind();
			drawable.draw();
		}

		void clear(float r, float g, float b, float a) {
			color = { r, g, b, a };
			glClearNamedFramebufferfv(FBO, GL_COLOR, 0, &color.r);
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

		struct {
			GLfloat r;
			GLfloat g;
			GLfloat b;
			GLfloat a;
		} color;

		GLfloat depth = 1.0;
	};
}