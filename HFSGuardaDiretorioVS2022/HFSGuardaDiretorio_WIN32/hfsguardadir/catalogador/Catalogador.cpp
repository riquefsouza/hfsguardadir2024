#include "stdafx.h"

#include <windowsx.h>
#include "Catalogador.h"
#include "FrmFilho.h"
#include "HFSGuardaDiretorio.h"
#include "FrmSplash.h"
#include "hfsguardadir/objetosbo/AbaBO.h"
#include "hfsguardadir/objetosbo/ExtensaoBO.h"
#include "hfsguardadir/objetosbo/DiretorioBO.h"
#include "hfsguardadir/objetosdao/VisaoDAO.h"
#include "hfsguardadir/objetosgui/Dialogo.h"
#include "hfsguardadir/objetosgui/EscolhaArquivo.h"
#include "hfsguardadir/objetos/Importar.h"
#include "hfsguardadir/objetosgui/TabControle.h"
#include "hfsguardadir/objetosgui/BarraPesquisar.h"

struct SCatalogador Catalogador;

void Catalogador_New() {
	Catalogador.CONSULTA_DIR_PAI = String_iniciar(
		"select aba, cod, ordem, coddirpai, nome, tam, tipo, modificado, " \
		"atributos, caminho, nomeaba, nomepai, caminhopai " \
		"from consultadirpai " \
		"order by 1,2,3,4");
	Catalogador.CONSULTA_DIR_FILHO = String_iniciar(
		"select aba, cod, ordem, coddirpai, nome, tam, tipo, modificado, " \
		"atributos, caminho, nomeaba, nomepai, caminhopai " \
		"from consultadirfilho " \
		"order by 1,2,3,4");
	Catalogador.CONSULTA_ARQUIVO = String_iniciar(
		"select aba, cod, ordem, coddirpai, nome, tam, tipo, modificado, " \
		"atributos, caminho, nomeaba, nomepai, caminhopai " \
		"from consultaarquivo " \
		"order by tipo desc, ordem");
	Catalogador.NO_RAIZ = String_iniciar("Raiz");

	Catalogador.bGravarLogImportacao = FALSE;

	Catalogador_iniciarSistema();
	SetCursor(LoadCursor(NULL, IDC_WAIT));

	if (FrmSplash_Criar(FrmPrincipal.frmPrincipal)) {
		FrmSplash_Mostrar();
	}
	
	Catalogador_CarregarDados(FrmSplash_ProgressoLog, TRUE, TRUE);
	Catalogador_CarregarAbas();
	Catalogador_tabPanelMudou();

	EndDialog(FrmSplash.frmSplash, TRUE);
	DestroyWindow(FrmSplash.frmSplash);

	SetCursor(LoadCursor(NULL, IDC_ARROW));
}

void Catalogador_Delete() {
	ListaDiretorio_removeTodos(&Catalogador.listaDiretorioFilho);
	ListaDiretorio_removeTodos(&Catalogador.listaArquivos);	
	ListaAba_removeTodos(&Catalogador.listaAbas);
	ListaDiretorio_removeTodos(&Catalogador.listaDiretorioPai);
	ListaExtensao_removeTodos(&Catalogador.listaExtensoes);

	ListaDiretorio_libera(&Catalogador.listaDiretorioFilho);
	ListaDiretorio_libera(&Catalogador.listaArquivos);
	ListaAba_libera(&Catalogador.listaAbas);
	ListaDiretorio_libera(&Catalogador.listaDiretorioPai);
	ListaExtensao_libera(&Catalogador.listaExtensoes);
}

void Catalogador_iniciarSistema() {
	Aba aba;
	String sBanco = Rotinas_AppDirName();
	sBanco = String_concatenar(sBanco, "GuardaDir.db");

    if (!Rotinas_FileExists(sBanco)){
        Rotinas_BancoConectar(sBanco);

        AbaBO_criarTabelaAbas();

		aba.codigo = 1;
		aba.nome = String_iniciar("DISCO1");
		aba.ordem = 0;
        AbaBO_incluirAba(aba);

        ExtensaoBO_criarTabelaExtensoes();
        DiretorioBO_criarTabelaDiretorios();
        VisaoDAO_criarVisao(String_iniciar("consultadirpai"));
        VisaoDAO_criarVisao(String_iniciar("consultadirfilho"));
        VisaoDAO_criarVisao(String_iniciar("consultaarquivo"));
    } else
        Rotinas_BancoConectar(sBanco);

}

void Catalogador_CarregarDados(IProgressoLog pLog, BOOL bExtensao, BOOL bDiretorio) {
	Catalogador.listaAbas = AbaBO_carregarAba(pLog);
    if (bExtensao) {
		Catalogador.listaExtensoes = ExtensaoBO_carregarExtensao(pLog);
    }
    if (bDiretorio) {
		Catalogador.listaDiretorioPai = DiretorioBO_carregarDiretorio(
			Catalogador.CONSULTA_DIR_PAI, pLog);
		Catalogador.listaDiretorioFilho = DiretorioBO_carregarDiretorio(
			Catalogador.CONSULTA_DIR_FILHO, pLog);
		Catalogador.listaArquivos = DiretorioBO_carregarDiretorio(
			Catalogador.CONSULTA_ARQUIVO, pLog);
    }		
}

void Catalogador_ExcluirDados(Aba aba, String sCaminho) {
    DiretorioBO_excluirListaDiretorio(&Catalogador.listaDiretorioPai, aba, sCaminho);
    DiretorioBO_excluirListaDiretorio(&Catalogador.listaDiretorioFilho, aba, sCaminho);
    DiretorioBO_excluirListaDiretorio(&Catalogador.listaArquivos, aba, sCaminho);
}

void Catalogador_AddItemArvore(Arvore arvore, Diretorio diretorio, int Nivel,
        HTREEITEM item1) {
    ListaDiretorio listaFilhos, local;
    HTREEITEM item2;
    Diretorio filho;
    TV_INSERTSTRUCT lpis, lpis2;

    if (Nivel == 0) {
        lpis = Arvore_item(diretorio.arquivo.nome.wstr, NULL, TVI_ROOT, Nivel);
		item1 = TreeView_InsertItem(arvore, &lpis);
		//TreeView_SelectSetFirstVisible(arvore, item1);
    }

    listaFilhos = DiretorioBO_itensFilhos(Catalogador.listaDiretorioFilho,
            diretorio.aba.codigo, diretorio.ordem,
            diretorio.codigo);

	for (local = listaFilhos; local != NULL; local = local->proximo) {
		filho = local->diretorio;

        lpis2 = Arvore_item(filho.arquivo.nome.wstr, item1, TVI_LAST, Nivel);
		item2 = TreeView_InsertItem(arvore, &lpis2);
		Catalogador_AddItemArvore(arvore, filho, ++Nivel, item2);
    }
}

void Catalogador_IncluirNovaAba() {
    Aba aba;

    String sAba =  Dialogo_entrada(FrmFilho.frmFilho, STR_FRMPRINCIPAL_DIGITAINCLUIRNOVAABA);

    if ((sAba.length > 0) && (String_Trim(sAba).length > 0)) {
        aba.codigo = AbaBO_retMaxCodAba(Catalogador.listaAbas);
        aba.nome = String_SubString(sAba, 1, 10);
        aba.ordem = ListaAba_conta(Catalogador.listaAbas) + 1;
        AbaBO_incluirAba(aba);
        Catalogador_IncluirNovaAba(aba.nome, aba.ordem-1);
		ListaAba_insereFim(&Catalogador.listaAbas, aba);
    }
}

void Catalogador_AlterarNomeAbaAtiva(IProgressoLog pLog) {
    Aba aba = Catalogador_getAbaAtual();
    String sAba = Dialogo_entrada(FrmFilho.frmFilho, STR_FRMPRINCIPAL_DIGITAALTERARNOMEABA,
            aba.nome);
    if ((sAba.length > 0) && (String_Trim(sAba).length > 0)) {
		aba.nome = String_SubString(sAba, 1, 10);
        AbaBO_alterarAba(aba);
		TabControle_altera(FrmFilho.tabControl, TabCtrl_GetCurSel(FrmFilho.tabControl), sAba.wstr);
		Catalogador_CarregarDados(pLog, FALSE, TRUE);
    }
}

void Catalogador_ExcluirAbaAtiva(IProgressoLog pLog) {
    Aba aba;
	int indiceSel = TabCtrl_GetCurSel(FrmFilho.tabControl);
    if (indiceSel > 0) {
        if (Dialogo_confirma(FrmFilho.frmFilho, STR_FRMPRINCIPAL_CONFIRMAEXCLUIRABA)) {
			SetCursor(LoadCursor(NULL, IDC_WAIT));

            aba = Catalogador_getAbaAtual();
			Catalogador_ExcluirDados(aba, String_iniciar(""));
            AbaBO_excluirAba(aba);
			TabControle_remove(FrmFilho.tabControl, indiceSel);

			Catalogador_CarregarDados(pLog, FALSE, FALSE);

			SendMessage(FrmPrincipal.barraStatus, SB_SETTEXT, 1, (LPARAM)_T(""));

			SetCursor(LoadCursor(NULL, IDC_ARROW));
        }
    } else
            Dialogo_mensagemErro(FrmFilho.frmFilho, STR_FRMPRINCIPAL_VALIDAEXCLUIRABA);
}

void Catalogador_IncluirNovaAba(String nomeAba, int numAba){
	TabControle_adiciona(FrmFilho.tabControl, numAba, nomeAba.wstr);
}

Arvore Catalogador_getArvoreAtual() {
	return FrmFilho.arvore;
}

Arvore Catalogador_getArvoreAtual(int nIndicePagina) {	
	return FrmFilho.arvore;
}

Tabela Catalogador_getTabelaAtual(int nIndicePagina) {	
	return FrmFilho.tabela;
}

Tabela Catalogador_getTabelaAtual() {	
	return FrmFilho.tabela;
}

void Catalogador_CarregarArvore(Arvore tvAba, Aba aba) {
	ListaDiretorio local;
	Diretorio diretorio;

	//Catalogador.nodeRaiz = TreeView_InsertItem(tvAba, 
		//&Arvore_item(Catalogador.NO_RAIZ.wstr, TVI_ROOT));
	//TreeView_SelectSetFirstVisible(tvAba, Catalogador.nodeRaiz);

	for (local = Catalogador.listaDiretorioPai; local != NULL; local = local->proximo) {
		diretorio = local->diretorio;

        if (diretorio.aba.codigo == aba.codigo) {
			Catalogador_AddItemArvore(tvAba, diretorio, 0, NULL);
        }
    }
}

void Catalogador_CarregarAbas() {
    Arvore tvAba;
	ListaAba local;
    Aba aba;
	int i = 0;

	for (local = Catalogador.listaAbas; local != NULL; local = local->proximo) {
		aba = local->aba;

		Catalogador_IncluirNovaAba(aba.nome, i);
        tvAba = Catalogador_getArvoreAtual(i);
		i++;
    }
}

Aba Catalogador_getAbaAtual() {
	int indiceSel = TabCtrl_GetCurSel(FrmFilho.tabControl);
    return *AbaBO_pegaAbaPorOrdem(Catalogador.listaAbas, indiceSel + 1);
}

void Catalogador_CarregarArquivosLista(Tabela tabela, BOOL bLista1, String caminho) {
	String sPaiCaminho, sCaminho = String_iniciar(caminho);
    ListaDiretorio local, listaLocal = ListaDiretorio_inicia();
	Diretorio diretorio;
    int nAba;

    if (bLista1) {
        sPaiCaminho = String_iniciar(sCaminho);
        if (!String_comparar(String_SubString(sCaminho, sCaminho.length, 1), Rotinas_BARRA_INVERTIDA)) {
            sCaminho = String_concatenar(sCaminho, Rotinas_BARRA_INVERTIDA);
        }
        nAba = Catalogador_getAbaAtual().codigo;

		for (local = Catalogador.listaArquivos; local != NULL; local = local->proximo) {
			diretorio = local->diretorio;

            if (diretorio.aba.codigo == nAba) {
                if (String_comparar(diretorio.caminhoPai, sPaiCaminho)) {
                    if (String_cStartsStr(sCaminho.str, diretorio.caminho.str)) {
						ListaDiretorio_insereFim(&listaLocal, diretorio);
                    }
                }
            }
        }
    } else {
		for (local = Catalogador.listaArquivos; local != NULL; local = local->proximo) {
			diretorio = local->diretorio;

			if (String_cContainsStr(String_UpperCase(diretorio.caminho).str,
				String_UpperCase(sCaminho).str)) {
				ListaDiretorio_insereFim(&listaLocal, diretorio);
            }
        }
    }
	Tabela_adiciona(tabela, bLista1, listaLocal, Catalogador.listaExtensoes, FrmBarraPesquisar.pb);

	ListaDiretorio_removeTodos(&listaLocal);
}

void Catalogador_TamTotalDiretorio(Aba aba, String sCaminho) {
	ListaDiretorio local;
	Diretorio diretorio;
    long conta;
    int nAba;
    unsigned long long soma, tam;
	String status = String_iniciar("");

    conta = 0;
    soma = 0;

	for (local = Catalogador.listaArquivos; local != NULL; local = local->proximo) {
		diretorio = local->diretorio;

		nAba = aba.codigo;
        if (diretorio.aba.codigo == nAba) {
            if (diretorio.tipo.codigo != 'D') {
                if (String_Trim(sCaminho).length > 0) {
                    if (String_cStartsStr(sCaminho.str, diretorio.caminho.str)) {
                        conta++;
                        tam = diretorio.arquivo.tamanho;
                        soma += tam;
                    }
                } else {
                    conta++;
                    tam = diretorio.arquivo.tamanho;
                    soma += tam;
                }
            }
        }
    }

	status = String_concatenar(status, 4, "Quantidade Total: ", String_FromULong(conta).str,
		", Tamanho Total: ", Rotinas_MontaTamanho(soma).str);

	SendMessage(FrmPrincipal.barraStatus, SB_SETTEXT, 0, (LPARAM)status.wstr);
}

BOOL Catalogador_testaSeparadorArquivo(String sDir) {
    String dir = String_SubString(sDir, sDir.length, 1);
    if (String_comparar(dir, Rotinas_BARRA_NORMAL)
            || String_comparar(dir, Rotinas_BARRA_INVERTIDA)) {
        return TRUE;
    } else {
        return FALSE;
    }
}

ListaString Catalogador_montaCaminho(String sCaminho, BOOL bRemover) {
    String caminho = sCaminho;
    ListaString sl = ListaString_inicia();
	String item;
    sl = Rotinas_SListSeparador(caminho, Rotinas_BARRA_INVERTIDA.str[0]);
	int tamlista = ListaString_conta(sl);

	if (tamlista > 1) {
		item = String_iniciar(ListaString_pesquisaItemOrd(sl, tamlista - 1));

		if (String_Trim(item).length == 0) {
			ListaString_removeItemOrd(&sl, tamlista - 1, TRUE);
		}
		if (bRemover) {
			ListaString_removeItemOrd(&sl, tamlista - 1, TRUE);
		}
	}
    return sl;
}

void Catalogador_Pesquisar() {
    Arvore arvoreLocal = Catalogador_getArvoreAtual();

    if (TreeView_GetCount(arvoreLocal) > 0) {
		//String edtPesquisa = Rotinas_retTexto(FrmBarraPesquisar.edtPesquisa);
		String edtPesquisa = String_iniciar("");
		Edit_GetText(FrmBarraPesquisar.edtPesquisa, edtPesquisa.wstr, TAM_MAX_STR);
		edtPesquisa = String_copiar(edtPesquisa.wstr);

        if (edtPesquisa.length >= 2) {
			FrmFilho_mostraOcultarTabelaPesquisa(TRUE);

			Catalogador_CarregarArquivosLista(FrmFilho.tabelaPesquisa, FALSE,
				edtPesquisa);
        } else {
			FrmFilho_mostraOcultarTabelaPesquisa(FALSE);
			Tabela_limpar(FrmFilho.tabelaPesquisa);
            Dialogo_mensagemInfo(FrmFilho.frmFilho, STR_FRMPRINCIPAL_TAMMAXPESQUISA);
        }
    }
}

void Catalogador_PesquisarArvoreDiretorio(String sCaminho, Aba aba, BOOL bRemover) {
	TabCtrl_SetCurSel(FrmFilho.tabControl, aba.ordem-1);
    Arvore arvore = Catalogador_getArvoreAtual();
	ListaString sl = Catalogador_montaCaminho(sCaminho, bRemover);
	Arvore_encontrarCaminhoPorNome(arvore, sl);

	ListaString_removeTodos(&sl);
	ListaString_libera(&sl);
}

void Catalogador_LerArvoreDiretorio(Arvore arvore, HTREEITEM item,
	HWND barraStatus) {
	String texto = String_iniciar("");
    String caminho = String_iniciar("");
	ListaString local;
	ListaString lista = Catalogador_montaCaminho(arvore, item);
	int ntamlista = ListaString_conta(lista);

	for (local = lista; local != NULL; local = local->proximo) {
		texto = local->str;

		caminho = String_concatenar(caminho, texto, Rotinas_BARRA_INVERTIDA);
	}

    if (ntamlista > 0) {
		caminho = String_SubString(caminho, 1, caminho.length - 1);
		SendMessage(barraStatus, SB_SETTEXT, 1, (LPARAM)caminho.wstr);
    }

	ListaString_removeTodos(&lista);
	ListaString_libera(&lista);
}

void Catalogador_ListarArquivos() {
	Tabela tabela = Catalogador_getTabelaAtual();
	String texto = FrmPrincipal_BarraStatusGetStatusText(1);
	Catalogador_CarregarArquivosLista(tabela, TRUE, texto);
	Catalogador_TamTotalDiretorio(Catalogador_getAbaAtual(), texto);
}

void Catalogador_tabPanelMudou(){
	Catalogador_tabPanelMudou(Catalogador_getAbaAtual());
}

void Catalogador_tabPanelMudou(Aba aba) {
	Arvore_limpar(Catalogador_getArvoreAtual());
	Tabela_limpar(Catalogador_getTabelaAtual());
	Catalogador_CarregarArvore(Catalogador_getArvoreAtual(), aba);
	Catalogador_TamTotalDiretorio(aba, String_iniciar(""));
}

void Catalogador_arvoreValorMudou(Arvore arvore, HTREEITEM item) {
	Catalogador_LerArvoreDiretorio(arvore, item, FrmPrincipal.barraStatus);
	Catalogador_ListarArquivos();
}

void Catalogador_DuploCliqueLista(String nome, String tipo) {
    if (String_comparar(tipo, Rotinas_lerStr(STR_TIPOLISTA_DIRETORIO))) {
		SetCursor(LoadCursor(NULL, IDC_WAIT));

        String sCaminho = FrmPrincipal_BarraStatusGetStatusText(1);
        if (Catalogador_testaSeparadorArquivo(sCaminho)) {
            sCaminho = String_concatenar(sCaminho, nome);
        } else {
            sCaminho = String_concatenar(sCaminho, Rotinas_BARRA_INVERTIDA, nome);
        }
		SendMessage(FrmPrincipal.barraStatus, SB_SETTEXT, 1, (LPARAM)sCaminho.wstr);

		Catalogador_PesquisarArvoreDiretorio(sCaminho, Catalogador_getAbaAtual(), FALSE);

		Catalogador_CarregarArquivosLista(Catalogador_getTabelaAtual(), TRUE, sCaminho);
		Catalogador_TamTotalDiretorio(Catalogador_getAbaAtual(), sCaminho);

		SetCursor(LoadCursor(NULL, IDC_ARROW));
    }
}

void Catalogador_EncontrarItemLista(String nomeAba, 
	String nome, String caminho) {

	SetCursor(LoadCursor(NULL, IDC_WAIT));
    
	Aba *aba = AbaBO_pegaAbaPorNome(Catalogador.listaAbas, nomeAba);
	Catalogador_tabPanelMudou(*aba);
	Catalogador_PesquisarArvoreDiretorio(caminho, *aba, TRUE);

	Arvore arvore = Catalogador_getArvoreAtual();
	Catalogador_arvoreValorMudou(arvore, TreeView_GetSelection(arvore));

    Tabela tabela = Catalogador_getTabelaAtual();
	int nlinha = Tabela_encontrarLinha(tabela, nome.wstr);
	Tabela_selecionaLinha(tabela, nlinha);
	Tabela_ScrollLines(tabela, nlinha);

	SetCursor(LoadCursor(NULL, IDC_ARROW));
}

int Catalogador_verificaNomeDiretorio(String sCaminho, RotuloRaiz *sRotuloRaiz) {
    sRotuloRaiz->rotulo = DiretorioBO_removerDrive(sCaminho);
    if (sRotuloRaiz->rotulo.length == 0) {

        sRotuloRaiz->rotulo = String_copiar(
			Dialogo_entrada(FrmFilho.frmFilho, STR_FRMPRINCIPAL_DIGITANOMEDIRETORIO));

        if (String_Trim(sRotuloRaiz->rotulo).length > 0) {
            sRotuloRaiz->rotulo = String_copiar(String_Trim(sRotuloRaiz->rotulo));

            if (sRotuloRaiz->rotulo.length > 0) {
                return 1;
            } else {
                Dialogo_mensagemInfo(FrmFilho.frmFilho, STR_FRMPRINCIPAL_VALIDANOMEDIRETORIO);
                return 0;
            }
        } else {
            return 0;
        }
    } else if (String_cPos(Rotinas_BARRA_INVERTIDA.str,
            sRotuloRaiz->rotulo.str) > 0) {
        sRotuloRaiz->rotulo = String_SubString(sRotuloRaiz->rotulo,
                String_cLastDelimiter(Rotinas_BARRA_INVERTIDA.str,
                        sRotuloRaiz->rotulo.str) + 1,
                sRotuloRaiz->rotulo.length);
        return 2;
    } else {
        return 3;
    }
}

void Catalogador_ExportarArquivo(TipoExportar tipo, IProgressoLog pLog) {
    String sExtensao = String_iniciar("");

    switch (tipo) {
        case teTXT:
            sExtensao = String_copiar("txt");
            break;
        case teCSV:
            sExtensao = String_copiar("csv");
            break;
        case teHTML:
            sExtensao = String_copiar("html");
            break;
        case teXML:
            sExtensao = String_copiar("xml");
            break;
        case teSQL:
            sExtensao = String_copiar("sql");
            break;
    }

    Aba aba = Catalogador_getAbaAtual();
    
	String sArq = Rotinas_AppDirPath();
	sArq = String_concatenar(Rotinas_BARRA_INVERTIDA, 3, aba.nome.str, ".", sExtensao.str);
	String arqSelecionado = EscolhaArquivo_salvarArquivo(FrmFilho.frmFilho, sArq, sExtensao);
    if (arqSelecionado.length > 0) {
        if (Rotinas_FileExists(arqSelecionado)) {
			SetCursor(LoadCursor(NULL, IDC_WAIT));
            DiretorioBO_exportarDiretorio(tipo, Catalogador_getAbaAtual(),
                    arqSelecionado, pLog);
			SetCursor(LoadCursor(NULL, IDC_ARROW));

            Dialogo_mensagemErro(FrmFilho.frmFilho, STR_FRMPRINCIPAL_SUCESSOEXPORTAR);
        }
    }
    
}

ListaString Catalogador_montaCaminho(Arvore arvore, HTREEITEM item) {
	HTREEITEM pai = item;
	ListaString lista = ListaString_inicia();
	String texto;

	do {
		texto = Arvore_GetItemText(arvore, pai);
		if (texto.length > 0) {
			ListaString_insereFim(&lista, texto);
			pai = TreeView_GetParent(arvore, pai);
		}
		else {
			break;
		}
	} while (pai != NULL); // && pai != TreeView_GetRoot(arvore));

	ListaString_inverter(&lista);

	return lista;
}

void Catalogador_ExcluirDiretorioSelecionado(IProgressoLog pLog) {
    Arvore arvore = Catalogador_getArvoreAtual();
	
    if (Arvore_isSelecionado(arvore)) {
        Tabela tabela = Catalogador_getTabelaAtual();

		if (Dialogo_confirma(FrmFilho.frmFilho, 
			STR_FRMPRINCIPAL_EXCLUIRDIRETORIOSELECIONADO)) {

			SetCursor(LoadCursor(NULL, IDC_WAIT));
            ListaString sl = Catalogador_montaCaminho(arvore, TreeView_GetSelection(arvore));
			String caminho = Rotinas_SListTexto(sl);

			ListaString_removeTodos(&sl);
			ListaString_libera(&sl);

			DiretorioBO_excluirDiretorio(Catalogador_getAbaAtual(), caminho);
			Catalogador_ExcluirDados(Catalogador_getAbaAtual(), caminho);

			TreeView_DeleteItem(arvore, TreeView_GetSelection(arvore));
			Tabela_limpar(tabela);

			Catalogador_CarregarDados(pLog, FALSE, FALSE);

			SetCursor(LoadCursor(NULL, IDC_ARROW));
        }
    }
}

void Catalogador_ImportarArquivo(ListaString log, IProgressoLog pLog) {
    int nResultado;

	String arquivo = EscolhaArquivo_abrirArquivo(FrmFilho.frmFilho);
	if (arquivo.length > 0) {
        if (Rotinas_FileExists(arquivo)) {
			SetCursor(LoadCursor(NULL, IDC_WAIT));
            nResultado = DiretorioBO_importarDiretorioViaXML(
				Catalogador_getAbaAtual(), arquivo, Catalogador.listaDiretorioPai, pLog);
            if (nResultado == -1) {
                Dialogo_mensagemErro(FrmFilho.frmFilho,
                        STR_FRMPRINCIPAL_IMPORTACAONAOREALIZADA);
            } else if (nResultado == -2) {
                Dialogo_mensagemErro(FrmFilho.frmFilho,
                        STR_FRMPRINCIPAL_DIRETORIOEXISTECATALOGO);
            } else {
				Catalogador_FinalizaImportacao(pLog);
            }
			SetCursor(LoadCursor(NULL, IDC_ARROW));
        }
    }
}

BOOL Catalogador_ImportarDiretorios(ListaString listaCaminho,
        BOOL bSubDiretorio, HWND frmImportarDiretorio) {
	ListaString local;
    int nAba, nRotuloRaiz, nCodDirRaiz;
    RotuloRaiz *sRotuloRaiz = new RotuloRaiz();
    String sCaminhoSemDrive;
    Importar importar;
	String sCaminho = String_iniciar("");

    nAba = Catalogador_getAbaAtual().codigo;
    nCodDirRaiz = DiretorioBO_retMaxCodDir(nAba, Catalogador.listaDiretorioPai);

	for (local = listaCaminho; local != NULL; local = local->proximo) {
		sCaminho = String_copiar(local->str);

        nRotuloRaiz = Catalogador_verificaNomeDiretorio(sCaminho, sRotuloRaiz);
        if (nRotuloRaiz > 0) {
            importar.aba = nAba;
            importar.codDirRaiz = nCodDirRaiz;
            importar.rotuloRaiz = sRotuloRaiz->rotulo;
            if (nRotuloRaiz == 1) {
                importar.nomeDirRaiz = sRotuloRaiz->rotulo;
            } else if (nRotuloRaiz == 2) {
                sCaminhoSemDrive = DiretorioBO_removerDrive(sCaminho);
                importar.nomeDirRaiz = String_SubString(
                        sCaminhoSemDrive, 1,
                        String_cLastDelimiter(Rotinas_BARRA_INVERTIDA.str,
                                sCaminhoSemDrive.str) - 1);
            } else if (nRotuloRaiz == 3) {
                importar.nomeDirRaiz = String_iniciar("");
            }
            importar.caminho = String_iniciar(sCaminho);

			ListaImportar_insereFim(&FrmImportarDiretorio.listaImportar, importar);
            nCodDirRaiz++;
        }
    }

	FrmImportarDiretorio.bSubDiretorio = bSubDiretorio;

    if (bSubDiretorio) {
		if (FrmImportarDiretorio_Criar(FrmPrincipal.frmPrincipal)) {
			FrmImportarDiretorio_Mostrar();
			FrmImportarDiretorio_iniciarImportacao(frmImportarDiretorio);
			EndDialog(FrmImportarDiretorio.frmImportarDiretorio, TRUE);
			DestroyWindow(FrmImportarDiretorio.frmImportarDiretorio);
		}
        return TRUE;
    } else {
        if (!DiretorioBO_verificaCodDir(importar.aba, importar.rotuloRaiz,
			Catalogador.listaDiretorioPai)) {
			if (FrmImportarDiretorio_Criar(FrmPrincipal.frmPrincipal)) {
				FrmImportarDiretorio_Mostrar();
				FrmImportarDiretorio_iniciarImportacao(frmImportarDiretorio);
				EndDialog(FrmImportarDiretorio.frmImportarDiretorio, TRUE);
				DestroyWindow(FrmImportarDiretorio.frmImportarDiretorio);
			}
			return TRUE;
        } else {
            Dialogo_mensagemErro(FrmFilho.frmFilho,
                    STR_FRMPRINCIPAL_DIRETORIOEXISTECATALOGO);

            return FALSE;
        }
    }

}

void Catalogador_FinalizaImportacao(IProgressoLog pLog) {
    Arvore tvAba;

	SetCursor(LoadCursor(NULL, IDC_WAIT));

	Catalogador_CarregarDados(pLog, TRUE, TRUE);
    tvAba = Catalogador_getArvoreAtual();
	Catalogador_CarregarArvore(tvAba, Catalogador_getAbaAtual());

	SetCursor(LoadCursor(NULL, IDC_ARROW));
    Dialogo_mensagemInfo(FrmFilho.frmFilho, STR_FRMPRINCIPAL_DIRIMPORTACAOSUCESSO);

}


void Catalogador_ComecaImportacao(BOOL bSubDiretorios, IProgressoLog pLog) {
    String sCaminho;
    ListaString listaCaminho = ListaString_inicia();

	String diretorio = EscolhaArquivo_abrirDiretorio(FrmFilho.frmFilho);
	if (diretorio.length > 0) {
		
		if (Rotinas_DirectoryExists(diretorio)) {
			SetCursor(LoadCursor(NULL, IDC_WAIT));
			sCaminho = diretorio;

            if (bSubDiretorios) {
                DiretorioBO_carregarSubDiretorios(sCaminho, listaCaminho);
            } else {                
				ListaString_insereFim(&listaCaminho, sCaminho);
            }

            if (Catalogador_ImportarDiretorios(listaCaminho, bSubDiretorios,
				FrmImportarDiretorio.frmImportarDiretorio)) {
				Catalogador_FinalizaImportacao(pLog);
            }

			SetCursor(LoadCursor(NULL, IDC_ARROW));
        }
    }

}
