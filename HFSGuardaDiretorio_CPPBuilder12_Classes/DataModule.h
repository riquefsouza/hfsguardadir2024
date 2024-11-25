// ---------------------------------------------------------------------------

#ifndef DataModuleH
#define DataModuleH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
// #include "SQLiteTable3.h"
#include <Data.DB.hpp>
#include <Data.DbxSqlite.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
#include <Datasnap.DBClient.hpp>
#include <Datasnap.Provider.hpp>

// ---------------------------------------------------------------------------
class Tdm : public TDataModule {
__published: // IDE-managed Components

	TSQLConnection *conexao;
	TSQLQuery *consultaDirFilho;
	TSQLQuery *consultaDirPai;
	TSQLQuery *consultaArquivo;
	TSQLTable *tabelaAbas;
	TLargeintField *tabelaAbascod;
	TWideStringField *tabelaAbasnome;
	TSQLQuery *consultaAuxiliar;
	TSQLTable *tabelaExtensoes;
	TSQLTable *tabelaDiretorios;
	TClientDataSet *cdsDiretorios;
	TClientDataSet *cdsExtensoes;
	TDataSetProvider *dspExtensoes;
	TDataSetProvider *dspDiretorios;

	void __fastcall DataModuleCreate(TObject *Sender);
	void __fastcall cdsExtensoesBeforeRefresh(TDataSet *DataSet);

private: // User declarations
		public : // User declarations
	__fastcall Tdm(TComponent* Owner);
	/*
	 TSQLiteDatabase *conexao;
	 TSQLiteTable *tabelaExtensoes, *tabelaAbas;
	 String SQLDiretorios, SQLExtensoes, SQLAbas;
	 String consultaDirPai, consultaDirFilho, consultaArquivo;
	 */
};

// ---------------------------------------------------------------------------
extern PACKAGE Tdm *dm;
// ---------------------------------------------------------------------------
#endif
