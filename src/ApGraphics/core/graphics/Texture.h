#pragma once
#ifndef _IOSTREAM_
	#include <iostream>
#endif // !_IOSTREAM_

#include "gl/glew.h"

namespace apanoo {
	class Texture
	{
	public:
		Texture(GLenum target, const std::string& filename);

		void bind(GLenum TextureUnit = 0);

		inline GLsizei const getWidth() const { return m_Width; }
		inline GLsizei const getHeight() const { return m_Height; }
		inline int const getBPP() const { return m_Bits; }
		inline std::string const getPath() const { return m_FileName; }
		inline GLuint const getTextureID() const { return m_TextureID; }

	private:
		bool load();

	private:
		int m_Width, m_Height, m_Bits;  // ¿í£¬ ¸ß£¬ Î»Êý
		GLenum m_TextureTarget;			
		GLuint m_TextureID;			
		std::string m_FileName;
		int m_Mode;						// (GL_RGB / GL_RGBA)
	};
}