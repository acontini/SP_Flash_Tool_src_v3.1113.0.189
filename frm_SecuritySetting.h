//---------------------------------------------------------------------------

#ifndef frm_SecuritySettingH
#define frm_SecuritySettingH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
#include "main.h"
#include <Menus.hpp>

using std::vector;

class Tm_SecuritySetting : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *m_GroupSecuritySetting;
	TButton *m_OK;
	TButton *m_Cancel;
	TPopupMenu *m_SecuritySettingRightClick;
	TMenuItem *m_UncheckAll;
	TMenuItem *m_CheckAll;
    TCheckBox *m_Lockdown_CheckBox;
	void __fastcall m_OKClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall m_CancelClick(TObject *Sender);
    void __fastcall m_CheckAllClick(TObject *Sender);
    void __fastcall m_UncheckAllClick(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall m_Lockdown_CheckBoxClick( TObject *Sender);
private:	// User declarations
    vector<TCheckBox*> m_pCheckBoxList;
    void CreateCheckBoxList(int count);
    void DestroyCheckBoxList(void);
    void SyncCheckBoxList(bool isLockdown);
public:		// User declarations
	__fastcall Tm_SecuritySetting(TComponent* Owner);
	void __fastcall Display(void);
};
//---------------------------------------------------------------------------
extern PACKAGE Tm_SecuritySetting *m_SecuritySetting;
//---------------------------------------------------------------------------
#endif
