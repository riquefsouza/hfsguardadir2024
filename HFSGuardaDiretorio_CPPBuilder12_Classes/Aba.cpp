// ---------------------------------------------------------------------------

#pragma hdrstop

#include "Aba.h"
#include "DataModule.h"
#include "Rotinas.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
TAba *Aba;

// ---------------------------------------------------------------------------
TAba::TAba() {
}

// ---------------------------------------------------------------------------
void TAba::carregarAba(std::vector<TAba> *listaAba, TProgressoLog progressoLog) {
	TAba aba;
	int total;
	TProgresso pb;

	listaAba->clear();

	dm->tabelaAbas->Open();
	total = dm->tabelaAbas->RecordCount;
	dm->tabelaAbas->First();

	/*
	 dm->tabelaAbas=dm->conexao->GetTable(AnsiString(dm->SQLAbas));
	 total = dm->tabelaAbas->Count();
	 dm->tabelaAbas->MoveFirst();
	 */
	if (total > 0) {
		pb.minimo = 0;
		pb.maximo = total - 1;
		pb.posicao = 0;
		pb.passo = 1;

		for (int i = 0; i < total; i++) {
			// aba = new TAba();
			aba.codigo = dm->tabelaAbas->Fields->FieldByNumber(1)->AsInteger;
			aba.nome = dm->tabelaAbas->Fields->FieldByNumber(2)->AsString;

			/*
			 aba.codigo = StrToInt(dm->tabelaAbas->FieldAsString(dm->tabelaAbas->FieldIndex("cod")));  //0
			 aba.nome = dm->tabelaAbas->FieldAsString(dm->tabelaAbas->FieldIndex("nome")); //1
			 */

			aba.ordem = (i+1);

			listaAba->push_back(aba);

			dm->tabelaAbas->Next();

			pb.posicao = i;

			if (progressoLog!=NULL) {
				progressoLog(pb);
			}

		}
	}

}

// ---------------------------------------------------------------------------
int TAba::retMaxCodAba(std::vector<TAba> *listaLocal) {
	int nMaior;
	TAba aba;

	nMaior = 0;

	for (unsigned int i = 0; i < listaLocal->size(); i++) {
		aba = listaLocal->at(i);
		if (aba.codigo > nMaior) {
			nMaior = aba.codigo;
		}
	}

	return nMaior + 1;
}

// ---------------------------------------------------------------------------
String TAba::abaToSQL(TAba aba) {
	return "insert into Abas(cod, nome) values(" + IntToStr(aba.codigo) + "," +
		QuotedStr(aba.nome) + ")";
}

// ---------------------------------------------------------------------------
bool TAba::incluirAba(TAba aba) {
	String sSQL;

	sSQL = abaToSQL(aba);
	return Rotinas->execConsulta(sSQL, True);
}

// ---------------------------------------------------------------------------
bool TAba::alterarAba(TAba aba) {
	String sSQL;

	sSQL = "update Abas set nome=" + QuotedStr(aba.nome) + " where cod=" +
		IntToStr(aba.codigo);
	return Rotinas->execConsulta(sSQL, True);
}

// ---------------------------------------------------------------------------
bool TAba::excluirAba(TAba aba) {
	String sSQL;

	sSQL = "delete from Diretorios where aba=" + IntToStr(aba.codigo);
	Rotinas->execConsulta(sSQL, true);
	sSQL = "delete from Abas where cod=" + IntToStr(aba.codigo);
	return Rotinas->execConsulta(sSQL, true);
}

// ---------------------------------------------------------------------------
Boolean TAba::criarTabelaAbas() {
	String sSQL;

	sSQL = "create table if (NOT EXISTS Abas(" \
	 "cod integer not null," \
	 "nome varchar(10) not null," \
	 "primary key (cod))";
	return Rotinas->execConsulta(sSQL, False);
}

// ---------------------------------------------------------------------------
TAba TAba::pegaAbaPorOrdem(std::vector<TAba> *lista, int ordem) {
	TAba aba;

	for (unsigned int i = 0; i < lista->size(); i++) {
		aba = lista->at(i);
		if (aba.ordem == ordem) {
			return aba;
		}
	}

	return aba;
}
// ---------------------------------------------------------------------------
int TAba::pegaOrdemPorNomeAba(std::vector<TAba> *lista, String nomeAba) {
	TAba aba;

	for (unsigned int i = 0; i < lista->size(); i++) {
		aba = lista->at(i);
		if (aba.nome == nomeAba) {
			return aba.ordem;
		}
	}

	return -1;
}
