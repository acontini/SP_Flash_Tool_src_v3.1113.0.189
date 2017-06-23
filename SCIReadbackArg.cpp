#include "SCIReadbackArg.h"

SCIReadbackArg::SCIReadbackArg()
{
    FillDefaultVaule();
}

SCIReadbackArg::~SCIReadbackArg()
{}

void SCIReadbackArg::FillDefaultVaule()
{
    memset(&rb_arg_,0,sizeof(FlashTool_Readback_Arg));

    rb_arg_.m_readback_accuracy = ACCURACY_AUTO;
    rb_arg_.m_cb_readback_flash_init = m_cb_readback_flash_init;
    rb_arg_.m_cb_readback_flash_init_arg = NULL;
    rb_arg_.m_cb_readback_flash = m_cb_readback_flash;
    rb_arg_.m_cb_readback_flash_arg = NULL;

}




