#include "ExtensaoBO.h"

#include "hfsguardadir/objetosdao/ExtensaoDAO.h"
#include "hfsguardadir/objetosbo/DiretorioBO.h"

using namespace hfsguardadir::objetosdao;
using namespace hfsguardadir::objetosbo;

namespace hfsguardadir {

namespace objetosbo {

ExtensaoBO* ExtensaoBO::instancia = NULL;

ExtensaoBO::ExtensaoBO()
{
    //diretorioGIF = Rotinas::getImagemByteArray("diretorio.gif");
    //arquivoGIF = Rotinas::getImagemByteArray("arquivo.gif");

	arquivoBMP = Rotinas::getImagemByteArray("ARQUIVO");
	diretorioBMP = Rotinas::getImagemByteArray("DIRETORIO");
	//dirabertoBMP = Rotinas::getImagemByteArray("Abrir.bmp");

	arquivo32BMP = Rotinas::getImagemByteArray("ARQUIVO32");
	diretorio32BMP = Rotinas::getImagemByteArray("DIRETORIO32");
	//diraberto32BMP = Rotinas::getImagemByteArray("Abrir32.bmp");
}

ExtensaoBO::ExtensaoBO(ExtensaoBO const&){

}

ExtensaoBO& ExtensaoBO::operator=(ExtensaoBO const&){
    return *instancia;
}

ExtensaoBO* ExtensaoBO::getInstancia() {
    if (!instancia) {
        instancia = new ExtensaoBO();
    }
    return instancia;
}

wxVector<Extensao> ExtensaoBO::carregarExtensao(IProgressoLog progressoLog) {
    return ExtensaoDAO::getInstancia()->consultarTudo(progressoLog);
}

int ExtensaoBO::retMaxCodExtensao(wxVector<Extensao> listaLocal) {
    int nMaior = 0;
    Extensao extensao;

    for (unsigned int i = 0; i < listaLocal.size(); ++i) {
        extensao = listaLocal.at(i);

        if (extensao.getCodigo() > nMaior) {
            nMaior = extensao.getCodigo();
        }
    }
    return nMaior + 1;
}

bool ExtensaoBO::existeExtensao(const wxString &sExtensao, wxVector<Extensao> listaLocal) {
    Extensao extensao;

    if (Rotinas::Trim(sExtensao).length() > 0) {
        for (unsigned int i = 0; i < listaLocal.size(); ++i) {
            extensao = listaLocal.at(i);

            if (Rotinas::Trim(extensao.getNome()).Lower() ==
				Rotinas::Trim(sExtensao).Lower()) {
                return true;
            }
        }
    }
    return false;
}

bool ExtensaoBO::incluirExtensao(Extensao extensao) {
    return ExtensaoDAO::getInstancia()->incluir(extensao);
}

bool ExtensaoBO::SalvarExtensao(wxVector<Extensao> listaExtensao,
	const wxString &sNomeDiretorio, const wxString &sCaminhoOriginal, wxArrayString log) {
    wxString sExtensao;
    Extensao extensao;
	wxImage pixmap;

    if (Rotinas::LastDelimiter('.', sNomeDiretorio) > 0) {
        sExtensao = Rotinas::SubString(sNomeDiretorio,
                Rotinas::LastDelimiter('.', sNomeDiretorio) + 1,
                sNomeDiretorio.length());
        if (!existeExtensao(sExtensao, listaExtensao)) {
            extensao.setCodigo(retMaxCodExtensao(listaExtensao));
            extensao.setNome(sExtensao.Lower());
            extensao.setOrdem(listaExtensao.size()+1);

			pixmap = Rotinas::extrairIconeArquivo(sCaminhoOriginal);
			if (pixmap.IsOk()) {

				extensao.setBmp16(Rotinas::ImageToMemoryBuffer(pixmap, wxBITMAP_TYPE_BMP));

				//extensao.setBmp16(Rotinas::ArquivoToQByteArray(sCaminhoOriginal, 16, Rotinas::EXTENSAO_BMP));
				//extensao.setBmp32(Rotinas::ArquivoToQByteArray(sCaminhoOriginal, 32, Rotinas::EXTENSAO_BMP));
				/*
				if (extensao.getBmp16()!=null) {
					extensao.setGif16(Rotinas::BmpParaImagem(extensao.getBmp16(),
							Rotinas.EXTENSAO_GIF));
				}
				if (extensao.getBmp32()!=null) {
					extensao.setGif32(Rotinas::BmpParaImagem(extensao.getBmp32(),
							Rotinas.EXTENSAO_GIF));
				}
				*/
				incluirExtensao(extensao);
				listaExtensao.push_back(extensao);
				log.Add("Salvando Extensão: " + extensao.getNome());
				return true;
			}
        }
    }

    return false;
}

void ExtensaoBO::salvarExtensoes(wxVector<Diretorio> listaDiretorio,
        wxVector<Extensao> listaExtensao, IProgressoLog progressoLog) {
    wxArrayString log;
    Diretorio diretorio;
    Progresso pb;

    pb.minimo = 0;
    pb.maximo = listaDiretorio.size() - 1;
    pb.posicao = 0;
    pb.passo = 1;

    for (unsigned int i = 0; i < listaDiretorio.size(); i++) {
        diretorio = listaDiretorio.at(i);

        if (diretorio.getTipo().getCodigo() == 'A') {
            SalvarExtensao(listaExtensao, diretorio.getNome(),
                    diretorio.getCaminhoOriginal(), log);
            if (log.size() > 0){
                pb.log = log[0];
                log.clear();
            }
        }

        pb.posicao = i;

        if (progressoLog != NULL) {
            progressoLog(pb);
        }
    }
}

bool ExtensaoBO::excluirExtensao(wxVector<Extensao> listaExtensao, int codigo) {
    Extensao extensao;

    if (ExtensaoDAO::getInstancia()->excluir(codigo)) {
        for (unsigned int i = 0; i < listaExtensao.size(); i++) {
            extensao = listaExtensao.at(i);
            if (extensao.getCodigo() == codigo) {
                listaExtensao.erase(&listaExtensao[i]);
                break;
            }
        }
        return true;
    } else {
        return false;
    }
}

bool ExtensaoBO::excluirTodasExtensoes(wxVector<Extensao> listaExtensao) {
    if (ExtensaoDAO::getInstancia()->excluirTudo()) {
        listaExtensao.clear();
        return true;
    } else {
        return false;
    }
}

bool ExtensaoBO::criarTabelaExtensoes() {
    return ExtensaoDAO::getInstancia()->criarTabela();
}

int ExtensaoBO::indiceExtensao(wxVector<Extensao> lista, const wxString &nomeExtensao) {
	wxString nomeExt = Rotinas::SubString(nomeExtensao,
            Rotinas::LastDelimiter('.', nomeExtensao) + 1,
            nomeExtensao.length());

    Extensao extensao;
    for (unsigned int i = 0; i < lista.size(); i++) {
        extensao = lista.at(i);

        if (Rotinas::Trim(extensao.getNome()).Lower() ==
			Rotinas::Trim(nomeExt).Lower()) {
            return (extensao.getOrdem() + 2);
        }
    }
    return -1;
}

Extensao* ExtensaoBO::pegaExtensaoPorOrdem(wxVector<Extensao> lista, int ordem) {
    Extensao *extensao = new Extensao();

    for (unsigned int i = 0; i < lista.size(); i++) {
        *extensao = lista.at(i);

        if (extensao->getOrdem() == ordem) {
            return extensao;
        }
    }
    return NULL;
}

Extensao* ExtensaoBO::pegaExtensaoPorCodigo(wxVector<Extensao> lista, int codigo) {
    Extensao *extensao = new Extensao();

    for (unsigned int i = 0; i < lista.size(); i++) {
        *extensao = lista.at(i);

        if (extensao->getCodigo() == codigo) {
            return extensao;
        }
    }
    return NULL;
}

Extensao ExtensaoBO::pegaExtensaoPorNome(wxVector<Extensao> lista,
        const wxString &nome, const wxString &tipo) {
    Extensao extensao;

    if (tipo == Rotinas::getRecurso("TipoLista.diretorio")){
		extensao.setBmp16(diretorioBMP);
		extensao.setBmp32(diretorio32BMP);
		//extensao.setGif16(diretorioGIF);
    } else {
        if (lista.size() > 0) {
			for (unsigned int i = 0; i < lista.size(); i++) {
				extensao = lista[i];

                if (extensao.getNome().Lower() ==
                        nome.Lower()) {
                    return extensao;
                }
            }
        }
        if (tipo == Rotinas::getRecurso("TipoLista.arquivo")){
			extensao.setBmp16(arquivoBMP);
			extensao.setBmp32(arquivo32BMP);
			//extensao.setGif16(arquivoGIF);
        }
    }
    return extensao;
}

bool ExtensaoBO::ExportarExtensao(TipoExportarExtensao tipo,
        wxVector<Extensao> listaExtensao) {
    Extensao extensao;
    wxString sCaminho, sImg16, sImg32, sExtensao;

    if (listaExtensao.size() > 0) {
        sCaminho = Rotinas::AppDirPath() + Rotinas::BARRA_INVERTIDA;

        if (tipo == teBMP) {
            sExtensao = "." + Rotinas::EXTENSAO_BMP;
        } else if (tipo == teICO) {
            sExtensao = "." + Rotinas::EXTENSAO_ICO;
        } else if (tipo == teGIF) {
            sExtensao = "." + Rotinas::EXTENSAO_GIF;
        } else if (tipo == teJPG) {
            sExtensao = "." + Rotinas::EXTENSAO_JPEG;
        } else if (tipo == tePNG) {
            sExtensao = "." + Rotinas::EXTENSAO_PNG;
        } else if (tipo == teTIF) {
            sExtensao = "." + Rotinas::EXTENSAO_TIFF;
        } else {
            sExtensao = ".img";
        }

        for (unsigned int i = 0; i < listaExtensao.size(); i++) {
            extensao = listaExtensao.at(i);

            sImg16 = sCaminho + extensao.getNome() + "16" + sExtensao;
            if (Rotinas::FileExists(sImg16)) {
                Rotinas::DeleteFromFile(sImg16);
            }

            sImg32 = sCaminho + extensao.getNome() + "32" + sExtensao;
            if (Rotinas::FileExists(sImg32)) {
                Rotinas::DeleteFromFile(sImg32);
            }

            switch (tipo) {
                case teBMP: {
                    Rotinas::SaveToFile(extensao.getBmp16(), sImg16);
                    Rotinas::SaveToFile(extensao.getBmp32(), sImg32);
                }
                break;
                case teICO: {
                    if (!extensao.getBmp16().IsEmpty()) {
                        Rotinas::SaveToFile(
                                Rotinas::BmpParaImagem(extensao.getBmp16(),
                                Rotinas::EXTENSAO_ICO), sImg16);
                    }
                    if (!extensao.getBmp32().IsEmpty()) {
                        Rotinas::SaveToFile(
                                Rotinas::BmpParaImagem(extensao.getBmp32(),
                                Rotinas::EXTENSAO_ICO), sImg32);
                    }
                }
                break;
                case teGIF: {
                    Rotinas::SaveToFile(extensao.getGif16(), sImg16);
                    Rotinas::SaveToFile(extensao.getGif32(), sImg32);
                }
                break;
                case teJPG: {
                    if (!extensao.getBmp16().IsEmpty()) {
                        Rotinas::SaveToFile(
                                Rotinas::BmpParaImagem(extensao.getBmp16(),
                                Rotinas::EXTENSAO_JPEG), sImg16);
                    }
                    if (!extensao.getBmp32().IsEmpty()) {
                        Rotinas::SaveToFile(
                                Rotinas::BmpParaImagem(extensao.getBmp32(),
                                Rotinas::EXTENSAO_JPEG), sImg32);
                    }
                }
                break;
                case tePNG: {
                    if (!extensao.getBmp16().IsEmpty()) {
                        Rotinas::SaveToFile(
                                Rotinas::BmpParaImagem(extensao.getBmp16(),
                                Rotinas::EXTENSAO_PNG), sImg16);
                    }
                    if (!extensao.getBmp32().IsEmpty()) {
                        Rotinas::SaveToFile(
                                Rotinas::BmpParaImagem(extensao.getBmp32(),
                                Rotinas::EXTENSAO_PNG), sImg32);
                    }
                }
                break;
                case teTIF: {
                    if (!extensao.getBmp16().IsEmpty()) {
                        Rotinas::SaveToFile(
                                Rotinas::BmpParaImagem(extensao.getBmp16(),
                                Rotinas::EXTENSAO_TIFF), sImg16);
                    }
                    if (!extensao.getBmp32().IsEmpty()) {
                        Rotinas::SaveToFile(
                                Rotinas::BmpParaImagem(extensao.getBmp32(),
                                Rotinas::EXTENSAO_TIFF), sImg32);
                    }
                }
                break;
                case teNUL: {
                }
            }

        }
        return true;
    }

    return false;
}

void ExtensaoBO::ImportarExtensao(const wxString &caminho,
        wxVector<Extensao> listaExtensao) {
    wxString sArquivo;
    wxArrayString listaArquivos, log;

    if (DiretorioBO::getInstancia()->carregarArquivos(caminho, listaArquivos)) {

        for (unsigned int i = 0; i < listaArquivos.size(); ++i) {
            sArquivo = listaArquivos[i];

            SalvarExtensao(listaExtensao, Rotinas::ExtractFileName(sArquivo),
                    sArquivo, log);
        }
    }

}

void ExtensaoBO::ExtrairExtensao(const wxString &caminho, wxVector<Extensao> listaExtensao) {
    wxString sArquivo;
    wxArrayString listaArquivos, log;

    if (DiretorioBO::getInstancia()->carregarTodosArquivos(caminho, listaArquivos)) {
        for (unsigned int i = 0; i < listaArquivos.size(); ++i) {
            sArquivo = listaArquivos[i];

            SalvarExtensao(listaExtensao, Rotinas::ExtractFileName(sArquivo),
                    sArquivo, log);
        }
    }

}

}
}
