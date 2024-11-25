// ---------------------------------------------------------------------------

#pragma hdrstop

#include "SQLiteTable3.h"
#include "SQLite3Lib.h"
// #include "sqlite3.h"
#include "Funcoes.h"
#include <sstream>
#include <cstdlib>
#include <cwchar>
#include <stdexcept>
// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
void DisposePointer(void *ponteiro) {
	if (ponteiro != NULL) {
		sqlite3_free(ponteiro);
		ponteiro = NULL;
	}
}
// ---------------------------------------------------------------------------
#ifdef WIN32

int SystemCollate(void *UserData, int Buf1Len, const void *Buf1, int Buf2Len,
	const void *Buf2) {
	return CompareStringW(LOCALE_USER_DEFAULT, 0, (PWideChar) Buf1, Buf1Len,
		(PWideChar) Buf2, Buf2Len) - 2;
}
#endif

// ---------------------------------------------------------------------------
TSQLiteDatabase::TSQLiteDatabase(const std::string sBanco) {
	std::stringstream ex;
	int resultado;
	const char *msgErro = NULL;

	this->bEmTransacao = false;
	this->listaParametros = new std::vector<TSQLiteParametro>();
	this->OnQuery = NULL;

	resultado = sqlite3_open(sBanco.c_str(), &dbHandle);

	if (resultado != SQLITE_OK) {
		if (dbHandle != NULL) {
			msgErro = sqlite3_errmsg(dbHandle);
			ex << "Falha ao abrir banco de dados '" << sBanco << "':" <<
				msgErro;
			throw std::logic_error(ex.str().c_str());
		}
		else {
			ex << "Falha ao abrir banco de dados '" << sBanco <<
				"': erro desconhecido";
			throw std::logic_error(ex.str().c_str());
		}
	}

	if (msgErro != NULL) {
		sqlite3_free((void*)msgErro);
	}

}

// ---------------------------------------------------------------------------
TSQLiteDatabase::~TSQLiteDatabase() {
	if (bEmTransacao) {
		this->Rollback(); // assume rollback
	}
	if (dbHandle != NULL) {
		sqlite3_close(dbHandle);
	}
	ParamsClear();
	delete this->listaParametros;
}

// ---------------------------------------------------------------------------
void TSQLiteDatabase::BeginTransaction() {
	if (!bEmTransacao) {
		this->ExecSQL("BEGIN TRANSACTION");
		this->bEmTransacao = true;
	}
	else
		throw std::logic_error("Transação já aberta");
}

// ---------------------------------------------------------------------------
void TSQLiteDatabase::Commit() {
	this->ExecSQL("COMMIT");
	this->bEmTransacao = false;
}

// ---------------------------------------------------------------------------
void TSQLiteDatabase::Rollback() {
	this->ExecSQL("ROLLBACK");
	this->bEmTransacao = false;
}

// ---------------------------------------------------------------------------
void TSQLiteDatabase::AddParamInt(std::string nome, __int64 valor) {
	TSQLiteParametro parametro;

	parametro.nome = nome;
	parametro.tipo = SQLITE_INTEGER;
	parametro.integerValor = valor;
	parametro.nuloValor = false;
	this->listaParametros->push_back(parametro);
}

// ---------------------------------------------------------------------------
void TSQLiteDatabase::AddParamFloat(std::string nome, double valor) {
	TSQLiteParametro parametro;

	parametro.nome = nome;
	parametro.tipo = SQLITE_FLOAT;
	parametro.doubleValor = valor;
	parametro.nuloValor = false;
	this->listaParametros->push_back(parametro);
}

// ---------------------------------------------------------------------------
void TSQLiteDatabase::AddParamText(std::string nome, std::string valor) {
	TSQLiteParametro parametro;

	parametro.nome = nome;
	parametro.tipo = SQLITE_TEXT;
	parametro.stringValor = valor;
	parametro.nuloValor = false;
	this->listaParametros->push_back(parametro);
}

// ---------------------------------------------------------------------------
void TSQLiteDatabase::AddParamNull(std::string nome) {
	TSQLiteParametro parametro;

	parametro.nome = nome;
	parametro.tipo = SQLITE_NULL;
	parametro.nuloValor = true;
	this->listaParametros->push_back(parametro);
}

// ---------------------------------------------------------------------------
void TSQLiteDatabase::SetParams(sqlite3_stmt *stmt) {
	TSQLiteParametro parametro;

	if (!this->listaParametros->empty()) {
		for (unsigned int i = 0; i < this->listaParametros->size(); i++) {
			parametro = this->listaParametros->at(i);

			i = sqlite3_bind_parameter_index(stmt, parametro.nome.c_str());
			if (i > 0) {
				switch (parametro.tipo) {
				case SQLITE_INTEGER:
					sqlite3_bind_int64(stmt, i, parametro.integerValor);
					break;
				case SQLITE_FLOAT:
					sqlite3_bind_double(stmt, i, parametro.doubleValor);
					break;
				case SQLITE_TEXT:
					sqlite3_bind_text(stmt, i, parametro.stringValor.c_str(),
						parametro.stringValor.length(), SQLITE_TRANSIENT);
					break;
				case SQLITE_NULL:
					sqlite3_bind_null(stmt, i);
					break;
				case SQLITE_BLOB: {
						// sqlite3_bind_blob(stmt, i, , );
					}
				}
			}
		}
	}

	ParamsClear();
}

// ---------------------------------------------------------------------------
void TSQLiteDatabase::ParamsClear() {
	this->listaParametros->clear();
}

// ---------------------------------------------------------------------------
void TSQLiteDatabase::ExecSQL(const std::string sSQL) {
	ExecSQL(sSQL, NULL);
}

// ---------------------------------------------------------------------------
void TSQLiteDatabase::ExecSQL(const std::string sSQL,
	const TSQLiteParametro bindings[]) {
	sqlite3_stmt *stmt;
	const char *NextSQLStatement;
	int nResultadoPasso;

	if (sqlite3_prepare_v2(dbHandle, sSQL.c_str(), -1, &stmt,
		&NextSQLStatement) != SQLITE_OK) {
		RaiseError("Erro executando SQL", sSQL);
	}

	if (stmt == NULL) {
		RaiseError("Não consegui preparar o SQL", sSQL);
	}

	DoQuery(sSQL);
	SetParams(stmt);
	if (bindings != NULL) {
		BindData(stmt, bindings);
	}

	nResultadoPasso = sqlite3_step(stmt);

	if (nResultadoPasso != SQLITE_DONE) {
		sqlite3_reset(stmt);
		RaiseError("Erro executando o procedimento do SQL", sSQL);
	}

	if (stmt != NULL) {
		sqlite3_finalize(stmt);
	}
}

// ---------------------------------------------------------------------------
TSQLiteTable* TSQLiteDatabase::GetTable(const std::string sSQL) {
	return new TSQLiteTable(this, sSQL);
}

// ---------------------------------------------------------------------------
TSQLiteTable* TSQLiteDatabase::GetTable(const std::string sSQL,
	const TSQLiteParametro bindings[]) {
	return new TSQLiteTable(this, sSQL, bindings);
}

// ---------------------------------------------------------------------------
void TSQLiteDatabase::UpdateBlob(const std::string sSQL, TStream *BlobData) {
	std::stringstream ex;
	int nTamanho;
	const char *msgErro = NULL;
	sqlite3_stmt *stmt;
	const char *NextSQLStatement;
	int nResultadoPasso;
	int nResultadoBind;
	void *ponteiro;

	// expects SQL of the form "UPDATE MYTABLE SET MYFIELD = ? WHERE MYKEY = 1"
	if (cppPos("?", sSQL) == 0) {
		RaiseError("O SQL deve conter um parâmetro de interrogação", sSQL);
	}

	if (sqlite3_prepare_v2(dbHandle, sSQL.c_str(), -1, &stmt,
		&NextSQLStatement) != SQLITE_OK) {
		RaiseError("Não consegui preparar o SQL", sSQL);
	}

	if (stmt == NULL) {
		RaiseError("Não consegui preparar o SQL", sSQL);
	}

	DoQuery(sSQL);

	// now bind the blob data
	nTamanho = BlobData->Size;

	ponteiro = GetMemory(nTamanho);

	if (ponteiro == NULL) {
		ex << "Erro ao alocar memória para salvar o BLOB: " << sSQL;
		throw std::logic_error(ex.str().c_str());
	}

	BlobData->Position = 0;
	BlobData->Read(&ponteiro, nTamanho);

	nResultadoBind = sqlite3_bind_blob(stmt, 1, ponteiro, nTamanho,
		*DisposePointer);

	if (nResultadoBind != SQLITE_OK) {
		RaiseError("Erro ao ligar(binding) BLOB para o banco de dados: ", sSQL);
	}

	nResultadoPasso = sqlite3_step(stmt);

	if (nResultadoPasso != SQLITE_DONE) {
		sqlite3_reset(stmt);
		RaiseError("Erro executando procedimento SQL: ", sSQL);
	}

	if (stmt != NULL) {
		sqlite3_finalize(stmt);
	}

	if (msgErro != NULL) {
		sqlite3_free((void*)msgErro);
	}
}

// ---------------------------------------------------------------------------
int TSQLiteDatabase::RowsChanged() {
	return sqlite3_changes(this->dbHandle);
}

// ---------------------------------------------------------------------------
void TSQLiteDatabase::RaiseError(std::string sMensagem, std::string sSQL) {
	std::stringstream ex;
	const char *msgErro = NULL;
	int retorno;

	retorno = sqlite3_errcode(this->dbHandle);
	if (retorno != SQLITE_OK) {
		msgErro = sqlite3_errmsg(this->dbHandle);
	}
	if (msgErro != NULL) {
		ex << sMensagem << ". Erro [" << retorno << "]: " << SQLiteErrorStr
			(retorno) << ". '" << sSQL << "': " << msgErro;
		throw std::logic_error(ex.str().c_str());
	}
	else {
		ex << sMensagem << ". '" << sSQL << "': Sem mensagem";
		throw std::logic_error(ex.str().c_str());
	}
}

// ---------------------------------------------------------------------------
std::string TSQLiteDatabase::SQLiteErrorStr(int nSQLiteErrorCode) {
	std::stringstream ex;

	switch (nSQLiteErrorCode) {
	case SQLITE_OK:
		return "Successful result";
	case SQLITE_ERROR:
		return "SQL error or missing database";
	case SQLITE_INTERNAL:
		return "An internal logic error in SQLite";
	case SQLITE_PERM:
		return "Access permission denied";
	case SQLITE_ABORT:
		return "Callback routine requested an abort";
	case SQLITE_BUSY:
		return "The database file is locked";
	case SQLITE_LOCKED:
		return "A table in the database is locked";
	case SQLITE_NOMEM:
		return "A malloc() failed";
	case SQLITE_READONLY:
		return "Attempt to write a readonly database";
	case SQLITE_INTERRUPT:
		return "Operation terminated by sqlite3_interrupt()";
	case SQLITE_IOERR:
		return "Some kind of disk I/O error occurred";
	case SQLITE_CORRUPT:
		return "The database disk image is malformed";
	case SQLITE_NOTFOUND:
		return "(Internal Only) Table or record not found";
	case SQLITE_FULL:
		return "Insertion failed because database is full";
	case SQLITE_CANTOPEN:
		return "Unable to open the database file";
	case SQLITE_PROTOCOL:
		return "Database lock protocol error";
	case SQLITE_EMPTY:
		return "Database is empty";
	case SQLITE_SCHEMA:
		return "The database schema changed";
	case SQLITE_TOOBIG:
		return "Too much data for one row of a table";
	case SQLITE_CONSTRAINT:
		return "Abort due to contraint violation";
	case SQLITE_MISMATCH:
		return "Data type mismatch";
	case SQLITE_MISUSE:
		return "Library used incorrectly";
	case SQLITE_NOLFS:
		return "Uses OS features not supported on host";
	case SQLITE_AUTH:
		return "Authorization denied";
	case SQLITE_FORMAT:
		return "Auxiliary database format error";
	case SQLITE_RANGE:
		return "2nd parameter to sqlite3_bind out of range";
	case SQLITE_NOTADB:
		return "File opened that is not a database file";
	case SQLITE_ROW:
		return "sqlite3_step() has another row ready";
	case SQLITE_DONE:
		return "sqlite3_step() has finished executing";
	default: {
			ex << "Unknown SQLite Error Code '" << nSQLiteErrorCode << "'";
			return ex.str();
		}
	}
}

// ---------------------------------------------------------------------------
void TSQLiteDatabase::BindData(sqlite3_stmt *stmt,
	const TSQLiteParametro bindings[]) {
	std::stringstream ex;
	TStream *BlobData;
	void *ponteiro;
	int nTamanho;
	unsigned int nTamParams = sizeof(*bindings) / sizeof(bindings[0]);

	for (unsigned int i = 0; i < nTamParams; i++) {
		switch (bindings[i].tipo) {
		case SQLITE_INTEGER: {
				if (sqlite3_bind_int64(stmt, i + 1, bindings[i].integerValor)
					!= SQLITE_OK)
					RaiseError("Não consegui fazer bind de int64", "BindData");
			} break;
		case SQLITE_FLOAT: {
				if (sqlite3_bind_double(stmt, i + 1, bindings[i].doubleValor)
					!= SQLITE_OK)
					RaiseError("Não consegui fazer bind de float", "BindData");
			} break;
		case SQLITE_TEXT: {
				if (sqlite3_bind_text(stmt, i + 1,
					bindings[i].stringValor.c_str(),
					bindings[i].stringValor.length(),
					SQLITE_STATIC) != SQLITE_OK)
					RaiseError("Não consegui fazer bind de texto", "BindData");
			} break;
		case SQLITE_BLOB: {
				BlobData = (TStream*)bindings[i].blobValor;

				nTamanho = BlobData->Size;
				ponteiro = GetMemory(nTamanho);

				if (ponteiro == NULL) {
					throw std::logic_error
						("Erro ao alocar memória para salvar o BLOB: ");
				}

				BlobData->Position = 0;
				BlobData->Read(&ponteiro, nTamanho);

				if (sqlite3_bind_blob(stmt, i + 1, ponteiro, nTamanho,
					*DisposePointer) != SQLITE_OK)
					RaiseError("Não consegui fazer bind de BLOB", "BindData");
			}
		case SQLITE_NULL: {
				if (bindings[i].nuloValor) {
					if (sqlite3_bind_null(stmt, i + 1) != SQLITE_OK)
						RaiseError("Não consegui fazer bind de NULL",
					"BindData");
				}
			}
		}
	}

}

// ---------------------------------------------------------------------------
void TSQLiteDatabase::DoQuery(std::string sSQL) {
	if (this->OnQuery != NULL) {
		this->OnQuery(sSQL);
	}
}

// ---------------------------------------------------------------------------
void TSQLiteDatabase::ExecSQL(TSQLiteQuery query) {
	int nResultadoPasso;

	if (query.stmt != NULL) {
		nResultadoPasso = sqlite3_step(query.stmt);

		if (nResultadoPasso != SQLITE_DONE) {
			sqlite3_reset(query.stmt);
			RaiseError("Error executing prepared SQL statement", query.sSQL);
		}
		sqlite3_reset(query.stmt);
	}
}

// ---------------------------------------------------------------------------
TSQLiteQuery TSQLiteDatabase::PrepareSQL(const std::string sSQL) {
	sqlite3_stmt *stmt;
	const char *NextSQLStatement;
	TSQLiteQuery resultado;

	resultado.sSQL = sSQL;
	resultado.stmt = NULL;

	if (sqlite3_prepare(dbHandle, sSQL.c_str(), -1, &stmt, &NextSQLStatement)
		!= SQLITE_OK)
		RaiseError("Não consegui preparar o SQL", sSQL);
	else
		resultado.stmt = stmt;

	if (resultado.stmt == NULL)
		RaiseError("Não consegui preparar o SQL", sSQL);

	DoQuery(sSQL);

	return resultado;
}

// ---------------------------------------------------------------------------
void TSQLiteDatabase::BindSQL(TSQLiteQuery query, const int Index,
	const int Value) {
	if (query.stmt != NULL)
		sqlite3_bind_int(query.stmt, Index, Value);
	else
		RaiseError(
		"Não consegui fazer o bind de int para preparar o procedimento SQL",
		query.sSQL);
}

// ---------------------------------------------------------------------------
void TSQLiteDatabase::BindSQL(TSQLiteQuery query, const int Index,
	const std::string Value) {
	if (query.stmt != NULL)
		sqlite3_bind_text(query.stmt, Index, Value.c_str(), Value.length(),
		SQLITE_STATIC);
	else
		RaiseError(
		"Não consegui fazer o bind de String para preparar o procedimento SQL",
		query.sSQL);
}

// ---------------------------------------------------------------------------
void TSQLiteDatabase::ReleaseSQL(TSQLiteQuery query) {
	if (query.stmt != NULL) {
		sqlite3_finalize(query.stmt);
		query.stmt = NULL;
	}
	else
		RaiseError("Não consegui liberar o procedimento SQL", query.sSQL);
}

// ---------------------------------------------------------------------------
TSQLiteUniTable* TSQLiteDatabase::GetUniTable(const std::string sSQL) {
	return new TSQLiteUniTable(this, sSQL);
}

// ---------------------------------------------------------------------------
TSQLiteUniTable* TSQLiteDatabase::GetUniTable(const std::string sSQL,
	const TSQLiteParametro bindings[]) {
	return new TSQLiteUniTable(this, sSQL, bindings);
}

// ---------------------------------------------------------------------------
__int64 TSQLiteDatabase::GetTableValue(const std::string sSQL) {
	return GetTableValue(sSQL, NULL);
}

// ---------------------------------------------------------------------------
__int64 TSQLiteDatabase::GetTableValue(const std::string sSQL,
	const TSQLiteParametro bindings[]) {
	__int64 resultado = 0;
	TSQLiteUniTable *tabela;

	tabela = this->GetUniTable(sSQL, bindings);

	if (!tabela->getEOF()) {
		resultado = tabela->FieldAsInteger(0);
	}

	delete tabela;

	return resultado;
}

// ---------------------------------------------------------------------------
std::string TSQLiteDatabase::GetTableString(const std::string sSQL) {
	return this->GetTableString(sSQL, NULL);
}

// ---------------------------------------------------------------------------
std::string TSQLiteDatabase::GetTableString(const std::string sSQL,
	const TSQLiteParametro bindings[]) {
	std::string resultado = "";
	TSQLiteUniTable *tabela;

	tabela = this->GetUniTable(sSQL, bindings);

	if (!tabela->getEOF()) {
		resultado = tabela->FieldAsString(0);
	}

	delete tabela;

	return resultado;
}

// ---------------------------------------------------------------------------
void TSQLiteDatabase::GetTableStringVetor(const std::string sSQL,
	std::vector<std::string> *Value) {
	TSQLiteUniTable *tabela;

	Value->clear();
	tabela = this->GetUniTable(sSQL);

	while (!tabela->getEOF()) {
		Value->push_back(tabela->FieldAsString(0));
		tabela->Next();
	}

	delete tabela;
}

// ---------------------------------------------------------------------------
bool TSQLiteDatabase::TableExists(std::string TableName) {
	std::string sSQL;
	TSQLiteTable *tabela;
	bool resultado = false;

	// returns true if (table exists in the database
	sSQL = "select [sql] from sqlite_master where [type] = 'table' and lower(name) = '"
		+ cppLowerCase(TableName) + "' ";
	tabela = this->GetTable(sSQL);
	resultado = (tabela->Count() > 0);

	delete tabela;

	return resultado;
}

// ---------------------------------------------------------------------------
__int64 TSQLiteDatabase::GetLastInsertRowID() {
	return sqlite3_last_insert_rowid(dbHandle);
}

// ---------------------------------------------------------------------------
__int64 TSQLiteDatabase::GetLastChangedRows() {
	return sqlite3_total_changes(dbHandle);
}

// ---------------------------------------------------------------------------
void TSQLiteDatabase::SetTimeout(int value) {
	sqlite3_busy_timeout(dbHandle, value);
}

// ---------------------------------------------------------------------------
int TSQLiteDatabase::Backup(TSQLiteDatabase *TargetDB) {
	return this->Backup(TargetDB, "main", "main");
}

// ---------------------------------------------------------------------------
int TSQLiteDatabase::Backup(TSQLiteDatabase *TargetDB, std::string targetName,
	std::string sourceName) {
	int retorno = -1;
	sqlite3_backup *pBackup;

	pBackup = sqlite3_backup_init(TargetDB->dbHandle, targetName.c_str(),
		this->dbHandle, sourceName.c_str());

	if (pBackup == NULL) {
		throw std::logic_error("Não consegui inicializar o backup");
	}
	else {
		retorno = sqlite3_backup_step(pBackup, -1); // copies entire db
		sqlite3_backup_finish(pBackup);
	}
	return retorno;
}

// ---------------------------------------------------------------------------
std::string TSQLiteDatabase::Version() {
	return sqlite3_libversion();
}

// ---------------------------------------------------------------------------
void TSQLiteDatabase::AddCustomCollate(std::string name,
	TCollateXCompare xCompare) {
	sqlite3_create_collation(dbHandle, name.c_str(), SQLITE_UTF8, NULL,
		xCompare);
}

// ---------------------------------------------------------------------------
void TSQLiteDatabase::AddSystemCollate() {
#ifdef WIN32
	sqlite3_create_collation(dbHandle, "SYSTEM", SQLITE_UTF16LE, NULL,
		*SystemCollate);
#endif
}
// ---------------------------------------------------------------------------

bool TSQLiteDatabase::IsTransactionOpen() {
	return this->bEmTransacao;
}

// ---------------------------------------------------------------------------
bool TSQLiteDatabase::GetSynchronised() {
	return this->bSincronizado;
}

// ---------------------------------------------------------------------------
void TSQLiteDatabase::SetSynchronised(bool value) {
	if (value != this->bSincronizado) {
		if (value)
			this->ExecSQL("PRAGMA synchronous = ON;");
		else
			this->ExecSQL("PRAGMA synchronous = OFF;");
		this->bSincronizado = value;
	}
}

// ---------------------------------------------------------------------------
void TSQLiteDatabase::SetOnQuery(THookQuery* query) {
	this->OnQuery = query;
}

// ------------------------------------------------------------------------------
// TSQLiteTable
// ---------------------------------------------------------------------------
TSQLiteTable::TSQLiteTable(TSQLiteDatabase *DB, const std::string sSQL) {
	new TSQLiteTable(DB, sSQL, NULL);
}

// ------------------------------------------------------------------------------
TSQLiteTable::TSQLiteTable(TSQLiteDatabase *DB, const std::string sSQL,
	const TSQLiteParametro bindings[]) {
	std::stringstream ex;
	sqlite3_stmt *stmt;
	const char *NextSQLStatement;
	int nResultadoPasso;
	TTipoColuna tipoColuna;
	int tipoColunaAtual, nQtdBytes;
	const char *tipoColunaDeclarada;
	std::string sTipoColunaDeclarada;
	TSQLiteColuna coluna;
	TMemoryStream *blobValor;
	const void *ponteiro;
	std::vector<TSQLiteColuna> *vetorColunas;

	this->nQtdLinhas = 0;
	this->nQtdColunas = 0;

	this->matrizResultados = new std::vector<std::vector<TSQLiteColuna> *>();

	if (sqlite3_prepare_v2(DB->dbHandle, sSQL.c_str(), -1, &stmt,
		&NextSQLStatement) != SQLITE_OK) {
		DB->RaiseError("Não consegui preparar o SQL", sSQL);
	}
	if (stmt == NULL) {
		DB->RaiseError("Não consegui preparar o SQL", sSQL);
	}

	DB->DoQuery(sSQL);
	DB->SetParams(stmt);
	if (bindings != NULL) {
		DB->BindData(stmt, bindings);
	}

	nResultadoPasso = sqlite3_step(stmt);
	while (nResultadoPasso != SQLITE_DONE) {
		switch (nResultadoPasso) {
		case SQLITE_ROW: {

				this->nQtdLinhas++;

				if (this->nQtdLinhas == 1) {
					this->nQtdColunas = sqlite3_column_count(stmt);

					this->vetorNomeColunas = new std::string[this->nQtdColunas];
					this->vetorTipoColunas = new TTipoColuna[this->nQtdColunas];

					for (unsigned int i = 0; i < this->nQtdColunas; i++) {
						this->vetorNomeColunas[i] =
							sqlite3_column_name(stmt, i);
					}

					for (unsigned int i = 0; i < this->nQtdColunas; i++) {
						tipoColunaDeclarada = sqlite3_column_decltype(stmt, i);
						sTipoColunaDeclarada = tipoColunaDeclarada;
						sTipoColunaDeclarada =
							cppUpperCase(sTipoColunaDeclarada);

						if (tipoColunaDeclarada == NULL) {
							tipoColuna =
								(TTipoColuna)sqlite3_column_type(stmt, i);
						}
						else if ((sTipoColunaDeclarada == "INTEGER") ||
							(sTipoColunaDeclarada == "BOOLEAN"))
							tipoColuna = SQLITE_INTEGER;
						else if ((sTipoColunaDeclarada == "NUMERIC") ||
							(sTipoColunaDeclarada == "FLOAT") ||
							(sTipoColunaDeclarada == "DOUBLE") ||
							(sTipoColunaDeclarada == "REAL"))
							tipoColuna = SQLITE_FLOAT;
						else if (sTipoColunaDeclarada == "BLOB")
							tipoColuna = SQLITE_BLOB;
						else
							tipoColuna = SQLITE_TEXT;
						this->vetorTipoColunas[i] = tipoColuna;
					}
				}

				vetorColunas = new std::vector<TSQLiteColuna>();
				for (unsigned int nColuna = 0; nColuna < this->nQtdColunas;
				nColuna++) {

					tipoColunaAtual = sqlite3_column_type(stmt, nColuna);

					coluna.ordem = nColuna;
					coluna.tipo = this->vetorTipoColunas[nColuna];
					coluna.nome = this->vetorNomeColunas[nColuna];
					coluna.integerValor = -1;
					coluna.doubleValor = -1;
					coluna.stringValor = "";
					coluna.blobValor = NULL;
					coluna.nuloValor = false;

					if (tipoColunaAtual == SQLITE_NULL) {
						coluna.nuloValor = true;
					}
					else if (coluna.tipo == SQLITE_INTEGER) {
						coluna.integerValor =
							sqlite3_column_int64(stmt, nColuna);
					}
					else if (coluna.tipo == SQLITE_FLOAT) {
						coluna.doubleValor =
							sqlite3_column_double(stmt, nColuna);
					}
					else if (coluna.tipo == SQLITE_BLOB) {
						nQtdBytes = sqlite3_column_bytes(stmt, nColuna);

						if (nQtdBytes == 0)
							blobValor = NULL;
						else {
							blobValor = new TMemoryStream();
							blobValor->Position = 0;

							ponteiro = sqlite3_column_blob(stmt, nColuna);

							blobValor->WriteBuffer(ponteiro, nQtdBytes);
						}
						coluna.blobValor = blobValor;
					}
					else {
						coluna.stringValor =
							(char*)sqlite3_column_text(stmt, nColuna);
					}

					vetorColunas->push_back(coluna);
				}

				matrizResultados->push_back(vetorColunas);

			} break;
		case SQLITE_BUSY: {
				ex << "Não consegui preparar o SQL: " << sSQL <<
					", SQLite está Ocupado";
				throw std::logic_error(ex.str().c_str());
			}
		default: {
				sqlite3_reset(stmt);
				DB->RaiseError("Não consegui recuperar dados", sSQL);
			}
		}
		nResultadoPasso = sqlite3_step(stmt);
	}
	this->nLinhaAtual = 0;

	if (stmt != NULL) {
		sqlite3_finalize(stmt);
	}
}

// ------------------------------------------------------------------------------
TSQLiteTable::~TSQLiteTable() {
	TTipoColuna tipo;

	if (this->matrizResultados != NULL) {
		for (unsigned int nLinha = 0; nLinha < this->nQtdLinhas; nLinha++) {
			for (unsigned int nColuna = 0; nColuna < this->nQtdColunas;
			nColuna++) {
				tipo = this->matrizResultados->at(nLinha)->at(nColuna).tipo;

				if (tipo == SQLITE_BLOB) {
					this->matrizResultados->at(nLinha)->at(nColuna)
						.blobValor->Free();
				}
			}
		}

		for (unsigned int nLinha = 0; nLinha < this->nQtdLinhas; nLinha++) {
			this->matrizResultados->at(nLinha)->clear();
			delete this->matrizResultados->at(nLinha);
		}
		this->matrizResultados->clear();
		delete this->matrizResultados;
	}
	if (this->vetorNomeColunas != NULL) {
		delete[]this->vetorNomeColunas;
	}
	if (this->vetorTipoColunas != NULL) {
		delete[]this->vetorTipoColunas;
	}
}

// ---------------------------------------------------------------------------
std::string TSQLiteTable::Columns(int i) {
	return this->vetorNomeColunas[i];
}

// ---------------------------------------------------------------------------
unsigned int TSQLiteTable::Count() {
	return this->nQtdLinhas;
}

// ---------------------------------------------------------------------------
unsigned int TSQLiteTable::ColCount() {
	return this->nQtdColunas;
}

// ---------------------------------------------------------------------------
unsigned int TSQLiteTable::Row() {
	return this->nLinhaAtual;
}

// ---------------------------------------------------------------------------
bool TSQLiteTable::Next() {
	if (!getEOF()) {
		this->nLinhaAtual++;
		return true;
	}
	return false;
}

// ---------------------------------------------------------------------------
bool TSQLiteTable::Previous() {
	if (!getBOF()) {
		this->nLinhaAtual--;
		return true;
	}
	return false;
}

// ---------------------------------------------------------------------------
bool TSQLiteTable::MoveFirst() {
	if (this->nQtdLinhas > 0) {
		this->nLinhaAtual = 0;
		return true;
	}
	return false;
}

// ---------------------------------------------------------------------------
bool TSQLiteTable::MoveLast() {
	if (this->Count() > 0) {
		this->nLinhaAtual = this->nQtdLinhas - 1;
		return true;
	}
	return false;
}

// ---------------------------------------------------------------------------
bool TSQLiteTable::MoveTo(unsigned int posicao) {
	if ((this->nQtdLinhas > 0) && (this->nQtdLinhas > posicao)) {
		this->nLinhaAtual = posicao;
		return true;
	}
	return false;
}

// ---------------------------------------------------------------------------
bool TSQLiteTable::getEOF() {
	return (this->nLinhaAtual >= this->nQtdLinhas);
}

// ---------------------------------------------------------------------------
bool TSQLiteTable::getBOF() {
	return (this->nLinhaAtual <= 0);
}

// ---------------------------------------------------------------------------
std::string TSQLiteTable::FieldByName(std::string sNomeCampo) {
	return Fields(this->FieldIndex(sNomeCampo));
}

// ---------------------------------------------------------------------------
int TSQLiteTable::FieldIndex(std::string sNomeCampo) {
	std::stringstream ex;
	int resultado = -1;
	std::string sNomeColuna;

	if (this->vetorNomeColunas == NULL) {
		ex << "Campo " << sNomeCampo <<
			" Não encontrado. Conjunto de dados Vazio";
		throw std::logic_error(ex.str().c_str());
	}

	if (this->nQtdColunas == 0) {
		ex << "Campo " << sNomeCampo <<
			" Não encontrado. Conjunto de dados Vazio";
		throw std::logic_error(ex.str().c_str());
	}

	for (unsigned int i = 0; i < this->nQtdColunas; i++) {
		sNomeColuna = this->vetorNomeColunas[i];
		if (cppUpperCase(sNomeColuna) == cppUpperCase(sNomeCampo)) {
			resultado = i;
			break;
		}
	}

	if (resultado < 0) {
		ex << "Campo " << sNomeCampo << " Não encontrado no Conjunto de dados";
		throw std::logic_error(ex.str().c_str());
	}

	return resultado;
}

// ---------------------------------------------------------------------------
std::string TSQLiteTable::Fields(unsigned int i) {
	std::stringstream ex;
	std::string retorno;
	TTipoColuna tipo;
	TSQLiteColuna coluna;

	retorno = "";
	if (getEOF()) {
		throw std::logic_error("Tabela está no fim do arquivo");
	}

	if (this->nQtdColunas > 0) {
		tipo = this->vetorTipoColunas[i];

		switch (tipo) {
		case SQLITE_TEXT: {
				coluna = this->matrizResultados->at(this->nLinhaAtual)->at(i);
				retorno = coluna.stringValor;
			} break;
		case SQLITE_INTEGER: {
				ex << this->FieldAsInteger(i);
				retorno = ex.str();
			} break;
		case SQLITE_FLOAT: {
				ex << this->FieldAsDouble(i);
				retorno = ex.str();
			} break;
		case SQLITE_BLOB:
			retorno = this->FieldAsBlobText(i);
			break;
		default:
			retorno = "";
		}
	}

	return retorno;
}

// ---------------------------------------------------------------------------
TMemoryStream* TSQLiteTable::FieldAsBlob(unsigned int i) {
	TTipoColuna tipo;
	TSQLiteColuna coluna;
	TMemoryStream *retorno;

	retorno = NULL;

	if (getEOF()) {
		throw std::logic_error("Tabela está no fim do arquivo");
	}
	if (this->nQtdColunas > 0) {
		tipo = this->vetorTipoColunas[i];

		if (tipo == SQLITE_BLOB) {
			coluna = this->matrizResultados->at(this->nLinhaAtual)->at(i);

			if (coluna.blobValor != NULL) {
				retorno = coluna.blobValor;
			}
		}
	}
	return retorno;
}

// ---------------------------------------------------------------------------
std::string TSQLiteTable::FieldAsBlobText(unsigned int i) {
	TMemoryStream *MemStream;
	char *Buffer;
	std::string *resultado = new std::string();

	(*resultado) = "";
	MemStream = this->FieldAsBlob(i);
	if (MemStream != NULL) {
		if (MemStream->Size > 0) {
			MemStream->Position = 0;
#ifdef __UNICODE
			Buffer = Ansistrings::AnsiStrAlloc(MemStream->Size + 1);
#else
			Buffer = (PAnsiChar)StrAlloc(MemStream->Size + 1);
#endif
			MemStream->ReadBuffer(Buffer, (int)MemStream->Size);
			(*(Buffer + (int)MemStream->Size)) = char(0);
			// SetString(resultado, Buffer, MemStream->Size);
			resultado = new std::string(Buffer, MemStream->Size);
			// Ansistrings::StrDispose(Buffer);
			delete Buffer;
		}
		MemStream->Free();
	}
	return (*resultado);
}

// ---------------------------------------------------------------------------
__int64 TSQLiteTable::FieldAsInteger(unsigned int i) {
	TTipoColuna tipo;
	TSQLiteColuna coluna;
	__int64 retorno;

	retorno = -1;

	if (getEOF()) {
		throw std::logic_error("Tabela está no fim do arquivo");
	}
	if (this->nQtdColunas > 0) {
		tipo = this->vetorTipoColunas[i];

		if (tipo == SQLITE_INTEGER) {
			coluna = this->matrizResultados->at(this->nLinhaAtual)->at(i);

			if (coluna.integerValor != NULL) {
				retorno = coluna.integerValor;
			}
		}
	}
	return retorno;
}

// ---------------------------------------------------------------------------
double TSQLiteTable::FieldAsDouble(unsigned int i) {
	TTipoColuna tipo;
	TSQLiteColuna coluna;
	double retorno;

	retorno = -1;

	if (getEOF()) {
		throw std::logic_error("Tabela está no fim do arquivo");
	}
	if (this->nQtdColunas > 0) {
		tipo = this->vetorTipoColunas[i];

		if (tipo == SQLITE_FLOAT) {
			coluna = this->matrizResultados->at(this->nLinhaAtual)->at(i);

			if (coluna.doubleValor != NULL) {
				retorno = coluna.doubleValor;
			}
		}
	}
	return retorno;
}

// ---------------------------------------------------------------------------
std::string TSQLiteTable::FieldAsString(unsigned int i) {
	TTipoColuna tipo;
	TSQLiteColuna coluna;
	std::string retorno;

	retorno = "";

	if (getEOF()) {
		throw std::logic_error("Tabela está no fim do arquivo");
	}
	if (this->nQtdColunas > 0) {
		tipo = this->vetorTipoColunas[i];

		if (tipo == SQLITE_TEXT) {
			coluna = this->matrizResultados->at(this->nLinhaAtual)->at(i);
			retorno = coluna.stringValor;
		}
	}
	return retorno;
}

// ---------------------------------------------------------------------------
bool TSQLiteTable::FieldIsNull(unsigned int i) {
	TTipoColuna tipo;
	TSQLiteColuna coluna;
	bool retorno;

	retorno = false;

	if (getEOF()) {
		throw std::logic_error("Tabela está no fim do arquivo");
	}
	if (this->nQtdColunas > 0) {
		tipo = this->vetorTipoColunas[i];

		if (tipo == SQLITE_NULL) {
			coluna = this->matrizResultados->at(this->nLinhaAtual)->at(i);
			retorno = coluna.nuloValor;
		}
	}
	return retorno;
}

// ---------------------------------------------------------------------------
int TSQLiteTable::CountResult() {
	if (!getEOF())
		return cppStrToInt(Fields(0));
	else
		return 0;

}
// ---------------------------------------------------------------------------
// TSQLiteUniTable
// ---------------------------------------------------------------------------
TSQLiteUniTable::TSQLiteUniTable(TSQLiteDatabase *DB, const std::string sSQL) {
	new TSQLiteUniTable(DB, sSQL, NULL);
}

// ---------------------------------------------------------------------------
TSQLiteUniTable::TSQLiteUniTable(TSQLiteDatabase *DB, const std::string sSQL,
	const TSQLiteParametro bindings[]) {
	const char *NextSQLStatement;

	this->localDB = DB;
	this->bEOF = false;
	this->nUniLinhaAtual = 0;
	this->nUniQtdColunas = 0;
	this->sql = sSQL;

	if (sqlite3_prepare_v2(DB->dbHandle, sSQL.c_str(), -1, &this->stmt,
		&NextSQLStatement) != SQLITE_OK) {
		DB->RaiseError("Não consegui preparar o SQL", sSQL);
	}
	if (stmt == NULL) {
		DB->RaiseError("Não consegui preparar o SQL", sSQL);
	}

	DB->DoQuery(sSQL);
	DB->SetParams(stmt);
	if (bindings != NULL) {
		DB->BindData(stmt, bindings);
	}

	this->nUniQtdColunas = sqlite3_column_count(stmt);
	this->vetorUniNomeColunas = new std::string[this->nUniQtdColunas];
	for (unsigned int i = 0; i < this->nUniQtdColunas; i++) {
		this->vetorUniNomeColunas[i] = sqlite3_column_name(stmt, i);
	}

	this->Next();
}

// ---------------------------------------------------------------------------
TSQLiteUniTable::~TSQLiteUniTable() {
	if (this->stmt == NULL) {
		sqlite3_finalize(this->stmt);
	}
	if (this->vetorUniNomeColunas != NULL) {
		delete[] this->vetorUniNomeColunas;
	}
}

// ---------------------------------------------------------------------------
std::string TSQLiteUniTable::Columns(int i) {
	return this->vetorUniNomeColunas[i];
}

// ---------------------------------------------------------------------------
unsigned int TSQLiteUniTable::ColCount() {
	return this->nUniQtdColunas;
}

// ---------------------------------------------------------------------------
unsigned int TSQLiteUniTable::Row() {
	return this->nUniLinhaAtual;
}

// ---------------------------------------------------------------------------
bool TSQLiteUniTable::Next() {
	int nResultadoPasso;

	this->bEOF = true;
	nResultadoPasso = sqlite3_step(this->stmt);
	switch (nResultadoPasso) {
	SQLITE_ROW: {
			this->bEOF = false;
			this->nUniLinhaAtual++;
		} break;
	SQLITE_DONE:
		// we are on the end of dataset
		// return EOF=true only
		{
		} break;
	default: {
			sqlite3_reset(this->stmt);
			localDB->RaiseError("Não consegui recuperar os dados", this->sql);
		}
	}
	return (!this->bEOF);

}

// ---------------------------------------------------------------------------
bool TSQLiteUniTable::getEOF() {
	return this->bEOF;
}

// ---------------------------------------------------------------------------
std::string TSQLiteUniTable::FieldByName(std::string sNomeCampo) {
	return Fields(this->FieldIndex(sNomeCampo));
}

// ---------------------------------------------------------------------------
int TSQLiteUniTable::FieldIndex(std::string sNomeCampo) {
	std::stringstream ex;
	int resultado = -1;
	std::string sNomeColuna;

	if (this->vetorUniNomeColunas == NULL) {
		ex << "Campo " << sNomeCampo <<
			" Não encontrado. Conjunto de dados Vazio";
		throw std::logic_error(ex.str().c_str());
	}

	if (this->nUniQtdColunas == 0) {
		ex << "Campo " << sNomeCampo <<
			" Não encontrado. Conjunto de dados Vazio";
		throw std::logic_error(ex.str().c_str());
	}

	for (unsigned int i = 0; i < this->nUniQtdColunas; i++) {
		sNomeColuna = this->vetorUniNomeColunas[i];
		if (cppUpperCase(sNomeColuna) == cppUpperCase(sNomeCampo)) {
			resultado = i;
			break;
		}
	}

	if (resultado < 0) {
		ex << "Campo " << sNomeCampo << " Não encontrado no Conjunto de dados";
		throw std::logic_error(ex.str().c_str());
	}

	return resultado;
}

// ---------------------------------------------------------------------------
std::string TSQLiteUniTable::Fields(unsigned int i) {
	char* texto;
	std::string retorno;

	texto = (char*)sqlite3_column_text(this->stmt, i);
	retorno = texto;

	return retorno;
}

// ---------------------------------------------------------------------------
TMemoryStream* TSQLiteUniTable::FieldAsBlob(unsigned int i) {
	int nQtdBytes;
	TMemoryStream *retorno;
	const void *ponteiro;

	retorno = new TMemoryStream();

	nQtdBytes = sqlite3_column_bytes(this->stmt, i);
	if (nQtdBytes > 0) {
		ponteiro = sqlite3_column_blob(this->stmt, i);
		retorno->WriteBuffer(ponteiro, nQtdBytes);
		retorno->Position = 0;
	}
	return retorno;
}

// ---------------------------------------------------------------------------
std::string TSQLiteUniTable::FieldAsBlobText(unsigned int i) {
	TMemoryStream *MemStream;
	char *Buffer;
	std::string *resultado = new std::string();

	(*resultado) = "";
	MemStream = this->FieldAsBlob(i);
	if (MemStream != NULL) {
		if (MemStream->Size > 0) {
			MemStream->Position = 0;
#ifdef __UNICODE
			Buffer = Ansistrings::AnsiStrAlloc(MemStream->Size + 1);
#else
			Buffer = (PAnsiChar)StrAlloc(MemStream->Size + 1);
#endif
			MemStream->ReadBuffer(Buffer, (int)MemStream->Size);
			(*(Buffer + (int)MemStream->Size)) = char(0);
			// SetString(resultado, Buffer, MemStream->Size);
			resultado = new std::string(Buffer, MemStream->Size);
			// Ansistrings::StrDispose(Buffer);
			delete Buffer;
		}
		MemStream->Free();
	}
	return (*resultado);

}

// ---------------------------------------------------------------------------
__int64 TSQLiteUniTable::FieldAsInteger(unsigned int i) {
	return sqlite3_column_int64(this->stmt, i);
}

// ---------------------------------------------------------------------------
double TSQLiteUniTable::FieldAsDouble(unsigned int i) {
	return sqlite3_column_double(this->stmt, i);
}

// ---------------------------------------------------------------------------
std::string TSQLiteUniTable::FieldAsString(unsigned int i) {
	return this->Fields(i);
}

// ---------------------------------------------------------------------------
bool TSQLiteUniTable::FieldIsNull(unsigned int i) {
	return (sqlite3_column_text(this->stmt, i) == NULL);
}

// ---------------------------------------------------------------------------
const void* TSQLiteUniTable::FieldAsBlobPtr(unsigned int i, int *iNumBytes) {
	(*iNumBytes) = sqlite3_column_bytes(this->stmt, i);
	return sqlite3_column_blob(this->stmt, i);
}
// ---------------------------------------------------------------------------
