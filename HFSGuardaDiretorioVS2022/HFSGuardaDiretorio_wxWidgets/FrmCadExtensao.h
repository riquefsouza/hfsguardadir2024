#ifndef __FRMCADEXTENSAO_H__
#define __FRMCADEXTENSAO_H__

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

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
#include <wx/listctrl.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/frame.h>
#include <wx/imaglist.h>

///////////////////////////////////////////////////////////////////////////////
/// Class FrmCadExtensao
///////////////////////////////////////////////////////////////////////////////
class FrmCadExtensao : public wxFrame
{
	private:
		wxMenuBar* barraMenu;
		wxMenu* menuExtensao;
		wxMenu* menuExportarTodos;
		wxMenu* menuImportarTodos;
        wxListCtrl* lcExtensao;
		wxButton* btnIncluir;
		wxButton* btnExcluir;
		wxImageList *imageList16;
		wxImageList *imageList32;

		void FrmCadExtensaoActivate( wxActivateEvent& event );
		void FrmCadExtensaoClose( wxCloseEvent& event );
		void menuIncluirExtensaoSelection( wxCommandEvent& event );
		void menuExcluirExtensaoSelection( wxCommandEvent& event );
		void menuExcluirTodasExtensoesSelection( wxCommandEvent& event );
		void menuExportarBitmapSelection( wxCommandEvent& event );
		void menuExportarIconeSelection( wxCommandEvent& event );
		void menuExportarGIFSelection( wxCommandEvent& event );
		void menuExportarJPEGSelection( wxCommandEvent& event );
		void menuExportarPNGSelection( wxCommandEvent& event );
		void menuExportarTIFFSelection( wxCommandEvent& event );
		void menuImportarIconesArquivosSelection( wxCommandEvent& event );
		void menuExtrairIconesArquivosSelection( wxCommandEvent& event );
		void lcExtensaoListColClick( wxListEvent& event );
		void lcExtensaoListItemSelected( wxListEvent& event );
		void btnIncluirClick( wxCommandEvent& event );
		void btnExcluirClick( wxCommandEvent& event );

        void CarregarExtensoesNaGrid();
	protected:

    public:
		FrmCadExtensao( wxWindow* parent );
		~FrmCadExtensao();

};
// ---------------------------------------------------------------------------
extern FrmCadExtensao *frmCadExtensao;
// ---------------------------------------------------------------------------
#endif //__FRMCADEXTENSAO_H__
