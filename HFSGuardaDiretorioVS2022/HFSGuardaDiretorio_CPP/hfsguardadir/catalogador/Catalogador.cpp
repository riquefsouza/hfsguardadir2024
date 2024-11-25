#include "hfsguardadir/catalogador/Catalogador.h"
//#include "FrmSplash.h"
//#include "FrmInfoDiretorio.h"
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


Catalogador::Catalogador() {
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
/*
	frmPrincipal->get_window()->set_cursor(Gdk::Cursor(Gdk::WATCH));

	mostrarOcultarListaItensPesquisados();

	FrmSplash::Mostrar();

	CarregarDados(FrmSplash::ProgressoLog, true, true);
	CarregarAbas();
	tabPanelMudou();

	FrmSplash::Fechar();

	frmPrincipal->get_window()->set_cursor(Gdk::Cursor(Gdk::ARROW));
*/
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
/*
void Catalogador::AddItemArvore(Arvore &arvore, Diretorio diretorio, int Nivel, Gtk::TreeRow node1) {
	std::vector<Diretorio> listaFilhos;
	Gtk::TreeRow node2;
	Diretorio filho;

	if (Nivel == 0) {
		node1 = *(arvore.getStore()->append());
		node1[arvore.modeloArvore.coluna0] = ExtensaoBO::getInstancia()->DiretorioXPM;
		node1[arvore.modeloArvore.coluna1] = diretorio.getNome();
	}

	listaFilhos = DiretorioBO::getInstancia()->itensFilhos(listaDiretorioFilho,
		diretorio.getAba().getCodigo(), diretorio.getOrdem(), diretorio.getCodigo());

	for (unsigned int i = 0; i < listaFilhos.size(); i++) {
		filho = listaFilhos.at(i);

		node2 = *(arvore.getStore()->append(node1.children()));
		node2[arvore.modeloArvore.coluna0] = ExtensaoBO::getInstancia()->DiretorioXPM;
		node2[arvore.modeloArvore.coluna1] = filho.getNome();

		AddItemArvore(arvore, filho, ++Nivel, node2);
	}
}

void Catalogador::IncluirNovaAba() {
	Aba aba;

	std::string sAba = Dialogo::entrada(frmPrincipal,
		"FrmPrincipal.DigitaIncluirNovaAba");

	if (Rotinas::Trim(sAba).length() > 0) {
		aba.setCodigo(AbaBO::getInstancia()->retMaxCodAba(listaAbas));
		aba.setNome(Rotinas::SubString(sAba, 1, 10));
		aba.setOrdem(listaAbas.size() + 1);
		AbaBO::getInstancia()->incluirAba(aba);
		incluirNovaAba(aba.getNome());
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

		gint pagina = frmPrincipal->notebook1->get_current_page();
		Gtk::Widget* tabPage = frmPrincipal->notebook1->get_nth_page(pagina);
		Gtk::HBox* tabAba = static_cast<Gtk::HBox*>(frmPrincipal->notebook1->get_tab_label(*tabPage));

		Glib::ListHandle<Gtk::Widget*> hlista = tabAba->get_children();
		std::vector<Gtk::Widget*, std::allocator<Gtk::Widget*>> lista =
			hlista.operator std::vector<Gtk::Widget*, std::allocator<Gtk::Widget*>>();
		Gtk::Label* labAba = static_cast<Gtk::Label*>(lista.at(1));

		labAba->set_label(sAba);

		CarregarDados(pLog, false, true);
	}
}

void Catalogador::ExcluirAbaAtiva(IProgressoLog pLog) {
	Aba aba;
	gint pagina = frmPrincipal->notebook1->get_current_page();
	if (pagina > 0) {
		bool res = Dialogo::confirma(frmPrincipal,
			"FrmPrincipal.ConfirmaExcluirAba");
		if (res) {
			frmPrincipal->get_window()->set_cursor(Gdk::Cursor(Gdk::WATCH));

			aba = getAbaAtual();
			ExcluirDados(aba, "");
			AbaBO::getInstancia()->excluirAba(aba);
			frmPrincipal->notebook1->remove_page(pagina);

			CarregarDados(pLog, false, false);
		 	frmPrincipal->getLabStatus2()->set_text("");

			frmPrincipal->get_window()->set_cursor(Gdk::Cursor(Gdk::ARROW));
		}
	}
	else
		Dialogo::mensagemErro(frmPrincipal,
			"FrmPrincipal.ValidaExcluirAba");
}

void Catalogador::incluirNovaAba(const std::string &nomeAba) {
	Gtk::HPaned *spPanel;
	Arvore *arvore;
	Tabela *tabela;
	Gtk::ScrolledWindow *scrollArvore;
	Gtk::ScrolledWindow *scrollTabela;

	tabela = manage(new class Tabela(true));
	tabela->set_name("tabela_" + nomeAba);
	tabela->set_visible(true);
	tabela->set_can_focus(true);

	scrollTabela = manage(new class Gtk::ScrolledWindow());
	scrollTabela->set_name("scrollTabela_" + nomeAba);
	scrollTabela->set_visible(true);
	scrollTabela->set_can_focus(true);
	scrollTabela->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	scrollTabela->set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
	scrollTabela->add(*tabela);

	arvore = manage(new class Arvore());
	arvore->set_name("arvore_" + nomeAba);
	arvore->set_visible(true);
	arvore->set_can_focus(true);

	scrollArvore = manage(new class Gtk::ScrolledWindow());
	scrollArvore->set_name("scrollArvore_" + nomeAba);
	scrollArvore->set_visible(true);
	scrollArvore->set_can_focus(true);
	scrollArvore->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	scrollArvore->set_shadow_type(Gtk::SHADOW_IN);
	scrollArvore->add(*arvore);

	spPanel = manage(new class Gtk::HPaned());
	spPanel->set_name("spPanel_" + nomeAba);
	spPanel->set_visible(true);
	spPanel->set_can_focus(true);
	spPanel->set_position(250);
	spPanel->add(*scrollArvore);
	spPanel->add(*scrollTabela);

	arvore->get_selection()->signal_changed().connect(sigc::mem_fun(frmPrincipal, &FrmPrincipal::on_arvoreFixa_selection_changed));
	arvore->signal_row_collapsed().connect(sigc::mem_fun(frmPrincipal, &FrmPrincipal::on_arvoreFixa_row_collapsed));
	arvore->signal_button_release_event().connect(sigc::mem_fun(frmPrincipal, &FrmPrincipal::on_arvoreFixa_button_release_event));
	arvore->signal_button_press_event().connect(sigc::mem_fun(frmPrincipal, &FrmPrincipal::on_arvoreFixa_button_press_event));
	arvore->signal_row_expanded().connect(sigc::mem_fun(frmPrincipal, &FrmPrincipal::on_arvoreFixa_row_expanded));

	tabela->signal_button_release_event().connect(sigc::mem_fun(frmPrincipal, &FrmPrincipal::on_tabelaFixa_button_release_event));
	tabela->signal_row_activated().connect(sigc::mem_fun(frmPrincipal, &FrmPrincipal::on_tabelaFixa_row_activated));

	frmPrincipal->adicionaTabPage(frmPrincipal->notebook1, spPanel, nomeAba);
}

Arvore* Catalogador::getArvoreAtualIndice(int nIndicePagina) {
	Gtk::HPaned* tabPage = static_cast<Gtk::HPaned*>(frmPrincipal->notebook1->get_nth_page(nIndicePagina));
	Gtk::ScrolledWindow* scrollArvore = static_cast<Gtk::ScrolledWindow*>(tabPage->get_child1());

	Glib::ListHandle<Gtk::Widget*> hlista = scrollArvore->get_children();
	std::vector<Gtk::Widget*, std::allocator<Gtk::Widget*>> lista =
		hlista.operator std::vector<Gtk::Widget*, std::allocator<Gtk::Widget*>>();
	Arvore* arvore = static_cast<Arvore*>(lista.at(0));

	return arvore;
}

Arvore* Catalogador::getArvoreAtual() {
	gint pagina = frmPrincipal->notebook1->get_current_page();
	return getArvoreAtualIndice(pagina);
}

Gtk::HPaned* Catalogador::getSplitAtual() {
	gint pagina = frmPrincipal->notebook1->get_current_page();
	Gtk::HPaned* tabPage = static_cast<Gtk::HPaned*>(frmPrincipal->notebook1->get_nth_page(pagina));
	return tabPage;
}

Tabela* Catalogador::getTabelaAtual() {
	gint pagina = frmPrincipal->notebook1->get_current_page();
	Gtk::HPaned* tabPage = static_cast<Gtk::HPaned*>(frmPrincipal->notebook1->get_nth_page(pagina));
	Gtk::ScrolledWindow* scrollTabela = static_cast<Gtk::ScrolledWindow*>(tabPage->get_child2());
	
	Glib::ListHandle<Gtk::Widget*> hlista = scrollTabela->get_children();
	std::vector<Gtk::Widget*, std::allocator<Gtk::Widget*>> lista =
		hlista.operator std::vector<Gtk::Widget*, std::allocator<Gtk::Widget*>>();
	Tabela* tabela = static_cast<Tabela*>(lista.at(0));

	return tabela;
}

void Catalogador::mostrarOcultarArvore() {
	Gtk::HPaned* tabPage = getSplitAtual();
	Gtk::ScrolledWindow* scrollArvore = static_cast<Gtk::ScrolledWindow*>(tabPage->get_child1());

	bool bVisivel = scrollArvore->get_visible();
	scrollArvore->set_visible(!bVisivel);
}

void Catalogador::mostrarOcultarListaItensPesquisados() {
	Gtk::ScrolledWindow* scrollTabela = static_cast<Gtk::ScrolledWindow*>(
		frmPrincipal->spPesquisa->get_child2());

	bool bVisivel = scrollTabela->get_visible();
	scrollTabela->set_visible(!bVisivel);
}

void Catalogador::CarregarArvore(Arvore* arvore, Aba aba) {
	Diretorio dir;
	Gtk::TreeRow nodeRaiz;

	arvore->limpar();

	for (unsigned int i = 0; i < listaDiretorioPai.size(); i++) {
		dir = listaDiretorioPai.at(i);

		if (dir.getAba().getCodigo() == aba.getCodigo()) {
			AddItemArvore(*arvore, dir, 0, nodeRaiz);
		}
	}
}

void Catalogador::CarregarAbas() {
	Arvore* tvAba;
	Aba aba;

	int nMaximum = listaAbas.size() - 1;
	frmPrincipal->pb->set_fraction(0);

	for (int i = 0; i < (nMaximum + 1); i++) {
		aba = listaAbas.at(i);

		if (i > 0) {
			incluirNovaAba(aba.getNome());
		}
		tvAba = getArvoreAtualIndice(i);
		CarregarArvore(tvAba, aba);

		frmPrincipal->pb->set_fraction(
			Rotinas::calculaProgresso(nMaximum, i));
	}
}

Aba Catalogador::getAbaAtual() {
	gint pagina = frmPrincipal->notebook1->get_current_page();
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
	frmPrincipal->getLabStatus1()->set_text(status);
}

std::vector<std::string> Catalogador::montaCaminho(const std::string &sCaminho, bool bRemover) {
	//sCaminho = NO_RAIZ + Rotinas.BARRA_INVERTIDA + sCaminho;
	std::vector<std::string> sl = Rotinas::SListSeparador(sCaminho, Rotinas::BARRA_INVERTIDA[0]);
	guint tam = sl.size();
	std::string item = sl.at(tam - 1);

	if (Rotinas::Trim(item).length() == 0) {
		sl.erase(sl.begin() + (tam - 1));
	}
	if (bRemover) {
		sl.erase(sl.begin() + (tam - 1));
	}
	return sl;
}

std::vector<std::string> Catalogador::montaCaminhoStatus(Arvore* arvore, Gtk::TreeIter iter) {
	std::vector<std::string> lista;
	std::string texto;
	Gtk::TreeRow linha;

	do {
		linha = *iter;
		texto = linha[arvore->modeloArvore.coluna1];

		if (texto.length() > 0) {
			lista.push_back(texto);

			iter = linha.parent();
		}
		else {
			break;
		}
	} while (arvore->getStore()->iter_is_valid(iter));

	std::reverse(lista.begin(), lista.end());
	
	return lista;
}

void Catalogador::Pesquisar() {
	Arvore* arvore = getArvoreAtual();

	if (arvore->getStore()->children().size() > 0) {

		std::string texto = frmPrincipal->edtPesquisa->get_text();
		Gtk::ScrolledWindow* scrollTabelaPesquisa = static_cast<Gtk::ScrolledWindow*>
			(frmPrincipal->spPesquisa->get_child2());

		if (texto.length() >= 2) {
			scrollTabelaPesquisa->set_visible(true);
			CarregarArquivosLista(false, frmPrincipal->tabelaPesquisa, texto);
			arvore->selecionarPrimeiroItem();
		}
		else {
			scrollTabelaPesquisa->set_visible(false);
			frmPrincipal->tabelaPesquisa->limpar();
			Dialogo::mensagemInfo(frmPrincipal, "FrmPrincipal.TamMaxPesquisa");
		}
	}
}

void Catalogador::PesquisarArvoreDiretorio(const std::string &sCaminho, Aba aba) {
	frmPrincipal->notebook1->set_current_page(aba.getOrdem() - 1);

	Arvore* arvore = getArvoreAtual();

	std::vector<std::string> sl = montaCaminho(sCaminho, false);
	Gtk::TreePath path = arvore->encontrarCaminhoPorNome(sl);

	if (!path.empty()) {
		arvore->expand_to_path(path);

		arvore->get_selection()->select(path);
		arvore->scroll_to_cell(path, arvore->coluna, 0, 0);
	}
}

void Catalogador::LerArvoreDiretorio(Arvore* arvore, 
	Gtk::TreeIter iter,	Gtk::Label* barraStatus) {
	std::string texto = "";
	std::string caminho = "";
	std::vector<std::string> lista = montaCaminhoStatus(arvore, iter);

	for (unsigned int i = 0; i < lista.size(); i++) {
		texto = lista.at(i);

		caminho += texto + Rotinas::BARRA_INVERTIDA;
	}

	if (lista.size() > 0) {
		caminho = Rotinas::SubString(caminho, 1, caminho.length() - 1);
		barraStatus->set_text(caminho);
	}
}

void Catalogador::ListarArquivos(Tabela* tabela, Arvore* arvore, Gtk::TreeIter iter) {
	std::string texto;

	iter = arvore->get_selection()->get_selected();
	if (iter) {
		LerArvoreDiretorio(arvore, iter, frmPrincipal->getLabStatus2());

		texto = frmPrincipal->getLabStatus2()->get_text();

		CarregarArquivosLista(true, tabela, texto);
		TamTotalDiretorio(texto);
	}
}

void Catalogador::tabPanelMudou() {
	Arvore* arvore = getArvoreAtual();
	Tabela* tabela = getTabelaAtual();
	Gtk::TreeIter iter;
		
	if (arvore->get_model()->children().size() > 0) {

		iter = arvore->get_model()->children().begin();
		if (iter) {
			ListarArquivos(tabela, arvore, iter);
		}
	}
}

void Catalogador::DuploCliqueLista(const std::string &nome, const std::string &tipo) {
	if (tipo == Rotinas::getRecurso("TipoLista.diretorio")) {
		frmPrincipal->get_window()->set_cursor(Gdk::Cursor(Gdk::WATCH));

		std::string sCaminho = frmPrincipal->getLabStatus2()->get_text();

		if (Rotinas::testaSeparadorArquivo(sCaminho)) {
			sCaminho += nome;
		}
		else {
			sCaminho += Rotinas::BARRA_INVERTIDA + nome;
		}

		PesquisarArvoreDiretorio(sCaminho, getAbaAtual());

		frmPrincipal->get_window()->set_cursor(Gdk::Cursor(Gdk::ARROW));
	}
}

void Catalogador::EncontrarItemLista(const std::string &nomeAba, const std::string &nome,
	const std::string &caminho) {
	frmPrincipal->get_window()->set_cursor(Gdk::Cursor(Gdk::WATCH));

	Aba aba = *AbaBO::getInstancia()->pegaAbaPorNome(listaAbas, nomeAba);
	PesquisarArvoreDiretorio(caminho, aba);

	Tabela* tabela = getTabelaAtual();
	Gtk::TreePath path = tabela->encontrarCaminhoPorNome(nome);

	if (!path.empty()) {
		tabela->get_selection()->select(path);
		tabela->scroll_to_cell(path, *tabela->colunaNome, 0, 0);
	}

	frmPrincipal->get_window()->set_cursor(Gdk::Cursor(Gdk::ARROW));
}

int Catalogador::verificaNomeDiretorio(const std::string &sCaminho, RotuloRaiz *sRotuloRaiz) {
	sRotuloRaiz->setRotulo(DiretorioBO::getInstancia()->removerDrive(sCaminho));

	if (sRotuloRaiz->getRotulo().length() == 0) {

		sRotuloRaiz->setRotulo(Dialogo::entrada(frmPrincipal,
			"FrmPrincipal.DigitaNomeDiretorio"));

		if ((sRotuloRaiz->getRotulo() != NULL)
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
			frmPrincipal->get_window()->set_cursor(Gdk::Cursor(Gdk::WATCH));

			DiretorioBO::getInstancia()->exportarDiretorio(tipo, aba, arquivo, pLog);

			frmPrincipal->get_window()->set_cursor(Gdk::Cursor(Gdk::ARROW));

			Dialogo::mensagemErro(frmPrincipal, "FrmPrincipal.SucessoExportar");
		}
	}
}

void Catalogador::ExcluirDiretorioSelecionado(IProgressoLog pLog) {
	Arvore* arvore = getArvoreAtual();
	Gtk::TreeIter iter;

	iter = arvore->get_model()->children().begin();
	if (iter)
	{
		if (arvore->get_selection()->is_selected(iter)) {
			Tabela* tabela = getTabelaAtual();

			bool res = Dialogo::confirma(frmPrincipal, "FrmPrincipal.ExcluirDiretorioSelecionado");
			if (res) {
				frmPrincipal->get_window()->set_cursor(Gdk::Cursor(Gdk::WATCH));

				std::vector<std::string> sl = montaCaminhoStatus(arvore, iter);
				std::string caminho = Rotinas::SListTexto(sl);

				Aba aba = getAbaAtual();

				DiretorioBO::getInstancia()->excluirDiretorio(aba, caminho);
				ExcluirDados(aba, caminho);

				arvore->getStore()->erase(iter);
				tabela->limpar();

				CarregarDados(pLog, false, false);

				frmPrincipal->get_window()->set_cursor(Gdk::Cursor(Gdk::ARROW));
			}
		}
	}
}

void Catalogador::ImportarArquivo(std::vector<std::string> log, IProgressoLog pLog) {
	int nResultado;

	std::string arquivo = EscolhaArquivo::abrirArquivo(frmPrincipal, EscolhaArquivo::FILTRO_XML);
	//FileInfo arquivo = new FileInfo(EscolhaArquivo.NomeArquivo);

	if (Rotinas::FileExists(arquivo)) {
		frmPrincipal->get_window()->set_cursor(Gdk::Cursor(Gdk::WATCH));

		nResultado = DiretorioBO::getInstancia()->importarDiretorioViaXML(
			getAbaAtual(), arquivo, listaDiretorioPai, pLog);
		if (nResultado == -1) {
			Dialogo::mensagemErro(frmPrincipal, "FrmPrincipal.ImportacaoNaoRealizada");
		}
		else if (nResultado == -2) {
			Dialogo::mensagemErro(frmPrincipal, "FrmPrincipal.DiretorioExisteCatalogo");
		}
		else {
			FinalizaImportacao(pLog);
		}
		frmPrincipal->get_window()->set_cursor(Gdk::Cursor(Gdk::ARROW));
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

void Catalogador::FinalizaImportacao(IProgressoLog pLog) {
	Arvore* tvAba;

	frmPrincipal->get_window()->set_cursor(Gdk::Cursor(Gdk::WATCH));

	CarregarDados(pLog, true, true);
	tvAba = getArvoreAtual();
	CarregarArvore(tvAba, getAbaAtual());
	tabPanelMudou();

	frmPrincipal->get_window()->set_cursor(Gdk::Cursor(Gdk::ARROW));
	Dialogo::mensagemInfo(frmPrincipal,
		"FrmPrincipal.DirImportacaoSucesso");
}

void Catalogador::ComecaImportacao(bool bSubDiretorios, IProgressoLog pLog) {
	std::string sCaminho = "";
	std::vector<std::string> listaCaminho;

	sCaminho = EscolhaArquivo::abrirDiretorio(frmPrincipal);
	if (sCaminho.length() > 0) {
		if (Rotinas::DirectoryExists(sCaminho)) {
			frmPrincipal->get_window()->set_cursor(Gdk::Cursor(Gdk::WATCH));

			frmImportarDiretorio = new FrmImportarDiretorio();

			if (bSubDiretorios) {
				DiretorioBO::getInstancia()->carregarSubDiretorios(sCaminho, listaCaminho);
			}
			else {
				listaCaminho.push_back(sCaminho);
			}

			if (ImportarDiretorios(listaCaminho, bSubDiretorios, frmImportarDiretorio)) {
				FinalizaImportacao(pLog);
			}

			frmPrincipal->get_window()->set_cursor(Gdk::Cursor(Gdk::ARROW));
		}
	}
}

void Catalogador::InformacoesDiretorioArquivo() {
	Tabela* tabela = getTabelaAtual();
	Gtk::TreeIter iter;

	iter = tabela->get_selection()->get_selected();
	if (iter) {
		if (tabela->get_selection()->is_selected(iter)) {
			Aba aba = getAbaAtual();
			Diretorio dir = tabela->getLinhaSelecionada();
			dir.setAba(aba);
			frmInfoDiretorio = new FrmInfoDiretorio();
			frmInfoDiretorio->setDiretorio(dir);
			FrmInfoDiretorio::Mostrar();
		}
	}
}
*/
}
}
