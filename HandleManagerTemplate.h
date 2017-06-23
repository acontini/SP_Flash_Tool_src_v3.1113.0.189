/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2011
*
*****************************************************************************/
#ifndef HANDLE_MANAGER_TEMPLATE_H
#define HANDLE_MANAGER_TEMPLATE_H

#include "Utility.h"
#include "Logger.h"

template<typename T>
class Concrete_HandleManager
{
public:
    typedef int  (__stdcall *HandleCreator)(T handle);
    typedef int  (__stdcall *HandleDestoryer)(T handle);

    explicit Concrete_HandleManager(T handle, HandleCreator creator, HandleDestoryer destoryer, int success_flag)
        : handle_(handle),
          creator_(creator),
          destoryer_(destoryer),
          success_flag_(success_flag) {}
	~Concrete_HandleManager() {}

        bool is_handle_ready() const {
        return is_handle_ready_;
    }

	T handle() const {
		return handle_;
	}

    int CreateHandle() {
		int ret = creator_(handle_);
        bool is_ready = (success_flag_ == ret);
        set_is_handle_ready(is_ready);
        LOG("Concrete_HandleManager(): CreateHandle(): is_handle_ready_(%s), return vlaue(%d).",
			(is_handle_ready() ? "Yes" : "No"), ret);
        return ret;
    }

    int DestroyHandle() {
		int ret = -1;
        if( is_handle_ready() ) {
			ret = destoryer_(handle_);
            bool is_destory = (success_flag_ == ret);
            LOG("Concrete_HandleManager(): DestroyHandle() is %s.",
                is_destory ? "success" : "failure");
        } else {
            LOG("Concrete_HandleManager(): DestroyHandle() falied!");
        }
        return ret;
    }

private:
    void set_is_handle_ready(bool is_ready) {
        this->is_handle_ready_ = is_ready;
    }

    DISALLOW_COPY_AND_ASSIGN(Concrete_HandleManager);

private:
    const T handle_;
    const int success_flag_;
    HandleCreator creator_;
    HandleDestoryer destoryer_;
    bool is_handle_ready_;
};

#endif // HANDLE_MANAGER_TEMPLATE_H
