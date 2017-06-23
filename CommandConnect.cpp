/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2011
*
*****************************************************************************/
#include <assert.h>

#include "CommandConnect.h"
#include "Logger.h"

//Brom Command Connect Concrete Class
BromCommandConnect::BromCommandConnect(
									   unsigned char com_port, 
									   const FlashTool_Connect_Arg *p_arg, 
									   FlashTool_Connect_Result *p_result, 
									   const ExternalMemoryConfig *p_external_memory_config, 
									   int *p_stopflag, 
									   FLASHTOOL_API_HANDLE_T *p_ft_handle, 
									   int force_charge) :
com_port_(com_port),
p_arg_(p_arg),
p_result_(p_result),
p_external_memory_config_(p_external_memory_config),
p_stopflag_(p_stopflag),
p_ft_handle_(p_ft_handle),
force_charge_(force_charge)
{
	Connect();
}

BromCommandConnect::~BromCommandConnect()
{
    Disconnect();
}

int BromCommandConnect::Connect()
{
	int ret = FlashTool_Connect( com_port_, p_arg_, p_result_, p_external_memory_config_, p_stopflag_, p_ft_handle_, force_charge_ );
    if( S_DONE != ret ) {
		this->set_is_connect(false);
		LOGD("ERROR: BromCommandConnect::Connect(): FlashTool_Connect() fail!");
	} else {
		this->set_is_connect(true);
		LOGD("BromCommandConnect::Connect(): FlashTool_Connect() succeed.");
	}
   
	this->set_connect_result(ret);
	return ret;
}

int BromCommandConnect::Disconnect()
{
	int ret;
	if ( this->is_connect() ) {
		ret = FlashTool_Disconnect(p_ft_handle_);
		if ( S_DONE != ret ) {
			this->set_is_connect(false);
			LOGD("ERROR: BromCommandConnect::Disconnect(): FlashTool_Disconnect() fail!");
		} else {
			LOGD("BromCommandConnect::Disconnect(): FlashTool_Disconnect() succeed.");
		}
	} else {
		LOGD("ERROR: BromCommandConnect::Disconnect(): is_connect(false).");
	}
	
	this->set_connect_result(ret);
	return ret;
}

//Eboot Command Connect Concrete Class
EbootCommandConnect::EbootCommandConnect(
	const Android_Boot_ARG *p_boot_arg, 
	const Android_ADV_Download_ARG *p_adv_dl_arg, 
	const ANDROID_ADV_HANDLE_T dl_handle, 
	const REBOOT_MODE reboot_mode) :
p_boot_arg_(p_boot_arg),
p_adv_dl_arg_(p_adv_dl_arg),
dl_handle_(dl_handle),
reboot_mode_(reboot_mode)
{
	Connect();
}

EbootCommandConnect::~EbootCommandConnect()
{
    Disconnect();
}

int EbootCommandConnect::Connect()
{
    assert( (NULL != dl_handle_) && "EbootCommandConnect::Disconnect(): dl_handle_ is NULL!");

	Android_ADV_SetBootArg(dl_handle_, *p_boot_arg_);
    Android_ADV_SetDownloadArg(dl_handle_, *p_adv_dl_arg_);

	EBOOT_RESULT ret = Android_ADV_Connect(dl_handle_);
    if ( EBOOT_SUCCESS != ret) {
		this->set_is_connect(false);
		LOGD("ERROR: EbootCommandConnect::Connect(): Android_ADV_Connect() failed!");
		return ret;
	} else {
		this->set_is_connect(true);
	}

	this->set_connect_result(static_cast<int>(ret));
	return ret;
}

int EbootCommandConnect::Disconnect()
{
	assert( (NULL != dl_handle_) && "EbootCommandConnect::Disconnect(): dl_handle_ is NULL!");

	EBOOT_RESULT ret;
	if ( this->is_connect() ) {
		ret = Android_ADV_Reboot(dl_handle_, reboot_mode_);
		if ( EBOOT_SUCCESS != ret ) {
			this->set_is_connect(false);
			LOGD("ERROR: EbootCommandConnect::Disconnect(): Android_ADV_Reboot() failed!");
		} 
	} else {
		LOGD("ERROR: EbootCommandConnect::Disconnect(): is_connect(false).");
	}

	this->set_connect_result(static_cast<int>(ret));
	return ret;
}