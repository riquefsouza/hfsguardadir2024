#ifndef EXTENSAOBO_H
#define EXTENSAOBO_H

#include <wx/vector.h>
#include "hfsguardadir/objetos/Extensao.h"
#include "hfsguardadir/objetos/Diretorio.h"
#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosbo {

class ExtensaoBO
{
private:
	wxMemoryBuffer diretorioBMP, diretorio32BMP;
	// wxMemoryBuffer diretorioGIF, arquivoGIF;
	//wxMemoryBuffer dirabertoBMP, diraberto32BMP;
	wxMemoryBuffer arquivoBMP, arquivo32BMP;

	ExtensaoBO();
    ExtensaoBO(ExtensaoBO const&);
    ExtensaoBO& operator=(ExtensaoBO const&);
    static ExtensaoBO* instancia;

public:
    static ExtensaoBO* getInstancia();

    wxVector<Extensao> carregarExtensao(IProgressoLog progressoLog);
    int retMaxCodExtensao(wxVector<Extensao> listaLocal);
    bool existeExtensao(const wxString &sExtensao, wxVector<Extensao> listaLocal);
    bool incluirExtensao(Extensao extensao);
    bool SalvarExtensao(wxVector<Extensao> listaExtensao, const wxString &sNomeDiretorio,
		const wxString &sCaminhoOriginal, wxArrayString log);
    void salvarExtensoes(wxVector<Diretorio> listaDiretorio,
            wxVector<Extensao> listaExtensao, IProgressoLog progressoLog);
    bool excluirExtensao(wxVector<Extensao> listaExtensao, int codigo);
    bool excluirTodasExtensoes(wxVector<Extensao> listaExtensao);
    bool criarTabelaExtensoes();
    int indiceExtensao(wxVector<Extensao> lista, const wxString &nomeExtensao);
    Extensao* pegaExtensaoPorOrdem(wxVector<Extensao> lista, int ordem);
    Extensao* pegaExtensaoPorCodigo(wxVector<Extensao> lista, int codigo);
    Extensao pegaExtensaoPorNome(wxVector<Extensao> lista,
            const wxString &nome, const wxString &tipo);
    bool ExportarExtensao(TipoExportarExtensao tipo,
                          wxVector<Extensao> listaExtensao);
    void ImportarExtensao(const wxString &caminho, wxVector<Extensao> listaExtensao);
    void ExtrairExtensao(const wxString &caminho, wxVector<Extensao> listaExtensao);
};

}
}

#endif // EXTENSAOBO_H
