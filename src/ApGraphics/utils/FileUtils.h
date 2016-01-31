#ifndef __FILEUTILS_H__
#define __FILEUTILS_H__

#ifndef _IOSTREAM_
	#include <iostream>
#endif // !_IOSTREAM_

#ifndef _FSTREAM_
	#include <fstream>
#endif // !_FSTREAM_

#include "freeimage.h"
#include "../log/Log.h"

namespace apanoo {
	// ��ȡshader�ļ�
	class FileUtils
	{
	public:
		static std::string readShader(const char* filename)
		{
			FILE * file = fopen(filename, "rt");
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

		static BYTE* readImage(const char* filename, GLsizei* width, GLsizei* height, int* bits)
		{
			// ͼƬ��ʽ
			FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;

			// ָ��ͼƬ��ָ��
			FIBITMAP *dib = nullptr;

			// ���ͼƬ��ʽ
			fif = FreeImage_GetFileType(filename, 0);

			// ����ʽλ�ã���������չ��ʽ�в²�
			if (fif == FIF_UNKNOWN)
			{
				fif = FreeImage_GetFIFFromFilename(filename);
			}

			// �����Ȼδ֪��ʽ�����ؿ�
			if (fif == FIF_UNKNOWN)
			{
				std::cout << "error read image!unknow image type : " << filename << std::endl;
				Log::Instance()->OutputSuccess("error read image!unknow image type : %s", filename);
				return nullptr;
			}

			// ����Ƿ�֧�ּ��ش˸�ʽ
			if (FreeImage_FIFSupportsReading(fif))
			{
				dib = FreeImage_Load(fif, filename);
			}

			// ���ܼ����򷵻ؿ�
			if (!dib)
			{
				std::cout << "error read image!unsupport image type : " << filename << std::endl;
				Log::Instance()->OutputSuccess("error read image!unsupport image type : %s", filename);
				return nullptr;
			}

			// ��ȡ����
			BYTE* pixels = FreeImage_GetBits(dib);

			// ��ȡͼƬ���
			*width = FreeImage_GetWidth(dib);
			*height = FreeImage_GetHeight(dib);

			// ��ȡͼƬλ��
			*bits = FreeImage_GetBPP(dib);

			int size = (*width) * (*height) * (*bits / 8);
			BYTE* result = new BYTE[size];
			memcpy(result, pixels, size); // copy ��Դ
			FreeImage_Unload(dib);		  // �ͷ���Դ
			return result;
		}
	};
}
#endif // ! __FILEUTILS_H__
