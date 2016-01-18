#pragma once
#include <stdio.h>

namespace apanoo {
	class Log
	{
	protected:
		Log()
		{
			Init("Log.txt");
		}
		Log(const Log &)
		{}
		Log & operator= (const Log &)
		{}

	public:
		// ����
		static Log * Instance()
		{
			// Instance of log class
			static Log instance;
			return &instance;
		}

		bool Init(char * newFilename);

		// ����հ���
		void OutputNewLine();

		// ���һ������
		void OutputSuccess(char * text, ...);
		void OutputError(char * text, ...);
		void OutputMisc(char * text, ...);

		// ��ȡ���һ��error��Ϣ
		const char * GetErrorString();

		// ���error��Ϣ
		void ClearErrorString();

	protected:
		char * m_Filename;
		FILE * m_LogFile;

		char m_ErrorString[512];
	};
}