// ---------------------------------------------------------------------------

#ifndef RotinasH
#define RotinasH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.StrUtils.hpp>
#include <System.Math.hpp>
#include <System.DateUtils.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include <Data.DB.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Imaging.GIFImg.hpp>
#include <Vcl.Imaging.Jpeg.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include "Windows.h"
#include "ShellAPI.h"
#include "DataModule.h"
// ---------------------------------------------------------------------------
const char BARRA_NORMAL = '\\';
const char BARRA_INVERTIDA = '/';

enum TTipoExportarExtensao {
	teNUL, teBMP, teICO, teGIF, teJPG, tePNG, teTIF
};

struct TProgresso {
	int minimo;
	int maximo;
	int posicao;
	int passo;
};

typedef void TProgressoLog(TProgresso);

class TRotinas {
private: // User declarations
public : // User declarations
	TRotinas();
	bool criarVisao(String visao);
	bool execConsulta(String sSQL, bool bComTransacao);
	bool atribuirParamsConexao();
	String NomeVolumeDrive(const char Drive, String Path);
	TIcon* extrairIconeArquivo(String sNomeArquivo);
	bool blobParaGIF(TDataSet* ds, TBlobField* campo, TGIFImage* imagem);
	TPngImage* blobParaPNG(TDataSet* ds, TBlobField* campo);
	void GIFParaBlob(TGIFImage* imagem, TDataSet* ds, TBlobField* campo);
	void PNGParaBlob(TPngImage* imagem, TDataSet* ds, TBlobField* campo);
	TJPEGImage* blobParaJPG(TDataSet* ds, TBlobField* campo);
	void JPGParaBlob(TJPEGImage* imagem, TDataSet* ds, TBlobField* campo);
	TIcon* blobParaIcone(TDataSet* ds, TBlobField* campo);
	Vcl::Graphics::TBitmap* blobParaBMP(TDataSet* ds, TBlobField* campo);
	void IconeParaBlob(TIcon* imagem, TDataSet* ds, TBlobField* campo);
	void BMPParaBlob(Vcl::Graphics::TBitmap* imagem, TDataSet* ds,
		TBlobField* campo);
	Vcl::Graphics::TBitmap* IconeParaBmp(TIcon* Icone, int nTamanho);
	TIcon* BmpParaIcone(Vcl::Graphics::TBitmap* Bitmap);
	TGIFImage* BMPParaGIF(Vcl::Graphics::TBitmap* bmp);
	Vcl::Graphics::TBitmap* GIFParaBMP(TGIFImage* gif, int nTamanho);
	TJPEGImage* BMPParaJPG(Vcl::Graphics::TBitmap* bmp);
	Vcl::Graphics::TBitmap* JPGParaBMP(TJPEGImage* jpg, int nTamanho);
	TPngImage* BMPParaPNG(Vcl::Graphics::TBitmap* bmp);
	Vcl::Graphics::TBitmap* PNGParaBMP(TPngImage* png, int nTamanho);
	void BMPParaTIF(Vcl::Graphics::TBitmap* bmp, String sArquivo);
	TTipoExportarExtensao DetectImage(const String InputFileName,
		Vcl::Graphics::TBitmap* BM);
	TIcon* StreamParaIcone(TMemoryStream* ms);
	TGIFImage* StreamParaGIF(TMemoryStream* ms);
	TJPEGImage* StreamParaJPG(TMemoryStream* ms);
	TMemoryStream* JPGParaStream(TJPEGImage* imagem);
	void StreamParaBlob(TMemoryStream* ms, TDataSet* ds, TBlobField* campo);
	Vcl::Graphics::TBitmap* RedimensionarBMP(Vcl::Graphics::TBitmap* imagem,
		int nTamanho);
	Vcl::Graphics::TBitmap* StreamParaBMP(TMemoryStream* ms);
	int CompareTextAsInteger(const String s1, const String s2);
	int CompareTextAsDateTime(const String s1, const String s2);
};

// ---------------------------------------------------------------------------
extern PACKAGE TRotinas *Rotinas;
// ---------------------------------------------------------------------------
#endif
