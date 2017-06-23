/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2009
*
*****************************************************************************/

#include <fstream>
#include <vector>
#include <string>
#include <cstdio>
#include <cassert>
#include <stdarg.h>
#include <windows.h>
#include <shlobj.h>

#include "Logger.h"
#include "version.h"
#include "FileUtils.h"
#pragma warn -8004

using namespace std;

class LoggerImpl {
public:
	LoggerImpl(const string& loggerName, Logger::Level baseLevel,
			Logger::Level curLevel);
	~LoggerImpl();

	void AddLogHandle(const string& fileName, Logger::Level level);
	void AddLogHandle(ostream* stdStream, Logger::Level level);
	void RemoveAllLogHandle();

	void SetCurrentLevel(Logger::Level level) {
		m_CurLevel = level;
}
	void SetBaseLevel(Logger::Level level) {
		m_BaseLevel = level;
	}
	bool Suppressed() const {
		return (m_CurLevel < m_BaseLevel);
	}
	string ContextInfo() const;
	string GetTimestamp() const;

	template<typename T>
	void Put(T obj);

	static string GetLevelString(Logger::Level level);

private:
	struct LogHandle {
		string FileName;
		Logger::Level HandleLevel;
		ostream* OutStream;
	};

	string m_LoggerName;
	Logger::Level m_CurLevel;
	Logger::Level m_BaseLevel;

	vector<LogHandle> m_LogHandles;
};

string LoggerImpl::GetLevelString(Logger::Level level) {
	switch (level) {
	case Logger::Verbose:
		return "VERBOSE";
	case Logger::Debug:
		return "DEBUG";
	case Logger::Info:
		return "INFO";
	case Logger::Warn:
		return "WARN";
	case Logger::Error:
		return "ERROR";
	case Logger::Off:
		return "OFF";
	default:
		return "UNKNOWN";
}
}

LoggerImpl::LoggerImpl(const string &loggerName, Logger::Level baseLevel,
		Logger::Level curLevel) :
	m_LoggerName(loggerName), m_BaseLevel(baseLevel), m_CurLevel(curLevel) {
}

LoggerImpl::~LoggerImpl() {
	RemoveAllLogHandle();
    }

string LoggerImpl::ContextInfo() const {
	char infoBuffer[256] = { 0 };
	DWORD pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();
	SYSTEMTIME timestamp;
	GetLocalTime(&timestamp);
	sprintf(infoBuffer,
			"%02d/%02d/%02d %02d:%02d:%02d.%03d %s[%lu][%lu][%s]: ",
			timestamp.wMonth, timestamp.wDay, timestamp.wYear, timestamp.wHour,
			timestamp.wMinute, timestamp.wSecond, timestamp.wMilliseconds,
			m_LoggerName.c_str(), pid, tid, GetLevelString(m_CurLevel).c_str());
	return string(infoBuffer);
}

string LoggerImpl::GetTimestamp() const {
	char infoTimestamp[_MAX_FNAME] = { 0 };
	SYSTEMTIME timestamp;
	GetLocalTime(&timestamp);
	sprintf(infoTimestamp,
			"%02d-%02d-%02d-%02d-%02d-%02d",
			timestamp.wMonth, timestamp.wDay, timestamp.wYear, timestamp.wHour,
			timestamp.wMinute, timestamp.wSecond);
	return string(infoTimestamp);
}

void LoggerImpl::AddLogHandle(const string& fileName, Logger::Level level) {
	assert(fileName != "");
	ofstream *fs = new ofstream(fileName.c_str(), std::ios_base::out
			| std::ios_base::app);
	if (fs != NULL && fs->is_open()) {
		LogHandle handle;
		handle.FileName = fileName;
		handle.HandleLevel = level;
		handle.OutStream = fs;
		m_LogHandles.push_back(handle);
    }
}

void LoggerImpl::AddLogHandle(ostream* stdStream, Logger::Level level) {
	assert(stdStream != NULL);
	LogHandle handle;
	handle.FileName = "";
	handle.HandleLevel = level;
	handle.OutStream = stdStream;
	m_LogHandles.push_back(handle);
}

void LoggerImpl::RemoveAllLogHandle() {
	for (vector<LogHandle>::const_iterator it = m_LogHandles.begin(); it
			!= m_LogHandles.end(); ++it) {
		if (it->FileName != "" && it->OutStream) {
			delete it->OutStream;
		}
	}
	m_LogHandles.clear();
}

template<typename T>
void LoggerImpl::Put(T obj) {
	if (!Suppressed()) {
		for (vector<LogHandle>::const_iterator it = m_LogHandles.begin(); it
				!= m_LogHandles.end(); ++it) {
			if (m_CurLevel >= it->HandleLevel) {
				if (it->OutStream) {
					*(it->OutStream) << obj;
					it->OutStream->flush();
				}
			}
		}
	}
}


//Logger
Logger::Logger(const string& loggerName, Level baseLevel) {
	pimpl = new LoggerImpl(loggerName, baseLevel, Logger::Verbose);
}

Logger::~Logger() {
	if (pimpl){
		pimpl->Put("\nLogger deinited.");
		delete pimpl;
	}
}

string Logger::ContextInfo() const {
	return pimpl->ContextInfo();
}

Logger& Logger::operator<<(Level level) {
	pimpl->SetCurrentLevel(level);
    return *this;
}

void Logger::SetBaseLevel(Logger::Level level) {
	pimpl->SetBaseLevel(level);
}

void Logger::AddLogHandle(const string& fileName, Logger::Level level) {
	pimpl->AddLogHandle(fileName, level);
}

void Logger::AddLogHandle(ostream* stdStream, Logger::Level level) {
	pimpl->AddLogHandle(stdStream, level);
}

void Logger::RemoveAllLogHandle() {
	pimpl->RemoveAllLogHandle();
}

void Logger::Log(Level level, const char *pattern, ...) {
	char buffer[2048];
	va_list params;
	va_start(params, pattern);
	vsnprintf(buffer, 2048, pattern, params);
	va_end(params);
	*this << level;
	*this << ContextInfo();
	*this << buffer << std::endl;
}

Logger& Logger::operator<<(ostream& (*pf)(ostream&)) {
	pimpl->Put(pf);
    return *this;
}
Logger& Logger::operator<<(ios_base& (*pf)(ios_base&)) {
	pimpl->Put(pf);
	return *this;
}
Logger& Logger::operator<<(ios& (*pf)(ios&)) {
	pimpl->Put(pf);
	return *this;
}
Logger& Logger::operator<<(bool val) {
	pimpl->Put(val);
	return *this;
}
Logger& Logger::operator<<(short val) {
	pimpl->Put(val);
	return *this;
}
Logger& Logger::operator<<(unsigned short val) {
	pimpl->Put(val);
	return *this;
}
Logger& Logger::operator<<(int val) {
	pimpl->Put(val);
	return *this;
}
Logger& Logger::operator<<(unsigned int val) {
	pimpl->Put(val);
	return *this;
}
Logger& Logger::operator<<(long val) {
	pimpl->Put(val);
	return *this;
}
Logger& Logger::operator<<(unsigned long val) {
	pimpl->Put(val);
	return *this;
}

Logger& Logger::operator<<(unsigned long long val){
      pimpl->Put(val);
	return *this;
}

Logger& Logger::operator<<(float val) {
	pimpl->Put(val);
	return *this;
}
Logger& Logger::operator<<(double val) {
	pimpl->Put(val);
	return *this;
}
Logger& Logger::operator<<(long double val) {
	pimpl->Put(val);
	return *this;
}
Logger& Logger::operator<<(const void* val) {
	pimpl->Put(val);
	return *this;
}
Logger& Logger::operator<<(streambuf* sb) {
	pimpl->Put(sb);
	return *this;
}
Logger& Logger::operator<<(const string& sb) {
	pimpl->Put(sb);
	return *this;
}
Logger& Logger::operator<<(char val) {
	pimpl->Put(val);
	return *this;
}
Logger& Logger::operator<<(const char* val) {
	pimpl->Put(val);
	return *this;
}
Logger& Logger::operator <<(const wchar_t* val) {
    pimpl->Put(val);
	return *this;
}

string DumpHex(unsigned long long val) {
	char buf[16] = { 0 };
	//sprintf(buf, "0x%08X", val);
	sprintf(buf, "0x%016I64X", val);
	return string(buf);
}

Logger& Logger::GetLogger(){
	static Logger mLogger("FlashTool");
	return mLogger;
}

void Logger::SetSPFlashToolLogFolder() {
    char szUserPath[MAX_PATH];
	if ( SHGetSpecialFolderPath(NULL, szUserPath, CSIDL_COMMON_APPDATA, 0) ) {
		GetLogger().sp_flash_tool_log_path = std::string(szUserPath) + "\\SP_FT_Logs";
	} else {
	    GetLogger().sp_flash_tool_log_path = FileUtils::GetAppDirectory() + "\\SP_FT_Logs";
	}

	if ( CREATE_DIR_FAIL == FileUtils::CheckDirectory(GetLogger().sp_flash_tool_log_path, true) ) {
	    assert( 0 && "To create SP Flash Tool logs path fails!");
	}
}

std::string Logger::GetSPFlashToolLogFolder() {
	return GetLogger().sp_flash_tool_log_path;
}

std::string Logger::DumpFileWithTimeStamp() const {
	return ( std::string("\\SP_FT_Dump_") + GetLogger().pimpl->GetTimestamp() );
}

void Logger::SetSPFlashToolDumpFileFolder() {
	GetLogger().SetSPFlashToolLogFolder();
	GetLogger().dump_files_path = GetLogger().sp_flash_tool_log_path + GetLogger().DumpFileWithTimeStamp();			
	if ( CREATE_DIR_FAIL == FileUtils::CheckDirectory(GetLogger().dump_files_path, true) ) {
	    assert( 0 && "To create SP Flash Tool logs dump path fails!");   
	}
}
std::string Logger::GetSPFlashToolDumpFileFolder() {
	return GetLogger().dump_files_path;
}

void Logger::DebugOn() {
	Logger::GetLogger().SetBaseLevel(Logger::Verbose);
	Logger::GetLogger().AddLogHandle(&cout, Logger::Info);
	Logger::GetLogger().AddLogHandle((GetLogger().dump_files_path+"\\SP_FLASH_TOOL.log"), Logger::Verbose);
	Logger::GetLogger() << Logger::Verbose<<std::endl;

       Logger::GetLogger() << ToolInfo::ToString() << std::endl;
}

void Logger::DebugOff() {
	Logger::GetLogger()<<Logger::Debug<<
			"================================================================="
			"================================================================="
			<<std::endl<<"Smart Phone Flash Tool runtime trace is OFF"<<std::endl<<
			"================================================================="
			"================================================================="
			<<std::endl;
	Logger::GetLogger().SetBaseLevel(Logger::Off);
	Logger::GetLogger().RemoveAllLogHandle();
}


void LogFunc::operator ()(const char * format,...)
{
	va_list params;
	static char msg[1024];

	va_start( params, format );
	_vsnprintf( msg, 1020, format, params );
	va_end( params );

	std::string func_name;
	if (NULL == m_func_name) {
		func_name = "";
	} else {
		func_name = std::string(m_func_name) + "(): ";
	}
	Logger::GetLogger()<<m_level;
	Logger::GetLogger()<<Logger::GetLogger().ContextInfo()
			<<func_name.c_str()
			<<msg
			<<"("<<m_file<<","<<m_line<<")"<<std::endl;
}
