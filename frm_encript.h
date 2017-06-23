//---------------------------------------------------------------------------

#ifndef frm_encriptH
#define frm_encriptH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
#include "main.h"
//---------------------------------------------------------------------------
class Tfrm_encription : public TForm

{
__published:	// IDE-managed Components
        TLabel *lb_Encription;
        TEdit *ed_Encription;
        TButton *btn_encription_ok;
        TButton *btn_encription_cancel;
        void __fastcall btn_encription_cancelClick(TObject *Sender);
        void __fastcall btn_encription_okClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall ed_EncriptionKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
        AnsiString m_strPassword;
	 AnsiString m_strPassword_day;
	 AnsiString m_strPassword_week;
	 AnsiString m_strPassword_month;
public:		// User declarations
        __fastcall Tfrm_encription(TComponent* Owner);
        bool Tfrm_encription::CheckPassword();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_encription *frm_encription;
//---------------------------------------------------------------------------
#endif
