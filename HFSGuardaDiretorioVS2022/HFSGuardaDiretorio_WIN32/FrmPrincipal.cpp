#include "stdafx.h"

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <commdlg.h>

#include "HFSGuardaDiretorio.h"
#include "resource.h"
#include "FrmPrincipal.h"
#include "FrmSplash.h"
#include "FrmSobre.h"
#include "FrmFilho.h"
#include "FrmCompararDiretorio.h"
#include "FrmImportarDiretorio.h"
#include "FrmInfoDiretorio.h"
#include "FrmCadExtensao.h"
#include "hfsguardadir/objetosgui/BarraPesquisar.h"
#include "hfsguardadir/catalogador/Catalogador.h"

struct SFrmPrincipal FrmPrincipal;

VOID FrmPrincipal_criaImageListTabs(HWND hwnd) {
	FrmPrincipal.imageListTabs = ImageList_Create(16, 16, ILC_COLOR8 | ILC_MASK, 2, 0);

	HINSTANCE hi = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
	HBITMAP hbmCDOURO = LoadBitmap(hi, MAKEINTRESOURCE(CDOURO));
	HBITMAP hbmCDPRATA = LoadBitmap(hi, MAKEINTRESOURCE(CDPRATA));

	ImageList_AddMasked(FrmPrincipal.imageListTabs, hbmCDOURO, RGB(255, 0, 255));
	ImageList_AddMasked(FrmPrincipal.imageListTabs, hbmCDPRATA, RGB(255, 0, 255));

	DeleteObject(hbmCDOURO);
	DeleteObject(hbmCDPRATA);
}

void FrmPrincipal_ProgressoLog(Progresso progresso)
{
	if (FrmBarraPesquisar.frmBarraPesquisar != NULL) {
		if (progresso.posicao == 0) {
			SendMessage(FrmBarraPesquisar.pb, PBM_SETRANGE, 0, MAKELPARAM(progresso.minimo, progresso.maximo));
			SendMessage(FrmBarraPesquisar.pb, PBM_SETSTEP, progresso.passo, 0);
		}

		SendMessage(FrmBarraPesquisar.pb, PBM_SETPOS, progresso.posicao, 0);
	}

}

VOID FrmPrincipal_Delete() {
	ImageList_Destroy(FrmPrincipal.imageListTabs);
	ImageList_Destroy(FrmPrincipal.imageList16);
	ImageList_Destroy(FrmPrincipal.imageList32);
}

LRESULT CALLBACK frmPrincipalProc(HWND hwnd, UINT Message, 
                                  WPARAM wParam, LPARAM lParam)
{
   switch(Message)
   {
      case WM_CREATE:
      {
         CLIENTCREATESTRUCT ccs;
         int iStatusWidths[] = {300, -1};

		 FrmPrincipal_criaImageListTabs(hwnd);
		 Rotinas_criaImageLists(hwnd, &FrmPrincipal.imageList16, &FrmPrincipal.imageList32);

         // Acha no menu onde as janelas filhas serão listadas
         ccs.hWindowMenu  = GetSubMenu(GetMenu(hwnd), 3);
         ccs.idFirstChild = ID_MDI_PRIMEIROFORM;
         FrmPrincipal.MDICliente = CreateWindowEx(WS_EX_CLIENTEDGE, _T("MDICLIENT"), NULL,
            WS_CHILD | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL | WS_TABSTOP,
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
            hwnd, (HMENU)ID_MDI_CLIENTE, g_hInstancia, (LPVOID)&ccs);
         ShowWindow(FrmPrincipal.MDICliente, SW_SHOW);

         FrmPrincipal.barraStatus = CreateWindowEx(0, STATUSCLASSNAME, NULL,
            WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP, 0, 0, 0, 0,
            hwnd, (HMENU)ID_BARRADESTATUS, g_hInstancia, NULL);
         SendMessage(FrmPrincipal.barraStatus, SB_SETPARTS, 2, (LPARAM)iStatusWidths);
         SendMessage(FrmPrincipal.barraStatus, SB_SETTEXT, 0, 
                  (LPARAM)Rotinas_lerStr(STR_FRMPRINCIPAL_BARRASTATUS1));

		 FrmBarraPesquisar.frmBarraPesquisar = CreateDialog((HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
			 MAKEINTRESOURCEW(BARRAPESQUISAR), hwnd, (DLGPROC)frmBarraPesquisarProc);
		 ShowWindow(FrmBarraPesquisar.frmBarraPesquisar, SW_SHOW);

		 MoveWindow(hwnd, 0, 0, 924, 546, TRUE);
         Rotinas_CentralizaTela(hwnd);

		 Rotinas_ChamarForm(hwnd, Rotinas_lerStr(STR_FILHO),
			 MAKEINTRESOURCEW(FRMPRINCIPAL), FrmPrincipal.MDICliente, 340, 165);

		 FrmFilho_Criar(hwnd);

		 FrmPrincipal.frmPrincipal = hwnd;
         
         return 0;
      }
	  break;
	  case WM_CONTEXTMENU:
	  {
		  FrmPrincipal_OnContextMenu(hwnd, lParam);
	  }
	  break;
      case WM_COMMAND:
      {
         switch(LOWORD(wParam))
         {
            case IDM_INCLUIR_NOVA_ABA:
				Catalogador_IncluirNovaAba();
            break;
            case IDM_ALTERAR_NOME_ABA_ATIVA:
				Catalogador_AlterarNomeAbaAtiva(FrmPrincipal_ProgressoLog);
            break;  
			case IDM_EXCLUIR_ABA_ATIVA: 
				Catalogador_ExcluirAbaAtiva(FrmPrincipal_ProgressoLog);
			break;
			case IDM_IMPORTAR_DIRETORIO: 
				Catalogador_ComecaImportacao(FALSE, FrmPrincipal_ProgressoLog);
			break;
			case IDM_IMPORTAR_SUBDIRETORIOS: 
				Catalogador_ComecaImportacao(TRUE, FrmPrincipal_ProgressoLog);
			break; 
			case IDM_COMPARAR_DIRETORIOS:
				FrmCompararDiretorio_Mostrar(hwnd);
			break;
			case IDM_CADASTRAR_EXTENSAO_ARQUIVO: 
				FrmCadExtensao_Mostrar(hwnd);
			break; 
			case IDM_EXPANDIR_DIRETORIOS:
				FrmFilho_arvoreExpandirTodos();
			break; 
			case IDM_COLAPSAR_DIRETORIOS:
				FrmFilho_arvoreColapsarTodos();
			break;
			case IDM_TXT:				
				Catalogador_ExportarArquivo(teTXT, FrmPrincipal_ProgressoLog);
			break; 
			case IDM_CSV: 
				Catalogador_ExportarArquivo(teCSV, FrmPrincipal_ProgressoLog);
			break; 
			case IDM_HTML: 
				Catalogador_ExportarArquivo(teHTML, FrmPrincipal_ProgressoLog);
			break; 
			case IDM_XML: 
				Catalogador_ExportarArquivo(teXML, FrmPrincipal_ProgressoLog);
			break; 
			case IDM_SQL: 
				Catalogador_ExportarArquivo(teSQL, FrmPrincipal_ProgressoLog);
			break; 
			case IDM_IMPORTAR_DIRETORIOS_VIA_XML: {
				ListaString log = ListaString_inicia();
				Catalogador_ImportarArquivo(log, FrmPrincipal_ProgressoLog);
			}
			break; 
			case IDM_GRAVAR_LOG_IMPORTACAO: {
				static BOOL bGravarLogImportacao = FALSE;
				bGravarLogImportacao = !bGravarLogImportacao;

				if (bGravarLogImportacao) {
					CheckMenuItem(GetMenu(hwnd), IDM_GRAVAR_LOG_IMPORTACAO, MF_BYCOMMAND | MF_CHECKED);
					Catalogador.bGravarLogImportacao = bGravarLogImportacao;
				}
				else {
					CheckMenuItem(GetMenu(hwnd), IDM_GRAVAR_LOG_IMPORTACAO, MF_BYCOMMAND | MF_UNCHECKED);
					Catalogador.bGravarLogImportacao = bGravarLogImportacao;
				}
			}
			break; 
			case IDM_MOSTRAR_OCULTAR_ARVORE_DIR_ABA_ATIVA: 
				FrmFilho_mostraOcultarArvore();
			break; 
			case IDM_MOSTRAR_OCULTAR_LISTA_ITENS_PESQUISADOS: 
				FrmFilho_mostraOcultarTabelaPesquisa();
			break; 
			case IDM_INFORMACOES_DIRETORIO_ARQUIVO: {
				Tabela tabela = Catalogador_getTabelaAtual();

				if (ListView_GetSelectedCount(tabela) > 0) {
					Aba aba = Catalogador_getAbaAtual();
					Diretorio dir = *Tabela_getItemSelecionado(tabela, TRUE);
					dir.aba = Aba_copiar(aba);
					FrmInfoDiretorio_Mostrar(hwnd, dir);
				}

			}
			break;
			case IDM_EXCLUIR_DIRETORIO_SELECIONADO:
				Catalogador_ExcluirDiretorioSelecionado(FrmPrincipal_ProgressoLog);
			break;
			case IDM_ICONES:
				FrmFilho_setVisao(LVS_ICON);
			break; 
			case IDM_LISTA: 
				FrmFilho_setVisao(LVS_LIST);
			break; 
			case IDM_DETALHES: 
				FrmFilho_setVisao(LVS_REPORT);
			break; 
			case IDM_ICONES_PEQUENOS:
				FrmFilho_setVisao(LVS_SMALLICON);
			break;
            case IDM_SOBRE:
				FrmSobre_Mostrar(hwnd);
            break;
            default:
            {
               if(LOWORD(wParam) >= ID_MDI_PRIMEIROFORM){
                  DefFrameProc(hwnd, FrmPrincipal.MDICliente, Message, wParam, lParam);
               }
               else {
                 HWND hFilha;
                 hFilha = (HWND)SendMessage(FrmPrincipal.MDICliente, WM_MDIGETACTIVE,0,0);
                 if(hFilha){
                    SendMessage(hFilha, WM_COMMAND, wParam, lParam);
                 }
               }
            }
         }
      }
      break;
      case WM_SIZE:
      {
         RECT rectClient, rectStatus, rectBarraPesquisar;
         UINT uBarraPesquisarHeight, uStatusHeight, uClientAlreaHeight;

		 //SendMessage(FrmBarraPesquisar.frmBarraPesquisar, TB_AUTOSIZE, 0, 0);
         SendMessage(FrmPrincipal.barraStatus, WM_SIZE, 0, 0);

         GetClientRect(hwnd, &rectClient);
         GetWindowRect(FrmPrincipal.barraStatus, &rectStatus);
		 GetWindowRect(FrmBarraPesquisar.frmBarraPesquisar, &rectBarraPesquisar);

         uBarraPesquisarHeight = rectBarraPesquisar.bottom - rectBarraPesquisar.top;
         uStatusHeight = rectStatus.bottom - rectStatus.top;
         uClientAlreaHeight = rectClient.bottom;
		
         MoveWindow(FrmPrincipal.MDICliente, 0, uBarraPesquisarHeight, rectClient.right,
                  uClientAlreaHeight - uStatusHeight - uBarraPesquisarHeight, TRUE);
		
		 MoveWindow(FrmBarraPesquisar.frmBarraPesquisar, 0, 0, rectClient.right, uBarraPesquisarHeight, TRUE);
		 
		 MoveWindow(FrmFilho.frmFilho, 0, 0, rectClient.right - 2,
			 uClientAlreaHeight - uStatusHeight - uBarraPesquisarHeight - 2, TRUE);
      }
      break;
	  case WM_CLOSE:
      {  
		  Rotinas_BancoDesconectar();
		  Catalogador_Delete();
		  FrmPrincipal_Delete();
		  DestroyWindow(hwnd);
      }       
      break;
      case WM_DESTROY:
         PostQuitMessage(0);
      break;
      default:
         return DefFrameProc(hwnd, FrmPrincipal.MDICliente, Message, wParam, lParam);
   }
   return 0;
}

VOID FrmPrincipal_OnContextMenu(HWND hwnd, LPARAM lParam) {
	HMENU hmenu;
	HMENU hmenuTrackPopup;
	INT xPos = GET_X_LPARAM(lParam);
	INT yPos = GET_Y_LPARAM(lParam);

	if ((hmenu = LoadMenu(g_hInstancia, MAKEINTRESOURCE(IDM_POPUP))) == NULL)
		return;

	hmenuTrackPopup = GetSubMenu(hmenu, 0);

	TrackPopupMenu(hmenuTrackPopup, TPM_LEFTALIGN | TPM_RIGHTBUTTON,
		xPos, yPos, 0, hwnd, NULL);

	DestroyMenu(hmenu);
}

String FrmPrincipal_BarraStatusGetStatusText(int indice) {
	//SB_GETTEXTLENGTH
	String texto = String_iniciar("");
	SendMessage(FrmPrincipal.barraStatus, SB_GETTEXT, indice, (LPARAM)texto.wstr);
	texto = String_copiar(texto.wstr);
	return texto;
}

