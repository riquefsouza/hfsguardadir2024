// ---------------------------------------------------------------------------

#ifndef SQLiteTable3H
#define SQLiteTable3H
// ---------------------------------------------------------------------------
#include "SQLite3Lib.h"
#include <string>
#include <exception>
#include <vector>
#include <locale>
#include <iostream>
#include <algorithm>
#include <System.Classes.hpp>
// ---------------------------------------------------------------------------
struct TSQLiteParametro {
	TTipoColuna tipo;
	std::string nome;

	__int64 integerValor;
	double doubleValor;
	std::string stringValor;
	TMemoryStream *blobValor;
	bool nuloValor;
};

struct TSQLiteColuna {
	int ordem;
	TTipoColuna tipo;
	std::string nome;

	__int64 integerValor;
	double doubleValor;
	std::string stringValor;
	TMemoryStream *blobValor;
	bool nuloValor;
};

void DisposePointer(void *ponteiro);

class TSQLiteTable;

class TSQLiteDatabase {
private: // User declarations
	bool bEmTransacao;
	std::vector<TSQLiteParametro> *listaParametros;
	std::string SQLiteErrorStr(int nSQLiteErrorCode);
public: // User declarations
	sqlite3 *dbHandle;

	TSQLiteDatabase(const std::string sBanco);
	~TSQLiteDatabase();

	void RaiseError(std::string sMensagem, std::string sSQL);
	void BeginTransaction();
	void Commit();
	void Rollback();
	void AddParamInt(std::string nome, __int64 valor);
	void AddParamFloat(std::string nome, double valor);
	void AddParamText(std::string nome, std::string valor);
	void AddParamNull(std::string nome);
	void SetParams(sqlite3_stmt *stmt);
	void ParamsClear();
	void ExecSQL(const std::string sSQL);
	TSQLiteTable* GetTable(const std::string sSQL);
	void UpdateBlob(const std::string sSQL, TStream *BlobData);
	int RowsChanged();

/*
	TSQLiteTable* GetTable(const AnsiString SQL, const TVarRec *Bindings);
	void ExecSQL(const AnsiString SQL, const TVarRec *Bindings);
	void ExecSQL(TSQLiteQuery *Query);
	TSQLiteQuery* PrepareSQL(const AnsiString SQL);
	void BindSQL(TSQLiteQuery *Query, const int Index, const int Value);
	void BindSQL(TSQLiteQuery *Query, const int Index, const String Value);
	void ReleaseSQL(TSQLiteQuery *Query);
	TSQLiteUniTable* GetUniTable(const AnsiString SQL);
	TSQLiteUniTable* GetUniTable(const AnsiString SQL, const TVarRec *Bindings);
	__int64 GetTableValue(const AnsiString SQL);
	__int64 GetTableValue(const AnsiString SQL, const TVarRec *Bindings);
	String GetTableString(const AnsiString SQL);
	String GetTableString(const AnsiString SQL, const TVarRec *Bindings);
	void GetTableStrings(const AnsiString SQL, TStrings *Value);
	bool TableExists(String TableName);
	__int64 GetLastInsertRowID();
	__int64 GetLastChangedRows();
	void SetTimeout(int Value);
	int Backup(TSQLiteDatabase *TargetDB);
	int Backup(TSQLiteDatabase *TargetDB, AnsiString targetName,
		AnsiString sourceName);
	String Version();
	void AddCustomCollate(String name, TCollateXCompare *xCompare);
	// adds collate named SYSTEM for (correct data sorting by user"s locale
	void AddSystemCollate();
	void ParamsClear();
	void AddParamInt(String name, __int64 value);
	void AddParamFloat(String name, double value);
	void AddParamText(String name, String value);
	void AddParamNull(String name);
	TSQLiteDB getDB();
	bool IsTransactionOpen();
	// database rows that were changed (or inserted or deleted) by the most recent SQL statement
	bool getSynchronised();
	void setSynchronised(bool value);
	// THookQuery *getOnQuery();
	// void setOnQuery(THookQuery *query);

	void RaiseError(String s, String SQL);
	void DoQuery(String value);
	void SetParams(TSQLiteStmt *Stmt);
	void BindData(TSQLiteStmt *Stmt, const TVarRec *Bindings);
*/
};

class TSQLiteTable {
private: // User declarations
	unsigned int nLinhaAtual;
	unsigned int nQtdColunas;
	unsigned int nQtdLinhas;
	std::string *vetorNomeColunas;
	TTipoColuna *vetorTipoColunas;
	std::vector< std::vector<TSQLiteColuna>* > *matrizResultados;
public: // User declarations

	TSQLiteTable(TSQLiteDatabase *DB, const std::string sSQL);
	/*
	TSQLiteTable(TSQLiteDatabase *DB, const std::string SQL,
		const TVarRec *Bindings);
	*/
	~TSQLiteTable();

	std::string Columns(int i);
	unsigned int Count();
	unsigned int ColCount();
	unsigned int Row();
	bool Next();
	bool Previous();
	bool MoveFirst();
	bool MoveLast();
	bool MoveTo(unsigned int posicao);
	bool getEOF();
	bool getBOF();
	std::string FieldByName(std::string sNomeCampo);
	int FieldIndex(std::string sNomeCampo);
	std::string Fields(unsigned int i);
	TMemoryStream* FieldAsBlob(unsigned int i);
	std::string FieldAsBlobText(unsigned int i);
	__int64 FieldAsInteger(unsigned int i);
	double FieldAsDouble(unsigned int i);
	std::string FieldAsString(unsigned int i);
	bool FieldIsNull(unsigned int i);
};
// ---------------------------------------------------------------------------
#endif
