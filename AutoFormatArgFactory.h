/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2011
*
*****************************************************************************/

#ifndef AUTOFORMATARGFACTORY_H_
#define AUTOFORMATARGFACTORY_H_

#include <string>
#include <stdexcept>

#include "SharedPtr.h"
#include "AutoFormatArg.h"
#include "FlashToolTypedefs.h"
#include "NonCopyable.h"

class AutoFormatArgFactory : private NonCopyable
{
public:
	AutoFormatArgFactory():
		auto_fmt_flag_(FORMAT_ALL_EXP_BL),
		da_report_(NULL),
		oper_flag_(NUTL_ADDR_LOGICAL),
		dl_handle_(NULL),
		flashtool_handle_(NULL)
	{}

	~AutoFormatArgFactory() {}
	/*Attention Begin, All setters need to be settled!!!*/
	void set_auto_fmt_flag(const NandAutoFormat_E auto_fmt_flag) {
		this->auto_fmt_flag_ = auto_fmt_flag;
	}

	void set_da_report(const DA_REPORT_T* da_report) {
		this->da_report_ = da_report;
	}

	void set_oper_flag(const NUTL_AddrTypeFlag_E oper_flag) {
		this->oper_flag_ = oper_flag;
	}

	void set_dl_handle(const DL_HANDLE_T dl_handle) {
		this->dl_handle_ = dl_handle;
	}

	void set_flashtool_handle(const FLASHTOOL_API_HANDLE_T flashtool_handle) {
		this->flashtool_handle_ = flashtool_handle;
	}
	/*Attention End*/

	//static SharedPtr<AutoFormatArg> CreateAutoFormatArg(const StorageLayoutType_E type, const AutoFormatArgFactory& auto_fmt_factory);
	SharedPtr<AutoFormatArg> CreateAutoFormatArg(const StorageLayoutType_E type);
private:
	void Dump(void);
private:
	//Nand auto format input parameters
	NandAutoFormat_E auto_fmt_flag_;
	const DA_REPORT_T* da_report_;
	NUTL_AddrTypeFlag_E oper_flag_;
	DL_HANDLE_T dl_handle_;
	FLASHTOOL_API_HANDLE_T flashtool_handle_;
};

#endif /* AUTOFORMATARGFACTORY_H_ */
