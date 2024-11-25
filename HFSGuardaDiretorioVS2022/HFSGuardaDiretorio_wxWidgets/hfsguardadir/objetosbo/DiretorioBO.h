#ifndef DIRETORIOBO_H
#define DIRETORIOBO_H

#include <wx/vector.h>
#include "hfsguardadir/objetos/Diretorio.h"
#include "hfsguardadir/objetos/DiretorioOrdem.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/comum/DiretorioXML.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosbo {

class DiretorioBO
{
private:
    DiretorioBO();
    DiretorioBO(DiretorioBO const&);
    DiretorioBO& operator=(DiretorioBO const&);
    static DiretorioBO* instancia;

    wxString diretorioToCSV(Diretorio diretorio);
    wxString diretorioToXML(Diretorio diretorio);
    wxString diretorioToTXT(Diretorio diretorio);
    wxString diretorioToHTML(Diretorio diretorio);

public:
    static const wxString SQL_CONSULTA_ARQUIVO;
    static DiretorioBO* getInstancia();

    wxVector<Diretorio> carregarDiretorio(const wxString &sSQL,
                                       IProgressoLog progressoLog);
    wxVector<Diretorio> carregarDiretorio(const wxString &sSQL,
                                       const wxString &sCondicaoTotal,
                                       IProgressoLog progressoLog);
    wxString removerDrive(wxString &sDiretorio);
    wxString arquivoAtributos(wxFileName &info);
    int retCodDirPai(int nAba, wxString &sDiretorio,
                                  wxVector<Diretorio> listaLocal);
    Diretorio atribuiDiretorio(int nAba, int nCodDirRaiz,
            wxString &sNomeDirRaiz, wxString &sDiretorio, bool bDiretorio,
            wxVector<Diretorio> listaLocal, Arquivo arquivo,
            DiretorioOrdem *dirOrdem);
    Arquivo wxFileNameToArquivo(wxFileName &info);
    void atribuiListaDiretorio(int nAba, int nCodDirRaiz,
            wxString &sNomeDirRaiz, wxString &sDiretorio, wxVector<Diretorio> *listaLocal,
            wxFileName &info, DiretorioOrdem *dirOrdem, IProgressoLog progressoLog);
    void ImportarDiretorio(int nAba, int nCodDirRaiz,
            wxString &sNomeDirRaiz, wxString &sDiretorio, wxVector<Diretorio> *listaLocal,
            DiretorioOrdem *dirOrdem, IProgressoLog progressoLog);
    bool verificaCodDir(int nAba, wxString &sDiretorio,
            wxVector<Diretorio> listaLocal);
    int retMaxCodDir(int nAba, wxVector<Diretorio> listaLocal);
    wxString diretorioToSQL(Diretorio diretorio, bool bInsert);
    void salvarDiretorio(wxVector<Diretorio> listaDiretorio,
            IProgressoLog progressoLog);
    bool excluirDiretorio(Aba aba, const wxString &sCaminho);
    void excluirListaDiretorio(wxVector<Diretorio> listaDiretorio,
            Aba aba, const wxString &sCaminho);
    void exportarDiretorio(TipoExportar tipo, Aba aba,
            wxString &sNomeArquivo, IProgressoLog progressoLog);
    bool criarTabelaDiretorios();
    int XMLParaDiretorio(wxString sTexto, int nArquivo,
            DiretorioXML *diretorioXML);
    int importarDiretorioViaXML(Aba aba, wxString &sNomeArquivo,
            wxVector<Diretorio> listaDirPai,
            IProgressoLog progressoLog);
    bool carregarSubDiretorios(const wxString &sDiretorio,
            wxArrayString listaLocal);
    bool carregarArquivos(const wxString &sDiretorio,
            wxArrayString listaLocal);
    bool carregarTodosArquivos(const wxString &sDiretorio,
            wxArrayString listaLocal);
    wxVector<Diretorio> itensFilhos(wxVector<Diretorio> lista_pai,
            int aba, int codDirPai, int codigo);
};

}
}

#endif // DIRETORIOBO_H
