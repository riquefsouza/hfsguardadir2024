#ifndef ROTINAS_H
#define ROTINAS_H

#include <wx/string.h>
#include <wx/datetime.h>
#include <wx/log.h>
#include <wx/buffer.h>
#include <wx/arrstr.h>
#include <wx/file.h>
#include <wx/filename.h>
#include <wx/textfile.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/numformatter.h>
#include <wx/icon.h>
#include <wx/msgdlg.h>
#include <wx/wxsqlite3.h>

#include <iostream>

#include "hfsguardadir/objetos/ConexaoParams.h"

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
    wxString log;
};

typedef void IProgressoLog(Progresso);

class Rotinas
{
private:
    wxSQLite3Database dbConexao;
    Rotinas();
    Rotinas(Rotinas const&);
    Rotinas& operator=(Rotinas const&);
    static Rotinas* instancia;

public:
	wxImage arquivoIcone;
	wxImage cdouroIcone;
	wxImage diretorioIcone;
	wxImage dirabertoIcone;

    static const wxString HFSGUARDADIR;

    static const char BARRA_NORMAL = '\\';
    static const char BARRA_INVERTIDA = '/';

    static const wxString FORMATO_DATA;
	static const wxString FORMATO_HORA;
    static const wxString FORMATO_DATAHORA;
    static const wxString FORMATO_DHARQUIVO;
    static const wxString EXTENSAO_BMP;
    static const wxString EXTENSAO_ICO;
    static const wxString EXTENSAO_GIF;
    static const wxString EXTENSAO_JPEG;
    static const wxString EXTENSAO_PNG;
    static const wxString EXTENSAO_TIFF;

    static Rotinas* getInstancia();

	static wxString AppDirPath();
	static wxString Trim(const wxString &texto);
    static int LastDelimiter(const wxString &subtexto, const wxString &texto);
    static int LastDelimiter(const wxChar &subtexto, const wxString &texto);
    static int Pos(const wxString &subtexto, const wxString &texto);
    static int Pos(const wxChar &subtexto, const wxString &texto);
    static bool StartsStr(const wxString &subtexto, const wxString &texto);
    static bool ContainsStr(const wxString &texto, const wxString &subtexto);
    static bool EndsStr(const wxString &subtexto, const wxString &texto);
    static wxString SubString(const wxString &texto, int inicio, int tamanho);
    static wxString StringReplaceAll(const wxString &texto, const wxString &velho,
            const wxString &novo);
	static wxString IntToStr(int valor);
	static int StrToInt(const wxString &texto);
	static wxULongLong StrToLong(const wxString &texto);
	static wxString DoubleToStr(const double valor);
    static wxString QuotedStr(const wxString &texto);
    static wxString QuotedStr(const wxChar &texto);
    static wxString formataDate(const wxString &formato, const wxDateTime &dt);
    static wxDateTime StringToDate(const wxString &sData);
    static wxString FormatLong(long valor);
    static wxString FormatDouble(long double valor);

	static wxString MontaTamanhoBig(long double nTam);
	static wxString MontaTamanho(long long nTam);

    static wxString testaNull(const wxString &res);
    static wxString trocaSeparador(const wxString &texto);
    static wxString ExtractFilePath(const wxString &sCaminho);
    static wxString ExtractFileName(const wxString &sCaminho);
    static bool FileExists(const wxString &sNomeArquivo);
    static bool DirectoryExists(const wxString &sNomeArquivo);
    static bool DeleteFromFile(const wxString &sNomeArquivo);
    static void SaveToFile(wxMemoryBuffer &imagem, const wxString &sNomeArquivo);
    static wxMemoryBuffer LoadFromFile(const wxString &sNomeArquivo);
    static wxString getRecurso(const wxString &chave);
    static wxImage getImagem(const wxString &arquivo);
    
	wxSQLite3Database* getConexao();
    bool Conectar(wxString &banco);
    bool Conectar(ConexaoParams cp);
    void Desconectar();
    bool criarVisao(const wxString &visao);
	void mostrarErro(wxSQLite3Exception& excecao, const wxString &titulo);
    bool execConsulta(const wxString &sSQL);

	static wxMemoryBuffer ImageToMemoryBuffer(const wxImage &image, wxBitmapType formato);
	static wxImage MemoryBufferToImage(const wxMemoryBuffer &membuffer, wxBitmapType formato);
	static wxMemoryBuffer getImagemByteArray(const wxString &arquivo);

	static wxMemoryBuffer BmpParaImagem(const wxMemoryBuffer &imagemBMP, const wxString &formato);
	
    static bool SListSaveToFile(const wxArrayString &lista, const wxString &sNomeArquivo);
    static wxArrayString SListLoadFromFile(const wxString &sNomeArquivo);
    static wxArrayString SListSeparador(const wxString &texto, const wxChar &separador);
	static wxString SListTexto(const wxArrayString &lista);

	static wxImage extrairIconeArquivo(const wxString &sNomeArquivo);
	static wxArrayString listarArquivosDiretorios(const wxString &sDiretorio);

	void testar();
};

}
}

#endif // ROTINAS_H
