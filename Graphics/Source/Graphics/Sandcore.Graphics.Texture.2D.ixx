module;
#include "Sandcore.Graphics.OpenGL.hpp"
export module Sandcore.Graphics.Texture.D2;

import std;
import Sandcore.Graphics.Texture;
import Sandcore.Graphics.Image;

export namespace Sandcore::Graphics {
	class Texture2D : public Texture {
	public:
		void create(int width, int height) {
			this->width = width;
			this->height = height;

			allocate<GL_TEXTURE_2D>();
			glTextureStorage2D(texture, 1, GL_RGBA8, width, height);
		}

		void load(std::filesystem::path path) {
			Image image;
			image.load(path);
			create(image.getWidth(), image.getHeight());
			glTextureSubImage2D(
				texture,
				0,
				0, 0,
				image.getWidth(), image.getHeight(),
				GL_RGBA, GL_UNSIGNED_BYTE,
				image.getData()
			);
		}

		auto getWidth() const { return width; };
		auto getHeight() const { return height; };

	private:
		int width = -1;
		int height = -1;
	};
}