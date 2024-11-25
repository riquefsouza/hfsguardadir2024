#ifndef ROTINAS_H
#define ROTINAS_H

#define TAM_MAX_STR 512

#include <string>
#include <vector>

#include "hfsguardadir/objetos/Arquivo.h"
#include "SQLite3Lib.h"

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
	int minimo = 0;
	int maximo = 0;
	int posicao = 0;
	int passo = 0;
	std::string log;
};

struct SArgumento {
	int quantidade = 0;
	std::string texto;
};

struct SImagemBuffer {
	size_t tamanho = 0;
	char* buffer = nullptr;
	std::string formato;
};

typedef struct SArgumento Argumento;

typedef void IProgressoLog(Progresso);

typedef struct SImagemBuffer ImagemBuffer;

class Rotinas {

private:
	static Argumento argumentos;

	Rotinas();
	Rotinas(Rotinas const&);
	Rotinas& operator=(Rotinas const&);
	static Rotinas* instancia;

public:
	static const std::string HFSGUARDADIR;

	static const std::string BARRA_NORMAL;
	static const std::string BARRA_INVERTIDA;

	static const std::string FORMATO_DATA;
	static const std::string FORMATO_HORA;
	static const std::string FORMATO_DATAHORA;
	static const std::string FORMATO_DHARQUIVO;
	static const std::string EXTENSAO_BMP;
	static const std::string EXTENSAO_ICO;
	static const std::string EXTENSAO_GIF;
	static const std::string EXTENSAO_JPEG;
	static const std::string EXTENSAO_PNG;
	static const std::string EXTENSAO_TIFF;

	static Rotinas* getInstancia();

	static unsigned int calculaProgresso(int nMaximo, int nProgresso);

	sqlite3* getConexao();
	bool BancoConectar(const std::string &sFonteDeDados);
	void BancoDesconectar();
	void BancoMostrarErro(const char* titulo);
	int BancoExec(const std::string &sSQL);
	bool BancoPasso(sqlite3_stmt* pstmt);
	int BancoExecPasso(sqlite3_stmt* pstmt, int ret, const char* titulo);

	//---------------------------------------------------------------------------
	//	FUNCOES C PURO
	//---------------------------------------------------------------------------
	static char* cNewStr(unsigned long long tamanho);
	static void cFreeStr(char* texto);
	static char* cWCharToChar(const wchar_t* origem);
	static int cLastIndexOf(const char* texto, const char alvo);
	static char* cTrim(const char* texto);
	static char* cLowerCase(const char* texto);
	static char* cUpperCase(const char* texto);
	static size_t cPos(const char* subtexto, const char* texto);
	static int cFind(const char* subtexto, const char* texto, int posInicial);
	static bool cStartsStr(const char* sub, const char* texto);
	static bool cContainsStr(const char* texto, const char* subtexto);
	static bool cEndsStr(const char* texto, const char* subtexto);
	static size_t cLastDelimiter(const char* sub, const char* texto);
	static char* cStrndup(const char* texto, size_t tamanho);
	static char* cSubString(const char* texto, int inicio, size_t tamanho);
	static char* cQuotedStr(const char* texto);
	static char* cReplaceAll(const char* texto,
		const char* velho, const char* novo);
	static char* cFromInt(int valor);
	static char* cFromULong(const unsigned long valor);
	static char* cFromLongLong(const long long valor);
	static char* cFromDouble(const double valor);
	static char* cFromLongDouble(const long double valor);
	static int cToInt(const char* texto);
	static long cToLong(const char* texto);
	static long long cToLongLong(const char* texto);
	static double cToDouble(const char* texto);
	static long double cToLongDouble(const char* texto);
	static bool cSomenteNumero(const char* texto);

	// ---------------------------------------------------------------------------

	static char* NewStr(size_t tamanho);
	static char* NewStr();
	static char* WCharToChar(const wchar_t* origem);
	static wchar_t* CharToWChar(const char* origem);
	static std::string WStringToString(const std::wstring &origem);
	static std::wstring StringToWString(const std::string &origem);
	static void setArgumentos(int argc, char *argv[]);
	static std::string AppDirPath();
	static std::string AppDirName();
	static std::string AppFileName();
	
	static std::string Trim(const std::string &texto);
	static std::string LowerCase(const std::string &texto);
	static std::string UpperCase(const std::string &texto);
	static size_t Pos(const std::string &subtexto, const std::string &texto);
	static bool StartsStr(const std::string &subtexto, const std::string &texto);
	static bool ContainsStr(const std::string &texto, const std::string &subtexto);
	static bool EndsStr(const std::string &texto, const std::string &subtexto);
	static size_t LastDelimiter(const std::string &subtexto, const std::string &texto);
	static std::string SubString(const std::string &texto, size_t inicio, size_t tamanho);
	static std::string QuotedStr(const std::string &texto);
	static std::string QuotedChar(const char caracter);
	static std::string ReplaceAll(const std::string &texto, 
		const std::string &velho, const std::string &novo);
	static std::string IntToStr(int valor);
	static int StrToInt(const std::string &texto);
	static std::string ULongToStr(const unsigned long valor);
	static std::string LongLongToStr(const long long valor);
	static std::string LongDoubleToStr(const long double valor);
	static unsigned long long StrToULongLong(const std::string &texto);
	static std::string DoubleToStr(const double valor);
	static double StrToDouble(const std::string &texto);
/*
	static std::string formataDate(const std::string formato, const DateTime* dt);
	static DateTime* StringToDate(const std::string &sData);
	static DateTime* DataHoraNow();
	static DateTime* RawToDataHora(const time_t rawTempo);
	*/
// ---------------------------------------------------------------------------
	static std::string MontaTamanhoBig(long double nTam);
	static std::string MontaTamanho(long long nTam);
	static std::string testaNull(char *res);
	static std::string trocaSeparador(const std::string &texto);
	static bool testaSeparadorArquivo(const std::string &sDir);
	static std::string ExtractFilePath(const std::string &sCaminho);
	static std::string ExtractFileName(const std::string &sCaminho);
	static bool FileExists(const std::string &sNomeArquivo);
	static bool DirectoryExists(const std::string &sNomeArquivo);
	static bool DeleteFromFile(const std::string &sNomeArquivo);
	static std::string getRecurso(const char* chave);
	// ---------------------------------------------------------------------------
	static std::vector<std::string> cListarArquivosDiretorios(const std::string &sDiretorio);
	static Arquivo FileInfoToArquivo(const std::string &sNomeArquivo);
	static bool SListSaveToFile(const std::vector<std::string> lista, const std::string &sNomeArquivo);
	static std::vector<std::string> SListLoadFromFile(const std::string &sNomeArquivo);
	static std::vector<std::string> SListSeparador(const std::string &texto, const char separador);
	static std::string SListTexto(const std::vector<std::string> lista);
	static bool BlobSaveToFile(const void* blob, size_t tamanho, const std::string &sNomeArquivo);
	static size_t BlobLoadFromFile(const std::string &sNomeArquivo, void** blob);
	// ---------------------------------------------------------------------------
	static ImagemBuffer XPMToPixbuf(const char** xpm);
	static ImagemBuffer imagemToPixbuf(const std::string &sNomeImagem);
	static ImagemBuffer ArquivoToPixbuf(const std::string &sArquivo);
	static bool PixbufToArquivo(ImagemBuffer pixbuf, 
		const std::string &sArquivo, const std::string &formato);
	static ImagemBuffer BlobToPixbuf(const void* blob, size_t tamanho);
	static size_t PixbufToBlob(ImagemBuffer pixbuf, void** blob, const std::string &formato);
	static ImagemBuffer extrairPixbufArquivo(const std::string &sCaminho, int tamanho);

	static void testar();


private:
	static std::string TrimLeft(const std::string &texto);
	static std::string TrimRight(const std::string &texto);
};

}
}

#endif
