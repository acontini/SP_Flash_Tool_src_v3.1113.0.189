#ifndef WRITEMEMORY_ARG_H_
#define WRITEMEMORY_ARG_H_

#include "flashtool_api.h"
#include <string>

class WriteMemoryArg
{
public:
	WriteMemoryArg();
	~WriteMemoryArg();

	WriteFlashMemoryParameter GetBromWriteMemoryArg(void) const {return this->wm_arg_;}

     //setters
    void set_cb_write_memory_progress(const CALLBACK_WRITE_FLASH_PROGRESS cb)
    {
        wm_arg_.m_cb_progress = cb;
    }

    
    void set_cb_write_memory_progress_arg(void *usr_arg)
    {
         wm_arg_.m_cb_progress_arg = usr_arg;
    }	

    void set_flash_type(const HW_StorageType_E storage_type)
    {
        wm_arg_.m_flash_type = storage_type;
    }

    void set_addressing_mode(const AddressingMode addr_mode)
    {
        wm_arg_.m_addressing_mode = addr_mode;
    }

    void set_address(const U64 addr)
    {
        wm_arg_.m_address = addr;
    }

    void set_container_length(unsigned int container_len)
    {
        wm_arg_.m_container_length = container_len;
    }

    void set_input_mode(const InputMode input_mode)
    {
        wm_arg_.m_input_mode = input_mode;
    }

    void set_program_mode(const ProgramMode prog_mode)
    {
        wm_arg_.m_program_mode = prog_mode;
    }

    void set_input(const std::string& file_name)
    {
        wm_arg_.m_input = file_name.c_str();
    }

    void set_input_length(unsigned int input_len)
    {
        wm_arg_.m_input_length = input_len;
    }

private:
       void FillDefaultValue(void);
       CALLBACK_WRITE_FLASH_PROGRESS cb_write_memory_progress;
	WriteFlashMemoryParameter wm_arg_;
};

#endif

