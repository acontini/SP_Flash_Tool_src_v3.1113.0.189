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
*  about.cpp
*
* Project:
* --------
*  Flash tool set
*
* Description:
* ------------
*  about window, display version, build date support feature.
*
* Author:
* -------
*  FZ Hsu (mtk00303)
*
*==============================================================================
*           HISTORY
* Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
*------------------------------------------------------------------------------
* $Revision:   1.2  $
* $Modtime:   Oct 19 2005 11:11:50  $
* $Log:   //mtkvs01/vmdata/flash_tool/archives/about.cpp-arc  $
 *
 * Aug 7 2008 MTK01952
 * [STP100001779] [FlashTool] v3.0828.00
 * New features:
 *  1. Add the backup and restore functinality 
 *
 * Sep 27 2006 mtk00539
 * [STP100001145] FlashTool v3.1.01 release
 * 
 *
 * Aug 16 2006 mtk00539
 * [STP100001057] FlashTool v3.1.00 release
 * Display build date
 * 
 *    Rev 1.2   Oct 19 2005 14:47:14   mtk00539
 *  1. [FlashTool][New] Adapt new BROM_DLL&DA v2.7.1008. 
 * Resolution for 141: [FlashTool v2.7.1008][New] Support NFB download and many new features.
 * 
 *    Rev 1.1   Jun 30 2003 19:19:34   mtk00539
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
 *    Rev 1.0   Jul 20 2002 19:26:08   admin
 * Initial revision.
*
*------------------------------------------------------------------------------
* Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
*==============================================================================
*******************************************************************************/

//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <assert.h>
#include "about.h"
#include "flashtool.h"
#include "meta.h"
#include "eboot\interface.h"
#include "WMMETA_Wrapper.h"
#include "version.h"
#include "Logger.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_About *Form_About;
//---------------------------------------------------------------------------
__fastcall TForm_About::TForm_About(TComponent* Owner)
        : TForm(Owner)
{
    hasNewVersion = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm_About::about_OK_BtnClick(TObject *Sender)
{
    Visible = false;        
}
//---------------------------------------------------------------------------
void __fastcall TForm_About::FormCreate(TObject *Sender)
{
   AnsiString as;
   tool_BuildInfo->Caption = "Build: " + AnsiString(ToolInfo::BuildInfo().c_str());
   tool_Comment->Caption = "Comment: "+ AnsiString(ToolInfo::Comments().c_str());
   VersionInfo->Caption = ToolInfo::ToolName().c_str();

#ifdef _DEBUG
     as = VersionInfo->Caption;
     as = as+" (DEBUG) ";
     VersionInfo->Caption = as;
#endif /* #ifdef _DEBUG */

   const char *p_version = NULL;
   const char *p_release_type = NULL;
   const char *p_build_date = NULL;

   // get the brom dll information
   Brom_GetDLLInfo(&p_version, &p_release_type, &p_build_date, NULL);
   assert(p_version != NULL);
   assert(p_release_type != NULL);
   assert(p_build_date != NULL);
   as = (strcmp(p_version,"") == 0) ? "brom.dll v2." : p_version;
   brom_dll_version->Caption = as;
   as = (strcmp(p_release_type,"") == 0) ? "brom_dll RELEASE_TYPE" : p_release_type ;
   brom_dll_release_type->Caption = as;
   as = (strcmp(p_build_date,"") == 0) ? "brom_dll BUILD_DATE" : p_build_date;
   brom_dll_build_date->Caption = as;

   // get the eboot dll information
   Eboot_GetDLLInfo(&p_version, &p_release_type, &p_build_date, NULL);
   as.printf("%s", p_version);
   eboot_dll_version->Caption = as;
   as.printf("%s", p_release_type);
   eboot_dll_release_type->Caption = as;
   as.printf("(Build-Date: %s)", p_build_date);
   eboot_dll_build_date->Caption = as;

   // get the meta dll information
   META_GetDLLInfo(&p_version, &p_release_type, &p_build_date, NULL);
   as.printf("%s", p_version);
   meta_dll_version->Caption = as;
   as.printf("%s", p_release_type);
   meta_dll_release_type->Caption = as;
   as.printf("(Build-Date: %s)", p_build_date);
   meta_dll_build_date->Caption = as;

   // get the sp meta dll information
   WM_META_GetDLLInfo_Wrapper(&p_version, &p_release_type, &p_build_date, NULL);
   as.printf("%s", p_version);
   sp_meta_dll_version->Caption = as;
   as.printf("%s", p_release_type);
   sp_meta_dll_release_type->Caption = as;
   as.printf("(Build-Date: %s)", p_build_date);
   sp_meta_dll_build_date->Caption = as;

   if(ToolInfo::IsCustomerVer()){
       check_update_btn->Visible = false;
   }else{
       AutoUpdater::Instance()->AddObserver(this);
       AutoUpdater::Instance()->Start();
   }
}


void TForm_About::newVersionDetected(const std::string &version, const std::string &path){
    this->hasNewVersion = true;
    this->newVersionPath = path;
    check_update_btn->Caption = AnsiString("Latest ver: ")+version.c_str();
}


void __fastcall TForm_About::check_update_btnClick(TObject *Sender)
{
    if(!this->hasNewVersion){
        LOGD("Start checking updates...");
        AutoUpdater::Instance()->Start();
    }else{
        int ret = MessageBox(NULL,"Are you sure to update?","Update Confirm",
            MB_TASKMODAL|MB_ICONINFORMATION|MB_OKCANCEL);
        if(ret == IDOK){
            LOGD(std::string("updating to latest version : ").append(this->newVersionPath).c_str());
            //ShellExecute(NULL, "open", this->newVersionPath.c_str(), NULL, NULL, SW_SHOWNORMAL);
            AutoUpdater::Instance()->ExecuteUpdate();
        }
    }
}

//---------------------------------------------------------------------------

