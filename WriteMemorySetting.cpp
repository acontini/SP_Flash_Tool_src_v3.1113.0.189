#include "WriteMemorySetting.h"

#include "WriteMemoryCommand.h"
#include "Logger.h"

WriteMemorySetting::WriteMemorySetting():
    cb_write_flash_progress(NULL),
    addr_(0),
    addr_mode_(AddressingMode_LogicalAddress),
    container_len_(0),
    storage_type_(HW_STORAGE_EMMC),
    input_len_(0),
    input_mode_(InputMode_FromFile),
    prog_mode_(ProgramMode_PageOnly)
{
}

WriteMemorySetting::~WriteMemorySetting()
{}

void WriteMemorySetting::Dump() const
{
     LOG("WriteMemorySetting...");
}

MacroSetting * WriteMemorySetting::Clone() const
{
     return new  WriteMemorySetting(*this);
}

SharedPtr<Command> WriteMemorySetting::CreateCommand(FLASHTOOL_API_HANDLE_T ft_handle)const
{
    SharedPtr<WriteMemoryCommand> cmd(new WriteMemoryCommand(ft_handle));
    cmd->writememory_arg_.set_address(addr_);
    cmd->writememory_arg_.set_addressing_mode(addr_mode_);
    cmd->writememory_arg_.set_container_length(container_len_);
    cmd->writememory_arg_.set_flash_type(storage_type_);
    cmd->writememory_arg_.set_input(input_file_);
    cmd->writememory_arg_.set_input_length(input_len_);
    cmd->writememory_arg_.set_input_mode(input_mode_);
    cmd->writememory_arg_.set_program_mode(prog_mode_);
    cmd->writememory_arg_.set_cb_write_memory_progress_arg(this->cb_wm_progress_arg_);
    if(cb_write_flash_progress != NULL)
    {
       cmd->writememory_arg_.set_cb_write_memory_progress(cb_write_flash_progress);
    }

    return cmd;
}


