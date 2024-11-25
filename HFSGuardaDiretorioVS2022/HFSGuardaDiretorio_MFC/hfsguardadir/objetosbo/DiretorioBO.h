#ifndef DIRETORIOBO_H
#define DIRETORIOBO_H

#pragma once

#include "hfsguardadir/objetos/Diretorio.h"
#include "hfsguardadir/objetos/DiretorioOrdem.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/comum/DiretorioXML.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosbo {

class DiretorioBO
{
private:
	DiretorioBO();
	DiretorioBO(DiretorioBO const&);
	DiretorioBO& operator=(DiretorioBO const&);
	static DiretorioBO* instancia;

	CString diretorioToCSV(Diretorio diretorio);
	CString diretorioToXML(Diretorio diretorio);
	CString diretorioToTXT(Diretorio diretorio);
	CString diretorioToHTML(Diretorio diretorio);

public:
	static const CString SQL_CONSULTA_ARQUIVO;
	static DiretorioBO* getInstancia();

	CList<Diretorio, Diretorio&>* carregarDiretorio(const CString &sSQL,
								   IProgressoLog progressoLog);
	CList<Diretorio, Diretorio&>* carregarDiretorio(const CString &sSQL,
									   const CString &sCondicaoTotal,
									   IProgressoLog progressoLog);
	CString removerDrive(const CString &sDiretorio);
	int retCodDirPai(int nAba, const CString &sDiretorio,
								  const CList<Diretorio, Diretorio&> &listaLocal);
	Diretorio atribuiDiretorio(int nAba, int nCodDirRaiz,
			const CString &sNomeDirRaiz, const CString &sDiretorio, BOOL bDiretorio,
			const CList<Diretorio, Diretorio&> &listaLocal, Arquivo arquivo,
			DiretorioOrdem *dirOrdem);
	void atribuiListaDiretorio(int nAba, int nCodDirRaiz,
			const CString &sNomeDirRaiz, const CString &sDiretorio, CList<Diretorio, Diretorio&> *listaLocal,
			Arquivo info, DiretorioOrdem *dirOrdem, IProgressoLog progressoLog);
	void ImportarDiretorio(int nAba, int nCodDirRaiz,
			const CString &sNomeDirRaiz, const CString &sDiretorio, CList<Diretorio, Diretorio&> *listaLocal,
			DiretorioOrdem *dirOrdem, IProgressoLog progressoLog);
	BOOL verificaCodDir(int nAba, const CString &sDiretorio,
			const CList<Diretorio, Diretorio&> &listaLocal);
	int retMaxCodDir(int nAba, const CList<Diretorio, Diretorio&> &listaLocal);
	CString diretorioToSQL(Diretorio diretorio, BOOL bInsert);
	void salvarDiretorio(const CList<Diretorio, Diretorio&> &listaDiretorio,
			IProgressoLog progressoLog);
	BOOL excluirDiretorio(Aba aba, const CString &sCaminho);
	void excluirListaDiretorio(CList<Diretorio, Diretorio&> *listaDiretorio,
			Aba aba, const CString &sCaminho);
	void exportarDiretorio(TipoExportar tipo, Aba aba,
			const CString &sNomeArquivo, IProgressoLog progressoLog);
	BOOL criarTabelaDiretorios();
	int XMLParaDiretorio(const CString &sTexto, int nArquivo,
			DiretorioXML *diretorioXML);
	int importarDiretorioViaXML(Aba aba, const CString &sNomeArquivo,
			const CList<Diretorio, Diretorio&> &listaDirPai,
			IProgressoLog progressoLog);
	BOOL carregarSubDiretorios(const CString &sDiretorio,
			CStringList &listaLocal);
	BOOL carregarArquivos(const CString &sDiretorio,
			CStringList &listaLocal);
	BOOL carregarTodosArquivos(const CString &sDiretorio,
			CStringList &listaLocal);
	CList<Diretorio, Diretorio&>* itensFilhos(const CList<Diretorio, Diretorio&> &lista_pai,
			int aba, int codDirPai, int codigo);

};

}
}

#endif // DIRETORIOBO_H
