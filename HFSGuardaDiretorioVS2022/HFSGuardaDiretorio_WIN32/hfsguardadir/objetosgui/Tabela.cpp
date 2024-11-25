#include "stdafx.h"

#include "hfsguardadir/objetosbo/ExtensaoBO.h"
#include "hfsguardadir/objetosgui/Tabela.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/catalogador/Catalogador.h"
#include "FrmPrincipal.h"
#include "resource.h"

HWND Tabela_cria(HWND hwnd, INT id, INT x, INT y, INT altura)
{ 
HWND hwndTabela;
DWORD nEstilo;
INT largura;
RECT rc;

GetClientRect(hwnd, &rc);
largura = rc.right - rc.left;

nEstilo = WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_VSCROLL | WS_HSCROLL |
LVS_REPORT | LVS_SINGLESEL | LVS_SHOWSELALWAYS | LVS_ALIGNLEFT | 
ES_AUTOVSCROLL | ES_AUTOHSCROLL;
      
hwndTabela = CreateWindowEx(WS_EX_CLIENTEDGE, WC_LISTVIEW, _T(""),  nEstilo,                  
     x, y, largura, altura, hwnd, (HMENU)id, 
    (HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE), NULL); 

return hwndTabela;
}

BOOL Tabela_insereColunas(HWND hwndTabela, UINT largura[],
    ListaString sColunas)
{
    LV_COLUMN lvc; 
  	ListaString local;
    INT nColunas;
     
    lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM; 
    lvc.fmt = LVCFMT_LEFT; 
    
    nColunas = -1;
	for (local = sColunas; local != NULL; local = local->proximo) {
   	    nColunas++;    
   	    lvc.cx = largura[nColunas];
        lvc.iSubItem = nColunas; 
        lvc.pszText = local->str.wstr;
        if (ListView_InsertColumn(hwndTabela, nColunas, &lvc) == -1)
            return FALSE; 
    } 
    ListView_SetItemCount(hwndTabela, MAXLINHAS_VISAOLISTA);
    return TRUE;
}

BOOL Tabela_insereLinha(HWND hwndTabela, UINT nQtdColunas, UINT nLinha, INT nImagem,  
	String colunas[QTD_MAX_COL])
{
	LVITEM lvItem;

	lvItem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM | LVIF_STATE;
	lvItem.state = LVIS_FOCUSED | LVIS_SELECTED; //0;
	lvItem.stateMask = LVIS_FOCUSED | LVIS_SELECTED; //0;     
	lvItem.iItem = nLinha;
	lvItem.iImage = nImagem;
	lvItem.iSubItem = 0;
	lvItem.lParam = (LPARAM)nLinha;
	lvItem.pszText = colunas[0].wstr;
	lvItem.cchTextMax = TAM_MAX_STR;

	if (ListView_InsertItem(hwndTabela, &lvItem) == -1)
		return FALSE;
	else {
		for (UINT nColuna = 1; nColuna < nQtdColunas; nColuna++)
		{
			ListView_SetItemText(hwndTabela, nLinha, nColuna, colunas[nColuna].wstr);
		}
	}
	return TRUE;
}

BOOL Tabela_insere(HWND hwndTabela, UINT nQtdColunas, ListaMString sLinhas, INT nImagem)
{
    ListaMString local;
    UINT nLinha;

	ListView_DeleteAllItems(hwndTabela);
   
    nLinha = -1;
	for (local = sLinhas; local != NULL; local = local->proximo) {
		nLinha++;
		if (!Tabela_insereLinha(hwndTabela, nQtdColunas, nLinha, nImagem, local->str))
			return FALSE;
	}

  return TRUE;
}

int CALLBACK Tabela_comparaASC(LPARAM item1, LPARAM item2, LPARAM lParamSort)
{
	if (item1 > item2)
		return 1;
	if (item1 < item2)
		return -1;

	return 0;
}

int CALLBACK Tabela_comparaDESC(LPARAM item1, LPARAM item2, LPARAM lParamSort)
{
	if (item1 < item2)
		return 1;
	if (item1 > item2)
		return -1;

	return 0;
}

BOOL Tabela_notifica(HWND hwndTabela, WPARAM wParam, LPARAM lParam, INT nIdItem, BOOL bTabelaDir)
{ 
	LPNMHDR pnmhdr = (LPNMHDR) lParam;
  
  if (LOWORD(wParam) == nIdItem) {

	  switch (pnmhdr->code) {
	  case LVN_COLUMNCLICK:
	  {
		  static BOOL bOrdemColuna = TRUE;
		  bOrdemColuna = !bOrdemColuna;

		  if (bOrdemColuna)
			  ListView_SortItems(hwndTabela, Tabela_comparaASC, 0);
		  else
			  ListView_SortItems(hwndTabela, Tabela_comparaDESC, 0);

	  }
	  break;
	  case NM_DBLCLK:
	  {
			LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE)lParam;
			Diretorio dir;

			if (ListView_GetSelectedCount(hwndTabela) > 0) {			
				dir = *Tabela_getItemSelecionado(hwndTabela, bTabelaDir);

				if (bTabelaDir) {					
					Catalogador_DuploCliqueLista(dir.arquivo.nome, 
						dir.tipo.nome);
				}
				else {
					Catalogador_EncontrarItemLista(dir.aba.nome, 
						dir.arquivo.nome, dir.caminho);
				}
				
			}

	  }
	  break;
	  }
  }
  return FALSE;
}

void Tabela_modeloColunas(HWND hTabela, BOOL bTabelaDir, HIMAGELIST imageList16, HIMAGELIST imageList32) {
	ListaString sColunas;	
	sColunas = ListaString_inicia();

	ListView_SetImageList(hTabela, imageList32, LVSIL_NORMAL);
	ListView_SetImageList(hTabela, imageList16, LVSIL_SMALL);

	if (bTabelaDir) {
		UINT nLargura[] = { 300, 100, 70, 120, 90, 500 };

		ListaString_insereFim(&sColunas, String_iniciar("Nome"));
		ListaString_insereFim(&sColunas, String_iniciar("Tamanho"));
		ListaString_insereFim(&sColunas, String_iniciar("Tipo"));
		ListaString_insereFim(&sColunas, String_iniciar("Modificado"));
		ListaString_insereFim(&sColunas, String_iniciar("Atributos"));
		ListaString_insereFim(&sColunas, String_iniciar("Caminho"));

		Tabela_insereColunas(hTabela, nLargura, sColunas);
	}
	else {
		UINT nLargura[] = { 300, 100, 70, 120, 90, 300, 70, 0, 0 };

		ListaString_insereFim(&sColunas, String_iniciar("Nome"));
		ListaString_insereFim(&sColunas, String_iniciar("Tamanho"));
		ListaString_insereFim(&sColunas, String_iniciar("Tipo"));
		ListaString_insereFim(&sColunas, String_iniciar("Modificado"));
		ListaString_insereFim(&sColunas, String_iniciar("Atributos"));
		ListaString_insereFim(&sColunas, String_iniciar("Caminho"));
		ListaString_insereFim(&sColunas, String_iniciar("Aba"));
		ListaString_insereFim(&sColunas, String_iniciar("Numero Aba"));
		ListaString_insereFim(&sColunas, String_iniciar("Nome do Pai"));

		Tabela_insereColunas(hTabela, nLargura, sColunas);
	}
}

void Tabela_limpar(HWND hTabela) {
	ListView_DeleteAllItems(hTabela);
}

void Tabela_adiciona(HWND hTabela, BOOL bTabelaDir, ListaDiretorio listaDir,
	ListaExtensao listaExtensao, HWND barraProgresso) {
	ListaDiretorio localDir;
	Diretorio dir;
	String sLinha = String_iniciar("");
	UINT nQtdColunas = 0, nLinha = 0;
	UINT nTamListaDir = ListaDiretorio_conta(listaDir);
	int nIndiceImagem;
	String sColuna[9];

	ListView_DeleteAllItems(hTabela);

	SendMessage(barraProgresso, PBM_SETRANGE, 0, MAKELPARAM(0, nTamListaDir));
	SendMessage(barraProgresso, PBM_SETSTEP, 1, 0);
	SendMessage(barraProgresso, PBM_SETPOS, nLinha, 0);

	for (localDir = listaDir; localDir != NULL; localDir = localDir->proximo) {
		dir = localDir->diretorio;

		sColuna[0] = String_iniciar(dir.arquivo.nome);

		if (dir.tipo.codigo == 'D') {
			sColuna[1] = String_limpar();
			nIndiceImagem = 0;
		}
		else {
			nIndiceImagem = ExtensaoBO_indiceExtensao(
				listaExtensao, dir.arquivo.nome);

			if (nIndiceImagem == -1) {
				nIndiceImagem = 1;
			}

			sColuna[1] = String_iniciar(dir.tamanhoFormatado);
		}	
		sColuna[2] = String_iniciar(dir.tipo.nome);
		sColuna[3] = String_iniciar(dir.modificadoFormatado);
		sColuna[4] = String_iniciar(dir.arquivo.atributos);
		sColuna[5] = String_iniciar(dir.caminho);

		if (bTabelaDir) {
			nQtdColunas = 6;
			sColuna[6] = String_limpar();
			sColuna[7] = String_limpar();
			sColuna[8] = String_limpar();
		}
		else {
			nQtdColunas = 9;		
			sColuna[6] = String_iniciar(dir.aba.nome);
			sColuna[7] = String_iniciar(String_FromInt(dir.aba.codigo));
			sColuna[8] = String_iniciar(dir.nomePai);
		}
		Tabela_insereLinha(hTabela, nQtdColunas, nLinha, nIndiceImagem, sColuna);
		
		nLinha++;
		SendMessage(barraProgresso, PBM_SETPOS, nLinha, 0);
	}
	SendMessage(barraProgresso, PBM_SETPOS, 0, 0);
}

BOOL Tabela_isSelecionado(HWND hTabela, UINT nLinha) {
	if (ListView_GetSelectedCount(hTabela) > 0) {
		return (ListView_GetItemState(hTabela, nLinha, LVIS_SELECTED)== LVIS_SELECTED);
	}

	return false;
}
VOID Tabela_selecionaLinha(HWND hTabela, UINT nLinha) {
	ListView_SetItemState(hTabela, nLinha, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
	ListView_EnsureVisible(hTabela, nLinha, FALSE);
}

VOID Tabela_ScrollLines(HWND hTabela, UINT nLinha) {
	ListView_Scroll(hTabela, 0, nLinha);
}

VOID Tabela_deselecionaLinha(HWND hTabela, UINT nLinha) {
	ListView_SetItemState(hTabela, nLinha, 0, 0);
}

UINT Tabela_encontrarLinha(HWND hTabela, LPCWSTR nome) {
	LPWSTR slinha = Rotinas_NewStr();
	UINT nlinha = 0;
	
	for (INT i = 0; i < ListView_GetItemCount(hTabela); i++) {
		ListView_GetItemText(hTabela, i, 0, slinha, TAM_MAX_STR);

		if (lstrcmp(slinha, nome)==0) {
			nlinha = i;
			break;
		}
	}
	return nlinha;
}

Diretorio* Tabela_getItemSelecionado(HWND hTabela, BOOL bTabelaDir) {
	WCHAR slinha[TAM_MAX_STR];
	Diretorio *dir = NULL;
	int nLinha;
	Aba aba;
	Tipo tipo;

	if (ListView_GetSelectedCount(hTabela) > 0) {
		dir = Diretorio_new();
	
		nLinha = ListView_GetSelectionMark(hTabela);

		slinha[0] = '\0';
		ListView_GetItemText(hTabela, nLinha, 0, slinha, TAM_MAX_STR);
		dir->arquivo.nome = String_iniciar(slinha);
			
		slinha[0] = '\0';
		ListView_GetItemText(hTabela, nLinha, 1, slinha, TAM_MAX_STR);
		dir->tamanhoFormatado = String_iniciar(slinha);

		slinha[0] = '\0';
		ListView_GetItemText(hTabela, nLinha, 2, slinha, TAM_MAX_STR);
		tipo.nome = String_iniciar(slinha);
		if (String_comparar(tipo.nome, Rotinas_lerStr(STR_TIPOLISTA_DIRETORIO))) {
			tipo.codigo = 'D';
		}
		else {
			tipo.codigo = 'A';
		}
		dir->tipo = Tipo_copiar(tipo);

		slinha[0] = '\0';
		ListView_GetItemText(hTabela, nLinha, 3, slinha, TAM_MAX_STR);
		dir->modificadoFormatado = String_iniciar(slinha);

		slinha[0] = '\0';
		ListView_GetItemText(hTabela, nLinha, 4, slinha, TAM_MAX_STR);
		dir->arquivo.atributos = String_iniciar(slinha);

		slinha[0] = '\0';
		ListView_GetItemText(hTabela, nLinha, 5, slinha, TAM_MAX_STR);
		dir->caminho = String_iniciar(slinha);

		if (!bTabelaDir) {
			slinha[0] = '\0';
			ListView_GetItemText(hTabela, nLinha, 6, slinha, TAM_MAX_STR);
			aba.nome = String_iniciar(slinha);
			
			slinha[0] = '\0';
			ListView_GetItemText(hTabela, nLinha, 7, slinha, TAM_MAX_STR);
			aba.codigo = slinha[0];

			dir->aba = Aba_copiar(aba);

			slinha[0] = '\0';
			ListView_GetItemText(hTabela, nLinha, 8, slinha, TAM_MAX_STR);
			dir->caminhoPai = String_iniciar(slinha);
		}
	}

	return dir;
}
