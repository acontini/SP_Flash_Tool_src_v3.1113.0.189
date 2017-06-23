/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2011
*
*****************************************************************************/

#include <assert.h>

#include "NandAutoFormatArg.h"
#include "Logger.h"
#include "NandLayoutParameter.h"
#include "PlatformInfo.h"
#include "GlobalData.h"

#ifdef __BORLANDC__
#pragma warn -8004
#endif

const string kNvramBin("NVRAM");
//FixedNandAutoFormatArg implement Begin 
FixedNandAutoFormatArg::FixedNandAutoFormatArg(
		const NandAutoFormat_E auto_fmt_flag,
		const DA_REPORT_T* da_report,
		const DL_HANDLE_T dl_handle) :
		auto_fmt_flag_(auto_fmt_flag),
		da_report_(da_report),
		dl_handle_(dl_handle)
{
}

void FixedNandAutoFormatArg::CalcFormatAllArg()
{
	assert(da_report_->m_nand_flash_size > 0 && "Nand flash size is NOT correct!");
	this->set_format_start_address(0);
	this->set_format_length(da_report_->m_nand_flash_size);
	this->set_nand_addr_type(NUTL_ADDR_PHYSICAL);
	LOG("%s(): format start address(0x%I64x), length(0x%I64x), type(%s).",
			__FUNC__,
			this->format_start_address(),
			this->format_length(),
			AddrTypeFlagToString(this->nand_addr_type()));
}

void FixedNandAutoFormatArg::CalcFormatPartialArg()
{
	assert(da_report_->m_nand_flash_size > 0 && "Nand flash size is NOT correct!");
        PartitionInfo part_info;
        memset(&part_info, 0, sizeof(PartitionInfo));
        NandLayoutParameter nand_para(dl_handle_, NULL);
        if(!nand_para.QueryPartitionInfobyName(kNvramBin, &part_info)) {
    	    LOG("ERROR: %s(): query %s in layout table failed!",
    			__FUNC__, kNvramBin);
    	    assert(0 && "Could not find layout table!");
    	    return;
        } 
	unsigned long long length_from_nvram = da_report_->m_nand_flash_size -
			part_info.start_addr;
	this->set_format_start_address(part_info.start_addr);
	this->set_format_length(length_from_nvram);
	this->set_nand_addr_type(NUTL_ADDR_PHYSICAL);
	LOG("%s(): format start address(0x%I64x), length(0x%I64x), type(%s).",
			__FUNC__,
			this->format_start_address(),
			this->format_length(),
			AddrTypeFlagToString(this->nand_addr_type()));
}

void FixedNandAutoFormatArg::UpdateFormatArg()
{
	switch (auto_fmt_flag_){
	case FORMAT_ALL:
		CalcFormatAllArg();
		break;
	case FORMAT_ALL_EXP_BL:
		CalcFormatPartialArg();
		break;
	default:
		CalcFormatPartialArg();
		break;
	}
}

inline unsigned long long FixedNandAutoFormatArg::GetAutoFormatStartAddress(void)
{
	UpdateFormatArg();
	return this->format_start_address();
}

inline unsigned long long FixedNandAutoFormatArg::GetAutoFormatLength(void)
{
	UpdateFormatArg();
	return this->format_length();
}

inline NUTL_AddrTypeFlag_E FixedNandAutoFormatArg::GetNandAddrType(void)
{
	UpdateFormatArg();
	return this->nand_addr_type();
}
//FixedNandAutoFormatArg implement End

//DynamicNandAutoFormatArg implement Begin
DynamicNandAutoFormatArg::DynamicNandAutoFormatArg(
		const NandAutoFormat_E auto_fmt_flag,
		const DA_REPORT_T* da_report,
		const NUTL_AddrTypeFlag_E oper_flag,
		const DL_HANDLE_T dl_handle,
		const FLASHTOOL_API_HANDLE_T flashtool_handle) :
		auto_fmt_flag_(auto_fmt_flag),
		da_report_(da_report),
		oper_flag_(oper_flag),
		dl_handle_(dl_handle),
		flashtool_handle_(flashtool_handle)

{
}

bool DynamicNandAutoFormatArg::CalcDynamicFormatAllArg(void)
{
	assert(da_report_->m_nand_flash_size > 0 && "Nand flash size is NOT correct!");
	if (NUTL_ADDR_PHYSICAL == oper_flag_) {
    	this->set_format_start_address(0);
    	this->set_format_length(da_report_->m_nand_flash_size);
    	this->set_nand_addr_type(NUTL_ADDR_PHYSICAL);
    } else if (NUTL_ADDR_LOGICAL == oper_flag_) {
    	unsigned long long length_without_pmt_after = da_report_->m_nand_flash_size -
    			(g_platform_info.getNandReservedBlocks() *
    			da_report_->m_nand_pagesize *
    			da_report_->m_nand_pages_per_block);
        this->set_format_start_address(0);
        this->set_format_length(length_without_pmt_after);
        this->set_nand_addr_type(NUTL_ADDR_LOGICAL);
    }
	LOG("%s(): format start address(0x%I64x), length(0x%I64x), type(%s).",
			__FUNC__,
			this->format_start_address(),
			this->format_length(),
			AddrTypeFlagToString(this->nand_addr_type()));
	return true;
}

bool DynamicNandAutoFormatArg::CalcDynamicFormatPartialArg(void)
{
	PartitionInfo part_info;
	memset(&part_info, 0, sizeof(PartitionInfo));
	NandLayoutParameter nand_para(dl_handle_, flashtool_handle_);
    if(!nand_para.QueryPartitionInfobyName(kNvramBin, &part_info)) {
    	LOG("ERROR: %s(): query %s in layout table failed!",
    			__FUNC__, kNvramBin);
    	assert(0 && "Could not find layout table!");
    	return false;
    } else {
    	unsigned long long start_addr_from_nvram = part_info.start_addr;
    	unsigned long long length_from_nvram_before_pmt = da_report_->m_nand_flash_size -
    			start_addr_from_nvram -
    			(g_platform_info.getNandReservedBlocks() *
    			da_report_->m_nand_pagesize *
    			da_report_->m_nand_pages_per_block);
        this->set_format_start_address(start_addr_from_nvram);
        this->set_format_length(length_from_nvram_before_pmt);
    }

	if (NUTL_ADDR_PHYSICAL == oper_flag_) {
    	this->set_nand_addr_type(NUTL_ADDR_PHYSICAL);
    } else if (NUTL_ADDR_LOGICAL == oper_flag_) {
        this->set_nand_addr_type(NUTL_ADDR_LOGICAL);
    }
	LOG("%s(): format start address(0x%I64x), length(0x%I64x), type(%s).",
			__FUNC__,
			this->format_start_address(),
			this->format_length(),
			AddrTypeFlagToString(this->nand_addr_type()));
	return true;
}

bool DynamicNandAutoFormatArg::UpdateDynamicFormatArg(void)
{
	bool is_success = false;
	switch (auto_fmt_flag_){
	case FORMAT_ALL:
		is_success = CalcDynamicFormatAllArg();
		break;
	case FORMAT_ALL_EXP_BL:
		is_success = CalcDynamicFormatPartialArg();
		break;
	default:
		is_success = CalcDynamicFormatPartialArg();
		break;
	}
	return is_success;
}

inline unsigned long long DynamicNandAutoFormatArg::GetAutoFormatStartAddress(void)
{
	UpdateDynamicFormatArg();
	return this->format_start_address();
}

inline unsigned long long DynamicNandAutoFormatArg::GetAutoFormatLength(void)
{
	UpdateDynamicFormatArg();
	return this->format_length();
}

inline NUTL_AddrTypeFlag_E DynamicNandAutoFormatArg::GetNandAddrType(void)
{
	UpdateDynamicFormatArg();
	return this->nand_addr_type();
}
//DynamicNandAutoFormatArg implement End
