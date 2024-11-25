// ---------------------------------------------------------------------------

#ifndef SQLiteTable3H
#define SQLiteTable3H
// ---------------------------------------------------------------------------
#include "SQLite3Lib.h"
// #include "sqlite3.h"
// #include "TMemoryStream.h"
#include <string>
#include <exception>
#include <vector>
#include <locale>
#include <iostream>
#include <algorithm>
#ifdef WIN32
#include "windows.h"
#endif
#include <System.Classes.hpp>
// ---------------------------------------------------------------------------

enum TTipoColuna {
	SQLITE_INTEGER = 1, SQLITE_FLOAT = 2, SQLITE_TEXT = 3, SQLITE_BLOB = 4,
	SQLITE_NULL = 5
};

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

typedef void THookQuery(std::string);

struct TSQLiteQuery {
	std::string sSQL;
	sqlite3_stmt *stmt;
};

void DisposePointer(void *ponteiro);

#ifdef WIN32
int SystemCollate(void *UserData, int Buf1Len, const void *Buf1, int Buf2Len,
	const void *Buf2);
#endif

class TSQLiteTable;
class TSQLiteUniTable;

class TSQLiteDatabase {
private: // User declarations
	bool bEmTransacao;
	bool bSincronizado;
	THookQuery *OnQuery;

	std::vector<TSQLiteParametro> *listaParametros;
	std::string SQLiteErrorStr(int nSQLiteErrorCode);
protected:
public: // User declarations

	sqlite3 *dbHandle;

	TSQLiteDatabase(const std::string sBanco);
	~TSQLiteDatabase();
	void BindData(sqlite3_stmt *stmt, const TSQLiteParametro bindings[]);
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

	TSQLiteTable* GetTable(const std::string sSQL,
		const TSQLiteParametro bindings[]);
	void ExecSQL(const std::string sSQL, const TSQLiteParametro bindings[]);
	void ExecSQL(TSQLiteQuery query);
	TSQLiteQuery PrepareSQL(const std::string sSQL);
	void BindSQL(TSQLiteQuery query, const int Index, const int Value);
	void BindSQL(TSQLiteQuery query, const int Index, const std::string Value);
	void ReleaseSQL(TSQLiteQuery query);
	TSQLiteUniTable* GetUniTable(const std::string sSQL);
	TSQLiteUniTable* GetUniTable(const std::string sSQL,
		const TSQLiteParametro bindings[]);
	__int64 GetTableValue(const std::string sSQL);
	__int64 GetTableValue(const std::string sSQL,
		const TSQLiteParametro bindings[]);
	std::string GetTableString(const std::string sSQL);
	std::string GetTableString(const std::string sSQL,
		const TSQLiteParametro bindings[]);
	void GetTableStringVetor(const std::string sSQL,
		std::vector<std::string> *Value);
	bool TableExists(std::string TableName);
	__int64 GetLastInsertRowID();
	__int64 GetLastChangedRows();
	void SetTimeout(int value);
	int Backup(TSQLiteDatabase *TargetDB);
	int Backup(TSQLiteDatabase *TargetDB, std::string targetName,
		std::string sourceName);
	std::string Version();
	void AddCustomCollate(std::string name, TCollateXCompare xCompare);
	// adds collate named SYSTEM for correct data sorting by user's locale
	void AddSystemCollate();

	bool IsTransactionOpen();
	// database rows that were changed (or inserted or deleted) by the most recent SQL statement
	bool GetSynchronised();
	void SetSynchronised(bool value);
	void SetOnQuery(THookQuery* query);
	void DoQuery(std::string value);
};

class TSQLiteTable {
private: // User declarations

	unsigned int nLinhaAtual;
	unsigned int nQtdColunas;
	unsigned int nQtdLinhas;

	std::string *vetorNomeColunas;

	TTipoColuna *vetorTipoColunas;

	std::vector<std::vector<TSQLiteColuna> *> *matrizResultados;

public: // User declarations

	TSQLiteTable(TSQLiteDatabase *DB, const std::string sSQL);
	TSQLiteTable(TSQLiteDatabase *DB, const std::string sSQL,
		const TSQLiteParametro bindings[]);
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
	// The property CountResult is used when you execute count(*) queries.
	// It returns 0 if (the result set is empty or the value of the
	// first field as an int.
	int CountResult();
};

class TSQLiteUniTable {
private: // User declarations
	unsigned int nUniLinhaAtual;
	unsigned int nUniQtdColunas;
	std::string *vetorUniNomeColunas;
	bool bEOF;
	sqlite3_stmt *stmt;
	TSQLiteDatabase *localDB;
	std::string sql;
public: // User declarations
	TSQLiteUniTable(TSQLiteDatabase *DB, const std::string sSQL);
	TSQLiteUniTable(TSQLiteDatabase *DB, const std::string sSQL,
		const TSQLiteParametro bindings[]);
	~TSQLiteUniTable();

	std::string Columns(int i);
	unsigned int ColCount();
	unsigned int Row();
	bool Next();
	bool getEOF();
	std::string FieldByName(std::string sNomeCampo);
	int FieldIndex(std::string sNomeCampo);
	std::string Fields(unsigned int i);
	TMemoryStream* FieldAsBlob(unsigned int i);
	std::string FieldAsBlobText(unsigned int i);
	__int64 FieldAsInteger(unsigned int i);
	double FieldAsDouble(unsigned int i);
	std::string FieldAsString(unsigned int i);
	bool FieldIsNull(unsigned int i);

	const void* FieldAsBlobPtr(unsigned int i, int *iNumBytes);

};
// ---------------------------------------------------------------------------
#endif
