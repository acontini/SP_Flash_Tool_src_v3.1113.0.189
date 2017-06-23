//---------------------------------------------------------------------------

#ifndef frm_FourInOneH
#define frm_FourInOneH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>

#include "FlashToolTypedefs.h"

//---------------------------------------------------------------------------
class TForm_FourInOne : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TLabel *Label1;
        TEdit *m_edtModemDatabaseFile;
        TButton *btnModemDatabase;
        TLabel *Label2;
        TEdit *m_edtAPDatabaseFile;
        TButton *btnAPDatabase;
        TGroupBox *GroupBox2;
        TCheckBox *cbIMEI1;
        TCheckBox *cbIMEI2;
        TEdit *m_edtIMEI1_Number;
        TEdit *m_edtIMEI2_Number;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TGroupBox *GroupBox3;
        TLabel *Label7;
        TCheckBox *cbBTAddr;
        TEdit *m_edtBT_Address;
        TGroupBox *GroupBox4;
        TLabel *Label6;
        TCheckBox *cbWIFIAddr;
        TEdit *m_edtWiFi_Address;
        TButton *btnOK;
        TButton *btnCancel;
        TOpenDialog *OpenModemDialog;
        TOpenDialog *OpenAPDialog;
    TLabel *Label8;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall btnModemDatabaseClick(TObject *Sender);
        void __fastcall btnAPDatabaseClick(TObject *Sender);
        void __fastcall btnOKClick(TObject *Sender);
        void __fastcall btnCancelClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
        bool __fastcall VerifyValidationOfIMEI(const AnsiString& szIMEI, const int nNum);
        bool __fastcall VerifyValidationOfBTWiFiAddr(const AnsiString& szAddr);

public:		// User declarations
        AnsiString m_asModem_Path;
        AnsiString m_asAP_Path;
        AnsiString m_asModem_Database;
        AnsiString m_asAP_Database;
        AnsiString m_asIMEI1_Number;
        AnsiString m_asIMEI2_Number;
        AnsiString m_asBT_Address;
        AnsiString m_asWiFi_Address;
        bool m_bWriteIMEI1;
        bool m_bWriteIMEI2;
        bool m_bWriteBTAddr;
        bool m_bWriteWIFIAddr;

        S_IMEISV_T  m_sIMEISV;
        S_IMEI_T    m_sIMEI;

        bool m_b2ndImeiSupport;
        __fastcall TForm_FourInOne(TComponent* Owner);
        void ShowAll();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_FourInOne *Form_FourInOne;
//---------------------------------------------------------------------------
#endif
