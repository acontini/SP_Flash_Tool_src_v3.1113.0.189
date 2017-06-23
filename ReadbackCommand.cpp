#include "ReadbackCommand.h"

#include "Logger.h"

SCIReadbackCommand::SCIReadbackCommand(FLASHTOOL_API_HANDLE_T ft_handle)
:ft_handle_(ft_handle)
{

}

SCIReadbackCommand::~SCIReadbackCommand()
{}

int SCIReadbackCommand::Execute()
{
  LOG("%s: Readback Command Execute!", __FUNC__);
  int ret = S_DONE;

  FlashTool_Readback_Arg rb_arg;
  FlashTool_Readback_Result rb_result;

  memset(&rb_arg, 0, sizeof(rb_arg));
  memset(&rb_result, 0, sizeof(rb_result));

  rb_arg = readback_arg_.GetBromReadbackArg();

  ret = FlashTool_Readback(ft_handle_, &rb_arg, &rb_result);
  if(ret != S_DONE)
  {
         LOGE("%s: Readback fail, ret(%d)", __FUNC__, ret);
  }

  return ret;
}



