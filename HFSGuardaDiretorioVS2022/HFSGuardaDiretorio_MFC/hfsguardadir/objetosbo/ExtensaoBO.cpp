#include "stdafx.h"

#include <stdio.h>
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

CList<Extensao, Extensao&>* ExtensaoBO::carregarExtensao(IProgressoLog progressoLog) {
    return ExtensaoDAO::getInstancia()->consultarTudo(progressoLog);
}

int ExtensaoBO::retMaxCodExtensao(const CList<Extensao, Extensao&> &listaLocal) {
	int nMaior = 0;
    Extensao extensao;
	POSITION pos;

	for (int i = 0; i < listaLocal.GetSize(); ++i) {
		pos = listaLocal.FindIndex(i);
		extensao = listaLocal.GetAt(pos);

        if (extensao.getCodigo() > nMaior) {
            nMaior = extensao.getCodigo();
        }
    }
    return nMaior + 1;
}

BOOL ExtensaoBO::existeExtensao(const CString &sExtensao, const CList<Extensao, Extensao&> &listaLocal) {
	CString sextensao = sExtensao;
    Extensao extensao;
	POSITION pos;

    if (Rotinas::Trim(sextensao).GetLength() > 0) {
		for (int i = 0; i < listaLocal.GetSize(); ++i) {
			pos = listaLocal.FindIndex(i);
			extensao = listaLocal.GetAt(pos);

            if (Rotinas::LowerCase(Rotinas::Trim(extensao.getNome())) =
				Rotinas::LowerCase(Rotinas::Trim(sextensao))) {
                return true;
            }
        }
    }
    return false;
}

BOOL ExtensaoBO::incluirExtensao(Extensao extensao) {
    return ExtensaoDAO::getInstancia()->incluir(extensao);
}

BOOL ExtensaoBO::SalvarExtensao(CList<Extensao, Extensao&> &listaExtensao,
	const CString &sNomeDiretorio, const CString &sCaminhoOriginal, CStringList &log) {
	CString sExtensao = _T("");
    Extensao extensao;
	HBITMAP bmp;
	CString slog = _T("");
	
    if (Rotinas::EndsStr(sNomeDiretorio, _T("."))) {
        sExtensao = Rotinas::SubString(sNomeDiretorio,
                Rotinas::LastDelimiter(_T("."), sNomeDiretorio) + 1,
                sNomeDiretorio.GetLength());
        if (!ExtensaoBO::existeExtensao(sExtensao, listaExtensao)) {
            extensao.setCodigo(ExtensaoBO::retMaxCodExtensao(listaExtensao));
            extensao.setNome(Rotinas::LowerCase(sExtensao));
            extensao.setOrdem(listaExtensao.GetSize()+1);

			bmp = Rotinas::extrairIconeArquivo(sCaminhoOriginal, 16);
			if (bmp != NULL) {
				extensao.setBmp16(Rotinas::HBitmapToBitmap(bmp, frmPrincipal->imageList16));

				bmp = Rotinas::extrairIconeArquivo(sCaminhoOriginal, 32);
				if (bmp != NULL) {
					extensao.setBmp32(Rotinas::HBitmapToBitmap(bmp, frmPrincipal->imageList32));
				}
				
				ExtensaoBO::incluirExtensao(extensao);
				listaExtensao.AddTail(extensao);
				slog = _T("Salvando Extensão: ") + extensao.getNome();
				log.AddTail(slog);
				return true;
			}
        }
    }

    return false;
}

void ExtensaoBO::salvarExtensoes(const CList<Diretorio, Diretorio&> &listaDiretorio,
        CList<Extensao, Extensao&> &listaExtensao, IProgressoLog progressoLog) {
	POSITION pos;
    CStringList log;
    Diretorio diretorio;
    Progresso pb;	

    pb.minimo = 0;
    pb.maximo = listaDiretorio.GetSize() - 1;
    pb.posicao = 0;
    pb.passo = 1;
	pb.log = _T("");

	for (int i = 0; i < listaDiretorio.GetSize(); ++i) {
		pos = listaDiretorio.FindIndex(i);
		diretorio = listaDiretorio.GetAt(pos);

        if (diretorio.getTipo().getCodigo() == 'A') {
			ExtensaoBO::SalvarExtensao(listaExtensao, diretorio.getNome(),
                    diretorio.getCaminhoOriginal(), log);
            if (log.GetSize() > 0){
				pb.log = log.GetHead();
				log.RemoveAll();
            }
        }

        pb.posicao++;

        if (progressoLog != NULL) {
            progressoLog(pb);
        }
    }
}

BOOL ExtensaoBO::excluirExtensao(CList<Extensao, Extensao&> &listaExtensao, int codigo) {
	POSITION pos;
    Extensao extensao;

    if (ExtensaoDAO::getInstancia()->excluir(codigo)) {
		for (int i = 0; i < listaExtensao.GetSize(); ++i) {
			pos = listaExtensao.FindIndex(i);
			extensao = listaExtensao.GetAt(pos);

			if (extensao.getCodigo() == codigo) {
				listaExtensao.RemoveAt(pos);
                break;
            }
        }
        return true;
    } else {
        return false;
    }
}

BOOL ExtensaoBO::excluirTodasExtensoes(CList<Extensao, Extensao&> &listaExtensao) {
    if (ExtensaoDAO::getInstancia()->excluirTudo()) {
		listaExtensao.RemoveAll();
        return true;
    } else {
        return false;
    }
}

BOOL ExtensaoBO::criarTabelaExtensoes() {
    return ExtensaoDAO::getInstancia()->criarTabela();
}

int ExtensaoBO::indiceExtensao(const CList<Extensao, Extensao&> &lista, const CString &nomeExtensao) {
	POSITION pos;
	Extensao extensao;

    CString snomeExtensao = Rotinas::SubString(nomeExtensao,
            Rotinas::LastDelimiter(_T("."), nomeExtensao) + 1,
            nomeExtensao.GetLength());
	    
	for (int i = 0; i < lista.GetSize(); ++i) {
		pos = lista.FindIndex(i);
		extensao = lista.GetAt(pos);

        if (Rotinas::LowerCase(Rotinas::Trim(extensao.getNome())) ==
			Rotinas::LowerCase(Rotinas::Trim(snomeExtensao))) {
            return (extensao.getOrdem() + 2);
        }
    }
    return -1;
}

Extensao* ExtensaoBO::pegaExtensaoPorOrdem(const CList<Extensao, Extensao&> &lista, int ordem) {
	POSITION pos;
    Extensao *extensao = new Extensao();

	for (int i = 0; i < lista.GetSize(); ++i) {
		pos = lista.FindIndex(i);
		*extensao = lista.GetAt(pos);

        if (extensao->getOrdem() == ordem) {
            return extensao;
        }
    }
    return NULL;
}

Extensao* ExtensaoBO::pegaExtensaoPorCodigo(const CList<Extensao, Extensao&> &lista, int codigo) {
	POSITION pos;
    Extensao *extensao = new Extensao();

	for (int i = 0; i < lista.GetSize(); ++i) {
		pos = lista.FindIndex(i);
		*extensao = lista.GetAt(pos);

        if (extensao->getCodigo() == codigo) {
            return extensao;
        }
    }
    return NULL;
}

/*
Extensao ExtensaoBO::pegaExtensaoPorNome(const CList<Extensao, Extensao&> &lista,
        const CString &nome, const CString &tipo) {
	POSITION pos;
    Extensao extensao;
	CString snome = nome;

    if (tipo == Rotinas::lerStr(STR_TIPOLISTA_DIRETORIO)){
		extensao.setBmp16(diretorioBMP);
		extensao.setBmp32(diretorio32BMP);
    } else {
        if (lista.GetSize() > 0) {
			for (int i = 0; i < lista.GetSize(); ++i) {
				pos = lista.FindIndex(i);
				extensao = lista.GetAt(pos);

				if (Rotinas::LowerCase(Rotinas::Trim(extensao.getNome())) ==
					Rotinas::LowerCase(Rotinas::Trim(snome)) {
                    return extensao;
                }
            }
        }
        if (tipo == Rotinas::lerStr(STR_TIPOLISTA_ARQUIVO)) {
			extensao.setBmp16(arquivoBMP);
			extensao.setBmp32(arquivo32BMP);
		}
    }
    return extensao;
}
*/

BOOL ExtensaoBO::ExportarExtensao(TipoExportarExtensao tipo,
        const CList<Extensao, Extensao&> &listaExtensao) {
	POSITION pos;
    Extensao extensao;
	CString sCaminho = _T("");
	CString sImg16 = _T("");
	CString sImg32 = _T("");
	CString sExtensao = _T("");

    if (listaExtensao.GetSize() > 0) {
		sCaminho = Rotinas::AppDirPath() + Rotinas::BARRA_INVERTIDA;

        if (tipo == teBMP) {
            sExtensao = _T(".") + Rotinas::EXTENSAO_BMP;
        } else if (tipo == teICO) {
			sExtensao = _T(".") + Rotinas::EXTENSAO_ICO;
        } else if (tipo == teGIF) {
			sExtensao = _T(".") + Rotinas::EXTENSAO_GIF;
        } else if (tipo == teJPG) {
			sExtensao = _T(".") + Rotinas::EXTENSAO_JPEG;
        } else if (tipo == tePNG) {
			sExtensao = _T(".") + Rotinas::EXTENSAO_PNG;
        } else if (tipo == teTIF) {
			sExtensao = _T(".") + Rotinas::EXTENSAO_TIFF;
        } else {
            sExtensao = _T(".img");
        }

		for (int i = 0; i < listaExtensao.GetSize(); ++i) {
			pos = listaExtensao.FindIndex(i);
			extensao = listaExtensao.GetAt(pos);

			sImg16 = sCaminho + extensao.getNome() + _T("16") + sExtensao;
            if (Rotinas::FileExists(sImg16)) {
                Rotinas::DeleteFromFile(sImg16);
            }

			sImg32 = sCaminho + extensao.getNome() + _T("32") + sExtensao;
            if (Rotinas::FileExists(sImg32)) {
                Rotinas::DeleteFromFile(sImg32);
            }

            switch (tipo) {
                case teBMP: {
                    //Rotinas::BlobSaveToFile(extensao.bmp16, 16, sImg16);
                    //Rotinas::BlobSaveToFile(extensao.bmp32, 16, sImg32);
                }
                break;
				/*
                case teICO: {
                    if (extensao.bmp16!=NULL) {
                        Rotinas::SaveToFile(
                                Rotinas::BmpParaImagem(extensao.bmp16,
                                Rotinas::EXTENSAO_ICO), sImg16);
                    }
                    if (extensao.bmp32!=NULL) {
                        Rotinas::SaveToFile(
                                Rotinas::BmpParaImagem(extensao.bmp32,
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
                    if (!extensao.bmp16.IsEmpty()) {
                        Rotinas::SaveToFile(
                                Rotinas::BmpParaImagem(extensao.bmp16,
                                Rotinas::EXTENSAO_JPEG), sImg16);
                    }
                    if (!extensao.bmp32.IsEmpty()) {
                        Rotinas::SaveToFile(
                                Rotinas::BmpParaImagem(extensao.bmp32,
                                Rotinas::EXTENSAO_JPEG), sImg32);
                    }
                }
                break;
                case tePNG: {
                    if (!extensao.bmp16.IsEmpty()) {
                        Rotinas::SaveToFile(
                                Rotinas::BmpParaImagem(extensao.bmp16,
                                Rotinas::EXTENSAO_PNG), sImg16);
                    }
                    if (!extensao.bmp32.IsEmpty()) {
                        Rotinas::SaveToFile(
                                Rotinas::BmpParaImagem(extensao.bmp32,
                                Rotinas::EXTENSAO_PNG), sImg32);
                    }
                }
                break;
                case teTIF: {
                    if (!extensao.bmp16.IsEmpty()) {
                        Rotinas::SaveToFile(
                                Rotinas::BmpParaImagem(extensao.bmp16,
                                Rotinas::EXTENSAO_TIFF), sImg16);
                    }
                    if (!extensao.bmp32.IsEmpty()) {
                        Rotinas::SaveToFile(
                                Rotinas::BmpParaImagem(extensao.bmp32,
                                Rotinas::EXTENSAO_TIFF), sImg32);
                    }
                }
                break;
				*/
                case teNUL: {
                }
            }

        }
        return true;
    }

    return false;
}

void ExtensaoBO::ImportarExtensao(const CString &caminho,
        CList<Extensao, Extensao&> &listaExtensao) {
	POSITION pos;
	CString sArquivo = _T("");
	CStringList listaArquivos;
	CStringList log;
		
    if (DiretorioBO::getInstancia()->carregarArquivos(caminho, listaArquivos)) {

		for (int i = 0; i < listaArquivos.GetSize(); ++i) {
			pos = listaArquivos.FindIndex(i);
			sArquivo = listaArquivos.GetAt(pos);

			ExtensaoBO::SalvarExtensao(listaExtensao, Rotinas::ExtractFileName(sArquivo),
                    sArquivo, log);
        }
    }
}

void ExtensaoBO::ExtrairExtensao(const CString &caminho, 
	CList<Extensao, Extensao&> &listaExtensao) {
	POSITION pos;
	CString sArquivo = _T("");
	CStringList listaArquivos;
	CStringList log;

	if (DiretorioBO::getInstancia()->carregarTodosArquivos(caminho, listaArquivos)) {

		for (int i = 0; i < listaArquivos.GetSize(); ++i) {
			pos = listaArquivos.FindIndex(i);
			sArquivo = listaArquivos.GetAt(pos);

			ExtensaoBO::SalvarExtensao(listaExtensao, Rotinas::ExtractFileName(sArquivo),
				sArquivo, log);
		}
	}

}

}
}
