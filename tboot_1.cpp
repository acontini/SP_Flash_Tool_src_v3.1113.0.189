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
*  tboot_1.cpp
*
* Project:
* --------
*  Flash tool set
*
* Description:
* ------------
*  a thread
*  1.write command to Boot ROM 
*  2.then jump to execute download agent
*
* Author:
* -------
*  FZ Hsu (mtk00303)
*
*==============================================================================
*           HISTORY
* Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
*------------------------------------------------------------------------------
* $Revision:   1.37  $
* $Modtime:   Jan 13 2006 21:45:40  $
* $Log:   //mtkvs01/vmdata/flash_tool/archives/tboot_1.cpp-arc  $
 *
 * Sep 8 2008 mtk01413
 * [STP100001809] [FlashTool] v3.0836.0 release
 * 
 *
 * Sep 4 2008 MTK01952
 * [STP100001792] [FlashTool] v3.0836
 * New feature:
 * 1. Enter META to Upload files
 *
 * Sep 1 2008 MTK01952
 * [STP100001792] [FlashTool] v3.0836
 * New feature:
 * 1. Add the upload files funcitonality 
 *
 * Aug 13 2008 MTK01952
 * [STP100001783] [FlashTool] v3.0832.0 release
 * 
 *
 * Aug 7 2008 MTK01952
 * [STP100001779] [FlashTool] v3.0828.00
 * New features:
 *  1. Add the backup and restore functinality 
 *
 * May 19 2008 MTK01952
 * [STP100001712] [FlashTool] GPS download Phase 2
 * 
 *
 * Mar 30 2008 MTK01952
 * [STP100001655] [FlashTool] v3.0808.0 DRAM Testing of Memory Test
 * 
 *
 * Mar 11 2008 MTK01952
 * [STP100001660] [BROM DLL] Enable DRAM restriction of MT6225
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
 * Enhancements:
 *  1. [FlashTool] Show Parameter List View automatically when loading secure-on MAUI
 *  2. [FlashTool] Move "Paremeter"/ "File Management"/ "ROM Writer" under "Window" menu item
 *  3. [FlashTool] Show DA version and Build Date in help dialog
 * 
 *
 * Sep 27 2006 mtk00539
 * [STP100001145] FlashTool v3.1.01 release
 * 
 *
 * Aug 17 2006 mtk00539
 * [STP100001057] FlashTool v3.1.00 release
 * Apply new read back FAT mechanism.
 *
 * Aug 16 2006 mtk00539
 * [STP100001057] FlashTool v3.1.00 release
 * Apply new auto format FAT mechanism.
 *
 * Aug 14 2006 mtk00539
 * [STP100001057] FlashTool v3.1.00 release
 * 
 *
 * Aug 11 2006 mtk01413
 * [STP100001053] FlashTool v2.9.1004 release
 * Bug fixes:
 *  1. [BROM_DLL] Fix Test DA download fail on MT6205/MT6205B.
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
 *  2. [FlashTool][BUG_FIX] Fix a bug to prevent Scroll back to Page1 when redrawing Test DA message.
 * 
 *
 * Mar 22 2006 mtk00539
 * [STP100000703] FlashTool v2.7.1017
 * [FlashTool] Use known BBCHIP_TYPE and EXT_CLOCK to increase start command hit rate in "Reset to Factory Default" procedure.
 * 
 *    Rev 1.37   Jan 14 2006 00:49:58   mtk00539
 * Bug fixes:
 *  1. [FlashTool] Fix scatter file path doesn't update on UI. 
 * 
 * Enhancements:
 *  1. [FlashTool] Record normal mode and test mode DA path separatedly.
 * Resolution for 159: [FlashTool v2.7.1015]
 * 
 *    Rev 1.36   Jan 04 2006 14:23:30   mtk00539
 *  1. [FlashTool] Fix NFI CS1 device takes no effect problem while selecting "enable NFI-CS1" flag.
 * Resolution for 158: [FlashTool v2.7.1014][New] Support Spansion MirrorBit Buffer-Program method.
 * 
 *    Rev 1.35   Dec 29 2005 10:57:26   mtk00539
 *  1. [FlashTool] Add download history feature.
 * Resolution for 156: [FlashTool v2.7.1013][BUG FIX] Fix BootROM start command failure while manually selecting NMT6226 or MT6227 baseband chip.
 * 
 *    Rev 1.34   Oct 19 2005 14:47:26   mtk00539
 *  1. [FlashTool][New] Adapt new BROM_DLL&DA v2.7.1008. 
 * Resolution for 141: [FlashTool v2.7.1008][New] Support NFB download and many new features.
 * 
 *    Rev 1.33   May 24 2005 20:03:42   mtk00539
 *  1. [FlashTool][New] Reset FAT to factory default setting. 
 *  2. [FlashTool][New] Option to enable/disable resource project id comparison. 
 * Resolution for 116: [FlashTool v2.6.1012][New] Reset FAT to factory default setting.
 * 
 *    Rev 1.32   Feb 16 2005 17:27:44   mtk00539
 *  1. [FlashTool][New] Adapt new BROM_DLL&DA v2.4.1009 to support SPANSION S71AL016D and SHARP LRS18C8A flash. 
 *  2. [FlashTool][Enhance] Allow to setup EMI setting in TestMode.
 *  3. [FlashTool][Enhance] Keep TestMode unless you disable it. In order to allow users to do test continuously.
 *  4. [FlashTool][Enhance] Add CTRL+S hot-key to save TestMode log into file.
 * Resolution for 106: [FlashTool v2.6.1009][New] Adapt new BROM_DLL&DA v2.4.1009 to support SPANSION S71AL016D and SHARP LRS18C8A flash.
 * 
 *    Rev 1.31   Nov 30 2004 14:22:42   mtk00539
 * Modify the skip auto-format warning message.
 * Resolution for 100: [FlashTool v2.6.1008][New] Adapt new BROM_DLL&DA v2.4.1008 to enable/disable speed-up baudrate in BootROM stage.
 * 
 *    Rev 1.30   Nov 25 2004 09:59:00   mtk00539
 * tboot_1::InitProgress() should not intialize g_ProgressTimeSec = 0 while bUpdateFinishBytes is false.
 * Resolution for 100: [FlashTool v2.6.1008][New] Adapt new BROM_DLL&DA v2.4.1008 to enable/disable speed-up baudrate in BootROM stage.
 * 
 *    Rev 1.29   Nov 22 2004 14:30:12   mtk00539
 *  1. [FlashTool][New] Adapt new BROM_DLL&DA v2.4.1008 to enable/disable speed-up baudrate in BootROM stage.
 * Resolution for 100: [FlashTool v2.6.1008][New] Adapt new BROM_DLL&DA v2.4.1008 to enable/disable speed-up baudrate in BootROM stage.
 * 
 *    Rev 1.28   Nov 05 2004 10:40:04   mtk00539
 *  1. [FlashTool][New] Adapt new BROM_DLL&DA v2.4.1007 to support S/W compatible mechanism for MT6218B_FN and MT6218B_GN and some enhancement.
 * Resolution for 97: [FlashTool v2.6.1007][New] Adapt new BROM_DLL&DA v2.4.1007 to support S/W compatible mechanism for MT6218B_FN and MT6218B_GN and some enhancement.
 * 
 *    Rev 1.27   Oct 29 2004 11:49:22   mtk00539
 *  1. [FlashTool][New] Adapt new BROM_DLL&DA v2.4.1006 to fix AM49DL3208GT & S71PL032J download fail problem and some enhancement.
 *  2. [FlashTool][New] Add auto-detect base band chip type flag.
 * Resolution for 1: META MAUI v1.0
 * 
 *    Rev 1.26   Sep 17 2004 17:04:08   mtk00539
 * process new error code FT_DA_HW_ERROR
 * Resolution for 91: [FlashTool v2.6.1005][New] Adapt new BROM_DLL&DA v2.4.1005 to fix MT6217 download fail problem.
 * 
 *    Rev 1.25   Aug 03 2004 22:42:28   mtk00539
 * remove unnecessar include files
 * 
 *    Rev 1.24   Aug 03 2004 15:07:06   mtk00539
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
 *    Rev 1.23   Jul 19 2004 11:13:26   mtk00539
 * add baudrate full sync count option
 * Resolution for 82: [FlashTool v2.6.1001][New] Adapt with BROM_DLL v2.4.1001 and many enhancement.
 *
 *    Rev 1.22   Jul 19 2004 02:10:56   mtk00539
 *  1. [FlashTool][New] Adapt new BROM_DLL v2.4.1001 for many features and bug fix.
 *  2. [FlashTool][Enhance] Export COM port read/write timeout setting.
 *  3. [FlashTool][Enhance] Change EMI setting to 32 bits.
 * Resolution for 82: [FlashTool v2.6.1001][New] Adapt with BROM_DLL v2.4.1001 and many enhancement.
 * 
 *    Rev 1.21   Jun 16 2004 16:38:12   mtk00539
 *  1. [FlashTool][Enhance] Re-org format option panel to prevent users confused.
 *  2. [FlashTool][Enhance] Do not close OK window when operation is done.
 * Resolution for 78: [FlashTool v2.5.1013][Enhance] Re-org format option panel to prevent users confused.
 * 
 *    Rev 1.20   May 26 2004 21:54:58   mtk00539
 * [FlashTool][New] Using BROM_DLL_v2.3.1005 new feature to add BootROM stage callback function to disable vibrator to avoid MT6218B series board layout issue.
 * Resolution for 74: [FlashTool v2.5.1011][New] Add new flag to pull down GPIO17.
 * 
 *    Rev 1.19   May 21 2004 15:54:54   mtk00539
 *  1. [FlashTool][BUF FIX] fix incorrect error message of resource detection.
 * Resolution for 71: [FlashTool v2.5.1010][BUF FIX] fix incorrect error message of resource detection.
 * 
 *    Rev 1.18   May 17 2004 12:58:14   mtk00539
 * [New] keep old interfaces of Boot_META, Boot_FlashTool & Brom_Verify 
 * Resolution for 69: [BootRom v2.3.1002][BUG FIX] fix RB_HANDLE deadlock.
 * 
 *    Rev 1.17   May 14 2004 17:04:22   mtk00539
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
 *    Rev 1.16   Mar 29 2004 14:20:16   mtk00539
 * [New] add baseband chip ECO revision checking flag for FlashDownload.
 * Resolution for 65: [FlashTool v2.5.1008][New] add baseband chip ECO revision checking flag for FlashDownload.
 * 
 *    Rev 1.15   Mar 12 2004 19:07:48   mtk00539
 * change log format
 * 
 *    Rev 1.14   Mar 09 2004 21:06:56   mtk00539
 * [Enhance] adapt new Boot_FlashTool interface.
 * 
 *    Rev 1.13   Mar 02 2004 00:28:20   mtk00539
 *  1. [FlashTool][Enhance] automatically select bbchip according to rom bbchip id..
 *  2. [FlashTool][Enhance] automatically load all the resource files.
 *  3. [FlashTool][Enhance] display resource and jump table information.
 *  4. [FlashTool][New] add MT6219 support.
 * Resolution for 54: [FlashTool v2.5.1006][Enhance] bbchip id detection and resource autoload.
 *
 *    Rev 1.12   Feb 05 2004 13:40:36   mtk00539
 * adapt to BROM DLL v2.2.1001
 * Resolution for 47: [FlashTool v2.5.1001][New] support multiple concatanated bin files download.
 * 
 *    Rev 1.11   Nov 14 2003 15:48:48   mtk00539
 * add SOC feature.
 * Resolution for 35: [BootRom v2.1.1005][New] Add SOC feature.
 * 
 *    Rev 1.10   Oct 18 2003 14:06:20   mtk00539
 * 1. modify for MT6218B boot rom verification.
 * 2. change version info.
 * Resolution for 31: [BootRom v2.1.1002][BUG FIX] Fix DA checksum error on Windows ME and 2000.
 *
 *    Rev 1.9   Sep 26 2003 11:37:16   mtk00539
 * check new return code
 * Resolution for 28: [BootRom v2.1.1001][New] See the reasons below.
 * Resolution for 29: [FlashTool v2.4.1001][New] See the reasons below.
 * 
 *    Rev 1.8   Sep 25 2003 14:03:28   mtk00539
 * adapt brom.dll v2.1.1001, please see SCR(29) for more details.
 * Resolution for 29: [FlashTool v2.4.1001][New] See the reasons below.
 * 
 *    Rev 1.7   Jul 09 2003 13:36:06   mtk00539
 * 1. reduce default timeout period and read/write incomplete retry times.
 * 2. increase version to 2.3.1002
 * Resolution for 14: [BootRom v2.0.1004] fine tune for high speed download card behavior.
 * 
 *    Rev 1.6   Jun 30 2003 19:19:36   mtk00539
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
 *    Rev 1.5   Jun 03 2003 22:24:56   mtk00539
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
 *    Rev 1.4   May 22 2003 19:23:58   mtk00539
 * support brom.lib v1.0.1010
 * Resolution for 6: [FlashTool v2.2][AddFeature] Support 6205/6205B at 13MHz, 26MHz and 52MHz.
 *
 *    Rev 1.3   May 20 2003 16:22:30   mtk00539
 * Support 6205/6205B at 13MHz, 26MHz and 52MHz
 * Resolution for 6: [FlashTool v2.2][AddFeature] Support 6205/6205B at 13MHz, 26MHz and 52MHz.
 *
 *    Rev 1.2   Nov 20 2002 19:52:58   mtk00303
 * update for reference phone
 * 
 *    Rev 1.1   Jul 26 2002 11:52:20   admin
 * ver 0726
 * 
 *    Rev 1.0   Jul 20 2002 19:26:16   admin
 * Initial revision.
*
*------------------------------------------------------------------------------
* Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
*==============================================================================
*******************************************************************************/

//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <algorithm>
#include <time.h>

#include "tboot_1.h"
#include "ext_mem1.h"
#include "main.h"
#include "ok_wnd.h"
#include "com_util.h"
#include "flashtool.h"
#include "DA_Option.h"
#include "WMMETA_Wrapper.h"
#include "SLA_Challenge.h"
#include "frm_Process.h"
#include "AndroidImageInfo.h"
#include "ImageMapRule.h"
#include "NvramBackupMap.h"
#include "Utility.h"
#include "GlobalData.h"
#include "ErrorLookup.h"
#include "FileUtils.h"
#include "FlashAllInOneAPIs.h"
#include "FlashToolErrorCodeDef.h"
#include "FlashToolUSB.h"
#include "CommandConnect.h"
#include "SharedPtr.h"
#include "HandleManager.h"
#include "NandLayoutParameter.h"
#include "AutoFormatArgFactory.h"
#include "SearchUSB.h"
#include "DownloadImageChecksum.h"
#include "version.h"
#include "command.h"
#include "FirmwareUpgradeConfig.h"
#include "CloneInfoHandle.h"
#include "CommandConfig.h"
#include "ReadbackSetting.h"
#include "WriteMemorySetting.h"

//test
#include "Command.h"

#pragma package(smart_init)
#pragma warn -8004

const int tboot_1::USB_SCAN_TIMEOUT(30);
const string tboot_1::MapFileName("backup.map");
const string tboot_1::DatFileName("backup.dat");
const string tboot_1::NvramName("NVRAM");
const string tboot_1::ProInfoName("__NODL_PRO_INFO");
const string tboot_1::BinRegionName("CUSTPACK3");
const string tboot_1::BootImgName("BOOTIMG");
const string tboot_1::kProductInfoName("PRO_INFO");
static const unsigned int BAUDRATE_TBL[] = { 0, 921600, 460800, 230400, 115200, 57600, 38400, 19200, 9600, 4800, 2400, 1200, 300, 110 };
const unsigned short kChipIDLength(16);
const unsigned int kRBPkgLen(131072); //128k = 128 * 1024
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall Unit4::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall tboot_1::tboot_1(bool CreateSuspended )
        : TThread(CreateSuspended)
{
    memset(&m_sIMEIdownload, 0, sizeof(m_sIMEIdownload));
    m_b2ndImeiSupport = false;
    m_bWriteIMEI2 = false;
    m_pModemDatabase = NULL;
    m_pApDatabase = NULL;
    m_pBTAddr = NULL;
    m_pWIFIAddr = NULL;
}
//---------------------------------------------------------------------------
__fastcall tboot_1::~tboot_1()
{
	if (MainForm->IsAutoPollingEnable() && (g_stopflag != BOOT_STOP)) {
		SendMessage(MainForm->Handle, AP_SPFT_DOWNLOAD_SUCCESSFUL, 0, 0);
	} else {
		PostMessage(MainForm->Handle, AP_SPFT_STOP, 0, 0);
	}
	g_stopflag = 0;
}
//---------------------------------------------------------------------------
void __fastcall tboot_1::ClearStatusBar()
{
	MainForm->HWStatusBarClear();
}
//---------------------------------------------------------------------------
void tboot_1::SyncInitProgress()
{
	Synchronize(InitProgress);
}

void __fastcall tboot_1::InitProgress()
{
	MainForm->CGauge1->Hint      = progress_hint;
	MainForm->CGauge1->ForeColor = progress_forecolor;
	MainForm->CGauge1->Progress  = progress_percentage;
	if ( bUpdateFinishBytes ) {
            g_ProgressTimeSec = 0;
	    MainForm->sb_Main->Panels->Items[0]->Text = IntToStr((__int64)progress_finished_bytes) + " Bytes / 0 Bps";
	}
	if (MainForm->IsAutoPollingEnable()) {
		AnsiString auto_polling_hint;
		auto_polling_hint.sprintf("Auto Polling On, Polling Count(%d)", MainForm->GetAutoPollingCount());
		MainForm->m_HWStatus->Panels->Items[2]->Text = auto_polling_hint;
	}
}
//---------------------------------------------------------------------------
void tboot_1::SyncUpdateProgress()
{
	Synchronize( UpdateProgress );
}
void __fastcall tboot_1::UpdateProgress()
{
	unsigned int    Bps;
	float           KBps;
	AnsiString      rate;

	MainForm->CGauge1->Progress = progress_percentage;
	MainForm->CGauge1->ForeColor = 	progress_forecolor;
	MainForm->CGauge1->Hint = progress_hint.c_str();
	MainForm->m_HWStatus->Panels->Items[2]->Text = speed_status.c_str();

	if( bUpdateFinishBytes ) {

		g_DisplayFinishedBytes = progress_finished_bytes;

		if( 0 >= g_ProgressTimeSec ) {
			rate = "0 Bps";
		}
		else if( 1024 < (Bps=progress_finished_bytes/g_ProgressTimeSec) ) {
			KBps = Bps;
			rate = FloatToStrF( KBps/1024, ffFixed, 7, 2) + " KBps";
		}
		else {
			rate = IntToStr(Bps) +  " Bps";
		}
	    MainForm->sb_Main->Panels->Items[0]->Text = IntToStr((__int64)progress_finished_bytes) + " Bytes / " + rate;
	}
}
//---------------------------------------------------------------------------
void tboot_1::SyncShowMsg()
{
    Synchronize( ShowMsg );
}
void __fastcall tboot_1::ShowMsg()
{
    ShowMessage( asMsg );

    // reset message string
    asMsg = "";
}
//---------------------------------------------------------------------------
void __fastcall tboot_1::ShowOK_Form()
{
	Form_OK->Visible = true;
	StopTimer();
}

//---------------------------------------------------------------------------
void __fastcall tboot_1::StartTimer()
{
	MainForm->Timer_Download->Enabled = true;
}

//---------------------------------------------------------------------------
void __fastcall tboot_1::StopTimer()
{
	MainForm->Timer_Download->Enabled = false;

    if ( frm_Processing->ModalResult == mrNone )
    {
        SendMessage(frm_Processing->Handle, AP_SPFT_META_EXIT, 0, 0);
    }
}

//---------------------------------------------------------------------------
void __fastcall tboot_1::StartUSBHintTimer()
{
    MainForm->m_2ndSiteUSBSecHint = USB_SCAN_TIMEOUT/2;
    MainForm->Timer_2ND_USB_Hint->Enabled = true;
}

//---------------------------------------------------------------------------
void __fastcall tboot_1::StopUSBHintTimer()
{
    MainForm->Timer_2ND_USB_Hint->Enabled = false;
    MainForm->sb_Main->Panels->Items[5]->Text = "";
}

//---------------------------------------------------------------------------
void __fastcall tboot_1::UpdateUSBVCOMInfo()
{
    const unsigned int com_num = GetUSBVCOMNumByPortName(m_strPort);
    AnsiString COM = "COM";
    if( 0 == com_num ) {
        //Searching USB VCOM
        MainForm->sb_Main->Panels->Items[2]->Text = "Searching";
    } else {    
        MainForm->sb_Main->Panels->Items[2]->Text = COM + NumberToString(com_num).c_str();
        LOGD(string("UpdateUSBVCOMInfo: USB Symbolic Name: ").append(m_strSymbolic).c_str());
		if(!m_strPort.empty()){
			MainForm->m_HWStatus->Panels->Items[3]->Text = m_strPort.c_str();    
        } else {            
            MainForm->m_HWStatus->Panels->Items[3]->Text = "";
        }
    }
}
//-----------------------------------------------------------------------------------------
void __fastcall tboot_1::StartChksumTimer()
{
	MainForm->Timer_Checksum->Enabled = true;
}

//---------------------------------------------------------------------------
void __fastcall tboot_1::StopChksumTimer()
{
	MainForm->Timer_Checksum->Enabled = false;    
}
static int __stdcall cb_checkusbstatus_init(void * arg, const char* usb_status);
static int __stdcall cb_checksum_init(void *usr_arg, const char* image_name);
static int __stdcall cb_checksum_progress(unsigned char finished_percentage, unsigned int finished_bytes, unsigned int total_bytes, void *usr_arg);
//-----------------------------------------------------------------------------------------
bool tboot_1::ChecksumBefDL()
{
      bool ret = true;

      if(FLASHTOOL_DOWNLOAD == g_flashtool_function ||
	   FLASHTOOL_FIRMWARE_UPGRADE == g_flashtool_function||
	   FLASHTOOL_SCI_WRITEMEMORY == g_flashtool_function)
      {	  
        //Check image buffer checksums
	std::string error_msg;
	DownloadImageChecksum dl_img_checksum;

       RomMemChecksumArg chksum_arg;
	RomMemChecksumResult chksum_res;

	memset(&chksum_arg, 0, sizeof(chksum_arg));
	memset(&chksum_res, 0, sizeof(chksum_res));

	chksum_arg.m_cb_rom_mem_checksum = cb_checksum_progress;
	chksum_arg.m_cb_rom_mem_checksum_init = cb_checksum_init;
	chksum_arg.m_cb_rom_mem_checksum_arg = this;
	chksum_arg.m_cb_rom_mem_checksum_init_arg = this;
	//chksum_arg.p_stopflag = &g_stopflag;
	
	if (dl_img_checksum.is_do_checksum() && dl_img_checksum.is_checksum_file_ready()) {
		if (!VerifyDLImagesBuffer(g_DL_HANDLE_NODE.m_dl_handle, error_msg, chksum_arg, chksum_res)) {
                     asMsg = error_msg.c_str();			
			Synchronize(ShowMsg);
			ret = false;
		}		
	}
	Synchronize(StopChksumTimer);
	MainForm->stHint->Visible = false;
      }  
      return ret;   
}
//-----------------------------------------------------------------------------------------
void __fastcall tboot_1::Execute()
{
    button_sentry s;

    if( g_stopflag == BOOT_STOP ) return;

    // reset error code mode
    ErrorLookup::SetErrorCodeMode(BROM);;
//    g_error_code_mode      = FLASHTOOL;  

    if(g_bDLCert)
    {
        LOGD("Enter Certification DL...");
        DLCertification();
    }
    else if(ChecksumBefDL())
    {         
          Synchronize(ClearStatusBar);

          progress_hint           = "";
          progress_forecolor      = clBlue;
          progress_percentage     = 0;
          progress_finished_bytes = 0;

          bUpdateFinishBytes      = true;
          SyncInitProgress();
	
        if( g_bDebugDA ) {
            DebugDA();
            // Memory Test cannot be operated automatically.
        }
       else {
           // flash download/ read back / format / memory test/ ...
           FlashTool();
        }
    }
 
    Terminate();
	//g_stopflag = 0;
    /*if ( this->Terminated)
    {
        return;
    }  */
}
/******************************************************************************/
/* FlashTool Modules                                                          */
/*                                                                            */
/*                                                                            */
/******************************************************************************/
//---------------------------------------------------------------------------
static int __stdcall cb_download_da_init(void *usr_arg);
static int __stdcall cb_download_da(unsigned char percent, unsigned int sent_bytes, unsigned int total_bytes, void *usr_arg);
static int __stdcall cb_download_flash_init(void *usr_arg);
static int __stdcall cb_download_flash(unsigned char percent, unsigned int  sent_bytes, unsigned int total_bytes, void *usr_arg);
static int __stdcall cb_download_bloader_init(void *usr_arg);
static int __stdcall cb_download_bloader(unsigned char percent, unsigned int sent_bytes, unsigned int total_bytes, void *usr_arg);
static int __stdcall cb_format_report_init(HW_StorageType_E storage_type, unsigned long long begin_addr, unsigned long long length, void *usr_arg);
static int __stdcall cb_format_report(unsigned char percent, void *usr_arg);
static int __stdcall cb_readback_flash_init(HW_StorageType_E  storage_type, unsigned long long rb_addr, unsigned int rb_length, const char *rb_filepath, void *usr_arg);
static int __stdcall cb_readback_flash(unsigned char percent, unsigned int sent_bytes, unsigned int  total_bytes, void *usr_arg);
static int __stdcall cb_da_report(const DA_REPORT_T  *p_da_report, void *usr_arg);
static int __stdcall cb_com_init_stage(HANDLE hCOM, void *usr_arg);
static int __stdcall cb_in_brom_stage(unsigned int brom_handle, HANDLE hCOM, void *usr_arg);
static int __stdcall cb_format_statistics(const FormatStatisticsReport_T  *p_report, void *usr_arg);
static int __stdcall cb_post_process_init(void *usr_arg);
static int __stdcall cb_post_process(unsigned char percent, void *usr_arg);
static int __stdcall cb_progress_init(void *usr_arg);
static int __stdcall cb_progress(unsigned char percent, unsigned int sent_bytes, unsigned int total_bytes, void *usr_arg);
static int __stdcall cb_security_pre_process_notify(void *usr_arg);
static int __stdcall cb_security_post_process_notify(void *usr_arg);
static int __stdcall cb_update_param_init(void *usr_arg);
static int __stdcall cb_update_param(unsigned char percent, void *usr_arg);
//---------------------------------------------------------------------------
void tboot_1::FlashTool()
{
	int ret = S_DONE; 

    ROM_INFO romInfo;
    bool bIsDADLImg;
    //bool bIsOperateNvram = (g_backup_restore_state == RESTORE_NVRAM_ONLY);
    bool bUSBBootRom = (g_platform_info.getPlatformConfig().supportUSBDownload()) &&
		( g_bDADownloadAll ||
		  (FLASHTOOL_FORMAT == g_flashtool_function) ||
		  (FLASHTOOL_READBACK == g_flashtool_function) ||
		  (FLASHTOOL_MEMORYTEST == g_flashtool_function)/*  ||
		  (BACKUP_FORMAT_DOWNLOAD_RESTORE == g_backup_restore_state)||
		  (FORMAT_DOWNLOAD_RESTORE_NVRAM == g_backup_restore_state)*/ );
    //USB BootRom DL DA Scenarios: Format/Download ALL/DA DL All/Readback/Memory Test
        if( bUSBBootRom ) {
        bIsDADLImg = true;
    }else{
        bIsDADLImg = (IsBLToBeDL(g_pCurNode->m_dl_handle) ||
		     IsCertToBeDL(g_AUTH_HANDLE) ||
		     IsSecurityToBeDL(g_SCERT_HANDLE));
    }
    
    LOG("tboot_1::FlashTool(): g_bUsbMode=%d, bIsDADLImg=%d",g_bUsbMode,bIsDADLImg/*,bIsOperateNvram*/);
    // if USB download/readback, com port auto-detection
    // if notify a new com port, then go on FlashTool functions
    if( g_bUsbMode && bIsDADLImg/* && !bIsOperateNvram*/)
    {
        Synchronize(UpdateUSBVCOMInfo);
		if (ScanUSBPort4DownloadDA(&g_stopflag, m_strSymbolic, m_strPort)) {
			LOGD("USB is found, port name(%s), symbolic name(%s).", m_strPort.c_str(), m_strSymbolic.c_str());
			Synchronize(UpdateUSBVCOMInfo);
		} else {
			LOGE("Search USB port failed!");
			goto tboot_end;
		}
    }
	LOG("tboot_1::FlashTool(): Platform(%s), DA Download All(%s).",
		g_platform_info.getLoadPlatformName().c_str(), g_bDADownloadAll ? "True" : "False");

//*** DOWNLOAD ===========================================================
    if( FLASHTOOL_DOWNLOAD == g_flashtool_function )
    {
        LOGD("Step: FLASHTOOL_DOWNLOAD.");		
        if( g_project_mode == DUMA)
        {
        	assert(0);
#if 0
        	LOGD("Step: FLASHTOOL_DOWNLOAD, DUMA.");
            // backup -> format -> download -> restore
            if ( g_backup_restore_state == BACKUP_FORMAT_DOWNLOAD_RESTORE )
            {
            	LOGD("Step: FLASHTOOL_DOWNLOAD, DUMA, BACKUP_FORMAT_DOWNLOAD_RESTORE.");
                assert(0);
                //ret = DownloadRestore();
                //if( S_DONE != ret ) goto tboot_end;
            }
            // write IMEI/BT/WiFi
            else if ( g_nvram_update_state == UPDATENVRAM )
            {
            	LOGD("Step: FLASHTOOL_DOWNLOAD, DUMA, UPDATE IMEI/BT/WiFi.");
                ret = DownloadFourInOne();
                if( S_DONE != ret ) goto tboot_end;
            }
            else if ( FORMAT_DL_UPDATENVRAM == g_nvram_update_state )
            {
            	LOGD("Step: FLASHTOOL_DOWNLOAD, DUMA, Format ->UPDATE IMEI/BT/WiFi.");
                ret = FormatDownloadFourInOne();
                if( S_DONE != ret ) goto tboot_end;
            }
            // basic download
            else
            {
            	LOGD("Step: FLASHTOOL_DOWNLOAD, DUMA, DOWNLOAD ONLY.");
                ret = Download();
                if( S_DONE != ret ) goto tboot_end;
            }
#endif
         }
         else if( g_project_mode == YuSu)
            {
        	 LOGD("Step: FLASHTOOL_DOWNLOAD, YuSu.");
                if ( g_nvram_update_state == UPDATENVRAM )
                {
                	LOGD("Step: FLASHTOOL_DOWNLOAD, YuSu, UPDATE IMEI/BT/WiFi.");
                    ret = DownloadYuSuFourInOne();
                    if( S_DONE != ret ) goto tboot_end;
                }
                else if ( FORMAT_DL_UPDATENVRAM == g_nvram_update_state )
                {
                	LOGD("Step: FLASHTOOL_DOWNLOAD, YuSu, Format ->UPDATE IMEI/BT/WiFi.");
                    ret = FormatDownloadYuSuFourInOne();
                    if( S_DONE != ret ) goto tboot_end;
                }
#if 0
                else if ( g_backup_restore_state == BACKUP_FORMAT_DOWNLOAD_RESTORE )
                {
					if ( g_bDADownloadAll ) {
						LOGD("Step: FLASHTOOL_DOWNLOAD, YuSu, DA DL ALL, BACKUP_FORMAT_DOWNLOAD_RESTORE_NVRAM.");
						ret = DABackupFormatDownloadRestore();
					} else {
                	LOGD("Step: FLASHTOOL_DOWNLOAD, YuSu, BACKUP_FORMAT_DOWNLOAD_RESTORE.");
                    //ret = DownloadYuSuRestore();
                    //ret = BackupFormatDownloadYuSuRestore();
                    ret = BackupFormatDownloadYuSuRestoreDLMode();
					}
                    if( S_DONE != ret ) goto tboot_end;
                }
#endif
#if 0                
				else if( g_backup_restore_state == FORMAT_DOWNLOAD_RESTORE_NVRAM)
                {
                    LOGD("Step: FLASHTOOL_DOWNLOAD, YuSu, FORMAT_DOWNLOAD_RESTORE_NVRAM.");
                    //TODO
                    //ret = FormatDownloadRestoreYuSu();
                    ret = FormatDownloadRestoreYuSuUnderDLMode();
                    if( S_DONE != ret ) goto tboot_end;
                }

                else if( g_backup_restore_state == RESTORE_NVRAM_ONLY)
                {
                    LOGD("Step: FLASHTOOL_DOWNLOAD, YuSu, RESTORE_NVRAM_ONLY.");
                    //TODO
                    //ret = RestoreOnlyYuSu();
                    ret = RestoreOnlyYuSuUnderDLMode();
                    if( S_DONE != ret ) goto tboot_end;
                }
#endif

                else if ( FLASHTOOL_DOWNLOAD == g_flashtool_function )
                {
                    if(g_bDADownloadAll){
                        LOGD("Step: FLASHTOOL_DOWNLOAD, YuSu, DA download all.");
                        ret = DownloadYuSu_ByDA();
                    }else{
                         //now only basic download
                	    LOGD("Step: FLASHTOOL_DOWNLOAD, YuSu, DOWNLOAD ONLY.");
                        ret = DownloadYuSu();
                    }
                    if( S_DONE != ret ) goto tboot_end;
                }                           
            }

    }
//*** Firmware upgrade ===================================================
	else if ( FLASHTOOL_FIRMWARE_UPGRADE == g_flashtool_function ) {
		if ( g_bDADownloadAll ) {
			LOGD("Step: FLASHTOOL_DOWNLOAD, YuSu, DA DL ALL, FIRMWARE UPGRADE.");
			ret = DABackupFormatDownloadRestore();
		} else {
    	LOGD("Step: FLASHTOOL_DOWNLOAD, YuSu, FIRMWARE UPGRADE.");
        //ret = DownloadYuSuRestore();
        //ret = BackupFormatDownloadYuSuRestore();
        ret = BackupFormatDownloadYuSuRestoreDLMode();
		}
        if( S_DONE != ret ) goto tboot_end;
	}
//*** READBACK ===========================================================
    else if( FLASHTOOL_READBACK == g_flashtool_function )
    {
        // fill the flash readback argurment
//        ArgFlashReadback();
        // call flash read back api
        LOGD("Step: FLASHTOOL_READBACK.");
        if (!g_bUsbDLDA) {
	//		ret = FlashReadback(&com, &arg, &result, &rb_arg, &rb_result,NULL, &g_stopflag);
			ret = FlashReadback_internal();
			if( S_DONE != ret ) goto tboot_end;
		} else {
            LOGD("Step: FLASHTOOL_READBACK, YuSu, USB_DOWNLOAD_DA.");
            ret = DownloadDAViaUSB();
            if( S_DONE != ret ) goto tboot_end;

            // fill the flash readback argurment
            ArgFlashReadback();
            ErrorLookup::SetErrorCodeMode(BROM);;
            Logger::GetLogger().Log(Logger::Debug,
            		"SkipBootRom: %d, DA_Handle is: %s, USB VCOM Num is: %d",
            		g_bSkipBootRom, arg.m_boot_arg.m_da_handle, com.com.number);
            // call flash usb read back api
		    ret = NandUtil_FlashReadback(&com, &arg, &result, &rb_arg, &rb_result, &g_stopflag);
            if( S_DONE != ret ) goto tboot_end;		
		}
    }

//*** Read Software Version =====================================================
	else if( FLASHTOOL_READ_SW_VERSION == g_flashtool_function ) {
		LOG("Step: FLASHTOOL_READ_SW_VERSION.");
		ret = FlashToolReadSWVersion();
		if( S_DONE != ret ) goto tboot_end;
	}

//*** Read Product Information ===================================================
	else if( FLASHTOOL_READ_PRODUCT_INFO == g_flashtool_function ) {
		LOG("Step: FLASHTOOL_READ_PRODUCT_INFO.");
		ret = FlashToolReadProductInfo();
		if( S_DONE != ret ) goto tboot_end;
	}

//*** FORMAT =============================================================
    else if( FLASHTOOL_FORMAT == g_flashtool_function )
    {
        LOGD("Step: FLASHTOOL_FORMAT.");
        // basic format
        if (MANUAL_FORMAT == g_FormatOption)
        {
	        if(g_bUsbDLDA){
	            LOGD("Step: MANUAL_FORMAT, YuSu, USB_DOWNLOAD_DA.");
		        ret = DownloadDAViaUSB();
		        if( S_DONE != ret ) goto tboot_end;			
	        }
            LOGD("Step: FLASHTOOL_FORMAT, MANUAL_FORMAT.");
            //ret = Format();
            ret = FlashFormat_internal();
            if( S_DONE != ret ) goto tboot_end;
        }
        // auto format
        else if (AUTO_FORMAT == g_FormatOption)
        {
 	        if(g_bUsbDLDA){
	            LOGD("Step: MANUAL_FORMAT, YuSu, USB_DOWNLOAD_DA.");
		        ret = DownloadDAViaUSB();
		        if( S_DONE != ret ) goto tboot_end;			
	        }           
            LOGD("Step: FLASHTOOL_FORMAT, AUTO_FORMAT.");
            ret = Auto_Format_Without_WatchDog();
            if( S_DONE != ret ) goto tboot_end;            
        }
#if 0
        else if (FORMAT_DOWNLOAD == g_FormatOption)
        {
            if( DUMA == g_project_mode)
            {
                ret = Auto_Format_With_WatchDog();
                if( S_DONE != ret ) goto tboot_end;
                LOGD("Step: FLASHTOOL_FORMAT, DUMA, FORMAT_DOWNLOAD.");
                ret = Download();
                if( S_DONE != ret ) goto tboot_end;
            }
            else
            {
            	if(g_bDADownloadAll){
            		LOGD("Step: FLASHTOOL_FORMAT, YUSU, FORMAT_DOWNLOAD ALL BY DA.");
            		ret = FormatDownloadYuSu_ByDA();
            	}else{
					LOGD("Step: FLASHTOOL_FORMAT, YUSU, FORMAT_DOWNLOAD.");
					ret = FormatDownloadYuSu();
            	}
                if( S_DONE != ret ) goto tboot_end;
            }
			DownloadImageChecksum dl_img_checksum;
			if (dl_img_checksum.is_do_checksum()) {
				std::string error_msg;
				if (!VerifyDLImagesBuffer(g_DL_HANDLE_NODE.m_dl_handle, error_msg)) {
					LOG("ERROR: %s(): %s.", __FUNC__, error_msg.c_str());
					if( S_DONE != ret ) goto tboot_end;
                }
			}
        }
#endif
    }

//*** MEMORYTEST============================================================
    else if( FLASHTOOL_MEMORYTEST == g_flashtool_function )
    {
        LOGD("Step: FLASHTOOL_MEMORYTEST.");
        ret = MemoryTest();
        if( S_DONE != ret ) goto tboot_end;
    }
    
//*** PARAMETER============================================================
    else if( FLASHTOOL_PARAMETER == g_flashtool_function )
    {
    	LOGD("Step: FLASHTOOL_PARAMETER.");

        if ( PAPAM_SEC_ROM_LOCK == g_ParameterType)
        {
        	LOGD("Step: FLASHTOOL_PARAMETER, SECURITY LOCK IMAGE.");
            ret = ParameterSecRomLock();
            if( S_DONE != ret ) goto tboot_end;
        }
        else if ( PARAM_OTP == g_ParameterType )
        {
        	LOGD("Step: FLASHTOOL_PARAMETER, OTP.");
            if (!g_bUsbDLDA)
            {
            	LOGD("Step: FLASHTOOL_PARAMETER, PARAMETER UPDATE VIA UART.");
                //ret = FlashToolOTP();
                ret = Parameter();
                if( S_DONE != ret ) goto tboot_end;
            }
            else
            {
            	LOGD("Step: FLASHTOOL_PARAMETER, YuSu, USB_DOWNLOAD_DA.");
                ret = DownloadDAViaUSB();
                if( S_DONE != ret ) goto tboot_end;

                ErrorLookup::SetErrorCodeMode(BROM);;
//                g_error_code_mode = FLASHTOOL;
                LOGD("Step: FLASHTOOL_PARAMETER, OTP UPDATE VIA USB.");
                ret = FlashToolOTP();
                //ret = Parameter();
                if( S_DONE != ret ) goto tboot_end;
            }

        }    
    }

//*** FLASHTOOL API TEST ==================================================
    else if( FLASHTOOL_API == g_flashtool_function )
    {
    	LOGD("Step: FLASHTOOL_API.");
    	assert(0); //not supported
//        ret = FlashToolAPITest ();
//        if( S_DONE != ret ) goto tboot_end;
    }

//*** ROMWRITER ===========================================================
    else if( FLASHTOOL_ROMWRITER == g_flashtool_function )
    {
    	LOGD("Step: FLASHTOOL_ROMWRITER.");
    	assert(0);//not supported
//        ret = RomWriter();
//        if( S_DONE != ret ) goto tboot_end;

    }

//*** DL Flash.bin ===========================================================
    else if( FLASHTOOL_FLASHBIN == g_flashtool_function )
    {
    	LOGD("Step: FLASHTOOL_FLASHBIN.");
    	assert(0);//not supported
//        ret = DLFlashBin();
//        if( S_DONE != ret ) goto tboot_end;
    }

//*** Write raw data to memory ===========================================================
	else if( FLASHTOOL_WRITEMEMORY == g_flashtool_function )
	{
		LOGD("Step: FLASHTOOL_WRITEMEMORY.");

		ret = WriteMemory();
		if( S_DONE != ret ) goto tboot_end;
	}
//***SCI Clone =============================================================
       else if(FLASHTOOL_SCI_READBACK == g_flashtool_function)
       {
              LOGD("Step: FLASHTOOL_SCI_READBACK.");

		ret = SCIReadback();
		if(S_DONE != ret) goto tboot_end;
	}
	else if(FLASHTOOL_SCI_WRITEMEMORY == g_flashtool_function)
	{
              LOGD("Step: FLASHTOOL_SCI_WRITEMEMORY.");

		ret = SCIWriteMemory();
		if(S_DONE != ret) goto tboot_end;
	}

//***SCI Download ===========================================================
	else if(FLASHTOOL_SCI_DOWNLOAD == g_flashtool_function)
	{
              LOGD("Step: FLASHTOOL_SCI_DOWNLOAD.");

		ret = SCIDownload();
		if(S_DONE != ret) goto tboot_end;
	}
//***FLASHTOOL_DONE========================================================
tboot_end:

    // stop timer
    Synchronize( StopTimer );
    //Synchronize ( ResetProgressBar );
    // check the stop flag and do not go show the final message
	if( BOOT_STOP == g_stopflag ) return;

    // show flash tool final Result
    if (ALL_IMG_LOCKED != g_ParamImageLockAll )
    {
        ShowFlashToolFinalResult ( ret );
    }
    g_ParamImageLockAll = NONE_IMG_LOCKED;

}
//---------------------------------------------------------------------------
void __fastcall tboot_1::ResetProgressBar()
{
    MainForm->CGauge1->Progress  = 0;
}
//---------------------------------------------------------------------------
void tboot_1::ShowFlashToolFinalResult( int ret )
{

    if ( S_DONE == ret ) {  // ok case
        // show OK form
		if (!MainForm->IsAutoPollingEnable()) {
			Synchronize( ShowOK_Form );
		}

    } else {
    	if(ErrorLookup::GetErrorCodeMode() != META){
    	asMsg = ErrorLookup::GetErrorMessage(ret,
				result.m_da_report.m_msp_err_code, com.baudrate).c_str();
    	}else{
    		//For META errors, we need update asMsg manually
    		asMsg = AnsiString(ErrorLookup::GetErrorMessage(ret,
					result.m_da_report.m_msp_err_code, com.baudrate).c_str())
					+ "\r\n" + asMsg;
    	}
		Synchronize( ShowMsg);
    }
}
//---------------------------------------------------------------------------
int tboot_1::Download( void )
{
	assert(0);
    int ret;
#if 0
    // fill flash download argument
    ArgFlashDownload();

    // call flash download api
    ret = FlashDownload( &com, &arg, &result, &dl_arg, &dl_result, NULL,&g_stopflag );
    if ( S_DONE != ret ) return ret;


    // GPS download relay mode
    if(  g_DL_HANDLE_NODE.m_param.m_gps_enable )
    {
        if ( g_bUsbDLRB )
        {
            asMsg = " GPS Download was forbidden by USB!! \n Please use the UART cable to download 'GPS ROM'. ";
            return -1;
        }

        ErrorLookup::SetErrorCodeMode(GPS);
//        g_error_code_mode = GPS;
        ret = GPSDownload();
        if ( S_DONE != ret ) return ret;
    }

    // enter meta mode to reset the FAT area to factory default
    if( RESET_TO_FACTORY == g_FormatAfterDownloadOption )
    {
        // can not USB cable to enter META Mode
        if ( g_bUsbDLRB )
        {
            asMsg = " THE FAT WAS NOT FORMAT!! Please use the UART cable and \n select the format option as the reset to factory default\n to reset the FAT area to factory default. ";
            return -1;
        }

        // when download the GPS ROM, since DA will entert the relay mode, and lose the control
        // use the fomat option to reset to factory default
        if( g_DL_HANDLE_NODE.m_param.m_gps_enable )
        {
            asMsg = " Please press Format and Select 'Reset to Factroy Deafault'. ";
            return -1;
        }

        ErrorLookup::SetErrorCodeMode(META);
//        g_error_code_mode = META;
        ret = EnterMETAResetFactoryDefault( );
        if( META_SUCCESS != ret ) return ret;
    }
 
    ret = DLFlashBin();
#endif
    //return S_DONE;
    return ret;
}

//---------------------------------------------------------------------------
int tboot_1::DownloadDAViaUSB( void )
{
    EBOOT_RESULT ret;
    Android_Boot_ARG boot_arg;
    DA_Download_ARG da_dl_arg;
    time_t   start, finish;
    string s_symbolic_str;
    string s_port_str;

	ErrorLookup::SetErrorCodeMode(FLASHTOOL);
    //Scan exist com port
    m_strSymbolicName.erase(m_strSymbolicName.begin(), m_strSymbolicName.end());
    m_strSymbolicName.begin();
	FlashToolUSBTable usb_table = GetFlashToolUSBTable();
	FlashToolUSB usb_preloader;
	if ( !usb_table.QueryUSBItemByName(FlashToolUSB::PRELOADER_VCOM, usb_preloader) ) {
		LOG("ERROR: tboot_1::DownloadDAViaUSB(): QueryUSBItemByName(): (%s) failed!",
			FlashToolUSB::PRELOADER_VCOM.c_str());
	} else {
		LOG("tboot_1::DownloadDAViaUSB(): QueryUSBItemByName(): Name(%s), PID(%s), VID(%s)",
			usb_preloader.GetUSBName().c_str(),
			usb_preloader.GetUSBPID().c_str(),
			usb_preloader.GetUSBVID().c_str());
	}
    LOGD("Double scan: Begin first scan USB VCOM port!");
    ScanExistUSBVComPort(m_strSymbolicName, m_strPortName,
		usb_preloader.GetUSBPID(), usb_preloader.GetUSBVID());
    LOGD("Double scan: Begin second scan USB VCOM port!");

    //Get start time
    time(&start);
    Synchronize(StartUSBHintTimer);
    do
    {
        if(BOOT_STOP == g_stopflag)
        {
        	LOGD("YuSu: User press stop button !");
            return FT_USER_PRESS_STOP_BUTTON;
        }
		else if( GetNewCreatedUSBVComPort(s_symbolic_str, 
			s_port_str, 	
			m_strSymbolicName,
			usb_preloader.GetUSBPID(),
			usb_preloader.GetUSBVID()))
        {
            //find usb_com port via MS DDK
            m_strPort =  s_port_str;
            Synchronize(StopUSBHintTimer);
            Synchronize(UpdateUSBVCOMInfo);

            Logger::GetLogger().Log(Logger::Debug,
            		"Double scan: Find usb port, symblic name is %s, friendly name is %s.(%s,%d)",
            		s_symbolic_str.c_str(), s_port_str.c_str(), __FILE__, __LINE__);
            break;
        }
        //Get current time
        time( &finish );

        if(difftime( finish, start) > 5)
        {
           Synchronize(StopUSBHintTimer);
           //SPFT_TRACE("Double scan: time out 5s passed, miss the chance to insert USB cable!", __FILE__, __LINE__);
        }

        //wait 15s if there still not found a new usb com port
        if( difftime ( finish, start ) > 15 )
        {
            LOGD("Double scan: time out passed, search usb port error!");
            return FT_FIND_USB_ERROR;
        }
    } while(1);
    ErrorLookup::SetErrorCodeMode(EBOOT);

    // fill flash download argument
    DA_PARSE_INFO da_parse_info;
    memset(&da_parse_info, 0, sizeof(da_parse_info));
    ArgFlashToolDLDA( boot_arg, da_dl_arg, s_symbolic_str, da_parse_info);

    LOGD(string("Number of DA region is").append(NumberToString(da_dl_arg.m_DA_info.count)).c_str());
    LOGD(string("Jump addr of DA region is ").append(NumberToString(da_dl_arg.m_DA_info.jump_addr)).c_str());

    for(unsigned short i = 0; i < da_dl_arg.m_DA_info.count; i++)
    {
        Logger::GetLogger().Log(Logger::Debug,
        		"DA_PARSE_INFO_REGION: start_addr is %x\n"
        		"DA_PARSE_INFO_REGION: buf is %x\n"
        		"DA_PARSE_INFO_REGION: buf_len is %d\n"
        		"(%s, %d)",
        		da_dl_arg.m_DA_info.da_region_list[i].start_addr,
        		da_dl_arg.m_DA_info.da_region_list[i].buffer,
        		da_dl_arg.m_DA_info.da_region_list[i].buffer_len,
        		__FILE__, __LINE__);
    }

    DA_INFO nandUtilInfo;
    DA_GetInfo(g_NAND_UTIL_DA_HANDLE, &nandUtilInfo);
    da_dl_arg.m_DA_path =  nandUtilInfo.filepath;

    LOGD(string("NandUtil path is: ").append(da_dl_arg.m_DA_path).c_str());
    LOGD(string("NandUtil is verified: ").append(da_dl_arg.is_DA_verify ? "Yes" : "No").c_str());

    ret = Android_DA_Download(boot_arg, &da_dl_arg);

    
    if(EBOOT_SUCCESS != ret)
    {
        if ( ret == S_DONE)
        {
            return -1;
        }
        else
        {
            return ret;
        }
    }

    //return S_DONE;
    return S_DONE;
}
int tboot_1::DownloadYuSu( void )
{
    int ret;
    bool is_need_dl_uboot, is_need_dl_image;
    ErrorLookup::SetErrorCodeMode(BROM);;
    
    // fill flash download argument
//    ArgFlashDownload();

    if(g_platform_info.getPlatformConfig().supportDADownloadAll()){
		
        ret = FlashDownload_internal();
        if ( S_DONE != ret )
        {
            Restore_Rom_File();
            return ret;
        }

         return S_DONE;
    }
    //Remove all other rom file untill UBOOT
    Remove_Other_Rom_File(is_need_dl_uboot, is_need_dl_image);

    LOG("tboot_1::DownloadYuSu(): DL BootLoader: %s, DL Android images: %s",
        (is_need_dl_uboot ? "Yes" : "No"),
        (is_need_dl_image ? "Yes" : "No"));

    // call flash download api
    if(is_need_dl_uboot)
    {
        // if we need'nt dl uboot, then we can skip it
//        ret = FlashDownload( &com, &arg, &result, &dl_arg, &dl_result, NULL,&g_stopflag );
    	ret = FlashDownload_internal();
        if ( S_DONE != ret )
        {
            Restore_Rom_File();
            return ret;
        }
    }

    if(is_need_dl_image)
    {
        //Scan exist com port
        m_strSymbolicName.erase(m_strSymbolicName.begin(), m_strSymbolicName.end());
        m_strSymbolicName.begin();
		FlashToolUSBTable usb_table = GetFlashToolUSBTable();
		FlashToolUSB usb_preloader;
		if ( !usb_table.QueryUSBItemByName(FlashToolUSB::PRELOADER_VCOM, usb_preloader) ) {
			LOG("ERROR: tboot_1::DownloadYuSu(): QueryUSBItemByName(): (%s) failed!",
				FlashToolUSB::PRELOADER_VCOM.c_str());
		} else {
			LOG("tboot_1::DownloadYuSu(): QueryUSBItemByName(): Name(%s), PID(%s), VID(%s)",
				usb_preloader.GetUSBName().c_str(),
				usb_preloader.GetUSBPID().c_str(),
				usb_preloader.GetUSBVID().c_str());
		}
        LOGD("Double scan: Begin first scan USB VCOM port!");
		ScanExistUSBVComPort(m_strSymbolicName, m_strPortName, 
			usb_preloader.GetUSBPID(), usb_preloader.GetUSBVID());

        Restore_Rom_File();

        ret = Download_Android_Images();
        if(EBOOT_SUCCESS != ret){
           return ret;
        } else {
           return S_DONE;
        }
    }

     if((is_need_dl_uboot==false) && (is_need_dl_image==false))
    {
        // if we need'nt download anyting , it will return flashtool list empty error
//        ret = FlashDownload( &com, &arg, &result, &dl_arg, &dl_result, NULL,&g_stopflag );
		LOG("ERROR: None images is to be downloadeded!");
        ret = FlashDownload_internal();
        if ( S_DONE != ret ){
            return ret;
            }
    }
      
    return S_DONE;
}

//---------------------------------------------------------------------------
int tboot_1::FormatDownloadYuSu( void )
{
    int ret;
    bool is_need_dl_uboot, is_need_dl_image;

    ErrorLookup::SetErrorCodeMode(BROM);;

    //Auto format without disconnect to execute download with FlashToolDownload api
	ret = Auto_Format_Without_Disconnect(); 
	if ( S_DONE != ret) {
		return ret;	    
	}

    FlashTool_Download_Arg fdl_arg;
    FlashTool_Download_Result fdl_res;
    
    ArgFlashToolAdvancedDownload(fdl_arg, fdl_res);
 
    //Remove all other rom file untill UBOOT
    Remove_Other_Rom_File(is_need_dl_uboot, is_need_dl_image);

    // call flash download api
    if(is_need_dl_uboot)
    {
        // if we need'nt dl uboot, then we can skip it
        ret = FlashTool_Download(g_ft_handle, &fdl_arg, &fdl_res);
        if ( S_DONE != ret ) {
            FlashTool_Disconnect(&g_ft_handle);
            LOGD("FormatDownloadYuSu: FlashTool_Download fail!");
            Restore_Rom_File();
            return ret;
        }

		if ( g_platform_info.getPlatformConfig().doesUSBDLControlBit() ) {
			ret = FlashTool_WriteUSBDownloadControlBit(g_ft_handle);
			if ( S_DONE != ret ) {
				FlashTool_Disconnect(&g_ft_handle);
				LOGD("ERROR: FormatDownloadYuSu: FlashTool_WriteUSBDownloadControlBit fail!");
				return ret;
			}	    
		}
		if(!ToolInfo::IsCustomerVer()) {
			FlashTool_EnableWDT_Arg wdt_arg;
			FlashTool_EnableWDT_Arg *p_wdt_arg = &wdt_arg;
			ArgFlashToolWatchDog(p_wdt_arg);
			ret = FlashTool_EnableWatchDogTimeout(g_ft_handle, p_wdt_arg);
			if(S_DONE != ret) {
				FlashTool_Disconnect(&g_ft_handle);
				LOGD("FormatDownloadYuSu: FlashTool_EnableWatchDogTimeout fail!");
				Restore_Rom_File();
    			return ret;
			}
		}
        ret = FlashTool_Disconnect(&g_ft_handle);
        if(S_DONE != ret) {
            LOGD("FormatDownloadYuSu: FlashTool_Disconnect fail!");
            Restore_Rom_File();
    	    return ret;
        }
    }

    if(is_need_dl_image)
    {
        //Scan exist com port
        m_strSymbolicName.erase(m_strSymbolicName.begin(), m_strSymbolicName.end());
        m_strSymbolicName.begin();
		FlashToolUSBTable usb_table = GetFlashToolUSBTable();
		FlashToolUSB usb_preloader;
		if ( !usb_table.QueryUSBItemByName(FlashToolUSB::PRELOADER_VCOM, usb_preloader) ) {
			LOG("ERROR: tboot_1::FormatDownloadYuSu(): QueryUSBItemByName(): (%s) failed!",
				FlashToolUSB::PRELOADER_VCOM.c_str());
		} else {
			LOG("tboot_1::FormatDownloadYuSu(): QueryUSBItemByName(): Name(%s), PID(%s), VID(%s)",
				usb_preloader.GetUSBName().c_str(),
				usb_preloader.GetUSBPID().c_str(),
				usb_preloader.GetUSBVID().c_str());
		}
        LOGD("Double scan: Begin first scan USB VCOM port!");
        ScanExistUSBVComPort(m_strSymbolicName, m_strPortName, 
			usb_preloader.GetUSBPID(), usb_preloader.GetUSBVID());

        Restore_Rom_File();

        ret = Download_Android_Images();
        if(EBOOT_SUCCESS != ret){
            if ( ret == S_DONE){
                return -1;
            } else {
                return ret;
            }
        }
    }

     if((is_need_dl_uboot==false) && (is_need_dl_image==false)) {
        // if we need'nt download anyting , it will return flashtool list empty error
        ret = FlashTool_Disconnect(&g_ft_handle);
        if(S_DONE != ret) {
            Restore_Rom_File();
    	    return ret;
        }
    }
      
    //return S_DONE;
    return S_DONE;
}
#if 0
//---------------------------------------------------------------------------
int tboot_1::FormatDownloadYuSuByAdv(  const Android_Image_File& img_file , const bool isDynamicLayout )
{
    int ret;
    bool is_need_dl_uboot, is_need_dl_image;

    ErrorLookup::SetErrorCodeMode(BROM);;

    //Auto format without disconnect to execute download with FlashToolDownload api
    FlashTool_Format_Arg       fmt_arg;
    FlashTool_Format_Result    fmt_res;
    
    ret = ArgFlashToolAdvancedFormat(fmt_arg, fmt_res, cn_result, false, isDynamicLayout);
    if(S_DONE != ret) {
        FlashTool_Disconnect(&g_ft_handle);
        return ret;
    }
 
    ret = FlashTool_Format(g_ft_handle,
                     &fmt_arg, &fmt_res);
    if(S_DONE != ret) {
        FlashTool_Disconnect(&g_ft_handle);
    }

    FlashTool_Download_Arg fdl_arg;
    FlashTool_Download_Result fdl_res;
    
    ArgFlashToolAdvancedDownload(fdl_arg, fdl_res);

    //Remove all other rom file untill UBOOT
    Remove_Other_Rom_File(is_need_dl_uboot, is_need_dl_image);

    // call flash download api
    if(is_need_dl_uboot)
    {
        // if we need'nt dl uboot, then we can skip it
        ret = FlashTool_Download(g_ft_handle, &fdl_arg, &fdl_res);
        if ( S_DONE != ret ) {
            FlashTool_Disconnect(&g_ft_handle);
            LOGD("FormatDownloadYuSuByAdv: FlashTool_Download fail!");
            Restore_Rom_File();
            return ret;
        }
        ret = FlashTool_EnableWatchDogTimeout(g_ft_handle, 5000);
        if(S_DONE != ret) {
            FlashTool_Disconnect(&g_ft_handle);
            LOGD("FormatDownloadYuSuByAdv: FlashTool_EnableWatchDogTimeout fail!");
            Restore_Rom_File();
    	    return ret;
        }        
        ret = FlashTool_Disconnect(&g_ft_handle);
        if(S_DONE != ret) {
            LOGD("FormatDownloadYuSuByAdv: FlashTool_Disconnect fail!");
            Restore_Rom_File();
    	    return ret;
        }
    }

    if(is_need_dl_image)
    {
        //Scan exist com port
        m_strSymbolicName.erase(m_strSymbolicName.begin(), m_strSymbolicName.end());
        m_strSymbolicName.begin();
		FlashToolUSBTable usb_table = GetFlashToolUSBTable();
		FlashToolUSB usb_preloader;
		if ( !usb_table.QueryUSBItemByName(FlashToolUSB::PRELOADER_VCOM, usb_preloader) ) {
			LOG("ERROR: tboot_1::FormatDownloadYuSuByAdv(): QueryUSBItemByName(): (%s) failed!",
				FlashToolUSB::PRELOADER_VCOM.c_str());
		} else {
			LOG("tboot_1::FormatDownloadYuSuByAdv(): QueryUSBItemByName(): Name(%s), PID(%s), VID(%s)",
				usb_preloader.GetUSBName().c_str(),
				usb_preloader.GetUSBPID().c_str(),
				usb_preloader.GetUSBVID().c_str());
		}
        LOGD("Double scan: Begin first scan USB VCOM port!");
        ScanExistUSBVComPort(m_strSymbolicName, m_strPortName,
			usb_preloader.GetUSBPID(), usb_preloader.GetUSBVID());

        Restore_Rom_File();
        //Insert a android image and rearrange android images array
        ReArrangeAndroidArray(img_file);

        ret = Download_Android_ImagesByAdv();
        if(EBOOT_SUCCESS != ret){
            return ret;
        }
    }

     if((is_need_dl_uboot==false) && (is_need_dl_image==false)) {
        // if we need'nt download anyting , it will return flashtool list empty error
        LOG("ERROR: None images is to be downloadeded!");
        ret = FlashTool_Disconnect(&g_ft_handle);
        if(S_DONE != ret) {
            Restore_Rom_File();
    	    return ret;
        }
    }
      
    return ret;
}
#endif
//---------------------------------------------------------------------------
void tboot_1::Remove_Other_Rom_File( bool &is_need_dl_uboot, bool &is_need_dl_image )
{
    DL_HANDLE_T &dl_handle = g_pCurNode->m_dl_handle;
    unsigned short  count;
    DownloadSet		dl_set;

    is_need_dl_uboot = false;
    is_need_dl_image = false;

    for(int i=0; i<ANDROID_IMAGE_FILE_NUMBER; i++)
    {
        g_android_image_files[i].is_download = false;
    }

    if (!DL_GetCount(dl_handle, &count))
    {
	    ROM_INFO rom[MAX_LOAD_SECTIONS];
		ImageType imgType = UNKNOWN_TYPE;
		ImageItem imgItem; 

	    if (!DL_Rom_GetInfoAll(dl_handle, rom, MAX_LOAD_SECTIONS))
	    {
	        for (int i = 0; i < count; i++)
	        {
		        imgType = GetImageMapRule().queryType(rom[i].name);
				imgItem = GetImageMapRule().getImageItem(imgType);
				if (imgItem.is_bootloader() && imgItem.is_format_effective())
		        {
		            is_need_dl_uboot = is_need_dl_uboot || rom[i].enable;
                }
		        else
		        {
		            const AndroidImageInfo &imgInfo =
		            		GetAndroidImageInfoTable()[rom[i].name];
                    //LOGD(GetAndroidImageInfoTable().Dump());
                    
		            if (imgInfo.isValid)
		            {
		                g_android_image_files[imgInfo.androidFileIndex].is_download
		                    = rom[i].enable;
		                g_android_image_files[imgInfo.androidFileIndex].m_format
			                = imgInfo.format;
		                g_android_image_files[imgInfo.androidFileIndex].m_type
		                    = imgInfo.type;
		                g_android_image_files[imgInfo.androidFileIndex].addr_off
		                    = (int) rom[i].begin_addr;
		                g_android_image_files[imgInfo.androidFileIndex].m_path
		                    = const_cast<char*>(imgInfo.filePath.c_str());
		                g_android_image_files[imgInfo.androidFileIndex].is_patch
		                    = imgInfo.isPatch;
		                
						if(i < count-1){
							g_android_image_files[imgInfo.androidFileIndex].addr_boundary
							    = rom[i+1].begin_addr;
						}else{
							g_android_image_files[imgInfo.androidFileIndex].addr_boundary
							    = 0xFFFFFFFF;
						}
		                DL_Rom_SetEnableAttr(dl_handle, i, _FALSE);
		                if (rom[i].enable)
		                {
		                    is_need_dl_image = true;
		                }
		            }
	            }
	        }
        }
    }

    return;
}

//---------------------------------------------------------------------------
void tboot_1::Restore_Rom_File()
{
    DL_HANDLE_T &dl_handle = g_pCurNode->m_dl_handle;
    unsigned short  count;

    if (!DL_GetCount(dl_handle, &count))
    {
        ROM_INFO rom[MAX_LOAD_SECTIONS];
		 ImageType imgType = UNKNOWN_TYPE;
		 ImageItem imgItem;

        if (!DL_Rom_GetInfoAll(dl_handle, rom, MAX_LOAD_SECTIONS))
        {
            for (int i = 0; i < count; i++)
            {
	            imgType = GetImageMapRule().queryType(rom[i].name);
				imgItem = GetImageMapRule().getImageItem(imgType);
				if (!imgItem.is_bootloader() && imgItem.is_format_effective())
	            {
	                const AndroidImageInfo &imgInfo =
	                		GetAndroidImageInfoTable()[rom[i].name];
		            if (imgInfo.isValid &&
                            g_android_image_files[imgInfo.androidFileIndex].is_download)
		            {
		                DL_Rom_SetEnableAttr(dl_handle, i, _TRUE);
		            }
	            }
	        }
       }
    }
}

//---------------------------------------------------------------------------
void __stdcall set_send_image_file_info(void *usr_arg, const char * file_type, unsigned int num_send, unsigned int total)
{
    tboot_1 *t = (tboot_1 *)usr_arg;

    t->progress_forecolor          = clYellow;
    t->progress_hint               = file_type;
    t->progress_percentage         = 0;

    LOGD(string("(CB)Image is wanted to be updated: ").append(file_type).c_str());
    t->SyncInitProgress();
}

//---------------------------------------------------------------------------
void __stdcall show_dl_percentage(void *usr_arg, unsigned int percentage)
{
    tboot_1 *t = (tboot_1 *)usr_arg;

    t->progress_percentage  = percentage;

    t->SyncInitProgress();
}
//---------------------------------------------------------------------------
int tboot_1::Download_Android_Images( void )
{
    EBOOT_RESULT ret;
    Android_Boot_ARG             boot_arg;
    Android_Download_ARG         dl_arg;
    memset(&boot_arg, 0, sizeof(boot_arg));
    memset(&dl_arg, 0, sizeof(dl_arg));

	ErrorLookup::SetErrorCodeMode(FLASHTOOL);
    LOGD("Double scan: Begin second scan USB VCOM port!");
	FlashToolUSBTable usb_table = GetFlashToolUSBTable();
	FlashToolUSB usb_preloader;
	if ( !usb_table.QueryUSBItemByName(FlashToolUSB::PRELOADER_VCOM, usb_preloader) ) {
		LOG("ERROR: tboot_1::Download_Android_Images(): QueryUSBItemByName(): (%s) failed!",
			FlashToolUSB::PRELOADER_VCOM.c_str());
	} else {
		LOG("tboot_1::Download_Android_Images(): QueryUSBItemByName(): Name(%s), PID(%s), VID(%s)",
			usb_preloader.GetUSBName().c_str(),
			usb_preloader.GetUSBPID().c_str(),
			usb_preloader.GetUSBVID().c_str());
	}
    if(!ScanUSBVOMWithTimeout(USB_SCAN_TIMEOUT, 
		usb_preloader.GetUSBPID(), usb_preloader.GetUSBVID())) {
        return FT_FIND_USB_ERROR;
    }
    //set eboot error mode
    ErrorLookup::SetErrorCodeMode(EBOOT);
	
	// Boot As Download Mode
    boot_arg.m_baud_rate  = (COMM_BAUDRATE)BAUDRATE_TBL[BAUD_RATE];
    boot_arg.m_comport    = GetUSBVCOMNumByPortName(m_strPort);
    boot_arg.m_p_comsymbol= (char*)m_strSymbolic.c_str();
    boot_arg.m_p_stopflag = &g_stopflag;
    boot_arg.m_p_thread   = this;

    // Download Image
    memcpy(&dl_arg.m_image_files, &g_android_image_files,
          ANDROID_IMAGE_FILE_NUMBER*sizeof(Android_Image_File));

    //memcpy(&dl_arg.m_auth_file, &MainForm->m_auth_file,
    //      sizeof(Android_Image_File));

    dl_arg.usb_com                      = 0;
    dl_arg.m_p_stopflag                 = &g_stopflag;
    dl_arg.m_p_thread                   = this;
    dl_arg.m_p_send_flash_percentage    = show_dl_percentage;
    dl_arg.m_p_send_image_file_status   = set_send_image_file_info;
    dl_arg.reboot_mode = REBOOT;
    dl_arg.is_verify = false;
	dl_arg.usb_com = GetUSBVCOMNumByPortName(m_strPort);
    //For new scatter file image size check
    dl_arg.is_boundary_Check = IsNewScatterFileWithBoundaryCheck(g_pCurNode->m_dl_handle);
    FillAndroidImageRegionInfo(g_pCurNode->m_dl_handle, dl_arg.m_region_info, dl_arg.m_region_num);

    LOGD(string("[Download_Android_Images] Is to do image boundary check: ")
    		.append((true == dl_arg.is_boundary_Check) ? "Y" : "N").c_str());

    ret = Android_Flash_Download(boot_arg, &dl_arg);

    if(EBOOT_SUCCESS != ret)
    {
        asMsg = "Download image error !";
        return ret;
    }
    else if (   ( UPDATENVRAM == g_nvram_update_state )/*||
                ( FORMAT_DL_UPDATENVRAM == g_nvram_update_state )||
                ( NOACTION != g_backup_restore_state )*/
            )
    {
        return ret;
    }
    else
    {
       // stop timer
       Synchronize( StopTimer );
       DisplaySecResult(dl_arg.sec_arg_result);
    }

    return ret;
}

void tboot_1::ArgAndroidAdvDL(Android_Boot_ARG &boot_arg, Android_ADV_Download_ARG &dl_adv_arg)
{
    memset(&boot_arg, 0, sizeof(boot_arg));
    memset(&dl_adv_arg, 0, sizeof(dl_adv_arg));

    // Boot As Download Mode
    boot_arg.m_baud_rate  = (COMM_BAUDRATE)BAUDRATE_TBL[BAUD_RATE];
    boot_arg.m_comport    = GetUSBVCOMNumByPortName(m_strPort);
    boot_arg.m_p_comsymbol= (char*)m_strSymbolic.c_str();
    boot_arg.m_p_stopflag = &g_stopflag;
    boot_arg.m_p_thread   = this;

    dl_adv_arg.m_p_send_flash_percentage    = show_dl_percentage;
    dl_adv_arg.m_p_send_image_file_status   = set_send_image_file_info;
    dl_adv_arg.m_is_verify = false;
    dl_adv_arg.m_is_boundary_Check = IsNewScatterFileWithBoundaryCheck(g_pCurNode->m_dl_handle);
    
    FillAndroidImageRegionInfo(g_pCurNode->m_dl_handle, dl_adv_arg.m_region_info, dl_adv_arg.m_region_num);

    return;
}

//---------------------------------------------------------------------------
int tboot_1::Download_Android_ImagesByAdv( void )
{
    EBOOT_RESULT ret;
    Android_Boot_ARG             boot_arg;
    Android_ADV_Download_ARG         dl_adv_arg;

	ErrorLookup::SetErrorCodeMode(FLASHTOOL);
    LOGD("Double scan: Begin second scan USB VCOM port!");
	FlashToolUSBTable usb_table = GetFlashToolUSBTable();
	FlashToolUSB usb_preloader;
	if ( !usb_table.QueryUSBItemByName(FlashToolUSB::PRELOADER_VCOM, usb_preloader) ) {
		LOG("ERROR: tboot_1::Download_Android_ImagesByAdv(): QueryUSBItemByName(): (%s) failed!",
			FlashToolUSB::PRELOADER_VCOM.c_str());
	} else {
		LOG("tboot_1::Download_Android_ImagesByAdv(): QueryUSBItemByName(): Name(%s), PID(%s), VID(%s)",
			usb_preloader.GetUSBName().c_str(),
			usb_preloader.GetUSBPID().c_str(),
			usb_preloader.GetUSBVID().c_str());
	}
    if(!ScanUSBVOMWithTimeout(USB_SCAN_TIMEOUT, 
		usb_preloader.GetUSBPID(),usb_preloader.GetUSBVID())) {
        return FT_FIND_USB_ERROR;
    }
    //set eboot error mode
    ErrorLookup::SetErrorCodeMode(EBOOT);

    ArgAndroidAdvDL(boot_arg, dl_adv_arg);
    Android_ADV_SetBootArg(g_Android_Adv_HANDLE, boot_arg);
    Android_ADV_SetDownloadArg(g_Android_Adv_HANDLE, dl_adv_arg);
    
    ret = Android_ADV_Connect(g_Android_Adv_HANDLE);
    if( EBOOT_SUCCESS != ret){
            LOGD("Download_Android_ImagesByAdv: Android_ADV_Connect");
            return ret;
    }

    for(int i=0; i<ANDROID_IMAGE_FILE_NUMBER; i++){
    	LOG("eboot adv sending image(%d): %s",i,g_android_image_files[i].m_path);
        ret = Android_ADV_SendImage(g_Android_Adv_HANDLE, g_android_image_files[i]);
        if( EBOOT_SUCCESS != ret){
            LOGD("Download_Android_ImagesByAdv: Android_ADV_SendImage fails!");
            return ret;
        }
    }
    
    ret = Android_ADV_Reboot(g_Android_Adv_HANDLE, REBOOT);
    if( EBOOT_SUCCESS != ret){
        LOGD("Download_Android_ImagesByAdv: Android_ADV_Reboot fails!");
        return ret;
    }
    
    return ret;
}

//---------------------------------------------------------------------------
void tboot_1::DisplaySecResult(const SecurityBitCtrl_YuSu_T& sec_arg_result)
{
    const char* p_TITLE_HINT = "[Hint] Rom Download Result: \r\n\r\n";
    const char* p_IMAGE_TYPE = "Image";
    const char* p_IS_DL = "Is Downloaded";
    const char* p_STATUS = "Status";
    const unsigned char LOG_ROW_LEN = 61;
    const int LOG_BUF_SIZE = 2048;   
    
    char sec_log[LOG_BUF_SIZE] = {'0'};
    char _c_split_row[LOG_ROW_LEN] = "";
    char _c_split_column[LOG_ROW_LEN] = "";
    memset(_c_split_row, '\=', LOG_ROW_LEN-2);
    memset(_c_split_column, '\ ', LOG_ROW_LEN-2);
    _c_split_row[LOG_ROW_LEN-3] = '\r';
    _c_split_row[LOG_ROW_LEN-2] = '\n';
    _c_split_column[LOG_ROW_LEN-3] = '\r';
    _c_split_column[LOG_ROW_LEN-2] = '\n';

    strcpy( sec_log, p_TITLE_HINT);
    strcat( sec_log, _c_split_row);

    FillColumnInfo(_c_split_column, p_IMAGE_TYPE, p_IS_DL, p_STATUS);
    strcat( sec_log, _c_split_column );
    strcat( sec_log, _c_split_row );

    unsigned short count = 0;
    ROM_INFO rom[MAX_LOAD_SECTIONS];

    if ( !(sec_arg_result.m_lockdown) )
    {
        GetLockImageInfo( sec_arg_result, NULL, 0, sec_log);
        strcat( sec_log, _c_split_row);
    }
    else
    {
        if (!DL_GetCount(g_pCurNode->m_dl_handle, &count))
        {
            ROM_INFO rom[MAX_LOAD_SECTIONS];

            if (!DL_Rom_GetInfoAll(g_pCurNode->m_dl_handle, rom, MAX_LOAD_SECTIONS))
            {
                for (int i = 1; i < count; i++)
                {
                    const AndroidImageInfo &imgInfo =
                    		GetAndroidImageInfoTable()[rom[i].name];
                    if(imgInfo.isValid)
                    {
						GetLockImageInfo( sec_arg_result, rom[i].name,
								imgInfo.androidFileIndex, sec_log);
						strcat( sec_log, _c_split_row);
                    }
    	        }
           }
        }
        else
        {
            return;
        }
    }
    asMsg = sec_log;
    Synchronize(ShowMsg);
    memset( sec_log, 0, sizeof(sec_log));

    return;
}

//---------------------------------------------------------------------------
bool tboot_1::CharMove(char* p_dst, const char* p_SRC, const unsigned char offset, const unsigned int num)
{
    const unsigned int LOG_BUF_SIZE = 2048;
    unsigned int len_src = strlen(p_SRC);
    if ( num > LOG_BUF_SIZE || len_src > LOG_BUF_SIZE )
    {
        return false;
    }
    else
    {
        for (unsigned int i = 0; i < num; i++)
        {
            p_dst[i+offset] = p_SRC[i];
        }
    }
    return true;
}
#if 0
//---------------------------------------------------------------------------
void tboot_1::cb_sp_dl_progress(int progress)
{
    MainForm->CGauge1->Hint      = "Start to Download Flash.Bin file";
    MainForm->CGauge1->ForeColor = clYellow;
    MainForm->CGauge1->Progress  = progress;
}
//---------------------------------------------------------------------------
void __stdcall show_send_flash_bin_percentage(unsigned int percentage)
{

    tboot_1 *t= MainForm->p1;

    if ( t->m_bDLFlashBin )
    {
        t->StartTimer();
    }

    if(percentage <= 0)
       return;

    t->progress_percentage  = percentage;

    t->SyncInitProgress();
//    MainForm->CGauge1->Progress  = percentage;
}

//---------------------------------------------------------------------------
int tboot_1::DLFlashBin( void )
{
//    int ret = S_DONE;
	ErrorLookup::SetErrorCodeMode(EBOOT);
//    g_error_code_mode = EBOOT;
    //wayne add for smart phone download
    //could receive msg download and inv(download)

    progress_hint= "Enter Smart Phone Eboot Download mode";
    progress_forecolor = clYellow;
    progress_percentage = 0;
    SyncInitProgress();
 // fix below CGauge operation by Shuning /**/
/*
    MainForm->CGauge1->Hint      = "Enter Smart Phone Eboot Download mode";

    //About interval between CGauge opertion:
    //We find if operate progress bar too quackly
    //it will show black bar. This issue seemed can be
    //resolved by add some sleep between this operation.
    MainForm->CGauge1->Progress  = 0;
    Sleep(300);
    MainForm->CGauge1->BackColor = clWhite;
    Sleep(300);
    MainForm->CGauge1->ForeColor = clYellow;

*/
/*
    if(!SP_BootAsDownload(COM_PORT,BAUD115200,&g_stopflag))
    {
      asMsg = "Enter WM EBOOT download mode fail";
      return -1;
    }

    MainForm->CGauge1->Hint      = "Start to Download Flash.Bin file";

    if(!SP_Download(MainForm->ed_SPBIN_File->Text.c_str(),&g_stopflag,
                    enum_wceusb_port, this, show_send_flash_bin_percentage))
    {
       //ShowMessage("Download Flash.Bin file fail");
       asMsg = "Download Flash.Bin file fail";
       return -1;
    }
*/

    // enable DLFlashBin flag to show time
    this->m_bDLFlashBin = true;
    char str_flash_file[256];
//     strcpy( str_flash_file, MainForm->ed_SPBIN_File->Text.c_str() );
     strcpy( str_flash_file, MainForm->asFlashBinFile.c_str() );
     FT_Download_ARG arg;
//     arg.m_binfile= MainForm->ed_SPBIN_File->Text.c_str();
     arg.m_binfile= str_flash_file;
     arg.m_p_baud = BAUD115200;
     arg.m_p_stopflag = &g_stopflag;
     arg.m_p_comport  = COM_PORT;
     arg.m_p_ft_send_flash_percentage = show_send_flash_bin_percentage;
     EBOOT_RESULT result;
     if(EBOOT_SUCCESS!=(result=SP_Flash_Download(arg)))
    {
       //ShowMessage("Download Flash.Bin file fail");
       asMsg = "Download Flash.Bin file fail";
       if ( result == S_DONE)
       {
           return -1;
       }
       else
       {
           return result;
       }
    }

    MainForm->CGauge1->Hint      = "Finish Download Flash.Bin file";
    MainForm->CGauge1->ForeColor = clYellow;
    MainForm->CGauge1->BackColor = clWhite;
    MainForm->CGauge1->Progress  = 100;

    // disable DLFlashBin flag to show time
    this->m_bDLFlashBin = false;
    return S_DONE;
}
#endif

//---------------------------------------------------------------------------


bool tboot_1::IsNvramFilesExist(const std::string& nvram_folder)
{
    const string mapFile = nvram_folder + "\\" + MapFileName;
    const string datFile = nvram_folder + "\\" + DatFileName;
    return ( FileUtils::IsFileExist(mapFile) && FileUtils::IsFileExist(datFile) );
}
//---------------------------------------------------------------------------
int tboot_1::ObtainPartitionRegion(const string &img_name, RB_INFO &rb_info)
{
	int ret = 0;
	PART_INFO part_info;
	memset(&part_info, 0, sizeof(part_info));

	ret = GetPartitionInfo(g_ft_handle, img_name, part_info);
	if ( S_DONE != ret ) {
		LOG("ERROR: tboot_1::ObtainPartitionRegion(): Obtain Nvram BinRegion start address and length failed!");
		return ret;
	} else {
	    rb_info.readback_addr = part_info.begin_addr;
		rb_info.readback_len = part_info.image_length;
		LOG("tboot_1::ObtainPartitionRegion(): Nvram BinRegion readback addr is 0x%016I64X, lenght is 0x%x",
			rb_info.readback_addr, rb_info.readback_len);
	}

    return ret;
}
int tboot_1::Conn2ObtianPartitionRegion(const string& img_name, RB_INFO &rb_info, bool &isDynamic)
{
	int ret = 0;
    PART_INFO part_info;
    memset(&part_info, 0, sizeof(part_info));

    //Step 1 Connect in DL mode
    ArgFlashToolConnect(cn_arg, cn_result);
	unsigned char  com_port = (!g_bUsbMode) ? COM_PORT : GetUSBVCOMNumByPortName(m_strPort);

	LOG("Getting com port(%d), is USB mode(%d)",com_port,g_bUsbMode);

	int  force_charge = /*g_bUsbModeWithBattery ? 0 : 1*/GetBatteryStatus();
	LOGD("FlashDownload_internal: force_charge(%d)", force_charge);
    ret = FlashTool_Connect( com_port, &cn_arg, &cn_result, NULL, &g_stopflag, &g_ft_handle, force_charge);
    if( S_DONE != ret ) {
		LOGD("ERROR: tboot_1::Conn2ObtianPartitionRegion(): FlashTool_Connect fail!");
    	return ret;
    }
    
    g_platform_info.setChipName(cn_result.m_da_report.m_bbchip_name);
    if( g_platform_info.getPlatformConfig().supportLogicalAddress()) {
        isDynamic = true; //Smart Phone Platform after MT6516 will apply dynamic layout
    } else {
        isDynamic = false;
    }  

	ret = GetPartitionInfo(g_ft_handle, img_name, part_info);
	if ( S_DONE != ret ) {
		LOG("ERROR: tboot_1::Conn2ObtianPartitionRegion(): Obtain (%s) start address and length failed!", img_name.c_str());
		return ret;
	} else {
	    rb_info.readback_addr = part_info.begin_addr;
		rb_info.readback_len = part_info.image_length;
		LOG("tboot_1::Conn2ObtianPartitionRegion(): (%s) readback addr is 0x%016I64X, lenght is 0x%x", 
			img_name.c_str(), rb_info.readback_addr, rb_info.readback_len);
	}

    return ret;
}

//---------------------------------------------------------------------------
int tboot_1::ReadbackPartitioWithoutDisconnect(const std::string &dest_folder,
		const std::string &file_name,
		const bool isDynamicLayout,
		RB_INFO &rb_info)
{
	int ret = 0;
	RBHandleManager readback_handler;

	ErrorLookup::SetErrorCodeMode(FLASHTOOL);
    E_CHECK_DIR_STATUS dirStatus = FileUtils::CheckDirectory(dest_folder);
	LOG("tboot_1::ReadbackPartitioWithoutDisconnect: Got backup dir by Chip ID, backup folder: %s", dest_folder.c_str());
    //error handling of creating backup folder
    if ( CREATE_DIR_FAIL == dirStatus ) {        
        LOGE("[Hint] Create backup directory: %s fails!");
        ret = FT_UPGRADE_DIR_CREATE_FAIL;
        return ret;
    } /*else if ( DIR_EXIST == dirStatus ) {
        std::ostringstream ss;
        ss<<"[Hint]\r\nBackup destination folder: \r\n"
          <<dest_folder
          <<"\r\nexists already!"
          <<"\r\nPlease move existing data of this folder to another place,"
          " then delete this folder before executing backup!";
          LOGW(m_as_err_msg.c_str());
          //pop up explorer
          ret = FT_UPGRADE_FOLDER_OVERLAPPED;
          return ret;
    }*/
    ErrorLookup::SetErrorCodeMode(BROM);

    FlashTool_Readback_Arg rb_arg;
    FlashTool_Readback_Result rb_result;

    ArgFlashToolAdvancedReadback(rb_arg, rb_result, isDynamicLayout, readback_handler.rb_handle());
    if ( S_DONE != ret ) {
		LOGD("ERROR: ArgFlashToolAdvancedReadback: FlashTool_Readback fail!");
        return ret;
    }
    
    rb_info.enable = _TRUE;
    rb_info.index = 0;
   
    ret = ArgFlashToolRBSetting(readback_handler.rb_handle(), rb_info, NUTL_ADDR_LOGICAL);
    if ( S_DONE != ret ) {
        LOGD("ReadbackPartitioWithoutDisconnect: ArgFlashToolRBSetting fail!");
        return ret;
    } 
    
    LOG("%s(): Dumping readback handle before FlashTool_Readback.", __FUNC__);
    readback_handler.Dump();
    ret = FlashTool_Readback(g_ft_handle, &rb_arg, &rb_result);
    if ( S_DONE != ret ) {
        LOGD("ReadbackPartitioWithoutDisconnect: FlashTool_Readback fail!");
        return ret;
    }            

	return ret;
}

//---------------------------------------------------------------------------
int tboot_1::WritePartition( const Android_Image_File& img_file )
{
    EBOOT_RESULT ret;
   
    ret = Android_ADV_SendImage(g_Android_Adv_HANDLE, img_file);
    if( EBOOT_SUCCESS != ret){
        LOGD("WriterPartition: Android_ADV_SendImage fails!");
        return ret;
    }

    ret = Android_ADV_Reboot(g_Android_Adv_HANDLE, REBOOT);
    if( EBOOT_SUCCESS != ret){
        LOGD("WriterPartition: Android_ADV_Reboot fails!");
        return ret;
    }
    
    return ret;
}

//---------------------------------------------------------------------------
int tboot_1::ReadPartitionRegionByScatterFile(DL_HANDLE_T pDLHandle,
		const std::string &image_folder,
		Android_Image_File &img_file,
		const string& img_name)
{
    assert(pDLHandle != NULL);

    int ret = S_UNDEFINED_ERROR;
    unsigned short count = 0;
    if (S_DONE == (ret = DL_GetCount(pDLHandle, &count))) {
	    ROM_INFO rom[MAX_LOAD_SECTIONS];
	    if (S_DONE == (ret = DL_Rom_GetInfoAll(pDLHandle, rom, MAX_LOAD_SECTIONS))) {
		    for (int i = 0; i < count; i++) {
                if( 0 == img_name.compare(rom[i].name) ) {
                    img_file.addr_off = rom[i].begin_addr;
                    img_file.addr_boundary = rom[i+1].begin_addr;
                    img_file.is_download = true;
                    img_file.m_type = DM_IMG_TYPE_CUST_IMAGE4;
                    img_file.m_format = DM_IMG_FORMAT_FAT;
                    img_file.is_patch = false;
                    strcpy(m_szNvramPath, string(image_folder + "\\" + BIN_REGION_FILE_NAME).c_str());
                    img_file.m_path = m_szNvramPath;
                    break;                 
                }            
		    }
	    } 
    } 

	LOG("tboot_1::ReadPartitionRegionByScatterFile():Dumping nvram image: 0x%x~0x%x, %s",img_file.addr_off,img_file.addr_boundary,img_file.m_path);

    return ret;
}

//---------------------------------------------------------------------------
bool tboot_1::ReArrangeAndroidArray(const Android_Image_File &img_file)
{
    int androidImgNum = GetAndroidImageInfoTable().ImageNum();
    if(0 == androidImgNum){
        LOGD("ReArrangeAndroidArray: Android Image info table is empty!");
        return false;
    }else {
        LOGD(GetAndroidImageInfoTable().Dump().c_str());
        Android_Image_File *pTmpAndroidImageArray = NULL;
        pTmpAndroidImageArray = new Android_Image_File[androidImgNum+1];
        if( NULL == pTmpAndroidImageArray ){
            LOGD("ReArrangeAndroidArray: Malloc temp android heap array for rearangeing fails!");
            return false;
        } else {
            memset(pTmpAndroidImageArray, 0, androidImgNum*sizeof(Android_Image_File));
            for(int i = 0; i < androidImgNum; i++){
                if (img_file.addr_off < g_android_image_files[i].addr_off) {
                    //Insert new partition image into android array
                    memcpy(pTmpAndroidImageArray+i, &img_file, sizeof(Android_Image_File));
                    //Copy extra images behind new partition
                    memcpy(pTmpAndroidImageArray+i+1, &g_android_image_files[i], (androidImgNum-i)*sizeof(Android_Image_File));
                    break;
                } else {
                    memcpy(pTmpAndroidImageArray+i, &g_android_image_files[i], sizeof(Android_Image_File));
                }
            }
            //restore android array which has been rearranged to original array
            memcpy(&g_android_image_files, pTmpAndroidImageArray, (androidImgNum+1)*sizeof(Android_Image_File));
        }
        delete[] pTmpAndroidImageArray;
        pTmpAndroidImageArray = NULL;
        return true;
    }
}
//---------------------------------------------------------------------------
int  tboot_1::BackupFormatDownloadYuSuRestore( void )
{
    assert(0 && "Not support!");
#if 0
    int ret;
    m_bUseChipID = MainForm->UseChipIDasBackupFolderName->Checked; 
    
    // Backup NVRAM
    // Reset progress bar and status bar
    Synchronize( ResetMETABackup );
    Synchronize( ResetFakeProgress ); 
    // Enter meta to Backup NVRAM
    ret = EnterMETABackup();
    if ( META_SUCCESS != ret ) {
        asMsg = "[Hint] Backup NVRAM operation is not done!";
        return ret;
    }  
    LOGD("Begin to enter format flow...");
    // Format->Download Android
    ret = FormatDownloadYuSu();
    if ( S_DONE != ret ) {
        asMsg = "[Hint] Download Android operation is not done!";
        return ret;
    }

    if(g_bUsbMode) {     
        Sleep(1000);
    }
    // Restore NVRAM
    // Reset progress bar and status bar
    Synchronize( ResetMETARestore );
    Synchronize( ResetFakeProgress );
    // Enter meta to Restore NVRAM
    ret = EnterMETARestore();
    if ( META_SUCCESS != ret ) {
        asMsg = "[Hint] Restore NVRAM operation is not done!";
        return ret;
    }

    return ret;
#endif
	return 0;
}

//---------------------------------------------------------------------------
int  tboot_1::BackupFormatDownloadYuSuRestoreDLMode( void )
{
	ErrorLookup::SetErrorCodeMode(BROM);
    int ret;
    Android_Image_File img_file;
    RB_INFO rb_info;
    memset(&rb_info, 0, sizeof(RB_INFO));

    ArgFlashToolConnect(cn_arg, cn_result);
	unsigned char  com_port = (!g_bUsbMode) ? COM_PORT : GetUSBVCOMNumByPortName(m_strPort);

	int  force_charge = /*g_bUsbModeWithBattery ? 0 : 1*/GetBatteryStatus();
	LOGD("FlashDownload_internal: force_charge(%d)", force_charge);
	ret = FlashTool_Connect( com_port, &cn_arg, &cn_result, NULL, &g_stopflag, &g_ft_handle, force_charge);
	if( S_DONE != ret ) {
		LOG("ERROR: %s(): FlashTool_Connect fail!", __FUNC__);
		return ret;
	}

	bool isDynamicLayout = false;
	g_platform_info.setChipName(cn_result.m_da_report.m_bbchip_name);
	if( g_platform_info.getPlatformConfig().supportLogicalAddress() ) {
		isDynamicLayout = true; //Smart Phone Platform after MT6516 will apply dynamic layout
	} else {
		isDynamicLayout = false; 
	}
   	   

	std::string bin_region_folder;//BinRegion folder,  "<app dir>/NvramBackup/<chip-id>"
	std::string binregion_file;
	NandLayoutParameter nand_mgr(g_pCurNode->m_dl_handle, g_ft_handle, NandLayoutParameter::kVitaltemsCount);
	//Temp demo firmware upgrade
	//NandLayoutParameter nand_mgr(g_pCurNode->m_dl_handle, g_ft_handle, NandLayoutParameter::kVitaltemsCount);
	//if (!nand_mgr.is_nand_layout_matched()) {
	    ErrorLookup::SetErrorCodeMode(FLASHTOOL);
		if(!FileUtils::MakeParentBackupDir()) {
	        FlashTool_Disconnect(&g_ft_handle);
			LOG("ERROR: %s(): MakeParentBackupDir() failed!", __FUNC__);
			return FT_UPGRADE_DIR_CREATE_FAIL;
		}
		ErrorLookup::SetErrorCodeMode(BROM);
		bin_region_folder = FileUtils::ComposeDirNameByChipID(cn_result.m_da_report.m_random_id, kChipIDLength);
		binregion_file = bin_region_folder+"\\"+BIN_REGION_FILE_NAME;
		std::string checksum_file(bin_region_folder+"\\"+BIN_REGION_CHECKSUM);
		
		//check backup dir first to figure out if a previous backup has been done.
		if ( FileUtils::IsFileExist(binregion_file))
		{
			LOG("%s(): NVRAM bin region already exists for this chip: %s, verifying the checksum...",
				__FUNC__, bin_region_folder.c_str());
			bool chksumOK = false;
			if(FileUtils::IsFileExist(checksum_file)){
				unsigned char origin_chksum = 0;
				unsigned char actual_chksum = 0;
				if(FileUtils::LoadCheckSum(checksum_file,origin_chksum) &&
						FileUtils::ComputeCheckSum(binregion_file,actual_chksum) &&
						origin_chksum == actual_chksum){
					chksumOK = true;
					LOG("%s(): origin_chksum(%u) VS actual_chksum(%u).",
						__FUNC__, origin_chksum, actual_chksum);
					LOG("%s(): NVRAM bin region checksum is OK.", __FUNC__);
				}
			}

			ErrorLookup::SetErrorCodeMode(FLASHTOOL);
			if(!chksumOK){
				LOG("%s:() NVRAM bin region checksum is wrong, need to remove dirty file first.", __FUNC__);
				//pop up explorer
				ShellExecute(NULL, "open", bin_region_folder.c_str(), NULL, NULL, SW_SHOWNORMAL);
				FlashTool_Disconnect(&g_ft_handle);
				return FT_UPGRADE_FILE_CORRUPTED;
			}
			ErrorLookup::SetErrorCodeMode(BROM);
		}
		else
		{
			//read back NVRAM bin region
			LOG("%s(): Reading back NVRAM bin region from target...", __FUNC__);
			ret = ObtainPartitionRegion(NvramName, rb_info);
			if ( S_DONE != ret ) {
				asMsg = "[Hint] Obtain Partition Region fails!";
				FlashTool_Disconnect(&g_ft_handle);
				return ret;
			}
			ret = ReadbackPartitioWithoutDisconnect(bin_region_folder,
					BIN_REGION_FILE_NAME,
					isDynamicLayout,
					rb_info);
			if ( S_DONE != ret ) {
				asMsg = "[Hint] Backup NVRAM operation is not done!";
				FlashTool_Disconnect(&g_ft_handle);
				return ret;
			}

			//compute & save checksum file
			unsigned char file_chksum = 0;
			FileUtils::ComputeCheckSum(binregion_file, file_chksum);
			FileUtils::SaveCheckSum(checksum_file, file_chksum);
			LOG("%s(): Compute & Save Bin Region checksum: %d", __FUNC__, file_chksum);
		}

		LOG("%s(): Obtain partition region by scatter file...", __FUNC__);
		ReadPartitionRegionByScatterFile(g_pCurNode->m_dl_handle, bin_region_folder, img_file, NvramName);
		//Format All after Nvram Binregion is read back
		#if 0
		g_NandAutoFormatFlag = FORMAT_ALL;
		//Physical format after NvramBinregion is readback
		isDynamicLayout = false;
	//} else {
	//	//Format All except bootloader and Nvram BinRegion if scatter file layout matches with PMT
	//	g_NandAutoFormatFlag = FORMAT_ALL_EXP_BL_NVRAM_BIN;
	//}

    LOG("%s(): Begin to enter format flow...", __FUNC__);
    FlashTool_Format_Arg       fmt_arg;
    FlashTool_Format_Result    fmt_res;
    g_FormatOption = AUTO_FORMAT;
    ArgFlashToolAdvancedFormat(fmt_arg, fmt_res, cn_result, false, isDynamicLayout);

    ret = FlashTool_Format(g_ft_handle,
                     &fmt_arg, &fmt_res);
    if(S_DONE != ret) {
        FlashTool_Disconnect(&g_ft_handle);
    }
    #endif
    		//format
         LOG("%s(): Begin to enter format flow...", __FUNC__);
	
	      
   BackupConfig backupConfig(bin_region_folder);
   BackupItem backupItem;
   std::list<std::string> backupItemTable;   
  
    ret = FormatWithoutConnection(nand_mgr, backupConfig);
    if(ret != S_DONE)
    {
         FlashTool_Disconnect(&g_ft_handle);
         LOGE("%s(): FlashTool_Format fail!", __FUNC__);
	  return ret;
    }    

    LOG("%s(): Begin to enter download flow...", __FUNC__);
    bool is_need_dl_uboot, is_need_dl_image;
    FlashTool_Download_Arg fdl_arg;
    FlashTool_Download_Result fdl_res;
    //Remove all rom files except bootloaders
    Remove_Other_Rom_File(is_need_dl_uboot, is_need_dl_image);

    ArgFlashToolAdvancedDownload(fdl_arg, fdl_res);
    if(is_need_dl_uboot && is_need_dl_image)
    {
        // First step: brom.dll downloads bootloaders
        ret = FlashTool_Download(g_ft_handle, &fdl_arg, &fdl_res);
        if ( S_DONE != ret ) {
            FlashTool_Disconnect(&g_ft_handle);
            LOGD("FormatDownloadYuSuByAdv: FlashTool_Download fail!");
            Restore_Rom_File();
            return ret;
        }
        if(!ToolInfo::IsCustomerVer()) {
			FlashTool_EnableWDT_Arg wdt_arg;
			FlashTool_EnableWDT_Arg *p_wdt_arg = &wdt_arg;
			ArgFlashToolWatchDog(p_wdt_arg);
			ret = FlashTool_EnableWatchDogTimeout(g_ft_handle, p_wdt_arg);
			if(S_DONE != ret) {
				FlashTool_Disconnect(&g_ft_handle);
				LOGD("FormatDownloadYuSuByAdv: FlashTool_EnableWatchDogTimeout fail!");
				Restore_Rom_File();
    			return ret;
			}
		}
        ret = FlashTool_Disconnect(&g_ft_handle);
        if(S_DONE != ret) {
            LOGD("FormatDownloadYuSuByAdv: FlashTool_Disconnect fail!");
            Restore_Rom_File();
    	    return ret;
        }

        //Second step: eboot.dll download Android images
        //Scan exist com port
        m_strSymbolicName.erase(m_strSymbolicName.begin(), m_strSymbolicName.end());
        m_strSymbolicName.begin();
		FlashToolUSBTable usb_table = GetFlashToolUSBTable();
		FlashToolUSB usb_preloader;
		if ( !usb_table.QueryUSBItemByName(FlashToolUSB::PRELOADER_VCOM, usb_preloader) ) {
			LOG("ERROR: tboot_1::FormatDownloadYuSuByAdv(): QueryUSBItemByName(): (%s) failed!",
				FlashToolUSB::PRELOADER_VCOM.c_str());
		} else {
			LOG("tboot_1::FormatDownloadYuSuByAdv(): QueryUSBItemByName(): Name(%s), PID(%s), VID(%s)",
				usb_preloader.GetUSBName().c_str(),
				usb_preloader.GetUSBPID().c_str(),
				usb_preloader.GetUSBVID().c_str());
		}
        LOGD("Double scan: Begin first scan USB VCOM port!");
        ScanExistUSBVComPort(m_strSymbolicName, m_strPortName,
			usb_preloader.GetUSBPID(), usb_preloader.GetUSBVID());

        Restore_Rom_File();
        //if (!nand_mgr.is_nand_layout_matched()){
        	//The action is ONLY needed when scatter file layout does not match with target layout
            //Insert a android image and rearrange android images array
            ReArrangeAndroidArray(img_file);
        //}

        ErrorLookup::SetErrorCodeMode(EBOOT);
        ret = Download_Android_ImagesByAdv();
        if(EBOOT_SUCCESS != ret){
        	LOG("ERROR: %s(): Download_Android_ImagesByAdv() failed.", __FUNC__);
            return ret;
        } else {
        	LOG("%s(): Remove diretory after restored: %s.", __FUNC__, bin_region_folder);
    		if (!FileUtils::DeleteDirectory(bin_region_folder)) {
    			LOG("%s(): Remove diretory failed.", __FUNC__);
    		}
    		ErrorLookup::SetErrorCodeMode(BROM);
    		return S_DONE;
        }

    } else {
       LOGD("ERROR: NOT all rom images are to be downloaded!");
       return S_UNDEFINED_ERROR;
    }
    
}

//---------------------------------------------------------------------------
RegionFormatSetting* tboot_1::CreateRegionFormatSetting(const std::string &image_name)
{      
	RegionFormatSetting *setting = new RegionFormatSetting(image_name);
	setting->set_if_do_partitial_format(true);
	setting->set_cb_format_report_arg(this);
	setting->set_cb_format_report_init_arg(this);
	setting->set_cb_format_statistics_arg(this);
	setting->set_format_report_cb(cb_format_report);
	setting->set_format_report_init_cb(cb_format_report_init);
	setting->set_format_statistics_cb(NULL);
	setting->set_dl_handle(g_pCurNode->m_dl_handle);
	setting->set_ft_handle(g_ft_handle);
	setting->set_conn_result(&cn_result);
	setting->set_is_validation(g_FormatValidation?_TRUE:_FALSE);

       return setting;
}

//---------------------------------------------------------------------------
int  tboot_1::FormatDownloadRestoreYuSu(){
	assert(0 && "deprecated function: FormatDownloadRestoreYuSu");
	return 0;
#if 0
    int ret;
    
    m_bUseChipID = MainForm->UseChipIDasBackupFolderName->Checked; 
    
    LOGD("Begin to enter format flow...");
    // Format->Download Android
    ret = FormatDownloadYuSu();
    if ( S_DONE != ret ) {
        asMsg = "[Hint] Download Android operation is not done!";
        return ret;
    }
    
    if(g_bUsbMode) {     
        Sleep(1000);
    }    
    // Restore NVRAM
    // Reset progress bar and status bar
    Synchronize( ResetMETARestore );
    Synchronize( ResetFakeProgress );
    m_strBackupFolder = g_BackupCalibrationDataFolderPath.c_str();
    // Enter meta to Restore NVRAM
    ret = EnterMETARestore();
    if ( META_SUCCESS != ret ) {
        asMsg = "[Hint] Restore NVRAM operation is not done!";
        return ret;
    }
    
    return ret;
#endif
}
#if 0
//---------------------------------------------------------------------------
int tboot_1::FormatDownloadRestoreYuSuUnderDLMode()
{
    int ret;
    Android_Image_File img_file;
    //m_bUseChipID = MainForm->UseChipIDasBackupFolderName->Checked; 
    std::string bin_region_folder;
    
    ArgFlashToolConnect(cn_arg, cn_result);
	unsigned char  com_port = (!g_bUsbMode) ? COM_PORT : GetUSBVCOMNumByPortName(m_strPort);

	int  force_charge = /*g_bUsbModeWithBattery ? 0 : 1*/GetBatteryStatus();
	LOGD("FlashDownload_internal: force_charge(%d)", force_charge);
    ret = FlashTool_Connect( com_port, &cn_arg, &cn_result, NULL, &g_stopflag, &g_ft_handle, force_charge);
    if( S_DONE != ret ) {
        LOGD("ObtianPartitionRegion: FlashTool_Connect fail!");
    	return ret;
    }
    
    bool isDynamicLayout = false;
    g_platform_info.setChipName(cn_result.m_da_report.m_bbchip_name);
    if( g_platform_info.getPlatformConfig().supportLogicalAddress() ) {
        isDynamicLayout = true;//Smart Phone Platform after MT6516 will apply dynamic layout
    } else {
        isDynamicLayout = false; 
    } 

    ErrorLookup::SetErrorCodeMode(FLASHTOOL);
	if(!FileUtils::MakeParentBackupDir()) {
        FlashTool_Disconnect(&g_ft_handle);
		LOG("ERROR: %s(): MakeParentBackupDir() failed!", __FUNC__);
		return FT_UPGRADE_DIR_CREATE_FAIL;
	}
	ErrorLookup::SetErrorCodeMode(BROM);
    bin_region_folder = FileUtils::ComposeDirNameByChipID(cn_result.m_da_report.m_random_id, kChipIDLength);
	ErrorLookup::SetErrorCodeMode(FLASHTOOL);
    //m_strBackupFolder = g_BackupCalibrationDataFolderPath.c_str();    
	E_CHECK_DIR_STATUS dirStatus = FileUtils::CheckDirectory(bin_region_folder);
	if ( DIR_EXIST != dirStatus ) {
	    LOG("FormatDownloadRestoreYuSuUnderDLMode: Obtain restore path fail!");
		return FT_UPGRADE_FOLDER_NOT_EXSIT;
	} else {
		LOG("FormatDownloadRestoreYuSuUnderDLMode: Obtain restore path is %s.", bin_region_folder.c_str());
	}
	ErrorLookup::SetErrorCodeMode(BROM);

    LOGD("FormatDownloadRestoreYuSuUnderDLMode: Obtain partition region by scatter file...");    
    ReadPartitionRegionByScatterFile(g_pCurNode->m_dl_handle, bin_region_folder, img_file, NvramName);
    
    LOGD("FormatDownloadRestoreYuSuUnderDLMode: Begin to enter format->download flow...");
    // Format->Download Android
    ret = FormatDownloadYuSuByAdv(img_file, isDynamicLayout);
    if ( EBOOT_SUCCESS != ret ) {
        asMsg = "[Hint] Format->Download Android operation is not done!";
        return ret;
    } else {
		LOGD(string("FormatDownloadRestoreYuSuUnderDLMode: Remove diretory after restored: ").append(bin_region_folder));
		if (!FileUtils::DeleteDirectory(bin_region_folder)) {
			LOGE("FormatDownloadRestoreYuSuUnderDLMode: Remove diretory failed.");
		}
        return S_DONE;
    }
    
}
#endif
int  tboot_1::RestoreOnlyYuSu(){
	assert(0 && "deprecated function: RestoreOnlyYuSu");
	return 0;
#if 0
    int ret;
    
    m_bUseChipID = MainForm->UseChipIDasBackupFolderName->Checked; 
    
    // Restore NVRAM
    // Reset progress bar and status bar
    Synchronize( ResetMETARestore );
    Synchronize( ResetFakeProgress );
    // Enter meta to Restore NVRAM
    m_strBackupFolder = g_BackupCalibrationDataFolderPath.c_str();
    ret = EnterMETARestore();
    if ( META_SUCCESS != ret ) {
        asMsg = "[Hint] Restore NVRAM operation is not done!";
        return ret;
    }
    
    return ret;
#endif
}
#if 0
//---------------------------------------------------------------------------
int tboot_1::RestoreOnlyYuSuUnderDLMode()
{
	assert(0 && "deprecated function: RestoreOnlyYuSuUnderDLMode");
	return 0;
#if 0
    int ret;
    Android_Image_File img_file;
    std::string bin_region_folder;
     
	ErrorLookup::SetErrorCodeMode(FLASHTOOL);
    LOGD("RestoreOnlyYuSuUnderDLMode: Double scan USB VCOM port!");
	FlashToolUSBTable usb_table = GetFlashToolUSBTable();
	FlashToolUSB usb_preloader;
	if ( !usb_table.QueryUSBItemByName(FlashToolUSB::PRELOADER_VCOM, usb_preloader) ) {
		LOG("ERROR: tboot_1::RestoreOnlyYuSuUnderDLMode(): QueryUSBItemByName(): (%s) failed!",
			FlashToolUSB::PRELOADER_VCOM.c_str());
	} else {
		LOG("tboot_1::RestoreOnlyYuSuUnderDLMode(): QueryUSBItemByName(): Name(%s), PID(%s), VID(%s)",
			usb_preloader.GetUSBName().c_str(),
			usb_preloader.GetUSBPID().c_str(),
			usb_preloader.GetUSBVID().c_str());
	}
    if(!ScanUSBVOMWithTimeout(USB_SCAN_TIMEOUT,
		usb_preloader.GetUSBName(), usb_preloader.GetUSBVID())) {
        return FT_FIND_USB_ERROR;
    }
    //set eboot error mode
    ErrorLookup::SetErrorCodeMode(EBOOT);

    Android_Boot_ARG             boot_arg;
    Android_ADV_Download_ARG         dl_adv_arg;    
    ArgAndroidAdvDL(boot_arg, dl_adv_arg);
    Android_ADV_SetBootArg(g_Android_Adv_HANDLE, boot_arg);
    Android_ADV_SetDownloadArg(g_Android_Adv_HANDLE, dl_adv_arg);
    
    ret = Android_ADV_Connect(g_Android_Adv_HANDLE);
    if( EBOOT_SUCCESS != ret){
		LOGD("ERROR: RestoreOnlyYuSuUnderDLMode: Android_ADV_Connect fails.");
        return ret;
    }
    
    bin_region_folder = g_BackupCalibrationDataFolderPath.c_str();
    ReadPartitionRegionByScatterFile(g_pCurNode->m_dl_handle, bin_region_folder, img_file, NvramName);
    ret = WritePartition(img_file);
    if ( EBOOT_SUCCESS != ret ) {
        asMsg = "[Hint] Restore NVRAM operation is not done!";
        return ret;
    } else {
		LOGD(string("RestoreOnlyYuSuUnderDLMode: Remove diretory after restored: ").append(bin_region_folder));
		if (!FileUtils::DeleteDirectory(bin_region_folder)) {
			LOGE("ERROR: RestoreOnlyYuSuUnderDLMode: Remove diretory failed.");
		}
        return S_DONE;
    }
#endif
}
#endif
//---------------------------------------------------------------------------
int  tboot_1::DownloadYuSuRestore( void )
{
	assert(0 && "deprecated function: DownloadYuSuRestore");
	return 0;
#if 0
    // download Android
    int ret;
    ret = DownloadYuSu();
    if ( S_DONE != ret ) {
        return ret;
    }
    // Reset progress bar and status bar
    Synchronize( ResetMETARestore );
    Synchronize( ResetFakeProgress );    
    // Enter meta to restore NVRAM
    ret = EnterMETARestore();
    if ( META_SUCCESS != ret ) {
         // Display download succeed message
        asMsg = "Download is DONE. But Restore NVRAM operation does not finish!";
        return ret;
    }

    return ret;
#endif
}


//---------------------------------------------------------------------------
int  tboot_1::DownloadFourInOne(void)
{

    // download
    int ret;

    ret = DownloadYuSu();
    if ( S_DONE != ret ) {
        return ret;
    }

    // Reset progress bar and status bar
    Synchronize( ResetDL_FourInOne_Info );
    Synchronize( ResetFakeProgress );
    
    // enter meta to write IMEI/BT/WiFi
    ret = EnterMETAUpdateNVRAM();
    if ( META_SUCCESS != ret ) {
         // Display download succeed message
        asMsg = "Download is DONE, but NVRAM IMEI/BT/WiFi operation does not finish!\n"
        		"[Possible Reason]:\n"
				"1. Write IMEI/BT/WiFi failed.\n"
				"2. Set Clean Boot failed.\n"
				"Please manually check IMEI/BT/WiFi on the phone.";
        return ret;
    }

    return ret;
}

//---------------------------------------------------------------------------
int  tboot_1::DownloadYuSuFourInOne(void)
{

    // download
    int ret;

    ret = DownloadYuSu();
        if ( S_DONE != ret ) {
        return ret;
    }
        
    if(g_bUsbMode) {     
        Sleep(1000);
    }
    // Reset progress bar and status bar
    Synchronize( ResetDL_FourInOne_Info );
    Synchronize( ResetFakeProgress );
    // enter meta to write IMEI/BT/WiFi
    ret = EnterMETAUpdateNVRAM();
    if ( META_SUCCESS != ret ) {
         // Display download succeed message
        asMsg = "Download is DONE, but NVRAM IMEI/BT/WiFi operation does not finish!\n"
        		"[Possible Reason]:\n"
        		"1. Write IMEI/BT/WiFi failed.\n"
        		"2. Set Clean Boot failed.\n"
        		"Please manually check IMEI/BT/WiFi on the phone.";
        return ret;
    }

    return ret;
}

#if 0
//---------------------------------------------------------------------------
int  tboot_1::FormatDownloadFourInOne(void)
{
    int ret;
    // Format
    ret = Auto_Format_With_WatchDog();
    if ( S_DONE != ret ) {
        asMsg = "[Format -> Download -> Write IMEI/BT/WiFi] Format operation is not done!";
        return ret;
    }
    // download
    ret = Download();
        if ( S_DONE != ret ) {
        asMsg = "[Format -> Download -> Write IMEI/BT/WiFi] Download operation is not done!";
        return ret;
    }
    // Reset progress bar and status bar
    Synchronize( ResetDL_FourInOne_Info );
    Synchronize( ResetFakeProgress );
    // enter meta to write IMEI/BT/WiFi
    ret = EnterMETAUpdateNVRAM();
    if ( META_SUCCESS != ret ) {
         // Display download succeed message
        asMsg = "[Format -> Download -> Write IMEI/BT/WiFi]Download is DONE, but NVRAM IMEI/BT/WiFi operation does not finish!\n"
        		"[Possible Reason]:\n"
        		"1. Write IMEI/BT/WiFi failed.\n"
        		"2. Set Clean Boot failed.\n"
        		"Please manually check IMEI/BT/WiFi on the phone.";
        return ret;
    }

    return ret;
}
#endif

//---------------------------------------------------------------------------
int  tboot_1::FormatDownloadYuSuFourInOne(void)
{
    int ret;
    
    // Format->download
    ret = FormatDownloadYuSu();
        if ( S_DONE != ret ) {
        asMsg = "[Format -> Download -> Write IMEI/BT/WiFi] Download operation is not done!";
        return ret;
    }
        
    if(g_bUsbMode) {     
        Sleep(1000);
    }    
    // Reset progress bar and status bar
    Synchronize( ResetDL_FourInOne_Info );
    Synchronize( ResetFakeProgress );
    // enter meta to write IMEI/BT/WiFi
    ret = EnterMETAUpdateNVRAM();
    if ( META_SUCCESS != ret ) {
         // Display download succeed message
        asMsg = "[Format -> Download -> Write IMEI/BT/WiFi]Download is DONE, but NVRAM IMEI/BT/WiFi operation does not finish!\n"
        		"[Possible Reason]:\n"
        		"1. Write IMEI/BT/WiFi failed.\n"
        		"2. Set Clean Boot failed.\n"
        		"Please manually check IMEI/BT/WiFi on the phone.";
        return ret;
    }

    return ret;
}
#if 0
//---------------------------------------------------------------------------
int tboot_1::Format( void )
{
    int ret;

    if( RESET_TO_FACTORY == g_FormatOption )
    {
        // set error code mode to META
    	ErrorLookup::SetErrorCodeMode(META);
//        g_error_code_mode = META;

        // go to META mode to reset factory default
        ret = EnterMETAResetFactoryDefault( );
        if( S_DONE != ret ) return ret;
    }
    else {

        // fill the flash format argurment
//        ArgFlashFormat();

        Logger::GetLogger().Log(Logger::Debug,
        		"Format start addr: %x, and length: %x (%s,%d)",
        		g_ulNandFormatStartAddr, g_ulNandFormatLength,
        		__FILE__, __LINE__);
        // call flash format api
//        ret = FlashFormat(&com, &arg, &result, &fmt_arg, &fmt_result,NULL, &g_stopflag);
        ret = FlashFormat_internal();
        g_ulNandFormatLengthByDAReport = result.m_da_report.m_nand_flash_size;
        
        if( S_DONE != ret ) return ret;
    }

    return ret;
}
#endif
//---------------------------------------------------------------------------
int tboot_1::Auto_Format_Without_WatchDog( void )
{
    int ret;

    //-1. Connect and get the HW information
    ArgFlashToolConnect(cn_arg, cn_result);
    unsigned char  com_port = (g_bUsbMode || g_bUsbDLDA) ? GetUSBVCOMNumByPortName(m_strPort)  : COM_PORT;    

    int  force_charge = /*g_bUsbModeWithBattery ? 0 : 1*/GetBatteryStatus();
    LOGD("FlashDownload_internal: force_charge(%d)", force_charge);
    if (!g_bUsbDLDA) {
        ret = FlashTool_Connect(com_port, &cn_arg, &cn_result, NULL, &g_stopflag,
    			&g_ft_handle,force_charge);
    } else {
        ret = FlashTool_NandUtil_Connect( com_port, &cn_arg, &cn_result, &g_stopflag, &g_ft_handle);
    }
	if (S_DONE != ret) {
		FlashTool_Disconnect(&g_ft_handle);
		return ret;
	}

    ErrorLookup::SetErrorCodeMode(FLASHTOOL);
    //std::string targetStorage = GetStorageByDAReport(cn_result);
    /*if(!g_platform_info.isStorageMatched(targetStorage))*/
    if(!CheckStorageByDAReport())
    {
         LOGD("Storage not matched.");
	  FlashTool_Disconnect(&g_ft_handle);
	  return FT_STORAGE_ERROR;
    }

    ErrorLookup::SetErrorCodeMode(BROM);
    bool isDynamicLayout = false;
    g_platform_info.setChipName(cn_result.m_da_report.m_bbchip_name);
    if( g_platform_info.getPlatformConfig().supportLogicalAddress()) {
        isDynamicLayout = true; //Smart Phone Platform after MT6516 will apply dynamic layout
    } else {
        isDynamicLayout = false;
    }

    FlashTool_Format_Arg       fmt_arg;
    FlashTool_Format_Result    fmt_res;    
    ret = ArgFlashToolAdvancedFormat(fmt_arg, fmt_res, cn_result, true, isDynamicLayout);
    if(S_DONE != ret) {
        FlashTool_Disconnect(&g_ft_handle);
        return ret;
    }
    
    ret = FlashTool_Format(g_ft_handle,
                     &fmt_arg, &fmt_res);

    if(S_DONE != ret) {
        FlashTool_Disconnect(&g_ft_handle);
        return ret;
    }

    ret = FlashTool_Disconnect(&g_ft_handle);
    if(S_DONE != ret) {
        return ret;
    }

    return ret;
}

//---------------------------------------------------------------------------
int tboot_1::Auto_Format_Without_Disconnect( void )
{
    int ret;  

    //-1. Connect and get the HW information
    ArgFlashToolConnect(cn_arg, cn_result);
    unsigned char  com_port = (!g_bUsbMode) ? COM_PORT : GetUSBVCOMNumByPortName(m_strPort);
    
    int  force_charge = /*g_bUsbModeWithBattery ? 0 : 1*/GetBatteryStatus();
    LOGD("FlashDownload_internal: force_charge(%d)", force_charge);
    ret = FlashTool_Connect( com_port, &cn_arg, &cn_result, NULL, &g_stopflag, &g_ft_handle,force_charge);
    if( S_DONE != ret ) {
        return ret;
    }

    bool isDynamicLayout = false;
    g_platform_info.setChipName(cn_result.m_da_report.m_bbchip_name);
    if( g_platform_info.getPlatformConfig().supportLogicalAddress() ) {
        isDynamicLayout = true; //Smart Phone Platform after MT6516 will apply dynamic layout
    } else {
        isDynamicLayout = false;
    }

	ErrorLookup::SetErrorCodeMode(FLASHTOOL);
    //if( FORMAT_DOWNLOAD == g_FormatOption ){
    	LOGD(string("Auto_Format_Without_Disconnect: The load to be downloadeded is for ").append(g_platform_info.getLoadPlatformName()).c_str());
    	LOGD(string("Auto_Format_Without_Disconnect: Target platform by DA report is ").append(g_platform_info.getTargetPlatformName()).c_str());
    	if( !g_platform_info.isPlatformMatched() ) {
            FlashTool_Disconnect( &g_ft_handle );
            return FT_DL_PLATFORM_ERROR;
        }
   // }
	ErrorLookup::SetErrorCodeMode(BROM);

    if( S_DONE != ret ) {
        FlashTool_Disconnect( &g_ft_handle );
        return ret;
    }

    FlashTool_Format_Arg       fmt_arg;
    FlashTool_Format_Result    fmt_res;
    
    ret = ArgFlashToolAdvancedFormat(fmt_arg, fmt_res, cn_result, false, isDynamicLayout);
    if(S_DONE != ret) {
        FlashTool_Disconnect(&g_ft_handle);
        return ret;
    }
    
    ret = FlashTool_Format(g_ft_handle,
                     &fmt_arg, &fmt_res);

    if(S_DONE != ret) {
        FlashTool_Disconnect(&g_ft_handle);
    }

    return ret;   
}

//---------------------------------------------------------------------------
#if 0
int tboot_1::Auto_Format_With_WatchDog( void )
{
    int ret;

    //-1. Connect and get the HW information
    ArgFlashToolConnect(cn_arg, cn_result);
    unsigned char  com_port = (!g_bUsbMode) ? COM_PORT : GetUSBVCOMNumByPortName(m_strPort);
    
    ret = FlashTool_Connect( com_port, &cn_arg, &cn_result, NULL, &g_stopflag, &g_ft_handle);

    if( S_DONE != ret ) {
        FlashTool_Disconnect( &g_ft_handle );
        return ret;
    }

    FlashTool_Format_Arg       fmt_arg;
    FlashTool_Format_Result    fmt_res;
    
    ArgFlashToolAdvancedFormat(fmt_arg, fmt_res, cn_result, false);
 
    ret = FlashTool_Format(g_ft_handle, &fmt_arg, &fmt_res);
    if(S_DONE != ret)
    {
        FlashTool_Disconnect(&g_ft_handle);
        return ret;
    }

    ret  = FlashTool_EnableWatchDogTimeout(g_ft_handle, 5000);
    if(S_DONE != ret)
    {
        FlashTool_Disconnect(&g_ft_handle);
        return ret;
    }

    ret = FlashTool_Disconnect(&g_ft_handle);
    if(S_DONE != ret)
    {
    	return ret;
    }

    if(g_bUsbMode)
    {
        //Sleep 10s to avoid conflict with target waiting for reset
        LOGD("USB DL DA: Sleep 10s to avoid conflict with target waiting for reset.");
        Sleep(10000);
    }
    
    return ret;
   
}
#endif
#if 0
//---------------------------------------------------------------------------
int tboot_1::FlashToolAPITest ( void )
{
    //- 1. connect
    ArgFlashToolConnect( cn_arg, cn_result );
    int ret = FlashTool_Connect( COM_PORT, &cn_arg, &cn_result, NULL, &g_stopflag, &g_ft_handle);
    if( S_DONE != ret ) {
        return ret;
    }

    //- 2. call RepairTool_GetExceptionRecord
    /*ret = RepairTool_GetExceptionRecord( g_ft_handle, MainForm->ed_ExceptionLog->Text.c_str(), MainForm->ed_SaveExceptionLog->Text.c_str());
    if( S_DONE != ret ) {
        FlashTool_Disconnect( &g_ft_handle );
        return ret;
    }*/

    //- N. disconnect
    FlashTool_Disconnect( &g_ft_handle );

    return ret;
}
//---------------------------------------------------------------------------
int tboot_1::RomWriter( void )
{
    //- 1. Connect
    ArgFlashToolConnect( cn_arg, cn_result );
    int ret = FlashTool_Connect( COM_PORT, &cn_arg, &cn_result, NULL, &g_stopflag, &g_ft_handle );
    if( S_DONE != ret ) return ret;


    //- 2. Change Baudrate
    FlashTool_ChangeBaudrate_Arg    cb_arg;
    ArgFlashToolChangeBaudrate( cb_arg );
    ret = FlashTool_ChangeBaudrate( g_ft_handle, &cb_arg);
    if( S_DONE != ret ) {
        FlashTool_Disconnect( &g_ft_handle );
        return ret;
    }

    //- 3. Extract NFB
    /*FlashTool_Progress_Arg       pgs_arg;
    ArgFlashToolProgress( pgs_arg );
    ret = FlashTool_ExtractNFB( g_ft_handle, MainForm->ed_SaveExtractNFB->Text.c_str(), &pgs_arg );
    if( S_DONE != ret ) {
        FlashTool_Disconnect( &g_ft_handle );
        return ret;
    }
    */
    //- N. Disconnect
    FlashTool_Disconnect( &g_ft_handle );

    return ret;
}
#endif
/*
//---------------------------------------------------------------------------
int tboot_1::EnterMETABackup ( void )
{
    g_error_code_mode = META;

	// update ResetFakeProgress
	progress_hint           = "Enter Meta to Backup Calibration Data ...";
	progress_forecolor      = (TColor) (0x00DBB0CC);
	Synchronize( ResetFakeProgress );

    // connect target in META Mode
    META_Connect_Req	    meta_con_req;
	META_Connect_Report	    meta_con_report;
    int ret;

    ArgMETAConnectWithTarget( meta_con_req, meta_con_report);
	if( META_SUCCESS != ( ret = META_ConnectWithTarget( &meta_con_req, &g_stopflag, &meta_con_report)) ) {
        // disconnect
        META_DisconnectWithTarget();
		// stop fake progress
		Synchronize( StopFakeProgress );
		return ret;
	}

    // create backup folder
    if ( !CreateBackupDir() ) {
        asMsg = "Create Backup Folder Failed.";
        Synchronize( StopFakeProgress );
        return -1;
    }

    // delete all backup file
    char *path = new  char[ g_BackupCalibrationDataFolderPath.Length() +  1 ];
    strcpy( path ,  g_BackupCalibrationDataFolderPath.c_str() );
    if( META_SUCCESS != ( ret = META_DeleteAllFilesInBackupFolder(  path  )) ) {
        // disconnect
        META_DisconnectWithTarget();
		// stop fake progress
		Synchronize( StopFakeProgress );
		return ret;
	}
    free( path );


    // backup calibration data
    if( META_SUCCESS != ( ret = META_QueryIfFunctionSupportedByTarget ( 5000, "META_MISC_GetIMEILocation" )) ) {

        // other error message, return
        if ( META_FUNC_NOT_IMPLEMENT_YET != ret )  {
            // disconnect
		    META_DisconnectWithTarget();
		    // stop fake progress
		    Synchronize( StopFakeProgress );
	        return ret;
        }

        MISC_BACKUP_REQ_T   meta_backup_req;
        ArgMETABackupCalibrationData( meta_backup_req );
        if( META_SUCCESS != ( ret = META_BasicBackupCalibrationData( &meta_backup_req, &g_stopflag )) ) {
            // disconnect
		    META_DisconnectWithTarget();
            // stop fake progress
		    Synchronize( StopFakeProgress );
            return ret;
        }

    } else {

        // support META_MISC_GetIMEILocation fucntion (patched load)
        // call META backup calibration data api (for patched load)
        MISC_BACKUP_REQ_T   meta_backup_req;
        ArgMETABackupCalibrationData( meta_backup_req );
        if( META_SUCCESS != ( ret = META_BackupCalibrationData( &meta_backup_req, &g_stopflag )) ) {
            // disconnect
		    META_DisconnectWithTarget();
		    // stop fake progress
		    Synchronize( StopFakeProgress );
	        return ret;
	    }

    }


    // to check if the backup is compelete
    BACKUP_RESULT_T cnf;
    ArgMETAGetBackupResultInfo( cnf );
    AnsiString  folderPath = "";
    folderPath =  g_BackupCalibrationDataFolderPath + "\\";
    char* fpath =  new  char[ folderPath.Length() +  1 ];
    strcpy ( fpath, folderPath.c_str() );
	if( META_SUCCESS != ( ret =  META_GetBackupResultInfo( fpath , &cnf ) ) ) {
        // disconnect
		META_DisconnectWithTarget();
        // stop fake progress
		Synchronize( StopFakeProgress );
        return ret;
    }
    free ( fpath );


    // call watchdog to reboot the phone
    FtWatchDog  meta_watchdog_req;
    ArgMETAEnableWatchDogTimer( meta_watchdog_req );
	if( META_SUCCESS != ( ret = META_EnableWatchDogTimer( 5000, &meta_watchdog_req) ) ) {
        // disconnect
		META_DisconnectWithTarget();
		// stop fake progress
		Synchronize( StopFakeProgress );
        return ret;
	}

    // disconnect
	META_DisconnectWithTarget();

    // stop fake progress
	Synchronize( FinishFakeProgress );

    return ret;
}
//---------------------------------------------------------------------------
int  tboot_1::EnterMETARestore ( void )
{
    g_error_code_mode       = META;

    // update ResetFakeProgress
	progress_hint           = "Enter Meta to Restore Calibration Data ...";
	progress_forecolor      = (TColor)(0x00FFCCCC);
	Synchronize( ResetFakeProgress );

    // clear hw status
    MainForm->sb_Main->Panels->Items[5]->Text = "";
    MainForm->m_HWStatus->Panels->Items[0]->Text = "";
    MainForm->m_HWStatus->Panels->Items[1]->Text = "";
    MainForm->m_HWStatus->Panels->Items[2]->Text = "";
    MainForm->m_HWStatus->Panels->Items[3]->Text = "";
  	MainForm->m_HWStatus->Hint = "";


    // connect with meta
    // fill META Connet with Target paprameter
    META_Connect_Req	    meta_con_req;
	META_Connect_Report	    meta_con_report;
    int ret;

    ArgMETAConnectWithTarget( meta_con_req, meta_con_report );
	if( META_SUCCESS != ( ret = META_ConnectWithTarget( &meta_con_req, &g_stopflag, &meta_con_report )) ) {
        // disconnect
        META_DisconnectWithTarget();
		// stop fake progress
		Synchronize( StopFakeProgress );
		return ret;
	}


    // check if the backup folder exist
    if ( ! CheckBackupDirExist() ) {

        asMsg = "Backup folder does not exist. Please select the option 'Backup->Download->Restore' to backup first.";
        // disconnect
        META_DisconnectWithTarget();
		// stop fake progress
		Synchronize( StopFakeProgress );

        return -1;
    }


     // enter meta mode to reset the FAT area to factory default
    if( RESET_TO_FACTORY == g_FormatAfterDownloadOption )
    {
        // call reset to factory default
    	if( META_SUCCESS != ( ret = META_NVRAM_ResetToFactoryDefault( 40000 ) ) ) {
            // disconnect
		    META_DisconnectWithTarget();
		    // stop fake progress
		    Synchronize( StopFakeProgress );
	    	return ret;
	    }
    }


    // backup calibration data
    if( META_SUCCESS != (ret = META_QueryIfFunctionSupportedByTarget ( 5000, "META_MISC_GetIMEILocation" )) ) {

        // other error message, return
        if ( META_FUNC_NOT_IMPLEMENT_YET != ret )  {
            // disconnect
		    META_DisconnectWithTarget();
		    // stop fake progress
		    Synchronize( StopFakeProgress );
	        return ret;
        }

        // not support META_MISC_GetIMEILocation fucntion
        // call basic META restore calibration data api (for non-patched load)
        MISC_RESTORE_REQ_T    meta_restore_req;
        ArgMETARestoreCalibrationData( meta_restore_req );
        if( META_SUCCESS != ( ret = META_BasicRestoreCalibrationData( &meta_restore_req,  &g_stopflag )) ) {
            // disconnect
            META_DisconnectWithTarget();
		    // stop fake progress
		    Synchronize( StopFakeProgress );
		    return ret;
	    }
    } else {

        // support META_MISC_GetIMEILocation fucntion
        // call META restore calibration data api (for patched load)
        MISC_RESTORE_REQ_T    meta_restore_req;
        ArgMETARestoreCalibrationData( meta_restore_req );
        if( META_SUCCESS != ( ret = META_RestoreCalibrationData( &meta_restore_req,  &g_stopflag ) ) ) {
            // disconnect
		    META_DisconnectWithTarget();
		    // stop fake progress
		    Synchronize( StopFakeProgress );
	        return ret;
	    }
    }


    // to check if the restore sccuess
    RESTORE_RESULT_T cnf;
    ArgMETAGetRestoreResultInfo( cnf );
    AnsiString  folderpath  = "";
    folderpath = g_BackupCalibrationDataFolderPath + "\\";
    char* fpath =  new  char[ folderpath.Length() +  1 ];
    strcpy ( fpath, folderpath.c_str() );
	if( META_SUCCESS != ( ret = META_GetRestoreResultInfo ( fpath , &cnf ) ) ) {
        // disconnect
		META_DisconnectWithTarget();
        // stop fake progress
		Synchronize( StopFakeProgress );
        return ret;
    }
    free ( fpath );



    // delete all backup file
    char *path = new  char[ g_BackupCalibrationDataFolderPath.Length() +  1 ];
    strcpy( path ,  g_BackupCalibrationDataFolderPath.c_str() );
    if( META_SUCCESS != ( ret = META_DeleteAllFilesInBackupFolder ( path ) ) ) {
        // disconnect
        META_DisconnectWithTarget();
		// stop fake progress
		Synchronize( StopFakeProgress );
		return ret;
	}
    free ( path );


    // disconnect
	META_DisconnectWithTarget();

    // remove backup folder
    if ( !RemoveBackupDir() )
    {
        asMsg = "Remove Backup Folder Failed.";
        Synchronize( StopFakeProgress );
        // stop fake progress
	    Synchronize( FinishFakeProgress );
        return -1;
    }

	// stop fake progress
	Synchronize( FinishFakeProgress );

    return ret;

} */

//---------------------------------------------------------------------------
int  tboot_1::EnterMETABackup ( void )
{
	assert(0 && "deprecated function:EnterMETABackup");
	return 0;
#if 0
	ErrorLookup::SetErrorCodeMode(EBOOT);

    META_RESULT  META_Result;
    EBOOT_RESULT EBOOT_Result;
    int ret;
    int meta_handle = 0;
    unsigned char  com_number = COM_PORT;   
    const int STEP = 4;    
 
    // Step: Scan usb ports
    EBOOT_Result = ScanMETAUSBPorts(com_number);
    if(EBOOT_SUCCESS != EBOOT_Result) {
        return EBOOT_Result;
    }

    ErrorLookup::SetErrorCodeMode(META);   
    // Step: Initial SP Meta
    ret = WM_META_GetAvailableHandle_Wrapper(&meta_handle);
    if(META_SUCCESS != ret) {
        m_as_err_msg = "[META Restore INFO]: WM_META_GetAvailableHandle fails!";
        LOGE(m_as_err_msg.c_str());
        ClearSPMeta( meta_handle );
       return ret;
    }
    
    ret = WM_META_Init_r_Wrapper(meta_handle);
    if(META_SUCCESS != ret) {
        m_as_err_msg = "[META Backup INFO]: WM_META_Init_r fails!";
        LOGE(m_as_err_msg.c_str());
        ClearSPMeta( meta_handle );
       return ret;
    }    
    m_meta__progress_value = int(100 * 1 / STEP);
    SyncStartFakeProgress();

    // Step: Connect in SP Meta
    ret = WM_META_ConnectInMetaMode_r_Wrapper( meta_handle, &g_stopflag, com_number);
    if( META_SUCCESS != ret ) {
        m_as_err_msg = "[META Backup INFO]: WM_META_ConnectInMetaMode_r fails!";
        LOGE(m_as_err_msg.c_str());
        ClearSPMeta( meta_handle );
        return ret;
    }
    m_meta__progress_value = int(100 * 2 / STEP);
    SyncStartFakeProgress();

    
    //***********Verifying new API SP_META_GetChipID***********//
    E_CHECK_DIR_STATUS dirStatus;
    if(m_bUseChipID){
        //try using Chip ID
        unsigned char chipId[20] = {0};
        const int CHIP_ID_LEN = 16;
        LOGD("entering SP_META_GETChipID...");
        ret = WM_META_GetChipID_Wrapper(meta_handle, 10000, chipId);

        if(ret == META_SUCCESS){
            //got chip id
            dirStatus = FileUtils::CheckDirByChipID(chipId, CHIP_ID_LEN, m_strBackupFolder, true);
            LOGD("Use Chip ID as backup folder name.");
        }else{
            //use com port instead
            dirStatus = FileUtils::CheckDirByCOMPort(com_number, m_strBackupFolder);
            LOGD("SP_META_GETChipID Not support! Use COM port as backup folder name.");
        }
    }else{
        //use com port
        dirStatus = FileUtils::CheckDirByCOMPort(com_number, m_strBackupFolder);
        LOGD("Use COM port as backup folder name.");
    }

    //error handling of creating backup folder
    if ( CREATE_DIR_FAIL == dirStatus ) {
        m_as_err_msg.printf( "[Hint] Create backup directory: %s fails!", m_strBackupFolder);
        LOGE(m_as_err_msg.c_str());
        ClearSPMeta( meta_handle );
        return META_FAILED;
    } else if ( DIR_EXIST == dirStatus ) {
        std::ostringstream ss;
        ss<<"[Hint]\r\nBackup destination folder: \r\n"
            <<m_strBackupFolder
            <<"\r\nexists already!"
            <<"\r\nPlease move existing data of this folder to another place,"
            " then delete this folder before executing backup!";
        m_as_err_msg = ss.str().c_str();
        LOGW(m_as_err_msg.c_str());
        ClearSPMeta( meta_handle );
        //pop up explorer
        ShellExecute(NULL, "open", m_strBackupFolder.c_str(), NULL, NULL, SW_SHOWNORMAL);
        return META_FAILED;
    }
    LOGD(string("[Hint]: Nvram Backup directory is: ")
        .append(m_strBackupFolder));

    const string mapFile = m_strBackupFolder + "\\" + MapFileName;
    const string datFile = m_strBackupFolder + "\\" + DatFileName;

    // Step4: Backup NVRAM
    // Unit of System time must second
    unsigned int ms_timeout=10000;
    NvramBackupMap nvramBackupMap("NVRAM_BACKUP.INI");
    nvramBackupMap.UpdateNvramBackupINIStatus();

    LOGD(string("[NVRAM Backup INFO]: Timeout for WM_META_Nvram_Backup is ")
    		.append(NumberToString(ms_timeout).append(" s.")));

    if(nvramBackupMap.IsReadNvramBackupINISuccess())
    {
    	string strNvramBackupFliterNames = nvramBackupMap.GetNvramBackupFilterFloderNames();
    	int delCount = nvramBackupMap.GetFilterFloderCount();
    
    	LOGD(string("[NVRAM Backup INFO]The folders will be deleted to backup: ")
    			.append(strNvramBackupFliterNames));
    	//ret = WM_META_Nvram_Backup_r_Wrapper(meta_handle, ms_timeout, mapFile.c_str(), datFile.c_str());
    	ret = WM_META_Nvram_Backup_Custom_r_Wrapper(meta_handle, ms_timeout,
    	    			                                mapFile.c_str(), datFile.c_str(),
    	    			                                strNvramBackupFliterNames.c_str(),
                                                        delCount, 0);
    }
    else
    {
    	m_as_err_msg = "[META Backup INFO]: Read NVRAMBackup ini file fails!";
        LOGE(m_as_err_msg.c_str());
    	ClearSPMeta( meta_handle );
    	return -1;
    }

    if(META_SUCCESS != ret){
        m_as_err_msg = "[META Backup INFO]: WM_META_Nvram_Backup_Custom_r fails!";
        LOGE(m_as_err_msg.c_str());
        ClearSPMeta( meta_handle );
        return ret;
    }
    m_meta__progress_value = int(100 * 3 / STEP);
    SyncStartFakeProgress();
    //The second parameter is delay time for reboot, the unit must second.
    WM_META_RebootTarget_r_Wrapper(meta_handle, 5);
    //WM_META_ShutDownTarget_r_Wrapper(meta_handle);
    WM_META_DisconnectWithTarget_r_Wrapper(meta_handle);
    WM_META_Deinit_r_Wrapper(&meta_handle);

    SendMessage(frm_Processing->Handle, AP_SPFT_META_EXIT, 0, 0);
    Synchronize( FinishFakeProgress );

    LOGD("[META Backup INFO]: Exit EnterMETABackup Function.");

    return ret;
#endif
}


//---------------------------------------------------------------------------
int  tboot_1::EnterMETARestore ( void )
{
	assert(0 && "deprecated function: EnterMETARestore");
	return 0;
#if 0
	ErrorLookup::SetErrorCodeMode(EBOOT);

    META_RESULT  META_Result;
    EBOOT_RESULT EBOOT_Result;
    int ret;
    int meta_handle = 0;
    const int STEP = 5;
    unsigned char com_number = COM_PORT;

    PostMessage(frm_Processing->Handle, AP_SPFT_META_RESTORE_NVRAM, 0, 0); 
    // Step: Scan usb ports
    EBOOT_Result = ScanMETAUSBPorts(com_number);
    if(EBOOT_SUCCESS != EBOOT_Result) {
        return EBOOT_Result;
    }
    
    ErrorLookup::SetErrorCodeMode(META); 
    // Step: connect with meta
    m_meta__progress_value = int(100 * 1 / STEP);
    SyncStartFakeProgress();

    ret = WM_META_GetAvailableHandle_Wrapper(&meta_handle);
    if(META_SUCCESS != ret) {
        m_as_err_msg = "[META Restore INFO]: WM_META_GetAvailableHandle fails!";
        LOGE(m_as_err_msg.c_str());
        ClearSPMeta( meta_handle );
       return ret;
    }
    
    // Step: Initial SP Meta
    ret = WM_META_Init_r_Wrapper(meta_handle);
    if(META_SUCCESS != ret) {
        m_as_err_msg = "[META Restore INFO]: WM_META_Init_r fails!";
        LOGE(m_as_err_msg.c_str());
        ClearSPMeta( meta_handle );
       return ret;
    }    
    m_meta__progress_value = int(100 * 2 / STEP);
    SyncStartFakeProgress();

    // Step: Connect in SP Meta
    ret = WM_META_ConnectInMetaMode_r_Wrapper( meta_handle, &g_stopflag, com_number);
    if( META_SUCCESS != ret ) {
        m_as_err_msg = "[META Restore INFO]: WM_META_ConnectInMetaMode_r fails!";
        LOGE(m_as_err_msg.c_str());
        ClearSPMeta( meta_handle );
        return ret;
    }
    m_meta__progress_value = int(100 * 3 / STEP);
    SyncStartFakeProgress();


    if(m_bUseChipID){
        unsigned char chipId[20] = {0};
        const int CHIP_ID_LEN = 16;
        LOGD("entering SP_META_GETChipID...");
        ret = WM_META_GetChipID_Wrapper(meta_handle, 10000, chipId);
        if(ret == META_SUCCESS){
            //got chip id
            meta_backup_folder = FileUtils::ComposeDirNameByChipID(chipId, CHIP_ID_LEN);
            LOGD("Use Chip ID as backup folder name.");
        }else{
            //use com port instead
            m_bUseChipID = false;
            meta_backup_folder = FileUtils::ComposeDirNameByCOMPort(COM_PORT);
            LOGD("SP_META_GETChipID Not support! Use COM port as backup folder name.");
        }
    }else{
        //using com port
        //use com port instead
        LOGD("Use COM port as backup folder name.");
        meta_backup_folder = FileUtils::ComposeDirNameByCOMPort(COM_PORT);
    }
    
    //check backup folder
	E_CHECK_DIR_STATUS dirStatus = FileUtils::CheckDirectory(meta_backup_folder);

    if(dirStatus != DIR_EXIST){
        //error
        m_as_err_msg.printf("[META Restore INFO]: Restore path (%s) does not exist",
        		meta_backup_folder.c_str());
        LOGE(m_as_err_msg.c_str());
        ClearSPMeta( meta_handle );
        return META_FAILED;
    }

    if (! IsNvramFilesExist(meta_backup_folder)){
        m_as_err_msg.printf("[META Restore INFO]: %s or %s does not exist under %s, please check first before restore!",
            MapFileName, DatFileName, meta_backup_folder);
        LOGE(m_as_err_msg.c_str());
        ClearSPMeta( meta_handle );
        return META_FAILED;
    }



    // Step: Restore NVRAM
    unsigned int ms_timeout=60000;
    const string mapFile = meta_backup_folder + "\\" + MapFileName;
    const string datFile = meta_backup_folder + "\\" + DatFileName;
    
    ret = WM_META_Nvram_Restore_r_Wrapper(meta_handle, ms_timeout, mapFile.c_str(), datFile.c_str());

    if(META_SUCCESS != ret){
        m_as_err_msg = "[META Restore INFO]: WM_META_Nvram_Restore_r fails!";
        LOGE(m_as_err_msg.c_str());
        ClearSPMeta( meta_handle );
        return ret;        
    }
    m_meta__progress_value = int(100 * 4 / STEP);
    SyncStartFakeProgress();

    // backup NVRAM to BinRegion (only WinMo need this step)
    if( g_project_mode == DUMA )
    {
        META_Result = EnterMETABackupNvram2BinRegion();
    	if (META_SUCCESS != META_Result)
        {
    		return META_Result;
        }
    }
    //TODO: check if MT6573 need SetCleanBoot
    else if ( g_project_mode == YuSu )
    {
        META_Result = EnterMETASetCleanBootFlag_r(meta_handle);
        if (META_SUCCESS != META_Result)
        {
        	m_as_err_msg = "[META Restore INFO]: EnterMETASetCleanBootFlag_r fails!";
            LOGE(m_as_err_msg.c_str());
            ClearSPMeta( meta_handle );
        	return META_Result;
        }
    }

    WM_META_ShutDownTarget_r_Wrapper(meta_handle);
    WM_META_DisconnectWithTarget_r_Wrapper(meta_handle);
    WM_META_Deinit_r_Wrapper(&meta_handle);

    SendMessage(frm_Processing->Handle, AP_SPFT_META_EXIT, 0, 0);
    Synchronize( FinishFakeProgress );

    if(m_bUseChipID == false){
        LOGD(string("[META Restore INFO]: Remove diretory after restored: ").append(m_strBackupFolder));
        if (!FileUtils::DeleteDirectory(m_strBackupFolder)) {
            LOGE("Remove diretory failed.");
        }
    }
    return ret;
#endif
}

//---------------------------------------------------------------------------
EBOOT_RESULT tboot_1::SP_BootAsMetaWrapper(int p_comport,COMM_BAUDRATE p_baud, int* p_BootStop)
{
     EBOOT_RESULT EBOOT_Result = EBOOT_EXCEPTION;
     Meta_Boot_Arg meta_arg;
     meta_arg.read_retry_time = 0;		  // 0 means use default value 2400 times
     meta_arg.read_interval_timeout = 0;   // 0 means use default value 10 ms
     meta_arg.m_p_stopflag =  p_BootStop;
     // Try to connect into META mode 10 times
     for(int i=0; i < 10 ; i++)
     {
         if( BOOT_STOP == (*p_BootStop) )
         {
              EBOOT_Result = USER_PRESS_STOP_BUTTON;
              break;              
         }
         else
         {
              EBOOT_Result = SP_BootAsMeta(p_comport, p_baud, meta_arg);	// Eboot use baud 115200 to sync with target
              if(EBOOT_SUCCESS == EBOOT_Result)
              {
                  break;
              }
         }
     }
     
     return EBOOT_Result;
}

//---------------------------------------------------------------------------
META_RESULT  tboot_1::ModemNVRAMInit( const char* database )
{
    time_t start = 0;
    time_t end = 0;

    char str[512];

    strcpy( str, database );
    bool ok;

    unsigned long      m_ulNvramIdb;
    Variant            m_vNVRAM_db_variant;
    E_METAAPP_RESULT_T  m_eConfirmState;

    LOGD(string("Begin to record time: ").append(NumberToString(time(&start))).c_str());

    META_RESULT MetaResult = META_NVRAM_Init( str, &m_ulNvramIdb );

    LOGD(string("Finish to record time: ").append(NumberToString(time(&end))).c_str());
    LOGD(string("META_NVRAM_Init API costs: ").append(NumberToString(difftime(end, start))).c_str());

    return  MetaResult;
}

//---------------------------------------------------------------------------
META_RESULT  tboot_1::ApNVRAMInit(const int meta_handle, const char* database )
{
    char str[512];

    strcpy( str, database );

    unsigned long db;
    META_RESULT result;
	
    result = ( META_RESULT ) WM_META_NVRAM_Init_r_Wrapper(meta_handle, str, &db) ;

    return  result;

}

//---------------------------------------------------------------------------
META_RESULT  tboot_1::NVRAMInit(void)
{
    char str[512];

    strcpy( str, m_pModemDatabase );
    bool ok;

    unsigned long      m_ulNvramIdb;
    Variant            m_vNVRAM_db_variant;
    E_METAAPP_RESULT_T  m_eConfirmState;
    META_RESULT MetaResult = META_NVRAM_Init( str, &m_ulNvramIdb );

    if ((META_SUCCESS == MetaResult)||
        (META_MAUI_DB_INCONSISTENT == MetaResult)
       )
    {
        if (META_MAUI_DB_INCONSISTENT == MetaResult)
        {
            m_eConfirmState = METAAPP_NVRAM_DB_INCONSISTENT;
        }
        else
        {
            m_eConfirmState = METAAPP_SUCCESS;
        }
        GetSupportInfoFromNVRAMDB();
//        META_NVRAM_SWC_RetrieveChangeList();
//        m_vNVRAM_db_variant = TVariant((long) m_ulNvramIdb);
    //    GetSupportInfoFromNVRAMDB();
    }
    else
    {
        m_eConfirmState = METAAPP_NVRAM_INIT_FAIL;
    }


    E_METAAPP_RESULT_T state = m_eConfirmState;
    if (METAAPP_SUCCESS != state )
    {
        if (METAAPP_NVRAM_DB_INCONSISTENT == state )
        {
            m_as_err_msg = "NVRAM database file is inconsistent with target load";
            Synchronize( ErrorMessage );
        }
        else
        {
            m_as_err_msg = "Execution Failure : Initialize NVRAM database file failed";
            Synchronize( ErrorMessage );
        }
        // Clear up progress bar
        Synchronize( StopFakeProgress );
    }
    
    return  MetaResult;
}
//---------------------------------------------------------------------------
void tboot_1::GetSupportInfoFromNVRAMDB()
{
    int rid_num;
    bool b2ndIMEISupport = true;
    META_RESULT MetaResult = META_NVRAM_GetRecNum("NVRAM_EF_IMEI_IMEISV_LID", &rid_num);
    if ((META_SUCCESS != MetaResult) || (1 == rid_num))
    {
        b2ndIMEISupport = false;
    }
    m_b2ndImeiSupport = b2ndIMEISupport;
    Synchronize( Sync2ndImeiSupport );
        
/*
    #ifndef  SERVICE_CENTER


    PostMessage(m_sHandle.handle[MSEL_IMEI_DOWNLOAD],
                WM_ML_IMEI_SECOND_CNF,
                (WPARAM)m_b2ndIMEISupport,
                0
                );
    #endif
*/
}

//---------------------------------------------------------------------------
int tboot_1::UploadIMEI(S_IMEI_T &sIMEIupload, int RID)
{
   // upload IMEI from flash
   FT_NVRAM_READ_REQ  m_psNVRAM_ReadReq;
   FT_NVRAM_READ_CNF  m_sNVRAM_ReadCnf;
   char        *m_cIMEIBuf[2];
   int          m_iIMEIBufSize;
   unsigned short m_usRID = RID;
   S_IMEISV_T       m_sIMEISVupload;
   S_IMEI_T         m_sIMEIupload;
   META_RESULT  MetaResult;
   //int ret;
   m_iIMEIBufSize = 0;
   m_cIMEIBuf[0] = NULL;
   m_cIMEIBuf[1] = NULL;

   //fill NVRAM read parameters
   if (NULL == m_cIMEIBuf[m_usRID-1])
   {
        MetaResult = META_NVRAM_GetRecLen("NVRAM_EF_IMEI_IMEISV_LID",
                                                      &m_iIMEIBufSize);
        if (MetaResult!=META_SUCCESS)
        {
            return METAAPP_FAIL;
        }
        m_cIMEIBuf[m_usRID-1] = new char[m_iIMEIBufSize];
    }
    m_psNVRAM_ReadReq.LID = "NVRAM_EF_IMEI_IMEISV_LID";
    m_psNVRAM_ReadReq.RID = m_usRID; // temp set to 1
    m_sNVRAM_ReadCnf.len = m_iIMEIBufSize;
    m_sNVRAM_ReadCnf.buf = m_cIMEIBuf[m_usRID-1];
    //read from flash
    MetaResult = META_NVRAM_Read_Ex(5000,
                                    &m_psNVRAM_ReadReq,
                                    &m_sNVRAM_ReadCnf);
    if (MetaResult != META_SUCCESS || m_sNVRAM_ReadCnf.status!= NVRAM_STATUS_SUCCESS)
    {
        return METAAPP_FAIL;
    }
    // decompose IMEI
    MetaResult = META_NVRAM_Decompose_IMEISV(&m_sIMEISVupload.s_IMEISV[m_usRID-1], m_cIMEIBuf[m_usRID-1], m_iIMEIBufSize);
    if (MetaResult != META_SUCCESS)
    {
        return METAAPP_FAIL;
    }

    for (int i=0; i<IMEI_ARRAY_LEN; i++)
    {
        m_sIMEIupload.c_imei[m_usRID-1][i] = m_sIMEISVupload.s_IMEISV[m_usRID-1].imei[i];
    }

    sIMEIupload= m_sIMEIupload;
    if(strlen(sIMEIupload.c_imei[RID-1])!=0)
    {
        AnsiString as_imei_checksum(sIMEIupload.c_imei[RID-1]);
        AnsiString as_imei = as_imei_checksum.SubString(1, MAX_IMEI_DIGIT_LEN);

        strcpy(sIMEIupload.c_imei[RID-1], as_imei.c_str());
    }

    if (NULL != m_cIMEIBuf[0])
    {
        delete [] m_cIMEIBuf[0];
        m_cIMEIBuf[0] = NULL;
    }
    if (NULL != m_cIMEIBuf[1])
    {
        delete [] m_cIMEIBuf[1];
        m_cIMEIBuf[1] = NULL;
    }
    
    return META_SUCCESS;
}
//---------------------------------------------------------------------------
int tboot_1::DownloadIMEI(S_IMEI_T &sIMEIDL, int RID )
{
    //download IMEI to flash
    FT_NVRAM_WRITE_REQ    sNVRAM_WriteReq;
    FT_NVRAM_WRITE_CNF    sNVRAM_WriteCnf;
    S_IMEISV_T       sIMEISVdownload;
    S_IMEI_T         sIMEIdownload;
    char        *cIMEIBuf[2];
    int          iIMEIBufSize;
    unsigned short usRID = RID;
    bool  bCheckChecksum;
    META_RESULT  MetaResult;
    //int ret;

    iIMEIBufSize = 0;
    cIMEIBuf[0] = NULL;
    cIMEIBuf[1] = NULL;
    bCheckChecksum = m_bCheckChecksum;


    unsigned short check_sum ;
    AnsiString as_check_sum;

    if(strlen(sIMEIDL.c_imei[usRID-1]) < MAX_IMEI_DIGIT_LEN )
    {
        META_NVRAM_Calculate_IMEI_CD(sIMEIDL.c_imei[usRID-1], &check_sum);
        as_check_sum = IntToStr(check_sum);
        strcat(sIMEIDL.c_imei[usRID-1],as_check_sum.c_str());
    }
   //set IMEI from IMEI form
    sIMEIdownload = sIMEIDL;  //Form_IMEI_setting->m_sIMEI
    for (int imei_idx = 0; imei_idx < 2; imei_idx++)
    {
        for (int i = 0; i < IMEI_ARRAY_LEN; i++)
        {
            sIMEISVdownload.s_IMEISV[imei_idx].imei[i] = sIMEIdownload.c_imei[imei_idx][i];
        }
    }

   // fill NVRAM write parameters
   if (NULL == cIMEIBuf[usRID-1])
    {
        MetaResult = META_NVRAM_GetRecLen("NVRAM_EF_IMEI_IMEISV_LID", &iIMEIBufSize);
        if(MetaResult != META_SUCCESS)
        {
            return METAAPP_FAIL ;
        }
        cIMEIBuf[usRID-1] = new char[iIMEIBufSize];
    }
    //Compose IMEI

    for (int i = 0; i < IMEI_ARRAY_LEN; i++)
    {
       sIMEISVdownload.s_IMEISV[usRID-1].imei[i] = sIMEIdownload.c_imei[usRID-1][i];
    }

    MetaResult = META_NVRAM_Compose_IMEISV_ex(&sIMEISVdownload.s_IMEISV[usRID-1], cIMEIBuf[usRID-1], iIMEIBufSize, bCheckChecksum);
    if (MetaResult != META_SUCCESS)
    {
        return METAAPP_FAIL;
    }

    sNVRAM_WriteReq.LID = "NVRAM_EF_IMEI_IMEISV_LID";
    sNVRAM_WriteReq.RID = usRID;
    sNVRAM_WriteReq.len = iIMEIBufSize;
    sNVRAM_WriteReq.buf = cIMEIBuf[usRID-1];
    //write to flash
    MetaResult = META_NVRAM_Write_Ex(5000,
                                    &sNVRAM_WriteReq,
                                    &sNVRAM_WriteCnf);
    if (MetaResult != META_SUCCESS ||sNVRAM_WriteCnf.status != NVRAM_STATUS_SUCCESS)
    {
        return METAAPP_FAIL;
    }

    if (NULL != cIMEIBuf[0])
    {
        delete [] cIMEIBuf[0];
        cIMEIBuf[0] = NULL;
    }
    if (NULL != cIMEIBuf[1])
    {
        delete [] cIMEIBuf[1];
        cIMEIBuf[1] = NULL;
    }
    
    return META_SUCCESS;
}

int tboot_1::WriteIMEItoNVRAM(S_IMEI_T &sIMEIdownload, int RID ,bool bCheckChecksum )
{
    //download IMEI to flash
    FT_NVRAM_WRITE_REQ    m_psNVRAM_WriteReq;
    FT_NVRAM_WRITE_CNF    m_psNVRAM_WriteCnf;
    S_IMEISV_T       m_sIMEISVdownload;
    S_IMEI_T         m_sIMEIdownload;
    char        *m_cIMEIBuf[2];
    int          m_iIMEIBufSize;
    unsigned short m_usRID = RID;
    bool  m_bCheckChecksum;
    META_RESULT  MetaResult;
    //int ret;

    m_iIMEIBufSize = 0;
    m_cIMEIBuf[0] = NULL;
    m_cIMEIBuf[1] = NULL;
    m_bCheckChecksum = bCheckChecksum;


    unsigned short check_sum ;
    AnsiString as_check_sum;

    if(strlen(sIMEIdownload.c_imei[m_usRID-1])< MAX_IMEI_DIGIT_LEN )
    {
        META_NVRAM_Calculate_IMEI_CD(sIMEIdownload.c_imei[m_usRID-1], &check_sum);
        as_check_sum = IntToStr(check_sum);
        strcat(sIMEIdownload.c_imei[m_usRID-1],as_check_sum.c_str());
    }
   //set IMEI from IMEI form
    m_sIMEIdownload = sIMEIdownload;  //Form_IMEI_setting->m_sIMEI
    for (int imei_idx=0; imei_idx<2; imei_idx++)
    {
        for (int i=0; i<IMEI_ARRAY_LEN; i++)
        {
            m_sIMEISVdownload.s_IMEISV[imei_idx].imei[i] = m_sIMEIdownload.c_imei[imei_idx][i];
        }
    }

   // fill NVRAM write parameters
   if (NULL == m_cIMEIBuf[m_usRID-1])
    {
        MetaResult = META_NVRAM_GetRecLen("NVRAM_EF_IMEI_IMEISV_LID", &m_iIMEIBufSize);
        if(MetaResult!=META_SUCCESS)
        {
            LOGD("[META ERROR]: META_NVRAM_GetRecLen() fails!");
            return METAAPP_FAIL ;
        }
        m_cIMEIBuf[m_usRID-1] = new char[m_iIMEIBufSize];
    }
    //Compose IMEI

    for (int i=0; i<IMEI_ARRAY_LEN; i++)
    {
        m_sIMEISVdownload.s_IMEISV[m_usRID-1].imei[i] = m_sIMEIdownload.c_imei[m_usRID-1][i];
    }

    MetaResult = META_NVRAM_Compose_IMEISV_ex(&m_sIMEISVdownload.s_IMEISV[m_usRID-1], m_cIMEIBuf[m_usRID-1], m_iIMEIBufSize, m_bCheckChecksum);
    if (MetaResult != META_SUCCESS)
    {
        LOGE("[META ERROR]: META_NVRAM_Compose_IMEISV_ex() fails!");
        return METAAPP_FAIL;
    }

    m_psNVRAM_WriteReq.LID = "NVRAM_EF_IMEI_IMEISV_LID";
    m_psNVRAM_WriteReq.RID = m_usRID;
    m_psNVRAM_WriteReq.len = m_iIMEIBufSize;
    m_psNVRAM_WriteReq.buf = m_cIMEIBuf[m_usRID-1];
    //write to flash
    MetaResult = META_NVRAM_Write_Ex(5000,
                                    &m_psNVRAM_WriteReq,
                                    &m_psNVRAM_WriteCnf);
     if (MetaResult != META_SUCCESS || m_psNVRAM_WriteCnf.status != NVRAM_STATUS_SUCCESS)
    {
        LOGE("[META ERROR]: META_NVRAM_Write_Ex() fails!");
        return METAAPP_FAIL;
    }

    if (m_cIMEIBuf[0])
    {
        delete [] m_cIMEIBuf[0];
        m_cIMEIBuf[0] = NULL;
    }
    if (m_cIMEIBuf[1])
    {
        delete [] m_cIMEIBuf[1];
        m_cIMEIBuf[1] = NULL;
    }
   return META_SUCCESS;
}

//---------------------------------------------------------------------------
int tboot_1::EnterMETAUpdateNVRAM(void)
{
	ErrorLookup::SetErrorCodeMode(EBOOT);

    META_RESULT  META_Result;
    int meta_handle;
    EBOOT_RESULT EBOOT_Result;
    S_IMEI_T sIMEIdownload;
    unsigned char  com_number = COM_PORT;
    const int STEP = 9;

    PostMessage(frm_Processing->Handle, AP_SPFT_META_IMEI_BT_WIFI, 0, 0);   
    // Step: Scan usb ports
    m_meta__progress_value = int(100 * 1 / STEP);
    SyncStartFakeProgress();
    EBOOT_Result = ScanMETAUSBPorts(com_number);
    if(EBOOT_SUCCESS != EBOOT_Result) {
        return EBOOT_Result;
    }

    ErrorLookup::SetErrorCodeMode(META);   
    // Step: connect into meta
    m_meta__progress_value = int(100 * 2 / STEP);
    SyncStartFakeProgress();

    //Init IMEI/BT/WIFI parameters
    Synchronize(InitIMIE_BT_WIFI_Para);
    // Step: Enter Maui meta to download IMEI
    m_meta__progress_value = int(100 * 3 / STEP);
    SyncStartFakeProgress();
	if ( m_bWriteIMEI1 || m_bWriteIMEI2 )
	{
		META_Result = EnterMETADownloadIMEI(com_number);
		if (META_SUCCESS != META_Result)
		{
			return META_Result;
		}

	}
    // Step: Complete Modem Meta
    m_meta__progress_value = int(100 * 4 / STEP);
    SyncStartFakeProgress();

    //Enter meta AP mode to write BT/WiFi
    Sleep(500);

    // Step: SP META init begin
    m_meta__progress_value = int(100 * 5 / STEP);
    SyncStartFakeProgress();
	META_Result = SPMETAInit(meta_handle, com_number);
	if (META_SUCCESS != META_Result)
	{
		return META_Result;
	}
    // Step: SP META init end
    m_meta__progress_value = int(100 * 6 / STEP);
    SyncStartFakeProgress();

    if ( m_bWriteBTAddr || m_bWriteWIFIAddr )
    {
        // Step: Update BT Addr begin
        m_meta__progress_value = int(100 * 7 / STEP);
        SyncStartFakeProgress();
        if ( m_bWriteBTAddr )
        {
        	META_Result = EnterMETADownloadBT_r(meta_handle);
    		if (META_SUCCESS != META_Result)
    		{
    			return META_Result;
    		}
        }

        // Step: Update BT Addr begin
        m_meta__progress_value = int(100 * 8 / STEP);
        SyncStartFakeProgress();
        if ( m_bWriteWIFIAddr )
        {
        	META_Result = EnterMETADownloadWIFI_r(meta_handle);
    		if (META_SUCCESS != META_Result)
    		{
    			return META_Result;
    		}
        }
        // Step: Update WIFI Addr begin
        m_meta__progress_value = int(100 * 9 / STEP);
        SyncStartFakeProgress();

        // backup NVRAM to BinRegion (only WinMo need this step)
        if( g_project_mode == DUMA )
        {
        	META_Result = EnterMETABackupNvram2BinRegion();
    		if (META_SUCCESS != META_Result)
    		{
    			return META_Result;
    		}
        }
    }
    //Backup Nvram to BinRegion after W1101
    if ( g_project_mode == YuSu )
    {
    	META_Result = EnterMETASetCleanBootFlag_r(meta_handle);
		if (META_SUCCESS != META_Result)
		{
			return META_Result;
		}
    }
    // end of update IMEI/WiFi/BT to NVRAM
    WM_META_ShutDownTarget_r_Wrapper(meta_handle);
    WM_META_DisconnectWithTarget_r_Wrapper(meta_handle);
    WM_META_Deinit_r_Wrapper(&meta_handle);
    SendMessage(frm_Processing->Handle, AP_SPFT_META_EXIT, 0, 0);

    Synchronize( FinishFakeProgress );

    return META_SUCCESS;
}

//---------------------------------------------------------------------------
META_RESULT tboot_1::EnterMETADownloadIMEI( int com_port )
{
    META_RESULT  META_Result;
    int RID;
    int rid_num;
    bool b2ndIMEISupport = true;
    char szLog[256];

    //int meta_handle;
    META_Result = META_Init(NULL);

    if ( META_SUCCESS != META_Result )
    {
        m_as_err_msg = "[META INFO]: Initialize Modem Meta fail!";
        ClearMeta();
        return META_Result;
    }
    // Wait 2s to try to connect modem META
    Sleep(2000);

    if(g_bUsbMode){
        META_ConnectByUSB_Req usbRequest;
        META_ConnectByUSB_Report usbReport;
        usbRequest.com_port = com_port;
        usbRequest.ms_connect_timeout = 40000;
        META_Result = META_ConnectInMetaModeByUSB(&usbRequest, &g_stopflag, &usbReport);
		LOG("tboot_1::EnterMETADownloadIMEI(): META_ConnectInMetaModeByUSB(): USB port(%d), return value(%d)", com_port,META_Result);
    }
    else{
        META_ConnectInMETA_Req     META_ConnectInMETA_Req;
        META_ConnectInMETA_Report  META_ConnectInMETA_Report;
       

        ArgMETAConnectWithTargetInMETA( META_ConnectInMETA_Req, META_ConnectInMETA_Report, com_port );
        
        META_Result = META_ConnectInMetaMode(&META_ConnectInMETA_Req,
                                                 &g_stopflag,
                                                 &META_ConnectInMETA_Report);
    }

    if( (META_SUCCESS != META_Result) && (META_MAUI_DB_INCONSISTENT != META_Result) )
    {
        if ( META_STOP_BOOTUP_PROCEDURE == META_Result )
        {
            m_as_err_msg = "[META INFO]: User forcibly stop META connection!";
        }
        else
        {
            m_as_err_msg = "[META INFO]: META_ConnectInMetaMode() fails!";
        }
        ClearMeta();
        return META_Result;
    }

    //Use META_UploadFilesToTarget_Ex to write IMEI for MT6573
    if(g_platform_info.getLoadPlatformName()!= "MT6516"){
		//-3. call META upload files api
		MISC_UPLOAD_REQ_EX_T meta_upload_req;
		AnsiString imei_status;

		ArgMETAUploadFilesToTarget(meta_upload_req, &imei_status);

		if (META_SUCCESS != (META_Result = META_UploadFilesToTarget_Ex(&meta_upload_req,
				&g_stopflag))) {
			LOG("ERROR:tboot_1::EnterMETADownloadIMEI(): META_UploadFilesToTarget_Ex() failed, error code (%d).",
				META_Result);
			META_DisconnectWithTarget();
			// stop fake progress
			Synchronize(StopFakeProgress);
			return META_Result;
		}
    }else{
    	//Use NVRAM op to write IMEI for MT6516

    	LOG("For MT6516, use NVRAM OP to write IMEI.  ModemDB: %s ",m_pModemDatabase);

    	// Initialize modem NVRAM with database file
		META_Result = ModemNVRAMInit( m_pModemDatabase );
		if( META_SUCCESS != META_Result)
		{
			if ( META_STOP_BOOTUP_PROCEDURE == META_Result )
			{
				m_as_err_msg = "[META INFO]: User forcibly stop to initate Modem NVRAM!";
			}
			else if (META_MAUI_DB_INCONSISTENT == META_Result )
			{
				m_as_err_msg = "[META INFO]: NVRAM database file is inconsistent with target load";
			}
			else
			{
				m_as_err_msg = "[META INFO]: Initialize NVRAM database file failed";
			}
			ClearMeta();
			return META_Result;
		}

		// get to know if support 2 IMEI
		META_Result = META_NVRAM_GetRecNum("NVRAM_EF_IMEI_IMEISV_LID", &rid_num);
		if ((META_SUCCESS != META_Result) || (1 == rid_num))
		{
			b2ndIMEISupport = false;
		}
		m_b2ndImeiSupport = b2ndIMEISupport;
		Synchronize(SyncFourInOne2ndImeiSupport);

		//write IMEI of SIM1
		if ( m_bWriteIMEI1 )
		{
			RID = 1;
			WriteSIMX2Nvram(RID);
		}
		// write IMEI of SIM2
		if ( m_bWriteIMEI2 && m_b2ndImeiSupport )
		{
			RID = 2;
			WriteSIMX2Nvram(RID);
		}
    }

    // Disconnect from Modem Meta
    META_DisconnectWithTarget();
    META_Deinit();

	return META_Result;
}

//---------------------------------------------------------------------------
META_RESULT tboot_1::WriteSIMX2Nvram( const int RID )
{
	META_RESULT  META_Result;
	S_IMEI_T sIMEIdownload;

    memcpy(&sIMEIdownload, &m_sIMEIdownload, sizeof(sIMEIdownload));

    Logger::GetLogger().Log(Logger::Debug,
    		"[SIM%d] IMEI of SIM1 to be written is %s (%s,%d)",
    		RID, sIMEIdownload.c_imei[RID-1],
    		__FILE__, __LINE__);

    META_Result = (META_RESULT)WriteIMEItoNVRAM(sIMEIdownload, RID, true);
    if ( META_Result != META_SUCCESS)
    {
        m_as_err_msg = "[META INFO]: Write IMEI of SIM1 to NVRAM failed!";
        ClearMeta();
        return META_Result;
    }

    return META_Result;
}

//---------------------------------------------------------------------------
META_RESULT tboot_1::SPMETAInit( int& meta_handle, int com_port )
{
	META_RESULT  META_Result;

    META_Result = (META_RESULT)WM_META_GetAvailableHandle_Wrapper(&meta_handle);
    if(META_SUCCESS != META_Result) {
        m_as_err_msg = "[META INFO]: WM_META_GetAvailableHandle fails!";
        return META_Result;
    }

    META_Result = (META_RESULT)WM_META_Init_r_Wrapper(meta_handle);
    if(META_SUCCESS != META_Result) {
        m_as_err_msg = "[META INFO]: WM_META_Init_r fails!";
        return META_Result;
    }

	META_Result = (META_RESULT)WM_META_ConnectInMetaMode_r_Wrapper(meta_handle, &g_stopflag, com_port);

    if( (META_SUCCESS != META_Result) && (META_MAUI_DB_INCONSISTENT != META_Result) )
    {
        if ( META_STOP_BOOTUP_PROCEDURE == META_Result )
        {
            m_as_err_msg = "[META INFO]: User forcibly stop to enter to meta AP mode!";
        }
        else
        {
            m_as_err_msg =  "[META INFO]: Could not enter into meta AP mode!";
        }
        ClearSPMeta();
        return META_Result;
    }

    // initialize AP NVRAM with database file
    META_Result = ApNVRAMInit(meta_handle, m_pApDatabase);
    if( META_SUCCESS != META_Result)
    {
        m_as_err_msg =  "[META INFO]: Initialize AP NVRAM database file ";
        ClearSPMeta();
        return META_Result;
    }
    LOGD("Step : Init AP Nvram Database successfully.");
    return META_Result;
}

//---------------------------------------------------------------------------
META_RESULT tboot_1::EnterMETADownloadWIFI_r( const int meta_handle )
{
	META_RESULT  META_Result;
    // enter AP meta to write WiFi address
    LOGD( "Step :Start to write WiFi MAC.");

    //get WIFI address and write WIFI address
    META_Result = (META_RESULT)WriteWIFItoNVRAM( m_pWIFIAddr, meta_handle );

    if( META_SUCCESS != META_Result )
    {
        if ( META_STOP_BOOTUP_PROCEDURE == META_Result )
        {
            m_as_err_msg = "[META INFO]: User forcibly stop to enter to write BT address!";
        }
        else
        {
            m_as_err_msg =  "[META INFO]: write WIFI MAC failed!";
        }
        ClearSPMeta(meta_handle);
        return META_Result;
    }

    LOGD( "Step: Write WIFI MAC and check successfully.");
	return META_Result;
}

//---------------------------------------------------------------------------
META_RESULT tboot_1::EnterMETADownloadBT_r( const int meta_handle )
{
	META_RESULT  META_Result;
	LOGD("Step : Start to write BT address.");
    //get BT address and write BT address
	META_Result = (META_RESULT)WriteBTtoNVRAM( m_pBTAddr, meta_handle );

    if( META_SUCCESS != META_Result )
    {
        if ( META_STOP_BOOTUP_PROCEDURE == META_Result )
        {
            m_as_err_msg = "[META INFO]: User forcibly stop to enter to write BT address!";
        }
        else
        {
            m_as_err_msg = "[META INFO]: Write BT address failed !";
        }
        ClearSPMeta(meta_handle);
        return META_Result;
    }

    LOGD( "Step: Write BT Address and check successfully.");
    return META_Result;
}

//---------------------------------------------------------------------------
META_RESULT tboot_1::EnterMETASetCleanBootFlag( void )
{
	META_RESULT  META_Result;
    unsigned int ms_timeout = 60000;

    META_Result = (META_RESULT)WM_META_SetCleanBootFlag_Wrapper(ms_timeout);
    if(META_SUCCESS != META_Result)
    {
        m_as_err_msg = "[SP META INFO]: Set Clean Boot Flag failed !\n"
        		"[Possible Reason]:\n"
        		"1. The load is too old, that doesn't support \"Set Clean Boot\".\n"
        		"2. Backup NVRAM to Bin Region failed.";
        ClearSPMeta();
        return META_Result;
    }
	return META_Result;
}

//---------------------------------------------------------------------------
META_RESULT tboot_1::EnterMETASetCleanBootFlag_r( int meta_handle )
{
	META_RESULT  META_Result;
    unsigned int ms_timeout = 60000;

    META_Result = (META_RESULT)WM_META_SetCleanBootFlag_r_Wrapper(meta_handle,ms_timeout);
    if(META_SUCCESS != META_Result)
    {
        m_as_err_msg = "[SP META INFO]: Set Clean Boot Flag failed !\n"
        		"[Possible Reason]:\n"
        		"1. The load is too old, that doesn't support \"Set Clean Boot\".\n"
        		"2. Backup NVRAM to Bin Region failed.";
        ClearSPMeta(meta_handle);
    }
	return META_Result;
}

//---------------------------------------------------------------------------
META_RESULT tboot_1::EnterMETABackupNvram2BinRegion( void )
{
	META_RESULT  META_Result;
    unsigned int ms_timeout = 60000;
    META_Result = (META_RESULT)WM_META_Nvram2Bin_Wrapper(ms_timeout);
    if(META_SUCCESS != META_Result)
    {
        m_as_err_msg = "[META INFO]: Backup NVRAM to BinRegion failed !";
        ClearSPMeta();
        return META_Result;
    }
	return META_Result;
}

//---------------------------------------------------------------------------
void __fastcall tboot_1::ClearMeta( void )
{
    LOGD( m_as_err_msg.c_str());
    Synchronize( ErrorMessage );

    //Disconnect connection
    META_DisconnectWithTarget();
    META_Deinit();

    //Meta operations fail, change processing hint
    PostMessage(frm_Processing->Handle, AP_SPFT_META_CLEAR_UP, 0, 0);

    //shut down target with SP meta.dll
    Sleep(500);
    WM_META_Init_Wrapper();
    WM_META_ConnectInMetaMode_Wrapper(&g_stopflag);
    WM_META_ShutDownTarget_Wrapper();
    WM_META_DisconnectWithTarget_Wrapper();
    WM_META_Deinit_Wrapper();

    Synchronize( StopFakeProgress );
}

//---------------------------------------------------------------------------
void __fastcall tboot_1::ClearSPMeta( int meta_handle )
{
    Synchronize( ErrorMessage );

    //Meta operations fail, change processing hint
    PostMessage(frm_Processing->Handle, AP_SPFT_META_CLEAR_UP, 0, 0);

    //TODO: seems the shutdown operation doesn't work.
    int ret = WM_META_ShutDownTarget_r_Wrapper(meta_handle);  
    Logger::GetLogger().Log(Logger::Debug, "WM_META_ShutDownTarget_r_Wrapper ret = %d", ret);

    ret = WM_META_DisconnectWithTarget_r_Wrapper(meta_handle);
    Logger::GetLogger().Log(Logger::Debug, "WM_META_DisconnectWithTarget_r_Wrapper ret = %d", ret);

    WM_META_Deinit_r_Wrapper(&meta_handle);

    Synchronize( StopFakeProgress );
}

//---------------------------------------------------------------------------
void __fastcall tboot_1::ClearSPMeta( void )
{
    LOGD( m_as_err_msg.c_str());
    Synchronize( ErrorMessage );

    //Meta operations fail, change processing hint
    PostMessage(frm_Processing->Handle, AP_SPFT_META_CLEAR_UP, 0, 0);
    //WM_META_Init_Wrapper();

    //FIXME: suspicious,do we need it? maybe we need 2 kinds of error handler, 
    //before connected& after connected
    int ret = WM_META_ConnectInMetaMode_Wrapper(&g_stopflag);
    Logger::GetLogger().Log(Logger::Debug, "WM_META_ConnectInMetaMode_Wrapper ret = %d", ret);

    WM_META_ShutDownTarget_Wrapper();
    WM_META_DisconnectWithTarget_Wrapper();
    WM_META_Deinit_Wrapper();

    Synchronize( StopFakeProgress );
}


//---------------------------------------------------------------------------
void tboot_1::DebugDA()
{
	int ret;
	HANDLE  hCOM = INVALID_HANDLE_VALUE;
    com_sentry	s( hCOM, COM_PORT );

    if( INVALID_HANDLE_VALUE == hCOM ) {
		// stop timer
		Synchronize(StopTimer);
		asMsg = "Open COM" + IntToStr(COM_PORT) + "failed!";
		Synchronize( ShowMsg );
    	return;
	}

    // fill BOOT_FLASHTOOL_ARG
    BOOT_FLASHTOOL_ARG	                boot_ft;
	BOOT_RESULT			                boot_result;
	ArgBootFlashTool( boot_ft, &boot_result );
   	ret = Boot_FlashTool( hCOM, &boot_ft, &boot_result, &g_stopflag );

	if( S_DONE != ret ) {
        // get error message
		asMsg = ErrorLookup::BromErrorMessage((STATUS_E) ret,
				result.m_da_report.m_msp_err_code,com.baudrate).c_str();
//        GetErrorMessag( (STATUS_E) ret, result.m_da_report.m_msp_err_code );
		// stop timer
		Synchronize(StopTimer);
		if( BOOT_STOP != g_stopflag ) {
			Synchronize( ShowMsg );
		}
		return;
	}

	COMMTIMEOUTS	timeouts;

	timeouts.ReadIntervalTimeout         = 0;
	timeouts.ReadTotalTimeoutMultiplier  = 1;
	timeouts.ReadTotalTimeoutConstant    = 1000;
	timeouts.WriteTotalTimeoutMultiplier = 1;
	timeouts.WriteTotalTimeoutConstant   = 1000;

	if( !::SetCommTimeouts( hCOM, &timeouts )) {
		// stop timer
		Synchronize( StopTimer );
		ret     = GetLastError();
		asMsg   = "SetCommTimeouts(): Error: ret=" + IntToStr(ret);
		Synchronize( ShowMsg );
		return;
	}

	bool bIsUpToDate = false;
	m_RecvString = "";

	while( g_bDebugDA && (BOOT_STOP!=g_stopflag) )
    {
		unsigned char  ch      = 0;
		unsigned long  readlen = 0;
		bool   bResult = ReadFile( hCOM, &ch, 1, &readlen, NULL );

		if( true == bResult && 1 == readlen )
        {
			AnsiString  str;
			m_RecvChar = ch;
			str.printf("%c", ch);
			m_RecvString += str;

			if( 0 == ( m_RecvString.Length()%1024 ) )
            {
				Synchronize( UpdateDebugDAWindow );
				bIsUpToDate = true;
			}
			else {
				bIsUpToDate = false;
			}
    	}
    	else if( !bIsUpToDate ) {
			Synchronize( UpdateDebugDAWindow );
			bIsUpToDate = true;
    	}
	}

	// stop timer
	Synchronize( StopTimer );
	return;
}
//---------------------------------------------------------------------------
void __fastcall tboot_1::UpdateDebugDAWindow()
{
    SCROLLINFO si;

	AnsiString s;
    //s = MainForm->DebugDAWindow->Text + IntToHex(m_RecvChar, 2) + " ";
    //s.printf("%s%c", MainForm->DebugDAWindow->Text.c_str(), m_RecvChar);
   	MainForm->DebugDAWindow->Text = m_RecvString;

    si.cbSize = sizeof( SCROLLINFO );
    si.fMask = SIF_RANGE | SIF_POS | SIF_PAGE;
    if( ::GetScrollInfo( MainForm->DebugDAWindow->Handle, SB_VERT, &si ) == TRUE ){
        si.nTrackPos = si.nMax - si.nPage;
        ::SetScrollInfo( MainForm->DebugDAWindow->Handle, SB_VERT, &si, TRUE );
    }
}

//---------------------------------------------------------------------------
void tboot_1::SyncDisplayFlashType()
{
	Synchronize( DisplayFlashType );
}

void __fastcall tboot_1::DisplayFlashType()
{
    if(m_bGetDAReportWithConnArg) {
        LOGD("Get DA report by m_bGetDAReportWithConnArg");
        ConvertDAReportToString(&cn_result.m_da_report, 
            m_strDeviceHint, sizeof(m_strDeviceHint), 
            m_strHWDetectionReport, sizeof(m_strHWDetectionReport));
        MainForm->HWStatusBarUpdate(&cn_result.m_da_report, m_strDeviceHint, m_strHWDetectionReport);
    } else {
        LOGD("Get DA report NOT by m_bGetDAReportWithConnArg.");
        ConvertDAReportToString(&result.m_da_report, 
            m_strDeviceHint, sizeof(m_strDeviceHint),  
            m_strHWDetectionReport, sizeof(m_strHWDetectionReport));
        MainForm->HWStatusBarUpdate(&result.m_da_report, m_strDeviceHint, m_strHWDetectionReport);
    }
    
}

//---------------------------------------------------------------------------
static int __stdcall cb_download_da_init(void *usr_arg)
{

	tboot_1 *t = (tboot_1 *)usr_arg;


    t->StartTimer();

	t->progress_hint            = "Download DA now...";
    t->progress_forecolor       = clRed;
	t->progress_percentage      = 0;
	t->progress_finished_bytes  = 0;

	t->bUpdateFinishBytes       = true;
	t->SyncInitProgress();

    return 0;
}
//---------------------------------------------------------------------------
static int __stdcall cb_download_da(unsigned char percent, unsigned int sent_bytes, unsigned int total_bytes, void *usr_arg)
{
	tboot_1 *t = (tboot_1 *)usr_arg;

	t->progress_percentage      = percent;
	t->progress_finished_bytes  = sent_bytes;
	t->progress_total_bytes     = total_bytes;

	t->bUpdateFinishBytes       = true;
	t->SyncUpdateProgress();

    return 0;
}
//---------------------------------------------------------------------------
static int __stdcall cb_checkusbstatus_init(void * arg, const char* usb_status)
{
    tboot_1 *t = (tboot_1 *)arg;

    t->speed_status = usb_status;

    t->SyncUpdateProgress();

    return 0;
}

//---------------------------------------------------------------------------
static int __stdcall cb_checksum_init(void *usr_arg, const char*image_name)
{
	tboot_1 *t = (tboot_1 *)usr_arg;

	t->StartChksumTimer();

      AnsiString s;

	if( NULL != image_name ) {
		s.printf("Caculate Checksum for \"%s\". ", 	image_name);	 
        }

	t->progress_hint            = s;
	t->progress_forecolor       = clFuchsia;
	t->progress_percentage      = 0;
	t->progress_finished_bytes  = 0;

	t->bUpdateFinishBytes       = true;
	t->SyncInitProgress();

    return 0;
}
//---------------------------------------------------------------------------
static int __stdcall cb_checksum_progress(unsigned char finished_percentage, unsigned int finished_bytes, unsigned int total_bytes, void *usr_arg)
{
	tboot_1 *t = (tboot_1 *)usr_arg;

        t->progress_percentage      = finished_percentage;
	t->progress_finished_bytes  = finished_bytes;
	t->progress_total_bytes     = total_bytes;

	t->bUpdateFinishBytes       = true;
	t->SyncUpdateProgress();

    return 0;
}

//---------------------------------------------------------------------------
static int __stdcall cb_download_flash_init(void *usr_arg)
{
	tboot_1 *t = (tboot_1 *)usr_arg;

	t->progress_hint            = "Download firmware to flash now...";
	t->progress_forecolor       = clYellow;
	t->progress_percentage      = 0;
	t->progress_finished_bytes  = 0;

	t->bUpdateFinishBytes       = true;
	t->SyncInitProgress();

    return 0;
}
//---------------------------------------------------------------------------
static int __stdcall cb_download_flash(unsigned char percent, unsigned int sent_bytes, unsigned int total_bytes, void *usr_arg)
{
	tboot_1 *t = (tboot_1 *)usr_arg;

	t->progress_percentage      = percent;
	t->progress_finished_bytes  = sent_bytes;
	t->progress_total_bytes     = total_bytes;

	t->bUpdateFinishBytes       = true;
	t->SyncUpdateProgress();

    return 0;
}
//---------------------------------------------------------------------------
static int __stdcall cb_da_dl_checksum__init(void *usr_arg, const char* image_name)
{
	tboot_1 *t = (tboot_1 *)usr_arg;
        std::ostringstream check_info;
	check_info<<"DA Download "<<image_name<<" checksum is executing ...";
	t->progress_hint            = check_info.str().c_str();
	t->progress_forecolor       = clSilver;
	t->progress_percentage      = 0;
	t->progress_finished_bytes  = 0;

	t->bUpdateFinishBytes       = true;
	t->SyncInitProgress();

    return 0;
}
//---------------------------------------------------------------------------
static int __stdcall cb_da_dl_checksum(unsigned char percent, unsigned int  sent_bytes, unsigned int total_bytes, void *usr_arg)
{
	tboot_1 *t = (tboot_1 *)usr_arg;

	t->progress_percentage      = percent;
	t->progress_finished_bytes  = sent_bytes;
	t->progress_total_bytes     = total_bytes;

	t->bUpdateFinishBytes       = true;
	t->SyncUpdateProgress();

    return 0;
}
//---------------------------------------------------------------------------
static int __stdcall cb_download_bloader_init(void *usr_arg)
{
	tboot_1 *t = (tboot_1 *)usr_arg;

	t->progress_hint            = "Download BootLoader now...";
	t->progress_forecolor       = (TColor) 0x00A00070;
	t->progress_percentage      = 0;
	t->progress_finished_bytes  = 0;

	t->bUpdateFinishBytes       = true;
	t->SyncInitProgress();

    return 0;
}
//---------------------------------------------------------------------------
static int __stdcall cb_download_bloader(unsigned char percent, unsigned int sent_bytes, unsigned int  total_bytes, void *usr_arg)
{
	tboot_1 *t = (tboot_1 *)usr_arg;

	t->progress_percentage      = percent;
	t->progress_finished_bytes  = sent_bytes;
	t->progress_total_bytes     = total_bytes;

	t->bUpdateFinishBytes       = true;
	t->SyncUpdateProgress();

    return 0;
}

//---------------------------------------------------------------------------
static int __stdcall cb_format_report_init(HW_StorageType_E storage_type, unsigned long long  begin_addr, unsigned long long length, void *usr_arg)
{

      tboot_1 *t = (tboot_1 *)usr_arg;

       t->progress_hint.printf("Format %s memory:  begin_addr(0x%016I64X), length(0x%016I64X). ",
		g_platform_info.getFlashToolStorageConfig().QueryStorageNameByStorageType(storage_type).c_str(), 
		begin_addr,
		length);

        t->progress_forecolor      = clGreen;
       	t->progress_percentage     = 0;

        t->bUpdateFinishBytes      = false;
        t->SyncInitProgress(); 

        return 0;
}
//---------------------------------------------------------------------------
static int __stdcall cb_format_report(unsigned char percent, void *usr_arg)
{

	tboot_1 *t = (tboot_1 *)usr_arg;

   	t->progress_percentage      = percent;

	t->bUpdateFinishBytes       = false;
	t->SyncUpdateProgress();

    return 0;
}
//---------------------------------------------------------------------------
static int __stdcall cb_readback_flash_init( HW_StorageType_E  storage_type, unsigned long long rb_addr, unsigned int  rb_length, const char *rb_filepath, void *usr_arg)
{

	tboot_1 *t = (tboot_1 *)usr_arg;
	LOG("cb_readback_flash_init(): storage_type(%s)", HWStorageTypeToString(storage_type));
    AnsiString s;
    if( NULL != rb_filepath ) {
		s.printf("Readback %s storage to \"%s\", ADDR(0x%016I64X), LEN(0x%016I64X). ", 
			g_platform_info.getFlashToolStorageConfig().QueryStorageNameByStorageType(storage_type).c_str(), 
			rb_filepath, rb_addr, 
			rb_length);
    }
    else {
    	s.printf("Readback %s storage to buffer, ADDR(0x%016I64X), LEN(0x%016I64X). ", 
			g_platform_info.getFlashToolStorageConfig().QueryStorageNameByStorageType(storage_type).c_str(),
			rb_addr,
			rb_length);
	}
      	t->progress_hint            = s;
	t->progress_forecolor       = clBlue;
	t->progress_percentage      = 0;
	t->progress_finished_bytes  = 0;

	t->bUpdateFinishBytes       = true;
	t->SyncInitProgress();

    return 0;
}
//---------------------------------------------------------------------------
static int __stdcall cb_readback_flash(unsigned char percent, unsigned int  sent_bytes, unsigned int total_bytes, void *usr_arg)
{

	tboot_1 *t = (tboot_1 *)usr_arg;

	t->progress_percentage      = percent;
	t->progress_finished_bytes  = sent_bytes;
	t->progress_total_bytes     = total_bytes;

	t->bUpdateFinishBytes       = true;
	t->SyncUpdateProgress();

    return 0;
}
//---------------------------------------------------------------------------
static int __stdcall cb_da_report(const DA_REPORT_T  *p_da_report, void *usr_arg)
{

	tboot_1 *t = (tboot_1 *)usr_arg;

	//unsued code
#if 0
	if( MainForm->mi_MultiLoad->Checked )
    {
		for( unsigned int index = 0; index < g_DL_HANDLE_LIST_nodes.size(); index++ )
        {
			if( g_DL_HANDLE_LIST_nodes[index].m_dl_handle == p_da_report->m_dl_handle )
            {
				t->dl_arg.m_otp_enable          = g_DL_HANDLE_LIST_nodes[index].m_param.m_otp_enable;
				t->dl_arg.m_otp_op              = g_DL_HANDLE_LIST_nodes[index].m_param.m_otp_op;
				t->dl_arg.m_otp.m_addr          = g_DL_HANDLE_LIST_nodes[index].m_param.m_otp.m_addr;
				t->dl_arg.m_otp.m_data          = g_DL_HANDLE_LIST_nodes[index].m_param.m_otp.m_data;
				t->dl_arg.m_otp.m_len           = g_DL_HANDLE_LIST_nodes[index].m_param.m_otp.m_len;
				t->dl_arg.m_ft_cfg_enable       = g_DL_HANDLE_LIST_nodes[index].m_param.m_ft_cfg_enable;
				t->dl_arg.m_ft_cfg.m_security_cfg.m_uint32 = g_DL_HANDLE_LIST_nodes[index].m_param.m_ft_cfg.m_security_cfg.m_uint32;
				t->dl_arg.m_sec_ro_enable       = g_DL_HANDLE_LIST_nodes[index].m_param.m_sec_ro_enable;
				t->dl_arg.m_sec_ro.m_data       = g_DL_HANDLE_LIST_nodes[index].m_param.m_sec_ro.m_data;
				t->dl_arg.m_sec_ro.m_len        = g_DL_HANDLE_LIST_nodes[index].m_param.m_sec_ro.m_len;
		        t->dl_arg.m_cust_para_enable    = g_DL_HANDLE_LIST_nodes[index].m_param.m_cust_para_enable;
				t->dl_arg.m_cust_para.m_data    = g_DL_HANDLE_LIST_nodes[index].m_param.m_cust_para.m_data;
				t->dl_arg.m_cust_para.m_len     = g_DL_HANDLE_LIST_nodes[index].m_param.m_cust_para.m_len;

				break;
			}
		}
	}
#endif

    LOG("cb_da_report(): DA report: m_da_report addr: %x, chip name: %s, chip type: %d. ext ram size: %x",
        p_da_report, p_da_report->m_bbchip_name, 
        p_da_report->m_bbchip_type, p_da_report->m_ext_ram_size);

    //Update DA Report Info when cb_da_report is updated in FlashTool_Download_Arg
    //Advanced api
    t->cn_result.m_da_report = *p_da_report;
    //All-in-one api
    t->result.m_da_report = *p_da_report;
    //Update GUI  
	t->SyncDisplayFlashType();

    return 0;
}
//---------------------------------------------------------------------------
bool PowerOnOxford( HANDLE hCard, void *usr_arg)
{
    tboot_1 *t = (tboot_1*) usr_arg;
    int (*mio_pull)(HANDLE handle, int which, int up);

	HINSTANCE g_hDLL = LoadLibrary("miodll.dll");

	if ( g_hDLL == NULL ) //if it is still NULL
	{
        t->asMsg.printf( "[Error] Loaded Oxford's DLL but failed" );
        t->SyncShowMsg();
		return false;
	}

	mio_pull = (int (*)(HANDLE,int,int))GetProcAddress( g_hDLL, "mio_pull" );

	if (hCard == (HANDLE)-1)
	{
        t->asMsg.printf( "[Error] Called Oxford's mio_open but failed" );
        t->SyncShowMsg();
		return false;
	}

    // Power-off
    mio_pull( hCard, 0, 1 );
    Sleep( 200 );
    mio_pull( hCard, 0, 0 );
    Sleep( 200 );

    // Power-on
    mio_pull(hCard, 1, 1);
	return true;
}
//---------------------------------------------------------------------------
static int __stdcall cb_com_init_stage( HANDLE hCOM, void *usr_arg)
{
    tboot_1 *t = (tboot_1*) usr_arg;

    OxQueryDeviceInfo deviceInfo;
    DWORD bytesReturned;
    BOOL ok;

    deviceInfo.dwRequestedType = OX_FOR_SERIAL_DRIVER;

    ok = DeviceIoControl( hCOM,
                          IOCTL_OXSER_QUERY_INFO,
                          &deviceInfo, sizeof(deviceInfo),
                          &deviceInfo, sizeof(deviceInfo),
                          &bytesReturned,
                          NULL);

    if ( ok )
    {
        if ( bytesReturned >= sizeof(deviceInfo) && deviceInfo.dwMagicNumber == OXMAGICNUMBER )
        {
            // if Oxford Card, then call PowerOnOxford()
            if ( deviceInfo.ChipId == OXCF950_CHIP_ID )
            {
                bool bPoweronOk = PowerOnOxford( hCOM, usr_arg );
                if ( !bPoweronOk )
                {
                    t->asMsg.printf("Failed to power on Oxford");
                    t->SyncShowMsg();
                    return 1;
                };

                return 0;
            }
        }
    }

    return 0;
}

//---------------------------------------------------------------------------
static int __stdcall cb_in_brom_stage( unsigned int brom_handle, HANDLE hCOM, void *usr_arg)
{

	unsigned short	value16;
    BBCHIP_TYPE	    *p_bbchip = (BBCHIP_TYPE *)usr_arg;

	if ( g_bPullDownGPIO17 && NULL!=p_bbchip && MT6218B==*p_bbchip )
    {
		// configure GPIO17 mode to GPIO
		value16 = 0x000C;
		Brom_Write16Cmd(brom_handle, hCOM, (0x80120000+0x0120+0x08)/*GPIO_MODE3_CLR*/, &value16, 1);

		// configure GPIO17 direction as output
		value16 = 0x0002;
		Brom_Write16Cmd(brom_handle, hCOM, (0x80120000+0x0010+0x04)/*GPIO_DIR2_SET*/, &value16, 1);

		// pull down GPIO17 to disable vibrator
		value16 = 0x0002;
		Brom_Write16Cmd(brom_handle, hCOM, (0x80120000+0x00a0+0x08)/*GPIO_DOUT2_CLR*/, &value16, 1);
	}

    return 0;
}
//---------------------------------------------------------------------------
static int __stdcall cb_format_statistics( const FormatStatisticsReport_T* p_report, void* usr_arg)
{
    LOGD("Enter format statistics callback function to report format result.");
	tboot_1 *t = (tboot_1 *)usr_arg;
	float			bad_block_ratio;
	float			float_size;
	unsigned int	size_of_bits;
	AnsiString		str_format_size;

	size_of_bits = ( p_report->m_fmt_length<<3 );
	float_size   = size_of_bits;

	if( 0x40000000 <= size_of_bits )
    {
		if( 0 == (size_of_bits%0x40000000) ) {
			str_format_size.printf("%dGb", size_of_bits>>30);
		} else {
			str_format_size.printf("%.2fGb", float_size/0x40000000);
		}
    }
	else if( 0x100000 <= size_of_bits )
    {
		if( 0 == (size_of_bits%0x100000) ) {
			str_format_size.printf("%dMb", size_of_bits>>20);
		}
		else {
			str_format_size.printf("%.2fMb", float_size/0x100000);
		}
	}
	else if( 0x400 <= size_of_bits )
    {
		if( 0 == (size_of_bits%0x400) ) {
			str_format_size.printf("%dKb", size_of_bits>>10);
		}
		else {
			str_format_size.printf("%.2fKb", float_size/0x400);
		}
	}
    else {
		str_format_size.printf("%db", size_of_bits);
	}

	bad_block_ratio = (p_report->m_bad_blocks+p_report->m_err_blocks);
	bad_block_ratio /= p_report->m_total_blocks;
	bad_block_ratio *= 100;

	t->asMsg.printf("Format Range: 0x%016I64X ~ 0x%016I64X\n"
					"Format Size: %s\n"
					"\n"
					"Bad Blocks: %lu\n"
					"Error Blocks: %lu\n"
					"Total Blocks: %lu\n"
					"\n"
					"Bad/Error Block Ratio: (%.3f%%)\n"
                    "\n"
                    "Press 'OK' to continue\n"
					,p_report->m_fmt_begin_addr, p_report->m_fmt_begin_addr+p_report->m_fmt_length-1
					,str_format_size.c_str()
					,p_report->m_bad_blocks
					,p_report->m_err_blocks
					,p_report->m_total_blocks
					,bad_block_ratio);

	t->SyncShowMsg();

    return 0;
}
//---------------------------------------------------------------------------
static int __stdcall cb_post_process_init( void *usr_arg )
{

	tboot_1 *t = (tboot_1 *)usr_arg;

    AnsiString s;
    s.printf("Proceed post-process now...");
	t->progress_hint        = s;
	t->progress_forecolor   = (TColor) 0x00990000;
	t->progress_percentage  = 0;

	t->bUpdateFinishBytes   = false;
	t->SyncInitProgress();

    return 0;
}
//---------------------------------------------------------------------------
static int __stdcall cb_post_process( unsigned char percent, void *usr_arg )
{

	tboot_1 *t = (tboot_1 *)usr_arg;

	t->progress_percentage  = percent;

	t->bUpdateFinishBytes   = false;
	t->SyncUpdateProgress();

    return 0;
}

//---------------------------------------------------------------------------
static int __stdcall cb_progress_init( void *usr_arg )
{

	tboot_1 *t = (tboot_1 *)usr_arg;

    t->StartTimer();

	t->progress_hint            = "Extract NFB image now...";
    t->progress_forecolor       = (TColor) 0x0088A050;
	t->progress_percentage      = 0;
	t->progress_finished_bytes  = 0;

	t->bUpdateFinishBytes       = true;
	t->SyncInitProgress();

    return 0;
}
//---------------------------------------------------------------------------
static int __stdcall cb_progress( unsigned char percent,
                                  unsigned long long  sent_bytes,
                                  unsigned long long  total_bytes,
                                  void*         usr_arg)
{

	tboot_1 *t = (tboot_1 *)usr_arg;

	t->progress_percentage      = percent;
	t->progress_finished_bytes  = sent_bytes;
	t->progress_total_bytes     = total_bytes;

	t->bUpdateFinishBytes       = true;
	t->SyncUpdateProgress();

    return 0;
}
//---------------------------------------------------------------------------
static int __stdcall cb_security_pre_process_notify ( void *usr_arg )
{
	tboot_1 *t = (tboot_1 *)usr_arg;

    t->asMsg.printf("Proceed 1st time download pre-process ... (it takes about 10~15 seconds)\n\nPlease press OK to close the window!");
	t->SyncShowMsg();

    return 0;
}
//---------------------------------------------------------------------------
static int __stdcall cb_update_param_init ( void *usr_arg )
{
	tboot_1 *t = (tboot_1 *)usr_arg;

    AnsiString s;
    s.printf("Update parameters now ...");
	t->progress_hint        = s;
	t->progress_forecolor   = (TColor) 0x008A28E5;
	t->progress_percentage  = 0;

	t->bUpdateFinishBytes   = false;
	t->SyncInitProgress();

    return 0;
}
//---------------------------------------------------------------------------
static int __stdcall cb_update_param( unsigned char percent, void *usr_arg )
{
	tboot_1 *t = (tboot_1 *)usr_arg;

	t->progress_percentage  = percent;

	t->bUpdateFinishBytes   = false;
	t->SyncUpdateProgress();

    return 0;
}
//---------------------------------------------------------------------------
static int __stdcall cb_security_post_process_notify(void *usr_arg)
{

	tboot_1 *t=(tboot_1 *)usr_arg;

	t->asMsg.printf("Proceed 1st time download post-process ... (it takes about 10~15 seconds)\n\nPlease press OK to continue!");
	t->SyncShowMsg();

    return 0;
}
/******************************************************************************/
/* Parameter Page Modules                                                     */
/*                                                                            */
/*                                                                            */
/******************************************************************************/
//---------------------------------------------------------------------------
int tboot_1::Parameter ()
{
    int     ret = S_DONE;
    bool    bParameterUpdate 	= false;
//	bool    bGpsFWUpdate		= false;

	if( !g_bParameterPage ) {
	    asMsg.printf("Please Setup any parameter first!!");
		return -1;
    }

    if( MainForm->cb_otp->Checked   /* || MainForm->cb_sec_setting->Checked ||
        MainForm->cb_sec_ro->Checked || MainForm->cb_cust->Checked  */){
        bParameterUpdate = true;
    }
#if 0
    if( MainForm->cb_gps->Checked ){
        bGpsFWUpdate = true;
    }
#endif

	if( bParameterUpdate /*|| bGpsFWUpdate*/ )
    {
//        // fill COM_PORT_SETTING parameter
//        ArgComPortSetting( com );
//
//        // fill FLASHTOOL_ARG
//        ArgFlashTool( arg, result );
//
//        // fill FLASHTOOL Parameter
//        FLASHTOOL_PARAMETER_ARG     pm_arg;
//        FLASHTOOL_PARAMETER_RESULT  pm_result;
//        ArgFlashToolParameter( pm_arg, pm_result );
//
//	    ret = FlashParameter( &com, &arg, &result, &pm_arg, &pm_result, &g_stopflag );

		ret = FlashParameter_internal();

		if( S_DONE != ret ) return ret;

//        // OTP Readback file save
//        if( MainForm->cb_otp->Checked && MainForm->rb_otp_Read->Checked && g_ParamReadbackConfig.m_otp_enable )
//        {
//		    if( MainForm->SaveFile(g_ParamReadbackConfig.m_otp_filepath.c_str(), pm_arg.m_param.m_otp.m_data,pm_arg.m_param.m_otp.m_len) )
//            {
//			    asMsg.printf("Fail to open \"%s\"!", g_ParamReadbackConfig.m_otp_filepath.c_str());
//				Synchronize(ShowMsg);
//            }
//        }

        //unused features
#if 0
        // secure RO setting Readback file save
		if( MainForm->cb_sec_ro->Checked && MainForm->rb_sec_ro_Read->Checked && g_ParamReadbackConfig.m_sec_ro_enable )
        {
		    if( MainForm->SaveFile(g_ParamReadbackConfig.m_sec_ro_filepath.c_str(),pm_arg.m_param.m_sec_ro.m_data,pm_arg.m_param.m_sec_ro.m_len) )
            {
                asMsg.printf("Fail to open \"%s\"!", g_ParamReadbackConfig.m_sec_ro_filepath.c_str());
                Synchronize(ShowMsg);
            }
        }

        // customer Parameter Readback file save
		if( MainForm->cb_cust->Checked && MainForm->rb_cust_Read->Checked && g_ParamReadbackConfig.m_cust_para_enable )
        {
            if( MainForm->SaveFile(g_ParamReadbackConfig.m_cust_para_filepath.c_str(),pm_arg.m_param.m_cust_para.m_data,pm_arg.m_param.m_cust_para.m_len) )
            {
			    asMsg.printf("Fail to open \"%s\"!", g_ParamReadbackConfig.m_cust_para_filepath.c_str());
                Synchronize(ShowMsg);
            }
        }

        // GPS FW Download/Readback (gps_brom.dll)
        if( bGpsFWUpdate )
        {
            if ( g_bUsbDLRB )
            {
                asMsg = " GPS Download/Readback was forbidden by USB!!\n Please use the UART cable to Download/Readback GPS ROM. ";
                return -1;
            }

		    if( MainForm->rb_gps_Write->Checked && g_ParamDownloadConfig.m_gps_enable )
            {
		    	ErrorLookup::SetErrorCodeMode(GPS);
//                g_error_code_mode = GPS;
		        ret = GPSDownload();
                if( S_DONE != ret ) return ret;
            }
            else if( MainForm->rb_gps_Read->Checked && g_ParamReadbackConfig.m_gps_enable )
            {
            	ErrorLookup::SetErrorCodeMode(GPS);
//                g_error_code_mode = GPS;
		        ret = GPSReadback();
                if( S_DONE != ret ) return ret;
            }
        }
#endif
    } // bParameterUpdate || bGpsFWUpdate

    return ret;
}
//---------------------------------------------------------------------------
int tboot_1::FlashToolOTP( void )
{
    int ret;
    unsigned int com_port = (g_bUsbDLDA || g_bUsbMode )? GetUSBVCOMNumByPortName(m_strPort) : COM_PORT;

    // fill FLASHTOOL Parameter
    FLASHTOOL_PARAMETER_ARG     pm_arg;
    FLASHTOOL_PARAMETER_RESULT  pm_result;
    ArgFlashToolOTP( pm_arg, pm_result );

    Logger::GetLogger().Log(Logger::Debug,
               "Parameter: SkipBootRom: %d, DA_Handle is: %s, USB VCOM Num is: %d \n(%s,%d)",
        		g_bSkipBootRom, arg.m_boot_arg.m_da_handle, com.com.number,
        		__FILE__, __LINE__);

    //-1. Connect and get the HW information
    ArgFlashToolConnect(cn_arg, cn_result);
    if (!g_bUsbDLDA) {
        LOGD("OTP By UART: FLASHTOOL_PARAMETER, OTP connect VIA UART.");
        int  force_charge = /*g_bUsbModeWithBattery ? 0 : 1*/GetBatteryStatus();
	 LOGD("FlashDownload_internal: force_charge(%d)", force_charge);
        ret = FlashTool_Connect( com_port, &cn_arg, &cn_result, NULL, &g_stopflag, &g_ft_handle,force_charge);
    } else {
        LOGD("OTP By USB: FLASHTOOL_PARAMETER, OTP connect VIA USB.");
        ret = FlashTool_NandUtil_Connect( com_port, &cn_arg, &cn_result, &g_stopflag, &g_ft_handle);
        //ret = FlashTool_Connect( com_port, &cn_arg, &cn_result, &g_stopflag, &g_ft_handle);
    }
    if( S_DONE != ret ) {
        FlashTool_Disconnect( &g_ft_handle );
        return ret;
    }

    //check if OTP has been locked, if locked, pop msg to user, if not, continue...
    if(pm_arg.m_param.m_otp_op != OTP_READ)
    {
          ret = FlashTool_OTP_LockCheckStatus(g_ft_handle);
          if(ret != S_DA_OTP_UNLOCKED)
          {
                 FlashTool_Disconnect(&g_ft_handle);
                 return ret;
          }
    }

    switch(pm_arg.m_param.m_otp_op)
    {
        case OTP_READ : 
            ret = FlashTool_OTP_Read(g_ft_handle, &pm_arg.m_param.m_otp);
            break;
         case OTP_WRITE : 
            ret = FlashTool_OTP_Write(g_ft_handle, &pm_arg.m_param.m_otp);
            break;   
         case OTP_LOCK : 
            ret = FlashTool_OTP_Lock(g_ft_handle);
            break;
         case OTP_WRITE_AND_LOCK :
            ret = FlashTool_OTP_Write(g_ft_handle, &pm_arg.m_param.m_otp);
            ret = FlashTool_OTP_Lock(g_ft_handle);
            break;
         default:
            break;
    }
    if( S_DONE != ret ) return ret;

    // OTP Readback file save
    if( MainForm->cb_otp->Checked && MainForm->rb_otp_Read->Checked && g_ParamReadbackConfig.m_otp_enable )
    {
	    if( MainForm->SaveFile(g_ParamReadbackConfig.m_otp_filepath.c_str(), pm_arg.m_param.m_otp.m_data,pm_arg.m_param.m_otp.m_len) )
        {
		    asMsg.printf("Fail to open \"%s\"!", g_ParamReadbackConfig.m_otp_filepath.c_str());
			Synchronize(ShowMsg);
            FlashTool_Disconnect(&g_ft_handle);
            ret = S_FT_OTP_INVALID_ADDRESS_RANGE;
        }
    }
    if(!ToolInfo::IsCustomerVer()) {
		FlashTool_EnableWDT_Arg wdt_arg;
		FlashTool_EnableWDT_Arg *p_wdt_arg = &wdt_arg;
		ArgFlashToolWatchDog(p_wdt_arg);
		ret = FlashTool_EnableWatchDogTimeout(g_ft_handle, p_wdt_arg);
		if( S_DONE != ret ) return ret;
	} 
    ret = FlashTool_Disconnect(&g_ft_handle);
    if( S_DONE != ret ) return ret;
    
    return ret;
}
//---------------------------------------------------------------------------
int tboot_1::ParameterSecRomLock( void )
{
    // fill Android download argument
    EBOOT_RESULT ret ;
    char sec_log[1024] = {'0'};

    Android_Boot_ARG             boot_arg;
    memset(&boot_arg, 0, sizeof(boot_arg));
    Android_Download_ARG         dl_arg;
    memset(&dl_arg, 0, sizeof(dl_arg));
    string   s_com_symbol;
    string   s_port_str;
    time_t   start, finish;
    SecurityBitCtrl_YuSu_T sec_arg;

    for(unsigned char i = 0; i < MAX_IMG_LOCK_COUNT; i++)
    {
    	sec_arg.img_info[i].image_type = DM_IMG_TYPE_UNKNOWN;
    	sec_arg.img_info[i].m_disable_download = 1;
    	sec_arg.m_lockdown = 1;
    }

    ErrorLookup::SetErrorCodeMode(FLASHTOOL);
    LOGD("Double scan: Begin second scan USB VCOM port!");
	FlashToolUSBTable usb_table = GetFlashToolUSBTable();
	FlashToolUSB usb_preloader;
	if ( !usb_table.QueryUSBItemByName(FlashToolUSB::PRELOADER_VCOM, usb_preloader) ) {
		LOG("ERROR: tboot_1::ParameterSecRomLock(): QueryUSBItemByName(): (%s) failed!",
			FlashToolUSB::PRELOADER_VCOM.c_str());
	} else {
		LOG("tboot_1::ParameterSecRomLock(): QueryUSBItemByName(): Name(%s), PID(%s), VID(%s)",
			usb_preloader.GetUSBName().c_str(),
			usb_preloader.GetUSBPID().c_str(),
			usb_preloader.GetUSBVID().c_str());
	}
    //Get start time
    time(&start);
    Synchronize(StartUSBHintTimer);
    do
    {
        if(BOOT_STOP == g_stopflag)
        {
            LOGD("YuSu: User press stop button !");
            return FT_USER_PRESS_STOP_BUTTON;
        }
        else if( GetNewCreatedUSBVComPort(s_com_symbol,
                                          s_port_str,
                                          m_strSymbolicName,
                                          usb_preloader.GetUSBPID(),
                                          usb_preloader.GetUSBVID())
                                          )
        {
            //find usb_com port via MS DDK
            Synchronize(StopUSBHintTimer);
            Logger::GetLogger().Log(Logger::Debug,
            		"Double scan: Find usb port, symblic name is %s, friendly name is %s.(%s,%d)",
            		s_com_symbol.c_str(), s_port_str.c_str(), __FILE__, __LINE__);
            break;
        }
        //Get current time
        time( &finish );

        if(difftime( finish, start) > 5)
        {
           Synchronize(StopUSBHintTimer);
           LOGD("Double scan: time out 5s passed, miss the chance to insert USB cable!");
        }

        //wait 10s if there still not found a new usb com port
        if(difftime( finish, start ) > 10 )
        {
             LOGD("Double scan: time out 10s passed, search usb port error!");
             return FT_FIND_USB_ERROR;
        }
    }while(1);
	//set eboot error mode
    ErrorLookup::SetErrorCodeMode(EBOOT);

    unsigned int baudrate_tbl[] = { 0, 921600, 460800, 230400, 115200, 57600, 38400, 19200, 9600, 4800, 2400, 1200, 300, 110 };
    // Boot As Download Mode
    boot_arg.m_baud_rate  = (COMM_BAUDRATE)baudrate_tbl[BAUD_RATE];
    boot_arg.m_comport    = boot_arg.m_comport;
    boot_arg.m_p_comsymbol= (char*)s_com_symbol.c_str();
    boot_arg.m_p_stopflag = &g_stopflag;
    boot_arg.m_p_thread   = this;

    dl_arg.usb_com                         = boot_arg.m_comport;
    dl_arg.m_p_stopflag                 = &g_stopflag;
    dl_arg.m_p_thread                   = this;
    dl_arg.m_p_send_flash_percentage    = show_dl_percentage;
    dl_arg.m_p_send_image_file_status   = set_send_image_file_info;
    dl_arg.reboot_mode = REBOOT;
    dl_arg.is_verify = false;
    //For new scatter file image size check
    dl_arg.is_boundary_Check = IsNewScatterFileWithBoundaryCheck(g_pCurNode->m_dl_handle);

    FillAndroidImageRegionInfo(g_pCurNode->m_dl_handle,dl_arg.m_region_info, dl_arg.m_region_num);

    LOGD(string("[Android_Images_Lock] Is to do image boundary check: ")
    		.append((true == dl_arg.is_boundary_Check) ? "Y" : "N").c_str());

    //Security rom lock setting
    sec_arg.m_lockdown = g_ParamsecBitCtrlYuSu.m_lockdown;

    //char sec_img_setting[30] = {'0'};
    LOGD("==================================Security rom lock setting:==================================");
    strcpy( sec_log, "[Hint]  Security Rom Lock Result: \r\n\r\n");
    unsigned short count;
    unsigned short index = 0;
    if (!DL_GetCount(g_pCurNode->m_dl_handle, &count))
    {    
        ROM_INFO rom[MAX_LOAD_SECTIONS];

        if (!DL_Rom_GetInfoAll(g_pCurNode->m_dl_handle, rom, MAX_LOAD_SECTIONS))
        {
            for (int i = 1; i < count; i++)
            {
                const AndroidImageInfo &imgInfo =
                		GetAndroidImageInfoTable()[rom[i].name];
                if(imgInfo.isValid)
                {
                    sec_arg.img_info[imgInfo.androidFileIndex].image_type = imgInfo.type;
                	sec_arg.img_info[imgInfo.androidFileIndex].m_disable_download =
                        g_ParamsecBitCtrlYuSu.img_info[imgInfo.androidFileIndex].m_disable_download;
                    GetLockImageInfo( sec_arg, rom[i].name,
                    		imgInfo.androidFileIndex, sec_log);
                    index++;
                }
	        }
       }
    }
    sec_arg.img_info[index].image_type = DM_IMG_TYPE_FT_LOCK_INFORM;
    sec_arg.img_info[index].m_disable_download = 0;

    LOGD(sec_log);
    LOGD("==================================Security rom lock setting end.==================================");

    ret = Android_Set_Lock(boot_arg, dl_arg, sec_arg);

    if ( SET_LOCK_RESPONSE_ERROR == ret )
    {
        asMsg = " \nImage Download Lock Setting Error !\n\nImage lock operation can only be processed ONCE!\n";
        return ret;
    }
    else if(EBOOT_SUCCESS != ret)
    {
        asMsg = " Image Download Lock Setting Error !";
        //Synchronize(ShowMsg);
        return ret;
    }
    
    return S_DONE;
}

//---------------------------------------------------------------------------
void tboot_1::FillColumnInfo(char* pSecLOg, const char* pColFir, 
                              const char* pColSec, const char* pColTir)
{
    const unsigned char LOG_IS_DL_POS = 20;
    const unsigned char LOG_FINAL_DL_INFO_POS = 40;

    CharMove(pSecLOg, pColFir, 0, strlen(pColFir));
    CharMove(pSecLOg, pColSec, LOG_IS_DL_POS, strlen(pColSec));
    CharMove(pSecLOg, pColTir, LOG_FINAL_DL_INFO_POS, strlen(pColTir));   
}

//---------------------------------------------------------------------------
int tboot_1::GetLockImageInfo(const SecurityBitCtrl_YuSu_T &secBitCtrl,
                                     const char *romName, 
                                     const unsigned char index, 
                                     char *sec_log)
{
    const char *p_ALL_LOCK_INFO = "All images have been locked. None has been downloaded!\r\n";
    const char *p_LOCK_INFO = "LOCKED";
    const char *p_UNLOCK_INFO = "DOWNLOADED";
    const char *p_UNSTART_INFO = "NOT START";
    const unsigned char LOG_ROW_LEN = 61; 

    char sec_img_setting[LOG_ROW_LEN] = "";
    memset(sec_img_setting, '\ ', LOG_ROW_LEN-2);
    sec_img_setting[LOG_ROW_LEN-3] = '\r';
    sec_img_setting[LOG_ROW_LEN-2] = '\n';

    if ( !secBitCtrl.m_lockdown && NULL == romName )
    {
        strcat(sec_log, p_ALL_LOCK_INFO);
        return g_ParamImageLockAll = ALL_IMG_LOCKED;
    }
    else 
    {

        if ( LOCKED == secBitCtrl.img_info[index].m_disable_download)
        {
            FillColumnInfo(sec_img_setting, romName, "N", p_LOCK_INFO); 
            strcat(sec_log, sec_img_setting);
        }
        else if (NOT_LOCKED == secBitCtrl.img_info[index].m_disable_download )
        {
            FillColumnInfo(sec_img_setting, romName, "Y", p_UNLOCK_INFO);
            strcat(sec_log, sec_img_setting);
        }
        else if ( LOCK_NOT_START == secBitCtrl.img_info[index].m_disable_download )
        {
            FillColumnInfo(sec_img_setting, romName, "N", p_UNSTART_INFO);
            strcat(sec_log, sec_img_setting);
        }
    }                                       
    return g_ParamImageLockAll = PARTIAL_IMG_LOCKED;
}

/******************************************************************************/
/* GPS Modules                                                                */
/*                                                                            */
/*                                                                            */
/******************************************************************************/
//---------------------------------------------------------------------------
static int __stdcall cb_gps_download_da_init( void *usr_arg );
static int __stdcall cb_gps_download_da( unsigned char percent, unsigned int sent_bytes, unsigned int total_bytes, void *usr_arg );
static int __stdcall cb_gps_download_flash_init( void *usr_arg );
static int __stdcall cb_gps_download_flash( unsigned char percent, unsigned int sent_bytes, unsigned int total_bytes, void *usr_arg );
static int __stdcall cb_gps_readback_flash_init( const char *rb_filepath, void *usr_arg );
static int __stdcall cb_gps_readback_flash( unsigned char percent, unsigned int sent_bytes, unsigned int total_bytes, void *usr_arg );
//---------------------------------------------------------------------------
WRAPPER_RETURN tboot_1::GPSDownload(void)
{

    CBromDllWrapper	    m_wrapper;
    WRAPPER_RETURN      ret;
    AnsiString          strAppDir;
    AnsiString          strLog	= "C:\\BROM_DLL_gps.log";	// default value.
    AnsiString          strDLL;
    AnsiString          strDA;
    AnsiString          strScat;
    AnsiString          strImg;
    CallBackFlashtool   cbFlashtool;
    CallBackDownload    cbDownload;

    // Init path
    strAppDir   = ExtractFilePath(Application->ExeName);
    strDLL      = strAppDir + "gps_brom.dll";
    strDA       = strAppDir + "gps_DA.bin";
    strScat     = strAppDir + "scat.txt";

    // get the  "mt33XX_gps_core.bin" file path
    if ( g_bParameterPage ) {
        strImg   = g_ParamDownloadConfig.m_gps_rom_filepath;
    }
    else {
        strImg   = g_DL_HANDLE_NODE.m_param.m_gps_rom_filepath;
    }


    memset( &cbFlashtool, 0, sizeof(cbFlashtool));
    memset( &cbDownload,  0, sizeof(cbDownload));

    cbFlashtool.cb_download_da_init         = cb_gps_download_da_init;
    cbFlashtool.cb_download_da_init_arg     = this;
    cbFlashtool.cb_download_da              = cb_gps_download_da;
    cbFlashtool.cb_download_da_arg          = this;

    cbDownload.cb_download_flash_init       = cb_gps_download_flash_init;
    cbDownload.cb_download_flash_init_arg   = this;
    cbDownload.cb_download_flash            = cb_gps_download_flash;
    cbDownload.cb_download_flash_arg        = this;

    //- 1. Load BromDLL library
    if( COMPLETE_SUCCESS != (ret = m_wrapper.fnLoadBromDLL(strDLL.c_str())) ) {
        if( ERROR_DLL_NOT_LOAD == ret ){
            ShowMessage("[Error] Loaded GPS BROM DLL but failed");
	    	return ERROR_DLL_NOT_LOAD;
        }
        else{
            return ret;
        }
    }

    m_wrapper.fnDebugOn(strLog.c_str());  //-- Debug On

    //- 2. Load DA
    if( COMPLETE_SUCCESS != (ret = m_wrapper.fnLoadDA(strDA.c_str())) ){
        return ret;
    }

    //- 3. Load Scatter file and Firmware
    if( COMPLETE_SUCCESS != (ret = m_wrapper.fnLoadImageByScatter(strScat.c_str(),strImg.c_str())) ){
        return ret;
    }

    //- 4. Download Firmware
    if( COMPLETE_SUCCESS != (ret = m_wrapper.fnDownloadFirmware(COM_PORT, &cbFlashtool, &cbDownload, &g_stopflag)) ){
        return ret;
    }

    m_wrapper.fnDebugOff(); //-- Debug Off

    return COMPLETE_SUCCESS;
}
//---------------------------------------------------------------------------

WRAPPER_RETURN tboot_1::GPSReadback( void )
{

    CBromDllWrapper	    m_wrapper;
    WRAPPER_RETURN      ret;
    AnsiString          strAppDir;
    AnsiString          strLog	= "C:\\BROM_DLL_gps.log";	// default value.
    AnsiString          strDLL;
    AnsiString          strDA;
    AnsiString          strRB;
    unsigned int        szRBAddr;
    unsigned int        szRBLen;
    CallBackFlashtool   cbFlashtool;
    CallBackReadback    cbReadback;

    // Init path
    strAppDir       = ExtractFilePath(Application->ExeName);
    strDLL          = strAppDir + "gps_brom.dll";
    strDA           = strAppDir + "gps_DA.bin";
//    strScat       = strAppDir + "scat.txt";

    if ( g_bParameterPage ) {
        strRB   	= g_ParamReadbackConfig.m_gps_rom_filepath;
        szRBAddr	= 0;
        szRBLen		= g_ParamReadbackConfig.m_gps_rom_filesize;
    }
    else {
        strRB   	= g_DL_HANDLE_NODE.m_param.m_gps_rom_filepath;
        szRBAddr	= 0;
        szRBLen		= g_DL_HANDLE_NODE.m_param.m_gps_rom_filesize;
    }


    memset(&cbFlashtool, 0, sizeof(cbFlashtool));
    memset(&cbReadback,  0, sizeof(cbReadback));

    cbFlashtool.cb_download_da_init         = cb_gps_download_da_init;
    cbFlashtool.cb_download_da_init_arg     = this;
    cbFlashtool.cb_download_da              = cb_gps_download_da;
    cbFlashtool.cb_download_da_arg          = this;

    cbReadback.cb_readback_flash_init       = cb_gps_readback_flash_init;
    cbReadback.cb_readback_flash_init_arg   = this;
    cbReadback.cb_readback_flash            = cb_gps_readback_flash;
    cbReadback.cb_readback_flash_arg        = this;

    //- 1. Load BromDLL library
    if( COMPLETE_SUCCESS != (ret = m_wrapper.fnLoadBromDLL(strDLL.c_str())) ) {
        if( ERROR_DLL_NOT_LOAD == ret ){
            ShowMessage("[Error] Loaded GPS BROM DLL but failed");
	    	return ERROR_DLL_NOT_LOAD;
        }
        else{
            return ret;
        }
    }

    m_wrapper.fnDebugOn(strLog.c_str());  //-- Debug On

    //- 2. Load DA
    if( COMPLETE_SUCCESS != (ret = m_wrapper.fnLoadDA(strDA.c_str())) ){
        return ret;
    }

    //- 3. Setup RB List
    if( COMPLETE_SUCCESS != (ret = m_wrapper.fnSetRBList(strRB.c_str(),szRBAddr,szRBLen)) ){
        return ret;
    }

    //- 4. Readback Firmware
    if( COMPLETE_SUCCESS != (ret = m_wrapper.fnReadbackFirmware(COM_PORT, &cbFlashtool, &cbReadback, &g_stopflag)) ){
        return ret;
    }

    m_wrapper.fnDebugOff(); //-- Debug Off

    return COMPLETE_SUCCESS;
}

//---------------------------------------------------------------------------
static int __stdcall cb_gps_download_da_init( void* usr_arg )
{

	tboot_1 *t = (tboot_1 *)usr_arg;

	t->progress_hint            = "Download GPS's DA now...";
    t->progress_forecolor       = clSkyBlue;
	t->progress_percentage      = 0;
	t->progress_finished_bytes  = 0;

	t->bUpdateFinishBytes       = true;
	t->SyncInitProgress();

    return 0;
}
//---------------------------------------------------------------------------
static int __stdcall cb_gps_download_da( unsigned char  percent,
                                         unsigned int   sent_bytes,
                                         unsigned int   total_bytes,
                                         void* usr_arg)
{

	tboot_1 *t = (tboot_1 *)usr_arg;

	t->progress_percentage      = percent;
	t->progress_finished_bytes  = sent_bytes;
	t->progress_total_bytes     = total_bytes;

	t->bUpdateFinishBytes       = true;
	t->SyncUpdateProgress();

    return 0;
}
//---------------------------------------------------------------------------
static int __stdcall cb_gps_download_flash_init( void* usr_arg )
{

	tboot_1 *t = (tboot_1 *)usr_arg;

	t->progress_hint            = "Download firmware to GPS's flash now...";
	t->progress_forecolor       = clSkyBlue;
	t->progress_percentage      = 0;
	t->progress_finished_bytes  = 0;

	t->bUpdateFinishBytes       = true;
	t->SyncInitProgress();

    return 0;
}
//---------------------------------------------------------------------------
static int __stdcall cb_gps_download_flash( unsigned char   percent,
                                            unsigned int    sent_bytes,
                                            unsigned int    total_bytes,
                                            void* usr_arg)
{

	tboot_1 *t=(tboot_1 *)usr_arg;

	t->progress_percentage      = percent;
	t->progress_finished_bytes  = sent_bytes;
	t->progress_total_bytes     = total_bytes;

	t->bUpdateFinishBytes       = true;
	t->SyncUpdateProgress();

    return 0;
}
//---------------------------------------------------------------------------
static int __stdcall cb_gps_readback_flash_init( const char* rb_filepath,
                                                 void* usr_arg)
{

	tboot_1 *t = (tboot_1 *)usr_arg;

    AnsiString s;

   	s.printf("Readback GPS FW from flash to \"%s\". ", rb_filepath);

	t->progress_hint            = s;
	t->progress_forecolor       = clSkyBlue;
	t->progress_percentage      = 0;
	t->progress_finished_bytes  = 0;

	t->bUpdateFinishBytes       = true;
	t->SyncInitProgress();

    return 0;
}
//---------------------------------------------------------------------------
static int __stdcall cb_gps_readback_flash( unsigned char percent,
                                            unsigned int sent_bytes,
                                            unsigned int total_bytes,
                                            void* usr_arg)
{

	tboot_1 *t = (tboot_1 *)usr_arg;

	t->progress_percentage      = percent;
	t->progress_finished_bytes  = sent_bytes;
	t->progress_total_bytes     = total_bytes;

	t->bUpdateFinishBytes       = true;
	t->SyncUpdateProgress();

    return 0;
}

/******************************************************************************/
/* Memory Test Modules                                                        */
/*                                                                            */
/*                                                                            */
/******************************************************************************/
//---------------------------------------------------------------------------
static int __stdcall cb_memorytest_init(void *user_arg);
static int __stdcall cb_memorytest_progress(unsigned int current_progress, void *usr_arg);
//---------------------------------------------------------------------------
int tboot_1::MemoryTest()
{
    // Reset Memory Test 's Result Memo
    MainForm->m_MT_ResultRichEditor->Text = "";
    MainForm->m_MT_ResultRichEditor->Update();

    //-1. Connect and get the HW information
    ArgFlashToolConnect(cn_arg, cn_result);
    unsigned char  com_port = (!g_bUsbMode) ? COM_PORT : GetUSBVCOMNumByPortName(m_strPort);
    
    int  force_charge = /*g_bUsbModeWithBattery ? 0 : 1*/GetBatteryStatus();
    LOGD("FlashDownload_internal: force_charge(%d)", force_charge);
    int ret = FlashTool_Connect( com_port, &cn_arg, &cn_result, NULL, &g_stopflag, &g_ft_handle,force_charge);
    if( S_DONE != ret ) {
        FlashTool_Disconnect( &g_ft_handle );
        return ret;
    }

    // if SRAM was not found, try to detect DRAM
    if ( S_DONE != cn_result.m_da_report.m_ext_ram_ret ) {
        ret = EnableDRAM( &cn_result );
    }

    //-2. update the memory detection report
    UpdateMemoryTestDetection ( );


    // FlashTool_MemoryTest_Arg initial setting
    FlashTool_MemoryTest_Arg            mt_arg;
    FlashTool_MemoryTest_Result         mt_result;
    ArgFlashToolMemoryTest( mt_arg , mt_result );

    // RAM test
    if (  MainForm->RAMCheckBox->Checked == true )
    {
        UpdateMemoryTestRichEditor("============\t\t RAM Test\t\t ============\r\n",  clPurple   );

        // if SRAM/DRAM is not dectected
        if ( HW_RAM_UNKNOWN == cn_result.m_da_report.m_ext_ram_type ) {
            UpdateMemoryTestRichEditor("SKIP! External RAM was not detected!\r\n",  clRed   );
        } else {
            // do RAM test
            ret = RAMTest( &mt_arg, &mt_result );
        }
    }
#if 0
    // NOR Flash test
    if (  MainForm->NORCheckBox->Checked == true )
    {
        UpdateMemoryTestRichEditor("============\t\t NOR Test\t\t ============\r\n",  clPurple   );

        // if NOR Flash is not found
		if( S_DONE != cn_result.m_da_report.m_nor_ret ) {
            UpdateMemoryTestRichEditor("SKIP! NOR Flash was not detected!\r\n",  clRed   );
        } else {
            // do NOR test
            ret = NORTest( &mt_arg, &mt_result );

        }
    }
#endif
    // NAND Flash test
    if (  MainForm->NANDCheckBox->Checked == true )
    {
        UpdateMemoryTestRichEditor("============\t\t NAND Test\t\t ============\r\n",  clPurple  );

        if ( S_DONE != cn_result.m_da_report.m_nand_ret ) {
            UpdateMemoryTestRichEditor("SKIP! NAND Flash was not detected!\r\n",  clRed   );
        } else {
            // do NAND test
            ret = NANDTest( &mt_arg, &mt_result );
        }
    }

    //EMMC test
    if (  MainForm->EMMCCheckBox->Checked == true )
    {
        UpdateMemoryTestRichEditor("============\t\t EMMC Test\t\t ============\r\n",  clPurple   );

        // if NOR Flash is not found
		if( S_DONE != cn_result.m_da_report.m_emmc_ret ) {
            UpdateMemoryTestRichEditor("SKIP! EMMC was not detected!\r\n",  clRed   );
        } else {
            // do NOR test
            ret =EMMCTest( &mt_arg, &mt_result );

        }
    }

    // Disconnect
    FlashTool_Disconnect( &g_ft_handle );

    return ret;
}
//---------------------------------------------------------------------------
int tboot_1::EnableDRAM( FlashTool_Connect_Result   *cn_result)
{
    int  ret;
    DRAM_SETTING    dram_cfg;

    //-1. Get the DRAM EMI Setting
    // from the DRAM Setting from UI
    //for smart phone EMI setting wayne add,
//     g_EMI_NFI_Setting.m_dram_cfg.m_valid = TRUE;
    if ( g_EMI_NFI_Setting.m_dram_cfg.m_valid == TRUE  ) {
        memcpy( &dram_cfg, &g_EMI_NFI_Setting.m_dram_cfg, sizeof(DRAM_SETTING) );
    }
    else {
        // added combo mcp
        //unsigned int nand_id =  ((unsigned int)cn_result->m_da_report.m_nand_flash_dev_code_1)<<8
        //    | ((unsigned int)cn_result->m_da_report.m_nand_flash_dev_code_2);

    	// from the MTK_ROM_INFO field in the ROM
        DL_HANDLE_T &dl_handle = g_pCurNode->m_dl_handle;
		DA_REPORT_T* p_da_report = &(cn_result->m_da_report);
		LOGD("dl_handle(0x%x), dram_cfg(0x%x), p_da_report(0x%x).", dl_handle, &dram_cfg, p_da_report);
        ret = DL_GetDRAMSetting ( dl_handle, &dram_cfg, p_da_report);
        if ( S_DONE != ret ) return ret;
    }

    //-2. enable DRAM
    FlashTool_EnableDRAM_Result   dram_result;
    ret = FlashTool_EnableDRAM ( g_ft_handle, dram_cfg, &dram_result );
    if ( S_DONE != ret ) return ret;

    //-3. update the connect result
    cn_result->m_da_report.m_ext_ram_ret         = dram_result.m_ext_ram_ret;
    cn_result->m_da_report.m_ext_ram_type        = dram_result.m_ext_ram_type;
    cn_result->m_da_report.m_ext_ram_chip_select = dram_result.m_ext_ram_chip_select;
    cn_result->m_da_report.m_ext_ram_size        = dram_result.m_ext_ram_size;

    return ret;
}
//---------------------------------------------------------------------------
int tboot_1::RAMTest( FlashTool_MemoryTest_Arg        *mt_arg,
                      FlashTool_MemoryTest_Result     *mt_result)
{
    int ret = S_DONE;

    // RAM Test 1.1 : Bus Test
    if ( MainForm->cb_MT_RAM_Data_Bus_Test->Checked )
    {
        UpdateMemoryTestRichEditor( "Data Bus Test :\r\n",  clBlack );
        ret = RAMDataBusTest( mt_arg, mt_result );
        if( S_DONE != ret ) {
            UpdateMemoryTestRichEditor( "FAILED!!\r\n",  clRed );
        } else {
            UpdateMemoryTestRichEditor( "OK!!\r\n",  clBlue );
        }
	}

    // RAM Test 1.2 : Addr Test
	if ( MainForm->cb_MT_RAM_Addr_Bus_Test->Checked )
    {
        UpdateMemoryTestRichEditor( "Address Bus Test :\r\n",  clBlack );
        ret = RAMAddrBusTest( mt_arg,  mt_result );
        if( S_DONE != ret ) {
            UpdateMemoryTestRichEditor( "FAILED!!\r\n",  clRed   );
        } else {
            UpdateMemoryTestRichEditor( "OK!!\r\n",  clBlue   );

        }
	 }

     // RAM Test 1.3 : Pattern Test
     if ( MainForm->cb_MT_RAM_Pattern_Test->Checked )
     {
        // define the pattern set for pattern test
        int test_pattern[9] = {0x44332211, 0xA5A5A5A5, 0xA5A5A500,
                               0xA500A500, 0xA5000000, 0x00000000,
                               0xFFFF0000, 0xFFFFFFFF, 0x5A5A5A5A};

        UpdateMemoryTestRichEditor("RAM Pattern Test :\r\nWriting ...",  clBlack   );
        ret = RAMPatternTest( mt_arg,  mt_result, test_pattern, 8 );
        if( S_DONE != ret ) {
            UpdateMemoryTestRichEditor( "FAILED!!\r\n",  clRed   );
        } else {
            UpdateMemoryTestRichEditor( "OK!!\r\n",  clBlue   );

        }
     }

    // RAM Test 1.4 : Increment/Decrement Test
    if ( MainForm->cb_MT_RAM_Inc_Dec_Test->Checked )
    {
        UpdateMemoryTestRichEditor("Increment/Decrement Test :\r\nWriting ...",  clBlack   );
        ret = RAMIncDecTest( mt_arg,  mt_result);
    }

    return ret;
}

//---------------------------------------------------------------------------

int tboot_1::RAMDataBusTest( FlashTool_MemoryTest_Arg        *mt_arg,
                             FlashTool_MemoryTest_Result     *mt_result)
{

    // DRAM or SRAM
    if ( HW_RAM_DRAM == cn_result.m_da_report.m_ext_ram_type ) {
        mt_arg->m_memory_device = HW_MEM_EXT_DRAM;
    } else {
        mt_arg->m_memory_device = HW_MEM_EXT_SRAM;
    }

    // Test method : data bus
	mt_arg->m_test_method = HW_MEM_DATA_BUS_TEST;

    return  FlashTool_MemoryTest( g_ft_handle, mt_arg, mt_result );
}

//---------------------------------------------------------------------------
int tboot_1::RAMAddrBusTest( FlashTool_MemoryTest_Arg        *mt_arg,
                             FlashTool_MemoryTest_Result     *mt_result)
{
    // DRAM or SRAM
    if ( HW_RAM_DRAM == cn_result.m_da_report.m_ext_ram_type ) {
        mt_arg->m_memory_device = HW_MEM_EXT_DRAM;
    } else {
        mt_arg->m_memory_device = HW_MEM_EXT_SRAM;
    }

    // Test method : address bus
    mt_arg->m_test_method = HW_MEM_ADDR_BUS_TEST;

    return FlashTool_MemoryTest( g_ft_handle, mt_arg, mt_result );
}

//---------------------------------------------------------------------------
int tboot_1::RAMPatternTest( FlashTool_MemoryTest_Arg        *mt_arg,
                             FlashTool_MemoryTest_Result     *mt_result,
                             int                             pattern_set[],
                             int                             pattern_size )
{

    int ret = S_DONE;

    for ( int i = 0 ; i < pattern_size ; i++ )
    {
        AnsiString s;
        s.printf("\t0x%08X, ", pattern_set[i]);
        UpdateMemoryTestRichEditor( s,  clBlack );
        ret = RAMOnePatternTest( mt_arg, mt_result, pattern_set[i] );
    }

    return ret;
}

//---------------------------------------------------------------------------
int tboot_1::RAMOnePatternTest( FlashTool_MemoryTest_Arg        *mt_arg,
                                FlashTool_MemoryTest_Result     *mt_result,
                                int                             pattern )
{

    // DRAM or SRAM
    if ( HW_RAM_DRAM == cn_result.m_da_report.m_ext_ram_type ) {
        mt_arg->m_memory_device = HW_MEM_EXT_DRAM;
    } else {
        mt_arg->m_memory_device = HW_MEM_EXT_SRAM;
    }
    // Test method : pattern test
    mt_arg->m_test_method  = HW_MEM_PATTERN_TEST;
    // Start addess
    mt_arg->m_start_addr   = 0;
    // Size
    mt_arg->m_size         = cn_result.m_da_report.m_ext_ram_size;
    // Memory I/O
    mt_arg->m_memory_io    = HW_MEM_IO_32BIT;
    // Assign the Pattern
    mt_arg->m_test_pattern = pattern;

    return FlashTool_MemoryTest( g_ft_handle, mt_arg, mt_result );
}

//---------------------------------------------------------------------------
int tboot_1::RAMIncDecTest( FlashTool_MemoryTest_Arg        *mt_arg,
                            FlashTool_MemoryTest_Result     *mt_result)
{
    // Memory 32 bits I/O increasement/decreasement pattern test
	int ret = RAMIncDecTestIO( mt_arg, mt_result, HW_MEM_IO_32BIT );
	if( S_DONE != ret ) {
	   	UpdateMemoryTestRichEditor( "FAILED!!\r\n",  clRed   );
    } else {
        UpdateMemoryTestRichEditor( "OK!!\r\n",  clBlue   );
    }

    return ret;
}

//---------------------------------------------------------------------------
int tboot_1::RAMIncDecTestIO( FlashTool_MemoryTest_Arg        *mt_arg,
                              FlashTool_MemoryTest_Result     *mt_result,
                              HW_MemoryIO_E                   io)
{
    // DRAM or SRAM
    if ( HW_RAM_DRAM == cn_result.m_da_report.m_ext_ram_type ) {
        mt_arg->m_memory_device = HW_MEM_EXT_DRAM;
    } else {
        mt_arg->m_memory_device = HW_MEM_EXT_SRAM;
    }

    // Test method : increment/ decrement test
    mt_arg->m_test_method = HW_MEM_INC_DEC_TEST;
    // Start addess
    mt_arg->m_start_addr  = 0;
    // Size
    mt_arg->m_size        = cn_result.m_da_report.m_ext_ram_size;
    // IO
    mt_arg->m_memory_io   = io;

    return FlashTool_MemoryTest(g_ft_handle, mt_arg, mt_result);
}
#if 0
//---------------------------------------------------------------------------
int tboot_1::NORTest( FlashTool_MemoryTest_Arg        *mt_arg,
                      FlashTool_MemoryTest_Result     *mt_result)
{
    int ret = S_DONE;

    // Step 2.1 : Address Bus Test
    if ( MainForm->cb_MT_NOR_Addr_Bus_Test->Checked )
    {
        UpdateMemoryTestRichEditor( "Address Bus Test(High Address Pins): ",  clBlack   );
        ret = NORAddrBusTest( mt_arg, mt_result);
    	if( S_DONE != ret ) {
            UpdateMemoryTestRichEditor( "FAILED!!\r\n",  clRed   );
    	} else {
            UpdateMemoryTestRichEditor( "OK!!\r\n",  clBlue   );
        }
    }

    // Step 2.2 : Pattern Test
    if ( MainForm->cb_MT_NOR_Pattern_Test->Checked )
    {
        UpdateMemoryTestRichEditor( "Pattern Test(0x5A5A):\r\n",  clBlack   );
        ret = NORPatternTest( mt_arg, mt_result);
        if( S_DONE != ret ) {
            UpdateMemoryTestRichEditor( "FAILED!!\r\n",  clRed   );
        } else {
            UpdateMemoryTestRichEditor( "OK!!\r\n",  clBlue   );
        }
    }

    return ret;
}

//---------------------------------------------------------------------------
int tboot_1::NORAddrBusTest( FlashTool_MemoryTest_Arg        *mt_arg,
                             FlashTool_MemoryTest_Result     *mt_result)
{
    // memory device : NOR
    mt_arg->m_memory_device = HW_MEM_NOR;

    // Test method
    mt_arg->m_test_method   = HW_MEM_ADDR_BUS_TEST;

    return FlashTool_MemoryTest(g_ft_handle, mt_arg, mt_result);
}

//---------------------------------------------------------------------------
int tboot_1::NORPatternTest( FlashTool_MemoryTest_Arg        *mt_arg,
                             FlashTool_MemoryTest_Result     *mt_result)
{

    // memory device : NOR
    mt_arg->m_memory_device = HW_MEM_NOR;
    // Test method
    mt_arg->m_test_method   = HW_MEM_PATTERN_TEST;
    // Start address
    mt_arg->m_start_addr    = 0;
    // Size
    mt_arg->m_size          = cn_result.m_da_report.m_nor_flash_size;
    // Memory I/O
    mt_arg->m_memory_io     = HW_MEM_IO_16BIT;
    // Test pattern
    mt_arg->m_test_pattern  = 0x5A5A;

    return FlashTool_MemoryTest(g_ft_handle, mt_arg, mt_result);
}
#endif

//---------------------------------------------------------------------------
int tboot_1::NANDTest( FlashTool_MemoryTest_Arg        *mt_arg,
                       FlashTool_MemoryTest_Result     *mt_result)
{

    int ret = S_DONE;

    // NAND Flash Test : Pattern Test
    if( MainForm->cb_MT_NAND_Pattern_Test->Checked )
    {
        UpdateMemoryTestRichEditor( "Pattern Test (0x5A):\r\n",  clBlack   );
        ret = NANDPatternTest( mt_arg, mt_result);
    	if( S_DONE != ret ) {
            UpdateMemoryTestRichEditor( "FAILED!!\r\n",  clRed   );
        } else {
            UpdateMemoryTestRichEditor( "OK!!\r\n",  clBlue   );
        }
    }

    return ret;
}

//---------------------------------------------------------------------------
int tboot_1::NANDPatternTest( FlashTool_MemoryTest_Arg        *mt_arg,
                              FlashTool_MemoryTest_Result     *mt_result)
{

    // memory device : nand
    mt_arg->m_memory_device = HW_MEM_NAND;
    // Test method
    mt_arg->m_test_method   = HW_MEM_PATTERN_TEST;
    // Start address
    mt_arg->m_start_addr    = 0;
    // Size
    mt_arg->m_size          = cn_result.m_da_report.m_nand_flash_size;
    // Memory I/O
    mt_arg->m_memory_io     = HW_MEM_IO_8BIT;
    // Test pattern
    mt_arg->m_test_pattern  = 0x5A;

    return FlashTool_MemoryTest(g_ft_handle, mt_arg, mt_result);
}

//---------------------------------------------------------------------------
int tboot_1::EMMCTest( FlashTool_MemoryTest_Arg        *mt_arg,
                      FlashTool_MemoryTest_Result     *mt_result)
{
    int ret = S_DONE;

    //Pattern Test
    if ( MainForm->cb_MT_EMMC_Pattern_Test->Checked )
    {
        UpdateMemoryTestRichEditor( "EMMC Pattern Test(0x5A5A):\r\n",  clBlack   );
        ret = EMMCPatternTest( mt_arg, mt_result);
        if( S_DONE != ret ) {
            UpdateMemoryTestRichEditor( "FAILED!!\r\n",  clRed   );
        } else {
            UpdateMemoryTestRichEditor( "OK!!\r\n",  clBlue   );
        }
    }

    return ret;
}

//---------------------------------------------------------------------------
int tboot_1::EMMCPatternTest( FlashTool_MemoryTest_Arg        *mt_arg,
                             FlashTool_MemoryTest_Result     *mt_result)
{

    // memory device : NOR
    mt_arg->m_memory_device = HW_MEM_EMMC;
    // Test method
    mt_arg->m_test_method   = HW_MEM_PATTERN_TEST;
    // Start address
    mt_arg->m_start_addr    = 0;
    // Size
    mt_arg->m_size          = cn_result.m_da_report.m_emmc_ua_size;
    // Memory I/O
    mt_arg->m_memory_io     = HW_MEM_IO_16BIT;
    // Test pattern
    mt_arg->m_test_pattern  = 0x5A5A;

    return FlashTool_MemoryTest(g_ft_handle, mt_arg, mt_result);
}

//---------------------------------------------------------------------------
void tboot_1::UpdateMemoryTestDetection()
{

    AnsiString s;
    UpdateMemoryTestRichEditor("===============	Memory Detection Report	 ===============\r\n", clHotLight  );

    // Internal SRAM report
    UpdateMemoryTestRichEditor( "Internal RAM:\r", clBlack );
   	switch( cn_result.m_da_report.m_int_sram_ret )
    {
	    case S_DONE:
            s.printf( "\tSize = 0x%08X (%dKB)\r\n",
                      cn_result.m_da_report.m_int_sram_size,
                      cn_result.m_da_report.m_int_sram_size/1024);

            UpdateMemoryTestRichEditor( s, clBlack );
		    break;

	    case S_DA_RAM_FLOARTING:
            UpdateMemoryTestRichEditor( "\tERROR: Internal SRAM data is floating!!\r\n", clRed );
		    break;

	    case S_DA_RAM_UNACCESSABLE:
            UpdateMemoryTestRichEditor( "\tERROR: Internal SRAM data is un-accessable!!\r\n", clRed );
		    break;

	    case S_DA_RAM_ERROR:
        default:
            UpdateMemoryTestRichEditor( "\tERROR: Internal SRAM was not detected!!\r\n", clRed );
		    break;
	}


    // External RAM (SRAM/DRAM) report
    UpdateMemoryTestRichEditor( "External RAM:\r", clBlack );
	switch( cn_result.m_da_report.m_ext_ram_ret )
    {
	    case S_DONE:
            if ( HW_RAM_DRAM == cn_result.m_da_report.m_ext_ram_type) {
                UpdateMemoryTestRichEditor( "\tType = DRAM\r\n", clBlack );
            } else {
                UpdateMemoryTestRichEditor( "\tType = SRAM\r\n", clBlack );
            }

		    if( 0x20000 <= cn_result.m_da_report.m_ext_ram_size ) {
			    s.printf( "\tSize = 0x%08X (%dMB/%dMb)\r\n",
                          cn_result.m_da_report.m_ext_ram_size,
                          cn_result.m_da_report.m_ext_ram_size/1024/1024,
                          cn_result.m_da_report.m_ext_ram_size/1024*8/1024);
		    } else {
			    s.printf( "\tSize = 0x%08X (%dMB/dKb)\r\n",
                          cn_result.m_da_report.m_ext_ram_size,
                          cn_result.m_da_report.m_ext_ram_size/1024,
                          cn_result.m_da_report.m_ext_ram_size/1024*8);
		    }
            UpdateMemoryTestRichEditor( s, clBlack );
		    break;

	    case S_DA_RAM_FLOARTING:
            UpdateMemoryTestRichEditor( "\tERROR: External RAM data is floating!!\r\n", clRed );
		    break;

	    case S_DA_RAM_UNACCESSABLE:
            UpdateMemoryTestRichEditor( "\tERROR: External RAM data is un-accessable!!\r\n", clRed );
		    break;

	    case S_DA_RAM_ERROR:
	    default:
            UpdateMemoryTestRichEditor( "\tERROR: External RAM was not detected!!\r\n", clRed );
		    break;
	}

#if 0

    // NOR flash report
    UpdateMemoryTestRichEditor( "NOR Flash:\r", clBlack );
    if( S_DONE == cn_result.m_da_report.m_nor_ret )
    {
        s.printf("\tDevice ID = \"%s\" (%d)\r\n\tSize = 0x%08X (%dMB/%dMb)\r\n",
                 GetNorFlashNameByTypeId( cn_result.m_da_report.m_nor_flash_id),
                 cn_result.m_da_report.m_nor_flash_id,
		         cn_result.m_da_report.m_nor_flash_size,
                 cn_result.m_da_report.m_nor_flash_size/1024/1024,
                 cn_result.m_da_report.m_nor_flash_size/1024/1024*8);
        UpdateMemoryTestRichEditor( s, clBlack );
    } else {
        UpdateMemoryTestRichEditor( "\tERROR: NOR Flash was not detected!\r\n", clRed );
    }
#endif

    // NAND flash report
    UpdateMemoryTestRichEditor( "NAND Flash:\r", clBlack );
    if( S_DONE == cn_result.m_da_report.m_nand_ret )
    {
        s.printf("\tDevice ID = \"%s\" (%d)\r\n\tSize = 0x%08X (%dMB/%dMb)\r\n",
                 GetNandFlashNameByTypeId( cn_result.m_da_report.m_nand_flash_id),
                 cn_result.m_da_report.m_nand_flash_id,
                 cn_result.m_da_report.m_nand_flash_size,
                 cn_result.m_da_report.m_nand_flash_size/1024/1024,
                 cn_result.m_da_report.m_nand_flash_size/1024/1024*8);
        UpdateMemoryTestRichEditor( s, clBlack );
    } else {
        UpdateMemoryTestRichEditor( "\tERROR: NAND Flash was not detected!\r\n", clRed );
    }

	// EMMC report
    UpdateMemoryTestRichEditor( "EMMC :\r", clBlack );
    if( S_DONE == cn_result.m_da_report.m_emmc_ret )
    {	
		s.printf("\t EMMC_PART_BOOT1 \tSize = 0x%016X(%dMB)\r\n"
			"\t EMMC_PART_BOOT2 \tSize = 0x%016X(%dMB)\r\n"
			"\t EMMC_PART_RPMB \tSize = 0x%016X(%dMB)\r\n"
			"\t EMMC_PART_GP1 \tSize = 0x%016X(%dMB)\r\n"
			"\t EMMC_PART_GP2 \tSize = 0x%016X(%dMB)\r\n"
			"\t EMMC_PART_GP3 \tSize = 0x%016X(%dMB)\r\n"
			"\t EMMC_PART_GP4 \tSize = 0x%016X(%dMB)\r\n"
			"\t EMMC_PART_USER \tSize = 0x%016I64X(%I64uMB)\r\n",
            cn_result.m_da_report.m_emmc_boot1_size, cn_result.m_da_report.m_emmc_boot1_size/1024/1024,
            cn_result.m_da_report.m_emmc_boot2_size, cn_result.m_da_report.m_emmc_boot2_size/1024/1024,             
            cn_result.m_da_report.m_emmc_rpmb_size, cn_result.m_da_report.m_emmc_rpmb_size/1024/1024,
            cn_result.m_da_report.m_emmc_gp1_size, cn_result.m_da_report.m_emmc_gp1_size/1024/1024,    
            cn_result.m_da_report.m_emmc_gp2_size, cn_result.m_da_report.m_emmc_gp2_size/1024/1024,
            cn_result.m_da_report.m_emmc_gp3_size, cn_result.m_da_report.m_emmc_gp3_size/1024/1024,    
            cn_result.m_da_report.m_emmc_gp4_size, cn_result.m_da_report.m_emmc_gp4_size/1024/1024,
            cn_result.m_da_report.m_emmc_ua_size, cn_result.m_da_report.m_emmc_ua_size/1024/1024);
		
        UpdateMemoryTestRichEditor( s, clBlack );
    } else {
        UpdateMemoryTestRichEditor( "\tERROR: EMMC was not detected!\r\n", clRed );
    }

}

//---------------------------------------------------------------------------
void __fastcall tboot_1::UpdateMemoryTestRichEditor(AnsiString s, TColor color )
{
    MainForm->m_MT_ResultRichEditor->SelAttributes->Color = color;
    MainForm->m_MT_ResultRichEditor->Lines->Add( s );
}

//---------------------------------------------------------------------------
static int __stdcall cb_memorytest_init(void *user_arg)
{
    MainForm->m_MT_ResultRichEditor->Lines->Add( "cb line1" );
    MainForm->m_MT_ResultRichEditor->Lines->Insert( MainForm->m_MT_ResultRichEditor->Lines->Count, "cb line2" );

    return 0;
}

//---------------------------------------------------------------------------
static int __stdcall cb_memorytest_progress(unsigned int current_progress, void *usr_arg)
{
    unsigned int line_count;
    AnsiString s, tmp_s;

    FlashTool_MemoryTest_Arg *p_mt_arg = (FlashTool_MemoryTest_Arg *)usr_arg;

    line_count =  MainForm->m_MT_ResultRichEditor->Lines->Count;

    if( p_mt_arg->m_test_method == HW_MEM_DATA_BUS_TEST ){
        s.printf( "[D%d]" , current_progress );

        tmp_s = MainForm->m_MT_ResultRichEditor->Lines->Strings[line_count-1];
        MainForm->m_MT_ResultRichEditor->Lines->Strings[line_count-1] = tmp_s + s;
    }

    else if( p_mt_arg->m_test_method == HW_MEM_ADDR_BUS_TEST ){
        s.printf( "[A%d]" , current_progress );

        tmp_s = MainForm->m_MT_ResultRichEditor->Lines->Strings[line_count-1];
        MainForm->m_MT_ResultRichEditor->Lines->Strings[line_count-1] = tmp_s + s;
    }

    else if( p_mt_arg->m_test_method == HW_MEM_PATTERN_TEST){
        s.printf( "(0x%08X)," , current_progress );

        tmp_s = MainForm->m_MT_ResultRichEditor->Lines->Strings[line_count-1];
        MainForm->m_MT_ResultRichEditor->Lines->Strings[line_count-1] = tmp_s + s;
    }

    return 0;
}



/******************************************************************************/
/* Meta functions                                                             */
/*                                                                            */
/*                                                                            */
/******************************************************************************/
//---------------------------------------------------------------------------
//static int __stdcall cb_boot_meta_in_brom_stage(unsigned int brom_handle, HANDLE hCOM, void *usr_arg);
//---------------------------------------------------------------------------
int tboot_1::EnterMETAResetFactoryDefault( void )
{

    // Start timer
  	Synchronize( StartTimer );


    // update ResetFakeProgress
	progress_hint           = "Reset NVRAM to factory default setting ...";
	progress_forecolor      = clGreen;
	Synchronize( ResetFakeProgress );


    // Connect Taget in Meta Mode
    // fill META Connet with Target paprameter
    META_Connect_Req	    meta_con_req;
	META_Connect_Report	    meta_con_report;
    META_RESULT meta_ret;

    ArgMETAConnectWithTarget( meta_con_req, meta_con_report);
	if( META_SUCCESS != ( meta_ret=META_ConnectWithTarget(&meta_con_req, &g_stopflag, &meta_con_report) ) ) {
		// stop fake progress
		Synchronize( StopFakeProgress );
		return meta_ret;
	}

    // Call Reset to Factory Default
	if( META_SUCCESS != ( meta_ret=META_NVRAM_ResetToFactoryDefault(40000) ) ) {
		META_DisconnectWithTarget();
		// stop fake progress
		Synchronize( StopFakeProgress );
		return meta_ret;
	}

	META_DisconnectWithTarget();

	// finish fake progress
	Synchronize( FinishFakeProgress );

	return meta_ret;
}
//---------------------------------------------------------------------------

void __fastcall tboot_1::InitIMEIPara( void )
{
    
    m_bIMEI1Check = Form_IMEI_setting->m_bIMEI1Check;
    m_bIMEI2Check = Form_IMEI_setting->m_bIMEI2Check;
    m_bIMEI1Update = Form_IMEI_setting->m_bIMEI1Update;
    m_bIMEI2Update = Form_IMEI_setting->m_bIMEI2Update; 
    m_bCheckChecksum = Form_IMEI_setting->m_bCheckChecksum;
    m_pModemDatabase = Form_IMEI_setting->m_asNVRAM_DB_File.c_str();
    strcpy(Form_IMEI_setting->m_sIMEI.c_imei[0], Form_IMEI_setting->m_edtIMEI1->Text.c_str());
    strcpy(Form_IMEI_setting->m_sIMEI.c_imei[1], Form_IMEI_setting->m_edtIMEI2->Text.c_str());
    memcpy(&m_sIMEIdownload, &(Form_IMEI_setting->m_sIMEI), sizeof(m_sIMEIdownload));

    Logger::GetLogger().Log(Logger::Debug,
    		"[META IMEI] Is IMEI 1 checked: %s\n"
    		"[META IMEI] Is IMEI 2 checked: %s\n"
    		"[META IMEI] Is IMEI 1 Updated: %s\n"
    		"[META IMEI] Is IMEI 2 checked: %s\n"
    		"[META IMEI] Modem database location: %s\n"
    		"[META IMEI] IMEI1 number of IMEI1 to be updated: %s\n"
    		"[META IMEI] IMEI1 number of IMEI2 to be updated: %s\n"
    		"(%s,%d)",
    		(m_bIMEI1Check? "TRUE" : "FALSE"),
    		(m_bIMEI2Check? "TRUE" : "FALSE"),
    		(m_bIMEI1Update? "TRUE" : "FALSE"),
    		(m_bIMEI2Update? "TRUE" : "FALSE"),
    		m_pModemDatabase,
    		m_sIMEIdownload.c_imei[0],
    		m_sIMEIdownload.c_imei[1],
    		__FILE__, __LINE__);
}

//---------------------------------------------------------------------------
void __fastcall tboot_1::InitIMIE_BT_WIFI_Para ( void )
{
    m_pModemDatabase = Form_FourInOne->m_asModem_Database.c_str();
    m_pApDatabase = Form_FourInOne->m_asAP_Database.c_str();
    m_pBTAddr = Form_FourInOne->m_asBT_Address.c_str();
    m_pWIFIAddr = Form_FourInOne->m_asWiFi_Address.c_str();
    //m_sIMEIdownload = Form_FourInOne->m_sIMEI;
    strcpy(Form_FourInOne->m_sIMEI.c_imei[0], Form_FourInOne->m_edtIMEI1_Number->Text.c_str());
    strcpy(Form_FourInOne->m_sIMEI.c_imei[1], Form_FourInOne->m_edtIMEI2_Number->Text.c_str());
    memcpy(&m_sIMEIdownload, &(Form_FourInOne->m_sIMEI), sizeof(m_sIMEIdownload));
    m_bWriteIMEI1 = Form_FourInOne->m_bWriteIMEI1;   
    m_bWriteIMEI2 = Form_FourInOne->m_bWriteIMEI2;
    m_bWriteBTAddr = Form_FourInOne->m_bWriteBTAddr;
    m_bWriteWIFIAddr = Form_FourInOne->m_bWriteWIFIAddr;    

    Logger::GetLogger().Log(Logger::Debug,
    		"[META IMEI/WIFI/BT] Is IMEI 1 checked: %s\n"
    		"[META IMEI/WIFI/BT] Is IMEI 2 checked: %s\n"
    		"[META IMEI/WIFI/BT] Is Write BT Address checked: %s\n"
    		"[META IMEI/WIFI/BT] Is Write WIFI Address checked: %s\n"
    		"[META IMEI/WIFI/BT] Modem database location: %s\n"
    		"[META IMEI/WIFI/BT] AP database location: %s\n"
    		"[META IMEI/WIFI/BT] BT address: %s\n"
    		"[META IMEI/WIFI/BT] WiFi address : %s\n"
    		"[META IMEI/WIFI/BT] IMEI1 number of IMEI1 to be updated: %s\n"
    		"[META IMEI/WIFI/BT] IMEI1 number of IMEI2 to be updated: %s\n"
    		"(%s,%d)",
    		(m_bWriteIMEI1? "TRUE" : "FALSE"),
    		(m_bWriteIMEI2? "TRUE" : "FALSE"),
    		(m_bWriteBTAddr? "TRUE" : "FALSE"),
    		(m_bWriteWIFIAddr? "TRUE" : "FALSE"),
    		m_pModemDatabase,
    		m_pApDatabase,
    		m_pBTAddr,
    		m_pWIFIAddr,
    		m_sIMEIdownload.c_imei[0],
    		m_sIMEIdownload.c_imei[1],
    		__FILE__, __LINE__);
}

//---------------------------------------------------------------------------
void __fastcall tboot_1::Sync2ndImeiSupport( void )
{
    Form_IMEI_setting->m_b2ndImeiSupport = m_b2ndImeiSupport;
}

//---------------------------------------------------------------------------
void __fastcall tboot_1::SyncFourInOne2ndImeiSupport ( void )
{
    Form_FourInOne->m_b2ndImeiSupport = m_b2ndImeiSupport;
}

//---------------------------------------------------------------------------
void __fastcall tboot_1::SyncStartFakeProgress()
{
   	Synchronize( StartFakeProgress );
}

//---------------------------------------------------------------------------
void __fastcall tboot_1::StartFakeProgress()
{
	MainForm->CGauge1->Progress = m_meta__progress_value;
}

//---------------------------------------------------------------------------
void __fastcall tboot_1::StopFakeProgress()
{
	MainForm->CGauge1->Progress = 0;
    // clear hw status
    MainForm->sb_Main->Panels->Items[0]->Text = "";

}

//---------------------------------------------------------------------------
void __fastcall tboot_1::ResetFakeProgress()
{
	MainForm->CGauge1->Hint       = progress_hint;
	MainForm->CGauge1->ForeColor  = progress_forecolor;
	MainForm->CGauge1->Progress   = 0;
}

//---------------------------------------------------------------------------
void __fastcall tboot_1::FinishFakeProgress()
{
    //MainForm clear up
    MainForm->CGauge1->Progress             = 100;
    //MainForm->m_FakeProgressTimer->Enabled  = false;
    // clear hw status
    MainForm->sb_Main->Panels->Items[0]->Text = "";
}

//---------------------------------------------------------------------------
void __fastcall tboot_1::ResetMETABackup( void )
{
    // update ResetFakeProgress
    progress_hint           = "Enter Meta to Backup NVRAM ...";
    progress_forecolor      = (TColor) (0x00DBB0CC);
    // clear hw status
    MainForm->sb_Main->Panels->Items[0]->Text = "Backup NVRAM";
    MainForm->sb_Main->Panels->Items[5]->Text = "";
    MainForm->m_HWStatus->Panels->Items[0]->Text = "";
    MainForm->m_HWStatus->Panels->Items[1]->Text = "";
    MainForm->m_HWStatus->Panels->Items[2]->Text = "";
    MainForm->m_HWStatus->Panels->Items[3]->Text = "";
    MainForm->m_HWStatus->Hint = "";
    return;
}

//---------------------------------------------------------------------------
void __fastcall tboot_1::ResetMETARestore( void )
{

    // update ResetFakeProgress
    progress_hint           = "Enter Meta to Restore NVRAM ...";
    progress_forecolor      = (TColor)(0x00FFCCCC);
    // clear hw status
    MainForm->sb_Main->Panels->Items[0]->Text = "Restore NVRAM";
    MainForm->sb_Main->Panels->Items[5]->Text = "";
    MainForm->m_HWStatus->Panels->Items[0]->Text = "";
    MainForm->m_HWStatus->Panels->Items[1]->Text = "";
    MainForm->m_HWStatus->Panels->Items[2]->Text = "";
    MainForm->m_HWStatus->Panels->Items[3]->Text = "";
    MainForm->m_HWStatus->Hint = "";
    return;
}

//---------------------------------------------------------------------------
void __fastcall tboot_1::ResetDL_IMEI_Info( void )
{
    // update ResetFakeProgress
    progress_hint           = "Enter Meta to Check or Update Data ...";
    //progress_forecolor      = (TColor)(0x00FFCCCC);
    // clOlive
    progress_forecolor =  (TColor)(0xFFD700);
    // clear hw status
    MainForm->sb_Main->Panels->Items[0]->Text = "IMEI check and update";
    MainForm->sb_Main->Panels->Items[5]->Text = "";
    MainForm->m_HWStatus->Panels->Items[0]->Text = "";
    MainForm->m_HWStatus->Panels->Items[1]->Text = "";
    MainForm->m_HWStatus->Panels->Items[2]->Text = "";
    MainForm->m_HWStatus->Panels->Items[3]->Text = "";
    MainForm->m_HWStatus->Hint = "";
}

//---------------------------------------------------------------------------
void __fastcall tboot_1::ResetDL_FourInOne_Info( void )
{
    // update ResetFakeProgress
    progress_hint           = "Enter Meta to Write IMEI/BT/WiFi ...";
    //progress_forecolor      = (TColor)(0x00FFCCCC);
    // Olive
    progress_forecolor =  (TColor)(0xFFD700);
    // clear hw status
    MainForm->sb_Main->Panels->Items[0]->Text = "Write IMEI/BT/WiFi";
    MainForm->sb_Main->Panels->Items[5]->Text = "";
    MainForm->m_HWStatus->Panels->Items[0]->Text = "";
    MainForm->m_HWStatus->Panels->Items[1]->Text = "";
    MainForm->m_HWStatus->Panels->Items[2]->Text = "";
    MainForm->m_HWStatus->Panels->Items[3]->Text = "";
    MainForm->m_HWStatus->Hint = "";
}

//---------------------------------------------------------------------------
void __fastcall tboot_1::ErrorMessage (void)
{
    ShowMessage(m_as_err_msg.c_str());
    m_as_err_msg = "";
}


//---------------------------------------------------------------------------
/*
static int __stdcall cb_boot_meta_in_brom_stage( unsigned int        brom_handle,
                                                 HANDLE              hCOM,
                                                 void                *usr_arg)
{
	tboot_1 *t=(tboot_1 *)usr_arg;
	// start fake progress
	t->SyncStartFakeProgress();
    return 0;
}
*/

/******************************************************************************/
/* moudles used to fill the FlashTool API's input paresmeters                 */
/*                                                                            */
/*                                                                            */
/******************************************************************************/
//---------------------------------------------------------------------------
int tboot_1::ArgFlashToolConnect( FlashTool_Connect_Arg           &ftConnect,
                                  FlashTool_Connect_Result        &ftConnectResult)
{

    memset( &ftConnect, 0, sizeof(ftConnect));
    memset( &ftConnectResult, 0, sizeof(ftConnectResult));
    
    // With All-In-One FLASHTOOL_RESULT to get DA report
    m_bGetDAReportWithConnArg = true;
    
    // com port timeout setting
	ftConnect.m_com_ms_read_timeout                 = g_COM_Read_Timeout;
	ftConnect.m_com_ms_write_timeout                = g_COM_Write_Timeout;

	// fill BOOT_FLASHTOOL_ARG
	ArgBootFlashTool(ftConnect.m_boot_arg, &(ftConnectResult.m_da_report.m_bbchip_type));

    // security pre-process notify callback
	ftConnect.m_cb_security_pre_process_notify      = cb_security_pre_process_notify;
	ftConnect.m_cb_security_pre_process_notify_arg  = this;

    // chip-select of NOR flash memory
	ftConnect.m_nor_chip_select[0]                  = CS_0;
	ftConnect.m_nor_chip_select[1]                  = CS_WITH_DECODER;
	ftConnect.m_nand_chip_select                    = g_bNFI_SelectCS1?CS_1:CS_0;

    //  NFI access contol register
	ftConnect.m_p_nand_acccon = g_EMI_NFI_Setting.m_bAuto?NULL:&(g_EMI_NFI_Setting.m_nand_acccon);

	// BMT block count
	ftConnect.m_boot_arg.m_bmt_block_count = g_platform_info.getBMTBlocks();

	ftConnect.m_storage_type = g_platform_info.getFlashToolStorageConfig().GetStorageType();
    ftConnect.m_p_dl_handle = g_pCurNode->m_dl_handle;

	return 0;
}
//---------------------------------------------------------------------------
int tboot_1::ArgBootFlashTool( BOOT_FLASHTOOL_ARG          &bft,
                               void                        *m_cb_in_brom_stage_arg)
{


    memset( &bft, 0, sizeof(bft));

	bft.m_bbchip_type                = (g_platform_info.getLoadPlatformName() == "MT6516") ? MT6516_AP : AUTO_DETECT_BBCHIP; //g_BBCHIP_TYPE;
	LOG("tboot_1::ArgBootFlashTool(): m_bbchip_type is %d.", bft.m_bbchip_type);
    bft.m_ext_clock                  = g_EXT_CLOCK;

    bft.m_ms_boot_timeout            = BOOT_INFINITE;
    bft.m_max_start_cmd_retry_count  = g_MaxBromStartCmdRetryCount;

    // Initialization for Edge Moudle
    // This callback function will be invoke after COM port is opened
	// You can do some initialization by using this callback function.
	bft.m_cb_com_init_stage          = cb_com_init_stage;
	bft.m_cb_com_init_stage_arg      = this;

    // This callback function will be invoke after BootROM start cmd is passed.
	// You can issue other BootROM command by brom_handle and hCOM which
    // provides callback arguments,or do whatever you want otherwise.
    bft.m_cb_in_brom_stage           = cb_in_brom_stage;
	bft.m_cb_in_brom_stage_arg       = m_cb_in_brom_stage_arg;

    // speed-up BootROM stage baudrate
    bft.m_speedup_brom_baudrate      = g_SpeedUpBootROMBaudrate?_TRUE:_FALSE;

	// Application's window handle to send WM_BROM_READY_TO_POWER_ON_TGT message
	bft.m_ready_power_on_wnd_handle	 = NULL;
	bft.m_ready_power_on_wparam		 = NULL;
	bft.m_ready_power_on_lparam		 = NULL;

	// serial link authentication arg
    bft.m_auth_handle                = g_AUTH_HANDLE;
	bft.m_scert_handle               = g_SCERT_HANDLE;
	bft.m_cb_sla_challenge           = SLA_Challenge;
	bft.m_cb_sla_challenge_arg       = this;
	bft.m_cb_sla_challenge_end       = SLA_Challenge_END;
	bft.m_cb_sla_challenge_end_arg   = this;


    // EMI Control for bank0 and bank1
    bft.m_p_bank0_mem_cfg            = g_EMI_Config[0].m_bAuto?NULL:&(g_EMI_Config[0].m_Config);
    bft.m_p_bank1_mem_cfg            = g_EMI_Config[1].m_bAuto?NULL:&(g_EMI_Config[1].m_Config);

    if ( g_bSkipBootRom ) {
    	bft.m_da_handle              = NULL;
    }
    else {
    	bft.m_da_handle              = g_DA_HANDLE;
    }

    // da download progress callack
    bft.m_cb_download_da_init        = cb_download_da_init;
    bft.m_cb_download_da_init_arg    = this;
    bft.m_cb_download_da             = cb_download_da;
    bft.m_cb_download_da_arg         = this;

    // download by USB
    //bft.m_usb_enable                 = (_BOOL) g_bUsbDLRB;

	return 0;
}

//---------------------------------------------------------------------------
int tboot_1::ArgFlashToolAdvancedFormat(FlashTool_Format_Arg &fmt_arg, FlashTool_Format_Result &fmt_res, 
                               const FlashTool_Connect_Result& cn_result, bool will_report, bool isDynamicLayout)
{
    int ret = S_DONE;
    PART_INFO part_info;
    memset( &part_info, 0, sizeof(part_info));
    memset( &fmt_arg,    0, sizeof(fmt_arg));
    memset( &fmt_res, 0, sizeof(fmt_res));
    unsigned long long format_start_addr = 0;
    unsigned long long format_length = 0;
    HW_StorageType_E hw_storage_type = g_platform_info.getFlashToolStorageConfig().GetStorageType() ;
    NUTL_AddrTypeFlag_E nand_format_addr_type = NUTL_ADDR_LOGICAL;
    if (AUTO_FORMAT == g_FormatOption) { 
        AutoFormatArgFactory auto_format_factory;
        auto_format_factory.set_dl_handle(g_pCurNode->m_dl_handle);
        auto_format_factory.set_flashtool_handle(g_ft_handle);
        auto_format_factory.set_da_report(&(cn_result.m_da_report));
        auto_format_factory.set_auto_fmt_flag(g_NandAutoFormatFlag);
        auto_format_factory.set_oper_flag((isDynamicLayout && !g_bPhysicallyFormatReadback)
		    ? NUTL_ADDR_LOGICAL : NUTL_ADDR_PHYSICAL);
        //FIXME when adds new storage type
	  StorageLayoutType_E type = GetStorageLayoutType(isDynamicLayout, hw_storage_type);
	  LOGD("isDynamisLayout(%d)", isDynamicLayout);
        SharedPtr<AutoFormatArg> auto_format_ptr = auto_format_factory.CreateAutoFormatArg(type);
	format_start_addr = auto_format_ptr.get()->GetAutoFormatStartAddress();
	format_length = auto_format_ptr.get()->GetAutoFormatLength();
	nand_format_addr_type = auto_format_ptr.get()->GetNandAddrType(); 
    } else { //manually format
        format_start_addr = g_ulNandFormatStartAddr;
	    format_length = g_ulNandFormatLength;
        nand_format_addr_type = (isDynamicLayout && !g_bPhysicallyFormatReadback)
		    ? NUTL_ADDR_LOGICAL : NUTL_ADDR_PHYSICAL; 
    }
    fmt_arg.m_format_cfg.m_format_begin_addr = format_start_addr;
    fmt_arg.m_format_cfg.m_format_length = format_length;
    fmt_arg.m_format_cfg.m_AddrType = nand_format_addr_type;

    fmt_arg.m_storage_type = hw_storage_type;
	fmt_arg.m_format_cfg.m_validation        = g_FormatValidation?_TRUE:_FALSE;
	fmt_arg.m_erase_flag                   = g_EraseFlag;
     
    fmt_arg.m_cb_format_report_init        = cb_format_report_init;
	fmt_arg.m_cb_format_report_init_arg    = this;
	fmt_arg.m_cb_format_report             = cb_format_report;
	fmt_arg.m_cb_format_report_arg         = this;
    //Report nand format info in ONLY format operation 
    fmt_arg.m_cb_format_statistics         = will_report ? cb_format_statistics : NULL;
	fmt_arg.m_cb_format_statistics_arg     = this;

    return 0;
}
#if 0
//---------------------------------------------------------------------------
int tboot_1::ArgAutoFormatRegion(FlashTool_Format_Arg &fmt_arg,
                                 const unsigned int nvram_start_addr, 
                                 const unsigned int nvram_length,
                                 const unsigned int nand_flash_size)
{
	LOG("ArgAutoFormatRegion(): nvram_start_addr=0x%X, nvram_length=0x%X, nand_flash_size=0x%X",
			nvram_start_addr, nvram_length, nand_flash_size);

    const int start_addr_behind_nvram = nvram_start_addr + nvram_length;
    //assert( (nand_flash_size - start_addr_behind_nvram) < 0 );
    
	//if ((BACKUP_FORMAT_DOWNLOAD_RESTORE == g_backup_restore_state) /*||
	//	(FORMAT_DOWNLOAD_RESTORE_NVRAM == g_backup_restore_state)*/) {
	//	LOGD("tboot_1::ArgAutoFormatRegion(): Firmware upgrade format all.");
 //       fmt_arg.m_format_cfg.m_format_begin_addr = 0;
 //       fmt_arg.m_format_cfg.m_format_length = nand_flash_size;
	//} else 
	//if ( FORMAT_DOWNLOAD == g_FormatOption ) {
	//	LOGD("tboot_1::ArgAutoFormatRegion(): Format all except bootloader and Nvram BinRegion.");
 //       fmt_arg.m_format_cfg.m_format_begin_addr = start_addr_behind_nvram; //Format All Except Pre-Loader and Nvram BinRegion
 //       fmt_arg.m_format_cfg.m_format_length     = (nand_flash_size - start_addr_behind_nvram);
 //   } else 
	if ( AUTO_FORMAT == g_FormatOption ) {		
        switch ( g_NandAutoFormatFlag ) {
            case FORMAT_ALL:
				LOGD("tboot_1::ArgAutoFormatRegion(): Auto format all.");
                fmt_arg.m_format_cfg.m_format_begin_addr = 0;
                fmt_arg.m_format_cfg.m_format_length = nand_flash_size;
                break;
            case FORMAT_NVRAM_BIN:
				LOGD("tboot_1::ArgAutoFormatRegion(): Auto format nvram binregion only.");
                fmt_arg.m_format_cfg.m_format_begin_addr = nvram_start_addr;
                fmt_arg.m_format_cfg.m_format_length = nvram_length;
                break;
            case FORMAT_ALL_EXP_BL_NVRAM_BIN:
                //FORMAT_ALL_EXP_BL_NVRAM_BIN is default setting
				LOGD("tboot_1::ArgAutoFormatRegion(): Auto format all except bootloader and nvram.");
            default:
                fmt_arg.m_format_cfg.m_format_begin_addr = start_addr_behind_nvram;
                fmt_arg.m_format_cfg.m_format_length = (nand_flash_size - start_addr_behind_nvram);
                break;                
        }
    } else {
        //Manually Format
        fmt_arg.m_format_cfg.m_format_begin_addr = g_ulNandFormatStartAddr;
        fmt_arg.m_format_cfg.m_format_length = g_ulNandFormatLength;        
    }

    return 0;
}
#endif
//---------------------------------------------------------------------------
int tboot_1::ArgFlashToolAdvancedDownload(FlashTool_Download_Arg &fdl_arg, FlashTool_Download_Result &fdl_res)
{
    memset( &fdl_arg,    0, sizeof(fdl_arg));
    memset( &fdl_res, 0, sizeof(fdl_res));

    if( MainForm->mi_MultiLoad->Checked ){
	    fdl_arg.m_dl_handle_list     = g_DL_HANDLE_LIST;
		fdl_arg.m_dl_handle          = NULL;
    }
    else{
	    fdl_arg.m_dl_handle          = g_DL_HANDLE_NODE.m_dl_handle;
		fdl_arg.m_dl_handle_list     = NULL;
    }


    //DA report callback
    fdl_arg.m_cb_da_report        = cb_da_report;
    fdl_arg.m_cb_da_report_arg    = this;

    // download progress callback
    fdl_arg.m_download_accuracy                   = ACCURACY_AUTO;
    fdl_arg.m_cb_download_flash_init              = cb_download_flash_init;
    fdl_arg.m_cb_download_flash_init_arg          = this;
    fdl_arg.m_cb_download_flash                   = cb_download_flash;
    fdl_arg.m_cb_download_flash_arg               = this;
    fdl_arg.m_cb_security_post_process_notify     = cb_security_post_process_notify;
    fdl_arg.m_cb_security_post_process_notify_arg = this;

    // Boot-Loader download progress callback
    fdl_arg.m_cb_download_bloader_init       = cb_download_bloader_init;
    fdl_arg.m_cb_download_bloader_init_arg   = this;
    fdl_arg.m_cb_download_bloader            = cb_download_bloader;
    fdl_arg.m_cb_download_bloader_arg        = this;

    fdl_arg.m_enable_tgt_res_layout_check   = _FALSE;
    fdl_arg.m_enable_bbchip_ver_check       = _FALSE;
    fdl_arg.m_downloadstyle_sequential      = _FALSE;

    //2011.08.16 Add for DA Download All checksum progress bar
    fdl_arg.m_cb_checksum_init = cb_da_dl_checksum__init;
    fdl_arg.m_cb_checksum_init_arg = this;
    fdl_arg.m_cb_checksum = cb_da_dl_checksum;
    fdl_arg.m_cb_checksum_arg = this;
    return 0;
}

//---------------------------------------------------------------------------
int tboot_1::ArgFlashToolWatchDog(FlashTool_EnableWDT_Arg *p_wdt_arg)
{
	assert(NULL != p_wdt_arg);
	memset(p_wdt_arg, 0, sizeof(FlashTool_EnableWDT_Arg));
	//timeout to reset bootRom
	p_wdt_arg->m_timeout_ms = 5000;
	p_wdt_arg->m_async = _FALSE;
	p_wdt_arg->m_reboot = _TRUE;
	return 0;
}

//---------------------------------------------------------------------------
bool tboot_1::ScanUSBVOMWithoutTimeout(const std::string& pid, const std::string& vid)
{
    string s_symbolic_str;
    string s_port_str;

    //Scan exist com port
    m_strSymbolicName.erase(m_strSymbolicName.begin(), m_strSymbolicName.end());
    m_strSymbolicName.begin();

    do
    {
	 //LOG("tboot_1::ScanUSBVOMWithoutTimeout(): USB PID(%s), USB VID(%s)", pid.c_str(), vid.c_str());
        Sleep(200);
        if(BOOT_STOP == g_stopflag)
        {
            LOGD("YuSu: User press stop button !");
            return false;
        }

        else if( GetNewCreatedUSBVComPort(s_symbolic_str,
                                          s_port_str,
                                          m_strSymbolicName,
                                          pid,
                                          vid)
                                          )
        {
            //find usb_com port via MS DDK
            m_strPort =  s_port_str;
            m_strSymbolic = s_symbolic_str;
            Synchronize(UpdateUSBVCOMInfo);
            break;
        }
    } while(1);
    return true;
    
}

//---------------------------------------------------------------------------
bool tboot_1::ScanUSBVOMWithTimeout(unsigned int timeout,
                                    const std::string& pid, 
                                    const std::string& vid)
{
    string   s_com_str;
    string   s_port_str;
    int s_com_port;
    time_t   start, finish;

	//Initilize USB Ports table
	FlashToolUSBTable usb_table = GetFlashToolUSBTable();
	FlashToolUSB usb_preloader;
	FlashToolUSB usb_da_highspeed;
	if ( !usb_table.QueryUSBItemByName(FlashToolUSB::PRELOADER_VCOM, usb_preloader) ) {
		LOG("ERROR: tboot_1::ScanUSBVOMWithTimeout(): QueryUSBItemByName(): (%s) failed!",
			FlashToolUSB::PRELOADER_VCOM.c_str());
	} 
	if ( !usb_table.QueryUSBItemByName(FlashToolUSB::DA_HIGHSPEED_VCOM, usb_da_highspeed) ) {
		LOG("ERROR: tboot_1::ScanUSBVOMWithTimeout(): QueryUSBItemByName(): (%s) failed!",
			FlashToolUSB::DA_HIGHSPEED_VCOM.c_str());
	} 
    //Get start time
    time(&start);
    
	if ( (usb_preloader.GetUSBPID() == pid) || 
		(usb_da_highspeed.GetUSBPID() == pid)) {
        Synchronize(StartUSBHintTimer);
    }
    
    do
    {
        if(BOOT_STOP == g_stopflag)
        {
            LOGD("tboot_1::ScanUSBVOMWithTimeout(): User press stop button !");
            Synchronize(StopUSBHintTimer); 
            return false;
        }
        else if( GetNewCreatedUSBVComPort(s_com_str,
                                          s_port_str,
                                          m_strSymbolicName,
                                          pid.c_str(),
                                          vid.c_str())
                                          )
        {
            //find usb_com port via MS DDK
            m_strPort =  s_port_str;
            m_strSymbolic = s_com_str;
            LOG("tboot_1::ScanUSBVOMWithTimeout(): Find usb port PID is %s, VID is %s, symblic name is %s, port num is %s.",
                pid.c_str(), vid.c_str(),
                s_com_str.c_str(), s_port_str.c_str());
            Synchronize(UpdateUSBVCOMInfo);
            Synchronize(StopUSBHintTimer); 
            break;
        }
        //Get current time
        time( &finish );
        
        if( difftime( finish, start) > (USB_SCAN_TIMEOUT/2 - 1) ) {
           Synchronize(StopUSBHintTimer);           
        }
        
        //wait if there still not found a new usb com port
        if(difftime( finish, start ) > timeout )
        {
            LOG("tboot_1::ScanUSBVOMWithTimeout(): Find usb port PID is %s, VID is %s, time out %u s passed, search usb port error!",
                pid.c_str(), vid.c_str(), timeout);            
            return false;
        }
    }while(1);
    
    return true;
}

//---------------------------------------------------------------------------
EBOOT_RESULT tboot_1::ScanMETAUSBPorts(unsigned char&  com_num)
{
    const unsigned int PRELOADER_USB_TIMEOUT = 15000;//15s
    const unsigned int GADGET_USB_TIMEOUT = 15000;//15s
    EBOOT_RESULT EBOOT_Result;

	//Initilize USB Ports table
	FlashToolUSBTable usb_table = GetFlashToolUSBTable();
	FlashToolUSB usb_preloader;
	if ( !usb_table.QueryUSBItemByName(FlashToolUSB::PRELOADER_VCOM, usb_preloader) ) {
		LOG("ERROR: tboot_1::ScanMETAUSBPorts(): QueryUSBItemByName(): (%s) failed!",
			FlashToolUSB::PRELOADER_VCOM.c_str());
	} else {
		LOG("tboot_1::ScanMETAUSBPorts(): QueryUSBItemByName(): Name(%s), PID(%s), VID(%s)",
			usb_preloader.GetUSBName().c_str(),
			usb_preloader.GetUSBPID().c_str(),
			usb_preloader.GetUSBVID().c_str());
	}
	ErrorLookup::SetErrorCodeMode(FLASHTOOL);
    if( g_bUsbMode ) {
        if( !ScanUSBVOMWithTimeout(PRELOADER_USB_TIMEOUT, 
			usb_preloader.GetUSBPID(), usb_preloader.GetUSBVID()) ) {
            Synchronize( StopFakeProgress );
            return static_cast<EBOOT_RESULT>(FT_FIND_USB_ERROR);
        } else {
            com_num = GetUSBVCOMNumByPortName(m_strPort);
            Logger::GetLogger().Log(Logger::Debug, 
                "The USB port number which is enumerated by Pre-Loader is %u.(%s, %d)", 
                com_num, __FILE__, __LINE__);
        }
    }
	ErrorLookup::SetErrorCodeMode(EBOOT);
    
    EBOOT_Result = SP_BootAsMetaWrapper(com_num, BAUD115200, &g_stopflag );
    Logger::GetLogger().Log(Logger::Debug, "SP_BootAsMetaWrapper with com port(%d), ret = %d",com_num,EBOOT_Result);
    if( USER_PRESS_STOP_BUTTON == EBOOT_Result)
    {
        Synchronize( StopFakeProgress );
        return EBOOT_Result = USER_PRESS_STOP_BUTTON;
    }
    else if( EBOOT_SUCCESS != EBOOT_Result )
    {
	 //SP do not boot into META
         m_as_err_msg = "[META INFO]: SmartPhone boot into META fail!";
         //Synchronize( ErrorMessage );
         Synchronize( StopFakeProgress );
    } else if ( EBOOT_SUCCESS == EBOOT_Result){
        LOGD("[META INFO]: SmartPhone boot into META Mode succeed.");
		FlashToolUSB usb_gadget;
		if ( !usb_table.QueryUSBItemByName(FlashToolUSB::GADGET_VCOM, usb_gadget) ) {
		LOG("ERROR: tboot_1::ScanMETAUSBPorts(): QueryUSBItemByName(): (%s) failed!",
			FlashToolUSB::GADGET_VCOM.c_str());
		}
        if( g_bUsbMode ) {
			if( !ScanUSBVOMWithTimeout(GADGET_USB_TIMEOUT, usb_gadget.GetUSBPID(), usb_gadget.GetUSBVID()) ) {
                Synchronize( StopFakeProgress );
                LOGD("[META INFO]: Scan Gadget USB port failed in META Mode!");
                return static_cast<EBOOT_RESULT>(FT_FIND_GADGET_USB_ERROR);
            } else {
                com_num = GetUSBVCOMNumByPortName(m_strPort);
                Logger::GetLogger().Log(Logger::Debug, 
                    "The Gadget USB port number which is enumerated by Linux kernel is %u.(%s, %d)", 
                    com_num, __FILE__, __LINE__);
            }
        }
    }

    return EBOOT_Result;
}

//---------------------------------------------------------------------------
int tboot_1::ArgComPortSetting( COM_PORT_SETTING  &comPortSetting )
{
    memset( &comPortSetting, 0 , sizeof (comPortSetting));
    if(g_bUsbMode || g_bUsbDLDA)
    {
        comPortSetting.com.number = GetUSBVCOMNumByPortName(m_strPort);
    }
    else
    {
        comPortSetting.com.number = COM_PORT;
    }

    comPortSetting.baudrate         = BAUD_RATE;
    comPortSetting.ms_read_timeout  = g_COM_Read_Timeout;
	comPortSetting.ms_write_timeout = g_COM_Write_Timeout;

	return 0;
}
//unused functions!
#if 0
int tboot_1::ArgComPortSetting_ByhCOM( COM_PORT_SETTING  &comPortSetting )
{
    memset( &comPortSetting, 0 , sizeof (comPortSetting));

    comPortSetting.com.handle       = NULL;
    comPortSetting.baudrate         = BAUD_RATE;
    comPortSetting.ms_read_timeout  = g_COM_Read_Timeout;
	comPortSetting.ms_write_timeout = g_COM_Write_Timeout;

	return 0;
}

//---------------------------------------------------------------------------
int tboot_1::ArgFlashDownload( void )
{
    // fill COM_PORT_SETTING
    ArgComPortSetting( com );

    // fill FLASHTOOL_ARG
    ArgFlashTool( arg, result );

    // fill FLASHTOOL_DOWNLOAD_ARG
    ArgFlashToolDownload( dl_arg, dl_result );

    return 0;

}
#endif
//---------------------------------------------------------------------------
int tboot_1::ArgFlashReadback( void )
{
    // fill COM_PORT_SETTING
    ArgComPortSetting(com);

    // fill FLASHTOOL_ARG
    ArgFlashTool(arg, result);

    // fill FLASHTOOL_READBACK_ARG
    ArgFlashToolReadback( rb_arg, rb_result );

    return 0;
}
#if 0
//---------------------------------------------------------------------------
int tboot_1::ArgFlashFormat( void )
{
    // fill COM_PORT_SETTING
    ArgComPortSetting( com );

    // fill FLASHTOOL_ARG
    ArgFlashTool( arg, result );

    // fill FLASHTOOL_FORMAT_ARG
    ArgFlashToolFormat( fmt_arg, fmt_result );

    return 0;
}
#endif
#if 0
//---------------------------------------------------------------------------
int tboot_1::ArgFlashToolDownload( FLASHTOOL_DOWNLOAD_ARG       &dl_arg,
                                   FLASHTOOL_DOWNLOAD_RESULT    &dl_result)
{

    memset( &dl_arg,    0, sizeof(dl_arg));
    memset( &dl_result, 0, sizeof(dl_result));

    if( MainForm->mi_MultiLoad->Checked ){
	    dl_arg.m_dl_handle_list     = g_DL_HANDLE_LIST;
		dl_arg.m_dl_handle          = NULL;
    }
    else{
	    dl_arg.m_dl_handle          = g_DL_HANDLE_NODE.m_dl_handle;
		dl_arg.m_dl_handle_list     = NULL;
    }
    /*
    switch( g_OperationMethod )
    {
        case NFB_OPERATION:
    	    dl_arg.m_storage_type = HW_STORAGE_NAND;
    		break;
        case NOR_OPERATION:
		default:
	    dl_arg.m_storage_type = HW_STORAGE_NOR;
    }
    */
    // download progress callback
    dl_arg.m_download_accuracy                   = ACCURACY_AUTO;
    dl_arg.m_cb_download_flash_init              = cb_download_flash_init;
    dl_arg.m_cb_download_flash_init_arg          = this;
    dl_arg.m_cb_download_flash                   = cb_download_flash;
    dl_arg.m_cb_download_flash_arg               = this;
    dl_arg.m_cb_security_post_process_notify     = cb_security_post_process_notify;
    dl_arg.m_cb_security_post_process_notify_arg = this;

    // format option
	if( NOR_OPERATION == g_OperationMethod ) {
	    dl_arg.m_format_cfg.m_format_begin_addr = g_ulFormatStartAddr;
	    dl_arg.m_format_cfg.m_format_length     = g_ulFormatLength;
    }
    else {
	    dl_arg.m_format_cfg.m_format_begin_addr = g_ulNandFormatStartAddr;
	    dl_arg.m_format_cfg.m_format_length     = g_ulNandFormatLength;
    }
	dl_arg.m_format_cfg.m_validation = g_FormatValidation?_TRUE:_FALSE;

	switch ( g_FormatAfterDownloadOption )
    {
        case AUTO_FORMAT:
            // enable auto format
	        dl_arg.m_format_enable                = _TRUE;
		    dl_arg.m_format_cfg.m_auto_format_fat = _TRUE;
			break;

        case MANUAL_FORMAT:
            // enable manual format
	        dl_arg.m_format_enable                = _TRUE;
		    dl_arg.m_format_cfg.m_auto_format_fat = _FALSE;
            break;

        case RESET_TO_FACTORY:
        case DISABLE_FORMAT:
        default:
            // disable format
            dl_arg.m_format_enable                = _FALSE;
            dl_arg.m_format_cfg.m_auto_format_fat = _FALSE;
            break;
    }
    dl_arg.m_cb_format_report_init        = cb_format_report_init;
    dl_arg.m_cb_format_report_init_arg    = this;
    dl_arg.m_cb_format_report             = cb_format_report;
    dl_arg.m_cb_format_report_arg         = this;
    dl_arg.m_enable_tgt_res_layout_check  = g_bCheckTgtResourceLayout?_TRUE:_FALSE;
    dl_arg.m_enable_bbchip_ver_check      = _FALSE; //g_bCheckECOVer?_TRUE:_FALSE;
    dl_arg.m_downloadstyle_sequential     = g_bDownloadStyleSequential?_TRUE:_FALSE;
    dl_arg.m_cb_format_statistics         = cb_format_statistics;
    dl_arg.m_cb_format_statistics_arg     = this;

    // parameter
    if( !MainForm->mi_MultiLoad->Checked ) {
        dl_arg.m_otp_enable         = g_DL_HANDLE_NODE.m_param.m_otp_enable;
	 	dl_arg.m_otp_op             = g_DL_HANDLE_NODE.m_param.m_otp_op;
	 	dl_arg.m_otp.m_addr         = g_DL_HANDLE_NODE.m_param.m_otp.m_addr;
	 	dl_arg.m_otp.m_data         = g_DL_HANDLE_NODE.m_param.m_otp.m_data;
	 	dl_arg.m_otp.m_len          = g_DL_HANDLE_NODE.m_param.m_otp.m_len;
	 	dl_arg.m_ft_cfg_enable      = g_DL_HANDLE_NODE.m_param.m_ft_cfg_enable;
	 	dl_arg.m_ft_cfg.m_security_cfg.m_uint32 = g_DL_HANDLE_NODE.m_param.m_ft_cfg.m_security_cfg.m_uint32;
	 	dl_arg.m_sec_ro_enable      = g_DL_HANDLE_NODE.m_param.m_sec_ro_enable;
	 	dl_arg.m_sec_ro.m_data      = g_DL_HANDLE_NODE.m_param.m_sec_ro.m_data;
	 	dl_arg.m_sec_ro.m_len       = g_DL_HANDLE_NODE.m_param.m_sec_ro.m_len;
        dl_arg.m_cust_para_enable   = g_DL_HANDLE_NODE.m_param.m_cust_para_enable;
		dl_arg.m_cust_para.m_data   = g_DL_HANDLE_NODE.m_param.m_cust_para.m_data;
		dl_arg.m_cust_para.m_len    = g_DL_HANDLE_NODE.m_param.m_cust_para.m_len;
    }

    dl_arg.m_cb_param_process_init		= cb_update_param_init;
    dl_arg.m_cb_param_process_init_arg	= this;
    dl_arg.m_cb_param_process			= cb_update_param;
    dl_arg.m_cb_param_process_arg		= this;

    // post-process callback
    dl_arg.m_cb_post_process_init		= cb_post_process_init;
    dl_arg.m_cb_post_process_init_arg	= this;
    dl_arg.m_cb_post_process			= cb_post_process;
    dl_arg.m_cb_post_process_arg		= this;

    // Boot-Loader download progress callback
    dl_arg.m_cb_download_bloader_init       = cb_download_bloader_init;
    dl_arg.m_cb_download_bloader_init_arg   = this;
    dl_arg.m_cb_download_bloader            = cb_download_bloader;
    dl_arg.m_cb_download_bloader_arg        = this;

    // trigger watch dog timeout after download
    // When GPS download, since DA will enter the relay mode
    // not eanable the watch dog time out
    if ( (!g_DL_HANDLE_NODE.m_param.m_gps_enable ) &&
         (( g_FormatAfterDownloadOption == RESET_TO_FACTORY  )  ||
          ( g_backup_restore_state == BACKUP_FORMAT_DOWNLOAD_RESTORE )))
    {
        // enable watchdog
        dl_arg.m_enable_wdt_timeout      = _TRUE;
        dl_arg.m_ms_wdt_timeout_interval = 5000; // ms
    }
    else {
        // disable watchdog
        dl_arg.m_enable_wdt_timeout      = _FALSE;
        dl_arg.m_ms_wdt_timeout_interval = 0;
    }
    // Write USB download control bit RTC_PDN2 bit7
    /*if( g_project_mode == YuSu)
    {
        dl_arg.m_write_usb_download_control_bit = _TRUE;
     }
     else {
         dl_arg.m_write_usb_download_control_bit = _FALSE;
         }
    */

    // Wayne Add for Smart phone download to enable watch dog
        dl_arg.m_enable_wdt_timeout      = _TRUE;
        dl_arg.m_ms_wdt_timeout_interval = 5000;

    // for GPS project
    dl_arg.m_relay_da_enable           = g_DL_HANDLE_NODE.m_param.m_gps_enable;
    dl_arg.m_gpio_gps.m_power_pin      = g_DL_HANDLE_NODE.m_param.m_gps_power_pin;
    dl_arg.m_gpio_gps.m_reset_pin      = g_DL_HANDLE_NODE.m_param.m_gps_reset_pin;
    dl_arg.m_gpio_gps.m_standby_pin    = g_DL_HANDLE_NODE.m_param.m_gps_standby_pin;
    dl_arg.m_gpio_gps.m_32k_pin        = g_DL_HANDLE_NODE.m_param.m_gps_32k_pin;

    return 0;
}
#endif
//---------------------------------------------------------------------------
int tboot_1::ArgFlashToolReadback( FLASHTOOL_READBACK_ARG       &rb_arg,
                                   FLASHTOOL_READBACK_RESULT    &rb_result)
{

    memset( &rb_arg,    0, sizeof(rb_arg));
    memset( &rb_result, 0, sizeof(rb_result));

#if 0    
    switch( g_OperationMethod )
    {
	    case EMMC_OPERATION:
		    rb_arg.m_storage_type = HW_STORAGE_EMMC;
			break;
        case NAND_OPERATION:
		default:
		    rb_arg.m_storage_type = HW_STORAGE_NAND;
    }
#endif

	rb_arg.m_storage_type = g_platform_info.getFlashToolStorageConfig().GetStorageType();
    // an object of RB_HANDLE
    rb_arg.m_rb_handle                  = g_RB_HANDLE;
    // the accuracy of the read back progress
    rb_arg.m_readback_accuracy          = ACCURACY_AUTO;
    // readback call back funciton
    rb_arg.m_cb_readback_flash_init     = cb_readback_flash_init;
    rb_arg.m_cb_readback_flash_init_arg = this;
    rb_arg.m_cb_readback_flash          = cb_readback_flash;
    rb_arg.m_cb_readback_flash_arg      = this;

    return 0;
}
#if 0
//---------------------------------------------------------------------------
int tboot_1::ArgFlashToolFormat( FLASHTOOL_FORMAT_ARG       &fmt_arg,
                                 FLASHTOOL_FORMAT_RESULT    &fmt_result)
{
    memset( &fmt_arg,    0, sizeof(fmt_arg));
    memset( &fmt_result, 0, sizeof(fmt_result));

	switch( g_OperationMethod )
    {
	    case NFB_OPERATION:
		    fmt_arg.m_storage_type                   = HW_STORAGE_NAND;
			fmt_arg.m_format_cfg.m_format_begin_addr = g_ulNandFormatStartAddr;
		    fmt_arg.m_format_cfg.m_format_length     = g_ulNandFormatLength;
			break;

        case NOR_OPERATION:
        default:
			fmt_arg.m_storage_type                   = HW_STORAGE_NOR;
			fmt_arg.m_format_cfg.m_format_begin_addr = g_ulFormatStartAddr;
		    fmt_arg.m_format_cfg.m_format_length     = g_ulFormatLength;
            break;
    }

    fmt_arg.m_cb_format_report_init        = cb_format_report_init;
	fmt_arg.m_cb_format_report_init_arg    = this;
	fmt_arg.m_cb_format_report             = cb_format_report;
	fmt_arg.m_cb_format_report_arg         = this;
	fmt_arg.m_cb_format_statistics         = cb_format_statistics;
	fmt_arg.m_cb_format_statistics_arg     = this;
	fmt_arg.m_erase_flag                   = g_EraseFlag;
	fmt_arg.m_format_cfg.m_validation      = g_FormatValidation?_TRUE:_FALSE;
	fmt_arg.m_format_cfg.m_auto_format_fat = AUTO_FORMAT == g_FormatOption?_TRUE:_FALSE;
    
    //fmt_arg.m_write_usb_download_control_bit =  _FALSE;

    // trigger watch dog timeout after format
    if ( g_backup_restore_state == BACKUP_FORMAT_DOWNLOAD_RESTORE)
    {
        // enable watchdog
        fmt_arg.m_enable_wdt_timeout      = _TRUE;
        fmt_arg.m_ms_wdt_timeout_interval = 5000; // ms
    }
    else {
        // disable watchdog
        fmt_arg.m_enable_wdt_timeout      = _FALSE;
        fmt_arg.m_ms_wdt_timeout_interval = 0;
    }

    return 0;
}
#endif
//---------------------------------------------------------------------------
int tboot_1::ArgFlashToolDAINFO(DA_PARSE_INFO_E& da_info,
                               DA_PARSE_INFO& da_parse_info)
{
    //DA_PARSE_INFO da_parse_info;
    memset(&da_parse_info, 0, sizeof(da_parse_info));
    memset(&da_info, 0, sizeof(da_info));

    DA_Parsing(g_NAND_UTIL_DA_HANDLE, &da_parse_info, NULL);

    da_info.count = da_parse_info.count;
    da_info.jump_addr = da_parse_info.jump_addr;
    da_info.da_region_list =
                          (DA_PARSE_INFO_REGION_E*)da_parse_info.da_region_list;

    return 0;
}

//---------------------------------------------------------------------------
int tboot_1::ArgFlashToolDLDA( Android_Boot_ARG &boot_arg,
                               DA_Download_ARG &da_dl_arg,
                               const string& s_com_str,
                               DA_PARSE_INFO& da_parse_info)
{

    memset( &boot_arg,    0, sizeof(boot_arg));
    memset( &da_dl_arg, 0, sizeof(da_dl_arg));

    ArgFlashToolDAINFO(da_dl_arg.m_DA_info, da_parse_info);                 

    unsigned int baudrate_tbl[] = { 0, 921600, 460800, 230400, 115200, 57600, 38400, 19200, 9600, 4800, 2400, 1200, 300, 110 };
    // Boot As Download Mode
    boot_arg.m_baud_rate  = (COMM_BAUDRATE)baudrate_tbl[BAUD_RATE];
    boot_arg.m_comport    = COM_PORT;
    boot_arg.m_p_comsymbol= (char*)s_com_str.c_str();
    boot_arg.m_p_stopflag = &g_stopflag;
    boot_arg.m_p_thread   = this;

    da_dl_arg.m_p_stopflag                 = &g_stopflag;
    da_dl_arg.m_p_thread                   = this;
    da_dl_arg.m_p_send_da_percentage       = cb_download_da;
    da_dl_arg.m_p_send_da_status           = cb_download_da_init;
    da_dl_arg.is_DA_verify = true;
    //For new scatter file image size check
    da_dl_arg.is_boundary_Check = IsNewScatterFileWithBoundaryCheck(g_pCurNode->m_dl_handle);
    LOGD(string("[Download_NandUtil_Image] Is to do image boundary check: ")
    		.append((true == da_dl_arg.is_boundary_Check) ? "Y" : "N").c_str());
    return 0;
}

//---------------------------------------------------------------------------
int tboot_1::ArgFlashToolOTP(FLASHTOOL_PARAMETER_ARG &pm_arg,
                                    FLASHTOOL_PARAMETER_RESULT &pm_result)
{
    memset(&pm_arg,    0, sizeof(pm_arg) );
    memset(&pm_result, 0, sizeof(pm_result));
     // DL handle
    pm_arg.m_dl_handle          = g_DL_HANDLE_NODE.m_dl_handle; 

    // OTP
    if( MainForm->cb_otp->Checked ){
        LOGD("[Parameter OTP]: OTP is Checked!");
        if( MainForm->rb_otp_Write->Checked && g_ParamDownloadConfig.m_otp_enable ){
            LOGD("[Parameter OTP]: OTP Write is Checked!");
            pm_arg.m_param.m_otp_enable	= g_ParamDownloadConfig.m_otp_enable;
    	    pm_arg.m_param.m_otp_op 	= g_ParamDownloadConfig.m_otp_op;
        	pm_arg.m_param.m_otp.m_addr = g_ParamDownloadConfig.m_otp.m_addr;
        	pm_arg.m_param.m_otp.m_data = g_ParamDownloadConfig.m_otp.m_data;
    	    pm_arg.m_param.m_otp.m_len 	= g_ParamDownloadConfig.m_otp.m_len;
        }
        else if( MainForm->rb_otp_Read->Checked && g_ParamReadbackConfig.m_otp_enable ){
            LOGD("[Parameter OTP]: OTP Read is Checked!");
            pm_arg.m_param.m_otp_enable = g_ParamReadbackConfig.m_otp_enable;
    	    pm_arg.m_param.m_otp.m_addr = g_ParamReadbackConfig.m_otp.m_addr;
        	pm_arg.m_param.m_otp.m_data = g_ParamReadbackConfig.m_otp.m_data;
        	pm_arg.m_param.m_otp.m_len 	= g_ParamReadbackConfig.m_otp.m_len;
        }

        Logger::GetLogger().Log(Logger::Debug,
        		"[Parameter OTP]: OTP enable is %d, addr is %d, len is %d, data is %s!",
        		pm_arg.m_param.m_otp_enable,
        		pm_arg.m_param.m_otp.m_addr,
        		pm_arg.m_param.m_otp.m_len,
        		pm_arg.m_param.m_otp.m_data);
    }

    pm_arg.m_cb_param_process_init		   = cb_update_param_init;
	pm_arg.m_cb_param_process_init_arg	   = this;
	pm_arg.m_cb_param_process			   = cb_update_param;
	pm_arg.m_cb_param_process_arg		   = this;

	pm_arg.m_cb_post_process_init		   = cb_post_process_init;
	pm_arg.m_cb_post_process_init_arg	   = this;
	pm_arg.m_cb_post_process			   = cb_post_process;
	pm_arg.m_cb_post_process_arg		   = this;

    return 0;
}
#if 0
//---------------------------------------------------------------------------
int tboot_1::ArgFlashToolParameter( FLASHTOOL_PARAMETER_ARG      &pm_arg,
                                    FLASHTOOL_PARAMETER_RESULT   &pm_result)
{

    memset(&pm_arg,    0, sizeof(pm_arg) );
    memset(&pm_result, 0, sizeof(pm_result));

    // DL handle
    pm_arg.m_dl_handle          = g_DL_HANDLE_NODE.m_dl_handle;

    // OTP
    if( MainForm->cb_otp->Checked ){
        LOGD("[Parameter OTP]: OTP is Checked!");
        if( MainForm->rb_otp_Write->Checked && g_ParamDownloadConfig.m_otp_enable ){
            LOGD("[Parameter OTP]: OTP Write is Checked!");
            pm_arg.m_param.m_otp_enable	= g_ParamDownloadConfig.m_otp_enable;
    	    pm_arg.m_param.m_otp_op 	= g_ParamDownloadConfig.m_otp_op;
        	pm_arg.m_param.m_otp.m_addr = g_ParamDownloadConfig.m_otp.m_addr;
        	pm_arg.m_param.m_otp.m_data = g_ParamDownloadConfig.m_otp.m_data;
    	    pm_arg.m_param.m_otp.m_len 	= g_ParamDownloadConfig.m_otp.m_len;
        }
        else if( MainForm->rb_otp_Read->Checked && g_ParamReadbackConfig.m_otp_enable ){
            LOGD("[Parameter OTP]: OTP Read is Checked!");
            pm_arg.m_param.m_otp_enable = g_ParamReadbackConfig.m_otp_enable;
    	    pm_arg.m_param.m_otp.m_addr = g_ParamReadbackConfig.m_otp.m_addr;
        	pm_arg.m_param.m_otp.m_data = g_ParamReadbackConfig.m_otp.m_data;
        	pm_arg.m_param.m_otp.m_len 	= g_ParamReadbackConfig.m_otp.m_len;
        }

        Logger::GetLogger().Log(Logger::Debug,
        		"[Parameter OTP]: OTP enable is %d, addr is %d, len is %d, data is %s!",
        		pm_arg.m_param.m_otp_enable,
        		pm_arg.m_param.m_otp.m_addr,
        		pm_arg.m_param.m_otp.m_len,
        		pm_arg.m_param.m_otp.m_data);
    }

    // secure RO setting
    if( MainForm->cb_sec_setting->Checked ){
        if( MainForm->rb_sec_setting_Write->Checked && g_ParamDownloadConfig.m_ft_cfg_enable ){
    	    pm_arg.m_param.m_ft_cfg_op 		= PARAM_WRITE;
	       	pm_arg.m_param.m_ft_cfg_enable 	= g_ParamDownloadConfig.m_ft_cfg_enable;
    		pm_arg.m_param.m_ft_cfg.m_security_cfg.m_uint32 = g_ParamDownloadConfig.m_ft_cfg.m_security_cfg.m_uint32;
        }
    }

    // secure RO
    if( MainForm->cb_sec_ro->Checked ){
        if( MainForm->rb_sec_ro_Write->Checked && g_ParamDownloadConfig.m_sec_ro_enable ){
    	    pm_arg.m_param.m_sec_ro_op 		= PARAM_WRITE;
    		pm_arg.m_param.m_sec_ro_enable 	= g_ParamDownloadConfig.m_sec_ro_enable;
        	pm_arg.m_param.m_sec_ro.m_data 	= g_ParamDownloadConfig.m_sec_ro.m_data;
    	    pm_arg.m_param.m_sec_ro.m_len 	= g_ParamDownloadConfig.m_sec_ro.m_len;
        }
        else if( MainForm->rb_sec_ro_Read->Checked && g_ParamReadbackConfig.m_sec_ro_enable ){
    	    pm_arg.m_param.m_sec_ro_op 		= PARAM_READ;
    		pm_arg.m_param.m_sec_ro_enable 	= g_ParamReadbackConfig.m_sec_ro_enable;
    	    pm_arg.m_param.m_sec_ro.m_data 	= g_ParamReadbackConfig.m_sec_ro.m_data;
        	pm_arg.m_param.m_sec_ro.m_len 	= g_ParamReadbackConfig.m_sec_ro.m_len;
        }
    }

    // Customer Parameter
    if( MainForm->cb_cust->Checked ){
        if( MainForm->rb_cust_Write->Checked && g_ParamDownloadConfig.m_cust_para_enable ){
    	    pm_arg.m_param.m_cust_para_op 		= PARAM_WRITE;
            pm_arg.m_param.m_cust_para_enable 	= g_ParamDownloadConfig.m_cust_para_enable;
    	    pm_arg.m_param.m_cust_para.m_data 	= g_ParamDownloadConfig.m_cust_para.m_data;
        	pm_arg.m_param.m_cust_para.m_len 	= g_ParamDownloadConfig.m_cust_para.m_len;
        }
        else if( MainForm->rb_cust_Read->Checked && g_ParamReadbackConfig.m_cust_para_enable ){
    	    pm_arg.m_param.m_cust_para_op 		= PARAM_READ;
            pm_arg.m_param.m_cust_para_enable 	= g_ParamReadbackConfig.m_cust_para_enable;
        	pm_arg.m_param.m_cust_para.m_data 	= g_ParamReadbackConfig.m_cust_para.m_data;
    	    pm_arg.m_param.m_cust_para.m_len 	= g_ParamReadbackConfig.m_cust_para.m_len;
        }
    }

    if( MainForm->cb_gps->Checked ){

		pm_arg.m_relay_da_enable           = g_DL_HANDLE_NODE.m_param.m_gps_enable;
        pm_arg.m_gpio_gps.m_power_pin      = g_DL_HANDLE_NODE.m_param.m_gps_power_pin;
        pm_arg.m_gpio_gps.m_reset_pin      = g_DL_HANDLE_NODE.m_param.m_gps_reset_pin;
        pm_arg.m_gpio_gps.m_standby_pin    = g_DL_HANDLE_NODE.m_param.m_gps_standby_pin;
        pm_arg.m_gpio_gps.m_32k_pin        = g_DL_HANDLE_NODE.m_param.m_gps_32k_pin;

    } else {

		pm_arg.m_relay_da_enable           = _FALSE;
        pm_arg.m_gpio_gps.m_power_pin      = 0xFFFF;
        pm_arg.m_gpio_gps.m_reset_pin      = 0xFFFF;
        pm_arg.m_gpio_gps.m_standby_pin    = 0xFFFF;
        pm_arg.m_gpio_gps.m_32k_pin        = 0xFFFF;

    }

	pm_arg.m_cb_param_process_init		   = cb_update_param_init;
	pm_arg.m_cb_param_process_init_arg	   = this;
	pm_arg.m_cb_param_process			   = cb_update_param;
	pm_arg.m_cb_param_process_arg		   = this;

	pm_arg.m_cb_post_process_init		   = cb_post_process_init;
	pm_arg.m_cb_post_process_init_arg	   = this;
	pm_arg.m_cb_post_process			   = cb_post_process;
	pm_arg.m_cb_post_process_arg		   = this;

    return 0;

}
#endif
//---------------------------------------------------------------------------
int tboot_1::ArgCloneChksum(S_CHKSUM_Arg &chksum_arg)
{
    chksum_arg.m_cb_rom_mem_checksum_init = cb_checksum_init;
    chksum_arg.m_cb_rom_mem_checksum_init_arg = this;
    chksum_arg.m_cb_rom_mem_checksum = cb_checksum_progress;
    chksum_arg.m_cb_rom_mem_checksum_arg = this;
    chksum_arg.stopflag = &g_stopflag;

     return 0;
}
//---------------------------------------------------------------------------
int tboot_1::ArgFlashTool(FLASHTOOL_ARG &arg, FLASHTOOL_RESULT &result)
{
    memset( &arg,    0, sizeof(arg));
    memset( &result, 0, sizeof(result));

    // With All-In-One FLASHTOOL_RESULT to get DA report
    m_bGetDAReportWithConnArg = false;

    // fill BOOT_FLASHTOOL_ARG
	ArgBootFlashTool( arg.m_boot_arg, &(result.m_da_report.m_bbchip_type) );

	arg.m_cb_da_report                       = cb_da_report;
    arg.m_cb_da_report_arg                   = this;
    arg.m_cb_security_pre_process_notify     = cb_security_pre_process_notify;
    arg.m_cb_security_pre_process_notify_arg = this;
	arg.m_baudrate_full_sync_count           = g_Baudrate_FullSync_Count;
	arg.m_nor_chip_select[0]                 = CS_0;
    arg.m_nor_chip_select[1]                 = CS_WITH_DECODER;
   	arg.m_nand_chip_select                   = g_bNFI_SelectCS1?CS_1:CS_0;
    arg.m_p_nand_acccon                      = g_EMI_NFI_Setting.m_bAuto?NULL:&(g_EMI_NFI_Setting.m_nand_acccon);


    // get the DRAM EMI Setting from UI
    if( ext_mem1Form->m_EnableDRAMSetting->Checked ) {
        arg.m_enable_ui_dram_cfg            = _TRUE;
        memcpy(&arg.m_dram_cfg, &g_EMI_NFI_Setting.m_dram_cfg, sizeof(DRAM_SETTING));
    }
    else{
        arg.m_enable_ui_dram_cfg            = _FALSE;
    }

    return 0;
}
#if 0
//---------------------------------------------------------------------------
int tboot_1::ArgFlashToolProgress(FlashTool_Progress_Arg  &pgs_arg)
{
    memset(&pgs_arg,  0, sizeof(pgs_arg));

    pgs_arg.m_cb_progress_init      = cb_progress_init;
    pgs_arg.m_cb_progress_init_arg  = this;
    pgs_arg.m_cb_progress           = cb_progress;
    pgs_arg.m_cb_progress_arg       = this;

    return 0;

}

//---------------------------------------------------------------------------
int tboot_1::ArgFlashToolChangeBaudrate(FlashTool_ChangeBaudrate_Arg &cb_arg)
{
    memset(&cb_arg,   0,   sizeof(cb_arg));

    cb_arg.m_baudrate                       = BAUD_RATE;
    cb_arg.m_baudrate_full_sync_count       = g_Baudrate_FullSync_Count;
    cb_arg.m_cb_set_high_speed_baudrate     = NULL;
    cb_arg.m_cb_set_high_speed_baudrate_arg = NULL;

    return 0;
}
#endif
//---------------------------------------------------------------------------
int tboot_1::ArgFlashToolMemoryTest( FlashTool_MemoryTest_Arg    &mt_arg,
                                     FlashTool_MemoryTest_Result &mt_result)
{

    memset(&mt_arg,    0, sizeof(mt_arg));
    memset(&mt_result, 0, sizeof(mt_result));

    mt_arg.m_cb_memorytest_progress         = cb_memorytest_progress;
    mt_arg.m_cb_memorytest_progress_arg     = &mt_arg;
    mt_arg.m_cb_memorytest_progress_init    = NULL;
    mt_arg.m_p_stopflag                     = NULL;

    return 0;
}
//---------------------------------------------------------------------------
int tboot_1::ArgMETAConnectWithTargetInMETA( META_ConnectInMETA_Req  &META_ConnectInMETA_Req ,
                                             META_ConnectInMETA_Report  &META_ConnectInMETA_Report,
                                             int com_port)
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
    return 0;
}
//---------------------------------------------------------------------------
/*
int tboot_1::ArgWMMETAConnectWithTargetInMETA( WM_META_ConnectInMETA_Req  &WM_META_ConnectInMETA_Req ,
                                           WM_META_ConnectInMETA_Report  &WM_META_ConnectInMETA_Report)
{
    memset(&WM_META_ConnectInMETA_Req,    0, sizeof(WM_META_ConnectInMETA_Req));
    memset(&WM_META_ConnectInMETA_Report, 0, sizeof(WM_META_ConnectInMETA_Report));
    WM_META_ConnectInMETA_Req.com_port = COM_PORT;

    // set baud rate = AUTO
    WM_META_ConnectInMETA_Req.baudrate[0] = META_BAUD57600;
    WM_META_ConnectInMETA_Req.baudrate[1] = META_BAUD115200;
    WM_META_ConnectInMETA_Req.baudrate[2] = META_BAUD230400;
    WM_META_ConnectInMETA_Req.baudrate[3] = META_BAUD460800;
    WM_META_ConnectInMETA_Req.baudrate[4] = META_BAUD921600;
    WM_META_ConnectInMETA_Req.baudrate[5] = META_BAUD1500000;
    WM_META_ConnectInMETA_Req.baudrate[6] = META_BAUD_END;
    WM_META_ConnectInMETA_Req.flowctrl = META_SW_FLOWCTRL;

    WM_META_ConnectInMETA_Req.ms_connect_timeout = 40000;
    return 0;
}
*/
//---------------------------------------------------------------------------
int tboot_1::ArgMETAConnectWithTarget( META_Connect_Req	     &meta_con_req,
                                       META_Connect_Report   &meta_con_report)
{

    static 	META_COMM_BAUDRATE  allow_baudrate[11]={
		META_BAUD115200,
		META_BAUD230400,
		META_BAUD460800,
		META_BAUD921600,
		META_BAUD1500000,
		META_BAUD_END,
		META_BAUD_END,
		META_BAUD_END,
		META_BAUD_END,
		META_BAUD_END,
		META_BAUD_END
	};


    memset(&meta_con_req,    0, sizeof(meta_con_req));
    memset(&meta_con_report, 0, sizeof(meta_con_report));



    meta_con_req.com_port = COM_PORT;

	memcpy(meta_con_req.baudrate, allow_baudrate, sizeof(meta_con_req.baudrate));

	meta_con_req.flowctrl           = META_SW_FLOWCTRL;
	meta_con_req.ms_connect_timeout = 40000;

    meta_con_req.boot_meta_arg.m_bbchip_type = g_BBCHIP_TYPE;
    meta_con_req.boot_meta_arg.m_ext_clock   = g_EXT_CLOCK;

    meta_con_req.boot_meta_arg.m_ms_boot_timeout           = BOOT_INFINITE;
    meta_con_req.boot_meta_arg.m_max_start_cmd_retry_count = g_MaxBromStartCmdRetryCount;

    // This callback function will be invoke after COM port is opened
	// You can do some initialization by using this callback function.
    meta_con_req.boot_meta_arg.m_cb_com_init_stage     = cb_com_init_stage;
    meta_con_req.boot_meta_arg.m_cb_com_init_stage_arg = this;

    // This callback function will be invoke after BootROM start cmd is passed.
    // You can issue other BootROM command by brom_handle and hCOM which provides callback arguments,
    // or do whatever you want otherwise.
    //meta_con_req.boot_meta_arg.m_cb_in_brom_stage      = cb_boot_meta_in_brom_stage;
    meta_con_req.boot_meta_arg.m_cb_in_brom_stage      = NULL;
    meta_con_req.boot_meta_arg.m_cb_in_brom_stage_arg  = this;

    // speed-up BootROM stage baudrate
    meta_con_req.boot_meta_arg.m_speedup_brom_baudrate = g_SpeedUpBootROMBaudrate?_TRUE:_FALSE;

	// WM_BROM_READY_TO_POWER_ON_TGT
	meta_con_req.boot_meta_arg.m_ready_power_on_wnd_handle	= NULL;
	meta_con_req.boot_meta_arg.m_ready_power_on_wparam		= NULL;
	meta_con_req.boot_meta_arg.m_ready_power_on_lparam		= NULL;

	// serial link authentication arg
	meta_con_req.boot_meta_arg.m_auth_handle = g_AUTH_HANDLE;
	meta_con_req.boot_meta_arg.m_cb_sla_challenge         = SLA_Challenge;
	meta_con_req.boot_meta_arg.m_cb_sla_challenge_arg     = this;
	meta_con_req.boot_meta_arg.m_cb_sla_challenge_end     = SLA_Challenge_END;
	meta_con_req.boot_meta_arg.m_cb_sla_challenge_end_arg = this;

    // Boot META, usb flag, msut to set false, since call the META_ConnectWithTarget() API
    meta_con_req.boot_meta_arg.m_usb_enable = _FALSE;

    return 0;

}
//---------------------------------------------------------------------------
static void __stdcall cb_backup_calibration_data_init( unsigned char total, unsigned char cur, void* usr_arg )
{
    AnsiString aTotal = total;
    AnsiString aCur = cur;

    MainForm->sb_Main->Panels->Items[5]->Text = " Total Backup Files : " + aTotal + ", Current Backup File : " + aCur ;

    // reset the output information
    if ( aTotal == aCur ) MainForm->sb_Main->Panels->Items[5]->Text = "";
    return;
}

//---------------------------------------------------------------------------
int tboot_1::ArgMETABackupCalibrationData( MISC_BACKUP_REQ_T    &meta_backup_req )
{
    memset(&meta_backup_req,    0, sizeof(meta_backup_req));

    char *iniPath = new  char[ gc_METABackupINI.Length() +  1 ];
    strcpy( iniPath ,  gc_METABackupINI.c_str() );
    meta_backup_req.m_pIniFilePath     = iniPath;

    char *path = new  char[ g_BackupCalibrationDataFolderPath.Length() +  1 ];
    strcpy( path ,  g_BackupCalibrationDataFolderPath.c_str() );
    meta_backup_req.m_pBackupFolderPath = path;

    meta_backup_req.cb_progress         = cb_backup_calibration_data_init;
    meta_backup_req.cb_progress_arg     = this;

    return 0;
}
//---------------------------------------------------------------------------
static void __stdcall cb_restore_calibration_data_init( unsigned char total, unsigned char cur, void* usr_arg )
{
    AnsiString aTotal = total;
    AnsiString aCur = cur;

    MainForm->sb_Main->Panels->Items[5]->Text = " Total Restore Files : " + aTotal + ", Current Restore File : " + aCur ;

    // reset the output information
    if ( aTotal == aCur ) MainForm->sb_Main->Panels->Items[5]->Text = "";

    // clear hw status
    MainForm->m_HWStatus->Panels->Items[0]->Text = "";
    MainForm->m_HWStatus->Panels->Items[1]->Text = "";
    MainForm->m_HWStatus->Panels->Items[2]->Text = "";
    MainForm->m_HWStatus->Panels->Items[3]->Text = "";
  	MainForm->m_HWStatus->Hint = "";

    return;
}

//---------------------------------------------------------------------------
int tboot_1::ArgMETARestoreCalibrationData( MISC_RESTORE_REQ_T  &meta_restore_req )
{
    memset(&meta_restore_req,   0, sizeof(meta_restore_req));

    char *iniPath = new  char[ gc_METABackupINI.Length() +  1 ];
    strcpy( iniPath ,  gc_METABackupINI.c_str() );
    meta_restore_req.m_pIniFilePath      = iniPath;

    char *backupPath = new  char[ g_BackupCalibrationDataFolderPath.Length() +  1 ];
    strcpy( backupPath ,  g_BackupCalibrationDataFolderPath.c_str() );
    meta_restore_req.m_pBackupFolderPath = backupPath;

    meta_restore_req.cb_progress         = cb_restore_calibration_data_init;
    meta_restore_req.cb_progress_arg     = this;

    return 0;
}
//---------------------------------------------------------------------------
/*
int ArgMETAReadNVRAM (FT_NVRAM_READ_REQ &m_psNVRAM_ReadReq, &m_sNVRAM_ReadCnf);
{
    m_psNVRAM_ReadReq.LID = "NVRAM_EF_IMEI_IMEISV_LID";
    m_psNVRAM_ReadReq.RID = 0; // temp set to 0

}
*/
//---------------------------------------------------------------------------
static void __stdcall cb_upload_calibration_data_init( unsigned char total, unsigned char cur, void* usr_arg )
{
    AnsiString aTotal = total;
    AnsiString aCur = cur;

    MainForm->sb_Main->Panels->Items[5]->Text = " Total Upload Files : " + aTotal + ", Current Upload File : " + aCur ;

    // reset the output information
    if ( aTotal == aCur ) MainForm->sb_Main->Panels->Items[5]->Text = "";

    // clear hw status
    MainForm->m_HWStatus->Panels->Items[0]->Text = "";
    MainForm->m_HWStatus->Panels->Items[1]->Text = "";
    MainForm->m_HWStatus->Panels->Items[2]->Text = "";
    MainForm->m_HWStatus->Panels->Items[3]->Text = "";
  	MainForm->m_HWStatus->Hint = "";

    return;
}
//---------------------------------------------------------------------------
//static void __stdcall cb_upload_imei(const char *errorMessage1,
//                                     const char *errorMessage2,
//                                     const char *imei1,
//                                     const char *imei2,
//                                     void *)
//{
//    AnsiString status;
//
//    if ((errorMessage1 != NULL) && (imei1 != NULL))
//    {
//        status += AnsiString("IMEI1: ") + imei1 + " (" + errorMessage1 + ")  ";
//    }
//
//    if ((errorMessage2 != NULL) && (imei2 != NULL))
//    {
//        status += AnsiString("IMEI2: ") + imei2 + " (" + errorMessage2 + ")";
//    }
//
//    MainForm->sb_Main->Panels->Items[5]->Text = status;
//
//    // clear hw status
//    MainForm->m_HWStatus->Panels->Items[0]->Text = "";
//    MainForm->m_HWStatus->Panels->Items[1]->Text = "";
//    MainForm->m_HWStatus->Panels->Items[2]->Text = "";
//    MainForm->m_HWStatus->Panels->Items[3]->Text = "";
//    MainForm->m_HWStatus->Hint = "";
//}

static void __stdcall cb_upload_imei(const int imei_num,
                                     const char **errMsg,
                                     const char **imei,
                                     void *usr_arg)
{
    if ((imei_num == 0) || (errMsg == NULL) ||
        (imei == NULL)  || (usr_arg == NULL))
    {
        return;
    }

    AnsiString *status = static_cast<AnsiString *>(usr_arg);

    for (int i=0; i<imei_num ; ++i)
    {
        if ((imei[i] == NULL) || (errMsg[i] == NULL))
        {
            continue;
        }

        (*status) += AnsiString("IMEI") + (i + 1) + ": " + imei[i] +
                     " (" + errMsg[i] + ")\n";
    }
    MainForm->sb_Main->Panels->Items[5]->Text = *status;
}

//---------------------------------------------------------------------------
int tboot_1::ArgMETAUploadFilesToTarget(MISC_UPLOAD_REQ_EX_T &meta_upload_req,
                                        AnsiString *imei_status)
{
    memset(&meta_upload_req,  0, sizeof(meta_upload_req));

    //Use FlashTool.ini for writing IMEI
    char *iniPath = new char[gc_FlashToolINI.Length() + 1];

    strcpy(iniPath, gc_FlashToolINI.c_str());

    meta_upload_req.m_pIniFilePath       = iniPath;
    meta_upload_req.cb_progress          = cb_upload_calibration_data_init;
    meta_upload_req.cb_progress_arg      = this;
    meta_upload_req.cb_imei_progress     = cb_upload_imei; /*cb_upload_imei;*/
    meta_upload_req.cb_imei_progress_arg = imei_status;

    return 0;
}

//---------------------------------------------------------------------------
int tboot_1::ArgMETAEnableWatchDogTimer( FtWatchDog &meta_watchdog_req )
{
    memset(&meta_watchdog_req,    0, sizeof(meta_watchdog_req));

    meta_watchdog_req.ms_timeout_interval = 5000;//ms

    return 0;
}
//---------------------------------------------------------------------------
int tboot_1::ArgMETAGetBackupResultInfo( BACKUP_RESULT_T &cnf )
{
    memset(&cnf,    0,     sizeof(cnf));

    return 0;
}


//added for DA download all
int tboot_1::DownloadYuSu_ByDA( void )
{
    int ret;
    bool is_need_dl_uboot, is_need_dl_image;
    ErrorLookup::SetErrorCodeMode(BROM);;
    
    // fill flash download argument
//    ArgFlashDownload();
//
//    ret = FlashDownload( &com, &arg, &result, &dl_arg, &dl_result, NULL,&g_stopflag );

    ret = FlashDownload_internal();

    return ret;
}
#if 0
int tboot_1::FormatDownloadYuSu_ByDA( void )
{
	int ret;
	ErrorLookup::SetErrorCodeMode(BROM);;

	//Auto format without disconnect to execute download with FlashToolDownload api
	ret = Auto_Format_Without_Disconnect();
	if (S_DONE != ret) {
		return ret;
	}

	g_platform_info.setChipName(cn_result.m_da_report.m_bbchip_name);
    
    LOG("tboot_1::FormatDownloadYuSu_ByDA(): m_bbchip_name(%s), isChipSupportUSBHighSpeed(%s), g_bDAEnableHS(%s)",
        cn_result.m_da_report.m_bbchip_name, 
        (g_platform_info.getPlatformConfig().supportUSBHighSpeed()) ? "Y" : "N",
        g_bDAEnableHS ? "Y" : "N");
	if( (g_platform_info.getPlatformConfig().supportUSBHighSpeed()) &&
        g_bDAEnableHS) {
		ret = FlashTool_SetupUSBDL(&g_ft_handle, (g_bDAEnableHS ? 1 : 0));
		if( S_DONE != ret ) {
			FlashTool_Disconnect( &g_ft_handle );
			return ret;
		}
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
		Synchronize(UpdateUSBVCOMInfo);
		if(!ScanUSBVOMWithTimeout(USB_SCAN_TIMEOUT, 
			usb_da_highspeed.GetUSBPID(), usb_da_highspeed.GetUSBVID())) {
			LOG("ERROR: FlashDownload_internal: Search %s Fail!", usb_da_highspeed.GetUSBName().c_str());
			return ret = S_UNDEFINED_ERROR;
		}
		LOG("'%s', '%s'\n", m_strPort, m_strSymbolic);
		unsigned char  com_port =  GetUSBVCOMNumByPortName(m_strPort);
		//Update COM_PORT for GUI error code in ErrorLookup.cpp S_COM_PORT_OPEN_FAIL
		COM_PORT = com_port;
		LOG("FormatDownloadYuSu_ByDA: Search COM(%d)\n", com_port);

		ret = FlashTool_ChangeCOM(&g_ft_handle, com_port);
		if( S_DONE != ret ) {
			LOGD("ERROR: FormatDownloadYuSu_ByDA: change COM fail!");      
			FlashTool_Disconnect( &g_ft_handle );
			return ret;
		}
	}

	FlashTool_Download_Arg fdl_arg;
	FlashTool_Download_Result fdl_res;
	ArgFlashToolAdvancedDownload(fdl_arg, fdl_res);

	ret = FlashTool_Download(g_ft_handle, &fdl_arg, &fdl_res);
	if ( S_DONE != ret ) {
		FlashTool_Disconnect(&g_ft_handle);
		LOGD("FormatDownloadYuSu: FlashTool_Download fail!");
		return ret;
	}
	ret = FlashTool_Disconnect(&g_ft_handle);
	if(S_DONE != ret) {
		LOGD("FormatDownloadYuSu: FlashTool_Disconnect fail!");
		return ret;
	}

	return S_DONE;
}
#endif

int tboot_1::FlashFormat_internal()
{
	int ret;
	ErrorLookup::SetErrorCodeMode(BROM);
#if 0
	bool enableWdt = (g_backup_restore_state == BACKUP_FORMAT_DOWNLOAD_RESTORE);
#endif
    ArgFlashToolConnect(cn_arg, cn_result);
    unsigned char  com_port = (g_bUsbMode || g_bUsbDLDA) ? GetUSBVCOMNumByPortName(m_strPort)  : COM_PORT;    

    if (!g_bUsbDLDA) {
    	int  force_charge = /*g_bUsbModeWithBattery ? 0 : 1*/GetBatteryStatus();
	LOGD("FlashFormat_internal: force_charge(%d)", force_charge);
        ret = FlashTool_Connect(com_port, &cn_arg, &cn_result, NULL, &g_stopflag,
    			&g_ft_handle,force_charge);
    } else {
        ret = FlashTool_NandUtil_Connect( com_port, &cn_arg, &cn_result, &g_stopflag, &g_ft_handle);
    }
	if (S_DONE != ret) {
		FlashTool_Disconnect(&g_ft_handle);
		return ret;
	}

   ErrorLookup::SetErrorCodeMode(FLASHTOOL);
 /*  std::string targetStorage = GetStorageByDAReport(cn_result);
   if(!g_platform_info.isStorageMatched(targetStorage))*/
   if(!CheckStorageByDAReport())
   {
       LOGD("Storage not matched.");
	 FlashTool_Disconnect(&g_ft_handle);
	 return FT_STORAGE_ERROR;
   }
   ErrorLookup::SetErrorCodeMode(BROM);
    
    bool isDynamicLayout = false;
    g_platform_info.setChipName(cn_result.m_da_report.m_bbchip_name);
    if( g_platform_info.getPlatformConfig().supportLogicalAddress()) {
        isDynamicLayout = true; //Smart Phone Platform after MT6516 will apply dynamic layout
    } else {
        isDynamicLayout = false;
    }

    FlashTool_Format_Arg       fmt_arg;
    FlashTool_Format_Result    fmt_res;
    ret = ArgFlashToolAdvancedFormat(fmt_arg, fmt_res, cn_result, true, isDynamicLayout); 
    if(S_DONE != ret) {
        FlashTool_Disconnect(&g_ft_handle);
        return ret;
    }
        
	ret = FlashTool_Format(g_ft_handle, &fmt_arg, &fmt_res);
	if(S_DONE != ret)
	{
		FlashTool_Disconnect(&g_ft_handle);
		return ret;
	}
#if 0
	if(enableWdt){
		ret  = FlashTool_EnableWatchDogTimeout(g_ft_handle, 5000);
		if(S_DONE != ret)
		{
			FlashTool_Disconnect(&g_ft_handle);
			return ret;
		}
	}
#endif
	ret = FlashTool_Disconnect(&g_ft_handle);    
    
 #if 0   
    if(g_bUsbDLDA){
        ArgFlashFormat();
        ret = NandUtil_FlashFormat (&com, &arg, &result, &fmt_arg, &fmt_result, &g_stopflag);
        g_ulNandFormatLengthByDAReport = result.m_da_report.m_nand_flash_size;
    } else {
    	ArgFlashToolConnect(cn_arg, cn_result);
    	unsigned char  com_port = (!g_bUsbMode) ? COM_PORT : GetUSBVCOMNumByPortName(m_strPort);

    	FlashTool_Format_Arg       fmt_arg;
    	FlashTool_Format_Result    fmt_res;
    	ArgFlashToolAdvancedFormat(fmt_arg, fmt_res, cn_result, true);
    	ret = FlashFormat_allInOne(com_port, g_stopflag, g_ft_handle, cn_arg,
    			cn_result, fmt_arg, fmt_res, enableWdt, g_bUsbDLDA);
        g_ulNandFormatLengthByDAReport = cn_result.m_da_report.m_nand_flash_size;
    }
#endif
//    ret = FlashFormat_allInOne(com_port, g_stopflag, g_ft_handle, cn_arg,
//    			cn_result, fmt_arg, fmt_res, enableWdt, g_bUsbDLDA);
	//FIXME
    g_ulNandFormatLengthByDAReport = cn_result.m_da_report.m_nand_flash_size;
 
	return ret;
}

bool  tboot_1::VerifyLayoutBeforeDownload(const DL_HANDLE_T &dl_handle,
                                          const FLASHTOOL_API_HANDLE_T &flashtool_handle)
{
      bool ret = true;
	  
      NandLayoutParameter nand_para(dl_handle, flashtool_handle);
      if(nand_para.is_target_layout_map_ready())
      	{
      	      LOG("%s(): Target layout map is ready.", __FUNC__);
			  
             if(!nand_para.CompareIsNandLayoutMatched())
             {
                   LOG("%s(): Load layout and target layout is not matched!", __FUNC__);
		     ret = false;
	      }
	}

	return ret;
}

int tboot_1::FlashDownload_internal()
{
	int ret;

	//-1. Connect and get the HW information
	ArgFlashToolConnect(cn_arg, cn_result);
	unsigned char  com_port = (!g_bUsbMode) ? COM_PORT : GetUSBVCOMNumByPortName(m_strPort);
	//Update brom.dll com port number
	COM_PORT = com_port;

	FlashTool_Download_Arg fdl_arg;
	FlashTool_Download_Result fdl_res;
	ArgFlashToolAdvancedDownload(fdl_arg, fdl_res);

       int  force_charge = /*g_bUsbModeWithBattery ? 0 : 1*/GetBatteryStatus();
	LOGD("FlashDownload_internal: force_charge(%d)", force_charge);
	ret = FlashTool_Connect( com_port, &cn_arg, &cn_result, NULL, &g_stopflag, &g_ft_handle,force_charge);
	if( S_DONE != ret ) {
		FlashTool_Disconnect( &g_ft_handle );
		return ret;
	}

	ErrorLookup::SetErrorCodeMode(FLASHTOOL);   
	
	g_platform_info.setChipName(cn_result.m_da_report.m_bbchip_name);
	LOGD(string("FlashDownload_internal: The load to be downloadeded is for ").append(g_platform_info.getLoadPlatformName()).c_str());
	LOGD(string("FlashDownload_internal: Target platform by DA report is ").append(g_platform_info.getTargetPlatformName()).c_str());
	if( !g_platform_info.isPlatformMatched() ) {
		FlashTool_Disconnect( &g_ft_handle );
		return FT_DL_PLATFORM_ERROR;
	}
      
       if(!VerifyLayoutBeforeDownload(g_DL_HANDLE_NODE.m_dl_handle, g_ft_handle))
       {
             FlashTool_Disconnect( &g_ft_handle );
             return FT_DOWNLOAD_LAYOUT_CHANGED;
	}	
	
	ErrorLookup::SetErrorCodeMode(BROM);

      LOG("tboot_1::FlashDownload_internal(): m_bbchip_name(%s), isChipSupportUSBHighSpeed(%s), g_bDAEnableHS(%s)",
        cn_result.m_da_report.m_bbchip_name, 
        g_platform_info.getPlatformConfig().supportUSBHighSpeed() ? "Y" : "N",
        g_bSwitchSpeed ? "Y" : "N");

      //get usb speed status
      FlashTool_USB_Status_Result usb_status_result;
      ret = GetUSBSpeedStatus(g_ft_handle, usb_status_result);
	if(S_DONE != ret)
	{
          LOGE("Get USB Speed Status fail! ret(%d)", ret);
	    FlashTool_Disconnect(&g_ft_handle);
	    return ret;
	}
	  
	if( g_platform_info.getPlatformConfig().supportUSBHighSpeed() &&
		g_bSwitchSpeed && (usb_status_result.usb_speed_status == USB_FULL_SPEED)) {		
		LOG("tboot_1::FlashDownload_internal(): DA Enable High Speed Flag is %s.",
			((g_bSwitchSpeed&&(usb_status_result.usb_speed_status == USB_FULL_SPEED))? "true" : "false"));

              Synchronize(UpdateUSBVCOMInfo);
             	if (!Swith2DAHighSpeed(&g_stopflag, m_strSymbolic, m_strPort, g_ft_handle, true, 30)) {
                FlashTool_Disconnect( &g_ft_handle );
				LOGE("Search and switch to DA HS USB Failed!");
                return ret = FT_FIND_USB_ERROR;
			} else {	 
				Synchronize(UpdateUSBVCOMInfo);
				speed_status= "USB_FULL_SPEED->USB_HIGH_SPEED";
			}
		
		ErrorLookup::SetErrorCodeMode(BROM);

	}

	ret = FlashTool_Download(g_ft_handle, &fdl_arg, &fdl_res);
	if ( S_DONE != ret ) {
		FlashTool_Disconnect(&g_ft_handle);
		LOGD("tboot_1::FlashDownload_internal: FlashTool_Download fail!");
		return ret;
	}

	if ( g_platform_info.getPlatformConfig().doesUSBDLControlBit() ) {
		ret = FlashTool_WriteUSBDownloadControlBit(g_ft_handle);
		if ( S_DONE != ret ) {
			FlashTool_Disconnect(&g_ft_handle);
			LOGD("ERROR: tboot_1::FlashDownload_internal: FlashTool_WriteUSBDownloadControlBit fail!");
			return ret;
		}	    
	}
	
	if(!ToolInfo::IsCustomerVer()) {
		FlashTool_EnableWDT_Arg wdt_arg;
		FlashTool_EnableWDT_Arg *p_wdt_arg = &wdt_arg;
		ArgFlashToolWatchDog(p_wdt_arg);
		ret = FlashTool_EnableWatchDogTimeout(g_ft_handle, p_wdt_arg);
		if(S_DONE != ret) {
			FlashTool_Disconnect(&g_ft_handle);
			LOGD("tboot_1::FlashDownload_internal: FlashTool_EnableWatchDogTimeout fail!");
			return ret;
		}
	}
	ret = FlashTool_Disconnect(&g_ft_handle);
	if(S_DONE != ret) {
		LOGD("tboot_1::FlashDownload_internal: FlashTool_Disconnect fail!");
		return ret;
	}

#if 0
	ret = FlashDownload_allInOne(com_port, g_stopflag, g_ft_handle, cn_arg,
			cn_result, fdl_arg, fdl_res);
#endif
	return ret;
}

int tboot_1::FlashReadback_internal()
{
	int ret;

	//-1. Connect and get the HW information
	ArgFlashToolConnect(cn_arg, cn_result);
	unsigned char  com_port = (!g_bUsbMode) ? COM_PORT : GetUSBVCOMNumByPortName(m_strPort);


	int force_charge = /*g_bUsbModeWithBattery ? 0 : 1*/GetBatteryStatus();
	LOGD("FlashReadback_internal: force_charge(%d)", force_charge);
	ret = FlashTool_Connect( com_port, &cn_arg, &cn_result, NULL, &g_stopflag, &g_ft_handle,force_charge);
	if( S_DONE != ret ) {
		FlashTool_Disconnect( &g_ft_handle );
		return ret;
	}

	bool isDynamicLayout = false;
	g_platform_info.setChipName(cn_result.m_da_report.m_bbchip_name);
    if( g_platform_info.getPlatformConfig().supportLogicalAddress()) {
        isDynamicLayout = true;//Smart Phone Platform after MT6516 will apply dynamic layout
    } else {
        isDynamicLayout = false; 
    }

	//get usb speed status
      FlashTool_USB_Status_Result usb_status_result;
      ret = GetUSBSpeedStatus(g_ft_handle, usb_status_result);
	if(S_DONE != ret)
	{
          LOGE("Get USB Speed Status fail! ret(%d)", ret);
	    FlashTool_Disconnect(&g_ft_handle);
	    return ret;
	}

	if( g_platform_info.getPlatformConfig().supportUSBHighSpeed() &&
		g_bSwitchSpeed && (usb_status_result.usb_speed_status == USB_FULL_SPEED)) {
		    ErrorLookup::SetErrorCodeMode(FLASHTOOL);
		    Synchronize(UpdateUSBVCOMInfo);
			if (!Swith2DAHighSpeed(&g_stopflag, m_strSymbolic, m_strPort, g_ft_handle, true, 30)) {
                FlashTool_Disconnect( &g_ft_handle );
				LOGE("Search and switch to DA HS USB Failed!");
                return  FT_FIND_USB_ERROR;
			} else {			      
                          speed_status= "USB_FULL_SPEED->USB_HIGH_SPEED";
				Synchronize(UpdateUSBVCOMInfo);
			}
			ErrorLookup::SetErrorCodeMode(BROM);
	}

	FlashTool_Readback_Arg rb_arg;
	FlashTool_Readback_Result rb_result;

	ret = ArgFlashToolAdvancedReadback(rb_arg, rb_result, isDynamicLayout, g_RB_HANDLE);
	if( S_DONE != ret ) {
		FlashTool_Disconnect( &g_ft_handle );
		return ret;
	}

	ret = FlashTool_Readback(g_ft_handle, &rb_arg, &rb_result);
	if ( S_DONE != ret ) {
		FlashTool_Disconnect(&g_ft_handle);
		LOGD("FlashReadback_internal: FlashTool_Download fail!");
		return ret;
	}
	ret = FlashTool_Disconnect(&g_ft_handle);
	if(S_DONE != ret) {
		LOGD("FlashReadback_internal: FlashTool_Disconnect fail!");
		return ret;
	}

	return S_DONE;
}

int tboot_1::ArgFlashToolAdvancedReadback(FlashTool_Readback_Arg &rb_arg,
		FlashTool_Readback_Result &rb_result, bool isDynamicLayout, RB_HANDLE_T rb_handle)
{
    memset( &rb_arg,    0, sizeof(rb_arg));
    memset( &rb_result, 0, sizeof(rb_result));

	rb_arg.m_storage_type = g_platform_info.getFlashToolStorageConfig().GetStorageType();
	LOG("tboot_1::ArgFlashToolAdvancedReadback(): m_storage_type(%s).", HWStorageTypeToString(rb_arg.m_storage_type));
	// an object of RB_HANDLE
	rb_arg.m_rb_handle = rb_handle;
	// the accuracy of the read back progress
	rb_arg.m_readback_accuracy = ACCURACY_AUTO;
	// readback call back funciton
	rb_arg.m_cb_readback_flash_init = cb_readback_flash_init;
	rb_arg.m_cb_readback_flash_init_arg = this;
	rb_arg.m_cb_readback_flash = cb_readback_flash;
	rb_arg.m_cb_readback_flash_arg = this;
   
	int ret = S_DONE;
	unsigned short count = 0;
	ret = RB_GetCount(rb_handle, &count);
	if ( S_DONE != ret ) {
		return ret;
	}

	RB_INFO	 *pRBInfo = NULL; 
	pRBInfo	= new RB_INFO[count];
	do{
		ret = RB_GetInfoAll( rb_handle, pRBInfo, count );
		if ( S_DONE != ret ) {
			break;
		}

		for (unsigned short i = 0; i < count; i++) {
			if ( isDynamicLayout) {
				ret = RB_SetAddrTypeFlag(rb_handle,  i, (g_bPhysicallyFormatReadback ? NUTL_ADDR_PHYSICAL : NUTL_ADDR_LOGICAL));
				LOG("ArgFlashToolAdvancedReadback: rom index: %d, rb_setaddrtypeflag setting: %s", 
					i,
					(g_bPhysicallyFormatReadback ? "NUTL_ADDR_PHYSICAL" : "NUTL_ADDR_LOGICAL" ));
			} else {
			    ret = RB_SetAddrTypeFlag(rb_handle,  i, NUTL_ADDR_PHYSICAL);//For MT6516 ONLY Physcial readback
				LOG("ArgFlashToolAdvancedReadback: rom index: %d, NUTL_ADDR_PHYSICAL", i);
			}
			if ( S_DONE != ret ) {
				break;
			}
		}
	} while(0);

	if ( NULL != pRBInfo ) {
	    delete [] pRBInfo;
		pRBInfo = NULL;
	}

    return ret;
}

int tboot_1::ArgFlashToolRBSetting(RB_HANDLE_T rb_handle, const RB_INFO &rb_info, const NUTL_AddrTypeFlag_E  addr_flag)
{
	int ret = 0;

	ret = RB_Append(rb_handle, rb_info.filepath, rb_info.readback_addr, rb_info.readback_len);
	if( S_DONE != ret ) {
		LOGD("ArgFlashToolRBSetting: RB_Append fail!");
		return ret;
	}

	ret = RB_SetReadbackFlag(rb_handle, 0, rb_info.m_read_flag);
	if( S_DONE != ret ) {
		LOGD("ArgFlashToolRBSetting: RB_SetReadbackFlag fail!");
		return ret;
	}

	ret = RB_SetAddrTypeFlag(rb_handle, 0, addr_flag);
	if( S_DONE != ret ) {
		LOGD("ArgFlashToolRBSetting: RB_SetAddrTypeFlag fail!");
		return ret;
	}

	return ret;
}

int tboot_1::FlashParameter_internal()
{
	int ret;

	//-1. Connect and get the HW information
	ArgFlashToolConnect(cn_arg, cn_result);
	unsigned char  com_port = (!g_bUsbMode) ? COM_PORT : GetUSBVCOMNumByPortName(m_strPort);

	//fill in OTP params
	OTP_T otp_arg;
	memset( &otp_arg, 0, sizeof(otp_arg));

	//connect
	int force_charge = /*g_bUsbModeWithBattery ? 0 : 1*/GetBatteryStatus();
	LOGD("FlashParameter_internal: force_charge(%d)", force_charge);
	ret = FlashTool_Connect( com_port, &cn_arg, &cn_result, NULL, &g_stopflag, &g_ft_handle,force_charge);
	if( S_DONE != ret ) {
		FlashTool_Disconnect( &g_ft_handle );
		return ret;
	}

	//OTP operations
	if (MainForm->rb_otp_Write->Checked && g_ParamDownloadConfig.m_otp_enable) {
		LOGD("[Parameter OTP]: OTP Write!");
        otp_arg.m_addr = g_ParamDownloadConfig.m_otp.m_addr;
    	otp_arg.m_data = g_ParamDownloadConfig.m_otp.m_data;
    	otp_arg.m_len  = g_ParamDownloadConfig.m_otp.m_len;        
      
      //check if OTP has been locked, if locked, pop msg to user, if not, continue...
           ret = FlashTool_OTP_LockCheckStatus(g_ft_handle);
          if(ret != S_DA_OTP_UNLOCKED)
          {
                 FlashTool_Disconnect(&g_ft_handle);
                 return ret;
          }
    
		switch(g_ParamDownloadConfig.m_otp_op){
		case OTP_WRITE:
            LOG("tboot_1::FlashParameter_internal(): FlashTool_OTP_Write(): OTP addr:%d, OTP len: %d, OTP data: %d",
                 otp_arg.m_addr, otp_arg.m_len, otp_arg.m_data);            
			ret = FlashTool_OTP_Write(g_ft_handle, &otp_arg);
			if(S_DONE != ret) {
				LOGW("FlashParameter_internal: FlashTool_OTP_Write fail!");
				FlashTool_Disconnect(&g_ft_handle);
				return ret;
			}
			break;

		case OTP_LOCK:
			ret = FlashTool_OTP_Lock(g_ft_handle);
			if(S_DONE != ret) {
				LOGW("FlashParameter_internal: FlashTool_OTP_Lock fail!");
				FlashTool_Disconnect(&g_ft_handle);
				return ret;
			}
			break;

		case OTP_WRITE_AND_LOCK:
			ret = FlashTool_OTP_Write(g_ft_handle, &otp_arg);
			if (S_DONE != ret) {
				LOGW("FlashParameter_internal: FlashTool_OTP_Write fail!");
				FlashTool_Disconnect(&g_ft_handle);
				return ret;
			}
			ret = FlashTool_OTP_Lock(g_ft_handle);
			if (S_DONE != ret) {
				LOGW("FlashParameter_internal: FlashTool_OTP_Lock fail!");
				FlashTool_Disconnect(&g_ft_handle);
				return ret;
			}
			break;

		default:
			assert(0);
		}

	}
	else if (MainForm->rb_otp_Read->Checked
			&& g_ParamReadbackConfig.m_otp_enable) {
    	otp_arg.m_addr = g_ParamReadbackConfig.m_otp.m_addr;
    	otp_arg.m_data = g_ParamReadbackConfig.m_otp.m_data;
    	otp_arg.m_len  = g_ParamReadbackConfig.m_otp.m_len;			
		//OTP read
		LOGD("[Parameter OTP]: OTP Read!");
        LOG("tboot_1::FlashParameter_internal(): FlashTool_OTP_Read(): OTP addr:%d, OTP len: %d, OTP data: %d",
            otp_arg.m_addr, otp_arg.m_len, otp_arg.m_data);  
		ret = FlashTool_OTP_Read(g_ft_handle, &otp_arg);
		if(S_DONE != ret) {
			LOGW("FlashParameter_internal: FlashTool_OTP_Read fail!");        
			FlashTool_Disconnect(&g_ft_handle);
			return ret;
		}

		//save to file.
		if( MainForm->SaveFile(g_ParamReadbackConfig.m_otp_filepath.c_str(), otp_arg.m_data,otp_arg.m_len) )
		{
			asMsg.printf("Fail to open \"%s\"!", g_ParamReadbackConfig.m_otp_filepath.c_str());
			Synchronize(ShowMsg);
		}

	}

	//disconnect
	ret = FlashTool_Disconnect(&g_ft_handle);
	if(S_DONE != ret) {
		LOGW("FlashParameter_internal: FlashTool_Disconnect fail!");
		return ret;
	}
	return S_DONE;
}
/******************************************************************************/
/* Write Memory Modules                                                        */
/*                                                                            */
/*                                                                            */
/******************************************************************************/
//---------------------------------------------------------------------------
static int __stdcall cb_write_memory_init(void *user_arg);
static int __stdcall cb_write_memory_progress( unsigned char percent,
                                  unsigned int  sent_bytes,
                                  unsigned int  total_bytes,
                                  void*         usr_arg);
//---------------------------------------------------------------------------
static int __stdcall cb_write_memory_init( void *usr_arg )
{

	tboot_1 *t = (tboot_1 *)usr_arg;

    t->StartTimer();

	t->progress_hint            = "Write raw data to flash now...";
    t->progress_forecolor       = (TColor) 0x0088A050;
	t->progress_percentage      = 0;
	t->progress_finished_bytes  = 0;

	t->bUpdateFinishBytes       = true;
	t->SyncInitProgress();

    return 0;
}
//---------------------------------------------------------------------------
static int __stdcall cb_write_memory_progress( unsigned char percent,
                                  unsigned int  sent_bytes,
                                  unsigned int  total_bytes,
                                  void*         usr_arg)
{

	tboot_1 *t = (tboot_1 *)usr_arg;

	t->progress_percentage      = percent;
	t->progress_finished_bytes  = sent_bytes;
	t->progress_total_bytes     = total_bytes;

	t->bUpdateFinishBytes       = true;

	t->SyncUpdateProgress();

    return 0;
}
//---------------------------------------------------------------------------
int tboot_1::ArgFlashToolWriteMemory(WriteFlashMemoryParameter  &wm_arg)
{
    memset(&wm_arg,  0, sizeof(wm_arg));

    wm_arg.m_flash_type             = (MainForm->rg_WM_Setting->ItemIndex == 0)?HW_STORAGE_NAND:HW_STORAGE_EMMC;
    wm_arg.m_addressing_mode        = AddressingMode_LogicalAddress;
    wm_arg.m_address                = g_WM_address;    // write start address
    wm_arg.m_container_length       = g_WM_container_length;    // write spare length
    wm_arg.m_input_mode             = InputMode_FromFile;
	wm_arg.m_program_mode = ProgramMode_PageOnly;
    wm_arg.m_input                  = g_WM_RawDataFilePath.c_str();
	// if m_input is a file, the length is zero because file length will be used as data length;
	// if m_input is a buffer, the length will be used as data length.
    wm_arg.m_input_length           = 0;

    cb_write_memory_init(this);

    wm_arg.m_cb_progress           = cb_write_memory_progress;
    wm_arg.m_cb_progress_arg       = this;

    return 0;

}

//---------------------------------------------------------------------------
int tboot_1::WriteMemory()
{
    //-1. Connect 
    ArgFlashToolConnect(cn_arg, cn_result);
    unsigned char  com_port = (!g_bUsbMode) ? COM_PORT : GetUSBVCOMNumByPortName(m_strPort);
    
    int  force_charge = /*g_bUsbModeWithBattery ? 0 : 1*/GetBatteryStatus();
    LOGD("%s: force_charge(%d)", __FUNC__, force_charge);
    int ret = FlashTool_Connect( com_port, &cn_arg, &cn_result, NULL, &g_stopflag, &g_ft_handle,force_charge);
    if( S_DONE != ret ) {
        LOG("tboot_1::WriteMemory(): FlashTool_Connect failed.");
        FlashTool_Disconnect( &g_ft_handle );
        return ret;
    }

    //- 2. if SRAM was not found, try to detect DRAM
    if ( S_DONE != cn_result.m_da_report.m_ext_ram_ret ) {
        ret = EnableDRAM( &cn_result );
        if ( S_DONE != ret ) {
			LOG("tboot_1::WriteMemory(): EnableDRAM failed.");
            FlashTool_Disconnect( &g_ft_handle );
            return ret;
        }
    }

    //- 3. Write raw data to memory
    WriteFlashMemoryParameter       wm_arg;
    ArgFlashToolWriteMemory( wm_arg );
	LOG("tboot_1::WriteMemory(): Dump WriteFlashMemoryParameter arg...");
	LOG("tboot_1::WriteMemory(): m_flash_type(%d)", wm_arg.m_flash_type);
	LOG("tboot_1::WriteMemory(): m_addressing_mode(%d)", wm_arg.m_addressing_mode);
	LOG("tboot_1::WriteMemory(): m_address(0x%I64x)", wm_arg.m_address);
	LOG("tboot_1::WriteMemory(): m_container_length(0x%x)", wm_arg.m_container_length);
	LOG("tboot_1::WriteMemory(): m_input_mode(%d)", wm_arg.m_input_mode);
	LOG("tboot_1::WriteMemory(): m_input(%s)", wm_arg.m_input);  
	LOG("tboot_1::WriteMemory(): m_input_length(0x%x)", wm_arg.m_input_length);

    ret = FlashTool_WriteFlashMemory( g_ft_handle, &wm_arg );
    if( S_DONE != ret ) {
        LOG("tboot_1::WriteMemory(): FlashTool_WriteFlashMemory failed.");
        FlashTool_Disconnect( &g_ft_handle );
        return ret;
    }

    //- N. Disconnect
    FlashTool_Disconnect( &g_ft_handle );

    return ret;
}

/******************************************************************************/
/* Read Software Version Modules                                  */
/*                                                                            */
/*                                                                            */
/******************************************************************************/
//---------------------------------------------------------------------------
int tboot_1::ArgFlashToolRBToBufSetting(RB_HANDLE_T rb_handle, const RB_INFO &rb_info, char* buf, unsigned int buf_len)
{
	int ret = 0;

	//RB_Append_ReadToBuf(RB_HANDLE_T  rb_handle, unsigned int rb_addr, unsigned int rb_len, char *buf, unsigned int buf_len);
	ret = RB_Append_ReadToBuf(rb_handle, rb_info.readback_addr, rb_info.readback_len, buf, buf_len);
	if( S_DONE != ret ) {
		LOGD("ERROR: ArgFlashToolRBToBufSetting(): RB_Append_ReadToBuf() failed!");
		return ret;
	}

	ret = RB_SetReadbackFlag(rb_handle, 0, rb_info.m_read_flag);
	if( S_DONE != ret ) {
		LOGD("ERROR: ArgFlashToolRBToBufSetting(): RB_SetReadbackFlag() failed!");
		return ret;
	}

	return ret;
}

//---------------------------------------------------------------------------
int tboot_1::ReadbackPartitionToBuffer(const RB_INFO &rb_info, const bool isDynamicLayout, const RB_HANDLE_T rb_handle, char* buf, unsigned int buf_len)
{
    int ret = 0;

    FlashTool_Readback_Arg rb_arg;
    FlashTool_Readback_Result rb_result;

    ArgFlashToolAdvancedReadback(rb_arg, rb_result, isDynamicLayout, rb_handle);
    if ( S_DONE != ret ) {
		LOGD("ERROR: ReadbackPartitionToBuffer(): ArgFlashToolAdvancedReadback() fail!");
        return ret;
    }

	ret = ArgFlashToolRBToBufSetting(rb_handle, rb_info, buf, buf_len);
    if ( S_DONE != ret ) {
		LOGD("ERROR: ReadbackPartitionToBuffer(): ArgFlashToolRBToBufSetting() failed!");
        return ret;
    } 
    
    ret = FlashTool_Readback(g_ft_handle, &rb_arg, &rb_result);
    if ( S_DONE != ret ) {
        LOGD("ERROR: ReadbackPartitionToBuffer(): FlashTool_Readback() fail!");
        return ret;
    }

    ret = RB_Delete(rb_handle, 0);
    if ( S_DONE != ret ) {
        LOGD("ERROR: ReadbackPartitionToBuffer(): RB_Delete() fail!");
        return ret;
    } 

	ret = FlashTool_Disconnect( &g_ft_handle );
	if ( S_DONE != ret) {
		LOGD("ERROR: ReadbackPartitionToBuffer(): FlashTool_Disconnect() failed!");
	}

	return ret;
}

//---------------------------------------------------------------------------
int tboot_1::FlashToolReadSWVersion(void)
{
	ErrorLookup::SetErrorCodeMode(BROM);
	int ret = 0;
    PART_INFO part_info;
    memset(&part_info, 0, sizeof(part_info));
	RB_INFO rb_info;
	memset(&rb_info, 0, sizeof(rb_info));
    bool isDynamic = false;

    ArgFlashToolConnect(cn_arg, cn_result);
	unsigned char  com_port = (!g_bUsbMode) ? COM_PORT : GetUSBVCOMNumByPortName(m_strPort);
	LOG("FlashToolReadSWVersion():Getting com port(%d), is USB mode(%d)",com_port,g_bUsbMode);

    int force_charge = /*g_bUsbModeWithBattery ? 0 : 1*/GetBatteryStatus();
    LOGD("FlashToolReadSWVersion: force_charge(%d)", force_charge);
    ret = FlashTool_Connect( com_port, &cn_arg, &cn_result, NULL, &g_stopflag, &g_ft_handle, force_charge);
    if( S_DONE != ret ) {
		LOGD("ERROR: tboot_1::FlashToolReadSWVersion(): FlashTool_Connect fail!");
    	return ret;
    }
    
    g_platform_info.setChipName(cn_result.m_da_report.m_bbchip_name);
    if( g_platform_info.getPlatformConfig().supportLogicalAddress()) {
        isDynamic = true; //Smart Phone Platform after MT6516 will apply dynamic layout
    } else {
        isDynamic = false;
    }   
   
	ret = GetPartitionInfo(g_ft_handle, BootImgName, part_info);
	if ( S_DONE != ret ) {
		LOG("ERROR: tboot_1::FlashToolReadSWVersion(): Obtain Boot image start address and length failed!");
		return ret;
	} else {
	    rb_info.readback_addr = part_info.begin_addr;
		rb_info.readback_len = part_info.image_length;
		LOG("tboot_1::FlashToolReadSWVersion(): Boot image readback addr(0x%016I64X), length(0x%X)", 
			rb_info.readback_addr, rb_info.readback_len);
	}

	//Page size alignment should be 4096
	const unsigned int BUF_LEN =  4096;
	char szBuf[BUF_LEN] = {'\0'};

	rb_info.m_read_flag = NUTL_READ_PAGE_ONLY;
      rb_info.enable = _TRUE;
      rb_info.index = 0;
	rb_info.readback_addr = part_info.begin_addr;
	rb_info.readback_len = BUF_LEN;
      ret  = ReadbackPartitionToBuffer( rb_info, isDynamic, g_SW_Ver_RB_HANDLE, szBuf, BUF_LEN);
	if( S_DONE != ret ) {
		LOG("ERROR: tboot_1::FlashToolReadSWVersion(): ReadbackPartitionToBuffer() failed!");		
		return ret;
	}

	const unsigned int SW_VERSION_OFFSET_IN_BOOT_HDR = 48;
	const unsigned int SW_LEN = 17;
	char szSW[SW_LEN] = "";
	//Size of name [BOOT_NAME_SIZE] in boot_img_hdr is 16 Bytes
    memcpy(szSW, 
		(szBuf + SW_VERSION_OFFSET_IN_BOOT_HDR),
        SW_LEN-1);
	LOG("tboot_1::FlashToolReadSWVersion(): Software version(%s).", szSW);

	return S_DONE;
}

//---------------------------------------------------------------------------
//DA Firmware Upgrade under DL Mode
//---------------------------------------------------------------------------
int tboot_1::SetBinRegionByScatterFile(DL_HANDLE_T p_dl_dandle,
									 WriteFlashMemoryParameter *p_write_flash_memory_para,
									 BackupItem &backup_item,
									 const string & binregion_file)
{
    assert(p_dl_dandle != NULL);
	LOG("tboot_1::SetBinRegionByScatterFile(): partition name(%s), backup path(%s).", backup_item.partition_name().c_str(), binregion_file.c_str());
    ErrorLookup::SetErrorCodeMode(FLASHTOOL);
	if ( !FileUtils::IsFileExist(binregion_file)) {
		     LOG("ERROR:tboot_1::SetBinRegionByScatterFile(): data file(%s) is not found!",  binregion_file.c_str());
		     return FT_UPGRADE_FILE_NOT_EXSIT;
	} else {		
			p_write_flash_memory_para->m_flash_type = g_platform_info.getFlashToolStorageConfig().GetStorageType();
			p_write_flash_memory_para->m_addressing_mode = AddressingMode_LogicalAddress;
			p_write_flash_memory_para->m_address = backup_item.start_addr();    // write start address
			p_write_flash_memory_para->m_container_length = 0;    // write spare length
			p_write_flash_memory_para->m_input_mode = InputMode_FromFile;

                   switch(backup_item.rom_type())
                   {
                   case YAFFS_IMG:
                       p_write_flash_memory_para->m_program_mode = ProgramMode_PageSpare;	
                       break;
                   case NORMAL_ROM:
                       p_write_flash_memory_para->m_program_mode = ProgramMode_PageOnly;	
                       break;
                   default:
                       p_write_flash_memory_para->m_program_mode = ProgramMode_PageOnly;	
                       break;
                   }     
                   
			p_write_flash_memory_para->m_input = binregion_file.c_str();	
			// if m_input is a file, the length is zero because file length will be used as data length;
			// if m_input is a buffer, the length will be used as data length.
			p_write_flash_memory_para->m_input_length  = 0;
			cb_write_memory_init(this);
			p_write_flash_memory_para->m_cb_progress = cb_write_memory_progress;
			p_write_flash_memory_para->m_cb_progress_arg = this;

			LOGD("restore from file(%s)", p_write_flash_memory_para->m_input);
		} 
	
	ErrorLookup::SetErrorCodeMode(BROM);

	LOG("tboot_1::SetBinRegionByScatterFile():Dumping image: start address(0x%x), partition path(%s).",
		p_write_flash_memory_para->m_address, p_write_flash_memory_para->m_input);

    return S_DONE;
}

//---------------------------------------------------------------------------
int tboot_1::DABackupFormatDownloadRestore()
{
	ErrorLookup::SetErrorCodeMode(BROM);
	int ret = 0;
	
    //share_prt manage connect and disconnect
	ArgFlashToolConnect(cn_arg, cn_result);
	unsigned char  com_port = (!g_bUsbMode) ? COM_PORT : GetUSBVCOMNumByPortName(m_strPort);
	LOG("tboot_1::DABackupFormatDownloadRestore(): Getting com port(%d), is USB mode(%d)",com_port,g_bUsbMode);
	int force_charge = /*g_bUsbModeWithBattery ? 0 : 1*/GetBatteryStatus();
	LOGD("DABackupFormatDownloadRestore: force_charge(%d).", force_charge);
      SharedPtr<CommandConnect> cmd_conn = SharedPtr<CommandConnect>(new BromCommandConnect(
		com_port, &cn_arg, &cn_result, NULL, &g_stopflag, &g_ft_handle, force_charge));
	CommandConnect *p_cmd_conn = cmd_conn.get();	
	if ( !p_cmd_conn->is_connect() ) {
		ret = p_cmd_conn->connect_result();
		LOG("ERROR: tboot_1::DABackupFormatDownloadRestore(): BromCommandConnect() failed, result code(%d).", ret);
		return ret;
	}

	g_platform_info.setChipName(cn_result.m_da_report.m_bbchip_name);
	LOG("tboot_1::DABackupFormatDownloadRestore(): The load to be downloadeded is %s.", g_platform_info.getLoadPlatformName().c_str());
	LOG("tboot_1::DABackupFormatDownloadRestore(): Target platform by DA report is %s.", g_platform_info.getTargetPlatformName().c_str());    
   
	ErrorLookup::SetErrorCodeMode(FLASHTOOL);
	if (!g_platform_info.isPlatformMatched()) {
		return FT_DL_PLATFORM_ERROR;
	}
    ErrorLookup::SetErrorCodeMode(BROM);

    bool isDynamicLayout = false;
    if( g_platform_info.getPlatformConfig().supportLogicalAddress()) {
        isDynamicLayout = true; //Smart Phone Platform after MT6516 will apply dynamic layout
    } else {
        isDynamicLayout = false;
    }

    
	//get usb speed status
      FlashTool_USB_Status_Result usb_status_result;
      ret = GetUSBSpeedStatus(g_ft_handle, usb_status_result);
	if(S_DONE != ret)
	{
          LOGE("Get USB Speed Status fail! ret(%d)", ret);
	    FlashTool_Disconnect(&g_ft_handle);
	    return ret;
	}
	
	//Switch Speed if platform supports and user wants to
	if((g_platform_info.getPlatformConfig().supportUSBHighSpeed()) &&
        g_bSwitchSpeed && (usb_status_result.usb_speed_status == USB_FULL_SPEED)) {
        #if 0
        ret = DASwitchSpeed(g_ft_handle, g_bDAEnableHS);
		if ( S_DONE != ret ) {
			//FlashTool_Disconnect(&g_ft_handle);
			LOG("tboot_1::DABackupFormatDownloadRestore(): DASwitchSpeed() failed, error code(%d).", ret);
			return ret;
		}
		#endif
		Synchronize(UpdateUSBVCOMInfo);
             	if (!Swith2DAHighSpeed(&g_stopflag, m_strSymbolic, m_strPort, g_ft_handle, true, 30)) {
                FlashTool_Disconnect( &g_ft_handle );
				LOGE("Search and switch to DA HS USB Failed!");
                return FT_FIND_USB_ERROR;
			} else {			      
                          speed_status = "USB_FULL_SPEED->USB_HIGH_SPEED";
				Synchronize(UpdateUSBVCOMInfo);
			}
	}
       
       //readback

	ErrorLookup::SetErrorCodeMode(FLASHTOOL);
     	NandLayoutParameter nand_mgr(g_pCurNode->m_dl_handle, g_ft_handle, NandLayoutParameter::kVitaltemsCount);
      if(!nand_mgr.is_load_layout_map_ready())
      	{
      	     LOGD("Get PMT fail.");
             ret = FT_UPGRADE_GET_PMT_FAIL;
            return ret;
	} 

      std::string bin_region_folder;//BinRegion folder,  "<app dir>/NvramBackup/<chip-id>"
      std::string binregion_file;
      bin_region_folder = FileUtils::ComposeDirNameByChipID(cn_result.m_da_report.m_random_id, kChipIDLength);

      BackupConfig backupConfig(bin_region_folder);
      BackupItem backupItem;              
      std::list<ROM_INFO> backupItemTable;
      	  
       ret = backupConfig.InitBackupInfoTable(); 
       backupItemTable = backupConfig.backup_roms();
      	   
	if (!nand_mgr.is_nand_layout_matched()) {

        LOGD("Layout has been changed, begin backup...");
	
      if(ret != S_DONE )
      {
              LOGE("Initial Backup Setting Table fail!");
	       return ret;
      }     

      for(std::list<ROM_INFO>::iterator it = backupItemTable.begin();
	     it != backupItemTable.end(); ++it)	
     {
               ErrorLookup::SetErrorCodeMode(FLASHTOOL);
               ret = nand_mgr.isSizeChanged((*it).name);
               if(ret != FT_SUCCESS)
               {
                       return ret;
               }
             
               backupConfig.QueryBackupItemByPartitionName((*it).name, &backupItem);
	   
               LOGD("partition_name(%s), file_path(%s), start_addr(0x%I64X), length(0x%X)",
               backupItem.partition_name().c_str(), backupItem.file_path().c_str(),backupItem.start_addr(), backupItem.length());
        
              ret = BackupWithoutConnection(backupItem, bin_region_folder, isDynamicLayout);
		 if(ret != S_DONE)
		 {
                   LOGE("Readback fail. partition name(%s).", backupItem.partition_name().c_str());
			return ret;
		 }
     }     	

}
	
	//format
     LOG("%s(): Begin to enter format flow...", __FUNC__);
  
    ret = FormatWithoutConnection(nand_mgr, backupConfig);
    if(ret != S_DONE)
    {
         LOGE("%s(): FlashTool_Format fail!", __FUNC__);
	  return ret;
    }   

    //Download
   LOG("tboot_1::DABackupFormatDownloadRestore(): Download begin...");
    FlashTool_Download_Arg fdl_arg;
    FlashTool_Download_Result fdl_res;    
    ArgFlashToolAdvancedDownload(fdl_arg, fdl_res);
	ret = FlashTool_Download(g_ft_handle, &fdl_arg, &fdl_res);
	if ( S_DONE != ret ) {
		LOG("ERROR: tboot_1::DABackupFormatDownloadRestore(): FlashTool_Download() failed!");
		return ret;
	}

     //Restore
    ErrorLookup::SetErrorCodeMode(FLASHTOOL);
    
     //Get partition Info again, new PMT is used.
    ret = backupConfig.InitBackupInfoTable();
	
     if(ret != S_DONE )
     {
       LOGE("Initial Backup Setting Table fail!");
	 return ret;
     }
     ErrorLookup::SetErrorCodeMode(BROM);
	 
     backupItemTable = backupConfig.backup_roms();
     for(std::list<ROM_INFO>::iterator it = backupItemTable.begin();
	     it != backupItemTable.end(); ++it)	
     {
           if(nand_mgr.SearchPartitionByName((*it).name))	 
          {
             backupConfig.QueryBackupItemByPartitionName((*it).name, &backupItem);
	       if (CheckIfBackupFileExist(bin_region_folder, backupItem)) {
		//Write partition back
		LOG("tboot_1::DABackupFormatDownloadRestore(): Write partition back begin...");
		WriteFlashMemoryParameter wm_arg;
		std::string filePath(backupItem.file_path());
		ret = SetBinRegionByScatterFile(g_pCurNode->m_dl_handle, &wm_arg, backupItem, filePath);
		if ( S_DONE != ret ) {
			LOG("ERROR: tboot_1::DABackupFormatDownloadRestore(): SetBinRegionByScatterFile() failed!");
			return ret;
		}	    
  
       	ret = FlashTool_WriteFlashMemory( g_ft_handle, &wm_arg );

		if( S_DONE != ret ) {
			LOG("ERROR: tboot_1::DABackupFormatDownloadRestore(): FlashTool_WriteFlashMemory() failed!");
			return ret;
		} 
	     }
	   }else if(((*it), NvramName.c_str()) != NULL ){
	            LOGD("NVRAM could not find in pre-load.");
                  return FT_UPGRADE_BACKUP_ROM_NOT_EXSIT;
	   }else{
	            LOGW("partition(%s) can not be found in pre-load, skip restore.", (*it).name);
                  continue;
	   }
     }
	
     LOG("tboot_1::DABackupFormatDownloadRestore(): Remove diretory %s after restored.", bin_region_folder.c_str());
     if (!FileUtils::DeleteDirectory(bin_region_folder)) {
	    LOG("tboot_1::DABackupFormatDownloadRestore(): : Remove diretory failed.");
     }	

     //Add auto reset for auto polling
     	if(!ToolInfo::IsCustomerVer()) {
		FlashTool_EnableWDT_Arg wdt_arg;
		FlashTool_EnableWDT_Arg *p_wdt_arg = &wdt_arg;
		ArgFlashToolWatchDog(p_wdt_arg);
		ret = FlashTool_EnableWatchDogTimeout(g_ft_handle, p_wdt_arg);
		if(S_DONE != ret) {			
			LOGD("tboot_1::DABackupFormatDownloadRestore(): FlashTool_EnableWatchDogTimeout fail!");
			return ret;
		}
	}
		
	return ret;
}

int tboot_1::BackupWithoutConnection(BackupItem &backupItem, const std::string &backupFolder, bool isDynamic)
{
       int ret = S_DONE;

		//check backup dir first to figure out if a previous backup has been done.
		ErrorLookup::SetErrorCodeMode(FLASHTOOL);
		if(!FileUtils::MakeParentBackupDir()) {
			LOG("ERROR: %s(): MakeParentBackupDir() failed!", __FUNC__);
			return FT_UPGRADE_DIR_CREATE_FAIL;
		}

		if(!CheckIfBackupFileExist(backupFolder, backupItem))
		{		
			//read back NVRAM bin region
			LOG("%s(): Reading back %s bin region from target...", __FUNC__, backupItem.partition_name());
			RB_INFO rb_info;
			memset(&rb_info, 0, sizeof(RB_INFO));

		      rb_info.readback_addr = backupItem.start_addr();
		      rb_info.readback_len = backupItem.length();
                   memcpy(rb_info.filepath, backupItem.file_path().c_str(), backupItem.file_path().size());

                   switch(backupItem.rom_type())
                   {
                   case YAFFS_IMG:
                       rb_info.m_read_flag = NUTL_READ_PAGE_SPARE_WITH_ECCDECODE;
                       break;
                   case NORMAL_ROM:
                       rb_info.m_read_flag = NUTL_READ_PAGE_ONLY;
                       break;
                   default:
                       rb_info.m_read_flag = NUTL_READ_PAGE_ONLY;
                       break;
                   }        
                   
                   ErrorLookup::SetErrorCodeMode(BROM);

			ret = ReadbackPartitioWithoutDisconnect(backupFolder,
					BIN_REGION_FILE_NAME,
					isDynamic,
					rb_info);
			if ( S_DONE != ret ) {
				LOGE("BackupWithoutConnection() failed! ret (%d)", ret);
				return ret;
			} else {
				//compute & save checksum file
				unsigned char file_chksum = 0;
				FileUtils::ComputeCheckSum(backupItem.file_path(), file_chksum);
				FileUtils::SaveCheckSum(backupItem.chksum_file(), file_chksum);
				LOG("%s(): Compute & Save Bin Region checksum: %d", __FUNC__, file_chksum);
			}
		}

	return ret;
}             

int tboot_1::FormatWithoutConnection(NandLayoutParameter &para, BackupConfig &config)
{
    int ret = S_DONE;

    ErrorLookup::SetErrorCodeMode(BROM);
    FirmwareUpgradeConfig fu_config;
    unsigned int rom_count;
    PART_INFO part_info[MAX_LOAD_SECTIONS];        
	
    bool is_layout_matched = para.CompareIsNandLayoutMatched() ;
    LOGD("is_layout_matched(%d), skip backup partitions", is_layout_matched);		
   
    PartitionExistStatus status = PARTITION_NOT_EXIST;	
    GetRomInfoByName(g_pCurNode->m_dl_handle, "FAT", status);    
    LOG("%s(): FAT status is(%d)", __FUNC__, status);

     if (!FlashTool_ReadPartitionCount(g_ft_handle, &rom_count)) {
        if( !FlashTool_ReadPartitionInfo(g_ft_handle, part_info, MAX_LOAD_SECTIONS) ) {
			
            for(unsigned int i=0; i<rom_count; i++){
        
               std::string name_str = part_info[i].name;
					
	         if(status == PARTITION_NOT_EXIST || status == PARTITION_ENABLE 
	   	                                                || status == PARTITION_INVISIBLE)
	         {			
	               if(IsPartitionShouldFmt(config, name_str, is_layout_matched))
	               {
                           fu_config.AddSettings(CreateRegionFormatSetting(name_str));
			  }
		       
	         }
                if(status == PARTITION_DISABLE){
			  if(is_layout_matched){
                          if(name_str.find("FAT") == std::string::npos//skip FAT and bootloaders
				     &&IsPartitionShouldFmt(config, name_str, is_layout_matched)) 
			      {
					 fu_config.AddSettings(CreateRegionFormatSetting(name_str));
			      }
			   }else{
                                  ErrorLookup::SetErrorCodeMode(FLASHTOOL);
                                  LOG("FAT is uncheck and layout has been changed.");
               	              return FT_UPGRADE_LAYOUT_CHANGED;        
		         }		
		   }			   
		}	  			 
	     }            	
        }
     
        ret = fu_config.CreateCommand(para)->Execute();
	
    return ret;
}

bool tboot_1::IsPartitionShouldFmt(BackupConfig &config, const std::string &name, bool layoutMatch)
{
      bool shouldFmt = true;

      if(config.backup_roms().size() == 0)
      	{
             return false;
	}

      if(name.find("PMT") == std::string::npos //skip PMT
	   && name.find("BMT") == std::string::npos // skip BMT 
	   && name.find("OTP") == std::string::npos )//skip RSV region) 
	{
	     if(layoutMatch)
	    {     		

               if(name.find("PRELOADER") != std::string::npos ||
                    name.find("DSP_BL") != std::string::npos)
               {
                    return false;
               }
        
               std::list<ROM_INFO> partitions = config.backup_roms();
	         for(std::list<ROM_INFO>::iterator it = partitions.begin();
		        it != partitions.end(); ++it)
              {
                     if(name.find((*it).name) != std::string::npos)
                    {
                       LOGD("skip (%s)", name.c_str());	
                       shouldFmt = false;
		          break;
	             }
	       }
	    } 
          else if(!g_platform_info.getPlatformConfig().supportAutoFormatAll())
          {
               //add for workaround for brom usb issue.
                if(name.find("PRELOADER") != std::string::npos ||
                    name.find("DSP_BL") != std::string::npos)
               {
                    return false;
               }
          }

      	}
	else
	{
             shouldFmt = false;
	}
      return shouldFmt;
}

/******************************************************************************/
/* Read Product Info Modules                                        */
/*                                                                            */
/*                                                                            */
/******************************************************************************/
int tboot_1::FlashToolReadProductInfo(void)
{
	ErrorLookup::SetErrorCodeMode(BROM);
	int ret = 0;
    RB_INFO rb_info;
    bool isDynamicLayout = false;
	const std::string kProductInfoFolderName("ProductInfo");
    std::string pro_info_folder;  //pro_info folder,  "<app dir>/ProductInfo/<chip-id>"
    
    ret = Conn2ObtianPartitionRegion(kProductInfoName, rb_info, isDynamicLayout);
    if ( S_DONE != ret ) {
        FlashTool_Disconnect(&g_ft_handle);
		LOG("ERROR: FlashToolReadProductInfo():  Conn2ObtianPartitionRegion() failed, error code(%d)!", ret);        
        return ret;
    }     

    ErrorLookup::SetErrorCodeMode(FLASHTOOL);
	if(!FileUtils::MakeParentBackupDir(kProductInfoFolderName)) {
        FlashTool_Disconnect(&g_ft_handle);
		LOG("ERROR: FlashToolReadProductInfo: %s(): MakeParentBackupDir(%s) failed!", __FUNC__, kProductInfoFolderName.c_str());
		return FT_UPGRADE_DIR_CREATE_FAIL;		
	}
    pro_info_folder = FileUtils::ComposeDirNameByChipID(cn_result.m_da_report.m_random_id, kChipIDLength, kProductInfoFolderName);
    E_CHECK_DIR_STATUS dir_status = FileUtils::CheckDirectory(pro_info_folder);
	LOG("tboot_1::ReadbackPartitioWithoutDisconnect: Got backup dir by Chip ID, backup folder: %s", pro_info_folder.c_str());
	if ( CREATE_DIR_FAIL == dir_status ) {
        FlashTool_Disconnect(&g_ft_handle);
		LOG("ERROR: %s(): create dir (%s) falied!", __FUNC__, pro_info_folder.c_str());
		return FT_UPGRADE_DIR_CREATE_FAIL;
	}
	ErrorLookup::SetErrorCodeMode(BROM);

    FlashTool_Readback_Arg rb_arg;
    FlashTool_Readback_Result rb_result;
	RBHandleManager readback_handler;
    ret = ArgFlashToolAdvancedReadback(rb_arg, rb_result, isDynamicLayout, readback_handler.rb_handle());
    if ( S_DONE != ret ) {
        FlashTool_Disconnect(&g_ft_handle);
		LOGD("ERROR: FlashToolReadProductInfo: FlashTool_Readback fail!");
        return ret;
    }

    rb_info.m_read_flag = NUTL_READ_PAGE_ONLY;
    rb_info.enable = _TRUE;
    rb_info.index = 0;
	strcpy(rb_info.filepath, string(pro_info_folder + "\\" + std::string(kProductInfoBinName)).c_str());

    ret = ArgFlashToolRBSetting(readback_handler.rb_handle(), rb_info, NUTL_ADDR_LOGICAL);
    if ( S_DONE != ret ) {
		FlashTool_Disconnect(&g_ft_handle);
        LOGD("FlashToolReadProductInfo: ArgFlashToolRBSetting fail!");
        return ret;
    } 

    LOG("Dumping readback handle before FlashTool_Readback.");
    readback_handler.Dump();

    ret = FlashTool_Readback(g_ft_handle, &rb_arg, &rb_result);
    if ( S_DONE != ret ) {
		FlashTool_Disconnect(&g_ft_handle);
        LOGD("FlashToolReadProductInfo: FlashTool_Readback fail!");
		return ret;
	}

	ret = FlashTool_Disconnect(&g_ft_handle);

	return S_DONE;
}

//---------------------------------------------------------------------------
//--------------------------------Certification file download-----------------------
int tboot_1::ArgFlashToolDLCert(SCERT_ARG_S &cdl_arg, void *m_cb_in_brom_stage_arg)
{
      memset( &cdl_arg, 0, sizeof(cdl_arg));
      cdl_arg.m_bbchip_type = (g_platform_info.getLoadPlatformName() == "MT6516") ? MT6516_AP : AUTO_DETECT_BBCHIP;
      LOGD("bbchip_type(%d).", cdl_arg.m_bbchip_type);
      cdl_arg.m_ext_clock = g_EXT_CLOCK;	  
      cdl_arg.m_ms_boot_timeout            = BOOT_INFINITE;
      cdl_arg.m_max_start_cmd_retry_count  = g_MaxBromStartCmdRetryCount;

      // Initialization for Edge Moudle
    // This callback function will be invoke after COM port is opened
	// You can do some initialization by using this callback function.
	cdl_arg.m_cb_com_init_stage          = cb_com_init_stage;
	cdl_arg.m_cb_com_init_stage_arg      = this;

    // This callback function will be invoke after BootROM start cmd is passed.
	// You can issue other BootROM command by brom_handle and hCOM which
    // provides callback arguments,or do whatever you want otherwise.
       cdl_arg.m_cb_in_brom_stage           = cb_in_brom_stage;
	cdl_arg.m_cb_in_brom_stage_arg       = m_cb_in_brom_stage_arg;

	cdl_arg.m_scert_handle = g_SCERT_HANDLE;


	return 0;

}

//------------------------------------------------------------------------------
int tboot_1::DLCertification(void)
{
    ErrorLookup::SetErrorCodeMode(BROM);
    
    int ret = 0;
    //set it to false to avoid side effect for other operations.
    if(g_bDLCert)
		g_bDLCert = false;

    LOGD("DL Certification begain...");
  
   //Search Brom port	
    Synchronize(UpdateUSBVCOMInfo);
    if (ScanUSBPort4DownloadCert(&g_stopflag, m_strSymbolic, m_strPort)) {
	LOGD("g_stopflag(%d).", g_stopflag);
	LOGD("USB is found, port name(%s), symbolic name(%s).", m_strPort.c_str(), m_strSymbolic.c_str());
	Synchronize(UpdateUSBVCOMInfo);
    } else {
		LOGE("Search USB port failed!");
		return FT_FIND_USB_ERROR;
   }

   //Obtain COM Handle
   unsigned int com_port = GetUSBVCOMNumByPortName(m_strPort);
   LOGD("Cert Brom COM Port Number(%d).", com_port);
   
   HANDLE  hCOM = INVALID_HANDLE_VALUE;
   com_sentry	s( hCOM, com_port );

   if( INVALID_HANDLE_VALUE == hCOM ) {
		// stop timer
		Synchronize(StopTimer);
		asMsg = "Open COM" + IntToStr(com_port) + "failed!";
		Synchronize( ShowMsg );
    	return FT_FIND_USB_ERROR;
	} 

   //Begin to send...
   SCERT_ARG_S cdl_arg;
   BOOT_RESULT cdl_res;
   ArgFlashToolDLCert(cdl_arg, &cdl_res);
   ret = Brom_SendSCERT(hCOM,  &cdl_arg,  &cdl_res, &g_stopflag);
   if(S_DONE != ret)  
   {
     		Synchronize(StopTimer);
		if( BOOT_STOP == g_stopflag ) {

                    return FT_USER_PRESS_STOP_BUTTON;
		}

    // show flash tool final Result
    if (ALL_IMG_LOCKED != g_ParamImageLockAll )
    {
        ShowFlashToolFinalResult ( ret );
    }
    g_ParamImageLockAll = NONE_IMG_LOCKED;
		
   }

  return ret;
   
}

//---------------------------------------------------------------------------
//===========================SCI Clone=========================
int tboot_1::SCIReadback()
{
      int ret;

	//-1. Connect and get the HW information
	ArgFlashToolConnect(cn_arg, cn_result);
	unsigned char  com_port = (!g_bUsbMode) ? COM_PORT : GetUSBVCOMNumByPortName(m_strPort);


	int force_charge = /*g_bUsbModeWithBattery ? 0 : 1*/GetBatteryStatus();
	LOGD("%s: force_charge(%d)", __FUNC__, force_charge);
	ret = FlashTool_Connect( com_port, &cn_arg, &cn_result, NULL, &g_stopflag, &g_ft_handle,force_charge);
	if( S_DONE != ret ) {
		FlashTool_Disconnect( &g_ft_handle );
		return ret;
	}

	bool isDynamicLayout = true;
	g_platform_info.setChipName(cn_result.m_da_report.m_bbchip_name);
	
	ErrorLookup::SetErrorCodeMode(BROM);
	Synchronize(UpdateUSBVCOMInfo);
           
	//get usb speed status
      FlashTool_USB_Status_Result usb_status_result;
      ret = GetUSBSpeedStatus(g_ft_handle, usb_status_result);
	if(S_DONE != ret)
	{
          LOGE("Get USB Speed Status fail! ret(%d)", ret);
	    FlashTool_Disconnect(&g_ft_handle);
	    return ret;
	}
	
	//Switch Speed if platform supports and user wants to
	if((g_platform_info.getPlatformConfig().supportUSBHighSpeed()) &&
        g_bSwitchSpeed && (usb_status_result.usb_speed_status == USB_FULL_SPEED)){
	
	if (!Swith2DAHighSpeed(&g_stopflag, m_strSymbolic, m_strPort, g_ft_handle, true, 30))
	{
            FlashTool_Disconnect( &g_ft_handle );
	      LOGE("Search and switch to DA HS USB Failed!");
             return FT_FIND_USB_ERROR;
	} else {	      
             speed_status= "USB_FULL_SPEED->USB_HIGH_SPEED";
		Synchronize(UpdateUSBVCOMInfo);
	}
   }
	ErrorLookup::SetErrorCodeMode(BROM);

	//Set Readback package length and Enable DRAM
	
      ret = RB_SetPacketLength(g_CLONE_RB_HANDLE, kRBPkgLen);
	if(S_DONE != ret)
	{
          LOGE("Set Readback package length fail! ret(%d)", ret);
	    FlashTool_Disconnect(&g_ft_handle);
	    return ret;
	}

      if(usb_status_result.usb_speed_status== USB_FULL_SPEED)
	{
	    LOGD("USB_FULL_SPEED, Enable DRAM...");
	    ret = EnableDRAM(&cn_result);
          if(S_DONE != ret)
	   {
              LOGE("Enable DRAM fail! ret(%d)", ret);
	        FlashTool_Disconnect(&g_ft_handle);
	        return ret;
	   }
       }

     //Readback PMT
	unsigned int rom_count(0);
        PART_INFO* p_part_info = NULL;
	CloneInfoItem clone_info;

        ret = FlashTool_ReadPartitionCount(g_ft_handle, &rom_count);
        if( S_DONE != ret ) 
	 {
		LOG("ERROR: %s():  FlashTool_ReadPartitionCount() failed, error code is(%d).", __FUNC__, ret);
	      FlashTool_Disconnect( &g_ft_handle );
		return ret;
        }
		
       //Create Readback files folder
       std::string sci_files_folder;
       ErrorLookup::SetErrorCodeMode(FLASHTOOL);
	if(!FileUtils::MakeParentBackupDir(SCI_FILE_FOLDER)) {
	              FlashTool_Disconnect(&g_ft_handle);
	              LOG("ERROR: %s(): MakeParentBackupDir() failed!", __FUNC__);
			return FT_UPGRADE_DIR_CREATE_FAIL;
	}

       std::string parentDir = FileUtils::GetAppDirectory() + "\\" + SCI_FILE_FOLDER;
	std::string prefix = "SCI_Files_";

       sci_files_folder = FileUtils::ComposeDirNameByTimeStamp(parentDir, prefix);

       E_CHECK_DIR_STATUS dirStatus = FileUtils::CheckDirectory(sci_files_folder);
	LOG("%s:Got backup dir by timestamp, readback folder: %s", __FUNC__,  sci_files_folder.c_str());
	
       //error handling of creating readback folder
       if ( CREATE_DIR_FAIL == dirStatus ) 
	{
            FlashTool_Disconnect(&g_ft_handle);
	
            LOGE("[Hint] Create reaback directory: %s fails!");
             ret = FT_UPGRADE_DIR_CREATE_FAIL;
             return ret;
        }	   

	//Initial Clone Info Table
       CloneInfoHandle clone_handle;
	CommandConfig cmd_config;
	SCIReadbackSetting rb_setting;
	
	std::string file_path;

	p_part_info = new PART_INFO[rom_count];
	
       ErrorLookup::SetErrorCodeMode(BROM);
	
        ret = FlashTool_ReadPartitionInfo(g_ft_handle, p_part_info, rom_count);
     	if( S_DONE != ret ) {
            LOG("ERROR: %s(): FlashTool_ReadPartitionInfo() failed!, error code(%d).", __FUNC__, ret);
             FlashTool_Disconnect( &g_ft_handle );
	     return ret;
    	}

        LOG("%s(): PMT is exist.", __FUNC__);	 

	  unsigned long long flash_size = CaculateFlashSize(cn_result.m_da_report);
	  bool lastFlag = false;
	  unsigned int block_number = 0;
        for(unsigned int i = 0; i < rom_count; i++){

		      
			std::string name( p_part_info[i].name); 
			LOGD("Now Partition (%s)", name.c_str());
			clone_info.set_partition_name(p_part_info[i].name);
			LOGD("begain create partition clone info length...");
                   clone_info.set_partition_len(p_part_info[i].image_length);
				   
			if( name.find("RSV") != std::string::npos || name.find("BMTPOOL") != std::string::npos)		
			{
                           LOG("MTK Protected Reserved Regions...");
                           lastFlag = true;
				 block_number = p_part_info[i].begin_addr & 0x0000FFFF;
				 LOGD("block_number(%d)", block_number);
				 clone_info.set_start_addr(flash_size - 128*1024*block_number);				
			}
			else
			{
			    clone_info.set_start_addr(p_part_info[i].begin_addr);
			} 	           

			if(clone_info.partition_len()<=512) 
			{
			    lastFlag = true;
			    clone_info.set_partition_len(flash_size - clone_info.start_addr());
        		} 

			  LOGD("Start addr(%I64X), Length(%I64X)", clone_info.start_addr(),clone_info.partition_len());
			
			file_path = sci_files_folder + "\\" + p_part_info[i].name;
		       
                    ErrorLookup::SetErrorCodeMode(FLASHTOOL);
			
                    if(! FileUtils::CreateFiles(file_path))
			{ 
                        LOGE("%s: Create image file fail." , __FUNC__);
	                 FlashTool_Disconnect( &g_ft_handle );
			     return FT_CREATE_FILE_FAIL;
			}
			clone_info.set_image_path(file_path);
			clone_handle.AddCloneInfoItem(clone_info);
			rb_setting.set_cb_readback_init(cb_readback_flash_init);
			rb_setting.set_cb_readback_progress(cb_readback_flash);
			rb_setting.set_cb_readback_init_arg(this);
			rb_setting.set_cb_readback_progress_arg(this);
			rb_setting.set_storage_type(HW_STORAGE_EMMC);
     			ReadbackItem rb_item(i, _TRUE, clone_info.start_addr(), clone_info.partition_len(),
				                             file_path);
			rb_setting.set_readback_handle(g_CLONE_RB_HANDLE);
			
	    
                   ErrorLookup::SetErrorCodeMode(BROM);
	             ret = rb_setting.InitialRBHandle(rb_item);
	             if(ret != S_DONE)
	              {
                           LOGE("%s: Initial RB Handle fail." , __FUNC__);
	                    FlashTool_Disconnect( &g_ft_handle );
		             return ret;
	              }

			 if(lastFlag)
			 {
			       LOGD("This is the last region...");
                               lastFlag = false;
				break;
			 }

        }

       if( NULL != p_part_info )
       {
           delete[] p_part_info;
           p_part_info = NULL;
       }

       //readback
	ErrorLookup::SetErrorCodeMode(BROM);

	cmd_config.AddCommandSetting(rb_setting);

       ret = cmd_config.CreateCommand(g_ft_handle)->Execute();

	if(ret != S_DONE)
	{
             LOGE("%s: Readback fail, ret(%d)", __FUNC__, ret);
	      FlashTool_Disconnect(&g_ft_handle);
	      return ret;
	}

	//do checksum
      std::set<std::string> partition_set = clone_handle.partition_name_set();
      unsigned char chksum_value;
	S_CHKSUM_Arg chksum_arg;

	ArgCloneChksum(chksum_arg);
	chksum_arg.chksum_value = chksum_value;
	
      for(std::set<std::string>::const_iterator it = partition_set.begin();
	     it!= partition_set.end(); ++it)
      {     
             if(clone_handle.QueryCloneInfoByPartitionName((*it), &clone_info))
             {
                 
                  bool ifStop = FileUtils::ComputeCloneCheckSum(clone_info.image_path(), chksum_arg);
				   
		      if(!ifStop && g_stopflag == BOOT_STOP)
			{
			     FlashTool_Disconnect( &g_ft_handle );
			     return FT_USER_PRESS_STOP_BUTTON;
			}
		      
	            LOG("%s: checksum_value(0x%x)", __FUNC__, chksum_arg.chksum_value);
			  
		      clone_info.set_chksum_value(chksum_arg.chksum_value);
		      clone_handle.UpdateCloneInfoTable(clone_info);
	      }
      }             
		 
      //save XML file
     std::string clone_file_path = sci_files_folder + "\\" + "clone_info.xml";
      clone_handle.SaveFile(clone_file_path);
      

    // Disconnect
    FlashTool_Disconnect( &g_ft_handle );
        return ret;       

}

int tboot_1::SCIWriteMemory()
{
         int ret = S_DONE;

	//-1. Connect and get the HW information
	ArgFlashToolConnect(cn_arg, cn_result);
	unsigned char  com_port = (!g_bUsbMode) ? COM_PORT : GetUSBVCOMNumByPortName(m_strPort);


	int force_charge = /*g_bUsbModeWithBattery ? 0 : 1*/GetBatteryStatus();
	LOGD("FlashReadback_internal: force_charge(%d)", force_charge);
	ret = FlashTool_Connect( com_port, &cn_arg, &cn_result, NULL, &g_stopflag, &g_ft_handle,force_charge);
	if( S_DONE != ret ) {
		FlashTool_Disconnect( &g_ft_handle );
		return ret;
	}

	bool isDynamicLayout = false;
	g_platform_info.setChipName(cn_result.m_da_report.m_bbchip_name);

	ErrorLookup::SetErrorCodeMode(FLASHTOOL);
	Synchronize(UpdateUSBVCOMInfo);
          
	//get usb speed status
      FlashTool_USB_Status_Result usb_status_result;
      ret = GetUSBSpeedStatus(g_ft_handle, usb_status_result);
	if(S_DONE != ret)
	{
          LOGE("Get USB Speed Status fail! ret(%d)", ret);
	    FlashTool_Disconnect(&g_ft_handle);
	    return ret;
	}
	
	//Swith Speed if platform supports and user wants to
	if((g_platform_info.getPlatformConfig().supportUSBHighSpeed()) &&
        g_bSwitchSpeed && (usb_status_result.usb_speed_status == USB_FULL_SPEED)){

	if (!Swith2DAHighSpeed(&g_stopflag, m_strSymbolic, m_strPort, g_ft_handle, true, 30)) {
             FlashTool_Disconnect( &g_ft_handle );
		LOGE("Search and switch to DA HS USB Failed!");
             return FT_FIND_USB_ERROR;
	} else {	      
             speed_status= "USB_FULL_SPEED->USB_HIGH_SPEED";
		Synchronize(UpdateUSBVCOMInfo);
	}
   }
	ErrorLookup::SetErrorCodeMode(BROM);


	//check if restore file is ready
       ErrorLookup::SetErrorCodeMode(FLASHTOOL);
	
       std::string restore_path(MainForm->ed_SCI_RestoreFile->Text.c_str());
      // assert(restore_path.empty());

	if(!FileUtils::IsDirectoryExist(restore_path))
	{
            LOGE("%s: Restore File Folder is not exist!", __FUNC__);
			
	     FlashTool_Disconnect( &g_ft_handle );
		 
	     return FT_FILE_FOLDER_IS_NOT_EXIST;
	}

	std::string restore_config_file = restore_path + "\\" + SCI_CONFIG_FILE;
	if(!FileUtils::IsFileExist(restore_config_file))
	{
            FlashTool_Disconnect( &g_ft_handle );
	     LOGE("%s: Restore config file is not exist!", __FUNC__);
	     return FT_FILE_IS_NOT_EXIT;
	}
      
	CloneInfoItem clone_info;
	CloneInfoHandle *clone_handle = new CloneInfoHandle(restore_config_file);
	std::set<std::string> partition_set = clone_handle->partition_name_set();
	WriteMemorySetting wm_setting;
	CommandConfig cmd_config;
	S_CHKSUM_Arg chksum_arg;

	ArgCloneChksum(chksum_arg);

      for(std::set<std::string>::const_iterator it = partition_set.begin();
	     it!= partition_set.end(); ++it)
      {     
            LOG("%s: partition(%s) has been put in the set.", __FUNC__, (*it).c_str());

             if(clone_handle->QueryCloneInfoByPartitionName((*it), &clone_info))
             {
                   
			std::string file_name = restore_path + "\\" + clone_info.partition_name();

			
			if(!FileUtils::IsFileExist(file_name))
	             {
                         FlashTool_Disconnect( &g_ft_handle );
	                   LOGE("%s: Restore file(%s) is not exist!", __FUNC__, clone_info.partition_name());
	                   return FT_FILE_IS_NOT_EXIT;
	             }
			 
                   bool ifStop = FileUtils::ComputeCloneCheckSum(file_name, chksum_arg);
				   
		      if(!ifStop && g_stopflag == BOOT_STOP)
			{
			     FlashTool_Disconnect( &g_ft_handle );
			     return FT_USER_PRESS_STOP_BUTTON;
			}
			  
		      LOG("%s: checksum_value(0x%x)", __FUNC__, chksum_arg.chksum_value);

		      if(chksum_arg.chksum_value != clone_info.chksum_value())		
		      {
                           LOGE("%s: checksum not match, chksum(0x%x), chksum in config file(0x%x)",
				         __FUNC__, chksum_arg.chksum_value, clone_info.chksum_value());
                           FlashTool_Disconnect( &g_ft_handle );
			      return FT_CHECKSUM_NOT_MATCH;
		      }
		      else
		      {
		             wm_setting.set_address(clone_info.start_addr());					 
				 wm_setting.set_input(file_name);
			       wm_setting.set_cb_write_memory_progress_arg(this);
			       wm_setting.set_cb_write_memory_progress(cb_write_memory_progress);
			       cb_write_memory_init(this);
                               cmd_config.AddCommandSetting(wm_setting);
		      }
	      }
      }

      ret = cmd_config.CreateCommand(g_ft_handle)->Execute();
      if(ret != S_DONE)
      {
            FlashTool_Disconnect(&g_ft_handle);
	     return ret;
      }

    // Disconnect
    FlashTool_Disconnect( &g_ft_handle );
	
        return ret;
}
//==========================================================
//---------------------------------------------------------------------------
//===========================SCI Download======================
int tboot_1::SCIDownload()
{
       int ret;

	//-1. Connect and get the HW information
	ArgFlashToolConnect(cn_arg, cn_result);
	unsigned char  com_port = (!g_bUsbMode) ? COM_PORT : GetUSBVCOMNumByPortName(m_strPort);
	//Update brom.dll com port number
	COM_PORT = com_port;

	FlashTool_Download_Arg fdl_arg;
	FlashTool_Download_Result fdl_res;
	ArgFlashToolAdvancedDownload(fdl_arg, fdl_res);

       int  force_charge = /*g_bUsbModeWithBattery ? 0 : 1*/GetBatteryStatus();
	LOGD("%s: force_charge(%d)", __FUNC__, force_charge);
	ret = FlashTool_Connect( com_port, &cn_arg, &cn_result, NULL, &g_stopflag, &g_ft_handle,force_charge);
	if( S_DONE != ret ) {
		FlashTool_Disconnect( &g_ft_handle );
		return ret;
	}

	ErrorLookup::SetErrorCodeMode(BROM);

    LOG("%s: m_bbchip_name(%s), isChipSupportUSBHighSpeed(%s), g_bSwitchSpeed(%s)", __FUNC__,
        cn_result.m_da_report.m_bbchip_name, 
        g_platform_info.getPlatformConfig().supportUSBHighSpeed() ? "Y" : "N",
        g_bSwitchSpeed ? "Y" : "N");

      	//get usb speed status
      FlashTool_USB_Status_Result usb_status_result;
      ret = GetUSBSpeedStatus(g_ft_handle, usb_status_result);
	if(S_DONE != ret)
	{
          LOGE("Get USB Speed Status fail! ret(%d)", ret);
	    FlashTool_Disconnect(&g_ft_handle);
	    return ret;
	}

			
	ErrorLookup::SetErrorCodeMode(FLASHTOOL);
	if( g_platform_info.getPlatformConfig().supportUSBHighSpeed() &&
		g_bSwitchSpeed && (usb_status_result.usb_speed_status == USB_FULL_SPEED)) {
		LOG("%s: DA Enable High Speed Flag is %s.", __FUNC__,
			((g_bSwitchSpeed && (usb_status_result.usb_speed_status == USB_FULL_SPEED)) ? "true" : "false"));

              Synchronize(UpdateUSBVCOMInfo);
             	if (!Swith2DAHighSpeed(&g_stopflag, m_strSymbolic, m_strPort, g_ft_handle, true, 30)) {
                FlashTool_Disconnect( &g_ft_handle );
				LOGE("%s: Search and switch to DA HS USB Failed!", __FUNC__);
                return FT_FIND_USB_ERROR;
			} else {	
				Synchronize(UpdateUSBVCOMInfo);
				speed_status= "USB_FULL_SPEED->USB_HIGH_SPEED";
			}
	}

	//check if layout changed, if change, partitial download will be forbidden.
	if(!CheckBefPartiDL(g_DL_HANDLE_NODE.m_dl_handle, g_ft_handle))
	{
           LOGE("Layout changed, partitial download is allowed.");
		   
	    FlashTool_Disconnect(&g_ft_handle);
		
	    return FT_SCI_DOWNLOAD_LAYOUT_CHANGE;
	} 
      		
	ErrorLookup::SetErrorCodeMode(BROM);

	ret = FlashTool_Download(g_ft_handle, &fdl_arg, &fdl_res);
	if ( S_DONE != ret ) {
		FlashTool_Disconnect(&g_ft_handle);
		LOGD("%s: FlashTool_Download fail!", __FUNC__);
		return ret;
	}

	if(!ToolInfo::IsCustomerVer()) {
		FlashTool_EnableWDT_Arg wdt_arg;
		FlashTool_EnableWDT_Arg *p_wdt_arg = &wdt_arg;
		ArgFlashToolWatchDog(p_wdt_arg);
		ret = FlashTool_EnableWatchDogTimeout(g_ft_handle, p_wdt_arg);
		if(S_DONE != ret) {
			FlashTool_Disconnect(&g_ft_handle);
			LOGD("%s: FlashTool_EnableWatchDogTimeout fail!", __FUNC__);
			return ret;
		}
	}
	ret = FlashTool_Disconnect(&g_ft_handle);
	if(S_DONE != ret) {
		LOGD("%s: FlashTool_Disconnect fail!", __FUNC__);
		return ret;
	}

      
    // Disconnect
    FlashTool_Disconnect( &g_ft_handle );
	return ret;
}
//==========================================================
//---------------------------------------------------------------------------
unsigned long long tboot_1::CaculateFlashSize(DA_REPORT_T &da_report)
{
      unsigned long long flash_size;

      if(da_report.m_nand_ret == S_DONE)
      	{
            flash_size = da_report.m_nand_flash_size;
	}
      else if(da_report.m_emmc_ret == S_DONE)
      	{
            flash_size = da_report.m_emmc_boot1_size + da_report.m_emmc_boot2_size+ da_report.m_emmc_gp1_size
				   + da_report.m_emmc_gp2_size+da_report.m_emmc_gp3_size + da_report.m_emmc_gp4_size
				   + da_report.m_emmc_rpmb_size + da_report.m_emmc_ua_size;
	}	

	return flash_size;
}
//----------------------------------------------------------------------------
StorageLayoutType_E tboot_1::GetStorageLayoutType(bool isDynamic, HW_StorageType_E &storage)
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

//----------------------------------------------------------------------------
/*
*if platform supports auto detect battery, the status value should be 2;
*if platform does not support auto detect battery, 
*if manual selection is with battery, the status value should be 0;
*if manual selection is without battery, the status value should be 1;
*/
int tboot_1::GetBatteryStatus(void)
{
     if(g_platform_info.getPlatformConfig().supportDLAutoDetectBattery())
     {
            LOGD("GetBatteryStatus: DA USB Download battery is auto detection.");
            return(2);
     }
	 
     else if(g_bUsbModeWithBattery)
     {
         LOGD("GetBatteryStatus: DA USB Download with battery.");
	  return(0);
    }
	 
     else 
    {
          LOGD("GetBatteryStatus: DA USB Download without battery.");
          return(1);
    }
}
//---------------------------------------------------------------------------
int tboot_1::GetUSBSpeedStatus(FLASHTOOL_API_HANDLE_T &ft_handle, FlashTool_USB_Status_Result &usb_status_result)
{
  //Configure parameter  
  int ret = S_DONE;
  FlashTool_USB_Status_Arg usb_status_arg;  
  usb_status_arg.m_cb_usb_status_init = cb_checkusbstatus_init;
  usb_status_arg.cb_usb_status_init_arg = this;
  
  //Get USB Speed Status
  ret = FlashTool_CheckUSBStatus(ft_handle, &usb_status_arg, &usb_status_result);
  if (S_DONE != ret) {
     LOGE("FlashTool_CheckUSBStatus failed, ret(%d).", ret);
 }

 return ret;
 
}

//---------------------------------------------------------------------------

std::string tboot_1::GetStorageByDAReport(const FlashTool_Connect_Result &result)
{
      std::string storage_target("NAND");

      if(cn_result.m_da_report.m_nand_ret == S_DONE)
      	{
            LOGD("Storage(%s).", storage_target.c_str());
	      return storage_target;
	}

	if(cn_result.m_da_report.m_emmc_ret == S_DONE)
      	{
            storage_target = "EMMC";
		
            LOGD("Storage(%s).", storage_target.c_str());
	      return storage_target;
	} 
		  
	if(cn_result.m_da_report.m_sdmmc_ret == S_DONE)
      	{
             storage_target = "SDMMC";
		LOGD("Storage(%s).", storage_target.c_str());
	      return storage_target;
	}	  

	storage_target = "Unknown";
	LOGD("Storage(%s).", storage_target.c_str());
	
	return storage_target;
}
//---------------------------------------------------------------------------
bool tboot_1::CheckStorageByDAReport()
{
       if(g_platform_info.getFlashToolStorageConfig().IsNandOperation())
       {
             return cn_result.m_da_report.m_nand_ret == S_DONE;
       }

       if(g_platform_info.getFlashToolStorageConfig().IsEMMCOperation())
       {
             return cn_result.m_da_report.m_emmc_ret == S_DONE;
       }

       if(g_platform_info.getFlashToolStorageConfig().IsSDMMCOperation())
       {
             return cn_result.m_da_report.m_sdmmc_ret == S_DONE;
       }

}
//---------------------------------------------------------------------------
bool tboot_1::CheckIfBackupFileExist(const std::string bin_region_folder, BackupItem &backup_item)
{
    bool ret = false;

    if ( FileUtils::IsFileExist(backup_item.file_path()))
   {
	  ErrorLookup::SetErrorCodeMode(FLASHTOOL);
	  LOG("%s(): %s already exists for this chip: %s, verifying the checksum...",
					__FUNC__, backup_item.partition_name().c_str(), bin_region_folder.c_str());

	  if(FileUtils::IsFileExist(backup_item.chksum_file()))
	  {
		unsigned char origin_chksum = 0;
		unsigned char actual_chksum = 0;
		if(FileUtils::LoadCheckSum(backup_item.chksum_file(),origin_chksum) &&
		    FileUtils::ComputeCheckSum(backup_item.file_path(),actual_chksum) &&
			origin_chksum == actual_chksum)
		{
			ret = true;
			LOG("%s(): %s data file checksum is OK.", __FUNC__, backup_item.partition_name().c_str());
		}

             if(!ret)
             {
                 FileUtils::DeleteDummyFile(backup_item.file_path().c_str());
                 FileUtils::DeleteDummyFile(backup_item.chksum_file().c_str());
             }
	   }

	   if(!ret)
	   {
		LOG("%s(): %s data file checksum is wrong, need to remove dirty file first.", __FUNC__, backup_item.partition_name().c_str());
		if (!FileUtils::DeleteDummyFile(backup_item.file_path().c_str())) {
		LOG("%s(): : Remove diretory failed due to dirty data.", __FUNC__);
	   }
      }
    }
    else 
    {      
         LOGD("Backup files for %s are not exist!", backup_item.partition_name().c_str());
    }

    return ret;
}

//---------------------------------------------------------------------------
bool tboot_1::CheckBefPartiDL(const DL_HANDLE_T &dl_handle,
                                                     const FLASHTOOL_API_HANDLE_T &ft_handle)
{
	int ret = true;
	
       bool layout_match = true;
	bool all_image_dl = true;

	//check if the visible layout changed
      NandLayoutParameter nand_para(dl_handle, ft_handle);
      if(nand_para.is_target_layout_map_ready())
      	{
      	      LOG("%s(): Target layout map is ready.", __FUNC__);
			  
             if(!nand_para.CompareVisibleLayoutMatched())
             {
                   LOG("%s(): Load layout and target visible layout is not matched!", __FUNC__);
		      layout_match = false;
	      }
	}
	  
      //check if all the images has been selected to download
      unsigned short rom_count;
      ROM_INFO rom_info[MAX_LOAD_SECTIONS];	 
      AnsiString rom_name;
	  
      ret = DL_GetCount(dl_handle, &rom_count);
      if(ret != S_DONE)
	{
            LOGE("Get rom count fail. ret(%d)");

		all_image_dl = false;		
	}

	ret = DL_Rom_GetInfoAll(dl_handle, rom_info, MAX_LOAD_SECTIONS);
      if(ret != S_DONE)
	{
            LOGE("Get rom info list fail. ret(%d)", ret);
			
		all_image_dl = false;		
	}
	  
      for(int i = 0; i < rom_count; i++)
      	{
           if(rom_info[i].item_is_visable && (!rom_info[i].enable))
           {
                LOGD("rom_name(%s), enable(%d)", rom_name.c_str(), rom_info[i].enable);
                all_image_dl = false;
	     }
	}   
      	
       LOGD("layout_match(%d), all_image_dl(%d)", layout_match, all_image_dl);
	return layout_match ||all_image_dl;
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
int tboot_1::ArgMETAGetRestoreResultInfo( RESTORE_RESULT_T &cnf)
{
    memset(&cnf,    0,     sizeof(cnf));

    return 0;
}

