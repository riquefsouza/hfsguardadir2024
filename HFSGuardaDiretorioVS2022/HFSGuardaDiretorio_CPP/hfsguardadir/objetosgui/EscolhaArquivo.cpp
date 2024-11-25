//#include "resource.h"
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
/*
void EscolhaArquivo::montaFiltro(Gtk::FileChooserDialog &fcdialog, const std::string &filtro) {
	std::vector<std::string> sl = Rotinas::SListSeparador(filtro, '|');
	Gtk::FileFilter ffiltro;
	bool bAdiciona = true;
	std::string item = "";
	
	for (unsigned int i = 0; i < sl.size(); i++) {
		item = sl.at(i);

		if (bAdiciona) {
			ffiltro.set_name(Rotinas::retUTF8(item));
			bAdiciona = false;
		}
		else {
			ffiltro.add_pattern(item);
			fcdialog.add_filter(ffiltro);
			bAdiciona = true;
		}
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

std::string EscolhaArquivo::escolher(Gtk::Window* pai, const std::string &filtro, const std::string &titulo,
	Gtk::FileChooserAction acao, const gchar* textoAcao,
	const std::string &diretorio, const std::string &arquivo) {

	std::string sretorno = "";

	Gtk::FileChooserDialog dialog(*pai, Rotinas::retUTF8(titulo), acao);
	dialog.add_button("Cancelar", Gtk::ResponseType::RESPONSE_CANCEL);
	dialog.add_button(textoAcao, Gtk::ResponseType::RESPONSE_ACCEPT);
	
	dialog.set_position(Gtk::WIN_POS_CENTER);
	EscolhaArquivo::montaFiltro(dialog, filtro);
	dialog.set_select_multiple(false);
	dialog.set_filename(arquivo);
	dialog.set_current_folder(diretorio);
	dialog.set_do_overwrite_confirmation(true);

	if (dialog.run() == Gtk::ResponseType::RESPONSE_ACCEPT)
	{
		if (acao == Gtk::FileChooserAction::FILE_CHOOSER_ACTION_SELECT_FOLDER)
			sretorno = dialog.get_filename();
		else
			sretorno = dialog.get_current_folder();
	}
	dialog.hide();
	return sretorno;
}

std::string EscolhaArquivo::abrirArquivo2(Gtk::Window* pai, const std::string filtro, 
	const std::string &diretorio, const std::string &arquivo) {
	std::string sarquivo = "";
	std::string titulo = Rotinas::getRecurso("EscolhaArquivo.openButtonText");

	sarquivo = EscolhaArquivo::escolher(pai, filtro, titulo, 
		Gtk::FileChooserAction::FILE_CHOOSER_ACTION_OPEN, "Abrir", diretorio, arquivo);

	return sarquivo;
}

std::string EscolhaArquivo::abrirArquivo(Gtk::Window* pai, const std::string filtro) {
	return EscolhaArquivo::abrirArquivo2(pai, filtro, "", "");
}

std::string EscolhaArquivo::salvarArquivo2(Gtk::Window* pai, const std::string filtro, 
	const std::string &diretorio, const std::string &arquivo) {
	std::string sarquivo = "";
	std::string titulo = Rotinas::getRecurso("EscolhaArquivo.saveButtonText");

	sarquivo = EscolhaArquivo::escolher(pai, filtro, titulo, 
		Gtk::FileChooserAction::FILE_CHOOSER_ACTION_SAVE, "Salvar", diretorio, arquivo);

	return sarquivo;
}

std::string EscolhaArquivo::salvarArquivo(Gtk::Window* pai, const std::string filtro) {
	return EscolhaArquivo::salvarArquivo2(pai, filtro, "", "");
}

std::string EscolhaArquivo::abrirDiretorio2(Gtk::Window* pai, const std::string &diretorio) {
	std::string sdiretorio = "";
	std::string titulo = Rotinas::getRecurso("EscolhaArquivo.ApproveButtonText");

	sdiretorio = EscolhaArquivo::escolher(pai, EscolhaArquivo::FILTRO_TODOS_DIRETORIOS, titulo,
		Gtk::FileChooserAction::FILE_CHOOSER_ACTION_SELECT_FOLDER, "Selecionar", diretorio, "");

	return sdiretorio;
}

std::string EscolhaArquivo::abrirDiretorio(Gtk::Window* pai) {
	//std::string dir = Glib::get_current_dir();
	std::string dir = Rotinas::AppDirName();
	return EscolhaArquivo::abrirDiretorio2(pai, dir);
}
*/

}
}
