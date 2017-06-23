/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2011
*
*****************************************************************************/

#include "AutoFormatArg.h"

AutoFormatArg::AutoFormatArg():
format_start_address_(0),
format_length_(0),
nand_addr_type_(NUTL_ADDR_LOGICAL)
{
}

AutoFormatArg::AutoFormatArg(const AutoFormatArg& ref)
{
	this->format_start_address_ = ref.format_start_address_;
	this->format_length_ = ref.format_length_;
}

AutoFormatArg& AutoFormatArg::operator =(const AutoFormatArg& ref)
{
    if (&ref != this) {
    	this->format_start_address_ = ref.format_start_address_;
    	this->format_length_ = ref.format_length_;
    }
    return *this;
}

AutoFormatArg::~AutoFormatArg() {
}
