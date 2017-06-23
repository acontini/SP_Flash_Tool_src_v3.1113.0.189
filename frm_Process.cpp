//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frm_Process.h"
#include "SPFTMsg.h"
#include "main.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrm_Processing *frm_Processing;
//---------------------------------------------------------------------------
__fastcall Tfrm_Processing::Tfrm_Processing(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_Processing::processTimerTimer(TObject *Sender)
{

        // Change the color
        // r s s
        // s r s
        // s s r
        processTimer->Interval = 700;
        red1Shape->Brush->Color = (red1Shape->Brush->Color ^ red2Shape->Brush->Color ^ clRed);
        red2Shape->Brush->Color = (red1Shape->Brush->Color ^ red2Shape->Brush->Color ^ clRed);
        red3Shape->Brush->Color = (red1Shape->Brush->Color ^ red2Shape->Brush->Color ^ clRed);

        return;

}
//---------------------------------------------------------------------------
void __fastcall Tfrm_Processing::FormShow(TObject *Sender)
{
    processTimer->Enabled = true;
    //Locate processing from to the center of the main form
    frm_Processing->Top = MainForm->Top + (MainForm->Height - frm_Processing->Height)/2;
    frm_Processing->Left = MainForm->Left + (MainForm->Width - frm_Processing->Width)/2;
 }
//---------------------------------------------------------------------------
void __fastcall Tfrm_Processing::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    processTimer->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_Processing::FormCreate(TObject *Sender)
{
    WindowProc = SubClassWndProc;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_Processing::SubClassWndProc( Messages::TMessage &Message )
{
    int state = Message.Msg;
    //int testtType = Message.LParam;
    switch (state)
    {
        case AP_SPFT_META_IMEI_BT_WIFI :
        {
            frm_Processing->tipLabel->Caption = "META MODE: Updating IMEI/BT/WIFI now. Please wait for a while...";
            frm_Processing->Visible = false;
            frm_Processing->ShowModal();
        }
        break;
        case AP_SPFT_META_IMEI :
        {
            frm_Processing->tipLabel->Caption = "META MODE: Updating IMEI now. Please wait for a while...";
            frm_Processing->Visible = false;
            frm_Processing->ShowModal();
        }
        break; 
        case AP_SPFT_META_BACKUP_NVRAM :
        {
            frm_Processing->tipLabel->Caption = "META MODE: Backing up NVRAM now. Please wait for a while...";
            frm_Processing->Visible = false;
            frm_Processing->ShowModal();
        }
        break; 
        case AP_SPFT_META_RESTORE_NVRAM :
        {
            frm_Processing->tipLabel->Caption = "META MODE: Restoring NVRAM now. Please wait for a while...";
            frm_Processing->Visible = false;
            frm_Processing->ShowModal();
        }
        break;         
        case AP_SPFT_META_CLEAR_UP:
        {
            frm_Processing->tipLabel->Caption = "Clear-up is processing. Please wait for a while...";
        }
        break;
        case AP_SPFT_META_EXIT:
        {
            frm_Processing->ModalResult = mrOk;
        } 
        break;
        default:
        {
            this->WndProc(Message);
        }
        break;
    }
}
void __fastcall Tfrm_Processing::FormResize(TObject *Sender)
{
    //Locate processing from to the center of the main form
    frm_Processing->Top = MainForm->Top + (MainForm->Height - frm_Processing->Height)/2;
    frm_Processing->Left = MainForm->Left + (MainForm->Width - frm_Processing->Width)/2;
}
//---------------------------------------------------------------------------

