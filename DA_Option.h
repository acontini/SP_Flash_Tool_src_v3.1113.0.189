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
*  OptiWnd.h
*
* Project:
* --------
*  Flash tool set
*
* Description:
* ------------
*  header file of option window
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
* $Modtime:   Jun 23 2003 19:18:28  $
* $Log:   //mtkvs01/vmdata/flash_tool/archives/DA_Option.h-arc  $
 *
 * Sep 27 2006 mtk00539
 * [STP100001145] FlashTool v3.1.01 release
 * 
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

#ifndef DA_OptionH
#define DA_OptionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm_DA_Option : public TForm
{
__published:	// IDE-managed Components
        TBitBtn *bb_OK;
        TBitBtn *bb_DA_Cancel;
        TPageControl *PageControl1;
        TTabSheet *ts_Download;
        TLabel *Label3;
        TMaskEdit *ed_StartAddr;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall bb_OKClick(TObject *Sender);
        void __fastcall bb_DA_CancelClick(TObject *Sender);
        void __fastcall ed_StartAddrKeyPress(TObject *Sender, char &Key);
private:	// User declarations

public:		// User declarations
        __fastcall TForm_DA_Option(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TForm_DA_Option *Form_DA_Option;
//---------------------------------------------------------------------------
#endif
