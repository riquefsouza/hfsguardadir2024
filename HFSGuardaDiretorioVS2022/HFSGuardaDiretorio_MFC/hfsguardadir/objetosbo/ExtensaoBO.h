#ifndef EXTENSAOBO_H
#define EXTENSAOBO_H

#pragma once

#include "hfsguardadir/objetos/Extensao.h"
#include "hfsguardadir/objetos/Diretorio.h"
#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosbo {

class ExtensaoBO
{
private:
	//CBitmap *diretorioBMP, *diretorio32BMP;
	//CBitmap *arquivoBMP, *arquivo32BMP;

	ExtensaoBO();
	ExtensaoBO(ExtensaoBO const&);
	ExtensaoBO& operator=(ExtensaoBO const&);
	static ExtensaoBO* instancia;

public:
	static ExtensaoBO* getInstancia();

	CList<Extensao, Extensao&>* carregarExtensao(IProgressoLog progressoLog);
	int retMaxCodExtensao(const CList<Extensao, Extensao&> &listaLocal);
	BOOL existeExtensao(const CString &sExtensao, const CList<Extensao, Extensao&> &listaLocal);
	BOOL incluirExtensao(Extensao extensao);
	BOOL SalvarExtensao(CList<Extensao, Extensao&> &listaExtensao, const CString &sNomeDiretorio,
						const CString &sCaminhoOriginal, CStringList &log);
	void salvarExtensoes(const CList<Diretorio, Diretorio&> &listaDiretorio,
			CList<Extensao, Extensao&> &listaExtensao, IProgressoLog progressoLog);
	BOOL excluirExtensao(CList<Extensao, Extensao&> &listaExtensao, int codigo);
	BOOL excluirTodasExtensoes(CList<Extensao, Extensao&> &listaExtensao);
	BOOL criarTabelaExtensoes();
	int indiceExtensao(const CList<Extensao, Extensao&> &lista, const CString &nomeExtensao);
	Extensao* pegaExtensaoPorOrdem(const CList<Extensao, Extensao&> &lista, int ordem);
	Extensao* pegaExtensaoPorCodigo(const CList<Extensao, Extensao&> &lista, int codigo);
	// Extensao pegaExtensaoPorNome(const CList<Extensao, Extensao&> &lista,
		//	const CString &nome, const CString &tipo);
	BOOL ExportarExtensao(TipoExportarExtensao tipo,
						  const CList<Extensao, Extensao&> &listaExtensao);
	void ImportarExtensao(const CString &caminho, CList<Extensao, Extensao&> &listaExtensao);
	void ExtrairExtensao(const CString &caminho, CList<Extensao, Extensao&> &listaExtensao);

};

}
}

#endif // EXTENSAOBO_H
