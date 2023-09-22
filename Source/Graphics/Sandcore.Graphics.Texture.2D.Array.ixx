module;
#include "Sandcore.Graphics.OpenGL.hpp"
export module Sandcore.Graphics.Texture.D2.Array;

import std;
import Sandcore.Graphics.Texture;
import Sandcore.Graphics.Image;

export namespace Sandcore {
	class Texture2DArray : public Texture {
	public:
		virtual void create(int width, int height, int depth) {
			this->width = width;
			this->height = height;
			this->depth = depth;


			allocate<GL_TEXTURE_2D_ARRAY>();
			glTextureStorage3D(texture, 7, GL_RGBA8, width, height, depth);
		}

		void load(std::filesystem::path path, int index) {
			Image image;
			image.load(path);
			
			glTextureSubImage3D(
				texture,
				0,
				0, 0, index,
				width, height, 1,
				GL_RGBA, GL_UNSIGNED_BYTE,
				image.getData()
			);
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