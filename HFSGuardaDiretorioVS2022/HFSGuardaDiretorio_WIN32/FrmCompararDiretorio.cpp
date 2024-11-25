#include "stdafx.h"

#include <windowsx.h>
#include <commctrl.h>

#include "HFSGuardaDiretorio.h"
#include "FrmPrincipal.h"
#include "FrmCompararDiretorio.h"
#include "resource.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/objetosgui/Arvore.h"
#include "hfsguardadir/objetosgui/Tabela.h"
#include "hfsguardadir/catalogador/Catalogador.h"
#include "hfsguardadir/objetosgui/Dialogo.h"
#include "hfsguardadir/objetosbo/AbaBO.h"
#include "hfsguardadir/objetosbo/DiretorioBO.h"

struct SFrmCompararDiretorio FrmCompararDiretorio;

LRESULT CALLBACK frmCompararDiretorioProc(HWND hwnd, UINT Message, WPARAM wParam, 
    LPARAM lParam )
{ 
   switch( Message ) {
   case WM_INITDIALOG:
   {      
	   int iStatusWidths[] = { 200, -1 };

	   FrmCompararDiretorio.barraStatus = CreateWindowEx(0, STATUSCLASSNAME, NULL,
		   WS_CHILD | WS_VISIBLE, 0, 0, 0, 0,
		   hwnd, (HMENU)ID_FRMCOMPARARDIRETORIO_BARRASTATUS1, g_hInstancia, NULL);
	   SendMessage(FrmCompararDiretorio.barraStatus, SB_SETPARTS, 2, (LPARAM)iStatusWidths);
	   SendMessage(FrmCompararDiretorio.barraStatus, SB_SETTEXT, 0,
		   (LPARAM)Rotinas_lerStr(STR_FRMCOMPARARDIRETORIO_BARRASTATUS1));

	   FrmCompararDiretorio.pb = Rotinas_pegaBarraProgresso(hwnd, ID_FRMCOMPARARDIRETORIO_PB, 0, 100, 1);

	   FrmCompararDiretorio.btnSalvarLog = GetDlgItem(hwnd, ID_FRMCOMPARARDIRETORIO_BTNSALVARLOG);
	   FrmCompararDiretorio.cmbAba1 = GetDlgItem(hwnd, ID_FRMCOMPARARDIRETORIO_CMBABA1);
	   FrmCompararDiretorio.cmbAba2 = GetDlgItem(hwnd, ID_FRMCOMPARARDIRETORIO_CMBABA2);
	   FrmCompararDiretorio.arvoreDir1 = GetDlgItem(hwnd, ID_FRMCOMPARARDIRETORIO_TVDIR1);
	   FrmCompararDiretorio.arvoreDir2 = GetDlgItem(hwnd, ID_FRMCOMPARARDIRETORIO_TVDIR2);
	   FrmCompararDiretorio.tabelaCompara = GetDlgItem(hwnd, ID_FRMCOMPARARDIRETORIO_LVCOMPARA);

	   TreeView_SetImageList(FrmCompararDiretorio.arvoreDir1, FrmPrincipal.imageList16, LVSIL_NORMAL);
	   TreeView_SetImageList(FrmCompararDiretorio.arvoreDir2, FrmPrincipal.imageList16, LVSIL_NORMAL);
	   
	   Rotinas_criaImageLists(hwnd, &FrmCompararDiretorio.imageList16, &FrmCompararDiretorio.imageList32);
	   Tabela_modeloColunas(FrmCompararDiretorio.tabelaCompara, TRUE, 
		   FrmCompararDiretorio.imageList16, FrmCompararDiretorio.imageList32);

	   FrmCompararDiretorio_montarArvores();
	   FrmCompararDiretorio_LimparComparacao();

	   FrmCompararDiretorio.frmCompararDiretorio = hwnd;

        return TRUE;
      }
      break;       
      case WM_COMMAND:
      {
        switch( LOWORD(wParam) ) {
          case ID_FRMCOMPARARDIRETORIO_BTNCOMPARARDIRETORIOS: 
          {     
			  FrmCompararDiretorio_btnCompararDiretoriosClick(hwnd);
          }
          break;
          case ID_FRMCOMPARARDIRETORIO_BTNSALVARLOG:
          {                
			  FrmCompararDiretorio_btnSalvarLogClick(hwnd);
          }
          break;
		  case ID_FRMCOMPARARDIRETORIO_CMBABA1:
		  {
			  if (HIWORD(wParam) == CBN_SELCHANGE) {
				  FrmCompararDiretorio_cmbAba1Choice();
			  }
		  }
		  break;
		  case ID_FRMCOMPARARDIRETORIO_CMBABA2:
		  {
			  if (HIWORD(wParam) == CBN_SELCHANGE) {
				  FrmCompararDiretorio_cmbAba2Choice();
			  }
		  }
		  break;
		}
      }   
      break;
      case WM_NOTIFY:
      { 
		  //Arvore_notifica(hwnd, FrmCompararDiretorio.arvoreDir1, wParam, lParam, ID_FRMCOMPARARDIRETORIO_TVDIR1);
		  //Arvore_notifica(hwnd, FrmCompararDiretorio.arvoreDir2, wParam, lParam, ID_FRMCOMPARARDIRETORIO_TVDIR2);
		  //Tabela_notifica(FrmCompararDiretorio.tabelaCompara, wParam, lParam, ID_FRMCOMPARARDIRETORIO_LVCOMPARA, TRUE);
      }      
      break;      
      case WM_CLOSE:
      {
		  FrmCompararDiretorio_Delete();
		  EndDialog(hwnd, FALSE);
      }
      break;
   }
  
   return FALSE;
}

VOID FrmCompararDiretorio_Mostrar(HWND hwnd) {
	DialogBox(g_hInstancia, MAKEINTRESOURCEW(FRMCOMPARARDIRETORIO), hwnd,
		(DLGPROC)frmCompararDiretorioProc);
}

VOID FrmCompararDiretorio_Delete() {
	ListaDiretorio_removeTodos(&FrmCompararDiretorio.listaCompara);
	ListaDiretorio_libera(&FrmCompararDiretorio.listaCompara);
	ImageList_Destroy(FrmPrincipal.imageListTabs);
	ImageList_Destroy(FrmPrincipal.imageList16);
	ImageList_Destroy(FrmPrincipal.imageList32);
}

void FrmCompararDiretorio_ProgressoLog(Progresso progresso)
{
	if (FrmCompararDiretorio.frmCompararDiretorio != NULL) {
		if (progresso.posicao == 0) {
			SendMessage(FrmCompararDiretorio.pb, PBM_SETRANGE, 0, MAKELPARAM(progresso.minimo, progresso.maximo));
			SendMessage(FrmCompararDiretorio.pb, PBM_SETSTEP, progresso.passo, 0);
		}
		SendMessage(FrmCompararDiretorio.pb, PBM_SETPOS, progresso.posicao, 0);
	}
}

void FrmCompararDiretorio_LimparComparacao() {
	SendMessage(FrmCompararDiretorio.pb, PBM_SETPOS, 0, 0);
	Tabela_limpar(FrmCompararDiretorio.tabelaCompara);
	Tabela_selecionaLinha(FrmCompararDiretorio.tabelaCompara, 0);
	Button_Enable(FrmCompararDiretorio.btnSalvarLog, FALSE);
	SendMessage(FrmCompararDiretorio.barraStatus, SB_SETTEXT, 1, (LPARAM)_T(""));
}

String FrmCompararDiretorio_BarraStatusGetStatusText(int indice) {
	String texto = String_iniciar("");
	SendMessage(FrmCompararDiretorio.barraStatus, SB_GETTEXT, indice, (LPARAM)texto.wstr);
	texto = String_copiar(texto.wstr);
	return texto;
}


void FrmCompararDiretorio_btnCompararDiretoriosClick(HWND hwnd) {
	String sCaminhoDir1 = String_iniciar(""), sCaminhoDir2 = String_iniciar("");
	BOOL bSelecionado;

	bSelecionado = FALSE;	
	if (Arvore_isSelecionado(FrmCompararDiretorio.arvoreDir1)) {
		Catalogador_LerArvoreDiretorio(FrmCompararDiretorio.arvoreDir1, 
			TreeView_GetSelection(FrmCompararDiretorio.arvoreDir1), FrmCompararDiretorio.barraStatus);
		sCaminhoDir1 = String_copiar(FrmCompararDiretorio_BarraStatusGetStatusText(1));

		if (Arvore_isSelecionado(FrmCompararDiretorio.arvoreDir2)) {
			Catalogador_LerArvoreDiretorio(FrmCompararDiretorio.arvoreDir2,
				TreeView_GetSelection(FrmCompararDiretorio.arvoreDir2), FrmCompararDiretorio.barraStatus);
			sCaminhoDir2 = String_copiar(FrmCompararDiretorio_BarraStatusGetStatusText(1));
			bSelecionado = TRUE;
		}
	}

	FrmCompararDiretorio_LimparComparacao();

	if (bSelecionado) {
		FrmCompararDiretorio_Comparar(hwnd, sCaminhoDir1, sCaminhoDir2);
	}
	else {
		Dialogo_mensagemInfo(hwnd,
			STR_FRMCOMPARARDIRETORIO_DIRETORIOSNAOSELECIONADOS);
	}
}

void FrmCompararDiretorio_btnSalvarLogClick(HWND hwnd) {
	String sLog;
	ListaString listaLocal = ListaString_inicia();
	ListaDiretorio local;
	Diretorio diretorio;
	
	int ntamlista = ListaDiretorio_conta(FrmCompararDiretorio.listaCompara);

	if (ntamlista > 0) {
		sLog = String_iniciar(Rotinas_AppDirPath());
		sLog = String_concatenar(Rotinas_BARRA_INVERTIDA, 
			Rotinas_formataDate(Rotinas_FORMATO_DHARQUIVO, Rotinas_DataHoraNow()),
			"_Comparacao.log");

		for (local = FrmCompararDiretorio.listaCompara; local != NULL; local = local->proximo) {
			diretorio = local->diretorio;
			ListaString_insereFim(&listaLocal, diretorio.caminho);
		}

		Rotinas_SListSaveToFile(listaLocal, sLog);

		Dialogo_mensagemInfo(hwnd,
			STR_FRMCOMPARARDIRETORIO_LOGSALVOMEMODIRSISTEMA);
	}
}

void FrmCompararDiretorio_cmbAba1Choice() {
	Aba *aba;

	Arvore_limpar(FrmCompararDiretorio.arvoreDir1);
	aba = AbaBO_pegaAbaPorOrdem(Catalogador.listaAbas,
		ComboBox_GetCurSel(FrmCompararDiretorio.cmbAba1) + 1);
	Catalogador_CarregarArvore(FrmCompararDiretorio.arvoreDir1, *aba);

	if (TreeView_GetCount(FrmCompararDiretorio.arvoreDir1) > 0) {
		TreeView_SelectItem(FrmCompararDiretorio.arvoreDir1, 
			TreeView_GetFirstVisible(FrmCompararDiretorio.arvoreDir1));
	}
	FrmCompararDiretorio_LimparComparacao();
}

void FrmCompararDiretorio_cmbAba2Choice() {
	Aba *aba;

	Arvore_limpar(FrmCompararDiretorio.arvoreDir2);
	aba = AbaBO_pegaAbaPorOrdem(Catalogador.listaAbas,
		ComboBox_GetCurSel(FrmCompararDiretorio.cmbAba2) + 1);
	Catalogador_CarregarArvore(FrmCompararDiretorio.arvoreDir2, *aba);

	if (TreeView_GetCount(FrmCompararDiretorio.arvoreDir2) > 0) {
		TreeView_SelectItem(FrmCompararDiretorio.arvoreDir2,
			TreeView_GetFirstVisible(FrmCompararDiretorio.arvoreDir2));
	}
	FrmCompararDiretorio_LimparComparacao();
}

void FrmCompararDiretorio_montarArvores()
{
	Aba aba;
	Aba *aba1;
	ListaAba local;
	
	for (local = Catalogador.listaAbas; local != NULL; local = local->proximo) {
		aba = local->aba;

		ComboBox_AddString(FrmCompararDiretorio.cmbAba1, aba.nome.wstr);
		ComboBox_AddString(FrmCompararDiretorio.cmbAba2, aba.nome.wstr);
	}
	ComboBox_SetCurSel(FrmCompararDiretorio.cmbAba1, 0);
	ComboBox_SetCurSel(FrmCompararDiretorio.cmbAba2, 0);

	aba1 = AbaBO_pegaAbaPorOrdem(Catalogador.listaAbas,
		ComboBox_GetCurSel(FrmCompararDiretorio.cmbAba1) + 1);
	Catalogador_CarregarArvore(FrmCompararDiretorio.arvoreDir1, *aba1);

	aba1 = AbaBO_pegaAbaPorOrdem(Catalogador.listaAbas,
		ComboBox_GetCurSel(FrmCompararDiretorio.cmbAba2) + 1);
	Catalogador_CarregarArvore(FrmCompararDiretorio.arvoreDir2, *aba1);
}

String FrmCompararDiretorio_SQLCompara(Aba aba1, Aba aba2, String caminho1,
	String caminho2) {
	String sSQL = String_iniciar("");

	sSQL = String_concatenar(DiretorioBO_SQL_CONSULTA_ARQUIVO, 10, 
		" WHERE aba=", String_FromInt(aba1.codigo).str,
		" AND caminho LIKE ", String_QuotedStr(String_concatenar(caminho1, "%")).str,
		" AND nome NOT IN (SELECT nome FROM Diretorios ",
		" WHERE aba=", String_FromInt(aba2.codigo).str, " AND caminho LIKE ",
		String_QuotedStr(String_concatenar(caminho2, "%")).str, ") ORDER BY 1, 2, 3");
	return sSQL;
}

void FrmCompararDiretorio_Comparar(HWND hwnd, String sCaminhoDir1, String sCaminhoDir2)
{
	String sSQL;
	Aba *aba1, *aba2;
	int tamLista;

	aba1 = AbaBO_pegaAbaPorOrdem(Catalogador.listaAbas,
		ComboBox_GetCurSel(FrmCompararDiretorio.cmbAba1) + 1);
	aba2 = AbaBO_pegaAbaPorOrdem(Catalogador.listaAbas,
		ComboBox_GetCurSel(FrmCompararDiretorio.cmbAba2) + 1);

	sSQL = FrmCompararDiretorio_SQLCompara(*aba1, *aba2, sCaminhoDir1, sCaminhoDir2);
	FrmCompararDiretorio.listaCompara = DiretorioBO_carregarDiretorio(sSQL,
		String_iniciar("consultaarquivo"), FrmCompararDiretorio_ProgressoLog);

	tamLista = ListaDiretorio_conta(FrmCompararDiretorio.listaCompara);

	if (tamLista > 0) {
		Tabela_adiciona(FrmCompararDiretorio.tabelaCompara, TRUE, 
			FrmCompararDiretorio.listaCompara,
			Catalogador.listaExtensoes, FrmCompararDiretorio.pb);
		Tabela_selecionaLinha(FrmCompararDiretorio.tabelaCompara, 0);

		SendMessage(FrmCompararDiretorio.barraStatus, SB_SETTEXT, 1,
			(LPARAM)String_FromInt(tamLista).wstr);
		Button_Enable(FrmCompararDiretorio.btnSalvarLog, TRUE);
	}
	else {
		Dialogo_mensagemInfo(hwnd,
			STR_FRMCOMPARARDIRETORIO_NENHUMADIFERENCAENCONTRADA);
	}
}
