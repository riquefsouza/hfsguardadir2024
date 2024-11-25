#ifndef FrmInfoDiretorio_H
#define FrmInfoDiretorio_H
// ---------------------------------------------------------------------------
#include "resource.h"
#include "hfsguardadir/objetos/Diretorio.h"
// ---------------------------------------------------------------------------
struct SFrmInfoDiretorio {
	GtkWidget *dialog_vbox3; 
	GtkWidget *vbox3; 
	GtkWidget *frame1; 
	GtkWidget *grid1; 
	GtkWidget *labArquivoComum; 
	GtkWidget *labArquivoOculto; 
	GtkWidget *labArquivoSistema; 
	GtkWidget *labLegendaDiretorio; 
	GtkWidget *labVolumeID; 
	GtkWidget *labArquivoSomenteLeitura; 
	GtkWidget *scrollTabela1; 
	GtkWidget *tabelaInfo; 
	GtkTreeViewColumn *colunaInfoItem; 
	GtkTreeViewColumn *colunaInfoDescricao; 
	GtkWidget *dialog_action_area3; 
	GtkWidget *btnOk; 

	GtkListStore *store;
	GtkTreeModel *modelo;
	GtkTreeSelection *selecao;

	GtkWidget *frmInfoDiretorio;
};
extern struct SFrmInfoDiretorio FrmInfoDiretorio;
// ---------------------------------------------------------------------------
	GtkWidget *FrmInfoDiretorio_Criar();
	void FrmInfoDiretorio_Mostrar();
	void on_FrmInfoDiretorio_destroy(GtkWidget* widget, gpointer user_data);

	void on_btnOk_clicked(GtkWidget* widget, gpointer user_data);
	void FrmInfoDiretorio_ConstruirGrid();
	void FrmInfoDiretorio_setDiretorio(Diretorio diretorio);
// ---------------------------------------------------------------------------
#endif
// ---------------------------------------------------------------------------
