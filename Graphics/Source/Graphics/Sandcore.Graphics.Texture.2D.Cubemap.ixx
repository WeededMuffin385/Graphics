module;
#include "Sandcore.Graphics.OpenGL.hpp"
export module Sandcore.Graphics.Texture.D2.Cubemap;

import std;
import Sandcore.Graphics.Texture;
import Sandcore.Graphics.Image;


export namespace Sandcore::Graphics {
	class Texture2DCubemap : public Texture {
	public:
		void create(int width) {
			create(width, width);
		}

		void create(int width, int height) {
			this->width = width;
			this->height = height;

			allocate<GL_TEXTURE_CUBE_MAP>();
			glTextureStorage2D(texture, 1, GL_RGBA8, width, height);

			setParameter(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		}


		void load(std::filesystem::path path, int index) {
			Image image;
			image.load(path);
			load(image, index);
		}

		void load(Image& image, int index) {
			glTextureSubImage3D(
				texture,
				0,
				0, 0, index,
				width, height, 1,
				GL_RGBA, GL_UNSIGNED_BYTE,
				image.getData()
			);
		}

		void load(std::filesystem::path path) {
			Image image;
			image.load(path / "posx.png");

			if (image.getWidth() != width) {
				create(image.getWidth());
			}

			load(path / "posx.png", 0);
			load(path / "negx.png", 1);

			load(path / "posy.png", 2);
			load(path / "negy.png", 3);

			load(path / "posz.png", 4);
			load(path / "negz.png", 5);
		}

		auto getWidth() const { return width; };
		auto getHeight() const { return height; };

	private:
		int width = -1;
		int height = -1;
	};
}