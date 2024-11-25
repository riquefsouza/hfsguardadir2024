#ifndef __FRMIMPORTARDIRETORIO_H__
#define __FRMIMPORTARDIRETORIO_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/textctrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/gauge.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/dialog.h>

#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/objetos/Diretorio.h"
#include "hfsguardadir/objetos/Importar.h"

using namespace hfsguardadir::comum;
using namespace hfsguardadir::objetos;

///////////////////////////////////////////////////////////////////////////////
/// Class FrmImportarDiretorio
///////////////////////////////////////////////////////////////////////////////
class FrmImportarDiretorio : public wxDialog
{
	private:		
		wxGauge* pbImportar;
		wxPanel* barraStatus;
		wxStaticText* barraStatus1;
		wxTextCtrl* memoImportaDir;
		wxStaticText* barraStatus2;

        static void ProgressoLog(Progresso progresso);
		
    protected:
	public:
		bool bSubDiretorio;
		wxVector<Importar> listaImportar;
		wxVector<Diretorio> listaDiretorio;

		FrmImportarDiretorio( wxWindow* parent );
		~FrmImportarDiretorio();
		void iniciarImportacao();
};
// ---------------------------------------------------------------------------
extern FrmImportarDiretorio *frmImportarDiretorio;
// ---------------------------------------------------------------------------
#endif //__FRMIMPORTARDIRETORIO_H__
