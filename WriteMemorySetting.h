#ifndef WRITE_MEMORY_SETTING_H_
#define WRITE_MEMORY_SETTING_H_

#include "Command.h"
#include "SharedPtr.h"
#include "flashtool_api.h"
#include "MacroSetting.h"

class WriteMemorySetting:public MacroSetting
{
public:
	WriteMemorySetting();
	~WriteMemorySetting();

	virtual SharedPtr<Command> CreateCommand(FLASHTOOL_API_HANDLE_T ft_handle) const;
	virtual MacroSetting* Clone(void) const;
	virtual void Dump(void) const;

    void set_cb_write_memory_progress(const CALLBACK_WRITE_FLASH_PROGRESS cb)
    {
        cb_write_flash_progress = cb;
    }

    void set_cb_write_memory_progress_arg(void *usr_arg)
   {
        cb_wm_progress_arg_ = usr_arg;
   }

    void set_flash_type(const HW_StorageType_E storage_type)
    {
        this->storage_type_ = storage_type;
    }

    void set_addressing_mode(const AddressingMode addr_mode)
    {
        this->addr_mode_ = addr_mode;
    }

    void set_address(const U64 addr)
    {
        this->addr_ = addr;
    }

    void set_container_length(unsigned int container_len)
    {
        this->container_len_ = container_len;
    }

    void set_input_mode(const InputMode input_mode)
    {
        this->input_mode_ = input_mode;
    }

    void set_program_mode(const ProgramMode prog_mode)
    {
        this->prog_mode_ = prog_mode;
    }

    void set_input(const std::string &file_name)
    {
        this->input_file_ = file_name.c_str();
    }

    void set_input_length(unsigned int input_len)
    {
        this->input_len_ = input_len;
    }

private:
   CALLBACK_WRITE_FLASH_PROGRESS cb_write_flash_progress;
   HW_StorageType_E storage_type_;
   unsigned int input_len_;
   unsigned int container_len_;
   U64 addr_;
   InputMode input_mode_;
   ProgramMode prog_mode_;
   AddressingMode addr_mode_;
   std::string input_file_;
   void *cb_wm_progress_arg_;
};

#endif

