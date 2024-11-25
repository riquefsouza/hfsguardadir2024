// ---------------------------------------------------------------------------

#pragma hdrstop

#include "Diretorio.h"
#include "Rotinas.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
TDiretorio *Diretorio;

// ---------------------------------------------------------------------------
TDiretorio::TDiretorio() {
}

// ---------------------------------------------------------------------------
void TDiretorio::carregarDiretorio(TSQLQuery* consultaDir,
	std::vector<TDiretorio> *listaDiretorio, TProgressoLog progressoLog) {
	TDiretorio diretorio;
	int total;
	String sTamanho;
	TProgresso pb;

	listaDiretorio->clear();

	consultaDir->Open();
	total = consultaDir->RecordCount;
	consultaDir->First();

	if (total > 0) {
		pb.minimo = 0;
		pb.maximo = total - 1;
		pb.posicao = 0;
		pb.passo = 1;

		for (int i = 0; i < total; i++) {
			// diretorio = new TDiretorio();

			diretorio.aba.codigo = consultaDir->Fields->FieldByNumber(1)
				->AsInteger;
			diretorio.codigo = consultaDir->Fields->FieldByNumber(2)->AsInteger;
			diretorio.ordem = consultaDir->Fields->FieldByNumber(3)->AsInteger;

			if (!consultaDir->Fields->FieldByNumber(4)->IsNull)
				diretorio.codDirPai = consultaDir->Fields->FieldByNumber(4)
					->AsInteger;
			else
				diretorio.codDirPai = -1;

			diretorio.nome = consultaDir->Fields->FieldByNumber(5)->AsString;
			diretorio.tamanho = consultaDir->Fields->FieldByNumber(6)
				->AsLargeInt;
			diretorio.tipo.codigo = consultaDir->Fields->FieldByNumber(7)
				->AsString[1];
			diretorio.modificado =
				StrToDateTime(consultaDir->Fields->FieldByNumber(8)->AsString);
			diretorio.atributos = consultaDir->Fields->FieldByNumber(9)
				->AsString;
			diretorio.caminho = consultaDir->Fields->FieldByNumber(10)
				->AsString;
			diretorio.aba.nome = consultaDir->Fields->FieldByNumber(11)
				->AsString;
			diretorio.nomePai = consultaDir->Fields->FieldByNumber(12)
				->AsString;
			diretorio.caminhoPai = consultaDir->Fields->FieldByNumber(13)
				->AsString;
			diretorio.tamanhoFormatado = MontaTamanho(diretorio.tamanho);
			if (diretorio.tipo.codigo == 'D')
				diretorio.tipo.nome = "Diretório";
			else
				diretorio.tipo.nome = "Arquivo";
			diretorio.modificadoFormatado =
				FormatDateTime("dd/mm/yyyy hh:nn:ss", diretorio.modificado);

			listaDiretorio->push_back(diretorio);

			consultaDir->Next();

			pb.posicao = i;

			if (progressoLog!=NULL) {
				progressoLog(pb);
			}
		}
	}
	consultaDir->Close();

}

/*
 void TDiretorio::carregarDiretorio(String sSQL, std::vector<TDiretorio> *listaDiretorio,
 TProgressoLog progressoLog){
 TDiretorio diretorio;
 int total;
 consultaDir: TSQLiteTable;
 sTamanho: String;

 listaDiretorio->clear();

 consultaDir=dm->conexao->GetTable(AnsiString(sSQL));
 total = consultaDir->Count;
 consultaDir->MoveFirst;

 if (total > 0) {
 pb->Min=1;
 pb->Max=total;
 pb->Position=1;
 pb->Step=1;

 for (int i = 1 ; i <= total; i++) {
 diretorio=TDiretorio();

 with diretorio; i++) {
 aba->codigo = StrToInt(consultaDir->FieldAsString(consultaDir->FieldIndex["aba"]));
 codigo = StrToInt(consultaDir->FieldAsString(consultaDir->FieldIndex["cod"]));
 ordem = StrToInt(consultaDir->FieldAsString(consultaDir->FieldIndex["ordem"]));

 if ((not consultaDir->FieldIsNull(consultaDir->FieldIndex["coddirpai"])))
 codDirPai = StrToInt(consultaDir->FieldAsString(consultaDir->FieldIndex["coddirpai"]))
 else
 codDirPai = -1;

 nome = consultaDir->FieldAsString(consultaDir->FieldIndex["nome"]);
 sTamanho=consultaDir->FieldAsString(consultaDir->FieldIndex["tam"]);
 if (Pos(".", sTamanho) > 0)
 sTamanho=StringReplace(sTamanho, ".0", "", [rfReplaceAll, rfIgnoreCase]);
 tamanho = StrTo__int64(sTamanho);
 tipo->codigo = consultaDir->FieldAsString(consultaDir->FieldIndex["tipo"]);
 modificado = StrToDateTime(consultaDir->FieldAsString(consultaDir->FieldIndex["modificado"]));
 atributos = consultaDir->FieldAsString(consultaDir->FieldIndex["atributos"]);
 caminho = consultaDir->FieldAsString(consultaDir->FieldIndex["caminho"]);
 aba->nome = consultaDir->FieldAsString(consultaDir->FieldIndex["nomeaba"]);
 nomePai = consultaDir->FieldAsString(consultaDir->FieldIndex["nomepai"]);
 caminhoPai = consultaDir->FieldAsString(consultaDir->FieldIndex["caminhopai"]);
 tamanhoFormatado=MontaTamanho(tamanho);
 if (tipo->codigo="D")
 tipo->nome="Diretório"
 else
 tipo->nome="Arquivo";
 modificadoFormatado=FormatDateTime("dd/mm/yyyy hh:nn:ss", modificado);
 }

 listaDiretorio->Add(diretorio);

 consultaDir->Next();

 pb->Position=i;
 }
 }
 consultaDir->Free();

 }
 */
// ---------------------------------------------------------------------------
TDiretorio TDiretorio::atribuiDiretorio(int nAba, int nCodDirRaiz,
	String sNomeDirRaiz, String sDiretorio, bool bDiretorio,
	std::vector<TDiretorio> *listaLocal, TArquivo arquivo, int *nOrdem) {
	TDiretorio diretorio;
	String sCaminho;

	sCaminho = removerDrive(sDiretorio);

	if ((sCaminho.Length() > 0) && (sNomeDirRaiz.Length() > 0)) {
		if (AnsiStartsStr(sNomeDirRaiz, sCaminho)) {
			sCaminho = sCaminho.SubString(sNomeDirRaiz.Length()+2,
				sCaminho.Length());
		}
		else {
			sCaminho = sNomeDirRaiz + BARRA_INVERTIDA + sCaminho;
		}
	}

	// diretorio= new TDiretorio();

	diretorio.aba.codigo = nAba;
	diretorio.codigo = nCodDirRaiz;
	diretorio.ordem = *nOrdem;
	diretorio.nome = arquivo.nome;
	diretorio.tamanho = arquivo.tamanho;
	diretorio.modificado = arquivo.modificado;
	diretorio.atributos = arquivoAtributos(arquivo.natributos);

	if (sDiretorio == "") {
		diretorio.caminho = arquivo.nome;
		diretorio.caminhoPai = "";
	}
	else {
		diretorio.caminho = sCaminho;
		diretorio.caminhoPai = diretorio.caminho.SubString(1,
			LastDelimiter(BARRA_INVERTIDA, diretorio.caminho) - 1);
	}

	if (bDiretorio) {
		diretorio.tipo.codigo = 'D';
		if ((*nOrdem) == 1)
			diretorio.codDirPai = 0;
		else
			diretorio.codDirPai = retCodDirPai(diretorio.aba.codigo,
			diretorio.caminhoPai, listaLocal);
	}
	else {
		diretorio.tipo.codigo = 'A';
		diretorio.codDirPai = retCodDirPai(diretorio.aba.codigo,
			diretorio.caminhoPai, listaLocal);
	}

	diretorio.aba.nome = "";
	diretorio.nomePai = "";
	diretorio.tamanhoFormatado = MontaTamanho(diretorio.tamanho);
	if (diretorio.tipo.codigo == 'D')
		diretorio.tipo.nome = "Diretório";
	else {
		diretorio.tipo.nome = "Arquivo";
	}
	diretorio.modificadoFormatado = FormatDateTime("dd/mm/yyyy hh:nn:ss",
		diretorio.modificado);
	diretorio.caminhoOriginal = sDiretorio;

	(*nOrdem)++;

	return diretorio;
}

// ---------------------------------------------------------------------------
void TDiretorio::atribuiListaDiretorio(int nAba, int nCodDirRaiz,
	String sNomeDirRaiz, String sDiretorio, std::vector<TDiretorio> *listaLocal,
	TSearchRec SearchRec, int *nOrdem, TStrings *log) {
	TDiretorio diretorio;

	if (FileExists(sDiretorio)) {
		diretorio = atribuiDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz,
			sDiretorio, false, listaLocal, searchRecToArquivo(SearchRec),
		nOrdem);
		listaLocal->push_back(diretorio);
		log->Append(sDiretorio);
	}
	else if (DirectoryExists(sDiretorio)) {
		if ((SearchRec.Name != ".") && (SearchRec.Name != "..")) {
			diretorio = atribuiDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz,
				sDiretorio, true, listaLocal, searchRecToArquivo(SearchRec),
				nOrdem);
			listaLocal->push_back(diretorio);
			log->Append(sDiretorio);

			ImportarDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz, sDiretorio,
				listaLocal, nOrdem, log);
		}
	}

}

// ---------------------------------------------------------------------------
void TDiretorio::ImportarDiretorio(int nAba, int nCodDirRaiz,
	String sNomeDirRaiz, String sDiretorio, std::vector<TDiretorio> *listaLocal,
	int *nOrdem, TStrings *log) {
	TSearchRec SearchRec;
	String sCaminho, sSeparador;

	if (sDiretorio.SubString(sDiretorio.Length(), 1) == BARRA_NORMAL)
		sSeparador = "";
	else
		sSeparador = BARRA_NORMAL;

	sCaminho = sDiretorio + sSeparador + "*.*";
	if (FindFirst(sCaminho, faAnyFile, SearchRec) == 0) {

		sCaminho = sDiretorio + sSeparador + SearchRec.Name;
		atribuiListaDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz, sCaminho,
			listaLocal, SearchRec, nOrdem, log);

		while (FindNext(SearchRec) == 0) {
			sCaminho = sDiretorio + sSeparador + SearchRec.Name;
			atribuiListaDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz, sCaminho,
				listaLocal, SearchRec, nOrdem, log);
		}
	}
	FindClose(SearchRec);
}

// ---------------------------------------------------------------------------
bool TDiretorio::verificaCodDir(int nAba, String sDiretorio,
	std::vector<TDiretorio> *listaLocal) {
	TDiretorio diretorio;

	if (sDiretorio.Length() > 0) {
		for (unsigned int i = 0; i < listaLocal->size(); i++) {
			diretorio = listaLocal->at(i);
			if (diretorio.aba.codigo == nAba) {
				if (diretorio.ordem == 1) {
					if (diretorio.codDirPai == 0) {
						if (diretorio.caminho == sDiretorio) {
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

// ---------------------------------------------------------------------------
int TDiretorio::retMaxCodDir(int nAba, std::vector<TDiretorio> *listaLocal) {
	int nMaior;
	TDiretorio diretorio;

	nMaior = -1;

	for (unsigned int i = 0; i < listaLocal->size(); i++) {
		diretorio = listaLocal->at(i);
		if (diretorio.aba.codigo == nAba) {
			if (diretorio.codigo > nMaior) {
				nMaior = diretorio.codigo;
			}
		}
	}

	return nMaior + 1;
}

// ---------------------------------------------------------------------------
String TDiretorio::diretorioToSQL(TDiretorio diretorio, bool bInsert) {
	String sSQL;

	if (bInsert) {
		sSQL = "insert into Diretorios(aba, cod, ordem, coddirpai, nome, tam," \
 "tipo,modificado, atributos, caminho) values(";
	}

	sSQL = sSQL + IntToStr(diretorio.aba.codigo) + ",";
	sSQL = sSQL + IntToStr(diretorio.codigo) + ",";
	sSQL = sSQL + IntToStr(diretorio.ordem) + ",";
	sSQL = sSQL + IntToStr(diretorio.codDirPai) + ",";
	sSQL = sSQL + QuotedStr(diretorio.nome) + ",";
	sSQL = sSQL + IntToStr(diretorio.tamanho) + ",";
	sSQL = sSQL + QuotedStr(diretorio.tipo.codigo) + ",";
	sSQL = sSQL + QuotedStr(diretorio.modificadoFormatado) + ",";
	sSQL = sSQL + QuotedStr(diretorio.atributos) + ",";
	sSQL = sSQL + QuotedStr(diretorio.caminho);

	if (bInsert)
		sSQL = sSQL + ")";

	return sSQL;
}

// ---------------------------------------------------------------------------
void TDiretorio::incluirDiretorio(TDiretorio diretorio)
{
  if (dm->cdsDiretorios->Active) {
	dm->cdsDiretorios->ReadOnly=false;
	dm->cdsDiretorios->Append();

	dm->cdsDiretorios->Fields->FieldByNumber(1)->AsInteger=diretorio.aba.codigo;
	dm->cdsDiretorios->Fields->FieldByNumber(2)->AsInteger=diretorio.codigo;
	dm->cdsDiretorios->Fields->FieldByNumber(3)->AsInteger=diretorio.ordem;
	dm->cdsDiretorios->Fields->FieldByNumber(4)->Value=diretorio.nome;
	dm->cdsDiretorios->Fields->FieldByNumber(5)->AsLargeInt=diretorio.tamanho;
	dm->cdsDiretorios->Fields->FieldByNumber(6)->AsString=diretorio.tipo.codigo;
	dm->cdsDiretorios->Fields->FieldByNumber(7)->Value=
		FormatDateTime("dd/mm/yyyy hh:nn:ss", diretorio.modificado);
	dm->cdsDiretorios->Fields->FieldByNumber(8)->Value=diretorio.atributos;
	dm->cdsDiretorios->Fields->FieldByNumber(9)->AsInteger=diretorio.codDirPai;
	dm->cdsDiretorios->Fields->FieldByNumber(10)->Value=diretorio.caminho;

	dm->cdsDiretorios->Post();
  }
}

// ---------------------------------------------------------------------------
void TDiretorio::salvarDiretorio(std::vector<TDiretorio> *listaDiretorio,
	TStrings* log, TProgressoLog progressoLog) {
	String sSQL;
	TDiretorio diretorio;
	int j;
	TProgresso pb;

	pb.minimo = 0;
	pb.maximo = listaDiretorio->size() - 1;
	pb.posicao = 0;
	pb.passo = 1;

	dm->cdsDiretorios->Open();
	// dm->conexao->beginTransaction;
	for (unsigned int i = 0; i < listaDiretorio->size(); i++) {
		diretorio = listaDiretorio->at(i);
		incluirDiretorio(diretorio);
		/*
		sSQL = diretorioToSQL(diretorio, true);
		Rotinas->execConsulta(sSQL, false);
		*/
		j = i + 1;
		log->Append(IntToStr(j) + " - Salvando Diretório: " +
			diretorio.caminho);

		pb.posicao = i;

		if (progressoLog!=NULL) {
			progressoLog(pb);
		}
	}

	// dm->conexao->Commit;
	dm->cdsDiretorios->ApplyUpdates(0);
	dm->cdsDiretorios->Close();

}

// ---------------------------------------------------------------------------
bool TDiretorio::excluirDiretorio(TAba aba, String sCaminho) {
	String sSQL;

	sSQL = "delete from Diretorios where caminho like " +
		QuotedStr(sCaminho + "%") + " and aba=" + IntToStr(aba.codigo);
	return Rotinas->execConsulta(sSQL, true);
}
// ---------------------------------------------------------------------------
void TDiretorio::excluirListaDiretorio(std::vector<TDiretorio> *listaDiretorio,
		TAba aba, String sCaminho)
{
  TDiretorio diretorio;
  std::vector<TDiretorio>::iterator it;

  for (it = listaDiretorio->end(); it != listaDiretorio->begin(); it--) {
	diretorio = it.operator *();

	if (diretorio.aba.codigo == aba.codigo) {
      if (sCaminho.Trim().Length() > 0) {
        if (AnsiStartsStr(sCaminho, diretorio.caminho)) {
		  listaDiretorio->erase(it);
		}
	  } else {
		listaDiretorio->erase(it);
      }
    }
  }

}
// ---------------------------------------------------------------------------
String TDiretorio::diretorioToCSV(TDiretorio diretorio) {
	String sCSV;

	sCSV = "\"";

	sCSV = sCSV + diretorio.aba.nome + "\";\"";
	sCSV = sCSV + diretorio.nome + "\";\"";
	sCSV = sCSV + IntToStr(diretorio.tamanho) + "\";\"";
	sCSV = sCSV + diretorio.tamanhoFormatado + "\";\"";
	sCSV = sCSV + diretorio.tipo.nome + "\";\"";
	sCSV = sCSV + diretorio.modificadoFormatado + "\";\"";
	sCSV = sCSV + diretorio.atributos + "\";\"";
	sCSV = sCSV + diretorio.caminho + "\"";

	return sCSV;
}

// ---------------------------------------------------------------------------
String TDiretorio::diretorioToXML(TDiretorio diretorio) {
	String sXML, sCR, sTAB, sTAB2;

	sTAB = char(9);
	sTAB2 = char(9)+char(9);
	if (TOSVersion::Platform == TOSVersion::pfWindows)
		sCR = char(13)+char(10);
	else
		sCR = char(10);

	sXML = sTAB + "<arquivo>" + sCR;

	sXML = sXML + sTAB2 + "<aba>" + IntToStr(diretorio.aba.codigo) +
		"</aba>" + sCR;
	sXML = sXML + sTAB2 + "<nomeAba>" + diretorio.aba.nome + "</nomeAba>" + sCR;
	sXML = sXML + sTAB2 + "<codigo>" + IntToStr(diretorio.codigo) +
		"</codigo>" + sCR;
	sXML = sXML + sTAB2 + "<ordem>" + IntToStr(diretorio.ordem) +
		"</ordem>" + sCR;
	sXML = sXML + sTAB2 + "<nome>" + diretorio.nome + "</nome>" + sCR;
	sXML = sXML + sTAB2 + "<tamanho>" + IntToStr(diretorio.tamanho) +
		"</tamanho>" + sCR;
	sXML = sXML + sTAB2 + "<tipo>" + diretorio.tipo.codigo + "</tipo>" + sCR;
	sXML = sXML + sTAB2 + "<modificado>" + diretorio.modificadoFormatado +
		"</modificado>" + sCR;
	sXML = sXML + sTAB2 + "<atributos>" + diretorio.atributos +
		"</atributos>" + sCR;
	sXML = sXML + sTAB2 + "<codDirPai>" + IntToStr(diretorio.codDirPai) +
		"</codDirPai>" + sCR;
	sXML = sXML + sTAB2 + "<caminho>" + diretorio.caminho + "</caminho>" + sCR;

	sXML = sXML + sTAB + "</arquivo>";

	return sXML;
}

// ---------------------------------------------------------------------------
String TDiretorio::diretorioToTXT(TDiretorio diretorio) {
	String sTXT, sTAB;

	sTAB = char(9);
	sTXT = "";
	sTXT = sTXT + diretorio.aba.nome + sTAB;
	sTXT = sTXT + diretorio.nome + sTAB;
	sTXT = sTXT + IntToStr(diretorio.tamanho) + sTAB;
	sTXT = sTXT + diretorio.tamanhoFormatado + sTAB;
	sTXT = sTXT + diretorio.tipo.nome + sTAB;
	sTXT = sTXT + diretorio.modificadoFormatado + sTAB;
	sTXT = sTXT + diretorio.atributos + sTAB;
	sTXT = sTXT + diretorio.caminho;

	return sTXT;
}

// ---------------------------------------------------------------------------
String TDiretorio::diretorioToHTML(TDiretorio diretorio) {
	String sHTML, sCR, sTAB, sTAB2;

	sTAB = char(9);
	sTAB2 = char(9)+char(9);
	if (TOSVersion::Platform == TOSVersion::pfWindows)
		sCR = char(13)+char(10);
	else
		sCR = char(10);

	sHTML = sHTML + sTAB + "<tr>" + sCR;

	sHTML = sHTML + sTAB2 + "<td>" + diretorio.aba.nome + "</td>" + sCR;
	sHTML = sHTML + sTAB2 + "<td>" + diretorio.nome + "</td>" + sCR;
	sHTML = sHTML + sTAB2 + "<td>" + IntToStr(diretorio.tamanho) +
		"</td>" + sCR;
	sHTML = sHTML + sTAB2 + "<td>" + StringReplace(diretorio.tamanhoFormatado,
		" ", "&nbsp;", TReplaceFlags() << rfReplaceAll << rfIgnoreCase) +
		"</td>" + sCR;
	sHTML = sHTML + sTAB2 + "<td>" + diretorio.tipo.nome + "</td>" + sCR;
	sHTML = sHTML + sTAB2 + "<td>" + StringReplace
		(diretorio.modificadoFormatado, " ", "&nbsp;",
		TReplaceFlags() << rfReplaceAll << rfIgnoreCase) + "</td>" + sCR;
	sHTML = sHTML + sTAB2 + "<td>" + diretorio.atributos + "</td>" + sCR;
	sHTML = sHTML + sTAB2 + "<td>" + diretorio.caminho + "</td>" + sCR;

	sHTML = sHTML + sTAB + "</tr>";
	return sHTML;
}

// ---------------------------------------------------------------------------
void TDiretorio::exportarDiretorio(TTipoExportar tipo, TAba aba,
	String sNomeArquivo, TProgressoLog progressoLog) {
	String sTexto, sCR, sTAB, sTAB2;
	TAba abaLocal;
	TDiretorio diretorio;
	TStringList* listaLocal;
	std::vector<TDiretorio> *listaDiretorio;

	sTAB = char(9);
	sTAB2 = char(9)+char(9);
	if (TOSVersion::Platform == TOSVersion::pfWindows)
		sCR = char(13)+char(10);
	else
		sCR = char(10);

	listaDiretorio = new std::vector<TDiretorio>();
	dm->consultaAuxiliar->SQL->Text = SQL_CONSULTA_ARQUIVO + " where aba=" +
		IntToStr(aba.codigo) + " order by 1, 2, 3";
	carregarDiretorio(dm->consultaAuxiliar, listaDiretorio, progressoLog);

	listaLocal = new TStringList();
	try {
		switch (tipo) {
		case TTipoExportar::teCSV: {
				sTexto =
					"\"Aba\";\"Nome\";\"TamanhoBytes\";\"Tamanho\";\"Tipo\";\"Modificado\";\"Atributos\";\"Caminho\"";
			} break;
		case TTipoExportar::teHTML: {
				sTexto = "<!DOCTYPE html>" + sCR;
				sTexto = sTexto + "<html>" + sCR;
				sTexto = sTexto + "<body>" + sCR;
				sTexto =
					sTexto +
					"<table border=\"1\" cellpadding=\"5\" cellspacing=\"0\">" +
					sCR;
				sTexto = sTexto + sTAB + "<tr>" + sCR;
				sTexto = sTexto + sTAB2 + "<th>Aba</th>" + sCR;
				sTexto = sTexto + sTAB2 + "<th>Nome</th>" + sCR;
				sTexto = sTexto + sTAB2 + "<th>Tamanho</th>" + sCR;
				sTexto = sTexto + sTAB2 + "<th>Tamanho Formatado</th>" + sCR;
				sTexto = sTexto + sTAB2 + "<th>Tipo</th>" + sCR;
				sTexto = sTexto + sTAB2 + "<th>Modificado</th>" + sCR;
				sTexto = sTexto + sTAB2 + "<th>Atributos</th>" + sCR;
				sTexto = sTexto + sTAB2 + "<th>Caminho</th>" + sCR;
				sTexto = sTexto + sTAB + "</tr>";
			} break;
		case TTipoExportar::teXML: {
				sTexto = "<diretorio>";
			} break;
		case TTipoExportar::teSQL: {
				abaLocal.codigo = listaDiretorio->at(0).aba.codigo;
				abaLocal.nome = listaDiretorio->at(0).aba.nome;
				sTexto = Aba->abaToSQL(abaLocal);
			} break;
		case TTipoExportar::teTXT: {
			}
		}
		listaLocal->Append(sTexto);

		for (unsigned int i = 0; i < listaDiretorio->size(); i++) {
			diretorio = listaDiretorio->at(i);
			if (diretorio.aba.codigo == aba.codigo) {
				if (tipo == TTipoExportar::teTXT)
					sTexto = diretorioToTXT(diretorio);
				else if (tipo == TTipoExportar::teCSV)
					sTexto = diretorioToCSV(diretorio);
				else if (tipo == TTipoExportar::teHTML)
					sTexto = diretorioToHTML(diretorio);
				else if (tipo == TTipoExportar::teXML)
					sTexto = diretorioToXML(diretorio);
				else if (tipo == TTipoExportar::teSQL)
					sTexto = diretorioToSQL(diretorio, true) + ";";

				listaLocal->Append(sTexto);
			}
		}

		if (tipo == teHTML) {
			sTexto = sTexto + sCR + "</table>" + sCR;
			sTexto = sTexto + "</body>" + sCR;
			sTexto = sTexto + "</html>" + sCR;
		}
		else if (tipo == teXML) {
			sTexto = "</diretorio>";
		}
		listaLocal->Append(sTexto);

		listaLocal->SaveToFile(sNomeArquivo);
	}
	__finally {
		listaLocal->Free();
		listaDiretorio->clear();
		delete listaDiretorio;
	}
}

// ---------------------------------------------------------------------------
bool TDiretorio::criarTabelaDiretorios() {
	String sSQL;

	sSQL = "create table if (NOT EXISTS Diretorios(" \
	 "aba int not null," \
	 "cod int not null," \
	 "ordem int not null," \
	 "nome varchar(255) not null," \
	 "tam numeric not null," \
	 "tipo char(1) not null," \
	 "modificado date not null," \
	 "atributos varchar(20) not null," \
	 "coddirpai int not null," \
	 "caminho varchar(255) not null," \
	 "primary key (aba, cod, ordem))";
	return Rotinas->execConsulta(sSQL, false);
}

// ---------------------------------------------------------------------------
int TDiretorio::importarDiretorioViaXML(TAba aba, String sNomeArquivo,
	std::vector<TDiretorio> *listaDirPai, TStrings* log,
	TProgressoLog progressoLog) {
	String sTexto, sCR, sTAB, sTAB2;
	int nArquivo, resultado;
	TStringList* listaLocal;
	TDiretorio* diretorio;
	std::vector<TDiretorio> *listaDiretorio;

	sTAB = char(9);
	sTAB2 = char(9)+char(9);
	if (TOSVersion::Platform == TOSVersion::pfWindows)
		sCR = char(13)+char(10);
	else
		sCR = char(10);

	resultado = 0;

	diretorio = new TDiretorio();
	listaDiretorio = new std::vector<TDiretorio>();
	listaLocal = new TStringList();
	listaLocal->LoadFromFile(sNomeArquivo);
	try {
		if (listaLocal->Strings[0].Trim() != "<diretorio>")
			resultado = -1;
		else {
			nArquivo = 0;
			for (int i = 0; i < listaLocal->Count; i++) {
				sTexto = listaLocal->Strings[i].Trim();
				nArquivo = XMLParaDiretorio(sTexto, nArquivo, &diretorio);

				if (nArquivo == -1) {
					resultado = -1;
				}
				else if (nArquivo == 13) {
					nArquivo = 1;
					diretorio->aba.codigo = aba.codigo;
					listaDiretorio->push_back(*diretorio);

					if (verificaCodDir(aba.codigo, diretorio->caminho,
						listaDirPai)) {
						resultado = -2;
					}
					diretorio = new TDiretorio();
				}
				else if (nArquivo == -3) {
					resultado = nArquivo;
				}
				else
					nArquivo++;

			}
		}

		salvarDiretorio(listaDiretorio, log, progressoLog);

	}
	__finally {
		listaLocal->Free();
		listaDiretorio->clear();
		delete listaDiretorio;
	}
	return resultado;
}

// ---------------------------------------------------------------------------
int TDiretorio::XMLParaDiretorio(String sTexto, int nArquivo,
	TDiretorio **diretorio) {
	String sTagInicio, sValor, sTagFim;
	int resultado;

	resultado = nArquivo;

	if (Pos(">", sTexto) > 0)
		sTagInicio = sTexto.SubString(1, Pos(">", sTexto));
	if ((Pos(">", sTexto) > 0) && (Pos("</", sTexto) > 1))
		sValor = sTexto.SubString(Pos(">", sTexto) + 1,
				Pos("</", sTexto) - Pos(">", sTexto) - 1);
	if (LastDelimiter(">", sTexto) > 0)
		sTagFim = sTexto.SubString(LastDelimiter("<", sTexto),
		LastDelimiter(">", sTexto));

	if ((nArquivo == 1) && (sTagInicio != "<arquivo>")) {
		resultado = -1;
	}
	if ((nArquivo == 2) && (sTagInicio != "<aba>") && (sTagFim != "</aba>")) {
		// diretorio->aba.codigo = StrToInt(sValor);
		resultado = -1;
	}
	if ((nArquivo == 3) && (sTagInicio != "<nomeAba>") &&
		(sTagFim != "</nomeAba>")) {
		// diretorio->aba.nome = sValor;
		resultado = -1;
	}
	if ((nArquivo == 4) && (sTagInicio == "<codigo>") &&
		(sTagFim == "</codigo>")) {
		(*diretorio)->codigo = StrToInt(sValor);
	}
	if ((nArquivo == 5) && (sTagInicio == "<ordem>") && (sTagFim == "</ordem>"))
	{
		(*diretorio)->ordem = StrToInt(sValor);
	}
	if ((nArquivo == 6) && (sTagInicio == "<nome>") && (sTagFim == "</nome>")) {
		(*diretorio)->nome = sValor;
	}
	if ((nArquivo == 7) && (sTagInicio == "<tamanho>") &&
		(sTagFim == "</tamanho>")) {
		(*diretorio)->tamanho = StrToInt64(sValor);
	}
	if ((nArquivo == 8) && (sTagInicio == "<tipo>") && (sTagFim == "</tipo>")) {
		(*diretorio)->tipo.codigo = sValor[1];
	}
	if ((nArquivo == 9) && (sTagInicio == "<modificado>") &&
		(sTagFim == "</modificado>")) {
		(*diretorio)->modificado = StrToDateTime(sValor);
		(*diretorio)->modificadoFormatado = sValor;
	}
	if ((nArquivo == 10) && (sTagInicio == "<atributos>") &&
		(sTagFim == "</atributos>")) {
		(*diretorio)->atributos = sValor;
	}
	if ((nArquivo == 11) && (sTagInicio == "<codDirPai>") &&
		(sTagFim == "</codDirPai>")) {
		(*diretorio)->codDirPai = StrToInt(sValor);
	}
	if ((nArquivo == 12) && (sTagInicio == "<caminho>") &&
		(sTagFim == "</caminho>")) {
		(*diretorio)->caminho = sValor;
	}
	if ((nArquivo == 13) && (sTagInicio != "</arquivo>")) {
		resultado = -1;
	}
	if (sTagInicio == "</diretorio>") {
		resultado = -3;
	}

	return resultado;

}

// ---------------------------------------------------------------------------
bool TDiretorio::carregarSubDiretorios(String sDiretorio,
	TStringList* listaLocal) {
	TSearchRec SearchRec;
	String sCaminho, sSeparador;

	if (sDiretorio.SubString(sDiretorio.Length(), 1) == BARRA_NORMAL)
		sSeparador = "";
	else
		sSeparador = BARRA_NORMAL;

	sCaminho = sDiretorio + sSeparador + "*.*";
	if (FindFirst(sCaminho, faDirectory, SearchRec) == 0) {

		while (FindNext(SearchRec) == 0) {
			sCaminho = sDiretorio + sSeparador + SearchRec.Name;

			if (SearchRec.Attr == faDirectory) {
				if (DirectoryExists(sCaminho)) {
					if ((SearchRec.Name != ".") && (SearchRec.Name != "..")) {
						listaLocal->Add(sCaminho);
					}
				}
			}
		}
	}
	FindClose(SearchRec);

	return (listaLocal->Count > 0);
}

// ---------------------------------------------------------------------------
bool TDiretorio::carregarArquivos(String sDiretorio, TStringList* listaLocal) {
	TSearchRec SearchRec;
	String sCaminho, sSeparador;

	if (sDiretorio.SubString(sDiretorio.Length(), 1) == BARRA_NORMAL)
		sSeparador = "";
	else
		sSeparador = BARRA_NORMAL;

	sCaminho = sDiretorio + sSeparador + "*.*";
	if (FindFirst(sCaminho, faArchive, SearchRec) == 0) {

		while (FindNext(SearchRec) == 0) {
			sCaminho = sDiretorio + sSeparador + SearchRec.Name;

			if (SearchRec.Attr == faArchive) {
				if (FileExists(sCaminho)) {
					if ((SearchRec.Name != ".") && (SearchRec.Name != "..")) {
						listaLocal->Add(sCaminho);
					}
				}
			}
		}
	}
	FindClose(SearchRec);

	return (listaLocal->Count > 0);
}

// ---------------------------------------------------------------------------
String TDiretorio::MontaTamanho(__int64 nTam) {
	if (nTam > 0) {
		return MontaTamanhoBig(nTam);
	}
	else
		return "";
}

// ---------------------------------------------------------------------------
String TDiretorio::MontaTamanhoBig(Extended nTam) {
	Extended nUmKilo, nUmMega, nUmGiga, nUmTera, nUmPeta;

	nUmKilo = 1024;
	nUmMega = nUmKilo * 1024;
	nUmGiga = nUmMega * 1024;
	nUmTera = nUmGiga * 1024;
	nUmPeta = nUmTera * 1024;

	if ((nTam < nUmKilo)) {
		return FormatFloat("#,##0.00", nTam) + " Byte(s)";
	}
	else if ((nTam > nUmKilo) && (nTam < nUmMega)) {
		nTam = nTam / nUmKilo;
		return FormatFloat("#,##0.00", nTam) + " KByte(s)";
	}
	else if ((nTam > nUmMega) && (nTam < nUmGiga)) {
		nTam = nTam / nUmMega;
		return FormatFloat("#,##0.00", nTam) + " MByte(s)";
	}
	else if ((nTam > nUmGiga) && (nTam < nUmTera)) {
		nTam = nTam / nUmGiga;
		return FormatFloat("#,##0.00", nTam) + " GByte(s)";
	}
	else if ((nTam > nUmTera) && (nTam < nUmPeta)) {
		nTam = nTam / nUmTera;
		return FormatFloat("#,##0.00", nTam) + " TByte(s)";
	}
	else {
		nTam = nTam / nUmPeta;
		return FormatFloat("#,##0.00", nTam) + " PByte(s)";
	}
}

// ---------------------------------------------------------------------------
std::vector<TDiretorio> * TDiretorio::itensFilhos
	(std::vector<TDiretorio> *lista_pai, int aba, int codDirPai, int codigo) {
	std::vector<TDiretorio> *lista;
	TDiretorio diretorio;

	lista = new std::vector<TDiretorio>();
	for (unsigned int i = 0; i < lista_pai->size(); i++) {
		diretorio = lista_pai->at(i);
		if (diretorio.aba.codigo == aba) {
			if (diretorio.codDirPai == codDirPai) {
				if (diretorio.codigo == codigo) {
					lista->push_back(diretorio);
				}
			}
		}
	}
	return lista;
}

// ---------------------------------------------------------------------------
String TDiretorio::arquivoAtributos(int nAtributos) {
	String sAtributos;

	sAtributos = "";
	if ((nAtributos && faReadOnly > 0))
		sAtributos = sAtributos + "[ROL]";
	if ((nAtributos && faHidden > 0))
		sAtributos = sAtributos + "[HID]";
	if ((nAtributos && faSysFile > 0))
		sAtributos = sAtributos + "[SYS]";
	// if ((nAtributos && faVolumeID > 0)) sAtributos=sAtributos+"[VOL]";
	if ((nAtributos && faDirectory > 0))
		sAtributos = sAtributos + "[DIR]";
	if ((nAtributos && faArchive > 0))
		sAtributos = sAtributos + "[ARQ]";
	// if ((nAtributos && faAnyFile > 0)) sAtributos=sAtributos+"[Q]";
	return sAtributos;
}

// ---------------------------------------------------------------------------
int TDiretorio::retCodDirPai(int nAba, String sDiretorio,
	std::vector<TDiretorio> *listaLocal) {
	TDiretorio diretorio;

	for (unsigned int i = 0; i < listaLocal->size(); i++) {
		diretorio = listaLocal->at(i);
		if (diretorio.aba.codigo == nAba) {
			if (diretorio.caminho == sDiretorio) {
				return diretorio.ordem;
			}
		}
	}
	return 0;

}

// ---------------------------------------------------------------------------
TArquivo TDiretorio::searchRecToArquivo(TSearchRec SearchRec) {
	TArquivo arquivo;

	// arquivo = new TArquivo();
	arquivo.nome = SearchRec.Name;
	arquivo.tamanho = SearchRec.Size;
	arquivo.modificado = SearchRec.TimeStamp;
	arquivo.natributos = SearchRec.Attr;
	return arquivo;
}

// ---------------------------------------------------------------------------
String TDiretorio::removerDrive(String sDiretorio) {
	String sDir;

	sDir = sDiretorio.SubString(4, sDiretorio.Length());
	sDir = StringReplace(sDir, BARRA_NORMAL, BARRA_INVERTIDA,
		TReplaceFlags() << rfReplaceAll << rfIgnoreCase);
	return sDir.Trim();
}

// ---------------------------------------------------------------------------
bool TDiretorio::carregarTodosArquivos(String sDiretorio,
	TStringList* listaLocal) {
	TSearchRec SearchRec;
	String sCaminho, sSeparador;

	if (sDiretorio.SubString(sDiretorio.Length(), 1) == BARRA_NORMAL)
		sSeparador = "";
	else
		sSeparador = BARRA_NORMAL;

	sCaminho = sDiretorio + sSeparador + "*.*";
	if (FindFirst(sCaminho, faAnyFile, SearchRec) == 0) {
		sCaminho = sDiretorio + sSeparador + SearchRec.Name;

		if (FileExists(sCaminho)) {
			listaLocal->Add(sCaminho);
		}
		else if (DirectoryExists(sCaminho)) {
			if ((SearchRec.Name != ".") && (SearchRec.Name != "..")) {
				carregarTodosArquivos(sCaminho, listaLocal);
			}
		}

		while (FindNext(SearchRec) == 0) {
			sCaminho = sDiretorio + sSeparador + SearchRec.Name;

			if (FileExists(sCaminho)) {
				listaLocal->Add(sCaminho);
			}
			else if (DirectoryExists(sCaminho)) {
				if ((SearchRec.Name != ".") && (SearchRec.Name != "..")) {
					carregarTodosArquivos(sCaminho, listaLocal);
				}
			}

		}
	}
	FindClose(SearchRec);

	return (listaLocal->Count > 0);
}
// ---------------------------------------------------------------------------
