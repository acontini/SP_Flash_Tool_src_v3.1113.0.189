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
*  main.h
*
* Project:
* --------
*  Flash tool set
*
* Description:
* ------------
*  main window header file 
*
* Author:
* -------
*  FZ Hsu (mtk00303)
*
*==============================================================================
*           HISTORY
* Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
*------------------------------------------------------------------------------
* $Revision:   1.35  $
* $Modtime:   Dec 28 2005 22:13:02  $
* $Log:   //mtkvs01/vmdata/flash_tool/archives/main.h-arc  $
 *
 * Feb 24 2009 MTK02172
 * [STP100001912] [FlashTool] v3.0908.00 release
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
 * Mar 30 2008 MTK01952
 * [STP100001655] [FlashTool] v3.0808.0 DRAM Testing of Memory Test
 * 
 *
 * Mar 5 2008 MTK01952
 * [STP100001655] [FlashTool] v3.0808.0 DRAM Testing of Memory Test
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
 *    Rev 1.35   Dec 29 2005 10:57:26   mtk00539
 *  1. [FlashTool] Add download history feature.
 * Resolution for 156: [FlashTool v2.7.1013][BUG FIX] Fix BootROM start command failure while manually selecting NMT6226 or MT6227 baseband chip.
 * 
 *    Rev 1.34   Nov 19 2005 00:58:06   mtk00539
 *  1. [FlashTool][New] Adapt new BROM_DLL&DA v2.7.1011. 
 * Resolution for 150: [FlashTool v2.7.1011][New] Add UID Secure Booting feature and Bug Fix.
 *
 *    Rev 1.33   Oct 19 2005 14:47:26   mtk00539
 *  1. [FlashTool][New] Adapt new BROM_DLL&DA v2.7.1008.
 * Resolution for 141: [FlashTool v2.7.1008][New] Support NFB download and many new features.
 * 
 *    Rev 1.32   Sep 13 2005 13:38:16   mtk00539
 *  1. [FlashTool][New] Adapt new BROM_DLL&DA v2.4.1016. 
 * Resolution for 131: [FlashTool v2.6.1016][Enhance] Workaround the 1st time power up failure issue when RTC is empty.
 * 
 *    Rev 1.31   Jul 25 2005 14:56:44   mtk00539
 *  1. [FlashTool][New] Support MT6229.
 * Resolution for 125: [FlashTool v2.6.1015][New] Support MT6229.
 * 
 *    Rev 1.30   Jul 22 2005 20:48:30   mtk00539
 *  1. [FlashTool][New] Support MT6227.
 * Resolution for 122: [FlashTool v2.6.1014][New] Support MT6227.
 * 
 *    Rev 1.29   May 24 2005 20:03:40   mtk00539
 *  1. [FlashTool][New] Reset FAT to factory default setting. 
 *  2. [FlashTool][New] Option to enable/disable resource project id comparison. 
 * Resolution for 116: [FlashTool v2.6.1012][New] Reset FAT to factory default setting.
 * 
 *    Rev 1.28   Apr 12 2005 22:14:00   mtk00539
 *  1. [FlashTool][New] Support MT6228 baseband chip.
 * Resolution for 110: [FlashTool v2.6.1011][New] Support MT6228 baseband chip.
 * 
 *    Rev 1.27   Feb 16 2005 17:27:44   mtk00539
 *  1. [FlashTool][New] Adapt new BROM_DLL&DA v2.4.1009 to support SPANSION S71AL016D and SHARP LRS18C8A flash. 
 *  2. [FlashTool][Enhance] Allow to setup EMI setting in TestMode.
 *  3. [FlashTool][Enhance] Keep TestMode unless you disable it. In order to allow users to do test continuously.
 *  4. [FlashTool][Enhance] Add CTRL+S hot-key to save TestMode log into file.
 * Resolution for 106: [FlashTool v2.6.1009][New] Adapt new BROM_DLL&DA v2.4.1009 to support SPANSION S71AL016D and SHARP LRS18C8A flash.
 *
 *    Rev 1.26   Nov 22 2004 14:30:12   mtk00539
 *  1. [FlashTool][New] Adapt new BROM_DLL&DA v2.4.1008 to enable/disable speed-up baudrate in BootROM stage.
 * Resolution for 100: [FlashTool v2.6.1008][New] Adapt new BROM_DLL&DA v2.4.1008 to enable/disable speed-up baudrate in BootROM stage.
 * 
 *    Rev 1.25   Oct 29 2004 11:49:22   mtk00539
 *  1. [FlashTool][New] Adapt new BROM_DLL&DA v2.4.1006 to fix AM49DL3208GT & S71PL032J download fail problem and some enhancement.
 *  2. [FlashTool][New] Add auto-detect base band chip type flag.
 * Resolution for 1: META MAUI v1.0
 * 
 *    Rev 1.24   Sep 03 2004 19:54:48   mtk00539
 * [FlashTool][New] Adapt new BROM_DLL&DA v2.4.1004 for MT6217 support.
 * Resolution for 89: [FlashTool v2.6.1004][New] Adapt new BROM_DLL&DA v2.4.1004 for MT6217 support.
 * 
 *    Rev 1.23   Jul 19 2004 11:13:30   mtk00539
 * add baudrate full sync count option
 * Resolution for 82: [FlashTool v2.6.1001][New] Adapt with BROM_DLL v2.4.1001 and many enhancement.
 * 
 *    Rev 1.22   Jul 19 2004 02:10:56   mtk00539
 *  1. [FlashTool][New] Adapt new BROM_DLL v2.4.1001 for many features and bug fix.
 *  2. [FlashTool][Enhance] Export COM port read/write timeout setting.
 *  3. [FlashTool][Enhance] Change EMI setting to 32 bits.
 * Resolution for 82: [FlashTool v2.6.1001][New] Adapt with BROM_DLL v2.4.1001 and many enhancement.
 * 
 *    Rev 1.21   Jun 16 2004 16:38:34   mtk00539
 *  1. [FlashTool][Enhance] Re-org format option panel to prevent users confused.
 *  2. [FlashTool][Enhance] Do not close OK window when operation is done.
 * Resolution for 78: [FlashTool v2.5.1013][Enhance] Re-org format option panel to prevent users confused.
 *
 *    Rev 1.20   Jun 03 2004 11:55:34   mtk00539
 * when users select new scatter file, set dialog initial dir to scatter file base dir.
 * Resolution for 76: [FlashTool v2.5.1012][BUG FIX] Fix bug in FAT range info import.
 * 
 *    Rev 1.19   May 26 2004 21:54:58   mtk00539
 * [FlashTool][New] Using BROM_DLL_v2.3.1005 new feature to add BootROM stage callback function to disable vibrator to avoid MT6218B series board layout issue.
 * Resolution for 74: [FlashTool v2.5.1011][New] Add new flag to pull down GPIO17.
 * 
 *    Rev 1.18   May 21 2004 15:54:54   mtk00539
 *  1. [FlashTool][BUF FIX] fix incorrect error message of resource detection.
 * Resolution for 71: [FlashTool v2.5.1010][BUF FIX] fix incorrect error message of resource detection.
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
 *    Rev 1.16   Apr 20 2004 15:58:30   mtk00539
 * [Enhance] hide seldom used option, it an be turn on again by Advance Mode hot-key CTRL+ALT+O.
 * Resolution for 65: [FlashTool v2.5.1008][New] add baseband chip ECO revision checking flag for FlashDownload.
 * 
 *    Rev 1.15   Mar 29 2004 14:20:16   mtk00539
 * [New] add baseband chip ECO revision checking flag for FlashDownload.
 * Resolution for 65: [FlashTool v2.5.1008][New] add baseband chip ECO revision checking flag for FlashDownload.
 * 
 *    Rev 1.14   Mar 02 2004 00:28:18   mtk00539
 *  1. [FlashTool][Enhance] automatically select bbchip according to rom bbchip id..
 *  2. [FlashTool][Enhance] automatically load all the resource files.
 *  3. [FlashTool][Enhance] display resource and jump table information.
 *  4. [FlashTool][New] add MT6219 support.
 * Resolution for 54: [FlashTool v2.5.1006][Enhance] bbchip id detection and resource autoload.
 * 
 *    Rev 1.13   Feb 11 2004 17:54:56   mtk00539
 * [Enhance] support selectable download
 * Resolution for 52: [FlashTool v2.5.1002][Enhance] selectable download.
 * 
 *    Rev 1.12   Feb 05 2004 13:40:36   mtk00539
 * adapt to BROM DLL v2.2.1001
 * Resolution for 47: [FlashTool v2.5.1001][New] support multiple concatanated bin files download.
 * 
 *    Rev 1.11   Oct 29 2003 17:39:12   mtk00539
 * modify packet length
 * 
 *    Rev 1.10   Oct 01 2003 23:38:18   mtk00539
 * Add packet length in DA_WRITE_CMD and DA_READ_CMD.
 * Resolution for 28: [BootRom v2.1.1001][New] See the reasons below.
 * 
 *    Rev 1.9   Sep 25 2003 14:03:28   mtk00539
 * adapt brom.dll v2.1.1001, please see SCR(29) for more details.
 * Resolution for 29: [FlashTool v2.4.1001][New] See the reasons below.
 * 
 *    Rev 1.8   Jun 30 2003 19:19:36   mtk00539
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
 *    Rev 1.7   Jun 11 2003 17:53:34   mtk00539
 * 1. Modify BootRom library to support MT6218
 * 2. Modify FlashTool and DA to support AM29PDL128G flash
 * Resolution for 9: [FlashTool v2.2.1005][Add Feature] Support MT6218 and new flash AM29PDL128G
 * 
 *    Rev 1.6   Jun 03 2003 22:24:54   mtk00539
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
 *    Rev 1.5   May 20 2003 16:22:30   mtk00539
 * Support 6205/6205B at 13MHz, 26MHz and 52MHz
 * Resolution for 6: [FlashTool v2.2][AddFeature] Support 6205/6205B at 13MHz, 26MHz and 52MHz.
 * 
 *    Rev 1.4   Jan 09 2003 17:55:32   mtk00303
 * add last 1~3 context switch task ID and frame tick time
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

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ToolWin.hpp>
#include <Menus.hpp>
#include <ActnList.hpp>
#include <Dialogs.hpp>
#include <ImgList.hpp>
#include <SyncObjs.hpp>
#include "CGAUGES.h"
#include <vector>
#include <list>
#include "Trayicon.h"

#include <stdio.h>
#include <string>

#include "eboot\interface.h"
#include "flashtool_handle.h"
#include "flashtool.h"
#include "tboot_1.h"
#include "CGAUGES.h"
#include "param.h"
#include <CheckLst.hpp>
#include "Logger.h"
#include "Setting.h"
#include "SPFTMsg.h"
#include "FlashToolTypedefs.h"
#include "PlatformInfo.h"
#include "updater.h"

#include "CloneInfoHandle.h"

//---------------------------------------------------------------------------
class DownloadBinFile
{
    public:
	    DownloadBinFile() {
		    m_Filepath = "";
		    m_Enable = false;
	    }

	    ~DownloadBinFile() { }

	    AnsiString		m_Filepath;
	    bool			m_Enable;
};

class DownloadSet
{
    public:
	    DownloadSet() {
		    m_Scatter = "";
		    m_BootLoader = "";
            m_BootLoader_Ext = "";
		    m_BootLoader_Enable = false;
		    m_BinFiles.clear();
	    }
	    ~DownloadSet() { }

	    bool operator == (const DownloadSet	&r_value);
        /*
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
	    }*/

	    AnsiString				m_Scatter;
	    AnsiString				m_BootLoader;
            AnsiString              m_BootLoader_Ext;
	    bool					m_BootLoader_Enable;
	    std::vector<DownloadBinFile>	m_BinFiles;
};

typedef std::list<DownloadSet>		DownloadHistoryList;

#define MAX_DOWNLOAD_HISTORY	10


//---------------------------------------------------------------------------
class TMainForm : public TForm, public IPlatformOb,  public IVersionOb
{
     friend class tboot_1;

__published:	// IDE-managed Components
    TMainMenu *m_Main;
    TMenuItem *File1;
    TMenuItem *Options1;
    TMenuItem *Run1;
    TMenuItem *Download1;
    TActionList *ActionList1;
    TMenuItem *Open1;
    TMenuItem *N1;
    TMenuItem *Exit1;
    TMenuItem *BaudRate1;
    TMenuItem *mi_115200;
    TMenuItem *mi_38400;
    TMenuItem *mi_19200;
    TMenuItem *mi_9600;
    TMenuItem *mi_57600;
    TOpenDialog *OpenLdMapDialog;
    TSaveDialog *SaveOptionDialog;
    TImageList *ImageList1;
    TAction *FileOpenDownloadAgent;
    TAction *FileSave_TestModeLog;
    TAction *Download;
    TMenuItem *N2;
	TMenuItem *mi_EMI_Config;
    TImageList *ImageList2;
    TOpenDialog *OpenDownloadAgentDialog;
    TMenuItem *Openlinkmapfile1;
    TAction *FileOpenLinkMap;
    TAction *View_toolbar;
    TAction *View_StatusBar;
    TAction *Exit;
    TOpenDialog *OpenSingleRomFile;
    TStatusBar *sb_Main;
    TAction *Readback;
    TMenuItem *ReadBack1;
    TPageControl *pc_mainframe;
    TTabSheet *ts_Download;
    TTabSheet *ts_Readback;
    TListView *ListView1;
    TToolBar *tb_ReadBack;
    TToolButton *tb_AddReadBackFile;
    TImageList *ImageList3;
    TToolButton *tb_DeleteReadBackFile;
    TListView *lv_ReadBack;
    TSaveDialog *sd_ReadBack;
    TMenuItem *mi_460800;
    TMenuItem *mi_230400;
    TTimer *Timer_Download;
    TCGauge *CGauge1;
    TToolBar *tb_Download;
    TToolButton *ToolButton10;
    TToolButton *tb_ReadBack2;
    TMenuItem *Help1;
    TMenuItem *About1;
    TEdit *ed_DA_File;
    TEdit *ed_LinkMapFile;
    TMenuItem *mi_FormatFDM;
    TLabel *lb_DA_File;
    TLabel *lb_LinkMapFile;
	TMenuItem *MCUClock1;
	TMenuItem *MCU_13MHz;
	TMenuItem *MCU_26MHz;
	TMenuItem *MCU_52MHz;
	TMenuItem *BaseBandChip1;
    TMenuItem *BBCHIP_MT6573_E2;
	TAction *action_ToggleDebugDA;
	TRichEdit *DebugDAWindow;
	TAction *action_ToggleTrace;
        TToolButton *tb_FormatButton;
	TAction *action_ForceStop;
	TAction *action_ToggleSkipBootRom;
	TMenuItem *mi_921600;
    TMenuItem *BBCHIP_MT6573_E1;
	TAction *action_PurgeDebugLog;
	TMenuItem *PacketLength1;
	TMenuItem *PL_1;
	TMenuItem *PL_2;
	TMenuItem *PL_3;
	TMenuItem *PL_4;
	TMenuItem *PL_5;
	TMenuItem *DCOMPort;
    TMenuItem *BBCHIP_UNKNOWN;
	TMenuItem *m_CheckECOVersion;
	TAction *action_AdvanceOption;
	TToolButton *RB_StopButton;
	TMenuItem *m_CheckTgtResourceLayout;
	TMenuItem *m_AutoLoadResByScat;
	TMenuItem *m_DA_Option;
	TMenuItem *m_ResourceOption;
	TMenuItem *m_BBChipOption;
	TMenuItem *m_BRomStartCmdRetryCount;
	TMenuItem *BBCHIP_MT6217;
	TMenuItem *m_PullDownGPIO17;
	TMenuItem *m_COM_Port_Timeout;
	TMenuItem *m_Transmission_Option;
	TMenuItem *m_SpeedUpBootROMBaudrate;
    TSaveDialog *Dialog_SaveTestModeLog;
    TMenuItem *m_SaveTestModeLog;
    TMenuItem *BBCHIP_MT6228;
    TMenuItem *m_CompareProjectId;
    TMenuItem *m_EnableNFICS1;
    TMenuItem *m_Menu_OperationMethod;
    TMenuItem *m_Menu_OPM_NAND;
    TMenuItem *m_Menu_OPM_EMMC;
    TStatusBar *m_HWStatus;
    TMenuItem *BBCHIP_MT6227;
    TMenuItem *BBCHIP_MT6229;
    TMenuItem *BBCHIP_MT6226;
    TMenuItem *N3;
    TMenuItem *m_DL_History_0;
    TMenuItem *m_DL_History_1;
    TMenuItem *m_DL_History_2;
    TMenuItem *m_DL_History_3;
    TMenuItem *m_DL_History_4;
    TMenuItem *m_DL_History_5;
    TMenuItem *m_DL_History_6;
    TMenuItem *m_DL_History_7;
    TMenuItem *m_DL_History_8;
    TMenuItem *m_DL_History_9;
    TMenuItem *BBCHIP_MT6226M;
    TTreeView *TreeView1;
    TImageList *ImageList4;
    TMenuItem *mi_MultiLoad;
    TPopupMenu *PopupMenu1;
    TMenuItem *AddaLoad1;
    TMenuItem *DeleteaLoad1;
    TEdit *ed_AUTH_File;
    TLabel *lb_NandUtil_File;
    TToolButton *tb_DL_StopButton;
    TToolButton *tb_DL_StartButton;
    TOpenDialog *m_OpenAuthFileDialog;
	TMenuItem *m_AutoBBCHIP;
	TMenuItem *m_AutoExtClock;
    TTabSheet *ts_Paremeter;
    TTabSheet *ts_FileManagement;
    TGroupBox *GroupBox1;
    TGroupBox *gb_sec_setting;
    TGroupBox *gb_cust;
    TGroupBox *gb_otp;
    TCheckBox *cb_sec_setting;
    TCheckBox *cb_cust;
    TCheckBox *cb_sec_ro;
    TCheckBox *cb_otp;
    TBitBtn *bb_ParameterButton;
    TBitBtn *bb_StopButton;
    TGroupBox *gb_sec_ro;
	TListView *m_ParamListView;
	TOpenDialog *m_SelectFileDialog;
    TPanel *Panel1;
    TRadioButton *rb_sec_setting_Write;
    TRadioButton *rb_cust_Write;
    TRadioButton *rb_cust_Read;
    TRadioButton *rb_sec_ro_Write;
    TRadioButton *rb_sec_ro_Read;
    TRadioButton *rb_otp_Write;
    TRadioButton *rb_otp_Read;
    TButton *bt_otp_setting;
    TEdit *ed_otp_Write;
    TEdit *ed_otp_Read;
    TLabel *lb_otp_Write;
    TLabel *lb_otp_Read;
    TButton *bt_sec_setting;
    TLabel *lb_sec_setting_Write;
    TEdit *ed_sec_setting_Write;
    TLabel *lb_sec_ro_Write;
    TLabel *lb_sec_ro_Read;
    TEdit *ed_sec_ro_Write;
    TEdit *ed_sec_ro_Read;
    TLabel *lb_cust_Write;
    TLabel *lb_cust_Read;
    TEdit *ed_cust_Write;
    TEdit *ed_cust_Read;
    TButton *bt_sec_ro_setting;
    TButton *bt_cust_setting;
    TListView *m_ReadParamListView;
	TButton *m_FS_StartButton;
	TButton *m_FS_StopButton;
    TGroupBox *GroupBox2;
    TEdit *ed_ExceptionLog;
    TGroupBox *GroupBox3;
    TButton *bt_SaveExceptionLog;
    TEdit *ed_SaveExceptionLog;
	TMenuItem *BBCHIP_MT6230;
	TMenuItem *BBCHIP_MT6225;
    TMenuItem *BBCHIP_MT6223;
    TMenuItem *BBCHIP_MT6227D;
    TTabSheet *ts_RomWriter;
    TButton *m_RW_StopButton;
    TGroupBox *GroupBox4;
    TEdit *ed_SaveExtractNFB;
    TButton *m_RW_StartButton;
    TButton *bt_SaveExtractNFB;
    TMenuItem *Window1;
    TMenuItem *m_Menu_Window_CheckParameterPage;
    TMenuItem *m_Menu_Window_CheckFileManagement;
    TMenuItem *m_Menu_Window_CheckROMWriter;
    TTabSheet *ts_MemoryTest;
    TGroupBox *GroupBox5;
    TGroupBox *GroupBox6;
    TCheckBox *cb_MT_RAM_Data_Bus_Test;
    TCheckBox *cb_MT_RAM_Addr_Bus_Test;
    TCheckBox *cb_MT_RAM_Pattern_Test;
    TCheckBox *cb_MT_RAM_Inc_Dec_Test;
        TGroupBox *gb_EMMCTest;
    TCheckBox *cb_MT_EMMC_Pattern_Test;
    TButton *bt_MT_SelectAll;
    TButton *m_MT_StartButton;
    TButton *m_MT_StopButton;
    TRichEdit *m_MT_ResultRichEditor;
    TPanel *Panel2;
    TPanel *Panel3;
        TGroupBox *gb_NANDTest;
    TCheckBox *cb_MT_NAND_Pattern_Test;
    TMenuItem *mi_USBDownloadDA;
    TMenuItem *BBCHIP_MT6226D;
    TMenuItem *BBCHIP_MT6223P;
    TGroupBox *gb_gps;
    TRadioButton *rb_gps_Write;
    TRadioButton *rb_gps_Read;
    TButton *bt_gps_setting;
    TLabel *lb_gps_Write;
    TEdit *ed_gps_Write;
    TEdit *ed_gps_Read;
    TLabel *lb_gps_Read;
    TCheckBox *cb_gps;
    TMenuItem *DownloadStyle;
    TCheckBox *EMMCCheckBox;
    TCheckBox *NANDCheckBox;
    TCheckBox *RAMCheckBox;
    TMenuItem *BBCHIP_MT6235;
    TMenuItem *BBCHIP_MT6238;
    TMenuItem *BBCHIP_MT6239;
    TMenuItem *BBCHIP_MT6268A;
    TMenuItem *BBCHIP_MT6251T;
    TMenuItem *BBCHIP_MT6253T;
    TMenuItem *BackupandRestore;
    TMenuItem *BackupRestore;
    TMenuItem *Restore;
    TMenuItem *RestoreOnly;
    TMenuItem *NoAction;
    TMenuItem *UploadSetting;
    TMenuItem *NoUpload;
    TMenuItem *UploadOnly;
    TMenuItem *Upload;
    TMenuItem *BBCHIP_MT6268B;
    TMenuItem *DAStartAddress;
    TAction *action_RecordCommand;
    TLabel *lb_AUTH_File;
    TEdit *ed_SCERT_File;

    TBitBtn *bb_OpenDownloadAgent;
    TBitBtn *bb_ScatterLoading;
    TBitBtn *bb_OpenAuthFile;
    TBitBtn *bb_OpenSCertFile;
    TOpenDialog *m_OpenSCertFileDialog;
    TMenuItem *m_Menu_IMEI_update;
    TMenuItem *m_Menu_Backup_Restore_NVRAM;
    TMenuItem *m_subMenu_IMEI_NoAction;
    TMenuItem *m_subMenu_IMEI_Update;
    TMenuItem *m_subMenu_Backup_Restore_NoAction;
    TMenuItem *m_subMenu_Backup_Format_DL_Restore_NVRAM;
    TMenuItem *m_Menu_FourInOne;
    TMenuItem *m_subMenu_FourInOne_NoAction;
    TMenuItem *m_subMenu_FourInOne_Write;
    TToolButton *tb_FirmwareUpgradeButton;
    TAction *action_FirmwareUpgrade;
    TTimer *Timer_2ND_USB_Hint;
    TMenuItem *m_subMenu_Format_DL_FourInOne_Write;
    TEdit *ed_sec_setting_Write_Ex;
    TMenuItem *m_subMenu_Format_DL_Restore_NVRAM;
    TMenuItem *m_subMenu_Restore_NVRAM_Only;
    TMenuItem *N4;
    TMenuItem *UseChipIDasBackupFolderName;
    TMenuItem *UseCOMPortasBackupFolderName;
    TMenuItem *m_Menu_DA_DL_all;
    TLabel *Label1;
    TEdit *ed_NandUtil_File;
    TBitBtn *bb_OpenNandUtil;
    TOpenDialog *OpenNandUtilFileDialog;
    TMenuItem *m_Menu_Physical_Fmt_RB;
    TMenuItem *m_Menu_DA_DL_all_no;
    TMenuItem *m_Menu_DA_DL_all_full;
    TMenuItem *m_Menu_DA_DL_all_high;
    TMenuItem *m_Menu_Locate_Logs;
    TMenuItem *m_Menu_USB_mode_with_bat;
    TMenuItem *m_Menu_USB_mode_without_bat;
    TMenuItem *m_Menu_DA_DL_All_Speed;
    TMenuItem *m_Menu_DA_DL_All_Battery;
    TMenuItem *m_Menu_WriteMemory_CheckParameterPage;
    TTabSheet *ts_WriteMemory;
    TToolBar *toolbar_WriteMemory;
    TToolButton *tb_OpenRawData;
    TToolButton *tb_WriteMemory;
    TToolButton *tb_WriteMemory_Stop;
    TRadioGroup *rg_WM_Setting;
    TLabel *lb_WM_OpenRawDataFileSizeValue;
    TLabel *lb_WM_OpenRawDataFileSize;
    TLabel *lb_WM_OpenRawDataFilePath;
    TEdit *ed_WM_OpenRawData;
    TOpenDialog *m_OpenWriteMemoryFileDialog;
    TGroupBox *gb_WriterMemoryPara;
    TPanel *panel_WriterMemory;
    TLabeledEdit *le_WM_Length;
    TLabeledEdit *le_WM_StartAddr;
    TToolButton *tb_ReadbackVersion;
    TToolButton *tb_ReadbackProductInfo;
    TTimer *Timer_Warning; /*used for DSP_BL uncheck hint.*/
    TCheckBox *cb_da_dl_checksum_;
    TStaticText *stHint;
    TAction *action_MarkNandBadBlockOption;

        TTabSheet *ts_SCIClone;
        TLabel *lb_Clone_DA_File;
        TEdit *ed_Clone_DA_File;
        TBitBtn *bb_Clone_OpenDA;
        TGroupBox *gb_SCI_Readback;
        TGroupBox *gb_SCI_Restore;
        TEdit *ed_SCI_RestoreFile;
        TBitBtn *bb_Restore_OpenFile;
        TBitBtn *bb_Clone_Readback;
        TBitBtn *bb_SCI_OpenFileFolder;
        TBitBtn *bb_SCI_Clone_Restore;
        TBitBtn *bb_Clone_Restore_Stop;
        TBitBtn *bb_Clone_Readback_Stop;
        TTimer *Timer_Checksum;
        TTabSheet *ts_SCIDownload;
        TLabel *lb_SCI_DL_DA;
        TEdit *ed_SCI_DL_DA_File;
        TBitBtn *bb_SCI_DL_OpenDAFile;
        TLabel *Label2;
        TEdit *ed_SCI_DL_SCIFile;
        TBitBtn *bb_OpenSCIFile;
        TBitBtn *bb_SCI_DL_Download;
        TBitBtn *bb_SCI_DL_Stop;
        TOpenDialog *OpenSCIFileDialog;
        TListView *lv_SCIDownload;
        TAction *action_ToggleSCI;
        TToolButton *tb_DL_Certification;
        TAction *action_ToggleDLCert;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall Download1Click(TObject *Sender);
    void __fastcall FileOpenDownloadAgentExecute(TObject *Sender);
    void __fastcall FileOpenLinkMapExecute(TObject *Sender);
    void __fastcall View_toolbarExecute(TObject *Sender);
    void __fastcall View_StatusBarExecute(TObject *Sender);
    void __fastcall mi_921600Click(TObject *Sender);
    void __fastcall br_460800Execute(TObject *Sender);
    void __fastcall br_230400Execute(TObject *Sender);
    void __fastcall br_115200Execute(TObject *Sender);
    void __fastcall br_57600Execute(TObject *Sender);
    void __fastcall br_38400Execute(TObject *Sender);
    void __fastcall br_19200Execute(TObject *Sender);
    void __fastcall br_9600Execute(TObject *Sender);
    void __fastcall mi_DEBUGClick(TObject *Sender);
    void __fastcall ExitExecute(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall mi_ViewClick(TObject *Sender);
    void __fastcall ListView1_oldClick(TObject *Sender);
    void __fastcall ReadbackExecute(TObject *Sender);
    void __fastcall tb_AddReadBackFileClick(TObject *Sender);
    void __fastcall tb_DeleteReadBackFileClick(TObject *Sender);
    void __fastcall Timer_DownloadTimer(TObject *Sender);
    void __fastcall Timer_2ND_USB_HintTimer(TObject *Sender);
    void __fastcall testOKWnd1Click(TObject *Sender);
    void __fastcall About1Click(TObject *Sender);
    void __fastcall mi_FormatFDMClick(TObject *Sender);
	void __fastcall action_ToggleDebugDAExecute(TObject *Sender);
	void __fastcall action_ToggleTraceExecute(TObject *Sender);
	void __fastcall action_ForceStopExecute(TObject *Sender);
	void __fastcall action_ToggleSkipBootRomExecute(TObject *Sender);
    void __fastcall action_PurgeDebugLogExecute(TObject *Sender);
    void __fastcall action_AdvanceOptionExecute(TObject *Sender);
	void __fastcall tb_FormatButtonClick(TObject *Sender);
	void __fastcall PL_1Click(TObject *Sender);
	void __fastcall PL_2Click(TObject *Sender);
	void __fastcall PL_3Click(TObject *Sender);
	void __fastcall PL_4Click(TObject *Sender);
	void __fastcall PL_5Click(TObject *Sender);
	void __fastcall Options1Click(TObject *Sender);
	void __fastcall COMPortSubMenuClick(TObject *Sender);
	void __fastcall ListView1Click(TObject *Sender);
	void __fastcall ListView1Change(TObject *Sender, TListItem *Item, TItemChange Change);
	void __fastcall ListView1Changing(TObject *Sender, TListItem *Item, TItemChange Change, bool &AllowChange);
	void __fastcall ListView1DblClick(TObject *Sender);
	void __fastcall lv_ReadBackChange(TObject *Sender, TListItem *Item, TItemChange Change);
	void __fastcall lv_ReadBackChanging(TObject *Sender, TListItem *Item, TItemChange Change, bool &AllowChange);
	void __fastcall lv_ReadBackClick(TObject *Sender);
	void __fastcall lv_ReadBack_oldDblClick(TObject *Sender);
    void __fastcall lv_ReadBackDblClick(TObject *Sender);
    void __fastcall lv_ReadBackKeyPress(TObject *Sender, char &Key);
    void __fastcall lv_ReadBackKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall m_CheckECOVersionClick(TObject *Sender);
	void __fastcall tb_DL_StopButtonClick(TObject *Sender);
	void __fastcall RB_StopButtonClick(TObject *Sender);
	void __fastcall m_CheckTgtResourceLayoutClick(TObject *Sender);
	void __fastcall m_AutoLoadResByScatClick(TObject *Sender);
	void __fastcall m_BRomStartCmdRetryCountClick(TObject *Sender);
	void __fastcall m_PullDownGPIO17Click(TObject *Sender);
	void __fastcall mi_EMI_ConfigClick(TObject *Sender);
	void __fastcall m_COM_Port_TimeoutClick(TObject *Sender);
	void __fastcall m_SpeedUpBootROMBaudrateClick(TObject *Sender);
    void __fastcall FileSave_TestModeLogExecute(TObject *Sender);
    void __fastcall m_CompareProjectIdClick(TObject *Sender);
    void __fastcall m_FakeProgressTimerTimer(TObject *Sender);
    void __fastcall m_EnableNFICS1Click(TObject *Sender);
    void __fastcall BBCHIP_MT6573_E2Click(TObject *Sender);
    void __fastcall BBCHIP_MT6217Click(TObject *Sender);
	void __fastcall BBCHIP_MT6573_E1Click(TObject *Sender);
	void __fastcall BBCHIP_UNKNOWNClick(TObject *Sender);
    void __fastcall BBCHIP_MT6228Click(TObject *Sender);
    void __fastcall BBCHIP_MT6227Click(TObject *Sender);
    void __fastcall BBCHIP_MT6229Click(TObject *Sender);
    void __fastcall BBCHIP_MT6226Click(TObject *Sender);
    void __fastcall BBCHIP_MT6230Click(TObject *Sender);
	void __fastcall BBCHIP_MT6225Click(TObject *Sender);
    void __fastcall BBCHIP_MT6223Click(TObject *Sender);
    void __fastcall BBCHIP_MT6227DClick(TObject *Sender);
    void __fastcall BBCHIP_MT6226DClick(TObject *Sender);
    void __fastcall BBCHIP_MT6226MClick(TObject *Sender);
    void __fastcall BBCHIP_MT6223PClick(TObject *Sender);
    void __fastcall BBCHIP_MT6235Click(TObject *Sender);
    void __fastcall BBCHIP_MT6238Click(TObject *Sender);
    void __fastcall BBCHIP_MT6239Click(TObject *Sender);
    void __fastcall BBCHIP_MT6268AClick(TObject *Sender);
    void __fastcall BBCHIP_MT6268BClick(TObject *Sender);
    void __fastcall BBCHIP_MT6251TClick(TObject *Sender);
    void __fastcall BBCHIP_MT6253TClick(TObject *Sender);
    void __fastcall File1Click(TObject *Sender);
	void __fastcall OnDownloadHistoryClick(TObject *Sender);
    void __fastcall mi_MultiLoadClick(TObject *Sender);
    void __fastcall AddaLoad1Click(TObject *Sender);
    void __fastcall DeleteaLoad1Click(TObject *Sender);
    void __fastcall TreeView1Click(TObject *Sender);
    void __fastcall tb_OpenAuthFileClick(TObject *Sender);
	void __fastcall m_AutoBBCHIPClick(TObject *Sender);
	void __fastcall m_AutoExtClockClick(TObject *Sender);
	void __fastcall m_ParamListViewClick(TObject *Sender);
	void __fastcall m_ParamListViewChange(TObject *Sender, TListItem *Item, TItemChange Change);
	void __fastcall m_ParamListViewChanging(TObject *Sender, TListItem *Item, TItemChange Change, bool &AllowChange);
	void __fastcall m_ParamListViewDblClick(TObject *Sender);
    void __fastcall tb_ParameterButtonClick(TObject *Sender);
    void __fastcall cb_otpClick(TObject *Sender);
    void __fastcall cb_sec_settingClick(TObject *Sender);
    void __fastcall cb_sec_roClick(TObject *Sender);
    void __fastcall cb_custClick(TObject *Sender);
    void __fastcall bt_otp_settingClick(TObject *Sender);
    void __fastcall bt_sec_settingClick(TObject *Sender);
    void __fastcall bt_sec_ro_settingClick(TObject *Sender);
    void __fastcall bt_cust_settingClick(TObject *Sender);
    void __fastcall bb_ParameterButtonClick(TObject *Sender);
    void __fastcall bb_StopButtonClick(TObject *Sender);
    void __fastcall m_ReadParamListViewChange(TObject *Sender, TListItem *Item, TItemChange Change);
    void __fastcall m_ReadParamListViewChanging(TObject *Sender, TListItem *Item, TItemChange Change, bool &AllowChange);
    void __fastcall m_ReadParamListViewClick(TObject *Sender);
    void __fastcall m_ReadParamListViewDblClick(TObject *Sender);
    void __fastcall m_FS_StartButtonClick(TObject *Sender);
    void __fastcall m_FS_StopButtonClick(TObject *Sender);
    void __fastcall bt_SaveExceptionLogClick(TObject *Sender);
    void __fastcall bt_SaveExtractNFBClick(TObject *Sender);
    void __fastcall m_RW_StartButtonClick(TObject *Sender);
    void __fastcall m_RW_StopButtonClick(TObject *Sender);
    void __fastcall m_Menu_Window_CheckParameterPageClick(TObject *Sender);
    void __fastcall m_Menu_Window_CheckFileManagementClick(TObject *Sender);
    void __fastcall m_Menu_Window_CheckROMWriterClick(TObject *Sender);
    void __fastcall bt_MT_SelectAllClick(TObject *Sender);
    void __fastcall m_MT_StartButtonClick(TObject *Sender);
    void __fastcall m_MT_StopButtonClick(TObject *Sender);
    void __fastcall mi_USBDownloadDAClick(TObject *Sender);
    void __fastcall cb_gpsClick(TObject *Sender);
    void __fastcall bt_gps_settingClick(TObject *Sender);
    void __fastcall DownloadStyleClick(TObject *Sender);
    void __fastcall RAMCheckBoxClick(TObject *Sender);
    void __fastcall EMMCCheckBoxClick(TObject *Sender);
    void __fastcall NANDCheckBoxClick(TObject *Sender);
    void __fastcall MCU_13MHzClick(TObject *Sender);
    void __fastcall MCU_26MHzClick(TObject *Sender);
    void __fastcall MCU_52MHzClick(TObject *Sender);
    void __fastcall DAStartAddressClick(TObject *Sender);
    void __fastcall sb_MainDrawPanel(TStatusBar *StatusBar, TStatusPanel *Panel, const TRect &Rect);
    void __fastcall cb_MT_RAM_Data_Bus_TestClick(TObject *Sender);
    void __fastcall cb_MT_RAM_Addr_Bus_TestClick(TObject *Sender);
    void __fastcall cb_MT_RAM_Pattern_TestClick(TObject *Sender);
    void __fastcall cb_MT_RAM_Inc_Dec_TestClick(TObject *Sender);
    void __fastcall cb_MT_EMMC_Pattern_TestClick(TObject *Sender);
    void __fastcall cb_MT_NAND_Pattern_TestClick(TObject *Sender);
    void __fastcall NoActionClick(TObject *Sender);
    void __fastcall BackupRestoreClick(TObject *Sender);
    void __fastcall RestoreClick(TObject *Sender);
    void __fastcall RestoreOnlyClick(TObject *Sender);
    void __fastcall NoUploadClick(TObject *Sender);
    void __fastcall UploadClick(TObject *Sender);
    void __fastcall UploadOnlyClick(TObject *Sender);
    void __fastcall action_RecordCommandExecute(TObject *Sender);
    void __fastcall ListView1InfoTip(TObject *Sender, TListItem *Item, AnsiString &InfoTip);

//    void __fastcall tb_DLFlashBinButtonClick(TObject *Sender);
//    void __fastcall bb_FlashBinClick(TObject *Sender);

    void __fastcall mi_IMEIupdateClick(TObject *Sender);

//   void __fastcall m_Menu_Backup_Restore_NVRAMClick(TObject *Sender);
//    void __fastcall m_subMenu_Backup_Format_DL_Restore_NVRAMClick(TObject *Sender);
//    void __fastcall m_subMenu_Backup_Restore_NoActionClick(TObject *Sender);

    void __fastcall m_subMenu_IMEI_NoActionClick(TObject *Sender);
    void __fastcall m_subMenu_IMEI_UpdateClick(TObject *Sender);

//    void __fastcall cbxProjectChange(TObject *Sender);

    void __fastcall m_subMenu_FourInOne_NoActionClick(TObject *Sender);
    void __fastcall m_subMenu_FourInOne_WriteClick(TObject *Sender);
    void __fastcall tb_FirmwareUpgradeButtonClick(TObject *Sender);
    void __fastcall m_subMenu_Format_DL_FourInOne_WriteClick(
          TObject *Sender);
    void __fastcall DefaultExceptionHandle(TObject* Sender, Exception* E);
    void __fastcall m_subMenu_Format_DL_Restore_NVRAMClick(
          TObject *Sender);
    void __fastcall m_subMenu_Restore_NVRAM_OnlyClick(TObject *Sender);
    void __fastcall UseChipIDasBackupFolderNameClick(TObject *Sender);
    void __fastcall UseCOMPortasBackupFolderNameClick(
          TObject *Sender);
    void __fastcall m_Menu_DA_DL_allClick(TObject *Sender);
    void __fastcall FileOpenNandUitlExecute(TObject *Sender);
	void __fastcall FileOpenCertFileExecute(TObject *Sender);
    void __fastcall m_Menu_Physical_Fmt_RBClick(TObject *Sender);
    void __fastcall m_Menu_DA_DL_all_noClick(TObject *Sender);
    void __fastcall m_Menu_DA_DL_all_fullClick(TObject *Sender);
    void __fastcall m_Menu_DA_DL_all_highClick(TObject *Sender);
    void __fastcall m_Menu_Locate_LogsClick(TObject *Sender);
    void __fastcall m_Menu_USB_mode_with_batClick(TObject *Sender);
    void __fastcall m_Menu_USB_mode_without_batClick(TObject *Sender);
    void __fastcall pc_mainframeChange(TObject *Sender);
    void __fastcall m_Menu_WriteMemory_CheckParameterPageClick(TObject *Sender);
    void __fastcall tb_OpenRawDataClick(TObject *Sender);
    void __fastcall tb_WriteMemoryClick(TObject *Sender);
    void __fastcall tb_WriteMemory_StopClick(TObject *Sender);
    void __fastcall ts_WriteMemoryShow(TObject *Sender);
    void __fastcall tb_ReadbackVersionClick(TObject *Sender);
    void __fastcall tb_ReadbackProductInfoClick(TObject *Sender);
    void __fastcall ListView1CustomDrawItem(TCustomListView *Sender,
    TListItem *Item, TCustomDrawState State, bool &DefaultDraw);
    void __fastcall Timer_WarningTimer(TObject *Sender);
    void __fastcall Timer_ChecksumTimer(TObject *Sender);
    void __fastcall action_MarkNandBadBlockOptionExecute(TObject *Sender);
        void __fastcall action_ToggleDLCertExecute(TObject *Sender);
        void __fastcall tb_DL_CertificationClick(TObject *Sender);

        void __fastcall bb_Clone_OpenDAClick(TObject *Sender);
        void __fastcall bb_Clone_ReadbackClick(TObject *Sender);
        void __fastcall bb_SCI_Clone_RestoreClick(TObject *Sender);
        void __fastcall bb_SCI_DL_DownloadClick(TObject *Sender);
        void __fastcall bb_SCI_DL_OpenDAFileClick(TObject *Sender);
        void __fastcall bb_OpenSCIFileClick(TObject *Sender);
        void __fastcall bb_SCI_DL_StopClick(TObject *Sender);
        void __fastcall bb_Clone_Readback_StopClick(TObject *Sender);
        void __fastcall bb_Clone_Restore_StopClick(TObject *Sender);
        void __fastcall bb_SCI_OpenFileFolderClick(TObject *Sender);
        void __fastcall bb_Restore_OpenFileClick(TObject *Sender);
        void __fastcall lv_SCIDownloadChange(TObject *Sender,
          TListItem *Item, TItemChange Change);
        void __fastcall lv_SCIDownloadChanging(TObject *Sender,
          TListItem *Item, TItemChange Change, bool &AllowChange);
        void __fastcall lv_SCIDownloadClick(TObject *Sender);
        void __fastcall action_ToggleSCIExecute(TObject *Sender);
 

private:	// User declarations

    int uiMultiBootConfigAddr;
    unsigned short m_COMPortList[255];
    unsigned short m_COMPortCount;
    TCriticalSection  *m_pUpdateListLock;
/*
    //progress bar hint and color
    m_progress_hint;
    m_progress_forecolor;
    //error message
    AnsiString m_as_err_msg;
*/    
protected:

   AnsiString asBin;
   AnsiString asNandUtilDAPath;
   AnsiString ScatBaseDir;
   AnsiString ROMBaseDir;
   AnsiString TestModeLogFile;
   AnsiString asFlashBinFile;
   char auth_path[255];

public:
    Android_Image_File	m_image_files[ANDROID_IMAGE_FILE_NUMBER];
    //Android_Image_File  m_auth_file;
    int __fastcall Load_Android_Image(DL_HANDLE_T  dl_handle, unsigned short index, const char *rom_filepath);
    HINSTANCE   DLLInst;
    void _fastcall SubClassWndProc(Messages::TMessage &Message);

public:		// User declarations

    __fastcall TMainForm(TComponent* Owner);

    void onPlatformChanged();
	void updateUIForPlatform();


    tboot_1 *p1;
    bool isTbootWorking;

    void uncheckAllBaudRate ( void );
    void updateStatusBar ( void );
    void updateMenuItem ( void );

    bool Parse ( MultiLoadNode *p_node, AnsiString asMapFileName, bool bAutoLoad );
    //add for SCI Partitial Download
    bool ParseSCIFile(const AnsiString &scatpath);
    void RedrawSCIDLList(MultiLoadNode *pNode);
	

    bool FileOpenDownloadAgentExecute ( void );
    bool FileOpenNandUtilBin(TOpenDialog *pOpenDialog, unsigned int daType);
    bool FileOpenLinkMapExecute ( MultiLoadNode  *p_node );
    bool FileSaveTestModeLogExecute ( void );
    bool OpenAuthFile ( void );
	bool OpenSCertFile( void );

    int  UpdateDA();

    //add for Download Certification Files
    void DisableDLCertButton(void);
    void EnableDLCertButton(void);
    void DisableDownloadButton( void );
    void EnableDownloadButton( void );
	    void DisableSCIDownloadButton( void );
    void EnableSCIDownloadButton( void );
	    void DisableSCICloneButton( void );
    void EnableSCICloneButton( void );
    void DisableReadbackButton( void );
    void EnableReadbackButton( void );
    void DisableFormatButton( void );
    void EnableFormatButton( void );
    void DisableFirmwareUpgradeButton ( void );
    void EnableFirmwareUpgradeButton ( void );
    void DisableStopButton( void );
    void EnableStopButton( void );
    void UpdateCaption( void );
    void ResetBackupRestoreItem( void );
    void ResetUploadItem( void );

    void UpdatePacketLength(unsigned short pkt_length);
    void RedrawDownloadList (MultiLoadNode  *p_node, bool bUpdateParamOnly);
    void RedrawDownloadCheckBox ( void );
    void RedrawReadbackList ( void );
#if 0
    void RedrawProjectComBox(void);
#endif
    bool LoadByDownloadSet(const DownloadSet &dl_set, MultiLoadNode  *p_node);

    void HWStatusBarClear ( void );
    void HWStatusBarUpdate(const DA_REPORT_T *p_da_report, const char *p_device_hint, const char *m_hw_detection_report);
    static int LoadFileInfo(const char *pathname, unsigned int *p_nFileLength, long *p_last_modify_time);
    static int LoadFile(const char *pathname, unsigned char **pp_buf, unsigned int *p_nFileLength, long *p_last_modify_time);
    int SaveFile(const char *pathname, unsigned char *p_buf, unsigned int nFileLength );

    void LoadSecRO( void );
    void LoadCustPara( void );
    void LoadGPS( void );
#if 0
    void AutoLoadDUMAROMs(MultiLoadNode *p_node);
#endif
    void AutoLoadYuSuROMs(MultiLoadNode *p_node);

    bool GetScatterFilePath(const MultiLoadNode *p_node, AnsiString& scatterFilePath);
    void AutoFillDatabasePath(const MultiLoadNode *p_node);

    void WriteBackFlashToolINI( void );
    void ReadFlashToolINI( void );
#if 0
    void WriteBackDUMAINI( void );
    void ReadDUMAINI( void );
#endif
    void WriteBackYuSuINI( void );
    void ReadYuSuINI( void );
    bool LoadDefultScatter( MultiLoadNode *p_node, AnsiString asMapFileName );
    bool LoadDefultDA( AnsiString asFileName);

    void start_DL( bool b_start_DL );
    void start_RB( bool b_start_RB );

    bool InitializeDL ( void );

    void CreateConfigFile();

    void Create_DL_ConfigFile(const std::wstring &filename);
    void Create_FMT_ConfigFile(const std::wstring &filename);
    void Create_RB_ConfigFile(const std::wstring &filename);
    void Create_RtFD_ConfigFile(const std::wstring &filename);
    void Create_DL_FMT_ConfigFile(const std::wstring &filename);
    void Create_DL_RtFD_ConfigFile(const std::wstring &filename);
    void Create_BK_DL_RS_ConfigFile(const std::wstring &filename);
    void Create_BK_DL_FMT_RS_ConfigFile(const std::wstring &filename);
    void Create_BK_DL_RtFD_RS_ConfigFile(const std::wstring &filename);
    void Create_BK_FMT_RS_ConfigFile(const std::wstring &filename);
    void Create_BK_RtFD_RS_ConfigFile(const std::wstring &filename);
    void Create_META_4in1_ConfigFile(const std::wstring &filename);
    void Create_FMT_DL_ConfigFile(const std::wstring &filename);

    ConsoleMode::GeneralSetting CreateGeneralSetting();
    ConsoleMode::DownloadSetting CreateDownloadSetting();
    ConsoleMode::FormatSetting CreateFormatSetting();
    ConsoleMode::ReadbackSetting CreateReadbackSetting();
    ConsoleMode::ResetToFactoryDefaultSetting CreateRtFDSetting();
    ConsoleMode::BackupSetting CreateBackupSetting();
    ConsoleMode::RestoreSetting CreateRestoreSetting();
    ConsoleMode::Write_BT_WIFI_IMEI_NVRAM_Setting Create_4IN1_Setting();

    void newVersionDetected(const std::string &version, const std::string &path);

    //added for DSP_BL hint
    void ShowHintMessage(TControl * sender, const std::string& hint, int offset_x, int offset_y);
    void CSHintMessage(int itemindex);
    void CSHintMessageChksum(const string& hint, int offset_x, int offset_y);

	bool IsAutoPollingEnable(void) const {
		return m_is_auto_polling_enable;
	}
	unsigned int GetAutoPollingCount(void) const {
		return this->m_auto_polling_count;
	}
	void SetAutoPollingCount(const unsigned int count) {
		this->m_auto_polling_count = count;
	}
	void SetAutoPollingUpperLimit(const unsigned int upper_limit) {
		this->m_auto_polling_upper_limit = upper_limit;
	}

      std::string RestoreFilePath(void) const {

              return this->m_restore_file_path;
      }
	
private:
    //DL list check
    bool IsDLListEmpty(void) const;
    //GUI initial parameters check
    bool IsInitialParameterCheckPass(void);
    bool checkBeforeSCIRestore();
    bool checkBeforeSCIDownload();

    //clone test
    void InitialConfigurations();
	
    //Partition size check
    int GetROMIndex(const char* rom_name, const DL_HANDLE_T dl_handle);
    int m_2ndSiteUSBSecHint;
   //Send image-brom_type entry list
   void BromDLTypeTblEntry(DL_HANDLE_T dl_handle);
   //Auto Polling Flag
   bool m_is_auto_polling_enable;
   //Auto Polling Download Count
   unsigned int m_auto_polling_count;
   //Auto Polling Upper Limit Count
   unsigned int m_auto_polling_upper_limit;

   std::string m_restore_file_path;
};

//---------------------------------------------------------------------------
extern int g_stopflag;

extern PACKAGE TMainForm *MainForm;


extern EXT_CLOCK	g_EXT_CLOCK;
extern BBCHIP_TYPE	g_BBCHIP_TYPE;
extern SP_BBCHIP_TYPE	g_SP_BBCHIP_TYPE;

extern FormatOption_E   	    g_FormatAfterDownloadOption;
extern FormatOption_E	        g_FormatOption;
//extern OptionMethod_E	        g_OperationMethod;
extern NUTL_EraseFlag_E	        g_EraseFlag;
extern NandAutoFormat_E         g_NandAutoFormatFlag;

extern NVRAM_UPDATE_STATE_E    g_nvram_update_state;

extern bool g_bSkipBootRom;
extern bool g_bCheckECOVer;
extern bool g_bCheckTgtResourceLayout;
extern bool g_bPullDownGPIO17;
extern bool g_SpeedUpBootROMBaudrate;
extern bool	g_FormatValidation;
extern bool g_bEnableAdvanceOption;
extern bool g_bParameterPage;
extern bool g_bDownloadStyleSequential;
extern bool	g_bNFI_SelectCS1;
extern bool g_bUsbDLRB;
extern bool g_bUsbMode;
extern bool g_bUsbModeWithBattery;
extern bool	g_bDebugDA;
extern bool g_bUsbDLDA;
extern bool g_bDLCert;

extern unsigned short g_PacketLength;

extern unsigned long long g_ulNandFormatStartAddr;
extern unsigned long long g_ulNandFormatLength;
extern unsigned int g_ulNandFormatLengthByDAReport;

extern unsigned int g_MaxBromStartCmdRetryCount;
extern unsigned int g_COM_Read_Timeout;
extern unsigned int g_COM_Write_Timeout;
extern unsigned int g_CostTimeSec;
extern unsigned int g_ProgressTimeSec;
extern unsigned int g_DisplayFinishedBytes;


extern unsigned char g_Baudrate_FullSync_Count;

extern AnsiString           g_BackupCalibrationDataFolderPath;
extern EMI_Config_S         g_EMI_Config[8];
extern DRAM_NFI_Setting     g_EMI_NFI_Setting;

extern std::vector<MultiLoadNode> g_DL_HANDLE_LIST_nodes;

extern DL_HANDLE_LIST_T	    g_DL_HANDLE_LIST;
extern DA_HANDLE_T	        g_DA_HANDLE;
extern DA_HANDLE_T          g_NAND_UTIL_DA_HANDLE;
extern RB_HANDLE_T	        g_RB_HANDLE;
extern RB_HANDLE_T           g_FU_RB_HANDLE;
extern RB_HANDLE_T           g_CLONE_RB_HANDLE;
extern RB_HANDLE_T           g_SW_Ver_RB_HANDLE;
extern ANDROID_ADV_HANDLE_T g_Android_Adv_HANDLE;
extern TTreeNode            *g_rootLoad;
extern AUTH_HANDLE_T	    g_AUTH_HANDLE;
extern SCERT_HANDLE_T g_SCERT_HANDLE;
extern FLASHTOOL_API_HANDLE_T   g_ft_handle;
extern ParamDownloadConfig_T    g_ParamDownloadConfig;
extern ParamReadbackConfig_T    g_ParamReadbackConfig;
extern ParamReadbackConfig_T    g_ReadbackPage_Param;
extern ParameterType_T          g_ParameterType;
extern FLASHTOOL_FUNCTION	    g_flashtool_function;
#if 0
extern BACKUP_RESTORE_STATE_E   g_backup_restore_state;
#endif
extern bool g_bDADownloadAll;
extern bool g_bSwitchSpeed;
extern bool g_bPhysicallyFormatReadback;
//Add for controllingl to mark nand bad blocks
extern bool g_bEnableMarkNandBadBlocks;
//Security Rom Lock
extern SecurityBitCtrl_YuSu_T g_ParamsecBitCtrlYuSu;
extern unsigned int g_ParamImageLockAll;
//Write Memory
extern AnsiString g_WM_RawDataFilePath;
extern unsigned long long g_WM_address;
extern unsigned int g_WM_container_length;

//encription
extern bool g_SCI_Mode;

class button_sentry
{
    public:
    button_sentry();
    ~button_sentry();
};

#endif
