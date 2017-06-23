/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2011
*
*****************************************************************************/

#ifndef AUTOFORMATARG_H_
#define AUTOFORMATARG_H_

#include "DOWNLOAD.h"

class AutoFormatArg
{
public:
	AutoFormatArg();
	AutoFormatArg(const AutoFormatArg& ref);
	AutoFormatArg& operator = (const AutoFormatArg& ref);
	virtual ~AutoFormatArg();

	virtual unsigned long long GetAutoFormatStartAddress(void) = 0;
	virtual unsigned long long GetAutoFormatLength(void) = 0;
	//For Nand interface ONLY, other storage type, please dummy implement
	virtual NUTL_AddrTypeFlag_E GetNandAddrType(void) = 0;

protected:
	unsigned long long format_start_address(void) const {
		return format_start_address_;
	}

	unsigned long long format_length(void) const {
		return format_length_;
	}

	void set_format_start_address(unsigned long long  start_addr) {
		this->format_start_address_ = start_addr;
	}

	void set_format_length(unsigned long long length) {
		this->format_length_ = length;
	}

	NUTL_AddrTypeFlag_E nand_addr_type(void) const {
		return nand_addr_type_;
	}

	void set_nand_addr_type(NUTL_AddrTypeFlag_E type) {
		this->nand_addr_type_ = type;
	}

private:
	unsigned long long format_start_address_;
	unsigned long long format_length_;
	NUTL_AddrTypeFlag_E nand_addr_type_;
};

#endif /* AUTOFORMATARG_H_ */
