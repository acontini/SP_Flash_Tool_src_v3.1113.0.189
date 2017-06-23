#include "RegionFormatCommand.h"

#include "Flashtool_api.h"
#include "Logger.h"
#include "RegionFormatSetting.h"

RegionFormatCommand::RegionFormatCommand(FLASHTOOL_API_HANDLE_T ft_handle):
ft_handle_(ft_handle)
{}

RegionFormatCommand::~RegionFormatCommand()
{}

int RegionFormatCommand::Execute()
{
      int ret = S_DONE;
      FlashTool_Format_Arg       fmt_arg;	 
      FlashTool_Format_Result    fmt_res;

      memset( &fmt_arg,    0, sizeof(fmt_arg));
      memset( &fmt_res, 0, sizeof(fmt_res));   

      fmt_arg = this->region_format_arg_.getRegionArg().format_arg;

      ret = FlashTool_Format(ft_handle_, &fmt_arg, &fmt_res);
      if(S_DONE != ret) {
        LOG("%s(): FlashTool_Format fail.", __FUNC__);
    }
    return ret;
}




