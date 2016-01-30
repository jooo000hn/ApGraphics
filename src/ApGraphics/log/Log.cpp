#include <stdarg.h>
#include <string.h>
#include "Log.h"
namespace apanoo {
	// Initiate
	bool Log::Init(char * newFilename)
	{
		// �ļ������
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

		// �������ļ������������
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

	// ����հ׺�
	void Log::OutputNewLine()
	{
		// Open
		m_LogFile = fopen(m_Filename, "a+");
		if (!m_LogFile)
		{
			return;
		}

		// ����հ׺�
		putc('\n', m_LogFile);

		// close
		fclose(m_LogFile);
		m_LogFile = NULL;
	}

	// ���һ�гɹ���Ϣ
	void Log::OutputSuccess(char * text, ...)
	{
		// ��ȡ�������
		va_list argList;
		va_start(argList, text);

		// Open 
		m_LogFile = fopen(m_Filename, "a+");
		if (!m_LogFile)
		{
			return;
		}

		// ����ɹ���Ϣ
		fprintf(m_LogFile, "<-> ");
		vfprintf(m_LogFile, text, argList);
		putc('\n', m_LogFile);

		// close 
		fclose(m_LogFile);
		m_LogFile = NULL;
		va_end(argList);
	}

	// ���һ�д�����Ϣ
	void Log::OutputError(char * text, ...)
	{
		// ��ȡ�������
		va_list argList;
		va_start(argList, text);

		// Open 
		m_LogFile = fopen(m_Filename, "a+");
		if (!m_LogFile)
		{
			return;
		}

		// ���������Ϣ
		fprintf(m_LogFile, "<!> ");
		vfprintf(m_LogFile, text, argList);
		putc('\n', m_LogFile);

		// close 
		fclose(m_LogFile);
		m_LogFile = NULL;

		// �������´���
		vsprintf(m_ErrorString, text, argList);

		va_end(argList);
	}

	// ���һ��������Ϣ
	void Log::OutputMisc(char * text, ...)
	{
		// ��ȡ�������
		va_list argList;
		va_start(argList, text);

		// Open
		m_LogFile = fopen(m_Filename, "a+");
		if (!m_LogFile)
		{
			return;
		}

		// ���������Ϣ
		fprintf(m_LogFile, "<#> ");
		vfprintf(m_LogFile, text, argList);
		putc('\n', m_LogFile);

		// close 
		fclose(m_LogFile);
		m_LogFile = NULL;
		va_end(argList);
	}



	// ��ȡ����error��Ϣ
	const char * Log::GetErrorString()
	{
		return (const char *)m_ErrorString;
	}

	// ������error��Ϣ
	void Log::ClearErrorString()
	{
		memset(m_ErrorString, 0, 512);
	}
}