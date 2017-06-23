/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2009
*
*****************************************************************************/

#include "Command.h"


Command::Command()
{
}

Command::~Command()
{
}

MacroCommand::MacroCommand()
    : m_Commands()
{
}

MacroCommand::~MacroCommand()
{
}

void MacroCommand::Add(const SharedPtr<Command> &command)
{
    m_Commands.push_back(command);
}

void MacroCommand::Remove(const SharedPtr<Command> &command)
{
    m_Commands.remove(command);
}

void MacroCommand::AddPreCommand(const SharedPtr<Command> &precommand)
{
    m_preCommands.push_back(precommand);
}

void MacroCommand::RemovePreCommand(const SharedPtr<Command> &precommand)
{
    m_preCommands.remove(precommand);
}

void MacroCommand::AddOperCommand(const SharedPtr<Command> &opercommand)
{
    m_operCommands.push_back(opercommand);
}

void MacroCommand::RemoveOperCommand(const SharedPtr<Command> &opercommand)
{
    m_operCommands.remove(opercommand);
}

int MacroCommand::Execute()
{
    Commands::const_iterator it;
    int ret = true;

    //Execute pre command first
    for (it=m_preCommands.begin(); it!=m_preCommands.end(); ++it)
    {
        if (!((*it)->Execute()))
        {
            ret = false;
        }
    }

    for (it=m_Commands.begin(); it!=m_Commands.end(); ++it)
    {
        if (!((*it)->Execute()))
        {
            ret = false;
        }
    }

    for (it=m_operCommands.begin(); it!=m_operCommands.end(); ++it)
    {
         ret = (*it)->Execute();
         if(ret)
         {
             return ret;
         }
    }
    return ret;
}
