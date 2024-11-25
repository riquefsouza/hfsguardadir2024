#include "resource.h"
#include "FrmCadExtensao.h"

#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/catalogador/Catalogador.h"
#include "hfsguardadir/objetos/Extensao.h"
#include "hfsguardadir/objetosbo/ExtensaoBO.h"
#include "hfsguardadir/objetosgui/EscolhaArquivo.h"
#include "hfsguardadir/objetosgui/Dialogo.h"

using namespace hfsguardadir::comum;
using namespace hfsguardadir::catalogador;
using namespace hfsguardadir::objetos;
using namespace hfsguardadir::objetosbo;
using namespace hfsguardadir::objetosgui;

FrmCadExtensao *frmCadExtensao = (FrmCadExtensao *) NULL;

FXDEFMAP(FrmCadExtensao) FrmCadExtensaoMap[]={
	FXMAPFUNC(SEL_COMMAND, FrmCadExtensao::MENU_INCLUIREXTENSAO, FrmCadExtensao::on_menuIncluirExtensao),
	FXMAPFUNC(SEL_COMMAND, FrmCadExtensao::MENU_EXCLUIREXTENSAO, FrmCadExtensao::on_menuExcluirExtensao),
	FXMAPFUNC(SEL_COMMAND, FrmCadExtensao::MENU_EXCLUIRTODASEXTENSOES, FrmCadExtensao::on_menuExcluirTodasExtensoes),
	FXMAPFUNC(SEL_COMMAND, FrmCadExtensao::MENU_EXPORTARBITMAP, FrmCadExtensao::on_menuExportarBitmap),
	FXMAPFUNC(SEL_COMMAND, FrmCadExtensao::MENU_EXPORTARICONE, FrmCadExtensao::on_menuExportarIcone),
	FXMAPFUNC(SEL_COMMAND, FrmCadExtensao::MENU_EXPORTARGIF, FrmCadExtensao::on_menuExportarGIF),
	FXMAPFUNC(SEL_COMMAND, FrmCadExtensao::MENU_EXPORTARJPEG, FrmCadExtensao::on_menuExportarJPEG),
	FXMAPFUNC(SEL_COMMAND, FrmCadExtensao::MENU_EXPORTARPNG, FrmCadExtensao::on_menuExportarPNG),
	FXMAPFUNC(SEL_COMMAND, FrmCadExtensao::MENU_EXPORTARTIFF, FrmCadExtensao::on_menuExportarTIFF),
	FXMAPFUNC(SEL_COMMAND, FrmCadExtensao::MENU_IMPORTARICONESARQUIVOS, FrmCadExtensao::on_menuImportarIconesArquivos),
	FXMAPFUNC(SEL_COMMAND, FrmCadExtensao::MENU_EXTRAIRICONESARQUIVOS, FrmCadExtensao::on_menuExtrairIconesArquivos),
	FXMAPFUNC(SEL_CLICKED, FrmCadExtensao::BTN_INCLUIR, FrmCadExtensao::on_btnIncluir_clicked),
	FXMAPFUNC(SEL_CLICKED, FrmCadExtensao::BTN_EXCLUIR, FrmCadExtensao::on_btnExcluir_clicked)
};
FXIMPLEMENT(FrmCadExtensao,FXDialogBox,FrmCadExtensaoMap,ARRAYNUMBER(FrmCadExtensaoMap))


FrmCadExtensao::FrmCadExtensao(FXWindow* owner):
  FXDialogBox(owner, "Cadastro de Extensão de Arquivo", DECOR_TITLE | DECOR_CLOSE,
    0, 0, 350, 418, 0, 0, 0, 0, 4, 4){

	barraMenu = new FXMenuBar(this, LAYOUT_SIDE_TOP | LAYOUT_FILL_X);

	menuExtensao = new FXMenuPane(this);
	new FXMenuTitle(barraMenu, "Extensão", NULL, menuExtensao);
	menuIncluirExtensao = new FXMenuCommand(menuExtensao, "Incluir Extensão", NULL, this, MENU_INCLUIREXTENSAO);
	menuExcluirExtensao = new FXMenuCommand(menuExtensao, "Excluir Extensão", NULL, this, MENU_EXCLUIREXTENSAO);
	menuExcluirTodasExtensoes = new FXMenuCommand(menuExtensao, "Excluir Todas Extensões", NULL, this, MENU_EXCLUIRTODASEXTENSOES);
	
	menuExportarTodos = new FXMenuPane(this);
	new FXMenuTitle(barraMenu, "Exportar Todos", NULL, menuExportarTodos);
	menuExportarBitmap = new FXMenuCommand(menuExportarTodos, "Exportar para Bitmap", NULL, this, MENU_EXPORTARBITMAP);
	menuExportarIcone = new FXMenuCommand(menuExportarTodos, "Exportar para Ícone", NULL, this, MENU_EXPORTARICONE);
	menuExportarGIF = new FXMenuCommand(menuExportarTodos, "Exportar para GIF", NULL, this, MENU_EXPORTARGIF);
	menuExportarJPEG = new FXMenuCommand(menuExportarTodos, "Exportar para JPEG", NULL, this, MENU_EXPORTARJPEG);
	menuExportarPNG = new FXMenuCommand(menuExportarTodos, "Exportar para PNG", NULL, this, MENU_EXPORTARPNG);
	menuExportarTIFF = new FXMenuCommand(menuExportarTodos, "Exportar para TIFF", NULL, this, MENU_EXPORTARTIFF);

	menuImportarTodos = new FXMenuPane(this);
	new FXMenuTitle(barraMenu, "Importar Todos", NULL, menuImportarTodos);
	menuImportarIconesArquivos = new FXMenuCommand(menuImportarTodos, "Importar Ícones dos Arquivos", NULL, this, MENU_IMPORTARICONESARQUIVOS);
	menuExtrairIconesArquivos = new FXMenuCommand(menuImportarTodos, "Extrair Ícones dos Arquivos", NULL, this, MENU_EXTRAIRICONESARQUIVOS);

	FXVerticalFrame *frame = new FXVerticalFrame(this, LAYOUT_FILL_X | LAYOUT_FILL_Y);

	tabelaExtensao = new FXTable(frame, this, TABELA_EXTENSAO, LAYOUT_FILL_X | LAYOUT_FILL_Y);
	tabelaExtensao->setTableStyle(TABLE_COL_SIZABLE | TABLE_READONLY);
	tabelaExtensao->setEditable(false);
	tabelaExtensao->setDefRowHeight(20);

	definirColunas(1);
	
	FXHorizontalFrame *frameBotoes = new FXHorizontalFrame(frame,
		LAYOUT_SIDE_BOTTOM | LAYOUT_FILL_X);

	btnIncluir = new FXButton(frameBotoes, "Incluir", 0, this, BTN_INCLUIR,
		LAYOUT_CENTER_X | FRAME_RAISED | FRAME_THICK, 0, 0, 0, 0, 30, 30);
	btnExcluir = new FXButton(frameBotoes, "Excluir", 0, this, BTN_EXCLUIR,
		LAYOUT_CENTER_X | FRAME_RAISED | FRAME_THICK, 0, 0, 0, 0, 30, 30);

	CarregarExtensoesNaGrid();
}

void FrmCadExtensao::create(){
  FXDialogBox::create();
}

FrmCadExtensao::~FrmCadExtensao(){
}

void FrmCadExtensao::mostrar(FXWindow* owner)
{
	frmCadExtensao = new FrmCadExtensao(owner);
	frmCadExtensao->execute(PLACEMENT_SCREEN);
}

void FrmCadExtensao::limparTabelaExtensao() {
	//this->clearItems();
	for (int r = 0; r < tabelaExtensao->getNumRows(); r++) {
		for (int c = 0; c < tabelaExtensao->getNumColumns(); c++) {
			tabelaExtensao->setItemText(r, c, "");
		}
	}
}

void FrmCadExtensao::definirColunas(int numRows) {
	tabelaExtensao->setTableSize(numRows, 2);
	tabelaExtensao->setColumnText(0, "Extensão");
	tabelaExtensao->setColumnText(1, "Ícone");
}

void FrmCadExtensao::CarregarExtensoesNaGrid() {
	Extensao extensao;

	int nTamListaDir = (int)catalogador->listaExtensoes.size();

	definirColunas(nTamListaDir);

	limparTabelaExtensao();

	for (int i = 0; i < nTamListaDir; i++) {
		extensao = catalogador->listaExtensoes.at(i);

		tabelaExtensao->setItemText(i, 0, extensao.getNome().c_str());
		//tabelaExtensao->setItemText(i, 1, extensao.getBmp16());
	}
}

long FrmCadExtensao::on_menuIncluirExtensao(FXObject* obj, FXSelector sel, void* ptr) {
	std::vector<std::string> log;

	std::string arquivo = EscolhaArquivo::abrirArquivo(
		frmCadExtensao, EscolhaArquivo::FILTRO_IMAGEM);

	if (arquivo.length() > 0) {
		if (Rotinas::FileExists(arquivo)) {

			if (ExtensaoBO::getInstancia()->SalvarExtensao(
				catalogador->listaExtensoes, arquivo, arquivo, log)) {

				CarregarExtensoesNaGrid();

				Dialogo::mensagemInfo(frmCadExtensao,
					"ExtensaoSalvaSucesso");
			}
			else {
				Dialogo::mensagemInfo(frmCadExtensao,
					"ExtensaoJaCadastrada");
			}
		}
	}

	return true;
}

long FrmCadExtensao::on_menuExcluirExtensao(FXObject* obj, FXSelector sel, void* ptr) {
	Extensao extensao;
	std::vector<int> indices;

	if (catalogador->listaExtensoes.size() > 0) {
		bool res = Dialogo::confirma(frmCadExtensao,
			"ExtensaoCertezaExcluir");
		if (res) {
			int row = tabelaExtensao->getCurrentRow();
			//int col = tabelaExtensao->getCurrentColumn();
			
			extensao = *ExtensaoBO::getInstancia()->pegaExtensaoPorOrdem(
				catalogador->listaExtensoes, row + 1);

			if (ExtensaoBO::getInstancia()->excluirExtensao(
				catalogador->listaExtensoes, extensao.getCodigo())) {
				CarregarExtensoesNaGrid();
				Dialogo::mensagemInfo(frmCadExtensao,
					"ExtensaoExcluidaSucesso");
			}
		}
	}
	return true;
}

long FrmCadExtensao::on_menuExcluirTodasExtensoes(FXObject* obj, FXSelector sel, void* ptr) {
	bool res = Dialogo::confirma(frmCadExtensao, "ExtensaoCertezaTodosExcluir");
	if (res) {
		if (ExtensaoBO::getInstancia()->excluirTodasExtensoes(catalogador->listaExtensoes)) {
			CarregarExtensoesNaGrid();
			Dialogo::mensagemInfo(frmCadExtensao, "ExtensoesExcluidasSucesso");
		}
	}	
	return true;
}

long FrmCadExtensao::on_menuExportarBitmap(FXObject* obj, FXSelector sel, void* ptr) {
	ExtensaoBO::getInstancia()->ExportarExtensao(teBMP, catalogador->listaExtensoes);
	return true;
}

long FrmCadExtensao::on_menuExportarIcone(FXObject* obj, FXSelector sel, void* ptr) {
	ExtensaoBO::getInstancia()->ExportarExtensao(teICO, catalogador->listaExtensoes);
	return true;
}

long FrmCadExtensao::on_menuExportarGIF(FXObject* obj, FXSelector sel, void* ptr) {
	ExtensaoBO::getInstancia()->ExportarExtensao(teGIF, catalogador->listaExtensoes);
	return true;
}

long FrmCadExtensao::on_menuExportarJPEG(FXObject* obj, FXSelector sel, void* ptr) {
	ExtensaoBO::getInstancia()->ExportarExtensao(teJPG, catalogador->listaExtensoes);
	return true;
}

long FrmCadExtensao::on_menuExportarPNG(FXObject* obj, FXSelector sel, void* ptr) {
	ExtensaoBO::getInstancia()->ExportarExtensao(tePNG, catalogador->listaExtensoes);
	return true;
}

long FrmCadExtensao::on_menuExportarTIFF(FXObject* obj, FXSelector sel, void* ptr) {
	ExtensaoBO::getInstancia()->ExportarExtensao(teTIF, catalogador->listaExtensoes);
	return true;
}

long FrmCadExtensao::on_menuImportarIconesArquivos(FXObject* obj, FXSelector sel, void* ptr) {
	std::string arquivo = EscolhaArquivo::abrirArquivo(frmCadExtensao,
		EscolhaArquivo::FILTRO_IMAGEM);

	if (arquivo.length() > 0) {
		if (Rotinas::FileExists(arquivo)) {
			ExtensaoBO::getInstancia()->ImportarExtensao(arquivo, catalogador->listaExtensoes);
			CarregarExtensoesNaGrid();
		}
	}
	return true;
}

long FrmCadExtensao::on_menuExtrairIconesArquivos(FXObject* obj, FXSelector sel, void* ptr) {
	std::string arquivo = EscolhaArquivo::abrirArquivo(frmCadExtensao,
		EscolhaArquivo::FILTRO_IMAGEM);

	if (arquivo.length() > 0) {
		if (Rotinas::FileExists(arquivo)) {
			ExtensaoBO::getInstancia()->ExtrairExtensao(arquivo, catalogador->listaExtensoes);
			CarregarExtensoesNaGrid();
		}
	}
	return true;
}

long FrmCadExtensao::on_btnIncluir_clicked(FXObject* obj, FXSelector sel, void* ptr) {
	on_menuIncluirExtensao(obj, sel, ptr);
	return true;
}

long FrmCadExtensao::on_btnExcluir_clicked(FXObject* obj, FXSelector sel, void* ptr) {
	on_menuExcluirExtensao(obj, sel, ptr);
	return true;
}

