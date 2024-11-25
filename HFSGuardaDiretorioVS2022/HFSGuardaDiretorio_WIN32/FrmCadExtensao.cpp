#include "stdafx.h"

#include <windows.h>
#include <commctrl.h>
#include <stdio.h>

#include "HFSGuardaDiretorio.h"
#include "FrmPrincipal.h"
#include "FrmCadExtensao.h"
#include "resource.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/comum/String.h"
#include "hfsguardadir/objetosgui/Tabela.h"
#include "hfsguardadir/objetosgui/EscolhaArquivo.h"
#include "hfsguardadir/objetosgui/Dialogo.h"
#include "hfsguardadir/comum/ListaString.h"
#include "hfsguardadir/objetosbo/ExtensaoBO.h"
#include "hfsguardadir/catalogador/Catalogador.h"

struct SFrmCadExtensao FrmCadExtensao;

LRESULT CALLBACK frmCadExtensaoProc(HWND hwnd, UINT Message, WPARAM wParam, 
    LPARAM lParam )
{ 
   switch( Message ) {
      case WM_INITDIALOG:
      {      
		  ListaString sColunas;
		  sColunas = ListaString_inicia();
		  UINT nLargura[] = { 100, 100 };

		  FrmCadExtensao.tabelaExtensao = GetDlgItem(hwnd, ID_FRMCADEXTENSAO_LVINFO);

		  ListaString_insereFim(&sColunas, String_iniciar("Extensão"));
		  ListaString_insereFim(&sColunas, String_iniciar("Ícone"));

		  Tabela_insereColunas(FrmCadExtensao.tabelaExtensao, nLargura, sColunas);

		  FrmCadExtensao_CarregarExtensoesNaGrid();

		  ListView_SetImageList(FrmCadExtensao.tabelaExtensao, FrmPrincipal.imageList16, LVSIL_SMALL);
		  ListView_SetImageList(FrmCadExtensao.tabelaExtensao, FrmPrincipal.imageList32, LVSIL_NORMAL);

		  FrmCadExtensao.frmCadExtensao = hwnd;

		  return TRUE;
      }
      break;       
	  case WM_COMMAND:
	  {
		  switch (wParam) {
		  case ID_FRMCADEXTENSAO_BTNINCLUIR:
		  {
			  FrmCadExtensao_menuIncluirExtensao(hwnd);
		  }
		  break;
		  case ID_FRMCADEXTENSAO_BTNEXCLUIR:
		  {
			  FrmCadExtensao_menuExcluirExtensao(hwnd);
		  }
		  break;
		  case IDM_INCLUIR_EXTENSAO:
		  {
			  FrmCadExtensao_menuIncluirExtensao(hwnd);
		  }
		  break;
		  case IDM_EXCLUIR_EXTENSAO:
		  {
			  FrmCadExtensao_menuExcluirExtensao(hwnd);
		  }
		  break;
		  case IDM_EXCLUIR_TODAS_EXTENSOES:
		  {
			  FrmCadExtensao_menuExcluirTodasExtensoes(hwnd);
		  }
		  break;
		  case IDM_EXPORTAR_BITMAP:
		  {
			  FrmCadExtensao_menuExportarBitmap(hwnd);
		  }
		  break;
		  case IDM_EXPORTAR_ICONE:
		  {
			  FrmCadExtensao_menuExportarIcone(hwnd);
		  }
		  break;
		  case IDM_EXPORTAR_GIF:
		  {
			  FrmCadExtensao_menuExportarGIF(hwnd);
		  }
		  break;
		  case IDM_EXPORTAR_JPEG:
		  {
			  FrmCadExtensao_menuExportarJPEG(hwnd);
		  }
		  break;
		  case IDM_EXPORTAR_PNG:
		  {
			  FrmCadExtensao_menuExportarPNG(hwnd);
		  }
		  break;
		  case IDM_EXPORTAR_TIFF:
		  {
			  FrmCadExtensao_menuExportarTIFF(hwnd);
		  }
		  break;
		  case IDM_IMPORTAR_ICONES_ARQUIVOS:
		  {
			  FrmCadExtensao_menuImportarIconesArquivos(hwnd);
		  }
		  break;
		  case IDM_EXTRAIR_ICONES_ARQUIVOS:
		  {
			  FrmCadExtensao_menuExtrairIconesArquivos(hwnd);
		  }
		  break;
		  }
	  }
	  break;
	  case WM_CLOSE:
	  {
		  EndDialog(hwnd, FALSE);
	  }
	  break;
   }
  
   return FALSE;
}

VOID FrmCadExtensao_Mostrar(HWND hwnd) {
	DialogBox(g_hInstancia, MAKEINTRESOURCEW(FRMCADEXTENSAO), hwnd,
		(DLGPROC)frmCadExtensaoProc);
}

void FrmCadExtensao_CarregarExtensoesNaGrid() {
	unsigned int nLinha = 0;
	ListaExtensao local;
	Extensao extensao;
	String cols[2];
	INT nImagem = 3; //ImageList_GetImageCount(FrmPrincipal.imageList16);
	
	for (local = Catalogador.listaExtensoes; local != NULL; local = local->proximo) {
		extensao = local->extensao;
		
		//ImageList_Add(FrmPrincipal.imageList16, extensao.hbmp16, NULL);
		//ImageList_Add(FrmPrincipal.imageList32, extensao.hbmp32, NULL);
		
		cols[0] = String_copiar(extensao.nome);
		cols[1] = String_iniciar("");		
		Tabela_insereLinha(FrmCadExtensao.tabelaExtensao, 2, nLinha, nImagem, cols);
		nLinha++;
		nImagem++;
	}

}


void FrmCadExtensao_menuIncluirExtensao(HWND hwnd) {
	ListaString log = ListaString_inicia();

	String arquivo = EscolhaArquivo_abrirArquivo(hwnd);
	if (arquivo.length > 0) {
		if (Rotinas_FileExists(arquivo)) {
			String nomeArquivo = Rotinas_ExtractFileName(arquivo);

			if (ExtensaoBO_SalvarExtensao(
				Catalogador.listaExtensoes, nomeArquivo, arquivo, log)) {

				FrmCadExtensao_CarregarExtensoesNaGrid();

				Dialogo_mensagemInfo(hwnd,
					STR_FRMCADEXTENSAO_EXTENSAOSALVASUCESSO);
			}
			else {
				Dialogo_mensagemInfo(hwnd,
					STR_FRMCADEXTENSAO_EXTENSAOJACADASTRADA);
			}
		}
	}

}

void FrmCadExtensao_menuExcluirExtensao(HWND hwnd) {
	Extensao *extensao;
	int ntamlista = ListaExtensao_conta(Catalogador.listaExtensoes);

	if (ntamlista > 0) {
		if (Dialogo_confirma(hwnd, STR_FRMCADEXTENSAO_EXTENSAOCERTEZAEXCLUIR)) {

			int ordem = ListView_GetSelectionMark(FrmCadExtensao.tabelaExtensao);

			extensao = ExtensaoBO_pegaExtensaoPorOrdem(
				Catalogador.listaExtensoes, ordem + 1);

			if (ExtensaoBO_excluirExtensao(
				Catalogador.listaExtensoes, extensao->codigo)) {
				FrmCadExtensao_CarregarExtensoesNaGrid();
				Dialogo_mensagemInfo(hwnd,
					STR_FRMCADEXTENSAO_EXTENSAOEXCLUIDASUCESSO);
			}
		}
	}
}

void FrmCadExtensao_menuExcluirTodasExtensoes(HWND hwnd) {
	int ntamlista = ListaExtensao_conta(Catalogador.listaExtensoes);

	if (ntamlista > 0) {
		if (Dialogo_confirma(hwnd, STR_FRMCADEXTENSAO_EXTENSAOCERTEZATODOSEXCLUIR)) {
			if (ExtensaoBO_excluirTodasExtensoes(
				Catalogador.listaExtensoes)) {
				FrmCadExtensao_CarregarExtensoesNaGrid();
				Dialogo_mensagemInfo(hwnd,
					STR_FRMCADEXTENSAO_EXTENSOESEXCLUIDASSUCESSO);
			}
		}
	}
}

void FrmCadExtensao_menuExportarBitmap(HWND hwnd) {

	if (ExtensaoBO_ExportarExtensao(teBMP,
		Catalogador.listaExtensoes)) {
		Dialogo_mensagemInfo(hwnd, STR_FRMCADEXTENSAO_EXPORTAREXTENSAO);
	}

}

void FrmCadExtensao_menuExportarIcone(HWND hwnd) {

	if (ExtensaoBO_ExportarExtensao(teICO,
		Catalogador.listaExtensoes)) {
		Dialogo_mensagemInfo(hwnd, STR_FRMCADEXTENSAO_EXPORTAREXTENSAO);
	}

}

void FrmCadExtensao_menuExportarGIF(HWND hwnd) {

	if (ExtensaoBO_ExportarExtensao(teGIF,
		Catalogador.listaExtensoes)) {
		Dialogo_mensagemInfo(hwnd, STR_FRMCADEXTENSAO_EXPORTAREXTENSAO);
	}

}

void FrmCadExtensao_menuExportarJPEG(HWND hwnd) {

	if (ExtensaoBO_ExportarExtensao(teJPG,
		Catalogador.listaExtensoes)) {
		Dialogo_mensagemInfo(hwnd, STR_FRMCADEXTENSAO_EXPORTAREXTENSAO);
	}

}

void FrmCadExtensao_menuExportarPNG(HWND hwnd) {

	if (ExtensaoBO_ExportarExtensao(tePNG,
		Catalogador.listaExtensoes)) {
		Dialogo_mensagemInfo(hwnd, STR_FRMCADEXTENSAO_EXPORTAREXTENSAO);
	}

}

void FrmCadExtensao_menuExportarTIFF(HWND hwnd) {

	if (ExtensaoBO_ExportarExtensao(teTIF,
		Catalogador.listaExtensoes)) {
		Dialogo_mensagemInfo(hwnd, STR_FRMCADEXTENSAO_EXPORTAREXTENSAO);
	}

}

void FrmCadExtensao_menuImportarIconesArquivos(HWND hwnd) {

	String diretorio = EscolhaArquivo_abrirDiretorio(hwnd);
	if (diretorio.length > 0) {
		
		if (Rotinas_DirectoryExists(diretorio)) {
			ExtensaoBO_ImportarExtensao(diretorio,
				Catalogador.listaExtensoes);
			FrmCadExtensao_CarregarExtensoesNaGrid();
		}
	}
}

void FrmCadExtensao_menuExtrairIconesArquivos(HWND hwnd) {

	String diretorio = EscolhaArquivo_abrirDiretorio(hwnd);
	if (diretorio.length > 0) {

		if (Rotinas_DirectoryExists(diretorio)) {
			ExtensaoBO_ExtrairExtensao(diretorio,
				Catalogador.listaExtensoes);
			FrmCadExtensao_CarregarExtensoesNaGrid();
		}
	}
}

