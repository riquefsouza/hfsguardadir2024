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
    diretorioGIF = Rotinas::getImagemByteArray("diretorio.gif");
    arquivoGIF = Rotinas::getImagemByteArray("arquivo.gif");

	arquivoBMP = Rotinas::getImagemByteArray("arquivo.bmp");
	diretorioBMP = Rotinas::getImagemByteArray("Fechar.bmp");
	//dirabertoBMP = Rotinas::getImagemByteArray("Abrir.bmp");

	arquivo32BMP = Rotinas::getImagemByteArray("arquivo32.bmp");
	diretorio32BMP = Rotinas::getImagemByteArray("Fechar32.bmp");
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

QList<Extensao> ExtensaoBO::carregarExtensao(IProgressoLog progressoLog) {
    return ExtensaoDAO::getInstancia()->consultarTudo(progressoLog);
}

int ExtensaoBO::retMaxCodExtensao(QList<Extensao> listaLocal) {
    int nMaior = 0;
    Extensao extensao;

    for (int i = 0; i < listaLocal.size(); ++i) {
        extensao = listaLocal.at(i);

        if (extensao.getCodigo() > nMaior) {
            nMaior = extensao.getCodigo();
        }
    }
    return nMaior + 1;
}

bool ExtensaoBO::existeExtensao(QString &sExtensao, QList<Extensao> listaLocal) {
    Extensao extensao;

    if (sExtensao.trimmed().length() > 0) {
        for (int i = 0; i < listaLocal.size(); ++i) {
            extensao = listaLocal.at(i);

            if (extensao.getNome().trimmed().toLower() ==
                    sExtensao.trimmed().toLower()) {
                return true;
            }
        }
    }
    return false;
}

bool ExtensaoBO::incluirExtensao(Extensao extensao) {
    return ExtensaoDAO::getInstancia()->incluir(extensao);
}

bool ExtensaoBO::SalvarExtensao(QList<Extensao> listaExtensao,
        QString sNomeDiretorio, QStringList log) {
    QString sExtensao;
    Extensao extensao;
	QPixmap pixmap;

    if (Rotinas::LastDelimiter('.', sNomeDiretorio) > 0) {
        sExtensao = Rotinas::SubString(sNomeDiretorio,
                Rotinas::LastDelimiter('.', sNomeDiretorio) + 1,
                sNomeDiretorio.length());
        if (!existeExtensao(sExtensao, listaExtensao)) {
            extensao.setCodigo(retMaxCodExtensao(listaExtensao));
            extensao.setNome(sExtensao.toLower());
            extensao.setOrdem(listaExtensao.size()+1);

            //pixmap = Rotinas::extrairIconeArquivo(sCaminhoOriginal);
			if (!pixmap.isNull()) {

				extensao.setBmp16(Rotinas::QPixmapToQByteArray(pixmap, Rotinas::EXTENSAO_BMP));

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
				listaExtensao.append(extensao);
				log.append("Salvando Extensão: " + extensao.getNome());
				return true;
			}
        }
    }

    return false;
}

void ExtensaoBO::salvarExtensoes(QList<Diretorio> listaDiretorio,
        QList<Extensao> listaExtensao, IProgressoLog progressoLog) {
    QStringList log;
    Diretorio diretorio;
    Progresso pb;

    pb.minimo = 0;
    pb.maximo = listaDiretorio.size() - 1;
    pb.posicao = 0;
    pb.passo = 1;

    for (int i = 0; i < listaDiretorio.size(); i++) {
        diretorio = listaDiretorio.at(i);

        if (diretorio.getTipo().getCodigo() == 'A') {
            SalvarExtensao(listaExtensao, diretorio.getNome(), log);
            if (log.size() > 0){
                pb.log = log.at(0);
                log.clear();
            }
        }

        pb.posicao = i;

        if (progressoLog != NULL) {
            progressoLog(pb);
        }
    }
}

bool ExtensaoBO::excluirExtensao(QList<Extensao> listaExtensao, int codigo) {
    Extensao extensao;

    if (ExtensaoDAO::getInstancia()->excluir(codigo)) {
        for (int i = 0; i < listaExtensao.size(); i++) {
            extensao = listaExtensao.at(i);
            if (extensao.getCodigo() == codigo) {
                listaExtensao.removeAt(i);
                break;
            }
        }
        return true;
    } else {
        return false;
    }
}

bool ExtensaoBO::excluirTodasExtensoes(QList<Extensao> listaExtensao) {
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

int ExtensaoBO::indiceExtensao(QList<Extensao> lista, QString &nomeExtensao) {
    nomeExtensao = Rotinas::SubString(nomeExtensao,
            Rotinas::LastDelimiter('.', nomeExtensao) + 1,
            nomeExtensao.length());

    Extensao extensao;
    for (int i = 0; i < lista.size(); i++) {
        extensao = lista.at(i);

        if (extensao.getNome().trimmed().toLower() ==
                nomeExtensao.trimmed().toLower()) {
            return (extensao.getOrdem() + 1);
        }
    }
    return -1;
}

Extensao* ExtensaoBO::pegaExtensaoPorOrdem(QList<Extensao> lista, int ordem) {
    Extensao *extensao = new Extensao();

    for (int i = 0; i < lista.size(); i++) {
        *extensao = lista.at(i);

        if (extensao->getOrdem() == ordem) {
            return extensao;
        }
    }
    return NULL;
}

Extensao* ExtensaoBO::pegaExtensaoPorCodigo(QList<Extensao> lista, int codigo) {
    Extensao *extensao = new Extensao();

    for (int i = 0; i < lista.size(); i++) {
        *extensao = lista.at(i);

        if (extensao->getCodigo() == codigo) {
            return extensao;
        }
    }
    return NULL;
}

Extensao ExtensaoBO::pegaExtensaoPorNome(QList<Extensao> lista,
        const QString &nome, const QString &tipo) {
    Extensao ext;

    if (tipo == Rotinas::getRecurso("TipoLista.diretorio")){
		ext.setBmp16(diretorioBMP);
		ext.setBmp32(diretorio32BMP);
        ext.setGif16(diretorioGIF);
    } else {
        if (lista.size() > 0) {
            foreach (Extensao extensao, lista) {
                if (extensao.getNome().toLower() ==
                        nome.toLower()) {
                    return extensao;
                }
            }
        }
        if (tipo == Rotinas::getRecurso("TipoLista.arquivo")){
			ext.setBmp16(arquivoBMP);
			ext.setBmp32(arquivo32BMP);
            ext.setGif16(arquivoGIF);
        }
    }
    return ext;
}

bool ExtensaoBO::ExportarExtensao(TipoExportarExtensao tipo,
        QList<Extensao> listaExtensao) {
    Extensao extensao;
    QString sCaminho, sImg16, sImg32, sExtensao;

    if (listaExtensao.size() > 0) {
        sCaminho = qApp->applicationDirPath() +
                Rotinas::BARRA_INVERTIDA;

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

        for (int i = 0; i < listaExtensao.size(); i++) {
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
                    if (!extensao.getBmp16().isEmpty()) {
                        Rotinas::SaveToFile(
                                Rotinas::BmpParaImagem(extensao.getBmp16(),
                                Rotinas::EXTENSAO_ICO), sImg16);
                    }
                    if (!extensao.getBmp32().isEmpty()) {
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
                    if (!extensao.getBmp16().isEmpty()) {
                        Rotinas::SaveToFile(
                                Rotinas::BmpParaImagem(extensao.getBmp16(),
                                Rotinas::EXTENSAO_JPEG), sImg16);
                    }
                    if (!extensao.getBmp32().isEmpty()) {
                        Rotinas::SaveToFile(
                                Rotinas::BmpParaImagem(extensao.getBmp32(),
                                Rotinas::EXTENSAO_JPEG), sImg32);
                    }
                }
                break;
                case tePNG: {
                    if (!extensao.getBmp16().isEmpty()) {
                        Rotinas::SaveToFile(
                                Rotinas::BmpParaImagem(extensao.getBmp16(),
                                Rotinas::EXTENSAO_PNG), sImg16);
                    }
                    if (!extensao.getBmp32().isEmpty()) {
                        Rotinas::SaveToFile(
                                Rotinas::BmpParaImagem(extensao.getBmp32(),
                                Rotinas::EXTENSAO_PNG), sImg32);
                    }
                }
                break;
                case teTIF: {
                    if (!extensao.getBmp16().isEmpty()) {
                        Rotinas::SaveToFile(
                                Rotinas::BmpParaImagem(extensao.getBmp16(),
                                Rotinas::EXTENSAO_TIFF), sImg16);
                    }
                    if (!extensao.getBmp32().isEmpty()) {
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

void ExtensaoBO::ImportarExtensao(QString &caminho,
        QList<Extensao> listaExtensao) {
    QString sArquivo;
    QStringList listaArquivos, log;

    if (DiretorioBO::getInstancia()->carregarArquivos(caminho, listaArquivos)) {

        for (int i = 0; i < listaArquivos.size(); ++i) {
            sArquivo = listaArquivos.at(i);

            SalvarExtensao(listaExtensao, Rotinas::ExtractFileName(sArquivo), log);
        }
    }

}

void ExtensaoBO::ExtrairExtensao(QString &caminho, QList<Extensao> listaExtensao) {
    QString sArquivo;
    QStringList listaArquivos, log;

    if (DiretorioBO::getInstancia()->carregarTodosArquivos(caminho, listaArquivos)) {
        for (int i = 0; i < listaArquivos.size(); ++i) {
            sArquivo = listaArquivos.at(i);

            SalvarExtensao(listaExtensao, Rotinas::ExtractFileName(sArquivo), log);
        }
    }

}

}
}
