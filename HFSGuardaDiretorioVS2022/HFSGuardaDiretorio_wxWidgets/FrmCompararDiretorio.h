#ifndef __FRMCOMPARARDIRETORIO_H__
#define __FRMCOMPARARDIRETORIO_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/button.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/gauge.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/choice.h>
#include <wx/treectrl.h>
#include <wx/stattext.h>
#include <wx/listctrl.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/imaglist.h>

#include "hfsguardadir\objetos\Diretorio.h"
#include "hfsguardadir\objetosgui\Arvore.h"
#include "hfsguardadir\objetosgui\Tabela.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::objetosgui;

///////////////////////////////////////////////////////////////////////////////
/// Class FrmCompararDiretorio
///////////////////////////////////////////////////////////////////////////////
class FrmCompararDiretorio : public wxFrame
{
	private:
		wxPanel* panelSuperior;
		wxButton* btnCompararDiretorios;
		wxGauge* pb;
		wxButton* btnSalvarLog;
		wxPanel* panelDiretorio;
		wxPanel* panelDiretorio1;
		wxChoice* cmbAba1;
		Arvore* arvoreDiretorio1;
		wxPanel* panelDiretorio2;
		wxChoice* cmbAba2;
		Arvore* arvoreDiretorio2;
		wxStaticText* labDiferencasEncontradas;
		Tabela* tabelaComparador;
		wxStatusBar* barraStatus;


        void FrmCompararDiretorioActivate( wxActivateEvent& event );
		void FrmCompararDiretorioClose( wxCloseEvent& event );
		void btnCompararDiretoriosClick( wxCommandEvent& event );
		void btnSalvarLogClick( wxCommandEvent& event );
		void cmbAba1Choice( wxCommandEvent& event );
		void arvoreDiretorio1GetInfo( wxTreeEvent& event );
		void arvoreDiretorio1SelChanged( wxTreeEvent& event );
		void cmbAba2Choice( wxCommandEvent& event );
		void arvoreDiretorio2GetInfo( wxTreeEvent& event );
		void arvoreDiretorio2SelChanged( wxTreeEvent& event );
		void tabelaComparadorListColClick( wxListEvent& event );
		void tabelaComparadorListItemSelected( wxListEvent& event );

        static void ProgressoLog(Progresso progresso);
		void montarArvores();
		void LimparComparacao();
		wxString SQLCompara(Aba aba1, Aba aba2, const wxString &caminho1,
			const wxString &caminho2);
		void Comparar(const wxString &sCaminhoDir1, const wxString &sCaminhoDir2);

	protected:
	public:
        wxVector<Diretorio> listaCompara;

		FrmCompararDiretorio( wxWindow* parent );
		~FrmCompararDiretorio();
};
// ---------------------------------------------------------------------------
extern FrmCompararDiretorio *frmCompararDiretorio;
// ---------------------------------------------------------------------------

#endif //__FRMCOMPARARDIRETORIO_H__
