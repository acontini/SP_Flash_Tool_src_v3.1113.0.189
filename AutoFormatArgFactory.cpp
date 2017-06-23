/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2011
*
*****************************************************************************/

#include "AutoFormatArgFactory.h"
#include "NandAutoFormatArg.h"
#include "EMMCAutoFormatArg.h"
#include "SDMMCAutoFormatArg.h"
#include "Logger.h"
#include "flashtool.h"

//SharedPtr<AutoFormatArg> AutoFormatArgFactory::CreateAutoFormatArg(const StorageLayoutType_E type,
//		const AutoFormatArgFactory& auto_fmt_factory)
//{
//	if ( FIXED_NAND == type) {
//		return SharedPtr<AutoFormatArg>(new FixedNandAutoFormatArg(auto_fmt_factory.auto_fmt_flag_, auto_fmt_factory.da_report_));
//	} else if ( DYNAMIC_NAND == type){
//		return SharedPtr<AutoFormatArg>(new DynamicNandAutoFormatArg(
//				auto_fmt_factory.auto_fmt_flag_,
//				auto_fmt_factory.da_report_,
//				auto_fmt_factory.oper_flag_,
//				auto_fmt_factory.dl_handle_,
//				auto_fmt_factory.flashtool_handle_));
//	} else {
//		assert(0 && "Un-support type!");
//		return SharedPtr<AutoFormatArg>(new DynamicNandAutoFormatArg(
//				auto_fmt_factory.auto_fmt_flag_,
//				auto_fmt_factory.da_report_,
//				auto_fmt_factory.oper_flag_,
//				auto_fmt_factory.dl_handle_,
//				auto_fmt_factory.flashtool_handle_));
//	}
//}

SharedPtr<AutoFormatArg> AutoFormatArgFactory::CreateAutoFormatArg(const StorageLayoutType_E type)
{
	Dump();
	if ( FIXED_NAND == type) {
		return SharedPtr<AutoFormatArg>(new FixedNandAutoFormatArg(this->auto_fmt_flag_, this->da_report_, this->dl_handle_));
	} else if ( DYNAMIC_NAND == type){
		return SharedPtr<AutoFormatArg>(new DynamicNandAutoFormatArg(
				this->auto_fmt_flag_,
				this->da_report_,
				this->oper_flag_,
				this->dl_handle_,
				this->flashtool_handle_));
	} else if ( EMMC == type) {
		return SharedPtr<AutoFormatArg>(new EMMCAutoFormatArg(
			this->auto_fmt_flag_,
			this->da_report_,
			this->dl_handle_,
			this->flashtool_handle_));
	} else if ( SDMMC == type) {
		return SharedPtr<AutoFormatArg>(new SDMMCAutoFormatArg(
			this->auto_fmt_flag_,
			this->da_report_,
			this->dl_handle_,
			this->flashtool_handle_));
	} else {
		assert(0 && "Un-support type!");
		return SharedPtr<AutoFormatArg>(new DynamicNandAutoFormatArg(
				this->auto_fmt_flag_,
				this->da_report_,
				this->oper_flag_,
				this->dl_handle_,
				this->flashtool_handle_));
	}
}

void AutoFormatArgFactory::Dump(void)
{
	LOG("%s(): auto_fmt_flag(%d), da_report_->m_nand_flash_size(0x%x).",
			__FUNC__, this->auto_fmt_flag_, this->da_report_->m_nand_flash_size);
	LOG("%s(): oper_flag_(%s), dl_handle_(0x%x), flashtool_handle_(0x%x)",
			__FUNC__,
			AddrTypeFlagToString(this->oper_flag_),
			this->dl_handle_,this->flashtool_handle_);
}
