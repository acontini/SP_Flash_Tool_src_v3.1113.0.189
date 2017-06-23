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
*  about.h
*
* Project:
* --------
*  Flash tool set
*
* Description:
* ------------
*  about window header
*
* Author:
* -------
*  FZ Hsu (mtk00303)
*
*==============================================================================
*           HISTORY
* Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
*------------------------------------------------------------------------------
* $Revision:   1.5  $
* $Modtime:   Oct 19 2005 11:12:04  $
* $Log:   //mtkvs01/vmdata/flash_tool/archives/about.h-arc  $
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
 * Aug 16 2006 mtk00539
 * [STP100001057] FlashTool v3.1.00 release
 * Display build date
 * 
 *    Rev 1.5   Oct 19 2005 14:47:14   mtk00539
 *  1. [FlashTool][New] Adapt new BROM_DLL&DA v2.7.1008. 
 * Resolution for 141: [FlashTool v2.7.1008][New] Support NFB download and many new features.
 * 
 *    Rev 1.4   Sep 26 2003 11:51:34   mtk00539
 * fix version info
 * Resolution for 29: [FlashTool v2.4.1001][New] See the reasons below.
 * 
 *    Rev 1.3   Jun 30 2003 19:19:34   mtk00539
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
 *    Rev 1.2   May 20 2003 16:22:30   mtk00539
 * Support 6205/6205B at 13MHz, 26MHz and 52MHz
 * Resolution for 6: [FlashTool v2.2][AddFeature] Support 6205/6205B at 13MHz, 26MHz and 52MHz.
 * 
 *    Rev 1.1   Jul 26 2002 11:52:14   admin
 * ver 0726
 * 
 *    Rev 1.0   Jul 20 2002 19:26:08   admin
 * Initial revision.
*
*------------------------------------------------------------------------------
* Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
*==============================================================================
*******************************************************************************/


//---------------------------------------------------------------------------

#ifndef aboutH
#define aboutH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

#include "updater.h"
//---------------------------------------------------------------------------
class TForm_About : public TForm, public IVersionOb
{
__published:	// IDE-managed Components
    TGroupBox *GroupBox1;
    TButton *about_OK_Btn;
	TLabel *VersionInfo;
    TLabel *tool_BuildInfo;
    TLabel *copyrightLabel;
	TLabel *brom_dll_version;
    TLabel *meta_dll_version;
	TLabel *brom_dll_release_type;
	TLabel *meta_dll_release_type;
	TLabel *brom_dll_build_date;
	TLabel *meta_dll_build_date;
    TLabel *da_version;
    TLabel *da_build_date;
    TGroupBox *GroupBox2;
    TLabel *eboot_dll_version;
    TLabel *eboot_dll_release_type;
    TLabel *eboot_dll_build_date;
    TLabel *sp_meta_dll_version;
    TLabel *sp_meta_dll_release_type;
    TLabel *sp_meta_dll_build_date;
    TLabel *tool_Comment;
    TButton *check_update_btn;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *nand_util_version;
    TLabel *nand_util_build_date;

    void __fastcall about_OK_BtnClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall check_update_btnClick(TObject *Sender);

public:		// User declarations
        __fastcall TForm_About(TComponent* Owner);

    void newVersionDetected(const std::string &version, const std::string &path);

private:
    bool hasNewVersion;
    std::string newVersionPath;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_About *Form_About;
//---------------------------------------------------------------------------
#endif
