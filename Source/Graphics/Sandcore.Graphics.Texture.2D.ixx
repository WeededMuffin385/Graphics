module;
#include "Sandcore.Graphics.OpenGL.hpp"
export module Sandcore.Graphics.Texture.TWOD;

import Sandcore.Graphics.Texture;

export namespace Sandcore {
	class Texture2D : public Texture {
	public:
		virtual void create(int width, int height) {
			this->width = width;
			this->height = height;

			allocate<GL_TEXTURE_2D>();
			glTextureStorage2D(texture, 1, GL_RGBA8, width, height);
		}

		auto getWidth() const { return width; };
		auto getHeight() const { return height; };

	private:
		int width = -1;
		int height = -1;
	};
}