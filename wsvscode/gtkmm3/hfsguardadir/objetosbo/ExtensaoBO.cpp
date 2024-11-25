#include "ExtensaoBO.h"
#include "resource.h"
#include "hfsguardadir/objetosdao/ExtensaoDAO.h"
#include "hfsguardadir/objetosbo/DiretorioBO.h"
#include "FrmPrincipal.h"

using namespace hfsguardadir::objetosdao;
using namespace hfsguardadir::objetosbo;

namespace hfsguardadir {

namespace objetosbo {

ExtensaoBO* ExtensaoBO::instancia = NULL;

ExtensaoBO::ExtensaoBO()
{
	diretorioBMP = Rotinas::imagemToPixbuf("diretorio.bmp");
	arquivoBMP = Rotinas::imagemToPixbuf("arquivo.bmp");
	DiretorioXPM = Rotinas::XPMToPixbuf(XPM_DIRETORIO);
	ArquivoXPM = Rotinas::XPMToPixbuf(XPM_ARQUIVO);
	DirAbertoXPM = Rotinas::XPMToPixbuf(XPM_DIR_ABERTO);
	CDOuroXPM = Rotinas::XPMToPixbuf(XPM_CDOURO);
	Diretorio32XPM = Rotinas::XPMToPixbuf(XPM_DIRETORIO32);
	Arquivo32XPM = Rotinas::XPMToPixbuf(XPM_ARQUIVO32);
	DirAberto32XPM = Rotinas::XPMToPixbuf(XPM_DIR_ABERTO32);
}

ExtensaoBO::ExtensaoBO(ExtensaoBO const&) {

}

ExtensaoBO& ExtensaoBO::operator=(ExtensaoBO const&) {
	return *instancia;
}

ExtensaoBO* ExtensaoBO::getInstancia() {
	if (!instancia) {
		instancia = new ExtensaoBO();
	}
	return instancia;
}

std::vector<Extensao> ExtensaoBO::carregarExtensao(IProgressoLog progressoLog) {
    return ExtensaoDAO::getInstancia()->consultarTudo(progressoLog);
}

int ExtensaoBO::retMaxCodExtensao(const std::vector<Extensao>  &listaLocal) {
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

bool ExtensaoBO::existeExtensao(const Glib::ustring &sExtensao, const std::vector<Extensao>  &listaLocal) {
	Glib::ustring sextensao = sExtensao;
    Extensao extensao;


    if (Rotinas::Trim(sextensao).length() > 0) {
		for (unsigned int i = 0; i < listaLocal.size(); ++i) {
			extensao = listaLocal.at(i);

            if (Rotinas::LowerCase(Rotinas::Trim(extensao.getNome())) ==
				Rotinas::LowerCase(Rotinas::Trim(sextensao))) {
                return true;
            }
        }
    }
    return false;
}

bool ExtensaoBO::incluirExtensao(Extensao extensao) {
    return ExtensaoDAO::getInstancia()->incluir(extensao);
}

bool ExtensaoBO::SalvarExtensao(std::vector<Extensao>  &listaExtensao,
	const Glib::ustring &sNomeDiretorio, const Glib::ustring &sCaminhoOriginal, std::vector<Glib::ustring> &log) {
	Glib::ustring sExtensao = "";
    Extensao extensao;
	Glib::ustring slog = "";
	Glib::RefPtr<Gdk::Pixbuf> pixbuf16, pixbuf32;

    if (Rotinas::EndsStr(sNomeDiretorio, ".")) {
        sExtensao = Rotinas::SubString(sNomeDiretorio,
                Rotinas::LastDelimiter(".", sNomeDiretorio) + 1,
                sNomeDiretorio.length());
        if (!ExtensaoBO::existeExtensao(sExtensao, listaExtensao)) {
            extensao.setCodigo(ExtensaoBO::retMaxCodExtensao(listaExtensao));
            extensao.setNome(Rotinas::LowerCase(sExtensao));
            extensao.setOrdem(listaExtensao.size()+1);

			pixbuf16 = Rotinas::extrairPixbufArquivo(sCaminhoOriginal, 16);
			if (pixbuf16) {
				extensao.setBmp16(pixbuf16);

				pixbuf32 = Rotinas::extrairPixbufArquivo(sCaminhoOriginal, 32);
				if (pixbuf32) {
					extensao.setBmp32(pixbuf32);

					ExtensaoBO::incluirExtensao(extensao);
					listaExtensao.push_back(extensao);
					log.push_back("Salvando Extensão: " + extensao.getNome());
				}

				return true;
			}

        }
    }

    return false;
}

void ExtensaoBO::salvarExtensoes(const std::vector<Diretorio>  &listaDiretorio,
        std::vector<Extensao>  &listaExtensao, IProgressoLog progressoLog) {

    std::vector<Glib::ustring> log;
    Diretorio diretorio;
    Progresso pb;

    pb.minimo = 0;
    pb.maximo = listaDiretorio.size() - 1;
    pb.posicao = 0;
    pb.passo = 1;
	pb.log = "";

	for (unsigned int i = 0; i < listaDiretorio.size(); ++i) {
		diretorio = listaDiretorio.at(i);

        if (diretorio.getTipo().getCodigo() == 'A') {
			ExtensaoBO::SalvarExtensao(listaExtensao, diretorio.getNome(),
                    diretorio.getCaminhoOriginal(), log);
            if (log.size() > 0){
				pb.log = log.at(0);
				log.clear();
            }
        }

        pb.posicao++;

        if (progressoLog != NULL) {
            progressoLog(pb);
        }
    }
}

bool ExtensaoBO::excluirExtensao(std::vector<Extensao>  &listaExtensao, int codigo) {

    Extensao extensao;

    if (ExtensaoDAO::getInstancia()->excluir(codigo)) {
		for (unsigned int i = 0; i < listaExtensao.size(); ++i) {
			extensao = listaExtensao.at(i);

			if (extensao.getCodigo() == codigo) {
				listaExtensao.erase(listaExtensao.begin() + i);
                break;
            }
        }
        return true;
    } else {
        return false;
    }
}

bool ExtensaoBO::excluirTodasExtensoes(std::vector<Extensao>  &listaExtensao) {
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

int ExtensaoBO::indiceExtensao(const std::vector<Extensao> &lista, const Glib::ustring &nomeExtensao) {

	Extensao extensao;

    Glib::ustring snomeExtensao = Rotinas::SubString(nomeExtensao,
            Rotinas::LastDelimiter(".", nomeExtensao) + 1,
            nomeExtensao.length());

	for (unsigned int i = 0; i < lista.size(); ++i) {
		extensao = lista.at(i);

        if (Rotinas::LowerCase(Rotinas::Trim(extensao.getNome())) ==
			Rotinas::LowerCase(Rotinas::Trim(snomeExtensao))) {
            return (extensao.getOrdem() + 2);
        }
    }
    return -1;
}

Glib::RefPtr<Gdk::Pixbuf> ExtensaoBO::pixbufExtensao(
	const std::vector<Extensao> &lista, const Glib::ustring &nomeExtensao) {
	Extensao extensao;
	Glib::RefPtr<Gdk::Pixbuf> pixbuf;

	Glib::ustring snomeExtensao = Rotinas::SubString(nomeExtensao,
		Rotinas::LastDelimiter(".", nomeExtensao) + 1,
		nomeExtensao.length());

	for (unsigned int i = 0; i < lista.size(); i++) {
		extensao = lista.at(i);

		if (Rotinas::LowerCase(Rotinas::Trim(extensao.getNome())) ==
			Rotinas::LowerCase(Rotinas::Trim(snomeExtensao))) {
			return extensao.getBmp16();
		}
	}
	return ExtensaoBO::ArquivoXPM;
}

Extensao* ExtensaoBO::pegaExtensaoPorOrdem(const std::vector<Extensao>  &lista, int ordem) {

    Extensao *extensao = new Extensao();

	for (unsigned int i = 0; i < lista.size(); ++i) {
		*extensao = lista.at(i);

        if (extensao->getOrdem() == ordem) {
            return extensao;
        }
    }
    return NULL;
}

Extensao* ExtensaoBO::pegaExtensaoPorCodigo(const std::vector<Extensao>  &lista, int codigo) {

    Extensao *extensao = new Extensao();

	for (unsigned int i = 0; i < lista.size(); ++i) {
		*extensao = lista.at(i);

        if (extensao->getCodigo() == codigo) {
            return extensao;
        }
    }
    return NULL;
}

Extensao* ExtensaoBO::pegaExtensaoPorNome(const std::vector<Extensao>  &lista,
        const Glib::ustring &nome, const Glib::ustring &tipo) {

	Extensao *extensao = new Extensao();
	Glib::ustring snome = nome;

    if (tipo == Rotinas::getRecurso("TipoLista.diretorio")){
		extensao->setBmp16(ExtensaoBO::DiretorioXPM);
		extensao->setBmp32(ExtensaoBO::Diretorio32XPM);
    } else {
        if (lista.size() > 0) {
			for (unsigned int i = 0; i < lista.size(); ++i) {
				*extensao = lista.at(i);

				if (Rotinas::LowerCase(Rotinas::Trim(extensao->getNome())) ==
					Rotinas::LowerCase(Rotinas::Trim(snome))) {
                    return extensao;
                }
            }
        }
        if (tipo == Rotinas::getRecurso("TipoLista.arquivo")) {
			extensao->setBmp16(ExtensaoBO::Arquivo32XPM);
			extensao->setBmp32(ExtensaoBO::Arquivo32XPM);
		}
    }
    return extensao;
}


bool ExtensaoBO::ExportarExtensao(TipoExportarExtensao tipo,
        const std::vector<Extensao>  &listaExtensao) {

    Extensao extensao;
	Glib::ustring sCaminho = "";
	Glib::ustring sImg16 = "";
	Glib::ustring sImg32 = "";
	Glib::ustring sExtensao = "";

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

		for (unsigned int i = 0; i < listaExtensao.size(); ++i) {
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
				Rotinas::PixbufToArquivo(extensao.getBmp16(), sImg16, Rotinas::EXTENSAO_BMP);
				Rotinas::PixbufToArquivo(extensao.getBmp32(), sImg32, Rotinas::EXTENSAO_BMP);
			}
						break;
			case teICO: {
				if (extensao.getBmp16())
					Rotinas::PixbufToArquivo(extensao.getBmp16(), sImg16, Rotinas::EXTENSAO_ICO);
				if (extensao.getBmp32())
					Rotinas::PixbufToArquivo(extensao.getBmp32(), sImg32, Rotinas::EXTENSAO_ICO);
			}
						break;
			case teGIF: {
				if (extensao.getBmp16())
					Rotinas::PixbufToArquivo(extensao.getBmp16(), sImg16, Rotinas::EXTENSAO_GIF);
				if (extensao.getBmp32())
					Rotinas::PixbufToArquivo(extensao.getBmp32(), sImg32, Rotinas::EXTENSAO_GIF);
			}
						break;
			case teJPG: {
				if (extensao.getBmp16())
					Rotinas::PixbufToArquivo(extensao.getBmp16(), sImg16, Rotinas::EXTENSAO_JPEG);
				if (extensao.getBmp32())
					Rotinas::PixbufToArquivo(extensao.getBmp32(), sImg32, Rotinas::EXTENSAO_JPEG);
			}
						break;
			case tePNG: {
				if (extensao.getBmp16())
					Rotinas::PixbufToArquivo(extensao.getBmp16(), sImg16, Rotinas::EXTENSAO_PNG);
				if (extensao.getBmp32())
					Rotinas::PixbufToArquivo(extensao.getBmp32(), sImg32, Rotinas::EXTENSAO_PNG);
			}
						break;
			case teTIF: {
				if (extensao.getBmp16())
					Rotinas::PixbufToArquivo(extensao.getBmp16(), sImg16, Rotinas::EXTENSAO_TIFF);
				if (extensao.getBmp32())
					Rotinas::PixbufToArquivo(extensao.getBmp32(), sImg32, Rotinas::EXTENSAO_TIFF);
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

void ExtensaoBO::ImportarExtensao(const Glib::ustring &caminho,
        std::vector<Extensao>  &listaExtensao) {

	Glib::ustring sArquivo = "";
	std::vector<Glib::ustring> listaArquivos;
	std::vector<Glib::ustring> log;

    if (DiretorioBO::getInstancia()->carregarArquivos(caminho, listaArquivos)) {

		for (unsigned int i = 0; i < listaArquivos.size(); ++i) {
			sArquivo = listaArquivos.at(i);

			ExtensaoBO::SalvarExtensao(listaExtensao, Rotinas::ExtractFileName(sArquivo),
                    sArquivo, log);
        }
    }
}

void ExtensaoBO::ExtrairExtensao(const Glib::ustring &caminho,
	std::vector<Extensao>  &listaExtensao) {

	Glib::ustring sArquivo = "";
	std::vector<Glib::ustring> listaArquivos;
	std::vector<Glib::ustring> log;

	if (DiretorioBO::getInstancia()->carregarTodosArquivos(caminho, listaArquivos)) {

		for (unsigned int i = 0; i < listaArquivos.size(); ++i) {
			sArquivo = listaArquivos.at(i);

			ExtensaoBO::SalvarExtensao(listaExtensao, Rotinas::ExtractFileName(sArquivo),
				sArquivo, log);
		}
	}

}

}
}
