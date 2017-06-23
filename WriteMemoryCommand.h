#ifndef WRITEMEMORY_COMMAND_H_
#define WRITEMEMORY_COMMAND_H_

#include "Command.h"
#include "flashtool_api.h"
#include "WriteMemoryArg.h"

class WriteMemoryCommand:public Command
{
public:
	explicit WriteMemoryCommand(FLASHTOOL_API_HANDLE_T ft_handle);
	~WriteMemoryCommand();

	WriteMemoryArg GetWriteMemoryArg(void) const {return this->writememory_arg_;}

	virtual int Execute();

private:
	friend class WriteMemorySetting;
	WriteMemoryArg writememory_arg_;
	FLASHTOOL_API_HANDLE_T ft_handle_;
};

#endif

