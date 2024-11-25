// ---------------------------------------------------------------------------

#ifndef ExtensaoH
#define ExtensaoH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include <vector>
#include "Diretorio.h"
#include "Rotinas.h"

// ---------------------------------------------------------------------------
class TExtensao {
private: // User declarations
		public : // User declarations

	int codigo;
	String nome;
	int ordem;

	Graphics::TBitmap *bmp16;
	Graphics::TBitmap *bmp32;

	TExtensao();
	void carregarExtensao(std::vector<TExtensao> *listaExtensao,
		TProgressoLog progressoLog);
	bool existeExtensao(String sExtensao, std::vector<TExtensao> *listaLocal);
	int retMaxCodExtensao(std::vector<TExtensao> *listaLocal);
	bool SalvarExtensao(std::vector<TExtensao> *listaExtensao,
		String sNomeDiretorio, String sCaminhoOriginal, TStrings* log);
	void salvarExtensoes(std::vector<TDiretorio> *listaDiretorio,
		std::vector<TExtensao> *listaExtensao, TStrings* log,
		TProgressoLog progressoLog);
	//String extensaoToSQL(TExtensao extensao, bool bInsert);
	bool excluirExtensao(std::vector<TExtensao> *listaExtensao, int codigo);
	bool excluirTodasExtensoes(std::vector<TExtensao> *listaExtensao);
	bool criarTabelaExtensoes();
	void incluirExtensao(TExtensao extensao);
	void carregarExtensoes(std::vector<TExtensao> *lista,
		TImageList* listaImg16, TImageList* listaImg32);
	int indiceExtensao(std::vector<TExtensao> *lista, String nomeExtensao);
	void ExportarExtensao(TTipoExportarExtensao tipo,
		std::vector<TExtensao> *listaExtensao);
	TExtensao pegaExtensaoPorOrdem(std::vector<TExtensao> *lista, int ordem);
	void ImportarExtensao(String caminho,
		std::vector<TExtensao> *listaExtensao);
	void ExtrairExtensao(String caminho, std::vector<TExtensao> *listaExtensao);

};

// ---------------------------------------------------------------------------
extern PACKAGE TExtensao *Extensao;
// ---------------------------------------------------------------------------
#endif
