//---------------------------------------------------------------------------

#ifndef frm_SplashH
#define frm_SplashH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TSplashFrom : public TForm
{
__published:	// IDE-managed Components
    TImage *SPFT_LoadingImage;

private:	// User declarations
public:		// User declarations
    __fastcall TSplashFrom(TComponent* Owner);
    bool __fastcall TSplashFormShow( TSplashFrom *pSplashFrom );
    void __fastcall TSplashFormDestory( TSplashFrom *pSplashFrom );
};
//---------------------------------------------------------------------------
extern PACKAGE TSplashFrom *SplashFrom;
//---------------------------------------------------------------------------
#endif
