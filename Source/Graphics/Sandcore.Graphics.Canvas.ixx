module;
#include "Sandcore.Graphics.OpenGL.hpp"
export module Sandcore.Graphics.Canvas;

import Sandcore.Graphics.Drawable;

export namespace Sandcore {
	class Canvas {
	public:
		Canvas() {

		}

		void draw(Drawable& drawable) {
			bind();
			drawable.draw();
		}

		void clear() {
			glClearNamedFramebufferfv(FBO, GL_COLOR, 0, color);
			glClearNamedFramebufferfv(FBO, GL_DEPTH, 0, &depth);
		}

		void setViewport(int width, int height, int left = 0, int top = 0) {
			glViewport(left, top, width, height);
		}

		void bind() {
			glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		}

	private:
		GLfloat color[4]{ 0, 0, 0, 0 };
		GLfloat depth = 1.0;

		GLuint FBO = 0;
	};
}