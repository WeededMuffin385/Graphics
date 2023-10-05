module;
#include "Sandcore.Graphics.OpenGL.hpp"
export module Sandcore.Graphics.Framebuffer;

import Sandcore.Graphics.Canvas;

export namespace Sandcore::Graphics {
	class Framebuffer : public Canvas {
	public:
		Framebuffer() {
			glCreateFramebuffers(1, &FBO);
		}

		~Framebuffer(){ glDeleteFramebuffers(1, &FBO); }
	};
}