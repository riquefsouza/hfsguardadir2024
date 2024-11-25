#ifndef __FRMPRINCIPAL_H__
#define __FRMPRINCIPAL_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/gauge.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/treectrl.h>
#include <wx/listctrl.h>
#include <wx/splitter.h>
#include <wx/notebook.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/imaglist.h>

#include "hfsguardadir/objetosgui/Arvore.h"
#include "hfsguardadir/objetosgui/Tabela.h"
#include "hfsguardadir/catalogador/Catalogador.h"
#include "hfsguardadir/comum/Rotinas.h"

#if defined(__WXMOTIF__) || defined(__WXPM__) || defined(__WXX11__)
#define USE_CONTEXT_MENU 0
#else
#define USE_CONTEXT_MENU 1
#endif

using namespace hfsguardadir::comum;
using namespace hfsguardadir::objetosgui;
using namespace hfsguardadir::catalogador;

///////////////////////////////////////////////////////////////////////////////
/// Class FrmPrincipal
///////////////////////////////////////////////////////////////////////////////
class FrmPrincipal : public wxFrame
{
	private:
		wxMenuBar* barraMenu;
		wxMenu* menuAba;
		wxMenu* menuDiretorio;
		wxMenu* menuExportarDiretoriosAbaAtiva;
		wxMenu* menuVisao;
		wxMenu* menuSobre;

		wxMenuItem* menuGravarLogImportacao;

		wxMenu* menuPopup;

		wxPanel* m_panel1;
		wxButton* btnImportarDiretorio;
		wxSplitterWindow* sp;
		wxButton* btnPesquisa;
        wxImageList *imageListTabs;

		static void ProgressoLog(Progresso progresso);
		void FrmPrincipalActivate( wxActivateEvent& event );
        void FrmPrincipalActivateApp( wxActivateEvent& event );
        void FrmPrincipalClose( wxCloseEvent& event );
        void menuIncluirNovaAbaSelection( wxCommandEvent& event );
        void menuAlterarNomeAbaAtivaSelection( wxCommandEvent& event );
        void menuExcluirAbaAtivaSelection( wxCommandEvent& event );
        void menuImportarDiretorioSelection( wxCommandEvent& event );
        void menuImportarSubDiretoriosSelection( wxCommandEvent& event );
        void menuCompararDiretoriosSelection( wxCommandEvent& event );
        void menuCadastrarExtensaoArquivoSelection( wxCommandEvent& event );
        void menuExpandirDiretoriosSelection( wxCommandEvent& event );
        void menuColapsarDiretoriosSelection( wxCommandEvent& event );
        void menuTXTSelection( wxCommandEvent& event );
        void menuCSVSelection( wxCommandEvent& event );
        void menuHTMLSelection( wxCommandEvent& event );
        void menuXMLSelection( wxCommandEvent& event );
        void menuSQLSelection( wxCommandEvent& event );
        void menuImportarDiretoriosViaXMLSelection( wxCommandEvent& event );
        void menuGravarLogImportacaoSelection( wxCommandEvent& event );
        void menuMostrarOcultarArvoreDirAbaAtivaSelection( wxCommandEvent& event );
        void menuMostrarOcultarListaItensPesquisadosSelection( wxCommandEvent& event );
        void menuSobreCatalogadorSelection( wxCommandEvent& event );
        void btnImportarDiretorioClick( wxCommandEvent& event );
        void btnPesquisaClick( wxCommandEvent& event );
        void notebookPageChanged( wxNotebookEvent& event );
		void tabelaPesquisaListColClick( wxListEvent& event );
		void tabelaPesquisaListItemSelected( wxListEvent& event );
		void ShowContextMenu(const wxPoint& pos);

		void menuInformacoesDiretorioArquivoSelection(wxCommandEvent& event);
		void menuExcluirDiretorioSelecionadoSelection(wxCommandEvent& event);

	protected:
#if USE_CONTEXT_MENU
		void FrmPrincipalOnContextMenu(wxContextMenuEvent& event);
#else
		void FrmPrincipalOnRightUp(wxMouseEvent& event)
		{
			ShowContextMenu(event.GetPosition());
		}
#endif

	public:
        wxImageList *imageList16;
        wxImageList *imageList32;
        wxGauge* pb;
        wxNotebook* notebook;
        wxStatusBar* barraStatus;
		wxTextCtrl* edtPesquisa;
		Tabela* tabelaPesquisa;
		wxSplitterWindow* spPesquisa;
		wxPanel* m_panel2;
		wxPanel* m_panel3;

		FrmPrincipal( wxWindow* parent );
		~FrmPrincipal();
        void arvoreSelChanged( wxTreeEvent& event );
		void tabelaListColClick(wxListEvent& event);
		void tabelaListItemSelected(wxListEvent& event);
		void spOnIdle( wxIdleEvent& );
		void spPesquisaOnIdle( wxIdleEvent& );

};
// ---------------------------------------------------------------------------
extern FrmPrincipal *frmPrincipal;
// ---------------------------------------------------------------------------
#endif //__FRMPRINCIPAL_H__
