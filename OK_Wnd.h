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
*  OK_Wnd.h
*
* Project:
* --------
*  Flash tool set
*
* Description:
* ------------
*  OK window header file 
*
* Author:
* -------
*  FZ Hsu (mtk00303)
*
*==============================================================================
*           HISTORY
* Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
*------------------------------------------------------------------------------
* $Revision:   1.0  $
* $Modtime:   Jul 20 2002 18:18:18  $
* $Log:   //mtkvs01/vmdata/flash_tool/archives/OK_Wnd.h-arc  $
 * 
 *    Rev 1.0   Jul 20 2002 19:26:16   admin
 * Initial revision.
*
*------------------------------------------------------------------------------
* Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
*==============================================================================
*******************************************************************************/

//---------------------------------------------------------------------------

#ifndef OK_WndH
#define OK_WndH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TForm_OK : public TForm
{
__published:	// IDE-managed Components
        TImage *img_OK;
        TTimer *Timer_OK;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall Timer_OKTimer(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
        __fastcall TForm_OK(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_OK *Form_OK;
//---------------------------------------------------------------------------
#endif
