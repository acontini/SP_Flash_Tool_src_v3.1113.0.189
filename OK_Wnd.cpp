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
*  OK_Wnd.cpp
*
* Project:
* --------
*  Flash tool set
*
* Description:
* ------------
*  display a OK window and close it
*
* Author:
* -------
*  FZ Hsu (mtk00303)
*
*==============================================================================
*           HISTORY
* Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
*------------------------------------------------------------------------------
* $Revision:   1.1  $
* $Modtime:   Jun 15 2004 17:43:40  $
* $Log:   //mtkvs01/vmdata/flash_tool/archives/OK_Wnd.cpp-arc  $
 * 
 *    Rev 1.1   Jun 16 2004 16:38:34   mtk00539
 *  1. [FlashTool][Enhance] Re-org format option panel to prevent users confused.
 *  2. [FlashTool][Enhance] Do not close OK window when operation is done.
 * Resolution for 78: [FlashTool v2.5.1013][Enhance] Re-org format option panel to prevent users confused.
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

#include "OK_Wnd.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_OK *Form_OK;
//---------------------------------------------------------------------------
__fastcall TForm_OK::TForm_OK(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_OK::FormShow(TObject *Sender)
{
//
   ClientHeight = img_OK->Picture->Height+1;
   ClientWidth = img_OK->Picture->Width+1;
   if( FLASHTOOL_DOWNLOAD == g_flashtool_function )
   {
      this->Caption = "Download OK";
   }
   else if( FLASHTOOL_FORMAT == g_flashtool_function )
   {
      this->Caption = "Format OK";
   }
   else if (FLASHTOOL_FIRMWARE_UPGRADE == g_flashtool_function)
   {
	  this->Caption = "Firmware Upgrade OK";
   }
   else
   {
      this->Caption="OK";
   }
//   Timer_OK->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm_OK::Timer_OKTimer(TObject *Sender)
{
//
   Timer_OK->Enabled = false;
   this->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm_OK::FormClose(TObject *Sender, TCloseAction &Action)
{
    //clear hardware status bar
     MainForm->HWStatusBarClear();
     //clear speed status
     MainForm->sb_Main->Panels->Items[0]->Text = "";
     //clear time status
     MainForm->sb_Main->Panels->Items[4]->Text = "";
     //clear progress bar
     MainForm->CGauge1->Hint      = "";
     MainForm->CGauge1->Progress  = 0;
     //clear BootRom hint
     MainForm->m_HWStatus->Panels->Items[3]->Text = "";
}
//---------------------------------------------------------------------------

