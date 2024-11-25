#ifndef ROTINAS_H
#define ROTINAS_H
// ---------------------------------------------------------------------------
#include "../../resource.h"
#include "ListaString.h"
#include "sqlite3.h"
#include "../objetos/Arquivo.h"
// ---------------------------------------------------------------------------
#define Rotinas_BARRA_NORMAL "\\"
#define Rotinas_BARRA_INVERTIDA "/"
#define Rotinas_HFSGUARDADIR "HFSGuardaDir"
#define Rotinas_FORMATO_DATA "%d/%m/%Y"
#define Rotinas_FORMATO_DATAHORA "%d/%m/%Y %H:%M:%S"
#define Rotinas_FORMATO_DHARQUIVO "%Y-%m-%d_%H:%M:%S"
#define Rotinas_EXTENSAO_BMP "bmp"
#define Rotinas_EXTENSAO_ICO "ico"
#define Rotinas_EXTENSAO_GIF "gif"
#define Rotinas_EXTENSAO_JPEG "jpeg"
#define Rotinas_EXTENSAO_PNG "png"
#define Rotinas_EXTENSAO_TIFF "tiff"

enum ETipoExportar {
	teTXT, teCSV, teHTML, teXML, teSQL
};

typedef enum ETipoExportar TipoExportar;

enum ETipoExportarExtensao {
	teNUL, teBMP, teICO, teGIF, teJPG, tePNG, teTIF
};

typedef enum ETipoExportarExtensao TipoExportarExtensao;

struct SProgresso {
	int minimo;
	int maximo;
	int posicao;
	int passo;
	GString *log;
};

struct SArgumento {
	int quantidade;
	GString* texto;
};

typedef struct SArgumento Argumento;

typedef struct SProgresso Progresso;

typedef void IProgressoLog(Progresso);

// ---------------------------------------------------------------------------
	gchar* Rotinas_retLocale(const gchar *sTexto);
	gchar* Rotinas_retUTF8(const gchar *sTexto);
	double Rotinas_calculaProgresso(int nMaximo, int nProgresso);

	GdkPixbuf* Rotinas_XPMToPixbuf(const char** xpm);
	GdkPixbuf* Rotinas_imagemToPixbuf(const char* sNomeImagem);
	GdkPixbuf* Rotinas_ArquivoToPixbuf(const char* sArquivo);
	gboolean Rotinas_PixbufToArquivo(GdkPixbuf* pixbuf, const char* sArquivo, const char* formato);
	GdkPixbuf* Rotinas_BlobToPixbuf(const void* blob, gssize tamanho);
	gsize Rotinas_PixbufToBlob(GdkPixbuf* pixbuf, void** blob, const char* formato);
	GdkPixbuf* Rotinas_extrairPixbufArquivo(const GString* sCaminho, int tamanho);

	sqlite3* Rotinas_getConexao();
	gboolean Rotinas_BancoConectar(GString *sFonteDeDados);
	void Rotinas_BancoDesconectar();
	void Rotinas_BancoMostrarErro(const char* titulo);
	int Rotinas_BancoExec(GString *sSQL);
	gboolean Rotinas_BancoPasso(sqlite3_stmt* pstmt);
	int Rotinas_BancoExecPasso(sqlite3_stmt* pstmt, int ret, const char* titulo);
// ---------------------------------------------------------------------------
	void Rotinas_argumentos(int argc, char *argv[]);
	GString* Rotinas_AppDirPath();

	GString* Rotinas_concatenar(const char* string1, const char* string2);
	GString* Rotinas_concatenar1(const GString* string1, const char* string2, const char* string3);
	GString* Rotinas_concatenar2(const GString* string1, const GString* string2, const char* string3);
	GString* Rotinas_concatenar3(const GString* string1, const GString* string2, const char* string3, const char* string4);
	GString* Rotinas_concatenar4(const GString* string1, const GString* string2, const char* string3, const char* string4,
		const char* string5, const char* string6);
	gboolean Rotinas_comparar(const GString* string1, const char* string2);

	GString* Rotinas_Trim(const GString *texto);
	GString* Rotinas_LowerCase(const GString *texto);
	GString* Rotinas_UpperCase(const GString *texto);
	int Rotinas_Pos(const GString* subtexto, const GString* texto);
	gboolean Rotinas_StartsStr(const GString* sub, const GString* texto);
	gboolean Rotinas_ContainsStr(const GString* texto, const GString* subtexto);
	gboolean Rotinas_EndsStr(const GString* texto, const GString* subtexto);
	int Rotinas_LastDelimiter(const GString* sub, const GString* texto);
	GString* Rotinas_SubString(const GString* texto, gsize inicio, gsize tamanho);
	GString* Rotinas_IntToStr(int valor);
	int Rotinas_StrToInt(const GString* texto);
	GString* Rotinas_QuotedStr(const GString* texto);
	GString* Rotinas_QuotedChar(const char caracter);
	GString* Rotinas_ReplaceAll(const GString* texto,
		const GString* velho, const GString* novo);
	GString* Rotinas_formataDate(const gchar* formato, const GDateTime* dt);
	GDateTime* Rotinas_StringToDate(const GString* sData);
	GDateTime* Rotinas_DataHoraNow();
	GString* Rotinas_ULongToStr(const unsigned long valor);
	GString* Rotinas_LongLongToStr(const long long valor);
	GString* Rotinas_LongDoubleToStr(const long double valor);
	guint64 Rotinas_StrToLong(const GString* texto);
	GString* Rotinas_DoubleToStr(const double valor);
	gdouble Rotinas_StrToDouble(const GString* texto);
// ---------------------------------------------------------------------------
	gchar* Rotinas_cNewStr(unsigned int tamanho);
	gchar* Rotinas_cWCharToChar(const wchar_t* origem);
	int Rotinas_cLastIndexOf(const gchar* texto, const char alvo);
	gchar* Rotinas_cTrim(const gchar* texto);
	gchar* Rotinas_cLowerCase(const gchar* texto);
	gchar* Rotinas_cUpperCase(const gchar* texto);
	int Rotinas_cPos(const gchar* subtexto, const gchar* texto);
	gboolean Rotinas_cStartsStr(const gchar* sub, const gchar* texto);
	gboolean Rotinas_cContainsStr(const gchar* texto, const gchar* subtexto);
	gboolean Rotinas_cEndsStr(const gchar* texto, const gchar* subtexto);
	int Rotinas_cLastDelimiter(const gchar* sub, const gchar* texto);
	gchar* Rotinas_cstrndup(const gchar* texto, size_t tamanho);
	gchar* Rotinas_cSubString(const gchar* texto, int inicio, int tamanho);
	gchar* Rotinas_cIntToStr(int valor);
	int Rotinas_cStrToInt(const gchar* texto);
	gchar* Rotinas_cQuotedStr(const gchar* texto);
	gchar* Rotinas_cReplaceAll(const gchar* texto,
		const gchar* velho, const gchar* novo);
	gchar* Rotinas_cFormatLong(const unsigned long valor);
	gchar* Rotinas_cFormatDouble(const long double valor);
	long long Rotinas_cStrToLong(const gchar* texto);
	gchar* Rotinas_cDoubleToStr(const double valor);
	gdouble Rotinas_cStrToDouble(const gchar* texto);
// ---------------------------------------------------------------------------
	GString* Rotinas_MontaTamanhoBig(long double nTam);
	GString* Rotinas_MontaTamanho(long long nTam);
	GString* Rotinas_testaNull(char *res);
	GString* Rotinas_trocaSeparador(const GString *texto);
	gboolean Rotinas_testaSeparadorArquivo(const GString* sDir);
	GString* Rotinas_ExtractFilePath(const GString *sCaminho);
#ifdef G_OS_WIN32
	GString* Rotinas_ExtractFilePathWindows(const GString *sCaminho);
	gboolean Rotinas_DirectoryExistsWindows(const GString *sNomeArquivo);
	gboolean Rotinas_FileExistsWindows(const GString *sNomeArquivo);
	gboolean Rotinas_DeleteFromFileWindows(const GString *sNomeArquivo);
#else
	gboolean Rotinas_FileExistsLinux(const GString *sNomeArquivo);
	gboolean Rotinas_DirectoryExistsLinux(const GString *sNomeArquivo);
#endif
	GString* Rotinas_ExtractFileName(const GString *sCaminho);
	gboolean Rotinas_FileExists(const GString *sNomeArquivo);
	gboolean Rotinas_DirectoryExists(const GString *sNomeArquivo);
	gboolean Rotinas_DeleteFromFile(const GString *sNomeArquivo);

	GString* Rotinas_getRecurso(const char* chave);
// ---------------------------------------------------------------------------
	ListaString Rotinas_cListarArquivosDiretorios(const char* sDiretorio);
	Arquivo Rotinas_FileInfoToArquivo(const GString *sCaminho);
	gboolean Rotinas_SListSaveToFile(const ListaString lista, const GString* sNomeArquivo);
	ListaString Rotinas_SListLoadFromFile(const GString* sNomeArquivo);
	ListaString Rotinas_SListSeparador(const GString* texto, const gchar separador);
	GString* Rotinas_SListTexto(const ListaString lista);
	gboolean Rotinas_BlobSaveToFile(const void* blob, size_t tamanho, const GString* sNomeArquivo);
	long long Rotinas_BlobLoadFromFile(const GString* sNomeArquivo, void** blob);
	ListaString Rotinas_listarArquivosDiretorios(const GString* sDiretorio);

	wchar_t* Rotinas_charArrayToLPCWSTR(const char* charArray);
	gchar** Rotinas_criarArrayDeString(const gchar* texto);
	void Rotinas_testar();

#endif
// ---------------------------------------------------------------------------
