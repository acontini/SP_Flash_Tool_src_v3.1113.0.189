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
*  Readback option window header file
*
* Author:
* -------
*  FZ Hsu (mtk00303)
*
*==============================================================================
*           HISTORY
* Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
*------------------------------------------------------------------------------
* $Revision:   1.3  $
* $Modtime:   Oct 19 2005 11:14:48  $
* $Log:   //mtkvs01/vmdata/flash_tool/archives/RB_Option.h-arc  $
 * 
 *    Rev 1.3   Oct 19 2005 14:47:26   mtk00539
 *  1. [FlashTool][New] Adapt new BROM_DLL&DA v2.7.1008. 
 * Resolution for 141: [FlashTool v2.7.1008][New] Support NFB download and many new features.
 * 
 *    Rev 1.2   Jun 30 2003 19:19:36   mtk00539
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
 *    Rev 1.1   Jan 09 2003 18:11:14   mtk00303
 * fix readback address bug
*
*------------------------------------------------------------------------------
* Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
*==============================================================================
*******************************************************************************/

//---------------------------------------------------------------------------

#ifndef RB_OptionH
#define RB_OptionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm_RB_Option : public TForm
{
__published:	// IDE-managed Components
        TBitBtn *bb_ReadBack_OK;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TGroupBox *gb_Readback_Parameter_Type;
        TRadioButton *rb_ReadbackHex;
        TRadioButton *rb_ReadbackDec;
        TLabel *lb_StartAddr;
        TEdit *ed_RB_StartAddr;
        TLabel *lb_Length;
        TEdit *ed_RB_Length;
        TBitBtn *bb_Cancel;
    TGroupBox *m_Group_ReadBackFlag;
    TRadioButton *m_Radio_ReadPageOnly;
    TGroupBox *m_Group_ReadBackRange;
    TRadioButton *m_Radio_ReadPageSpare;
    TRadioButton *m_Radio_ReadPageWithECC;
    TRadioButton *m_Radio_ReadSpareOnly;
        void __fastcall bb_ReadBack_OKClick(TObject *Sender);
        void __fastcall bb_CancelClick(TObject *Sender);
        void __fastcall rb_ReadbackFlagClick(TObject *Sender);
        void __fastcall rb_ReadbackHexClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormHide(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
        void _fastcall KeyPress_Hex(TObject *Sender, char &Key);
        void _fastcall KeyPress_Dec(TObject *Sender, char &Key);
		unsigned int m_Original_Group_ReadBackRange_Top;

public:		// User declarations
        __fastcall TForm_RB_Option(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_RB_Option *Form_RB_Option;
//---------------------------------------------------------------------------
#endif

