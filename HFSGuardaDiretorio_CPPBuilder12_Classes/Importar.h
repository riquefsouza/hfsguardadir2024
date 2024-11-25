// ---------------------------------------------------------------------------

#ifndef ImportarH
#define ImportarH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.ComCtrls.hpp>
#include <vector>
#include "Diretorio.h"
#include "Extensao.h"

// ---------------------------------------------------------------------------
class TImportar {
private: // User declarations
		public : // User declarations

	int aba;
	int codDirRaiz;
	String rotuloRaiz;
	String nomeDirRaiz;
	String caminho;

	TImportar();
	void CarregarListaDiretorios(TImportar importar, int *nOrdem,
		std::vector<TDiretorio> *listaDiretorio, TStrings* log);
	void ImportacaoCompleta(TImportar importar, int *nOrdem,
		std::vector<TExtensao> *listaExtensao, TStrings* log,
		TProgressoLog progressoLog);

};

// ---------------------------------------------------------------------------
extern PACKAGE TImportar *Importar;
// ---------------------------------------------------------------------------
#endif
