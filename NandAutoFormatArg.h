/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2011
*
*****************************************************************************/

#ifndef NANDAUTOFORMATARG_H_
#define NANDAUTOFORMATARG_H_

#include <string>
#include "AutoFormatArg.h"
#include "FlashToolTypedefs.h"

struct DL_HANDLE;
typedef struct DL_HANDLE *  DL_HANDLE_T;
struct FLASHTOOL_API_HANDLE;
typedef struct FLASHTOOL_API_HANDLE *   FLASHTOOL_API_HANDLE_T;

//FixedNandAutoFormatArg declaration Begin
class FixedNandAutoFormatArg : public AutoFormatArg
{
public:
	explicit FixedNandAutoFormatArg(
        const NandAutoFormat_E auto_fmt_flag = FORMAT_ALL_EXP_BL,
        const DA_REPORT_T* da_report = NULL,
	const DL_HANDLE_T dl_handle = NULL);
	virtual ~FixedNandAutoFormatArg() {}

	virtual unsigned long long GetAutoFormatStartAddress(void);
	virtual unsigned long long GetAutoFormatLength(void);
	virtual NUTL_AddrTypeFlag_E GetNandAddrType(void);

private:
	void CalcFormatAllArg(void);
	void CalcFormatNvramArg(void);
	void CalcFormatPartialArg(void);
	void UpdateFormatArg(void);

private:
	NandAutoFormat_E auto_fmt_flag_;
	const DA_REPORT_T* da_report_;
        DL_HANDLE_T dl_handle_;
};
//FixedNandAutoFormatArg declaration End

//DynamicNandAutoFormatArg declaration Begin
class DynamicNandAutoFormatArg : public AutoFormatArg
{
public:
	explicit DynamicNandAutoFormatArg(
			const NandAutoFormat_E auto_fmt_flag = FORMAT_ALL_EXP_BL,
			const DA_REPORT_T* da_report = NULL,
			const NUTL_AddrTypeFlag_E oper_flag = NUTL_ADDR_LOGICAL,
			const DL_HANDLE_T dl_handle = NULL,
			const FLASHTOOL_API_HANDLE_T flashtool_handle = NULL);
	virtual ~DynamicNandAutoFormatArg() {}

	virtual unsigned long long GetAutoFormatStartAddress(void);
	virtual unsigned long long GetAutoFormatLength(void);
	virtual NUTL_AddrTypeFlag_E GetNandAddrType(void);

private:
	bool CalcDynamicFormatAllArg(void);
	bool CalcDynamicFormatNvramArg(void);
	bool CalcDynamicFormatPartialArg(void);
	bool UpdateDynamicFormatArg(void);

private:
	NandAutoFormat_E auto_fmt_flag_;
	const DA_REPORT_T* da_report_;
	NUTL_AddrTypeFlag_E oper_flag_;
	DL_HANDLE_T dl_handle_;
	FLASHTOOL_API_HANDLE_T flashtool_handle_;
};
//DynamicNandAutoFormatArg declaration End

#endif /* NANDAUTOFORMATARG_H_ */
