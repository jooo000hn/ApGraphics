#include "Texture.h"
#include "../../utils/FileUtils.h"

namespace apanoo {

	Texture::Texture(GLenum target, const std::string& filename)
		: m_TextureTarget(target), m_FileName(filename)
	{
		load();
	}

	bool Texture::load()
	{
		// ø™∆ÙŒ∆¿Ì
		glEnable(GL_TEXTURE_2D);

		// …Í«ÎŒ∆¿ÌID
		glGenTextures(1, &m_TextureID);

		// ∂¡»°Õº∆¨
		BYTE* pixels = FileUtils::readImage(m_FileName.c_str(), &m_Width, &m_Height, &m_Bits);
		if (pixels == nullptr)
		{
			std::cout << "failed load texture: " << m_FileName.c_str()<< std::endl;
			Log::Instance()->OutputError("failed load texture: %s", m_FileName.c_str());
			return false;
		}

		// work out what format to tell glTexImage2D to use...
		if (getBPP() == 24) {	   // RGB 24bit
			m_Mode = GL_RGB;
		}
		else if (getBPP() == 32) { // RGBA 32bit
			m_Mode = GL_RGBA;
		}
		else {
			std::cout << "failed load texture: unsport image bits! file: " << m_FileName.c_str() << std::endl;
			Log::Instance()->OutputError("failed load texture: unsport image bits! file: %s", m_FileName.c_str());
			delete[] pixels;
			return false;
		}

		glBindTexture(m_TextureTarget, m_TextureID);
		glTexImage2D(m_TextureTarget, 0, m_Mode, getWidth(), getHeight(), 0, m_Mode == GL_RGB ? GL_BGR : GL_BGRA, GL_UNSIGNED_BYTE, pixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 

		glBindTexture(m_TextureTarget, 0);
		delete[] pixels;

		std::cout << "load texture success: " << m_FileName.c_str() << std::endl;
		Log::Instance()->OutputSuccess("load texture success: %s", m_FileName.c_str());

		return true;
	}

	void Texture::bind(GLenum textureUnit)
	{
		glActiveTexture(textureUnit);
		glBindTexture(m_TextureTarget, m_TextureID);
	}
}