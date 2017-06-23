#include "ReadbackSetting.h"

#include "ReadbackCommand.h"
#include "Logger.h"

SCIReadbackSetting::SCIReadbackSetting()
    : cb_readback_init_(NULL),
      cb_readback_progress_(NULL)
{
}

SCIReadbackSetting::~SCIReadbackSetting()
{
      LOG("destroy RB handle.");
      RB_ClearAll(readback_handle_);
	LOG("%s: Clear all RB handle.", __FUNC__);
}

SCIReadbackSetting* SCIReadbackSetting::Clone() const
{
      return new SCIReadbackSetting(*this);
}
void SCIReadbackSetting::Dump(void) const
{
      LOG("SCIReadbackSetting...");
}

int SCIReadbackSetting::InitialRBHandle(const ReadbackItem &rb_item)
{
      LOG("Initial Handle...");
      int ret = S_DONE;
	  
                   ret = RB_Append(readback_handle_, rb_item.path().c_str(), rb_item.addr(), rb_item.len());
			if (ret != S_DONE) {
				LOGE("%s: RB_Append fail, ret(%d), path(%s)", __FUNC__, ret, rb_item.path().c_str());
			}

			ret = RB_SetEnableAttr(readback_handle_, rb_item.index(), _TRUE);
			if (ret != S_DONE) {
				LOGE("%s: RB_SetEnableAttr fail, ret(%d)", __FUNC__, ret);
			}

			ret = RB_SetReadbackFlag(readback_handle_, rb_item.index(), rb_item.read_flag());
			if (ret != S_DONE) {
				LOGE("%s: RB_SetReadbackFlag fail, ret(%d)", __FUNC__, ret);
			}

			ret = RB_SetReadbackAddr(readback_handle_, rb_item.index(), rb_item.addr());
			if (ret != S_DONE) {
				LOGE("%s: RB_SetReadbackAddr fail, ret(%d)", __FUNC__, ret);
			}

			ret = RB_SetReadbackLength(readback_handle_, rb_item.index(), rb_item.len());
			if (ret != S_DONE) {
				LOGE("%s: RB_SetReadbackLength fail, ret(%d)", __FUNC__, ret);
			}

			ret = RB_SetAddrTypeFlag(readback_handle_, rb_item.index(), NUTL_ADDR_PHYSICAL);

			if (ret != S_DONE) {
				LOGE("%s: RB_SetAddrTypeFlag fail, ret(%d)", __FUNC__, ret);
			}


		return ret;
}

SharedPtr<Command> SCIReadbackSetting::CreateCommand(FLASHTOOL_API_HANDLE_T ft_handle)const
{
    SharedPtr<SCIReadbackCommand> cmd(new SCIReadbackCommand(ft_handle));
    cmd->readback_arg_.set_storage_type(storage_type_);
    cmd->readback_arg_.set_rb_handle(readback_handle_);
    cmd->readback_arg_.set_cb_readback_init_arg(this->cb_readback_init_arg_);
    cmd->readback_arg_.set_cb_readback_progress_arg(this->cb_readback_arg_);

    if(cb_readback_init_ != NULL)
    {
        cmd->readback_arg_.set_cb_readback_init(cb_readback_init_);
    }
    if(cb_readback_progress_ != NULL)
    {
        cmd->readback_arg_.set_cb_readback_progress(cb_readback_progress_);
    }

    return cmd;
}



