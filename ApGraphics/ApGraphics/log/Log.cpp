#include <stdarg.h>
#include <string.h>
#include "Log.h"
namespace apanoo {
	// Initiate
	bool Log::Init(char * newFilename)
	{
		// 文件名清空
		if (m_Filename)
		{
			delete[] m_Filename;
		}

		m_Filename = new char[strlen(newFilename)];
		if (!m_Filename)
		{
			return false;
		}

		strcpy(m_Filename, newFilename);

		// 创建新文件，不输出内容
		m_LogFile = fopen(m_Filename, "wb");
		if (!m_LogFile)
		{
			return false;
		}

		// Close
		fclose(m_LogFile);
		m_LogFile = NULL;

		return true;
	}

	// 输出空白航
	void Log::OutputNewLine()
	{
		// Open
		m_LogFile = fopen(m_Filename, "a+");
		if (!m_LogFile)
		{
			return;
		}

		// 输出空白航
		putc('\n', m_LogFile);

		// close
		fclose(m_LogFile);
		m_LogFile = NULL;
	}

	// 输出一行成功信息
	void Log::OutputSuccess(char * text, ...)
	{
		// 获取输出内容
		va_list argList;
		va_start(argList, text);

		// Open 
		m_LogFile = fopen(m_Filename, "a+");
		if (!m_LogFile)
		{
			return;
		}

		// 输出成功信息
		fprintf(m_LogFile, "<-> ");
		vfprintf(m_LogFile, text, argList);
		putc('\n', m_LogFile);

		// close 
		fclose(m_LogFile);
		m_LogFile = NULL;
		va_end(argList);
	}

	// 输出一行错误信息
	void Log::OutputError(char * text, ...)
	{
		// 获取输出内容
		va_list argList;
		va_start(argList, text);

		// Open 
		m_LogFile = fopen(m_Filename, "a+");
		if (!m_LogFile)
		{
			return;
		}

		// 输出错误信息
		fprintf(m_LogFile, "<!> ");
		vfprintf(m_LogFile, text, argList);
		putc('\n', m_LogFile);

		// close 
		fclose(m_LogFile);
		m_LogFile = NULL;

		// 保存最新错误
		vsprintf(m_ErrorString, text, argList);

		va_end(argList);
	}

	// 输出一行杂项信息
	void Log::OutputMisc(char * text, ...)
	{
		// 获取输出内容
		va_list argList;
		va_start(argList, text);

		// Open
		m_LogFile = fopen(m_Filename, "a+");
		if (!m_LogFile)
		{
			return;
		}

		// 输出杂项信息
		fprintf(m_LogFile, "<#> ");
		vfprintf(m_LogFile, text, argList);
		putc('\n', m_LogFile);

		// close 
		fclose(m_LogFile);
		m_LogFile = NULL;
		va_end(argList);
	}



	// 获取最新error信息
	const char * Log::GetErrorString()
	{
		return (const char *)m_ErrorString;
	}

	// 清空最近error信息
	void Log::ClearErrorString()
	{
		memset(m_ErrorString, 0, 512);
	}
}