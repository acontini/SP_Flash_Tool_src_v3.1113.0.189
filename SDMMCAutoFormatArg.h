/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2011
*
*****************************************************************************/

#ifndef SDMMCAUTOFORMATARG_H_
#define SDMMCAUTOFORMATARG_H_

#include <string>
#include "AutoFormatArg.h"
#include "FlashToolTypedefs.h"

struct DL_HANDLE;
typedef struct DL_HANDLE *  DL_HANDLE_T;
struct FLASHTOOL_API_HANDLE;
typedef struct FLASHTOOL_API_HANDLE *   FLASHTOOL_API_HANDLE_T;

//EMMCAutoFormatArg declaration Begin
class SDMMCAutoFormatArg : public AutoFormatArg
{
public:
	explicit SDMMCAutoFormatArg(
		const NandAutoFormat_E auto_fmt_flag = FORMAT_ALL_EXP_BL,
        const DA_REPORT_T* da_report = NULL,
	    const DL_HANDLE_T dl_handle = NULL,
	    const FLASHTOOL_API_HANDLE_T flashtool_handle = NULL);
	virtual ~SDMMCAutoFormatArg() {}

	virtual unsigned long long GetAutoFormatStartAddress(void);
	virtual unsigned long long GetAutoFormatLength(void);
	virtual NUTL_AddrTypeFlag_E GetNandAddrType(void);

private:
	void CalcFormatAllArg(void);
	void CalcFormatNvramArg(void);
	void CalcFormatPartialArg(void);
	void UpdateFormatArg(void);
	void UpdateFormatLen(void);

        void CalcFormatAllLength(const DA_REPORT_T* da_report);

private:
	NandAutoFormat_E auto_fmt_flag_;
	const DA_REPORT_T* da_report_;
       DL_HANDLE_T dl_handle_;
	  FLASHTOOL_API_HANDLE_T flashtool_handle_;
          unsigned long long format_all_length_;
};
//EMMCAutoFormatArg declaration End

#endif /* EMMCAUTOFORMATARG_H_ */

