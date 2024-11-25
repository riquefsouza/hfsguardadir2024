// ---------------------------------------------------------------------------

#pragma hdrstop

#include "SQLiteTable3.h"
#include "SQLite3Lib.h"
#include "Funcoes.h"
#include <sstream>
#include <cstdlib>
#include <cwchar>
// ---------------------------------------------------------------------------
#pragma package(smart_init)
// ---------------------------------------------------------------------------
void DisposePointer(void *ponteiro)
{
	if (ponteiro!=NULL) {
		sqlite3_free(ponteiro);
		ponteiro = NULL;
	}
}
// ---------------------------------------------------------------------------
TSQLiteDatabase::TSQLiteDatabase(const std::string sBanco) {
	std::stringstream ex;
	int resultado;
	const char *msgErro = NULL;

	this->bEmTransacao = false;
	this->listaParametros = new std::vector<TSQLiteParametro>();

	resultado = sqlite3_open(sBanco.c_str(), &dbHandle);

	if (resultado != SQLITE_OK) {
		if (dbHandle!=NULL) {
			msgErro = sqlite3_errmsg(dbHandle);
			ex << "Falha ao abrir banco de dados '" << sBanco << "':" << msgErro;
			throw std::logic_error(ex.str().c_str());
		} else {
			ex << "Falha ao abrir banco de dados '" << sBanco << "': erro desconhecido";
			throw std::logic_error(ex.str().c_str());
		}
	}

	if (msgErro!=NULL) {
		sqlite3_free((void*)msgErro);
	}

}
// ---------------------------------------------------------------------------
TSQLiteDatabase::~TSQLiteDatabase() {
	if (bEmTransacao){
		this->Rollback();  //assume rollback
	}
	if (dbHandle!=NULL) {
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
					//sqlite3_bind_blob(stmt, i, , );
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
	sqlite3_stmt *stmt;
	const char *NextSQLStatement;
	int nResultadoPasso;

	if (sqlite3_prepare_v2(dbHandle, sSQL.c_str(), -1,
		&stmt, &NextSQLStatement) != SQLITE_OK) {
		RaiseError("Erro executando SQL", sSQL);
	}

	if (stmt == NULL){
		RaiseError("Não consegui preparar o SQL", sSQL);
	}

	//DoQuery(sSQL);
	SetParams(stmt);
	//BindData(stmt, Bindings); Se Tiver valor para passar

	nResultadoPasso = sqlite3_step(stmt);

	if (nResultadoPasso != SQLITE_DONE) {
		sqlite3_reset(stmt);
		RaiseError("Erro executando o procedimento do SQL", sSQL);
	}

	if (stmt!=NULL){
		sqlite3_finalize(stmt);
	}
}
// ---------------------------------------------------------------------------
TSQLiteTable* TSQLiteDatabase::GetTable(const std::string sSQL) {
	return new TSQLiteTable(this, sSQL);
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

	//DoQuery(sSQL);

	// now bind the blob data
	nTamanho = BlobData->Size;

	ponteiro = GetMemory(nTamanho);

	if (ponteiro == NULL) {
		ex << "Erro ao alocar memória para salvar o BLOB: " << sSQL;
		throw std::logic_error(ex.str().c_str());
	}

	BlobData->Position = 0;
	BlobData->Read(&ponteiro, nTamanho);

	nResultadoBind = sqlite3_bind_blob(stmt, 1, ponteiro,
		nTamanho, *DisposePointer);

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
	if (retorno != SQLITE_OK){
		msgErro = sqlite3_errmsg(this->dbHandle);
	}
	if (msgErro != NULL) {
		ex << sMensagem << ". Erro [" << retorno << "]: " <<
			SQLiteErrorStr(retorno) << ". '" << sSQL << "': " << msgErro;
		throw std::logic_error(ex.str().c_str());
	} else {
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

// ------------------------------------------------------------------------------
// TSQLiteTable
// ------------------------------------------------------------------------------
TSQLiteTable::TSQLiteTable(TSQLiteDatabase *DB, const std::string sSQL) {
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

	this->matrizResultados = new std::vector< std::vector<TSQLiteColuna>* >();

	if (sqlite3_prepare_v2(DB->dbHandle, sSQL.c_str(), -1, &stmt,
		&NextSQLStatement) != SQLITE_OK) {
		DB->RaiseError("Não consegui preparar o SQL", sSQL);
	}
	if (stmt == NULL) {
		DB->RaiseError("Não consegui preparar o SQL", sSQL);
	}

	// DB->DoQuery(SQL);
	DB->SetParams(stmt);
	// DB->BindData(Stmt, Bindings);

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
						this->vetorNomeColunas[i] = sqlite3_column_name(stmt, i);
					}

					for (unsigned int i = 0; i < this->nQtdColunas; i++) {
						tipoColunaDeclarada = sqlite3_column_decltype(stmt, i);
						sTipoColunaDeclarada = tipoColunaDeclarada;
						sTipoColunaDeclarada = cppUpperCase(sTipoColunaDeclarada);

						if (tipoColunaDeclarada == NULL) {
							tipoColuna = (TTipoColuna)sqlite3_column_type(stmt, i);
						} else if ((sTipoColunaDeclarada == "INTEGER") ||
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
				for (unsigned int nColuna = 0; nColuna < this->nQtdColunas; nColuna++) {

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
					} else if (coluna.tipo == SQLITE_INTEGER) {
						coluna.integerValor = sqlite3_column_int64(stmt, nColuna);
					}
					else if (coluna.tipo == SQLITE_FLOAT) {
						coluna.doubleValor = sqlite3_column_double(stmt, nColuna);
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
						coluna.stringValor = (char*)sqlite3_column_text(stmt, nColuna);
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
TSQLiteTable::~TSQLiteTable(){
	TTipoColuna tipo;

	if (this->matrizResultados!=NULL) {
		for (unsigned int nLinha = 0; nLinha < this->nQtdLinhas; nLinha++) {
			for (unsigned int nColuna = 0; nColuna < this->nQtdColunas; nColuna++) {
				tipo = this->matrizResultados->at(nLinha)->at(nColuna).tipo;

				if (tipo == SQLITE_BLOB) {
					this->matrizResultados->at(nLinha)->at(nColuna).blobValor->Free();
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
	if (this->vetorNomeColunas!=NULL){
		delete[] this->vetorNomeColunas;
	}
	if (this->vetorTipoColunas!=NULL){
		delete[] this->vetorTipoColunas;
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
		//return resultado;
	}

	if (this->nQtdColunas == 0) {
		ex << "Campo " << sNomeCampo <<
			" Não encontrado. Conjunto de dados Vazio";
		throw std::logic_error(ex.str().c_str());
		//return resultado;
	}

	for (unsigned int i = 0; i < this->nQtdColunas; i++) {
		sNomeColuna = this->vetorNomeColunas[i];
		if (sNomeColuna == sNomeCampo) {
			resultado = i;
			break;
		}
	}

	if (resultado < 0) {
		ex << "Campo " << sNomeCampo <<	" Não encontrado no Conjunto de dados";
		throw std::logic_error(ex.str().c_str());
		//return resultado;
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
	if (getEOF()){
		throw std::logic_error("Tabela está no fim do arquivo");
		//return retorno;
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

	if (getEOF()){
		throw std::logic_error("Tabela está no fim do arquivo");
		//return retorno;
	}
	if (this->nQtdColunas > 0) {
		tipo = this->vetorTipoColunas[i];

		if (tipo == SQLITE_BLOB) {
			coluna = this->matrizResultados->at(this->nLinhaAtual)->at(i);

			if (coluna.blobValor!=NULL){
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
	std::string *resultado;

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
			//Ansistrings::StrDispose(Buffer);
			delete Buffer;
		}
	}
	return (*resultado);
}
// ---------------------------------------------------------------------------
__int64 TSQLiteTable::FieldAsInteger(unsigned int i){
	TTipoColuna tipo;
	TSQLiteColuna coluna;
	__int64 retorno;

	retorno = -1;

	if (getEOF()){
		throw std::logic_error("Tabela está no fim do arquivo");
		//return retorno;
	}
	if (this->nQtdColunas > 0) {
		tipo = this->vetorTipoColunas[i];

		if (tipo == SQLITE_INTEGER) {
			coluna = this->matrizResultados->at(this->nLinhaAtual)->at(i);

			if (coluna.integerValor!=NULL){
				retorno = coluna.integerValor;
			}
		}
	}
	return retorno;
}
// ---------------------------------------------------------------------------
double TSQLiteTable::FieldAsDouble(unsigned int i){
	TTipoColuna tipo;
	TSQLiteColuna coluna;
	double retorno;

	retorno = -1;

	if (getEOF()){
		throw std::logic_error("Tabela está no fim do arquivo");
		//return retorno;
	}
	if (this->nQtdColunas > 0) {
		tipo = this->vetorTipoColunas[i];

		if (tipo == SQLITE_FLOAT) {
			coluna = this->matrizResultados->at(this->nLinhaAtual)->at(i);

			if (coluna.doubleValor!=NULL){
				retorno = coluna.doubleValor;
			}
		}
	}
	return retorno;
}
// ---------------------------------------------------------------------------
std::string TSQLiteTable::FieldAsString(unsigned int i){
	TTipoColuna tipo;
	TSQLiteColuna coluna;
	std::string retorno;

	retorno = "";

	if (getEOF()){
		throw std::logic_error("Tabela está no fim do arquivo");
		//return retorno;
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
bool TSQLiteTable::FieldIsNull(unsigned int i){
	TTipoColuna tipo;
	TSQLiteColuna coluna;
	bool retorno;

	retorno = false;

	if (getEOF()){
		throw std::logic_error("Tabela está no fim do arquivo");
		//return retorno;
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

