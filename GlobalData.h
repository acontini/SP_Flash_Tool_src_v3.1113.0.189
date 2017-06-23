/*
 * GlobalData.h
 *
 *  Created on: Jan 5, 2011
 *      Author: MTK81019
 */

#ifndef GLOBALDATA_H_
#define GLOBALDATA_H_

#include <string>

#include "Eboot\interface.h"
#include "FlashToolTypedefs.h"
#include "PlatformInfo.h"

extern unsigned int            COM_PORT;
extern MultiLoadNode	       g_DL_HANDLE_NODE;
extern MultiLoadNode          *g_pCurNode;
extern UART_BAUDRATE           BAUD_RATE;
extern Project_Operation_E     g_project_mode;
//FIXME
extern Android_Image_File	g_android_image_files[ANDROID_IMAGE_FILE_NUMBER];

//bellow is Flash tool global configurations, put them here first
extern AnsiString gc_METABackupINI;
extern AnsiString gc_FlashToolINI;

extern PlatformInfo g_platform_info;

extern const char * const BIN_REGION_FILE_NAME;
extern const char * const BIN_REGION_CHECKSUM;
extern const char * const PRO_INFO_CHECKSUM;
//Demo R/W product info
extern const char * const kProductInfoBinName;
extern const char * const SCI_FILE_FOLDER;
extern const char * const SCI_CONFIG_FILE;

#endif /* GLOBALDATA_H_ */
