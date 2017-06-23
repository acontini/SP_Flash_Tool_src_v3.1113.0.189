#include "WriteMemoryArg.h"

WriteMemoryArg::WriteMemoryArg()
{
   FillDefaultValue();
}

WriteMemoryArg::~WriteMemoryArg()
{}

void WriteMemoryArg::FillDefaultValue()
{
   wm_arg_.m_flash_type = HW_STORAGE_NAND;
   wm_arg_.m_addressing_mode = AddressingMode_LogicalAddress;
   wm_arg_.m_address = 0;
   wm_arg_.m_container_length = 0;
   wm_arg_.m_input_mode = InputMode_FromFile;
   wm_arg_.m_program_mode = ProgramMode_PageOnly;
   wm_arg_.m_input = NULL;
   wm_arg_.m_input_length = 0;
   wm_arg_.m_cb_progress = cb_write_memory_progress;
   wm_arg_.m_cb_progress_arg = this;
}


