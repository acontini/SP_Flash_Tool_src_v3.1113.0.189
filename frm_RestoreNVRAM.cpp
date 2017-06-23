//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frm_RestoreNVRAM.h"
#include "main.h"
#include "FlashToolTypedefs.h"
#include <inifiles.hpp>
#include "GlobalData.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_Backup_Restore_NVRAM *Form_Backup_Restore_NVRAM;
//---------------------------------------------------------------------------
__fastcall TForm_Backup_Restore_NVRAM::TForm_Backup_Restore_NVRAM(TComponent* Owner)
        : TForm(Owner), SUFFIX_DAT("dat"), SUFFIX_MAP("map")
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_Backup_Restore_NVRAM::btnSaveNvramDatafileClick(TObject *Sender)
{
    int iLastDel;
    AnsiString backupFileDes;

    if ( asNVRAMfile_Path.Length() > 0 )
    {
       SaveNVRAMdatafileDialog->InitialDir = asNVRAMfile_Path;
       SaveNVRAMdatafileDialog->FileName = "";
    }
    else if( 0 < m_edtNVRAMDataFile->Text.Length() )
    {
        iLastDel = m_edtNVRAMDataFile->Text.LastDelimiter("\\:");

        if ( iLastDel > 0)
        {
	        SaveNVRAMdatafileDialog->InitialDir = m_edtNVRAMDataFile->Text.SubString(1, iLastDel-1 );
        }
    }
 
    if ( SaveNVRAMdatafileDialog->Execute() )
    {
        BackupAdjustFileName(SaveNVRAMdatafileDialog->FileName, SUFFIX_DAT, backupFileDes);
        m_edtNVRAMDataFile->Text = SaveNVRAMdatafileDialog->FileName;

        iLastDel = m_edtNVRAMDataFile->Text.LastDelimiter("\\:");
        if( 0 < iLastDel ){
          asNVRAMfile_Path = m_edtNVRAMDataFile->Text.SubString(1, iLastDel-1 );
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_Backup_Restore_NVRAM::btnSaveNvramMapfileClick(TObject *Sender)
{
    int iLastDel;
    AnsiString backupFileDes;

    if ( asNVRAMfile_Path.Length() > 0 )
    {
        SaveNVRAMmapfileDialog->InitialDir = asNVRAMfile_Path;
        SaveNVRAMmapfileDialog->FileName = "";
    }
    else if( 0 < m_edtNVRAMmapFile->Text.Length() )
    {
        iLastDel = m_edtNVRAMmapFile->Text.LastDelimiter("\\:");

        if ( iLastDel > 0)
        {
	        SaveNVRAMmapfileDialog->InitialDir = m_edtNVRAMmapFile->Text.SubString(1, iLastDel-1 );
        }
    }  

    if ( SaveNVRAMmapfileDialog->Execute() )
    {
        BackupAdjustFileName(SaveNVRAMmapfileDialog->FileName, SUFFIX_MAP, backupFileDes);
        m_edtNVRAMmapFile->Text = SaveNVRAMmapfileDialog->FileName;
        iLastDel = m_edtNVRAMmapFile->Text.LastDelimiter("\\:");

        if( 0 < iLastDel ){
            asNVRAMfile_Path = m_edtNVRAMmapFile->Text.SubString(1, iLastDel-1 );
        }    
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_Backup_Restore_NVRAM::btnOKClick(TObject *Sender)
{
    if(m_edtNVRAMDataFile->Text.IsEmpty())
       {
         ShowMessage(" You must save a NVRAM data file before Backup_Restore. ");
         return;
       }
    if(m_edtNVRAMmapFile->Text.IsEmpty())
       {
         ShowMessage(" You must save a NVRAM map file before Backup_Restore. ");
         return;
       }

    int iLastDel;
    iLastDel = m_edtNVRAMmapFile->Text.LastDelimiter("\\:");
    if( 0 < iLastDel ){
        asNVRAMfile_Path = m_edtNVRAMmapFile->Text.SubString(1, iLastDel-1 );
    }

    //if you select Restore,then disable IMEI operation
    if( g_nvram_update_state !=  NOACTIONNVRAM )
    {
        g_nvram_update_state  =  NOACTIONNVRAM;
    }
    
    m_asNVRAM_data_File= m_edtNVRAMDataFile->Text;
    m_asNVRAM_map_File = m_edtNVRAMmapFile->Text;

    MainForm->updateMenuItem();
    Visible = false;

}
//---------------------------------------------------------------------------
void __fastcall TForm_Backup_Restore_NVRAM::btnCancelClick(TObject *Sender)
{
    g_backup_restore_state =  NOACTION;
    MainForm->updateMenuItem();
    Visible = false;         
}
//---------------------------------------------------------------------------
void __fastcall TForm_Backup_Restore_NVRAM::FormCreate(TObject *Sender)
{
    TIniFile *ini;
    ini = new TIniFile(gc_FlashToolINI);
    /****************************************** [BACKUP_FORMAT_DOWNLOAD_RESTORE NVRAM] Section *************************************************/
    Form_Backup_Restore_NVRAM->m_asNVRAM_data_File = ini->ReadString( "BACKUP_FORMAT_DOWNLOAD_RESTORE", "backup_restore_path", "" );
    Form_Backup_Restore_NVRAM->m_asNVRAM_data_File = ini->ReadString( "BACKUP_FORMAT_DOWNLOAD_RESTORE", "datafile", "" );
    Form_Backup_Restore_NVRAM->m_asNVRAM_map_File = ini->ReadString( "BACKUP_FORMAT_DOWNLOAD_RESTORE", "mapfile", "");
    g_backup_restore_state = (BACKUP_RESTORE_STATE_E)ini->ReadInteger( "BACKUP_FORMAT_DOWNLOAD_RESTORE", "BackupRestoreState",   0 );

    delete ini;
    ShowAll();
    MainForm->updateMenuItem();        
}
//---------------------------------------------------------------------------
void TForm_Backup_Restore_NVRAM::ShowAll()
{

   m_edtNVRAMDataFile->Text = m_asNVRAM_data_File;
   m_edtNVRAMmapFile->Text = m_asNVRAM_map_File;

}
//---------------------------------------------------------------------------
void __fastcall TForm_Backup_Restore_NVRAM::FormShow(TObject *Sender)
{
    ShowAll();
}
//---------------------------------------------------------------------------

void __fastcall TForm_Backup_Restore_NVRAM::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    Hide();        
}
//---------------------------------------------------------------------------

void __fastcall TForm_Backup_Restore_NVRAM::BackupAdjustFileName(const AnsiString&
        backupFileSrc, const char* suffix, AnsiString& backupFileDes)
{
    int pos = backupFileSrc.AnsiPos(".");
    if( pos != 0)
    {
       if(backupFileSrc.SubString(pos + 1,3) != suffix)
       {
            backupFileDes = backupFileSrc.SubString(0,pos) + suffix;
            return;
       }
       else
       {
            return;
       }
    }
    else
    {
        backupFileDes = backupFileSrc + "." + suffix;
        return;
    }
}
//---------------------------------------------------------------------------
