#include "FrmImportarDiretorio.h"

#include "hfsguardadir/objetosdao/AbaDAO.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/catalogador/Catalogador.h"
#include "hfsguardadir/objetosbo/ImportarBO.h"
#include "hfsguardadir/objetosbo/DiretorioBO.h"
#include "hfsguardadir/objetosgui/Dialogo.h"

using namespace hfsguardadir::objetosdao;
using namespace hfsguardadir::comum;
using namespace hfsguardadir::catalogador;
using namespace hfsguardadir::objetosbo;
using namespace hfsguardadir::objetosgui;

FrmImportarDiretorio *frmImportarDiretorio;

FrmImportarDiretorio::FrmImportarDiretorio( wxWindow* parent ) :
    wxDialog( parent, wxID_ANY, wxT("Importando Diret\u00f3rio"), wxDefaultPosition, wxSize( 685,462 ), wxDEFAULT_DIALOG_STYLE )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	memoImportaDir = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxTE_MULTILINE|wxTE_READONLY );
	bSizer1->Add( memoImportaDir, 1, wxALL|wxEXPAND, 5 );

	pbImportar = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	pbImportar->SetValue( 0 );
	bSizer1->Add( pbImportar, 0, wxALL|wxEXPAND, 5 );

	barraStatus = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );

	barraStatus1 = new wxStaticText( barraStatus, wxID_ANY, wxT("Total de linhas sendo processadas:"), wxDefaultPosition, wxSize( 200,-1 ), 0 );
	barraStatus1->Wrap( -1 );
	bSizer2->Add( barraStatus1, 0, wxALL, 1 );

	barraStatus2 = new wxStaticText( barraStatus, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	barraStatus2->Wrap( -1 );
	bSizer2->Add( barraStatus2, 1, wxALL | wxEXPAND, 1 );

	barraStatus->SetSizer( bSizer2 );
	barraStatus->Layout();
	bSizer2->Fit( barraStatus );
	bSizer1->Add( barraStatus, 0, wxALL|wxEXPAND, 5 );

	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
}

FrmImportarDiretorio::~FrmImportarDiretorio()
{
   	// Disconnect Events
}

void FrmImportarDiretorio::iniciarImportacao()
{
	wxString sLog;
	wxArrayString log;

	for each(Importar importar in listaImportar) {
		catalogador->diretorioOrdem.setOrdem(1);

		if (!bSubDiretorio) {
			SetCursor(wxCURSOR_WAIT);

			ImportarBO::getInstancia()->ImportacaoCompleta(importar,
				&catalogador->diretorioOrdem, catalogador->listaExtensoes,
				ProgressoLog);

			SetCursor(wxCURSOR_ARROW);
		}
		else {
			if (!DiretorioBO::getInstancia()->verificaCodDir(importar.getAba(),
				importar.getRotuloRaiz(), catalogador->listaDiretorioPai)) {
				SetCursor(wxCURSOR_WAIT);

				ImportarBO::getInstancia()->ImportacaoCompleta(importar,
					&catalogador->diretorioOrdem, catalogador->listaExtensoes,
					ProgressoLog);

				SetCursor(wxCURSOR_ARROW);
			}
			else {
				Dialogo::mensagemInfo(this,
					"FrmImportarDiretorio.DiretorioExisteCatalogo");
			}
		}
	}

	if (catalogador->bGravarLogImportacao) {
		if (memoImportaDir->GetNumberOfLines() > 0) {
			sLog = Rotinas::AppDirPath() + Rotinas::BARRA_INVERTIDA
				+ Rotinas::formataDate(Rotinas::FORMATO_DHARQUIVO, wxDateTime::Now())
				+ "_Importacao.log";

			for (int i = 0; i < memoImportaDir->GetNumberOfLines(); i++)
			{
				log.Add(memoImportaDir->GetLineText(i));
			}
			Rotinas::SListSaveToFile(log, sLog);
		}
	}

	this->Close();
}


void FrmImportarDiretorio::ProgressoLog(Progresso progresso)
{
  if (frmImportarDiretorio!=NULL){
	  if (progresso.posicao == 0) {
		 frmImportarDiretorio->pbImportar->SetValue(progresso.minimo);
		 frmImportarDiretorio->pbImportar->SetRange(progresso.maximo);		 
	  }

	  frmImportarDiretorio->pbImportar->SetValue( progresso.posicao );

	  if (!progresso.log.IsEmpty()) {
		  int pos = frmImportarDiretorio->memoImportaDir->GetNumberOfLines();
		  frmImportarDiretorio->memoImportaDir->AppendText(progresso.log + "\n");
		  frmImportarDiretorio->memoImportaDir->SetSelection(pos, pos);
		  frmImportarDiretorio->memoImportaDir->ScrollLines(pos);
		  frmImportarDiretorio->barraStatus1->SetLabelText("Total de linhas sendo processadas:");
		  frmImportarDiretorio->barraStatus2->SetLabelText(Rotinas::IntToStr(pos));		  
	  }
  }
}
