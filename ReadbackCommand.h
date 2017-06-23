#ifndef READBACK_COMMAND_H_
#define READBACK_COMMAND_H_

#include "Command.h"
#include "flashtool_api.h"
#include "SCIReadbackArg.h"
class SCIReadbackCommand:public Command
{
public:
	SCIReadbackCommand(FLASHTOOL_API_HANDLE_T ft_handle);
	virtual ~SCIReadbackCommand();

	SCIReadbackArg GetReadbackArg(void) const {return this->readback_arg_;}

	virtual int Execute();

private:
	friend class SCIReadbackSetting;
	FLASHTOOL_API_HANDLE_T ft_handle_;
	SCIReadbackArg readback_arg_;
};

#endif

