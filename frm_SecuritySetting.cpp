//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frm_SecuritySetting.h"
#include "main.h"
#include "AndroidImageInfo.h"
#include "ImageMapRule.h"
#pragma warn -8004 
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tm_SecuritySetting *m_SecuritySetting;
//---------------------------------------------------------------------------
__fastcall Tm_SecuritySetting::Tm_SecuritySetting(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tm_SecuritySetting::Display(void)
{
    static bool isFirstTimeDisplay = true;
    if(!isFirstTimeDisplay)
    {
        m_Lockdown_CheckBox->Checked = !g_ParamsecBitCtrlYuSu.m_lockdown;
        if(m_Lockdown_CheckBox->Checked)
        {
            SyncCheckBoxList(m_Lockdown_CheckBox->Checked);
        }
        else
        {
            for(unsigned int i = 0; i < m_pCheckBoxList.size(); i++)
            {
                m_pCheckBoxList.at(i)->Checked =
                    !g_ParamsecBitCtrlYuSu.img_info[i].m_disable_download;
            }
        }
    }
    else
    {
        isFirstTimeDisplay = false;
        return;
    }
}
//---------------------------------------------------------------------------
void __fastcall Tm_SecuritySetting::m_OKClick(TObject *Sender)
{

    g_ParameterType = PAPAM_SEC_ROM_LOCK;
    
    g_ParamsecBitCtrlYuSu.m_lockdown = this->m_Lockdown_CheckBox->Checked ? 0 : 1;

    AnsiString ss = "";
    AnsiString ssEx = "";
    AnsiString ssImg = "";
    AnsiString sLockAll = "LOCK ALL";
    const unsigned char COLUMN_LEN = 6;
    const char SZ_LOCK_TRUE[] = ": Y; ";
    const char SZ_LOCK_FALSE[] = ": N; ";
    bool isAllImgUnChecked = true;

    if ( !g_ParamsecBitCtrlYuSu.m_lockdown )
    {
        sLockAll += SZ_LOCK_TRUE;
        ss += sLockAll;
        MainForm->ed_sec_setting_Write->Text = ss;
        MainForm->ed_sec_setting_Write_Ex->Text = ssEx;
    }
    else
    {
        for(unsigned int i = 0; i < m_pCheckBoxList.size(); i++)
        {
            const AndroidImageInfo &imageRef =
            		GetAndroidImageInfoTable().GetImageByAndroidFileIndex(i);
            g_ParamsecBitCtrlYuSu.img_info[i].m_disable_download  = !m_pCheckBoxList.at(i)->Checked;
            g_ParamsecBitCtrlYuSu.img_info[i].image_type = imageRef.type;
            isAllImgUnChecked = isAllImgUnChecked &&
                (g_ParamsecBitCtrlYuSu.img_info[i].m_disable_download);

            if(i < COLUMN_LEN)
            {
                ssImg = imageRef.romName.c_str();
                ssImg +=
                    (!g_ParamsecBitCtrlYuSu.img_info[i].m_disable_download)?
                    SZ_LOCK_TRUE : SZ_LOCK_FALSE;
                ss += ssImg;
            }
            else
            {
                ssImg = imageRef.romName.c_str();
                ssImg +=
                    (!g_ParamsecBitCtrlYuSu.img_info[i].m_disable_download)?
                    SZ_LOCK_TRUE : SZ_LOCK_FALSE;
                ssEx += ssImg;
            }
            //it++;
        }

        sLockAll += (!g_ParamsecBitCtrlYuSu.m_lockdown ? SZ_LOCK_TRUE : SZ_LOCK_FALSE);
        ss = (sLockAll + ss);

        MainForm->ed_sec_setting_Write->Text = ss;
        MainForm->ed_sec_setting_Write_Ex->Text = ssEx;
    }

    if ( !m_Lockdown_CheckBox->Checked && isAllImgUnChecked )
    {
       ShowMessage("Please at least select one image to lock before carrying on!");
       return;
    }

    Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall Tm_SecuritySetting::FormShow(TObject *Sender)
{
    int androidImgCount = GetAndroidImageInfoTable().ImageNum();
    CreateCheckBoxList(androidImgCount);
	Display();
}
//---------------------------------------------------------------------------

void __fastcall Tm_SecuritySetting::FormClose(TObject *Sender,
      TCloseAction &Action)
{
	Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall Tm_SecuritySetting::m_CancelClick(TObject *Sender)
{
	Visible = false;
}
//---------------------------------------------------------------------------


void __fastcall Tm_SecuritySetting::FormHide(TObject *Sender)
{
    DestroyCheckBoxList();
}
//---------------------------------------------------------------------------

void __fastcall Tm_SecuritySetting::m_CheckAllClick(TObject *Sender)
{
    this->m_Lockdown_CheckBox->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall Tm_SecuritySetting::m_UncheckAllClick(TObject *Sender)
{
    this->m_Lockdown_CheckBox->Checked = false;
}
//---------------------------------------------------------------------------

void __fastcall Tm_SecuritySetting::m_Lockdown_CheckBoxClick( TObject *Sender)
{
    SyncCheckBoxList(m_Lockdown_CheckBox->Checked);
}
//---------------------------------------------------------------------------

void Tm_SecuritySetting::CreateCheckBoxList(int count)
{
    if( 0 == count ){
        return;
    }
    else {
        TCheckBox *pRomCheckBox = NULL;
        const int CHECKBOX_TOP = 26;
        const int CHECKBOX_HEIGHT = 25;
        const int CHECKBOX_INTERVAL = 25;
        const int CHECKBOX_WIDTH = 200;
        int offset = 0;
        ROM_INFO romInfo;
        AnsiString sCheckBoxCaption;
        m_pCheckBoxList.clear();

        for( int i=0; i < count ; i++ )
        {
            const AndroidImageInfo &imageRef =
            		GetAndroidImageInfoTable().GetImageByAndroidFileIndex(i);
            if(imageRef.isValid)
            {
                pRomCheckBox = new TCheckBox(m_GroupSecuritySetting);
                pRomCheckBox->Parent = m_GroupSecuritySetting;
                pRomCheckBox->Left = m_Lockdown_CheckBox->Left;
                pRomCheckBox->Top += (CHECKBOX_TOP + m_GroupSecuritySetting->Top + offset);
                offset += CHECKBOX_INTERVAL;
                pRomCheckBox->Height = CHECKBOX_HEIGHT;
                pRomCheckBox->Width = CHECKBOX_WIDTH;
                sCheckBoxCaption.sprintf("Forbid to download %s", imageRef.romName.c_str());
                pRomCheckBox->Caption = sCheckBoxCaption;
                //pRomCheckBox->OnClick = CheckBoxItemOnClick;
                pRomCheckBox->Show();
                m_pCheckBoxList.push_back(pRomCheckBox);
            }
        }
    }
}
//---------------------------------------------------------------------------

void Tm_SecuritySetting::DestroyCheckBoxList(void)
{
    if( m_pCheckBoxList.empty() )
    {
        return;
    }
    else
    {
        for(vector<TCheckBox*>::const_iterator it = m_pCheckBoxList.begin();
            it != m_pCheckBoxList.end(); it++)
        {
            delete (*it);
        }
        m_pCheckBoxList.clear();        
    }
}
//---------------------------------------------------------------------------

void Tm_SecuritySetting::SyncCheckBoxList(bool isLockdown)
{
    if(!isLockdown)
    {
        for(vector<TCheckBox*>::const_iterator it = m_pCheckBoxList.begin();
            it != m_pCheckBoxList.end(); it++)
        {
            (*it)->Checked = false;
        }
    }
    else
    {
        for(vector<TCheckBox*>::const_iterator it = m_pCheckBoxList.begin();
            it != m_pCheckBoxList.end(); it++)
        {
            (*it)->Checked = true;
        }
    }
}
//---------------------------------------------------------------------------


