
#ifndef REGION_FORMAT_COMMAND_H_
#define REGION_FORMAT_COMMAND_H_

#include "RegionFormatArg.h"
#include "command.h"

class RegionFormatCommand : public Command
{
public:
	RegionFormatCommand(FLASHTOOL_API_HANDLE_T ft_handle);
	virtual ~RegionFormatCommand();

	RegionFormatArg GetRegionFormatArg(void) const{return this->region_format_arg_;}

	virtual int Execute();
   
private:
	friend class RegionFormatSetting;
	RegionFormatArg region_format_arg_;
	FLASHTOOL_API_HANDLE_T ft_handle_;

};
#endif



