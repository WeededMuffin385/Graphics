module;
#include "Sandcore.Graphics.OpenGL.hpp"
export module Sandcore.Graphics.Texture;

export namespace Sandcore::Graphics {
	class Texture {
	public:
		Texture() {

		}

		virtual ~Texture() {
			clear();
		}

		Texture(Texture&& other) {
			texture = other.texture;
			other.texture = 0;

			unit = other.unit;
		}

		Texture& operator=(Texture&& other) {
			if (this != &other) {
				clear();
				texture = other.texture;
				other.texture = 0;

				unit = other.unit;
			}

			return *this;
		}

		Texture(const Texture& other) = delete;
		Texture& operator=(const Texture& other) = delete;

		void setParameter(GLenum name, GLint value) {
			glTextureParameteri(texture, name, value);
		}

		void generateMipmap() {
			glGenerateTextureMipmap(texture);
		}

		void bind(GLuint unit = 0) {
			glBindTextureUnit(unit, texture);
		}

		void unbind() {
			glBindTextureUnit(unit, 0);
		}
	protected:
		template<GLenum T>
		void allocate() {
			glDeleteTextures(1, &texture);
			glCreateTextures(T, 1, &texture);

			setParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			setParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			setParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			setParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}

		void clear() {
			glDeleteTextures(1, &texture);
		}

		GLuint unit = 0;
		GLuint texture = 0;
	};
}