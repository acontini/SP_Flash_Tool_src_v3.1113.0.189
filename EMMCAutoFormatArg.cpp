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

#include "EMMCAutoFormatArg.h"
#include "Logger.h"
#include "PlatformInfo.h"
#include "GlobalData.h"
#include "NandLayoutParameter.h"

#ifdef __BORLANDC__
#pragma warn -8004
#endif

const string kNvramBin("NVRAM");
const string kFATBin("__NODL_FAT");

//EMMCAutoFormatArg implement Begin 
EMMCAutoFormatArg::EMMCAutoFormatArg(
		const NandAutoFormat_E auto_fmt_flag,
		const DA_REPORT_T* da_report,
		const DL_HANDLE_T dl_handle,
		const FLASHTOOL_API_HANDLE_T flashtool_handle) :
        auto_fmt_flag_(auto_fmt_flag),
		da_report_(da_report),
		dl_handle_(dl_handle),
		flashtool_handle_(flashtool_handle),
		format_all_length_(0)
{
        CalcFormatAllLength(da_report_);
}

void EMMCAutoFormatArg::CalcFormatAllArg()
{
	assert(da_report_->m_emmc_ua_size > 0 && "Nand flash size is NOT correct!");
	this->set_format_start_address(0);
	
	this->set_format_length(this->format_all_length_);	
	this->UpdateFormatLen();
	//this->set_format_length(da_report_->m_emmc_ua_size);
	
	LOG("%s(): format start address(0x%I64x), length(0x%I64x).",
			__FUNC__,
			this->format_start_address(),
			this->format_length());
}
void EMMCAutoFormatArg::CalcFormatPartialArg()
{
	assert(da_report_->m_emmc_ua_size > 0 && "Nand flash size is NOT correct!");
	PartitionInfo nvram_part_info;
	memset(&nvram_part_info, 0, sizeof(PartitionInfo));
	PartitionInfo fat_part_info;
	memset(&fat_part_info, 0, sizeof(PartitionInfo));

	NandLayoutParameter nand_para(dl_handle_, flashtool_handle_);
	if(!nand_para.QueryPartitionInfobyName(kNvramBin, &nvram_part_info)) {
		LOGE("Query %s in layout table failed!", kNvramBin.c_str());
		assert(0 && "Could not find layout table!");
		return;
	} 

       unsigned long long length_from_nvram(0);

	length_from_nvram = this->format_all_length_ - nvram_part_info.start_addr;	                                                               ;

	this->set_format_start_address(nvram_part_info.start_addr);
	this->set_format_length(length_from_nvram);	

	this->UpdateFormatLen();
	
	LOGD("format start address(0x%I64x), length(0x%I64x).",
		this->format_start_address(),
		this->format_length());
}

void EMMCAutoFormatArg::UpdateFormatArg()
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

inline unsigned long long EMMCAutoFormatArg::GetAutoFormatStartAddress(void)
{
	UpdateFormatArg();
	return this->format_start_address();
}

inline unsigned long long EMMCAutoFormatArg::GetAutoFormatLength(void)
{
	UpdateFormatArg();
	return this->format_length();
}

inline NUTL_AddrTypeFlag_E EMMCAutoFormatArg::GetNandAddrType(void)
{
	//Dummy implement
	LOGD("EMMC dummy implement NUTL_AddrTypeFlag_E(NUTL_ADDR_LOGICAL)");
	return NUTL_ADDR_LOGICAL;
}

//Block align is necessary for EMMC format
void EMMCAutoFormatArg::UpdateFormatLen(void)
{
          unsigned long long length(0);

	   length = this-> format_length();
	   LOGD("checking format length(0x%I64x).", length);
	   if(0 != (length % 512))
	   {
               length = (length/512 - 1) * 512;	  
	        LOGD("format length is not 512 align, and has been change to length(0x%I64x).", length);
	   }

	   this->set_format_length(length);
	   LOGD("format start address(0x%I64x), length(0x%I64x).",
		this->format_start_address(),
		this->format_length());
}

void  EMMCAutoFormatArg::CalcFormatAllLength(const DA_REPORT_T* da_report)
{
      this->format_all_length_ = da_report->m_emmc_boot1_size + 
	  	da_report->m_emmc_boot2_size + da_report->m_emmc_ua_size + da_report->m_emmc_rpmb_size + 
	  	da_report->m_emmc_gp1_size + da_report->m_emmc_gp2_size + da_report->m_emmc_gp3_size + 
	  	da_report->m_emmc_gp4_size;

}
	
//EMMCAutoFormatArg implement End
