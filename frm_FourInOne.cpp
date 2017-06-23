//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frm_FourInOne.h"
#include "main.h"
#include "GlobalData.h"

#include <inifiles.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_FourInOne *Form_FourInOne;
//---------------------------------------------------------------------------
__fastcall TForm_FourInOne::TForm_FourInOne(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_FourInOne::FormShow(TObject *Sender)
{
     ShowAll();        
}
//---------------------------------------------------------------------------
void __fastcall TForm_FourInOne::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    Hide();
}
//---------------------------------------------------------------------------
void TForm_FourInOne::ShowAll()
{
    m_edtModemDatabaseFile->Text = m_asModem_Database;
    m_edtAPDatabaseFile->Text = m_asAP_Database;
    m_edtIMEI1_Number->Text = m_asIMEI1_Number;
    m_edtIMEI2_Number->Text = m_asIMEI2_Number;
    m_edtBT_Address->Text = m_asBT_Address;
    m_edtWiFi_Address->Text = m_asWiFi_Address;
}
void __fastcall TForm_FourInOne::btnModemDatabaseClick(TObject *Sender)
{
    int iLastDel;

    if ( m_asModem_Path.Length() > 0 )
    {
       OpenModemDialog->InitialDir = m_asModem_Path;
       OpenModemDialog->FileName = "";
    }
    else if( 0 < m_edtModemDatabaseFile->Text.Length() )
    {
        iLastDel = m_edtModemDatabaseFile->Text.LastDelimiter("\\:");

        if ( iLastDel > 0)
        {
            OpenModemDialog->InitialDir = m_edtModemDatabaseFile->Text.SubString(1, iLastDel-1 );
        }
    }


    if ( OpenModemDialog->Execute() )
    {
        m_edtModemDatabaseFile->Text = OpenModemDialog->FileName;
        iLastDel = m_edtModemDatabaseFile->Text.LastDelimiter("\\:");

        if( 0 < iLastDel )
        {
            m_asModem_Path = m_edtModemDatabaseFile->Text.SubString(1, iLastDel-1 );
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_FourInOne::btnAPDatabaseClick(TObject *Sender)
{
    int iLastDel;

    if ( m_asAP_Path.Length() > 0 )
    {
       OpenAPDialog->InitialDir = m_asAP_Path;
       OpenAPDialog->FileName = "";
    }
    else if( 0 < m_edtAPDatabaseFile->Text.Length() )
    {
        iLastDel = m_edtAPDatabaseFile->Text.LastDelimiter("\\:");

        if ( iLastDel > 0)
        {
	        OpenAPDialog->InitialDir = m_edtAPDatabaseFile->Text.SubString(1, iLastDel-1 );
        }
    }


    if ( OpenAPDialog->Execute() )
    {
        m_edtAPDatabaseFile->Text = OpenAPDialog->FileName;
        iLastDel = m_edtAPDatabaseFile->Text.LastDelimiter("\\:");

        if( 0 < iLastDel )
        {
            m_asAP_Path = m_edtAPDatabaseFile->Text.SubString(1, iLastDel-1 );
        }
    }

}
//---------------------------------------------------------------------------
void __fastcall TForm_FourInOne::btnOKClick(TObject *Sender)
{

    m_asModem_Database = m_edtModemDatabaseFile->Text;
    m_asAP_Database = m_edtAPDatabaseFile->Text;
    m_asIMEI1_Number = m_edtIMEI1_Number->Text;
    m_asIMEI2_Number = m_edtIMEI2_Number->Text;
    m_asBT_Address = m_edtBT_Address->Text;
    m_asWiFi_Address = m_edtWiFi_Address->Text;

    m_bWriteIMEI1 = cbIMEI1->Checked ? true : false;
    m_bWriteIMEI2 = cbIMEI2->Checked ? true : false;
    m_bWriteBTAddr = cbBTAddr->Checked ? true : false;
    m_bWriteWIFIAddr = cbWIFIAddr->Checked ? true : false;   
    
    strcpy(m_sIMEI.c_imei[0], m_edtIMEI1_Number->Text.c_str());
    strcpy(m_sIMEI.c_imei[1], m_edtIMEI2_Number->Text.c_str());

    if(m_edtModemDatabaseFile->Text.IsEmpty() &&
           (cbIMEI1->Checked || cbIMEI2->Checked))
    {
         ShowMessage("You must open a Modem database file!");
         return;
    }
    if(m_edtAPDatabaseFile->Text.IsEmpty() &&
           (cbBTAddr->Checked || cbWIFIAddr->Checked))
    {
         ShowMessage("You must open a AP Modem database file!");
         return;
    }

    if(cbIMEI1->Checked)
    {
         if ( !VerifyValidationOfIMEI(m_asIMEI1_Number, 1) )
         {
            return;
         }
    }
    if(cbIMEI2->Checked)
    {
         if ( !VerifyValidationOfIMEI(m_asIMEI2_Number, 2) )
         {
            return;
         }         
    }

    if(cbBTAddr->Checked)
    {
         if ( m_edtBT_Address->Text.IsEmpty() )
         {
            ShowMessage("BT address text box is NULL. You must type a new BT address!");
            return;
         }
         if ( !VerifyValidationOfBTWiFiAddr(m_asBT_Address) )
         {
            return;
         }          
    }
    if(cbWIFIAddr->Checked)
    {
         if ( m_edtWiFi_Address->Text.IsEmpty() )
         {
            ShowMessage("WiFi address text box is NULL. You must type a new WiFi address!");
            return;
         }
         if ( !VerifyValidationOfBTWiFiAddr(m_asWiFi_Address) )
         {
            return;
         }          
    }
    if(!cbIMEI1->Checked &&
       !cbIMEI2->Checked &&
       !cbBTAddr->Checked &&
       !cbWIFIAddr->Checked )
    {
        ShowMessage("You must at least check one item to update!");
        return;
    }

    //update BACKUP.ini for IMEI writing
    if(cbIMEI1->Checked || cbIMEI2->Checked){
        //TIniFile *ini = new TIniFile(gc_METABackupINI);
        TIniFile *ini = new TIniFile(gc_FlashToolINI);
        if(cbIMEI1->Checked){
            LOGD("writing IMEI1 to FlashTool.INI");
            ini->WriteString("IMEI","IMEI1",m_edtIMEI1_Number->Text.c_str());
        }else{
            ini->DeleteKey("IMEI","IMEI1");
        }

        if(cbIMEI2->Checked){
            LOGD("writing IMEI2 to FlashTool.INI");
            ini->WriteString("IMEI","IMEI2",m_edtIMEI2_Number->Text.c_str());
        }else{
            ini->DeleteKey("IMEI","IMEI2");
        }
        delete ini;
    }

    Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm_FourInOne::btnCancelClick(TObject *Sender)
{
    g_nvram_update_state = NOACTIONNVRAM;
    MainForm->updateMenuItem();
    Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm_FourInOne::FormCreate(TObject *Sender)
{
    TIniFile *ini;
    ini = new TIniFile(gc_FlashToolINI);
    /****************************************** [Update NVRAM] Section *************************************************/
    m_asModem_Database = ini->ReadString( "NVRAM", "ModemDatabase", "" );
    m_asAP_Database = ini->ReadString( "NVRAM", "ApDatabase", "" );
    m_asIMEI1_Number = ini->ReadString( "IMEI", "IMEI1", "" );
    m_asIMEI2_Number =ini->ReadString( "IMEI", "IMEI2", "" );
    m_asBT_Address = ini->ReadString( "NVRAM", "BtAddress", "" );
    m_asWiFi_Address = ini->ReadString( "NVRAM", "WiFiAddress", "" );
    m_bWriteIMEI1 = ini->ReadBool ( "NVRAM", "CheckIMEI1", false );
    m_bWriteIMEI2 = ini->ReadBool ( "NVRAM", "CheckIMEI2", false );
    m_bWriteBTAddr = ini->ReadBool ( "NVRAM", "CheckBTAddr", false );
    m_bWriteWIFIAddr = ini->ReadBool ( "NVRAM", "CheckWIFIAddr", false );
    g_nvram_update_state = (NVRAM_UPDATE_STATE_E)ini->ReadInteger( "NVRAM", "UpdateNVRAMState",   0 );

    cbIMEI1->Checked = m_bWriteIMEI1;
    cbIMEI2->Checked = m_bWriteIMEI2;
    cbBTAddr->Checked = m_bWriteBTAddr;
    cbWIFIAddr->Checked = m_bWriteWIFIAddr;

    delete ini;
    ShowAll();
    MainForm->updateMenuItem();          
}
//---------------------------------------------------------------------------
bool __fastcall TForm_FourInOne::VerifyValidationOfIMEI(const AnsiString& szIMEI, const int nNum)
{
    char cIMEILog[127] = {'\0'};

    if ( szIMEI.IsEmpty() )
    {
        sprintf(cIMEILog, 
            "[IMEI%d Hint] IMEI%d of SIM%d text box is NULL. You must type a new IMEI value of SIM%d!",
            nNum, nNum, nNum, nNum);
        ShowMessage(cIMEILog);
        return false;
    }  
    
    if ( (szIMEI.Length() < 14) || (szIMEI.Length() >15) )
    {
        sprintf(cIMEILog, 
            "[IMEI%d Hint] IMEI%d length need to be equal to 14 or 15.",
            nNum, nNum);
        ShowMessage(cIMEILog);    
        return false;
    }
    char cIMEI[16] = {'\0'};
    strncpy(cIMEI, szIMEI.c_str(), szIMEI.Length());
    for (int i = 0; i < szIMEI.Length(); i++)
    {
        if ( '0' <= cIMEI[i] && cIMEI[i] <= '9' )
        {
            continue;
        }
        else
        {
            sprintf(cIMEILog, 
                "[IMEI%d Hint] IMEI%d number should only contain NUMBERs[0-9]!",
                nNum, nNum, nNum, nNum);
            ShowMessage(cIMEILog);
            return false;
        }
    }
    return true;
}
//---------------------------------------------------------------------------
bool __fastcall TForm_FourInOne::VerifyValidationOfBTWiFiAddr(const AnsiString& szAddr)
{
    if ( 12 != szAddr.Length() )
    {
        ShowMessage("BT/Wifi address length need to be equal to 12!");
        return false;
    }
    char cIMEI[16] = {'\0'};
    strncpy(cIMEI, szAddr.c_str(), szAddr.Length());
    for (int i = 0; i < szAddr.Length(); i++)
    {
        if ( ('0' <= cIMEI[i] && cIMEI[i] <= '9') || ('a' <= cIMEI[i] && cIMEI[i] <= 'f') || ('A' <= cIMEI[i] && cIMEI[i] <= 'F') )
        {
            continue;
        }
        else
        {
            ShowMessage("BT/Wifi address should only contain HEX NUMBERs[0-9] or CHARACTERs[a-f]!");
            return false;
        }
    }
    return true;
}
//---------------------------------------------------------------------------

