#include "hfsguardadir\objetosgui\Dialogo.h"
#include "resource.h"

namespace hfsguardadir {

namespace objetosgui {

Dialogo::Dialogo()
{
}


Dialogo::~Dialogo()
{
}

int Dialogo::MsgDlg(FXWindow* pai, const char *sTitulo, const char *sMensagem){
	//, Gtk::MessageType tipo, Gtk::ButtonsType botoes) {

	return FXMessageBox::information(pai, MBOX_OK, sTitulo, sMensagem);
}

void Dialogo::mensagemErro2(FXWindow* pai, const char* recurso, const std::string &texto) {
	std::string msg, titulo;

	msg = Rotinas::getRecurso(recurso);
	msg += " " + texto;

	titulo = Rotinas::getRecurso("Dialogo.erro");

	FXMessageBox::error(pai, MBOX_OK, titulo.c_str(), msg.c_str());
}

void Dialogo::mensagemErro(FXWindow* pai, const char* recurso) {
	Dialogo::mensagemErro2(pai, recurso, "");
}

void Dialogo::mensagemInfo(FXWindow* pai, const char* recurso) {
	std::string msg, titulo;

	msg = Rotinas::getRecurso(recurso);
	titulo = Rotinas::getRecurso("Dialogo.info");

	FXMessageBox::information(pai, MBOX_OK, titulo.c_str(), msg.c_str());
}

bool Dialogo::confirma(FXWindow* pai, const char* recurso) {
	std::string msg, titulo;

	msg = Rotinas::getRecurso(recurso);
	titulo = Rotinas::getRecurso("Dialogo.confirma");

	return (FXMessageBox::question(pai, MBOX_YES_NO, titulo.c_str(), msg.c_str()) == MBOX_CLICKED_YES);
}

std::string Dialogo::entrada2(FXWindow* pai, const char* recurso,
	const std::string &valorInicial) {
	FXString titulo, rotulo;
	std::string texto;

	int response;

	texto = "";
	titulo = Rotinas::getRecurso("Dialogo.entrada").c_str();
	rotulo = Rotinas::getRecurso(recurso).c_str();
	
	FXDialogBox* dialog = new FXDialogBox(pai, titulo);

	FXGroupBox* grupo = new FXGroupBox(dialog, "", 
		GROUPBOX_TITLE_LEFT | FRAME_RIDGE | LAYOUT_FILL_X);

	FXHorizontalFrame* frameok = new FXHorizontalFrame(dialog,
		LAYOUT_BOTTOM | LAYOUT_FILL_X | PACK_UNIFORM_WIDTH);
	new FXButton(frameok, "&Ok", NULL, dialog, FXDialogBox::ID_ACCEPT,
		LAYOUT_CENTER_X | FRAME_RAISED | FRAME_THICK, 0, 0, 0, 0, 30, 30);
	new FXButton(frameok, "&Cancelar", NULL, dialog, FXDialogBox::ID_CANCEL,
		LAYOUT_CENTER_X | FRAME_RAISED | FRAME_THICK, 0, 0, 0, 0, 30, 30);

	FXBMPIcon* icone = new FXBMPIcon(pai->getApp(), cdouro);

	FXMatrix* matrix = new FXMatrix(grupo, 2);
	FXLabel* label1 = new FXLabel(matrix, rotulo, icone);
	FXTextField* local_entry1 = new FXTextField(matrix, 30, dialog, FXDialogBox::ID_LAST, FRAME_SUNKEN);
	local_entry1->setTextStyle(TEXTFIELD_LIMITED);
	local_entry1->setText(valorInicial.c_str());
	
	response = dialog->execute(PLACEMENT_SCREEN);

	if (response == FXDialogBox::ID_ACCEPT)
	{
		texto = local_entry1->getText().text();
	}

	delete dialog;
	delete icone;

	return texto;
}

std::string Dialogo::entrada(FXWindow* pai, const char* recurso) {
	return Dialogo::entrada2(pai, recurso, "");
}

}
}