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
		// 单例
		static Log * Instance()
		{
			// Instance of log class
			static Log instance;
			return &instance;
		}

		bool Init(char * newFilename);

		// 输出空白行
		void OutputNewLine();

		// 输出一行文字
		void OutputSuccess(char * text, ...);
		void OutputError(char * text, ...);
		void OutputMisc(char * text, ...);

		// 获取最近一次error信息
		const char * GetErrorString();

		// 清除error信息
		void ClearErrorString();

	protected:
		char * m_Filename;
		FILE * m_LogFile;

		char m_ErrorString[512];
	};
}