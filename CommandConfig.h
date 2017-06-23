#ifndef COMMAND_CONFIG_H_
#define COMMAND_CONFIG_H_

#include "flashtool_api.h"
#include "Command.h" 
#include "MacroSetting.h"

#include <vector>

class Command;
class CommandConfig
{
public:
	CommandConfig();
	~CommandConfig();

	void AddCommandSetting(const MacroSetting &setting);
        SharedPtr<Command> CreateCommand(FLASHTOOL_API_HANDLE_T ft_handle) const;
private:
	 typedef std::vector<SharedPtr<MacroSetting> > CommandSettings;
        CommandSettings m_CommandSettings;
 
};
#endif

