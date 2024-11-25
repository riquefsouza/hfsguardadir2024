// ---------------------------------------------------------------------------

#pragma hdrstop

#include "Extensao.h"
#include "DataModule.h"
#include <Vcl.Dialogs.hpp>
#include <System.UITypes.hpp>
// ---------------------------------------------------------------------------
#pragma package(smart_init)
TExtensao *Extensao;

// ---------------------------------------------------------------------------
TExtensao::TExtensao() {
}

// ---------------------------------------------------------------------------
void TExtensao::carregarExtensao(std::vector<TExtensao> *listaExtensao,
	TProgressoLog progressoLog) {
	TExtensao extensao;
	int total;
	// TMemoryStream *msBMP16, *msBMP32;
	TBlobField *campoBMP16, *campoBMP32;
	TProgresso pb;

	listaExtensao->clear();

	dm->tabelaExtensoes->Open();
	total = dm->tabelaExtensoes->RecordCount;
	dm->tabelaExtensoes->First();
	/*
	 dm->tabelaExtensoes = dm->conexao->GetTable(AnsiString(dm->SQLExtensoes));
	 total = dm->tabelaExtensoes->Count;
	 dm->tabelaExtensoes->MoveFirst;
	 */
	if (total > 0) {
		pb.minimo = 0;
		pb.maximo = total - 1;
		pb.posicao = 0;
		pb.passo = 1;

		for (int i = 0; i < total; i++) {
			// Extensao = TExtensao();

			extensao.codigo = dm->tabelaExtensoes->Fields->FieldByNumber(1)
				->AsInteger;
			extensao.nome = dm->tabelaExtensoes->Fields->FieldByNumber(2)
				->AsString;
			campoBMP16 =
				(TBlobField*) dm->tabelaExtensoes->Fields->FieldByNumber(3);
			campoBMP32 =
				(TBlobField*) dm->tabelaExtensoes->Fields->FieldByNumber(4);
			extensao.bmp32 = Rotinas->blobParaBMP(dm->tabelaExtensoes,
				campoBMP32);
			extensao.bmp16 = Rotinas->blobParaBMP(dm->tabelaExtensoes,
				campoBMP16);

			/*
			 extensao.codigo =
			 StrToInt(dm->tabelaExtensoes->FieldAsString
			 (dm->tabelaExtensoes->FieldIndex["cod"]));
			 extensao.nome = dm->tabelaExtensoes->FieldAsString
			 (dm->tabelaExtensoes->FieldIndex["nome"]);

			 msBMP16 = dm->tabelaExtensoes->FieldAsBlob
			 (dm->tabelaExtensoes->FieldIndex["bmp16"]);
			 extensao.bmp16 = Rotinas->StreamParaBMP(msBMP16);
			 msBMP16->Free();

			 msBMP32 = dm->tabelaExtensoes->FieldAsBlob
			 (dm->tabelaExtensoes->FieldIndex["bmp32"]);
			 extensao.bmp32 = Rotinas->StreamParaBMP(msBMP32);
			 msBMP32->Free();
			 */
			extensao.ordem = (i+1);

			listaExtensao->push_back(extensao);

			dm->tabelaExtensoes->Next();

			pb.posicao = i;

			if (progressoLog!=NULL) {
				progressoLog(pb);
			}
		}
	}

	dm->tabelaExtensoes->Close();
}

// ---------------------------------------------------------------------------
bool TExtensao::existeExtensao(String sExtensao,
	std::vector<TExtensao> *listaLocal) {
	TExtensao extensao;

	if (sExtensao.Trim().Length() > 0) {
		for (unsigned int i = 0; i < listaLocal->size(); i++) {
			extensao = listaLocal->at(i);
			if (extensao.nome.Trim().LowerCase() == sExtensao.Trim()
				.LowerCase()) {
				return true;
			}
		}
	}
	return false;
}

// ---------------------------------------------------------------------------
int TExtensao::retMaxCodExtensao(std::vector<TExtensao> *listaLocal) {
	int nMaior;
	TExtensao extensao;

	nMaior = 0;

	for (unsigned int i = 0; i < listaLocal->size(); i++) {
		extensao = listaLocal->at(i);
		if ((extensao.codigo > nMaior)) {
			nMaior = extensao.codigo;
		}
	}

	return nMaior + 1;
}

// ---------------------------------------------------------------------------
bool TExtensao::SalvarExtensao(std::vector<TExtensao> *listaExtensao,
	String sNomeDiretorio, String sCaminhoOriginal, TStrings* log) {
	String sExtensao;
	TExtensao extensao;
	TIcon *icone;

	if (LastDelimiter(".", sNomeDiretorio) > 0) {
		sExtensao = sNomeDiretorio.SubString
			(LastDelimiter(".", sNomeDiretorio) + 1, sNomeDiretorio.Length());
		if (!existeExtensao(sExtensao, listaExtensao)) {
			// extensao = new TExtensao();
			extensao.codigo = retMaxCodExtensao(listaExtensao);
			extensao.nome = LowerCase(sExtensao);
			icone = Rotinas->extrairIconeArquivo(sCaminhoOriginal);
			extensao.bmp32 = Rotinas->IconeParaBmp(icone, 32);
			extensao.bmp16 = Rotinas->RedimensionarBMP(extensao.bmp32, 16);
			incluirExtensao(extensao);
			listaExtensao->push_back(extensao);
			log->Append("Salvando Extensão: " + extensao.nome);
			return true;
		}
	}
	return false;

}

// ---------------------------------------------------------------------------
void TExtensao::salvarExtensoes(std::vector<TDiretorio> *listaDiretorio,
	std::vector<TExtensao> *listaExtensao, TStrings* log,
	TProgressoLog progressoLog) {

	TDiretorio diretorio;
	TProgresso pb;

	pb.minimo = 0;
	pb.maximo = listaDiretorio->size() - 1;
	pb.posicao = 0;
	pb.passo = 1;

	dm->cdsExtensoes->Open();
	// dm->conexao->beginTransaction;
	for (unsigned int i = 0; i < listaDiretorio->size(); i++) {
		diretorio = listaDiretorio->at(i);

		if (diretorio.tipo.codigo == 'A') {
			SalvarExtensao(listaExtensao, diretorio.nome,
				diretorio.caminhoOriginal, log);
		}

		pb.posicao = i;

		if (progressoLog!=NULL) {
			progressoLog(pb);
		};
	}
	// dm->conexao->Commit;
	dm->cdsExtensoes->ApplyUpdates(0);
	dm->cdsExtensoes->Close();

}

// ---------------------------------------------------------------------------
/*
String TExtensao::extensaoToSQL(TExtensao extensao, bool bInsert) {
	String sSQL;

	if (bInsert) {
		sSQL = "insert into Extensoes(cod, nome) values(";
	}

	sSQL = sSQL + IntToStr(extensao.codigo) + ",";
	sSQL = sSQL + QuotedStr(extensao.nome);

	if (bInsert)
		sSQL = sSQL + ")";
	return sSQL;
}
*/
// ---------------------------------------------------------------------------
bool TExtensao::excluirExtensao(std::vector<TExtensao> *listaExtensao,
	int codigo) {
	String sSQL;
	TExtensao extensao;
	std::vector<TExtensao>::iterator it;

	sSQL = "delete from Extensoes where cod=" + IntToStr(codigo);
	if (Rotinas->execConsulta(sSQL, true)) {

		// for (unsigned int i = 0; i < listaExtensao->size(); i++) {
		for (it = listaExtensao->begin(); it != listaExtensao->end(); it++) {
			extensao = *it; // listaExtensao->at(i);
			if (extensao.codigo == codigo) {
				listaExtensao->erase(it);
				break;
			}
		}
		return true;
	}
	else {
		return false;
	}

}

// ---------------------------------------------------------------------------
bool TExtensao::excluirTodasExtensoes(std::vector<TExtensao> *listaExtensao) {
	String sSQL;

	sSQL = "delete from Extensoes";
	if (Rotinas->execConsulta(sSQL, true)) {
		listaExtensao->clear();
		return true;
	}
	else {
		return false;
	}
}

// ---------------------------------------------------------------------------
bool TExtensao::criarTabelaExtensoes() {
	String sSQL;

	sSQL = "create table if (NOT EXISTS Extensoes(" \
	 "cod int not null," \
	 "nome varchar(20) not null," \
	 "bmp16 BLOB COLLATE NOCASE null," \
	 "bmp32 BLOB COLLATE NOCASE null," \
	 "primary key (cod))";
	return Rotinas->execConsulta(sSQL, false);
}

// ---------------------------------------------------------------------------
/*
 void TExtensao::incluirExtensao(TExtensao extensao) {
 String sSQL;
 TMemoryStream* ms;

 sSQL = extensaoToSQL(extensao, true);
 Rotinas->execConsulta(sSQL, false);

 ms = new TMemoryStream();
 try {
 extensao->bmp16->SaveToStream(ms);
 ms->Position = 0;
 dm->conexao->UpdateBlob
 (AnsiString("UPDATE Extensoes set bmp16=? WHERE cod=" +
 IntToStr(extensao->codigo)), ms);
 }
 __finally {
 ms->Free();
 }

 ms = new TMemoryStream();
 try {
 extensao->bmp32->SaveToStream(ms);
 ms->Position = 0;
 dm->conexao->UpdateBlob
 (AnsiString("UPDATE Extensoes set bmp32=? WHERE cod=" +
 IntToStr(extensao->codigo)), ms);
 }
 __finally {
 ms->Free();
 }
 }
 */
void TExtensao::incluirExtensao(TExtensao extensao) {
	TBlobField *campoBMP16, *campoBMP32;

	if (dm->cdsExtensoes->Active) {
		dm->cdsExtensoes->ReadOnly = false;
		dm->cdsExtensoes->Append();
		dm->cdsExtensoes->Fields->FieldByNumber(1)->Value = extensao.codigo;
		dm->cdsExtensoes->Fields->FieldByNumber(2)->Value = extensao.nome;
		campoBMP16 = (TBlobField*)dm->cdsExtensoes->Fields->FieldByNumber(3);
		campoBMP32 = (TBlobField*)dm->cdsExtensoes->Fields->FieldByNumber(4);

		Rotinas->BMPParaBlob(extensao.bmp16, dm->cdsExtensoes, campoBMP16);
		Rotinas->BMPParaBlob(extensao.bmp32, dm->cdsExtensoes, campoBMP32);

		dm->cdsExtensoes->Post();
	}
}

// ---------------------------------------------------------------------------
void TExtensao::carregarExtensoes(std::vector<TExtensao> *lista,
	TImageList* listaImg16, TImageList* listaImg32) {
	TExtensao extensao;

	for (unsigned int i = 0; i < lista->size(); i++) {
		extensao = lista->at(i);
		listaImg16->Add(extensao.bmp16, NULL);
		listaImg32->Add(extensao.bmp32, NULL);
	}

}

// ---------------------------------------------------------------------------
int TExtensao::indiceExtensao(std::vector<TExtensao> *lista,
	String nomeExtensao) {
	TExtensao extensao;

	nomeExtensao = nomeExtensao.SubString(LastDelimiter(".", nomeExtensao) + 1,
		nomeExtensao.Length());

	for (unsigned int i = 0; i < lista->size(); i++) {
		extensao = lista->at(i);
		if (extensao.nome.Trim().LowerCase() == nomeExtensao.Trim().LowerCase())
		{
			return (extensao.ordem + 1);
		}
	}
	return -1;
}

// ---------------------------------------------------------------------------
void TExtensao::ExportarExtensao(TTipoExportarExtensao tipo,
	std::vector<TExtensao> *listaExtensao) {
	String sCaminho, sImg16, sImg32, sExtensao;
	TExtensao extensao;
	TIcon* icone;
	TGIFImage* gifImagem;
	TJPEGImage* jpgImagem;
	TPngImage* pngImagem;

	if (listaExtensao->size() > 0) {
		sCaminho = ExtractFilePath(ParamStr(0));

		if (tipo == TTipoExportarExtensao::teBMP)
			sExtensao = ".bmp";
		else if (tipo == TTipoExportarExtensao::teICO)
			sExtensao = ".ico";
		else if (tipo == TTipoExportarExtensao::teGIF)
			sExtensao = ".gif";
		else if (tipo == TTipoExportarExtensao::teJPG)
			sExtensao = ".jpg";
		else if (tipo == TTipoExportarExtensao::tePNG)
			sExtensao = ".png";
		else if (tipo == TTipoExportarExtensao::teTIF)
			sExtensao = ".tif";

		for (unsigned int i = 0; i < listaExtensao->size(); i++) {
			extensao = listaExtensao->at(i);

			sImg16 = sCaminho + extensao.nome + "16" + sExtensao;
			if (FileExists(sImg16))
				DeleteFile(sImg16);

			sImg32 = sCaminho + extensao.nome + "32" + sExtensao; ;
			if (FileExists(sImg32))
				DeleteFile(sImg32);

			switch (tipo) {
			case TTipoExportarExtensao::teBMP: {
					extensao.bmp16->SaveToFile(sImg16);
					extensao.bmp32->SaveToFile(sImg32);
				} break;
			case TTipoExportarExtensao::teICO: {
					icone = Rotinas->BmpParaIcone(extensao.bmp16);
					icone->SaveToFile(sImg16);
					icone->Free();

					icone = Rotinas->BmpParaIcone(extensao.bmp32);
					icone->SaveToFile(sImg32);
					icone->Free();
				} break;
			case TTipoExportarExtensao::teGIF: {
					gifImagem = Rotinas->BMPParaGIF(extensao.bmp16);
					gifImagem->SaveToFile(sImg16);
					gifImagem->Free();

					gifImagem = Rotinas->BMPParaGIF(extensao.bmp32);
					gifImagem->SaveToFile(sImg32);
					gifImagem->Free();
				} break;
			case TTipoExportarExtensao::teJPG: {
					jpgImagem = Rotinas->BMPParaJPG(extensao.bmp16);
					jpgImagem->SaveToFile(sImg16);
					jpgImagem->Free();

					jpgImagem = Rotinas->BMPParaJPG(extensao.bmp32);
					jpgImagem->SaveToFile(sImg32);
					jpgImagem->Free();
				} break;
			case TTipoExportarExtensao::tePNG: {
					pngImagem = Rotinas->BMPParaPNG(extensao.bmp16);
					pngImagem->SaveToFile(sImg16);
					pngImagem->Free();

					pngImagem = Rotinas->BMPParaPNG(extensao.bmp32);
					pngImagem->SaveToFile(sImg32);
					pngImagem->Free();
				} break;
			case TTipoExportarExtensao::teTIF: {
					Rotinas->BMPParaTIF(extensao.bmp16, sImg16);
					Rotinas->BMPParaTIF(extensao.bmp32, sImg32);
				} break;
			case TTipoExportarExtensao::teNUL: {
				}
			}

		}
		MessageDlg("Ícones salvos no mesmo diretório do sistema!",
			mtInformation, TMsgDlgButtons() << mbOK, 0);
	}
}

// ---------------------------------------------------------------------------
TExtensao TExtensao::pegaExtensaoPorOrdem(std::vector<TExtensao> *lista,
	int ordem) {
	TExtensao extensao;

	for (unsigned int i = 0; i < lista->size(); i++) {
		extensao = lista->at(i);
		if (extensao.ordem == ordem) {
			return extensao;
		}
	}
	return extensao;
}

// ---------------------------------------------------------------------------
void TExtensao::ImportarExtensao(String caminho,
	std::vector<TExtensao> *listaExtensao) {
	TStringList* listaArquivos;
	TExtensao extensao;
	String sExtensao, sArquivo;
	TTipoExportarExtensao tipo;
	Vcl::Graphics::TBitmap* bmp;

	listaArquivos = new TStringList();
	try {
		if (Diretorio->carregarArquivos(caminho, listaArquivos)) {

			// dm->conexao->beginTransaction;
			dm->cdsExtensoes->Open();
			for (int i = 0; i < listaArquivos->Count; i++) {
				sArquivo = listaArquivos->Strings[i];
				sExtensao =
					sArquivo.SubString(LastDelimiter(BARRA_NORMAL, sArquivo) +
					1, sArquivo.Length());
				sExtensao = sExtensao.SubString(1, Pos(".", sExtensao) - 1);

				if (!existeExtensao(sExtensao, listaExtensao)) {
					bmp = new Vcl::Graphics::TBitmap();
					tipo = Rotinas->DetectImage(sArquivo, bmp);

					if (tipo != teNUL) {
						// extensao = new TExtensao();
						extensao.codigo = retMaxCodExtensao(listaExtensao);
						extensao.nome = LowerCase(sExtensao);
						extensao.bmp32 = Rotinas->RedimensionarBMP(bmp, 32);
						extensao.bmp16 = Rotinas->RedimensionarBMP(bmp, 16);

						incluirExtensao(extensao);
						listaExtensao->push_back(extensao);
					}
				}
			}
			// dm->conexao->Commit;
			dm->cdsExtensoes->ApplyUpdates(0);
			dm->cdsExtensoes->Close();
		}
	}
	__finally {
		listaArquivos->Free();
	}
}

// ---------------------------------------------------------------------------
void TExtensao::ExtrairExtensao(String caminho,
	std::vector<TExtensao> *listaExtensao) {
	TStringList* listaArquivos;
	String sArquivo;
	TStringList* log;

	listaArquivos = new TStringList();
	log = new TStringList();
	try {
		if (Diretorio->carregarTodosArquivos(caminho, listaArquivos)) {

			// dm->conexao->beginTransaction;
			dm->cdsExtensoes->Open();
			for (int i = 0; i < listaArquivos->Count; i++) {
				sArquivo = listaArquivos->Strings[i];
				SalvarExtensao(listaExtensao, ExtractFileName(sArquivo),
					sArquivo, log);
			}
			// dm->conexao->Commit;
			dm->cdsExtensoes->ApplyUpdates(0);
			dm->cdsExtensoes->Close();
		}
	}
	__finally {
		listaArquivos->Free();
		log->Free();
	}
}
// ---------------------------------------------------------------------------
