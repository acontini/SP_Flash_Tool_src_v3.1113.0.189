/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2011
*
*****************************************************************************/
#ifndef SPFLASHTOOL_COMMAND_CONNECT_
#define SPFLASHTOOL_COMMAND_CONNECT_

#include "Utility.h"
#include "flashtool.h"
#include "eboot\interface.h"

//Command Connect Basic Class
class CommandConnect
{
public:
	CommandConnect() : is_connect_(false), connect_result_(0) {}
	virtual ~CommandConnect() {}

	bool is_connect() const {
		return is_connect_;
	}	
	int connect_result() const {
		return connect_result_;
	}

protected:
	virtual int Connect(void) = 0;
	virtual int Disconnect(void) = 0;

	void set_is_connect(bool is_conn) {
		this->is_connect_ = is_conn;
	}
	void set_connect_result(int ret) {
		this->connect_result_ = ret;
	}

private:
    DISALLOW_COPY_AND_ASSIGN(CommandConnect);
	bool is_connect_;
	int connect_result_;
};

//Brom Command Connect Concrete Class
class BromCommandConnect : public CommandConnect
{
public:
	BromCommandConnect(
		unsigned char  com_port,
        const FlashTool_Connect_Arg  *p_arg,
		FlashTool_Connect_Result  *p_result,
		const ExternalMemoryConfig      *p_external_memory_config,
		int *p_stopflag,
		FLASHTOOL_API_HANDLE_T  *p_ft_handle,
		int force_charge);
	~BromCommandConnect();

	virtual int Connect();
	virtual int Disconnect();

private:
    DISALLOW_COPY_AND_ASSIGN(BromCommandConnect);

private:
	unsigned char  com_port_;
    const FlashTool_Connect_Arg  *p_arg_;
    FlashTool_Connect_Result  *p_result_;
    const ExternalMemoryConfig      *p_external_memory_config_;
    int *p_stopflag_;
    FLASHTOOL_API_HANDLE_T  *p_ft_handle_;
    int force_charge_;
};

//Eboot Command Connect Concrete Class
class EbootCommandConnect : public CommandConnect
{
public:
	EbootCommandConnect(
		const Android_Boot_ARG *p_boot_arg,
		const Android_ADV_Download_ARG *p_adv_dl_arg,
		const ANDROID_ADV_HANDLE_T dl_handle,
		const REBOOT_MODE reboot_mode);
	~EbootCommandConnect();
	
	virtual int Connect();
	virtual int Disconnect();
    
private:
	DISALLOW_COPY_AND_ASSIGN(EbootCommandConnect);

private:
	const Android_Boot_ARG *p_boot_arg_;
    const Android_ADV_Download_ARG *p_adv_dl_arg_;
    const ANDROID_ADV_HANDLE_T dl_handle_;
    const REBOOT_MODE reboot_mode_;
};

#endif // SPFLASHTOOL_COMMAND_CONNECT_