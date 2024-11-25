#include "EscolhaArquivo.h"
#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosgui {

EscolhaArquivo::EscolhaArquivo()
{

}

QString EscolhaArquivo::getTextoExtensao(const QString &extensao) {
	if (extensao.toLower() == "txt") return Rotinas::getRecurso("EscolhaArquivo.filtroTXT");
	if (extensao.toLower() == "csv") return Rotinas::getRecurso("EscolhaArquivo.filtroCSV");
	if (extensao.toLower() == "html") return Rotinas::getRecurso("EscolhaArquivo.filtroHTML");
	if (extensao.toLower() == "xml") return Rotinas::getRecurso("EscolhaArquivo.filtroXML");
	if (extensao.toLower() == "sql") return Rotinas::getRecurso("EscolhaArquivo.filtroSQL");
	if (extensao.toLower() == "bmp") return Rotinas::getRecurso("EscolhaArquivo.filtroBMP");
	if (extensao.toLower() == "ico") return Rotinas::getRecurso("EscolhaArquivo.filtroICO");
	if (extensao.toLower() == "jpg") return Rotinas::getRecurso("EscolhaArquivo.filtroJPG");
	if (extensao.toLower() == "gif") return Rotinas::getRecurso("EscolhaArquivo.filtroGIF");
	if (extensao.toLower() == "png") return Rotinas::getRecurso("EscolhaArquivo.filtroPNG");
	if (extensao.toLower() == "tif") return Rotinas::getRecurso("EscolhaArquivo.filtroTIF");
	return Rotinas::getRecurso("EscolhaArquivo.acceptAllFileFilterText");
}

QString EscolhaArquivo::abrirDiretorio(QWidget *parent) {
	QString diretorio = QDir::currentPath();
	QFileDialog::Options opcoes = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
	QString dir = QFileDialog::getExistingDirectory(parent, 
		Rotinas::getRecurso("EscolhaArquivo.ApproveButtonText"), diretorio, opcoes);
	
	return dir;
}

QString EscolhaArquivo::abrirArquivo(QWidget *parent) {
	QString arquivo;
	
	return abrirArquivo(parent, arquivo, "");
}

QString EscolhaArquivo::abrirArquivo(QWidget *parent, const QString &arquivo, const QString &extensao) {
	QString filtroSelecionado;
	QString arq = QFileDialog::getOpenFileName(parent,
		Rotinas::getRecurso("EscolhaArquivo.openButtonText"), arquivo, getTextoExtensao(extensao), &filtroSelecionado);

	return arq;
}

QString EscolhaArquivo::salvarArquivo(QWidget *parent, const QString &arquivo, const QString &extensao) {
	QString filtroSelecionado;
	QString arq = QFileDialog::getSaveFileName(parent,
		Rotinas::getRecurso("EscolhaArquivo.saveButtonText"), arquivo, getTextoExtensao(extensao), &filtroSelecionado);

	return arq;
}

}
}
