#ifndef __FRMINFODIRETORIO_H__
#define __FRMINFODIRETORIO_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/listctrl.h>
#include <wx/button.h>
#include <wx/dialog.h>

#include "hfsguardadir/objetos/Diretorio.h"

using namespace hfsguardadir::objetos;

///////////////////////////////////////////////////////////////////////////////
/// Class FrmInfoDiretorio
///////////////////////////////////////////////////////////////////////////////
class FrmInfoDiretorio : public wxDialog
{
	private:
		wxPanel* panelLegenda;
		wxStaticText* labArquivoComum;
		wxStaticText* labArquivoOculto;
		wxStaticText* labArquivoSistema;
		wxStaticText* labLegendaDiretorio;
		wxStaticText* labVolumeID;
		wxStaticText* labArquivoSomenteLeitura;
		wxListCtrl* lcInfo;
		wxButton* btnOk;

		void FrmInfoDiretorioActivate( wxActivateEvent& event );
		void FrmInfoDiretorioClose( wxCloseEvent& event );
		void FrmInfoDiretorioInitDialog( wxInitDialogEvent& event );
		void lcInfoListColClick( wxListEvent& event );
		void lcInfoListItemSelected( wxListEvent& event );
		void btnOkClick( wxCommandEvent& event );

    protected:

	public:
		void setDiretorio(Diretorio diretorio);

		FrmInfoDiretorio( wxWindow* parent );
		~FrmInfoDiretorio();

};
//---------------------------------------------------------------------------
extern FrmInfoDiretorio *frmInfoDiretorio;
//---------------------------------------------------------------------------
#endif //__FRMINFODIRETORIO_H__
