#include "resource.h"
#include "hfsguardadir/objetosgui/EscolhaArquivo.h"

#include <gtkmm/filefilter.h>

namespace hfsguardadir {

namespace objetosgui {

const Glib::ustring EscolhaArquivo::FILTRO_TODOS_DIRETORIOS = "Todos os Diret�rios (*.*)|*.*";
const Glib::ustring EscolhaArquivo::FILTRO_TODOS_ARQUIVOS = "Todos os Arquivos (*.*)|*.*";
const Glib::ustring EscolhaArquivo::FILTRO_XML = "Arquivo XML (*.xml)|*.xml";
const Glib::ustring EscolhaArquivo::FILTRO_EXPORTAR = "Arquivo TXT (*.txt)|*.txt|Arquivo CSV (*.csv)|*.csv|Arquivo HTML (*.html)|*.html|Arquivo XML (*.xml)|*.xml|Arquivo SQL (*.sql)|*.sql";
const Glib::ustring EscolhaArquivo::FILTRO_IMAGEM = "Arquivo BMP (*.bmp)|*.bmp|Arquivo ICO (*.ico)|*.ico|Arquivo GIF (*.gif)|*.gif|Arquivo JPEG (*.png)|*.png|Arquivo PNG (*.jpg)|*.jpg|Arquivo TIFF (*.tif)|*.tif";

EscolhaArquivo::EscolhaArquivo()
{
}


EscolhaArquivo::~EscolhaArquivo()
{
}

void EscolhaArquivo::montaFiltro(Gtk::FileChooserDialog &fcdialog, const Glib::ustring &filtro) {
	std::vector<Glib::ustring> sl = Rotinas::SListSeparador(filtro, '|');
	Gtk::FileFilter ffiltro;
	bool bAdiciona = true;
	Glib::ustring item = "";

	for (unsigned int i = 0; i < sl.size(); i++) {
		item = sl.at(i);

		if (bAdiciona) {
			ffiltro.set_name(item);
			bAdiciona = false;
		}
		else {
			ffiltro.add_pattern(item);
			fcdialog.add_filter(ffiltro);
			bAdiciona = true;
		}
	}
}

Glib::ustring EscolhaArquivo::getTextoExtensao(const Glib::ustring &extensao) {
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

Glib::ustring EscolhaArquivo::escolher(Gtk::Window* pai, const Glib::ustring &filtro, const Glib::ustring &titulo,
	Gtk::FileChooserAction acao, const gchar* textoAcao,
	const Glib::ustring &diretorio, const Glib::ustring &arquivo) {

	Glib::ustring sretorno = "";

	Gtk::FileChooserDialog dialog(*pai, titulo, acao);
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

Glib::ustring EscolhaArquivo::abrirArquivo2(Gtk::Window* pai, const Glib::ustring filtro,
	const Glib::ustring &diretorio, const Glib::ustring &arquivo) {
	Glib::ustring sarquivo = "";
	Glib::ustring titulo = Rotinas::getRecurso("EscolhaArquivo.openButtonText");

	sarquivo = EscolhaArquivo::escolher(pai, filtro, titulo,
		Gtk::FileChooserAction::FILE_CHOOSER_ACTION_OPEN, "Abrir", diretorio, arquivo);

	return sarquivo;
}

Glib::ustring EscolhaArquivo::abrirArquivo(Gtk::Window* pai, const Glib::ustring filtro) {
	return EscolhaArquivo::abrirArquivo2(pai, filtro, "", "");
}

Glib::ustring EscolhaArquivo::salvarArquivo2(Gtk::Window* pai, const Glib::ustring filtro,
	const Glib::ustring &diretorio, const Glib::ustring &arquivo) {
	Glib::ustring sarquivo = "";
	Glib::ustring titulo = Rotinas::getRecurso("EscolhaArquivo.saveButtonText");

	sarquivo = EscolhaArquivo::escolher(pai, filtro, titulo,
		Gtk::FileChooserAction::FILE_CHOOSER_ACTION_SAVE, "Salvar", diretorio, arquivo);

	return sarquivo;
}

Glib::ustring EscolhaArquivo::salvarArquivo(Gtk::Window* pai, const Glib::ustring filtro) {
	return EscolhaArquivo::salvarArquivo2(pai, filtro, "", "");
}

Glib::ustring EscolhaArquivo::abrirDiretorio2(Gtk::Window* pai, const Glib::ustring &diretorio) {
	Glib::ustring sdiretorio = "";
	Glib::ustring titulo = Rotinas::getRecurso("EscolhaArquivo.ApproveButtonText");

	sdiretorio = EscolhaArquivo::escolher(pai, EscolhaArquivo::FILTRO_TODOS_DIRETORIOS, titulo,
		Gtk::FileChooserAction::FILE_CHOOSER_ACTION_SELECT_FOLDER, "Selecionar", diretorio, "");

	return sdiretorio;
}

Glib::ustring EscolhaArquivo::abrirDiretorio(Gtk::Window* pai) {
	//Glib::ustring dir = Glib::get_current_dir();
	Glib::ustring dir = Rotinas::AppDirName();
	return EscolhaArquivo::abrirDiretorio2(pai, dir);
}


}
}
