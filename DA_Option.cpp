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
*  OptiWnd.cpp
*
* Project:
* --------
*  Flash tool set
*
* Description:
* ------------
*  Option config window
*
* Author:
* -------
*  FZ Hsu (mtk00303)
*
*==============================================================================
*           HISTORY
* Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
*------------------------------------------------------------------------------
* $Revision:   1.4  $
* $Modtime:   Oct 19 2005 11:12:10  $
* $Log:   //mtkvs01/vmdata/flash_tool/archives/DA_Option.cpp-arc  $
 *
 * Sep 27 2006 mtk00539
 * [STP100001145] FlashTool v3.1.01 release
 * 
 * 
 *    Rev 1.4   Oct 19 2005 14:47:14   mtk00539
 *  1. [FlashTool][New] Adapt new BROM_DLL&DA v2.7.1008. 
 * Resolution for 141: [FlashTool v2.7.1008][New] Support NFB download and many new features.
 * 
 *    Rev 1.3   Jul 19 2004 02:10:54   mtk00539
 *  1. [FlashTool][New] Adapt new BROM_DLL v2.4.1001 for many features and bug fix.
 *  2. [FlashTool][Enhance] Export COM port read/write timeout setting.
 *  3. [FlashTool][Enhance] Change EMI setting to 32 bits.
 * Resolution for 82: [FlashTool v2.6.1001][New] Adapt with BROM_DLL v2.4.1001 and many enhancement.
 * 
 *    Rev 1.2   Oct 01 2003 23:38:16   mtk00539
 * Add packet length in DA_WRITE_CMD and DA_READ_CMD.
 * Resolution for 28: [BootRom v2.1.1001][New] See the reasons below.
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
 *    Rev 1.0   Jul 26 2002 11:53:18   admin
 * Initial revision.
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

#include "DA_Option.h"
#include "main.h"
#include "ext_mem1.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_DA_Option *Form_DA_Option;

extern bool DEBUG;
extern int iFlashItemIndex;

//---------------------------------------------------------------------------
__fastcall TForm_DA_Option::TForm_DA_Option(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_DA_Option::FormShow(TObject *Sender)
{
	DA_INFO	da_info;
	DA_GetInfo(g_DA_HANDLE, &da_info);
	ed_StartAddr->Text = "0x"+IntToHex((int)da_info.start_addr, 8);
}
//---------------------------------------------------------------------------
void __fastcall TForm_DA_Option::bb_OKClick(TObject *Sender)
{
	DA_SetDefaultStartAddr(g_DA_HANDLE, strtoul(ed_StartAddr->Text.c_str(), NULL, 16));
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm_DA_Option::bb_DA_CancelClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm_DA_Option::ed_StartAddrKeyPress(TObject *Sender, char &Key)
{

      if ( Key == '\x1B' )
      {
         ed_StartAddr->Undo();
      }
      else if ( Key < '0' || Key > '9' )
      {
         if ( Key !='\b' &&
              ( Key < 'A' ||  (Key > 'F' && Key < 'a') || Key > 'f'))
        Key=NULL;
      }


   return;  // OLD
}
//---------------------------------------------------------------------------
