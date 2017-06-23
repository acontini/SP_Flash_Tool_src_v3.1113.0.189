//---------------------------------------------------------------------------

#ifndef frm_IMEIDownloadH
#define frm_IMEIDownloadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
#include "FlashToolTypedefs.h"

/*---------------------------------------------------------------------------*/
class TForm_IMEI_setting : public TForm
{
__published:	// IDE-managed Components
        TEdit *m_edtNVRAMDatabaseFile;
        TLabel *Label1;
        TButton *btnOpenNVRAMDatabase;
        TGroupBox *gbSIM1;
        TCheckBox *cbIMEI1InitialCheck;
        TEdit *m_edtInitialIMEI1;
        TLabel *Label2;
        TCheckBox *cbIMEI1Update;
        TEdit *m_edtIMEI1;
        TLabel *Label3;
        TEdit *m_edtChecksum1;
        TLabel *Label4;
        TGroupBox *gbSIM2;
        TCheckBox *cbIMEI2InitialCheck;
        TEdit *m_edtInitialIMEI2;
        TLabel *Label5;
        TCheckBox *cbIMEI2Update;
        TEdit *m_edtIMEI2;
        TLabel *Label6;
        TEdit *m_edtChecksum2;
        TLabel *Label7;
        TButton *btnOK;
        TButton *btnCancel;
        TCheckBox *cbChecksum;
        TLabel *Label8;
        TOpenDialog *OpenNVRAMdatabaseFileDialog;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall btnOpenNVRAMDatabaseClick(TObject *Sender);
        void __fastcall btnOKClick(TObject *Sender);
        void __fastcall btnCancelClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:
   S_IMEISV_T  m_sIMEISV;
   S_IMEI_T    m_sIMEI;

   S_IMEISV_T  m_sIMEISVupload;
   S_IMEI_T    m_sIMEIupload;
   bool m_b2ndImeiSupport;
   bool m_bCheckChecksum;
   bool m_bIMEI1Check;
   bool m_bIMEI1Update;
   bool m_bIMEI2Check;
   bool m_bIMEI2Update;
   AnsiString m_asNVRAM_DB_File;
   AnsiString m_asInitialIMEI;
   TEdit *m_edtIMEI[2];
   TEdit *m_edtChecksum[2];

public:		// User declarations

        __fastcall TForm_IMEI_setting(TComponent* Owner);
        bool CheckFields(int i);
        void NoCheckFields(int i);
        bool IsValidIMEI(AnsiString imei_str);
        void IMEICheck(TObject *Sender);
        void ReDrawHCIFields(void);
        void ShowAll();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_IMEI_setting *Form_IMEI_setting;
//---------------------------------------------------------------------------
#endif
