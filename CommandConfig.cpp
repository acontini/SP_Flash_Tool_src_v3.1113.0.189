#include "CommandConfig.h"


CommandConfig::CommandConfig():
m_CommandSettings()
{}

CommandConfig::~CommandConfig()
{}

void CommandConfig::AddCommandSetting(const MacroSetting &setting)
{
     m_CommandSettings.push_back(SharedPtr<MacroSetting>(setting.Clone()));
}

SharedPtr<Command> CommandConfig::CreateCommand(FLASHTOOL_API_HANDLE_T ft_handle) const
{
     SharedPtr<MacroCommand> cmd(new MacroCommand());

     for(std::vector<SharedPtr<MacroSetting> >::const_iterator it = m_CommandSettings.begin();
	    it != m_CommandSettings.end(); ++it)
    {
          cmd->AddOperCommand((*it)->CreateCommand(ft_handle));
    }

    return cmd;
}


