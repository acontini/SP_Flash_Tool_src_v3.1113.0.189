/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2011
*
*****************************************************************************/
#include "OperationIndicator.h"
#include "Logger.h"

using std::string;
using std::map;

#define ENUM_TO_CASE_STRING(case_id)\
	case case_id:\
		return #case_id

OperationIndicator::OperationIndicator(void) :
is_da_dl_all_(false),
is_da_high_speed_(false),
is_da_dl_without_bat_(false),
is_da_dl_auto_detect_bat_(false),
da_dl_type_(DA_DL_ALL_FULL_SPEED_WITH_BAT),
nvram_op_(NVRAM_NO_ACTION)
{
	InitDADLHintMap();
	InitNvramOperationHintMap();
}

OperationIndicator::OperationIndicator(const bool is_da_dl_all,
				   const bool is_da_high_speed,
				   const bool is_da_dl_without_bat,
				   const bool is_da_dl_auto_detect_bat,
				   const NvramOperation nvram_op) :
is_da_dl_all_(is_da_dl_all),
is_da_high_speed_(is_da_high_speed),
is_da_dl_without_bat_(is_da_dl_without_bat),
is_da_dl_auto_detect_bat_(is_da_dl_auto_detect_bat),
da_dl_type_(DA_DL_ALL_FULL_SPEED_WITH_BAT),
nvram_op_(nvram_op)
{
	InitDADLHintMap();
	InitNvramOperationHintMap();
}

OperationIndicator::~OperationIndicator(void)
{
}

void OperationIndicator::InitDADLHintMap()
{
	//Full with Bat 00, Full w/o Bat 01, High with Bat 10, High w/o Bat 11
	this->da_dl_hint_[DA_DL_ALL_FULL_SPEED_WITH_BAT] = 
		"DA DL All With Battery (Full Speed)";
	this->da_dl_hint_[DA_DL_ALL_FULL_SPEED_WITHOUT_BAT] = 
		"DA DL All Without Battery (Full Speed)";
	this->da_dl_hint_[DA_DL_ALL_HIGH_SPEED_WITH_BAT] = 
		"DA DL All With Battery (High Speed)";
	this->da_dl_hint_[DA_DL_ALL_HIGH_SPEED_WITHOUT_BAT] = 
		"DA DL All Without Battery (High Speed)";
	this->da_dl_hint_[DA_DL_ALL_FULL_SPEED_AUTO_DETECT_BAT] = 
		"DA DL All (Bat. Auto Detection) (Full Speed)";
	this->da_dl_hint_[DA_DL_ALL_HIGH_SPEED_AUTO_DETECT_BAT] = 
		"DA DL All (Bat. Auto Detection) (High Speed)";
}

void OperationIndicator::InitNvramOperationHintMap()
{
	this->nvram_op_hint_[NVRAM_FOUR_IN_ONE] =
		"Download->Upload Nvram";
	this->nvram_op_hint_[NVRAM_FOUR_IN_ONE_WITH_FORMAT] = 
		"Format->Download->Upload Nvram";
	this->nvram_op_hint_[NVRAM_FIRMWARE_UPGRADE] =
		"Backup Nvram->Format All->Download->Restore Nvram";
}

string OperationIndicator::GetDADLHint()
{
	if ( this->is_da_dl_all_ ) {
		return QueryDADLHint(da_dl_type_);
	} else {
		return string("");
	}
}

string OperationIndicator::QueryDADLHint(const DADLType da_dl_type) 
{
	map<DADLType, string>::const_iterator it = da_dl_hint_.find(da_dl_type);
	if ( it != da_dl_hint_.end() ) {
		LOG("%s(): da_dl_type(%s), da_dl_hint(%s)",
			__FUNC__,
			DADLTypeToString(da_dl_type).c_str(),
			it->second);
		return it->second;
	} else {
		LOG("ERROR: %s(): da_dl_type(%s) error, could not find DA download hint!", 
			__FUNC__,
			DADLTypeToString(da_dl_type).c_str());
		return string("");
	}
}

string OperationIndicator::QueryNvramOperationHint(const NvramOperation nvram_op) 
{
	map<NvramOperation, string>::const_iterator it = nvram_op_hint_.find(nvram_op);
	if ( it != nvram_op_hint_.end() ) {
		LOG("%s(): nvram_op(%s), da_dl_hint(%s)",
			__FUNC__,
			NvramOperationToString(nvram_op).c_str(),
			it->second);
		return it->second;
	} else {
		LOG("%s(): nvram_op(%s) error, could not find Nvram operation hint!",
			__FUNC__,
			NvramOperationToString(nvram_op).c_str());
		return string("Unknown DL Type");
	}
}

void OperationIndicator::SetDADLAttr(const bool is_da_high_speed, const bool is_da_dl_without_bat, const bool is_da_dl_auto_detect_bat)
{
	unsigned short index = is_da_dl_auto_detect_bat ? 1 : 0;
	index = (index << 1) | (is_da_dl_without_bat ? 1 : 0);
	index = (index << 1) | (is_da_high_speed ? 1 : 0);
	this->da_dl_type_ = static_cast<DADLType>(index);
	LOGD("is_da_dl_all_(%s), is_da_high_speed(%s), is_da_dl_without_bat(%s), is_da_dl_auto_detect_bat(%s).",
		is_da_dl_all_ ? "true" : "false",
		is_da_high_speed ? "true" : "false",
		is_da_dl_auto_detect_bat ? "true" : "false",
		is_da_dl_without_bat ? "true" : "false");		
	LOGD("da_dl_index(%d), da_dl_hint_(%s).", da_dl_type_, GetDADLHint());
}

string OperationIndicator::NvramOperationToString(const NvramOperation nvram_op)
{
	switch ( nvram_op ) {
		ENUM_TO_CASE_STRING(NVRAM_NO_ACTION);
		ENUM_TO_CASE_STRING(NVRAM_FOUR_IN_ONE);
		ENUM_TO_CASE_STRING(NVRAM_FOUR_IN_ONE_WITH_FORMAT);
		ENUM_TO_CASE_STRING(NVRAM_FIRMWARE_UPGRADE);
		default:
			return string("??");
	}
}

string OperationIndicator::DADLTypeToString(const DADLType da_dl_type)
{
	switch ( da_dl_type ) {
		ENUM_TO_CASE_STRING(DA_DL_ALL_FULL_SPEED_WITH_BAT);
		ENUM_TO_CASE_STRING(DA_DL_ALL_FULL_SPEED_WITHOUT_BAT);
		ENUM_TO_CASE_STRING(DA_DL_ALL_HIGH_SPEED_WITH_BAT);
		ENUM_TO_CASE_STRING(DA_DL_ALL_HIGH_SPEED_WITHOUT_BAT);
		ENUM_TO_CASE_STRING(DA_DL_ALL_FULL_SPEED_AUTO_DETECT_BAT);
		ENUM_TO_CASE_STRING(DA_DL_ALL_HIGH_SPEED_AUTO_DETECT_BAT);
		default:
			return string("??");
	}
}

