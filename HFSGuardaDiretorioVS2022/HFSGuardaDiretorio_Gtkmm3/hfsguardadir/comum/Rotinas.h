#ifndef ROTINAS_H
#define ROTINAS_H

#ifndef PTRDIFF_MAX
#define PTRDIFF_MAX (std::numeric_limits<ptrdiff_t>::max())
#endif

#define TAM_MAX_STR 512

#include <giomm/file.h>
#include <giomm/memoryinputstream.h>
#include <glibmm/ustring.h>
#include <gtkmm/treemodelcolumn.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/liststore.h>
#include <gtkmm/treestore.h>
#include <gtkmm/image.h>
/*
#ifdef G_OS_WIN32
	#include <windows.h>
#else
	#include <unistd.h>
#endif
*/
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
	int minimo;
	int maximo;
	int posicao;
	int passo;
	Glib::ustring log;
};

struct SArgumento {
	int quantidade;
	std::string texto;
};

typedef struct SArgumento Argumento;

typedef void IProgressoLog(Progresso);

class Rotinas {

private:
	static Argumento argumentos;

	Rotinas();
	Rotinas(Rotinas const&);
	Rotinas& operator=(Rotinas const&);
	static Rotinas* instancia;

public:
	static const Glib::ustring HFSGUARDADIR;

	static const Glib::ustring BARRA_NORMAL;
	static const Glib::ustring BARRA_INVERTIDA;

	static const Glib::ustring FORMATO_DATA;
	static const Glib::ustring FORMATO_HORA;
	static const Glib::ustring FORMATO_DATAHORA;
	static const Glib::ustring FORMATO_DHARQUIVO;
	static const Glib::ustring EXTENSAO_BMP;
	static const Glib::ustring EXTENSAO_ICO;
	static const Glib::ustring EXTENSAO_GIF;
	static const Glib::ustring EXTENSAO_JPEG;
	static const Glib::ustring EXTENSAO_PNG;
	static const Glib::ustring EXTENSAO_TIFF;

	static Rotinas* getInstancia();

	void MsgDlg(Glib::ustring sMensagem, Glib::ustring sTitulo, Gtk::MessageType tipo);
	static Glib::ustring retLocale(Glib::ustring sTexto);
	static Glib::ustring retUTF8(Glib::ustring sTexto);
	static Glib::ustring retUTF8(char* sTexto);
	static double calculaProgresso(int nMaximo, int nProgresso);
	
	sqlite3* getConexao();
	bool BancoConectar(const Glib::ustring &sFonteDeDados);
	void BancoDesconectar();
	void BancoMostrarErro(const char* titulo);
	int BancoExec(const Glib::ustring &sSQL);
	bool BancoPasso(sqlite3_stmt* pstmt);
	int BancoExecPasso(sqlite3_stmt* pstmt, int ret, const char* titulo);

	// ---------------------------------------------------------------------------

	static char* NewStr(unsigned int tamanho);
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
	static int Pos(const std::string &subtexto, const std::string &texto);
	static bool StartsStr(const std::string &subtexto, const std::string &texto);
	static bool ContainsStr(const std::string &texto, const std::string &subtexto);
	static bool EndsStr(const std::string &texto, const std::string &subtexto);
	static int LastDelimiter(const std::string &subtexto, const std::string &texto);
	static std::string SubString(const std::string &texto, int inicio, int tamanho);
	static std::string IntToStr(int valor);
	static int StrToInt(const std::string &texto);
	static std::string QuotedStr(const std::string &texto);
	static std::string QuotedChar(const char caracter);
	static std::string ReplaceAll(const std::string &texto, 
		const std::string &velho, const std::string &novo);
	static std::string ULongToStr(const unsigned long valor);
	static std::string LongLongToStr(const long long valor);
	static std::string LongDoubleToStr(const long double valor);
	static guint64 StrToLong(const std::string &texto);
	static std::string DoubleToStr(const double valor);
	static gdouble StrToDouble(const std::string &texto);

	static Glib::ustring formataDate(const Glib::ustring formato, const GDateTime* dt);
	static GDateTime* StringToDate(const Glib::ustring &sData);
	static GDateTime* DataHoraNow();
	static GDateTime* RawToDataHora(const time_t rawTempo);

// ---------------------------------------------------------------------------
	static Glib::ustring MontaTamanhoBig(long double nTam);
	static Glib::ustring MontaTamanho(long long nTam);
	static Glib::ustring testaNull(char *res);
	static Glib::ustring trocaSeparador(const Glib::ustring &texto);
	static bool testaSeparadorArquivo(const Glib::ustring &sDir);
	static std::string ExtractFilePath(const std::string &sCaminho);
	static std::string ExtractFileName(const std::string &sCaminho);
	static bool FileExists(const Glib::ustring &sNomeArquivo);
	static bool DirectoryExists(const Glib::ustring &sNomeArquivo);
	static bool DeleteFromFile(const Glib::ustring &sNomeArquivo);
	static Glib::ustring getRecurso(const char* chave);
	// ---------------------------------------------------------------------------
	static std::vector<Glib::ustring> cListarArquivosDiretorios(const Glib::ustring &sDiretorio);
	static Arquivo FileInfoToArquivo2(const Glib::ustring &sCaminho);
	static Arquivo FileInfoToArquivo(const std::string &sNomeArquivo);
	static bool SListSaveToFile(const std::vector<Glib::ustring> lista, const Glib::ustring &sNomeArquivo);
	static std::vector<Glib::ustring> SListLoadFromFile(const Glib::ustring &sNomeArquivo);
	static std::vector<Glib::ustring> SListSeparador(const Glib::ustring &texto, const gchar separador);
	static Glib::ustring SListTexto(const std::vector<Glib::ustring> lista);
	static bool BlobSaveToFile(const void* blob, size_t tamanho, const Glib::ustring &sNomeArquivo);
	static long BlobLoadFromFile(const Glib::ustring &sNomeArquivo, void** blob);
	static std::vector<Glib::ustring> listarArquivosDiretorios(const Glib::ustring &sDiretorio);
	// ---------------------------------------------------------------------------
	static Glib::RefPtr<Gdk::Pixbuf> XPMToPixbuf(const char** xpm);
	static Glib::RefPtr<Gdk::Pixbuf> imagemToPixbuf(const Glib::ustring &sNomeImagem);
	static Glib::RefPtr<Gdk::Pixbuf> ArquivoToPixbuf(const Glib::ustring &sArquivo);
	static bool PixbufToArquivo(Glib::RefPtr<Gdk::Pixbuf> pixbuf, 
		const Glib::ustring &sArquivo, const Glib::ustring &formato);
	static Glib::RefPtr<Gdk::Pixbuf> BlobToPixbuf(const void* blob, int tamanho);
	static gsize PixbufToBlob(Glib::RefPtr<Gdk::Pixbuf> pixbuf, void*& blob, const Glib::ustring &formato);
	static Glib::RefPtr<Gdk::Pixbuf> extrairPixbufArquivo(const Glib::ustring &sCaminho, int tamanho);

	static void testar();


private:
	static std::string TrimLeft(const std::string &texto);
	static std::string TrimRight(const std::string &texto);
};

}
}

#endif
