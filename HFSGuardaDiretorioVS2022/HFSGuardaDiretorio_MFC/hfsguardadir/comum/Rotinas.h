#ifndef ROTINAS_H
#define ROTINAS_H

#pragma once

#include <commctrl.h>
#include "SQLite3Lib.h"
#include "hfsguardadir/objetos/ConexaoParams.h"
#include "hfsguardadir/objetos/Arquivo.h"

#define TAM_MAX_STR 512

using namespace hfsguardadir::objetos;

namespace hfsguardadir {

namespace comum {

enum TipoExportar {
    teTXT, teCSV, teHTML, teXML, teSQL
};

enum TipoExportarExtensao {
    teNUL, teBMP, teICO, teGIF, teJPG, tePNG, teTIF
};

struct Progresso {
    int minimo;
    int maximo;
    int posicao;
    int passo;
    CString log;
};

typedef void IProgressoLog(Progresso);

class Rotinas
{
private:
    Rotinas();
    Rotinas(Rotinas const&);
    Rotinas& operator=(Rotinas const&);
    static Rotinas* instancia;

public:
    static const CString HFSGUARDADIR;

    static const char BARRA_NORMAL = '\\';
    static const char BARRA_INVERTIDA = '/';

    static const CString FORMATO_DATA;
	static const CString FORMATO_HORA;
    static const CString FORMATO_DATAHORA;
    static const CString FORMATO_DHARQUIVO;
    static const CString EXTENSAO_BMP;
    static const CString EXTENSAO_ICO;
    static const CString EXTENSAO_GIF;
    static const CString EXTENSAO_JPEG;
    static const CString EXTENSAO_PNG;
    static const CString EXTENSAO_TIFF;

    static Rotinas* getInstancia();

	static char* StringToChar(const CString &texto);
	static LPWSTR NewStr(INT ntam);
	static LPWSTR NewStr();
	static CString lerStr(UINT nId);
	static CString retTexto(CWnd* cwnd);
	BOOL VerificaInstancia(LPTSTR sNomeClasse, LPTSTR sNomeJanela);

	sqlite3* getConexao();
	BOOL BancoConectar(const CString &sFonteDeDados);
	VOID BancoDesconectar();
	VOID BancoMostrarErro(const char* titulo);
	INT BancoExec(const CString &sSQL);
	BOOL BancoPasso(sqlite3_stmt* pstmt);
	INT BancoExecPasso(sqlite3_stmt* pstmt, int ret, const char* titulo);

	static VOID criaImageLists(CImageList *imageList16, CImageList *imageList32);
	static CTime DataHoraNow();
	static CString formataDate(const CString &formato, const CTime &dt);
	static CTime StringToDate(const CString &sData);
	CEdit* criaEdit(CWnd pai, INT id, LPTSTR sTexto,
		INT x, INT y, INT largura,
		BOOL bHabilitado, INT nMaxTam, BOOL bComSenha, BOOL bSoNumero);

	static CString Trim(const CString &texto);
	static CString LowerCase(const CString &texto);
	static CString UpperCase(const CString &texto);
	static int LastIndexOf(const CString &texto, const CString &subtexto);
    static int LastDelimiter(const CString &subtexto, const CString &texto);
    static int LastDelimiter(char subtexto, const CString &texto);
    static int Pos(const CString &subtexto, const CString &texto);
    static int Pos(LPCWSTR subtexto, const CString &texto);
    static bool StartsStr(const CString &subtexto, const CString &texto);
    static bool ContainsStr(const CString &texto, const CString &subtexto);
    static bool EndsStr(const CString &texto, const CString &subtexto);
    static CString SubString(const CString &texto, int inicio, int tamanho);
    static CString StringReplaceAll(const CString &texto, const CString &velho,
            const CString &novo);
    static CString QuotedStr(const CString &texto);
    static CString QuotedStr(char texto);	
	static CString FromInt(int valor);
    static CString FromULong(unsigned long valor);
	static CString FromLongLong(long long valor);
    static CString FromLongDouble(long double valor);
	static int ToInt(const CString& valor);
	static long ToLong(const CString& valor);
	static long long ToLongLong(const CString& valor);
	static unsigned long ToULong(const CString& valor);
	static unsigned long long ToULongLong(const CString& valor);

	VOID copiaBitmap(CWnd pai, INT idBMP, RECT rc);
	HBITMAP BitmapToHBitmap(const BITMAP bmp);
	static void setBarraProgresso(CProgressCtrl *pb, int nMin, int nMax, int nPasso);
	static bool criarVisao(const CString &visao);
	static CString MontaTamanhoBig(long double nTam);
	static CString MontaTamanho(long long nTam);

    static CString testaNull(const char* res);
    static CString trocaSeparador(const CString &texto);
	static CString AppDirPath();
	static CString AppDirName();
	static CString AppFileName();
    static CString ExtractFilePath(const CString &sCaminho);
    static CString ExtractFileName(const CString &sCaminho);
    static bool FileExists(const CString &sNomeArquivo);
    static bool DirectoryExists(const CString &sNomeArquivo);
    static bool DeleteFromFile(const CString &sNomeArquivo);
	static Arquivo FileInfoToArquivo(const CFileFind &finder);
    static void SaveToFile(const CByteArray &imagem, const CString &sNomeArquivo);
    static CByteArray* LoadFromFile(const CString &sNomeArquivo);
    static CString getRecurso(const CString &chave);

	static HBITMAP iconeToBitmapFromID(WORD idIcone, int largura, int altura);
	static HBITMAP iconeToBitmap(HICON hIcon, int tamanho);
	static HBITMAP extrairIconeArquivo(const CString &sNomeArquivo, int tamanho);
	static HBITMAP HBitmapFromBlob(void* blob, long larguraAltura);
	static BITMAP BitmapFromBlob(void* blob, long larguraAltura);
	static HBITMAP HBitmapLoadFromFile(const CString &sNomeArquivo);
	static BITMAP BitmapLoadFromFile(const CString &sNomeArquivo);
	static BOOL FileExists2(const CString &sNomeArquivo);
	static BOOL SaveTextToFile(const CString &sTexto, const CString &sNomeArquivo);

    static bool SListSaveToFile(const CStringList &lista, const CString &sNomeArquivo);
    static CStringList* SListLoadFromFile(const CString &sNomeArquivo);
    static CStringList* SListSeparador(const CString &texto, const char separador);
	static CString SListTexto(const CStringList &lista);
	static CStringList* SListInverter(const CStringList &lista);

	static CBitmap& extrairIconeArquivo(const CString &sNomeArquivo);
	static CStringList* listarArquivosDiretorios(const CString &sDiretorio);
	static BOOL BlobSaveToFile(const void* blob, size_t tamanho, const CString &sNomeArquivo);
	static long BlobLoadFromFile(const CString &sNomeArquivo, void** blob);
	static VOID errhandler(LPCWSTR erro, HWND hwd);
	static PBITMAPINFO CreateHBitmapInfoStruct(HWND hwnd, HBITMAP hBmp);
	static void CriarHBitmapFile(HWND hwnd, LPTSTR pszFile, PBITMAPINFO pbi,
		HBITMAP hBMP, HDC hDC);
	static BOOL HBitmapSaveToFile(HBITMAP hBMP, const CString &sNomeArquivo);
	static CBitmap* BlobToBitmap(const void* blobBmp, int tamanhoBmp, CImageList *imageList);
	static CBitmap* HBitmapToBitmap(HBITMAP hBMP, CImageList *imageList);
	static int Rotinas::BitmapToBlob(CBitmap* cbmp, void** blobBmp);

	static void testar();
};

}
}

#endif // ROTINAS_H
