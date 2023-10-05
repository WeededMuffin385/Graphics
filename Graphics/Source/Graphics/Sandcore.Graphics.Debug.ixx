module;
#include "Sandcore.Graphics.OpenGL.hpp"
export module Sandcore.Graphics.Debug;

import std;

export namespace Sandcore::Graphics {
	const bool debug = false;

	const char* get_source_string(GLenum source) {
		switch (source) {
			case GL_DEBUG_SOURCE_API:
				return "API";
			case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
				return "Window System";
			case GL_DEBUG_SOURCE_SHADER_COMPILER:
				return "Shader Compiler";
			case GL_DEBUG_SOURCE_THIRD_PARTY:
				return "Third Party";
			case GL_DEBUG_SOURCE_APPLICATION:
				return "Application";
			case GL_DEBUG_SOURCE_OTHER:
				return "Other";
			default:
				return "Unknown";
		}
	}

	const char* get_type_string(GLenum type) {
		switch (type) {
			case GL_DEBUG_TYPE_ERROR:
				return "Error";
			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
				return "Deprecated Behavior";
			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
				return "Undefined Behavior";
			case GL_DEBUG_TYPE_PORTABILITY:
				return "Portability";
			case GL_DEBUG_TYPE_PERFORMANCE:
				return "Performance";
			case GL_DEBUG_TYPE_MARKER:
				return "Marker";
			case GL_DEBUG_TYPE_PUSH_GROUP:
				return "Push Group";
			case GL_DEBUG_TYPE_POP_GROUP:
				return "Pop Group";
			case GL_DEBUG_TYPE_OTHER:
				return "Other";
			default:
				return "Unknown";
		}
	}

	const char* get_severity_string(GLenum severity) {
		switch (severity) {
			case GL_DEBUG_SEVERITY_HIGH:
				return "High";
			case GL_DEBUG_SEVERITY_MEDIUM:
				return "Medium";
			case GL_DEBUG_SEVERITY_LOW:
				return "Low";
			case GL_DEBUG_SEVERITY_NOTIFICATION:
				return "Notification";
			default:
				return "Unknown";
		}
	}

	void GLAPIENTRY MessageCallback(
		GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam) {
		std::print("[OpenGL Debug] Source: {} | Type: {} | Severity: {} | Message: {}\n", get_source_string(source), get_type_string(type), get_severity_string(severity), message);
		if (severity == GL_DEBUG_SEVERITY_HIGH) throw std::exception("OpenGL error");
	}

	void debugInit() {
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(MessageCallback, 0);
	}
}