/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2009
*
*****************************************************************************/
#include <vcl.h>
#pragma hdrstop

#pragma warn -8027  // Functions containing do are not expanded inline
#pragma warn -8004
#include "utilcls.h"
#include <algorithm>
#include <atlbase.h>
#include <utility> 
#include <time.h>
#include <iomanip>

#include "tboot_1.h"
#include "com_enum.h"
#include "DOWNLOAD.H"
#include "FlashToolCommand.h"
#include "Logger.h"
#include "SLA_Challenge.h"
#include "Utility.h"
#include "Eboot\interface.h"
#include "meta.h"
#include "WMMETA_Wrapper.h"

#include "AndroidImageInfo.h"
#include "ImageMapRule.h"
#include "Utility.h"
#include "FileUtils.h"
#include "GlobalData.h"
#include "ErrorLookup.h"
#include "FlashAllInOneAPIs.h"
#include "FlashToolUSB.h"
#include "version.h"

#include "DownloadImageChecksum.h"

/***************************global data definition***************************/
/**
 * Global data for DL_HANDLE_T
 */
class DownloadHandleInitializer;
class ConsoleModeData{
public:
    static DL_HANDLE_T downloadHandle;
	static std::auto_ptr<DownloadHandleInitializer> DL_init_ptr;

private:
    ConsoleModeData();
};

DL_HANDLE_T ConsoleModeData::downloadHandle;
std::auto_ptr<DownloadHandleInitializer> ConsoleModeData::DL_init_ptr;

/****************************************************************************/ 

extern int g_stopflag;

using ConsoleMode::BackupSetting;
using ConsoleMode::Write_BT_WIFI_IMEI_NVRAM_Setting;
using ConsoleMode::DownloadSetting;
using ConsoleMode::FormatSetting;
using ConsoleMode::GeneralSetting;
using ConsoleMode::ResetToFactoryDefaultSetting;
using ConsoleMode::RestoreSetting;
using std::find;
using std::mismatch;
using std::pair;
using std::vector;
using std::wstring;


static int __stdcall COMPortOpenCallback(HANDLE, void *)
{
    Logger::GetLogger() << Logger::Info
           << "COM port is open." << endl
           << "Trying to sync with the target..." << endl;
    return 0;
}

static int __stdcall DownloadDAProgressInit(void *) 
{
	Logger::GetLogger()<<Logger::Info
		<< "Downloading DA now..."<<endl;
	return 0;
}

static int __stdcall DownloadDAProgressCallBack(unsigned char percent, unsigned int sent_bytes, unsigned int total_bytes, void *usr_arg)
{
	static unsigned char lastReportedProgress = 0;
	if ( (percent != lastReportedProgress) && 
		(percent % 10 == 0) ) {
		Logger::GetLogger() << Logger::Info
			<< (int) percent
			<< "% of DA has been sent to target."<<endl; 
		lastReportedProgress = percent;
	}
	return 0;
}

static int __stdcall DownloadBootloaderProgressInit(void *)
{
	Logger::GetLogger() << Logger::Info
           << "Downloading bootloader..." << endl;
    return 0;
}

static int __stdcall DownloadProgressInit(void *)
{
	Logger::GetLogger() << Logger::Info
           << "Downloading images..." << endl;
    return 0;
}

static int __stdcall DownloadProgressCallback(unsigned char currentProgress,
                                             unsigned int, unsigned int,
                                              void *)
{
    static unsigned char lastReportedProgress = 0;

    if ((currentProgress != lastReportedProgress) &&
        (currentProgress % 10 == 0)) {
    	Logger::GetLogger() << Logger::Info
               << (int) currentProgress
               << "% of image data sent to the target." << endl;
        lastReportedProgress = currentProgress;
    }

    return 0;
}

static int __stdcall cb_rom_mem_checksum_init(void *usr_arg, const char* image_name)
{
	Logger::GetLogger() << Logger::Info
           << "Verifying " << image_name << "memory buffer now..."<<std::endl;

    return 0;
}

static int __stdcall cb_rom_mem_checksum(unsigned char finished_percentage, unsigned int finished_bytes, unsigned int total_bytes, void *usr_arg)
{
       static unsigned char last_percentage = 0;

	if ( (finished_percentage != last_percentage) &&
		(finished_percentage % 10 == 0) ) {
    	Logger::GetLogger() << Logger::Info
               << (int) finished_percentage
               << "% of the image has been done." << std::endl;
			last_percentage = finished_percentage;
    }

    return 0;
}

static int __stdcall cb_da_dl_checksum_init(void *usr_arg, const char* image_name)
{
	Logger::GetLogger() << Logger::Info
	<< image_name <<" checksum is executing ..." << std::endl;


    return 0;
}
//---------------------------------------------------------------------------
static int __stdcall cb_da_dl_checksum(unsigned char percent, unsigned int  sent_bytes, unsigned int total_bytes, void *usr_arg)
{
       static unsigned char last_percentage = 0;

	if ( (percent != last_percentage) &&
		(percent % 10 == 0) ) {
    	Logger::GetLogger() << Logger::Info
               << (int) percent
               << "% of the image has been done." << std::endl;
			last_percentage = percent;
    }

    return 0;
}

//---------------------------------------------------------------------------
static int __stdcall cb_usbstatus_init(void * arg, const char* usb_status)
{
    Logger::GetLogger()<<Logger::Info
		<<"USB Speed Status: "<<usb_status<<std::endl;

    return 0;
}


static void FillFlashToolConnectArg(FlashTool_Connect_Arg &ftConnect,
		FlashTool_Connect_Result &ftConnectResult,
		DA_HANDLE_T &daHandle,
		AUTH_HANDLE_T &authHandle,
		SCERT_HANDLE_T &scertHandle)
{
    memset( &ftConnect, 0, sizeof(ftConnect));
    memset( &ftConnectResult, 0, sizeof(ftConnectResult));

    // With All-In-One FLASHTOOL_RESULT to get DA report
    //FIXME
    //m_bGetDAReportWithConnArg = true;

    // com port timeout setting
	ftConnect.m_com_ms_read_timeout                 = COM_DEFAULT_TIMEOUT;
	ftConnect.m_com_ms_write_timeout                = COM_DEFAULT_TIMEOUT;

	// fill BOOT_FLASHTOOL_ARG
    BOOT_FLASHTOOL_ARG &bootFlashtoolArg = ftConnect.m_boot_arg;

    bootFlashtoolArg.m_bbchip_type     = (g_platform_info.getLoadPlatformName() == "MT6516") ? MT6516_AP : AUTO_DETECT_BBCHIP;
    bootFlashtoolArg.m_ext_clock       = AUTO_DETECT_EXT_CLOCK;
    bootFlashtoolArg.m_ms_boot_timeout = 200000;/*Extend time out to 200s for poor adb reboot time*/;
    bootFlashtoolArg.m_max_start_cmd_retry_count =
                                    DEFAULT_BROM_START_CMD_RETRY_COUNT;

    bootFlashtoolArg.m_cb_com_init_stage     = COMPortOpenCallback;
    bootFlashtoolArg.m_cb_com_init_stage_arg = NULL;
    bootFlashtoolArg.m_cb_in_brom_stage      = NULL;
    bootFlashtoolArg.m_cb_in_brom_stage_arg  = NULL;

    bootFlashtoolArg.m_speedup_brom_baudrate = _TRUE;

    bootFlashtoolArg.m_ready_power_on_wnd_handle = NULL;
    bootFlashtoolArg.m_ready_power_on_wparam     = NULL;
    bootFlashtoolArg.m_ready_power_on_lparam     = NULL;

    bootFlashtoolArg.m_auth_handle               = authHandle;
    bootFlashtoolArg.m_cb_sla_challenge          = SLA_Challenge;
    bootFlashtoolArg.m_cb_sla_challenge_arg      = NULL;
    bootFlashtoolArg.m_cb_sla_challenge_end      = SLA_Challenge_END;
    bootFlashtoolArg.m_cb_sla_challenge_end_arg  = NULL;
	bootFlashtoolArg.m_scert_handle = scertHandle;

    bootFlashtoolArg.m_p_bank0_mem_cfg = NULL;
    bootFlashtoolArg.m_p_bank1_mem_cfg = NULL;

    bootFlashtoolArg.m_da_handle = daHandle;

    bootFlashtoolArg.m_cb_download_da_init       = DownloadDAProgressInit;
    bootFlashtoolArg.m_cb_download_da_init_arg   = NULL;
    bootFlashtoolArg.m_cb_download_da            = DownloadDAProgressCallBack;
    bootFlashtoolArg.m_cb_download_da_arg        = NULL;

    //bootFlashtoolArg.m_usb_enable = _FALSE;

    ftConnect.m_cb_security_pre_process_notify     = NULL;
    ftConnect.m_cb_security_pre_process_notify_arg = NULL;
    ftConnect.m_nor_chip_select[0]                 = CS_0;
    ftConnect.m_nor_chip_select[1]                 = CS_WITH_DECODER;
    ftConnect.m_nand_chip_select                   = CS_0;
    ftConnect.m_p_nand_acccon                      = NULL;
   //*************set Boot Arg end*************


    // security pre-process notify callback
	ftConnect.m_cb_security_pre_process_notify      = NULL;
	ftConnect.m_cb_security_pre_process_notify_arg  = NULL;

	ftConnect.m_boot_arg.m_bmt_block_count = g_platform_info.getBMTBlocks();

   //add for Console Mode download fail issue with v3.1204.04     
    ftConnect.m_storage_type = g_platform_info.getFlashToolStorageConfig().GetStorageType();
    ftConnect.m_p_dl_handle = ConsoleModeData::downloadHandle;

}

static void FillFlashToolAdvancedDownloadArg(FlashTool_Download_Arg &fdl_arg,
		FlashTool_Download_Result &fdl_res,
		DL_HANDLE_T &downloadHandle)
{
    memset( &fdl_arg,    0, sizeof(fdl_arg));
    memset( &fdl_res, 0, sizeof(fdl_res));

	fdl_arg.m_dl_handle          = downloadHandle;
	fdl_arg.m_dl_handle_list     = NULL;

    //DA report callback
    fdl_arg.m_cb_da_report        = NULL;
    fdl_arg.m_cb_da_report_arg    = NULL;

    // download progress callback
    fdl_arg.m_download_accuracy                   = ACCURACY_AUTO;
    fdl_arg.m_cb_download_flash_init              = DownloadProgressInit;
    fdl_arg.m_cb_download_flash_init_arg          = NULL;
    fdl_arg.m_cb_download_flash                   = DownloadProgressCallback;
    fdl_arg.m_cb_download_flash_arg               = NULL;
    fdl_arg.m_cb_security_post_process_notify     = NULL;
    fdl_arg.m_cb_security_post_process_notify_arg = NULL;

    // Boot-Loader download progress callback
    fdl_arg.m_cb_download_bloader_init       = DownloadBootloaderProgressInit;
    fdl_arg.m_cb_download_bloader_init_arg   = NULL;
    fdl_arg.m_cb_download_bloader            = DownloadProgressCallback;
    fdl_arg.m_cb_download_bloader_arg        = NULL;
    fdl_arg.m_enable_tgt_res_layout_check   = _FALSE;
    fdl_arg.m_enable_bbchip_ver_check       = _FALSE;
    fdl_arg.m_downloadstyle_sequential      = _FALSE;

    //add for da-download-all-with-chksum
    fdl_arg.m_cb_checksum_init = cb_da_dl_checksum_init;
    fdl_arg.m_cb_checksum_init_arg = NULL;
    fdl_arg.m_cb_checksum = cb_da_dl_checksum;
    fdl_arg.m_cb_checksum_arg = NULL;

}

void FillChecksumArg(RomMemChecksumArg &arg, RomMemChecksumResult &res)
{
     memset(&arg, 0, sizeof(arg));
     memset(&res, 0, sizeof(res));

    arg.m_cb_rom_mem_checksum = cb_rom_mem_checksum;
    arg.m_cb_rom_mem_checksum_arg = NULL;
    arg.m_cb_rom_mem_checksum_init = cb_rom_mem_checksum_init;
    arg.m_cb_rom_mem_checksum_init_arg = NULL;
	
}


static int __stdcall FillFlashToolWatchDogArg(FlashTool_EnableWDT_Arg *p_wdt_arg,unsigned int uTimeOut)
{
	assert(NULL != p_wdt_arg);
	memset(p_wdt_arg, 0, sizeof(FlashTool_EnableWDT_Arg));
	//timeout to reset bootRom
	p_wdt_arg->m_timeout_ms = uTimeOut;//15000;
	p_wdt_arg->m_async = _FALSE;
	p_wdt_arg->m_reboot = _FALSE;
	return 0;
}

void FillUSBStatusArg(FlashTool_USB_Status_Arg &usb_status_arg, FlashTool_USB_Status_Result &usb_status_result)
{
       memset(&usb_status_arg, 0, sizeof(usb_status_arg));
       memset(&usb_status_result, 0, sizeof(usb_status_result)); 
       
       usb_status_arg.m_cb_usb_status_init = cb_usbstatus_init;
       usb_status_arg.cb_usb_status_init_arg = NULL;
}

static int __stdcall ReadbackProgressInit(HW_StorageType_E  storage_type, 
										  unsigned long long begin_addr, 
										  unsigned int length, 
										  const char *rb_filepath, 
										  void *usr_arg)
{
	Logger::GetLogger() << Logger::Info
		<< "===========================" <<endl
		<< "Readback rom..." << endl;
	Logger::GetLogger() << "Readback path: "
		<< rb_filepath << endl;
	Logger::GetLogger() << "Readback begin address: "
		<< DumpHex(begin_addr)<<endl;
	Logger::GetLogger() << "Readback length: "
		<< DumpHex(length)<<endl;
	Logger::GetLogger() << dec;
    return 0;
}

static int __stdcall ReadbackProgressCallback(unsigned char finished_percentage, unsigned int sent_bytes, unsigned int  total_bytes, void *usr_arg)
{
	static unsigned char last_percentage = 0;

	if ( (finished_percentage != last_percentage) &&
		(finished_percentage % 10 == 0) ) {
    	Logger::GetLogger() << Logger::Info
               << (int) finished_percentage
               << "% of rom has been read back." << endl;
			last_percentage = finished_percentage;
    }

    return 0;
}

static void FillFlashToolAdvancedReadbackArg(FlashTool_Readback_Arg& rb_arg,
											 FlashTool_Readback_Result& rb_result, RB_HANDLE_T& rb_handle,
											 const GeneralSetting &generalSetting)
{
	rb_arg.m_storage_type = generalSetting.Get_flash_operation();
	// an object of RB_HANDLE
	rb_arg.m_rb_handle = rb_handle;
	// the accuracy of the read back progress
	rb_arg.m_readback_accuracy = ACCURACY_AUTO;
	// readback call back funciton
	rb_arg.m_cb_readback_flash_init = ReadbackProgressInit;
	rb_arg.m_cb_readback_flash_init_arg = NULL;
	rb_arg.m_cb_readback_flash = ReadbackProgressCallback;
	rb_arg.m_cb_readback_flash_arg = NULL;
}

static void FillComPortSetting(COM_PORT_SETTING &comPortSetting,
                               const GeneralSetting &generalSetting)
{
    const wstring comPort = generalSetting.GetComPort();
    const wstring portType = generalSetting.GetPortType();

    comPortSetting.com.number =
            ((comPort == L"USB") || portType == L"USB")? 0 : ::_wtoi(comPort.c_str());

    comPortSetting.baudrate         = UART_BAUD_921600;
    comPortSetting.ms_read_timeout  = COM_DEFAULT_TIMEOUT;
    comPortSetting.ms_write_timeout = COM_DEFAULT_TIMEOUT;
}

#if 0
static void FillFlashToolArg(FLASHTOOL_ARG &flashToolArg,
                             DA_HANDLE_T &daHandle,
                             AUTH_HANDLE_T &authHandle,
							 SCERT_HANDLE_T &scertHandle
							 )
{
    ::memset(&flashToolArg, 0, sizeof(flashToolArg));

    BOOT_FLASHTOOL_ARG &bootFlashtoolArg = flashToolArg.m_boot_arg;

    bootFlashtoolArg.m_bbchip_type     = AUTO_DETECT_BBCHIP;
    bootFlashtoolArg.m_ext_clock       = AUTO_DETECT_EXT_CLOCK;
    bootFlashtoolArg.m_ms_boot_timeout = 100000;/*30000*/;
    bootFlashtoolArg.m_max_start_cmd_retry_count =
                                    DEFAULT_BROM_START_CMD_RETRY_COUNT;

    bootFlashtoolArg.m_cb_com_init_stage     = COMPortOpenCallback;
    bootFlashtoolArg.m_cb_com_init_stage_arg = NULL;
    bootFlashtoolArg.m_cb_in_brom_stage      = NULL;
    bootFlashtoolArg.m_cb_in_brom_stage_arg  = NULL;

    bootFlashtoolArg.m_speedup_brom_baudrate = _TRUE;

    bootFlashtoolArg.m_ready_power_on_wnd_handle = NULL;
    bootFlashtoolArg.m_ready_power_on_wparam     = NULL;
    bootFlashtoolArg.m_ready_power_on_lparam     = NULL;

    bootFlashtoolArg.m_auth_handle               = authHandle;
    bootFlashtoolArg.m_cb_sla_challenge          = SLA_Challenge;
    bootFlashtoolArg.m_cb_sla_challenge_arg      = NULL;
    bootFlashtoolArg.m_cb_sla_challenge_end      = SLA_Challenge_END;
    bootFlashtoolArg.m_cb_sla_challenge_end_arg  = NULL;
	bootFlashtoolArg.m_scert_handle = scertHandle;

    bootFlashtoolArg.m_p_bank0_mem_cfg = NULL;
    bootFlashtoolArg.m_p_bank1_mem_cfg = NULL;

    bootFlashtoolArg.m_da_handle = daHandle;

    bootFlashtoolArg.m_cb_download_da_init       = NULL;
    bootFlashtoolArg.m_cb_download_da_init_arg   = NULL;
    bootFlashtoolArg.m_cb_download_da            = NULL;
    bootFlashtoolArg.m_cb_download_da_arg        = NULL;

    bootFlashtoolArg.m_usb_enable = _FALSE;

    flashToolArg.m_cb_da_report     = NULL;
    flashToolArg.m_cb_da_report_arg = NULL;

    flashToolArg.m_cb_security_pre_process_notify     = NULL;
    flashToolArg.m_cb_security_pre_process_notify_arg = NULL;
    flashToolArg.m_baudrate_full_sync_count           = 1;
    flashToolArg.m_nor_chip_select[0]                 = CS0;
    flashToolArg.m_nor_chip_select[1]                 = CS_WITH_DECODER;
    flashToolArg.m_nand_chip_select                   = CS0;
    flashToolArg.m_p_nand_acccon                      = NULL;
    flashToolArg.m_enable_ui_dram_cfg                 = _FALSE;
}

static void FillFlashToolResult(FLASHTOOL_RESULT &flashToolResult)
{
    ::memset(&flashToolResult, 0, sizeof(flashToolResult));
}


static void FillFlashToolDownloadArg(
                    FLASHTOOL_DOWNLOAD_ARG &flashToolDownloadArg,
                    DL_HANDLE_T &downloadHandle,
                    bool checkBasebandVersion,
                    const DownloadSetting &downloadSetting,
                    const GeneralSetting &generalSetting )
{
    ::memset(&flashToolDownloadArg, 0, sizeof(flashToolDownloadArg));

/*
    if(L"NOR" == generalSetting.Get_flash_operation() )
    {
        flashToolDownloadArg.m_storage_type = HW_STORAGE_NOR;
    }
    else
    {
    	 flashToolDownloadArg.m_storage_type = HW_STORAGE_NAND;
    }
*/

    flashToolDownloadArg.m_dl_handle_list = NULL;
    flashToolDownloadArg.m_dl_handle      = downloadHandle;

    flashToolDownloadArg.m_download_accuracy = ACCURACY_AUTO;
    flashToolDownloadArg.m_cb_download_flash_init = DownloadProgressInit;
    flashToolDownloadArg.m_cb_download_flash_init_arg = NULL;
    flashToolDownloadArg.m_cb_download_flash = DownloadProgressCallback;
    flashToolDownloadArg.m_cb_download_flash_arg = NULL;
    flashToolDownloadArg.m_cb_security_post_process_notify = NULL;
    flashToolDownloadArg.m_cb_security_post_process_notify_arg = NULL;

    if (downloadSetting.IsAutoFormatEnabled())
    {
        flashToolDownloadArg.m_format_enable                  = _TRUE;
        flashToolDownloadArg.m_format_cfg.m_auto_format_fat   = _TRUE;
        flashToolDownloadArg.m_format_cfg.m_format_begin_addr = 0;
        flashToolDownloadArg.m_format_cfg.m_format_length     = 0;
    }
    else if (downloadSetting.IsManualFormatEnabled())
    {
        flashToolDownloadArg.m_format_enable                = _TRUE;
        flashToolDownloadArg.m_format_cfg.m_auto_format_fat = _FALSE;
        flashToolDownloadArg.m_format_cfg.m_format_begin_addr =
                                downloadSetting.GetManualFormatBeginAddress();
        flashToolDownloadArg.m_format_cfg.m_format_length =
                                downloadSetting.GetManualFormatLength();
    }
    else
    {
        flashToolDownloadArg.m_format_enable                  = _FALSE;
        flashToolDownloadArg.m_format_cfg.m_auto_format_fat   = _FALSE;
        flashToolDownloadArg.m_format_cfg.m_format_begin_addr = 0;
        flashToolDownloadArg.m_format_cfg.m_format_length     = 0;
    }

    flashToolDownloadArg.m_cb_format_report_init       = NULL;
    flashToolDownloadArg.m_cb_format_report_init_arg   = NULL;
    flashToolDownloadArg.m_cb_format_report            = NULL;
    flashToolDownloadArg.m_cb_format_report_arg        = NULL;
    flashToolDownloadArg.m_enable_tgt_res_layout_check = _TRUE;
    flashToolDownloadArg.m_enable_bbchip_ver_check =     _FALSE;
                                    //checkBasebandVersion ? _TRUE : _FALSE;
    flashToolDownloadArg.m_downloadstyle_sequential    = _FALSE;
    flashToolDownloadArg.m_cb_format_statistics        = NULL;
    flashToolDownloadArg.m_cb_format_statistics_arg    = NULL;

    flashToolDownloadArg.m_otp_enable                = _FALSE;
    flashToolDownloadArg.m_ft_cfg_enable             = _FALSE;
    flashToolDownloadArg.m_sec_ro_enable             = _FALSE;
    flashToolDownloadArg.m_cust_para_enable          = _FALSE;
    flashToolDownloadArg.m_cb_param_process_init     = NULL;
    flashToolDownloadArg.m_cb_param_process_init_arg = NULL;
    flashToolDownloadArg.m_cb_param_process          = NULL;
    flashToolDownloadArg.m_cb_param_process_arg      = NULL;

    flashToolDownloadArg.m_cb_post_process_init     = NULL;
    flashToolDownloadArg.m_cb_post_process_init_arg = NULL;
    flashToolDownloadArg.m_cb_post_process          = NULL;
    flashToolDownloadArg.m_cb_post_process_arg      = NULL;

    flashToolDownloadArg.m_cb_download_bloader_init     = DownloadBootloaderProgressInit;
    flashToolDownloadArg.m_cb_download_bloader_init_arg = NULL;
    flashToolDownloadArg.m_cb_download_bloader          = DownloadProgressCallback;
    flashToolDownloadArg.m_cb_download_bloader_arg      = NULL;
/*
    if(L"Android" == downloadSetting.GetDLOS())
    {
      flashToolDownloadArg.m_write_usb_download_control_bit = _TRUE;
    }
    else
    {
      flashToolDownloadArg.m_write_usb_download_control_bit = _FALSE;
    }
*/
    if (downloadSetting.IsWatchdogTimerEnabled())
    {
        flashToolDownloadArg.m_enable_wdt_timeout      = _TRUE;
        flashToolDownloadArg.m_ms_wdt_timeout_interval = 5000;
    }
    else
    {
        flashToolDownloadArg.m_enable_wdt_timeout      = _FALSE;
        flashToolDownloadArg.m_ms_wdt_timeout_interval = 0;
    }

    flashToolDownloadArg.m_enable_wdt_timeout      = _TRUE;
    flashToolDownloadArg.m_ms_wdt_timeout_interval = 5000;

    flashToolDownloadArg.m_relay_da_enable = _FALSE;
}

static void FillFlashToolDownloadResult(
                FLASHTOOL_DOWNLOAD_RESULT &flashToolDownloadResult)
{
    ::memset(&flashToolDownloadResult, 0, sizeof(flashToolDownloadResult));
}
#endif

/**
 * Take care of DA handle initialization and deinitialization
 */
class DAHandleInitializer : private NonCopyable
{
public:
    DAHandleInitializer(DA_HANDLE_T &daHandle,
                  const wstring &daFilePath)
        : m_DAHandle(daHandle)
    {
        USES_CONVERSION;

        DA_Create(&m_DAHandle);

        int ret = DA_Load(m_DAHandle, W2CA(daFilePath.c_str()), _FALSE, _FALSE);

        if (ret != S_DONE)
        {
            DA_Unload(m_DAHandle);
            DA_Destroy(&m_DAHandle);
            // throw exception
            throw std::runtime_error(string("DA_Load() failed. ")
                    .append(__FILE__).append(", ").append(__FUNC__));
        }
    }

    ~DAHandleInitializer()
    {
        DA_Unload(m_DAHandle);
        DA_Destroy(&m_DAHandle);
    }

private:
    DA_HANDLE_T &m_DAHandle;
};

/**
 * Take care of AUTH handle initialization and deinitialization
 */
class AuthHandleInitializer : private NonCopyable
{
public:
    AuthHandleInitializer(AUTH_HANDLE_T &authHandle,
                  const wstring &authFilePath)
        : m_AuthHandle(authHandle)
    {
        USES_CONVERSION;

        AUTH_Create(&m_AuthHandle);

        int ret = AUTH_Load(m_AuthHandle, W2CA(authFilePath.c_str()));

        if (ret != S_DONE)
        {
            AUTH_Unload(m_AuthHandle);
            AUTH_Destroy(&m_AuthHandle);
            // throw exception
            throw std::runtime_error(string("AUTH_Load() failed. ")
                    .append(__FILE__).append(", ").append(__FUNC__));
        }
    }

    ~AuthHandleInitializer()
    {
        AUTH_Unload(m_AuthHandle);
        AUTH_Destroy(&m_AuthHandle);
    }

private:
    AUTH_HANDLE_T &m_AuthHandle;
};

/**
 * Take care of SCERT handle initialization and deinitialization
 */
class ScertHandleInitializer : private NonCopyable
{
public:
    ScertHandleInitializer(SCERT_HANDLE_T &scertHandle,
                  const wstring &scertFilePath)
        : m_ScertHandle(scertHandle)
    {
        USES_CONVERSION;

        SCERT_Create(&m_ScertHandle);

        int ret = SCERT_Load(m_ScertHandle, W2CA(scertFilePath.c_str()));

        if (ret != S_DONE)
        {
            SCERT_Unload(m_ScertHandle);
            SCERT_Destroy(&m_ScertHandle);
            // throw exception
            throw std::runtime_error(string("SCERT_Load() failed. ")
                    .append(__FILE__).append(", ").append(__FUNC__));
        }
    }

    ~ScertHandleInitializer()
    {
        SCERT_Unload(m_ScertHandle);
        SCERT_Destroy(&m_ScertHandle);
    }

private:
    SCERT_HANDLE_T &m_ScertHandle;
};

/**
 * Take care of download handle initialization and deinitialization
 */
class DownloadHandleInitializer : private NonCopyable
{
public:
    DownloadHandleInitializer(DL_HANDLE_T &downloadHandle,
                              const wstring &scatterFilePath,
                              /* const & */ vector<ConsoleMode::DownloadSetting::Download_Item> downloadList);

    ~DownloadHandleInitializer();

	bool IsLoaded() const { return m_bLoaded; }

private:
    DL_HANDLE_T &m_DownloadHandle;
	bool m_bLoaded;
};

/**
** DownloadHandleInitializer implemetation
**/
DownloadHandleInitializer::DownloadHandleInitializer(
                                DL_HANDLE_T &downloadHandle,
                                const wstring &scatterFilePath,
                                /* const & */ vector<DownloadSetting::Download_Item> downloadList)
    : m_DownloadHandle(downloadHandle)
{
    USES_CONVERSION;

    int ret;

    ret = DL_Create(&m_DownloadHandle);

    if ( ret != S_DONE )
    {
       throw std::runtime_error(string("DL_Create() failed. ")
    		   .append(__FILE__).append(", ").append(__FUNC__));
    }

    g_pCurNode->m_dl_handle = m_DownloadHandle;

    ret = DL_LoadScatter(m_DownloadHandle,
                             W2CA(scatterFilePath.c_str()),
                             g_platform_info.getLoadPlatformName().c_str());
    if (ret != S_DONE)
    {
        DL_Rom_UnloadAll(m_DownloadHandle);
        DL_Destroy(&m_DownloadHandle);
        // throw exception
        throw std::runtime_error(string("DL_LoadScatter() failed: ")
        		.append(W2CA(scatterFilePath.c_str())).append("\n")
        		.append(__FILE__).append(", ").append(__FUNC__));
    }

    /* Adapt new storage layout file, 2012/12/22 { */
    std::string error_msg;
    DL_PlatformInfo plat_info;
    DL_GetPlatformInfo(g_DL_HANDLE_NODE.m_dl_handle, &plat_info);
    g_platform_info.InitByPlatCfgInfo(plat_info, error_msg, false);
    /* Adapt new storage layout file, 2012/12/22 } */

    //get BMT block count from DL handle, this is a MUST before download.
	unsigned int bmt_block_count = 0;
	if ( S_DONE != ( ret = DL_GetBMTBlockCount(m_DownloadHandle, &bmt_block_count)) ) {
		LOGW("Warning: DownloadHandleInitializer: Get BMT block count failed, default BMT block count is used!");
        g_platform_info.setBMTBlocks(PlatformInfo::DEFAULT_BMT_BLOCKS_MT6573);
		//throw std::runtime_error(string("DL_GetBMTBlockCount() failed! ")
		//        		.append(__FILE__).append(", ").append(__FUNC__));
	} else {
		g_platform_info.setBMTBlocks(bmt_block_count);
		LOG("DownloadHandleInitializer: Get BMT block count is %d.", bmt_block_count);
	}


    unsigned short numRoms;

    ret = DL_GetCount(m_DownloadHandle, &numRoms);

    if (ret != S_DONE)
    {
        DL_Rom_UnloadAll(m_DownloadHandle);
        DL_Destroy(&m_DownloadHandle);
        // throw exception
        throw std::runtime_error(string("DL_GetCount() failed.")
        		.append(__FILE__).append(", ").append(__FUNC__));
    }

    ROM_INFO romInfo[MAX_LOAD_SECTIONS];

    ret = DL_Rom_GetInfoAll(m_DownloadHandle, romInfo, MAX_LOAD_SECTIONS);

    if (ret != S_DONE)
    {
        DL_Rom_UnloadAll(m_DownloadHandle);
        DL_Destroy(&m_DownloadHandle);
        // throw exception
        throw std::runtime_error(string("DL_Rom_GetInfoAll() failed.")
        		.append(__FILE__).append(", ").append(__FUNC__));
    }


    for (unsigned short i=0; i<numRoms; ++i)
    {
        /*const vector<wstring>::iterator result = find(downloadList.begin(),
                                                      downloadList.end(),
                                                      wstring(A2CW(romInfo[i].name)));*/

        vector<DownloadSetting::Download_Item>::iterator result = downloadList.begin();

        for( ; ; result++)
        {
            if(downloadList.end() == result)
                break;

            if(A2CW(romInfo[i].name) == result->name)
                break;
        }

        const bool romEnabled = (result != downloadList.end());

        if(romEnabled){
            ret = DL_Rom_Load(m_DownloadHandle, i, W2CA(result->path.c_str()));
            LOGI(string("DL_Rom_Load for ").append(W2CA(result->path.c_str())).c_str());

            if(S_DONE != ret){
                DL_Rom_UnloadAll(m_DownloadHandle);
                DL_Destroy(&m_DownloadHandle);
                throw std::runtime_error(string("DL_Rom_Load() failed for ")
                    .append(W2CA(result->path.c_str())).append(__FILE__).append(", ").append(__FUNC__));
                break;
            } 

            ret = DL_Rom_SetEnableAttr(m_DownloadHandle, i, (romEnabled ? _TRUE : _FALSE));

            if (ret != S_DONE)
           {
                DL_Rom_UnloadAll(m_DownloadHandle);
                DL_Destroy(&m_DownloadHandle);
               // throw exception
                throw std::runtime_error(string("DL_Rom_SetEnableAttr() failed. ")
            		   .append(__FILE__).append(", ").append(__FUNC__));
          }
      }
    }

    ret = DL_Rom_GetInfoAll(m_DownloadHandle, romInfo, MAX_LOAD_SECTIONS);

    if (ret != S_DONE)
    {
        DL_Rom_UnloadAll(m_DownloadHandle);
        DL_Destroy(&m_DownloadHandle);
        // throw exception
        throw std::runtime_error(string("DL_Rom_GetInfoAll() failed. ")
        		.append(__FILE__).append(", ").append(__FUNC__));
    }

    //******filling AndroidImageInfo Table******//
    GetAndroidImageInfoTable().Reset();
	for (int i=0; i<numRoms; i++)
	{
		ImageType imgType = GetImageMapRule().queryType(romInfo[i].name);
		ImageItem imgItem = GetImageMapRule().getImageItem(imgType);

		if(!imgItem.is_bootloader()) {
			AndroidImageInfo info;
			info.romIndex = i;
			info.type = static_cast<DM_IMG_TYPE>(imgType);
			info.format = static_cast<DM_IMG_FORMAT>(imgItem.eboot_format());
			info.filePath = romInfo[i].filepath;
            info.romName = romInfo[i].name;
			GetAndroidImageInfoTable().UpdateInfo(romInfo[i].name,info);
		}
	}
	//*******end of filling AndroiImageInfo Table******//


    for (unsigned short i=0; i<numRoms; ++i)
    {
    	Logger::GetLogger() << Logger::Info
               << "(" << (romInfo[i].enable ? "v" : "x") << ")"
               << romInfo[i].name << " ";
    }

    Logger::GetLogger() << endl;
	
	m_bLoaded = (S_DONE == ret);  //set m_bLoaded true if load succeed
	Logger::GetLogger()<<"DownloadHandleInitializer inited result: "<<
			(m_bLoaded?"succeed":"failed")<<endl;
}

DownloadHandleInitializer::~DownloadHandleInitializer()
{
	Logger::GetLogger()<<"Executing ~DownloadHandleInitializer..."<<endl;
	if(m_bLoaded){
		Logger::GetLogger()<<"Free DL Handle in ~DownloadHandleInitializer()..."<<endl;
		DL_Rom_UnloadAll(m_DownloadHandle);
		DL_Destroy(&m_DownloadHandle);
	}
	m_bLoaded = false;
}

int PrepareDLHandleCommand::Execute()
{
	Logger::GetLogger()<<"Executing PrepareDLHandleCommand..."<<endl;
    ConsoleModeData::DL_init_ptr.reset(new DownloadHandleInitializer(
                                    ConsoleModeData::downloadHandle,
                                    m_DownloadSetting.GetScatterFilePath(),
                                    m_DownloadSetting.GetDownloadList()));
									
    Logger::GetLogger()<<"PrepareDLHandleCommand Executed!"<<endl;
	return (ConsoleModeData::DL_init_ptr.get())->IsLoaded();
}

/**
 * Take care of download handle initialization and deinitialization
 */
class ReadbackHandleInitializer : private NonCopyable
{
public:
    ReadbackHandleInitializer(RB_HANDLE_T &rbHandle,
		vector<ConsoleMode::ReadbackSetting::Readback_Item> rbList,
		const ConsoleMode::ReadbackSetting& rbSetting);

    ~ReadbackHandleInitializer();

	bool IsInitRBHandleSuccess() const {
		return m_IsInitRBHandle;
	}

private:
    RB_HANDLE_T &m_ReadbackHandle;
	bool m_IsInitRBHandle;
};

/**
** ReadbackHandleInitializer implemetation
**/
ReadbackHandleInitializer::ReadbackHandleInitializer(
                                RB_HANDLE_T &rbHandle,
                                vector<ConsoleMode::ReadbackSetting::Readback_Item> rbList,
								const ConsoleMode::ReadbackSetting& rbSetting)
    : m_ReadbackHandle(rbHandle)
{
	USES_CONVERSION;
    int ret;

    ret = RB_Create(&m_ReadbackHandle);
    if ( ret != S_DONE ) {
       throw std::runtime_error(string("RB_Create() failed. ")
    		   .append(__FILE__).append(", ").append(__FUNC__));
    }

	try {
		vector<ConsoleMode::ReadbackSetting::Readback_Item>::iterator it = rbList.begin();
		for(unsigned int i = 0; i < rbSetting.GetReadbackList().size(); i++, it++) {
            //RB_Append should be invoked at the very beginning
			ret = RB_Append(m_ReadbackHandle, W2A(it->GetReadbackPath().c_str()), 
				it->GetReadbackStartAddr(), it->GetReadbackLength());
			if (ret != S_DONE) {
				throw std::runtime_error(string("RB_Append() failed. Readback index: ")
					.append(NumberToString(it->GetReadbackIndex())
					.append(", ").append(__FILE__).append(". ").append(__FUNC__)));
			}

			ret = RB_SetEnableAttr(m_ReadbackHandle, it->GetReadbackIndex(), 
				(it->GetReadbackEnable() ? _TRUE : _FALSE));
			if (ret != S_DONE) {
				throw std::runtime_error(string("RB_SetEnableAttr() failed. Readback index: ")
					.append(NumberToString(it->GetReadbackIndex())
					.append(", ").append(__FILE__).append(". ").append(__FUNC__)));
			}

			ret = RB_SetReadbackFlag(m_ReadbackHandle, it->GetReadbackIndex(), 
				it->GetReadbackFlag());
			if (ret != S_DONE) {
				throw std::runtime_error(string("RB_SetReadbackFlag() failed. Readback index: ")
					.append(NumberToString(it->GetReadbackIndex())
					.append(", ").append(__FILE__).append(". ").append(__FUNC__)));
			}

			ret = RB_SetReadbackAddr(m_ReadbackHandle, it->GetReadbackIndex(),
				it->GetReadbackStartAddr());
			if (ret != S_DONE) {
				throw std::runtime_error(string("RB_SetReadbackAddr() failed. Readback index: ")
					.append(NumberToString(it->GetReadbackIndex())
					.append(", ").append(__FILE__).append(". ").append(__FUNC__)));
			}

			ret = RB_SetReadbackLength(m_ReadbackHandle, it->GetReadbackIndex(),
				it->GetReadbackLength());
			if (ret != S_DONE) {
				throw std::runtime_error(string("RB_SetReadbackLength() failed. Readback index: ")
					.append(NumberToString(it->GetReadbackIndex())
					.append(", ").append(__FILE__).append(". ").append(__FUNC__)));
			}

			ret = RB_SetAddrTypeFlag(m_ReadbackHandle, it->GetReadbackIndex(),
				rbSetting.IsPhysicalReadbackEnabled() ? NUTL_ADDR_PHYSICAL : NUTL_ADDR_LOGICAL);

			if (ret != S_DONE) {
				throw std::runtime_error(string("RB_SetAddrTypeFlag() failed. Readback index: ")
					.append(NumberToString(it->GetReadbackIndex())
					.append(", ").append(__FILE__).append(". ").append(__FUNC__)));
			} else {
				Logger::GetLogger() << Logger::Info
					<< "Readback Rom index: " << NumberToString(it->GetReadbackIndex())
					<< ", Addr_type: "<<(rbSetting.IsPhysicalReadbackEnabled() ? "NUTL_ADDR_PHYSICAL" : "NUTL_ADDR_LOGICAL")
					<< endl;			
			}

		}

	} catch(std::runtime_error e) {
		RB_ClearAll(m_ReadbackHandle);
		RB_Destroy(&m_ReadbackHandle);
        m_IsInitRBHandle = false;
		Logger::GetLogger()<<Logger::Info
			<< "ReadbackHandleInitializer initializer failed!"<< endl;
		throw std::runtime_error(e.what());
    } catch(...)  {
		RB_ClearAll(m_ReadbackHandle);
		RB_Destroy(&m_ReadbackHandle);
		m_IsInitRBHandle = false;
		Logger::GetLogger()<<Logger::Info
			<< "ReadbackHandleInitializer initializer failed!"<< endl;
		throw std::runtime_error(string("Readback failed!").append(__FILE__).append(", ").append(__FUNC__));
	}

	//set m_IsInitRBHandle true if intialize Readback handle succeed
	m_IsInitRBHandle = (S_DONE == ret); 
	Logger::GetLogger()<<Logger::Info
		<<"ReadbackHandleInitializer inited result: "
		<<(m_IsInitRBHandle?"succeed":"failed")<<endl;
}

ReadbackHandleInitializer::~ReadbackHandleInitializer()
{
	//Logger::GetLogger()<<"Executing ~ReadbackHandleInitializer..."<<endl;
	if(m_IsInitRBHandle){
		//Logger::GetLogger()<<"Free Readback Handle in ~ReadbackHandleInitializer()..."<<endl;
		RB_ClearAll(m_ReadbackHandle);
		RB_Destroy(&m_ReadbackHandle);
	}
	m_IsInitRBHandle = false;
}

/*Commands*/
DownloadCommand::DownloadCommand(const GeneralSetting  &generalSetting,
                                 const DownloadSetting &downloadSetting)
    : m_GeneralSetting(generalSetting),
      m_DownloadSetting(downloadSetting)
{
}

DownloadCommand::~DownloadCommand()
{
}

extern int __stdcall enum_wceusb_port(void *usr_arg);


void __stdcall command_lien_set_send_image_file_info(void *usr_arg, const char * file_type, unsigned int num_send, unsigned int total)
{
	Logger::GetLogger() << Logger::Info << "Begin download: " << file_type
          << "   ["   <<  num_send << " of " <<  total << "]  "
          << endl;
}

void __stdcall command_lien_show_dl_percentage(void *usr_arg, unsigned int percentage)
{
    static unsigned int lastPercentage = 0;	
	if ( (lastPercentage != percentage) &&
		(percentage%10 == 0) ) {
    	Logger::GetLogger() << Logger::Info << percentage << "%"  << endl;
			lastPercentage = percentage;
}
}

int DownloadCommand::DLYuSuFlashBin( void )
{
    EBOOT_RESULT ret;

    Android_Boot_ARG             boot_arg;
    Android_Download_ARG         dl_arg;
    string  s_com_str;
    string  s_port_str;
    int s_com_port = 0;
    time_t   start, finish;
    std::set<string> exist_com_port_str;

	//Initilize USB Ports table
	FlashToolUSBTable usb_table = GetFlashToolUSBTable();
	FlashToolUSB usb_preloader;
	if ( !usb_table.QueryUSBItemByName(FlashToolUSB::PRELOADER_VCOM, usb_preloader) ) {
		LOG("ERROR:  DownloadCommand::DLYuSuFlashBin(): QueryUSBItemByName(): (%s) failed!",
			FlashToolUSB::PRELOADER_VCOM.c_str());
	} else {
		LOG(" DownloadCommand::DLYuSuFlashBin(): QueryUSBItemByName(): Name(%s), PID(%s), VID(%s)",
			usb_preloader.GetUSBName().c_str(),
			usb_preloader.GetUSBPID().c_str(),
			usb_preloader.GetUSBVID().c_str());
	}
    tboot_1::Restore_Rom_File();
    
	ErrorLookup::SetErrorCodeMode(FLASHTOOL);
    //Get start time
    time(&start);
    do
    {
        
		if(BOOT_STOP == g_stopflag)
        {
            LOGD("YuSu: User press stop button !");
            return ret= static_cast<EBOOT_RESULT> (FT_USER_PRESS_STOP_BUTTON);
        }
        else if( GetNewCreatedUSBVComPort( s_com_str,
                                           s_port_str,
                                           exist_com_port_str,
			usb_preloader.GetUSBPID(),
			usb_preloader.GetUSBVID())
                                                   )
        {
            //find usb_com port via MS DDK
            LOGD(string("Double scan: Find usb port: ").append(s_com_str).append("  ").append(s_port_str).c_str());
            break;
        }
        //Get current time
        time( &finish );
        
		const int PRELOADER_TIMEOUT = 30;
        //wait 10s if there still not found a new usb com port
        if(difftime( finish, start ) > PRELOADER_TIMEOUT /* 30s */)
        {
            LOG("Double scan: time out %ds passed, search usb port error!", PRELOADER_TIMEOUT);
            return FT_FIND_USB_ERROR;
        }
   }while(1);
   ErrorLookup::SetErrorCodeMode(EBOOT);

    unsigned int baudrate_tbl[] = { 0, 921600, 460800, 230400, 115200, 57600, 38400, 19200, 9600, 4800, 2400, 1200, 300, 110 };
    // Boot As Download Mode
    boot_arg.m_baud_rate  = (COMM_BAUDRATE)baudrate_tbl[BAUD_RATE];
    boot_arg.m_comport    = 1;
    boot_arg.m_p_comsymbol= (char*)s_com_str.c_str();
    boot_arg.m_p_stopflag = &g_stopflag;
    boot_arg.m_p_thread   = this;


    // Download Image
    memcpy(&dl_arg.m_image_files, &g_android_image_files,
          ANDROID_IMAGE_FILE_NUMBER*sizeof(Android_Image_File));
    //dl_arg.m_auth_file.is_download= false;   //disable auth verify

    dl_arg.usb_com                      = s_com_port;;
    dl_arg.m_p_stopflag                 = &g_stopflag;
    dl_arg.m_p_thread                   = this;
    dl_arg.m_p_send_flash_percentage    = command_lien_show_dl_percentage;
    dl_arg.m_p_send_image_file_status   = command_lien_set_send_image_file_info;
    dl_arg.reboot_mode = AUTOBOOT;
    dl_arg.is_verify = false;
    //For new scatter file image size check
    dl_arg.is_boundary_Check = IsNewScatterFileWithBoundaryCheck(g_pCurNode->m_dl_handle);
    //Fill image region info for partition check
    FillAndroidImageRegionInfo(g_pCurNode->m_dl_handle, dl_arg.m_region_info, dl_arg.m_region_num);

    LOGD(string("[Download_Android_Images] Is to do image boundary check: ")
    		.append((true == dl_arg.is_boundary_Check) ? "Y" : "N").c_str());
    
    ret = Android_Flash_Download(boot_arg, &dl_arg);

    if(EBOOT_SUCCESS != ret)
    {
        LOGD("Download Android Images fails!");
        return ret;
    }

    return S_DONE;
}
#if 0
int DownloadCommand::DLFlashBin( void )
{
 //   int ret = S_DONE;
    int stopFlag;

    const wstring comPort = m_GeneralSetting.GetComPort();

     FT_Download_ARG arg;
     arg.m_binfile= TStringConverter<TCHAR>::WideToAnsi(m_GeneralSetting.GetFlashBinFilePath().c_str());
     arg.m_p_baud = BAUD115200;
     arg.m_p_stopflag = &stopFlag;
     arg.m_p_comport  = _wtoi(comPort.c_str());
     arg.m_p_ft_send_flash_percentage = NULL;
     EBOOT_RESULT result;
     if(EBOOT_SUCCESS!=(result=SP_Flash_Download(arg)))
    {
    	 Logger::GetLogger() << Logger::Info << "Download Flash.Bin file fail" << endl;
       return result;
    }
    return S_DONE;
}
#endif

int DownloadCommand::Execute()
{
    ErrorLookup::SetErrorCodeMode(BROM);

    USES_CONVERSION;

    Logger::GetLogger() << Logger::Info << "MTK Platform: " << g_platform_info.getLoadPlatformName() <<endl;

    Logger::GetLogger() << Logger::Info
           << __FUNC__ << endl;

    COM_PORT_SETTING comPortSetting;

    FillComPortSetting(comPortSetting, m_GeneralSetting);
    
	//Handles Initializers
    DA_HANDLE_T daHandle;
    DAHandleInitializer daHandleInitiailzer(
                    daHandle, m_GeneralSetting.GetDownloadAgentFilePath());

	const wstring authFilePath(m_GeneralSetting.GetAuthenticationFilePath());
	const wstring scertFilePath(m_GeneralSetting.GetSCertFilePath());
    AUTH_HANDLE_T authHandle = NULL;
	SCERT_HANDLE_T scertHandle = NULL;
	if (!authFilePath.empty()) {
		AuthHandleInitializer authHandleInitializer(authHandle, authFilePath);
	}
	if (!scertFilePath.empty()) {
		ScertHandleInitializer scertHandleInitializer(scertHandle, scertFilePath);
	}

#if 0
    FLASHTOOL_ARG flashToolArg;
    FillFlashToolArg(flashToolArg, daHandle, authHandle, scertHandle);

    Logger::GetLogger().Log(Logger::Info,
    		"Console Mode: FLASHTOOL_DOWNLOAD, FLASHTOOL_ARG time out %u ms.",
            flashToolArg.m_boot_arg.m_ms_boot_timeout);

    FLASHTOOL_RESULT flashToolResult;
    FillFlashToolResult(flashToolResult);

/*     DL_HANDLE_T downloadHandle;
    DownloadHandleInitializer downloadHandleInitializer(
                                    downloadHandle,
                                    m_DownloadSetting.GetScatterFilePath(),
                                    m_DownloadSetting.GetDownloadList()); */

    FLASHTOOL_DOWNLOAD_ARG flashToolDownloadArg;
    FillFlashToolDownloadArg(flashToolDownloadArg,
                             ConsoleModeData::downloadHandle,
                             m_GeneralSetting.IsCheckBasebandVersionEnabled(),
                             m_DownloadSetting,
                             m_GeneralSetting);


    vector<DownloadSetting::Download_Item> downloadList(m_DownloadSetting.GetDownloadList());

    vector<DownloadSetting::Download_Item>::iterator result = downloadList.begin();

    for(; ; result++)
    {
        if(result == downloadList.end())
                break;

        if((*result).name == L"SECURE_RO")
                break;
    }

    if (result != downloadList.end())
    {
        const wstring scatterFilePath = m_DownloadSetting.GetScatterFilePath();
        const AnsiString secROFilePath =
                ExtractFileDir(W2CA(scatterFilePath.c_str())) + "\\SECURE_RO";

        if (FileExists(secROFilePath))
        {
            flashToolDownloadArg.m_sec_ro_enable = _TRUE;
            flashToolDownloadArg.m_sec_ro.m_len =
            		FileUtils::GetFileSize(secROFilePath.c_str());

            // FIXME: memory leak
            flashToolDownloadArg.m_sec_ro.m_data =
            		FileUtils::GetFileContent(secROFilePath.c_str());
        }
    }

    FLASHTOOL_DOWNLOAD_RESULT flashToolDownloadResult;
    FillFlashToolDownloadResult(flashToolDownloadResult);

#endif

	//Check image buffer checksums
	std::string error_msg;
	DownloadImageChecksum dl_img_checksum;

       RomMemChecksumArg chksum_arg;
	RomMemChecksumResult chksum_res;

	memset(&chksum_arg, 0, sizeof(chksum_arg));
	memset(&chksum_res, 0, sizeof(chksum_res));

	chksum_arg.m_cb_rom_mem_checksum = cb_rom_mem_checksum;
	chksum_arg.m_cb_rom_mem_checksum_init = cb_rom_mem_checksum_init;
	chksum_arg.m_cb_rom_mem_checksum_arg = this;
	chksum_arg.m_cb_rom_mem_checksum_init_arg = this;
	
	if (dl_img_checksum.is_do_checksum() && dl_img_checksum.is_checksum_file_ready()) {
		if (!VerifyDLImagesBuffer(g_DL_HANDLE_NODE.m_dl_handle, error_msg, chksum_arg, chksum_res)) {
			ShowMessage(error_msg.c_str());
			return 8;
		}
	}
	
	int stopFlag(0);
    if (comPortSetting.com.number == 0)
    {
        // Search for a newly created COM port
      if(m_GeneralSetting.GetComPort() == L"USB")
    	{
    	   LOGD("Search for a newly created COM port");
    	Logger::GetLogger() << Logger::Info
               << "Searching for newly created USB COM port" << endl;
        unsigned char new_com_port_num = 0;
        const int kTimeout = 30;
		std::string symbolic_name;
		std::string friendly_name;
		if (!ScanUSBPort4DownloadDA(&stopFlag, symbolic_name, friendly_name, true, kTimeout)) {
			Logger::GetLogger() << Logger::Error
                   << "Download failed: no USB COM port detected in "
                   << kTimeout << "s" << endl;
            return false;
		} else {
			new_com_port_num = GetUSBVCOMNumByPortName(friendly_name);
        Logger::GetLogger() << Logger::Info
               << "USB COM port detected: COM" << new_com_port_num << endl;
		}
        comPortSetting.com.number = new_com_port_num;
        //flashToolArg.m_boot_arg.m_usb_enable = _TRUE;
    }

	 if(m_GeneralSetting.GetPortType() == L"USB")
	 {
            LOGD("Search USB port by port name.");

	     comPortSetting.com.number = ::_wtoi(m_GeneralSetting.GetComPort().c_str());
	     LOGD("Wait for COM%d...", comPortSetting.com.number);
			
	      Logger::GetLogger() << Logger::Info
               << "Searching for newly created USB COM port by COM Number" << endl;
             unsigned char new_com_port_num = 0;
             const int kTimeout = 30;
		if (!ScanUSBPortByCOMNum(&stopFlag, comPortSetting.com.number, kTimeout)) {
			Logger::GetLogger() << Logger::Error
                   << "Download failed: no USB COM port detected in "
                   << kTimeout << "s" << endl;
               return false;
		} else {
                   Logger::GetLogger() << Logger::Info
                         << "USB COM port detected: COM" << comPortSetting.com.number << endl;
		}
	 }
    }

    int ret = S_DONE;
	if (!m_DownloadSetting.IsDADownloadAll()) {
		if(L"Android" == m_DownloadSetting.GetDLOS())
		{
			bool is_need_dl_uboot, is_need_dl_image;

#if 0
			flashToolDownloadArg.m_otp_op = OTP_WRITE;
#endif

			tboot_1::Remove_Other_Rom_File(is_need_dl_uboot, is_need_dl_image);
		}
	}
#if 0
    Logger::GetLogger().Log(Logger::Info, "Console Mode: FLASHTOOL_DOWNLOAD, FLASHTOOL_ARG time out %u.",
            flashToolArg.m_boot_arg.m_ms_boot_timeout);
    Logger::GetLogger().Log(Logger::Info,"Watchdog timer enabled: %s",
        (_TRUE == flashToolDownloadArg.m_enable_wdt_timeout) ? "YES" :"NO");
    Logger::GetLogger().Log(Logger::Info, "Watchdog timer interval: %u ms",
        flashToolDownloadArg.m_ms_wdt_timeout_interval);
#endif

   //add for da-download-with-chksum
   bool b_enable_chksum = m_DownloadSetting.IsDADownloadAllWithChksum();
   LOG("%s(): set DL_SetChecksumEnable(%s).", __FUNC__, b_enable_chksum ? "True" : "False");
   ret = DL_SetChecksumEnable(ConsoleModeData::downloadHandle, b_enable_chksum);
   if (S_DONE != ret) {
	LOG("ERROR: %s(): DL_SetChecksumEnable() failed, error code(%d).", __FUNC__, ret);
	Logger::GetLogger() << Logger::Error
            << "set DL_SetChecksumEnable() failed: " << ErrorLookup::GetErrorMessage(ret) << endl;
	return false;
   }
	
    
    if(L"dl-all" == m_DownloadSetting.GetDLOperation())
    {

    	Logger::GetLogger() << Logger::Info
               << "Begin download Stage1 ... ... "  << endl;

#if 0
        // DL mloader & Eboot
        ret   = FlashDownload(&comPortSetting,
                              &flashToolArg,
                              &flashToolResult,
                              &flashToolDownloadArg,
                              &flashToolDownloadResult,
                              NULL,
                              &stopFlag);
#endif

        FLASHTOOL_API_HANDLE_T ft_handle;
        FlashTool_Connect_Arg ftConnect;
		FlashTool_Connect_Result ftConnectResult;
		FillFlashToolConnectArg(ftConnect,ftConnectResult,daHandle,authHandle,scertHandle);

		FlashTool_Download_Arg fdl_arg;
		FlashTool_Download_Result fdl_res;

		
	      FlashTool_USB_Status_Arg usb_status_arg;
	      FlashTool_USB_Status_Result usb_status_result;
            FillUSBStatusArg(usb_status_arg, usb_status_result);      

		//Huihui Test
		if(ConsoleModeData::downloadHandle == NULL)
		{
		       Logger::GetLogger() << Logger::Info
			       << "downloadHandle has been killed."  << endl;
	       }
		else 
		{
		       Logger::GetLogger() << Logger::Info
			       << "downloadHandle is ok."  << endl;
	       }
		
		FillFlashToolAdvancedDownloadArg(fdl_arg,fdl_res,ConsoleModeData::downloadHandle);
	    
		FlashTool_EnableWDT_Arg wdt_arg;
        FlashTool_EnableWDT_Arg *p_wdt_arg = &wdt_arg;
        unsigned int uWatchDogTimeout = m_DownloadSetting.GetWatchdogInterval();
        FillFlashToolWatchDogArg(p_wdt_arg,uWatchDogTimeout);    
          
     	ret = FlashDownload_allInOne(
    			comPortSetting.com.number,
    			stopFlag,
    			ft_handle,
    			ftConnect,
    			ftConnectResult,
    			fdl_arg,
    			fdl_res,
				m_DownloadSetting.IsDADownloadAll(),
				m_DownloadSetting.IsDADownloadHighSpeed(),
				m_DownloadSetting.IsDADownloadWithoutBattery(),
				m_DownloadSetting.IsDADLAutoDetect(),
				usb_status_arg,
				usb_status_result,
				p_wdt_arg);
         
    }

	if(ret == S_DONE && !m_DownloadSetting.IsDADownloadAll())
	{
		if(L"Android" == m_DownloadSetting.GetDLOS())
		{
			Logger::GetLogger() << Logger::Info
				<< "Begin download Stage2 ... ... "  << endl;
			ret = DLYuSuFlashBin();
		}
#if 0   
		else // WM or null
		{
			//Remove code related to WinMobile 
			assert(0); //not supported

			if(ret == S_DONE)
			{
				ret = DLFlashBin();
			}

		}
#endif
	}

    if (ret == S_DONE) {
    	Logger::GetLogger() << Logger::Info
               << "Download succeeded." << endl;
        return true;
	} else {
    	Logger::GetLogger() << Logger::Error
            << "Download failed: " << ErrorLookup::GetErrorMessage(ret) << endl;
		return false;
	}

#if 0
    if(-1 == ret)
    {
    	Logger::GetLogger() << Logger::Error << "Download Flash.bin Error!";
    }
    else
    {
    	Logger::GetLogger() << Logger::Error
            << "Download failed: " << ErrorLookup::GetErrorMessage(ret) << endl;
    } 
#endif    
}

static int __stdcall FormatProgressInit(HW_StorageType_E  storage_type, unsigned long long begin_addr, unsigned long long length, void *usr_arg)
{
	Logger::GetLogger() << Logger::Info
           << "Formating Flash..." << endl;
	Logger::GetLogger() << "Format begin address: "
           << DumpHex(begin_addr)<<endl;
	Logger::GetLogger() << "Format length: "
           << DumpHex(length)<<endl;
	Logger::GetLogger() << dec;
    return 0;
}

static int __stdcall FormatProgressCallback(unsigned char finished_percentage, void *usr_arg)
{
	static unsigned char last_percentage = 0;

	if ( (finished_percentage != last_percentage) &&
		(finished_percentage % 10 == 0) ) {
    	Logger::GetLogger() << Logger::Info
               << (int) finished_percentage
               << "% of flash has been format." << endl;
			last_percentage = finished_percentage;
    }

    return 0;
}

static void FillFlashToolAdvancedFormatArg(FlashTool_Format_Arg &fmt_arg,
		FlashTool_Format_Result &fmt_res, const FormatSetting &formatSetting, const GeneralSetting &generalSetting)
{
	memset( &fmt_arg,    0, sizeof(fmt_arg));
	memset( &fmt_res, 0, sizeof(fmt_res));

	fmt_arg.m_storage_type = generalSetting.Get_flash_operation();

	if (formatSetting.IsAutoFormatEnabled())
	{
		//fmt_arg.m_format_cfg.m_auto_format_fat = _TRUE;
	}
	else if (formatSetting.IsManualFormatEnabled())
	{
		fmt_arg.m_format_cfg.m_auto_format_fat = _FALSE;
		fmt_arg.m_format_cfg.m_format_begin_addr =
								formatSetting.GetManualFormatBeginAddress();
		fmt_arg.m_format_cfg.m_format_length =
								formatSetting.GetManualFormatLength();
	}

	fmt_arg.m_cb_format_report_init     = FormatProgressInit;
	fmt_arg.m_cb_format_report_init_arg = NULL;
	fmt_arg.m_cb_format_report          = FormatProgressCallback;
	fmt_arg.m_cb_format_report_arg      = NULL;
	fmt_arg.m_cb_format_statistics      = NULL;
	fmt_arg.m_cb_format_statistics_arg  = NULL;
	fmt_arg.m_erase_flag                = NUTL_ERASE;
	fmt_arg.m_format_cfg.m_validation   = _FALSE;
	fmt_arg.m_format_cfg.m_AddrType = formatSetting.IsPhysicallyFormat() ? NUTL_ADDR_PHYSICAL : NUTL_ADDR_LOGICAL;
}

#if 0
static void FillFlashToolFormatArg(FLASHTOOL_FORMAT_ARG &flashToolFormatArg,
                                   const FormatSetting &formatSetting)
{
    ::memset(&flashToolFormatArg, 0, sizeof(flashToolFormatArg));

    flashToolFormatArg.m_storage_type = HW_STORAGE_NAND /*formatSetting.GetStorageType()*/;


    if (formatSetting.IsAutoFormatEnabled())
    {
        flashToolFormatArg.m_format_cfg.m_auto_format_fat = _TRUE;
    }
    else if (formatSetting.IsManualFormatEnabled())
    {
        flashToolFormatArg.m_format_cfg.m_auto_format_fat = _FALSE;
        flashToolFormatArg.m_format_cfg.m_format_begin_addr =
                                formatSetting.GetManualFormatBeginAddress();
        flashToolFormatArg.m_format_cfg.m_format_length =
                                formatSetting.GetManualFormatLength();
    }
    else
    {
        // error
    }

    flashToolFormatArg.m_cb_format_report_init     = FormatProgressInit;
    flashToolFormatArg.m_cb_format_report_init_arg = NULL;
    flashToolFormatArg.m_cb_format_report          = FormatProgressCallback;
    flashToolFormatArg.m_cb_format_report_arg      = NULL;
    flashToolFormatArg.m_cb_format_statistics      = NULL;
    flashToolFormatArg.m_cb_format_statistics_arg  = NULL;
    flashToolFormatArg.m_erase_flag                = NUTL_ERASE;
    flashToolFormatArg.m_format_cfg.m_validation   = _FALSE;

    //flashToolFormatArg.m_write_usb_download_control_bit = _FALSE;

    if (formatSetting.IsWatchdogTimerEnabled())
    {
    	Logger::GetLogger()<<__FUNC__<<" : "<<"Watchdog is enabled with "<<
    			formatSetting.GetWatchdogInterval()<< " ms."<<endl;
        flashToolFormatArg.m_enable_wdt_timeout      = _TRUE;
        flashToolFormatArg.m_ms_wdt_timeout_interval =
            formatSetting.GetWatchdogInterval() >= 5000 ?
            formatSetting.GetWatchdogInterval():
            5000;
    }
    else
    {
    	Logger::GetLogger()<<__FUNC__<<" : "<<"Watchdog is NOT enabled!"<<endl;
        flashToolFormatArg.m_enable_wdt_timeout      = _FALSE;
        flashToolFormatArg.m_ms_wdt_timeout_interval = 0;
    }
}

static void FillFlashToolFormatResult(
                    FLASHTOOL_FORMAT_RESULT &flashToolFormatResult)
{
    ::memset(&flashToolFormatResult, 0, sizeof(flashToolFormatResult));
}
#endif

FormatCommand::FormatCommand(const GeneralSetting &generalSetting,
                             const FormatSetting  &formatSetting)
    : m_GeneralSetting(generalSetting),
      m_FormatSetting(formatSetting)
{
}

FormatCommand::~FormatCommand()
{
}

int FormatCommand::Execute()
{
    ErrorLookup::SetErrorCodeMode(BROM);;
	Logger::GetLogger() << Logger::Info
           << __FUNC__ << endl;

    COM_PORT_SETTING comPortSetting;
    FillComPortSetting(comPortSetting, m_GeneralSetting);

    DA_HANDLE_T daHandle;
    DAHandleInitializer daHandleInitiailzer(
                    daHandle, m_GeneralSetting.GetDownloadAgentFilePath());

    const wstring authFilePath(m_GeneralSetting.GetAuthenticationFilePath());
	const wstring scertFilePath(m_GeneralSetting.GetSCertFilePath());
	AUTH_HANDLE_T authHandle = NULL;
	SCERT_HANDLE_T scertHandle = NULL;
	if ( !authFilePath.empty() ) {
	    AuthHandleInitializer authHandleInitializer(authHandle, authFilePath);
	}
	if ( !scertFilePath.empty() ) {
		ScertHandleInitializer scertHandleInitializer(scertHandle, scertFilePath);
	}

#if 0
    FLASHTOOL_ARG flashToolArg;
    FillFlashToolArg(flashToolArg, daHandle, authHandle, scertHandle);

    FLASHTOOL_RESULT flashToolResult;
    FillFlashToolResult(flashToolResult);

    FLASHTOOL_FORMAT_ARG flashToolFormatArg;
    FillFlashToolFormatArg(flashToolFormatArg, m_FormatSetting);

    FLASHTOOL_FORMAT_RESULT flashToolFormatResult;
    FillFlashToolFormatResult(flashToolFormatResult);

    Logger::GetLogger().Log(Logger::Info, "Watchdog timer enabled: %s", 
       (_TRUE == flashToolFormatArg.m_enable_wdt_timeout) ? "YES" :"NO");
    Logger::GetLogger().Log(Logger::Info, "Watchdog timer interval: %u ms",
        flashToolFormatArg.m_ms_wdt_timeout_interval);
    Logger::GetLogger().Log(Logger::Info, "Manual format begin address = %x, length = %x",
        flashToolFormatArg.m_format_cfg.m_format_begin_addr,
        flashToolFormatArg.m_format_cfg.m_format_length);
#endif
    
	int stopFlag(0);
    if (comPortSetting.com.number == 0)
    {
        // Search for a newly created COM port
      if(m_GeneralSetting.GetComPort() == L"USB")
    	{
    	   LOGD("Search for a newly created COM port");
    	Logger::GetLogger() << Logger::Info
               << "Searching for newly created USB COM port" << endl;
        unsigned char new_com_port_num = 0;
        const int kTimeout = 30;
		std::string symbolic_name;
		std::string friendly_name;
		if (!ScanUSBPort4DownloadDA(&stopFlag, symbolic_name, friendly_name, true, kTimeout)) {
			Logger::GetLogger() << Logger::Error
                   << "Download failed: no USB COM port detected in "
                   << kTimeout << "s" << endl;
            return false;
		} else {
			new_com_port_num = GetUSBVCOMNumByPortName(friendly_name);
        Logger::GetLogger() << Logger::Info
               << "USB COM port detected: COM" << new_com_port_num << endl;
		}
        comPortSetting.com.number = new_com_port_num;
        //flashToolArg.m_boot_arg.m_usb_enable = _TRUE;
    }

	 if(m_GeneralSetting.GetPortType() == L"USB")
	 {
            LOGD("Search USB port by port name.");
   
	     comPortSetting.com.number = ::_wtoi(m_GeneralSetting.GetComPort().c_str());
	     LOGD("Wait for COM%d...", comPortSetting.com.number);
			
	      Logger::GetLogger() << Logger::Info
               << "Searching for newly created USB COM port by COM Number" << endl;
             unsigned char new_com_port_num = 0;
             const int kTimeout = 30;
		if (!ScanUSBPortByCOMNum(&stopFlag, comPortSetting.com.number, kTimeout)) {
			Logger::GetLogger() << Logger::Error
                   << "Download failed: no USB COM port detected in "
                   << kTimeout << "s" << endl;
               return false;
		} else {
                   Logger::GetLogger() << Logger::Info
                         << "USB COM port detected: COM" << comPortSetting.com.number << endl;
		}
	 }
    }

   
#if 0
    const int ret = FlashFormat(&comPortSetting,
                                &flashToolArg,
                                &flashToolResult,
                                &flashToolFormatArg,
                                &flashToolFormatResult,
                                NULL,
                                &stopFlag);
#endif

    FLASHTOOL_API_HANDLE_T ft_handle;
	FlashTool_Connect_Arg ftConnect;
	FlashTool_Connect_Result ftConnectResult;
	FillFlashToolConnectArg(ftConnect,ftConnectResult,daHandle,authHandle,scertHandle);

	FlashTool_Format_Arg fmt_arg;
	FlashTool_Format_Result fmt_res;
	FillFlashToolAdvancedFormatArg(fmt_arg, fmt_res, m_FormatSetting, m_GeneralSetting);
		
	FlashTool_EnableWDT_Arg wdt_arg;
    FlashTool_EnableWDT_Arg *p_wdt_arg = &wdt_arg;
    unsigned int uWatchDogTimeout = 15000;//m_FormatSetting.GetWatchdogInterval();
    FillFlashToolWatchDogArg(p_wdt_arg,uWatchDogTimeout);
	int ret = FlashFormat_allInOne(
			comPortSetting.com.number,
			stopFlag,
			ft_handle,
			ftConnect,
			ftConnectResult,
			fmt_arg,
			fmt_res,
			m_FormatSetting.GetAutoFormatFlag(),
			m_FormatSetting.IsAutoFormatEnabled(),
			m_FormatSetting.IsWatchdogTimerEnabled(),
			false,
			(!ToolInfo::IsCustomerVer()),
			p_wdt_arg);


    if (ret == S_DONE)
    {
    	Logger::GetLogger() << Logger::Info
               << "Format succeeded." << endl;

        if( L"USB" == m_GeneralSetting.GetComPort()){
            LOGD("USB DL DA: Sleep 10s to avoid conflict with target waiting for reset.");
            //Sleep(10000);
            LOGD("USB DL DA: Sleep (%d)s to avoid conflict with target waiting for reset.", m_GeneralSetting.GetSleepTime());
           // Sleep(m_GeneralSetting.GetSleepTime());
        }
        return true;
    }

    Logger::GetLogger() << Logger::Info
        << "Format failed: " << ErrorLookup::GetErrorMessage(ret) << endl;
    return false;
}

static void FillMETAConnectReq(META_Connect_Req &connectReq,
                               const GeneralSetting &generalSetting,
                               AUTH_HANDLE_T &authHandle)
{
    static META_COMM_BAUDRATE allow_baudrate[11] =
    {
        META_BAUD115200,
        META_BAUD230400,
        META_BAUD460800,
        META_BAUD921600,
        META_BAUD_END,
        META_BAUD_END,
        META_BAUD_END,
        META_BAUD_END,
        META_BAUD_END,
        META_BAUD_END,
        META_BAUD_END
    };

    ::memset(&connectReq, 0, sizeof(connectReq));
    ::memcpy(connectReq.baudrate, allow_baudrate, sizeof(connectReq.baudrate));

    const wstring comPort = generalSetting.GetComPort();

    connectReq.com_port =
            (comPort == L"USB") ? 0 : ::_wtoi(comPort.c_str());

    connectReq.flowctrl           = META_SW_FLOWCTRL;
    connectReq.ms_connect_timeout = 40000;

    connectReq.boot_meta_arg.m_bbchip_type = AUTO_DETECT_BBCHIP;
    connectReq.boot_meta_arg.m_ext_clock   = AUTO_DETECT_EXT_CLOCK;

    connectReq.boot_meta_arg.m_ms_boot_timeout = 30000;
    connectReq.boot_meta_arg.m_max_start_cmd_retry_count =
                                            DEFAULT_BROM_START_CMD_RETRY_COUNT;

    // This callback function will be invoke after COM port is opened
    // You can do some initialization by using this callback function.
    connectReq.boot_meta_arg.m_cb_com_init_stage     = COMPortOpenCallback;
    connectReq.boot_meta_arg.m_cb_com_init_stage_arg = NULL;

    // This callback function will be invoke after BootROM start cmd is passed.
    // You can issue other BootROM command by brom_handle and hCOM which provides callback arguments,
    // or do whatever you want otherwise.
    connectReq.boot_meta_arg.m_cb_in_brom_stage      = NULL;
    connectReq.boot_meta_arg.m_cb_in_brom_stage_arg  = NULL;

    // speed-up BootROM stage baudrate
    connectReq.boot_meta_arg.m_speedup_brom_baudrate = _TRUE;

    // WM_BROM_READY_TO_POWER_ON_TGT
    connectReq.boot_meta_arg.m_ready_power_on_wnd_handle = NULL;
    connectReq.boot_meta_arg.m_ready_power_on_wparam     = NULL;
    connectReq.boot_meta_arg.m_ready_power_on_lparam     = NULL;

    // serial link authentication arg
    connectReq.boot_meta_arg.m_auth_handle              = authHandle;
    connectReq.boot_meta_arg.m_cb_sla_challenge         = SLA_Challenge;
    connectReq.boot_meta_arg.m_cb_sla_challenge_arg     = NULL;
    connectReq.boot_meta_arg.m_cb_sla_challenge_end     = SLA_Challenge_END;
    connectReq.boot_meta_arg.m_cb_sla_challenge_end_arg = NULL;

    // Boot META, usb flag, msut to set false, since call the META_ConnectWithTarget() API
    connectReq.boot_meta_arg.m_usb_enable = _FALSE;
}

static void FillMETAConnectReport(META_Connect_Report &metaConnectReport)
{
    ::memset(&metaConnectReport, 0, sizeof(metaConnectReport));
}

static void FillMETAConnectByUSBReq(META_ConnectByUSB_Req &connectByUSBReq,
                                    const GeneralSetting &generalSetting,
                                    AUTH_HANDLE_T &authHandle)
{
    ::memset(&connectByUSBReq, 0, sizeof(connectByUSBReq));

    const wstring comPort = generalSetting.GetComPort();

    connectByUSBReq.com_port =
            (comPort == L"USB") ? 0 : ::_wtoi(comPort.c_str());

    connectByUSBReq.ms_connect_timeout = 40000;

    connectByUSBReq.boot_meta_arg.m_bbchip_type = AUTO_DETECT_BBCHIP;
    connectByUSBReq.boot_meta_arg.m_ext_clock   = AUTO_DETECT_EXT_CLOCK;

    connectByUSBReq.boot_meta_arg.m_ms_boot_timeout = 30000;
    connectByUSBReq.boot_meta_arg.m_max_start_cmd_retry_count =
                                            DEFAULT_BROM_START_CMD_RETRY_COUNT;

    // This callback function will be invoke after COM port is opened
    // You can do some initialization by using this callback function.
    connectByUSBReq.boot_meta_arg.m_cb_com_init_stage     = COMPortOpenCallback;
    connectByUSBReq.boot_meta_arg.m_cb_com_init_stage_arg = NULL;

    // This callback function will be invoke after BootROM start cmd is passed.
    // You can issue other BootROM command by brom_handle and hCOM which provides callback arguments,
    // or do whatever you want otherwise.
    connectByUSBReq.boot_meta_arg.m_cb_in_brom_stage      = NULL;
    connectByUSBReq.boot_meta_arg.m_cb_in_brom_stage_arg  = NULL;

    // speed-up BootROM stage baudrate
    connectByUSBReq.boot_meta_arg.m_speedup_brom_baudrate = _TRUE;

    // WM_BROM_READY_TO_POWER_ON_TGT
    connectByUSBReq.boot_meta_arg.m_ready_power_on_wnd_handle = NULL;
    connectByUSBReq.boot_meta_arg.m_ready_power_on_wparam     = NULL;
    connectByUSBReq.boot_meta_arg.m_ready_power_on_lparam     = NULL;

    // serial link authentication arg
    connectByUSBReq.boot_meta_arg.m_auth_handle              = authHandle;
    connectByUSBReq.boot_meta_arg.m_cb_sla_challenge         = SLA_Challenge;
    connectByUSBReq.boot_meta_arg.m_cb_sla_challenge_arg     = NULL;
    connectByUSBReq.boot_meta_arg.m_cb_sla_challenge_end     = SLA_Challenge_END;
    connectByUSBReq.boot_meta_arg.m_cb_sla_challenge_end_arg = NULL;

    // Boot META, usb flag, msut to set false, since call the META_ConnectWithTarget() API
    connectByUSBReq.boot_meta_arg.m_usb_enable = _TRUE;
}

static void FillMETAConnectByUSBReport(META_ConnectByUSB_Report &metaConnectReport)
{
    ::memset(&metaConnectReport, 0, sizeof(metaConnectReport));
}

static void FillMETAConnectInMETAReq(
                        META_ConnectInMETA_Req &metaConnectInMETAReq,
                        const GeneralSetting &generalSetting)
{
    static META_COMM_BAUDRATE allow_baudrate[11] =
    {
        META_BAUD115200,
        META_BAUD230400,
        META_BAUD460800,
        META_BAUD921600,
        META_BAUD_END,
        META_BAUD_END,
        META_BAUD_END,
        META_BAUD_END,
        META_BAUD_END,
        META_BAUD_END,
        META_BAUD_END
    };

    ::memset(&metaConnectInMETAReq, 0, sizeof(metaConnectInMETAReq));
    ::memcpy(metaConnectInMETAReq.baudrate,
             allow_baudrate,
             sizeof(metaConnectInMETAReq.baudrate));

    const wstring comPort = generalSetting.GetComPort();

    metaConnectInMETAReq.com_port =
            (comPort == L"USB") ? 0 : ::_wtoi(comPort.c_str());

    metaConnectInMETAReq.flowctrl           = META_SW_FLOWCTRL;
    metaConnectInMETAReq.ms_connect_timeout = 40000;
}

static void FillMETAConnectInMETAReport(
                    META_ConnectInMETA_Report &metaConnectInMETAReport)
{
    ::memset(&metaConnectInMETAReport, 0, sizeof(metaConnectInMETAReport));
}

ResetToFactoryDefaultCommand::ResetToFactoryDefaultCommand(
            const GeneralSetting &generalSetting,
            const ResetToFactoryDefaultSetting &resetToFactoryDefaultSetting)
    : m_GeneralSetting(generalSetting),
      m_ResetToFactoryDefaultSetting(resetToFactoryDefaultSetting)
{
}

ResetToFactoryDefaultCommand::~ResetToFactoryDefaultCommand()
{
}
                                
int ResetToFactoryDefaultCommand::Execute()
{
	Logger::GetLogger() << Logger::Info
           << __FUNC__ << endl;

    ErrorLookup::SetErrorCodeMode(META);
    if (m_ResetToFactoryDefaultSetting.ShouldReconnectToMETAMode())
    {
        META_ConnectInMETA_Req connectInMETAReq;
        FillMETAConnectInMETAReq(connectInMETAReq, m_GeneralSetting);

        META_ConnectInMETA_Report connectInMETAReport;
        FillMETAConnectInMETAReport(connectInMETAReport);

        int stopFlag;
        
        META_RESULT result = META_ConnectInMetaMode(&connectInMETAReq,
                                                    &stopFlag,
                                                    &connectInMETAReport);
        if (result != META_SUCCESS)
        {
        	Logger::GetLogger() << Logger::Info
                   << "[META] reconnect with META mode failed: "
                   << ErrorLookup::GetErrorMessage(result) << endl;
            return false;
        }
    }
    else
    {
        // FIXME
        const wstring authFilePath(m_GeneralSetting.GetAuthenticationFilePath());
        const bool authEnabled = !authFilePath.empty();
        AUTH_HANDLE_T authHandle = NULL;

        if (authEnabled)
        {
            USES_CONVERSION;
            AUTH_Create(&authHandle);
            AUTH_Load(authHandle, W2CA(authFilePath.c_str()));
        }

        META_RESULT result;

        if (m_GeneralSetting.GetComPort() == L"USB")
        {
            META_ConnectByUSB_Req connectReq;
            FillMETAConnectByUSBReq(connectReq, m_GeneralSetting, authHandle);

            META_ConnectByUSB_Report connectReport;
            FillMETAConnectByUSBReport(connectReport);

            //
            // Search for a newly created COM port
            //
            Logger::GetLogger() << Logger::Info
                   << "Searching for newly created USB COM port" << endl;

            unsigned short newCOMPortNum;

            if (!SearchNewlyCreatedCOMPort(newCOMPortNum))
            {
            	Logger::GetLogger() << Logger::Info
                       << "Download failed: no USB COM port detected" << endl;
                return false;
            }

            Logger::GetLogger() << Logger::Info
                   << "USB COM port detected: COM" << newCOMPortNum
                   << endl;

            connectReq.com_port = newCOMPortNum;

            int stopFlag;

            result = META_ConnectWithTargetByUSB(&connectReq,
                                                 &stopFlag,
                                                 &connectReport);
        }
        else
        {
            META_Connect_Req connectReq;
            FillMETAConnectReq(connectReq, m_GeneralSetting, authHandle);

            META_Connect_Report connectReport;
            FillMETAConnectReport(connectReport);

            int stopFlag;

            result = META_ConnectWithTarget(&connectReq,
                                            &stopFlag,
                                            &connectReport);
        }

        // FIXME
        if (authEnabled)
        {
            AUTH_Destroy(&authHandle);
        }

        if (result != META_SUCCESS)
        {
        	Logger::GetLogger() << Logger::Info
                   << "[META] connect with target failed: "
                   << ErrorLookup::GetErrorMessage(result) << endl;
            return false;
        }
    }

    const META_RESULT result = META_NVRAM_ResetToFactoryDefault(40000);

    META_DisconnectWithTarget();

    if (result == META_SUCCESS)
    {
    	Logger::GetLogger() << Logger::Info
               << "Reset-to-factory-default succeeded." << endl;
        return true;
    }

    Logger::GetLogger() << Logger::Info
           << "Reset-to-factory-default failed: "
           << ErrorLookup::GetErrorMessage(result) << endl;
    return false;
}

static void FillBackupReq(MISC_BACKUP_REQ_T &backupReq,
                          const char *iniFilePath,
                          const char *backupDirectoryPath)
{
    memset(&backupReq, 0, sizeof(backupReq));

    backupReq.m_pIniFilePath      = const_cast<char *>(iniFilePath);
    backupReq.m_pBackupFolderPath = const_cast<char *>(backupDirectoryPath);
    backupReq.cb_progress         = NULL;
    backupReq.cb_progress_arg     = NULL;
}

static void FillBackupResult(BACKUP_RESULT_T &backupResult)
{
    ::memset(&backupResult, 0, sizeof(backupResult));
}

BackupCommand::BackupCommand(const GeneralSetting &generalSetting,
                             const BackupSetting &backupSetting)
    : m_GeneralSetting(generalSetting),
      m_BackupSetting(backupSetting)
{
}

BT_WIFI_IMEI_NVRAMCommand::BT_WIFI_IMEI_NVRAMCommand(const GeneralSetting &generalSetting,
                             const Write_BT_WIFI_IMEI_NVRAM_Setting &setting)
    : m_GeneralSetting(generalSetting),
      m_setting(setting)
{
}

bool BT_WIFI_IMEI_NVRAMCommand::SP_BootAsMetaWrapper(int p_comport, int* p_BootStop)
{
     Meta_Boot_Arg meta_arg;
     meta_arg.read_retry_time = 0;		  // 0 means use default value 2400 times
     meta_arg.read_interval_timeout = 0;   // 0 means use default value 10 ms

     for(int i=0; i < 6 ; i++)
     {
        if(EBOOT_SUCCESS == SP_BootAsMeta(p_comport, BAUD115200, meta_arg))
        {
            return true;
        }
     }
     
     return false;
}

META_RESULT BT_WIFI_IMEI_NVRAMCommand::ArgMETAConnectWithTargetInMETA(  int com_port,
                                                                META_ConnectInMETA_Req  &META_ConnectInMETA_Req ,
                                                                META_ConnectInMETA_Report  &META_ConnectInMETA_Report)
{
    memset(&META_ConnectInMETA_Req,    0, sizeof(META_ConnectInMETA_Req));
    memset(&META_ConnectInMETA_Report, 0, sizeof(META_ConnectInMETA_Report));
    META_ConnectInMETA_Req.com_port = com_port;

    // set baud rate = AUTO
    META_ConnectInMETA_Req.baudrate[0] = META_BAUD57600;
    META_ConnectInMETA_Req.baudrate[1] = META_BAUD115200;
    META_ConnectInMETA_Req.baudrate[2] = META_BAUD230400;
    META_ConnectInMETA_Req.baudrate[3] = META_BAUD460800;
    META_ConnectInMETA_Req.baudrate[4] = META_BAUD921600;
    META_ConnectInMETA_Req.baudrate[5] = META_BAUD1500000;
    META_ConnectInMETA_Req.baudrate[6] = META_BAUD_END;
    META_ConnectInMETA_Req.flowctrl = META_SW_FLOWCTRL;

    META_ConnectInMETA_Req.ms_connect_timeout = 40000;
    return META_SUCCESS;
}

META_RESULT  BT_WIFI_IMEI_NVRAMCommand::ModemNVRAMInit( AnsiString database )
{
    char str[512];

    strcpy( str, database.c_str() );
    bool ok;

    unsigned long      m_ulNvramIdb;
    Variant            m_vNVRAM_db_variant;
    E_METAAPP_RESULT_T  m_eConfirmState;
    META_RESULT MetaResult = META_NVRAM_Init( str, &m_ulNvramIdb );

    return  MetaResult;
}

META_RESULT  BT_WIFI_IMEI_NVRAMCommand::ApNVRAMInit( const int meta_handle, AnsiString database )
{
    char str[512];

    strcpy( str, database.c_str() );

    unsigned long db;
    META_RESULT  META_Result = (META_RESULT)WM_META_NVRAM_Init_r_Wrapper (meta_handle, str, &db) ;

    return  META_Result;
}

inline char* UnicodeToAnsi( const wchar_t* szStr )
{
  int nLen = WideCharToMultiByte( CP_ACP, 0, szStr, -1, NULL, 0, NULL, NULL );
  if (nLen == 0)
  {
     return NULL;
  }
  char* pResult = new char[nLen];
  WideCharToMultiByte( CP_ACP, 0, szStr, -1, pResult, nLen, NULL, NULL );
  return pResult;
}

//---------------------------------------------------------------------------
static META_RESULT EnterMETASetCleanBootFlag_r( const int meta_handle )
{
	META_RESULT  META_Result;
    unsigned int ms_timeout = 60000;

    META_Result = (META_RESULT)WM_META_SetCleanBootFlag_r_Wrapper(meta_handle, ms_timeout);
    if(META_SUCCESS != META_Result)
    {
        LOGD("[SP META INFO]: Set Clean Boot Flag failed !");
        return META_Result;
    }
	return META_Result;
}
int  BT_WIFI_IMEI_NVRAMCommand::Execute()
{
    // boot smart phone as meta mode
    META_RESULT  META_Result;
    EBOOT_RESULT EBOOT_Result;
    int meta_handle;
    int stopFlag = 0;

    COM_PORT_SETTING comPortSetting;
    FillComPortSetting(comPortSetting, m_GeneralSetting);

    char * p_str;
    unsigned short com_number = comPortSetting.com.number;
    const unsigned int TIME_OUT = 15000;
    
    bool is_write_IMEI1 = false;
    bool is_write_IMEI2 = false;
    bool is_write_WiFi = false;
    bool is_write_BT = false;

    is_write_IMEI1 = (0 == m_setting.m_is_write_IMEI1.compare(L"true")) ? true : false;
    is_write_IMEI2 = (0 == m_setting.m_is_write_IMEI2.compare(L"true")) ? true : false;
    is_write_WiFi = (0 == m_setting.m_is_write_WiFi.compare(L"true")) ? true : false;
    is_write_BT = (0 == m_setting.m_is_write_BT.compare(L"true")) ? true : false;

    Logger::GetLogger() << Logger::Info
           << "[Cosole Mode: META] Write IMEI/BT/WiFi " << endl;

    Logger::GetLogger() << Logger::Info
           << "[Cosole Mode: META] Write IMEI for SIM1 : "
           << ((is_write_IMEI1) ? "Yes" : "No") << endl
           << "[Cosole Mode: META] Write IMEI for SIM2 : "
           << ((is_write_IMEI2) ? "Yes" : "No") << endl
           << "[Cosole Mode: META] Write WiFi : "
           << ((is_write_WiFi) ? "Yes" : "No") << endl
           << "[Cosole Mode: META] Write BT : "
           << ((is_write_BT) ? "Yes" : "No") << endl;



    if (comPortSetting.com.number == 0) {
        // Search for a newly created COM port
        Logger::GetLogger() << Logger::Info
               << "Searching for a newly created USB COM port by Pre-Loader..." << endl;

		//Initilize USB Ports table
		FlashToolUSBTable usb_table = GetFlashToolUSBTable();
		FlashToolUSB usb_preloader;
		if ( !usb_table.QueryUSBItemByName(FlashToolUSB::PRELOADER_VCOM, usb_preloader) ) {
			LOG("ERROR:  BT_WIFI_IMEI_NVRAMCommand::Execute()(): QueryUSBItemByName(): (%s) failed!",
				FlashToolUSB::PRELOADER_VCOM.c_str());
		} else {
			LOG(" DownloadCommand::DLYuSuFlashBinl(): QueryUSBItemByName(): Name(%s), PID(%s), VID(%s)",
				usb_preloader.GetUSBName().c_str(),
				usb_preloader.GetUSBPID().c_str(),
				usb_preloader.GetUSBVID().c_str());
		}

        if (!ScanNewCreateUSBVComPortWithTimeout(TIME_OUT, com_number, 
			usb_preloader.GetUSBPID(), usb_preloader.GetUSBVID())) {
            Logger::GetLogger() << Logger::Info
                   << "Entering USB META failed: no "
				   << usb_preloader.GetUSBName().c_str()
				   <<"port detected in "
                   << TIME_OUT/1000
                   << "s"
                   << endl;
            return false;
        } else {
            Logger::GetLogger() << Logger::Info
                   << "USB COM port detected: COM" << com_number << endl;
        }
        //flashToolArg.m_boot_arg.m_usb_enable = _TRUE;
    }

    Logger::GetLogger() << Logger::Info
                       << "Boot As META mode with COM" << com_number << endl;
    if( !SP_BootAsMetaWrapper(com_number, &stopFlag ) ) {
	 //SP do not boot into META
    	Logger::GetLogger() << Logger::Info
                << "[Cosole Mode: META] SmartPhone boot into META failed!" << endl;
         return false;
    } else {
        if (comPortSetting.com.number == 0) {
            // Search for a newly created COM port
            Logger::GetLogger() << Logger::Info
                   << "Searching for a newly created Gadget Serial USB port in META Mode..." << endl;  
			FlashToolUSBTable usb_table = GetFlashToolUSBTable();
			FlashToolUSB usb_gadget;
			if ( !usb_table.QueryUSBItemByName(FlashToolUSB::GADGET_VCOM, usb_gadget) ) {
				LOG("ERROR: ReadbackCommand::Execute(): QueryUSBItemByName(): (%s) failed!",
					FlashToolUSB::GADGET_VCOM.c_str());
				return false;
			}
            if (!ScanNewCreateUSBVComPortWithTimeout(TIME_OUT, com_number, 
				usb_gadget.GetUSBPID(), usb_gadget.GetUSBVID())) {
                Logger::GetLogger() << Logger::Info
                       << "Entering USB META failed: no Gadget Serial USB COM port detected in "
                       << TIME_OUT/1000
                       << "s"
                       << endl;
                return false;
            } else {
                Logger::GetLogger() << Logger::Info
                        << "USB COM port detected: COM" << com_number << endl;
            }
        }
    }

    Logger::GetLogger() << Logger::Info
           << "[Cosole Mode: META] SmartPhone boot into META succeed." << endl;
    // enter modem meta to write IMEI
    // connect with modem meta

    META_ConnectInMETA_Req     META_ConnectInMETA_Req;
    META_ConnectInMETA_Report  META_ConnectInMETA_Report;

    // fill META Connet with Target paprameter
    ArgMETAConnectWithTargetInMETA(com_number, META_ConnectInMETA_Req, META_ConnectInMETA_Report );
    // Wait 2s to try to connect modem META
    Sleep(2000);
    META_Result = META_ConnectInMetaMode(&META_ConnectInMETA_Req,
                                 &g_stopflag,
                                 &META_ConnectInMETA_Report);
    
    if(META_SUCCESS == META_Result)
    {
        Logger::GetLogger() << Logger::Info
            << "[Cosole Mode: META] Fill META Connet with Target paprameter is successful." << endl;
    }
    else
    {
        Logger::GetLogger() << Logger::Info
            << "[Cosole Mode: META] META_ConnectInMetaMode failed." << endl;
    }
    
    // initialize modem NVRAM with database file
    META_Result = ModemNVRAMInit(m_setting.m_asModem_Database.c_str());
    if( META_SUCCESS != META_Result )
    {

       META_DisconnectWithTarget();

        if (META_MAUI_DB_INCONSISTENT == META_Result )
        {
        	Logger::GetLogger() << Logger::Info
            << "[Cosole Mode: META] Execution Warning : NVRAM database file is inconsistent with target load!"
            << endl;
        }
        else
        {
        	Logger::GetLogger() << Logger::Info
            << "[Cosole Mode: META] Execution Failure : Initialize NVRAM database file!"
            << endl;
        }

       return false;
    }

    Logger::GetLogger() << Logger::Info
           << "[Cosole Mode: META] Initialize modem NVRAM with database file is successful." << endl;

    // get to know if support 2 IMEI
    int rid_num;
    bool m_b2ndIMEISupport = true;
    
    META_Result = META_NVRAM_GetRecNum("NVRAM_EF_IMEI_IMEISV_LID", &rid_num);
    if((META_SUCCESS != META_Result) || (1 == rid_num))
    {
        m_b2ndIMEISupport = false;
        LOGI("[Cosole Mode: META] Target does not support the second SIM.");       
    }
    else
    {
        LOGI("[Cosole Mode: META] Target supports the second SIM.");
    }    
  
    //prepare write IMEIs
    S_IMEI_T sIMEIdownload;
    char str[512];
    bool bWritetoBinReg;
    int RID;

    p_str =  UnicodeToAnsi(m_setting.m_asIMEI1_Number.c_str());
    strcpy(sIMEIdownload.c_imei[0], p_str);
    delete p_str;

    p_str =  UnicodeToAnsi(m_setting.m_asIMEI2_Number.c_str());
    strcpy(sIMEIdownload.c_imei[1], p_str);
    delete p_str;

    //write IMEI of SIM1
    if (is_write_IMEI1)
    {
        RID=1;
        META_Result = (META_RESULT)tboot_1::WriteIMEItoNVRAM(sIMEIdownload,RID,true);
        if (META_Result!=META_SUCCESS)
        {
    	    Logger::GetLogger() << Logger::Info
                << "[Cosole Mode: META] Execution Error : Write IMEI of SIM1 failed!"
                << endl;
            META_DisconnectWithTarget();
            return META_Result;
        }
        else
        {
            bWritetoBinReg = true;
        }
        
        if ( bWritetoBinReg )
        {
            bWritetoBinReg = false;
        Logger::GetLogger() << Logger::Info
               << "[Cosole Mode: META] Write IMEI of SIM1 successfully." << endl;
        }
    }
    else
    {
        LOGI("[Cosole Mode: META] User skips to write IMEI of SMI1.");
    }

    // write IMEI of SIM2
    if ( is_write_IMEI2 )
    {
        if ( m_b2ndIMEISupport)
        {
              RID=2;
              META_Result= (META_RESULT)tboot_1::WriteIMEItoNVRAM(sIMEIdownload,RID,true);
              if (META_Result!=META_SUCCESS)
             {
        	  Logger::GetLogger() << Logger::Info
                 <<"[Cosole Mode: META] Execution Error : Write IMEI of SIM2 failed!"
                 << endl;
                 META_DisconnectWithTarget();

                 return META_Result;
              }
              else
              {
                 bWritetoBinReg = true;
              }
        }
        else
        {
            LOGI("[Cosole Mode: META] Target does not support the second SIM."); 
        }
        if ( bWritetoBinReg )
        {
             //bWritetoBinReg = false;
    	Logger::GetLogger() << Logger::Info
                   << "[Cosole Mode: META] Write IMEI of SIM2 is successful." << endl;
        }
    }
    else
    {
        LOGI("[Cosole Mode: META] User skips to write IMEI of SMI2.");
    }
    
    // disconnect
    if(META_SUCCESS != META_DisconnectWithTarget())
    {
    	Logger::GetLogger() << Logger::Info <<"[Cosole Mode: META] META_DisconnectWithTarget failed!"<< endl;
        return false;
    }

    Logger::GetLogger() << Logger::Info
           << "[Cosole Mode: META] META_DisconnectWithTarget successfully." << endl;
    META_Deinit();

    //enter meta AP mode to write BT/WiFi
    if( META_SUCCESS != WM_META_GetAvailableHandle_Wrapper(&meta_handle) )
    {
        Logger::GetLogger() << Logger::Info <<"[Cosole Mode: META] WM_META_GetAvailableHandle failed!"<< endl;
        return false;
    }

    if(META_SUCCESS != WM_META_Init_r_Wrapper(meta_handle))
    {
        LOGI("[Cosole Mode: META] WM_META_Init failed!");
        return false;
    }

    META_Result = (META_RESULT)WM_META_ConnectInMetaMode_r_Wrapper(meta_handle, &g_stopflag, com_number);
    if( (META_SUCCESS != META_Result) && (META_MAUI_DB_INCONSISTENT != META_Result) )
    {
       // disconnect
        WM_META_DisconnectWithTarget_r_Wrapper(meta_handle);
        WM_META_Deinit_r_Wrapper(&meta_handle);
        //META_Init(NULL);
        Logger::GetLogger() << Logger::Info
        <<"[Cosole Mode: META] Execution Error : can not enter to meta AP mode!"<< endl;
        return false;
    }

    Logger::GetLogger() << Logger::Info
           << "[Cosole Mode: META] WM_META_ConnectInMetaMode_Wrapper is successful." << endl;

    // enter AP meta to write BT address
    if (is_write_BT)
    {
        Logger::GetLogger()  << Logger::Info
        <<"[Cosole Mode: META] Enter AP meta to write BT Address to smartphone AP nvram."
        << endl << "[Cosole Mode: META] Start to Init AP Nvram Database."
        << endl;
        // initialize AP NVRAM with database file
        META_Result = ApNVRAMInit(meta_handle, m_setting.m_asAP_Database.c_str());
        if( META_SUCCESS != META_Result)
        {
    	Logger::GetLogger() << Logger::Info <<"[Cosole Mode: META] Execution Failure : Initialize AP NVRAM database file "<< endl;
            goto clean;
        }

        Logger::GetLogger()  << Logger::Info
        <<"[Cosole Mode: META] Initialize AP Nvram Database successfully."
        << endl << "[Cosole Mode: META] Start to write BT address." << endl;

        //get BT address and write BT address
        if(m_setting.m_asBT_Address.length() == 0)
        {
    	Logger::GetLogger() << Logger::Info << "[Cosole Mode: META] BT address is empty!" << endl;
            return false;
        }

        p_str =  UnicodeToAnsi(m_setting.m_asBT_Address.c_str());
        META_Result = (META_RESULT)WriteBTtoNVRAM(p_str, meta_handle);
        delete p_str;

        if( META_SUCCESS != META_Result )
        {
    	Logger::GetLogger() << Logger::Info <<"[Cosole Mode: META] Write BT address failed!"<< endl;
            goto clean;
        }

        Logger::GetLogger() << Logger::Info
        <<"[Cosole Mode: META] Write BT Address and check successfully."<< endl;
    }
    else
    {
        LOGI("[Cosole Mode: META] User skips to write BT address.");
    }

     // enter AP meta to write WiFi address  
    if (is_write_WiFi)
    {
        Logger::GetLogger() << Logger::Info
        <<"[Cosole Mode: META] Start to write WiFi MAC." <<endl;
        if(m_setting.m_asWiFi_Address.length() == 0)
        {
    	    Logger::GetLogger() << Logger::Info << "[Cosole Mode: META] BT address is empty!" << endl;
            return false;
        }
        p_str =  UnicodeToAnsi(m_setting.m_asWiFi_Address.c_str());
        META_Result = (META_RESULT)WriteWIFItoNVRAM(p_str, meta_handle );
        delete p_str;

        if( META_SUCCESS != META_Result )
        {
    	    Logger::GetLogger() << Logger::Info <<"[Cosole Mode: META] Write WIFI MAC failed!"<< endl;
            goto clean;
        }

        Logger::GetLogger() << Logger::Info <<"[Cosole Mode: META] Write WIFI MAC and check successfully."<< endl;
    }
    else
    {
        LOGI("[Cosole Mode: META] User skips to write WiFi address.");
    }

    // backup NVRAM to BinRegion (only WinMo need this step)
    if( g_project_mode == DUMA)
    {
        LOGW("[Cosole Mode: META] This version does not support WinMo anymore!");
        Logger::GetLogger() << Logger::Warn
            <<"[Cosole Mode: META]This version does not support WinMo anymore!"<< endl;
        return false;
        /*
        unsigned int ms_timeout=10000;
        ret=WM_META_Nvram2Bin_Wrapper(ms_timeout);
        if(META_SUCCESS != ret)
        {
        	Logger::GetLogger() << Logger::Info
            <<"[Cosole Mode: META] Execution Error : Backup NVRAM to BinRegion failed!"<< endl;
            goto clean;
        }*/
    }
    else if ( g_project_mode == YuSu )
    {
        META_Result = EnterMETASetCleanBootFlag_r(meta_handle);
        if (META_SUCCESS != META_Result)
        {
           return false;
        }
    }
// end of backup NVRAM
    WM_META_RebootTarget_r_Wrapper(meta_handle, 0);
    WM_META_DisconnectWithTarget_r_Wrapper(meta_handle);
    WM_META_Deinit_r_Wrapper(&meta_handle);
    //META_Init(NULL);
    Logger::GetLogger() << Logger::Info <<"[Cosole Mode: META] All Actions Succeed."<< endl;
    return  true;

clean:
    WM_META_ShutDownTarget_r_Wrapper(meta_handle);
    WM_META_DisconnectWithTarget_r_Wrapper(meta_handle);
    WM_META_Deinit_r_Wrapper(&meta_handle);
    //META_Init(NULL);
    Logger::GetLogger() << Logger::Info <<"Fail !"<< endl;
    return false;

}

bool BT_WIFI_IMEI_NVRAMCommand::CreateDirectory(const wstring &directoryPath)
{
    if (::CreateDirectoryW(directoryPath.c_str(), NULL) != 0)
    {
        return (::GetLastError() == ERROR_ALREADY_EXISTS);
    }

    return true;
}


BackupCommand::~BackupCommand()
{
}

int BackupCommand::Execute()
{
    ErrorLookup::SetErrorCodeMode(BROM);;
	Logger::GetLogger() << Logger::Info
           << __FUNC__ << endl;

    // FIXME
    const wstring authFilePath(m_GeneralSetting.GetAuthenticationFilePath());
    const bool authEnabled = !authFilePath.empty();
    AUTH_HANDLE_T authHandle = NULL;

    if (authEnabled)
    {
        USES_CONVERSION;
        AUTH_Create(&authHandle);
        AUTH_Load(authHandle, W2CA(authFilePath.c_str()));
    }

    META_Connect_Req connectReq;
    FillMETAConnectReq(connectReq, m_GeneralSetting, authHandle);

    META_Connect_Report m_METAConnectReport;
    FillMETAConnectReport(m_METAConnectReport);

    int stopFlag;

    ErrorLookup::SetErrorCodeMode(META);
    META_RESULT result = META_ConnectWithTarget(&connectReq,
                                                &stopFlag,
                                                &m_METAConnectReport);

    if (result != META_SUCCESS)
    {
    	Logger::GetLogger() << Logger::Info
               << "[META] connect with target failed: "
               << ErrorLookup::GetErrorMessage(result) << endl;
        return false;
    }

    const wstring backupDirectoryPath(
                    m_BackupSetting.GetBackupDirectoryPath());

    if (!CreateDirectory(backupDirectoryPath))
    {
    	Logger::GetLogger() << Logger::Info
               << "Failed to create backup directory" << endl;
        META_DisconnectWithTarget();
        return false;
    }

    USES_CONVERSION;
    result = META_DeleteAllFilesInBackupFolder(
                            W2CA(backupDirectoryPath.c_str()));

    if (result != META_SUCCESS)
    {
    	Logger::GetLogger() << Logger::Info
               << "Failed to clear backup directory" << endl;
        META_DisconnectWithTarget();
        return false;
    }

    //
    // Backup calibration data
    //
    result = META_QueryIfFunctionSupportedByTarget(
                                5000, "META_MISC_GetIMEILocation");

    if (result != META_SUCCESS)
    {
        if (result != META_FUNC_NOT_IMPLEMENT_YET)
        {
            META_DisconnectWithTarget();
            return false;
        }

        MISC_BACKUP_REQ_T backupReq;
        FillBackupReq(backupReq,
                      W2CA(m_BackupSetting.GetIniFilePath().c_str()),
                      W2CA(backupDirectoryPath.c_str()));

        int stopFlag;

        result = META_BasicBackupCalibrationData(&backupReq, &stopFlag);

        if (result != META_SUCCESS)
        {
            META_DisconnectWithTarget();
            return false;
        }
    }
    else
    {
        MISC_BACKUP_REQ_T backupReq;
        FillBackupReq(backupReq,
                      W2CA(m_BackupSetting.GetIniFilePath().c_str()),
                      W2CA(backupDirectoryPath.c_str()));

        int stopFlag;

        result = META_BackupCalibrationData(&backupReq, &stopFlag);

        if (result != META_SUCCESS)
        {
            META_DisconnectWithTarget();
            return false;
        }
    }

    BACKUP_RESULT_T backupResult;
    FillBackupResult(backupResult);

    result = META_GetBackupResultInfo(W2CA(backupDirectoryPath.c_str()),
                                      &backupResult);

    if (result != META_SUCCESS)
    {
        META_DisconnectWithTarget();
        return false;
    }

    if (m_BackupSetting.IsWatchdogTimerEnabled())
    {
        FtWatchDog watchDogReq;

        ::memset(&watchDogReq, 0, sizeof(watchDogReq));
        watchDogReq.ms_timeout_interval = 5000;

        result = META_EnableWatchDogTimer(5000, &watchDogReq);

        if (result != META_SUCCESS)
        {
            META_DisconnectWithTarget();
            return false;
        }
    }

    META_DisconnectWithTarget();

    // FIXME
    if (authEnabled)
    {
        AUTH_Destroy(&authHandle);
    }

    return true;
}

bool BackupCommand::CreateDirectory(const wstring &directoryPath)
{
    if (::CreateDirectoryW(directoryPath.c_str(), NULL) != 0)
    {
        return (::GetLastError() == ERROR_ALREADY_EXISTS);
    }

    return true;
}

static void FillRestoreReq(MISC_RESTORE_REQ_T &restoreReq,
                          const char *iniFilePath,
                          const char *restoreDirectoryPath)
{
    ::memset(&restoreReq, 0, sizeof(restoreReq));

    restoreReq.m_pIniFilePath      = const_cast<char *>(iniFilePath);
    restoreReq.m_pBackupFolderPath = const_cast<char *>(restoreDirectoryPath);
    restoreReq.cb_progress         = NULL;
    restoreReq.cb_progress_arg     = NULL;
}

static void FillRestoreResult(RESTORE_RESULT_T &restoreResult)
{
    ::memset(&restoreResult, 0, sizeof(restoreResult));
}

RestoreCommand::RestoreCommand(const GeneralSetting &generalSetting,
                               const RestoreSetting &restoreSetting)
    : m_GeneralSetting(generalSetting),
      m_RestoreSetting(restoreSetting)
{
}

RestoreCommand::~RestoreCommand()
{
}

int RestoreCommand::Execute()
{
    USES_CONVERSION;
    Logger::GetLogger() << Logger::Info
           << __FUNC__ << endl;

    int stopFlag;

    ErrorLookup::SetErrorCodeMode(META);
    if (m_RestoreSetting.ShouldReconnectToMETAMode())
    {
        META_ConnectInMETA_Req connectInMETAReq;
        FillMETAConnectInMETAReq(connectInMETAReq, m_GeneralSetting);

        META_ConnectInMETA_Report connectInMETAReport;
        FillMETAConnectInMETAReport(connectInMETAReport);
        // Wait 2s to try to connect modem META
        Sleep(2000);
        META_RESULT result = META_ConnectInMetaMode(&connectInMETAReq,
                                                    &stopFlag,
                                                    &connectInMETAReport);
        if (result != META_SUCCESS)
        {
        	Logger::GetLogger() << Logger::Info
                   << "[META] reconnect with META mode failed: "
                   << ErrorLookup::GetErrorMessage(result) << endl;
            return false;
        }
    }
    else
    {
        // FIXME
        const wstring authFilePath(m_GeneralSetting.GetAuthenticationFilePath());
        const bool authEnabled = !authFilePath.empty();
        AUTH_HANDLE_T authHandle = NULL;

        if (authEnabled)
        {
            USES_CONVERSION;
            AUTH_Create(&authHandle);
            AUTH_Load(authHandle, W2CA(authFilePath.c_str()));
        }

        META_Connect_Req connectReq;
        FillMETAConnectReq(connectReq, m_GeneralSetting, authHandle);

        META_Connect_Report connectReport;
        FillMETAConnectReport(connectReport);

        META_RESULT result = META_ConnectWithTarget(&connectReq,
                                                    &stopFlag,
                                                    &connectReport);

        if (result != META_SUCCESS)
        {
        	Logger::GetLogger() << Logger::Info
                   << "[META] connect with target failed: "
                   << ErrorLookup::GetErrorMessage(result) << endl;
            return false;
        }

        // FIXME
        if (authEnabled)
        {
            AUTH_Destroy(&authHandle);
        }
    }

    META_RESULT result = META_QueryIfFunctionSupportedByTarget(
                                    5000, "META_MISC_GetIMEILocation");

    const wstring restoreDirectoryPath(
                        m_RestoreSetting.GetRestoreDirectoryPath());

    if (result != META_SUCCESS)
    {
        if (result != META_FUNC_NOT_IMPLEMENT_YET)
        {
            META_DisconnectWithTarget();
            return false;
        }

        MISC_RESTORE_REQ_T restoreReq;

        FillRestoreReq(restoreReq,
                       W2CA(m_RestoreSetting.GetIniFilePath().c_str()),
                       W2CA(restoreDirectoryPath.c_str()));

        result = META_BasicRestoreCalibrationData(&restoreReq, &stopFlag);

        if (result != META_SUCCESS)
        {
        	Logger::GetLogger() << Logger::Info
                   << "Failed to restore calibration data" << endl;
            META_DisconnectWithTarget();
            return false;
        }
    }
    else
    {
        MISC_RESTORE_REQ_T restoreReq;

        FillRestoreReq(restoreReq,
                       W2CA(m_RestoreSetting.GetIniFilePath().c_str()),
                       W2CA(restoreDirectoryPath.c_str()));

        int stopFlag;

        result = META_RestoreCalibrationData(&restoreReq, &stopFlag);

        if (result != META_SUCCESS)
        {
        	Logger::GetLogger() << Logger::Info
                   << "Failed to restore calibration data" << endl;
            META_DisconnectWithTarget();
            return false;
        }
    }

    RESTORE_RESULT_T restoreResult;
    FillRestoreResult(restoreResult);

    result = META_GetRestoreResultInfo(W2CA(restoreDirectoryPath.c_str()),
                                       &restoreResult);

    if (result != META_SUCCESS)
    {
    	Logger::GetLogger() << Logger::Info
               << "Failed to get restore result" << endl;
        META_DisconnectWithTarget();
        return false;
    }

    result = META_DeleteAllFilesInBackupFolder(
                        W2CA(restoreDirectoryPath.c_str()));

    if (result != META_SUCCESS)
    {
    	Logger::GetLogger() << Logger::Info
               << "Failed to delete all files in the backup directory" << endl;
        META_DisconnectWithTarget();
        return false;
    }

    META_DisconnectWithTarget();

    return true;
}

ReadbackCommand::ReadbackCommand(const ConsoleMode::GeneralSetting &generalSetting,
								 const ConsoleMode::ReadbackSetting &reabackSetting)
								 :m_GeneralSetting(generalSetting),
								 m_ReabackSetting(reabackSetting)
{
}

ReadbackCommand::~ReadbackCommand()
{
}

int ReadbackCommand::Execute()
{
	ErrorLookup::SetErrorCodeMode(BROM);

	USES_CONVERSION;

	//Logger::GetLogger() << Logger::Info << "MTK Platform: " 
	//	<< g_platform_info.getLoadPlatformName() <<endl;

	COM_PORT_SETTING comPortSetting;
	FillComPortSetting(comPortSetting, m_GeneralSetting);

	//Handles Initializers
	DA_HANDLE_T daHandle;
	DAHandleInitializer daHandleInitiailzer(
		daHandle, m_GeneralSetting.GetDownloadAgentFilePath());

    const wstring authFilePath(m_GeneralSetting.GetAuthenticationFilePath());
	const wstring scertFilePath(m_GeneralSetting.GetSCertFilePath());
	AUTH_HANDLE_T authHandle = NULL;
	SCERT_HANDLE_T scertHandle = NULL;
	if ( !authFilePath.empty() ) {
	    AuthHandleInitializer authHandleInitializer(authHandle, authFilePath);
	}
	if ( !scertFilePath.empty() ) {
		ScertHandleInitializer scertHandleInitializer(scertHandle, scertFilePath);
	}

	RB_HANDLE_T readbackHandle;
	ReadbackHandleInitializer readbackHandleInitializer(
		readbackHandle,
		m_ReabackSetting.GetReadbackList(),
		m_ReabackSetting);

	int stopFlag(0);
    if (comPortSetting.com.number == 0) {
		// Search for a newly created COM port
      if(m_GeneralSetting.GetComPort() == L"USB")
    	{
    	   LOGD("Search for a newly created COM port");
		Logger::GetLogger() << Logger::Info
               << "Searching for newly created USB COM port" << endl;
        unsigned char new_com_port_num = 0;
        const int kTimeout = 30;
		std::string symbolic_name;
		std::string friendly_name;
		if (!ScanUSBPort4DownloadDA(&stopFlag, symbolic_name, friendly_name, true, kTimeout)) {
			Logger::GetLogger() << Logger::Error
				<< "Download failed: no USB COM port detected in "
                   << kTimeout << "s" << endl;
			return false;
		} else {
			new_com_port_num = GetUSBVCOMNumByPortName(friendly_name);
		Logger::GetLogger() << Logger::Info
               << "USB COM port detected: COM" << new_com_port_num << endl;
	}
        comPortSetting.com.number = new_com_port_num;
        //flashToolArg.m_boot_arg.m_usb_enable = _TRUE;
	}

	 if(m_GeneralSetting.GetPortType() == L"USB")
	 {
            LOGD("Search USB port by port name.");

	     comPortSetting.com.number = ::_wtoi(m_GeneralSetting.GetComPort().c_str());
	     LOGD("Wait for COM%d...", comPortSetting.com.number);
			
	      Logger::GetLogger() << Logger::Info
               << "Searching for newly created USB COM port by COM Number" << endl;
             unsigned char new_com_port_num = 0;
             const int kTimeout = 30;
		if (!ScanUSBPortByCOMNum(&stopFlag, comPortSetting.com.number, kTimeout)) {
			Logger::GetLogger() << Logger::Error
                   << "Download failed: no USB COM port detected in "
                   << kTimeout << "s" << endl;
               return false;
		} else {
                   Logger::GetLogger() << Logger::Info
                         << "USB COM port detected: COM" << comPortSetting.com.number << endl;
		}
	 }
	}

	FLASHTOOL_API_HANDLE_T ft_handle;
	FlashTool_Connect_Arg ftConnect;
	FlashTool_Connect_Result ftConnectResult;
	FillFlashToolConnectArg(ftConnect,ftConnectResult,daHandle,authHandle,scertHandle);

	int ret = S_DONE;
	ret = FlashTool_Connect(comPortSetting.com.number, &ftConnect, &ftConnectResult, 
		NULL, &stopFlag, &ft_handle, true);
	if( S_DONE != ret ) {
		Logger::GetLogger() << Logger::Info
			<< "FlashTool_Connect falied: "
			<<  ErrorLookup::GetErrorMessage(ret) << endl;
		return false;
	}

	FlashTool_Readback_Arg rb_arg;
	FlashTool_Readback_Result rb_result;
	FillFlashToolAdvancedReadbackArg(rb_arg, rb_result, readbackHandle, m_GeneralSetting);

	ret = FlashTool_Readback(ft_handle, &rb_arg, &rb_result);
	if ( S_DONE == ret ) {
		Logger::GetLogger() << Logger::Info
			<< "Readback succeeded." << endl;
		return true;	    
	} else {
		FlashTool_Disconnect(&ft_handle);
		Logger::GetLogger() << Logger::Error
			<< "Readback falied: "
			<< ErrorLookup::GetErrorMessage(ret) 
			<< endl;
		return false;
	}
}
