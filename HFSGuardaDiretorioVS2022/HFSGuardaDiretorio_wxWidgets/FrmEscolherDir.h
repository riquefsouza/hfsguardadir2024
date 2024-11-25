#ifndef __FRMESCOLHERDIR_H__
#define __FRMESCOLHERDIR_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/dirctrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////////
/// Class FrmEscolherDir
///////////////////////////////////////////////////////////////////////////////
class FrmEscolherDir : public wxDialog
{
	private:

	protected:
		wxGenericDirCtrl* arvoreDiretorio;
		wxPanel* panelDiretorio;
		wxTextCtrl* edtDiretorio;
		wxPanel* panelBotoes;
		wxButton* btnOk;
		wxButton* btnCancelar;

		// Virtual event handlers, overide them in your derived class
		void arvoreDiretorioSelChanged( wxTreeEvent& event );
		void btnOkClick( wxCommandEvent& event );
		void btnCancelarClick( wxCommandEvent& event );


	public:
        wxStaticText* labDiretorio;

		FrmEscolherDir( wxWindow* parent );
		~FrmEscolherDir();

};
// ---------------------------------------------------------------------------
extern FrmEscolherDir *frmEscolherDir;
// ---------------------------------------------------------------------------
#endif //__FRMESCOLHERDIR_H__
