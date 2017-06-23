/******************************************************************************
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
 *  frm_FormatOption.cpp
 *
 * Project:
 * --------
 *  Flash tool set
 *
 * Description:
 * ------------
 *  Form of format option
 *
 * Author:
 * -------
 *  Amos Hsu (mtk00539)
 *
 *==============================================================================
 *           HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
 * $Revision:   1.7  $
 * $Modtime:   Nov 11 2005 11:28:14  $
 * $Log:   //mtkvs01/vmdata/flash_tool/archives/frm_FormatOption.cpp-arc  $
 *
 * Aug 7 2008 MTK01952
 * [STP100001779] [FlashTool] v3.0828.00
 * New features:
 *  1. Add the backup and restore functinality 
 *
 * Aug 16 2006 mtk00539
 * [STP100001057] FlashTool v3.1.00 release
 * Apply new auto format FAT mechanism.
 * 
 *    Rev 1.7   Nov 19 2005 00:58:00   mtk00539
 *  1. [FlashTool][New] Adapt new BROM_DLL&DA v2.7.1011. 
 * Resolution for 150: [FlashTool v2.7.1011][New] Add UID Secure Booting feature and Bug Fix.
 * 
 *    Rev 1.6   Oct 19 2005 14:47:24   mtk00539
 *  1. [FlashTool][New] Adapt new BROM_DLL&DA v2.7.1008. 
 * Resolution for 141: [FlashTool v2.7.1008][New] Support NFB download and many new features.
 * 
 *    Rev 1.5   May 24 2005 20:03:38   mtk00539
 *  1. [FlashTool][New] Reset FAT to factory default setting. 
 *  2. [FlashTool][New] Option to enable/disable resource project id comparison. 
 * Resolution for 116: [FlashTool v2.6.1012][New] Reset FAT to factory default setting.
 * 
 *    Rev 1.4   Jun 16 2004 16:38:14   mtk00539
 *  1. [FlashTool][Enhance] Re-org format option panel to prevent users confused.
 *  2. [FlashTool][Enhance] Do not close OK window when operation is done.
 * Resolution for 78: [FlashTool v2.5.1013][Enhance] Re-org format option panel to prevent users confused.
 * 
 *    Rev 1.3   May 14 2004 17:03:58   mtk00539
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
 *    Rev 1.1   Jun 03 2003 22:24:54   mtk00539
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
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *==============================================================================
 *******************************************************************************/

//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include "frm_FormatOption.h"
#include "DL_Go.h"
#include "FlashToolTypedefs.h"
#include "assert.h"
#include "GlobalData.h"
#include "flashtool_handle.h"
#include "Logger.h"

#ifdef __BORLANDC__
#pragma warn -8004
#endif

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormatOption *FormatOption;


//---------------------------------------------------------------------------
__fastcall TFormatOption::TFormatOption(TComponent* Owner)
	: TForm(Owner)
{
	g_platform_info.addObserver(this);
	InitDefaultFormatArgFuncTable();
}
//---------------------------------------------------------------------------
void __fastcall TFormatOption::OnShow(TObject *Sender) {

	//Initial format flag control flags
	InitFormatFlag(g_bEnableMarkNandBadBlocks);
	//Update platform info again after download handle is ready
	onPlatformChanged();

    if(g_FormatValidation) {
        m_FormatValidation->Checked = true;
    }
    else {
        m_FormatValidation->Checked = false;
    }

       int addressing_type = g_platform_info.getFlashToolStorageConfig().GetAddressingType();
	LOGD("Tracking Addressing Modification: addressing_type(%d)", addressing_type);
	
	FormatStartAddr->Text = "0x" + IntToHex((__int64)g_ulNandFormatStartAddr, addressing_type);
   	FormatLength->Text = "0x" + IntToHex((__int64)g_ulNandFormatLength, addressing_type);
	

  	// save the original groupbox height
  	m_Original_GroupBox_Height = GroupBox1->Height;
   	m_Original_Form_Height = Height;
    m_Original_Panel_ManualFormat2_Height = m_Panel_ManualFormat2->Height;
//  	m_Panel_Offset = m_Panel_ResetToFactoryDefault1->Top-m_Panel_DisableFormat1->Top;

	if(bCallFromFormatButton) {

        GroupBox1->Height -= m_Panel_Offset;
       	Height -= m_Panel_Offset;

//        m_Panel_ResetToFactoryDefault1->Top -= m_Panel_Offset;
//        m_Panel_ResetToFactoryDefault2->Top -= m_Panel_Offset;
    	m_Panel_AutoFormat1->Top -= m_Panel_Offset;
    	m_Panel_AutoFormat2->Top -= m_Panel_Offset;
        m_Panel_ManualFormat1->Top -= m_Panel_Offset;
        m_Panel_ManualFormat2->Top -= m_Panel_Offset;
        /*
    	m_Panel_DisableFormat1->Enabled = false;
    	m_Panel_DisableFormat2->Enabled = false;
        */

    	m_Panel_AutoFormat1->Visible = true;
    	m_Panel_AutoFormat2->Visible = true;
    	m_Panel_ManualFormat1->Visible = true;
    	m_Panel_ManualFormat2->Visible = true;

#if 0
		switch(g_FormatOption) {
		case MANUAL_FORMAT:
			m_Radio_ManualFormatClick(Sender);
			break;
		case AUTO_FORMAT:
			m_Radio_AutoFormatClick(Sender);
			break;
		case RESET_TO_FACTORY:
                        m_Radio_ResetToFactoryDefaultClick(Sender);
                        break;
		default:
	     //		m_Radio_ResetToFactoryDefaultClick(Sender);
                        m_Radio_ManualFormatClick(Sender);
			break;
		}
#endif
             m_Group_EraseFlag->ItemIndex = 0;
		m_Group_AutoFormatFlag->ItemIndex = g_NandAutoFormatFlag;
            //hard code to fix the option on "format whole flash except bootloader"
             m_group_autoformatflag_partial->ItemIndex = 0;
	}
    else {

//    	m_Panel_DisableFormat1->Visible = true;
//   	m_Panel_DisableFormat2->Visible = true;
//    	m_Panel_ResetToFactoryDefault1->Visible = true;
//    	m_Panel_ResetToFactoryDefault2->Visible = true;
    	m_Panel_AutoFormat1->Visible = true;
    	m_Panel_AutoFormat2->Visible = true;
    	m_Panel_ManualFormat1->Visible = true;
    	m_Panel_ManualFormat2->Visible = true;

		switch(g_FormatAfterDownloadOption) {
		case RESET_TO_FACTORY:
			m_Radio_ResetToFactoryDefaultClick(Sender);
			break;
		case AUTO_FORMAT:
			m_Radio_AutoFormatClick(Sender);
			break;
		case MANUAL_FORMAT:
			m_Radio_ManualFormatClick(Sender);
			break;
		case DISABLE_FORMAT:
		default:
			m_Radio_DisableFormatClick(Sender);
			break;
		}

    }

	if( bCallFromFormatButton && (g_platform_info.getFlashToolStorageConfig().IsNandOperation()) && g_bEnableAdvanceOption ) {
        m_Group_EraseFlag->Visible = true;
    }
    else {
       	m_Panel_ManualFormat2->Height -= (m_Group_EraseFlag->Height+10);
        GroupBox1->Height -= (m_Group_EraseFlag->Height+10);
       	Height -= (m_Group_EraseFlag->Height+10);
        m_Group_EraseFlag->Visible = false;
	}

    Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormatOption::btn_FormatOKClick(TObject *Sender)
{
    // Fomat OK button is clicked

	g_ulNandFormatStartAddr = StrToInt64(FormatStartAddr->Text.c_str());
	g_ulNandFormatLength    = StrToInt64(FormatLength->Text.c_str());


    if( !bCallFromFormatButton ) {
#if 0
		if( m_Radio_ResetToFactoryDefault->Checked )
                {
			g_FormatAfterDownloadOption = RESET_TO_FACTORY;

		}
		else
#endif
        if(m_Radio_AutoFormat->Checked) {
			g_FormatAfterDownloadOption = AUTO_FORMAT;
	    }
	    else if(m_Radio_ManualFormat->Checked) {
		    g_FormatAfterDownloadOption = MANUAL_FORMAT;
	    }
#if 0        
            else {
			g_FormatAfterDownloadOption = DISABLE_FORMAT;
            }
#endif
		MainForm->updateMenuItem();
    }
	else {
#if 0
		if( m_Radio_ResetToFactoryDefault->Checked ) {
			g_FormatOption = RESET_TO_FACTORY;
		}
                 /* Peng add auto format*/
		else
#endif        
			if ( m_Radio_AutoFormat->Checked ) {
				g_FormatOption = AUTO_FORMAT;
			} else {
				g_FormatOption = MANUAL_FORMAT;
			}

        switch ( m_Group_EraseFlag->ItemIndex )
        {
            case 1:
                g_EraseFlag = NUTL_FORCE_ERASE;
                break;
            case 2:
                g_EraseFlag = NUTL_MARK_BAD_BLOCK;
                break;
            case 0:
            default:
                g_EraseFlag = NUTL_ERASE;
                break;
        }

       if(m_Group_AutoFormatFlag->Visible == true)

      {
         switch ( m_Group_AutoFormatFlag->ItemIndex ) {
            case 0:
                g_NandAutoFormatFlag = FORMAT_ALL;
                break;
            case 1:
                g_NandAutoFormatFlag = FORMAT_ALL_EXP_BL;
                break;
            default:
                g_NandAutoFormatFlag = FORMAT_ALL_EXP_BL;
                break;            
          }
       }
       else
       {
             g_NandAutoFormatFlag = FORMAT_ALL_EXP_BL;
       }

		if( MT6205 != g_BBCHIP_TYPE ) {
			MainForm->start_DL( true );
		}
        else {
			Form_DL_GO->ShowModal();
        }
	}

	Hide();
}
//---------------------------------------------------------------------------
void __fastcall TFormatOption::btn_FormatCancelClick(TObject *Sender)
{
	Hide();
}

//---------------------------------------------------------------------------

void __fastcall TFormatOption::m_Radio_ManualFormatClick(TObject *Sender)
{
//	m_Radio_DisableFormat->Checked = false;
//	m_Radio_ResetToFactoryDefault->Checked = false;
	m_Radio_AutoFormat->Checked = false;
	m_Radio_ManualFormat->Checked = true;

    FormatStartAddr->Enabled = true;
    FormatLength->Enabled = true;

	m_Group_AutoFormatFlag->Enabled = false;
      m_group_autoformatflag_partial->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormatOption::m_Radio_AutoFormatClick(TObject *Sender)
{
//	m_Radio_DisableFormat->Checked = false;
//	m_Radio_ResetToFactoryDefault->Checked = false;
	m_Radio_AutoFormat->Checked = true;
	m_Radio_ManualFormat->Checked = false;
    
    FormatStartAddr->Enabled = false;
    FormatLength->Enabled = false;

	m_Group_AutoFormatFlag->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormatOption::m_Radio_DisableFormatClick(TObject *Sender)
{
//	m_Radio_DisableFormat->Checked = true;
//	m_Radio_ResetToFactoryDefault->Checked = false;
	m_Radio_AutoFormat->Checked = false;
	m_Radio_ManualFormat->Checked = false;
       m_group_autoformatflag_partial->Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall TFormatOption::m_Radio_ResetToFactoryDefaultClick(TObject *Sender)
{
//	m_Radio_DisableFormat->Checked         = false;
//	m_Radio_ResetToFactoryDefault->Checked = true;
	m_Radio_AutoFormat->Checked            = false;
	m_Radio_ManualFormat->Checked          = false;

}

//---------------------------------------------------------------------------
void __fastcall TFormatOption::FormClose(TObject *Sender, TCloseAction &Action)
{
	Hide();
}
//---------------------------------------------------------------------------
void __fastcall TFormatOption::Hide()
{

    Visible = false;

    // restore the original groupbox height
    GroupBox1->Height = m_Original_GroupBox_Height;
    Height = m_Original_Form_Height;
    m_Panel_ManualFormat2->Height = m_Original_Panel_ManualFormat2_Height;

    if(bCallFromFormatButton) {
//            m_Panel_ResetToFactoryDefault1->Top += m_Panel_Offset;
//            m_Panel_ResetToFactoryDefault2->Top += m_Panel_Offset;
            m_Panel_AutoFormat1->Top += m_Panel_Offset;
            m_Panel_AutoFormat2->Top += m_Panel_Offset;
            m_Panel_ManualFormat1->Top += m_Panel_Offset;
            m_Panel_ManualFormat2->Top += m_Panel_Offset;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormatOption::m_FormatValidationClick( TObject *Sender)
{
    if(m_FormatValidation->Checked) {
        g_FormatValidation = true;
    }
    else {
        g_FormatValidation = false;
    }
}

//update UI accordingly when platform changed.
void TFormatOption::onPlatformChanged(){
	const PlatformInfo& plat_info = g_platform_info;
	std::string storage_name = plat_info.getFlashToolStorageConfig().GetStorageName();
	LOGD("platform name(%s), storage type(%s)", 
		g_platform_info.getLoadPlatformName().c_str(), storage_name.c_str());
	SetAutoFormatRegionStatus(&plat_info);
	if (plat_info.getPlatformConfig().isDefaultSetFormatLength()) {
        DefaultFormatArgDispatcher(storage_name, &plat_info, g_pCurNode->m_dl_handle);
	}

       if(!plat_info.getPlatformConfig().supportAutoFormatAll())
       {
          m_Group_AutoFormatFlag->Visible = false;
          m_group_autoformatflag_partial->Visible = true;
       }
       else
       {
          m_Group_AutoFormatFlag->Visible = true;
          m_group_autoformatflag_partial->Visible = false;
       }
}

void TFormatOption::InitDefaultFormatArgFuncTable(void)
{
	this->storage_format_arg_func_map_.insert(pair<std::string, SetDefaultFormatArgFunc>(std::string("NAND"), SetNandDefaultFormatArg));
	this->storage_format_arg_func_map_.insert(pair<std::string, SetDefaultFormatArgFunc>(std::string("EMMC"), SetEMMCDefaultFormatArg));
	//TODO: Add SDMMC format arg function if SDMMC is different from EMMC
	this->storage_format_arg_func_map_.insert(pair<std::string, SetDefaultFormatArgFunc>(std::string("SDMMC"), SetEMMCDefaultFormatArg));
}

void TFormatOption::DefaultFormatArgDispatcher(const std::string& storage_name, const PlatformInfo* p_platform_info, DL_HANDLE_T p_dl_handle)
{
	std::map<std::string, SetDefaultFormatArgFunc>::iterator it = this->storage_format_arg_func_map_.find(storage_name);
	if ( it != this->storage_format_arg_func_map_.end() ) {
		it->second(this, p_platform_info, p_dl_handle);
	} else {
		LOGW("storage_name(%s) could not default format arg function, nand format arg function is applied.", storage_name.c_str());
		SetNandDefaultFormatArg(this, p_platform_info, p_dl_handle);
	}
}

void TFormatOption::SetAutoFormatRegionStatus(const PlatformInfo* p_platform_info)
{
	bool is_support_auto_format = p_platform_info->getPlatformConfig().supportAutoFormat() && 
		p_platform_info->getFlashToolStorageConfig().IsSupportAutoFormat();
	LOGD("Storage type(%s) (%s) auto format.", 
		p_platform_info->getFlashToolStorageConfig().GetStorageName().c_str(),
		is_support_auto_format ? "supports" : "dose not support");
	p_platform_info->getFlashToolStorageConfig().Dump();
	this->m_Radio_AutoFormat->Enabled = is_support_auto_format;
	this->m_Group_AutoFormatFlag->Enabled = is_support_auto_format;
      this->m_group_autoformatflag_partial->Enabled = is_support_auto_format;
	this->m_Radio_AutoFormat->Checked = is_support_auto_format;
	this->m_Radio_ManualFormat->Checked = !is_support_auto_format;
}

void TFormatOption::SetNandDefaultFormatArg(void* form_arg, const PlatformInfo* p_platform_info, DL_HANDLE_T p_dl_handle/*dummy arg*/)
{
	TFormatOption* format_form = static_cast<TFormatOption*>(form_arg);
	if (p_platform_info->getPlatformConfig().supportLogicalAddress()) {
		if (g_bPhysicallyFormatReadback) {
			g_ulNandFormatLength = 0x20000000;
			format_form->FormatLength->Text = "0x" + IntToHex((__int64) g_ulNandFormatLength, 8);
		} else {
			//whole flash size(0x2000 0000) - resived flash size(2048*64*(80BMT+2PMT))
			g_ulNandFormatLength = 0x1F5C0000;
			format_form->FormatLength->Text = "0x" + IntToHex((__int64) g_ulNandFormatLength, 8);
		}
	}else{
		g_ulNandFormatLength = 0x20000000;
		format_form->FormatLength->Text = "0x" + IntToHex((__int64)g_ulNandFormatLength, 8);
	}
	LOGD("format length(0x%I64x).", g_ulNandFormatLength);
}

void TFormatOption::SetEMMCDefaultFormatArg(void* form_arg, const PlatformInfo* p_platform_info, DL_HANDLE_T p_dl_handle)
{
	TFormatOption* format_form = static_cast<TFormatOption*>(form_arg);
	assert(NULL != p_dl_handle);
	unsigned short rom_count = 0;
	ROM_INFO rom_info; 
	memset(&rom_info, 0, sizeof(ROM_INFO));
	unsigned long long roms_max_length = 0;
	int i = 0;
	if (!DL_GetCount(p_dl_handle, &rom_count)) {
		i = rom_count - 1;
		for (; i >= 0; i--) {
		    if( !DL_Rom_GetInfo(p_dl_handle, i, &rom_info) ) {			
				if (_TRUE == rom_info.item_is_visable) {
					LOGD("rom_name(%s), rom_begin_addr(0x%I64x), rom_end_addr(0x%I64x).",
							rom_info.name, rom_info.begin_addr, rom_info.end_addr);
					roms_max_length = (rom_info.end_addr > 0) ? rom_info.end_addr : rom_info.begin_addr;
					break;
				}
			}
		}
	}

       //EMMC format length must be block(512) align.
	if(0 != (roms_max_length % 512))
	{
              roms_max_length = (roms_max_length/512 - 1) * 512;
	}
	
	g_ulNandFormatLength = roms_max_length;

	int addressing_type = 0;
	addressing_type = g_platform_info.getFlashToolStorageConfig().GetAddressingType();
	LOGD("Tracking Addressing Modification: addressing_type(%d).", addressing_type);
	
	format_form->FormatLength->Text = "0x" + IntToHex(static_cast<__int64>(g_ulNandFormatLength), addressing_type);
	LOGD("format length(0x%I64x).", g_ulNandFormatLength);
}

void TFormatOption::InitFormatFlag(const bool is_mark_bad_block_enable)
{
	m_Group_EraseFlag->Items->Clear();
	if (is_mark_bad_block_enable) {
		m_Group_EraseFlag->Items->Add("Normal Erase (Bad block is skipped)");
		m_Group_EraseFlag->Items->Add("Forcedly Erase (Bad block mark is erased)");
		m_Group_EraseFlag->Items->Add("Mark as Bad Block");
	} else {
		m_Group_EraseFlag->Items->Add("Normal Erase (Bad block is skipped)");
		m_Group_EraseFlag->Items->Add("Forcedly Erase (Bad block mark is erased)");
	}
}
