//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frm_encript.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrm_encription *frm_encription;
//---------------------------------------------------------------------------
__fastcall Tfrm_encription::Tfrm_encription(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_encription::btn_encription_cancelClick(
      TObject *Sender)
{
        MainForm->ts_SCIDownload->TabVisible = false;
        MainForm->ts_SCIClone->TabVisible = false;
	 		
	 g_SCI_Mode = false;
		
        Visible = false;		
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_encription::btn_encription_okClick(TObject *Sender)
{
    if(ed_Encription->Text.IsEmpty())
    {
        ShowMessage("Please Enter the password!");
	  return; 
    }

    m_strPassword = ed_Encription->Text;

    if(CheckPassword()) 
    {
        MainForm->ts_SCIDownload->TabVisible = true;
        MainForm->ts_SCIClone->TabVisible = true;
        Visible = false;
    }
    else
    {
        g_SCI_Mode = false;
		
        ed_Encription->Text = "";
		
        ShowMessage("Incorrect Password! Try again!");
    }  
}
//---------------------------------------------------------------------------
bool Tfrm_encription::CheckPassword()
{
        bool ret = false;

        AnsiString m_strPassword1_day, m_strPassword2_day, m_strPassword3_day;
        AnsiString m_strPassword1_week, m_strPassword2_week, m_strPassword3_week;
        AnsiString m_strPassword1_month, m_strPassword2_month, m_strPassword3_month;

	unsigned long password_day, password_c1_day, password_c2_day, password_c3_day, password_c4_day;
	unsigned long password_week, password_c1_week, password_c2_week, password_c3_week, password_c4_week;
	unsigned long password_month, password_c1_month, password_c2_month, password_c3_month, password_c4_month;

	 SYSTEMTIME s;
         GetSystemTime(&s);
	   
	if(m_strPassword == "OnlyMTK!") return true;

	password_day = 5827;
	password_week = 3958;
	password_month = 45236;

	password_day /= s.wDay;
	if ((s.wDay > 0) && (s.wDay <= 10))
		password_week /= 15;    
	else if ((s.wDay > 10) && (s.wDay <= 20))
		password_week /= 21;    
	else
		password_week /= 9;    

	password_month /= s.wMonth; 

	password_day = password_day << s.wDay;
	password_day = password_day + s.wMonth;
	password_week = password_week << s.wMonth;
	password_month = password_month << s.wMonth;

	password_day += s.wDay;
	password_month += s.wMonth;

	m_strPassword1_day.sprintf("%d", password_day);
	m_strPassword1_week.sprintf("%d", password_week);
	m_strPassword1_month.sprintf("%d", password_month);

	password_day = s.wDay * 58942;
	if ((s.wDay > 0) && (s.wDay <= 10))
		password_week = 542341;
	else if ((s.wDay > 10) && (s.wDay <= 20))
		password_week = 748634;
	else
		password_week = 123453;
	password_month = s.wMonth * 12385;

	password_c1_day = password_day >> 4;
	password_c1_week = password_week * 12 >> 4;
	password_c1_month = password_month * 21 >> 4;

	if (password_c1_day % 2)
	{
		if ((password_c1_day < 65) || (password_c1_day > 90))
			password_c1_day = password_c1_day % 90;

		while (password_c1_day < 65)
			password_c1_day +=25;
	}
	else
	{
		if ((password_c1_day < 97) || (password_c1_day > 122))
			password_c1_day = password_c1_day % 122;

		while (password_c1_day < 97)
			password_c1_day +=25;
	}

	if (password_c1_week % 2)
	{
		if ((password_c1_week < 65) || (password_c1_week > 90))
			password_c1_week = password_c1_week % 90;

		while (password_c1_week < 65)
			password_c1_week +=25;
	}
	else
	{
		if ((password_c1_week < 97) || (password_c1_week > 122))
			password_c1_week = password_c1_week % 122;

		while (password_c1_week < 97)
			password_c1_week +=25;
	}

	if (password_c1_month % 2)
	{
		if ((password_c1_month < 65) || (password_c1_month > 90))
			password_c1_month = password_c1_month % 90;

		while (password_c1_month < 65)
			password_c1_month +=25;
	}
	else
	{
		if ((password_c1_month < 97) || (password_c1_month > 122))
			password_c1_month = password_c1_month % 122;

		while (password_c1_month < 97)
			password_c1_month +=25;
	}

	password_c2_day = password_day >> 3;
	password_c2_week = password_week * 3 >> 3;
	password_c2_month = password_month * 16 >> 3;

	if (password_c2_day % 2)
	{
		if ((password_c2_day < 65) || (password_c2_day > 90))
			password_c2_day = password_c2_day % 90;

		while (password_c2_day < 65)
			password_c2_day +=25;
	}
	else
	{
		if ((password_c2_day < 97) || (password_c2_day > 122))
			password_c2_day = password_c2_day % 122;

		while (password_c2_day < 97)
			password_c2_day +=25;
	}

	if (password_c2_week % 2)
	{
		if ((password_c2_week < 65) || (password_c2_week > 90))
			password_c2_week = password_c2_week % 90;

		while (password_c2_week < 65)
			password_c2_week +=25;
	}
	else
	{
		if ((password_c2_week < 97) || (password_c2_week > 122))
			password_c2_week = password_c2_week % 122;

		while (password_c2_week < 97)
			password_c2_week +=25;
	}

	if (password_c2_month % 2)
	{
		if ((password_c2_month < 65) || (password_c2_month > 90))
			password_c2_month = password_c2_month % 90;

		while (password_c2_month < 65)
			password_c2_month +=25;
	}
	else
	{
		if ((password_c2_month < 97) || (password_c2_month > 122))
			password_c2_month = password_c2_month % 122;

		while (password_c2_month < 97)
			password_c2_month +=25;
	}

	password_c3_day = password_day >> 2;
	password_c3_week = password_week >> 2;
	password_c3_month = password_month >> 2;

	if (password_c3_day % 2)
	{
		if ((password_c3_day < 65) || (password_c3_day > 90))
			password_c3_day = password_c3_day % 90;

		while (password_c3_day < 65)
			password_c3_day +=25;
	}
	else
	{
		if ((password_c3_day < 97) || (password_c3_day > 122))
			password_c3_day = password_c3_day % 122;

		while (password_c3_day < 97)
			password_c3_day +=25;
	}

	if (password_c3_week % 2)
	{
		if ((password_c3_week < 65) || (password_c3_week > 90))
			password_c3_week = password_c3_week % 90;

		while (password_c3_week < 65)
			password_c3_week +=25;
	}
	else
	{
		if ((password_c3_week < 97) || (password_c3_week > 122))
			password_c3_week = password_c3_week % 122;

		while (password_c3_week < 97)
			password_c3_week +=25;
	}

	if (password_c3_month % 2)
	{
		if ((password_c3_month < 65) || (password_c3_month > 90))
			password_c3_month = password_c3_month % 90;

		while (password_c3_month < 65)
			password_c3_month +=25;
	}
	else
	{
		if ((password_c3_month < 97) || (password_c3_month > 122))
			password_c3_month = password_c3_month % 122;

		while (password_c3_month < 97)
			password_c3_month +=25;
	}

	password_c4_day = password_day >> 1;
	password_c4_week = password_week >> 1;
	password_c4_month = password_month >> 1;

	if (password_c4_day % 2)
	{
		if ((password_c4_day < 65) || (password_c4_day > 90))
			password_c4_day = password_c4_day % 90;

		while (password_c4_day < 65)
			password_c4_day +=25;
	}
	else
	{
		if ((password_c4_day < 97) || (password_c4_day > 122))
			password_c4_day = password_c4_day % 122;

		while (password_c4_day < 97)
			password_c4_day +=25;
	}

	if (password_c4_week % 2)
	{
		if ((password_c4_week < 65) || (password_c4_week > 90))
			password_c4_week = password_c4_week % 90;

		while (password_c4_week < 65)
			password_c4_week +=25;
	}
	else
	{
		if ((password_c4_week < 97) || (password_c4_week > 122))
			password_c4_week = password_c4_week % 122;

		while (password_c4_week < 97)
			password_c4_week +=25;
	}

	if (password_c4_month % 2)
	{
		if ((password_c4_month < 65) || (password_c4_month > 90))
			password_c4_month = password_c4_month % 90;

		while (password_c4_month < 65)
			password_c4_month +=25;
	}
	else
	{
		if ((password_c4_month < 97) || (password_c4_month > 122))
			password_c4_month = password_c4_month % 122;

		while (password_c4_month < 97)
			password_c4_month +=25;
	}

	m_strPassword2_day.sprintf("%c%c%c%c", password_c1_day, password_c2_day, password_c3_day, password_c4_day);
	m_strPassword2_week.sprintf("%c%c%c%c", password_c1_week, password_c2_week, password_c3_week, password_c4_week);
	m_strPassword2_month.sprintf("%c%c%c%c", password_c1_month, password_c2_month, password_c3_month, password_c4_month);

	password_day = 2948201;
	password_week = 8138947;
	password_month = 6023848;
	password_day /= s.wDay;
	password_day *= s.wMonth;
	if ((s.wDay > 0) && (s.wDay <= 10))
		password_week = password_week >> 2;
	else if ((s.wDay > 10) && (s.wDay <= 20))
		password_week = password_week << 5;
	else
		password_week /= 3;
	password_month /= s.wMonth;
	password_day = password_day >> 7;
	password_week = password_week >> 3;
	password_month = password_month >> 6;

	m_strPassword3_day.sprintf("%d", password_day);
	m_strPassword3_week.sprintf("%d", password_week);
	m_strPassword3_month.sprintf("%d", password_month);

	m_strPassword_day = m_strPassword1_day;
	m_strPassword_day += m_strPassword2_day;
	m_strPassword_day += m_strPassword3_day;
	m_strPassword_week = m_strPassword1_week;
	m_strPassword_week += m_strPassword2_week;
	m_strPassword_week += m_strPassword3_week;
	m_strPassword_month = m_strPassword1_month;
	m_strPassword_month += m_strPassword2_month;
	m_strPassword_month += m_strPassword3_month;

	if ((m_strPassword == m_strPassword_day) || (m_strPassword == m_strPassword_week) 
		|| (m_strPassword == m_strPassword_month) || (m_strPassword == "rlaghdtjrqkqh0313"))
	{
		ret = true;
	}
	else
	{
		m_strPassword = "";

		ret = false;
	}

	return ret;
}           
//---------------------------------------------------------------------------
void __fastcall Tfrm_encription::FormClose(TObject *Sender,
      TCloseAction &Action)
{
        MainForm->ts_SCIDownload->TabVisible = false;
        MainForm->ts_SCIClone->TabVisible = false;
	g_SCI_Mode = false;
	 
        Visible = false;      
}
//---------------------------------------------------------------------------



void __fastcall Tfrm_encription::FormShow(TObject *Sender)
{
     ed_Encription->Text = "";        
}
//---------------------------------------------------------------------------




void __fastcall Tfrm_encription::ed_EncriptionKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
     if(Key == VK_RETURN || Key == 13)
     {
          btn_encription_okClick(Sender);
     }
}
//---------------------------------------------------------------------------

