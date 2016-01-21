#ifndef __FILEUTILS_H__
#define __FILEUTILS_H__

#include <iostream>
#include <fstream>
#include "freeimage.h"

namespace apanoo {
	
	class ResourcesLoader
	{
	public:

		// ��ȡshader�ļ�
		static std::string load_shader(const char* filename)
		{
			std::string path = "./Resources/shaders/" + std::string(filename);
			FILE * file = fopen(path.c_str(), "rt");
			fseek(file, 0, SEEK_END);
			unsigned long length = ftell(file);  // �����ļ�����

			char* data = new char[length + 1];   // �����ڴ�

			memset(data, 0, length + 1);         // ����
			fseek(file, 0, SEEK_SET);			 // �ص��ļ�ͷ
			fread(data, 1, length, file);		 // ��ȡ�ļ�����

			fclose(file);
			std::string result(data);

			delete[] data;
			return result;
		}

		// ��ȡͼƬ
		static BYTE* load_image(const char* filename, GLsizei* width, GLsizei* height)
		{
			std::string path = "./Resources/textures/" + std::string(filename);

			// ͼƬ��ʽ
			FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;

			// ָ��ͼƬ��ָ��
			FIBITMAP *dib = nullptr;

			// ���ͼƬ��ʽ
			fif = FreeImage_GetFileType(path.c_str(), 0);

			// ����ʽλ�ã���������չ��ʽ�в²�
			if (fif == FIF_UNKNOWN)
			{
				fif = FreeImage_GetFIFFromFilename(path.c_str());
			}

			// �����Ȼδ֪��ʽ�����ؿ�
			if (fif == FIF_UNKNOWN)
				return nullptr;

			// ����Ƿ�֧�ּ��ش˸�ʽ
			if (FreeImage_FIFSupportsReading(fif))
			{
				dib = FreeImage_Load(fif, path.c_str());
			}

			// ���ܼ����򷵻ؿ�
			if (!dib)
			{
				return nullptr;
			}

			// ��ȡ����
			BYTE* pixels = FreeImage_GetBits(dib);

			// ��ȡͼƬ���
			*width = FreeImage_GetWidth(dib);
			*height = FreeImage_GetHeight(dib);
			int bits = FreeImage_GetBPP(dib);

			int size = (*width) * (*height) * (bits / 8);
			BYTE* result = new BYTE[size];
			memcpy(result, pixels, size); // copy ��Դ
			FreeImage_Unload(dib);		  // �ͷ���Դ
			return result;
		}
	};
}
#endif // 
