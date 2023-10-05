module;
#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <stb/stb_image_resize.h>
#include <stb/stb_image_write.h>
#include <stb/stb_image.h>
export module Sandcore.Graphics.Image;

import std;

export namespace Sandcore::Graphics {
	struct Pixel {
		std::uint8_t r;
		std::uint8_t g;
		std::uint8_t b;
		std::uint8_t a;
	};

	class Image {
	public:
		Image() {

		}

		Image(int width, int height) {
			create(width, height);
		}

		~Image() {
			free();
		}

		Image(const Image& image) = delete;
		void operator=(const Image& image) = delete;

		Image(Image&& image) = delete;
		void operator=(Image&& image) = delete;

		Pixel& at(int x, int y) {
			return data[x + y * width];
		}

		void free() {
			std::free(data);
		}

		void create(int width, int height) {
			this->width = width;
			this->height = height;
			data = (Pixel*)(std::malloc(width * height * sizeof(Pixel)));
		}

		void load(std::filesystem::path path) {
			data = (Pixel*)(stbi_load(path.string().c_str(), &width, &height, nullptr, channels));
		}

		void save(std::filesystem::path path) {
			auto extension = path.extension();

			if (extension == ".png") stbi_write_png(path.string().c_str(), width, height, channels, data, width * channels);
			if (extension == ".jpg" || extension == ".jpeg") stbi_write_jpg(path.string().c_str(), width, height, channels, data, 100);
		}

		auto getData() const { return data; }
		auto getWidth() const { return width; }
		auto getHeight() const { return height; }
	private:
		Pixel* data = nullptr;
		int width = 0;
		int height = 0;
		int channels = 4;
	};
}