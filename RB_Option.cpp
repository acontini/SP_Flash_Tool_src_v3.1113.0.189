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
*  RB_Option.cpp
*
* Project:
* --------
*  Flash tool set
*
* Description:
* ------------
*  Readback option window
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
* $Modtime:   Oct 19 2005 11:14:36  $
* $Log:   //mtkvs01/vmdata/flash_tool/archives/RB_Option.cpp-arc  $
 *
 * Aug 30 2007 mtk01413
 * [STP100001497] [FlashTool] v3.2.0 release
 * 
 *
 * Aug 13 2006 mtk01413
 * [STP100001057] FlashTool v3.1.00 release
 * 
 * 
 *    Rev 1.5   Oct 19 2005 14:47:26   mtk00539
 *  1. [FlashTool][New] Adapt new BROM_DLL&DA v2.7.1008. 
 * Resolution for 141: [FlashTool v2.7.1008][New] Support NFB download and many new features.
 * 
 *    Rev 1.4   Oct 01 2003 23:38:18   mtk00539
 * Add packet length in DA_WRITE_CMD and DA_READ_CMD.
 * Resolution for 28: [BootRom v2.1.1001][New] See the reasons below.
 * 
 *    Rev 1.3   Jun 30 2003 19:19:36   mtk00539
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
 *    Rev 1.2   Jan 09 2003 18:11:16   mtk00303
 * fix readback address bug
*
*------------------------------------------------------------------------------
* Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
*==============================================================================
*******************************************************************************/


//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RB_Option.h"
#include "main.h"
#include "GlobalData.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_RB_Option *Form_RB_Option;

bool bReadbackAddrLengthTypeHex;

//---------------------------------------------------------------------------
__fastcall TForm_RB_Option::TForm_RB_Option(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm_RB_Option::bb_ReadBack_OKClick(TObject *Sender)
{
	int ret;
    unsigned long long readback_addr;
    unsigned long readback_len;

    TListItem *pli = MainForm->lv_ReadBack->Selected;
    if ( pli != NULL )
    {
	  if ( ed_RB_StartAddr->Text.Length() > 0 )
        {
		if( bReadbackAddrLengthTypeHex )
            {
			//readback_addr = strtoul(ed_RB_StartAddr->Text.c_str(), NULL, 16);

                  AnsiString addr_text =  ed_RB_StartAddr->Text;

                 if(addr_text.Pos("0x") == 0 && addr_text.Pos("0X") == 0)
                 {
                      addr_text = "0x" + addr_text;
                 }                  
	
		    LOGD("Tracking Addressing Modification: ed_RB_StartAddr->Text(%s).", ed_RB_StartAddr->Text.c_str());
								
		    readback_addr = StrToInt64(ed_RB_StartAddr->Text.c_str());
		    LOGD("Tracking Addressing Modification: readback_addr(%I64u).", readback_addr);
		}
		else
            {
			//readback_addr = strtoul(ed_RB_StartAddr->Text.c_str(), NULL, 10);
			readback_addr = StrToInt64(ed_RB_StartAddr->Text.c_str());
			LOGD("Tracking Addressing Modification: ed_RB_StartAddr->Text(%s).", ed_RB_StartAddr->Text.c_str());
			LOGD("Tracking Addressing Modification: readback_addr(%I64u).", readback_addr);
		}
	}

		if ( ed_RB_Length->Text.Length() > 0 )
            {
                    AnsiString len_text =  ed_RB_Length->Text;

			if ( bReadbackAddrLengthTypeHex )
                   {
                         if(len_text.Pos("0x") == 0 && len_text.Pos("0X") == 0)
                         {
                             len_text = "0x" + len_text;
                         }

				readback_len = strtoul(ed_RB_Length->Text.c_str(), NULL, 16);
           		}
			else
                   {
				readback_len = strtoul(ed_RB_Length->Text.c_str(), NULL, 10);
			} 

                   if(StrToInt64(len_text.c_str())> 0xFFFFFFFF )
                   {
                         LOGD("Readback length has exceeded the avilable value:0x%X", readback_len);

                         std::string msg;
                         sprintf((char*)msg.c_str(), "[ERROR] %s has been exceeded avilable range(0x0~0xFFFFFFFF), \nplease modify the input and try again.", ed_RB_Length->Text.c_str());
                         ShowMessage(AnsiString(msg.c_str()));

                         return;
                   }
		}

		// set read back flag 
		NUTL_ReadFlag_E		read_flag;
		if(m_Radio_ReadPageSpare->Checked)
        {
			read_flag = NUTL_READ_PAGE_SPARE;
		}
		else if(m_Radio_ReadPageOnly->Checked)
        {
			read_flag = NUTL_READ_PAGE_ONLY;
		}
		else if(m_Radio_ReadSpareOnly->Checked)
        {
			read_flag = NUTL_READ_SPARE_ONLY;
		}
		else if(m_Radio_ReadPageWithECC->Checked)
        {
			read_flag = NUTL_READ_PAGE_WITH_ECC;
		}
		else {
			read_flag = NUTL_READ_PAGE_WITH_ECC;
		}

		if(S_DONE != (ret=RB_SetReadbackFlag(g_RB_HANDLE, MainForm->lv_ReadBack->ItemIndex, read_flag)))
        {
			if( S_FTHND_HANDLE_BUSY_NOW == ret )
            {
				ShowMessage("Program is busy! Can not update setting right now.");
			}
			else {
				ShowMessage("Update readback setting fail!");
			}
			goto end;
		}
#if 0       
		if(S_DONE != RB_SetAddrTypeFlag(g_RB_HANDLE,  MainForm->lv_ReadBack->ItemIndex, 
            (g_bPhysicallyFormatReadback ? NUTL_ADDR_PHYSICAL : NUTL_ADDR_LOGICAL)))
        {
			if( S_FTHND_HANDLE_BUSY_NOW == ret )
            {
				ShowMessage("program is busy! can not update setting right now.");
			}
			else {
				ShowMessage("update readback setting fail!");
			}
			goto end;
		}         
        LOG("rb_form: rb_setaddrtypeflag setting: %d", (g_bPhysicallyFormatReadback ? NUTL_ADDR_PHYSICAL : NUTL_ADDR_LOGICAL ));
#endif       
		if ( g_platform_info.getFlashToolStorageConfig().IsNandOperation() )
        {
			// NAND flash read back must be pagesize alignment 
			if( 0 != ( readback_addr%(2048*2) ) )
            {
				/*readback_addr = ((readback_addr/2048)+1)*2048;
				ShowMessage("[WARNING] Read back address is adjusted to 4096 pagesize alignment!"); */
                ShowMessage("[WARNING] Read back start address needs to be aligned to 4096(0x1000)!");
                //return;
			}				
			if( 0 != ( readback_len%(2048*2) ) )
            {
				/*readback_len = ((readback_len/2048)+1)*2048;
				ShowMessage("[WARNING] Read back length is adjusted to 4096 pagesize alignment!");*/
                ShowMessage("[WARNING] Read back length needs to be aligned to 4096(0x1000)!");
                //return;
			}

            if( 0x1000 > readback_len )
            {
                ShowMessage("[WARNING] Read back length must larger than 0x1000!");
                //return;
            }
		}
		else if(g_platform_info.getFlashToolStorageConfig().IsEMMCOperation())
        {
            // EMMC read back must be 512-Bytes aligned
			if( 0 != (readback_addr%512) ) {
				//readback_addr = ((readback_addr/512)+1)*512;
				ShowMessage("[WARNING] Read back address is adjusted to 512-Bytes alignment!");
				return;
			}
			if( 0 != (readback_len%512) ) {
				//readback_len = ((readback_len/512)+1)*512;
				ShowMessage("[WARNING] Read back length is adjusted to 512-Bytes alignment!");
				return;
			}
        }

		if(S_DONE != (ret=RB_SetReadbackAddr(g_RB_HANDLE, MainForm->lv_ReadBack->ItemIndex, readback_addr))) {
			if( S_FTHND_HANDLE_BUSY_NOW == ret )
            {
				ShowMessage("Program is busy! Can not update setting right now.");
			}
			else
            {
				ShowMessage("Update readback setting fail!");
			}
			goto end;
		}

		if(S_DONE != (ret=RB_SetReadbackLength(g_RB_HANDLE, MainForm->lv_ReadBack->ItemIndex, readback_len))) {
			if( S_FTHND_HANDLE_BUSY_NOW == ret )
            {
				ShowMessage("Program is busy! Can not update setting right now.");
			}
			else
            {
				ShowMessage("Update readback setting fail!");
			}
			goto end;
		}

		MainForm->RedrawReadbackList();
    } // if

end:
    Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm_RB_Option::bb_CancelClick(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void _fastcall TForm_RB_Option::KeyPress_Dec(TObject *Sender, char &Key)
{

      if ( Key == '\x1B' )
      {
        dynamic_cast<TEdit *>( Sender)->Undo();
      }
      else if ( Key < '0' || Key > '9' )
      {
         if ( Key !='\b' )
        Key=NULL;
      }

}
//---------------------------------------------------------------------------
void _fastcall TForm_RB_Option::KeyPress_Hex(TObject *Sender, char &Key)
{
      if ( Key == '\x1B' )
      {
        dynamic_cast<TEdit *>( Sender)->Undo();
      }
      else if ( Key < '0' || Key > '9' )
      {
         if ( Key !='\b' &&
              ( Key < 'A' ||  (Key > 'F' && Key < 'a') || Key > 'f'))
        Key=NULL;
      }
}
//---------------------------------------------------------------------------

void __fastcall TForm_RB_Option::rb_ReadbackFlagClick(TObject *Sender)
{
   if ( bReadbackAddrLengthTypeHex )
   { 
     //ed_RB_StartAddr->Text = IntToStr(StrToInt64(ed_RB_StartAddr->Text));
     //ed_RB_Length->Text = IntToStr(strtoul(ed_RB_Length->Text.c_str(), NULL, 16));
     ed_RB_StartAddr->Text = "0x" + IntToHex((__int64)StrToInt64(ed_RB_StartAddr->Text), g_platform_info.getFlashToolStorageConfig().GetAddressingType());
     ed_RB_Length->Text = "0x" + IntToHex((int)strtoul(ed_RB_Length->Text.c_str(), NULL, 10), 8);

     ed_RB_StartAddr->OnKeyPress = KeyPress_Dec;
     ed_RB_Length->OnKeyPress = KeyPress_Dec;

     bReadbackAddrLengthTypeHex = false;
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm_RB_Option::rb_ReadbackHexClick(TObject *Sender)
{
   if ( ! bReadbackAddrLengthTypeHex )
   {
    if(0 == ed_RB_StartAddr->Text.Pos("0x")){
           ed_RB_StartAddr->Text = "0x" + ed_RB_StartAddr->Text;
     }
     LOGD("Tracking Addressing Modification: ed_RB_StartAddr->Text(%s).", ed_RB_StartAddr->Text.c_str());
	 
     ed_RB_StartAddr->Text = "0x" + IntToHex((__int64)StrToInt64(ed_RB_StartAddr->Text), g_platform_info.getFlashToolStorageConfig().GetAddressingType());
     ed_RB_Length->Text = "0x" + IntToHex((int)strtoul(ed_RB_Length->Text.c_str(), NULL, 10), 8);
     ed_RB_StartAddr->OnKeyPress = KeyPress_Hex;
     ed_RB_Length->OnKeyPress = KeyPress_Hex;

     bReadbackAddrLengthTypeHex = true;
   }

}
//---------------------------------------------------------------------------

void __fastcall TForm_RB_Option::FormCreate(TObject *Sender)
{
    bReadbackAddrLengthTypeHex = true;
    rb_ReadbackHex->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm_RB_Option::FormHide(TObject *Sender)
{
	if( m_Group_ReadBackRange->Top != (int)m_Original_Group_ReadBackRange_Top ) {
		m_Group_ReadBackRange->Top = (int)m_Original_Group_ReadBackRange_Top;
	}

	if( g_platform_info.getFlashToolStorageConfig().IsNandOperation() ) {
		m_Group_ReadBackFlag->Visible = true;
	}

}
//---------------------------------------------------------------------------

void __fastcall TForm_RB_Option::FormShow(TObject *Sender)
{
	m_Original_Group_ReadBackRange_Top = m_Group_ReadBackRange->Top;

	if (!g_platform_info.getFlashToolStorageConfig().IsNandOperation()) {
		m_Group_ReadBackRange->Top = m_Group_ReadBackFlag->Top;
		m_Group_ReadBackFlag->Visible = false;
	} else {
        m_Group_ReadBackRange->Top = m_Original_Group_ReadBackRange_Top;
        m_Group_ReadBackFlag->Visible = true;
	}

}
//---------------------------------------------------------------------------



