#ifndef __FRMSOBRE_H__
#define __FRMSOBRE_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////////
/// Class FrmSobre
///////////////////////////////////////////////////////////////////////////////
class FrmSobre : public wxDialog
{
	private:
		wxStaticText* m_staticText1;
		wxStaticText* m_staticText2;
		wxStaticText* m_staticText3;
		wxStaticText* m_staticText4;
		wxButton* btnOk;

		void FrmSobreClose( wxCloseEvent& event );
		void FrmSobreInitDialog( wxInitDialogEvent& event );
		void btnOkClick( wxCommandEvent& event );

    protected:

	public:
		FrmSobre( wxWindow* parent );
		~FrmSobre();

};
// ---------------------------------------------------------------------------
extern FrmSobre *frmSobre;
// ---------------------------------------------------------------------------
#endif //__FRMSOBRE_H__
