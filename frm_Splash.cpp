//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#pragma warn -8004
#include "frm_Splash.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSplashFrom *SplashFrom;
//---------------------------------------------------------------------------
__fastcall TSplashFrom::TSplashFrom(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
bool __fastcall TSplashFrom::TSplashFormShow( TSplashFrom *pSplashFrom )
{
    if ( NULL == pSplashFrom )
    {
        return false;
    }
    else
    {
        pSplashFrom-> FormStyle=fsStayOnTop;
        pSplashFrom-> BorderStyle=bsNone;
        pSplashFrom-> Position=poScreenCenter;
        pSplashFrom-> Show();
        pSplashFrom-> Update();
        return true;
    }
}

//---------------------------------------------------------------------------
void __fastcall TSplashFrom::TSplashFormDestory( TSplashFrom *pSplashFrom )
{
    pSplashFrom->Hide();
    pSplashFrom->Close();
    delete pSplashFrom;
    pSplashFrom = NULL;
}
//---------------------------------------------------------------------------