#ifndef __FRMSPLASH_H__
#define __FRMSPLASH_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/gauge.h>
#include <wx/sizer.h>
#include <wx/dialog.h>

#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::comum;

///////////////////////////////////////////////////////////////////////////////
/// Class FrmSplash
///////////////////////////////////////////////////////////////////////////////
class FrmSplash : public wxDialog
{
	private:
		wxStaticText* m_staticText1;
		wxStaticText* m_staticText2;
		wxGauge* gauge1;

		void FrmSplashClose( wxCloseEvent& event );
		void FrmSplashInitDialog( wxInitDialogEvent& event );

    protected:

	public:
		FrmSplash(wxWindow* parent);
		~FrmSplash();
		static void ProgressoLog(Progresso progresso);

};
// ---------------------------------------------------------------------------
extern FrmSplash *frmSplash;
// ---------------------------------------------------------------------------
#endif //__FRMSPLASH_H__
