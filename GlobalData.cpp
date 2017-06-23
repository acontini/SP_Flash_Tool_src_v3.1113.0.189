/*
 * GlobalData.cpp
 *
 *  Created on: Dec 17, 2010
 *      Author: MTK81019
 */
#pragma hdrstop

#include "GlobalData.h"

unsigned int            COM_PORT        = 1; // default com port 1
UART_BAUDRATE           BAUD_RATE;

MultiLoadNode	        g_DL_HANDLE_NODE;
MultiLoadNode          *g_pCurNode      = &g_DL_HANDLE_NODE;

Project_Operation_E     g_project_mode  = YuSu;

Android_Image_File	g_android_image_files[ANDROID_IMAGE_FILE_NUMBER];

AnsiString gc_METABackupINI(ExtractFilePath( Application->ExeName ) + "BACKUP.INI");

AnsiString gc_FlashToolINI(ChangeFileExt(Application->ExeName, ".INI" ));



//platform infomation
PlatformInfo g_platform_info;

const char * const BIN_REGION_FILE_NAME = "BinRegion.img";
const char * const kProductInfoBinName = "PRO_INFO.bin";

const char * const BIN_REGION_CHECKSUM = "chksum_binRegion";
const char * const PRO_INFO_CHECKSUM = "chksum_proInfo";

//SCI Clone file folder
const char * const SCI_FILE_FOLDER = "SCI_Files";
const char * const SCI_CONFIG_FILE = "clone_info.xml";





