#pragma once
#include "gl/glew.h"
#include <string>

namespace apanoo {
	class Texture
	{
	public:
		Texture(const char* filename);

		void bind();

		inline const unsigned int getID() const { return m_ID; }
		inline const unsigned int getWidth() { return m_Width; }
		inline const unsigned int getHeight() { return m_Height; }
		
	private:
		void init(const char* filename);

	private:
		GLuint m_ID;

		int m_Height;
		int m_Width;
	};
}
