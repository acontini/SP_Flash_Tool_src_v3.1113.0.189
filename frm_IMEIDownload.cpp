//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frm_IMEIDownload.h"
#include "main.h"
#include "FlashToolTypedefs.h"
#include <inifiles.hpp>
#include "GlobalData.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_IMEI_setting *Form_IMEI_setting;
//---------------------------------------------------------------------------
__fastcall TForm_IMEI_setting::TForm_IMEI_setting(TComponent* Owner)
        : TForm(Owner)
{
    m_edtIMEI[0] = m_edtIMEI1;
    m_edtIMEI[1] = m_edtIMEI2;
    m_edtChecksum[0] = m_edtChecksum1;
    m_edtChecksum[1] = m_edtChecksum2;
    m_asInitialIMEI="12345678";
    m_b2ndImeiSupport=true;
    m_bCheckChecksum=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm_IMEI_setting::FormClose(TObject *Sender,
      TCloseAction &Action)
{
     Hide();        
}
//---------------------------------------------------------------------------
void TForm_IMEI_setting::ShowAll()
{
    m_edtInitialIMEI1->ReadOnly=true;
    m_edtInitialIMEI2->ReadOnly=true;
    m_edtChecksum1->Visible=false;
    Label4->Visible=false;
    m_edtChecksum2->Visible = false;
    Label7->Visible=false;
    cbChecksum->Visible=false;
    Label8->Visible=false;
    m_edtInitialIMEI1->Visible=false;
    Label2->Visible=false;
    m_edtInitialIMEI2->Visible=false;
    Label5->Visible=false;

    m_b2ndImeiSupport=true;
    m_bCheckChecksum=true;

    cbChecksum->Checked=m_bCheckChecksum;
    cbIMEI1InitialCheck->Checked=m_bIMEI1Check;
    cbIMEI1Update->Checked=m_bIMEI1Update;
    cbIMEI2InitialCheck->Checked=m_bIMEI2Check;
    cbIMEI2Update->Checked=m_bIMEI2Update;
    m_edtNVRAMDatabaseFile->Text=m_asNVRAM_DB_File;
    m_edtInitialIMEI1->Text=m_asInitialIMEI;
    m_edtInitialIMEI2->Text=m_asInitialIMEI;
    ReDrawHCIFields();
}
//---------------------------------------------------------------------------
void __fastcall TForm_IMEI_setting::FormShow(TObject *Sender)
{
//    gbSIM2->Visible = false;
 //   m_edtIMEI2->Visible = false;
 //    m_edtChecksum2->Visible = false;
       ShowAll();
      
}
//---------------------------------------------------------------------------
void __fastcall TForm_IMEI_setting::btnOpenNVRAMDatabaseClick(
      TObject *Sender)
{
    static AnsiString asNVRAMdatabase_Path;
    int iLastDel;

    if ( asNVRAMdatabase_Path.Length() > 0 )
    {
       OpenNVRAMdatabaseFileDialog->InitialDir = asNVRAMdatabase_Path;
    }
    else if( 0 < m_edtNVRAMDatabaseFile->Text.Length() )
    {
        iLastDel = m_edtNVRAMDatabaseFile->Text.LastDelimiter("\\:");

        if ( iLastDel > 0)
        {
	        OpenNVRAMdatabaseFileDialog->InitialDir = m_edtNVRAMDatabaseFile->Text.SubString(1, iLastDel-1 );
        }
    }


    if ( OpenNVRAMdatabaseFileDialog->Execute() )
    {
      m_edtNVRAMDatabaseFile->Text = OpenNVRAMdatabaseFileDialog->FileName;
      iLastDel = m_edtNVRAMDatabaseFile->Text.LastDelimiter("\\:");

      if( 0 < iLastDel ){
          asNVRAMdatabase_Path = m_edtNVRAMDatabaseFile->Text.SubString(1, iLastDel-1 );
      }
    }

}
//---------------------------------------------------------------------------
void __fastcall TForm_IMEI_setting::btnOKClick(TObject *Sender)
{
   if ( cbIMEI1InitialCheck->Checked  ||
        cbIMEI1Update->Checked ||
        cbIMEI2InitialCheck->Checked  ||
        cbIMEI2Update->Checked )
   {
       if(m_edtNVRAMDatabaseFile->Text.IsEmpty())
       {
         ShowMessage(" You must open a modem database file before check/update IMEI. ");
         return;
       }
       if(m_edtIMEI1->Text.IsEmpty() && cbIMEI1Update->Checked)
       {
         ShowMessage(" You must type a new IMEI of SIM1 for update. ");
         return;
       }
       if(m_edtIMEI2->Text.IsEmpty() && cbIMEI2Update->Checked)
       {
         ShowMessage(" You must type a new IMEI of SIM2 for update. ");
         return;
       }
       if (cbIMEI1Update->Checked)
       {
           if(!CheckFields(0)){
            return; }
       }

       if (cbIMEI2Update->Checked)
       {
           if(!CheckFields(1)){
            return; }
       }
#if 0
       //if user select IMEI operation,then disable Restore operation
      if( g_backup_restore_state !=  NOACTION )
      {
          g_backup_restore_state =  NOACTION;
      }
#endif
      if( g_nvram_update_state !=  NOACTIONNVRAM )
      {
          g_nvram_update_state  =  NOACTIONNVRAM;
      }

   }
   else
   {
       assert(0);
   }
   m_b2ndImeiSupport = true;

   m_bCheckChecksum=cbChecksum->Checked;
   m_bIMEI1Check=cbIMEI1InitialCheck->Checked;
   m_bIMEI1Update=cbIMEI1Update->Checked;
   m_bIMEI2Check=cbIMEI2InitialCheck->Checked;
   m_bIMEI2Update=cbIMEI2Update->Checked;
   m_asNVRAM_DB_File=m_edtNVRAMDatabaseFile->Text;
   if (!cbIMEI1Update->Checked)
   {
        NoCheckFields(0);
   }
   if (!cbIMEI2Update->Checked)
   {
        NoCheckFields(1);
   }

   MainForm->updateMenuItem();
   Visible = false;
//   MainForm->start_DL(true);
}
//---------------------------------------------------------------------------
bool TForm_IMEI_setting::CheckFields(int i)
{
       AnsiString  text;

        text = m_edtIMEI[i]->Text;
        if (!IsValidIMEI(text))
        {
            IMEICheck(m_edtIMEI[i]);
            return false;
        }    
        strcpy(m_sIMEI.c_imei[i], m_edtIMEI[i]->Text.c_str());
        strcat(m_sIMEI.c_imei[i], m_edtChecksum[i]->Text.c_str());

    return true;
}
void TForm_IMEI_setting::NoCheckFields(int i)
{
    strcpy(m_sIMEI.c_imei[i], m_edtIMEI[i]->Text.c_str());
    strcat(m_sIMEI.c_imei[i], m_edtChecksum[i]->Text.c_str());
}
//---------------------------------------------------------------------------
bool TForm_IMEI_setting::IsValidIMEI(AnsiString imei_str)
{
    if ((imei_str.Length() == MAX_IMEI_DIGIT_LEN) || (imei_str.Length()==14))
    {
        return true;
    }
    else
    {
        return false;
    }
}

//---------------------------------------------------------------------------
void TForm_IMEI_setting::IMEICheck(TObject *Sender)
{
     int  i;
     int  data;
     AnsiString  text;
     TEdit *edit = (TEdit*)Sender;
     char  hint[] = " IMEI digit length shall be equal to 14 or 15 ";

     text = edit->Text;
     if( !IsValidIMEI( text) )
     {
         ShowMessage( hint );
         edit->SetFocus();
     }
}
//---------------------------------------------------------------------------
void TForm_IMEI_setting::ReDrawHCIFields(void)
{
    int imei_num = m_b2ndImeiSupport ? 2 : 1;
    for (int i=0; i<imei_num; i++)
    {
        AnsiString as_imei_checksum(m_sIMEI.c_imei[i]);
        m_edtIMEI[i]->Text = as_imei_checksum.SubString(1, MAX_IMEI_DIGIT_LEN);
        if (as_imei_checksum.Length() > MAX_IMEI_DIGIT_LEN)
        {
            m_edtChecksum[i]->Text =  as_imei_checksum.SubString(MAX_IMEI_DIGIT_LEN+1, 1);
        }
        //IMEICheck(m_edtIMEI[i]);

    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_IMEI_setting::btnCancelClick(TObject *Sender)
{
      Visible = false;        
}
//---------------------------------------------------------------------------

void __fastcall TForm_IMEI_setting::FormCreate(TObject *Sender)
{
    TIniFile *ini;
    ini = new TIniFile(gc_FlashToolINI);
    /****************************************** [IMEI] Section *************************************************/
    Form_IMEI_setting->m_asNVRAM_DB_File = ini->ReadString( "IMEI", "NVRAMdatabase", "" );
    Form_IMEI_setting->m_asInitialIMEI = ini->ReadString( "IMEI", "SIM1initial", m_asInitialIMEI);
    Form_IMEI_setting->m_asInitialIMEI = ini->ReadString( "IMEI", "SIM2initial", m_asInitialIMEI);

    AnsiString as_IMEI1;
    as_IMEI1 = ini->ReadString( "IMEI", "SIM1", "" );
    strcpy(Form_IMEI_setting->m_sIMEI.c_imei[0],as_IMEI1.c_str());
    AnsiString as_IMEI2 = ini->ReadString( "IMEI", "SIM2", "" );
    strcpy(Form_IMEI_setting->m_sIMEI.c_imei[1], as_IMEI2.c_str());

    Form_IMEI_setting->m_bIMEI1Check =  ini->ReadBool ( "IMEI", "checkSIM1", false );
    Form_IMEI_setting->m_bIMEI2Check=  ini->ReadBool ( "IMEI", "checkSIM2", false );
    Form_IMEI_setting->m_bIMEI1Update=  ini->ReadBool ( "IMEI", "updateSIM1", false );
    Form_IMEI_setting->m_bIMEI2Update=  ini->ReadBool ( "IMEI", "updateSIM2", false );
    delete ini;

    ShowAll();
    MainForm->updateMenuItem();
}
//---------------------------------------------------------------------------
