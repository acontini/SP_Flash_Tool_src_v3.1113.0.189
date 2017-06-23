/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2009
*
*****************************************************************************/

#ifndef _UTILITY_H
#define _UTILITY_H

#include <SyncObjs.hpp>
#include <string>
#include <iostream>
#include <sstream>
#include <set>
#include <setupapi.h>
#include <time.h>

#include "flashtool.h"
#include "eboot\interface.h"
#include "download.h"

#include "NandLayoutParameter.h"

//#define    PID_PRELOADER    "2000"
//#define    VID_PRELOADER    "0E8D"

//#define    PID_BOOTROM    "0003"
//#define    VID_BOOTROM    "0E8D"

//Gadget
//#define PID_GADGET "0005&MI_02"
//#define VID_GADGET "0BB4"

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  TypeName& operator=(const TypeName&)

#define ENUM_TO_CASE_STRING(case_id)\
	case case_id:\
		return #case_id

template<typename T>
std::string NumberToString(T number) {   //Usage: NumberToString ( Number );
	std::ostringstream ss;
	ss << number;
	return ss.str();
}

template<typename T>
std::wstring NumberToWString(T number) {
	std::wostringstream wss;
	wss << number;
	return wss.str();
}

template<typename T>
T StringToNumber(const std::string &text) {  //Usage: StringToNumber<Type> ( String );
	std::istringstream ss(text);
	T result;
	return ss >> result ? result : 0;
}

template<typename T>
T WStringToNumber(const std::wstring &text) {
	std::wistringstream wss(text);
	T result;
	return wss >> result ? result : 0;
}

//template<typename T> //T could be string or char*
std::string ToUppercaseString(const std::string& str);
std::string ToLowercaseString(const std::string& str);
std::string WStr2Str(const std::wstring& ws);
std::wstring Str2WStr(const std::string& s);

bool SearchNewlyCreatedCOMPort(unsigned short &comPortNum);

DWORD GetParentProcessId();

bool IsNewScatterFileWithBoundaryCheck(DL_HANDLE_T pDLHandle);

void ScanExistUSBVComPort( std::set<std::string>  &exist_symbollic_str,
                           std::set<std::string> &exist_port_str,
                           const std::string& PID,
                           const std::string& VID);

void FillAndroidImageRegionInfo( DL_HANDLE_T pDLHandle, 
                                 REGION_INFO_E* region_info, 
                                 unsigned int &region_num);

bool GetNewCreatedUSBVComPort( std::string &usb_symbolic_str,
		                       std::string &usb_port_str,
                               std::set<std::string> &exist_com_port_str,
                               const std::string& PID,
                               const std::string& VID);

bool ScanNewCreateUSBVComPortWithTimeout( unsigned int time_out,
                               unsigned short& com_num,
                               const std::string& PID,
                               const std::string& VID);
//Search USB port for downloading DA
bool ScanUSBPort4DownloadDA(int* stop_flag,
							std::string& symbolic_name,
							std::string& friendly_name,
							const bool with_timeout = false, 
							const unsigned int timeout = 30); 

bool ScanUSBPortByCOMNum(int* stop_flag, 
	                                                 unsigned char com_num, 
	                                                 unsigned int time_out = 30);

//Switch Brom Full Speed to DA High Speed
bool Swith2DAHighSpeed(int* stop_flag,
					   std::string& symbolic_name,
					   std::string& friendly_name,
					   FLASHTOOL_API_HANDLE_T flashtool_handle,
					   const bool with_timeout = false,
					   const unsigned int timeout = 30);

bool ScanUSBPort4DownloadCert(int* stop_flag,
							std::string& symbolic_name,
							std::string& friendly_name,
							const bool with_timeout=false, 
							const unsigned int timeout=30);

unsigned char GetUSBVCOMNumByPortName(const std::string& usb_port);

bool IsDigitChar(const char character);

bool IsImgsToBeDLWithPath(DL_HANDLE_T pDLHandle, std::string &errHint);

bool IsNullImgsToBeDL(DL_HANDLE_T pDLHandle);

bool IsAllImgsToBeDL(DL_HANDLE_T pDLHandle);

bool IsNecessaryImgsToBeDL(DL_HANDLE_T pDLHandle);

bool IsBLToBeDL(DL_HANDLE_T pDLHandle);

bool IsSecurityToBeDL(SCERT_HANDLE_T  scert_handle);

bool IsCertToBeDL(AUTH_HANDLE_T  auth_handle);

bool IsFoundDLImageByScatterFile(DL_HANDLE_T p_dl_handle, 
				   ROM_INFO *p_rom_info,
				   const std::string &rom_name);

void FillChecksumArg(RomMemChecksumArg &arg, RomMemChecksumResult &res);
bool VerifyDLImagesBuffer(DL_HANDLE_T dl_handle, std::string& error_msg, RomMemChecksumArg &chksum_arg, RomMemChecksumResult &chksum_res);

class CS_Sentry
{
public:
	CS_Sentry(TCriticalSection  *cs):m_cs(cs) { m_cs->Acquire(); }
	~CS_Sentry() { m_cs->Release(); }

private:
	TCriticalSection	*m_cs;
};

void CheckSingleInstanceOfFlashTool(bool isConsole);

void GetRomRegionByName(DL_HANDLE_T pDLHandle,
		const std::string &rom_name,
		U64 &begin_addr,
		U64 &length);

void GetRomInfoByName(DL_HANDLE_T pDLHandle,		 
		                   const std::string &rom_name,
		                   PartitionExistStatus &parti_status);

bool CheckIfRSVByAddr(U64 addr);

//void GetBMTFormatInfo(DL_HANDLE_T pDLHandle, U64 &begin_addr);
#endif // _UTILITY_H
