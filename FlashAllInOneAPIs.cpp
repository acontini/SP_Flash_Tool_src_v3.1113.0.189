/*
 * FlashAllInOneAPIs.cpp
 *
 *  Created on: Apr 11, 2011
 *      Author: mtk81019
 */
#pragma hdrstop

#include "FlashAllInOneAPIs.h"
#include "GlobalData.h"
#include "ErrorLookup.h"
#include "Logger.h"
#include "assert.h"
#include "Utility.h"
#include "FlashToolUSB.h"
#include "version.h"
#include "AutoFormatArgFactory.h"

#include <systdate.h>
#include <DateUtils.hpp>

#pragma warn -8004

using std::string;
using std::vector;

int GetAllPreparedDLRomFileSize(DL_HANDLE_T &dl_handle)
{
    // compute  all enable download rom file size
    unsigned short numRoms = 0;
    int ret = DL_GetCount(dl_handle, &numRoms);
    if (ret != S_DONE)
    {
        DL_Rom_UnloadAll(dl_handle);
        DL_Destroy(&dl_handle);
        // throw exception
        throw std::runtime_error(string("DL_GetCount() failed.")
        		.append(__FILE__).append(", ").append(__FUNC__));
    }

    ROM_INFO romInfo[MAX_LOAD_SECTIONS];

    ret = DL_Rom_GetInfoAll(dl_handle, romInfo, MAX_LOAD_SECTIONS);

    if (ret != S_DONE)
    {
    DL_Rom_UnloadAll(dl_handle);
    DL_Destroy(&dl_handle);
    // throw exception
    throw std::runtime_error(string("DL_Rom_GetInfoAll() failed.")
    		.append(__FILE__).append(", ").append(__FUNC__));
    }

    int  downloadSize = 0;
    for (unsigned short i=0; i<numRoms; ++i)
    {
        ROM_INFO& nthRomInfo = romInfo[i];
        if(nthRomInfo.enable)
        {
            downloadSize += nthRomInfo.filesize;
        }   
    }

    return downloadSize;
    
}

int FlashDownload_allInOne(
		unsigned char com_port,
		int &stopflag,
		FLASHTOOL_API_HANDLE_T &ft_handle,
		FlashTool_Connect_Arg &ftConnect,
		FlashTool_Connect_Result &ftConnectResult,
		FlashTool_Download_Arg &fdl_arg,
		FlashTool_Download_Result &fdl_res,
		bool DADLAll,
		bool DADLHighSpeed,
		bool bUsbwithoutBattery,
		bool bAutoDetect,
		FlashTool_USB_Status_Arg &us_arg,
		FlashTool_USB_Status_Result &us_res,
		const FlashTool_EnableWDT_Arg* p_wdt_arg)
{
	//connect
	int force_charge = 0;
	
	if(g_platform_info.getPlatformConfig().supportDLAutoDetectBattery() && bAutoDetect) 
	{
	        force_charge = 2;
		  LOG("FlashDownload_allInOne: DA USB Download battery is auto detection, force_charge(%d).", force_charge);
	}
	else 
	{
	        force_charge = bUsbwithoutBattery?1:0;
	
	        LOG("FlashDownload_allInOne: DA USB Download without battery is %s", (force_charge ? "enabled" : "disabled"));
	}
	int ret = FlashTool_Connect(com_port, &ftConnect, &ftConnectResult, NULL, &stopflag,
			&ft_handle, force_charge);
	
	
	if (S_DONE != ret) {
		FlashTool_Disconnect(&ft_handle);
		return ret;
	}

	g_platform_info.setChipName(ftConnectResult.m_da_report.m_bbchip_name);
	LOGD(string("FlashDownload_allInOne: The load to be downloadeded is for ").append(
			g_platform_info.getLoadPlatformName()).c_str());
	LOGD(string("FlashDownload_allInOne: Target platform by DA report is ").append(
			g_platform_info.getTargetPlatformName()).c_str());
   
	ErrorLookup::SetErrorCodeMode(FLASHTOOL);
	if (!g_platform_info.isPlatformMatched()) {
		FlashTool_Disconnect(&ft_handle);
		return FT_DL_PLATFORM_ERROR;
	}
    ErrorLookup::SetErrorCodeMode(BROM);


	//get usb speed status
      ret = FlashTool_CheckUSBStatus(ft_handle, &us_arg, &us_res);
	
	LOGD("USB Speed Status(%s)", USBSpeedStatusToString(us_res.usb_speed_status));
      
       if(S_DONE != ret)
	{
          LOGE("Get USB Speed Status fail! ret(%d)", ret);
	    FlashTool_Disconnect(&ft_handle);
	    return ret;
	}

	//Swich Speed if platform supports and user wants to
	if(DADLAll && DADLHighSpeed&&(us_res.usb_speed_status == USB_FULL_SPEED)) {
			LOG("FlashDownload_allInOne: DA Enable High Speed Flag is %s.", 
				(DADLHighSpeed && (us_res.usb_speed_status == USB_FULL_SPEED) ? "true" : "false"));
			ret = FlashTool_SetupUSBDL(&ft_handle, (DADLHighSpeed ? 1 : 0));
			if( S_DONE != ret ) {
				FlashTool_Disconnect( &ft_handle );
				return ret;
			}

			ErrorLookup::SetErrorCodeMode(FLASHTOOL);
			const unsigned int USB_SCAN_TIMEOUT = 30000;
			unsigned short da_highspeed_port = 0;

			//Initilize USB Ports table
			FlashToolUSBTable usb_table = GetFlashToolUSBTable();
			FlashToolUSB usb_da_highspeed;
			if ( !usb_table.QueryUSBItemByName(FlashToolUSB::DA_HIGHSPEED_VCOM, usb_da_highspeed) ) {
				LOG("ERROR: tboot_1::FormatDownloadYuSu_ByDA(): QueryUSBItemByName(): (%s) failed!",
					FlashToolUSB::DA_HIGHSPEED_VCOM.c_str());
			} else {
				LOG("tboot_1::FormatDownloadYuSu_ByDA(): QueryUSBItemByName(): Name(%s), PID(%s), VID(%s)",
					usb_da_highspeed.GetUSBName().c_str(),
					usb_da_highspeed.GetUSBPID().c_str(),
					usb_da_highspeed.GetUSBVID().c_str());
			}

			if(!ScanNewCreateUSBVComPortWithTimeout(USB_SCAN_TIMEOUT, da_highspeed_port, 
				usb_da_highspeed.GetUSBPID(), usb_da_highspeed.GetUSBVID())) {
				LOG("FlashDownload_allInOne: Search%s Fail!", usb_da_highspeed.GetUSBName().c_str());
				return ret = FT_FIND_USB_ERROR;
			}
			ErrorLookup::SetErrorCodeMode(BROM);
                   com_port = da_highspeed_port;
			COM_PORT = com_port;
			LOG("FlashDownload_allInOne: Obtain COM(%d)\n", com_port);

			ret = FlashTool_ChangeCOM(&ft_handle, com_port);
			if( S_DONE != ret ) {
				LOGD("FlashDownload_allInOne: change COM fail!");      
				FlashTool_Disconnect( &ft_handle );
				return ret;
			}
	}

	//download

      //download speed log for performance auto test case require
         int uDLFileSize = GetAllPreparedDLRomFileSize(fdl_arg.m_dl_handle);
        TDateTime uStartTime = Now(); 
      //download speed log for performance auto test case require      
    
	ret = FlashTool_Download(ft_handle, &fdl_arg, &fdl_res);
	if ( S_DONE != ret ) {
		FlashTool_Disconnect(&ft_handle);
		LOGD("FormatDownloadYuSu: FlashTool_Download fail!");
		return ret;
	}

    //download speed log for performance auto test case require  
        TDateTime uEndTime = Now();
    
        //download speed is 
        int dlSpeed (0);

        if(SecondsBetween(uStartTime, uEndTime) != 0)
        {
               dlSpeed= uDLFileSize/SecondsBetween(uStartTime, uEndTime);
               
               //print download speed log.
               Logger::GetLogger()<<Logger::Info<<
               "totalsize: "<<uDLFileSize<<"bytes, "<<endl
               <<"time: "<<(int)SecondsBetween(uStartTime, uEndTime)<<"s, "<<endl
               <<"download speed: "<<dlSpeed/1024/1024<<"Mbps."<<endl;
        }
        else
        {
             Logger::GetLogger()<<Logger::Info<<
                "Abnormal Download Time 0"<<endl;
        }
       
    //download speed log for performance auto test case require       
	
	if(!ToolInfo::IsCustomerVer()) {
		ret = FlashTool_EnableWatchDogTimeout(ft_handle, p_wdt_arg);
		if(S_DONE != ret) {
			FlashTool_Disconnect(&ft_handle);
			LOGD("FormatDownloadYuSu: FlashTool_EnableWatchDogTimeout fail!");
			return ret;
		}
	}
	ret = FlashTool_Disconnect(&ft_handle);
	if(S_DONE != ret) {
		LOGD("FormatDownloadYuSu: FlashTool_Disconnect fail!");
		return ret;
	}

	return S_DONE;

}

int FlashFormat_allInOne(
		unsigned char com_port,
		int &stopflag,
		FLASHTOOL_API_HANDLE_T &ft_handle,
		FlashTool_Connect_Arg &ftConnect,
		FlashTool_Connect_Result &ftConnectResult,
		FlashTool_Format_Arg &fmt_arg,
		FlashTool_Format_Result &fmt_res,
		NandAutoFormat_E autoFormatFlag,
		bool autoFormat,
		bool enableWDT,
		bool isNandUtilFmt,
		bool bUsbwithBattery,
		const FlashTool_EnableWDT_Arg* p_wdt_arg)
{
    int ret;
    if (!isNandUtilFmt) {
    	int force_charge = 0;
	if(g_platform_info.getPlatformConfig().supportDLAutoDetectBattery()) 
		force_charge = 2;
	else force_charge = bUsbwithBattery? 0: 1;
        ret = FlashTool_Connect(com_port, &ftConnect, &ftConnectResult, NULL, &stopflag,
    			&ft_handle, force_charge);
    } else {
        ret = FlashTool_NandUtil_Connect( com_port, &ftConnect, &ftConnectResult, &stopflag, &ft_handle);
    }

	if (S_DONE != ret) {
		FlashTool_Disconnect(&ft_handle);
		return ret;
	} 

      if(autoFormat == true)
      {
            FillAutoFormatArg(ftConnectResult, ft_handle, autoFormatFlag, fmt_arg);
      }

	ret = FlashTool_Format(ft_handle, &fmt_arg, &fmt_res);
	if(S_DONE != ret)
	{
		FlashTool_Disconnect(&ft_handle);
		return ret;
	}

	if(enableWDT){
		ret  = FlashTool_EnableWatchDogTimeout(ft_handle, p_wdt_arg);
		if(S_DONE != ret)
		{
			FlashTool_Disconnect(&ft_handle);
			return ret;
		}
	}

	ret = FlashTool_Disconnect(&ft_handle);
	return ret;
}


void FillAutoFormatArg(FlashTool_Connect_Result &result,
                                        FLASHTOOL_API_HANDLE_T &handle,
                                        NandAutoFormat_E &flag,
                                        FlashTool_Format_Arg &arg)
{
       AutoFormatArgFactory auto_format_factory;
       auto_format_factory.set_dl_handle(result.m_da_report.m_dl_handle);
       auto_format_factory.set_flashtool_handle(handle);
       auto_format_factory.set_da_report(&(result.m_da_report));
       auto_format_factory.set_auto_fmt_flag(flag);
       auto_format_factory.set_oper_flag((!arg.m_format_cfg.m_AddrType)? NUTL_ADDR_LOGICAL : NUTL_ADDR_PHYSICAL);

        HW_StorageType_E storage = arg.m_storage_type;

	StorageLayoutType_E type = GetStorageLayout(arg.m_format_cfg.m_AddrType, storage);
	
      SharedPtr<AutoFormatArg> auto_format_ptr = auto_format_factory.CreateAutoFormatArg(type);

      arg.m_format_cfg.m_format_begin_addr = auto_format_ptr.get()->GetAutoFormatStartAddress();
      arg.m_format_cfg.m_format_length = auto_format_ptr.get()->GetAutoFormatLength();
}

int GetPartitionInfo(
		const FLASHTOOL_API_HANDLE_T &flashtool_handle,
		const string &part_name,
		PART_INFO &part_info)
{
    assert( NULL != flashtool_handle );
    int ret;
    unsigned int rom_count = 0;
    bool isImgNameMatch = false;
    PART_INFO *pPartInfo = NULL;

    do {
        ret = FlashTool_ReadPartitionCount(flashtool_handle, &rom_count);
        if( S_DONE != ret ) {
            LOG("ERROR: FlashTool_ReadPartitionCount fail, errorcode is %d", ret);
            break;
        }
        pPartInfo = new PART_INFO[rom_count];

        ret = FlashTool_ReadPartitionInfo(flashtool_handle, pPartInfo, rom_count);
     	if( S_DONE != ret ) {
            LOG("ERROR: FlashTool_ReadPartitionInfo fail!, errorcode is %d", ret);
    		break;
    	}

		string rom_name;
        for(unsigned int i = 0; i < rom_count; i++){
            rom_name = pPartInfo[i].name;
            if(ToUppercaseString(rom_name) == part_name){
                part_info.begin_addr= pPartInfo[i].begin_addr;
                part_info.image_length = pPartInfo[i].image_length;
                isImgNameMatch = true;
                break;
            }
        }

        if(!isImgNameMatch){
            LOG("ERROR: Image that is wanted to read back does not be found!");
            ret = S_FT_READBACK_FAIL;
            break;
        }
    }while(0);

    if( NULL != pPartInfo ){
        delete[] pPartInfo;
        pPartInfo = NULL;
    }

    return ret;
}

int DASwitchSpeed(
				  FLASHTOOL_API_HANDLE_T &flashtool_handle,
				  const bool enable_hs)
{
	int ret = 0;
	LOG("DASwitchSpeed(): DA Enable High Speed Flag is %s.", 
		(enable_hs ? "true" : "false"));
	ret = FlashTool_SetupUSBDL(&flashtool_handle, (enable_hs ? 1 : 0));
	if( S_DONE != ret ) {
		LOG("ERROR: DASwitchSpeed(): FlashTool_SetupUSBDL() failed!");
		return ret;
	}

	ErrorLookup::SetErrorCodeMode(FLASHTOOL);
	const unsigned int USB_SCAN_TIMEOUT = 30000;
	unsigned short da_highspeed_port = 0;
	//Initilize USB Ports table
	FlashToolUSBTable usb_table = GetFlashToolUSBTable();
	FlashToolUSB usb_da_highspeed;
	if ( !usb_table.QueryUSBItemByName(FlashToolUSB::DA_HIGHSPEED_VCOM, usb_da_highspeed) ) {
		LOG("ERROR: DASwitchSpeed(): QueryUSBItemByName(): (%s) failed!",
			FlashToolUSB::DA_HIGHSPEED_VCOM.c_str());
	} else {
		LOG("DASwitchSpeed(): QueryUSBItemByName(): Name(%s), PID(%s), VID(%s)",
			usb_da_highspeed.GetUSBName().c_str(),
			usb_da_highspeed.GetUSBPID().c_str(),
			usb_da_highspeed.GetUSBVID().c_str());
	}

	if(!ScanNewCreateUSBVComPortWithTimeout(USB_SCAN_TIMEOUT, da_highspeed_port, 
		usb_da_highspeed.GetUSBPID(), usb_da_highspeed.GetUSBVID())) {
			LOG("DASwitchSpeed(): Search %s Fail!", usb_da_highspeed.GetUSBName().c_str());
			return ret = FT_FIND_USB_ERROR;
	}
	ErrorLookup::SetErrorCodeMode(BROM);

	COM_PORT = da_highspeed_port;
	LOG("DASwitchSpeed(): Obtain COM(%d)\n", da_highspeed_port);
	ret = FlashTool_ChangeCOM(&flashtool_handle, da_highspeed_port);
	if( S_DONE != ret ) {
		LOGD("DASwitchSpeed(): FlashTool_ChangeCOM() failed!");      
		return ret;
	}

	return ret;
}

int ReadbackDump(
				 FLASHTOOL_API_HANDLE_T &flashtool_handle,
				 RB_HANDLE_T &rb_handle,
				 const FlashTool_Readback_Arg &rb_arg,
				 FlashTool_Readback_Result &rb_result,
				 const std::vector<RB_INFO> & rb_items)
{
	//TODO: If there is a attribute inf RB_INFO for RB_SetAddrTypeFlag, 
	//in flashtool_handle.h
	//RB_HANDLE could be temporatorly applied in function stack
	int ret = 0;

	vector<RB_INFO>::const_iterator it = rb_items.begin();
	for(; it != rb_items.end(); ++it) {

		ret = RB_Append(rb_handle, it->filepath, it->readback_addr, it->readback_len);
		if( S_DONE != ret ) {
			LOG("ERROR: ReadbackDump(): RB_Append() fail, error code(%d)!", ret);
			return ret;
		}

		do {
			ret = RB_SetReadbackFlag(rb_handle, 0, it->m_read_flag);
			if( S_DONE != ret ) {
				LOG("ERROR: ReadbackDump: RB_SetReadbackFlag() fail, error code(%d)!", ret);
				break;
			}

			ret = FlashTool_Readback(flashtool_handle, &rb_arg, &rb_result);
			if ( S_DONE != ret ) {
				LOG("ERROR: ReadbackDump: FlashTool_Readback() fail, error code(%d)!", ret);
				break;
			}
		} while(0);

		ret = RB_Delete(rb_handle, 0);
		if ( S_DONE != ret ) {
			LOGD("ReadbackDump: RB_Delete() fail!");
			return ret;
		} 
	}

	return ret;
}

StorageLayoutType_E GetStorageLayout(bool isDynamic, HW_StorageType_E &storage)
{
    StorageLayoutType_E storage_layout_type = EMMC;

    switch(storage)
    {
    case HW_STORAGE_NAND:
        storage_layout_type = (isDynamic)? DYNAMIC_NAND : FIXED_NAND;
	  LOGD("storage type: NAND");
	  break;
    case HW_STORAGE_EMMC:
	  storage_layout_type = EMMC;
	  LOGD("storage type: EMMC");
	  break;
    case HW_STORAGE_SDMMC:
	  storage_layout_type = SDMMC;
	  LOGD("storage type: SDMMC");
	  break;
     default:
         LOGD("storage type: Unknown");
	  break;
    }

    return storage_layout_type;
}
