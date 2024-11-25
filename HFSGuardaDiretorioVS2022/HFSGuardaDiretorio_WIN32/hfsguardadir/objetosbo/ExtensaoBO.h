#ifndef EXTENSAOBO_H
#define EXTENSAOBO_H

#include "hfsguardadir/objetos/Extensao.h"
#include "hfsguardadir/objetos/Diretorio.h"
#include "hfsguardadir/comum/Rotinas.h"

//void ExtensaoBO_iniciar(HWND hwnd);
ListaExtensao ExtensaoBO_carregarExtensao(IProgressoLog progressoLog);
int ExtensaoBO_retMaxCodExtensao(ListaExtensao listaLocal);
BOOL ExtensaoBO_existeExtensao(String sExtensao, ListaExtensao listaLocal);
BOOL ExtensaoBO_incluirExtensao(Extensao extensao);
BOOL ExtensaoBO_SalvarExtensao(ListaExtensao listaExtensao, String sNomeDiretorio,
					String sCaminhoOriginal, ListaString log);
void ExtensaoBO_salvarExtensoes(ListaDiretorio listaDiretorio,
		ListaExtensao listaExtensao, IProgressoLog progressoLog);
BOOL ExtensaoBO_excluirExtensao(ListaExtensao listaExtensao, int codigo);
BOOL ExtensaoBO_excluirTodasExtensoes(ListaExtensao listaExtensao);
BOOL ExtensaoBO_criarTabelaExtensoes();
int ExtensaoBO_indiceExtensao(ListaExtensao lista, String nomeExtensao);
Extensao* ExtensaoBO_pegaExtensaoPorOrdem(ListaExtensao lista, int ordem);
Extensao* ExtensaoBO_pegaExtensaoPorCodigo(ListaExtensao lista, int codigo);
Extensao ExtensaoBO_pegaExtensaoPorNome(ListaExtensao lista,
		const String nome, const String tipo);
BOOL ExtensaoBO_ExportarExtensao(TipoExportarExtensao tipo,
					  ListaExtensao listaExtensao);
void ExtensaoBO_ImportarExtensao(String caminho, ListaExtensao listaExtensao);
void ExtensaoBO_ExtrairExtensao(String caminho, ListaExtensao listaExtensao);

#endif
