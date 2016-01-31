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
	// 读取shader文件
	class FileUtils
	{
	public:
		static std::string readShader(const char* filename)
		{
			FILE * file = fopen(filename, "rt");
			fseek(file, 0, SEEK_END);
			unsigned long length = ftell(file);  // 计算文件长度

			char* data = new char[length + 1];   // 分配内存

			memset(data, 0, length + 1);         // 清零
			fseek(file, 0, SEEK_SET);			 // 回到文件头
			fread(data, 1, length, file);		 // 读取文件内容

			fclose(file);
			std::string result(data);

			delete[] data;
			return result;
		}

		static BYTE* readImage(const char* filename, GLsizei* width, GLsizei* height, int* bits)
		{
			// 图片格式
			FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;

			// 指向图片的指针
			FIBITMAP *dib = nullptr;

			// 检查图片格式
			fif = FreeImage_GetFileType(filename, 0);

			// 若格式位置，尝试在扩展格式中猜测
			if (fif == FIF_UNKNOWN)
			{
				fif = FreeImage_GetFIFFromFilename(filename);
			}

			// 如果仍然未知格式，返回空
			if (fif == FIF_UNKNOWN)
			{
				std::cout << "error read image!unknow image type : " << filename << std::endl;
				Log::Instance()->OutputSuccess("error read image!unknow image type : %s", filename);
				return nullptr;
			}

			// 检测是否支持加载此格式
			if (FreeImage_FIFSupportsReading(fif))
			{
				dib = FreeImage_Load(fif, filename);
			}

			// 不能加载则返回空
			if (!dib)
			{
				std::cout << "error read image!unsupport image type : " << filename << std::endl;
				Log::Instance()->OutputSuccess("error read image!unsupport image type : %s", filename);
				return nullptr;
			}

			// 获取数据
			BYTE* pixels = FreeImage_GetBits(dib);

			// 获取图片宽高
			*width = FreeImage_GetWidth(dib);
			*height = FreeImage_GetHeight(dib);

			// 获取图片位数
			*bits = FreeImage_GetBPP(dib);

			int size = (*width) * (*height) * (*bits / 8);
			BYTE* result = new BYTE[size];
			memcpy(result, pixels, size); // copy 资源
			FreeImage_Unload(dib);		  // 释放资源
			return result;
		}
	};
}
#endif // ! __FILEUTILS_H__
