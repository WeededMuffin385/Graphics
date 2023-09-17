module;
#include "Sandcore.Graphics.OpenGL.hpp"
export module Sandcore.Graphics.Texture.THREED;

import Sandcore.Graphics.Texture;

export namespace Sandcore {
	class Texture3D : public Texture {
	public:
		virtual void create(int width, int height, int depth) {
			this->width = width;
			this->height = height;
			this->depth = depth;


			allocate<GL_TEXTURE_3D>();
			glTextureStorage3D(texture, 7, GL_RGBA8, width, height, depth);
		}

		auto getWidth() const { return width; };
		auto getHeight() const { return height; };
		auto getDepth() const { return depth; };

	private:
		int width = -1;
		int height = -1;
		int depth = -1;
	};
}