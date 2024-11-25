// ---------------------------------------------------------------------------

#ifndef ArquivoH
#define ArquivoH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>

// ---------------------------------------------------------------------------
class TArquivo {
private: // User declarations
		public : // User declarations

	String nome;
	__int64 tamanho;
	TDateTime modificado;
	int natributos;

	TArquivo();
};

// ---------------------------------------------------------------------------
extern PACKAGE TArquivo *Arquivo;
// ---------------------------------------------------------------------------
#endif
