/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2010
*
*****************************************************************************/

#ifndef _SP_FLASHTOOL_MSG_H
#define _SP_FLASHTOOL_MSG_H

typedef enum
{
    //META
    AP_SPFT_META_IMEI_BT_WIFI = WM_USER + 6000,
    AP_SPFT_META_IMEI,
    AP_SPFT_META_BACKUP_NVRAM,
    AP_SPFT_META_RESTORE_NVRAM,
    AP_SPFT_META_CLEAR_UP ,
    AP_SPFT_META_EXIT ,
    AP_SPFT_DOWNLOAD_SUCCESSFUL,
	AP_SPFT_STOP,
    //DOWNLOAD
    //AP_SPFT_DL_2ND_SITE_USB_HINT,
} SPFT_MSG;

#endif //_SP_FLASHTOOL_MSG_H