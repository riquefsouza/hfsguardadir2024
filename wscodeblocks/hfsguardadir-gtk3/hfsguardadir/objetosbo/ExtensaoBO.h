#ifndef EXTENSAOBO_H
#define EXTENSAOBO_H

#include "../objetos/Extensao.h"
#include "../objetos/Diretorio.h"
#include "../comum/Rotinas.h"

extern GdkPixbuf* ExtensaoBO_diretorioBMP;
extern GdkPixbuf* ExtensaoBO_arquivoBMP;

extern GdkPixbuf* ExtensaoBO_DiretorioXPM;
extern GdkPixbuf* ExtensaoBO_Diretorio32XPM;
extern GdkPixbuf* ExtensaoBO_DirAbertoXPM;
extern GdkPixbuf* ExtensaoBO_DirAberto32XPM;
extern GdkPixbuf* ExtensaoBO_CDOuroXPM;
extern GdkPixbuf* ExtensaoBO_ArquivoXPM;
extern GdkPixbuf* ExtensaoBO_Arquivo32XPM;

void ExtensaoBO_iniciar();
ListaExtensao ExtensaoBO_carregarExtensao(IProgressoLog progressoLog);
int ExtensaoBO_retMaxCodExtensao(ListaExtensao listaLocal);
gboolean ExtensaoBO_existeExtensao(GString* sExtensao, ListaExtensao listaLocal);
gboolean ExtensaoBO_incluirExtensao(Extensao extensao);
gboolean ExtensaoBO_SalvarExtensao(ListaExtensao listaExtensao, GString* sNomeDiretorio,
					GString* sCaminhoOriginal, ListaString log);
void ExtensaoBO_salvarExtensoes(ListaDiretorio listaDiretorio,
		ListaExtensao listaExtensao, IProgressoLog progressoLog);
gboolean ExtensaoBO_excluirExtensao(ListaExtensao listaExtensao, int codigo);
gboolean ExtensaoBO_excluirTodasExtensoes(ListaExtensao listaExtensao);
gboolean ExtensaoBO_criarTabelaExtensoes();
int ExtensaoBO_indiceExtensao(ListaExtensao lista, GString* nomeExtensao);
GdkPixbuf* ExtensaoBO_pixbufExtensao(ListaExtensao lista, const GString* nomeExtensao);
Extensao ExtensaoBO_pegaExtensaoPorOrdem(ListaExtensao lista, int ordem);
Extensao ExtensaoBO_pegaExtensaoPorCodigo(ListaExtensao lista, int codigo);
Extensao ExtensaoBO_pegaExtensaoPorNome(ListaExtensao lista,
		const GString* nome, const GString* tipo);
gboolean ExtensaoBO_ExportarExtensao(TipoExportarExtensao tipo,
					  ListaExtensao listaExtensao);
void ExtensaoBO_ImportarExtensao(GString* caminho, ListaExtensao listaExtensao);
void ExtensaoBO_ExtrairExtensao(GString* caminho, ListaExtensao listaExtensao);

#endif
