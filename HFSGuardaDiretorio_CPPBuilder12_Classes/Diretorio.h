// ---------------------------------------------------------------------------

#ifndef DiretorioH
#define DiretorioH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Data.SqlExpr.hpp>
#include <vector>
#include "Arquivo.h"
#include "Aba.h"
// ---------------------------------------------------------------------------
const String SQL_CONSULTA_ARQUIVO = "select aba, cod, ordem, coddirpai, nome, " \
 "tam, tipo, modificado, atributos, caminho, nomeaba, nomepai, caminhopai " \
 "from consultaarquivo";

enum TTipoExportar {
	teTXT, teCSV, teHTML, teXML, teSQL
};

struct TTipo {
	char codigo;
	String nome;
};

class TDiretorio : public TArquivo {
private: // User declarations
		public : // User declarations

	TAba aba;
	int codigo;
	int ordem;
	int codDirPai;
	TTipo tipo;
	String atributos;
	String caminho;
	String nomePai;
	String caminhoPai;
	String tamanhoFormatado;
	String modificadoFormatado;
	String caminhoOriginal;

	TDiretorio();
	// void carregarDiretorio(String sSQL,
	// std::vector<TDiretorio> *listaDiretorio, TProgressoLog progressoLog);
	void carregarDiretorio(TSQLQuery* consultaDir,
		std::vector<TDiretorio> *listaDiretorio, TProgressoLog progressoLog);
	TDiretorio atribuiDiretorio(int nAba, int nCodDirRaiz, String sNomeDirRaiz,
		String sDiretorio, bool bDiretorio, std::vector<TDiretorio> *listaLocal,
		TArquivo arquivo, int *nOrdem);
	void atribuiListaDiretorio(int nAba, int nCodDirRaiz, String sNomeDirRaiz,
		String sDiretorio, std::vector<TDiretorio> *listaLocal,
		TSearchRec SearchRec, int *nOrdem, TStrings *log);
	void ImportarDiretorio(int nAba, int nCodDirRaiz, String sNomeDirRaiz,
		String sDiretorio, std::vector<TDiretorio> *listaLocal, int *nOrdem,
		TStrings *log);
	bool verificaCodDir(int nAba, String sDiretorio,
		std::vector<TDiretorio> *listaLocal);
	int retMaxCodDir(int nAba, std::vector<TDiretorio> *listaLocal);
	String diretorioToSQL(TDiretorio diretorio, bool bInsert);
	void incluirDiretorio(TDiretorio diretorio);
	void salvarDiretorio(std::vector<TDiretorio> *listaDiretorio, TStrings* log,
		TProgressoLog progressoLog);
	bool excluirDiretorio(TAba aba, String sCaminho);
	void excluirListaDiretorio(std::vector<TDiretorio> *listaDiretorio,
		TAba aba, String sCaminho);
	String diretorioToCSV(TDiretorio diretorio);
	String diretorioToXML(TDiretorio diretorio);
	String diretorioToTXT(TDiretorio diretorio);
	String diretorioToHTML(TDiretorio diretorio);
	void exportarDiretorio(TTipoExportar tipo, TAba aba, String sNomeArquivo,
		TProgressoLog progressoLog);
	bool criarTabelaDiretorios();
	int importarDiretorioViaXML(TAba aba, String sNomeArquivo,
		std::vector<TDiretorio> *listaDirPai, TStrings* log,
		TProgressoLog progressoLog);
	int XMLParaDiretorio(String sTexto, int nArquivo, TDiretorio **diretorio);
	bool carregarSubDiretorios(String sDiretorio, TStringList* listaLocal);
	bool carregarArquivos(String sDiretorio, TStringList* listaLocal);
	String MontaTamanho(__int64 nTam);
	String MontaTamanhoBig(Extended nTam);
	std::vector<TDiretorio> *itensFilhos(std::vector<TDiretorio> *lista_pai,
		int aba, int codDirPai, int codigo);
	String arquivoAtributos(int nAtributos);
	int retCodDirPai(int nAba, String sDiretorio,
		std::vector<TDiretorio> *listaLocal);
	TArquivo searchRecToArquivo(TSearchRec SearchRec);
	String removerDrive(String sDiretorio);
	bool carregarTodosArquivos(String sDiretorio, TStringList* listaLocal);

};

// ---------------------------------------------------------------------------
extern PACKAGE TDiretorio *Diretorio;
// ---------------------------------------------------------------------------
#endif
