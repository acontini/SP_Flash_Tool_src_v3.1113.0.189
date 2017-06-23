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
*  ext_mem1.h
*
* Project:
* --------
*  Flash tool set
*
* Description:
* ------------
*  external memory 1 setup window header file
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
* $Modtime:   Oct 19 2005 11:12:36  $
* $Log:   //mtkvs01/vmdata/flash_tool/archives/EXT_MEM1.H-arc  $
 *
 * Dec 31 2008 MTK02172
 * [STP100001884] [FlashTool] v3.0852.00 release
 * 
 *
 * Dec 3 2007 mtk01413
 * [STP100001568] [FlashTool] v3.0748.0 release
 * New features:
 *  1. USB Download on MT6225/MT6226/MT6227 Series BB
 *  2. GPS Download
 *  3. NOR+SDR in MT6238
 *
 * May 24 2006 mtk01413
 * [STP100000879] FlashTool v2.8.1001 release
 *  1. [FlashTool][NEW] Support 6229 Download, add m_emi_gen_c in DRAM setting
 * 
 *    Rev 1.2   Oct 19 2005 14:47:14   mtk00539
 *  1. [FlashTool][New] Adapt new BROM_DLL&DA v2.7.1008. 
 * Resolution for 141: [FlashTool v2.7.1008][New] Support NFB download and many new features.
 * 
 *    Rev 1.1   Jul 19 2004 02:10:54   mtk00539
 *  1. [FlashTool][New] Adapt new BROM_DLL v2.4.1001 for many features and bug fix.
 *  2. [FlashTool][Enhance] Export COM port read/write timeout setting.
 *  3. [FlashTool][Enhance] Change EMI setting to 32 bits.
 * Resolution for 82: [FlashTool v2.6.1001][New] Adapt with BROM_DLL v2.4.1001 and many enhancement.
 * 
 *    Rev 1.0   Jul 20 2002 19:26:10   admin
 * Initial revision.
*
*------------------------------------------------------------------------------
* Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
*==============================================================================
*******************************************************************************/


//---------------------------------------------------------------------------

#ifndef ext_mem1H
#define ext_mem1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class Text_mem1Form : public TForm
{
__published:	// IDE-managed Components
	TButton *btn_EMI_OK;
	TGroupBox *GroupBox1;
	TPanel *m_Panel_ManualEMI_1;
	TPanel *m_Panel_ManualEMI_2;
	TLabel *Label4;
	TLabel *Label3;
	TButton *btn_EMI_Cancel;
	TLabel *Label1;
	TComboBox *m_Bank1_Option;
	TLabel *Label2;
	TComboBox *m_Bank0_Option;
	TPanel *Panel1;
	TEdit *m_Bank0_EMI;
	TEdit *m_Bank1_EMI;
	TLabel *Label5;
	TLabel *Label6;
        TPanel *Panel2;
    TCheckBox *m_EnableDRAMSetting;
    TPanel *Panel3;
    TEdit *m_emi_gen_a;
    TLabel *Label9;
    TEdit *m_emi_gen_b;
    TLabel *Label15;
    TLabel *Label10;
    TEdit *m_emi_con_i;
    TEdit *m_emi_con_i_ext;
    TLabel *Label11;
    TLabel *Label12;
    TEdit *m_emi_con_k;
    TEdit *m_emi_con_l;
    TLabel *Label13;
    TPanel *Panel4;
    TEdit *m_nand_acccon;
    TLabel *Label14;
    TEdit *m_emi_gen_c;
    TLabel *Label7;
    TComboBox *m_nfi_Option;
    TLabel *Label8;
    TEdit *m_emi_con_m;
    TLabel *Label16;
    TEdit *m_emi_gen_d;
    TLabel *Label17;
    TEdit *m_emi_con_j;
    TLabel *Label18;
    TEdit *m_emi_con_n;
        TLabel *Label19;
        TLabel *Label20;
        TLabel *Label21;
        TLabel *Label22;
        TLabel *Label23;
        TLabel *Label24;
        TLabel *Label25;
        TEdit *m_emi_del_a;
        TEdit *m_emi_del_b;
        TEdit *m_emi_del_c;
        TEdit *m_emi_del_d;
        TEdit *m_emi_del_e;
        TEdit *m_emi_del_f;
        TEdit *m_emi_del_g;
        TLabel *Label26;
        TLabel *Label27;
        TLabel *Label28;
        TEdit *m_emi_del_h;
        TEdit *m_emi_del_i;
        TEdit *m_emi_del_j;
        TLabel *Label29;
        TLabel *Label30;
        TLabel *Label31;
        TLabel *Label32;
        TLabel *Label33;
        TLabel *Label34;
        TLabel *Label35;
        TLabel *Label36;
        TLabel *Label37;
        TEdit *m_emi_arb_a;
        TEdit *m_emi_arb_b;
        TEdit *m_emi_arb_c;
        TEdit *m_emi_arb_d;
        TEdit *m_emi_arb_e;
        TEdit *m_emi_arb_f;
        TEdit *m_emi_arb_g;
        TEdit *m_emi_arb_h;
        TEdit *m_emi_arb_i;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btn_EMI_OKClick(TObject *Sender);
	void __fastcall btn_EMI_CancelClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall m_Bank0_OptionChange(TObject *Sender);
	void __fastcall m_Bank1_OptionChange(TObject *Sender);
    void __fastcall m_EnableDRAMSettingClick(TObject *Sender);
    void __fastcall m_nfi_OptionChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall Text_mem1Form(TComponent* Owner);
    void __fastcall EnableDRAMSetting(bool bEnable);
};
//---------------------------------------------------------------------------
extern PACKAGE Text_mem1Form *ext_mem1Form;
//---------------------------------------------------------------------------
#endif
