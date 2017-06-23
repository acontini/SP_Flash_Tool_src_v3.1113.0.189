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
 *  frm_FormatOption.h
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
 * $Modtime:   Dec 15 2005 08:44:58  $
 * $Log:   //mtkvs01/vmdata/flash_tool/archives/frm_FormatOption.h-arc  $
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
 * Aug 16 2006 mtk00539
 * [STP100001057] FlashTool v3.1.00 release
 * Apply new auto format FAT mechanism.
 * 
 *    Rev 1.7   Dec 29 2005 10:57:24   mtk00539
 *  1. [FlashTool] Add download history feature.
 * Resolution for 156: [FlashTool v2.7.1013][BUG FIX] Fix BootROM start command failure while manually selecting NMT6226 or MT6227 baseband chip.
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
 *    Rev 1.4   Jun 16 2004 16:38:32   mtk00539
 *  1. [FlashTool][Enhance] Re-org format option panel to prevent users confused.
 *  2. [FlashTool][Enhance] Do not close OK window when operation is done.
 * Resolution for 78: [FlashTool v2.5.1013][Enhance] Re-org format option panel to prevent users confused.
 * 
 *    Rev 1.3   May 14 2004 17:04:20   mtk00539
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

#ifndef frm_FormatOptionH
#define frm_FormatOptionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <string>

class PlatformInfo;
typedef struct DL_HANDLE *  DL_HANDLE_T;

typedef void (*SetDefaultFormatArgFunc)(void* form_arg, const PlatformInfo* p_platform_info, DL_HANDLE_T p_dl_handle/*dummy arg*/);

//---------------------------------------------------------------------------
class TFormatOption : public TForm, public IPlatformOb
{
__published:	// IDE-managed Components
	TLabeledEdit *FormatStartAddr;
	TLabeledEdit *FormatLength;
	TButton *btn_FormatOK;
	TButton *btn_FormatCancel;
	TGroupBox *GroupBox1;
	TRadioButton *m_Radio_AutoFormat;
	TPanel *m_Panel_AutoFormat2;
	TPanel *m_Panel_AutoFormat1;
	TPanel *m_Panel_ManualFormat1;
	TRadioButton *m_Radio_ManualFormat;
	TPanel *m_Panel_ManualFormat2;
	TLabel *Label4;
    TLabel *Label8;
    TCheckBox *m_FormatValidation;
    TRadioGroup *m_Group_EraseFlag;
    TRadioGroup *m_Group_AutoFormatFlag;
        TRadioGroup *m_group_autoformatflag_partial;
    void __fastcall btn_FormatOKClick(TObject *Sender);
    void __fastcall btn_FormatCancelClick(TObject *Sender);
    void __fastcall OnShow(TObject *Sender);
    void __fastcall m_Radio_ManualFormatClick(TObject *Sender);
    void __fastcall m_Radio_AutoFormatClick(TObject *Sender);
    void __fastcall m_Radio_DisableFormatClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall Hide();
    void __fastcall m_Radio_ResetToFactoryDefaultClick(TObject *Sender);
    void __fastcall m_FormatValidationClick(TObject *Sender);


private:	// User declarations
	unsigned int m_Original_GroupBox_Height;
	unsigned int m_Original_Form_Height;
    unsigned int m_Original_Panel_ManualFormat2_Height;
	unsigned int m_Panel_Offset;
public:		// User declarations
    bool	bCallFromFormatButton;
	__fastcall TFormatOption(TComponent* Owner);

	void onPlatformChanged();
private:
	void InitDefaultFormatArgFuncTable(void);
	void DefaultFormatArgDispatcher(const std::string& storage_name, const PlatformInfo* p_platform_info, DL_HANDLE_T p_dl_handle);
	void SetAutoFormatRegionStatus(const PlatformInfo* p_platform_info);
	static void SetNandDefaultFormatArg(void* form_arg, const PlatformInfo* p_platform_info, DL_HANDLE_T p_dl_handle/*dummy arg*/);
	static void SetEMMCDefaultFormatArg(void* form_arg, const PlatformInfo* p_platform_info, DL_HANDLE_T p_dl_handle);
	//Add to control format flag
	void InitFormatFlag(const bool is_mark_bad_block_enable);

private:
	std::map<std::string, SetDefaultFormatArgFunc> storage_format_arg_func_map_;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormatOption *FormatOption;
//---------------------------------------------------------------------------
#endif
