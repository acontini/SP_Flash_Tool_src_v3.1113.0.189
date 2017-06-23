#include "WriteMemoryCommand.h"

#include "flashtool_api.h"
#include "Logger.h"

WriteMemoryCommand::WriteMemoryCommand(FLASHTOOL_API_HANDLE_T ft_handle)
:ft_handle_(ft_handle)
{}

WriteMemoryCommand::~WriteMemoryCommand()
{}

int WriteMemoryCommand::Execute()
{
  LOG("executing write memory..., partition(%s)", writememory_arg_.GetBromWriteMemoryArg().m_input);
 
  int ret = S_DONE;
   
  WriteFlashMemoryParameter  wm_arg;
  memset(&wm_arg, 0, sizeof(wm_arg));

  wm_arg = writememory_arg_.GetBromWriteMemoryArg();

  ret = FlashTool_WriteFlashMemory(ft_handle_, &wm_arg);
  if(S_DONE != ret)
  {
       LOGE("%s: WriteMemory fail, ret(%d).", __FUNC__, ret);
  }

  return ret;
}




