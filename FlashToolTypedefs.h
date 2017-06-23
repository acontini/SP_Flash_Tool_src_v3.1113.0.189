/*
 * FlashToolTypedefs.h
 *
 *  Created on: Jan 5, 2011
 *      Author: MTK81019
 */

#ifndef FLASHTOOLTYPEDEFS_H_
#define FLASHTOOLTYPEDEFS_H_

#include <vcl.h>
#pragma hdrstop

#include "flashtool_handle.h"
#include "param.h"
#include "meta.h"
#include "IMEI_common.h"

//---------------------------------------------------------------------------
typedef struct
{
    char c_imei[2][16];
}S_IMEI_T;

typedef struct
{
    IMEISV_struct_T s_IMEISV[2];
}S_IMEISV_T;


class MultiLoadNode
{

    public:

	    MultiLoadNode()	{ reset(); }
	    ~MultiLoadNode() { }

	    void reset() {
		    m_scat_file= NULL;
		    m_dl_handle = NULL;
		    m_param.reset();
	    }

	    AnsiString				m_scat_file;
	    DL_HANDLE_T				m_dl_handle;
	    ParamDownloadConfig_T	m_param;


};

typedef enum {
	DISABLE_FORMAT = 0,
	RESET_TO_FACTORY,
	AUTO_FORMAT,
	MANUAL_FORMAT,
} FormatOption_E;

typedef enum {
    FORMAT_ALL = 0,
    FORMAT_ALL_EXP_BL,
}NandAutoFormat_E;

typedef enum {
	FIXED_NAND = 0,
      DYNAMIC_NAND = 1,
	EMMC =2,
	SDMMC = 3,
}StorageLayoutType_E;

typedef enum {
    FLASHTOOL_DOWNLOAD = 0,
    FLASHTOOL_READBACK,
    FLASHTOOL_FORMAT,
    FLASHTOOL_PARAMETER,
    FLASHTOOL_API,
    FLASHTOOL_ROMWRITER,
    FLASHTOOL_MEMORYTEST,
    FLASHTOOL_FLASHBIN, 
    FLASHTOOL_WRITEMEMORY,
	FLASHTOOL_READ_SW_VERSION,
	FLASHTOOL_FIRMWARE_UPGRADE,
    FLASHTOOL_READ_PRODUCT_INFO,
    //SCI Clone
    FLASHTOOL_SCI_READBACK,
    FLASHTOOL_SCI_WRITEMEMORY,
    //SCI Download
    FLASHTOOL_SCI_DOWNLOAD
} FLASHTOOL_FUNCTION;

typedef enum {
    LV_NFB_BOOTLOADER = 0,
    LV_NFB_EXT_BOOTLOADER,
    LV_NFB_DL_ROM,
    LV_NOR_BOOTLOADER,
    LV_NOR_DL_ROM,
    LV_OTP,
    LV_FTCFG,
    LV_SEC_RO,
    LV_CUST_PARA,
    LV_GPS_ROM
} ListViewItemType_E;

typedef enum {
	FLASHTOOL = 0,
    BROM      = 1,
	META      = 2,
	GPS       = 3,
    EBOOT     = 4,
} ERROR_CODE_MODE_E;
#if 0
typedef enum {
    NOACTION      = 0,
    BACKUPRESTORE = 1,
    RESTORE       = 2,
    RESTOREONLY   = 3, //DUMA

    BACKUP_FORMAT_DOWNLOAD_RESTORE = 4,
    //added two restore features
    FORMAT_DOWNLOAD_RESTORE_NVRAM = 5,
    RESTORE_NVRAM_ONLY = 6
} BACKUP_RESTORE_STATE_E;
#endif
typedef enum {
    NOACTIONNVRAM      =0,
    UPDATENVRAM    =1,
    FORMAT_DL_UPDATENVRAM = 2,
} NVRAM_UPDATE_STATE_E;

typedef enum {
    BY_NONE = 0,
    BY_RID = 1,
    BY_COM = 2,
} BACKUP_FOLDER_TYPE_E;

typedef enum {
    DUMA      =0,
    YuSu      ,
} Project_Operation_E;

typedef	enum {
	MT6516	= 0,
    MT6573_E1  = 1,
    MT6573_E2  = 2,
	SP_BBCHIP_TYPE_END,
	SP_AUTO_DETECT_BBCHIP = 254,
	SP_UNKNOWN_BBCHIP_TYPE = 255
} SP_BBCHIP_TYPE;

typedef enum
{
    NORMAL_DA_BIN = 0,
    NAND_UTIL_DA_BIN =1
} DA_BIN_TYPE_E;

//---------------------------------------------------------------------------

typedef struct {
	bool	        m_bAuto;
	unsigned int    m_Config;
} EMI_Config_S;

typedef struct {
    // NAND NFI Setting
	bool	        m_bAuto;
	unsigned int	m_nand_acccon;

    // DRAM EMI Setting
    DRAM_SETTING    m_dram_cfg;
} DRAM_NFI_Setting;

//----------------------------------------------------------------------------
typedef enum{
   NORMAL_SCATTER = 0,
   SCI_FILE = 1 
} SCAT_FILE_TYPE_E;

#endif /* FLASHTOOLTYPEDEFS_H_ */
