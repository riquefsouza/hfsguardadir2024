#include "resource.h"
#include "hfsguardadir\objetosgui\EscolhaArquivo.h"

namespace hfsguardadir {

namespace objetosgui {

const std::string EscolhaArquivo::FILTRO_TODOS_DIRETORIOS = "Todos os Diretórios (*.*)|*.*";
const std::string EscolhaArquivo::FILTRO_TODOS_ARQUIVOS = "Todos os Arquivos (*.*)|*.*";
const std::string EscolhaArquivo::FILTRO_XML = "Arquivo XML (*.xml)|*.xml";
const std::string EscolhaArquivo::FILTRO_EXPORTAR = "Arquivo TXT (*.txt)|*.txt|Arquivo CSV (*.csv)|*.csv|Arquivo HTML (*.html)|*.html|Arquivo XML (*.xml)|*.xml|Arquivo SQL (*.sql)|*.sql";
const std::string EscolhaArquivo::FILTRO_IMAGEM = "Arquivo BMP (*.bmp)|*.bmp|Arquivo ICO (*.ico)|*.ico|Arquivo GIF (*.gif)|*.gif|Arquivo JPEG (*.png)|*.png|Arquivo PNG (*.jpg)|*.jpg|Arquivo TIFF (*.tif)|*.tif";

EscolhaArquivo::EscolhaArquivo()
{
}


EscolhaArquivo::~EscolhaArquivo()
{
}

void EscolhaArquivo::montaFiltro(FXFileDialog* fcdialog, const std::string filtro) {
	std::vector<std::string> sl = Rotinas::SListSeparador(filtro, '|');
	std::string item = "";
	
	for (unsigned int i = 0; i < sl.size(); i++) {
		item = sl.at(i);
		fcdialog->setPatternList(item.c_str());
	}
}

std::string EscolhaArquivo::getTextoExtensao(const std::string &extensao) {
	if (Rotinas::LowerCase(extensao) == "txt") return Rotinas::getRecurso("EscolhaArquivo.filtroTXT");
	if (Rotinas::LowerCase(extensao) == "csv") return Rotinas::getRecurso("EscolhaArquivo.filtroCSV");
	if (Rotinas::LowerCase(extensao) == "html") return Rotinas::getRecurso("EscolhaArquivo.filtroHTML");
	if (Rotinas::LowerCase(extensao) == "xml") return Rotinas::getRecurso("EscolhaArquivo.filtroXML");
	if (Rotinas::LowerCase(extensao) == "sql") return Rotinas::getRecurso("EscolhaArquivo.filtroSQL");
	if (Rotinas::LowerCase(extensao) == "bmp") return Rotinas::getRecurso("EscolhaArquivo.filtroBMP");
	if (Rotinas::LowerCase(extensao) == "ico") return Rotinas::getRecurso("EscolhaArquivo.filtroICO");
	if (Rotinas::LowerCase(extensao) == "jpg") return Rotinas::getRecurso("EscolhaArquivo.filtroJPG");
	if (Rotinas::LowerCase(extensao) == "gif") return Rotinas::getRecurso("EscolhaArquivo.filtroGIF");
	if (Rotinas::LowerCase(extensao) == "png") return Rotinas::getRecurso("EscolhaArquivo.filtroPNG");
	if (Rotinas::LowerCase(extensao) == "tif") return Rotinas::getRecurso("EscolhaArquivo.filtroTIF");
	return Rotinas::getRecurso("EscolhaArquivo.acceptAllFileFilterText");
}

std::string EscolhaArquivo::escolher(FXWindow* pai, const std::string &filtro, const std::string &titulo,
	std::string acao, const char* textoAcao,
	const std::string &diretorio, const std::string &arquivo) {

	std::string sretorno = "";

	FXFileDialog* dialog = new FXFileDialog(pai, titulo.c_str());
	EscolhaArquivo::montaFiltro(dialog, filtro);
	//dialog.set_select_multiple(false);
	dialog->setFilename(arquivo.c_str());
	dialog->setDirectory(diretorio.c_str());
	//dialog.set_do_overwrite_confirmation(true);

	int response = dialog->execute(PLACEMENT_SCREEN);

	if (response == FXDialogBox::ID_ACCEPT)
	{
		if (acao == "OPEN")
			sretorno = dialog->getFilename().text();
		else
			sretorno = dialog->getDirectory().text();
	}

	delete dialog;

	return sretorno;
}

std::string EscolhaArquivo::abrirArquivo2(FXWindow* pai, const std::string filtro,
	const std::string &diretorio, const std::string &arquivo) {
	std::string sarquivo = "";
	std::string titulo = Rotinas::getRecurso("EscolhaArquivo.openButtonText");

	sarquivo = EscolhaArquivo::escolher(pai, filtro, titulo, 
		"OPEN", "Abrir", diretorio, arquivo);

	return sarquivo;
}

std::string EscolhaArquivo::abrirArquivo(FXWindow* pai, const std::string filtro) {
	return EscolhaArquivo::abrirArquivo2(pai, filtro, "", "");
}

std::string EscolhaArquivo::salvarArquivo2(FXWindow* pai, const std::string filtro,
	const std::string &diretorio, const std::string &arquivo) {
	std::string sarquivo = "";
	std::string titulo = Rotinas::getRecurso("EscolhaArquivo.saveButtonText");

	sarquivo = EscolhaArquivo::escolher(pai, filtro, titulo, 
		"SAVE", "Salvar", diretorio, arquivo);

	return sarquivo;
}

std::string EscolhaArquivo::salvarArquivo(FXWindow* pai, const std::string filtro) {
	return EscolhaArquivo::salvarArquivo2(pai, filtro, "", "");
}

std::string EscolhaArquivo::abrirDiretorio2(FXWindow* pai, const std::string &diretorio) {
	std::string sdiretorio = "";
	std::string titulo = Rotinas::getRecurso("EscolhaArquivo.ApproveButtonText");

	sdiretorio = EscolhaArquivo::escolher(pai, EscolhaArquivo::FILTRO_TODOS_DIRETORIOS, titulo,
		"SELECT_FOLDER", "Selecionar", diretorio, "");

	return sdiretorio;
}

std::string EscolhaArquivo::abrirDiretorio(FXWindow* pai) {
	std::string dir = Rotinas::AppDirName();
	return EscolhaArquivo::abrirDiretorio2(pai, dir);
}


}
}
