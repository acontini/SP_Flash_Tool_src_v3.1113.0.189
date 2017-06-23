#include "RegionFormatArg.h"

#include "RegionFormatCommand.h"
#include "Utility.h"
#include "Logger.h"

RegionFormatArg::RegionFormatArg()
{}

RegionFormatArg::~RegionFormatArg()
{}

void RegionFormatArg::Dump()
{
       LOG("%s(): format start address(0x%I64x), format length(0x%I64x).", __FUNC__, 
	   	      this->sregion_format_arg_.format_arg.m_format_cfg.m_format_begin_addr,
	   	       this->sregion_format_arg_.format_arg.m_format_cfg.m_format_length);
}


