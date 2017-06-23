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
*  Flash_tool.cpp
*
* Project:
* --------
*  Flash tool set
*
* Description:
* ------------
*  Flash tool set main project file
*
* Author:
* -------
*  FZ Hsu (mtk00303)
*
*==============================================================================
*           HISTORY
* Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
*------------------------------------------------------------------------------
* $Revision:   1.7  $
* $Modtime:   Jul 12 2004 00:22:30  $
* $Log:   //mtkvs01/vmdata/flash_tool/archives/Flash_tool.cpp-arc  $
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
 * Mar 30 2008 MTK01952
 * [STP100001655] [FlashTool] v3.0808.0 DRAM Testing of Memory Test
 * 
 *
 * Mar 5 2008 MTK01952
 * [STP100001655] [FlashTool] v3.0808.0 DRAM Testing of Memory Test
 * 
 *
 * Aug 13 2006 mtk01413
 * [STP100001057] FlashTool v3.1.00 release
 * 
 * 
 *    Rev 1.7   Jul 19 2004 02:10:54   mtk00539
 *  1. [FlashTool][New] Adapt new BROM_DLL v2.4.1001 for many features and bug fix.
 *  2. [FlashTool][Enhance] Export COM port read/write timeout setting.
 *  3. [FlashTool][Enhance] Change EMI setting to 32 bits.
 * Resolution for 82: [FlashTool v2.6.1001][New] Adapt with BROM_DLL v2.4.1001 and many enhancement.
 * 
 *    Rev 1.6   May 14 2004 17:03:58   mtk00539
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
 *    Rev 1.5   Mar 09 2004 21:06:44   mtk00539
 * [Enhance] adapt new Boot_FlashTool interface.
 * 
 *    Rev 1.4   Jun 30 2003 19:19:34   mtk00539
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
 *    Rev 1.3   Jun 03 2003 22:24:54   mtk00539
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
 *    Rev 1.2   May 20 2003 16:22:30   mtk00539
 * Support 6205/6205B at 13MHz, 26MHz and 52MHz
 * Resolution for 6: [FlashTool v2.2][AddFeature] Support 6205/6205B at 13MHz, 26MHz and 52MHz.
 * 
 *    Rev 1.1   Jul 26 2002 11:52:18   admin
 * ver 0726
 * 
 *    Rev 1.0   Jul 20 2002 19:26:12   admin
 * Initial revision.
*
*------------------------------------------------------------------------------
* Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
*==============================================================================
*******************************************************************************/

//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <windows.h>
#include "ConsoleMode.h"
#include "eboot\interface.h"
#include "frm_Splash.h"
#include "Utility.h"

#pragma warn -8004

USEFORM("main.cpp", MainForm);
USEFORM("DA_Option.cpp", Form_DA_Option);
USEFORM("ext_mem1.cpp", ext_mem1Form);
USEFORM("OK_Wnd.cpp", Form_OK);
USEFORM("about.cpp", Form_About);
USEFORM("RB_Option.cpp", Form_RB_Option);
USEFORM("DL_Go.cpp", Form_DL_GO);
USEFORM("RB_Go.cpp", Form_RB_GO);
USEFORM("frm_FormatOption.cpp", FormatOption);
USEFORM("frm_BootROMStartCmdRetry.cpp", frm_BromStartCmdRetry);
USEFORM("frm_COM_Option.cpp", COM_Option);
USEFORM("frm_SecuritySetting.cpp", m_SecuritySetting);
USEFORM("frm_OTPSetting.cpp", m_OTPSetting);
USEFORM("frm_ParameterReadSetting.cpp", m_ParameterReadSetting);
USEFORM("frm_IMEIDownload.cpp", Form_IMEI_setting);
USEFORM("frm_FourInOne.cpp", Form_FourInOne);
USEFORM("frm_Process.cpp", frm_Processing);
USEFORM("frm_Splash.cpp", SplashFrom);
USEFORM("frm_encript.cpp", frm_encription);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR commandLine, int)
{

    try
    {
        if ((commandLine != NULL) && (::strlen(commandLine) != 0))
        {
            int ret;

            //CloseActiveSync();

            ret = ConsoleMode::Run(GetCommandLine());

            //RestartActiveSync("");

            return ret;
        }

        //check single instance for GUI
        CheckSingleInstanceOfFlashTool(false);

        Application->Initialize();

        Application->Title = "Smart Phone Flash Tool";
         TSplashFrom *pSplashFrom = new TSplashFrom(Application);
        if(!pSplashFrom->TSplashFormShow(pSplashFrom))
        {
            ShowMessage("New intial splash sceen failed!");
            exit(0);
        }

        Application->CreateForm(__classid(TMainForm), &MainForm);
        Application->CreateForm(__classid(TForm_DA_Option), &Form_DA_Option);
                 Application->CreateForm(__classid(Text_mem1Form), &ext_mem1Form);
                 Application->CreateForm(__classid(TForm_OK), &Form_OK);
                 Application->CreateForm(__classid(TForm_About), &Form_About);
                 Application->CreateForm(__classid(TForm_RB_Option), &Form_RB_Option);
                 Application->CreateForm(__classid(TForm_DL_GO), &Form_DL_GO);
                 Application->CreateForm(__classid(TForm_RB_GO), &Form_RB_GO);
                 Application->CreateForm(__classid(TFormatOption), &FormatOption);
                 Application->CreateForm(__classid(Tfrm_BromStartCmdRetry), &frm_BromStartCmdRetry);
                 Application->CreateForm(__classid(TCOM_Option), &COM_Option);
                 Application->CreateForm(__classid(Tm_SecuritySetting), &m_SecuritySetting);
                 Application->CreateForm(__classid(Tm_OTPSetting), &m_OTPSetting);
                 Application->CreateForm(__classid(Tm_ParameterReadSetting), &m_ParameterReadSetting);
                 Application->CreateForm(__classid(TForm_IMEI_setting), &Form_IMEI_setting);
                 Application->CreateForm(__classid(TForm_FourInOne), &Form_FourInOne);
                 Application->CreateForm(__classid(Tfrm_Processing), &frm_Processing);
                 Application->CreateForm(__classid(Tfrm_encription), &frm_encription);
                 pSplashFrom->TSplashFormDestory(pSplashFrom);
        Application->HintPause     = 100; // 0.1 sec
        Application->HintHidePause = 100000; // 100 sec
        Application->Run();
    }
    catch ( Exception &exception )
    {
        //RestartActiveSync("");
        Application->ShowException( &exception );
    }

    return 0;
}
//---------------------------------------------------------------------------
