//---------------------------------------------------------------------------

#ifndef frm_ProcessH
#define frm_ProcessH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class Tfrm_Processing : public TForm
{
__published:	// IDE-managed Components
        TPanel *masterPanel;
        TShape *red1Shape;
        TShape *red2Shape;
        TShape *red3Shape;
        TLabel *tipLabel;
        TTimer *processTimer;
        void __fastcall processTimerTimer(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormResize(TObject *Sender);
private:	// User declarations
        void __fastcall SubClassWndProc( Messages::TMessage &Message );
public:		// User declarations
        __fastcall Tfrm_Processing(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_Processing *frm_Processing;
//---------------------------------------------------------------------------
#endif
