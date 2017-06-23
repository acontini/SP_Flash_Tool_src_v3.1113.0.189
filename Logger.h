/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2009
*
*****************************************************************************/

#ifndef _LOGGER_H
#define _LOGGER_H

#include <iostream>

class LoggerImpl;

class Logger {
    public:
	enum Level {
		Verbose = 0,
		Debug,
		Info,  //default for console mode
		Warn,
		Error,
		Off
        };

	void SetBaseLevel(Level baselevel);
	void AddLogHandle(const std::string& fileName, Logger::Level level);
	void AddLogHandle(std::ostream* stdStream, Logger::Level level);
	void RemoveAllLogHandle();

	std::string ContextInfo() const; //get time,logger name, pid, tid
	void Log(Level level,const char *pattern, ...);

	Logger& operator<<(Level curlevel);

	Logger& operator<< (bool val );
	Logger& operator<< (short val );
	Logger& operator<< (unsigned short val );
	Logger& operator<< (int val );
	Logger& operator<< (unsigned int val );
	Logger& operator<< (long val );
	Logger& operator<< (unsigned long val );
	Logger& operator<< (unsigned long long val);
	Logger& operator<< (float val );
	Logger& operator<< (double val );
	Logger& operator<< (long double val );
	Logger& operator<< (const void* val );
	Logger& operator<< (char val);
	Logger& operator<< (const char* val);
	Logger& operator<< (const wchar_t* val);
	Logger& operator<< (std::streambuf* sb );
	Logger& operator<< (const std::string& sb );

	Logger& operator<<(std::ostream& (*pf)(std::ostream&));
	Logger& operator<< (std::ios& ( *pf )(std::ios&));
	Logger& operator<<(std::ios_base& (*pf)(std::ios_base&));

        ~Logger();
private:
	LoggerImpl *pimpl;
	Logger(const std::string& loggerName, Level baseLevel = Warn);
	std::string DumpFileWithTimeStamp(void) const;

	std::string sp_flash_tool_log_path;
	std::string dump_files_path;

public:
	static Logger& GetLogger();	
	static void DebugOn();
	static void DebugOff();
	static void SetSPFlashToolLogFolder();
	static std::string GetSPFlashToolLogFolder();
	static void SetSPFlashToolDumpFileFolder();
	static std::string GetSPFlashToolDumpFileFolder();
};

class LogFunc{
public:
	LogFunc(const Logger::Level level = Logger::Verbose,
			const char * file = NULL,
			const char* func_name = NULL,
			int line = 0):
		m_level(level),
		m_file(file),
		m_func_name(func_name),
		m_line(line)
	{}
	void operator ()(const char * format,...);
private:
	Logger::Level m_level;
	const char * m_file;
	const char* m_func_name;
	int m_line;
};

#define LOG (LogFunc(Logger::Debug, __FILE__, NULL, __LINE__))
#define LOGV (LogFunc(Logger::Verbose, __FILE__, __FUNC__, __LINE__))
#define LOGD (LogFunc(Logger::Debug, __FILE__, __FUNC__, __LINE__))
#define LOGI (LogFunc(Logger::Info, __FILE__, __FUNC__, __LINE__))
#define LOGW (LogFunc(Logger::Warn, __FILE__, __FUNC__, __LINE__))
#define LOGE (LogFunc(Logger::Error, __FILE__, __FUNC__, __LINE__))

std::string DumpHex(unsigned long long val);

#endif // _LOGGER_H
