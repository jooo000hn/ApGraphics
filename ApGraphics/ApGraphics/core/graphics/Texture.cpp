#include "Texture.h"
#include "../../utils/ResourcesLoader.h"

namespace apanoo {

	Texture::Texture(const char* filename)
	{
		init(filename);
	}


	void Texture::bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}

	void Texture::init(const char* filename)
	{
		BYTE* pixels = ResourcesLoader::load_image(filename, &m_Width, &m_Height);

		GLuint result;
		glGenTextures(1, &result); // ��������ID
		glBindTexture(GL_TEXTURE_2D, result);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// ��������
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);

		glBindTexture(GL_TEXTURE_2D, 0);

		// �ͷ���Դ
		delete[] pixels;

		m_ID = result;
	}
}