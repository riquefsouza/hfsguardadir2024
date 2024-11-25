// ---------------------------------------------------------------------------

#pragma hdrstop

#include "Rotinas.h"
#include "Extensao.h"
#include "Diretorio.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
TRotinas *Rotinas;

// ---------------------------------------------------------------------------
TRotinas::TRotinas() {
}

// ---------------------------------------------------------------------------
Boolean TRotinas::criarVisao(String visao) {
	String sSQL;

	sSQL = "create view " + visao + " as " \
 "SELECT d.aba,d.cod,d.ordem,d.coddirpai,d.nome,d.tam,d.tipo,d.modificado," \
 "d.atributos,d.caminho" \
 ",(select nome as nomeaba from Abas where cod=d.aba) as nomeaba" \
 ",(select nome as nomepai from Diretorios where cod=d.cod " \
 "  and ordem=d.coddirpai and aba=d.aba) as nomepai" \
 ",(select caminho as caminhopai from Diretorios where cod=d.cod " \
 " and ordem=d.coddirpai and aba=d.aba) as caminhopai " \
 "FROM Diretorios d ";

	if (visao == "consultadirpai")
		sSQL += "where d.tipo='D' and d.coddirpai = 0";
	else if (visao == "consultadirfilho")
		sSQL += "where d.tipo='D' and d.coddirpai > 0";

	return execConsulta(sSQL, False);
}

// ---------------------------------------------------------------------------
bool TRotinas::execConsulta(String sSQL, bool bComTransacao) {
	dm->consultaAuxiliar->Close();
	dm->consultaAuxiliar->SQL->Text = sSQL;
	return (dm->consultaAuxiliar->ExecSQL() > 0);

}

/*
 bool TRotinas::execConsulta(String sSQL, bool bComTransacao){

 if (bComTransacao) {
 dm->conexao->beginTransaction();
 }

 dm->conexao->ExecSQL(AnsiString(sSQL));

 if (bComTransacao) {
 dm->conexao->Commit();
 }

 return true;
 }
 */
// ---------------------------------------------------------------------------

bool TRotinas::atribuirParamsConexao() {
	String sDLL, sBanco;
	TAba aba;

	sDLL = ExtractFilePath(ParamStr(0)) + "sqlite3.dll";

	if (FileExists(sDLL)) {
		sBanco = ExtractFilePath(ParamStr(0)) + "GuardaDir.db";

		// dm->conexao = new TSQLiteDatabase(sBanco);

		dm->conexao->DriverName = "Sqlite";
		dm->conexao->Params->Clear();
		dm->conexao->Params->Append("DriverName=Sqlite");
		dm->conexao->Params->Append("DriverUnit=Data.DbxSqlite");
		dm->conexao->Params->Append
			("DriverPackageLoader=TDBXSqliteDriverLoader,DBXSqliteDriver210.bpl"
			);
		dm->conexao->Params->Append
			("MetaDataPackageLoader=TDBXSqliteMetaDataCommandFactory,DbxSqliteDriver210.bpl"
			);
		dm->conexao->Params->Append("FailIfMissing=False");
		dm->conexao->Params->Append("Database=" + sBanco);

		if (!FileExists(sBanco)) {

			Aba->criarTabelaAbas();

			aba.codigo = 1;
			aba.nome = "DVD";
			Aba->incluirAba(aba);

			Extensao->criarTabelaExtensoes();
			Diretorio->criarTabelaDiretorios();
			Rotinas->criarVisao("consultadirpai");
			Rotinas->criarVisao("consultadirfilho");
			Rotinas->criarVisao("consultaarquivo");
		}
		else
			dm->conexao->Open();

		return true;
	}
	else
		return false;
}
// ---------------------------------------------------------------------------

String TRotinas::NomeVolumeDrive(const char Drive, String Path) {
	DWord* MaxCompLen;
	DWord* FileSysFlag;
	Cardinal PrevErrorMode;
	String resultado;

	if (Path == "")
		Path = (String)Drive + ":" + BARRA_NORMAL;

	// SetLength(resultado, 255);

	PrevErrorMode = SetErrorMode(SEM_FAILCRITICALERRORS);
	try {
		if (GetVolumeInformation(Path.c_str(), resultado.c_str(), 255, NULL,
			MaxCompLen, FileSysFlag, NULL, 0))
			return resultado;
	}
	__finally {
		SetErrorMode(PrevErrorMode);
	}
	return "";
}
// ---------------------------------------------------------------------------

TIcon* TRotinas::extrairIconeArquivo(String sNomeArquivo) {
	TIcon *icone;
	Word *filtro;

	(*filtro) = 0;
	icone = new TIcon();
	icone->Handle = ExtractAssociatedIcon(HInstance, sNomeArquivo.c_str(),
		filtro);
	return icone;
}
// ---------------------------------------------------------------------------

bool TRotinas::blobParaGIF(TDataSet* ds, TBlobField* campo, TGIFImage* imagem) {
	TStream* Stream;

	imagem = new TGIFImage();
	try {
		Stream = ds->CreateBlobStream(campo, bmRead);
		try {
			Stream->Position = 0;
			imagem->LoadFromStream(Stream);
			return true;
		}
		__finally {
			Stream->Free();
		}
	}
	catch (const Exception& e) {
		return false;
	}
	return false;
}
// ---------------------------------------------------------------------------

TPngImage* TRotinas::blobParaPNG(TDataSet* ds, TBlobField* campo) {
	TStream* Stream;
	TPngImage* imagem;

	imagem = new TPngImage();
	Stream = ds->CreateBlobStream(campo, bmRead);
	try {
		Stream->Position = 0;
		imagem->LoadFromStream(Stream);
	}
	__finally {
		Stream->Free();
	}
	return imagem;
}
// ---------------------------------------------------------------------------

void TRotinas::GIFParaBlob(TGIFImage* imagem, TDataSet* ds, TBlobField* campo) {
	TStream* blob;
	TMemoryStream* ms;

	blob = ds->CreateBlobStream(campo, bmWrite);
	ms = new TMemoryStream();
	try {
		imagem->SaveToStream(ms);
		ms->Position = 0;
		blob->Seek(0, soFromBeginning);
		blob->CopyFrom(ms, ms->Size);
	}
	__finally {
		ms->Free();
		blob->Free();
	}
}
// ---------------------------------------------------------------------------

void TRotinas::PNGParaBlob(TPngImage* imagem, TDataSet* ds, TBlobField* campo) {
	TStream* blob;
	TMemoryStream* ms;

	blob = ds->CreateBlobStream(campo, bmWrite);
	ms = new TMemoryStream();
	try {
		imagem->SaveToStream(ms);
		ms->Position = 0;
		blob->Seek(0, soFromBeginning);
		blob->CopyFrom(ms, ms->Size);
	}
	__finally {
		ms->Free();
		blob->Free();
	}
}
// ---------------------------------------------------------------------------

TJPEGImage* TRotinas::blobParaJPG(TDataSet* ds, TBlobField* campo) {
	TStream* blob;
	TMemoryStream* ms;
	TJPEGImage* imagem;

	imagem = new TJPEGImage();
	// imagem->CompressionQuality = 100;
	blob = ds->CreateBlobStream(campo, bmRead);
	ms = new TMemoryStream();
	try {
		blob->Seek(0, soFromBeginning);
		ms->CopyFrom(blob, blob->Size);
		ms->Position = 0;
		imagem->LoadFromStream(ms);
	}
	__finally {
		ms->Free();
		blob->Free();
	}
	return imagem;
}
// ---------------------------------------------------------------------------

void TRotinas::JPGParaBlob(TJPEGImage* imagem, TDataSet* ds, TBlobField* campo)
{
	TStream* blob;
	TMemoryStream* ms;

	blob = ds->CreateBlobStream(campo, bmWrite);
	ms = new TMemoryStream();
	try {
		imagem->CompressionQuality = 100;
		imagem->SaveToStream(ms);

		ms->Position = 0;
		blob->Seek(0, soFromBeginning);
		blob->CopyFrom(ms, ms->Size);
	}
	__finally {
		ms->Free();
		blob->Free();
	}
}
// ---------------------------------------------------------------------------

TIcon* TRotinas::blobParaIcone(TDataSet* ds, TBlobField* campo) {
	TStream* Stream;
	TIcon* imagem;

	imagem = new TIcon();
	Stream = ds->CreateBlobStream(campo, bmReadWrite);
	try {
		Stream->Position = 0;
		imagem->LoadFromStream(Stream);
	}
	__finally {
		Stream->Free();
	}
	return imagem;
}
// ---------------------------------------------------------------------------

Vcl::Graphics::TBitmap* TRotinas::blobParaBMP(TDataSet* ds, TBlobField* campo) {
	TStream* Stream;
	Vcl::Graphics::TBitmap* imagem;

	imagem = new Vcl::Graphics::TBitmap();
	Stream = ds->CreateBlobStream(campo, bmReadWrite);
	try {
		Stream->Position = 0;
		imagem->LoadFromStream(Stream);
	}
	__finally {
		Stream->Free();
	}
	return imagem;
}
// ---------------------------------------------------------------------------

void TRotinas::IconeParaBlob(TIcon* imagem, TDataSet* ds, TBlobField* campo) {
	TStream* blob;
	TMemoryStream* ms;

	blob = ds->CreateBlobStream(campo, bmWrite);
	ms = new TMemoryStream();
	try {
		imagem->SaveToStream(ms);
		ms->Position = 0;
		blob->Seek(0, soFromBeginning);
		blob->CopyFrom(ms, ms->Size);
	}
	__finally {
		ms->Free();
		blob->Free();
	}
}
// ---------------------------------------------------------------------------

void TRotinas::BMPParaBlob(Vcl::Graphics::TBitmap* imagem, TDataSet* ds,
	TBlobField* campo) {
	TStream* blob;
	TMemoryStream* ms;

	blob = ds->CreateBlobStream(campo, bmWrite);
	ms = new TMemoryStream();
	try {
		imagem->SaveToStream(ms);
		ms->Position = 0;
		blob->Seek(0, soFromBeginning);
		blob->CopyFrom(ms, ms->Size);
	}
	__finally {
		ms->Free();
		blob->Free();
	}
}
// ---------------------------------------------------------------------------

Vcl::Graphics::TBitmap* TRotinas::IconeParaBmp(TIcon* Icone, int nTamanho) {
	// IconInfo: TIconInfo;
	Vcl::Graphics::TBitmap* bmp;

	// GetIconInfo( Icone->Handle, IconInfo );
	bmp = new Vcl::Graphics::TBitmap();
	// bmp->Width = ( IconInfo->xHotspot * 2 );
	// bmp->Height = ( IconInfo->yHotspot * 2 );
	bmp->Width = nTamanho;
	bmp->Height = nTamanho;
	// para salvar bmp com formato de 256 cores
	// bmp->PixelFormat = pf8bit;
	// bmp->PixelFormat = pfDevice;
	// bmp->Transparent = True;
	// bmp->TransparentMode = tmAuto;
	bmp->Canvas->StretchDraw(Rect(0, 0, bmp->Width, bmp->Height), Icone);

	return bmp;
}
// ---------------------------------------------------------------------------

TIcon* TRotinas::BmpParaIcone(Vcl::Graphics::TBitmap* Bitmap) {
	TIconInfo* IconInfo;
	TIcon* icone;

	IconInfo->fIcon = true;
	IconInfo->xHotspot = Bitmap->Width;
	IconInfo->yHotspot = Bitmap->Height;
	IconInfo->hbmColor = Bitmap->Handle;
	IconInfo->hbmMask = Bitmap->MaskHandle;
	icone = new TIcon();
	icone->Handle = CreateIconIndirect(IconInfo);
	return icone;
}
// ---------------------------------------------------------------------------

TGIFImage* TRotinas::BMPParaGIF(Vcl::Graphics::TBitmap* bmp) {
	TGIFImage* gif;

	gif = new TGIFImage();
	gif->Width = bmp->Width;
	gif->Height = bmp->Height;
	gif->Assign(bmp);
	return gif;
}
// ---------------------------------------------------------------------------

Vcl::Graphics::TBitmap* TRotinas::GIFParaBMP(TGIFImage* gif, int nTamanho) {
	Vcl::Graphics::TBitmap* bmp;

	bmp = new Vcl::Graphics::TBitmap();
	bmp->Width = nTamanho;
	bmp->Height = nTamanho;
	// para salvar bmp com formato de 256 cores
	bmp->PixelFormat = pf8bit;
	bmp->Canvas->StretchDraw(Rect(0, 0, bmp->Width, bmp->Height), gif);
	// bmp->Assign(gif);
	return bmp;
}
// ---------------------------------------------------------------------------

TJPEGImage* TRotinas::BMPParaJPG(Vcl::Graphics::TBitmap* bmp) {
	TJPEGImage* jpg;

	jpg = new TJPEGImage();
	jpg->CompressionQuality = 100;
	jpg->Assign(bmp);
	return jpg;
}
// ---------------------------------------------------------------------------

Vcl::Graphics::TBitmap* TRotinas::JPGParaBMP(TJPEGImage* jpg, int nTamanho) {
	Vcl::Graphics::TBitmap* bmp;

	bmp = new Vcl::Graphics::TBitmap();
	bmp->Width = nTamanho;
	bmp->Height = nTamanho;
	// para salvar bmp com formato de 256 cores
	bmp->PixelFormat = pf8bit;
	bmp->Canvas->StretchDraw(Rect(0, 0, bmp->Width, bmp->Height), jpg);
	// bmp->Assign(jpg);
	return bmp;
}
// ---------------------------------------------------------------------------

TPngImage* TRotinas::BMPParaPNG(Vcl::Graphics::TBitmap* bmp) {
	TPngImage* png;

	png = new TPngImage();
	png->Assign(bmp);
	return png;
}
// ---------------------------------------------------------------------------

Vcl::Graphics::TBitmap* TRotinas::PNGParaBMP(TPngImage* png, int nTamanho) {
	Vcl::Graphics::TBitmap* bmp;

	bmp = new Vcl::Graphics::TBitmap();
	bmp->Width = nTamanho;
	bmp->Height = nTamanho;
	// para salvar bmp com formato de 256 cores
	bmp->PixelFormat = pf8bit;
	bmp->Canvas->StretchDraw(Rect(0, 0, bmp->Width, bmp->Height), png);
	// bmp->Assign(png);
	return bmp;
}
// ---------------------------------------------------------------------------

void TRotinas::BMPParaTIF(Vcl::Graphics::TBitmap* bmp, String sArquivo) {
	// WriteTiffToFile(sArquivo, bmp );
}
// ---------------------------------------------------------------------------

TTipoExportarExtensao TRotinas::DetectImage(const String InputFileName,
	Vcl::Graphics::TBitmap* BM) {
	TFileStream* FS;
	AnsiString FirstBytes;
	char cFirstBytes[8];
	TGraphic* Graphic;
	TTipoExportarExtensao resultado;
	String firstPNG;

	resultado = TTipoExportarExtensao::teNUL;

	firstPNG = AnsiChar(137);
	firstPNG += "PNG";
	firstPNG += AnsiChar(13) + AnsiChar(10) + AnsiChar(26) + AnsiChar(10);

	Graphic = NULL;
	FS = new TFileStream(InputFileName, fmOpenRead);
	try {
		// SetLength(FirstBytes, 8);
		// cFirstBytes = (char*)malloc(8);
		FS->Read(&cFirstBytes[1], 8);
		FirstBytes = cFirstBytes;

		if (FirstBytes.SubString(1, 2) == "BM") {
			Graphic = new Vcl::Graphics::TBitmap();
			resultado = teBMP;
		}
		else if (FirstBytes == firstPNG) {
			Graphic = new TPngImage();
			resultado = tePNG;
		}
		else if (FirstBytes.SubString(1, 3) == "GIF") {
			Graphic = new TGIFImage();
			resultado = teGIF;
		}
		else if (FirstBytes.SubString(1, 2) == '\xFF' + '\xD8') {
			Graphic = new TJPEGImage();
			resultado = teJPG;
		}
		if (Graphic != NULL) {
			try {
				FS->Seek(0, soFromBeginning);
				Graphic->LoadFromStream(FS);
				BM->Assign(Graphic);
			}
			catch (const Exception& e) {
			}
			Graphic->Free();
		}
	}
	__finally {
		FS->Free();
	}
	return resultado;
}
// ---------------------------------------------------------------------------

TIcon* TRotinas::StreamParaIcone(TMemoryStream* ms) {
	TIcon* imagem;

	imagem = new TIcon();
	ms->Position = 0;
	imagem->LoadFromStream(ms);
	return imagem;
}
// ---------------------------------------------------------------------------

TGIFImage* TRotinas::StreamParaGIF(TMemoryStream* ms) {
	TGIFImage* imagem;

	imagem = new TGIFImage();
	ms->Position = 0;
	imagem->LoadFromStream(ms);
	return imagem;
}
// ---------------------------------------------------------------------------

TJPEGImage* TRotinas::StreamParaJPG(TMemoryStream* ms) {
	TJPEGImage* imagem;

	imagem = new TJPEGImage();
	imagem->CompressionQuality = 100;

	ms->Position = 0;
	imagem->LoadFromStream(ms);
	return imagem;
}
// ---------------------------------------------------------------------------

TMemoryStream* TRotinas::JPGParaStream(TJPEGImage* imagem) {
	TMemoryStream* ms;

	ms = new TMemoryStream();
	imagem->SaveToStream(ms);
	ms->Position = 0;
	return ms;
}
// ---------------------------------------------------------------------------

void TRotinas::StreamParaBlob(TMemoryStream* ms, TDataSet* ds,
	TBlobField* campo) {
	TStream* blob;

	blob = ds->CreateBlobStream(campo, bmWrite);
	try {
		ms->Position = 0;
		blob->Seek(0, soFromBeginning);
		blob->CopyFrom(ms, ms->Size);
	}
	__finally {
		ms->Free();
		blob->Free();
	}
}
// ---------------------------------------------------------------------------

Vcl::Graphics::TBitmap* TRotinas::RedimensionarBMP
	(Vcl::Graphics::TBitmap* imagem, int nTamanho) {
	Vcl::Graphics::TBitmap* bmp;

	bmp = new Vcl::Graphics::TBitmap();
	bmp->Width = nTamanho;
	bmp->Height = nTamanho;
	// bmp->PixelFormat = pf8bit;
	// bmp->Transparent = True;
	// bmp->TransparentMode = tmAuto;
	bmp->Canvas->StretchDraw(Rect(0, 0, bmp->Width, bmp->Height), imagem);
	return bmp;
}
// ---------------------------------------------------------------------------

Vcl::Graphics::TBitmap* TRotinas::StreamParaBMP(TMemoryStream* ms) {
	Vcl::Graphics::TBitmap* imagem;

	imagem = new Vcl::Graphics::TBitmap();
	ms->Position = 0;
	imagem->LoadFromStream(ms);
	return imagem;
}
// ---------------------------------------------------------------------------
int TRotinas::CompareTextAsInteger(const String s1, const String s2) {
	return CompareValue(StrToInt(s1), StrToInt(s2));
}
// ---------------------------------------------------------------------------
int TRotinas::CompareTextAsDateTime(const String s1, const String s2) {
	return CompareDateTime(StrToDateTime(s1), StrToDateTime(s2));
}
// ---------------------------------------------------------------------------
