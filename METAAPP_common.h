/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2005
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/
/*****************************************************************************
 *
 * Filename:
 * ---------
 *   METAAPP_common.h
 *
 * Project:
 * --------
 *   Maui META APP
 *
 * Description:
 * ------------
 *   META application common header
 *
 * Author:
 * -------
 *  Andy Ueng (mtk00490)
 *
 *============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
 * $Revision$
 * $Modtime$
 * $Log$
 *
 * Dec 2 2008 mtk01569
 * [STP100001861] [META] META ver 5.0848.0
 * 
 *
 * Sep 8 2008 mtk01569
 * [STP100001807] [META] META ver 5.0836.0
 * 
 *
 * Apr 24 2008 mtk00490
 * [STP100001693] [META] META ver 5.0816.0
 * 
 *
 * Feb 22 2008 mtk00490
 * [STP100001646] [META] META ver 5.0808.0
 * 
 *
 * Dec 3 2007 mtk00490
 * [STP100001570] [META] META ver 5.0748.0
 * 
 *
 * Sep 8 2007 mtk00490
 * [STP100001505] [META] META ver 5.6.0
 * 
 *
 * Jul 15 2007 mtk00490
 * [STP100001471] [META] META ver 5.5.0
 * 
 *
 * May 19 2007 mtk00490
 * [STP100001406] [META] META ver 5.3.8
 * 
 *
 * Feb 8 2007 mtk00490
 * [STP100001308] [META] META ver 5.3.6.0
 * 
 *
 * Nov 23 2006 mtk00490
 * [STP100001231] [META] META ver 5.3.4.0
 * 
 *
 * Nov 8 2006 mtk00490
 * [STP100001203] [META] META ver 5.3.3.0
 * 
 *
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/
#ifndef  _METAAPP_COMMON_H_
#define  _METAAPP_COMMON_H_

#include <windows.h>

#define NOT_FOUND -1

//#define  SERVICE_CENTER
#ifndef  SERVICE_CENTER
typedef enum
{
    MSEL_AUDIO=0,
    MSEL_BARCODE_DOWNLOAD,
    MSEL_BASEBAND,
    MSEL_BT_TOOL,
    MSEL_CMMB_TOOL,
    MSEL_DATABASE_CHANGE,
    MSEL_FACTORY,
    MSEL_FAT_EDITOR,
    MSEL_FM_TOOL,
    MSEL_GETVERSION,
    MSEL_IMEI_DOWNLOAD,
    MSEL_MMIDOWNLOAD,
    MSEL_NVRAM_EDIT,
    MSEL_RF_TOOL,
    MSEL_SETTING,
    MSEL_TDMB_TOOL,
    MSEL_UPATE_PARAMETERS,
    MSEL_WIFI_TOOL,
    TOTAL_MENU_ITEMS
} E_MSEL_MENU;
#else
typedef enum
{
    MSEL_RF_TOOL=0,
    MSEL_UPATE_PARAMETERS,
    TOTAL_MENU_ITEMS
} E_MSEL_MENU;
#endif

typedef struct
{
    HWND handle[TOTAL_MENU_ITEMS];
}S_FORM_HANDLE_T;

typedef enum
{
    DEC_FORMAT = 0,
    HEX_FORMAT
}E_VALUE_FORMAT_T;

typedef enum
{
    STOP_TAG = 0,
    START_TAG
}E_BUTTON_TAG_T;

typedef enum
{
    METAAPP_SUCCESS=0,
    METAAPP_FAIL,
    METAAPP_TIMEOUT,
    METAAPP_STOP,
    METAAPP_CANCEL,
    METAAPP_SECTION_OK,
    METAAPP_NVRAM_INIT_FAIL,
    METAAPP_NVRAM_RESET_FAIL,
    METAAPP_NVRAM_SIZE_INCONSISTENT,
    METAAPP_NVRAM_DB_INCONSISTENT,
    METAAPP_NVRAM_LID_VER_NOT_SUPPORT,
    METAAPP_FAT_DISK_NOT_ENOUGH,
    METAAPP_FAT_FILE_NOT_FOUND,
    METAAPP_FAT_DRIVE_NOT_FOUND,
    METAAPP_FAT_PATH_NOT_FOUND,
    METAAPP_IMEI_CD_ERROR,
    METAAPP_TDMB_DISK_FULL
} E_METAAPP_RESULT_T;

typedef enum
{
    BAUD_RATE_AUTO_INDEX=0,
    BAUD_RATE_57600_INDEX,
    BAUD_RATE_115200_INDEX,
    BAUD_RATE_230400_INDEX,
    BAUD_RATE_460800_INDEX,
    BAUD_RATE_921600_INDEX,
    BAUD_RATE_1500000_INDEX
}E_BAUD_RATE_INDEX;

#endif
