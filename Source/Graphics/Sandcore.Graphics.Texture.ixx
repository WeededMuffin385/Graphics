module;
#include "Sandcore.Graphics.OpenGL.hpp"
export module Sandcore.Graphics.Texture;

export namespace Sandcore {
	class Texture {
	public:
		virtual ~Texture() {
			glDeleteTextures(1, &texture);
		}

		virtual void create() = 0;

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
		template<GLenum Type>
		void allocate() {
			glDeleteTextures(1, &texture);
			glCreateTextures(Type, 1, &texture);
		}

		GLuint unit = -1;
		GLuint texture = -1;
	};
}