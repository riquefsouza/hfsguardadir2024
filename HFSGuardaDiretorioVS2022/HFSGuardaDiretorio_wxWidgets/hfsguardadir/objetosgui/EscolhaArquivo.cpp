#include "EscolhaArquivo.h"
#include "hfsguardadir/comum/Rotinas.h"

#include <wx/dirdlg.h>
#include <wx/filedlg.h> 

using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosgui {

EscolhaArquivo::EscolhaArquivo()
{

}

wxString EscolhaArquivo::getTextoExtensao(const wxString &extensao) {
	if (extensao.Lower() == "txt") return Rotinas::getRecurso("EscolhaArquivo.filtroTXT");
	if (extensao.Lower() == "csv") return Rotinas::getRecurso("EscolhaArquivo.filtroCSV");
	if (extensao.Lower() == "html") return Rotinas::getRecurso("EscolhaArquivo.filtroHTML");
	if (extensao.Lower() == "xml") return Rotinas::getRecurso("EscolhaArquivo.filtroXML");
	if (extensao.Lower() == "sql") return Rotinas::getRecurso("EscolhaArquivo.filtroSQL");
	if (extensao.Lower() == "bmp") return Rotinas::getRecurso("EscolhaArquivo.filtroBMP");
	if (extensao.Lower() == "ico") return Rotinas::getRecurso("EscolhaArquivo.filtroICO");
	if (extensao.Lower() == "jpg") return Rotinas::getRecurso("EscolhaArquivo.filtroJPG");
	if (extensao.Lower() == "gif") return Rotinas::getRecurso("EscolhaArquivo.filtroGIF");
	if (extensao.Lower() == "png") return Rotinas::getRecurso("EscolhaArquivo.filtroPNG");
	if (extensao.Lower() == "tif") return Rotinas::getRecurso("EscolhaArquivo.filtroTIF");
	return Rotinas::getRecurso("EscolhaArquivo.acceptAllFileFilterText");
}

wxString EscolhaArquivo::abrirDiretorio(wxWindow *parent) {
	return wxDirSelector(Rotinas::getRecurso("EscolhaArquivo.ApproveButtonText"));
}

wxString EscolhaArquivo::abrirArquivo(wxWindow *parent) {
	return wxFileSelectorEx();
}

wxString EscolhaArquivo::abrirArquivo(wxWindow *parent, const wxString &arquivo, const wxString &extensao) {
	return wxFileSelector(Rotinas::getRecurso("EscolhaArquivo.openButtonText"),
		wxEmptyString, arquivo, extensao, getTextoExtensao(extensao), wxFD_OPEN | wxFD_FILE_MUST_EXIST, parent);
}

wxString EscolhaArquivo::salvarArquivo(wxWindow *parent, const wxString &arquivo, const wxString &extensao) {
	return wxFileSelector(Rotinas::getRecurso("EscolhaArquivo.saveButtonText"),
		wxEmptyString, arquivo, extensao, getTextoExtensao(extensao), wxFD_SAVE | wxFD_OVERWRITE_PROMPT, parent);
}

}
}
