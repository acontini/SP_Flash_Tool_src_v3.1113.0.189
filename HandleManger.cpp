/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2011
*
*****************************************************************************/
#include "HandleManager.h"
#include "Logger.h"
#include <new> 

#pragma warn -8004

/*****************************************************************************
*  Brom Readback Handle Manager Begin
*****************************************************************************/
//rb_handle_ must be defined before rb_handle_mgr_
RBHandleManager::RBHandleManager()
: rb_handle_(NULL), rb_handle_mgr_(&rb_handle_, RB_Create, RB_Destroy, S_DONE)
{
	LOG("RBHandleManager::RBHandleManager(): CreateHandle()...");
	rb_handle_mgr_.CreateHandle();
	set_is_handle_ready(rb_handle_mgr_.is_handle_ready());
}

RBHandleManager::RBHandleManager(RB_HANDLE_T rb_handle = NULL)
: rb_handle_(rb_handle), rb_handle_mgr_(&rb_handle_, RB_Create, RB_Destroy, S_DONE)
{
	LOG("RBHandleManager::RBHandleManager(): CreateHandle(%d).", rb_handle);
	rb_handle_mgr_.CreateHandle();
	set_is_handle_ready(rb_handle_mgr_.is_handle_ready());
}

RB_HANDLE_T RBHandleManager::rb_handle() const
{
	return *(rb_handle_mgr_.handle());
}

int RBHandleManager::HandleUnload(void) 
{
	unsigned short count = 0;
	int ret =  RB_GetCount(rb_handle_, &count);
	LOG("RBHandleManger::HandleUnload(): RB_GetCount(): count(%d).", count);
	if ( S_DONE == ret )
	{
		for (unsigned short i=0; i<count; i++) {
			RB_Delete(rb_handle_, i);
			LOG("RBHandleManger::HandleUnload(): RB_Delete(): count(%d), the (%u) RB resource is deleted.", 
				count, i+1);
		}
	} else {
		LOG("ERROR: RBHandleManger::HandleUnload(): RB_GetCount() failed, error code(%d).", ret);
	}
	return ret;
}

RBHandleManager::~RBHandleManager(void)
{
	int ret = -1;
	if ( is_handle_ready() ) {
		ret = HandleUnload();
		if (S_DONE == ret ) {
			rb_handle_mgr_.DestroyHandle();
		} else {
			LOG("ERROR: RBHandleManger::~RBHandleManger(): HandleUnload() failed, error code(%d).", ret); 
		}
	}
}

void RBHandleManager::Dump() const
{
	int ret = S_DONE;
	unsigned short count = 0;
	ret = RB_GetCount(rb_handle_, &count);
	if (S_DONE != ret) {
		LOG("ERROR: %s(): RB_GetCount failed!", __FUNC__);
		return;
	}

	RB_INFO *rb_infos = NULL;
	try {
		rb_infos = new RB_INFO[count];
		ret = RB_GetInfoAll(rb_handle_, rb_infos, count);
		if (S_DONE != ret) {
			LOG("ERROR: %s(): RB_GetInfoAll failed!", __FUNC__);
		} else {
			for (unsigned short i = 0; i< count; i++) {
				LOG("RB[%d]:enabled(%d), read_flag(%d), part_id(%d), addr(0x%016I64X), length(0x%X), path(%s)",
					rb_infos[i].index,
					rb_infos[i].enable,
					rb_infos[i].m_read_flag,
					rb_infos[i].part_id,
					rb_infos[i].readback_addr,
					rb_infos[i].readback_len,
					rb_infos[i].filepath);
			}
		}
	} catch ( std::bad_alloc ex ) {
		LOG("ERROR: %s(): malloc memory for readback info failed(%s)!", __FUNC__, ex.what());
	}

	if(rb_infos != NULL){
		delete [] rb_infos;
		rb_infos = NULL;
	}

}
/*****************************************************************************
*  Brom Readback Handle Manager End
*****************************************************************************/