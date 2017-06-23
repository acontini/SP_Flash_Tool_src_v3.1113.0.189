/*
 * FlashAllInOneAPIs.h
 *
 *  Created on: Apr 11, 2011
 *      Author: mtk81019
 */

#ifndef FLASHALLINONEAPIS_H_
#define FLASHALLINONEAPIS_H_

#include "flashtool_api.h"
#include "flashtool_handle.h"
#include "FlashToolTypedefs.h"

#include <iostream>
#include <vector>

int FlashDownload_allInOne(
		unsigned char com_port,
		int &stopflag,
		FLASHTOOL_API_HANDLE_T &ft_handle,
		FlashTool_Connect_Arg &ftConnect,
		FlashTool_Connect_Result &ftConnectResult,
		FlashTool_Download_Arg &fdl_arg,
		FlashTool_Download_Result &fdl_res,
		bool bDADLAll,
		bool bDADLHighSpeed,
		bool bUsbwithoutBattery,
		bool bAutoDetect,
		FlashTool_USB_Status_Arg &us_arg,
		FlashTool_USB_Status_Result &us_res,
		const FlashTool_EnableWDT_Arg* p_wdt_arg);

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
		const FlashTool_EnableWDT_Arg* p_wdt_arg);

//get total size of all download images.
int GetAllPreparedDLRomFileSize();

//get a particular partition's info
int GetPartitionInfo(
		const FLASHTOOL_API_HANDLE_T &flashtool_handle,
		const std::string &part_name,
		PART_INFO &part_info);

//DA switches speed
int DASwitchSpeed(
				  FLASHTOOL_API_HANDLE_T &flashtool_handle,
				  const bool enable_hs);

//Readback dump utility api
int ReadbackDump(
				 FLASHTOOL_API_HANDLE_T &flashtool_handle,
				 RB_HANDLE_T &rb_handle,
				 const FlashTool_Readback_Arg &rb_arg,
				 FlashTool_Readback_Result &rb_result,
				 const std::vector<RB_INFO> & rb_items);

void FillAutoFormatArg(           FlashTool_Connect_Result &result,
                                        FLASHTOOL_API_HANDLE_T &handle,
                                        NandAutoFormat_E &flag,
                                        FlashTool_Format_Arg &arg);

StorageLayoutType_E GetStorageLayout(bool isDynamic, HW_StorageType_E &storage);

#endif /* FLASHALLINONEAPIS_H_ */
