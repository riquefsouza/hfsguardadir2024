// ---------------------------------------------------------------------------

#pragma hdrstop

#include "Importar.h"
#include <System.SysUtils.hpp>
// ---------------------------------------------------------------------------
#pragma package(smart_init)
TImportar *Importar;

// ---------------------------------------------------------------------------
TImportar::TImportar() {
}

// ---------------------------------------------------------------------------
void TImportar::CarregarListaDiretorios(TImportar importar, int *nOrdem,
	std::vector<TDiretorio> *listaDiretorio, TStrings* log) {
	TArquivo arquivo;
	TDiretorio diretorio;

	// arquivo = new TArquivo();
	arquivo.nome = importar.rotuloRaiz;
	arquivo.tamanho = 0;
	arquivo.modificado = Now();
	arquivo.natributos = faDirectory;

	diretorio = Diretorio->atribuiDiretorio(importar.aba, importar.codDirRaiz,
		importar.nomeDirRaiz, "", true, listaDiretorio, arquivo, nOrdem);

	listaDiretorio->push_back(diretorio);
	log->Append(importar.caminho);

	Diretorio->ImportarDiretorio(importar.aba, importar.codDirRaiz,
		importar.nomeDirRaiz, importar.caminho, listaDiretorio, nOrdem, log);

}

// ---------------------------------------------------------------------------
void TImportar::ImportacaoCompleta(TImportar importar, int *nOrdem,
	std::vector<TExtensao> *listaExtensao, TStrings* log,
	TProgressoLog progressoLog) {
	std::vector<TDiretorio> *listaDiretorio;

	listaDiretorio = new std::vector<TDiretorio>();
	try {
		CarregarListaDiretorios(importar, nOrdem, listaDiretorio, log);

		if (TOSVersion::Platform == TOSVersion::pfWindows) {
			Extensao->salvarExtensoes(listaDiretorio, listaExtensao, log,
			progressoLog);
		}
		Diretorio->salvarDiretorio(listaDiretorio, log, progressoLog);

	}
	__finally {
		listaDiretorio->clear();
		delete listaDiretorio;
	}

}
// ---------------------------------------------------------------------------
