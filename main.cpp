/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2002
*
*****************************************************************************/

/*******************************************************************************
* Filename:
* ---------
*  main.cpp
*
* Project:
* --------
*  Flash tool set
*
* Description:
* ------------
*  Flash tool set main window
*
* Author:
* -------
*  FZ Hsu (mtk00303)
*
*==============================================================================
*           HISTORY
* Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
*------------------------------------------------------------------------------
* $Revision:   1.44  $
* $Modtime:   Jan 13 2006 23:50:24  $
* $Log:   //mtkvs01/vmdata/flash_tool/archives/main.cpp-arc  $
 *
 * Feb 24 2009 MTK02172
 * [STP100001912] [FlashTool] v3.0908.00 release
 * 
 *
 * Dec 31 2008 MTK02172
 * [STP100001884] [FlashTool] v3.0852.00 release
 * 
 *
 * Dec 3 2008 mtk01413
 * [STP100001857] [FlashTool] v3.08480 release
 * 
 *
 * Sep 8 2008 mtk01413
 * [STP100001809] [FlashTool] v3.0836.0 release
 * 
 *
 * Sep 1 2008 MTK01952
 * [STP100001792] [FlashTool] v3.0836
 * New feature:
 * 1. Add the upload files funcitonality 
 *
 * Aug 7 2008 MTK01952
 * [STP100001779] [FlashTool] v3.0828.00
 * New features:
 *  1. Add the backup and restore functinality 
 *
 * May 19 2008 mtk01413
 * [STP100001708] [FlashTool] v3.0820.0 release
 * 1. USB DL: Forbid user to select Boot Loader
 *
 * May 19 2008 MTK01952
 * [STP100001712] [FlashTool] GPS download Phase 2
 * 
 *
 * May 16 2008 mtk01413
 * [STP100001691] [FlashTool] v3.0808.0 release
 * New features:
 *  1. USB Download for End User (MT6230)
 * 
 *
 * Mar 30 2008 MTK01952
 * [STP100001655] [FlashTool] v3.0808.0 DRAM Testing of Memory Test
 * 
 *
 * Mar 5 2008 MTK01952
 * [STP100001655] [FlashTool] v3.0808.0 DRAM Testing of Memory Test
 * 
 *
 * Feb 22 2008 mtk01413
 * [STP100001644] [FlashTool] v3.0808.0 release
 * 
 *
 * Jan 31 2008 mtk01413
 * [STP100001630] [FlashTool] v3.0804.0 release
 * 
 *
 * Dec 3 2007 mtk01413
 * [STP100001568] [FlashTool] v3.0748.0 release
 * New features:
 *  1. USB Download on MT6225/MT6226/MT6227 Series BB
 *  2. GPS Download
 *  3. NOR+SDR in MT6238
 *
 * Aug 30 2007 mtk01413
 * [STP100001497] [FlashTool] v3.2.0 release
 * 
 *
 * May 18 2007 mtk01413
 * [STP100001402] FlashTool v3.1.05 release
 * 
 *
 * Mar 12 2007 mtk01413
 * [STP100001329] FlashTool v3.1.04 release
 * 
 *
 * Nov 2 2006 mtk01413
 * [STP100001195] FlashTool v3.1.02 release
 * Enhancements:
 *  1. [FlashTool] Check SEC_RO/Security Setting/OTP checked-box and filename.
 *
 * Sep 27 2006 mtk00539
 * [STP100001145] FlashTool v3.1.01 release
 * 
 *
 * Aug 16 2006 mtk00539
 * [STP100001057] FlashTool v3.1.00 release
 * Remove SECURE_CUSTOM_NAME checking flag
 *
 * Aug 13 2006 mtk01413
 * [STP100001057] FlashTool v3.1.00 release
 * 
 *
 * Jul 21 2006 mtk01413
 * [STP100001021] FlashTool v2.9.1002 release
 * 
 *
 * Jun 12 2006 mtk01413
 * [STP100000922] FlashTool v2.9.1001 release
 * New features:
 *  1. [FlashTool/BROM_DLL] Support Multi-Load Autodetection Download.
 * 
 *
 * May 24 2006 mtk01413
 * [STP100000879] FlashTool v2.8.1001 release
 *  1. [FlashTool][NEW] Support 6229 Download, add m_emi_gen_c in DRAM setting
 *
 * Feb 23 2006 mtk00539
 * [STP100000625] FlashTool v2.7.1016
 * 
 * 
 *    Rev 1.44   Jan 14 2006 00:49:52   mtk00539
 * Bug fixes:
 *  1. [FlashTool] Fix scatter file path doesn't update on UI. 
 * 
 * Enhancements:
 *  1. [FlashTool] Record normal mode and test mode DA path separatedly.
 * Resolution for 159: [FlashTool v2.7.1015]
 * 
 *    Rev 1.43   Dec 29 2005 15:57:52   mtk00539
 * [BUG FIX] Fix the 10th download history could not be loaded problem.
 * Resolution for 156: [FlashTool v2.7.1013][BUG FIX] Fix BootROM start command failure while manually selecting NMT6226 or MT6227 baseband chip.
 *
 *    Rev 1.42   Dec 29 2005 10:57:24   mtk00539
 *  1. [FlashTool] Add download history feature.
 * Resolution for 156: [FlashTool v2.7.1013][BUG FIX] Fix BootROM start command failure while manually selecting NMT6226 or MT6227 baseband chip.
 * 
 *    Rev 1.41   Oct 19 2005 14:47:24   mtk00539
 *  1. [FlashTool][New] Adapt new BROM_DLL&DA v2.7.1008. 
 * Resolution for 141: [FlashTool v2.7.1008][New] Support NFB download and many new features.
 * 
 *    Rev 1.40   Sep 13 2005 13:38:14   mtk00539
 *  1. [FlashTool][New] Adapt new BROM_DLL&DA v2.4.1016. 
 * Resolution for 131: [FlashTool v2.6.1016][Enhance] Workaround the 1st time power up failure issue when RTC is empty.
 * 
 *    Rev 1.39   Jul 25 2005 14:56:46   mtk00539
 *  1. [FlashTool][New] Support MT6229.
 * Resolution for 125: [FlashTool v2.6.1015][New] Support MT6229.
 * 
 *    Rev 1.38   Jul 22 2005 20:48:28   mtk00539
 *  1. [FlashTool][New] Support MT6227.
 * Resolution for 122: [FlashTool v2.6.1014][New] Support MT6227.
 * 
 *    Rev 1.37   May 26 2005 14:31:10   mtk00539
 * call META_CancelAllBlockingCall() when press stop button.
 * Resolution for 116: [FlashTool v2.6.1012][New] Reset FAT to factory default setting.
 * 
 *    Rev 1.36   May 24 2005 20:03:38   mtk00539
 *  1. [FlashTool][New] Reset FAT to factory default setting. 
 *  2. [FlashTool][New] Option to enable/disable resource project id comparison. 
 * Resolution for 116: [FlashTool v2.6.1012][New] Reset FAT to factory default setting.
 * 
 *    Rev 1.35   Apr 12 2005 22:13:58   mtk00539
 *  1. [FlashTool][New] Support MT6228 baseband chip.
 * Resolution for 110: [FlashTool v2.6.1011][New] Support MT6228 baseband chip.
 * 
 *    Rev 1.34   Feb 16 2005 17:27:42   mtk00539
 *  1. [FlashTool][New] Adapt new BROM_DLL&DA v2.4.1009 to support SPANSION S71AL016D and SHARP LRS18C8A flash. 
 *  2. [FlashTool][Enhance] Allow to setup EMI setting in TestMode.
 *  3. [FlashTool][Enhance] Keep TestMode unless you disable it. In order to allow users to do test continuously.
 *  4. [FlashTool][Enhance] Add CTRL+S hot-key to save TestMode log into file.
 * Resolution for 106: [FlashTool v2.6.1009][New] Adapt new BROM_DLL&DA v2.4.1009 to support SPANSION S71AL016D and SHARP LRS18C8A flash.
 *
 *    Rev 1.33   Nov 22 2004 14:30:10   mtk00539
 *  1. [FlashTool][New] Adapt new BROM_DLL&DA v2.4.1008 to enable/disable speed-up baudrate in BootROM stage.
 * Resolution for 100: [FlashTool v2.6.1008][New] Adapt new BROM_DLL&DA v2.4.1008 to enable/disable speed-up baudrate in BootROM stage.
 * 
 *    Rev 1.32   Oct 29 2004 11:49:20   mtk00539
 *  1. [FlashTool][New] Adapt new BROM_DLL&DA v2.4.1006 to fix AM49DL3208GT & S71PL032J download fail problem and some enhancement.
 *  2. [FlashTool][New] Add auto-detect base band chip type flag.
 * Resolution for 1: META MAUI v1.0
 * 
 *    Rev 1.31   Sep 14 2004 16:42:02   mtk00539
 * [New] Adapt new BROM_DLL&DA v2.4.1005 to fix MT6217 download fail problem.
 * Resolution for 91: [FlashTool v2.6.1005][New] Adapt new BROM_DLL&DA v2.4.1005 to fix MT6217 download fail problem.
 * 
 *    Rev 1.30   Sep 03 2004 19:54:46   mtk00539
 * [FlashTool][New] Adapt new BROM_DLL&DA v2.4.1004 for MT6217 support.
 * Resolution for 89: [FlashTool v2.6.1004][New] Adapt new BROM_DLL&DA v2.4.1004 for MT6217 support.
 * 
 *    Rev 1.29   Aug 09 2004 09:58:10   mtk00539
 * change default baudrate_full_sync_count to 1.
 * 
 *    Rev 1.28   Aug 03 2004 22:42:28   mtk00539
 * remove unnecessar include files
 * 
 *    Rev 1.27   Aug 03 2004 15:07:10   mtk00539
 * [FlashTool v2.6.1002][New] Adapt with BROM_DLL v2.4.1002 and many enhancement.
 * 
 * Reason:
 *  1. [FlashTool][New] Adapt new BROM_DLL v2.4.1002 for many features and bug fix.
 *  2. [FlashTool][Enhance] Display external SRAM size of target NOR flash MCP.
 * 
 * How to verify this SCR?
 *  1. use FlashTool to verify.
 * Resolution for 84: [FlashTool v2.6.1002][New] Adapt with BROM_DLL v2.4.1002 and many enhancement.
 * 
 *    Rev 1.26   Jul 19 2004 11:13:28   mtk00539
 * add baudrate full sync count option
 * Resolution for 82: [FlashTool v2.6.1001][New] Adapt with BROM_DLL v2.4.1001 and many enhancement.
 * 
 *    Rev 1.25   Jul 19 2004 02:10:54   mtk00539
 *  1. [FlashTool][New] Adapt new BROM_DLL v2.4.1001 for many features and bug fix.
 *  2. [FlashTool][Enhance] Export COM port read/write timeout setting.
 *  3. [FlashTool][Enhance] Change EMI setting to 32 bits.
 * Resolution for 82: [FlashTool v2.6.1001][New] Adapt with BROM_DLL v2.4.1001 and many enhancement.
 * 
 *    Rev 1.24   Jun 16 2004 16:38:32   mtk00539
 *  1. [FlashTool][Enhance] Re-org format option panel to prevent users confused.
 *  2. [FlashTool][Enhance] Do not close OK window when operation is done.
 * Resolution for 78: [FlashTool v2.5.1013][Enhance] Re-org format option panel to prevent users confused.
 * 
 *    Rev 1.23   Jun 03 2004 11:55:32   mtk00539
 * when users select new scatter file, set dialog initial dir to scatter file base dir.
 * Resolution for 76: [FlashTool v2.5.1012][BUG FIX] Fix bug in FAT range info import.
 * 
 *    Rev 1.22   May 26 2004 21:54:56   mtk00539
 * [FlashTool][New] Using BROM_DLL_v2.3.1005 new feature to add BootROM stage callback function to disable vibrator to avoid MT6218B series board layout issue.
 * Resolution for 74: [FlashTool v2.5.1011][New] Add new flag to pull down GPIO17.
 * 
 *    Rev 1.21   May 21 2004 17:26:00   mtk00539
 * fix ROM hint
 * Resolution for 71: [FlashTool v2.5.1010][BUF FIX] fix incorrect error message of resource detection.
 * 
 *    Rev 1.20   May 21 2004 15:54:52   mtk00539
 *  1. [FlashTool][BUF FIX] fix incorrect error message of resource detection.
 * Resolution for 71: [FlashTool v2.5.1010][BUF FIX] fix incorrect error message of resource detection.
 * 
 *    Rev 1.19   May 14 2004 17:04:20   mtk00539
 *  1. [FlashTool][New] add CTRL+ALT+O hot-key to toggle Advanced Option Mode.
 *  2. [FlashTool][New] add FAT auto format mechanism.
 *  3. [FlashTool][New] add DA auto selection mechanism.
 *  4. [FlashTool][New] add STOP button.
 *  5. [FlashTool][Enhance] start timer when BootROM start cmd pass.
 *  6. [FlashTool][New] display flash info in status bar hint.
 *  7. [FlashTool][New] display format range info in format progress bar hint.
 *  8. [FlashTool][New] record the DA, Scatter and DL path separately.
 * Resolution for 68: [FlashTool v2.5.1009][New] add FAT auto format, DA auto selection mechanism and lots of enhancements.
 * 
 *    Rev 1.18   Apr 20 2004 15:58:28   mtk00539
 * [Enhance] hide seldom used option, it an be turn on again by Advance Mode hot-key CTRL+ALT+O.
 * Resolution for 65: [FlashTool v2.5.1008][New] add baseband chip ECO revision checking flag for FlashDownload.
 * 
 *    Rev 1.17   Mar 29 2004 14:20:10   mtk00539
 * [New] add baseband chip ECO revision checking flag for FlashDownload.
 * Resolution for 65: [FlashTool v2.5.1008][New] add baseband chip ECO revision checking flag for FlashDownload.
 * 
 *    Rev 1.16   Mar 02 2004 00:28:16   mtk00539
 *  1. [FlashTool][Enhance] automatically select bbchip according to rom bbchip id..
 *  2. [FlashTool][Enhance] automatically load all the resource files.
 *  3. [FlashTool][Enhance] display resource and jump table information.
 *  4. [FlashTool][New] add MT6219 support.
 * Resolution for 54: [FlashTool v2.5.1006][Enhance] bbchip id detection and resource autoload.
 * 
 *    Rev 1.15   Feb 11 2004 17:54:56   mtk00539
 * [Enhance] support selectable download
 * Resolution for 52: [FlashTool v2.5.1002][Enhance] selectable download.
 * 
 *    Rev 1.14   Feb 05 2004 13:40:34   mtk00539
 * adapt to BROM DLL v2.2.1001
 * Resolution for 47: [FlashTool v2.5.1001][New] support multiple concatanated bin files download.
 * 
 *    Rev 1.13   Oct 29 2003 17:39:12   mtk00539
 * modify packet length
 * 
 *    Rev 1.12   Oct 06 2003 14:25:54   mtk00539
 * Do not check DA handle when users select MT6208
 * Resolution for 29: [FlashTool v2.4.1001][New] See the reasons below.
 * 
 *    Rev 1.11   Oct 01 2003 23:38:16   mtk00539
 * Add packet length in DA_WRITE_CMD and DA_READ_CMD.
 * Resolution for 28: [BootRom v2.1.1001][New] See the reasons below.
 *
 *    Rev 1.10   Sep 25 2003 14:03:28   mtk00539
 * adapt brom.dll v2.1.1001, please see SCR(29) for more details.
 * Resolution for 29: [FlashTool v2.4.1001][New] See the reasons below.
 * 
 *    Rev 1.9   Jun 30 2003 19:19:36   mtk00539
 *  1. [FlashTool][Add Features] Split flashtool function into brom.dll
 *  2. [FlashTool][Add Features] Format function: users can format any range you want without downloading procedure.
 *  3. [FlashTool][Add Features] Report format percentage.
 *  4. [FlashTool][Add Features] Check format range.
 *  5. [FlashTool][Add Features] Merge FlashTool for Pluto version.
 *  6. [FlashTool][Add Features] Runtime debug log: you can press (CTRL+ALT+T) to enable/disable debug log whenever you want.
 *  7. [FlashTool][Add Features] Forcedly Stop hot-key: you can forcedly stop FlashTool by pressing CTRL+Z.
 *  8. [FlashTool][BUG FIXED] Fix FlashTool MEM_CMD end_addr bug, FlashTool should use (begin_addr+length-1) as end_addr.
 * Resolution for 11: [FlashTool v2.3.1001][New Version] Split flashtool function into brom.dll
 *
 *    Rev 1.8   Jun 11 2003 17:53:34   mtk00539
 * 1. Modify BootRom library to support MT6218
 * 2. Modify FlashTool and DA to support AM29PDL128G flash
 * Resolution for 9: [FlashTool v2.2.1005][Add Feature] Support MT6218 and new flash AM29PDL128G
 * 
 *    Rev 1.7   Jun 03 2003 22:24:54   mtk00539
 * 1. extend timeout to 10 sec for large image download in boot_2.cpp
 * 2. disable unnecesssary debug hot-key.
 * 3. add shift+ctrl+A for Jensen's DA debug tool kit.
 * 4. enable build number, and start from 1003.
 * 5. save baseband chip type, mcu frequency and auto-memory wait state setup flag to ini file.
 * 6. add DA_SET_REG_CMD command and remove FINISH_CMD, so that release power key could be issued from FlashTool, not hardcoded in DA.
 * 7. add DA_MCU_FREQ_CMD command, so that we don't have to select different DA while switching frequency.
 * 8. add new flash MB84VD23280FA-70 for Chicago project.
 * 9. remove DEVICE_CMD, DA will check flash automatically and report the flash type to PC.
 * 10. add DA_FORMAT_CMD command to support range format.
 * 11. display flash type on FlashTool.
 * 12. merge the DOWNLOAD.H header file, both FlashTool and DA will use the same header file.
 * 13. modify SPEED_CMD handshake by adding a sync mechanism to detect whether if the speed change is done by both sides.
 * Resolution for 7: [FlashTool v2.2.1003][AddFeature] Enhanced for KLM and Chicago project.
 * 
 *    Rev 1.6   May 20 2003 16:22:30   mtk00539
 * Support 6205/6205B at 13MHz, 26MHz and 52MHz
 * Resolution for 6: [FlashTool v2.2][AddFeature] Support 6205/6205B at 13MHz, 26MHz and 52MHz.
 *
 *    Rev 1.5   Jan 09 2003 17:45:34   mtk00303
 * update for version 2
 * add flash erase, program timeout
 * add last 1~3 context switch ID, frame tick time
 * 
 *    Rev 1.4   Dec 10 2002 23:24:30   mtk00303
 * remove redundant comment
 * 
 *    Rev 1.3   Nov 20 2002 19:52:58   mtk00303
 * update for reference phone
 * 
 *    Rev 1.2   Jul 30 2002 10:45:24   admin
 * 2002_0730
 * 
 *    Rev 1.1   Jul 26 2002 11:52:18   admin
 * ver 0726
 * 
 *    Rev 1.0   Jul 20 2002 19:26:14   admin
 * Initial revision.
*
*------------------------------------------------------------------------------
* Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
*==============================================================================
*******************************************************************************/

//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <string>
using   namespace   std;

#include <inifiles.hpp>
#include <FileCtrl.hpp>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>

#include <vector>
#include "meta.h"
#include "WMMETA_Wrapper.h"
#include "main.h"
#include "ext_mem1.h"

#include "tboot_1.h"
#include "about.h"

#include "DA_option.h"
#include "RB_option.h"
#include "frm_FormatOption.h"

#include "DL_Go.h"
#include "RB_Go.h"
#include "com_util.h"
#include "com_enum.h"
#include "frm_BootROMStartCmdRetry.h"
#include "frm_COM_Option.h"
#include "frm_SecuritySetting.h"
#include "frm_OTPSetting.h"
#include "frm_ParameterReadSetting.h"
#include "frm_IMEIDownload.h"
//#include "frm_RestoreNVRAM.h"
#include "frm_FourInOne.h"
#include "frm_Process.h"
#include "frm_encript.h"

#include "Utility.h"
#include "ImageMapRule.h"
#include "AndroidImageInfo.h"
#include "FileUtils.h"
#include "GlobalData.h"
#include "Logger.h"
#include "version.h"
#include "updater.h"
#include "Platforms.h"
#include "CloneInfoHandle.h"

#include "ErrorLookup.h"

#include "FlashToolUSB.h"
#include "OperationIndicator.h"
#include "DownloadImageChecksum.h"
#include "NandLayoutParameter.h"
#include "HintMessageHandle.h"
#include "CloneInfoHandle.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Trayicon"
#pragma link "CGAUGES"
#pragma link "CGAUGES"
#pragma resource "*.dfm"

#ifdef __BORLANDC__
#pragma warn -8004
#endif

extern int  WM_META_DebugOn_Wrapper();
extern int  WM_META_DebugOff_Wrapper();

TMainForm *MainForm;

DownloadHistoryList	g_DownloadHistory;

EXT_CLOCK	g_EXT_CLOCK   = AUTO_DETECT_EXT_CLOCK;

BBCHIP_TYPE	g_BBCHIP_TYPE = UNKNOWN_BBCHIP_TYPE;
SP_BBCHIP_TYPE	g_SP_BBCHIP_TYPE = SP_UNKNOWN_BBCHIP_TYPE;

FLASHTOOL_FUNCTION	    g_flashtool_function    = FLASHTOOL_DOWNLOAD;
//to distingush normal scatter or sci file
SCAT_FILE_TYPE_E g_scatter_type = NORMAL_SCATTER;
#if 0
BACKUP_RESTORE_STATE_E  g_backup_restore_state  = NOACTION;
#endif
NVRAM_UPDATE_STATE_E    g_nvram_update_state    = NOACTIONNVRAM ;

BACKUP_FOLDER_TYPE_E    g_backup_restore_folder_type = BY_NONE;

int g_stopflag = 0;
int iFlashItemIndex = 0;

FormatOption_E	g_FormatAfterDownloadOption;
FormatOption_E	g_FormatOption;

unsigned long long g_ulNandFormatStartAddr = 0;
unsigned long long g_ulNandFormatLength = 0;

//have not been modified
unsigned int g_ulNandFormatLengthByDAReport = -1;

unsigned int g_COM_Read_Timeout          = COM_DEFAULT_TIMEOUT;
unsigned int g_COM_Write_Timeout         = COM_DEFAULT_TIMEOUT;
unsigned int g_MaxBromStartCmdRetryCount = DEFAULT_BROM_START_CMD_RETRY_COUNT;
unsigned int g_CostTimeSec;
unsigned int g_ProgressTimeSec;
unsigned int g_DisplayFinishedBytes;

unsigned char g_Baudrate_FullSync_Count = 1;

bool    bInitComPort = false;
bool    DEBUG = true;
bool	g_bDebugDA = false;
bool	g_bTrace = false;
bool	g_bSkipBootRom = false;
//bool	g_bCheckECOVer = true;
bool	g_bCheckECOVer = false;
bool	g_bCommandRecordingMode = false;
bool	g_bCheckTgtResourceLayout = true;
bool	g_bAutoLoadResByScat = true;
bool	g_bEnableAdvanceOption = false;
bool	g_bPullDownGPIO17 = true;
bool	g_SpeedUpBootROMBaudrate = true;
bool	g_CompareResProjectId = true;
bool	g_FormatValidation = false;
bool    g_bParameterPage = false;
bool    g_bDownloadStyleSequential = false;
bool	g_bNFI_SelectCS1 = false;
bool    g_bUsbDLRB = false;
bool    g_bUsbMode = false;
bool    g_bUsbModeWithBattery = false;

bool    g_bUsbDLDA = false;
//add for certification download, when cert dl mode, we set it to true to avoid use searching funciton for dl DA.
bool   g_bDLCert = false;

bool    g_bDADownloadAll = false;
bool    g_bSwitchSpeed = false;
bool    g_bPhysicallyFormatReadback = false;
//Add for controllingl to mark nand bad blocks
bool    g_bEnableMarkNandBadBlocks = false;
//Add for certification files download
bool    g_bDLCertificationMode = false;
//OptionMethod_E	    g_OperationMethod = NAND_OPERATION;
NUTL_EraseFlag_E	g_EraseFlag = NUTL_ERASE;
NandAutoFormat_E    g_NandAutoFormatFlag = FORMAT_ALL_EXP_BL;

unsigned short      g_PacketLength = 256;


DL_HANDLE_LIST_T    g_DL_HANDLE_LIST = NULL;

std::vector<MultiLoadNode>      g_DL_HANDLE_LIST_nodes;


DA_HANDLE_T	    g_DA_HANDLE     = NULL;
DA_HANDLE_T     g_NAND_UTIL_DA_HANDLE = NULL;
RB_HANDLE_T	    g_RB_HANDLE     = NULL;
RB_HANDLE_T     g_FU_RB_HANDLE = NULL;
RB_HANDLE_T     g_CLONE_RB_HANDLE = NULL;
RB_HANDLE_T     g_SW_Ver_RB_HANDLE = NULL;
AUTH_HANDLE_T g_AUTH_HANDLE   = NULL;
SCERT_HANDLE_T g_SCERT_HANDLE = NULL;
ANDROID_ADV_HANDLE_T g_Android_Adv_HANDLE = NULL;

FLASHTOOL_API_HANDLE_T  g_ft_handle = NULL;

bool g_SCI_Mode = false;

ParamDownloadConfig_T   g_ParamDownloadConfig;
ParamReadbackConfig_T   g_ParamReadbackConfig;
ParamReadbackConfig_T   g_ReadbackPage_Param;
ParameterType_T         g_ParameterType;

SecurityBitCtrl_YuSu_T g_ParamsecBitCtrlYuSu;
unsigned int g_ParamImageLockAll = NONE_IMG_LOCKED;

EMI_Config_S		g_EMI_Config[8];
DRAM_NFI_Setting	g_EMI_NFI_Setting = { _TRUE, 0, _FALSE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };	// apply BootLoader's DRAM setting by default
//Write Memory
AnsiString g_WM_RawDataFilePath;
unsigned long long g_WM_address = 0;
unsigned int g_WM_container_length = 0;

//WinMo image name for scatter file
static const char SCATTER_EOOT_NAME[] = "eboot";

//Android image name for scatter file
static const char SCATTER_UBOOT_NAME[] = "UBOOT";

AnsiString	g_asNormalModeDAPath;
AnsiString	g_asTestModeDAPath;
AnsiString  g_BackupCalibrationDataFolderPath;

TTreeNode * g_rootLoad;

ListViewItemType_E	g_LV_ItemType[] = {
    LV_NFB_BOOTLOADER
    ,LV_NFB_EXT_BOOTLOADER
	,LV_NFB_DL_ROM
    ,LV_NOR_BOOTLOADER
	,LV_NOR_DL_ROM
	,LV_OTP
	,LV_FTCFG
	,LV_SEC_RO
	,LV_CUST_PARA
    ,LV_GPS_ROM
};

static AnsiString  g_as_project_selection_Array[] =
{
    "WinMo",
    "Android",
};

//---------------------------------------------------------------------------
static bool OpenReadDA_File( AnsiString asFileName, unsigned int daBinType )
{
	int ret;

    switch(daBinType)
    {
        case NORMAL_DA_BIN:
             {
                 ret = DA_Load(g_DA_HANDLE, asFileName.c_str(), g_bDebugDA?_FALSE:_TRUE, _FALSE);

	         MainForm->ed_Clone_DA_File->Text = ((S_DONE == ret ) ? (asFileName.c_str()) : "");
                MainForm->ed_SCI_DL_DA_File->Text = ((S_DONE == ret ) ? (asFileName.c_str()) : "");
	         MainForm->ed_DA_File->Text = ((S_DONE == ret ) ? (asFileName.c_str()) : "");
		    LOGD("OpenReadDA_File(): NORMAL_DA_BIN: DA_Load _TRUE, _FALSE");
                 //g_asNormalModeDAPath = ((S_DONE == ret ) ? (asFileName.c_str()) : NULL);
                 break;
             }
        case NAND_UTIL_DA_BIN:
             {
                 ret = DA_Load(g_NAND_UTIL_DA_HANDLE, asFileName.c_str(), g_bDebugDA?_FALSE:_TRUE, _TRUE);
                 MainForm->ed_NandUtil_File->Text = ((S_DONE == ret ) ?  (asFileName.c_str()) : "");
				 LOGD("OpenReadDA_File(): NAND_UTIL_DA_BIN: DA_Load _TRUE, _TRUE");
                 //asNandUtilDAPath = ((S_DONE == ret ) ? (asFileName.c_str()) : "");
                 break;
             }
        default:
             ret = S_DA_ERROR_BEGIN;
             break;
    }

	if( S_DONE != ret )
    {
		if( S_FTHND_HANDLE_BUSY_NOW == ret ) {
			ShowMessage("Program is busy! Can not reload DA right now.");
		}
		else if( S_INVALID_DA_FILE == ret ) {
			ShowMessage(" \"" + asFileName + "\" is not a valid DA format!");
		}
		else {
			ShowMessage(" Load DA \"" + asFileName + "\" fail!");
		}
		return false;
	}
    else
    {
	    return true;
    }
}
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner),
		m_is_auto_polling_enable(false),
		m_auto_polling_count(0),
		m_auto_polling_upper_limit(0)
{
}
//-----------------------------------------------------------------------------
void __fastcall TMainForm::Download1Click(TObject *Sender)
{
    g_flashtool_function = FLASHTOOL_DOWNLOAD;
    
	if ( !IsInitialParameterCheckPass() ) {
		return;
	}

	if (!IsAllImgsToBeDL(g_pCurNode->m_dl_handle)) {
		std::string error_hint  = "Not ALL images are correctly loaded, which may cause boot up issue!\n" 
			"Do you still want to go on downloading anyway?";
		int ret = MessageBox(NULL, error_hint.c_str(), "Download Warning", MB_YESNO|MB_ICONWARNING|MB_DEFBUTTON2);
	    if (ret != IDYES) {
		    return;
		}
	}
    if( !InitializeDL() )   {
        return;
    }
	
    if( MT6205 != g_BBCHIP_TYPE )
	   start_DL(true);
    else
	   Form_DL_GO->ShowModal();

}

//------------------------------------------------------------------------------
bool TMainForm::InitializeDL ( void )
{
    if( NULL == g_pCurNode ) 
    {
        return false;
    }

    DL_HANDLE_T &dl_handle = g_pCurNode->m_dl_handle;
    MultiLoadNode*  p_node = g_pCurNode;
    DL_INFO		dl_info;
    DL_GetInfo(p_node->m_dl_handle, &dl_info);

    if ( asBin.IsEmpty() )
    {
        //if (! FileOpenDownloadAgentExecute() )
        if (!FileOpenNandUtilBin(OpenDownloadAgentDialog, NORMAL_DA_BIN))
        {
            ShowMessage(" You must open download agent file before downloading. ");
            return false;
        }
    } else {
		//Update DA by DA_Load
		if(!OpenReadDA_File( asBin,  NORMAL_DA_BIN)) {
		    ShowMessage(" Load DA Fail!");
			LOGD("ERROR: TMainForm::InitializeDLFile(): OpenReadDA_File() fails!");
			return false;
		}
    }

    if( g_bUsbDLDA &&
        asNandUtilDAPath.IsEmpty())
    {
        if ( !FileOpenNandUtilBin(OpenNandUtilFileDialog, NAND_UTIL_DA_BIN) )
        {
            ShowMessage(" You must open Nand Util file before downloading. ");
            return false;
        }
    }
#if 0
    if( g_project_mode == DUMA)
    {
        if(ed_SPBIN_File->Text.IsEmpty())
        {
            ShowMessage(" You must open Flash.Bin before downloading. ");
            return false;
        }
        else
        {
            asFlashBinFile=ed_SPBIN_File->Text;
        }
    }
#endif
/*
    if( g_project_mode == YuSu)
    {
        if(ed_AUTH_File->Text.IsEmpty())
        {
            m_auth_file.is_download = false;
            
            ShowMessage(" You must open Auth File before downloading. ");
            return;
           
        }
        else
        {
            //for android verify
            strncpy(auth_path, ed_AUTH_File->Text.c_str(), 254);
            m_auth_file.m_path = auth_path;
            m_auth_file.m_format = DM_IMG_FORMAT_FAT;
            m_auth_file.m_type = DM_IMG_TYPE_AUTHEN_FILE;
            m_auth_file.addr_off = 0;
            m_auth_file.is_download = true;
        }
    }
*/


    if ( !g_bDebugDA && g_pCurNode->m_scat_file.IsEmpty() )
    {
        if ( ! FileOpenLinkMapExecute(g_pCurNode) )
        {
          ShowMessage(" You must open an scatter file before downloading. ");
          return false;
        }
    }

    if ( !g_bDebugDA && mi_MultiLoad->Checked )
    {
        int handleNumber = 0;
        DL_GetHandleNumber(g_DL_HANDLE_LIST,&handleNumber);

        if( 0 == handleNumber)
        {
          ShowMessage(" You must at least add 1 load in Multi-Load mode. ");
          return false;
        }
    }
    if( g_project_mode == DUMA)
    {
        assert(0);
    }

    // Check ParamListView Download Items
    if( dl_info.m_config.m_security_supported )
    {
        if( true == p_node->m_param.m_otp_enable )
        {
            if ( p_node->m_param.m_otp_filepath.Length() <= 0 )
            {
                ShowMessage(" You must choose a OTP file!");
                return false;
    	    }
    	}

        if( true == p_node->m_param.m_sec_ro_enable )
        {
            if ( p_node->m_param.m_sec_ro_filepath.Length() <= 0 )
            {
                ShowMessage(" You must choose a Secure RO file!");
                return false;
    	    }
    	}

		if( true == p_node->m_param.m_cust_para_enable )
		{
            if ( p_node->m_param.m_cust_para_filepath.Length() <= 0 )
            {
                ShowMessage(" You must choose a Parameter file!");
                return false;
            }
    	}
    }

    // clean Flash device info
    HWStatusBarClear();

    // update Status Bar
    updateStatusBar();

    // update DA to the lastest version
    if( UpdateDA() )
    {
        return false;
    }
    // check if NFB enabled
    _BOOL	bIsNFB=_FALSE;
    DL_IsNFB(dl_handle, &bIsNFB);

    int ret = S_DONE;
    AnsiString s1, s2;
    BL_INFO		bl_info;
    ROM_INFO	rom_info;
    bool IsUpdate = false;
	
    while( S_DONE != (ret=DL_IsReady(dl_handle, &rom_info, &bl_info, _TRUE)) )
    {
        if( S_FTHND_FILE_IS_UPDATED == ret )
        {
            if( DL_Rom_Load(dl_handle, rom_info.index, rom_info.filepath) )
            {
                s1 = rom_info.name;
                s2 = rom_info.filepath;
        	
                if( S_DL_LOAD_REGION_IS_OVERLAP == ret )
                {
                    ShowMessage( "\"" + s2 + "\" is too large and causes region overlap!");
                    return false;
                }
                else
                {
                    ShowMessage(" Load " + s1 + " from file \"" + s2 + "\" fail!");
                    return false;
                }
             }
             IsUpdate = true;
        }
        else
        {
            break;
        }
    }

    if(IsUpdate)
    {
          IsUpdate = false;
          RedrawDownloadList(g_pCurNode, false);
    }

    ret = S_DONE;	

    if ( g_bDebugDA ) 
    {
        DebugDAWindow->Text = "";
    }

    if( !g_bDebugDA )
    {
        // construct current download set
        DownloadSet		dl_set;
				
        // get scatter file path
        dl_set.m_Scatter = g_pCurNode->m_scat_file.c_str();
		
        // get bin file info
        unsigned short	count=0;
		
        if( ( S_DONE == DL_GetCount(dl_handle, &count) ) && (0<count) )
        {
            ROM_INFO	rom[MAX_LOAD_SECTIONS];
            if( S_DONE == DL_Rom_GetInfoAll(dl_handle, rom, MAX_LOAD_SECTIONS) )
            {
                for( int i=0; i < count; i++ )
                {
                    DownloadBinFile		dl_bin;
                    dl_bin.m_Filepath = rom[i].filepath;
                    dl_bin.m_Enable   = rom[i].enable?true:false;
                    dl_set.m_BinFiles.push_back( dl_bin );
                 }
             }
        }
	
        if( bIsNFB )
        {
            // get BootLoader info
            BL_INFO		bl_info;
			
            if( S_DONE == DL_BL_GetInfo( dl_handle, &bl_info ) )
            {
                dl_set.m_BootLoader        = bl_info.m_filepath;
                dl_set.m_BootLoader_Enable = bl_info.m_enable?true:false;
            }
        }
				

        // delete the oldest history
        if( MAX_DOWNLOAD_HISTORY == g_DownloadHistory.size() ) 
        {
            g_DownloadHistory.pop_back ();
        }
	
        g_DownloadHistory.clear();
        // insert new download set to the top of history
        g_DownloadHistory.push_front( dl_set );
    }


    //write download history to INI
	WriteBackYuSuINI();
#if 0
    if( g_project_mode == DUMA)
    {
    		WriteBackDUMAINI();
    }
    else if( g_project_mode == YuSu)
    {
    		WriteBackYuSuINI();
    }
#endif

	//2011.08.10 add for DA DL All checksum
	//int ret(S_DONE);
	if(g_bDADownloadAll) {
		bool b_enable_checksum = MainForm->cb_da_dl_checksum_->Checked;
		LOG("%s(): set DL_SetChecksumEnable(%s).", __FUNC__, b_enable_checksum ? "True" : "False");
		ret = DL_SetChecksumEnable(dl_handle, b_enable_checksum);
		if (S_DONE != ret) {
			LOG("ERROR: %s(): DL_SetChecksumEnable() failed, error code(%d).", __FUNC__, ret);
			return false;
		}
	}
    return true;
}

//------------------------------------------------------------------------------
void TMainForm::start_DL( bool b_start_DL )
{
    if (g_bCommandRecordingMode)
    {
        CreateConfigFile();
        return;
    }

	g_CostTimeSec = 0;  // reset download time
	g_ProgressTimeSec = 0;

	sb_Main->Panels->Items[4]->Text = " 0:00 sec ";

	p1 = new tboot_1( true );
	p1->FreeOnTerminate  = true;
	p1->Resume();
}
//---------------------------------------------------------------------------
#include <exception>
#include <sstream>
#include <string>
#pragma warn -8027  // Functions containing do are not expanded inline
#include <utilcls.h>
#pragma warn .8027
#include "Config.h"

using ConsoleMode::Config;
using ConsoleMode::ConfigType;
using ConsoleMode::GeneralSetting;
using ConsoleMode::DownloadSetting;
using ConsoleMode::FormatSetting;
using ConsoleMode::ReadbackSetting;
using ConsoleMode::ResetToFactoryDefaultSetting;
using ConsoleMode::BackupSetting;
using ConsoleMode::Write_BT_WIFI_IMEI_NVRAM_Setting;
using ConsoleMode::RestoreSetting;


void TMainForm::CreateConfigFile()
{
    void (TMainForm::*configFileCreator)(const std::wstring &) = NULL;

	if (   FLASHTOOL_DOWNLOAD == g_flashtool_function
		|| FLASHTOOL_FLASHBIN == g_flashtool_function) {
			if (g_FormatAfterDownloadOption == DISABLE_FORMAT) {
				//if (g_backup_restore_state == NOACTION) {
					if( g_nvram_update_state == UPDATENVRAM && g_project_mode == YuSu)  {
						configFileCreator = &TMainForm::Create_META_4in1_ConfigFile;
					} else {
						configFileCreator = &TMainForm::Create_DL_ConfigFile;
					}
				//} else if (g_backup_restore_state == BACKUPRESTORE) {
				//	configFileCreator = &TMainForm::Create_BK_DL_RS_ConfigFile;
				//}
			} else if (g_FormatAfterDownloadOption == RESET_TO_FACTORY) {
				assert(0 && "Not support!");
#if 0
				if (g_backup_restore_state == NOACTION) {
					configFileCreator = &TMainForm::Create_DL_RtFD_ConfigFile;
				} else if (g_backup_restore_state == BACKUPRESTORE) {
					configFileCreator =
						&TMainForm::Create_BK_DL_RtFD_RS_ConfigFile;
				}
#endif
			} else if ((g_FormatAfterDownloadOption == AUTO_FORMAT) ||
				(g_FormatAfterDownloadOption == MANUAL_FORMAT)) {
					assert(0 && "Not Support!");
#if 0
					if (g_backup_restore_state == NOACTION) {
						configFileCreator = &TMainForm::Create_DL_FMT_ConfigFile;
					} else if (g_backup_restore_state == BACKUPRESTORE)            {
						configFileCreator = &TMainForm::Create_BK_DL_FMT_RS_ConfigFile;
					}
#endif
			}
	} else if (g_flashtool_function == FLASHTOOL_FORMAT)  {
		if (g_FormatOption == RESET_TO_FACTORY) {
			assert(0 && "Not support!");
#if 0
			if (g_backup_restore_state == NOACTION) {
				configFileCreator = &TMainForm::Create_RtFD_ConfigFile;
			} else if (g_backup_restore_state == BACKUPRESTORE) {
				configFileCreator = &TMainForm::Create_BK_RtFD_RS_ConfigFile;
			}
#endif
		} else if ( g_FormatOption == MANUAL_FORMAT ||g_FormatOption == AUTO_FORMAT  ) {
			configFileCreator = &TMainForm::Create_FMT_ConfigFile;
#if 0			
			if (g_backup_restore_state == NOACTION) {
				configFileCreator = &TMainForm::Create_FMT_ConfigFile;
			} 			
			else if (g_backup_restore_state == BACKUPRESTORE) {
				configFileCreator = &TMainForm::Create_BK_FMT_RS_ConfigFile;
			}
#endif
		}
	} else if ( FLASHTOOL_READBACK == g_flashtool_function) {
		configFileCreator = &TMainForm::Create_RB_ConfigFile;
	} else if ( g_flashtool_function == FLASHTOOL_FIRMWARE_UPGRADE ) { 
		//FIXME Fomrat->Download might be needed for cosole mode?...
		configFileCreator = &TMainForm::Create_FMT_DL_ConfigFile;
	}
    if (configFileCreator == NULL)
    {
        MessageDlg("This operation is not supported in Command-Recording Mode",
                   mtError, TMsgDlgButtons() << mbOK, 0);
        return;
    }

    static AnsiString initialDirectory(GetCurrentDir());
    AnsiString filename("config.xml");

    if (!PromptForFileName(filename,
                          "FlashTool Console Mode config files (*.xml)|*.xml",
                          "xml", "", initialDirectory, true))
    {
        return;
    }

    // Record the initial directory
    initialDirectory = ExtractFilePath(filename);

    const TOleString oleStr(AnsiToOLESTR(filename.c_str()));
    (this->*configFileCreator)(static_cast<BSTR>(oleStr));
}

void TMainForm::Create_META_4in1_ConfigFile(const std::wstring &filename)
{
    Config config;

    config.SetGeneralSetting(CreateGeneralSetting());
    config.AddCommandSetting(Create_4IN1_Setting());
    config.SaveFile(filename, ConfigType::META_4IN1);
}

void TMainForm::Create_DL_ConfigFile(const std::wstring &filename)
{
    Config config;

    config.SetGeneralSetting(CreateGeneralSetting());
    config.AddCommandSetting(CreateDownloadSetting());
    config.SaveFile(filename, ConfigType::DOWNLOAD);
}

void TMainForm::Create_FMT_ConfigFile(const std::wstring &filename)
{
    Config config;

    config.SetGeneralSetting(CreateGeneralSetting());
    config.AddCommandSetting(CreateFormatSetting());
    config.SaveFile(filename, ConfigType::FORMAT);
}

void TMainForm::Create_RB_ConfigFile(const std::wstring &filename)
{
    Config config;

    config.SetGeneralSetting(CreateGeneralSetting());
    config.AddCommandSetting(CreateReadbackSetting());
    config.SaveFile(filename, ConfigType::READBACK);
}

void TMainForm::Create_RtFD_ConfigFile(const std::wstring &filename)
{
    Config config;

    config.SetGeneralSetting(CreateGeneralSetting());
    config.AddCommandSetting(CreateRtFDSetting());
    config.SaveFile(filename, ConfigType::RTFD);
}

void TMainForm::Create_DL_FMT_ConfigFile(const std::wstring &filename)
{
    Config config;

    config.SetGeneralSetting(CreateGeneralSetting());
    config.AddCommandSetting(CreateDownloadSetting());
    config.SaveFile(filename, ConfigType::DOWNLOAD_FORMAT);
}

void TMainForm::Create_DL_RtFD_ConfigFile(const std::wstring &filename)
{
    Config config;

    config.SetGeneralSetting(CreateGeneralSetting());
    config.AddCommandSetting(CreateDownloadSetting());
    config.AddCommandSetting(CreateRtFDSetting());
    config.SaveFile(filename, ConfigType::DOWNLOAD_RTFD);
}

void TMainForm::Create_BK_DL_RS_ConfigFile(const std::wstring &filename)
{
    Config config;

    config.SetGeneralSetting(CreateGeneralSetting());
    config.AddCommandSetting(CreateBackupSetting());
    config.AddCommandSetting(CreateDownloadSetting());
    config.AddCommandSetting(CreateRestoreSetting());
    config.SaveFile(filename, ConfigType::BACKUP_DOWNLOAD_RESTORE);
}

void TMainForm::Create_BK_DL_FMT_RS_ConfigFile(const std::wstring &filename)
{
    Config config;

    config.SetGeneralSetting(CreateGeneralSetting());
    config.AddCommandSetting(CreateBackupSetting());
    config.AddCommandSetting(CreateDownloadSetting());
    config.AddCommandSetting(CreateRestoreSetting());
    config.SaveFile(filename, ConfigType::BACKUP_DOWNLOAD_FORMAT_RESTORE);
}

void TMainForm::Create_BK_DL_RtFD_RS_ConfigFile(const std::wstring &filename)
{
    Config config;

    config.SetGeneralSetting(CreateGeneralSetting());
    config.AddCommandSetting(CreateBackupSetting());
    config.AddCommandSetting(CreateDownloadSetting());
    config.AddCommandSetting(CreateRtFDSetting());
    config.AddCommandSetting(CreateRestoreSetting());
    config.SaveFile(filename, ConfigType::BACKUP_DOWNLOAD_RTFD_RESTORE);
}

void TMainForm::Create_BK_FMT_RS_ConfigFile(const std::wstring &filename)
{
    Config config;

    config.SetGeneralSetting(CreateGeneralSetting());
    config.AddCommandSetting(CreateBackupSetting());
    config.AddCommandSetting(CreateFormatSetting());
    config.AddCommandSetting(CreateRestoreSetting());
    config.SaveFile(filename, ConfigType::BACKUP_FORMAT_RESTORE);
}

void TMainForm::Create_BK_RtFD_RS_ConfigFile(const std::wstring &filename)
{
    Config config;

    config.SetGeneralSetting(CreateGeneralSetting());
    config.AddCommandSetting(CreateBackupSetting());
    config.AddCommandSetting(CreateRtFDSetting());
    config.AddCommandSetting(CreateRestoreSetting());
    config.SaveFile(filename, ConfigType::BACKUP_RTFD_RESTORE);
}

void TMainForm::Create_FMT_DL_ConfigFile(const std::wstring &filename)
{
    Config config;

    config.SetGeneralSetting(CreateGeneralSetting());
    config.AddCommandSetting(CreateFormatSetting());
    config.AddCommandSetting(CreateDownloadSetting());
    config.SaveFile(filename, ConfigType::FORMAT_DOWNLOAD);
}

GeneralSetting TMainForm::CreateGeneralSetting()
{
    std::wostringstream comPort;
    std::wstring   str_OperationMethod;
    std::wstring   str_dl_operation;

    if (g_bUsbMode)
    {
        comPort << L"USB";
    }
    else
    {
        comPort << COM_PORT;
    }

	str_OperationMethod = Str2WStr(g_platform_info.getFlashToolStorageConfig().GetStorageName());

#if 0
    if( NAND_OPERATION == g_OperationMethod )
    {
        str_OperationMethod = L"NAND";
    }
    else  if( EMMC_OPERATION == g_OperationMethod )
    {
        str_OperationMethod = L"EMMC";
    }
    else
    {
        str_OperationMethod = L"NAND";
    }
#endif

    DA_INFO daInfo;
    DA_GetInfo(g_DA_HANDLE, &daInfo);

    const TOleString downloadAgentFilepath(AnsiToOLESTR(daInfo.filepath));
	const TOleString authenticationFilepath(AnsiToOLESTR(ed_AUTH_File->Text.c_str()));
	const TOleString scertFilePath(AnsiToOLESTR(ed_SCERT_File->Text.c_str()));

#if 0
    const TOleString flashBinFilepath(AnsiToOLESTR(ed_SCERT_File->Text.c_str()));
#endif
    if ((ed_AUTH_File->Text.Length() == 0) && (ed_SCERT_File->Text.Length() == 0)) {
        return GeneralSetting(g_bTrace,
                              comPort.str(),
                              str_OperationMethod,
                              g_bCheckECOVer,
                              static_cast<BSTR>(downloadAgentFilepath),
                              std::wstring(),
							  std::wstring());
	} else if ((ed_AUTH_File->Text.Length() == 0) ) {
       return GeneralSetting(g_bTrace,
                          comPort.str(),
                          str_OperationMethod,
                          g_bCheckECOVer,
                          static_cast<BSTR>(downloadAgentFilepath),
                          std::wstring(),
						  static_cast<BSTR>(scertFilePath));
	} else if ((ed_SCERT_File->Text.Length() == 0) ) {
       return GeneralSetting(g_bTrace,
                          comPort.str(),
                          str_OperationMethod,
                          g_bCheckECOVer,
                          static_cast<BSTR>(downloadAgentFilepath),
                          static_cast<BSTR>(authenticationFilepath),
						  std::wstring());
	} else {
       return GeneralSetting(g_bTrace,
                          comPort.str(),
                          str_OperationMethod,
                          g_bCheckECOVer,
                          static_cast<BSTR>(downloadAgentFilepath),
                          static_cast<BSTR>(authenticationFilepath),
						  static_cast<BSTR>(scertFilePath));
	}
}

DownloadSetting TMainForm::CreateDownloadSetting()
{
    std::vector<DownloadSetting::Download_Item> downloadList;

    DL_INFO downloadInfo;
    DL_GetInfo(g_pCurNode->m_dl_handle, &downloadInfo);

    if (downloadInfo.m_config.m_is_nfb)
    {
        BL_INFO info;

        if ((DL_BL_GetInfo(g_pCurNode->m_dl_handle, &info) == S_DONE) &&
            info.m_enable)
        {
            DownloadSetting::Download_Item       item;

            item.name =  L"BOOTLOADER";
            downloadList.push_back(item);
        }
    }

    unsigned short numRoms;
    DL_GetCount(g_pCurNode->m_dl_handle, &numRoms);

    ROM_INFO romInfo[MAX_LOAD_SECTIONS];
    DL_Rom_GetInfoAll(g_pCurNode->m_dl_handle, romInfo, MAX_LOAD_SECTIONS);

    for (unsigned short i=0; i<numRoms; ++i)
    {
        if (romInfo[i].enable)
        {
            const TOleString name(AnsiToOLESTR(romInfo[i].name));
            const TOleString path(AnsiToOLESTR(romInfo[i].filepath));

            DownloadSetting::Download_Item       item;

            item.name =  static_cast<BSTR>(name);
            item.path =  static_cast<BSTR>(path);

            downloadList.push_back(item);
        }
    }

    if (g_pCurNode->m_param.m_sec_ro_enable)
    {
        DownloadSetting::Download_Item       item;

        item.name =  L"SECURE_RO";
        downloadList.push_back(item);
    }

    const TOleString scatterFilepath(
                        AnsiToOLESTR(g_pCurNode->m_scat_file.c_str()));

    const bool autoFormatEnabled =
                    (g_FormatAfterDownloadOption == AUTO_FORMAT);

    unsigned int manualFormatBeginAddress = 0;
    unsigned int manualFormatLength = 0;

    if (g_FormatAfterDownloadOption == MANUAL_FORMAT)
    {
        manualFormatBeginAddress = g_ulNandFormatStartAddr;

        manualFormatLength = g_ulNandFormatLength;
    }

    const bool watchdogTimerEnabled = 
                    (g_FormatAfterDownloadOption == RESET_TO_FACTORY)/* ||
                    (g_backup_restore_state == BACKUPRESTORE)*/;

    std::wstring     wstr_dl_operation;

    if(FLASHTOOL_FLASHBIN == g_flashtool_function)
    {
        wstr_dl_operation =  L"dl-flash-only";
    }
    else
    {
        wstr_dl_operation =  L"dl-all";
    }

    std::wstring     wstr_dl_os;
    if(DUMA == g_project_mode)
    {
        wstr_dl_os =  L"WM";
    }
    else
    {
        wstr_dl_os =  L"Android";
    }


    const TOleString oles_dl_operation(
                        WideToOLESTR(wstr_dl_operation.c_str()));

    const TOleString oles_dl_os(
                        WideToOLESTR(wstr_dl_os.c_str()));

	bool isDADLAll = g_bDADownloadAll;
    bool isDADLHighSpeed = g_bDADownloadAll &&
		(g_platform_info.getPlatformConfig().supportUSBHighSpeed()) &&
		g_bSwitchSpeed;
	bool isDADLWithoutBat = g_bDADownloadAll &&
		!g_bUsbModeWithBattery;
	bool isDADLAllWithChksum = cb_da_dl_checksum_->Checked;

    return DownloadSetting(static_cast<BSTR>(scatterFilepath),
                           static_cast<BSTR>(oles_dl_operation),
                           static_cast<BSTR>(oles_dl_os),
                           downloadList,
                           autoFormatEnabled,
                           manualFormatBeginAddress,
                           manualFormatLength,
                           watchdogTimerEnabled,
						   isDADLAll,
						   isDADLHighSpeed,
						   isDADLWithoutBat,
                                                   isDADLAllWithChksum);
}

FormatSetting TMainForm::CreateFormatSetting()
{
    const bool autoFormatEnabled = /*false;*/(g_FormatOption == AUTO_FORMAT);

    const HW_StorageType_E storageType = g_platform_info.getFlashToolStorageConfig().GetStorageType();

    const unsigned int manualFormatBeginAddress = g_ulNandFormatStartAddr;

    const unsigned int manualFormatLength = g_ulNandFormatLength;

    const bool watchdogTimerEnabled = true;
                            //(g_backup_restore_state == BACKUPRESTORE);
    const unsigned int watchdogInterval = 5000;  

	bool isPhysicallyFormat;
	if( g_platform_info.getPlatformConfig().supportLogicalAddress() ) {
		isPhysicallyFormat = g_bPhysicallyFormatReadback;
	} else {
		isPhysicallyFormat = true;
	}    

    return FormatSetting(autoFormatEnabled,
                         storageType,
                         manualFormatBeginAddress,
                         manualFormatLength,
                         watchdogTimerEnabled,
                         watchdogInterval,
						 isPhysicallyFormat,
						 g_NandAutoFormatFlag);
}

ReadbackSetting TMainForm::CreateReadbackSetting()
{
    std::vector<ReadbackSetting::Readback_Item> rbList;
    unsigned short count;
    if ( ( S_DONE == RB_GetCount(g_RB_HANDLE, &count)) && ( 0<count ) ){
        RB_INFO	*rb=new RB_INFO[count];
        
        if( NULL != rb ) {
            if( S_DONE == RB_GetInfoAll(g_RB_HANDLE, rb, count) ) {
               for (unsigned short i = 0; i < count; i++)  {
                    if ( _TRUE == rb[i].enable )  {
                        unsigned short index = rb[i].index;
                        const NUTL_ReadFlag_E flag = rb[i].m_read_flag;
                        unsigned long long startAddr = rb[i].readback_addr;
                        unsigned int length = rb[i].readback_len;
                        const TOleString path(AnsiToOLESTR(rb[i].filepath));
                        
                        ReadbackSetting::Readback_Item item;
						item.SetReadbackIndex(index);
						item.SetReadbackFlag(flag);
						item.SetReadbackStartAddr(startAddr);
						item.SetReadbackLength(length);
						item.SetReadbackPath(static_cast<BSTR>(path));                    
                        rbList.push_back(item);
                    }
                }
            }
        } else {
            rb = NULL;
        }
        
        delete []rb;

        bool isPhysicalRB = g_bPhysicallyFormatReadback;

        return ReadbackSetting(rbList, isPhysicalRB);
    } else {
        MessageDlg("Readback list might be empty, please check readback list before generate readback xml!",
                   mtError, TMsgDlgButtons() << mbOK, 0);
        return ReadbackSetting(rbList, false);
    }
}

ResetToFactoryDefaultSetting TMainForm::CreateRtFDSetting()
{
    bool reconnectToMETAMode;

    if (g_flashtool_function == FLASHTOOL_DOWNLOAD)
    {
        reconnectToMETAMode = false;
    }
    else if (g_flashtool_function == FLASHTOOL_FORMAT)
    {
		assert( 0 && "Not Support!");
#if 0
        if (g_backup_restore_state == NOACTION)
        {
            reconnectToMETAMode = false;
        }
        else if (g_backup_restore_state == BACKUPRESTORE)
        {
            reconnectToMETAMode = true;
        }
#endif
    }
    else
    {
        // TODO
    }

    return ResetToFactoryDefaultSetting(reconnectToMETAMode);
}

Write_BT_WIFI_IMEI_NVRAM_Setting TMainForm::Create_4IN1_Setting()
{
    AnsiString str_is_write_IMEI1;
    AnsiString str_is_write_IMEI2;
    AnsiString str_is_write_WiFi;
    AnsiString str_is_write_BT;
    
    str_is_write_IMEI1 = (Form_FourInOne->m_bWriteIMEI1) ? "true" : "false";
    str_is_write_IMEI2 = (Form_FourInOne->m_bWriteIMEI2) ? "true" : "false"; 
    str_is_write_WiFi = (Form_FourInOne->m_bWriteWIFIAddr) ? "true" : "false";
    str_is_write_BT = (Form_FourInOne->m_bWriteBTAddr) ? "true" : "false"; 

    const TOleString ole_is_write_IMEI1(AnsiToOLESTR(str_is_write_IMEI1.c_str()));
    const TOleString ole_is_write_IMEI2(AnsiToOLESTR(str_is_write_IMEI2.c_str()));
    const TOleString ole_is_write_WiFi(AnsiToOLESTR(str_is_write_WiFi.c_str()));
    const TOleString ole_is_write_BT(AnsiToOLESTR(str_is_write_BT.c_str()));  
    
    const TOleString ole_Modem_Database(AnsiToOLESTR(Form_FourInOne->m_asModem_Database.c_str()));
    const TOleString ole_AP_Database(AnsiToOLESTR(Form_FourInOne->m_asAP_Database.c_str()));
    const TOleString ole_IMEI1_Number(AnsiToOLESTR(Form_FourInOne->m_asIMEI1_Number.c_str()));
    const TOleString ole_IMEI2_Number(AnsiToOLESTR(Form_FourInOne->m_asIMEI2_Number.c_str()));
    const TOleString ole_BT_Address(AnsiToOLESTR(Form_FourInOne->m_asBT_Address.c_str()));
    const TOleString ole_WiFi_Address(AnsiToOLESTR(Form_FourInOne->m_asWiFi_Address.c_str()));

    return Write_BT_WIFI_IMEI_NVRAM_Setting(
                                            static_cast<BSTR>(ole_is_write_IMEI1),
                                            static_cast<BSTR>(ole_is_write_IMEI2),
                                            static_cast<BSTR>(ole_is_write_WiFi),
                                            static_cast<BSTR>(ole_is_write_BT),                                            
                                            static_cast<BSTR>(ole_Modem_Database),
                                            static_cast<BSTR>(ole_AP_Database),
                                            static_cast<BSTR>(ole_IMEI1_Number),
                                            static_cast<BSTR>(ole_IMEI2_Number),
                                            static_cast<BSTR>(ole_BT_Address),
                                            static_cast<BSTR>(ole_WiFi_Address));
}

BackupSetting TMainForm::CreateBackupSetting()
{
    AnsiString str(gc_METABackupINI);
    const TOleString iniFilePath(AnsiToOLESTR(gc_METABackupINI.c_str()));

    str = ExtractFilePath(Application->ExeName) + "backup" + IntToStr(COM_PORT);

    const TOleString backupDirectoryPath(AnsiToOLESTR(str.c_str()));
    bool watchdogTimerEnabled;

    if (g_flashtool_function == FLASHTOOL_DOWNLOAD)
    {
        watchdogTimerEnabled = true;
    }
    else if (g_flashtool_function == FLASHTOOL_FORMAT)
    {
        watchdogTimerEnabled = (g_FormatOption != RESET_TO_FACTORY);
    }
    else
    {
        // TODO
    }

    return BackupSetting(static_cast<BSTR>(iniFilePath),
                         static_cast<BSTR>(backupDirectoryPath),
                         watchdogTimerEnabled);
}

RestoreSetting TMainForm::CreateRestoreSetting()
{
    AnsiString str(gc_METABackupINI);
    const TOleString iniFilePath(AnsiToOLESTR(str.c_str()));

    str = ExtractFilePath(Application->ExeName) + "backup" + IntToStr(COM_PORT);

    const TOleString restoreDirectoryPath(AnsiToOLESTR(str.c_str()));
    bool reconnectToMETAMode;

    if (g_flashtool_function == FLASHTOOL_DOWNLOAD)
    {
        reconnectToMETAMode =
                (g_FormatAfterDownloadOption == RESET_TO_FACTORY);
    }
    else if (g_flashtool_function == FLASHTOOL_FORMAT)
    {
        reconnectToMETAMode = (g_FormatOption == RESET_TO_FACTORY);
    }
    else
    {
        // TODO
    }

    return RestoreSetting(reconnectToMETAMode,
                          static_cast<BSTR>(iniFilePath),
                          static_cast<BSTR>(restoreDirectoryPath));
}
/*
//---------------------------------------------------------------------------
bool TMainForm::FileOpenDownloadAgentExecute ( void )
{
    static AnsiString asDA_Path;

    if ( asDA_Path.Length() > 0 )
    {
       OpenDownloadAgentDialog->InitialDir = asDA_Path;
    }
    else if( 0 < ed_DA_File->Text.Length() )
    {
        const int iLastDel = ed_DA_File->Text.LastDelimiter("\\:");

        if ( iLastDel > 0)
        {
	        OpenDownloadAgentDialog->InitialDir = ed_DA_File->Text.SubString(1, iLastDel-1 );
        }
	}

    if ( OpenDownloadAgentDialog->Execute() )    // *.bin file
    {
         if ( OpenReadDA_File( OpenDownloadAgentDialog->FileName, NORMAL_DA_BIN ))
         {
            asBin = OpenDownloadAgentDialog->FileName;

			if( g_bDebugDA ) {
				// save as TestMode DA path
				g_asTestModeDAPath   = asBin;
			}
			else {
				// save as NormalMode DA path
				g_asNormalModeDAPath = asBin;
			}

            const int iLastDel = asBin.LastDelimiter("\\:");

            if ( iLastDel > 0 ) {
                asDA_Path = asBin.SubString( 1, iLastDel-1 );
            }

            return true;
         }
         else {
            return false;
        }
    }
    else {
        return false;
    }
}*/

//---------------------------------------------------------------------------
bool TMainForm::FileOpenNandUtilBin(TOpenDialog *pOpenDialog,
                                    unsigned int daType)
{
    static AnsiString asDA_Path;

    if ( asDA_Path.Length() > 0 )
    {
       pOpenDialog->InitialDir = asDA_Path;
    }
    else if( 0 < ed_DA_File->Text.Length() )
    {
        const int iLastDel = ed_DA_File->Text.LastDelimiter("\\:");

        if ( iLastDel > 0)
        {
	        pOpenDialog->InitialDir = ed_DA_File->Text.SubString(1, iLastDel-1 );
        }
	}

    if ( pOpenDialog->Execute() )    // *.bin file
    {
         if ( OpenReadDA_File( pOpenDialog->FileName, daType))
         {
            asBin = pOpenDialog->FileName;

			if( g_bDebugDA ) {
				// save as TestMode DA path
				g_asTestModeDAPath   = asBin;
			}
			else if( NORMAL_DA_BIN == daType) {
				// save as NormalMode DA path
			    g_asNormalModeDAPath = asBin;
			}
            else if( NAND_UTIL_DA_BIN == daType) {
                asNandUtilDAPath = asBin;
            }

            const int iLastDel = asBin.LastDelimiter("\\:");

            if ( iLastDel > 0 ) {
                asDA_Path = asBin.SubString( 1, iLastDel-1 );
            }

            return true;
         }
         else {
            return false;
        }
    }
    else {
        return false;
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FileOpenDownloadAgentExecute(TObject *Sender)
{
    //FileOpenDownloadAgentExecute();
    FileOpenNandUtilBin(OpenDownloadAgentDialog, NORMAL_DA_BIN);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FileOpenNandUitlExecute(TObject *Sender)
{
    FileOpenNandUtilBin(OpenNandUtilFileDialog, NAND_UTIL_DA_BIN);
}
//---------------------------------------------------------------------------

bool TMainForm::Parse(MultiLoadNode *p_node, AnsiString asMapFileName, bool bAutoLoad)
{
    int ret;
    unsigned short count;

    if( NULL == p_node ) return false;

    DL_HANDLE_T &dl_handle = p_node->m_dl_handle;
    //Send image-type table before load scatter file, otherwise, default table will be used
    BromDLTypeTblEntry(dl_handle);
    // load scatter
	if( S_DONE != ( ret = DL_LoadScatter(dl_handle, asMapFileName.c_str() , g_platform_info.getLoadPlatformName().c_str()) ) )
    {
        if( S_FTHND_HANDLE_BUSY_NOW == ret )
        {
            ShowMessage("Program is busy! Can not reload scat file right now.");
        }
        else if( S_DL_SCAT_OFFSET_IS_NOT_WORD_ALIGN == ret )
        {
            ShowMessage("Failed to load scatter file \"" + asMapFileName + "\"!\n\nThe offset value of one load region is not WORD alignment!");
        }
        else if( S_DL_SCAT_ADDR_IS_NOT_WORD_ALIGN == ret )
        {
            ShowMessage("Failed to load scatter file \"" + asMapFileName + "\"!\n\nThe region begin address of one load region is not WORD alignment!");
        }
        else if( S_DL_SCAT_ADDR_IS_NOT_ASCENDING_ORDER == ret )
        {
            ShowMessage("Failed to load scatter file \"" + asMapFileName + "\"!\n\nThe region begin address of one load region is not ascending sorting sequence!");
        }
        else
        {
            ShowMessage("Incorrect scatter file format!");
        }
        return false;
    }
    
	p_node->m_scat_file = asMapFileName;

#if 0
    if( bAutoLoad )
    {
        // auto load download bin files
        // workaround for extra size of eMMC ICS load 
      /*  if(S_FILEPATH_NOT_SPECIFIED_YET == 
			DL_AutoLoadByScatRegionName( dl_handle, asMapFileName.c_str(), NORMAL_ROM|RESOURCE_BIN|JUMPTABLE_BIN|YAFFS_IMG, _TRUE )) {
				string errHint = "[Hint] Bootloader files are lost when automatically loading by scatter file.\n"
					"Please make sure you want to go through anyway.";
				ShowMessage(errHint.c_str());
		}*/

#if 0
        //possible access violation when ListView is empty
        if(mi_USBDownloadDA->Checked)
        {
    	    TListItem  *pItem=ListView1->Items->Item[0];
            ListViewItemType_E	type=*((ListViewItemType_E *)pItem->Data);

            if( (LV_NFB_BOOTLOADER == type) || (LV_NFB_EXT_BOOTLOADER == type) )
            {
                DL_BL_SetEnableAttr(dl_handle, _FALSE);
    	    }
            else if( LV_NOR_BOOTLOADER == type )
            {
                DL_Rom_SetEnableAttr(dl_handle, 0, _FALSE);
    	    }
        }
#endif
        //---------------------------------------------------------
        // update Parameter List
        AnsiString tmp_dir;
        AnsiString tmp_file;

        // initialize Check Box of SEC_RO and CUST_PARA
        tmp_dir = ExtractFileDir(asMapFileName);

        // 1. Load SEC_RO
        p_node->m_param.m_sec_ro_enable   = _TRUE;
        p_node->m_param.m_sec_ro_filepath = "";
        p_node->m_param.m_sec_ro.m_len    = 0;

        tmp_file = tmp_dir + "\\SECURE_RO";
        if( FileExists(tmp_file) )
        {
     		if( !LoadFile(tmp_file.c_str(), &p_node->m_param.m_sec_ro.m_data, &p_node->m_param.m_sec_ro.m_len, NULL) )
            {
                p_node->m_param.m_sec_ro_filepath = tmp_file;
            }
        }

        // 2. Load CUST_PARA
        p_node->m_param.m_cust_para_enable   = _TRUE;
        p_node->m_param.m_cust_para_filepath = "";
        p_node->m_param.m_cust_para.m_len    = 0;

        tmp_file = tmp_dir + "\\CUST_PARA";
        if( FileExists(tmp_file) )
        {
     		if( !LoadFile(tmp_file.c_str(), &p_node->m_param.m_cust_para.m_data, &p_node->m_param.m_cust_para.m_len, NULL) )
            {
                p_node->m_param.m_cust_para_filepath = tmp_file;
            }
        }

        // 3. Load GPS Project
        // Check if GPS Project exists
        AnsiString gps_dir = tmp_dir + "\\GPS";
        if( DirectoryExists(gps_dir) )
        {
            unsigned int bFindGpsRom = 0;

            p_node->m_param.m_gps_download = (_BOOL) true;

            AnsiString gps_rom = gps_dir + "\\M-core";
            AnsiString gps_ini = gps_dir + "\\gps.ini";

            if( FileExists(gps_rom) ) {
                bFindGpsRom = 1;
            }
            else
            {
                // search *.bin
                TSearchRec sr;
                if ( FindFirst(gps_dir+"\\*.bin", 0, sr) == 0 )
                {
                    do
                    {
                        gps_rom = gps_dir + "\\" + sr.Name;
                        bFindGpsRom = 1;
                        break;
                    } while ( FindNext(sr) == 0 );
                    FindClose(sr);
                }
            }

            if( bFindGpsRom && FileExists(gps_ini) )
            {
                p_node->m_param.m_gps_enable        = (_BOOL) true;
                p_node->m_param.m_gps_rom_dirpath   = gps_dir;
                p_node->m_param.m_gps_rom_filepath  = gps_rom;
                p_node->m_param.m_gps_ini_filepath  = gps_ini;

                LoadFileInfo(gps_rom.c_str(), &p_node->m_param.m_gps_rom_filesize, NULL);

                TIniFile *ini = new TIniFile( gps_ini );
            	p_node->m_param.m_gps_power_pin     = ini->ReadInteger( "GPIO", "gpio_gps_power_pin",   0xFFFF );
                p_node->m_param.m_gps_reset_pin     = ini->ReadInteger( "GPIO", "gpio_gps_reset_pin",   0xFFFF );
                p_node->m_param.m_gps_standby_pin   = ini->ReadInteger( "GPIO", "gpio_gps_standby_pin", 0xFFFF );
                p_node->m_param.m_gps_32k_pin       = ini->ReadInteger( "GPIO", "gpio_gps_32k_pin",     0xFFFF );
            }
            else
            {
                p_node->m_param.m_gps_enable   = (_BOOL) false;
            }
        }
        else{
            p_node->m_param.m_gps_download = (_BOOL) false;
        }
    }
#endif

    //Check BT type Uboot/Eboot (which project)
    unsigned short rom_count;
    ROM_INFO rom_info[MAX_LOAD_SECTIONS];
    if(!DL_GetCount(dl_handle, &rom_count))
    {
        ROM_INFO rom_info[MAX_LOAD_SECTIONS];
        if(!DL_Rom_GetInfoAll(dl_handle, rom_info, MAX_LOAD_SECTIONS))
        {
            for (int i=0; i<rom_count; i++)
            {
                if (strcmpi(rom_info[i].name, SCATTER_UBOOT_NAME) == 0)
                {
                    g_project_mode= YuSu;
                    break;
                }
                else if (strcmpi(rom_info[i].name, SCATTER_EOOT_NAME) == 0)
                {
                    g_project_mode=DUMA;
                    break;
                }
            }
        }
    }
#if 0
    // update project combox
    RedrawProjectComBox();
#endif
    // auto load ROMs
    AutoLoadYuSuROMs(p_node);

    //Fill in AP/BP database file path
    AutoFillDatabasePath(p_node);

#if 0
	if( g_project_mode == DUMA )
    {
        AutoLoadDUMAROMs(p_node);
    }
    else if (g_project_mode == YuSu)
    {
        AutoLoadYuSuROMs(p_node);

        //Fill in AP/BP database file path
        AutoFillDatabasePath(p_node);
    }
#endif
    RedrawReadbackList();
    RedrawDownloadList(p_node, false);
    
    // show Parameter List View
    //now disable parameter list
/*
    DL_INFO dl_info;
    if( !DL_GetInfo(dl_handle, &dl_info) )
    {
        if( dl_info.m_config.m_security_supported || p_node->m_param.m_gps_download ){
            m_ParamListView->Visible = true;
        }
        else{
            m_ParamListView->Visible = false;
        }
    }
*/
    return true;
}

//------------------------------------------------------------------------------
bool TMainForm::FileOpenLinkMapExecute(MultiLoadNode *p_node)
{
#if 0
    const char SCATTER_FILE_FOR_MT6573[] = "MT6573";
    const int SCATTER_FILE_LEN = strlen(SCATTER_FILE_FOR_MT6573);
#endif
    if( NULL ==  p_node ) {
        return false;
    }

    if ( ScatBaseDir.Length() > 0 )
    {
        OpenLdMapDialog->InitialDir = ScatBaseDir;
        OpenLdMapDialog->FileName   = "";
    }

    else if( 0 < ed_LinkMapFile->Text.Length() )
    {
        const int iLastDel = ed_LinkMapFile->Text.LastDelimiter("\\:");

        if ( iLastDel > 0)
        {
	        OpenLdMapDialog->InitialDir = ed_LinkMapFile->Text.SubString(1, iLastDel-1 );
		 OpenLdMapDialog->FileName   = "";
        }
    }

    if ( OpenLdMapDialog->Execute() )
    {
        /* Adapt new storage layout file, 2012/12/22 { */
#if 0
		std::string error_msg;
		bool isSCI = (MainForm->ts_SCIDownload == MainForm->pc_mainframe->ActivePage)
			           ||(MainForm->ts_SCIClone == MainForm->pc_mainframe->ActivePage);
		g_platform_info.initByScatterFile(OpenLdMapDialog->FileName.c_str(), error_msg, isSCI);
    	if(!g_platform_info.is_scatter_file_valid()) {
			ShowMessage(error_msg.c_str());
			return false;
		} else if (!g_platform_info.is_storage_type_support()) {
			ShowMessage(error_msg.c_str());
		}
#endif
        /* Adapt new storage layout file, 2012/12/22 } */
		
		/******Load configration XML files begin******/
		//Load usb_setting.xml table
		FlashToolUSBTable usb_table = GetFlashToolUSBTable();
		//Load storage_setting.xml table
		GetFlashToolStorageTable();
		/******Load configration XML files end******/
        const int iLastDel = OpenLdMapDialog->FileName.LastDelimiter("\\");
#if 0       
		const AnsiString DLG_FILE_NAME =
            (OpenLdMapDialog->FileName.SubString((iLastDel+1), SCATTER_FILE_LEN));

        if( 0 != strncmp(SCATTER_FILE_FOR_MT6573, DLG_FILE_NAME.c_str(), SCATTER_FILE_LEN) )
        {
        	const AnsiString HINT_VER = \
        			AnsiString("SP Flash Tool of this version ONLY supports ") + \
        			AnsiString(SCATTER_FILE_FOR_MT6573) + \
        			AnsiString(", please select a scatter file for ") + \
        			AnsiString(SCATTER_FILE_FOR_MT6573) + \
        			AnsiString("!");
        	ShowMessage(HINT_VER);
            return false;
        }
#endif

    	DL_Destroy(&g_DL_HANDLE_NODE.m_dl_handle);
        DL_Create(&g_DL_HANDLE_NODE.m_dl_handle);
    	if( Parse(p_node, OpenLdMapDialog->FileName, true))
        {
            if ( iLastDel > 0)
            {
               ScatBaseDir  = p_node->m_scat_file.SubString(1, iLastDel-1 );
//               ROMBaseDir   = ScatBaseDir;
            }
            /* Adapt new storage layout file, 2012/12/22 { */
            DL_PlatformInfo plat_info;
            DL_GetPlatformInfo(g_DL_HANDLE_NODE.m_dl_handle, &plat_info);
            std::string error_msg;
            bool isSCI = (MainForm->ts_SCIDownload == MainForm->pc_mainframe->ActivePage)
                ||(MainForm->ts_SCIClone == MainForm->pc_mainframe->ActivePage);
            g_platform_info.InitByPlatCfgInfo(plat_info, error_msg, isSCI);
            //load path will be used to find out PC checksum file.
            g_platform_info.set_load_path(string(ScatBaseDir.c_str()));
            
            //Update Auto Polling
            this->m_is_auto_polling_enable = g_platform_info.getPlatformConfig().IsAutoPollingEnable();
	     this->m_auto_polling_upper_limit = g_platform_info.getPlatformConfig().AutoPollingUpperLimit();
            LOGD("m_is_auto_polling_enable(%s), m_auto_polling_upper_limit(%d).",
            m_is_auto_polling_enable ? "true" : "false", m_auto_polling_upper_limit);

            //Update UI
            this->gb_NANDTest->Enabled = g_platform_info.getFlashToolStorageConfig().IsNandOperation();
	      this->gb_EMMCTest->Enabled = g_platform_info.getFlashToolStorageConfig().IsEMMCOperation();
            
            if(!g_platform_info.is_scatter_file_valid()) {
                ShowMessage(error_msg.c_str());
                return false;
            } else if (!g_platform_info.is_storage_type_support()) {
                ShowMessage(error_msg.c_str());
            }
            unsigned int bmt_block_count = 0;
            if ( g_platform_info.getPlatformConfig().supportLogicalAddress() && g_platform_info.getFlashToolStorageConfig().IsNandOperation()){
            int ret(S_DONE);                
            if((S_DONE != (ret = DL_GetBMTBlockCount(g_DL_HANDLE_NODE.m_dl_handle, &bmt_block_count))) ) {

                 ShowMessage("[Warning Hint] Get BMT block count fail, default BMT block count is used!");
                 LOGW("WARNING: TMainForm::Parse(): Get BMT block count failed(%d)! ",ret);
                 if(S_INVALID_BMTSIZE == ret){
                        g_platform_info.setBMTBlocks(PlatformInfo::DEFAULT_BMT_BLOCKS_MT6573);
                        g_platform_info.setDADownloadAllEnabled(false);
                        LOGW("Default BMT block count(%d) will be used.", PlatformInfo::DEFAULT_BMT_BLOCKS_MT6573);
                  }else{
                        //assert(0 && "DL_GetBMTBlockCount unknown error!");
                        LOGW("WARNING: TMainForm::Parse(): Get BMT block count failed(%d)! ",ret);
                  }
             } else {                                       
                    g_platform_info.setBMTBlocks(bmt_block_count);                    
                    g_platform_info.setDADownloadAllEnabled(true);
                    LOG("TMainForm::Parse(): Get BMT block count is %d.", bmt_block_count);		
                }
            }
            /* Adapt new storage layout file, 2012/12/22 } */
    	    return true;
    	}
    	else {
        	return false;
    	}
    }
	// do not add "else" !
    return false;
}
//------------------------------------------------------------------------------

void __fastcall TMainForm::FileOpenLinkMapExecute(TObject *Sender)
{
        g_scatter_type = NORMAL_SCATTER;
	
	FileOpenLinkMapExecute(g_pCurNode);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	g_platform_info.addObserver(this);
	isTbootWorking = false;
    WindowProc = SubClassWndProc;

    //CloseActiveSync();
    Application->OnException = DefaultExceptionHandle;
    m_pUpdateListLock = new TCriticalSection();

	// init META_DLL
	//META_Init(NULL);

	g_pCurNode = &g_DL_HANDLE_NODE;
	DL_HANDLE_T &dl_handle = g_pCurNode->m_dl_handle;

	//Default enable logs for tracking issues
	/* Enable log trace before invoking APIs, 2012/08/17 {*/
	if(ToolInfo::IsDefaultEnableLogs()) {
		g_bTrace = true;
		FileUtils::DebugLogsOn();
		UpdateCaption();
	}
	/* Enable log trace before invoking APIs, 2012/08/17 }*/

	DL_Create(&dl_handle);
	DA_Create(&g_DA_HANDLE);
    DA_Create(&g_NAND_UTIL_DA_HANDLE);
	RB_Create(&g_RB_HANDLE);
    RB_Create(&g_FU_RB_HANDLE);
	RB_Create(&g_CLONE_RB_HANDLE);
	RB_Create(&g_SW_Ver_RB_HANDLE);
	AUTH_Create(&g_AUTH_HANDLE);
	SCERT_Create(&g_SCERT_HANDLE);
    DL_CreateList(&g_DL_HANDLE_LIST);

    Android_ADV_Create(&g_Android_Adv_HANDLE);
        
    Timer_Download->Enabled = false;

    br_115200Execute(Sender);

	g_rootLoad = TreeView1->Items->AddChild( NULL, "Multi-Load");
	g_rootLoad->Data = NULL;

    // Open the FlashTool.ini and parse the ini file
    ReadFlashToolINI();
    // Open Android.INI to load Android download history
    ReadYuSuINI();

    // Compare the project ID
    DL_ResourceProjectIdComparisonSetting( dl_handle, g_CompareResProjectId?_TRUE:_FALSE );

	RedrawReadbackList();
	RedrawDownloadList( g_pCurNode, false );

    // show Parameter List View
    m_ParamListView->Visible = false;
    // now disable parameter list

    // show ts_Download tabsheet in first page
        ts_Download->Show();
    
    updateMenuItem();
    updateStatusBar();
#if 0    
	// show Project Combox
    cbxProject->Items->Add(g_as_project_selection_Array[DUMA]);
    cbxProject->Items->Add(g_as_project_selection_Array[YuSu]);
    cbxProject->ItemIndex= g_project_mode;

    //show download list
    cbxProjectChange(cbxProject);
#endif
    if(!ToolInfo::IsCustomerVer()){
        AutoUpdater::Instance()->AddObserver(this);
        AutoUpdater::Instance()->Start();
    }

}

//---------------------------------------------------------------------------
void __fastcall TMainForm::View_toolbarExecute(TObject *Sender)
{
/*
   if ( tb_Main->Visible )
   {
     tb_Main->Visible = false;
     mi_ToolBar->Checked = false;
   }
   else
   {
     tb_Main->Visible = true;
     mi_ToolBar->Checked = true;
   }
*/
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::View_StatusBarExecute(TObject *Sender)
{
/*
   if ( sb_Main->Visible )
   {
      sb_Main->Visible = false;
      mi_StatusBar->Checked = false;
   }
   else
   {
      sb_Main->Visible = true;
      mi_StatusBar->Checked = true;
   }
*/
}
//---------------------------------------------------------------------------

void TMainForm::updateStatusBar()
{
    if( g_bUsbMode  ) {
        sb_Main->Panels->Items[2]->Text = "USB";
    } else {
        sb_Main->Panels->Items[2]->Text = "COM"+IntToStr(COM_PORT);
    }

	//FIXME: urgly if/else...
	NvramOperation nvram_op = NVRAM_NO_ACTION;
	if (UPDATENVRAM == g_nvram_update_state) {
		nvram_op = NVRAM_FOUR_IN_ONE;
	} else if (FORMAT_DL_UPDATENVRAM == g_nvram_update_state) {
		nvram_op = NVRAM_FOUR_IN_ONE_WITH_FORMAT;
	}
//	} else if (BACKUP_FORMAT_DOWNLOAD_RESTORE == g_backup_restore_state) {
//		nvram_op = NVRAM_FIRMWARE_UPGRADE;
//    }

    OperationIndicator op_indicator;
	op_indicator.SetDADLALL(g_bDADownloadAll);
	op_indicator.SetDADLAttr(g_bSwitchSpeed, 
		!g_bUsbModeWithBattery, 
		g_platform_info.getPlatformConfig().supportDLAutoDetectBattery());
	op_indicator.SetNvramOp(nvram_op);
	m_HWStatus->Panels->Items[2]->Text = op_indicator.GetDADLHint().c_str();
	//m_HWStatus->Panels->Items[3]->Text = op_indicator.QueryNvramOperationHint(nvram_op).c_str();

    switch ( BAUD_RATE )
    {
        case UART_BAUD_921600:
             sb_Main->Panels->Items[3]->Text = "921600 bps";
             break;
        case UART_BAUD_460800:
             sb_Main->Panels->Items[3]->Text = "460800 bps";
             break;
        case UART_BAUD_230400:
             sb_Main->Panels->Items[3]->Text = "230400 bps";
             break;
        case UART_BAUD_115200:
             sb_Main->Panels->Items[3]->Text = "115200 bps";
             break;
        case UART_BAUD_57600:
             sb_Main->Panels->Items[3]->Text = "57600 bps";
             break;
        case UART_BAUD_38400:
             sb_Main->Panels->Items[3]->Text = "38400 bps";
             break;
        case UART_BAUD_19200:
             sb_Main->Panels->Items[3]->Text = "19200 bps";
             break;
        case UART_BAUD_9600:
             sb_Main->Panels->Items[3]->Text = "9600 bps";
             break;
        default :
             if (DEBUG)
             ShowMessage(" main.cpp : undefined Baud Rate " + IntToStr( COM_PORT));
             break;
     }

	sb_Main->Panels->Items[1]->Text = g_platform_info.getFlashToolStorageConfig().GetStorageName().c_str();
#if 0
	switch ( g_OperationMethod )
    {
	    case NAND_OPERATION:
		    sb_Main->Panels->Items[1]->Text = "NAND";
		    break;

	    case EMMC_OPERATION:
		    sb_Main->Panels->Items[1]->Text = "EMMC";
		    break;
            
	    default:
		    sb_Main->Panels->Items[1]->Text = "UNKNOWN";
		    break;
	}
#endif
}

//--------------------------------------------------

void TMainForm::updateMenuItem()
{
    // MCU TYPE
    m_AutoBBCHIP->Checked   = false;
   	BBCHIP_MT6573_E1->Checked  = false;
   	BBCHIP_MT6573_E2->Checked = false;
    BBCHIP_UNKNOWN->Checked = false;

    switch( g_SP_BBCHIP_TYPE )
    {
   	    case MT6573_E1:
            BBCHIP_MT6573_E1->Checked = true;
            BaudRate1->Enabled = true;
            DCOMPort->Enabled = true;
            mi_USBDownloadDA->Enabled = false;
            mi_USBDownloadDA->Checked = false;
            break;

        case MT6573_E2:
    	    BBCHIP_MT6573_E2->Checked = true;
            BaudRate1->Enabled = false;
            DCOMPort->Enabled = false;
            mi_USBDownloadDA->Enabled = true;
            mi_USBDownloadDA->Checked = true;
            break;
        /*
        case SP_UNKNOWN_BBCHIP_TYPE:
    	    BBCHIP_UNKNOWN->Checked = true;
            BaudRate1->Enabled = true;
            DCOMPort->Enabled = true;
            mi_USBDownloadDA->Enabled = true;
            mi_USBDownloadDA->Checked = false;
            break;
        */
        default:
	        m_AutoBBCHIP->Checked = true;
            break;
	}
    //Update USB DL DA menu
    if(g_bUsbMode){
    	mi_USBDownloadDA->Checked = true; 
		BaudRate1->Enabled              = false;
		DCOMPort->Enabled               = false;
        //enable DA Download All when USB Mode is enabled
		//And target supports BMT
		g_bDADownloadAll = true;
		if(g_platform_info.isDADownloadAllEnabled()){
			m_Menu_DA_DL_all->Enabled = true;
		}
    }else{
       	mi_USBDownloadDA->Checked = false;
		BaudRate1->Enabled              = true;
		DCOMPort->Enabled               = true;
		//disable DA Download All when USB Mode is disabled
        	g_bDADownloadAll = false;
		g_bSwitchSpeed = false;
	
		m_Menu_DA_DL_all->Enabled = false;
    }

    if(g_bDADownloadAll){
    	m_Menu_DA_DL_all->Checked = true;
    	m_Menu_DA_DL_all_no->Checked = false;

    	if(g_bSwitchSpeed){
    		m_Menu_DA_DL_all_full->Checked = false;
    		m_Menu_DA_DL_all_high->Checked = true;
    	}else{
    		m_Menu_DA_DL_all_full->Checked = true;
    		m_Menu_DA_DL_all_high->Checked = false;
    	}
		
		if(g_bUsbModeWithBattery){
    		m_Menu_USB_mode_with_bat->Checked = true;
    		m_Menu_USB_mode_without_bat->Checked = false;
    	}else{
    		m_Menu_USB_mode_with_bat->Checked = false;
			m_Menu_USB_mode_without_bat->Checked = true;
    	}
        //Disable operations with Pre-Loader
		//IMEI/WiFi/BT//Backup->Format->Download->Restore
        //g_backup_restore_state =  NOACTION;
		g_nvram_update_state    = NOACTIONNVRAM ;
		//m_Menu_Backup_Restore_NVRAM->Enabled = false;
		MainForm->m_Menu_FourInOne->Enabled = false;
		//2011.08.10 add for DA DL All checksum
		MainForm->cb_da_dl_checksum_->Enabled = true;
    }else{
    	m_Menu_DA_DL_all->Checked = false;
    	m_Menu_DA_DL_all_no->Checked = true;
    	m_Menu_DA_DL_all_full->Checked = false;
		m_Menu_DA_DL_all_high->Checked = false;
		m_Menu_USB_mode_with_bat->Checked = false;
		m_Menu_USB_mode_without_bat->Checked = false;
		//Enable operations with Pre-Loader
		//Backup->Format->Download->Restore & IMEI/WiFi/BT
		Platform config = g_platform_info.getPlatformConfig(); //FIXME
        if(config.supportFirmwareUpgrade()) {
        m_Menu_Backup_Restore_NVRAM->Enabled = true;
        }
		MainForm->m_Menu_FourInOne->Enabled = false;
	    //2011.08.10 add for DA DL All checksum
		MainForm->cb_da_dl_checksum_->Enabled = false;
		MainForm->cb_da_dl_checksum_->Checked = false;
    }

    // MCU FREQUENCY
    m_AutoExtClock->Checked = false;

    MCU_13MHz->Enabled = true;
    MCU_26MHz->Enabled = true;
    MCU_52MHz->Enabled = true;

   	MCU_13MHz->Checked = false;
   	MCU_26MHz->Checked = false;
   	MCU_52MHz->Checked = false;

    switch( g_EXT_CLOCK )
    {
        case EXT_13M:
    	    MCU_13MHz->Checked  = true;
            break;

        case EXT_26M:
    	    MCU_26MHz->Checked  = true;
            break;

        case EXT_52M:
    	    MCU_52MHz->Checked  = true;
            break;

        default:
	        m_AutoExtClock->Checked = true;
            break;
	}

    uncheckAllBaudRate();

    mi_921600->Enabled = true;
    mi_460800->Enabled = true;
    mi_230400->Enabled = true;
    mi_57600->Enabled  = true;
    mi_38400->Enabled  = true;
    mi_19200->Enabled  = true;
    mi_9600->Enabled   = true;

    switch ( BAUD_RATE )
    {
        case UART_BAUD_921600:
            mi_921600->Checked = true;
            break;
        case UART_BAUD_460800:
            mi_460800->Checked = true;
            break;
        case UART_BAUD_230400:
            mi_230400->Checked = true;
            break;
        case UART_BAUD_115200:
            mi_115200->Checked = true;
            break;
        case UART_BAUD_57600:
            mi_57600->Checked  = true;
            break;
        case UART_BAUD_38400:
            mi_38400->Checked  = true;
            break;
        case UART_BAUD_19200:
            mi_19200->Checked  = true;
            break;
        case UART_BAUD_9600:
            mi_9600->Checked   = true;
            break;
        default :
            if (DEBUG) ShowMessage(" main.cpp : undefined Baud Rate " + IntToStr( COM_PORT ));
            break;
     }

    switch( g_FormatAfterDownloadOption )
    {
	    case RESET_TO_FACTORY:
		    mi_FormatFDM->Checked = true;
		    mi_FormatFDM->Caption = "Format FAT (RESET FACTORY DEFAULT) ...";
		    break;

	    case AUTO_FORMAT:
		    mi_FormatFDM->Checked = true;
		    mi_FormatFDM->Caption = "Format FAT (AUTO) ...";
		    break;

	    case MANUAL_FORMAT:
		    mi_FormatFDM->Checked = true;
		    mi_FormatFDM->Caption = "Format FAT (MANUAL) ...";
		    break;

	    case DISABLE_FORMAT:
	    default:
		    mi_FormatFDM->Checked = false;
		    mi_FormatFDM->Caption = "Format FAT (DISABLED) ...";
		    break;
	}

#if 0
    // update restore NVRAM item
    switch( g_backup_restore_state )
    {
	    case BACKUP_FORMAT_DOWNLOAD_RESTORE:
            m_Menu_Backup_Restore_NVRAM->Caption = "Backup Restore NVRAM (Backup NVRAM -> Format -> Download -> Restore NVRAM) ...";
            m_subMenu_Backup_Restore_NoAction->Checked = false;
            m_subMenu_Backup_Format_DL_Restore_NVRAM->Checked = true;
            m_subMenu_Format_DL_Restore_NVRAM->Checked = false;
            m_subMenu_Restore_NVRAM_Only->Checked = false;
            m_Menu_Backup_Restore_NVRAM->Checked = true;
			//Firmware upgrade 2.0 (Phase one) restore(download) BinRegion.img by Pre-Loader
			//Disable DA DL All
			//m_Menu_DA_DL_all->Enabled = false;
		    break;
        case FORMAT_DOWNLOAD_RESTORE_NVRAM:
    		m_Menu_Backup_Restore_NVRAM->Caption = "Backup Restore NVRAM (Format -> Download -> Restore NVRAM) ...";
            m_subMenu_Backup_Restore_NoAction->Checked = false;
            m_subMenu_Backup_Format_DL_Restore_NVRAM->Checked = false;
            m_subMenu_Format_DL_Restore_NVRAM->Checked = true;
            m_subMenu_Restore_NVRAM_Only->Checked = false;
            m_Menu_Backup_Restore_NVRAM->Checked = true;
			//Firmware upgrade 2.0 (Phase one) restore(download) BinRegion.img by Pre-Loader
			//Disable DA DL All
			//m_Menu_DA_DL_all->Enabled = false;
		    break;
        case RESTORE_NVRAM_ONLY:
            m_Menu_Backup_Restore_NVRAM->Caption = "Backup Restore NVRAM (Restore NVRAM Only) ...";
            m_subMenu_Backup_Restore_NoAction->Checked = false;
            m_subMenu_Backup_Format_DL_Restore_NVRAM->Checked = false;
            m_subMenu_Format_DL_Restore_NVRAM->Checked = false;
            m_subMenu_Restore_NVRAM_Only->Checked = true;
            m_Menu_Backup_Restore_NVRAM->Checked = true;
		    break;
	    case NOACTION:
        default:
            m_Menu_Backup_Restore_NVRAM->Caption = "Backup Restore NVRAM (No Action) ...";
            m_subMenu_Backup_Restore_NoAction->Checked = true;
            m_subMenu_Backup_Format_DL_Restore_NVRAM->Checked = false;
            m_subMenu_Format_DL_Restore_NVRAM->Checked = false;
            m_subMenu_Restore_NVRAM_Only->Checked = false;
            m_Menu_Backup_Restore_NVRAM->Checked = false;
			//Firmware upgrade 2.0 (Phase one) restore(download) BinRegion.img by Pre-Loader
			//No Action: Enable DA DL All
			//m_Menu_DA_DL_all->Enabled = true;
		    break;
    }
#endif
    // update NVRAM  item
    switch( g_nvram_update_state )
    {

	    case UPDATENVRAM:
		    m_Menu_FourInOne->Caption = "Write IMEI/BT/WiFi (Download -> Write IMEI/BT/WiFi) ...";
                    m_subMenu_FourInOne_NoAction->Checked = false;
                    m_subMenu_FourInOne_Write->Checked = true;
                    m_subMenu_Format_DL_FourInOne_Write->Checked = false;
                    m_Menu_FourInOne->Checked = false;
		    break;
 	    case FORMAT_DL_UPDATENVRAM:
		    m_Menu_FourInOne->Caption = "Write IMEI/BT/WiFi (Format -> Download -> Write IMEI/BT/WiFi) ...";
                    m_subMenu_FourInOne_NoAction->Checked = false;
                    m_subMenu_FourInOne_Write->Checked = false;
                    m_subMenu_Format_DL_FourInOne_Write->Checked = true;
                    m_Menu_FourInOne->Checked = false;
		    break;
	    case NOACTIONNVRAM:
            default:
                    m_Menu_FourInOne->Caption = "Write IMEI/BT/WiFi (No Action) ...";
                    m_subMenu_FourInOne_NoAction->Checked = true;
                    m_subMenu_FourInOne_Write->Checked = false;
                    m_subMenu_Format_DL_FourInOne_Write->Checked = false;
                    m_Menu_FourInOne->Checked = false;
		    break;
    }


        m_CheckECOVersion->Checked = false;


    if( g_bCheckTgtResourceLayout ) {
	    m_CheckTgtResourceLayout->Checked = true;
    } else {
	    m_CheckTgtResourceLayout->Checked = false;
    }

    if( g_bAutoLoadResByScat ) {
	    m_AutoLoadResByScat->Checked = true;
    } else {
	    m_AutoLoadResByScat->Checked = false;
    }

    if( g_bPullDownGPIO17 ) {
    	m_PullDownGPIO17->Checked = true;
    } else {
    	m_PullDownGPIO17->Checked = false;
    }

   	if( g_SpeedUpBootROMBaudrate ) {
        m_SpeedUpBootROMBaudrate->Checked = true;
	} else {
        m_SpeedUpBootROMBaudrate->Checked = false;
	}

   	if( g_CompareResProjectId ) {
        m_CompareProjectId->Checked = true;
	} else {
        m_CompareProjectId->Checked = false;
	}

   	if( g_bNFI_SelectCS1 ) {
        m_EnableNFICS1->Checked = true;
	} else {
        m_EnableNFICS1->Checked = false;
	}

    if( g_bDownloadStyleSequential ) {
        DownloadStyle->Checked = true;
    } else {
        DownloadStyle->Checked = false;
    }

	m_Menu_OPM_NAND->Checked = g_platform_info.getFlashToolStorageConfig().IsNandOperation();
	m_Menu_OPM_EMMC->Checked  = g_platform_info.getFlashToolStorageConfig().IsEMMCOperation();
#if 0
    switch( g_OperationMethod )
    {
	    case NAND_OPERATION:
		    m_Menu_OPM_NAND->Checked = true;
		    break;

	    case EMMC_OPERATION:
		    m_Menu_OPM_EMMC->Checked  = true;
		    break;  

	    default:
            assert(0 && "Storage is unknown!");
		    break;
	}
#endif

    if(ToolInfo::IsCustomerVer()){
        MainForm->m_Menu_FourInOne->Visible = false;
    }

#if 0
    switch( g_project_mode )
    {
            case DUMA:
                 m_Menu_IMEI_update->Enabled = true;
                 //m_Menu_Backup_Restore_NVRAM->Visible = false;
                 bb_FlashBin->Enabled = true;   //Flash.bin button
                 tb_DLFlashBinButton->Enabled = true;   //DL Flash.bin button
                 m_Menu_Window_CheckParameterPage->Enabled = false;
                 m_Menu_Window_CheckParameterPage->Checked = false;
                 ts_Paremeter->TabVisible = false; // Disable Paremeter tab under WinMo

                 break;
            case YuSu:
                 m_Menu_IMEI_update->Enabled = true;
                 //m_Menu_Backup_Restore_NVRAM->Visible = true;
                 bb_FlashBin->Enabled = false;
                 tb_DLFlashBinButton->Enabled = false;
                 m_Menu_Window_CheckParameterPage->Enabled = true; // YuSu Image Lock Setting
                 break;

            default:
                 break;
    }
#endif
#if 0
    //Disable Firmware Upgrade/IMEI+WiFi+BT when storage type is EMMC
	//FIXME when EMMC and SDMMC support firmware upgrade
	if(!g_platform_info.getPlatformConfig().supportFirmwareUpgrade()) {
		tb_FirmwareUpgradeButton->Enabled = false;
		m_Menu_FourInOne->Enabled = false;
		m_Menu_Backup_Restore_NVRAM->Enabled = false;
	} else {
		m_Menu_FourInOne->Enabled = false;
		m_Menu_Backup_Restore_NVRAM->Enabled = true;

		//Disable Format->DL ToolBarButton when Nvram data is to be modified
		if( /*(g_backup_restore_state != NOACTION) ||*/
			(g_nvram_update_state != NOACTIONNVRAM) ){
			tb_FirmwareUpgradeButton->Enabled = false;
		} else {
			tb_FirmwareUpgradeButton->Enabled = true;
		}

	}
#endif
#if 0
    //Backup/Restore folder type
    if( g_backup_restore_state != NOACTION ) {
        UseChipIDasBackupFolderName->Checked =  (BY_RID == g_backup_restore_folder_type);
        UseCOMPortasBackupFolderName->Checked = !(UseChipIDasBackupFolderName->Checked);
    }
    else {
        g_backup_restore_folder_type = BY_NONE;
        UseChipIDasBackupFolderName->Checked = false;
        UseCOMPortasBackupFolderName->Checked = false;
    }
#endif
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::m_AutoExtClockClick(TObject *Sender)
{
	g_EXT_CLOCK = AUTO_DETECT_EXT_CLOCK;
	updateMenuItem();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MCU_13MHzClick(TObject *Sender)
{
	g_EXT_CLOCK = EXT_13M;

	updateStatusBar();
	updateMenuItem();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::MCU_26MHzClick(TObject *Sender)
{
	g_EXT_CLOCK = EXT_26M;

	updateStatusBar();
	updateMenuItem();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::MCU_52MHzClick(TObject *Sender)
{
	g_EXT_CLOCK = EXT_52M;

	updateStatusBar();
	updateMenuItem();
}

//---------------------------------------------------------------------------
void TMainForm::uncheckAllBaudRate()
{
   mi_921600->Checked = false;    // High Speed
   mi_460800->Checked = false;
   mi_230400->Checked = false;
   mi_115200->Checked = false;
   mi_57600->Checked  = false;
   mi_38400->Checked  = false;
   mi_19200->Checked  = false;
   mi_9600->Checked   = false;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mi_921600Click(TObject *Sender)
{
   BAUD_RATE  = UART_BAUD_921600;
   uncheckAllBaudRate();
   mi_921600->Checked = true;
   updateStatusBar();
   PL_3Click(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::br_460800Execute(TObject *Sender)
{
   BAUD_RATE  = UART_BAUD_460800;
   uncheckAllBaudRate();
   mi_460800->Checked = true;
   updateStatusBar();
   PL_3Click(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::br_230400Execute(TObject *Sender)
{
   BAUD_RATE  = UART_BAUD_230400;
   uncheckAllBaudRate();
   mi_230400->Checked = true;
   updateStatusBar();
   PL_2Click(Sender);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::br_115200Execute(TObject *Sender)
{
   BAUD_RATE  = UART_BAUD_115200;
   uncheckAllBaudRate();
   mi_115200->Checked = true;

   updateStatusBar();
   PL_2Click(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::br_19200Execute(TObject *Sender)
{

    BAUD_RATE  = UART_BAUD_19200;
    uncheckAllBaudRate();
    mi_19200->Checked = true;

    updateStatusBar();
    PL_1Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::br_57600Execute(TObject *Sender)
{
    BAUD_RATE  = UART_BAUD_57600;
    uncheckAllBaudRate();
    mi_57600->Checked = true;

    updateStatusBar();
    PL_1Click(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::br_38400Execute(TObject *Sender)
{
    BAUD_RATE  = UART_BAUD_38400;
    uncheckAllBaudRate();
    mi_38400->Checked = true;

    updateStatusBar();
    PL_1Click(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::br_9600Execute(TObject *Sender)
{
    BAUD_RATE  = UART_BAUD_9600;
    uncheckAllBaudRate();
    mi_9600->Checked = true;
    updateStatusBar();
    PL_1Click(Sender);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::mi_DEBUGClick(TObject *Sender)
{
   if (DEBUG)
   {
      DEBUG = false;
      ShowMessage(" disable DEBUG ");
   }
   else
   {
      DEBUG = true;
      ShowMessage(" enable DEBUG ");
   }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ExitExecute(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
    //RestartActiveSync("");

    if( g_project_mode == YuSu)
    {
        WriteBackYuSuINI();
    }
    
    WriteBackFlashToolINI();

    DL_Destroy(&g_DL_HANDLE_NODE.m_dl_handle);

    if( NULL != g_DL_HANDLE_NODE.m_param.m_sec_ro.m_data ){
        free(g_DL_HANDLE_NODE.m_param.m_sec_ro.m_data);
    }
    if( NULL != g_DL_HANDLE_NODE.m_param.m_cust_para.m_data ){
        free(g_DL_HANDLE_NODE.m_param.m_cust_para.m_data );
    }
    if( NULL != g_DL_HANDLE_NODE.m_param.m_otp.m_data ){
        free(g_DL_HANDLE_NODE.m_param.m_otp.m_data);
    }

    DA_Destroy(&g_DA_HANDLE);
    DA_Destroy(&g_NAND_UTIL_DA_HANDLE);
    RB_Destroy(&g_RB_HANDLE);
    RB_Destroy(&g_FU_RB_HANDLE);
	RB_Destroy(&g_CLONE_RB_HANDLE);
	RB_Destroy(&g_SW_Ver_RB_HANDLE);
    AUTH_Destroy(&g_AUTH_HANDLE);
	SCERT_Destroy(&g_SCERT_HANDLE);
    DL_DestroyList(&g_DL_HANDLE_LIST);

    Android_ADV_Destory(&g_Android_Adv_HANDLE);

    // destroy META_DLL
    // META_Deinit();
		
	//Default enable logs for tracking issues
	if(ToolInfo::IsDefaultEnableLogs()) {
		if(g_bTrace) {
			g_bTrace = false;
			FileUtils::DebugLogsOff();
			UpdateCaption();
		}
	}
}

//---------------------------------------------------------------------------
void TMainForm::ReadYuSuINI( void )
{
	string androidDir = FileUtils::GetAppDirectory()+"\\Android";
    string iniPath = androidDir + "\\Android.INI";

    if(!FileUtils::IsDirectoryExist(androidDir) ||
        !FileUtils::IsFileExist(iniPath)){
        //return directly if ini not exists.
        return;
    }

    AnsiString asYuSuiniFile =  iniPath.c_str();

    TIniFile *ini;
    try{
    ini = new TIniFile(asYuSuiniFile);
    }catch(...){
    	return;
    }
/****************************************** [DL_HISTORY_X] Section *************************************************/

    g_DownloadHistory.clear();
    // load download history
    for( int i=0; i < MAX_DOWNLOAD_HISTORY; i++ )
    {
        DownloadSet		dl_set;
        int	file_count = ini->ReadInteger( "DL_HISTORY_"+IntToStr(i), "file_count", 1 );

	    dl_set.m_Scatter = ini->ReadString( "DL_HISTORY_"+IntToStr(i), "scatter_file", "");
        /*
	    if( dl_set.m_Scatter.IsEmpty() ) {

           LoadDefultScatter( g_pCurNode,str_scatt_path.c_str());
           break;
	    }*/

        if ( dl_set.m_Scatter.IsEmpty()) {
            continue;
		}

        //dl_set.m_BootLoader	   = ini->ReadString ( "DL_HISTORY_"+IntToStr(i), "bootloader", "" );
        //dl_set.m_BootLoader_Enable = ini->ReadBool   ( "DL_HISTORY_"+IntToStr(i), "bootloader_enable", true );


        for ( int j=0; j < file_count; j++ )
        {
            DownloadBinFile		dl_bin;
            dl_bin.m_Filepath = ini->ReadString ( "DL_HISTORY_"+IntToStr(i), "file"+IntToStr(j), "" );
            dl_bin.m_Enable   = ini->ReadBool   ( "DL_HISTORY_"+IntToStr(i), "file"+IntToStr(j)+"_enable", true );
            dl_set.m_BinFiles.push_back( dl_bin );
        }

	    g_DownloadHistory.push_back( dl_set );
    }

#if 0
    // load 1st history
    if( 0 < g_DownloadHistory.size() ) {
        /*bool ret=*/ LoadByDownloadSet( *g_DownloadHistory.begin(), g_pCurNode );
        /*
        if(!ret) {
            LoadDefultScatter( g_pCurNode,str_scatt_path.c_str());
        }*/
    }
#endif


/****************************************** [FORM] Section *************************************************/
    AnsiString asNull;
    asNandUtilDAPath = ini->ReadString("FORM", "NandUtilDAPath", "");
#if 0 
	// AUTH file
	ed_AUTH_File->Text = ini->ReadString( "FORM", "AUTH_File", "");

    int ret = S_DONE;

    //won't load auth file automatically
	if( 0 < ed_AUTH_File->Text.Length() )
    {
		if( S_DONE != ( ret = AUTH_Load( g_AUTH_HANDLE, ed_AUTH_File->Text.c_str())) )
        {
			if( S_FTHND_HANDLE_BUSY_NOW == ret )
            {
				ShowMessage( "Program is busy! Can not update setting right now." );
			}
			else {
				ShowMessage( "Load Authentication File \"" + ed_AUTH_File->Text + "\" fail!" );
			}
		}
	}
#endif
    if( NULL != asNandUtilDAPath.data())
    {
	    if ( !OpenReadDA_File( asNandUtilDAPath, NAND_UTIL_DA_BIN) )
        {
            ed_NandUtil_File->Text = "";
            asNandUtilDAPath = "";
        }
    }
    else
    {
        ed_NandUtil_File->Text = "";
        asNandUtilDAPath = "";
    }

/****************************************** [DOWNLOAD] Section ****************************************************/

/****************************************** [READBACK] Section *************************************************/

/****************************************** [TRANS_OPTION] Section *************************************************/

/****************************************** [EMI] Section *************************************************/

    delete ini;
}
#if 0
//---------------------------------------------------------------------------
void TMainForm::ReadDUMAINI( void )
{
	string winMoDir = FileUtils::GetAppDirectory()+"\\WinMo";
    string str_scatt_path = winMoDir + "\\MT6516_WinMo_scatter.txt";
    string str_ini_path = winMoDir + "\\WinMobile.INI";

    if(!FileUtils::IsDirectoryExist(winMoDir) ||
        !FileUtils::IsFileExist(str_ini_path)){
        //return directly if ini not exists.
        return;
    }

    AnsiString asDUMAiniFile =  str_ini_path.c_str();

    TIniFile *ini;
    try{
    ini = new TIniFile(asDUMAiniFile);
    }catch(...){
    	return;
    }
/****************************************** [DL_HISTORY_X] Section *************************************************/

    // load download history
    g_DownloadHistory.clear();
    for( int i=0; i < MAX_DOWNLOAD_HISTORY; i++ )
    {
		DownloadSet		dl_set;

		dl_set.m_Scatter = ini->ReadString( "DL_HISTORY_"+IntToStr(i), "scatter_file", "");

		if( dl_set.m_Scatter.IsEmpty() ) {

                         LoadDefultScatter( g_pCurNode,str_scatt_path.c_str());
			break;
		}
        if( dl_set.m_Scatter.Length() == 1 && dl_set.m_Scatter.c_str()[0] == '0'){
            continue;
        }

		dl_set.m_BootLoader	       = ini->ReadString ( "DL_HISTORY_"+IntToStr(i), "bootloader", "" );
		dl_set.m_BootLoader_Ext    = ini->ReadString ( "DL_HISTORY_"+IntToStr(i), "bootloader_ext", "" );
		dl_set.m_BootLoader_Enable = ini->ReadBool   ( "DL_HISTORY_"+IntToStr(i), "bootloader_enable", true );

		const int file_count = ini->ReadInteger( "DL_HISTORY_"+IntToStr(i), "file_count", 1 );

		for ( int j=0; j < file_count; j++ )
        {
			DownloadBinFile		dl_bin;
			dl_bin.m_Filepath = ini->ReadString ( "DL_HISTORY_"+IntToStr(i), "file"+IntToStr(j), "" );
			dl_bin.m_Enable   = ini->ReadBool   ( "DL_HISTORY_"+IntToStr(i), "file"+IntToStr(j)+"_enable", true );
			dl_set.m_BinFiles.push_back( dl_bin );
		}
		g_DownloadHistory.push_back( dl_set );
	}

	// load 1st history
	if( 0 < g_DownloadHistory.size() ) {
	       bool ret= LoadByDownloadSet( *g_DownloadHistory.begin(), g_pCurNode );

               if(!ret) {
                    LoadDefultScatter( g_pCurNode,str_scatt_path.c_str());
                    }

	}


/****************************************** [FORM] Section *************************************************/
 /*
    AnsiString asNull;

    // Flash bin file
    ed_SPBIN_File->Text  = ini->ReadString ( "FORM", "flash_bin", "" );

    // AUTH file
	ed_AUTH_File->Text = ini->ReadString( "FORM", "AUTH_File", "" );

    int ret = S_DONE;

	if( 0 < ed_AUTH_File->Text.Length() )
    {
		if( S_DONE != ( ret = AUTH_Load( g_AUTH_HANDLE, ed_AUTH_File->Text.c_str())) )
        {
			if( S_FTHND_HANDLE_BUSY_NOW == ret )
            {
				ShowMessage( "Program is busy! Can not update setting right now." );
			}
			else {
				ShowMessage( "Load Authentication File \"" + ed_AUTH_File->Text + "\" fail!" );
			}
		}
	}
*/
    delete ini;
}
#endif
//---------------------------------------------------------------------------
void TMainForm::ReadFlashToolINI( void )
{
    string str_da_path = FileUtils::GetAppDirectory() + "\\MTK_AllInOne_DA.bin";
    TIniFile *ini;
    ini = new TIniFile(gc_FlashToolINI);

    /****************************************** [PROJECT] Section *************************************************/
    int index    =  ini->ReadInteger( "PROJECT", "project", YuSu );
    g_project_mode = (Project_Operation_E)index;
/****************************************** [DL_HISTORY_X] Section *************************************************/

   
/****************************************** [FORM] Section *************************************************/

    g_bPullDownGPIO17  = ini->ReadBool ( "FORM", "pull_down_gpio17", true );

    COM_PORT           = ini->ReadInteger ( "FORM", "com", 1 );

    g_MaxBromStartCmdRetryCount = ini->ReadInteger ( "FORM", "brom_start_cmd_retry_count", DEFAULT_BROM_START_CMD_RETRY_COUNT );
    m_BRomStartCmdRetryCount->Caption.printf ( "BootROM start cmd retry (%d) ...", g_MaxBromStartCmdRetryCount );


    int iBaudRate    =  ini->ReadInteger( "FORM", "baudrate", 921600 );
	switch ( iBaudRate )
	{
		case 921600:
			BAUD_RATE = UART_BAUD_921600;
			break;
		case 460800:
			BAUD_RATE = UART_BAUD_460800;
			break;
		case 230400:
			BAUD_RATE = UART_BAUD_230400;
			break;
		case 115200:
			BAUD_RATE = UART_BAUD_115200;
			break;
		case 57600:
			BAUD_RATE = UART_BAUD_57600;
			break;
		case 38400:
			BAUD_RATE = UART_BAUD_38400;
			break;
		case 19200:
			BAUD_RATE = UART_BAUD_19200;
			break;
		case 9600:
			BAUD_RATE = UART_BAUD_9600;
			break;
		default:
			BAUD_RATE = UART_BAUD_19200;
			break;
	}
    //DL Options
    g_bUsbMode = ini->ReadBool( "FORM", "usb_mode", false);
    //g_bUsbModeWithBattery = ini->ReadBool( "FORM", "dl_with_battery", true);
	//g_bDADownloadAll = ini->ReadBool( "FORM", "da_dl_all", false);
	//g_bDAEnableHS = ini->ReadBool( "FORM", "da_enable_hs", false);
   
    AnsiString asNull;

    g_asNormalModeDAPath = asBin = ini->ReadString ( "FORM", "bin", asNull );

    g_asTestModeDAPath   = ini->ReadString ( "FORM", "testmode_da_path", g_asNormalModeDAPath );

	if ( access( asBin.c_str(), 0 ) != 0 ) {
		asBin.SetLength(0);
                asBin= str_da_path.c_str();
                LoadDefultDA( asBin);
	}
	else {
		// load DA
		OpenReadDA_File( asBin, NORMAL_DA_BIN);
	}

	g_FormatValidation = ini->ReadInteger ( "FORM", "erase_validation", false );

        // Flash bin file
 //       ed_SPBIN_File->Text  = ini->ReadString ( "FORM", "flash_bin", "" );
#if 0 
	// AUTH file
	ed_AUTH_File->Text = ini->ReadString( "FORM", "AUTH_File", asNull );

    int ret;

  //won't load auth file automatically
	if( 0 < ed_AUTH_File->Text.Length() )
    {
		if( S_DONE != ( ret = AUTH_Load( g_AUTH_HANDLE, ed_AUTH_File->Text.c_str())) )
        {
			if( S_FTHND_HANDLE_BUSY_NOW == ret )
            {
				ShowMessage( "Program is busy! Can not update setting right now." );
			}
			else {
				ShowMessage( "Load Authentication File \"" + ed_AUTH_File->Text + "\" fail!" );
			}
		}
	}

	// SCERT file
	ed_SCERT_File->Text = ini->ReadString( "FORM", "SCERT_File", asNull );

	if( 0 < ed_SCERT_File->Text.Length() )
    {
		if( S_DONE != ( ret = SCERT_Load( g_SCERT_HANDLE, ed_SCERT_File->Text.c_str())) )
        {
			if( S_FTHND_HANDLE_BUSY_NOW == ret )
            {
				ShowMessage( "Program is busy! Can not update CERT File right now." );
			}
			else {
				ShowMessage( "Load Certification File \"" + ed_SCERT_File->Text + "\" fail!" );
			}
		}
	}
#endif
	iFlashItemIndex = ini->ReadInteger( "FORM", "flashitemindex", 2 );

	g_ulNandFormatStartAddr = StrToInt64(ini->ReadString( "FORM", "FormatStartAddr", "0x0000000000000000").c_str());
	g_ulNandFormatLength    = StrToInt64(ini->ReadString( "FORM", "FormatLength", "0x0000000000000000").c_str());
    g_FormatOption          = (FormatOption_E) ini->ReadInteger( "FORM", "FormatOption", MANUAL_FORMAT );
/****************************************** [DOWNLOAD] Section ****************************************************/
	g_bCheckTgtResourceLayout   = ini->ReadBool( "DOWNLOAD", "chk_tgt_resource_layout", true );
	g_bCheckECOVer              = ini->ReadBool( "DOWNLOAD", "check_bbchip_eco_ver", false );
    g_bAutoLoadResByScat        = ini->ReadBool( "DOWNLOAD", "auto_load_resource_by_scat", true );
	//g_FormatAfterDownloadOption = (FormatOption_E) ini->ReadInteger( "DOWNLOAD", "FormatAfterDownloadOption", DISABLE_FORMAT );
    g_FormatAfterDownloadOption =  DISABLE_FORMAT ;
    g_CompareResProjectId       = ini->ReadBool ( "DOWNLOAD", "compare_resource_project_id", true);


/****************************************** [READBACK] Section *************************************************/

    int iReadBackCount = ini->ReadInteger( "READBACK", "readback_count", 0 );

    if ( iReadBackCount > 0)
    {
        for ( int i=0; i < iReadBackCount; i++ )
        {
			AnsiString as_rb_file       = ini->ReadString( "READBACK", "file"+IntToStr(i), "ROM_"+ IntToStr( i ));
			bool enable                 = ini->ReadBool  ( "READBACK", "file"+IntToStr(i)+"_enable", true);
			NUTL_ReadFlag_E	read_flag   = (NUTL_ReadFlag_E) ini->ReadInteger( "READBACK", "file"+IntToStr(i)+"_read_flag", NUTL_READ_PAGE_SPARE);

			AnsiString as_readback_addr = ini->ReadString( "READBACK", "startaddr"+IntToStr(i), "0x0000000000000000" );
			AnsiString as_readback_len  = ini->ReadString( "READBACK", "length"+IntToStr(i),    "0x00001000" );

			unsigned long long readback_addr = StrToInt64(as_readback_addr.c_str());
			unsigned long readback_len  = strtoul( as_readback_len.c_str() , NULL, 16);

			if ( !RB_Append( g_RB_HANDLE, as_rb_file.c_str(), readback_addr, readback_len ) )
            {
				RB_SetEnableAttr(g_RB_HANDLE, i, enable?_TRUE:_FALSE);
				RB_SetReadbackFlag(g_RB_HANDLE, i, read_flag);
			}
        }
    }


/****************************************** [TRANS_OPTION] Section *************************************************/

    g_PacketLength            = ini->ReadInteger ( "TRANS_OPTION", "packet_length", 1024 );
    g_Baudrate_FullSync_Count = ini->ReadInteger ( "TRANS_OPTION", "baudrate_full_sync_count", 1 );
    g_SpeedUpBootROMBaudrate  = ini->ReadBool    ( "TRANS_OPTION", "speedup_brom_baudrate", true);


/****************************************** [EMI] Section *************************************************/
    for ( int i=0 ; i<2 ; i++ )
    {
		g_EMI_Config[i].m_bAuto  = ini->ReadBool ( "EMI", "bank"+IntToStr(i)+"_auto", true);
		g_EMI_Config[i].m_Config = strtoul(ini->ReadString( "EMI", "bank"+IntToStr(i)+"_cfg", "0x00004102" ).c_str(), NULL, 16);
	}

	// NAND NFI Setting
	g_EMI_NFI_Setting.m_bAuto           = ini->ReadBool ( "EMI", "nand_acccon_auto", true);
	g_EMI_NFI_Setting.m_nand_acccon     = strtoul(ini->ReadString ( "EMI", "nand_acccon", "0x000007FF" ).c_str(), NULL, 16);
	// manual DRAM EMI Setting
	g_EMI_NFI_Setting.m_dram_cfg.m_emi_gen_a        = strtoul(ini->ReadString ( "EMI", "emi_gen_a", "0x0000030A" ).c_str(), NULL, 16);
	g_EMI_NFI_Setting.m_dram_cfg.m_emi_gen_b        = strtoul(ini->ReadString ( "EMI", "emi_gen_b", "0x00666660" ).c_str(),       NULL, 16);
	g_EMI_NFI_Setting.m_dram_cfg.m_emi_gen_c        = strtoul(ini->ReadString ( "EMI", "emi_gen_c", "0x00666666" ).c_str(), NULL, 16);
   	g_EMI_NFI_Setting.m_dram_cfg.m_emi_gen_d        = strtoul(ini->ReadString ( "EMI", "emi_gen_d", "0x0001000E" ).c_str(), NULL, 16);
    g_EMI_NFI_Setting.m_dram_cfg.m_emi_con_i        = strtoul(ini->ReadString ( "EMI", "emi_con_i", "0x00314000" ).c_str(), NULL, 16);
	g_EMI_NFI_Setting.m_dram_cfg.m_emi_con_i_ext    = strtoul(ini->ReadString ( "EMI", "emi_don_i_ext", "0x0" ).c_str(),    NULL, 16);
	g_EMI_NFI_Setting.m_dram_cfg.m_emi_con_j        = strtoul(ini->ReadString ( "EMI", "emi_con_j", "0x2DA12620" ).c_str(), NULL, 16);
	g_EMI_NFI_Setting.m_dram_cfg.m_emi_con_k        = strtoul(ini->ReadString ( "EMI", "emi_con_k", "0x00180000" ).c_str(), NULL, 16);
	g_EMI_NFI_Setting.m_dram_cfg.m_emi_con_l        = strtoul(ini->ReadString ( "EMI", "emi_con_l", "0x00015004" ).c_str(), NULL, 16);
	g_EMI_NFI_Setting.m_dram_cfg.m_emi_con_m        = strtoul(ini->ReadString ( "EMI", "emi_con_m", "0x0" ).c_str(),        NULL, 16);
	g_EMI_NFI_Setting.m_dram_cfg.m_emi_con_n        = strtoul(ini->ReadString ( "EMI", "emi_con_n", "0x00530001" ).c_str(), NULL, 16);

	g_EMI_NFI_Setting.m_dram_cfg.m_emi_del_a        = strtoul(ini->ReadString ( "EMI", "emi_del_a", "0x0" ).c_str(), NULL, 16);
	g_EMI_NFI_Setting.m_dram_cfg.m_emi_del_b        = strtoul(ini->ReadString ( "EMI", "emi_del_b", "0x0" ).c_str(), NULL, 16);
	g_EMI_NFI_Setting.m_dram_cfg.m_emi_del_c        = strtoul(ini->ReadString ( "EMI", "emi_del_c", "0x0" ).c_str(), NULL, 16);
	g_EMI_NFI_Setting.m_dram_cfg.m_emi_del_d        = strtoul(ini->ReadString ( "EMI", "emi_del_d", "0x0" ).c_str(), NULL, 16);
	g_EMI_NFI_Setting.m_dram_cfg.m_emi_del_e        = strtoul(ini->ReadString ( "EMI", "emi_del_e", "0x0" ).c_str(), NULL, 16);
	g_EMI_NFI_Setting.m_dram_cfg.m_emi_del_f        = strtoul(ini->ReadString ( "EMI", "emi_del_f", "0x0" ).c_str(), NULL, 16);
	g_EMI_NFI_Setting.m_dram_cfg.m_emi_del_g        = strtoul(ini->ReadString ( "EMI", "emi_del_g", "0x0" ).c_str(), NULL, 16);
	g_EMI_NFI_Setting.m_dram_cfg.m_emi_del_h        = strtoul(ini->ReadString ( "EMI", "emi_del_h", "0x0" ).c_str(), NULL, 16);
	g_EMI_NFI_Setting.m_dram_cfg.m_emi_del_i        = strtoul(ini->ReadString ( "EMI", "emi_del_i", "0x22220000" ).c_str(), NULL, 16);
	g_EMI_NFI_Setting.m_dram_cfg.m_emi_del_j        = strtoul(ini->ReadString ( "EMI", "emi_del_j", "0x12000000" ).c_str(), NULL, 16);
	g_EMI_NFI_Setting.m_dram_cfg.m_emi_arb_a        = strtoul(ini->ReadString ( "EMI", "emi_arb_a", "0x0" ).c_str(), NULL, 16);
	g_EMI_NFI_Setting.m_dram_cfg.m_emi_arb_b        = strtoul(ini->ReadString ( "EMI", "emi_arb_b", "0x0" ).c_str(), NULL, 16);
	g_EMI_NFI_Setting.m_dram_cfg.m_emi_arb_c        = strtoul(ini->ReadString ( "EMI", "emi_arb_c", "0x0" ).c_str(), NULL, 16);
	g_EMI_NFI_Setting.m_dram_cfg.m_emi_arb_d        = strtoul(ini->ReadString ( "EMI", "emi_arb_d", "0x0" ).c_str(), NULL, 16);
	g_EMI_NFI_Setting.m_dram_cfg.m_emi_arb_e        = strtoul(ini->ReadString ( "EMI", "emi_arb_e", "0x0" ).c_str(), NULL, 16);
	g_EMI_NFI_Setting.m_dram_cfg.m_emi_arb_f        = strtoul(ini->ReadString ( "EMI", "emi_arb_f", "0x0" ).c_str(), NULL, 16);
	g_EMI_NFI_Setting.m_dram_cfg.m_emi_arb_g        = strtoul(ini->ReadString ( "EMI", "emi_arb_g", "0x0" ).c_str(), NULL, 16);
	g_EMI_NFI_Setting.m_dram_cfg.m_emi_arb_h        = strtoul(ini->ReadString ( "EMI", "emi_arb_h", "0x0" ).c_str(), NULL, 16);
	g_EMI_NFI_Setting.m_dram_cfg.m_emi_arb_i        = strtoul(ini->ReadString ( "EMI", "emi_arb_i", "0x0" ).c_str(), NULL, 16);

	// update packet length
	UpdatePacketLength ( g_PacketLength );
#if 0
/****************************************** [BACKUP_FORMAT_DOWNLOAD_RESTORE NVRAM] Section *************************************************/
    g_backup_restore_state =
        (BACKUP_RESTORE_STATE_E)ini->ReadInteger( "BACKUP_FORMAT_DOWNLOAD_RESTORE", "BackupRestoreState",  NOACTION);
    g_backup_restore_folder_type =
        (BACKUP_FOLDER_TYPE_E)ini->ReadInteger("BACKUP_FORMAT_DOWNLOAD_RESTORE", "BackupRestoreFolderType", BY_NONE);
#endif                                   
 /****************************************** [WRITE_MEMORY] Section *************************************************/
    g_WM_RawDataFilePath  = ini->ReadString( "WRITE_MEMORY", "raw_data_path", "");
    g_WM_address = StrToInt64(ini->ReadString( "WRITE_MEMORY", "start_addr", "0x0000000000000000").c_str());
    g_WM_container_length  = strtoul(ini->ReadString( "WRITE_MEMORY", "constainer_length", "0x00000000").c_str(), NULL, 16);
   
	if(!g_WM_RawDataFilePath.IsEmpty()) {
        unsigned int raw_data_len = 0;
		AnsiString s;
		if(MainForm->LoadFileInfo(g_WM_RawDataFilePath.c_str(), &raw_data_len, NULL)) {
			s.printf("Fail to load a raw data file \"%s\" !", g_WM_RawDataFilePath.c_str());
			ShowMessage(s);
			// reset File path and File size
			ed_WM_OpenRawData->Text = " ";
			lb_WM_OpenRawDataFileSizeValue->Caption = "0  (Bytes)";
		} else {
            s.printf("0x%016I64X",raw_data_len);
            lb_WM_OpenRawDataFileSizeValue->Caption = s + "  (Bytes)";
		}
	}

    delete ini;
}
//---------------------------------------------------------------------------
void TMainForm::WriteBackYuSuINI( void )
{
    unsigned int	i;
    DownloadHistoryList::iterator	iter;

	string androidDir = FileUtils::GetAppDirectory()+"\\Android";

	FileUtils::CheckDirectory(androidDir); //will create the dir if not exists.

    string iniPath = androidDir + "\\Android.INI";
    AnsiString asYuSuiniFile =  iniPath.c_str();

    TIniFile *ini;
    try {
          ini = new TIniFile(asYuSuiniFile);
    } catch (...) {
        return;
    }


/****************************************** [EMI] Section *************************************************/

/****************************************** [FORM] Section *************************************************/
    ini->WriteString ( "FORM", "NandUtilDAPath",             asNandUtilDAPath);
#if 0
    ini->WriteString ( "FORM", "AUTH_File",                  ed_AUTH_File->Text );
#endif
/****************************************** [DOWNLOAD] Section ****************************************************/

/****************************************** [DL_HISTORY_X] Section *************************************************/

    // erase existing section first
    for ( i=0; i<MAX_DOWNLOAD_HISTORY; i++ )
    {
		ini->EraseSection ( "DL_HISTORY_"+IntToStr(i));
    }

	// save download history
    for ( i=0, iter=g_DownloadHistory.begin(); i<MAX_DOWNLOAD_HISTORY && iter!=g_DownloadHistory.end(); i++, iter++)
    {
		// write new section data
		ini->WriteString  ( "DL_HISTORY_"+IntToStr(i), "scatter_file",      iter->m_Scatter);
		//ini->WriteString  ( "DL_HISTORY_"+IntToStr(i), "bootloader",        iter->m_BootLoader);
		//ini->WriteBool    ( "DL_HISTORY_"+IntToStr(i), "bootloader_enable", iter->m_BootLoader_Enable);
		ini->WriteInteger ( "DL_HISTORY_"+IntToStr(i), "file_count",        iter->m_BinFiles.size());

		for ( unsigned int j=0; j<iter->m_BinFiles.size(); j++ )
        {
			ini->WriteString ( "DL_HISTORY_"+IntToStr(i), "file"+IntToStr(j), iter->m_BinFiles[j].m_Filepath);
			ini->WriteBool   ( "DL_HISTORY_"+IntToStr(i), "file"+IntToStr(j)+"_enable", iter->m_BinFiles[j].m_Enable);
		}
	}


/****************************************** [READBACK] Section *************************************************/

/****************************************** [TRANS_OPTION] Section *************************************************/

	delete ini;
}
#if 0
//---------------------------------------------------------------------------
void TMainForm::WriteBackDUMAINI( void )
{
	unsigned int	i;
	DownloadHistoryList::iterator	iter;

	string winMoDir = FileUtils::GetAppDirectory()+"\\WinMo";
	FileUtils::CheckDirectory(winMoDir); //will create the dir if not exists.

    string iniPath = winMoDir + "\\WinMobile.INI";
    AnsiString asDUMAiniFile =  iniPath.c_str();

    TIniFile *ini;
    try {
          ini = new TIniFile(asDUMAiniFile);
    } catch (...) {
        return;
    }


/****************************************** [EMI] Section *************************************************/

/****************************************** [IMEI] Section *************************************************/

/****************************************** [FORM] Section *************************************************/


        ini->WriteString ( "FORM", "flash_bin",                  ed_SPBIN_File->Text );
        ini->WriteString ( "FORM", "AUTH_File",                  ed_AUTH_File->Text );
/****************************************** [DOWNLOAD] Section ****************************************************/

/****************************************** [DL_HISTORY_X] Section *************************************************/

	// erase existing section first
	for ( i=0; i<MAX_DOWNLOAD_HISTORY; i++ )
        {
		ini->EraseSection ( "DL_HISTORY_"+IntToStr(i));
	}

	// save download history
	for ( i=0, iter=g_DownloadHistory.begin(); i<MAX_DOWNLOAD_HISTORY && iter!=g_DownloadHistory.end(); i++, iter++)
        {
		// write new section data
		ini->WriteString  ( "DL_HISTORY_"+IntToStr(i), "scatter_file",      iter->m_Scatter);
		ini->WriteString  ( "DL_HISTORY_"+IntToStr(i), "bootloader",        iter->m_BootLoader);
		ini->WriteString  ( "DL_HISTORY_"+IntToStr(i), "bootloader_ext",    iter->m_BootLoader_Ext);
		ini->WriteBool    ( "DL_HISTORY_"+IntToStr(i), "bootloader_enable", iter->m_BootLoader_Enable);
		ini->WriteInteger ( "DL_HISTORY_"+IntToStr(i), "file_count",        iter->m_BinFiles.size());

		for ( unsigned int j=0; j<iter->m_BinFiles.size(); j++ )
                {
			ini->WriteString ( "DL_HISTORY_"+IntToStr(i), "file"+IntToStr(j), iter->m_BinFiles[j].m_Filepath);
			ini->WriteBool   ( "DL_HISTORY_"+IntToStr(i), "file"+IntToStr(j)+"_enable", iter->m_BinFiles[j].m_Enable);
		}
	}


/****************************************** [READBACK] Section *************************************************/

/****************************************** [TRANS_OPTION] Section *************************************************/

	delete ini;
}
#endif
//---------------------------------------------------------------------------
void TMainForm::WriteBackFlashToolINI( void )
{
	unsigned int	i;
	DownloadHistoryList::iterator	iter;

    TIniFile *ini;

    try {
        ini = new TIniFile(gc_FlashToolINI);
    } catch (...) {
        return;
    }
/****************************************** [PROJECT] Section *************************************************/
    //int index    =  g_project_mode;
    //ini->WriteInteger( "PROJECT", "project", index );
/****************************************** [EMI] Section *************************************************/
	for ( i=0; i<2; i++ )
    {
		ini->WriteBool  ( "EMI", "bank"+IntToStr(i)+"_auto", g_EMI_Config[i].m_bAuto );
		ini->WriteString( "EMI", "bank"+IntToStr(i)+"_cfg", "0x"+IntToHex((int)(g_EMI_Config[i].m_Config), 8));
	}

//NAND NFI Setting
	ini->WriteBool  ( "EMI", "nand_acccon_auto", g_EMI_NFI_Setting.m_bAuto);
	ini->WriteString( "EMI", "nand_acccon", "0x"+IntToHex((int)(g_EMI_NFI_Setting.m_nand_acccon), 8));

//DRAM EMI Setting
	ini->WriteString( "EMI", "emi_gen_a", "0x"+IntToHex((int)(g_EMI_NFI_Setting.m_dram_cfg.m_emi_gen_a), 8));
	ini->WriteString( "EMI", "emi_gen_b", "0x"+IntToHex((int)(g_EMI_NFI_Setting.m_dram_cfg.m_emi_gen_b), 8));
	ini->WriteString( "EMI", "emi_gen_c", "0x"+IntToHex((int)(g_EMI_NFI_Setting.m_dram_cfg.m_emi_gen_c), 8));
	ini->WriteString( "EMI", "emi_gen_d", "0x"+IntToHex((int)(g_EMI_NFI_Setting.m_dram_cfg.m_emi_gen_d), 8));
	ini->WriteString( "EMI", "emi_con_i", "0x"+IntToHex((int)(g_EMI_NFI_Setting.m_dram_cfg.m_emi_con_i), 8));
	ini->WriteString( "EMI", "emi_con_i_ext", "0x"+IntToHex((int)(g_EMI_NFI_Setting.m_dram_cfg.m_emi_con_i_ext), 8));
	ini->WriteString( "EMI", "emi_con_j", "0x"+IntToHex((int)(g_EMI_NFI_Setting.m_dram_cfg.m_emi_con_j), 8));
	ini->WriteString( "EMI", "emi_con_k", "0x"+IntToHex((int)(g_EMI_NFI_Setting.m_dram_cfg.m_emi_con_k), 8));
	ini->WriteString( "EMI", "emi_con_l", "0x"+IntToHex((int)(g_EMI_NFI_Setting.m_dram_cfg.m_emi_con_l), 8));
	ini->WriteString( "EMI", "emi_con_m", "0x"+IntToHex((int)(g_EMI_NFI_Setting.m_dram_cfg.m_emi_con_m), 8));
	ini->WriteString( "EMI", "emi_con_n", "0x"+IntToHex((int)(g_EMI_NFI_Setting.m_dram_cfg.m_emi_con_n), 8));
	ini->WriteString( "EMI", "emi_del_a", "0x"+IntToHex((int)(g_EMI_NFI_Setting.m_dram_cfg.m_emi_del_a), 8));
	ini->WriteString( "EMI", "emi_del_b", "0x"+IntToHex((int)(g_EMI_NFI_Setting.m_dram_cfg.m_emi_del_b), 8));
	ini->WriteString( "EMI", "emi_del_c", "0x"+IntToHex((int)(g_EMI_NFI_Setting.m_dram_cfg.m_emi_del_c), 8));
	ini->WriteString( "EMI", "emi_del_d", "0x"+IntToHex((int)(g_EMI_NFI_Setting.m_dram_cfg.m_emi_del_d), 8));
	ini->WriteString( "EMI", "emi_del_e", "0x"+IntToHex((int)(g_EMI_NFI_Setting.m_dram_cfg.m_emi_del_e), 8));
	ini->WriteString( "EMI", "emi_del_f", "0x"+IntToHex((int)(g_EMI_NFI_Setting.m_dram_cfg.m_emi_del_f), 8));
	ini->WriteString( "EMI", "emi_del_g", "0x"+IntToHex((int)(g_EMI_NFI_Setting.m_dram_cfg.m_emi_del_g), 8));
	ini->WriteString( "EMI", "emi_del_h", "0x"+IntToHex((int)(g_EMI_NFI_Setting.m_dram_cfg.m_emi_del_h), 8));
	ini->WriteString( "EMI", "emi_del_i", "0x"+IntToHex((int)(g_EMI_NFI_Setting.m_dram_cfg.m_emi_del_i), 8));
	ini->WriteString( "EMI", "emi_del_j", "0x"+IntToHex((int)(g_EMI_NFI_Setting.m_dram_cfg.m_emi_del_j), 8));
	ini->WriteString( "EMI", "emi_arb_a", "0x"+IntToHex((int)(g_EMI_NFI_Setting.m_dram_cfg.m_emi_arb_a), 8));
	ini->WriteString( "EMI", "emi_arb_b", "0x"+IntToHex((int)(g_EMI_NFI_Setting.m_dram_cfg.m_emi_arb_b), 8));
	ini->WriteString( "EMI", "emi_arb_c", "0x"+IntToHex((int)(g_EMI_NFI_Setting.m_dram_cfg.m_emi_arb_c), 8));
	ini->WriteString( "EMI", "emi_arb_d", "0x"+IntToHex((int)(g_EMI_NFI_Setting.m_dram_cfg.m_emi_arb_d), 8));
	ini->WriteString( "EMI", "emi_arb_e", "0x"+IntToHex((int)(g_EMI_NFI_Setting.m_dram_cfg.m_emi_arb_e), 8));
	ini->WriteString( "EMI", "emi_arb_f", "0x"+IntToHex((int)(g_EMI_NFI_Setting.m_dram_cfg.m_emi_arb_f), 8));
	ini->WriteString( "EMI", "emi_arb_g", "0x"+IntToHex((int)(g_EMI_NFI_Setting.m_dram_cfg.m_emi_arb_g), 8));
	ini->WriteString( "EMI", "emi_arb_h", "0x"+IntToHex((int)(g_EMI_NFI_Setting.m_dram_cfg.m_emi_arb_h), 8));
	ini->WriteString( "EMI", "emi_arb_i", "0x"+IntToHex((int)(g_EMI_NFI_Setting.m_dram_cfg.m_emi_arb_i), 8));

/****************************************** [IMEI] Section *************************************************/
#if 0
       ini->WriteBool  ( "IMEI", "checkSIM1", Form_IMEI_setting->m_bIMEI1Check);
       ini->WriteBool  ( "IMEI", "checkSIM2", Form_IMEI_setting->m_bIMEI2Check);
       ini->WriteBool  ( "IMEI", "updateSIM1", Form_IMEI_setting->m_bIMEI1Update);
       ini->WriteBool  ( "IMEI", "updateSIM2", Form_IMEI_setting->m_bIMEI2Update);

    ini->WriteString( "IMEI", "NVRAMdatabase",Form_IMEI_setting->m_asNVRAM_DB_File );
    ini->WriteString( "IMEI", "SIM1initial",Form_IMEI_setting->m_asInitialIMEI );
    ini->WriteString( "IMEI", "SIM2initial",Form_IMEI_setting->m_asInitialIMEI );
    AnsiString as_IMEI1(Form_IMEI_setting->m_sIMEI.c_imei[0]);
    ini->WriteString( "IMEI", "SIM1",as_IMEI1 );
    AnsiString as_IMEI2(Form_IMEI_setting->m_sIMEI.c_imei[1]);
    ini->WriteString( "IMEI", "SIM2",as_IMEI2 );
#endif
/****************************************** [BACKUP_FORMAT_DOWNLOAD_RESTORE NVRAM] Section *************************************************/
    //ini->WriteString( "BACKUP_FORMAT_DOWNLOAD_RESTORE", "backup_restore_path", Form_Backup_Restore_NVRAM->m_asNVRAM_data_File);
    //ini->WriteString( "BACKUP_FORMAT_DOWNLOAD_RESTORE", "datafile",Form_Backup_Restore_NVRAM->m_asNVRAM_data_File );
    //ini->WriteString( "BACKUP_FORMAT_DOWNLOAD_RESTORE", "mapfile",Form_Backup_Restore_NVRAM->m_asNVRAM_map_File );
#if 0
	ini->WriteInteger( "BACKUP_FORMAT_DOWNLOAD_RESTORE", "BackupRestoreState", g_backup_restore_state );
    ini->WriteInteger("BACKUP_FORMAT_DOWNLOAD_RESTORE", "BackupRestoreFolderType", g_backup_restore_folder_type);
#endif
/****************************************** [Write BT/WiFi] Section ***************/
        ini->WriteString  ( "NVRAM", "ModemDatabase", Form_FourInOne->m_asModem_Database);
        ini->WriteString  ( "NVRAM", "ApDatabase", Form_FourInOne->m_asAP_Database);
        //ini->WriteString  ( "IMEI", "IMEI1", Form_FourInOne->m_asIMEI1_Number);
        //ini->WriteString  ( "IMEI", "IMEI2", Form_FourInOne->m_asIMEI2_Number);
        ini->WriteString  ( "NVRAM", "BtAddress", Form_FourInOne->m_asBT_Address);
        ini->WriteString  ( "NVRAM", "WiFiAddress", Form_FourInOne->m_asWiFi_Address);
        ini->WriteBool  ( "NVRAM", "CheckIMEI1", Form_FourInOne->m_bWriteIMEI1);
        ini->WriteBool  ( "NVRAM", "CheckIMEI2", Form_FourInOne->m_bWriteIMEI2);
        ini->WriteBool  ( "NVRAM", "CheckBTAddr", Form_FourInOne->m_bWriteBTAddr);
        ini->WriteBool  ( "NVRAM", "CheckWIFIAddr", Form_FourInOne->m_bWriteWIFIAddr);
        ini->WriteInteger  ( "NVRAM", "UpdateNVRAMState", g_nvram_update_state);

/****************************************** [FORM] Section *************************************************/

    ini->WriteInteger( "FORM", "com", COM_PORT );
    switch ( BAUD_RATE )
    {
        case UART_BAUD_921600:
            ini->WriteInteger( "FORM", "baudrate", 921600);
            break;
        case UART_BAUD_460800:
            ini->WriteInteger( "FORM", "baudrate", 460800);
            break;
        case UART_BAUD_230400:
            ini->WriteInteger( "FORM", "baudrate", 230400);
            break;
        case UART_BAUD_115200:
            ini->WriteInteger( "FORM", "baudrate", 115200);
            break;
        case UART_BAUD_57600:
            ini->WriteInteger( "FORM", "baudrate", 57600);
            break;
        case UART_BAUD_38400:
            ini->WriteInteger( "FORM", "baudrate", 38400);
            break;
        case UART_BAUD_19200:
            ini->WriteInteger( "FORM", "baudrate", 19200);
            break;
        case UART_BAUD_9600:
            ini->WriteInteger( "FORM", "baudrate", 9600);
            break;
        default :
            ini->WriteInteger( "FORM", "baudrate", 19200);
            if (DEBUG) ShowMessage( " main.cpp : undefined Baud Rate " + IntToStr( COM_PORT ));
            break;
    }
    //DL Options
    ini->WriteBool ( "FORM", "usb_mode", g_bUsbMode );
    //ini->WriteBool ( "FORM", "dl_with_battery", g_bUsbModeWithBattery);
	//ini->WriteBool ( "FORM", "da_dl_all", g_bDADownloadAll);
	//ini->WriteBool( "FORM", "da_enable_hs", g_bDAEnableHS);
    
//        ini->WriteString ( "FORM", "flash_bin",                  ed_SPBIN_File->Text );
	ini->WriteString ( "FORM", "bin",                        g_asNormalModeDAPath );
#if 0
	ini->WriteString ( "FORM", "AUTH_File",                  ed_AUTH_File->Text );
	ini->WriteString ( "FORM", "SCERT_File",                 ed_SCERT_File->Text );
#endif
	ini->WriteBool   ( "FORM", "pull_down_gpio17",           g_bPullDownGPIO17 );
	ini->WriteInteger( "FORM", "brom_start_cmd_retry_count", g_MaxBromStartCmdRetryCount );
	ini->WriteInteger( "FORM", "OperationMethod",            g_platform_info.getFlashToolStorageConfig().GetStorageType() );
	ini->WriteInteger( "FORM", "erase_validation",           g_FormatValidation );
    ini->WriteInteger( "FORM", "flashitemindex",             iFlashItemIndex );
	ini->WriteString ( "FORM", "FormatStartAddr",        "0x" + IntToHex((__int64) g_ulNandFormatStartAddr, 16) );
	ini->WriteString ( "FORM", "FormatLength",           "0x" + IntToHex((__int64) g_ulNandFormatLength, 16) );
	ini->WriteInteger( "FORM", "FormatOption",                g_FormatOption);


/****************************************** [DOWNLOAD] Section ****************************************************/

    ini->WriteBool    ( "DOWNLOAD", "compare_resource_project_id", g_CompareResProjectId );
    //ini->WriteInteger ( "DOWNLOAD", "FormatAfterDownloadOption",   g_FormatAfterDownloadOption);
    ini->WriteInteger ( "DOWNLOAD", "FormatAfterDownloadOption",   DISABLE_FORMAT);


/****************************************** [DL_HISTORY_X] Section *************************************************/
/*
	// erase existing section first
	for ( i=0; i<MAX_DOWNLOAD_HISTORY; i++ )
    {
		ini->EraseSection ( "DL_HISTORY_"+IntToStr(i));
	}

	// save download history
	for ( i=0, iter=g_DownloadHistory.begin(); i<MAX_DOWNLOAD_HISTORY && iter!=g_DownloadHistory.end(); i++, iter++)
    {
		// write new section data
		ini->WriteString  ( "DL_HISTORY_"+IntToStr(i), "scatter_file",      iter->m_Scatter);
		ini->WriteString  ( "DL_HISTORY_"+IntToStr(i), "bootloader",        iter->m_BootLoader);
		ini->WriteString  ( "DL_HISTORY_"+IntToStr(i), "bootloader_ext",    iter->m_BootLoader_Ext);
		ini->WriteBool    ( "DL_HISTORY_"+IntToStr(i), "bootloader_enable", iter->m_BootLoader_Enable);
		ini->WriteInteger ( "DL_HISTORY_"+IntToStr(i), "file_count",        iter->m_BinFiles.size());

		for ( unsigned int j=0; j<iter->m_BinFiles.size(); j++ )
        {
			ini->WriteString ( "DL_HISTORY_"+IntToStr(i), "file"+IntToStr(j), iter->m_BinFiles[j].m_Filepath);
			ini->WriteBool   ( "DL_HISTORY_"+IntToStr(i), "file"+IntToStr(j)+"_enable", iter->m_BinFiles[j].m_Enable);
		}
	}

*/
/****************************************** [READBACK] Section *************************************************/

	unsigned short	count;
	if ( ( S_DONE == RB_GetCount(g_RB_HANDLE, &count)) && ( 0<count ) )
    {
		RB_INFO	*rb=new RB_INFO[count];

		if( NULL != rb )
        {
			ini->WriteInteger( "READBACK", "readback_count", count );

			if( S_DONE == RB_GetInfoAll(g_RB_HANDLE, rb, count) )
            {
				for ( i=0; i<(unsigned int)count; i++ )
                {
                    // read back file name
					ini->WriteString ( "READBACK", "file"+IntToStr(i),              rb[i].filepath);
                    // RB_FILE enable flag
					ini->WriteInteger( "READBACK", "file"+IntToStr(i)+"_enable",    rb[i].enable);
					ini->WriteInteger( "READBACK", "file"+IntToStr(i)+"_read_flag", rb[i].m_read_flag);
                    // read back addr
					ini->WriteString ( "READBACK", "startaddr"+IntToStr(i), "0x"+IntToHex((__int64)rb[i].readback_addr, 16));
                    // read back length
					ini->WriteString ( "READBACK", "length"+IntToStr(i), "0x"+IntToHex((int)rb[i].readback_len, 8));
				}
			}
			delete [] rb;
		}
	}

/****************************************** [TRANS_OPTION] Section *************************************************/
	ini->WriteInteger( "TRANS_OPTION", "packet_length",            g_PacketLength );
	ini->WriteInteger( "TRANS_OPTION", "baudrate_full_sync_count", g_Baudrate_FullSync_Count );
	ini->WriteBool   ( "TRANS_OPTION", "speedup_brom_baudrate",    g_SpeedUpBootROMBaudrate);

/****************************************** [Write Memory] Section *************************************************/
      
	ini->WriteString( "WRITE_MEMORY", "raw_data_path", g_WM_RawDataFilePath.c_str());
	ini->WriteString( "WRITE_MEMORY", "start_addr", "0x"+IntToHex(static_cast<__int64>(g_WM_address), 16) );
	ini->WriteString ( "WRITE_MEMORY", "constainer_length", "0x"+IntToHex(static_cast<int>(g_WM_container_length), 8) );

	delete ini;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mi_ViewClick(TObject *Sender)
{
   updateMenuItem();
}

//---------------------------------------------------------------------------
int TMainForm::GetROMIndex(const char* rom_name, const DL_HANDLE_T dl_handle)
{
    int itemIndex = -1;

    unsigned short	count=0;
    ROM_INFO romInfo;
    DL_GetCount( dl_handle, &count );

    for (unsigned short i = 0; i < count; i++)
    {
        DL_Rom_GetInfo( dl_handle, i, &romInfo);
        if( 0 == strcmp(romInfo.name, rom_name) )
        {
            itemIndex = romInfo.index;
            break;
        }
    }
    return itemIndex;  
}

//Select Single ROM file when clicking ROM name in ListView
void __fastcall TMainForm::ListView1_oldClick(TObject *Sender)
{
    int iLastDel;
    int ret;
    TListView *plv = dynamic_cast<TListView *>(Sender);

    if ( plv->Selected == NULL ) return;
    if ( NULL == g_pCurNode ) return;


    DL_HANDLE_T &dl_handle=g_pCurNode->m_dl_handle;

    if( ROMBaseDir.Length() > 0 )
    {
    	OpenSingleRomFile->InitialDir = ROMBaseDir;
    	OpenSingleRomFile->FileName = "";
    }
    else if( 4 <= plv->Selected->SubItems->Count )
    {
    	iLastDel = plv->Selected->SubItems->Strings[3].LastDelimiter("\\:");

    	if ( iLastDel > 0)
    	{
        	OpenSingleRomFile->InitialDir = plv->Selected->SubItems->Strings[3].SubString(1, iLastDel-1 );
		    OpenSingleRomFile->FileName = "";
	    }
    }

	// open file
	if( !OpenSingleRomFile->Execute() ) {
		return;
	}

    ListViewItemType_E	type=*((ListViewItemType_E *)plv->Selected->Data);

    if( LV_NFB_BOOTLOADER == type )
    {
		// load boot loader
		if( S_DONE != (ret = DL_BL_Load(dl_handle, OpenSingleRomFile->FileName.c_str())) )
        {
			if( S_FTHND_HANDLE_BUSY_NOW == ret )
            {
				ShowMessage( "Program is busy! Can not update setting right now." );
				return;
			}
			else
            {
				ShowMessage( "Load boot-loader \"" + OpenSingleRomFile->FileName + "\" fail!" );
				return;
			}
		}
	}
	else {
	    // load ROM list
        if(g_project_mode==DUMA)
        {
	        if( S_DONE != ( ret = DL_Rom_Load(dl_handle, (LV_NFB_DL_ROM==type)?(plv->ItemIndex-1):plv->ItemIndex, OpenSingleRomFile->FileName.c_str())) )
            {
                if( S_FTHND_HANDLE_BUSY_NOW == ret ) {
                    ShowMessage( "Program is busy! Can not update setting right now." );
                    return;
                }
                else if( S_DL_LOAD_REGION_IS_OVERLAP == ret ) {
                    ShowMessage( "\"" + OpenSingleRomFile->FileName + "\" is too large and causes region overlap!");
                    return;
                }
                else {
                    ShowMessage( "Load file \"" + OpenSingleRomFile->FileName + "\" fail!" );
                    return;
                }
	        }
        }
        if(g_project_mode==YuSu)
        {
            int itemIndex = GetROMIndex(plv->Selected->Caption.c_str(), dl_handle);
            if ( -1 == itemIndex )
            {
                ShowMessage("Obtaining rom index fails.");
                return;
            }

            //if( S_DONE != ( ret = Load_Android_Image(dl_handle, (LV_NFB_DL_ROM==type)?(plv->ItemIndex-1):plv->ItemIndex, OpenSingleRomFile->FileName.c_str())) )
            if( S_DONE != ( ret = Load_Android_Image(dl_handle, itemIndex, OpenSingleRomFile->FileName.c_str())) )
            {
                if( S_FTHND_HANDLE_BUSY_NOW == ret ) {
                        ShowMessage( "Program is busy! Can not update setting right now." );
                        return;
                }
                else if( S_DL_LOAD_REGION_IS_OVERLAP == ret ) {
                        ShowMessage( "\"" + OpenSingleRomFile->FileName + "\" is too large and causes region overlap!");
                        return;
                }
                else {
                        ShowMessage( "Load file \"" + OpenSingleRomFile->FileName + "\" fail!" );
                        return;
                }
            }
        }
#if 0
        iLastDel = OpenSingleRomFile->FileName.LastDelimiter("\\:");
        if ( iLastDel > 0)
        {
	        ROMBaseDir = OpenSingleRomFile->FileName.SubString(1, iLastDel-1 );
        }

	    // auto load download bin files
        unsigned short	count=0;
        DL_GetCount( dl_handle, &count );

        if( g_bAutoLoadResByScat && !strcmp( "ROM", plv->Selected->Caption.c_str()) && 1<count )
        {
            DL_AutoLoadByScatRegionName(dl_handle, OpenSingleRomFile->FileName.c_str(), NORMAL_ROM|RESOURCE_BIN|JUMPTABLE_BIN|YAFFS_IMG, _FALSE);
        }
#endif
	}

	RedrawReadbackList();
	RedrawDownloadList(g_pCurNode, false);
}


int __fastcall TMainForm::Load_Android_Image(DL_HANDLE_T  dl_handle, unsigned short index, const char *rom_filepath)
{
	int ret = DL_Rom_Load(dl_handle, index, rom_filepath);
	if(ret == S_DONE) {
		ROM_INFO rom;
		if(S_DONE == DL_Rom_GetInfo(dl_handle,index,&rom)){
			ImageType imgType = GetImageMapRule().queryType(rom.name);
			ImageItem imgItem = GetImageMapRule().getImageItem(imgType);

			if(!imgItem.is_bootloader() && imgItem.is_format_effective()){
				AndroidImageInfo info;
				info.romIndex = index;
				info.type = static_cast<DM_IMG_TYPE>(imgType);
				info.format = static_cast<DM_IMG_FORMAT>(imgItem.eboot_format());
				info.romName = rom.name;
				info.filePath = rom.filepath;
                GetAndroidImageInfoTable().UpdateInfo(rom.name,info);
        }
	}
        LOGD("Update Single Image");
        LOGD(GetAndroidImageInfoTable().Dump().c_str());
	}
	//Redraw listview after loading image
	RedrawDownloadList(g_pCurNode, false);
	return ret;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ReadbackExecute(TObject *Sender)
{

	if (IsDLListEmpty()) {
		ShowMessage("Please select scatter file before Readback.");
	    return;
	}

    g_flashtool_function = FLASHTOOL_READBACK;
	//FIXME
#if 0	
	g_backup_restore_state =  NOACTION;
#endif
	g_nvram_update_state    = NOACTIONNVRAM ;

	updateMenuItem();

    if ( asBin.IsEmpty() )
    {
       //if (! FileOpenDownloadAgentExecute() )
       if (! FileOpenNandUtilBin(OpenDownloadAgentDialog, NORMAL_DA_BIN) )
       {
          ShowMessage(" You must open download agent file before downloading. ");
          return;
       }
    }

    if( g_bUsbDLDA &&
        g_project_mode == YuSu &&
        asNandUtilDAPath.IsEmpty())
    {
        if ( !FileOpenNandUtilBin(OpenNandUtilFileDialog, NAND_UTIL_DA_BIN) )
        {
            ShowMessage(" You must open Nand Util file before doing Readback. ");
            return;
        }
    }    

    if ( lv_ReadBack->Items->Count ==0 )
    {
        ShowMessage(" Please add read back file.");
        return;
    }

    // clean Flash device info
	HWStatusBarClear();

    // update DA to the latest version
	if( UpdateDA() ) return;

    if( MT6205 != g_BBCHIP_TYPE )
        start_DL(true);
    else
        Form_RB_GO->ShowModal();
}
//------------------------------------------------------------------------------
void TMainForm::start_RB( bool b_start_RB )
{
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::tb_AddReadBackFileClick(TObject *Sender)
{
	int ret;
	AnsiString s;
	TListItem *pListItem;

    unsigned long long default_readback_addr = 0x0000000000000000;
    unsigned long default_readback_len = 0x00001000;

	s = "ROM_" + IntToStr(lv_ReadBack->Items->Count);
	if( S_DONE != ( ret=RB_Append(g_RB_HANDLE, s.c_str(), default_readback_addr, default_readback_len)))
    {
		if( S_FTHND_HANDLE_BUSY_NOW == ret ) {
			ShowMessage("Program is busy! Can not update setting right now.");
		}
		else {
			ShowMessage("Add Readback file error ");
		}
		return;
	}

	RedrawReadbackList();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::tb_DeleteReadBackFileClick(TObject *Sender)
{
	int ret;

	if ( lv_ReadBack->Selected == NULL ) return;

	if( S_DONE != (ret=RB_Delete(g_RB_HANDLE, lv_ReadBack->ItemIndex)))
    {
		if( S_FTHND_HANDLE_BUSY_NOW == ret ) {
			ShowMessage("Program is busy! Can not delete readback entry right now.");
		}
		else {
			ShowMessage("Delete readback entry fail!");
		}
		return;
	}
	else {
		lv_ReadBack->Selected->Delete();
	}
}


//---------------------------------------------------------------------------

void __fastcall TMainForm::lv_ReadBack_oldDblClick(TObject *Sender)
{
	int ret;
	TListView *plv = dynamic_cast<TListView *>(Sender);

	if ( plv->Selected == NULL ) return;

	sd_ReadBack->FileName = plv->Selected->SubItems->Strings[2];

	RB_INFO	rb_info;
	if( S_DONE != ( ret=RB_GetInfo(g_RB_HANDLE, plv->ItemIndex, &rb_info)))
    {
		if( S_FTHND_HANDLE_BUSY_NOW == ret ) {
			ShowMessage("Program is busy! Can not update setting right now.");
		}
		else {
			ShowMessage("Update readback setting fail!");
		}
		return;
	}

	if ( sd_ReadBack->Execute() )
	{
		if( S_DONE != (ret=RB_SetFilepath(g_RB_HANDLE, plv->ItemIndex, sd_ReadBack->FileName.c_str())))
        {
			if( S_FTHND_HANDLE_BUSY_NOW == ret ) {
				ShowMessage("Program is busy! Can not update setting right now.");
			}
			else {
				ShowMessage("Update readback setting fail!");
			}
			return;
		}
		else {
			plv->Selected->SubItems->Strings[2] = sd_ReadBack->FileName ;
		}
	}
	else {
		return;
	}

	Form_RB_Option->rb_ReadbackHex->Checked = true;

	int addressing_type = 0;
	addressing_type = g_platform_info.getFlashToolStorageConfig().GetAddressingType();
	LOGD("Tracking Addressing Modification: addressing_type(%d)", addressing_type);
	
	Form_RB_Option->ed_RB_StartAddr->Text = "0x" + IntToHex((__int64)rb_info.readback_addr, 16);
	Form_RB_Option->ed_RB_Length->Text = "0x" + IntToHex((int)rb_info.readback_len, 8);

	switch( rb_info.m_read_flag )
    {
	    case NUTL_READ_PAGE_ONLY:
    	    Form_RB_Option->m_Radio_ReadPageOnly->Checked = true;
		    break;

	    case NUTL_READ_SPARE_ONLY:
        	Form_RB_Option->m_Radio_ReadSpareOnly->Checked = true;
		    break;

	    case NUTL_READ_PAGE_WITH_ECC:
    	    Form_RB_Option->m_Radio_ReadPageWithECC->Checked = true;
		    break;

	    case NUTL_READ_PAGE_SPARE:
	    default:
    	    Form_RB_Option->m_Radio_ReadPageSpare->Checked = true;
		    break;
	}

	Form_RB_Option->Visible = true;

	Form_RB_Option->bb_ReadBack_OK->Visible = true;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::Timer_DownloadTimer(TObject *Sender)
{
	unsigned int Bps;
	float KBps;
	AnsiString rate;
	AnsiString Zero;
	static unsigned int LastDisplayFinishedBytes=0;

	g_CostTimeSec++;
	g_ProgressTimeSec++;

    Zero = (10>(g_CostTimeSec%60)) ? "0" : "";

	sb_Main->Panels->Items[4]->Text = " " + IntToStr(g_CostTimeSec/60) + ":" + Zero + IntToStr(g_CostTimeSec%60) + " sec ";

	if( LastDisplayFinishedBytes != g_DisplayFinishedBytes )
    {

		LastDisplayFinishedBytes = g_DisplayFinishedBytes;

		if( 0 >= g_ProgressTimeSec ) {
			rate = "0 Bps";
		}
		else if( 1024 < (Bps=g_DisplayFinishedBytes/g_ProgressTimeSec) ) {
			KBps = Bps;
			rate = FloatToStrF( KBps/1024, ffFixed, 7, 2) + " KBps";
		}
		else {
			rate = IntToStr(Bps) +  " Bps";
		}

	    MainForm->sb_Main->Panels->Items[0]->Text = IntToStr(g_DisplayFinishedBytes) + " Bytes / " + rate;
	}
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::Timer_2ND_USB_HintTimer(TObject *Sender)
{
     if(m_2ndSiteUSBSecHint > 0)
     {
         MainForm->sb_Main->Panels->Items[5]->Text = AnsiString().sprintf("Please insert USB cable in %d seconds",
                                                       --m_2ndSiteUSBSecHint);
     }
     else
     {
         MainForm->sb_Main->Panels->Items[5]->Text = "";
     }
}
//---------------------------------------------------------------------------

#ifdef _DEBUG
  #include "ok_wnd.h"
#endif /* #ifdef _DEBUG */

void __fastcall TMainForm::testOKWnd1Click(TObject *Sender)
{
#ifdef _DEBUG

    Form_OK->ClientHeight = Form_OK->img_OK->Picture->Height+1;
    Form_OK->ClientWidth  = Form_OK->img_OK->Picture->Width+1;

    //Form_OK->img_OK->Height = Form_OK->img_OK->Picture->Height;
    //Form_OK->img_OK->Width  = Form_OK->img_OK->Picture->Width;
    //Form_OK->ClientHeight   = Form_OK->img_OK->Height+1;
    //Form_OK->ClientWidth    = Form_OK->img_OK->Width+1;

    Form_OK->Show();

#endif /* #ifdef _DEBUG */
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::About1Click(TObject *Sender)
{
    AnsiString as;
    DA_INFO da_info;
    DA_INFO nand_util_info;
    unsigned int ret;


    // retrieval the DA information
    if( !DA_GetInfo( g_DA_HANDLE, &da_info) )
    {
        if( strlen(da_info.version) != 0 )
        {
            as.printf("DA_v%s",da_info.version);
            Form_About->da_version->Caption = as;

            if( strlen( da_info.last_modified_date ) != 0 )
            {
                as.printf( "(Build-Date: %s)", da_info.last_modified_date );
                Form_About->da_build_date->Caption = as;
            }
            else{
                Form_About->da_build_date->Caption = "";
            }
        }
        else{
            Form_About->da_version->Caption    = "";
            Form_About->da_build_date->Caption = "";
        }
    }
    else{
        Form_About->da_version->Caption    = "";
        Form_About->da_build_date->Caption = "";
    }

    // retrieval the NandUtil information
    if( !DA_GetInfo( g_NAND_UTIL_DA_HANDLE, &nand_util_info) )
    {
        if( strlen(nand_util_info.version) != 0 )
        {
            as.printf("NandUtil_v%s",da_info.version);
            Form_About->nand_util_version->Caption = as;

            if( strlen( nand_util_info.last_modified_date ) != 0 )
            {
                as.printf( "(Build-Date: %s)", nand_util_info.last_modified_date );
                Form_About->nand_util_build_date->Caption = as;
            }
            else{
                Form_About->nand_util_build_date->Caption = "";
            }
        }
        else{
            Form_About->nand_util_version->Caption    = "";
            Form_About->nand_util_build_date->Caption = "";
        }
    }
    else{
        Form_About->da_version->Caption    = "";
        Form_About->da_build_date->Caption = "";
    }

    // show FlashTool about Form
    Form_About->Show();

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::mi_FormatFDMClick(TObject *Sender)
{
	FormatOption->bCallFromFormatButton = false;
	FormatOption->Visible = true;

/*	if(bFormatFDM) {
        bFormatFDM = false;
	}
    else {
        bFormatFDM = true;
	}

	updateMenuItem();*/
}
//---------------------------------------------------------------------------
void TMainForm::DisableDLCertButton(void)
{
	tb_DL_Certification->Enabled = false;
}

//---------------------------------------------------------------------------
void TMainForm::EnableDLCertButton(void)
{
	tb_DL_Certification->Enabled = true;
}

//---------------------------------------------------------------------------
void TMainForm::DisableDownloadButton ( void )
{
	// disable download button
    tb_DL_StartButton->Enabled = false;
#if 0
    tb_DLFlashBinButton->Enabled = false;
#endif
    Download1->Enabled = false;
    Download->Enabled = false;
}
//---------------------------------------------------------------------------
void TMainForm::EnableDownloadButton ( void )
{
	// enable download button
    tb_DL_StartButton->Enabled = true;
#if 0
    tb_DLFlashBinButton->Enabled = true;
#endif
    Download1->Enabled = true;
    Download->Enabled = true;
}
//---------------------------------------------------------------------------
void TMainForm::DisableReadbackButton ( void )
{
	// disable readback button
    ReadBack1->Enabled = false;
    tb_ReadBack2->Enabled = false;
	tb_ReadbackVersion->Enabled = false;
	tb_ReadbackProductInfo->Enabled = false;
}
//---------------------------------------------------------------------------
void TMainForm::EnableReadbackButton ( void )
{
	// enable readback button
    ReadBack1->Enabled = true;
    tb_ReadBack2->Enabled = true;
	tb_ReadbackVersion->Enabled = true;
	tb_ReadbackProductInfo->Enabled = true;
}
//---------------------------------------------------------------------------
void TMainForm::DisableSCICloneButton(void)
{
     //disable clone button
       MainForm->bb_Clone_OpenDA->Enabled = false;
	 MainForm->bb_SCI_OpenFileFolder->Enabled = false;
	 MainForm->bb_Clone_Readback->Enabled = false;
	 MainForm->bb_Restore_OpenFile->Enabled = false;
	 MainForm->bb_SCI_Clone_Restore->Enabled = false; 
}
//----------------------------------------------------------------------------
void TMainForm::EnableSCICloneButton(void)
{
     //disable clone button
       MainForm->bb_Clone_OpenDA->Enabled = true;
	 MainForm->bb_SCI_OpenFileFolder->Enabled = true;
	 MainForm->bb_Clone_Readback->Enabled = true;
	 MainForm->bb_Restore_OpenFile->Enabled = true;
	 MainForm->bb_SCI_Clone_Restore->Enabled = true; 
}
//---------------------------------------------------------------------------
void TMainForm::DisableSCIDownloadButton(void)
{
     //disable sci download button
	 MainForm->bb_SCI_DL_OpenDAFile->Enabled= false;
	 MainForm->bb_SCI_DL_Download->Enabled = false;
	 MainForm->bb_OpenSCIFile->Enabled = false;
}

//---------------------------------------------------------------------------
void TMainForm::EnableSCIDownloadButton(void)
{
     //disable sci download button
	 MainForm->bb_SCI_DL_OpenDAFile->Enabled= true;
	 MainForm->bb_SCI_DL_Download->Enabled = true;
	 MainForm->bb_OpenSCIFile->Enabled = true;
}

//---------------------------------------------------------------------------
void TMainForm::DisableFormatButton ( void )
{
	// disable download button
    tb_FormatButton->Enabled = false;
}
//---------------------------------------------------------------------------
void TMainForm::EnableFormatButton ( void )
{
	// enable download button
    tb_FormatButton->Enabled = true;
}

//---------------------------------------------------------------------------
void TMainForm::DisableFirmwareUpgradeButton ( void )
{
    tb_FirmwareUpgradeButton->Enabled = false;
}

//---------------------------------------------------------------------------
void TMainForm::EnableFirmwareUpgradeButton ( void )
{
   tb_FirmwareUpgradeButton->Enabled = true;
}
//---------------------------------------------------------------------------
void TMainForm::UpdateCaption ( void )
{
	AnsiString s;
	s = "Smart Phone Flash Tool";

	if(g_bDebugDA) {
		s += " (Test Mode)";
	}
	if(g_bTrace) {
		s += " (Runtime Trace Mode)";
	}
	if(g_bSkipBootRom) {
		s += " (Skip BootRom Mode)";
	}
	if(g_bEnableAdvanceOption) {
		s += " (Advanced Mode)";
	}
	if(g_bCommandRecordingMode) {
		s += " (Command-Recording Mode)";
	}
	if (g_bEnableMarkNandBadBlocks) {
		s += " (Mark Nand bad blocks Mode)";
	}
	if(g_bDLCertificationMode){
		s += " (Certification Download Mode)";
	}

    Caption = s;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::action_ToggleDebugDAExecute(TObject *Sender)
{
	// toggle debug DA flag
	if( g_bDebugDA ) {
		g_bDebugDA                    = false;
        DebugDAWindow->Visible        = false;
        Panel1->Visible               = true;
        // now disable parameter list
       //		ListView1->Visible            = true;
	    m_ParamListView->Visible      = true;
        tb_ReadBack->Visible          = true;
        lv_ReadBack->Visible          = true;
        m_SaveTestModeLog->Visible    = false;
        FileSave_TestModeLog->Enabled = false;

		// restore NormalMode DA path
		asBin = g_asNormalModeDAPath;
	}
	else {
		g_bDebugDA                    = true;
        DebugDAWindow->Visible        = true;
        DebugDAWindow->Text           = "";
        Panel1->Visible               = false;
		ListView1->Visible            = false;
		m_ParamListView->Visible      = false;
        tb_ReadBack->Visible          = false;
        lv_ReadBack->Visible          = false;
        m_SaveTestModeLog->Visible    = true;
        FileSave_TestModeLog->Enabled = true;

		// restore TestMode DA path
		asBin = g_asTestModeDAPath;
	}

	// reload DA
	OpenReadDA_File(asBin, NORMAL_DA_BIN);

	UpdateCaption();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::action_ToggleTraceExecute(TObject *Sender)
{
	// toggle runtime trace flag  (Ctrl + Alt + T)
	if( g_bTrace ) {
	    g_bTrace = false;
		FileUtils::DebugLogsOff();
	} else {
	    g_bTrace = true;
        FileUtils::DebugLogsOn();
	}
	UpdateCaption();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::action_RecordCommandExecute(TObject *Sender)
{
    g_bCommandRecordingMode = !g_bCommandRecordingMode;
    UpdateCaption();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::tb_FormatButtonClick(TObject *Sender)
{
	if (IsDLListEmpty()) {
		ShowMessage("Please select scatter file before format.");
	    return;
	}

	g_flashtool_function = FLASHTOOL_FORMAT;
	//FIXME
#if 0
	g_backup_restore_state =  NOACTION;
#endif
	g_nvram_update_state    = NOACTIONNVRAM ;
	updateMenuItem();

	if ( asBin.IsEmpty() )
    {
	//if (! FileOpenDownloadAgentExecute())
        if ( !FileOpenNandUtilBin(OpenDownloadAgentDialog, NORMAL_DA_BIN) )
		{
			ShowMessage(" You must open download agent file before formating. ");
			return;
		}
	}

	if ( 0 == ListView1->Items->Count ) {
	    ShowMessage("[Hint] Format block info is stored in the scatter file, please select a scatter file before excuting!");
	    return ;
	}

	// clean Flash device info
	HWStatusBarClear();

    // update DA to the lastest version
    if ( UpdateDA() ) return;

    FormatOption->bCallFromFormatButton = true;
    FormatOption->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::action_ForceStopExecute(TObject *Sender)
{
    // Ctrl + Alt + Z
	g_stopflag = BOOT_STOP;
	META_CancelAllBlockingCall();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::tb_FirmwareUpgradeButtonClick(TObject *Sender)
{
    g_flashtool_function = FLASHTOOL_FIRMWARE_UPGRADE;
    //g_FormatOption = FIRMWARE_UPGRADE_FORMAT;
	//FIXME
#if 0
	g_backup_restore_state =  NOACTION;
#endif
	g_nvram_update_state    = NOACTIONNVRAM ;
	updateMenuItem();
	
	/*if (!IsAllImgsToBeDL(g_pCurNode->m_dl_handle)) {
	    ShowMessage("Please make sure all images are checked to be downloaded for \"Firmware Upgrade\"!");
		return;
	}*/
	if(!IsNecessaryImgsToBeDL(g_pCurNode->m_dl_handle))
	{
	     ShowMessage("Please make sure all necessary images are checked to be downloaded for \"Firmware Upgrade\"!");
             return;
	}

	if ( !IsInitialParameterCheckPass() ) {
		return;
	}
    else if ( !InitializeDL() )
    {
        return;
    }   
  
    {
        start_DL(true);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::action_ToggleSkipBootRomExecute(TObject *Sender)
{
	// toggle skip bootrom flag, Ctrl + Alt + B
	if( g_bSkipBootRom ) {
		g_bSkipBootRom = false;
        g_bUsbDLDA = false;
	}
	else {
		g_bSkipBootRom = true;
        g_bUsbDLDA = true;
	}

    // USB DL DA: User Forbidden to select Boot Loader
    TListItem 		*pItem=ListView1->Items->Item[0];
    if( NULL != pItem && g_bUsbDLDA)
    {
        DL_HANDLE_T		&dl_handle=g_pCurNode->m_dl_handle;
        ListViewItemType_E	type=*((ListViewItemType_E *)pItem->Data);

	    if( (LV_NFB_BOOTLOADER == type) || (LV_NFB_EXT_BOOTLOADER == type) ) {
	        DL_BL_SetEnableAttr(dl_handle, _FALSE);
        }
	    else if( LV_NOR_BOOTLOADER == type ) {
	        DL_Rom_SetEnableAttr(dl_handle, 0, _FALSE);
        }
        else if ( LV_NOR_DL_ROM == type ) {
            DL_Rom_SetEnableAttr(dl_handle, 0, _FALSE);
         }
         RedrawDownloadCheckBox();
    }
	UpdateCaption();
}


//---------------------------------------------------------------------------

void __fastcall TMainForm::action_PurgeDebugLogExecute(TObject *Sender)
{
    // Ctrl + X
	Brom_DebugClear();
    META_DebugClear();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::PL_1Click(TObject *Sender)
{
    UpdatePacketLength(256);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PL_2Click(TObject *Sender)
{
    UpdatePacketLength(1024);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PL_3Click(TObject *Sender)
{
    UpdatePacketLength(4096);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PL_4Click(TObject *Sender)
{
    UpdatePacketLength(10240);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PL_5Click(TObject *Sender)
{
    UpdatePacketLength(20480);
}
//---------------------------------------------------------------------------

void TMainForm::UpdatePacketLength(unsigned short pkt_length)
{
    PL_1->Checked = false;
    PL_2->Checked = false;
    PL_3->Checked = false;
    PL_4->Checked = false;
    PL_5->Checked = false;

	switch( pkt_length )
    {
    	case 256:
        	g_PacketLength = 256;
		    PL_1->Checked = true;
        	break;

        case 1024:
        	g_PacketLength = 1024;
		    PL_2->Checked = true;
        	break;

        case 4096:
        	g_PacketLength = 4096;
		    PL_3->Checked = true;
        	break;

        case 10240:
        	g_PacketLength = 10240;
		    PL_4->Checked = true;
        	break;

        case 20480:
        	g_PacketLength = 20480;
		    PL_5->Checked = true;
        	break;

    	default:
        	g_PacketLength = 1024;
		    PL_2->Checked = true;
            break;
	}

    DL_SetPacketLength( g_pCurNode->m_dl_handle, g_PacketLength );
	/* Mark to use default packet length, 2012/08/17 { */
    //RB_SetPacketLength( g_RB_HANDLE, g_PacketLength );
	/* Mark to use default packet length, 2012/08/17 } */
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::Options1Click(TObject *Sender)
{
    int ret;
    unsigned short com_port_list[255];
    unsigned short com_port_count = sizeof(com_port_list)/sizeof(unsigned short);

	LOG("TMainForm::Options1Click(): Platform(%s), isAlertNoCOMPort(%s)",
		g_platform_info.getLoadPlatformName().c_str(),
		g_platform_info.getPlatformConfig().doesAlertNoCOMPort() ? "Y" : "N");
    if( COM_ENUM_OK != (ret=ComPortEnumerate(com_port_list, &com_port_count)) &&
	    g_platform_info.getPlatformConfig().doesAlertNoCOMPort() )
    {
		if( COM_ENUM_NO_COM_PORT_FOUND == ret )
        {
            ShowMessage(" No COM port detected! ");
    	}
    	else
        {
            ShowMessage(" Enumerate COM port fail! ");
        }
        
        return;
    }

    if( com_port_count == m_COMPortCount && !memcmp((void *)com_port_list, (void *)m_COMPortList, m_COMPortCount*sizeof(unsigned short)) )
    {
//		ShowMessage(" COM ports are the same! ");
    	return;
    }

    // assign new com port list
    m_COMPortCount = com_port_count;
    memcpy((void *)m_COMPortList, (void *)com_port_list, m_COMPortCount*sizeof(unsigned short));

    DCOMPort->Clear();

    AnsiString s;
    bool DefaultChecked = false;

    for( int i=0;  i < m_COMPortCount ;  i++ )
    {
    	TMenuItem *NewItem = new TMenuItem(DCOMPort);
       	s = "COM" + IntToStr(m_COMPortList[i]);
        NewItem->Caption = s;
        NewItem->Enabled = true;
        NewItem->Visible = true;
        NewItem->OnClick = COMPortSubMenuClick;

        if( m_COMPortList[i] == (int)COM_PORT )
        {
            NewItem->Checked = true;
            DefaultChecked = true;
        }
        DCOMPort->Add(NewItem);
    }

    if( !DefaultChecked )
    {
        DCOMPort->Items[0]->Checked = true;
        COM_PORT = m_COMPortList[0];
    }

    updateStatusBar();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::COMPortSubMenuClick(TObject *Sender)
{
	for( unsigned short i=0; i<m_COMPortCount; i++ )
    {
        DCOMPort->Items[i]->Checked = false;
    }

	((TMenuItem *)Sender)->Checked = true;
	COM_PORT = m_COMPortList[DCOMPort->IndexOf(((TMenuItem *)Sender))];
	updateStatusBar();
}
//---------------------------------------------------------------------------
static int DL_IndexOfChangedCheckBox = -1;

void __fastcall TMainForm::ListView1Click(TObject *Sender)
{
	TListView *plv = dynamic_cast<TListView *>(Sender);
	//	ShowMessage("Click");

    if( NULL == g_pCurNode ) {
	    return;
	}

	DL_HANDLE_T &dl_handle=g_pCurNode->m_dl_handle;

	if( 0<=DL_IndexOfChangedCheckBox && DL_IndexOfChangedCheckBox<plv->Items->Count ) {
		TListItem *pItem=plv->Items->Item[DL_IndexOfChangedCheckBox];
		ListViewItemType_E	type=*((ListViewItemType_E *)pItem->Data);

        // USB DL: User Forbidden to select Boot Loader
        if( g_bUsbDLRB ){
            if( (LV_NOR_BOOTLOADER == type ) || (LV_NFB_BOOTLOADER == type) || (LV_NFB_EXT_BOOTLOADER == type) ){
                RedrawDownloadCheckBox();
                return;
            }
        }

		if( (LV_NFB_BOOTLOADER == type) || (LV_NFB_EXT_BOOTLOADER == type) ) {
			DL_BL_SetEnableAttr(dl_handle, pItem->Checked?_TRUE:_FALSE);
		}
		else {
            int itemIndex = GetROMIndex(pItem->Caption.c_str(), dl_handle);
            if ( -1 == itemIndex ) {
                ShowMessage("Obtaining rom index fails.");
                return;
            } else {
			    DL_Rom_SetEnableAttr(dl_handle, itemIndex, pItem->Checked?_TRUE:_FALSE);
                /*Logger::GetLogger().Log(Logger::Debug, "DL_Rom_SetEnableAttr: item index: %d, item name: %s, checked: %d",
                    itemIndex, pItem->Caption.c_str(), pItem->Checked);*/
            } 
		}
		RedrawDownloadCheckBox();
	}
	else {
		ListView1_oldClick(Sender);
	}

    DL_IndexOfChangedCheckBox = -1;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ListView1DblClick(TObject *Sender)
{
	ListView1Click(Sender);
}
//---------------------------------------------------------------------------

static bool DL_bPreviousCheckBoxValue;

void __fastcall TMainForm::ListView1Change(TObject *Sender, TListItem *Item, TItemChange Change)
{
	 //ShowMessage("Changed");
      if( (ctState == Change) &&
    	(Item->Checked != DL_bPreviousCheckBoxValue) ) {
        DL_IndexOfChangedCheckBox = Item->Index;
        return;
      }

    DL_IndexOfChangedCheckBox = -1;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ListView1Changing(TObject *Sender, TListItem *Item, TItemChange Change, bool &AllowChange)
{
	 //ShowMessage("Changing");

	DL_bPreviousCheckBoxValue = Item->Checked;

      DL_IndexOfChangedCheckBox = -1;
}
//---------------------------------------------------------------------------

void TMainForm::RedrawDownloadList(MultiLoadNode  *p_node, bool bUpdateParamOnly)
{

    CS_Sentry	cs(m_pUpdateListLock);

    AnsiString s;
    DL_INFO dl_info;
    unsigned short  count;
    TListItem	    *pListItem;
    const int SCATTER_FILE_LEN = strlen("scatter.txt");

    if( !bUpdateParamOnly ) {
        ListView1->Items->Clear();
    }
    m_ParamListView->Items->Clear();

    if( NULL == p_node ) {
	return;
    }

    DL_HANDLE_T &dl_handle=p_node->m_dl_handle;

    DL_GetInfo(dl_handle, &dl_info);

    if ( bUpdateParamOnly ) {
	goto update_param;
    }

    // update scatter path
    ed_LinkMapFile->Text = p_node->m_scat_file;
    if ( ed_LinkMapFile->Text.Length() < SCATTER_FILE_LEN )
    {
        ed_LinkMapFile->Text = "";
        return;
    }
/*    // add BootLoader entry
    if ( dl_info.m_config.m_is_nfb )
    {
        pListItem = ListView1->Items->Add();
        pListItem->Caption = "NFB-BootLoader";
        BL_INFO	bl_info;

        STATUS_E ret_bl_get_info;

        ret_bl_get_info = (STATUS_E) DL_BL_GetInfo(dl_handle, &bl_info);
        if( S_DONE == ret_bl_get_info )
        {
            int bl_addr = (int)bl_info.m_start_addr;
            int bl_size = (int)bl_info.m_filesize;

            AnsiString  region_prefix;
            pListItem->Checked = _TRUE==bl_info.m_enable?true:false;
            pListItem->SubItems->Add("");
    	    pListItem->SubItems->Add( "0x" + IntToHex(bl_addr, 8) );
            pListItem->SubItems->Add( "0x" + IntToHex(bl_addr+bl_size-1, 8) );
            pListItem->SubItems->Add(bl_info.m_filepath);
        }
        pListItem->Data     = &g_LV_ItemType[LV_NFB_BOOTLOADER];

        if( S_DONE == ret_bl_get_info && bl_info.m_ext_bootloader_exist)
        {
            int ext_bl_addr = (int)bl_info.m_start_addr+(int)bl_info.m_filesize;
            int ext_bl_size = (int)bl_info.m_ext_filesize;

    		pListItem = ListView1->Items->Add();
	    	pListItem->Caption = "NFB-ExtBootLoader";

        	pListItem->Checked = _TRUE==bl_info.m_enable?true:false;
	        pListItem->SubItems->Add("");
    		pListItem->SubItems->Add( "0x" + IntToHex(ext_bl_addr, 8) );
        	pListItem->SubItems->Add( "0x" + IntToHex(ext_bl_addr + ext_bl_size - 1, 8) );
	        pListItem->SubItems->Add(bl_info.m_ext_filepath);
         	pListItem->Data     = &g_LV_ItemType[LV_NFB_EXT_BOOTLOADER];
        }

        // change operation to NFB
		//g_OperationMethod   = NFB_OPERATION;
	}
	else {
        // change operation to NOR
		//g_OperationMethod   = NOR_OPERATION;
	}
	updateMenuItem();
	updateStatusBar();
 */
    // add ROM list
    if ( !DL_GetCount(dl_handle, &count) )
    {
	  ROM_INFO	rom[MAX_LOAD_SECTIONS];
        AnsiString  region_prefix;

        if( !DL_Rom_GetInfoAll(dl_handle, rom, MAX_LOAD_SECTIONS) )
        {
            for ( int i=0; i<count; i++ )
            {
/*                LOGD("============TMainForm::RedrawDownloadList============");
                    Logger::GetLogger().Log(Logger::Debug,
                		"ROM_INFO: Item: %d, rom name: %s is visable : %s, path: %s.",
                		i, rom[i].name, (rom[i].item_is_visable == _TRUE? "Yes" : "No"), rom[i].filepath)*/;
	            
                if(_TRUE == rom[i].item_is_visable)
                {
                  pListItem = ListView1->Items->Add();
		     pListItem->Caption = rom[i].name;
                  pListItem->Checked = ((_TRUE==rom[i].enable)?true:false);
                    //pListItem = ListView1->Items->Add();
                    if ( OFFSET_VALUE == rom[i].addr_type ) {
                        region_prefix = "+";
                    }
	                else {
                        region_prefix = "";
	                }

		       int addressing_type = 0;
			addressing_type = g_platform_info.getFlashToolStorageConfig().GetAddressingType();
			LOGD("Tracking Addressing Modification: addressing_type(%d).", addressing_type);
			
                    pListItem->SubItems->Add( region_prefix + "0x" + IntToHex((__int64)rom[i].region_addr, addressing_type) );
                    pListItem->SubItems->Add( "0x" + IntToHex((__int64)rom[i].begin_addr, addressing_type) );
                    pListItem->SubItems->Add( "0x" + IntToHex((__int64)rom[i].end_addr, addressing_type) );
                    pListItem->SubItems->Add(rom[i].filepath);

                   if ( dl_info.m_config.m_is_nfb ) {
                    // NFB: ROMs
                       pListItem->Data = &g_LV_ItemType[LV_NFB_DL_ROM];
                   }
                   else {
                   // NOR BOOT: BOOTLOADER and ROMs
                   if ( pListItem->Caption == AnsiString("BOOTLOADER") ) {
                        pListItem->Data = &g_LV_ItemType[LV_NOR_BOOTLOADER];
                   }
                   else {
                        pListItem->Data = &g_LV_ItemType[LV_NOR_DL_ROM];
                   }
                }						   
	        }
            else
            {
                continue;
            }			      			
        }			
    }
}

update_param:
	// update parameter list view

	// add OTP parameters
	{
		pListItem = m_ParamListView->Items->Add();
		pListItem->Caption = "OTP";
		pListItem->Checked = p_node->m_param.m_otp_enable?true:false;
		s.printf("addr(0x%08X), len(%lu), %s, %s", p_node->m_param.m_otp.m_addr, p_node->m_param.m_otp.m_len, OTPOpToString(p_node->m_param.m_otp_op), p_node->m_param.m_otp_filepath.c_str());
	    pListItem->SubItems->Add(s);
		pListItem->Data = &g_LV_ItemType[LV_OTP];
	}
	// add Security Setting
	if( dl_info.m_config.m_security_supported )
	{
		AnsiString	str_lock   ="";
		AnsiString	str_code   ="";
		AnsiString	str_sec_ro ="";
		AnsiString	str_fat    ="";
		AnsiString	str_restricted_area  ="";
		AnsiString	str_secure_cust_name ="";

		if ( p_node->m_param.m_ft_cfg.m_security_cfg.m_bit_ctrl.m_lockdown ) {
			str_lock.printf("SecuritySetting(Lockdown), ");
		}
        else {
//			str_lock.printf("SecuritySetting(Allow-Overwrite), ");
    	}

		if ( !p_node->m_param.m_ft_cfg.m_security_cfg.m_bit_ctrl.m_disable_code_download ) {
			str_code = "W";
		}

		if ( !p_node->m_param.m_ft_cfg.m_security_cfg.m_bit_ctrl.m_disable_code_readback )
        {
			if( 0 < str_code.Length() )
            {
				str_code += "/";
			}
			str_code += "R";
		}

		if ( !p_node->m_param.m_ft_cfg.m_security_cfg.m_bit_ctrl.m_disable_code_format )
        {
			if ( 0 < str_code.Length() ) {
				str_code += "/";
			}
			str_code += "F";
		}

		if ( 0 == str_code.Length() ) {
			str_code = "Forbidden";
		}

		if ( !p_node->m_param.m_ft_cfg.m_security_cfg.m_bit_ctrl.m_disable_sec_ro_download )
        {
			str_sec_ro = "W";
		}

		if ( !p_node->m_param.m_ft_cfg.m_security_cfg.m_bit_ctrl.m_disable_sec_ro_readback )
        {
			if( 0 < str_sec_ro.Length() ) {
				str_sec_ro += "/";
			}
			str_sec_ro += "R";
		}

		if ( 0 == str_sec_ro.Length() ) {
			str_sec_ro = "Forbidden";
		}

		if ( !p_node->m_param.m_ft_cfg.m_security_cfg.m_bit_ctrl.m_disable_fat_download ) {
			str_fat = "W";
		}

		if ( !p_node->m_param.m_ft_cfg.m_security_cfg.m_bit_ctrl.m_disable_fat_readback )
        {
			if( 0 < str_fat.Length() )
            {
				str_fat += "/";
			}
			str_fat += "R";
		}

		if ( !p_node->m_param.m_ft_cfg.m_security_cfg.m_bit_ctrl.m_disable_fat_format )
        {
			if( 0 < str_fat.Length() )
            {
				str_fat += "/";
			}
			str_fat += "F";
		}

		if ( 0 == str_fat.Length() ) {
			str_fat = "Forbidden";
		}

		if ( p_node->m_param.m_ft_cfg.m_security_cfg.m_bit_ctrl.m_restricted_area_access_forbidden ) {
			str_restricted_area.printf(", RestrictedArea(Forbidden)");
		}
        else {
//			str_restricted_area.printf(", RestrictedArea(Allow-Overwrite)");
    	}

		pListItem = m_ParamListView->Items->Add();
		pListItem->Caption = "Security Setting";
		pListItem->Checked = p_node->m_param.m_ft_cfg_enable?true:false;
		s.printf("%sCODE(%s), SEC_RO(%s), FAT(%s)%s%s", str_lock.c_str(), str_code.c_str(), str_sec_ro.c_str(), str_fat.c_str(), str_restricted_area.c_str(), str_secure_cust_name.c_str());
	    pListItem->SubItems->Add(s);
		pListItem->Data = &g_LV_ItemType[LV_FTCFG];
	}
    else{
        p_node->m_param.m_ft_cfg_enable = (_BOOL) false;
    }


	// add SEC_RO m_parameters
	if( dl_info.m_config.m_security_supported && p_node->m_param.m_sec_ro.m_len > 0 )
	{
		pListItem = m_ParamListView->Items->Add();
		pListItem->Caption = "Secure RO Data";
		pListItem->Checked = p_node->m_param.m_sec_ro_enable?true:false;
		s.printf("len(%I64u): %s", p_node->m_param.m_sec_ro.m_len, p_node->m_param.m_sec_ro_filepath.c_str());
	    pListItem->SubItems->Add(s);
		pListItem->Data = &g_LV_ItemType[LV_SEC_RO];
	}
    else{
        p_node->m_param.m_sec_ro_enable = (_BOOL) false;
    }

	// add CUST_PARA m_parameters
	if( dl_info.m_config.m_cust_para_supported )
	{
		pListItem = m_ParamListView->Items->Add();
		pListItem->Caption = "Custom Parameters";
		pListItem->Checked = p_node->m_param.m_cust_para_enable?true:false;
		s.printf("len(%I64u): %s", p_node->m_param.m_cust_para.m_len, p_node->m_param.m_cust_para_filepath.c_str());
	    pListItem->SubItems->Add(s);
		pListItem->Data = &g_LV_ItemType[LV_CUST_PARA];
	}
    else{
        p_node->m_param.m_cust_para_enable = (_BOOL) false;
    }

    // add GPS ROM to List View
    if( p_node->m_param.m_gps_download )
    {
		pListItem = m_ParamListView->Items->Add();
		pListItem->Caption = "GPS ROM";
		pListItem->Checked = p_node->m_param.m_gps_enable?true:false;
		s.printf("len(%lu): %s", p_node->m_param.m_gps_rom_filesize, p_node->m_param.m_gps_rom_filepath.c_str());
	    pListItem->SubItems->Add(s);
		pListItem->Data = &g_LV_ItemType[LV_GPS_ROM];
    }
    else{
    	p_node->m_param.m_gps_enable = (_BOOL) false;
    }
}
//---------------------------------------------------------------------------
void TMainForm::RedrawDownloadCheckBox()
{

    CS_Sentry	cs(m_pUpdateListLock);

    unsigned short	count;

    if ( NULL == g_pCurNode ) return;

    DL_HANDLE_T &dl_handle = g_pCurNode->m_dl_handle;
    for ( int i=0; i<ListView1->Items->Count; i++ )
    {
		ListViewItemType_E	type=*((ListViewItemType_E *)ListView1->Items->Item[i]->Data);

		if ( LV_NFB_BOOTLOADER == type )
        {
			BL_INFO	bl_info;
			if( S_DONE == DL_BL_GetInfo(dl_handle, &bl_info) )
            {
				ListView1->Items->Item[i]->Checked = (_TRUE==bl_info.m_enable)?true:false;

                LOGD("TMainForm::RedrawDownloadCheckBox");
                Logger::GetLogger().Log(Logger::Debug, "BL info, m_filepath: %s, m_enable: %d",
                		bl_info.m_filepath, bl_info.m_enable);
			}
		}
        else if( LV_NFB_EXT_BOOTLOADER == type )
        {
			BL_INFO	bl_info;
			if( S_DONE == DL_BL_GetInfo(dl_handle, &bl_info) )
            {
				ListView1->Items->Item[i]->Checked = (_TRUE==bl_info.m_enable)?true:false;
			}
        }
		else {
			ROM_INFO	rom;
            int itemIndex = GetROMIndex( ListView1->Items->Item[i]->Caption.c_str(), dl_handle);
            if ( -1 == itemIndex )
            {
                ShowMessage("Obtaining rom index fails.");
                return;
            }            

			if ( S_DONE == DL_Rom_GetInfo(dl_handle, itemIndex, &rom) ) {
/* NFB MBA: Ray, 20080502
				if( (LV_NFB_DL_ROM==type) && rom.enable ) {
					// always enable boot loader, if there is any rom files selected to download
					ListView1->Items->Item[0]->Checked = true;
					DL_BL_SetEnableAttr(dl_handle, _TRUE);
				}
*/
				ListView1->Items->Item[i]->Checked = ((_TRUE==rom.enable) ? true : false) && \
                                                     ((_TRUE==rom.item_is_visable) ? true : false);
#if 0
//Mark old log info
                LOGD("======================RedrawDownloadCheckBox===========================");
                Logger::GetLogger().Log(Logger::Debug,
                		"ROM INFO: item index: %d, name: %s, m_filepath: %s, rom_index: %d, m_enable: %d, item_is_visable: %d",
                		itemIndex, rom.name, rom.filepath, rom.index, rom.enable, rom.item_is_visable);
#endif
			}
		}	
              
              if(i == DL_IndexOfChangedCheckBox)
	    		CSHintMessage(i);
		
	}	
}

//---------------------------------------------------------------------------
void TMainForm::RedrawReadbackList()
{
    unsigned short count;
	AnsiString	s;
	TListItem	*pListItem;

    lv_ReadBack->Items->Clear();

	if( !RB_GetCount(g_RB_HANDLE, &count) && 0<count )
    {

		RB_INFO	 *rb = new RB_INFO[count];

		if( NULL != rb )
        {
			if( !RB_GetInfoAll( g_RB_HANDLE, rb, count ) )
            {
				for( int i=0; i < count; i++ )
                {
					TListItem	*pListItem;
					pListItem = lv_ReadBack->Items->Add();
					pListItem->Checked = (_TRUE==rb[i].enable?true:false);

					if( g_platform_info.getFlashToolStorageConfig().IsNandOperation() )
                    {
						switch( rb[i].m_read_flag )
                        {
						    case NUTL_READ_PAGE_ONLY:
							    pListItem->Caption = "PageOnly";
							    break;

						    case NUTL_READ_SPARE_ONLY:
							    pListItem->Caption = "SpareOnly";
							    break;

						    case NUTL_READ_PAGE_WITH_ECC:
							    pListItem->Caption = "PageWithECC";
							    break;

						    case NUTL_READ_PAGE_SPARE:
						    default:
							    pListItem->Caption = "PageSpare";
							    break;
						}

					}
                    else    // NOR_OPERATION or EMMC_OPERATION
                    {
						pListItem->Caption = "N/A";
                    }
                    //TODO: EMMC_OPERATION should provide all types of partitions
                                   int addressing_type = 0;
					addressing_type = g_platform_info.getFlashToolStorageConfig().GetAddressingType();
                                   LOGD("Tracking Addressing Modification: addressing_type(%d)", addressing_type);
					pListItem->SubItems->Add( "0x" + IntToHex((__int64)rb[i].readback_addr, 16) );
					pListItem->SubItems->Add( "0x" + IntToHex((int)rb[i].readback_len, 8) );
					pListItem->SubItems->Add( rb[i].filepath );
				}
			}
			delete [] rb;
		}
	}


	// update "Read" parameter list view
    m_ReadParamListView->Items->Clear();
	// add OTP parameters
	{
		pListItem = m_ReadParamListView->Items->Add();
		pListItem->Caption = "OTP";
		pListItem->Checked = g_ReadbackPage_Param.m_otp_enable?true:false;
		s.printf("addr(0x%08X), len(%lu), %s", g_ReadbackPage_Param.m_otp.m_addr, g_ReadbackPage_Param.m_otp.m_len, g_ReadbackPage_Param.m_otp_filepath.c_str());
	    pListItem->SubItems->Add(s);
		pListItem->Data = &g_LV_ItemType[LV_OTP];
	}
	// add SEC_RO m_parameters
	{
		pListItem = m_ReadParamListView->Items->Add();
		pListItem->Caption = "Secure RO Data";
		pListItem->Checked = g_ReadbackPage_Param.m_sec_ro_enable?true:false;
		s.printf("len(%d): %s", g_ReadbackPage_Param.m_sec_ro.m_len, g_ReadbackPage_Param.m_sec_ro_filepath.c_str());
	        pListItem->SubItems->Add(s);
		pListItem->Data = &g_LV_ItemType[LV_SEC_RO];
	}
	// add CUST_PARA m_parameters
	{
		pListItem = m_ReadParamListView->Items->Add();
		pListItem->Caption = "Custom Parameters";
		pListItem->Checked = g_ReadbackPage_Param.m_cust_para_enable?true:false;
		s.printf("len(%d): %s", g_ReadbackPage_Param.m_cust_para.m_len, g_ReadbackPage_Param.m_cust_para_filepath.c_str());
	    pListItem->SubItems->Add(s);
		pListItem->Data = &g_LV_ItemType[LV_CUST_PARA];
	}
}
//---------------------------------------------------------------------------
static int RB_IndexOfChangedCheckBox = -1;
static bool RB_bPreviousCheckBoxValue;

void __fastcall TMainForm::lv_ReadBackChange(TObject *Sender, TListItem *Item, TItemChange Change)
{
	// ShowMessage("Changed");

    if( (ctState == Change) && (Item->Checked != RB_bPreviousCheckBoxValue) )
    {
        RB_IndexOfChangedCheckBox = Item->Index;
        return;
    }

    RB_IndexOfChangedCheckBox = -1;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::lv_ReadBackChanging(TObject *Sender, TListItem *Item, TItemChange Change, bool &AllowChange)
{
	// ShowMessage("Changing");

	RB_bPreviousCheckBoxValue = Item->Checked;

    RB_IndexOfChangedCheckBox = -1;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::lv_ReadBackClick(TObject *Sender)
{
	TListView *plv = dynamic_cast<TListView *>(Sender);

	//	ShowMessage("Click");

    if( 0<=RB_IndexOfChangedCheckBox && RB_IndexOfChangedCheckBox<plv->Items->Count )
    {
	    // update enabled flag according to checkbox
		RB_SetEnableAttr(g_RB_HANDLE, RB_IndexOfChangedCheckBox, plv->Items->Item[RB_IndexOfChangedCheckBox]->Checked?_TRUE:_FALSE);
        /*if(plv->Items->Item[RB_IndexOfChangedCheckBox]->Checked) {
			ShowMessage("Enable");
        }
        else {
			ShowMessage("Disable");
    	}*/
    }

    RB_IndexOfChangedCheckBox = -1;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::lv_ReadBackDblClick(TObject *Sender)
{
	TListView *plv = dynamic_cast<TListView *>(Sender);

	//	ShowMessage("DoubleClick");

    if( 0<=RB_IndexOfChangedCheckBox && RB_IndexOfChangedCheckBox<plv->Items->Count )
    {
	    // update enabled flag according to checkbox
		RB_SetEnableAttr(g_RB_HANDLE, RB_IndexOfChangedCheckBox, plv->Items->Item[RB_IndexOfChangedCheckBox]->Checked?_TRUE:_FALSE);
        /*if(plv->Items->Item[RB_IndexOfChangedCheckBox]->Checked) {
			ShowMessage("Enable");
        }
        else {
			ShowMessage("Disable");
    	}*/
    }
	else {
		lv_ReadBack_oldDblClick(Sender);
    }

    RB_IndexOfChangedCheckBox = -1;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ListView1InfoTip(TObject *Sender, TListItem *Item, AnsiString &InfoTip)
{
	static ROM_TYPE			rom_type;
	static ROM_INFO			rom;
	static MTK_Resource		res_info;
	static MTK_JumpTable	jmptbl_info;
	static BL_INFO			bl_info;
	static char	custom_name[128], bbchip_name[128];

	char *p_filename=NULL;
	char path[512];
	AnsiString  filename;
	AnsiString	res_string;
	AnsiString	filepath="";

	InfoTip = "";

    if( NULL == g_pCurNode ) {
    	return;
	}

	DL_HANDLE_T &dl_handle = g_pCurNode->m_dl_handle;
	ListViewItemType_E	type=*((ListViewItemType_E *)Item->Data);

	// get NFB hint
	if( LV_NFB_BOOTLOADER == type )
    {
		// boot loader info
		if( S_DONE == DL_BL_GetInfo(dl_handle, &bl_info) && 0!=bl_info.m_chksum )
        {
			GetFullPathName(bl_info.m_filepath, sizeof(path), path, &p_filename);

			if( NULL!=p_filename && (strlen(bl_info.m_filepath)>(strlen(p_filename)+12)) )
            {
				filename.printf("%.12s...\\%s", path, p_filename);
			}
			else {
				filename = bl_info.m_filepath;
			}

			InfoTip.printf(" %s  (%u bytes)\nVER(%s), START_ADDR(0x%08X), CHKSUM_SEED(0x%08X), CHKSUM(0x%08X) "
					, filename.c_str()
					, bl_info.m_filesize
					, bl_info.m_version
					, bl_info.m_start_addr
					, bl_info.m_chksum_seed
					, bl_info.m_chksum);
	    }
	    else if( 0 < bl_info.m_filesize ) {
			InfoTip.printf(" %s  (%u bytes) ", filename.c_str(), bl_info.m_filesize);
		}
		return;
	}

	// get filepath
	if( 4 <= Item->SubItems->Count ) {
		filepath = Item->SubItems->Strings[3];
	}

	if( 0 >= filepath.Length() ) {
		InfoTip = "";
		return;
	}

	// get resource info
	if( (((rom.index+1)!=Item->Index)||stricmp(rom.filepath, filepath.c_str())) &&
        (S_DONE==DL_Rom_GetInfo(dl_handle, (LV_NFB_DL_ROM==type)?(Item->Index-1):Item->Index, &rom)) )
    {
		if( (RESOURCE_BIN==rom.rom_type) && (S_DONE==DL_Rom_GetResInfo(dl_handle, rom.index, &res_info)) ) {
			rom_type = RESOURCE_BIN;
		}
		else if( (JUMPTABLE_BIN==rom.rom_type) && (S_DONE==DL_GetJumpTableInfo(dl_handle, &jmptbl_info)) ) {
			rom_type = JUMPTABLE_BIN;
		}
		else {
			if( S_DONE != DL_GetCustomName(dl_handle, custom_name, sizeof(custom_name)) ||
				S_DONE != DL_GetBBChipName(dl_handle, bbchip_name, sizeof(bbchip_name)) )
			{
				custom_name[0] = '\0';
				bbchip_name[0] = '\0';
			}
			rom_type = NORMAL_ROM;
		}
	}

display:
	GetFullPathName(rom.filepath, sizeof(path), path, &p_filename);
	if( NULL!=p_filename && (strlen(rom.filepath)>(strlen(p_filename)+12)) ) {
		filename.printf("%.12s...\\%s", path, p_filename);
	}
	else {
		filename = rom.filepath;
	}

	if( RESOURCE_BIN == rom_type ) {
		res_string.printf( "[%s]:  [%s]  (0x%08X), (0x%08X), (0x%08X + 0x%08X)=%u, magic(0x%08X) ",
			               res_info.m_prefix,
                           res_info.m_project_id,
                           res_info.m_type_ver,
                           res_info.m_base_addr,
                           res_info.m_table_size,
                           res_info.m_content_size,
                           res_info.m_table_size+res_info.m_content_size,
                           res_info.m_magic);

		InfoTip = " " + filename + "  (" + IntToStr((__int64)rom.filesize) + " bytes)\n\n" + res_string;
	}

	else if( JUMPTABLE_BIN == rom_type )
    {

		InfoTip = " " + filename + "  (" + IntToStr((__int64)rom.filesize) + " bytes)\n";

		for ( int i=0; i < jmptbl_info.m_res_count; i++ )
        {
			res_string.printf( "\n[%d][%s]:  [%s]  (0x%08X), (0x%08X), (0x%08X + 0x%08X)=%u, magic(0x%08X) ",
                               i,
                               jmptbl_info.m_res[i].m_prefix,
                               jmptbl_info.m_res[i].m_project_id,
                               jmptbl_info.m_res[i].m_type_ver,
                               jmptbl_info.m_res[i].m_base_addr,
                               jmptbl_info.m_res[i].m_table_size,
                               jmptbl_info.m_res[i].m_content_size,
                               jmptbl_info.m_res[i].m_table_size + jmptbl_info.m_res[i].m_content_size,
                               jmptbl_info.m_res[i].m_magic);
			InfoTip += res_string;
		}
	}

	else if( !strcmp(rom.name, "ROM") && '\0'!=custom_name[0] && '\0'!=bbchip_name )
	{
		InfoTip.printf(" %s  (%I64u bytes), %s, %s ", filename.c_str(), rom.filesize, custom_name, bbchip_name);
	}

	else {
		InfoTip = " " + filename + "  (" + IntToStr((__int64)rom.filesize) + " bytes) ";
	}
}

void __fastcall TMainForm::m_CheckECOVersionClick(TObject *Sender)
{
	if ( g_bCheckECOVer ) {
        g_bCheckECOVer = false;
	}
    else {
        g_bCheckECOVer = true;
	}

	updateMenuItem();
}
//---------------------------------------------------------------------------

int TMainForm::UpdateDA()
{
	int ret;
	AnsiString s;
	DA_INFO	da_info;

    if(!g_bUsbDLDA)
    {
        ret = DA_IsReady(g_DA_HANDLE, &da_info, _TRUE);
        if( S_FTHND_FILE_IS_NOT_LOADED_YET == ret || S_FTHND_FILE_IS_UPDATED == ret )
        {
            ret = DA_Load(g_DA_HANDLE, da_info.filepath, g_bDebugDA?_FALSE:_TRUE, g_bUsbDLDA?_FALSE:_TRUE);
        }
 		else if (S_DONE != ret) {
			//s = da_info.filepath;
            s = g_asNormalModeDAPath.c_str();
			ShowMessage(" Check DA \"" + s + "\" fail!");
			return 3;
		}
    }
    else
    {
        ret = DA_IsReady(g_NAND_UTIL_DA_HANDLE, &da_info, _TRUE);
        if( S_FTHND_FILE_IS_NOT_LOADED_YET == ret || S_FTHND_FILE_IS_UPDATED == ret )
        {
            ret = DA_Load(g_NAND_UTIL_DA_HANDLE, da_info.filepath, g_bDebugDA?_FALSE:_TRUE, g_bUsbDLDA?_TRUE:_FALSE);
        }
 		else if (S_DONE != ret) {
			//s = da_info.filepath;
            s = asNandUtilDAPath.c_str();
			ShowMessage(" Check NandUtil \"" + s + "\" fail!");
			return 3;
		}
    }
    if( S_INVALID_DA_FILE == ret ) {
        s = da_info.filepath;
		ShowMessage(" \"" + s + "\" is not a valid " + (g_bUsbDLDA?"NandUtil":"DA") +" format!");
		return 1;
	}
	else if (S_DONE != ret) {
	    s = da_info.filepath;
		ShowMessage(" Load \"" + s + "\"" + (g_bUsbDLDA?"NandUtil":"DA") + "fail!");
		return 2;
    }
    else {
	    return 0;
    }

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::action_AdvanceOptionExecute(TObject *Sender)
{
    if( g_bEnableAdvanceOption ) {
        BaseBandChip1->Visible = false;
        MCUClock1->Visible = false;
        m_Transmission_Option->Visible = false;
        m_COM_Port_Timeout->Visible = false;
        m_BBChipOption ->Visible = false;
        mi_EMI_Config->Visible = false;
		PacketLength1->Visible = false;
        m_CheckTgtResourceLayout->Visible = false;
        m_AutoLoadResByScat->Visible = false;
        m_DA_Option->Visible = false;
        m_ResourceOption->Visible = false;
        m_BRomStartCmdRetryCount->Visible = false;
        m_PullDownGPIO17->Visible = false;

        g_bEnableAdvanceOption = false;
        mi_USBDownloadDA->Visible = true;

        //m_Menu_Backup_Restore_NVRAM->Visible = false;
        m_EnableNFICS1->Visible = false;
		//Physical operation
		m_Menu_Physical_Fmt_RB->Visible = false;
        g_bPhysicallyFormatReadback = false;
        m_Menu_Physical_Fmt_RB->Checked = false;
		//Readback SW Version
		tb_ReadbackVersion->Visible = false;
		//Readback Product Info
		tb_ReadbackProductInfo->Visible = false;
	}
    else {

	    //BaseBandChip1->Visible = true;
        //MCUClock1->Visible = true;
        m_Transmission_Option->Visible = true;
        m_COM_Port_Timeout->Visible = true;
        m_BBChipOption ->Visible = true;
        mi_EMI_Config->Visible = true;
		PacketLength1->Visible = true;
        //m_CheckTgtResourceLayout->Visible = true;
        m_AutoLoadResByScat->Visible = true;
        m_DA_Option->Visible = true;
        //m_ResourceOption->Visible = true;
        //m_BRomStartCmdRetryCount->Visible = true;
        //m_PullDownGPIO17->Visible = true;

        g_bEnableAdvanceOption = true;
        mi_USBDownloadDA->Visible = true;

        //m_Menu_Backup_Restore_NVRAM->Visible = true;
		m_Menu_Physical_Fmt_RB->Visible = true;
        m_EnableNFICS1->Visible = true;
		//Readback SW Version
		tb_ReadbackVersion->Visible = true;
		//Readback Product Info
		tb_ReadbackProductInfo->Visible = true;
	}

   	UpdateCaption();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::tb_DL_StopButtonClick(TObject *Sender)
{
    // reset stop flag
	g_stopflag = BOOT_STOP;

	META_CancelAllBlockingCall();
}
//---------------------------------------------------------------------------

void TMainForm::DisableStopButton()
{
	// disable stop button
    tb_DL_StopButton->Enabled = false;
    RB_StopButton->Enabled = false;
    bb_SCI_DL_Stop->Enabled = false;
    bb_Clone_Readback_Stop->Enabled = false;
    bb_Clone_Restore_Stop ->Enabled= false;
}
//---------------------------------------------------------------------------
void TMainForm::EnableStopButton()
{
	// enable stop button
    tb_DL_StopButton->Enabled = true;
    RB_StopButton->Enabled = true;
    bb_SCI_DL_Stop->Enabled = true;
    bb_Clone_Readback_Stop->Enabled = true;
    bb_Clone_Restore_Stop->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::RB_StopButtonClick(TObject *Sender)
{
	g_stopflag = BOOT_STOP;
	META_CancelAllBlockingCall();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::m_CheckTgtResourceLayoutClick(TObject *Sender)
{
	if( g_bCheckTgtResourceLayout ) {
        g_bCheckTgtResourceLayout = false;
	}
    else {
        g_bCheckTgtResourceLayout = true;
	}

	updateMenuItem();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::m_AutoLoadResByScatClick(TObject *Sender)
{
	if( g_bAutoLoadResByScat ) {
        g_bAutoLoadResByScat = false;
	}
    else {
        g_bAutoLoadResByScat = true;
	}

	updateMenuItem();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::m_BRomStartCmdRetryCountClick(TObject *Sender)
{
	frm_BromStartCmdRetry->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::m_PullDownGPIO17Click(TObject *Sender)
{
	if ( g_bPullDownGPIO17 ) {
        g_bPullDownGPIO17 = false;
	}
    else {
        g_bPullDownGPIO17 = true;
	}

	updateMenuItem();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::mi_EMI_ConfigClick(TObject *Sender)
{
	ext_mem1Form->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::m_COM_Port_TimeoutClick(TObject *Sender)
{
	COM_Option->Visible = true;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::m_SpeedUpBootROMBaudrateClick(TObject *Sender)
{
	if( g_SpeedUpBootROMBaudrate ) {
        g_SpeedUpBootROMBaudrate = false;
	}
    else {
        g_SpeedUpBootROMBaudrate = true;
	}
	updateMenuItem();
}
//---------------------------------------------------------------------------

bool TMainForm::FileSaveTestModeLogExecute()
{
    int iLastDel;
    AnsiString file_ext;

    Dialog_SaveTestModeLog->Filter = "Text files (*.txt)|*.TXT";
    if ( Dialog_SaveTestModeLog->Execute() )
    {
        TestModeLogFile = Dialog_SaveTestModeLog->FileName;
        iLastDel = TestModeLogFile.LastDelimiter(".");

        if ( 0 < iLastDel )
        {
	        file_ext = TestModeLogFile.SubString(iLastDel+1, 1000);
            if ( stricmp(file_ext.c_str(), "txt")) {
                TestModeLogFile += ".txt";
            }
        }
        else {
            TestModeLogFile += ".txt";
        }

        return true;
    }
    else {
        return false;
    }
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::FileSave_TestModeLogExecute(TObject *Sender)
{
    if( g_bDebugDA && FileSaveTestModeLogExecute() )
    {
        FILE    *fp;
        if( NULL != ( fp=fopen( TestModeLogFile.c_str(), "w+b" ) ) )
        {
            fwrite((void *)DebugDAWindow->Text.c_str(), 1, DebugDAWindow->Text.Length(), fp);
            fclose(fp);
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::m_CompareProjectIdClick(TObject *Sender)
{
	if( g_CompareResProjectId ) {
        g_CompareResProjectId = false;
	}
    else {
        g_CompareResProjectId = true;
	}
    DL_ResourceProjectIdComparisonSetting(g_pCurNode->m_dl_handle, g_CompareResProjectId?_TRUE:_FALSE);
	updateMenuItem();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::m_FakeProgressTimerTimer(TObject *Sender)
{
	MainForm->CGauge1->Progress += 2;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::m_EnableNFICS1Click(TObject *Sender)
{
	if( g_bNFI_SelectCS1 ) {
        g_bNFI_SelectCS1 = false;
	}
    else {
        g_bNFI_SelectCS1 = true;
	}
	updateMenuItem();
}
//---------------------------------------------------------------------------
#if 0
void __fastcall TMainForm::m_Menu_OPM_NANDClick(TObject *Sender)
{
	if( g_platform_info.getFlashToolStorageConfig().IsNandOperation() ) {
        return;
    }
	
	g_platform_info.getFlashToolStorageConfig().set_operation(NAND_OPERATION);
	LOG("TMainForm::m_Menu_OPM_NANDClick(): Storage type(%s)", 
		g_platform_info.getFlashToolStorageConfig().GetStorageName().c_str());
	updateMenuItem();
    updateStatusBar();
    RedrawReadbackList();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::m_Menu_OPM_EMMCClick(TObject *Sender)
{
	if( g_platform_info.getFlashToolStorageConfig().IsEMMCOperation() ) {
        return;
    }

    g_platform_info.getFlashToolStorageConfig().set_operation(EMMC_OPERATION);
	updateMenuItem();
    updateStatusBar();
    RedrawReadbackList();
}
#endif
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormDestroy(TObject *Sender)
{
   	delete m_pUpdateListLock;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::sb_MainDrawPanel(TStatusBar *StatusBar, TStatusPanel *Panel, const TRect &Rect)
{
    AnsiString  s;

    if( 1 != Panel->Index ) {
        return;
    }

    StatusBar->Canvas->Font->Color = (TColor) 0x00000000;
    s = g_platform_info.getFlashToolStorageConfig().GetStorageName().c_str();
#if 0
	switch( g_platform_info.getFlashToolStorageConfig().GetStorageType() )
    {
	    case NAND_OPERATION:
		    s = " NAND";
		    break;

	    case EMMC_OPERATION:
            StatusBar->Canvas->Font->Color = (TColor) 0x007000A0;
		    s = " EMMC";
		    break;

	    default:
		    s = "??";
		    break;
	}
#endif
    StatusBar->Canvas->Font->Style = TFontStyles() << fsBold;
    StatusBar->Canvas->Font->Name = "Arial";
    StatusBar->Canvas->Font->Size = 9;
    StatusBar->Canvas->TextOutA(Rect.Left+2, Rect.Top+2, s);
}
//---------------------------------------------------------------------------
void TMainForm::HWStatusBarClear()
{
    MainForm->sb_Main->Panels->Items[5]->Text = "";
  	MainForm->sb_Main->Hint = "";
    MainForm->m_HWStatus->Panels->Items[0]->Text = "";
    MainForm->m_HWStatus->Panels->Items[1]->Text = "";
    //MainForm->m_HWStatus->Panels->Items[2]->Text = "";
    MainForm->m_HWStatus->Panels->Items[3]->Text = "";
  	MainForm->m_HWStatus->Hint = "";

	// reset download time
    sb_Main->Panels->Items[4]->Text = " 0:00 sec ";
    g_CostTimeSec = 0;  // reset download time
	g_ProgressTimeSec = 0;
}

//---------------------------------------------------------------------------
void TMainForm::HWStatusBarUpdate( const DA_REPORT_T *p_da_report,
                                   const char *p_device_hint, 
                                   const char *m_hw_detection_report)
{

	if( NULL == p_da_report ) {
		return;
	}

    LOG( "(CB-UI)TMainForm::HWStatusBarUpdate():m_da_report addr: %x, chip name: %s, chip type: %d, ext ram size: %x",
            p_da_report, p_da_report->m_bbchip_name, 
            p_da_report->m_bbchip_type, p_da_report->m_ext_ram_size);

	AnsiString  s;

	// selected DL_HANDLE name
	if( NULL != p_da_report->m_dl_handle )
    {
		char cust_name[1024];

		if( S_DONE == DL_GetCustomName( p_da_report->m_dl_handle, cust_name, sizeof(cust_name) ) )
        {
			s.printf( "Project: %s", cust_name);
			MainForm->m_HWStatus->Panels->Items[2]->Text = s;
		}
	}

	// bbchip info
	MainForm->m_HWStatus->Panels->Items[0]->Text = p_da_report->m_bbchip_name;

	// ram
	AnsiString	str_ext_ram_size;
	AnsiString	str_ext_ram_type;
	double size_in_double;

	//size_in_double = p_da_report->m_ext_ram_size*8;
	size_in_double = p_da_report->m_ext_ram_size;
    LOG("(CB-UI)TMainForm::HWStatusBarUpdate(): da report ext ram size: %x, extern ram size: %x.", 
        p_da_report->m_ext_ram_size, size_in_double);
	
	if ( 0x100000 <= size_in_double )
    {
		str_ext_ram_size.printf("%dMb", (unsigned int)((size_in_double/0x100000)*8));
    }
    else {
		str_ext_ram_size.printf("%dKb", (unsigned int)(size_in_double*8/0x400));
	}

	switch ( p_da_report->m_ext_ram_type )
    {
	    case HW_RAM_SRAM:
		    str_ext_ram_type = "SRAM";
		    break;

	    case HW_RAM_DRAM:
		    str_ext_ram_type = "DRAM";
		    break;

	    case HW_RAM_UNKNOWN:
	    default:
		    str_ext_ram_type = "RAM Fail";
		    break;
	}

	if( S_DONE == p_da_report->m_ext_ram_ret ) {
		s.printf( "%s %s", str_ext_ram_size.c_str(), str_ext_ram_type.c_str() );
	}
	else {
		s = str_ext_ram_type;
	}

	MainForm->m_HWStatus->Panels->Items[1]->Text = s;
#if 0
	// NOR flash
	s.printf("NOR: %s", p_nor_flash_hint);
	MainForm->sb_Main->Panels->Items[5]->Text    = s;
#endif
	// Device Info
	s.printf("%s", p_device_hint);
	MainForm->m_HWStatus->Panels->Items[3]->Text = s;

	// set hint
	MainForm->m_HWStatus->Hint = m_hw_detection_report;

	// Multi-Load
	if ( mi_MultiLoad->Checked )
    {
		for ( unsigned int index = 0; index < g_DL_HANDLE_LIST_nodes.size(); index++ )
        {
			if( g_DL_HANDLE_LIST_nodes[index].m_dl_handle == p_da_report->m_dl_handle )
            {
				TTreeNode * node    = g_rootLoad->Item[index];
				node->ImageIndex    = 2;
				node->SelectedIndex = 2;
				break;
			}
		}
	}
}


//---------------------------------------------------------------------------

bool TMainForm::LoadByDownloadSet(const DownloadSet &dl_set, MultiLoadNode  *p_node)
{
	unsigned int i;
	AnsiString	err;

	if( NULL ==  p_node ) {
		return false;
	}

	DL_HANDLE_T &dl_handle = p_node->m_dl_handle;

	// check if scatter file exists
	if( INVALID_FILE_ATTRIBUTES == GetFileAttributes(dl_set.m_Scatter.c_str()) ) {
        LOGE("Default scatter file doesn't exit!");
		return false;
	}

	// check if bootloader exists
	if( 0<dl_set.m_BootLoader.Length() && INVALID_FILE_ATTRIBUTES==GetFileAttributes(dl_set.m_BootLoader.c_str()) ) {
		// pop error message
		err.printf("BootLoader doesn't exit!\n\n%s", dl_set.m_BootLoader.c_str());
		ShowMessage(err);
		return false;
	}

	// check if all the bin files exist
	for ( i=0; i<dl_set.m_BinFiles.size(); i++ )
    {
		if ( dl_set.m_BinFiles[i].m_Enable &&
			(0<dl_set.m_BinFiles[i].m_Filepath.Length()) &&
            INVALID_FILE_ATTRIBUTES==GetFileAttributes(dl_set.m_BinFiles[i].m_Filepath.c_str())
        ) {
			// pop error message
			err.printf("File[%d] doesn't exit!\n\n%s", i, dl_set.m_BinFiles[i].m_Filepath.c_str());
			ShowMessage(err);
			return false;
		}
	}
	//Send image-type table before load scatter file, otherwise, default table will be used
    BromDLTypeTblEntry(dl_handle);
	// load scatter
	std::string error_msg;
	bool isSCI = (MainForm->ts_SCIDownload == MainForm->pc_mainframe->ActivePage)
		           ||(MainForm->ts_SCIClone == MainForm->pc_mainframe->ActivePage);
    /* Adapt new storage layout file, 2012/12/22 { */
#if 0
	g_platform_info.initByScatterFile(dl_set.m_Scatter.c_str(), error_msg, isSCI);
	if(!g_platform_info.is_scatter_file_valid()) {
		ShowMessage(error_msg.c_str());
		return false;
	} else if (!g_platform_info.is_storage_type_support()) {
		ShowMessage(error_msg.c_str());
	}
#endif
    /* Adapt new storage layout file, 2012/12/22 } */
   
	/******Load configration XML files begin******/
	//Load usb_setting.xml table
	FlashToolUSBTable usb_table = GetFlashToolUSBTable();
	//Load storage_setting.xml table
	GetFlashToolStorageTable();
	/******Load configration XML files end******/
	if ( S_DONE != DL_LoadScatter(dl_handle, dl_set.m_Scatter.c_str(), g_platform_info.getLoadPlatformName().c_str() ) )
    {
		// pop error message
		err.printf("Fail to load Scatter file!\n\n%s", dl_set.m_Scatter.c_str());
		ShowMessage(err);
		return false;
	}
    /* Adapt new storage layout file, 2012/12/22 { */
    DL_PlatformInfo plat_info;
    DL_GetPlatformInfo(g_DL_HANDLE_NODE.m_dl_handle, &plat_info);
    g_platform_info.InitByPlatCfgInfo(plat_info, error_msg, isSCI);

    //Update Auto Polling 
    this->m_is_auto_polling_enable = g_platform_info.getPlatformConfig().IsAutoPollingEnable();
    this->m_auto_polling_upper_limit = g_platform_info.getPlatformConfig().AutoPollingUpperLimit();
    LOGD("m_is_auto_polling_enable(%s), m_auto_polling_upper_limit(%d).",
		m_is_auto_polling_enable ? "true" : "false", m_auto_polling_upper_limit);

    //Update UI
    this->gb_NANDTest->Enabled = g_platform_info.getFlashToolStorageConfig().IsNandOperation();
    this->gb_EMMCTest->Enabled = g_platform_info.getFlashToolStorageConfig().IsEMMCOperation();
    
	if(!g_platform_info.is_scatter_file_valid()) {
		ShowMessage(error_msg.c_str());
		return false;
	} else if (!g_platform_info.is_storage_type_support()) {
		ShowMessage(error_msg.c_str());
	}
    /* Adapt new storage layout file, 2012/12/22 } */
	p_node->m_scat_file = dl_set.m_Scatter;

	// update scatter file's base directory
	if ( 0 < p_node->m_scat_file.Length() )
    {
		int iLastDel = p_node->m_scat_file.LastDelimiter("\\:");

		if ( 0 < iLastDel ) {
			ScatBaseDir = p_node->m_scat_file.SubString(1, iLastDel-1 );
		}
	}
	
	//Get BMT Pool count
	unsigned int bmt_block_count = 0;
	if ( g_platform_info.getPlatformConfig().supportLogicalAddress()){
		int ret = S_DONE;
		if((S_DONE != ( ret = DL_GetBMTBlockCount(dl_handle, &bmt_block_count)))  ) {
		    ShowMessage("[Warning Hint] Get BMT block count fail, default BMT block count is used!");
			
			LOG("WARNING: TMainForm::LoadByDownloadSet(): Get BMT block count failed(%d)! DA DL all will be disabled.",ret);
			if(S_INVALID_BMTSIZE == ret){
				g_platform_info.setDADownloadAllEnabled(false);
				g_platform_info.setBMTBlocks(PlatformInfo::DEFAULT_BMT_BLOCKS_MT6573);
			}else{
				assert(0 && "DL_GetBMTBlockCount unknown error!");
			}
		} else {
			g_platform_info.setBMTBlocks(bmt_block_count);
			g_platform_info.setDADownloadAllEnabled(true);
			LOG("TMainForm::LoadByDownloadSet(): Get BMT block count is %d.", bmt_block_count);
		}
	}

	// load boot loader
	if ( 0 < dl_set.m_BootLoader.Length() )
    {
		if ( S_DONE != DL_BL_Load(dl_handle, dl_set.m_BootLoader.c_str()) ) {
			// pop error message
			err.printf("Fail to load BootLoader!\n\n%s", dl_set.m_BootLoader.c_str());
			ShowMessage(err);
			return false;
		}
		DL_BL_SetEnableAttr (dl_handle, dl_set.m_BootLoader_Enable?_TRUE:_FALSE);
	}

	// load bin files
	GetAndroidImageInfoTable().Reset();
	for ( unsigned int i=0; i < dl_set.m_BinFiles.size(); i++ )
    {
		if( dl_set.m_BinFiles[i].m_Enable &&
			(0<dl_set.m_BinFiles[i].m_Filepath.Length()))
        {
			if(S_DONE == DL_Rom_Load(dl_handle, i, dl_set.m_BinFiles[i].m_Filepath.c_str())){
				//fill AndroidImageInfoTable
				if(g_project_mode == YuSu){
					ROM_INFO rom;
					if(S_DONE == DL_Rom_GetInfo(dl_handle,i,&rom)){
						ImageType imgType = GetImageMapRule().queryType(rom.name);
						ImageItem imgItem = GetImageMapRule().getImageItem(imgType);
						if( !imgItem.is_bootloader() && imgItem.is_format_effective() ){
							AndroidImageInfo info;
							info.romIndex = i;
							info.type = static_cast<DM_IMG_TYPE>(imgType);
							info.format = static_cast<DM_IMG_FORMAT>(imgItem.eboot_format());
							info.romName = rom.name;
							info.filePath = rom.filepath;
							GetAndroidImageInfoTable().UpdateInfo(rom.name,info);
						}
					}
				}
			}else{
			// pop error message
			err.printf("Fail to load File[%d]!\n\n%s", i, dl_set.m_BinFiles[i].m_Filepath.c_str());
			ShowMessage(err);
			return false;
		}
		}
		DL_Rom_SetEnableAttr(dl_handle, i, dl_set.m_BinFiles[i].m_Enable?_TRUE:_FALSE);
		// update ROM file's base directory
		if( 0==i && 0<dl_set.m_BinFiles[i].m_Filepath.Length() )
        {
			int iLastDel = dl_set.m_BinFiles[i].m_Filepath.LastDelimiter("\\:");
			if( 0 < iLastDel ) {
				ROMBaseDir = dl_set.m_BinFiles[i].m_Filepath.SubString(1, iLastDel-1 );
			}
		}


					}

    // update Parameter List
    {
        //---------------------------------------------------------
        // update Parameter List
        AnsiString tmp_dir;
        AnsiString tmp_file;

        // initialize Check Box of SEC_RO and CUST_PARA
        tmp_dir = ExtractFileDir(p_node->m_scat_file);

        // Load SEC_RO
        p_node->m_param.m_sec_ro_enable     = _TRUE;
        p_node->m_param.m_sec_ro_filepath   = "";

        tmp_file = tmp_dir + "\\SECURE_RO";
        if ( FileExists(tmp_file) )
        {
     		if ( !LoadFile(tmp_file.c_str(), &p_node->m_param.m_sec_ro.m_data, &p_node->m_param.m_sec_ro.m_len, NULL) )
            {
                p_node->m_param.m_sec_ro_filepath = tmp_file;
            }
        }

        // Load CUST_PARA
        p_node->m_param.m_cust_para_enable = _TRUE;
        p_node->m_param.m_cust_para_filepath = "";

        tmp_file = tmp_dir + "\\CUST_PARA";
        if ( FileExists(tmp_file) )
        {
     		if( !LoadFile(tmp_file.c_str(), &p_node->m_param.m_cust_para.m_data, &p_node->m_param.m_cust_para.m_len, NULL) )
            {
                p_node->m_param.m_cust_para_filepath = tmp_file;
            }
        }

        // Check if GPS Project exists
        AnsiString gps_dir = tmp_dir + "\\GPS";
        if( DirectoryExists(gps_dir) )
        {
            unsigned int bFindGpsRom = 0;

            p_node->m_param.m_gps_download = (_BOOL) true;

            AnsiString gps_rom = gps_dir + "\\M-core";
            AnsiString gps_ini = gps_dir + "\\gps.ini";

            if ( FileExists(gps_rom) ) {
                bFindGpsRom = 1;
            }
            else
            {
                TSearchRec sr;
                if ( FindFirst(gps_dir+"\\*.bin", 0, sr) == 0 )
                {
                    do
                    {
                        gps_rom = gps_dir + "\\" + sr.Name;
                        bFindGpsRom = 1;
                        break;
                    } while( FindNext(sr) == 0 );

                    FindClose(sr);
                }
            }

            if ( bFindGpsRom && FileExists(gps_ini) )
            {
                p_node->m_param.m_gps_enable        = (_BOOL) true;
                p_node->m_param.m_gps_rom_dirpath   = gps_dir;
                p_node->m_param.m_gps_rom_filepath  = gps_rom;
                p_node->m_param.m_gps_ini_filepath  = gps_ini;

                LoadFileInfo(gps_rom.c_str(), &p_node->m_param.m_gps_rom_filesize, NULL);

                TIniFile *ini = new TIniFile( gps_ini );
            	p_node->m_param.m_gps_power_pin     = ini->ReadInteger( "GPIO", "gpio_gps_power_pin", 0xFFFF );
                p_node->m_param.m_gps_reset_pin     = ini->ReadInteger( "GPIO", "gpio_gps_reset_pin", 0xFFFF );
                p_node->m_param.m_gps_standby_pin   = ini->ReadInteger( "GPIO", "gpio_gps_standby_pin", 0xFFFF );
                p_node->m_param.m_gps_32k_pin       = ini->ReadInteger( "GPIO", "gpio_gps_32k_pin", 0xFFFF );
            }
            else{
                p_node->m_param.m_gps_enable        = (_BOOL) false;
            }
        }
        else{
            p_node->m_param.m_gps_download = (_BOOL) false;
        }
    }

	return true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::File1Click(TObject *Sender)
{
	int i;
//    const int SCATTER_FILE_LEN = strlen("scatter.txt");

    TMenuItem * DL_History[MAX_DOWNLOAD_HISTORY] = {
    	 m_DL_History_0
    	,m_DL_History_1
    	,m_DL_History_2
    	,m_DL_History_3
    	,m_DL_History_4
    	,m_DL_History_5
    	,m_DL_History_6
    	,m_DL_History_7
    	,m_DL_History_8
    	,m_DL_History_9
	};

	// invisible all history
	for(i=0; i<MAX_DOWNLOAD_HISTORY; i++) {
		DL_History[i]->Visible = false;
	}

	// update
//	if(!g_bDebugDA &&
//        ed_LinkMapFile->Text.Length() > SCATTER_FILE_LEN) {

	DownloadHistoryList::iterator	iter;
	for(i=0, iter=g_DownloadHistory.begin(); iter!=g_DownloadHistory.end(); i++, iter++) {
            if(iter->m_Scatter.IsEmpty())
            {
                continue;
            }
	    DL_History[i]->Caption.printf("%d: %s", i+1, iter->m_Scatter.c_str());
	    DL_History[i]->Visible = true;
	    DL_History[i]->OnClick = OnDownloadHistoryClick;
	}

//    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OnDownloadHistoryClick(TObject *Sender)
{
    int index;
    int i;

	// find download history index
	TMenuItem * cur_item = (TMenuItem *)Sender;
	AnsiString	title=cur_item->Caption.c_str();

	// Caption = "X&XXXXXXXXXX", delete '&' char
	char *s=title.c_str();
	char *p=strchr(s, '&');

	if( NULL != p ) {
		title.Delete(p-s+1, 1);
	}
	index = (atoi(title.c_str())-1);

	// move current index to the top of history
	DownloadHistoryList::iterator	iter;

	for ( i=0, iter=g_DownloadHistory.begin(); 0!=index && iter!=g_DownloadHistory.end(); i++, iter++)
    {
		if( i == index ) {
			DownloadSet	dl_set = (*iter);
			g_DownloadHistory.erase(iter);
			g_DownloadHistory.push_front(dl_set);
			break;
		}
	}

	// load by download history
	if(!LoadByDownloadSet(g_DownloadHistory.front(), g_pCurNode)) {
		// delete history that doesn't exist anymore
		g_DownloadHistory.pop_front();
		return;
	}

	// update list view
	RedrawReadbackList();
	RedrawDownloadList(g_pCurNode, false);

	//DL_HANDLE_T &dl_handle=g_pCurNode->m_dl_handle;

    // show Parameter List View
    //now disable parameter list
/*
    DL_INFO dl_info;
    if( !DL_GetInfo(dl_handle, &dl_info) )
    {
        if( dl_info.m_config.m_security_supported || g_pCurNode->m_param.m_gps_download ){
            m_ParamListView->Visible = true;
        }
        else{
            m_ParamListView->Visible = false;
        }
    }
    */
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mi_MultiLoadClick(TObject *Sender)
{
	if( mi_MultiLoad->Checked ){
		mi_MultiLoad->Checked = false;
		TreeView1->Visible = false;
		g_pCurNode = &g_DL_HANDLE_NODE;
	}
	else{
		mi_MultiLoad->Checked = true;
		TreeView1->Visible = true;
        g_rootLoad->Selected = true;
		g_pCurNode = NULL;
	}

	RedrawReadbackList();
	RedrawDownloadList(g_pCurNode, false);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::AddaLoad1Click(TObject *Sender)
{
	TTreeNode * nLoad;
	MultiLoadNode	node;
	char	bbchip_name[128];

	// Create DL_HANDLE instance
	DL_Create(&node.m_dl_handle);

	// load by scatter file
	if(!FileOpenLinkMapExecute(&node)) {
		goto error;
	}

	DL_GetBBChipName(node.m_dl_handle, bbchip_name, sizeof(bbchip_name));

	/* 2. Add this DL_HANDLE into List */
	if( !DL_AddHandleToList(g_DL_HANDLE_LIST, node.m_dl_handle) ){
		g_DL_HANDLE_LIST_nodes.push_back(node);    //binding
	}
	else{
		ShowMessage(AnsiString(bbchip_name) + " has already existed!");
        g_rootLoad->Selected = true;
		goto error;
	}

	// Tree View
	nLoad = TreeView1->Items->AddChild(g_rootLoad, AnsiString(bbchip_name));
	nLoad->ImageIndex = 1;
	nLoad->SelectedIndex = 1;
	nLoad->Data = &g_DL_HANDLE_LIST_nodes[g_DL_HANDLE_LIST_nodes.size()-1];
	g_rootLoad->Expand(true);

	nLoad->Selected = true;
	g_pCurNode = (MultiLoadNode *)nLoad->Data;
 	RedrawReadbackList();
	RedrawDownloadList(g_pCurNode, false);
	goto end;

error:
	DL_Destroy(&node.m_dl_handle);
end:
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DeleteaLoad1Click(TObject *Sender)
{
	if( TreeView1->Selected != g_rootLoad )
    {
		//Release DL_HANDLE instance
		DL_DeleteHandleFromList(g_DL_HANDLE_LIST,g_DL_HANDLE_LIST_nodes[TreeView1->Selected->Index].m_dl_handle);

		DL_Rom_UnloadAll(g_DL_HANDLE_LIST_nodes[TreeView1->Selected->Index].m_dl_handle);
		DL_Destroy(&g_DL_HANDLE_LIST_nodes[TreeView1->Selected->Index].m_dl_handle);

		g_DL_HANDLE_LIST_nodes.erase(&g_DL_HANDLE_LIST_nodes[TreeView1->Selected->Index]);

		//Tree View
		TreeView1->Selected->Delete();

        g_rootLoad->Selected = true;
		g_pCurNode = NULL;
 		RedrawReadbackList();
		RedrawDownloadList(g_pCurNode, false);
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::TreeView1Click(TObject *Sender)
{
	if( TreeView1->Selected != g_rootLoad )
    {
		// reDraw ListView 
		g_pCurNode = &g_DL_HANDLE_LIST_nodes[TreeView1->Selected->Index];
		RedrawReadbackList();
		RedrawDownloadList(g_pCurNode, false);
	}
}
//---------------------------------------------------------------------------
bool TMainForm::OpenAuthFile()
{
	static AnsiString asAUTH_Path;
	int ret;
	
	if ( 0 < asAUTH_Path.Length() )
    {
		m_OpenAuthFileDialog->InitialDir = asAUTH_Path;
	}
	else if ( 0 < ed_AUTH_File->Text.Length() )
    {
		const int iLastDel = ed_AUTH_File->Text.LastDelimiter("\\:");

		if ( 0 < iLastDel ) {
			m_OpenAuthFileDialog->InitialDir = ed_AUTH_File->Text.SubString(1, iLastDel-1 );
		}
	}

	if ( m_OpenAuthFileDialog->Execute() )
    {
		if( S_DONE != (ret=AUTH_Load(g_AUTH_HANDLE, m_OpenAuthFileDialog->FileName.c_str())) )
        {
			if( S_FTHND_HANDLE_BUSY_NOW == ret ) {
				ShowMessage(" Program is busy! Can not reload AUTH file right now.");
			}
			else {
				ShowMessage(" Load AUTH file \"" + m_OpenAuthFileDialog->FileName + "\" fail!");
			}
			return false;
		}

		ed_AUTH_File->Text = m_OpenAuthFileDialog->FileName;

		const int iLastDel = ed_AUTH_File->Text.LastDelimiter("\\:");

		if( 0 < iLastDel ) {
			asAUTH_Path = ed_AUTH_File->Text.SubString(1, iLastDel-1 );
		}

		return true;
	}
	else {
		return false;
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::tb_OpenAuthFileClick(TObject *Sender)
{
    OpenAuthFile();
}

//---------------------------------------------------------------------------
bool TMainForm::OpenSCertFile()
{
    static AnsiString asSCERT_Path;

    if (0 < asSCERT_Path.Length())
    {
        m_OpenSCertFileDialog->InitialDir = asSCERT_Path;
    }
    else if (0 < ed_SCERT_File->Text.Length())
    {
        const int iLastDel = ed_SCERT_File->Text.LastDelimiter("\\:");

        if (0 < iLastDel)
        {
            m_OpenSCertFileDialog->InitialDir = ed_SCERT_File->Text.SubString(1, iLastDel-1 );
        }
    }

    if (m_OpenSCertFileDialog->Execute())
    {
        ed_SCERT_File->Text = m_OpenSCertFileDialog->FileName;

        const int iLastDel = ed_SCERT_File->Text.LastDelimiter("\\:");

        if (0 < iLastDel)
        {
            asSCERT_Path = ed_SCERT_File->Text.SubString(1, iLastDel-1 );
        }
    }
    else
    {
        ed_SCERT_File->Text = "";
    }

    SCERT_Unload(g_SCERT_HANDLE);

    if (ed_SCERT_File->Text.Length() == 0)
    {
        return true;
    }

    const int ret = SCERT_Load(g_SCERT_HANDLE, ed_SCERT_File->Text.c_str());
    if (ret != S_DONE)
    {
        if (ret == S_FTHND_HANDLE_BUSY_NOW)
        {
            ShowMessage(" Program is busy! Can not reload CERT file right now.");
        }
        else
        {
            ShowMessage(" Load CERT file \"" + m_OpenSCertFileDialog->FileName + "\" fail!");
        }
    }

    return (ret == S_DONE);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FileOpenCertFileExecute(TObject *Sender)
{
    OpenSCertFile();    
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::m_AutoBBCHIPClick(TObject *Sender)
{
	g_BBCHIP_TYPE = AUTO_DETECT_BBCHIP;
	updateMenuItem();
}

//---------------------------------------------------------------------------

static int Param_IndexOfChangedCheckBox = -1;

void __fastcall TMainForm::m_ParamListViewClick(TObject *Sender)
{
	TListView *plv = dynamic_cast<TListView *>(Sender);

    if( NULL == g_pCurNode ) {
    	return;
	}

	ParamDownloadConfig_T	&param = g_pCurNode->m_param;

	if( 0<=Param_IndexOfChangedCheckBox && Param_IndexOfChangedCheckBox<plv->Items->Count )
    {
		TListItem *pItem = plv->Items->Item[Param_IndexOfChangedCheckBox];
		ListViewItemType_E	type =*((ListViewItemType_E *)pItem->Data);

		switch( type )
        {
		    case LV_OTP:
			    param.m_otp_enable       = pItem->Checked?_TRUE:_FALSE;
			    break;

		    case LV_FTCFG:
			    param.m_ft_cfg_enable    = pItem->Checked?_TRUE:_FALSE;
			    break;

		    case LV_SEC_RO:
			    param.m_sec_ro_enable    = pItem->Checked?_TRUE:_FALSE;
			    break;

		    case LV_CUST_PARA:
			    param.m_cust_para_enable = pItem->Checked?_TRUE:_FALSE;
			    break;

            case LV_GPS_ROM:
                param.m_gps_enable       = pItem->Checked?_TRUE:_FALSE;
                break;

		    default:
			    break;
		}
	}
	else if( NULL != plv->Selected )
    {
		TListItem *pItem=plv->Selected;
		ListViewItemType_E	type=*((ListViewItemType_E *)pItem->Data);

		switch( type )
        {
		    case LV_OTP:
                g_bParameterPage = false;
			    m_OTPSetting->Visible = true;

                if( param.m_otp_op == OTP_WRITE )
                {
                    m_OTPSetting->m_Write->Checked     = true;
                    m_OTPSetting->m_WriteLock->Checked = false;
                    m_OTPSetting->m_Lock->Checked      = false;
                }
                else if( param.m_otp_op == OTP_WRITE_AND_LOCK )
                {
                    m_OTPSetting->m_Write->Checked     = false;
                    m_OTPSetting->m_WriteLock->Checked = true;
                    m_OTPSetting->m_Lock->Checked      = false;
                }
                else if( param.m_otp_op == OTP_LOCK )
                {
                    m_OTPSetting->m_Write->Checked     = false;
                    m_OTPSetting->m_WriteLock->Checked = false;
                    m_OTPSetting->m_Lock->Checked      = true;
                }

       		    m_OTPSetting->m_otp_addr->Text  = param.m_otp.m_addr;
   	    	    m_OTPSetting->m_otp_len->Text   = param.m_otp.m_len;
                m_OTPSetting->m_otp_file->Text  = param.m_otp_filepath;
			    break;

		    case LV_FTCFG:
                g_bParameterPage = false;
                m_SecuritySetting->Visible = true;
			    break;

		    case LV_SEC_RO:
                g_bParameterPage = false;
			    LoadSecRO();
			    break;

		    case LV_CUST_PARA:
                g_bParameterPage = false;
			    LoadCustPara();
			    break;

            case LV_GPS_ROM:
                g_bParameterPage = false;
			    LoadGPS();
			    break;

		    default:
			    break;
		}
	}

    Param_IndexOfChangedCheckBox = -1;
}
//---------------------------------------------------------------------------

static bool Param_bPreviousCheckBoxValue;

void __fastcall TMainForm::m_ParamListViewChange(TObject *Sender,
      TListItem *Item, TItemChange Change)
{
	// ShowMessage("Changed");

    if( (ctState == Change) &&
    	(Item->Checked != Param_bPreviousCheckBoxValue) ) {
        Param_IndexOfChangedCheckBox = Item->Index;
        return;
    }

    Param_IndexOfChangedCheckBox = -1;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::m_ParamListViewChanging(TObject *Sender,
      TListItem *Item, TItemChange Change, bool &AllowChange)
{
	Param_bPreviousCheckBoxValue = Item->Checked;

    Param_IndexOfChangedCheckBox = -1;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::m_ParamListViewDblClick(TObject *Sender)
{
	m_ParamListViewClick(Sender);
}
//---------------------------------------------------------------------------
int TMainForm::LoadFileInfo(const char *pathname, unsigned int *p_nFileLength, long *p_last_modify_time)
{
	FILE *fp;
	struct _stat  file_stat={0};

	if( NULL == pathname || '\0' == pathname[0] || NULL == p_nFileLength ) return 1;


	FileUtils::FileOpenSentry	file_sentry(pathname, "rb", fp);

    if( NULL == fp ) {
        return 2;
    }

	if( _fstat(fileno(fp), &file_stat) ) {
		return 3;
	}

	unsigned int file_len;
	unsigned int buf_len;

	if( 0 >= (file_len=filelength(fileno(fp))) ) {
		return 4;
	}

	if( 0 != (file_len%2) ) {
		buf_len = file_len+1;
	}
	else {
		buf_len = file_len;
	}

	*p_nFileLength = buf_len;
	if( NULL != p_last_modify_time ) {
		*p_last_modify_time = file_stat.st_mtime;
	}

    return 0;
}
//---------------------------------------------------------------------------
int TMainForm::LoadFile(const char *pathname, unsigned char **pp_buf, unsigned int *p_nFileLength, long *p_last_modify_time)
{

	FILE *fp;
    unsigned int    ret;

	if( NULL == pp_buf ) {
		LOGW("pp_buf is NULL");
		return 1;
	}

    ret = LoadFileInfo(pathname, p_nFileLength, p_last_modify_time);
    if( ret ){
        return ret;
    }

    FileUtils::FileOpenSentry	file_sentry(pathname, "rb", fp);

    unsigned int buf_len = *p_nFileLength;
	unsigned char *buf;

	if( NULL == (buf=(unsigned char *)malloc(buf_len)) ) {
        LOGW("buf malloc fails.");
		return 5;
	}

      ErrorLookup::SetErrorCodeMode(FLASHTOOL);
	if( buf_len > fread(buf, 1, buf_len, fp) ) {
		free(buf);
        LOGW("buf_len is bigger than fread length.");
		return FT_OTP_FILE_NOT_WORD_ALIGN;
	}

	if( NULL != *pp_buf ) {
		free(*pp_buf);
	}

	*pp_buf = buf;

	return 0;
}
//---------------------------------------------------------------------------
void TMainForm::LoadSecRO(void)
{
	AnsiString	s;
    ParamDownloadConfig_T   * param;

    if( g_bParameterPage ){
        param = &g_ParamDownloadConfig;
    }
    else{
        if( NULL == g_pCurNode ) {
        	return;
    	}
        param = &g_pCurNode->m_param;
    }

	m_SelectFileDialog->Title = "Open SEC_RO file ...";
	m_SelectFileDialog->InitialDir = ROMBaseDir;

    if( m_SelectFileDialog->Execute() )
    {
		if(LoadFile(m_SelectFileDialog->FileName.c_str(), &param->m_sec_ro.m_data, &param->m_sec_ro.m_len, NULL)) {
			s.printf("Fail to load SEC_RO file \"%s\" !", m_SelectFileDialog->FileName.c_str());
			ShowMessage(s);
			return;
		}
	}

	param->m_sec_ro_filepath = m_SelectFileDialog->FileName;

    if( g_bParameterPage ){
        AnsiString ss;
        ss.printf("len(%lu): %s", param->m_sec_ro.m_len, param->m_sec_ro_filepath.c_str());
        ed_sec_ro_Write->Text = ss;
    }
    else{
    	RedrawDownloadList(g_pCurNode, true);
    }
}
//---------------------------------------------------------------------------
void TMainForm::LoadCustPara( void )
{
	AnsiString	s;
    ParamDownloadConfig_T   *param;

    if( g_bParameterPage ) {
        param = &g_ParamDownloadConfig;
    }
    else{
        if( NULL == g_pCurNode ) return;
        param = &g_pCurNode->m_param;
    }

	m_SelectFileDialog->Title = "Open Custom Defined Parameters file ...";
	m_SelectFileDialog->InitialDir = ROMBaseDir;

    if( m_SelectFileDialog->Execute() )
    {
		if( LoadFile( m_SelectFileDialog->FileName.c_str(), &param->m_cust_para.m_data, &param->m_cust_para.m_len, NULL) )
        {
			s.printf("Fail to load SEC_RO file \"%s\" !", m_SelectFileDialog->FileName.c_str());
			ShowMessage(s);
			return;
		}
	}

	param->m_cust_para_filepath = m_SelectFileDialog->FileName;

    if( g_bParameterPage )
    {
        AnsiString ss;
        ss.printf("len(%lu): %s", param->m_cust_para.m_len, param->m_cust_para_filepath.c_str());
        ed_cust_Write->Text = ss;
    }
    else{
    	RedrawDownloadList(g_pCurNode, true);
    }
}
//---------------------------------------------------------------------------
void TMainForm::LoadGPS( void )
{
	AnsiString	s;
    ParamDownloadConfig_T   *param;

    if( g_bParameterPage ) {
        param = &g_ParamDownloadConfig;
    }
    else{
        if( NULL == g_pCurNode ) {
        	return;
    	}
        param = &g_pCurNode->m_param;
    }

	m_SelectFileDialog->Title      = "Open GPS ROM file ...";
	m_SelectFileDialog->InitialDir = ROMBaseDir + "\\GPS";

    if( m_SelectFileDialog->Execute() )
    {
        AnsiString  selectDir;
//        AnsiString  selectSca;
        AnsiString  selectIni;
		if(LoadFileInfo(m_SelectFileDialog->FileName.c_str(), &param->m_gps_rom_filesize, NULL)) {
			s.printf("Fail to load GPS ROM \"%s\" !", m_SelectFileDialog->FileName.c_str());
			ShowMessage(s);
			return;
		}

        selectDir = ExtractFilePath(m_SelectFileDialog->FileName);
//        selectSca = selectDir + "scat.txt";
        selectIni = selectDir + "gps.ini";

//        if( !FileExists(selectSca) ){
//			s.printf("Fail to load GPS FW's Scatter File  \"%s\" !", selectSca.c_str());
//			ShowMessage(s);
//			return;
//        }

        if( !FileExists(selectIni) ){
			s.printf("Fail to load GPS FW's INI File      \"%s\" !", selectIni.c_str());
			ShowMessage(s);
			return;
        }
	}
    else{
        return;
    }

	param->m_gps_rom_filepath = m_SelectFileDialog->FileName;
    param->m_gps_rom_dirpath  = ExtractFilePath(param->m_gps_rom_filepath);
//    param->m_gps_sca_filepath = param->m_gps_rom_dirpath + "scat.txt";
    param->m_gps_ini_filepath = param->m_gps_rom_dirpath + "gps.ini";

    TIniFile *ini = new TIniFile( param->m_gps_ini_filepath );
    param->m_gps_power_pin   = ini->ReadInteger( "GPIO", "gpio_gps_power_pin", 1 );
    param->m_gps_reset_pin   = ini->ReadInteger( "GPIO", "gpio_gps_reset_pin", 25 );
    param->m_gps_standby_pin = ini->ReadInteger( "GPIO", "gpio_gps_standby_pin", 42 );
    param->m_gps_32k_pin     = ini->ReadInteger( "GPIO", "gpio_gps_32k_pin", 36 );

    if( g_bParameterPage )
    {
        AnsiString ss;
        ss.printf("len(%lu): %s", param->m_gps_rom_filesize, param->m_gps_rom_filepath.c_str());
        ed_gps_Write->Text = ss;
    }
    else{
    	RedrawDownloadList(g_pCurNode, true);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::tb_ParameterButtonClick(TObject *Sender)
{
	g_flashtool_function = FLASHTOOL_PARAMETER;

	if ( asBin.IsEmpty() )
    {
		//if ( !FileOpenDownloadAgentExecute() )
        if ( !FileOpenNandUtilBin(OpenDownloadAgentDialog, NORMAL_DA_BIN) )
		{
			ShowMessage(" You must open download agent file before downloading. ");
			return;
		}
	}

	// clean Flash device info
	HWStatusBarClear();

	if( UpdateDA() ) {
		return;
	}

    start_DL( true );
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::cb_otpClick(TObject *Sender)
{
    if( cb_otp->Checked )
    {
        g_ParamDownloadConfig.m_otp_enable = (_BOOL) true;
        g_ParamReadbackConfig.m_otp_enable = (_BOOL) true;

        gb_otp->Enabled = true;
        bt_otp_setting->Enabled = true;
        rb_otp_Write->Enabled   = true;
        rb_otp_Read->Enabled    = true;
        lb_otp_Write->Enabled   = true;
        lb_otp_Read->Enabled    = true;
        ed_otp_Write->Enabled   = true;
        ed_otp_Read->Enabled    = true;

        g_ParameterType = PARAM_OTP;
        //Disable Security Lock
        cb_sec_setting->Enabled = false;
		cb_sec_setting->Checked = false;
	} else {
		g_ParamDownloadConfig.m_otp_enable = (_BOOL) false;
		g_ParamReadbackConfig.m_otp_enable = (_BOOL) false;

		gb_otp->Enabled         = false;
		bt_otp_setting->Enabled = false;
		rb_otp_Write->Enabled   = false;
		rb_otp_Read->Enabled    = false;
		lb_otp_Write->Enabled   = false;
		lb_otp_Read->Enabled    = false;
		ed_otp_Write->Enabled   = false;
		ed_otp_Read->Enabled    = false;
        //enable image lock depend on platform.xml feature description
		cb_sec_setting->Enabled = g_platform_info.getPlatformConfig().supportImageLock();
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cb_sec_settingClick(TObject *Sender)
{
    if( cb_sec_setting->Checked )
    {
        g_ParamDownloadConfig.m_ft_cfg_enable = (_BOOL) true;

        gb_sec_setting->Enabled         = true;
		bt_sec_setting->Enabled         = true;
		rb_sec_setting_Write->Enabled   = true;
		lb_sec_setting_Write->Enabled   = true;
		ed_sec_setting_Write->Enabled   = false;
        g_ParameterType = PAPAM_SEC_ROM_LOCK;
        //Disable OTP
        cb_otp->Enabled = false;
		cb_otp->Checked = false;
    }
    else{
        g_ParamDownloadConfig.m_ft_cfg_enable = (_BOOL) false;

        gb_sec_setting->Enabled         = false;
		bt_sec_setting->Enabled         = false;
		rb_sec_setting_Write->Enabled   = false;
		lb_sec_setting_Write->Enabled   = false;
		ed_sec_setting_Write->Enabled   = false;
        cb_otp->Enabled = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cb_sec_roClick(TObject *Sender)
{
    if( cb_sec_ro->Checked ){
        g_ParamDownloadConfig.m_sec_ro_enable = (_BOOL) true;
        g_ParamReadbackConfig.m_sec_ro_enable = (_BOOL) true;

        gb_sec_ro->Enabled          = true;
		bt_sec_ro_setting->Enabled  = true;
		rb_sec_ro_Write->Enabled    = true;
		rb_sec_ro_Read->Enabled     = true;
		lb_sec_ro_Write->Enabled    = true;
		lb_sec_ro_Read->Enabled     = true;
		ed_sec_ro_Write->Enabled    = true;
		ed_sec_ro_Read->Enabled     = true;
    }
    else{
        g_ParamDownloadConfig.m_sec_ro_enable = (_BOOL) false;
        g_ParamReadbackConfig.m_sec_ro_enable = (_BOOL) false;

        gb_sec_ro->Enabled          = false;
		bt_sec_ro_setting->Enabled  = false;
		rb_sec_ro_Write->Enabled    = false;
		rb_sec_ro_Read->Enabled     = false;
		lb_sec_ro_Write->Enabled    = false;
		lb_sec_ro_Read->Enabled     = false;
		ed_sec_ro_Write->Enabled    = false;
		ed_sec_ro_Read->Enabled     = false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cb_custClick(TObject *Sender)
{
    if( cb_cust->Checked ){
        g_ParamDownloadConfig.m_cust_para_enable = (_BOOL) true;
        g_ParamReadbackConfig.m_cust_para_enable = (_BOOL) true;

        gb_cust->Enabled          = true;
		bt_cust_setting->Enabled  = true;
		rb_cust_Write->Enabled    = true;
		rb_cust_Read->Enabled     = true;
		lb_cust_Write->Enabled    = true;
		lb_cust_Read->Enabled     = true;
		ed_cust_Write->Enabled    = true;
		ed_cust_Read->Enabled     = true;
    }
    else{
        g_ParamDownloadConfig.m_cust_para_enable = (_BOOL) false;
        g_ParamReadbackConfig.m_cust_para_enable = (_BOOL) false;

        gb_cust->Enabled = false;
		bt_cust_setting->Enabled  = false;
		rb_cust_Write->Enabled    = false;
		rb_cust_Read->Enabled     = false;
		lb_cust_Write->Enabled    = false;
		lb_cust_Read->Enabled     = false;
		ed_cust_Write->Enabled    = false;
		ed_cust_Read->Enabled     = false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::bt_otp_settingClick(TObject *Sender)
{
    g_bParameterPage = true;

    if( rb_otp_Write->Checked ) {
        m_OTPSetting->Visible = true;

        if( g_ParamDownloadConfig.m_otp_op == OTP_WRITE ){
            m_OTPSetting->m_Write->Checked     = true;
            m_OTPSetting->m_WriteLock->Checked = false;
            m_OTPSetting->m_Lock->Checked      = false;
        }
        else if( g_ParamDownloadConfig.m_otp_op == OTP_WRITE_AND_LOCK ){
            m_OTPSetting->m_Write->Checked     = false;
            m_OTPSetting->m_WriteLock->Checked = true;
            m_OTPSetting->m_Lock->Checked      = false;
        }
        else if( g_ParamDownloadConfig.m_otp_op == OTP_LOCK ){
            m_OTPSetting->m_Write->Checked     = false;
            m_OTPSetting->m_WriteLock->Checked = false;
            m_OTPSetting->m_Lock->Checked      = true;
        }
        m_OTPSetting->m_otp_addr->Text = g_ParamDownloadConfig.m_otp.m_addr;
        m_OTPSetting->m_otp_len->Text  = g_ParamDownloadConfig.m_otp.m_len;
        m_OTPSetting->m_otp_file->Text = g_ParamDownloadConfig.m_otp_filepath;
    }
    else if( rb_otp_Read->Checked ) {
        g_ParameterType = PARAM_OTP;
        m_ParameterReadSetting->Visible = true;

        m_ParameterReadSetting->Label1->Visible = true;
        m_ParameterReadSetting->m_addr->Visible = true;

        m_ParameterReadSetting->m_addr->Text = g_ParamReadbackConfig.m_otp.m_addr;
        m_ParameterReadSetting->m_len->Text  = g_ParamReadbackConfig.m_otp.m_len;
        m_ParameterReadSetting->m_file->Text = g_ParamReadbackConfig.m_otp_filepath ;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::bt_sec_settingClick(TObject *Sender)
{
    g_bParameterPage = true;

    if( rb_sec_setting_Write->Checked ){
        m_SecuritySetting->Visible = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::bt_sec_ro_settingClick(TObject *Sender)
{
    g_bParameterPage = true;

    if( rb_sec_ro_Write->Checked ) {
        LoadSecRO();
    }
    else if( rb_sec_ro_Read->Checked ) {
        g_ParameterType = PARAM_SEC_RO;
        m_ParameterReadSetting->Visible = true;

        m_ParameterReadSetting->Label1->Visible = false;
        m_ParameterReadSetting->m_addr->Visible = false;

        m_ParameterReadSetting->m_len->Text  = g_ParamReadbackConfig.m_sec_ro.m_len;
        m_ParameterReadSetting->m_file->Text = g_ParamReadbackConfig.m_sec_ro_filepath ;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::bt_cust_settingClick(TObject *Sender)
{
    g_bParameterPage = true;

    if( rb_cust_Write->Checked ) {
        LoadCustPara();
    }
    else if( rb_cust_Read->Checked ) {
        g_ParameterType = PARAM_CUST;
        m_ParameterReadSetting->Visible = true;

        m_ParameterReadSetting->Label1->Visible = false;
        m_ParameterReadSetting->m_addr->Visible = false;

        m_ParameterReadSetting->m_len->Text  = g_ParamReadbackConfig.m_cust_para.m_len;
        m_ParameterReadSetting->m_file->Text = g_ParamReadbackConfig.m_cust_para_filepath ;
    }
}
//---------------------------------------------------------------------------
int TMainForm::SaveFile(const char *pathname, unsigned char *p_buf, unsigned int nFileLength) {

	FILE *fp;

	if( NULL == pathname || '\0' == pathname[0] || NULL == p_buf || 0 == nFileLength ) {
		return 1;
	}

	FileUtils::FileOpenSentry	file_sentry(pathname, "wb", fp);

	if( NULL == fp ) {
		return 2;
	}

	if( nFileLength > fwrite(p_buf, 1, nFileLength, fp) ) {
		return 3;
	}

	return 0;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::bb_ParameterButtonClick(TObject *Sender)
{
       if (IsDLListEmpty()) {
		ShowMessage("Please select scatter file before Readback.");
	        return;
	}

	/******Load configration XML files begin******/
	//Load usb_setting.xml table
	FlashToolUSBTable usb_table = GetFlashToolUSBTable();
	//Load storage_setting.xml table
	GetFlashToolStorageTable();
	/******Load configration XML files end******/

    g_flashtool_function = FLASHTOOL_PARAMETER;
 	//FIXME
#if 0
	g_backup_restore_state =  NOACTION;
#endif
	g_nvram_update_state    = NOACTIONNVRAM ;
	updateMenuItem();
    
	if ( !cb_sec_setting->Checked && !cb_otp->Checked) {
        ShowMessage("Please check one item of \"General Setting\" before update.");
        return;
    } 

    if ( asBin.IsEmpty() )
    {
        //if ( !FileOpenDownloadAgentExecute() )
        if( !FileOpenNandUtilBin(OpenDownloadAgentDialog, NORMAL_DA_BIN) )
        {
            ShowMessage(" You must open download agent file before downloading. ");
            return;
        }
    }

    if( g_bUsbDLDA &&
        g_project_mode == YuSu &&
        asNandUtilDAPath.IsEmpty())
    {
        if ( !FileOpenNandUtilBin(OpenNandUtilFileDialog, NAND_UTIL_DA_BIN) )
        {
            ShowMessage(" You must open Nand Util file before doing Parameter things. ");
            return;
        }
    }

    AnsiString ss = ed_sec_setting_Write->Text;
    if ( cb_sec_setting->Checked && ss.IsEmpty() )
    {
        ShowMessage("Please check lock image before update.");
        return;
    }

	if ( cb_otp->Checked && 
         ed_otp_Write->Text.IsEmpty() && 
		 ed_otp_Read->Text.IsEmpty()) {
		 ShowMessage("Please set up OTP Write/Read by clicking \"Setting\" before update.");
		 return;
	}

    // clean flash device info
    HWStatusBarClear();

    //if user select IMEI operation,then disable Restore operation
#if 0
    if( g_backup_restore_state !=  NOACTION )
    {
        g_backup_restore_state =  NOACTION;
    }
#endif
    if( g_nvram_update_state !=  NOACTIONNVRAM )
    {
        g_nvram_update_state  =  NOACTIONNVRAM;
    }

    // update DA to the latest version
    if( UpdateDA() ) return;

    start_DL(true);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::bb_StopButtonClick(TObject *Sender)
{
	g_stopflag = BOOT_STOP;
	META_CancelAllBlockingCall();
}
//---------------------------------------------------------------------------
static bool ParamRead_bPreviousCheckBoxValue;

void __fastcall TMainForm::m_ReadParamListViewChange( TObject *Sender, TListItem *Item, TItemChange Change)
{
	// ShowMessage("Changed");

    if( (ctState == Change) && (Item->Checked != ParamRead_bPreviousCheckBoxValue) )
    {
        Param_IndexOfChangedCheckBox = Item->Index;
        return;
    }

    Param_IndexOfChangedCheckBox = -1;

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::m_ReadParamListViewChanging(TObject *Sender,
      TListItem *Item, TItemChange Change, bool &AllowChange)
{
	ParamRead_bPreviousCheckBoxValue = Item->Checked;

    Param_IndexOfChangedCheckBox = -1;

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::m_ReadParamListViewClick(TObject *Sender)
{
	TListView *plv = dynamic_cast<TListView *>(Sender);

    if( NULL == g_pCurNode ) return;

	ParamReadbackConfig_T	&param=g_ReadbackPage_Param;

	if( 0 <= Param_IndexOfChangedCheckBox && Param_IndexOfChangedCheckBox<plv->Items->Count )
    {
		TListItem *pItem=plv->Items->Item[Param_IndexOfChangedCheckBox];
		ListViewItemType_E	type=*((ListViewItemType_E *)pItem->Data);

		switch ( type )
        {
		    case LV_OTP:
			    param.m_otp_enable       = pItem->Checked?_TRUE:_FALSE;
			    break;

		    case LV_SEC_RO:
			    param.m_sec_ro_enable    = pItem->Checked?_TRUE:_FALSE;
			    break;

		    case LV_CUST_PARA:
			    param.m_cust_para_enable = pItem->Checked?_TRUE:_FALSE;
			    break;

		    default:
			    break;
		}
	}
	else if( NULL != plv->Selected )
    {
		TListItem *pItem=plv->Selected;
		ListViewItemType_E	type=*((ListViewItemType_E *)pItem->Data);

		switch( type )
        {
		    case LV_OTP:
                g_ParameterType  = PARAM_OTP;
                g_bParameterPage = false;
                m_ParameterReadSetting->Visible = true;
                m_ParameterReadSetting->Label1->Visible = true;
                m_ParameterReadSetting->m_addr->Visible = true;
                m_ParameterReadSetting->m_addr->Text = param.m_otp.m_addr;
                m_ParameterReadSetting->m_len->Text  = param.m_otp.m_len;
                m_ParameterReadSetting->m_file->Text = param.m_otp_filepath ;
			    break;

		    case LV_SEC_RO:
                g_ParameterType  = PARAM_SEC_RO;
                g_bParameterPage = false;
                m_ParameterReadSetting->Visible = true;
                m_ParameterReadSetting->Label1->Visible = false;
                m_ParameterReadSetting->m_addr->Visible = false;
                m_ParameterReadSetting->m_len->Text  = param.m_sec_ro.m_len;
                m_ParameterReadSetting->m_file->Text = param.m_sec_ro_filepath ;
			    break;

		    case LV_CUST_PARA:
                g_ParameterType  = PARAM_CUST;
                g_bParameterPage = false;
                m_ParameterReadSetting->Visible = true;
                m_ParameterReadSetting->Label1->Visible = false;
                m_ParameterReadSetting->m_addr->Visible = false;
                m_ParameterReadSetting->m_len->Text  = param.m_cust_para.m_len;
                m_ParameterReadSetting->m_file->Text = param.m_cust_para_filepath ;
			    break;

		    default:
			    break;
		}
	}

    Param_IndexOfChangedCheckBox = -1;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::m_ReadParamListViewDblClick(TObject *Sender)
{
	m_ReadParamListViewClick( Sender );
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::m_FS_StartButtonClick(TObject *Sender)
{

	g_flashtool_function = FLASHTOOL_API;

    if( ed_ExceptionLog->Text.Length() == 0 )
    {
        ShowMessage( "You must input your File Name of Exception Log !!" );
        return;
    }

    if( ed_SaveExceptionLog->Text.Length() == 0 )
    {
        ShowMessage( "You must input your Saving Path of Exception Log !!" );
        return;
    }

	if ( asBin.IsEmpty() )
    {
		//if ( !FileOpenDownloadAgentExecute() )
        if ( !FileOpenNandUtilBin(OpenDownloadAgentDialog, NORMAL_DA_BIN) )
		{
			ShowMessage( "You must open download agent file before downloading." );
			return;
		}
	}

	// clean Flash device info
	HWStatusBarClear();

	if( UpdateDA() ) return;

    start_DL( true );

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::m_FS_StopButtonClick(TObject *Sender)
{
	g_stopflag = BOOT_STOP;
	META_CancelAllBlockingCall();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::bt_SaveExceptionLogClick(TObject *Sender)
{
	AnsiString	s;

	m_SelectFileDialog->Title = "Save Exception Log file as...";
//	m_SelectFileDialog->InitialDir = MainForm->ROMBaseDir;

    if( m_SelectFileDialog->Execute() )
    {
        ed_SaveExceptionLog->Text = m_SelectFileDialog->FileName.c_str();
	}
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::BBCHIP_MT6573_E2Click(TObject *Sender)
{
	g_SP_BBCHIP_TYPE = MT6573_E2;
    g_bUsbMode = true;
    
	updateStatusBar();
	updateMenuItem();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::BBCHIP_MT6573_E1Click(TObject *Sender)
{
    g_SP_BBCHIP_TYPE = MT6573_E1;
    g_bUsbMode = false;

    updateStatusBar();
    updateMenuItem();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BBCHIP_UNKNOWNClick(TObject *Sender)
{
	g_SP_BBCHIP_TYPE = SP_UNKNOWN_BBCHIP_TYPE;
    g_bUsbMode = false;

	updateStatusBar();
	updateMenuItem();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::BBCHIP_MT6217Click(TObject *Sender)
{
	g_BBCHIP_TYPE = MT6217;

	updateStatusBar();
	updateMenuItem();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::BBCHIP_MT6228Click(TObject *Sender)
{
	g_BBCHIP_TYPE = MT6228;

	updateStatusBar();
	updateMenuItem();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::BBCHIP_MT6227Click(TObject *Sender)
{
	g_BBCHIP_TYPE = MT6227;

	updateStatusBar();
	updateMenuItem();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BBCHIP_MT6229Click(TObject *Sender)
{
	g_BBCHIP_TYPE = MT6229;

	updateStatusBar();
	updateMenuItem();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BBCHIP_MT6226Click(TObject *Sender)
{
	g_BBCHIP_TYPE = MT6226;

	updateStatusBar();
	updateMenuItem();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::BBCHIP_MT6226MClick(TObject *Sender)
{
	g_BBCHIP_TYPE = MT6226;

	updateStatusBar();
	updateMenuItem();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::BBCHIP_MT6230Click(TObject *Sender)
{
	g_BBCHIP_TYPE = MT6230;

	updateStatusBar();
	updateMenuItem();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BBCHIP_MT6225Click(TObject *Sender)
{
	g_BBCHIP_TYPE = MT6225;

	updateStatusBar();
	updateMenuItem();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BBCHIP_MT6223Click(TObject *Sender)
{
	g_BBCHIP_TYPE = MT6223;

	updateStatusBar();
	updateMenuItem();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BBCHIP_MT6227DClick(TObject *Sender)
{
	g_BBCHIP_TYPE = MT6227D;

	updateStatusBar();
	updateMenuItem();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BBCHIP_MT6226DClick(TObject *Sender)
{
	g_BBCHIP_TYPE = MT6226D;

	updateStatusBar();
	updateMenuItem();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BBCHIP_MT6223PClick(TObject *Sender)
{
	g_BBCHIP_TYPE = MT6223P;

	updateStatusBar();
	updateMenuItem();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BBCHIP_MT6235Click(TObject *Sender)
{
	g_BBCHIP_TYPE = MT6235;

	updateStatusBar();
	updateMenuItem();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BBCHIP_MT6238Click(TObject *Sender)
{
  	g_BBCHIP_TYPE = MT6238;

	updateStatusBar();
	updateMenuItem();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::BBCHIP_MT6239Click(TObject *Sender)
{
    g_BBCHIP_TYPE = MT6239;

	updateStatusBar();
	updateMenuItem();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::BBCHIP_MT6268AClick(TObject *Sender)
{
  	g_BBCHIP_TYPE = MT6268A;

	updateStatusBar();
	updateMenuItem();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::BBCHIP_MT6251TClick(TObject *Sender)
{
    g_BBCHIP_TYPE = MT6251T;

	updateStatusBar();
	updateMenuItem();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::BBCHIP_MT6253TClick(TObject *Sender)
{
    g_BBCHIP_TYPE = MT6253T;

	updateStatusBar();
	updateMenuItem();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::BBCHIP_MT6268BClick(TObject *Sender)
{
    g_BBCHIP_TYPE = MT6268B;

	updateStatusBar();
	updateMenuItem();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::bt_SaveExtractNFBClick(TObject *Sender)
{
	AnsiString	s;

	m_SelectFileDialog->Title = "Save NFB intermediate file as...";
//	m_SelectFileDialog->InitialDir = MainForm->ROMBaseDir;

    if( m_SelectFileDialog->Execute() )
    {
        ed_SaveExtractNFB->Text = m_SelectFileDialog->FileName.c_str();
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::m_RW_StartButtonClick(TObject *Sender)
{

	g_flashtool_function = FLASHTOOL_ROMWRITER;

    if( ed_SaveExtractNFB->Text.Length() == 0 )
    {
        ShowMessage(" You must input your Saving Path of NFB intermediate file !!");
        return;
    }

	if ( asBin.IsEmpty() )
    {
		//if ( !FileOpenDownloadAgentExecute() )
        if ( !FileOpenNandUtilBin(OpenDownloadAgentDialog, NORMAL_DA_BIN) )
		{
			ShowMessage(" You must open download agent file before downloading. ");
			return;
		}
	}

	// clean Flash device info
	HWStatusBarClear();

	if( UpdateDA() ) return;

    start_DL(true);

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::m_RW_StopButtonClick(TObject *Sender)
{
	g_stopflag = BOOT_STOP;
	META_CancelAllBlockingCall();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::m_Menu_Window_CheckParameterPageClick( TObject *Sender)
{
    if( m_Menu_Window_CheckParameterPage->Checked ) {
        m_Menu_Window_CheckParameterPage->Checked = false;
        ts_Paremeter->TabVisible = false;
        g_flashtool_function = FLASHTOOL_PARAMETER;
		//FIXME
		//g_backup_restore_state =  NOACTION;
		g_nvram_update_state    = NOACTIONNVRAM ;
		updateMenuItem();
    }
    else{
        m_Menu_Window_CheckParameterPage->Checked = true;
        ts_Paremeter->TabVisible = true;
        g_flashtool_function    = FLASHTOOL_DOWNLOAD;
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::m_Menu_Window_CheckFileManagementClick( TObject *Sender)
{
     if( m_Menu_Window_CheckFileManagement->Checked ) {
        m_Menu_Window_CheckFileManagement->Checked = false;
        ts_FileManagement->TabVisible = false;
     }
     else{
        m_Menu_Window_CheckFileManagement->Checked = true;
        ts_FileManagement->TabVisible = true;
     }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::m_Menu_Window_CheckROMWriterClick( TObject *Sender)
{
    if( m_Menu_Window_CheckROMWriter->Checked ) {
        m_Menu_Window_CheckROMWriter->Checked = false;
        ts_RomWriter->TabVisible = false;
    }
    else{
        m_Menu_Window_CheckROMWriter->Checked = true;
        ts_RomWriter->TabVisible = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::bt_MT_SelectAllClick(TObject *Sender)
{
    // enable all RAM testing method
    RAMCheckBox->Checked = true;
    cb_MT_RAM_Data_Bus_Test->Checked = true;
    cb_MT_RAM_Addr_Bus_Test->Checked = true;
    cb_MT_RAM_Pattern_Test->Checked  = true;
    cb_MT_RAM_Inc_Dec_Test->Checked  = true;
#if 0
    // enable all NOR flash testing method
    NORCheckBox->Checked = true;
    cb_MT_NOR_Addr_Bus_Test->Checked = true;
    cb_MT_NOR_Pattern_Test->Checked  = true;
#endif

    // enable all NAND flash testing method
    NANDCheckBox->Checked = true;
    cb_MT_NAND_Pattern_Test->Checked = true;

    // enable all EMMC testing method
    EMMCCheckBox->Checked = true;
    cb_MT_EMMC_Pattern_Test->Checked  = true;

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::m_MT_StartButtonClick(TObject *Sender)
{
	
	if (IsDLListEmpty()) {
		ShowMessage("Please select scatter file before Memory Test.");
	    return;
	}

	g_flashtool_function = FLASHTOOL_MEMORYTEST;
	//FIXME
	//g_backup_restore_state =  NOACTION;
	g_nvram_update_state    = NOACTIONNVRAM ;
	updateMenuItem();

    if( NULL == g_pCurNode ) return;

    // load DA
   	if ( asBin.IsEmpty() )
    {
		//if ( !FileOpenDownloadAgentExecute() )
        if ( !FileOpenNandUtilBin(OpenDownloadAgentDialog, NORMAL_DA_BIN) )
		{
			ShowMessage( " Open the download agent file " );
			return;
		}
	}

    // parse scatter file and load images
	if ( !g_bDebugDA && g_pCurNode->m_scat_file.IsEmpty() )
    {
		if ( !FileOpenLinkMapExecute(g_pCurNode) )
		{
			ShowMessage( " Open the scatter file accroding to your project " );
			return;
		}
	}


	// clean Flash device info
	HWStatusBarClear();

    	// update DA to the leatest version
	if( UpdateDA() ) return;

    start_DL( true );
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::m_MT_StopButtonClick(TObject *Sender)
{
	g_stopflag = BOOT_STOP;
	META_CancelAllBlockingCall();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::mi_USBDownloadDAClick(TObject *Sender)
{    
    if( mi_USBDownloadDA->Checked == false ){
        g_bUsbMode = true;
    } else {
        g_bUsbMode = false;
    }

	if(!g_bUsbMode) {
		if (m_COMPortCount > 0) {
			for( unsigned short i=0; i<m_COMPortCount; i++ )  {
				DCOMPort->Items[i]->Checked = false;
			}

			DCOMPort->Items[0]->Checked = true;
			COM_PORT = m_COMPortList[0];
		} else {
			COM_PORT = 1;
			LOGE("No COM port is found, set COM_PORT to default COM1");
		}
	}

    LOGD("g_bUsbMode(%s).", g_bUsbMode ? "true" : "false");  
    updateMenuItem();
    UpdateCaption();
    updateStatusBar();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::cb_gpsClick(TObject *Sender)
{
    if( cb_gps->Checked )
    {
        g_ParamDownloadConfig.m_gps_enable = (_BOOL) true;
        g_ParamReadbackConfig.m_gps_enable = (_BOOL) true;

        	gb_gps->Enabled = true;
		bt_gps_setting->Enabled = true;
		rb_gps_Write->Enabled   = true;
		rb_gps_Read->Enabled    = true;
		lb_gps_Write->Enabled   = true;
		lb_gps_Read->Enabled    = true;
		ed_gps_Write->Enabled   = true;
		ed_gps_Read->Enabled    = true;
    }
    else{
        g_ParamDownloadConfig.m_gps_enable = (_BOOL) false;
        g_ParamReadbackConfig.m_gps_enable = (_BOOL) false;

        gb_gps->Enabled = false;
		bt_gps_setting->Enabled = false;
		rb_gps_Write->Enabled   = false;
		rb_gps_Read->Enabled    = false;
		lb_gps_Write->Enabled   = false;
		lb_gps_Read->Enabled    = false;
		ed_gps_Write->Enabled   = false;
		ed_gps_Read->Enabled    = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::bt_gps_settingClick(TObject *Sender)
{
    g_bParameterPage = true;

    if( rb_gps_Write->Checked ) {
        LoadGPS();
    }
    else if( rb_gps_Read->Checked )
    {
        g_ParameterType = PARAM_GPS;
        m_ParameterReadSetting->Visible = true;

        m_ParameterReadSetting->Label1->Visible = false;
        m_ParameterReadSetting->m_addr->Visible = false;

        m_ParameterReadSetting->m_len->Text  = g_ParamReadbackConfig.m_gps_rom_filesize;
        m_ParameterReadSetting->m_file->Text = g_ParamReadbackConfig.m_gps_rom_filepath;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DownloadStyleClick(TObject *Sender)
{
	if(g_bDownloadStyleSequential) {
        g_bDownloadStyleSequential = false;
	}
    else {
        g_bDownloadStyleSequential = true;
	}

	updateMenuItem();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::RAMCheckBoxClick(TObject *Sender)
{
    if ( RAMCheckBox->Checked == true ) {
        cb_MT_RAM_Data_Bus_Test->Enabled = true;
        cb_MT_RAM_Addr_Bus_Test->Enabled = true;
        cb_MT_RAM_Pattern_Test->Enabled = true;
        cb_MT_RAM_Inc_Dec_Test->Enabled = true;
   } else {
        cb_MT_RAM_Data_Bus_Test->Enabled = false;
        cb_MT_RAM_Addr_Bus_Test->Enabled = false;
        cb_MT_RAM_Pattern_Test->Enabled = false;
        cb_MT_RAM_Inc_Dec_Test->Enabled = false;
    }    
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::EMMCCheckBoxClick(TObject *Sender)
{
    if ( EMMCCheckBox->Checked == true ) {
        cb_MT_EMMC_Pattern_Test->Enabled = true;
    } else {
        cb_MT_EMMC_Pattern_Test->Enabled = false;
    }    
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::NANDCheckBoxClick(TObject *Sender)
{
    if ( NANDCheckBox->Checked == true) {
        cb_MT_NAND_Pattern_Test->Enabled = true;
    } else {
        cb_MT_NAND_Pattern_Test->Enabled = false;
    }    
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cb_MT_RAM_Data_Bus_TestClick(TObject *Sender)
{
    if ( (cb_MT_RAM_Data_Bus_Test->Checked == false) &&
         (cb_MT_RAM_Addr_Bus_Test->Checked == false) &&
         (cb_MT_RAM_Pattern_Test->Checked  == false) &&
         (cb_MT_RAM_Inc_Dec_Test->Checked  == false) )
    {
        RAMCheckBox->Checked = false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cb_MT_RAM_Addr_Bus_TestClick(TObject *Sender)
{
    if ( (cb_MT_RAM_Data_Bus_Test->Checked == false) &&
         (cb_MT_RAM_Addr_Bus_Test->Checked == false) &&
         (cb_MT_RAM_Pattern_Test->Checked  == false) &&
         (cb_MT_RAM_Inc_Dec_Test->Checked  == false) )
    {
        RAMCheckBox->Checked = false;
    }    
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cb_MT_RAM_Pattern_TestClick(TObject *Sender)
{
    if ( (cb_MT_RAM_Data_Bus_Test->Checked == false) &&
         (cb_MT_RAM_Addr_Bus_Test->Checked == false) &&
         (cb_MT_RAM_Pattern_Test->Checked  == false) &&
         (cb_MT_RAM_Inc_Dec_Test->Checked  == false) )
    {
        RAMCheckBox->Checked = false;
    }    
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cb_MT_RAM_Inc_Dec_TestClick(TObject *Sender)
{
    if ( (cb_MT_RAM_Data_Bus_Test->Checked == false) &&
         (cb_MT_RAM_Addr_Bus_Test->Checked == false) &&
         (cb_MT_RAM_Pattern_Test->Checked  == false) &&
         (cb_MT_RAM_Inc_Dec_Test->Checked  == false) )
    {
        RAMCheckBox->Checked = false;
    }    
}
//---------------------------------------------------------------------------
#if 0
void __fastcall TMainForm::cb_MT_NOR_Addr_Bus_TestClick(TObject *Sender)
{
    if ( (cb_MT_NOR_Addr_Bus_Test->Checked == false) &&
         (cb_MT_NOR_Pattern_Test->Checked  == false) )
    {
        NORCheckBox->Checked = false;
    }
}
#endif
//---------------------------------------------------------------------------

void __fastcall TMainForm::cb_MT_EMMC_Pattern_TestClick(TObject *Sender)
{
    if ( cb_MT_EMMC_Pattern_Test->Checked  == false )
    {
        EMMCCheckBox->Checked = false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cb_MT_NAND_Pattern_TestClick(TObject *Sender)
{
    if ( (cb_MT_NAND_Pattern_Test->Checked == false) )
    {
        NANDCheckBox->Checked = false;
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::lv_ReadBackKeyPress(TObject *Sender, char &Key)
{
    if ( Key =='\b')
    {
        tb_DeleteReadBackFileClick(Sender);
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::lv_ReadBackKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if ( Key == 46 || Key == 109 )
    {
        tb_DeleteReadBackFileClick(Sender);
    }
    else if ( Key == 107 || Key == 13 )
    {
        tb_AddReadBackFileClick( Sender);
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::NoActionClick(TObject *Sender)
{
    ResetBackupRestoreItem();
    updateMenuItem();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::BackupRestoreClick(TObject *Sender)
{
	assert(0 && "Not support");
    if ( BackupRestore->Checked == false )
    {
        NoAction->Checked      = false;
        BackupRestore->Checked = true;
        Restore->Checked       = false;
        RestoreOnly->Checked   = false;
#if 0
        g_backup_restore_state = BACKUPRESTORE;
#endif
        // reset upload item to avoid operation conflict with  backup and restore
        ResetUploadItem();

    } else {
        ResetBackupRestoreItem();
    }
    updateMenuItem();

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::RestoreClick(TObject *Sender)
{
	assert(0 && "Not support");
    if ( Restore->Checked == false )
    {
        NoAction->Checked       = false;
        BackupRestore->Checked  = false;
        Restore->Checked        = true;
        RestoreOnly->Checked    = false;
#if 0
        g_backup_restore_state  = BACKUP_FORMAT_DOWNLOAD_RESTORE;
#endif
        // reset upload item to avoid operation conflict with  backup and restore
        ResetUploadItem();

    } else {
        ResetBackupRestoreItem();
    }
    updateMenuItem();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::RestoreOnlyClick(TObject *Sender)
{
    assert(0 && "Not support");
    if ( RestoreOnly->Checked == false )
    {
        NoAction->Checked      = false;
        BackupRestore->Checked = false;
        Restore->Checked       = false;
        RestoreOnly->Checked   = true;
#if 0
        g_backup_restore_state = RESTOREONLY;
#endif
        // reset upload item to avoid operation conflict with  backup and restore
        ResetUploadItem();

    } else {
        ResetBackupRestoreItem();
    }
    updateMenuItem();
}

//---------------------------------------------------------------------------
void TMainForm::ResetBackupRestoreItem( void )
{
	assert(0 && "Not support");
    NoAction->Checked      = true;
    BackupRestore->Checked = false;
    Restore->Checked       = false;
    RestoreOnly->Checked   = false;
#if 0
    g_backup_restore_state =  NOACTION;
#endif
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::NoUploadClick(TObject *Sender)
{
    ResetUploadItem();
    updateMenuItem();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::UploadClick(TObject *Sender)
{
    assert(0);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::UploadOnlyClick(TObject *Sender)
{
    assert(0);
}

//---------------------------------------------------------------------------
void TMainForm::ResetUploadItem( void )
{
    assert(0);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DAStartAddressClick(TObject *Sender)
{
    Form_DA_Option->Visible = true;
}
//---------------------------------------------------------------------------

/*bool DownloadSet::operator==(const DownloadSet &r_value)
{
    if( 0==m_Scatter.AnsiCompareIC(r_value.m_Scatter) &&
        0==m_BootLoader.AnsiCompareIC(r_value.m_BootLoader) &&
        0==m_BootLoader_Ext.AnsiCompareIC(r_value.m_BootLoader_Ext) &&
        m_BinFiles.size()==r_value.m_BinFiles.size()
    ) {
        unsigned int i;
        for(i=0; i < m_BinFiles.size(); i++) {
            if( 0 != m_BinFiles[i].m_Filepath.AnsiCompareIC(r_value.m_BinFiles[i].m_Filepath) ) {
                return false;
            }
        }
        return true;
    }
    return false;
}  */

//---------------------------------------------------------------------------
button_sentry::button_sentry()
{
        //disable DLCert button
        MainForm->DisableDLCertButton();
        // disable download button
        MainForm->DisableDownloadButton();
        // disable readback button
        MainForm->DisableReadbackButton();
        // disable format button
        MainForm->DisableFormatButton();
	  MainForm->DisableSCICloneButton();
	  MainForm->DisableSCIDownloadButton();
        // disable format -> download button
        MainForm->DisableFirmwareUpgradeButton();
        // disable operation method
        // MainForm->m_Menu_OperationMethod->Enabled = false;
        // enable stop button
        MainForm->EnableStopButton();
#if 0
        // disable project combox
        MainForm->cbxProject->Enabled = false;
#endif
        // disable Options menu
        MainForm->BaudRate1->Enabled = false;
        MainForm->DCOMPort->Enabled = false;
       //  MainForm->m_Menu_OperationMethod->Enabled = false;
        MainForm->m_BBChipOption->Enabled = false;
        MainForm->m_Menu_IMEI_update->Enabled = false;
        MainForm->m_Menu_Backup_Restore_NVRAM->Enabled = false;
        MainForm->mi_USBDownloadDA->Enabled = false;

        if(ToolInfo::IsCustomerVer()){
        MainForm->m_Menu_FourInOne->Visible = false;
        }else{
        MainForm->m_Menu_FourInOne->Enabled = false;
        }

        //DA DL All menu
        MainForm->m_Menu_DA_DL_all->Enabled = false;

        //disable some button on main frame
       MainForm->bb_OpenDownloadAgent->Enabled = false;
	 MainForm->bb_ScatterLoading->Enabled = false;
       MainForm->bb_OpenAuthFile->Enabled = false;
	MainForm->bb_OpenSCertFile->Enabled = false;
       MainForm->bb_OpenNandUtil->Enabled = false;
#if 0
        MainForm->bb_FlashBin->Enabled = false;
#endif
        //Disable File menu
        MainForm->Open1->Enabled = false;
        MainForm->Openlinkmapfile1->Enabled = false;
        MainForm->m_DL_History_0->Enabled = false;
		//Disable Window menu
		MainForm->m_Menu_Window_CheckParameterPage->Enabled = false;
		MainForm->m_Menu_WriteMemory_CheckParameterPage->Enabled = false;

        //disable image ListView1
        MainForm->ListView1->Enabled = false;

        MainForm->bb_ParameterButton->Enabled = false;
        MainForm->bb_StopButton->Enabled      = true;

        MainForm->m_FS_StartButton->Enabled   = false;
        MainForm->m_FS_StopButton->Enabled    = true;

        MainForm->m_RW_StartButton->Enabled   = false;
        MainForm->m_RW_StopButton->Enabled    = true;

        MainForm->m_MT_StartButton->Enabled   = false;
        MainForm->m_MT_StopButton->Enabled    = true;

        MainForm->m_ParamListView->Enabled    = false;
        MainForm->m_Transmission_Option->Enabled = false;
        MainForm->m_DA_Option->Enabled = false;
		//Disable Write Memory Button
		MainForm->tb_WriteMemory->Enabled    = false;
		MainForm->tb_WriteMemory_Stop->Enabled    = true;
		MainForm->tb_OpenRawData->Enabled = false;

        MainForm->m_Menu_Physical_Fmt_RB->Enabled = false;

        if( MainForm->mi_MultiLoad->Checked )
        {
            MainForm->AddaLoad1->Enabled      = false;
            MainForm->DeleteaLoad1->Enabled   = false;
	    }

		//2011.08.10 add for DA DL All checksum, 
		MainForm->cb_da_dl_checksum_->Enabled = false;

        //disable to switch tab when tboot1 work thread is executed
         MainForm->ts_SCIDownload->TabVisible = (MainForm->ts_SCIDownload == MainForm->pc_mainframe->ActivePage);
        MainForm->ts_SCIClone->TabVisible = (MainForm->ts_SCIClone == MainForm->pc_mainframe->ActivePage);
        MainForm->ts_Download->TabVisible = (MainForm->ts_Download == MainForm->pc_mainframe->ActivePage);
        MainForm->ts_Readback->TabVisible = (MainForm->ts_Readback == MainForm->pc_mainframe->ActivePage);
        MainForm->ts_MemoryTest->TabVisible = (MainForm->ts_MemoryTest == MainForm->pc_mainframe->ActivePage);
        MainForm->ts_Paremeter->TabVisible = (MainForm->ts_Paremeter == MainForm->pc_mainframe->ActivePage);
        MainForm->ts_WriteMemory->TabVisible = (MainForm->ts_WriteMemory == MainForm->pc_mainframe->ActivePage);   
        MainForm->isTbootWorking = true;
}

//---------------------------------------------------------------------------
button_sentry::~button_sentry()
{
        //enable DLCert button
        MainForm->EnableDLCertButton();
        // enable download button
        MainForm->EnableDownloadButton();
        // enable readback button
        MainForm->EnableReadbackButton();
        // enable format button
        MainForm->EnableFormatButton();
	 MainForm->EnableSCICloneButton();
	 MainForm->EnableSCIDownloadButton();
        // enable format -> download button
        MainForm->EnableFirmwareUpgradeButton();
        // enable operation method
	    //		MainForm->m_Menu_OperationMethod->Enabled = true;
        // disable stop button
        MainForm->DisableStopButton();
#if 0
        // enable project combox
        MainForm->cbxProject->Enabled = true;
#endif
        // enable Options menu
        MainForm->BaudRate1->Enabled = true;
        MainForm->DCOMPort->Enabled = true;

        MainForm->m_BBChipOption->Enabled = true;
        MainForm->m_Menu_IMEI_update->Enabled = true;
        MainForm->m_Menu_Backup_Restore_NVRAM->Enabled = true;
        MainForm->mi_USBDownloadDA->Enabled = true;

        if(ToolInfo::IsCustomerVer()){
        MainForm->m_Menu_FourInOne->Visible = false;
        }else{
        MainForm->m_Menu_FourInOne->Enabled = false;
        }

        //enable some button on main frame
        MainForm->bb_OpenDownloadAgent->Enabled = true;
        MainForm->bb_ScatterLoading->Enabled = true;
        MainForm->bb_OpenAuthFile->Enabled = true;
		MainForm->bb_OpenSCertFile->Enabled = true;
        MainForm->bb_OpenNandUtil->Enabled = true;
#if 0
        MainForm->bb_FlashBin->Enabled = true;
#endif
        MainForm->bb_OpenNandUtil->Enabled = true;

        //enable File menu
        MainForm->Open1->Enabled = true;
        MainForm->Openlinkmapfile1->Enabled = true;
        MainForm->m_DL_History_0->Enabled = true;
		//enable Window menu
		MainForm->m_Menu_Window_CheckParameterPage->Enabled = true;
		MainForm->m_Menu_WriteMemory_CheckParameterPage->Enabled = true;

        //DA DL All menu
        //MainForm->m_Menu_DA_DL_all->Enabled = g_platform_info.isDADownloadAllEnabled();

        //enable image ListView1
        MainForm->ListView1->Enabled = true;

        MainForm->bb_ParameterButton->Enabled = true;
        MainForm->bb_StopButton->Enabled      = false;

        MainForm->m_FS_StartButton->Enabled   = true;
        MainForm->m_FS_StopButton->Enabled    = false;

        MainForm->m_RW_StartButton->Enabled   = true;
        MainForm->m_RW_StopButton->Enabled    = false;

        MainForm->m_MT_StartButton->Enabled   = true;
        MainForm->m_MT_StopButton->Enabled    = false;

        MainForm->m_ParamListView->Enabled    = true;
        MainForm->m_Transmission_Option->Enabled = true;
        MainForm->m_DA_Option->Enabled = true;

		//Enable Write Memory Button
		MainForm->tb_WriteMemory->Enabled    = true;
		MainForm->tb_WriteMemory_Stop->Enabled    = false;
		MainForm->tb_OpenRawData->Enabled = true;

        MainForm->m_Menu_Physical_Fmt_RB->Enabled = true;

        //enable to switch tab when tboot1 work thread is executed
        if(g_SCI_Mode)
      	  {
      	      MainForm->ts_SCIClone->TabVisible = true;
	      MainForm->ts_SCIDownload->TabVisible = true;
	  }
        MainForm->ts_Download->TabVisible = true;
        MainForm->ts_Readback->TabVisible = true;
        MainForm->ts_MemoryTest->TabVisible = true;
        MainForm->ts_Paremeter->TabVisible = MainForm->m_Menu_Window_CheckParameterPage->Checked;
        MainForm->ts_WriteMemory->TabVisible = MainForm->m_Menu_WriteMemory_CheckParameterPage->Checked;
        MainForm->mi_USBDownloadDA->Enabled = true;
        if( MainForm->mi_MultiLoad->Checked )
        {
            for( int index = 0; index < g_rootLoad->Count; index++ )
            {
                if( ( g_rootLoad->Item[index]->ImageIndex    == 2 ) ||
                            ( g_rootLoad->Item[index]->SelectedIndex == 2) )
                {
                    g_rootLoad->Item[index]->ImageIndex    = 1;
                    g_rootLoad->Item[index]->SelectedIndex = 1;
                }
            }

            MainForm->AddaLoad1->Enabled    = true;
            MainForm->DeleteaLoad1->Enabled = true;
        }

		//2011.08.10 add for DA DL All checksum, 
		//whether is enabled is decided by updateMenuItem g_bDADownloadAll
		MainForm->cb_da_dl_checksum_->Enabled = true;

		MainForm->updateUIForPlatform();
		
        MainForm->updateMenuItem();
        MainForm->isTbootWorking = false;
}
#if 0
//---------------------------------------------------------------------------
void __fastcall TMainForm::tb_DLFlashBinButtonClick(TObject *Sender)
{
    if(ed_SPBIN_File->Text.IsEmpty())
    {
         ShowMessage(" You must open Flash.Bin before downloading. ");
         return;
    }
    else
    {
        asFlashBinFile=ed_SPBIN_File->Text;
    }

    // clean Flash device info
    HWStatusBarClear();

    // update Status Bar
    updateStatusBar();

    g_flashtool_function=FLASHTOOL_FLASHBIN;
    start_DL(true);
}
#endif
#if 0
//---------------------------------------------------------------------------
void __fastcall TMainForm::bb_FlashBinClick(TObject *Sender)
{
    static AnsiString asSPBIN_Path;
    int iLastDel;
    int ret;

    asSPBIN_Path = ROMBaseDir;
    if ( 0 < asSPBIN_Path.Length() )
    {
        OpenSPBINFile->InitialDir = asSPBIN_Path;
    }
    else if ( 0 < ed_SPBIN_File->Text.Length() )
    {
        iLastDel = ed_SPBIN_File->Text.LastDelimiter("\\:");
        if ( 0 < iLastDel ) {
           OpenSPBINFile->InitialDir = ed_SPBIN_File->Text.SubString(1, iLastDel-1 );
        }
    }

    if ( OpenSPBINFile->Execute() )
    {
      ed_SPBIN_File->Text = OpenSPBINFile->FileName;
      asFlashBinFile = OpenSPBINFile->FileName;
      iLastDel = ed_SPBIN_File->Text.LastDelimiter("\\:");

      if( 0 < iLastDel ){
          asSPBIN_Path = ed_SPBIN_File->Text.SubString(1, iLastDel-1 );
          ROMBaseDir = asSPBIN_Path;
      }
    }
}
#endif
//---------------------------------------------------------------------------
void __fastcall TMainForm::mi_IMEIupdateClick(TObject *Sender)
{
//    Form_IMEI_setting->Visible = true;
}
//---------------------------------------------------------------------------
#if 0
void __fastcall TMainForm::m_Menu_Backup_Restore_NVRAMClick(TObject *Sender)
{
/*
    if ( m_Menu_Restore_NVRAM->Checked == false )
    {
        Form_Restore_NVRAM->Visible = true;
    }
    else
    {
        m_Menu_Restore_NVRAM->Checked = false;
        g_backup_restore_state = NOACTION;
    }
    */
}
#endif
//---------------------------------------------------------------------------
#if 0
void __fastcall TMainForm::m_subMenu_Backup_Format_DL_Restore_NVRAMClick(TObject *Sender)
{
    g_backup_restore_state = BACKUP_FORMAT_DOWNLOAD_RESTORE;
    g_nvram_update_state = NOACTIONNVRAM;
    updateMenuItem();
    updateStatusBar();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::m_subMenu_Backup_Restore_NoActionClick(TObject *Sender)
{
    g_backup_restore_state =  NOACTION;
    updateMenuItem();
	updateStatusBar();
}
//---------------------------------------------------------------------------
#endif

void __fastcall TMainForm::m_subMenu_IMEI_NoActionClick(TObject *Sender)
{
    assert(0);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::m_subMenu_IMEI_UpdateClick(TObject *Sender)
{
    Form_IMEI_setting->Visible = true;    
}
//---------------------------------------------------------------------------
#if 0
void __fastcall TMainForm::cbxProjectChange(TObject *Sender)
{
//     DL_Destroy(&g_pCurNode->m_dl_handle);
//     DL_Create(&g_pCurNode->m_dl_handle);

     DL_Destroy(&g_DL_HANDLE_NODE.m_dl_handle);
     DL_Create(&g_DL_HANDLE_NODE.m_dl_handle);
     
     int i = (int) cbxProject->ItemIndex;
     switch (i)
            {
                case DUMA:
                    {
                       g_project_mode=DUMA;

                         // update flash.bin path
                       ed_SPBIN_File->Text = "" ;
                       ed_AUTH_File->Text = "" ;
                        // Open the FlashTool.ini and parse the ini file
                       ReadDUMAINI();
                       DL_HANDLE_T &dl_handle = g_pCurNode->m_dl_handle;
                        // Compare the project ID
                       DL_ResourceProjectIdComparisonSetting( dl_handle, g_CompareResProjectId?_TRUE:_FALSE );

	               RedrawReadbackList();
                       RedrawDownloadList( g_pCurNode, false );

                       // show Parameter List View
                       //   now disable parameter list
                       /*
                       DL_INFO dl_info;
                       if( !DL_GetInfo( dl_handle, &dl_info ) )
                       {
                          if( dl_info.m_config.m_security_supported || g_pCurNode->m_param.m_gps_download )
                            {
                                  //GPS Project : todo : what kind of rule to show M-core?
                                m_ParamListView->Visible = true;
                            }
                          else{
                                m_ParamListView->Visible = false;
                              }
                        }
                        */

                    }
                    break;

                case YuSu:
                    {
                       g_project_mode=YuSu;

                       // update flash.bin path
                       ed_SPBIN_File->Text = "" ;
                       ed_AUTH_File->Text = "" ;
                       ReadYuSuINI();
                       DL_HANDLE_T &dl_handle = g_pCurNode->m_dl_handle;
                        // Compare the project ID
                       DL_ResourceProjectIdComparisonSetting( dl_handle, g_CompareResProjectId?_TRUE:_FALSE );

	                   RedrawReadbackList();
                       RedrawDownloadList( g_pCurNode, false );

                       // show Parameter List View
                        //   now disable parameter list
                        /*
                       DL_INFO dl_info;
                       if( !DL_GetInfo( dl_handle, &dl_info ) )
                       {
                          if( dl_info.m_config.m_security_supported || g_pCurNode->m_param.m_gps_download )
                            {
                                  //GPS Project : todo : what kind of rule to show M-core?
                                m_ParamListView->Visible = true;
                            }
                          else{
                                m_ParamListView->Visible = false;
                              }
                        }
                        */
                    }
                    break;
            }        

    UpdateCaption();
    updateMenuItem();                       
}
#endif
#if 0
//---------------------------------------------------------------------------
void TMainForm::RedrawProjectComBox()
{
     switch ( g_project_mode )
            {
                case DUMA:
                    {
                       cbxProject->ItemIndex =DUMA;
                       break;
                    }
                case YuSu:
                    {
                       cbxProject->ItemIndex =YuSu;
                       break;
                    }
            }
     ed_SPBIN_File->Text = "" ;
}
#endif
//---------------------------------------------------------------------------
bool TMainForm::LoadDefultScatter( MultiLoadNode *p_node, AnsiString asMapFileName )
{
     if( NULL ==  p_node ) {
		              return false;
	                     }

                	DL_HANDLE_T &dl_handle = p_node->m_dl_handle;

	                // load scatter
                	if ( S_DONE != DL_LoadScatter(dl_handle, asMapFileName.c_str(), g_platform_info.getLoadPlatformName().c_str()) )
                        {
		                return false;
	                 }
                	p_node->m_scat_file = asMapFileName;

	               // update scatter file's base directory
	            if ( 0 < p_node->m_scat_file.Length() )
                    {
		           int iLastDel = p_node->m_scat_file.LastDelimiter("\\:");

		         if ( 0 < iLastDel ) {
		         	ScatBaseDir = p_node->m_scat_file.SubString(1, iLastDel-1 );
	         	}
          	    }

                    return true;

}
//---------------------------------------------------------------------------
bool TMainForm::LoadDefultDA( AnsiString asFileName)
{
       //	int ret;

	if( S_DONE != DA_Load(g_DA_HANDLE, asFileName.c_str(), g_bDebugDA?_FALSE:_TRUE, _FALSE))
    {
		return false;
	}

   
	   MainForm->ed_Clone_DA_File->Text = asFileName;
          MainForm->ed_SCI_DL_DA_File->Text = asFileName;
	   MainForm->ed_DA_File->Text = asFileName;

	return true;
}
#if 0
//---------------------------------------------------------------------------
void TMainForm::AutoLoadDUMAROMs(MultiLoadNode *p_node)
{

        AnsiString temp_scat_path;
        AnsiString temp_rom_file;
        unsigned short rom_count;
        ROM_INFO	 rom_info[MAX_LOAD_SECTIONS];

        if( NULL ==  p_node ) {
		return ;
        }

        DL_HANDLE_T &dl_handle = p_node->m_dl_handle;
        int iLastDel = p_node->m_scat_file.LastDelimiter("\\:");

         if ( iLastDel > 0) {
               temp_scat_path  = p_node->m_scat_file.SubString(1, iLastDel-1 );
         }
         else{
               return;
         }

        if(!DL_GetCount(dl_handle, &rom_count))
        {
            if(!DL_Rom_GetInfoAll(dl_handle, rom_info, MAX_LOAD_SECTIONS))
            {
                //auto load
                for (int i=0; i<rom_count; i++)
                {
                   if (strcmpi(rom_info[i].name, "xldr") == 0)
                   {
                      temp_rom_file = temp_scat_path + "\\MT6516_mldrnandforMTK.nb0";
                      if(S_DONE ==  DL_Rom_Load(dl_handle, i, temp_rom_file.c_str()))
                      {
                      }
                   }
                   else if(strcmpi(rom_info[i].name, "eboot") == 0)
                   {
                      temp_rom_file = temp_scat_path + "\\MT6516_EBOOTNAND.nb0";
                      if(S_DONE ==  DL_Rom_Load(dl_handle, i, temp_rom_file.c_str()))
                      {
                      }
                   }
                }  //for
            }
        }

        temp_rom_file = temp_scat_path + "\\FLASH.bin";
        if( INVALID_FILE_ATTRIBUTES == GetFileAttributes(temp_rom_file.c_str()) ) {
              return ;
	}
        ed_SPBIN_File->Text = temp_rom_file.c_str();
        asFlashBinFile = ed_SPBIN_File->Text;

}
#endif
//---------------------------------------------------------------------------
void TMainForm::AutoLoadYuSuROMs(MultiLoadNode *p_node)
{
	ErrorLookup::SetErrorCodeMode(BROM);

	AnsiString temp_scat_path;
	if (!GetScatterFilePath(p_node, temp_scat_path)) {
		return;
	}

	unsigned short rom_count(0);
	ROM_INFO rom_info[MAX_LOAD_SECTIONS];
	memset(rom_info, 0, sizeof(ROM_INFO)*MAX_LOAD_SECTIONS);
	DL_HANDLE_T &dl_handle = p_node->m_dl_handle;

	vector<string> remoteFiles;
	vector<string> satisfiedFiles; //file list whose name contain prefix
	FileUtils::ListFiles(temp_scat_path.c_str(), remoteFiles);

	GetAndroidImageInfoTable().Reset(); //first, reset android image infos

	int ret(S_DONE);
	int err_ret(S_DONE);
	bool is_load_rom_fail(false);
	bool is_find_img(false);
	const std::string kErrRomMsgPrefix("Fail to load rom file: ");
	std::string err_msg;
	std::string file_name;
	std::map<std::string, int> err_msg_map;

	if(!DL_GetCount(dl_handle, &rom_count)) {
		if(!DL_Rom_GetInfoAll(dl_handle, rom_info, MAX_LOAD_SECTIONS)) {
			//auto load
			ImageType imgType = UNKNOWN_TYPE;
			ImageItem imgItem;
			std::string rom_file;
			std::list<std::string> prefixs;
			const std::string kScatterFilePath(temp_scat_path.c_str());
			for (int i=0; i<rom_count; i++) {
				imgType = GetImageMapRule().queryType(rom_info[i].name);
				imgItem = GetImageMapRule().getImageItem(imgType);
				prefixs = imgItem.prefixes();
				imgItem.Dump();
				
                    for(std::list<std::string>::const_iterator it_prefix = prefixs.begin();
				  it_prefix != prefixs.end(); ++it_prefix)
			{
			       satisfiedFiles.clear();
				 file_name = "";
			       is_find_img = FileUtils::FindFileByPrefix(remoteFiles, *(it_prefix), satisfiedFiles);

				if(!is_find_img)
				{
				     LOGD("No satisified files for this prefix(%s)", it_prefix->c_str());
                               continue;
				}

                          for(std::vector<string>::const_iterator it_file = satisfiedFiles.begin();
						  it_file != satisfiedFiles.end(); ++it_file)
				{
                               if(!imgItem.isSuffixMatch((*it_file)))
				     {
                                    LOGD("object file is found, %s", it_file->c_str());
					    file_name = (*it_file);
					    break;
				     }
				}				
								 
                          rom_file = kScatterFilePath + "\\" + file_name;
				LOGD("rom_file(%s).", rom_file.c_str());
				ret = DL_Rom_Load(dl_handle, i, rom_file.c_str());
				if(S_DONE ==  ret) {
				      //add to AndroidImageInfoTable except preloader
				      //TODO: refine this
				      if( !imgItem.is_bootloader() && imgItem.is_format_effective() ) {
						AndroidImageInfo info;
						info.romIndex = i;
						info.type = static_cast<DM_IMG_TYPE>(imgType);
						info.format = static_cast<DM_IMG_FORMAT>(imgItem.eboot_format());
						info.filePath = rom_file.c_str();
						info.romName = rom_info[i].name;
						GetAndroidImageInfoTable().UpdateInfo(rom_info[i].name,info);
						break;
					}
				} else{
						err_ret = ret;
						is_load_rom_fail = true;
						err_msg = kErrRomMsgPrefix + rom_info[i].name + ".";
						err_msg_map.insert(std::make_pair(err_msg, err_ret));
				}							
				
			}
					
			}//for
			//LOGD(GetAndroidImageInfoTable().Dump());
		}
	}

	if (is_load_rom_fail) {
	        std::map<std::string, int>::iterator it = err_msg_map.begin();
		std::ostringstream ostr;
		ostr << std::endl;
		for (; it != err_msg_map.end(); it++) {
			ostr <<ErrorLookup::GetErrorMessage( it->second) << std::endl 
				<< "[Extra Error Hint] " <<std::endl
				<< it->first.c_str() << std::endl<<std::endl;
		}
		std::string err_hint = ostr.str();
		LOGE("DL_Rom_Load() falied!, error hint: %s.", err_hint.c_str());
		ShowMessage(err_hint.c_str());
	}
}

//---------------------------------------------------------------------------
bool TMainForm::GetScatterFilePath(const MultiLoadNode *p_node, AnsiString& scatterFilePath)
{
    if( NULL ==  p_node ) {
		return false;
	}

    int iLastDel = p_node->m_scat_file.LastDelimiter("\\:");

    if ( iLastDel > 0) {
        scatterFilePath  = p_node->m_scat_file.SubString(1, iLastDel-1 );
        return true;
    }
    else{
        return false;
    }
}

//************Search AP/BP database file**************//
static bool startsWith(const string &file_name, const string &pattern){
	return (file_name.find(pattern) == 0);
}

//---------------------------------------------------------------------------
void TMainForm::AutoFillDatabasePath(const MultiLoadNode *p_node)
{
	AnsiString scatter_path;
    if( !GetScatterFilePath(p_node, scatter_path) ) {
		return ;
	}

    Form_FourInOne->m_asAP_Path = scatter_path;
    Form_FourInOne->m_asModem_Path = scatter_path;

    std::vector<std::string> AP_DB_files;
 	std::vector<std::string> Modem_DB_files;

	FileUtils::SearchFile(scatter_path.c_str(), AP_DB_files, "APDB", startsWith);
	FileUtils::SearchFile(scatter_path.c_str(), Modem_DB_files, "BPLGUInfoCustomApp", startsWith);

	for(std::vector<std::string>::const_iterator it = AP_DB_files.begin();
	    it != AP_DB_files.end(); ++it)
	{
	    if( it->find("ENUM") == std::string::npos){
			Form_FourInOne->m_asAP_Database = scatter_path+"\\"+it->c_str();
			break;
		}
	}
	if(Modem_DB_files.size() >0){
		Form_FourInOne->m_asModem_Database = scatter_path + "\\"
            + Modem_DB_files.front().c_str();
	}
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::m_subMenu_FourInOne_NoActionClick(
      TObject *Sender)
{
    g_nvram_update_state    = NOACTIONNVRAM ;
    updateMenuItem();
	updateStatusBar();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::m_subMenu_FourInOne_WriteClick(TObject *Sender)
{
     g_nvram_update_state = UPDATENVRAM;
     //g_backup_restore_state = NOACTION;
     updateMenuItem();
	 updateStatusBar();
     Form_FourInOne->Visible = true;
}
//---------------------------------------------------------------------------
bool DownloadSet::operator == (const DownloadSet	&r_value)
{
    if( 0==m_Scatter.AnsiCompareIC(r_value.m_Scatter) &&
		0==m_BootLoader.AnsiCompareIC(r_value.m_BootLoader) &&
		m_BinFiles.size()==r_value.m_BinFiles.size()
	   )
    {
        unsigned int i;
        for(i=0; i < m_BinFiles.size(); i++)
        {
            if( 0 != m_BinFiles[i].m_Filepath.AnsiCompareIC(r_value.m_BinFiles[i].m_Filepath) )
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::m_subMenu_Format_DL_FourInOne_WriteClick(
      TObject *Sender)
{
     g_nvram_update_state = FORMAT_DL_UPDATENVRAM;
     //g_backup_restore_state = NOACTION;
     updateMenuItem();
	 updateStatusBar();
     Form_FourInOne->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DefaultExceptionHandle(TObject* Sender, Exception* exp){
	LOGE(exp->Message.c_str());
	Application->ShowException( exp );
	exit(1);
}

void __fastcall TMainForm::m_subMenu_Format_DL_Restore_NVRAMClick(
      TObject *Sender)
{
	/*
	AnsiString RestorePath;
	if(SelectDirectory("Choose the directory which you want to restore", 
				FileUtils::GetAppDirectory().c_str(), RestorePath)) {
			g_BackupCalibrationDataFolderPath = RestorePath;
	}*/

   //only update options when select a correct folder.
    //g_backup_restore_state = FORMAT_DOWNLOAD_RESTORE_NVRAM;
    g_nvram_update_state = NOACTIONNVRAM;
    updateMenuItem();
     
//    Form_Backup_Restore_NVRAM->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::m_subMenu_Restore_NVRAM_OnlyClick(
      TObject *Sender)
{
    AnsiString RestorePath;
    if(SelectDirectory("Choose the directory which you want to restore", 
            FileUtils::GetAppDirectory().c_str(), RestorePath)) {
        g_BackupCalibrationDataFolderPath = RestorePath;

        //only update options when select a correct folder.
    //g_backup_restore_state = RESTORE_NVRAM_ONLY;
    g_nvram_update_state = NOACTIONNVRAM;
    updateMenuItem();
    }
//    Form_Backup_Restore_NVRAM->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::UseChipIDasBackupFolderNameClick(TObject *Sender)
{
    g_backup_restore_folder_type = BY_RID;
    updateMenuItem();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::UseCOMPortasBackupFolderNameClick(
      TObject *Sender)
{
    g_backup_restore_folder_type = BY_COM;
    updateMenuItem();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::m_Menu_DA_DL_allClick(TObject *Sender)
{
	//FIXME when remove all global variables
//    if(g_bDADownloadAll){
//        g_bDADownloadAll = false;
//        m_Menu_DA_DL_all->Checked = false;
//    }else{
//        g_bDADownloadAll = true;
//        m_Menu_DA_DL_all->Checked = true;
//    }
//    updateMenuItem();
}

//---------------------------------------------------------------------------

void TMainForm::newVersionDetected(const std::string &version, const std::string &path){
	if(isTbootWorking){
		return;
	}
	string msg("New Flash tool version detected:\n");
	msg.append("v").append(version);
	msg.append("\nAre you sure to update?");
	int ret = MessageBox(NULL, msg.c_str(), "Updates Available",
			MB_TASKMODAL | MB_ICONINFORMATION | MB_OKCANCEL);
	if (ret == IDOK) {
		LOGD(std::string("updating to latest version : ").append(path).c_str());
		AutoUpdater::Instance()->ExecuteUpdate();
	}
}
inline bool TMainForm::IsDLListEmpty(void) const
{
	if ( 0 == ListView1->Items->Count ) {	    
		return true;
	} else {
		return false;
	}
}
//---------------------------------------------------------------------------
bool TMainForm::IsInitialParameterCheckPass(void)
{
       	if (IsDLListEmpty()) {
		ShowMessage("[Hint] Download list is empty, please select a scatter file before excuting!");
	    return false;
	}

	if ((MainForm->ed_SCERT_File->Text.IsEmpty()) && IsNullImgsToBeDL(g_pCurNode->m_dl_handle)) {
        ShowMessage("[Hint] Please make sure at least one image check box is checked before excuting DOWNLOAD!");
		return false;
	}      

    std::string errHint;
	if ( !IsImgsToBeDLWithPath(g_pCurNode->m_dl_handle, errHint) ) {
		ShowMessage(errHint.c_str());
		return false;
	}

	return true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::m_Menu_Physical_Fmt_RBClick(TObject *Sender)
{
    if(g_bPhysicallyFormatReadback){
        g_bPhysicallyFormatReadback = false;
        m_Menu_Physical_Fmt_RB->Checked = false;
    }else{
        g_bPhysicallyFormatReadback = true;
        m_Menu_Physical_Fmt_RB->Checked = true;
    }
    updateMenuItem();
}
//---------------------------------------------------------------------------

//function for updating UI when platform changed
void TMainForm::onPlatformChanged(){
	LOG("TMainForm::onPlatformChanged(): platform name = %s",g_platform_info.getLoadPlatformName().c_str());
	LOG("TMainForm::onPlatformChanged(): isDADownloadAllEnabled(%s)", g_platform_info.isDADownloadAllEnabled() ? "Y" : "N");

	updateUIForPlatform();
}
     
void TMainForm::updateUIForPlatform(){
	
	Platform config = g_platform_info.getPlatformConfig();

	m_Menu_Backup_Restore_NVRAM->Enabled = config.supportBackupRestore();
	//For MT6573 or later, disable NandUtil USB
	bb_OpenNandUtil->Enabled = config.supportNandUtil();
	action_ToggleSkipBootRom->Enabled = config.supportNandUtil();
	//For MT6573 disable image lock temporarily
    cb_sec_setting->Enabled = config.supportImageLock();
	rb_sec_setting_Write->Enabled = config.supportImageLock();
	bt_sec_setting->Enabled = config.supportImageLock();

    //tb_Format_DLButton->Enabled = true;
    //m_Menu_FourInOne->Enabled = true;
	if(config.supportUSBDownload()){
		mi_USBDownloadDA->Enabled = true;
             
	  if(g_platform_info.isDADownloadAllEnabled()){
		m_Menu_DA_DL_all->Enabled = true;
		if (config.isDefaultNotSwitchSpeed()) {
			g_bUsbMode = true;
			g_bDADownloadAll = true;
			g_bSwitchSpeed = false;
		}else{
                   g_bUsbMode = true;
			g_bDADownloadAll = true;
			g_bSwitchSpeed = true;		}           
		
	  } else {
		g_bDADownloadAll = false;
		g_bSwitchSpeed = false;
		m_Menu_DA_DL_all->Enabled = false;
	}
		
	} else {
		g_bUsbMode = false;
		mi_USBDownloadDA->Enabled = false;
	}

    if(config.supportFirmwareUpgrade() &&
		g_platform_info.getFlashToolStorageConfig().IsSupportAutoFormat()) {
        //m_Menu_Backup_Restore_NVRAM->Enabled = true;
    	tb_FirmwareUpgradeButton->Enabled = true;
    } else {
        //g_backup_restore_state =  NOACTION;
        //m_Menu_Backup_Restore_NVRAM->Enabled = false;
    	tb_FirmwareUpgradeButton->Enabled = false;
    }

	if(config.supportLogicalAddress()){
		m_Menu_Physical_Fmt_RB->Enabled = true;
	} else {
		g_bPhysicallyFormatReadback = false;
		m_Menu_Physical_Fmt_RB->Enabled = false;
	}
    //Block UI dl w/o bat according platform.xml for auto detection
	if(config.supportDLAutoDetectBattery()) {
		m_Menu_DA_DL_All_Battery->Enabled = false;
	} else {
		m_Menu_DA_DL_All_Battery->Enabled = true;
	}

    LOG("TMainForm::updateUIForPlatform(): DA download all Enabled: %d",m_Menu_DA_DL_all->Enabled);
	LOG("TMainForm::updateUIForPlatform(): Storage type(%s).", 
		g_platform_info.getFlashToolStorageConfig().GetStorageName().c_str());

	updateMenuItem();
    updateStatusBar();
}
	
void __fastcall TMainForm::m_Menu_DA_DL_all_noClick(TObject *Sender)
{
    g_bDADownloadAll = false;
    g_bUsbModeWithBattery = false;
    g_bSwitchSpeed = false;
    updateMenuItem();
    updateStatusBar();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::m_Menu_DA_DL_all_fullClick(TObject *Sender)
{
    g_bDADownloadAll = true;
    g_bSwitchSpeed = false;
    updateMenuItem();
    updateStatusBar();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::m_Menu_DA_DL_all_highClick(TObject *Sender)
{
    g_bDADownloadAll = true;
    g_bSwitchSpeed = true;
    updateMenuItem();
    updateStatusBar();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::m_Menu_Locate_LogsClick(TObject *Sender)
{
    //pop up explorer
	Logger::SetSPFlashToolLogFolder();
	ShellExecute(NULL, "open", Logger::GetSPFlashToolLogFolder().c_str(), NULL, NULL, SW_SHOWNORMAL);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::m_Menu_USB_mode_with_batClick(TObject *Sender)
{
    g_bDADownloadAll = true;
    g_bUsbModeWithBattery = true;
    updateMenuItem();

    UpdateCaption();
    updateStatusBar();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::m_Menu_USB_mode_without_batClick(TObject *Sender)
{
    g_bDADownloadAll = true;
    g_bUsbModeWithBattery = false;    
    updateMenuItem();

    UpdateCaption();
    updateStatusBar();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::pc_mainframeChange(TObject *Sender)
{
    if (MainForm->ts_Download != MainForm->pc_mainframe->ActivePage) {
        m_HWStatus->Panels->Items[2]->Text = "";
	} else {
	    updateStatusBar();
	}

    if (g_scatter_type == NORMAL_SCATTER)
    {
          ed_SCI_DL_SCIFile->Text = "";
          lv_SCIDownload->Items->Clear();
          
    }else if(g_scatter_type == SCI_FILE)
    {
          ed_LinkMapFile->Text = "";
          ListView1->Items->Clear();
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::m_Menu_WriteMemory_CheckParameterPageClick(TObject *Sender)
{
    if( m_Menu_WriteMemory_CheckParameterPage->Checked ) {
        m_Menu_WriteMemory_CheckParameterPage->Checked = false;
        ts_WriteMemory->TabVisible = false;
        g_flashtool_function = FLASHTOOL_WRITEMEMORY;
    }
    else{
        m_Menu_WriteMemory_CheckParameterPage->Checked = true;
        ts_WriteMemory->TabVisible = true;
        g_flashtool_function    = FLASHTOOL_DOWNLOAD;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::tb_OpenRawDataClick(TObject *Sender)
{
    unsigned int   raw_data_len = 0;

    AnsiString	s;

    m_OpenWriteMemoryFileDialog->Title = "Open a raw data file to write into memory ...";

    if(!m_OpenWriteMemoryFileDialog->Execute())
    {
		s.printf("Fail to open a raw data file \"%s\" !", m_OpenWriteMemoryFileDialog->FileName.c_str());
		ShowMessage(s);
		return;
    }

	if(MainForm->LoadFileInfo(m_OpenWriteMemoryFileDialog->FileName.c_str(),&raw_data_len, NULL))
    {
    	s.printf("Fail to load a raw data file \"%s\" !", m_OpenWriteMemoryFileDialog->FileName.c_str());
		ShowMessage(s);

        // reset File path and File size
        ed_WM_OpenRawData->Text = " ";
        lb_WM_OpenRawDataFileSizeValue->Caption = "0  (Bytes)";

    	return;
	}

    // assign File path and File size
    ed_WM_OpenRawData->Text = m_OpenWriteMemoryFileDialog->FileName;
    g_WM_RawDataFilePath = m_OpenWriteMemoryFileDialog->FileName;


    s.printf("0x%08X",raw_data_len);
    lb_WM_OpenRawDataFileSizeValue->Caption = s + "  (Bytes)";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::tb_WriteMemoryClick(TObject *Sender)
{
    g_flashtool_function = FLASHTOOL_WRITEMEMORY;

    if (IsDLListEmpty()) {
		ShowMessage("Please select scatter file before writing memory.");
	    return;
	}
    
    if( ed_WM_OpenRawData->Text.Length() == 0 ) {
        ShowMessage(" You must provide a raw data file before starting to write memory.");
        return;
    }

    g_WM_address =  StrToInt64(le_WM_StartAddr->Text.c_str());
    g_WM_container_length = strtoul(le_WM_Length->Text.c_str(), NULL, 16);

	if ( asBin.IsEmpty() ){
		if ( !FileOpenNandUtilBin(OpenDownloadAgentDialog, NORMAL_DA_BIN) ){
			ShowMessage(" You must open download agent file before writing memory. ");
			return;
		}
	} else {
		//Update DA by DA_Load
		if(!OpenReadDA_File( asBin,  NORMAL_DA_BIN)) {
		    ShowMessage(" Load DA Fail!");
			LOGD("ERROR: TMainForm::tb_WriteMemoryClick(): OpenReadDA_File() fails!");
			return;
		}
	}
		

	if( UpdateDA() ) return;

    start_DL(true);

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::tb_WriteMemory_StopClick(TObject *Sender)
{
    // reset stop flag
	g_stopflag = BOOT_STOP;
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::ts_WriteMemoryShow(TObject *Sender)
{
    ed_WM_OpenRawData->Text = g_WM_RawDataFilePath.c_str();
    le_WM_StartAddr->Text = "0x" + IntToHex(static_cast<__int64>(g_WM_address), 16);
    le_WM_Length->Text = "0x" + IntToHex(static_cast<int>(g_WM_container_length), 8);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::tb_ReadbackVersionClick(TObject *Sender)
{
	if (IsDLListEmpty()) {
		ShowMessage("Please select scatter file before Readback Software Version.");
	    return;
	}

    g_flashtool_function = FLASHTOOL_READ_SW_VERSION;
	//FIXME
	//g_backup_restore_state =  NOACTION;
	g_nvram_update_state    = NOACTIONNVRAM ;
	updateMenuItem();

    if ( asBin.IsEmpty() )
    {
       //if (! FileOpenDownloadAgentExecute() )
       if (! FileOpenNandUtilBin(OpenDownloadAgentDialog, NORMAL_DA_BIN) )
       {
          ShowMessage(" You must open download agent file before reading back. ");
          return;
       }
    }

    // clean Flash device info
	HWStatusBarClear();

    // update DA to the latest version
	if( UpdateDA() ) return;

    start_DL(true);

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::tb_ReadbackProductInfoClick(TObject *Sender)
{
	if (IsDLListEmpty()) {
		ShowMessage("Please select scatter file before Readback Software Version.");
	    return;
	}

    g_flashtool_function = FLASHTOOL_READ_PRODUCT_INFO;
	//FIXME
	//g_backup_restore_state =  NOACTION;
	g_nvram_update_state    = NOACTIONNVRAM ;
	updateMenuItem();

    if ( asBin.IsEmpty() )
    {
       //if (! FileOpenDownloadAgentExecute() )
       if (! FileOpenNandUtilBin(OpenDownloadAgentDialog, NORMAL_DA_BIN) )
       {
          ShowMessage(" You must open download agent file before reading back. ");
          return;
       }
    }

    // clean Flash device info
	HWStatusBarClear();

    // update DA to the latest version
	if( UpdateDA() ) return;

    start_DL(true);
}
//---------------------------------------------------------------------------
/*****************************************************************************
*
* ShowHintMessage() is used to config both the location and content of the hint message in GUI.
*
******************************************************************************/
void TMainForm::ShowHintMessage(TControl *sender, const string& hint, int offset_x, int offset_y )
{
	TPoint pt0 = pc_mainframe->ClientOrigin;
	TPoint pt1 = sender->ClientOrigin;

	stHint->Left = (pt1.x - pt0.x) + offset_x;
	stHint->Top = (pt1.y - pt0.y) + offset_y;

	stHint->Caption = hint.c_str();

	stHint->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ListView1CustomDrawItem(TCustomListView *Sender,
      TListItem *Item, TCustomDrawState State, bool &DefaultDraw)
{
        HintMessageHandle hint_handle;
	 hint_handle.QueryHintInfo(Item->Caption.c_str());

	if(hint_handle.is_show_hint() && Item->Checked == false)
	{                		
		Sender->Canvas->Font->Color = clRed;
	}                    
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Timer_ChecksumTimer(TObject *Sender)
{
      ShowHintMessage(this, "PC Checksum processing, please wait a minute...", 300, 160);     
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Timer_WarningTimer(TObject *Sender)
{	
	 Timer_Warning->Enabled = false;
        stHint->Visible = false;    	
}
//---------------------------------------------------------------------------

/**************************************************************************
* Check the item if meet condition of hint message show and show the hint message.
***************************************************************************/
void TMainForm::CSHintMessage(int itemindex)
{
	 HintMessageHandle hint_handle;
	 hint_handle.QueryHintInfo(ListView1->Items->Item[itemindex]->Caption.c_str());

	 if(hint_handle.is_show_hint() && ListView1->Items->Item[itemindex]->Checked == false)
	 {	       
              Timer_Warning->Enabled = true;
		ShowHintMessage(ListView1, hint_handle.hint_message().c_str(),hint_handle.offset_x(), hint_handle.offset_y());
	 }
}   

void __fastcall TMainForm::action_MarkNandBadBlockOptionExecute(
      TObject *Sender)
{
	if (g_bEnableMarkNandBadBlocks) {
		g_bEnableMarkNandBadBlocks = false;
	} else {
		g_bEnableMarkNandBadBlocks = true;
	}
    UpdateCaption();    
}
//---------------------------------------------------------------------------
void TMainForm::BromDLTypeTblEntry(DL_HANDLE_T dl_handle)
{
	std::set<ImageType> img_type_set = GetImageMapRule().image_type_set();
	ImageItem img_item;
	std::set<ImageType>::iterator it;
	for (it = img_type_set.begin(); it != img_type_set.end(); it++) {
		img_item = GetImageMapRule().getImageItem(*it);
		if( img_item.is_format_effective() ) {
			LOG("%s(): image name(%s), image brom type(%d).", 
				__FUNC__, img_item.type_name().c_str(), img_item.brom_format());
			if (S_DONE != DL_ImgTypeTblEntryAdd(dl_handle, img_item.type_name().c_str(), 
				static_cast<ROM_TYPE>(img_item.brom_format()))) {
					LOG("ERROR: %s(): add image(%s), enum(%d) into DL_ImgTypeTblEntryAdd() failed!.",
						__FUNC__, img_item.type_name().c_str(), img_item.brom_format());
					return;
			}
		}
	}
	DL_ImgTypeTblEntryList(dl_handle);

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::action_ToggleDLCertExecute(TObject *Sender)
{
        //Certification DL Mode, Ctrl + Alt + C
        g_bDLCertificationMode = (!g_bDLCertificationMode);
        tb_DL_Certification->Visible = g_bDLCertificationMode;

	 UpdateCaption();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::tb_DL_CertificationClick(TObject *Sender)
{

  /******Load configration XML files begin******/
  //Load usb_setting.xml table
  FlashToolUSBTable usb_table = GetFlashToolUSBTable();
  //Load storage_setting.xml table
  GetFlashToolStorageTable();
 /******Load configration XML files end******/


   if(ed_SCERT_File->Text.IsEmpty()){
      ShowMessage("[Hint]Please select a certification file before excuting!");
      return;
   }
   g_bDLCert = true;
   LOGD("g_bDLCert(%d).", g_bDLCert);

   if( MT6205 != g_BBCHIP_TYPE )
	   start_DL(true);
}
//---------------------------------------------------------------------------
void _fastcall TMainForm::SubClassWndProc(Messages::TMessage &Message)
{
    switch (Message.Msg)                               
    {
        case AP_SPFT_DOWNLOAD_SUCCESSFUL:                     
        {
			if (this->IsAutoPollingEnable() && (!this->isTbootWorking) && (BOOT_STOP != g_stopflag))
             {
                 //Download1Click(tb_DL_StartButton);
				 if (this->m_auto_polling_count < this->m_auto_polling_upper_limit) {
					 this->m_auto_polling_count++;
					 LOGD("Auto polling upper limit(%d), polling count(%d).",
						 this->m_auto_polling_upper_limit, this->m_auto_polling_count);
					 start_DL(true);
				 } else {
					 LOGD("Auto Polling Done, auto polling upper limit(%d), polling count(%d).",
						 this->m_auto_polling_upper_limit, this->m_auto_polling_count);
				 }
             }
			break;
        }

		case AP_SPFT_STOP:
        default:
        {
            this->WndProc(Message);
			break;
        }
    }
}
//--------------------------------------------------------------------------- 
void __fastcall TMainForm::bb_Clone_OpenDAClick(TObject *Sender)
{
    FileOpenNandUtilBin(OpenDownloadAgentDialog, NORMAL_DA_BIN);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::bb_Clone_ReadbackClick(TObject *Sender)
{

  InitialConfigurations();

  g_flashtool_function = FLASHTOOL_SCI_READBACK;

  if( MT6205 != g_BBCHIP_TYPE )
  {
       start_DL(true);
  }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::bb_SCI_Clone_RestoreClick(TObject *Sender)
{

  g_flashtool_function = FLASHTOOL_SCI_WRITEMEMORY;

  if(!checkBeforeSCIRestore())
  {
      ShowMessage("Please select files that to be restored before operation!");
      return;
  }

  if( MT6205 != g_BBCHIP_TYPE )
  {
       start_DL(true);
  }
}
//--------------------------------------------------------------------------- 
void __fastcall TMainForm::bb_SCI_DL_DownloadClick(TObject *Sender)
{
  g_flashtool_function = FLASHTOOL_SCI_DOWNLOAD;

  if(!checkBeforeSCIDownload())
  {
      ShowMessage("Please select SCI file before download!");
      return;
  }

  if( MT6205 != g_BBCHIP_TYPE )
  {
       start_DL(true);
  }
}
//---------------------------------------------------------------------------
bool TMainForm::checkBeforeSCIRestore()
{
  bool ret = true;

  ret = !(ed_SCI_RestoreFile->Text.IsEmpty());
  
  this->m_restore_file_path = ed_SCI_DL_SCIFile->Text.c_str();
  LOGD("%s: Restore Files Path: %s", __FUNC__, m_restore_file_path);

  //assert(!m_restore_file_path.empty());

  return ret;
}
//---------------------------------------------------------------------------
bool TMainForm::checkBeforeSCIDownload()
{
  bool ret = true;

  ret = !(ed_SCI_DL_SCIFile->Text.IsEmpty());

  return ret;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::bb_SCI_DL_OpenDAFileClick(TObject *Sender)
{
  FileOpenNandUtilBin(OpenDownloadAgentDialog, NORMAL_DA_BIN);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::bb_OpenSCIFileClick(TObject *Sender)
{
    int ret = S_DONE;

    g_scatter_type = SCI_FILE;

    //set default path for open dialog
    if ( ScatBaseDir.Length() > 0 )
    {
        OpenSCIFileDialog->InitialDir = ScatBaseDir;
        OpenSCIFileDialog->FileName   = "";
    }
    else if( 0 < ed_SCI_DL_SCIFile->Text.Length() )
    {
        const int iLastDel = ed_SCI_DL_SCIFile->Text.LastDelimiter("\\:");

        if ( iLastDel > 0)
        {
	        OpenSCIFileDialog->InitialDir = ed_SCI_DL_SCIFile->Text.SubString(1, iLastDel-1 );
		  OpenSCIFileDialog->FileName = "";
        }
    }

    if ( OpenSCIFileDialog->Execute() )
    {    
       /******Load configration XML files begin******/
	//Load usb_setting.xml table
	FlashToolUSBTable usb_table = GetFlashToolUSBTable();
	//Load storage_setting.xml table
	GetFlashToolStorageTable();
	/******Load configration XML files end******/
	AnsiString scattPath = OpenSCIFileDialog->FileName;
       const int iLastDel = OpenSCIFileDialog->FileName.LastDelimiter("\\");

       //create DL handle
	 DL_Destroy(&g_DL_HANDLE_NODE.m_dl_handle);
        DL_Create(&g_DL_HANDLE_NODE.m_dl_handle);

        g_DL_HANDLE_NODE.m_scat_file = scattPath;

	 //Send image-type table before load scatter file, otherwise, default table will be used
        BromDLTypeTblEntry(g_DL_HANDLE_NODE.m_dl_handle);

	 if(!ParseSCIFile(scattPath)) return;

       if ( iLastDel > 0)
       {
           ScatBaseDir  = g_DL_HANDLE_NODE.m_scat_file.SubString(1, iLastDel-1 );
       }

	 ed_SCI_DL_SCIFile->Text = g_DL_HANDLE_NODE.m_scat_file;

    	    return;
    	}
	 
            
}
//---------------------------------------------------------------------------
bool TMainForm::ParseSCIFile(const AnsiString &scatpath)
{
      int ret = S_DONE;

      //load SCI File
      if( S_DONE != ( ret = DL_LoadSCIScatter(g_DL_HANDLE_NODE.m_dl_handle, scatpath.c_str()) ) )
       {
            if( S_FTHND_HANDLE_BUSY_NOW == ret )
           {
                 ShowMessage("Program is busy! Can not reload scat file right now.");
           }
           else if( S_DL_SCAT_OFFSET_IS_NOT_WORD_ALIGN == ret )
           {
                 ShowMessage("Failed to load scatter file \"" + scatpath + "\"!\n\nThe offset value of one load region is not WORD alignment!");
           }
           else if( S_DL_SCAT_ADDR_IS_NOT_WORD_ALIGN == ret )
           {
                 ShowMessage("Failed to load scatter file \"" + scatpath + "\"!\n\nThe region begin address of one load region is not WORD alignment!");
           }
          else if( S_DL_SCAT_ADDR_IS_NOT_ASCENDING_ORDER == ret )
          {
                 ShowMessage("Failed to load scatter file \"" + scatpath + "\"!\n\nThe region begin address of one load region is not ascending sorting sequence!");
          }
         else
          {
                ShowMessage("Incorrect scatter file format!");
          } 
          return false;
       }   

        //platform settings
        DL_PlatformInfo pl_info;
	  std::string error_msg;

	  ret = DL_GetPlatformInfo(g_DL_HANDLE_NODE.m_dl_handle, &pl_info);

	  g_platform_info.setSimpleName(pl_info.m_szBBChipType);
	  g_platform_info.setStorage(pl_info.m_szStorageType);	 
        bool isSCI = (MainForm->ts_SCIDownload == MainForm->pc_mainframe->ActivePage)
			    ||(MainForm->ts_SCIClone == MainForm->pc_mainframe->ActivePage);
	  g_platform_info.initByScatterFile(OpenLdMapDialog->FileName.c_str(), error_msg, isSCI);

        unsigned int bmt_block_count = 0;
	 g_platform_info.setBMTBlocks(bmt_block_count);
	 g_platform_info.setDADownloadAllEnabled(true);
	 LOG("TMainForm::Parse(): Get BMT block count is %d.", bmt_block_count);	
	  
    	  if(!g_platform_info.is_scatter_file_valid()) {
			ShowMessage(error_msg.c_str());
			 return false;
	  } else if (!g_platform_info.is_storage_type_support()) {
			ShowMessage(error_msg.c_str());
			return false;
	 }

	  //redraw download list
	  RedrawSCIDLList(&g_DL_HANDLE_NODE);

	  return true;
	  
}
//---------------------------------------------------------------------------
void TMainForm::RedrawSCIDLList(MultiLoadNode *pNode)
{
      CS_Sentry cs_sentry(m_pUpdateListLock);

      unsigned short rom_count;
      TListItem *pListItem;
	DL_HANDLE_T &dl_handle = pNode->m_dl_handle;

	lv_SCIDownload->Items->Clear();

	if(!DL_GetCount(dl_handle, &rom_count))
	{
           ROM_INFO rom_info[MAX_LOAD_SECTIONS];
           
           if(!DL_Rom_GetInfoAll(dl_handle, rom_info, MAX_LOAD_SECTIONS))
	     {
	         for(int i = 0; i < rom_count; i++)
	        {
                    if(_TRUE == rom_info[i].item_is_visable)
                   {
                        pListItem = lv_SCIDownload->Items->Add();
			     pListItem->Caption = rom_info[i].name;
			     pListItem->Checked = ((rom_info[i].enable == _TRUE)?true:false);
			     pListItem->SubItems->Add("0x" + IntToHex((__int64)rom_info[i].begin_addr, 16));
			     LOGD("name(%s), enable(%d)", pListItem->Caption.c_str(), pListItem->Checked);
		       }
	             else
	             {
                         continue;
		      }		
	        }
		}
	}	  
}    

//---------------------------------------------------------------------------

void __fastcall TMainForm::bb_SCI_DL_StopClick(TObject *Sender)
{
        g_stopflag = BOOT_STOP;

	META_CancelAllBlockingCall();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::bb_Clone_Readback_StopClick(TObject *Sender)
{
    	g_stopflag = BOOT_STOP;

	META_CancelAllBlockingCall();        
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::bb_Clone_Restore_StopClick(TObject *Sender)
{
     	g_stopflag = BOOT_STOP;

	META_CancelAllBlockingCall();        
}
//--------------------------------------------------------------------------- 
void __fastcall TMainForm::bb_SCI_OpenFileFolderClick(TObject *Sender)
{
    std::string sciFileFolder = FileUtils::GetAppDirectory() + "\\" + SCI_FILE_FOLDER;

     ShellExecute(NULL, "open", sciFileFolder.c_str(), NULL, NULL, SW_SHOWNORMAL);      
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::bb_Restore_OpenFileClick(TObject *Sender)
{
     AnsiString RestorePath;

     InitialConfigurations();

     if(SelectDirectory("Choose the directory which you want to restore",
				    L"", RestorePath))
     {
          LOG("%s: m_restore_file_path(%s)", __FUNC__, m_restore_file_path.c_str());
          ed_SCI_RestoreFile->Text = RestorePath;
     }

      std::string path(ed_SCI_RestoreFile->Text.c_str());
      m_restore_file_path = path;
	 
     std::string filePath = m_restore_file_path + "\\" + "clone_info.xml";

     if(!FileUtils::IsFileExist(filePath))
     {
          ShowMessage("Restore configure file clone_info.xml is not exist!");
	    LOGE("%s: config file is not exist!", __FUNC__);
          ed_SCI_RestoreFile->Text = "";
	    return;
     }

     //GetCloneInfoHandle(filePath);
}
//---------------------------------------------------------------------------
/*
  Initial USB/Platform tables
  */
void TMainForm::InitialConfigurations()
{
  int ret;
       
  /******Load configration XML files begin******/
  //Load usb_setting.xml table
  FlashToolUSBTable usb_table = GetFlashToolUSBTable();
  //Load storage_setting.xml table
  GetFlashToolStorageTable();
  /******Load configration XML files end******/

  PlatformInfo pl_info;
  std::string error_msg;

   g_platform_info.setSimpleName("MT6575");
   g_platform_info.setStorage("EMMC");
    bool isSCI = (MainForm->ts_SCIDownload == MainForm->pc_mainframe->ActivePage)
		       ||(MainForm->ts_SCIClone == MainForm->pc_mainframe->ActivePage);
   g_platform_info.initByScatterFile(OpenLdMapDialog->FileName.c_str(), error_msg, isSCI);

   unsigned int bmt_block_count = 0;
   g_platform_info.setBMTBlocks(bmt_block_count);
   g_platform_info.setDADownloadAllEnabled(true);
   LOG("TMainForm::Parse(): Get BMT block count is %d.", bmt_block_count);	
	  
   if(!g_platform_info.is_scatter_file_valid()) {
		ShowMessage(error_msg.c_str());
		return;
   } else if (!g_platform_info.is_storage_type_support()) {
		ShowMessage(error_msg.c_str());
   }   
}
//----------------------------------------------------------------------------
void __fastcall TMainForm::lv_SCIDownloadChange(TObject *Sender,
      TListItem *Item, TItemChange Change)
{
    //ShowMessage("Change");
    if( (ctState == Change) &&
    	(Item->Checked != DL_bPreviousCheckBoxValue) )
    {
        DL_IndexOfChangedCheckBox = Item->Index;
        return;
    }

    DL_IndexOfChangedCheckBox = -1;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::lv_SCIDownloadChanging(TObject *Sender,
      TListItem *Item, TItemChange Change, bool &AllowChange)
{
      //ShowMessage("Changing");

      DL_bPreviousCheckBoxValue = Item->Checked;

      DL_IndexOfChangedCheckBox = -1;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::lv_SCIDownloadClick(TObject *Sender)
{
     	 TListView *plv = dynamic_cast<TListView *>(Sender);
		 
	 //	ShowMessage("Click");

       if( NULL == g_pCurNode )  return;

	DL_HANDLE_T &dl_handle=g_pCurNode->m_dl_handle;

	if( 0 <= DL_IndexOfChangedCheckBox && DL_IndexOfChangedCheckBox < plv->Items->Count ) 
	{
		TListItem *pItem=plv->Items->Item[DL_IndexOfChangedCheckBox];

		if(pItem == NULL) return;
            
		DL_Rom_SetEnableAttrByRomName(dl_handle, pItem->Caption.c_str(), pItem->Checked?_TRUE:_FALSE); 
             LOGD("name(%s),Enable(%d)", pItem->Caption.c_str(), pItem->Checked?true:false);
		//for UT test
		#if 0
		 int itemIndex = GetROMIndex( pItem->Caption.c_str(), dl_handle);
            if ( -1 == itemIndex )
            {
                ShowMessage("Obtaining rom index fails.");
                return;
            }   
             DL_Rom_SetEnableAttr(dl_handle, itemIndex, (_BOOL)(pItem->Checked?true:false));
	       LOGD("name(%s),itemIndex(%d), Enable(%d)", pItem->Caption.c_str(), itemIndex, pItem->Checked?true:false);
            #endif
	}

      DL_IndexOfChangedCheckBox = -1;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::action_ToggleSCIExecute(TObject *Sender)
{
    //Ctrl + Alt + L
    g_SCI_Mode = (!g_SCI_Mode);
    LOGD("g_SCI_Mode (%d)", g_SCI_Mode);

    if(!g_SCI_Mode)
    {
        ts_SCIDownload->TabVisible = g_SCI_Mode;
        ts_SCIClone->TabVisible = g_SCI_Mode;
    }
    else 
    {
        frm_encription->Visible = true;
    }  
}
//---------------------------------------------------------------------------

