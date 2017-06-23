#ifndef SCI_READBACK_ARG_H_
#define SCI_READBACK_ARG_H_

#include "flashtool_api.h"

class SCIReadbackArg
{
public:
        SCIReadbackArg();
	 ~SCIReadbackArg();

      FlashTool_Readback_Arg GetBromReadbackArg(void) const { return this->rb_arg_;}

	void set_cb_readback_init(CALLBACK_READBACK_PROGRESS_INIT cb)
       {
              rb_arg_.m_cb_readback_flash_init = cb;
       }

        void set_cb_readback_progress(CALLBACK_READBACK_PROGRESS cb)
      {
              rb_arg_.m_cb_readback_flash = cb;
      }

        void set_rb_handle(RB_HANDLE_T handle)
      {
              rb_arg_.m_rb_handle = handle;
      }

       void set_storage_type(HW_StorageType_E type)
      {
              rb_arg_.m_storage_type = type;
      }

	void set_cb_readback_init_arg(void *usr_arg)
	{
             rb_arg_.m_cb_readback_flash_init_arg= usr_arg;
	}

	void set_cb_readback_progress_arg(void *usr_arg)
	{
            rb_arg_.m_cb_readback_flash_arg= usr_arg;
	}

private:
        void FillDefaultVaule();
        FlashTool_Readback_Arg  rb_arg_;
        CALLBACK_READBACK_PROGRESS m_cb_readback_flash;
        CALLBACK_READBACK_PROGRESS_INIT m_cb_readback_flash_init;
};

#endif


