#ifndef DIALOGO_H
#define DIALOGO_H

#include "../../resource.h"

gint Dialogo_MsgDlg(GtkWidget *pai, const gchar *sTitulo,
	const gchar *sMensagem, GtkMessageType tipo, GtkButtonsType botoes);
void Dialogo_mensagemErro2(GtkWidget *pai, const char* recurso, const GString* texto);
void Dialogo_mensagemErro(GtkWidget *pai, const char* recurso);
void Dialogo_mensagemInfo(GtkWidget *pai, const char* recurso);
gboolean Dialogo_confirma(GtkWidget *pai, const char* recurso);
GString* Dialogo_entrada(GtkWidget *pai, const char* recurso);
GString* Dialogo_entrada2(GtkWidget *pai, const char* recurso,
	const GString* valorInicial);

#endif
