#ifndef ROTINAS_H
#define ROTINAS_H

#include <commctrl.h>
#include "SQLite3Lib.h"
#include "ListaString.h"
#include "hfsguardadir/objetos/Arquivo.h"

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
	String log;
};

typedef void IProgressoLog(Progresso);

extern String Rotinas_HFSGUARDADIR;

extern String Rotinas_BARRA_NORMAL;
extern String Rotinas_BARRA_INVERTIDA;

extern String Rotinas_FORMATO_DATA;
extern String Rotinas_FORMATO_HORA;
extern String Rotinas_FORMATO_DATAHORA;
extern String Rotinas_FORMATO_DHARQUIVO;
extern String Rotinas_EXTENSAO_BMP;
extern String Rotinas_EXTENSAO_ICO;
extern String Rotinas_EXTENSAO_GIF;
extern String Rotinas_EXTENSAO_JPEG;
extern String Rotinas_EXTENSAO_PNG;
extern String Rotinas_EXTENSAO_TIFF;

//extern sqlite3* dbConexao;
LPWSTR Rotinas_NewStr(INT ntam);
LPWSTR Rotinas_NewStr();

/*
const char* Rotinas_LPCWSTRToCharArray(LPCWSTR stexto);
LPCWSTR Rotinas_CharArrayToLPCWSTR(char* stexto);
//char* Rotinas_NewStr(unsigned long long tamanho);
//char* Rotinas_WCharToChar(const wchar_t* origem);
int Rotinas_LastIndexOf(LPCWSTR texto, WCHAR alvo);
LPWSTR Rotinas_Trim(LPCWSTR texto);
LPWSTR Rotinas_LowerCase(LPCWSTR texto);
LPWSTR Rotinas_UpperCase(LPCWSTR texto);
int Rotinas_Pos(LPCWSTR subtexto, LPCWSTR texto);
BOOL Rotinas_StartsStr(LPCWSTR sub, LPCWSTR texto);
BOOL Rotinas_ContainsStr(LPCWSTR texto, LPCWSTR subtexto);
BOOL Rotinas_EndsStr(LPCWSTR texto, LPCWSTR subtexto);
int Rotinas_LastDelimiter(LPCWSTR sub, LPCWSTR texto);
LPWSTR Rotinas_strndup(LPCWSTR texto, size_t tamanho);
LPWSTR Rotinas_SubString(LPCWSTR texto, int inicio, int tamanho);
LPWSTR Rotinas_IntToStr(int valor);
int Rotinas_StrToInt(LPCWSTR texto);
LPWSTR Rotinas_QuotedStr(LPCWSTR texto);
LPWSTR Rotinas_StringReplaceAll(LPCWSTR texto, LPCWSTR velho, LPCWSTR novo);
LPWSTR Rotinas_FormatLong(const unsigned long valor);
LPWSTR Rotinas_FormatDouble(const long double valor);
unsigned long long Rotinas_StrToLong(LPCWSTR texto);
LPWSTR Rotinas_DoubleToStr(const double valor);
double Rotinas_StrToDouble(LPCWSTR texto);
//LPWSTR Rotinas_formataDate(LPCWSTR formato, DateTime dt);
//DateTime Rotinas_StringToDate(LPCWSTR sData);
*/

INT Rotinas_RegistrarClasseForm(WNDCLASSEX WndClassEx, WNDPROC WndFrmProc, 
  LPCTSTR sNomeClasse);
HWND Rotinas_ChamarForm(HWND hwnd, LPCTSTR sTituloForm, LPCTSTR sNomeClasse, 
    HWND hMDICliente, INT largura, INT altura);
HWND Rotinas_ChamarDlgNaoModal(HWND hwnd, LPCTSTR sNomeDialog, 
    DLGPROC lpDlgProc);    
VOID Rotinas_CentralizaTela(HWND hWnd);
VOID Rotinas_criaImageLists(HWND hwnd, HIMAGELIST *imageList16, HIMAGELIST *imageList32);

SYSTEMTIME Rotinas_DataHoraNow();
BOOL Rotinas_DataHoraComparar(SYSTEMTIME st1, SYSTEMTIME st2);
String Rotinas_formataDate(String formato, SYSTEMTIME sTempo);
SYSTEMTIME Rotinas_StringToDate(String sData);

String Rotinas_retTexto(HWND hwnd);
LPWSTR Rotinas_lerStr(UINT nId);
/*
HWND Rotinas_criaBotao(HWND hwnd, LPTSTR sTexto, INT id, INT x, INT y, BOOL bHabilitado);
HWND Rotinas_criaRotulo(HWND hwnd, LPTSTR sTexto, INT id, INT x, INT y, INT largura);
*/
HWND Rotinas_criaEdit(HWND hwnd, INT id, LPTSTR sTexto, INT x, INT y, INT largura, BOOL bHabilitado,
    INT nMaxTam, BOOL bComSenha, BOOL bSoNumero);

sqlite3* Rotinas_getConexao();
BOOL Rotinas_BancoConectar(String sFonteDeDados);
VOID Rotinas_BancoDesconectar();
VOID Rotinas_BancoMostrarErro(const char* titulo);
INT Rotinas_BancoExec(String sSQL);
BOOL Rotinas_BancoPasso(sqlite3_stmt* pstmt);
INT Rotinas_BancoExecPasso(sqlite3_stmt* pstmt, int ret, const char* titulo);

/*
VOID Rotinas_AdicionaItemLista(HWND lstLista,
     ListaString *slCodLista, HWND sCampoCodigo, HWND sCampoDesc);
VOID Rotinas_RemoveItemLista(HWND lstLista, ListaString *slCodLista);
VOID Rotinas_AdicionaValoresLista(LPTSTR sTextoSql, HWND lstLista, 
                                  ListaString *slCodLista);
*/

VOID Rotinas_copiaBitmap(HWND hwnd, INT idBMP, RECT rc);
    	 
HWND Rotinas_pegaBarraProgresso(HWND hwnd, int nIDDlgItem, int nMin, int nMax, int nPasso);

BOOL Rotinas_criarVisao(String visao);
String Rotinas_MontaTamanhoBig(long double nTam);
String Rotinas_MontaTamanho(long long nTam);
String Rotinas_testaNull(const char* res);
String Rotinas_trocaSeparador(String texto);
String Rotinas_AppDirPath();
String Rotinas_AppDirName();
String Rotinas_AppFileName();
String Rotinas_ExtractFileName(String sCaminho);
String Rotinas_ExtractFilePath(String sCaminho);
BOOL Rotinas_FileExists(String sNomeArquivo);
BOOL Rotinas_DirectoryExists(String sNomeArquivo);
BOOL Rotinas_DeleteFromFile(String sNomeArquivo);

Arquivo Rotinas_FileInfoToArquivo(WIN32_FIND_DATA finder);

HBITMAP Rotinas_BitmapToHBitmap(const BITMAP bmp);
HBITMAP Rotinas_iconeToBitmapFromID(WORD idIcone, int largura, int altura);
HBITMAP Rotinas_iconeToBitmap(HICON hIcon, int tamanho);
HBITMAP Rotinas_extrairIconeArquivo(String sNomeArquivo, int tamanho);
HBITMAP Rotinas_HBitmapFromBlob(void* blob, long larguraAltura);
BITMAP Rotinas_BitmapFromBlob(void* blob, long larguraAltura);
HBITMAP Rotinas_HBitmapLoadFromFile(String sNomeArquivo);
BITMAP Rotinas_BitmapLoadFromFile(String sNomeArquivo);

BOOL Rotinas_FileExists2(String sNomeArquivo);
BOOL Rotinas_SaveTextToFile(String sTexto, String sNomeArquivo);

BOOL Rotinas_SListSaveToFile(ListaString lista, String sNomeArquivo);
ListaString Rotinas_SListLoadFromFile(String sNomeArquivo);
ListaString Rotinas_SListSeparador(String texto, char separador);
String Rotinas_SListTexto(ListaString lista);
ListaString Rotinas_listarArquivosDiretorios(String sDiretorio);

BOOL Rotinas_BlobSaveToFile(const void* blob, size_t tamanho, String sNomeArquivo);
long Rotinas_BlobLoadFromFile(String sNomeArquivo, void** blob);

VOID Rotinas_errhandler(LPCWSTR erro, HWND hwd);
PBITMAPINFO Rotinas_CreateHBitmapInfoStruct(HWND hwnd, HBITMAP hBmp);
void Rotinas_CriarHBitmapFile(HWND hwnd, LPTSTR pszFile, PBITMAPINFO pbi,
	HBITMAP hBMP, HDC hDC);
BOOL Rotinas_HBitmapSaveToFile(HBITMAP hBMP, String sNomeArquivo);
BITMAP Rotinas_BlobToBitmap(const void* blobBmp, int tamanhoBmp, HIMAGELIST *imageList);
BITMAP Rotinas_HBitmapToBitmap(HBITMAP hBMP, HIMAGELIST *imageList);
int Rotinas_BitmapToBlob(BITMAP bmp, void** blobBmp);

VOID Rotinas_testar();

#endif
