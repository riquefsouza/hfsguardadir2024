#ifndef ESCOLHAARQUIVO_H
#define ESCOLHAARQUIVO_H

#include "../../resource.h"

#define EscolhaArquivo_FILTRO_TODOS_DIRETORIOS "Todos os Diretórios (*.*)|*.*"
#define EscolhaArquivo_FILTRO_TODOS_ARQUIVOS "Todos os Arquivos (*.*)|*.*"
#define EscolhaArquivo_FILTRO_XML "Arquivo XML (*.xml)|*.xml"
#define EscolhaArquivo_FILTRO_EXPORTAR "Arquivo TXT (*.txt)|*.txt|Arquivo CSV (*.csv)|*.csv|Arquivo HTML (*.html)|*.html|Arquivo XML (*.xml)|*.xml|Arquivo SQL (*.sql)|*.sql"
#define EscolhaArquivo_FILTRO_IMAGEM "Arquivo BMP (*.bmp)|*.bmp|Arquivo ICO (*.ico)|*.ico|Arquivo GIF (*.gif)|*.gif|Arquivo JPEG (*.png)|*.png|Arquivo PNG (*.jpg)|*.jpg|Arquivo TIFF (*.tif)|*.tif"

void EscolhaArquivo_montaFiltro(GtkWidget* fcdialog, const gchar* filtro);
GString* EscolhaArquivo_getTextoExtensao(const GString* extensao);
GString* EscolhaArquivo_escolher(GtkWidget *pai, const gchar *filtro, const GString *titulo,
	GtkFileChooserAction acao, const gchar* textoAcao, const GString* diretorio, const GString* arquivo);
GString* EscolhaArquivo_abrirArquivo2(GtkWidget *pai, const gchar* filtro, const GString* diretorio, const GString* arquivo);
GString* EscolhaArquivo_abrirArquivo(GtkWidget *pai, const gchar* filtro);
GString* EscolhaArquivo_salvarArquivo2(GtkWidget *pai, const gchar* filtro, const GString* diretorio, const GString* arquivo);
GString* EscolhaArquivo_salvarArquivo(GtkWidget *pai, const gchar* filtro);
GString* EscolhaArquivo_abrirDiretorio2(GtkWidget *pai, const GString* diretorio);
GString* EscolhaArquivo_abrirDiretorio(GtkWidget *pai);

#endif
