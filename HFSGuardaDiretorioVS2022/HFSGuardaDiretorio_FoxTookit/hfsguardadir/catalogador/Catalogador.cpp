#include "resource.h"

#include "hfsguardadir\catalogador\Catalogador.h"
#include "FrmSplash.h"
#include "FrmInfoDiretorio.h"
#include "hfsguardadir/objetosbo/AbaBO.h"
#include "hfsguardadir/objetosbo/ExtensaoBO.h"
#include "hfsguardadir/objetosbo/DiretorioBO.h"
#include "hfsguardadir/objetosdao/VisaoDAO.h"
#include "hfsguardadir/objetosgui/Dialogo.h"
#include "hfsguardadir/objetosgui/EscolhaArquivo.h"
#include "hfsguardadir/objetos/Importar.h"

using namespace hfsguardadir::objetosbo;
using namespace hfsguardadir::objetosdao;
using namespace hfsguardadir::objetos;
using namespace hfsguardadir::catalogador;

hfsguardadir::catalogador::Catalogador *catalogador;

namespace hfsguardadir {

namespace catalogador {


Catalogador::Catalogador(FXApp* app, FrmPrincipal* form) {
	CONSULTA_DIR_PAI = 
		"select aba, cod, ordem, coddirpai, nome, tam, tipo, modificado, " \
		"atributos, caminho, nomeaba, nomepai, caminhopai " \
		"from consultadirpai " \
		"order by 1,2,3,4";
	CONSULTA_DIR_FILHO = 
		"select aba, cod, ordem, coddirpai, nome, tam, tipo, modificado, " \
		"atributos, caminho, nomeaba, nomepai, caminhopai " \
		"from consultadirfilho " \
		"order by 1,2,3,4";
	CONSULTA_ARQUIVO = 
		"select aba, cod, ordem, coddirpai, nome, tam, tipo, modificado, " \
		"atributos, caminho, nomeaba, nomepai, caminhopai " \
		"from consultaarquivo " \
		"order by tipo desc, ordem";

	bGravarLogImportacao = false;

	app->beginWaitCursor();

	mostrarOcultarListaItensPesquisados(form);

	FrmSplash::Mostrar(app);

	CarregarDados(FrmSplash::ProgressoLog, true, true);
	CarregarAbas(form);
	tabPanelMudou(form);

	FrmSplash::Fechar();

	app->endWaitCursor();

}

Catalogador::~Catalogador() {
}

void Catalogador::iniciarSistema() {
	Aba aba;
	std::string sBanco = Rotinas::AppDirName();
	sBanco += "GuardaDir.db";

	if (!Rotinas::FileExists(sBanco)) {
		Rotinas::getInstancia()->BancoConectar(sBanco);

		AbaBO::getInstancia()->criarTabelaAbas();

		aba.setCodigo(1);
		aba.setNome("DISCO1");
		aba.setOrdem(0);
		AbaBO::getInstancia()->incluirAba(aba);

		ExtensaoBO::getInstancia()->criarTabelaExtensoes();
		DiretorioBO::getInstancia()->criarTabelaDiretorios();
		VisaoDAO::getInstancia()->criarVisao("consultadirpai");
		VisaoDAO::getInstancia()->criarVisao("consultadirfilho");
		VisaoDAO::getInstancia()->criarVisao("consultaarquivo");
	}
	else
		Rotinas::getInstancia()->BancoConectar(sBanco);
}

void Catalogador::CarregarDados(IProgressoLog pLog, bool bExtensao, bool bDiretorio) {
	listaAbas = AbaBO::getInstancia()->carregarAba(pLog);
	if (bExtensao) {
		listaExtensoes = ExtensaoBO::getInstancia()->carregarExtensao(pLog);
	}
	if (bDiretorio) {
		listaDiretorioPai = DiretorioBO::getInstancia()->carregarDiretorio(
			CONSULTA_DIR_PAI, "", pLog);
		listaDiretorioFilho = DiretorioBO::getInstancia()->carregarDiretorio(
			CONSULTA_DIR_FILHO, "", pLog);
		listaArquivos = DiretorioBO::getInstancia()->carregarDiretorio(
			CONSULTA_ARQUIVO, "", pLog);
	}
}

void Catalogador::ExcluirDados(Aba aba, const std::string &sCaminho) {
	DiretorioBO::getInstancia()->excluirListaDiretorio(listaDiretorioPai, aba, sCaminho);
	DiretorioBO::getInstancia()->excluirListaDiretorio(listaDiretorioFilho, aba, sCaminho);
	DiretorioBO::getInstancia()->excluirListaDiretorio(listaArquivos, aba, sCaminho);
}

void Catalogador::AddItemArvore(FrmPrincipal* form, Arvore* arvore, Diretorio diretorio, int Nivel, FXTreeItem* node1) {
	std::vector<Diretorio> listaFilhos;
	FXTreeItem* node2;
	Diretorio filho;

	//ExtensaoBO::getInstancia()->DiretorioXPM;
	FXBMPIcon* iconeDiretorio = new FXBMPIcon(form->getApp(), Fechar);
	//ExtensaoBO::getInstancia()->DirAbertoXPM
	FXBMPIcon* iconeDirAberto = new FXBMPIcon(form->getApp(), Abrir);

	if (Nivel == 0) {
		node1 = new FXTreeItem(diretorio.getNome().c_str(), iconeDirAberto, iconeDiretorio);
		arvore->appendItem(NULL, node1);
	}

	listaFilhos = DiretorioBO::getInstancia()->itensFilhos(listaDiretorioFilho,
		diretorio.getAba().getCodigo(), diretorio.getOrdem(), diretorio.getCodigo());

	for (unsigned int i = 0; i < listaFilhos.size(); i++) {
		filho = listaFilhos.at(i);

		//ExtensaoBO::getInstancia()->DiretorioXPM;
		FXBMPIcon* iconeDiretorio = new FXBMPIcon(form->getApp(), Fechar);
		node2 = new FXTreeItem(filho.getNome().c_str(), iconeDirAberto, iconeDiretorio);
		arvore->appendItem(node1, node2);

		AddItemArvore(form, arvore, filho, ++Nivel, node2);
	}
}

void Catalogador::IncluirNovaAba() {
	Aba aba;

	std::string sAba = Dialogo::entrada(frmPrincipal,
		"FrmPrincipal.DigitaIncluirNovaAba");

	if (Rotinas::Trim(sAba).length() > 0) {
		aba.setCodigo(AbaBO::getInstancia()->retMaxCodAba(listaAbas));
		aba.setNome(Rotinas::SubString(sAba, 1, 10));
		aba.setOrdem((int)listaAbas.size() + 1);
		AbaBO::getInstancia()->incluirAba(aba);
		incluirNovaAba(frmPrincipal, aba.getNome());
		listaAbas.push_back(aba);
	}
}

void Catalogador::AlterarNomeAbaAtiva(IProgressoLog pLog) {
	Aba aba = getAbaAtual();
	std::string sAba = Dialogo::entrada2(frmPrincipal,
		"FrmPrincipal.DigitaAlterarNomeAba", aba.getNome());
	if (Rotinas::Trim(sAba).length() > 0) {
		aba.setNome(Rotinas::SubString(sAba, 1, 10));
		AbaBO::getInstancia()->alterarAba(aba);

		int pagina = frmPrincipal->barraTab->getCurrent();
		//FXWindow* tabPage = frmPrincipal->barraTab->childAtIndex(pagina);
		FXTabItem* tabAba = static_cast<FXTabItem*>(frmPrincipal->barraTab->childAtIndex(pagina));
		tabAba->setText(sAba.c_str());

		CarregarDados(pLog, false, true);
	}
}

void Catalogador::ExcluirAbaAtiva(IProgressoLog pLog) {
	Aba aba;
	int pagina = frmPrincipal->barraTab->getCurrent();
	if (pagina > 0) {
		bool res = Dialogo::confirma(frmPrincipal,
			"FrmPrincipal.ConfirmaExcluirAba");
		if (res) {
			frmPrincipal->getApp()->beginWaitCursor();

			aba = getAbaAtual();
			ExcluirDados(aba, "");
			AbaBO::getInstancia()->excluirAba(aba);
			//frmPrincipal->barraTab->remove_page(pagina);

			CarregarDados(pLog, false, false);
			frmPrincipal->barraStatus->getStatusLine()->setNormalText("");

			frmPrincipal->getApp()->endWaitCursor();
		}
	}
	else
		Dialogo::mensagemErro(frmPrincipal,
			"FrmPrincipal.ValidaExcluirAba");
}

void Catalogador::incluirNovaAba(FrmPrincipal* form, const std::string &nomeAba) {
	
	FXSplitter* spLocal = new FXSplitter(form->framePrincipal, LAYOUT_FILL_X | LAYOUT_FILL_Y);
	

	Arvore* arvore = new Arvore(spLocal, form, form->ID_ARVORE_FIXA,
		TREELIST_SINGLESELECT | TREELIST_ROOT_BOXES | TREELIST_SHOWS_BOXES | TREELIST_SHOWS_LINES);

	Tabela* tabela = new Tabela(spLocal, form, form->ID_TABELA_FIXA,
		TABLE_COL_SIZABLE | TABLE_READONLY, true);
	tabela->setEditable(false);
	tabela->setDefRowHeight(20);
	
	form->listaFrames->append(spLocal);
	spLocal->setSplit(0, 300);

	form->adicionaTabPage(form->barraTab, nomeAba.c_str());
}

Arvore* Catalogador::getArvoreAtualIndice(FrmPrincipal* form, int nIndicePagina) {
	FXSplitter* spLocal = form->listaFrames->at(nIndicePagina);
	FXWindow* child = spLocal->childAtIndex(0);
	Arvore* arvore = static_cast<Arvore*>(child);
	return arvore;
}

Arvore* Catalogador::getArvoreAtual(FrmPrincipal* form) {
	int pagina = form->barraTab->getCurrent();
	return getArvoreAtualIndice(form, pagina);
}

FXSplitter* Catalogador::getSplitAtual(FrmPrincipal* form) {
	int pagina = form->barraTab->getCurrent();
	FXSplitter* spLocal = form->listaFrames->at(pagina);
	return spLocal;
}

Tabela* Catalogador::getTabelaAtual(FrmPrincipal* form) {
	int pagina = form->barraTab->getCurrent();
	FXSplitter* spLocal = form->listaFrames->at(pagina);
	FXWindow* child = spLocal->childAtIndex(1);
	Tabela* tabela = static_cast<Tabela*>(child);
	return tabela;
}

void Catalogador::mostrarOcultarArvore() {
	FXSplitter* splitterTab = getSplitAtual(frmPrincipal);
	
	bool bVisivel = splitterTab->getSplit(0) == 300;
	if (bVisivel) {
		splitterTab->setSplit(0, 0);
	}
	else {
		splitterTab->setSplit(0, 300);
	}
}

void Catalogador::mostrarOcultarListaItensPesquisados(FrmPrincipal* form) {	
	bool bNotVisivel = form->spPesquisa->getSplit(0) == form->getHeight();
	if (bNotVisivel) {
		form->spPesquisa->setSplit(0, 450);
	}
	else {
		form->spPesquisa->setSplit(0, form->getHeight());
	}
}

void Catalogador::CarregarArvore(FrmPrincipal* form, Arvore* arvore, Aba aba) {
	Diretorio dir;

	arvore->limpar();
	for (unsigned int i = 0; i < listaDiretorioPai.size(); i++) {
		dir = listaDiretorioPai.at(i);

		if (dir.getAba().getCodigo() == aba.getCodigo()) {
			AddItemArvore(form, arvore, dir, 0, NULL);
		}
	}
}

void Catalogador::CarregarAbas(FrmPrincipal* form) {
	Arvore* tvAba;
	Aba aba;

	int nMaximum = (int)listaAbas.size() - 1;
	form->pb->setProgress(0);

	for (int i = 0; i < (nMaximum + 1); i++) {
		aba = listaAbas.at(i);

		if (i > 0) {
			incluirNovaAba(form, aba.getNome());
		}
		tvAba = getArvoreAtualIndice(form, i);
		CarregarArvore(form, tvAba, aba);

		form->pb->setProgress(
			Rotinas::calculaProgresso(nMaximum, i));
	}
}

Aba Catalogador::getAbaAtual() {
	int pagina = frmPrincipal->barraTab->getCurrent();
	return *AbaBO::getInstancia()->pegaAbaPorOrdem(
		listaAbas, pagina + 1);
}

void Catalogador::CarregarArquivosLista(bool bLista1, Tabela* tabela, const std::string &sCaminho) {
	std::string sPaiCaminho = "";
	std::vector<Diretorio> listaLocal;
	int nAba;
	Diretorio dir;
	std::string scaminho = sCaminho;

	tabela->limpar();

	if (bLista1) {
		sPaiCaminho = scaminho;
		if (Rotinas::SubString(scaminho, scaminho.length(), 1) != Rotinas::BARRA_INVERTIDA) {
			scaminho += Rotinas::BARRA_INVERTIDA;
		}
		nAba = getAbaAtual().getCodigo();

		for (unsigned int i = 0; i < listaArquivos.size(); i++) {
			dir = listaArquivos.at(i);

			if (dir.getAba().getCodigo() == nAba) {
				if (dir.getCaminhoPai() == sPaiCaminho) {
					if (Rotinas::StartsStr(scaminho, dir.getCaminho())) {
						listaLocal.push_back(dir);
					}
				}
			}
		}
	}
	else {
		for (unsigned int i = 0; i < listaArquivos.size(); i++) {
			dir = listaArquivos.at(i);

			if (Rotinas::ContainsStr(Rotinas::UpperCase(dir.getCaminho()),
				Rotinas::UpperCase(scaminho))) {
				listaLocal.push_back(dir);
			}
		}
	}
	tabela->carregar(listaLocal, listaExtensoes, frmPrincipal->pb);
}

void Catalogador::TamTotalDiretorio(const std::string &sCaminho) {
	long conta;
	int nAba;
	unsigned long long soma;
	Diretorio dir;
	std::string status = "";

	conta = 0;
	soma = 0;

	for (unsigned int i = 0; i < listaArquivos.size(); i++) {
		dir = listaArquivos.at(i);

		nAba = getAbaAtual().getCodigo();
		if (dir.getAba().getCodigo() == nAba) {
			if (dir.getTipo().getCodigo() != 'D') {
				if (Rotinas::Trim(sCaminho).length() > 0) {
					if (Rotinas::StartsStr(sCaminho, dir.getCaminho())) {
						conta++;
						soma += dir.getTamanho();
					}
				}
				else {
					conta++;
					soma += dir.getTamanho();
				}
			}
		}
	}

	status = "Quantidade Total: " + Rotinas::ULongToStr(conta);
	status += ", Tamanho Total: " + Rotinas::MontaTamanho(soma);
	frmPrincipal->labStatus->setText(status.c_str());
}

std::vector<std::string> Catalogador::montaCaminho(const std::string &sCaminho, bool bRemover) {
	//sCaminho = NO_RAIZ + Rotinas.BARRA_INVERTIDA + sCaminho;
	std::vector<std::string> sl = Rotinas::SListSeparador(sCaminho, Rotinas::BARRA_INVERTIDA[0]);
	size_t tam = sl.size();
	std::string item = sl.at(tam - 1);

	if (Rotinas::Trim(item).length() == 0) {
		sl.erase(sl.begin() + (tam - 1));
	}
	if (bRemover) {
		sl.erase(sl.begin() + (tam - 1));
	}
	return sl;
}

std::vector<std::string> Catalogador::montaCaminhoStatus(Arvore* arvore, FXTreeItem* iter) {
	std::vector<std::string> lista;
	std::string texto;
	FXTreeItem* linha;

	do {
		linha = iter;
		texto = linha->getText().text();

		if (texto.length() > 0) {
			lista.push_back(texto);

			iter = linha->getParent();
		}
		else {
			break;
		}
		
	} while (iter!=nullptr); //(arvore->isItemEnabled(iter));

	std::reverse(lista.begin(), lista.end());
	
	return lista;
}

void Catalogador::Pesquisar() {
	Arvore* arvore = getArvoreAtual(frmPrincipal);

	if (arvore->getNumItems() > 0) {

		std::string texto = frmPrincipal->edtPesquisa->getText().text();
		FXSplitter* scrollTabelaPesquisa = getSplitAtual(frmPrincipal);

		if (texto.length() >= 2) {
			scrollTabelaPesquisa->show();
			CarregarArquivosLista(false, frmPrincipal->tabelaPesquisa, texto);
			arvore->selecionarPrimeiroItem();
		}
		else {
			scrollTabelaPesquisa->hide();
			frmPrincipal->tabelaPesquisa->limpar();
			Dialogo::mensagemInfo(frmPrincipal, "FrmPrincipal.TamMaxPesquisa");
		}
	}
}

void Catalogador::PesquisarArvoreDiretorio(const std::string &sCaminho, Aba aba) {
	frmPrincipal->barraTab->setCurrent(aba.getOrdem() - 1);

	Arvore* arvore = getArvoreAtual(frmPrincipal);

	std::vector<std::string> sl = montaCaminho(sCaminho, false);
	FXTreeItem* path = arvore->encontrarCaminhoPorNome(sl);

	if (!path->isEnabled()) {
		arvore->expandTree(path);

		arvore->selectItem(path);
		//arvore->scroll();
		//arvore->scroll_to_cell(path, arvore->coluna, 0, 0);
	}
}

void Catalogador::LerArvoreDiretorio(Arvore* arvore, 
	FXTreeItem* iter, FXLabel* barraStatus) {
	std::string texto = "";
	std::string caminho = "";
	std::vector<std::string> lista = montaCaminhoStatus(arvore, iter);

	for (unsigned int i = 0; i < lista.size(); i++) {
		texto = lista.at(i);

		caminho += texto + Rotinas::BARRA_INVERTIDA;
	}

	if (lista.size() > 0) {
		caminho = Rotinas::SubString(caminho, 1, caminho.length() - 1);
		barraStatus->setText(caminho.c_str());
	}
}

void Catalogador::ListarArquivos(Tabela* tabela, Arvore* arvore, FXTreeItem* iter) {
	std::string texto;

	iter = arvore->getCurrentItem();
	if (iter) {
		LerArvoreDiretorio(arvore, iter, frmPrincipal->labStatus);

		texto = frmPrincipal->labStatus->getText().text();

		CarregarArquivosLista(true, tabela, texto);
		TamTotalDiretorio(texto);
	}
}

void Catalogador::tabPanelMudou(FrmPrincipal* form) {
	Arvore* arvore = getArvoreAtual(form);
	Tabela* tabela = getTabelaAtual(form);
	FXTreeItem* item;
		
	if (arvore->getNumItems() > 0) {

		item = arvore->getFirstItem();		
		if (arvore->isItemSelected(item)) {
			ListarArquivos(tabela, arvore, item);
		}
	}

	for (FXival i = 0; i < form->listaFrames->no(); i++) {
		form->listaFrames->at(i)->hide();
	}
	form->listaFrames->at(form->barraTab->getCurrent())->show();
}

void Catalogador::DuploCliqueLista(const std::string &nome, const std::string &tipo) {
	if (tipo == Rotinas::getRecurso("TipoLista.diretorio")) {
		frmPrincipal->getApp()->beginWaitCursor();

		std::string sCaminho = frmPrincipal->labStatus->getText().text();

		if (Rotinas::testaSeparadorArquivo(sCaminho)) {
			sCaminho += nome;
		}
		else {
			sCaminho += Rotinas::BARRA_INVERTIDA + nome;
		}

		PesquisarArvoreDiretorio(sCaminho, getAbaAtual());

		frmPrincipal->getApp()->endWaitCursor();
	}
}

void Catalogador::EncontrarItemLista(const std::string &nomeAba, const std::string &nome,
	const std::string &caminho) {
	frmPrincipal->getApp()->beginWaitCursor();

	Aba aba = *AbaBO::getInstancia()->pegaAbaPorNome(listaAbas, nomeAba);
	PesquisarArvoreDiretorio(caminho, aba);

	Tabela* tabela = getTabelaAtual(frmPrincipal);
	unsigned int row = tabela->encontrarCaminhoPorNome(nome);

	if (row > 0) {
		tabela->selectRow(row);
		//tabela->scroll();
		//tabela->scroll_to_cell(path, *tabela->colunaNome, 0, 0);
	}

	frmPrincipal->getApp()->endWaitCursor();
}

int Catalogador::verificaNomeDiretorio(const std::string &sCaminho, RotuloRaiz *sRotuloRaiz) {
	sRotuloRaiz->setRotulo(DiretorioBO::getInstancia()->removerDrive(sCaminho));

	if (sRotuloRaiz->getRotulo().length() == 0) {

		sRotuloRaiz->setRotulo(Dialogo::entrada(frmPrincipal,
			"FrmPrincipal.DigitaNomeDiretorio"));

		if ((sRotuloRaiz->getRotulo().c_str()!=nullptr)
			&& (Rotinas::Trim(sRotuloRaiz->getRotulo()).length() > 0)) {
			sRotuloRaiz->getRotulo() = Rotinas::Trim(sRotuloRaiz->getRotulo());

			if (sRotuloRaiz->getRotulo().length() > 0) {
				return 1;
			}
			else {
				Dialogo::mensagemInfo(frmPrincipal,
					"FrmPrincipal.ValidaNomeDiretorio");
				return 0;
			}
		}
		else {
			return 0;
		}
	}
	else if (Rotinas::Pos(Rotinas::BARRA_INVERTIDA,
		sRotuloRaiz->getRotulo()) > 0) {
		sRotuloRaiz->setRotulo(Rotinas::SubString(sRotuloRaiz->getRotulo(),
			Rotinas::LastDelimiter(Rotinas::BARRA_INVERTIDA,
				sRotuloRaiz->getRotulo()) + 1,
			sRotuloRaiz->getRotulo().length()));
		return 2;
	}
	else {
		return 3;
	}
}

void Catalogador::ExportarArquivo(TipoExportar tipo, IProgressoLog pLog) {
	std::string sExtensao = "";

	switch (tipo) {
	case teTXT:
		sExtensao = "txt";
		break;
	case teCSV:
		sExtensao = "csv";
		break;
	case teHTML:
		sExtensao = "html";
		break;
	case teXML:
		sExtensao = "xml";
		break;
	case teSQL:
		sExtensao = "sql";
		break;
	}

	Aba aba = getAbaAtual();
	std::string sDiretorio = Rotinas::AppDirPath();
	std::string sArquivo = aba.getNome() + "." + sExtensao;
	std::string arquivo = EscolhaArquivo::salvarArquivo2(frmPrincipal,
		EscolhaArquivo::FILTRO_EXPORTAR, sDiretorio, sArquivo);
	if (arquivo.length() > 0) {
		//GFileInfo* info = Rotinas::getFileInfo(arquivo);				
		if (!Rotinas::FileExists(arquivo)) {
			frmPrincipal->getApp()->beginWaitCursor();

			DiretorioBO::getInstancia()->exportarDiretorio(tipo, aba, arquivo, pLog);

			frmPrincipal->getApp()->endWaitCursor();

			Dialogo::mensagemErro(frmPrincipal, "FrmPrincipal.SucessoExportar");
		}
	}
}

void Catalogador::ExcluirDiretorioSelecionado(IProgressoLog pLog) {
	Arvore* arvore = getArvoreAtual(frmPrincipal);
	FXTreeItem* iter;

	iter = arvore->getCurrentItem();
	if (iter)
	{
		Tabela* tabela = getTabelaAtual(frmPrincipal);

		bool res = Dialogo::confirma(frmPrincipal, "FrmPrincipal.ExcluirDiretorioSelecionado");
		if (res) {
			frmPrincipal->getApp()->beginWaitCursor();

			std::vector<std::string> sl = montaCaminhoStatus(arvore, iter);
			std::string caminho = Rotinas::SListTexto(sl);

			Aba aba = getAbaAtual();

			DiretorioBO::getInstancia()->excluirDiretorio(aba, caminho);
			ExcluirDados(aba, caminho);

			arvore->removeItem(iter);
			tabela->limpar();

			CarregarDados(pLog, false, false);

			frmPrincipal->getApp()->endWaitCursor();
		}
	}
}

void Catalogador::ImportarArquivo(FrmPrincipal* form, std::vector<std::string> log, IProgressoLog pLog) {
	int nResultado;

	std::string arquivo = EscolhaArquivo::abrirArquivo(frmPrincipal, EscolhaArquivo::FILTRO_XML);
	//FileInfo arquivo = new FileInfo(EscolhaArquivo.NomeArquivo);

	if (Rotinas::FileExists(arquivo)) {
		form->getApp()->beginWaitCursor();

		nResultado = DiretorioBO::getInstancia()->importarDiretorioViaXML(
			getAbaAtual(), arquivo, listaDiretorioPai, pLog);
		if (nResultado == -1) {
			Dialogo::mensagemErro(form, "FrmPrincipal.ImportacaoNaoRealizada");
		}
		else if (nResultado == -2) {
			Dialogo::mensagemErro(form, "FrmPrincipal.DiretorioExisteCatalogo");
		}
		else {
			FinalizaImportacao(form, pLog);
		}
		form->getApp()->endWaitCursor();
	}
}

bool Catalogador::ImportarDiretorios(std::vector<std::string> listaCaminho,
	bool bSubDiretorio, FrmImportarDiretorio* frmImportarDiretorio) {

	int nAba, nRotuloRaiz, nCodDirRaiz;
	RotuloRaiz *sRotuloRaiz = new RotuloRaiz();
	std::string sCaminhoSemDrive, sCaminho = "";
	Importar importar;

	nAba = getAbaAtual().getCodigo();
	nCodDirRaiz = DiretorioBO::getInstancia()->retMaxCodDir(nAba,
		listaDiretorioPai);

	for (unsigned int i = 0; i < listaCaminho.size(); i++) {
		sCaminho = listaCaminho.at(i);

		nRotuloRaiz = verificaNomeDiretorio(sCaminho, sRotuloRaiz);
		if (nRotuloRaiz > 0) {
			importar.setAba(nAba);
			importar.setCodDirRaiz(nCodDirRaiz);
			importar.setRotuloRaiz(sRotuloRaiz->getRotulo());
			if (nRotuloRaiz == 1) {
				importar.setNomeDirRaiz(sRotuloRaiz->getRotulo());
			}
			else if (nRotuloRaiz == 2) {
				sCaminhoSemDrive = DiretorioBO::getInstancia()->removerDrive(sCaminho);
				importar.setNomeDirRaiz(Rotinas::SubString(
					sCaminhoSemDrive, 1,
					Rotinas::LastDelimiter(Rotinas::BARRA_INVERTIDA,
						sCaminhoSemDrive) - 1));
			}
			else if (nRotuloRaiz == 3) {
				importar.setNomeDirRaiz("");
			}
			importar.setCaminho(sCaminho);

			frmImportarDiretorio->listaImportar.push_back(importar);
			nCodDirRaiz++;
		}
	}

	frmImportarDiretorio->bSubDiretorio = bSubDiretorio;

	if (bSubDiretorio) {
		FrmImportarDiretorio::Mostrar();
		frmImportarDiretorio->ImportarDir();
		FrmImportarDiretorio::Fechar();
		return true;
	}
	else {
		if (!DiretorioBO::getInstancia()->verificaCodDir(
			importar.getAba(), importar.getRotuloRaiz(),
			listaDiretorioPai)) {
			FrmImportarDiretorio::Mostrar();
			frmImportarDiretorio->ImportarDir();
			FrmImportarDiretorio::Fechar();
			return true;
		}
		else {
			Dialogo::mensagemErro(frmPrincipal,
				"FrmPrincipal.DiretorioExisteCatalogo");

			return false;
		}
	}
}

void Catalogador::FinalizaImportacao(FrmPrincipal* form, IProgressoLog pLog) {
	Arvore* tvAba;

	form->getApp()->beginWaitCursor();

	CarregarDados(pLog, true, true);
	tvAba = getArvoreAtual(form);
	CarregarArvore(form, tvAba, getAbaAtual());
	tabPanelMudou(form);

	form->getApp()->endWaitCursor();
	Dialogo::mensagemInfo(frmPrincipal, "FrmPrincipal.DirImportacaoSucesso");
}

void Catalogador::ComecaImportacao(FrmPrincipal* form, bool bSubDiretorios, IProgressoLog pLog) {
	std::string sCaminho = "";
	std::vector<std::string> listaCaminho;

	sCaminho = EscolhaArquivo::abrirDiretorio(form);
	if (sCaminho.length() > 0) {
		if (Rotinas::DirectoryExists(sCaminho)) {
			form->getApp()->beginWaitCursor();

			frmImportarDiretorio = new FrmImportarDiretorio(form);

			if (bSubDiretorios) {
				DiretorioBO::getInstancia()->carregarSubDiretorios(sCaminho, listaCaminho);
			}
			else {
				listaCaminho.push_back(sCaminho);
			}

			if (ImportarDiretorios(listaCaminho, bSubDiretorios, frmImportarDiretorio)) {
				FinalizaImportacao(form, pLog);
			}

			form->getApp()->endWaitCursor();
		}
	}
}

void Catalogador::InformacoesDiretorioArquivo() {
	Tabela* tabela = getTabelaAtual(frmPrincipal);

	int row = tabela->getCurrentRow();

	if (tabela->isRowSelected(row)) {
		Aba aba = getAbaAtual();
		Diretorio dir = tabela->getLinhaSelecionada();
		dir.setAba(aba);
		frmInfoDiretorio = new FrmInfoDiretorio(frmPrincipal);
		frmInfoDiretorio->setDiretorio(dir);
		FrmInfoDiretorio::Mostrar(frmPrincipal);
	}
}

}
}
