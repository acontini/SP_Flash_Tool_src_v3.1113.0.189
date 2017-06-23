/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2011
*
*****************************************************************************/
#ifndef HANDLE_MANAGER_H
#define HANDLE_MANAGER_H

#include "Utility.h"
#include "HandleManagerTemplate.h"
#include "flashtool.h"

class HandleManager
{
public:
	HandleManager(void) : is_handle_ready_(false), handle_result_(0) {}
	virtual ~HandleManager(void) {}

	bool is_handle_ready() const {
		return is_handle_ready_;
	}

	int handle_result() const {
		return handle_result_;
	}

    // For debugging purpose
	virtual void Dump() const = 0;

protected:
	//If the handle resouce do not need delete, just void implement
    virtual int HandleUnload(void) = 0;
	
	void set_is_handle_ready(bool is_ready) {
		is_handle_ready_ = is_ready;
	}

	void set_handle_result(int result) {
		handle_result_ = result;
	}

private:
	DISALLOW_COPY_AND_ASSIGN(HandleManager);
	bool is_handle_ready_;
	int handle_result_;
};

class RBHandleManager : public HandleManager
{
public:
	RBHandleManager(void);
	RBHandleManager(RB_HANDLE_T rb_handle);
    virtual ~RBHandleManager(void);
	RB_HANDLE_T rb_handle(void) const;
	virtual void Dump() const;
private:
	virtual int HandleUnload(void);
	DISALLOW_COPY_AND_ASSIGN(RBHandleManager);
private:
	RB_HANDLE_T rb_handle_;
	Concrete_HandleManager<RB_HANDLE_T*> rb_handle_mgr_;
};

#endif //HANDLE_MANAGER_H
