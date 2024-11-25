// ---------------------------------------------------------------------------

#ifndef AbaH
#define AbaH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.ComCtrls.hpp>
#include <vector>
#include "Rotinas.h"
// ---------------------------------------------------------------------------
class TAba {
private: // User declarations
public : // User declarations
	int codigo;
	String nome;
	int ordem;

	TAba();
	void carregarAba(std::vector<TAba> *listaAba, TProgressoLog progressoLog);
	int retMaxCodAba(std::vector<TAba> *listaLocal);
	String abaToSQL(TAba aba);
	bool incluirAba(TAba aba);
	bool alterarAba(TAba aba);
	bool excluirAba(TAba aba);
	bool criarTabelaAbas();
	TAba pegaAbaPorOrdem(std::vector<TAba> *lista, int ordem);
    int pegaOrdemPorNomeAba(std::vector<TAba> *lista, String nomeAba);
};

// ---------------------------------------------------------------------------
extern PACKAGE TAba *Aba;
// ---------------------------------------------------------------------------
#endif
