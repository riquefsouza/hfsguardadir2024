#include "stdafx.h"

#include "DiretorioBO.h"
#include "resource.h"
#include "hfsguardadir/objetosdao/DiretorioDAO.h"
#include "hfsguardadir/objetosbo/AbaBO.h"

using namespace hfsguardadir::objetosdao;
using namespace hfsguardadir::objetosbo;

namespace hfsguardadir {

namespace objetosbo {

const CString DiretorioBO::SQL_CONSULTA_ARQUIVO = _T("select aba, cod, " \
            "ordem, coddirpai, nome, tam, tipo, modificado, atributos, " \
            "caminho, nomeaba, nomepai, caminhopai from consultaarquivo");

DiretorioBO* DiretorioBO::instancia = NULL;

DiretorioBO::DiretorioBO()
{

}

DiretorioBO::DiretorioBO(DiretorioBO const&) {

}

DiretorioBO& DiretorioBO::operator=(DiretorioBO const&) {
	return *instancia;
}

DiretorioBO* DiretorioBO::getInstancia() {
	if (!instancia) {
		instancia = new DiretorioBO();
	}
	return instancia;
}

CList<Diretorio, Diretorio&>* DiretorioBO::carregarDiretorio(
        const CString &sSQL, IProgressoLog progressoLog) {
    return DiretorioDAO::getInstancia()->consultarTudo(sSQL, _T(""), progressoLog);
}

CList<Diretorio, Diretorio&>* DiretorioBO::carregarDiretorio(const CString &sSQL,
	const CString &sCondicaoTotal, IProgressoLog progressoLog) {

    return DiretorioDAO::getInstancia()->consultarTudo(
                sSQL, sCondicaoTotal, progressoLog);
}


CString DiretorioBO::removerDrive(const CString &sDiretorio) {
	CString sArq = sDiretorio;
	CString drive = _T(":");
	BOOL bAchou = FALSE;

	/*
	WCHAR drives[512];
	drives[0] = '\0';
	if (GetLogicalDriveStrings(511, drives)) {
		drive = _T(drives[0]);
	}
	*/

    if (sArq.GetLength() > 0) {
        if (Rotinas::ContainsStr(Rotinas::UpperCase(sArq),
			Rotinas::UpperCase(drive))) {
                bAchou = TRUE;
        }
    }
    sArq = Rotinas::trocaSeparador(sArq);
    if (bAchou) {
        sArq = Rotinas::SubString(sArq, drive.GetLength()+3, sArq.GetLength());
    }	
	return sArq;
}

int DiretorioBO::retCodDirPai(int nAba, const CString &sDiretorio,
                              const CList<Diretorio, Diretorio&> &listaLocal) {
	POSITION pos;
    Diretorio diretorio;

	for (int i = 0; i < listaLocal.GetSize(); ++i) {
		pos = listaLocal.FindIndex(i);
		diretorio = listaLocal.GetAt(pos);

        if (diretorio.getAba().getCodigo() == nAba) {
            if (diretorio.getCaminho() == sDiretorio) {
                return diretorio.getOrdem();
            }
        }
    }
    return 0;
}

Diretorio DiretorioBO::atribuiDiretorio(int nAba, int nCodDirRaiz,
        const CString &sNomeDirRaiz, const CString &sDiretorio, BOOL bDiretorio,
        const CList<Diretorio, Diretorio&> &listaLocal, Arquivo arquivo,
        DiretorioOrdem *dirOrdem) {
    int nOrdem = dirOrdem->getOrdem();
    Diretorio diretorio;
    CString sCaminho, sDir;
	long long tamanho;

    Aba abaLocal;
    Tipo tipoLocal;

    sCaminho = removerDrive(sDiretorio);

    if ((sCaminho.GetLength() > 0) && (sNomeDirRaiz.GetLength() > 0)) {
        if (Rotinas::StartsStr(sCaminho, sNomeDirRaiz)) {
            sCaminho = Rotinas::SubString(sCaminho, sNomeDirRaiz.GetLength()+2,
                        sCaminho.GetLength());
            sDir = Rotinas::SubString(sDiretorio, sNomeDirRaiz.GetLength()+2,
                            sDiretorio.GetLength());
        } else {
            sCaminho = sNomeDirRaiz + Rotinas::BARRA_INVERTIDA + sCaminho;
            sDir = sNomeDirRaiz + Rotinas::BARRA_INVERTIDA + sDiretorio;
        }
    }

    abaLocal.setCodigo(nAba);
    diretorio.setCodigo(nCodDirRaiz);
    diretorio.setOrdem(nOrdem);
    diretorio.setNome(arquivo.getNome());
    diretorio.setTamanho(arquivo.getTamanho());
	diretorio.setModificado(arquivo.getModificado());	
    diretorio.setAtributos(arquivo.getAtributos());

    if (sDiretorio.GetLength()==0) {
        diretorio.setCaminho(arquivo.getNome());
		diretorio.setCaminhoPai(_T(""));
    } else {
        diretorio.setCaminho(sCaminho);
        diretorio.setCaminhoPai(Rotinas::SubString(diretorio.getCaminho(), 1,
                Rotinas::LastDelimiter(Rotinas::BARRA_INVERTIDA,
                        diretorio.getCaminho()) - 1));
    }

    if (bDiretorio) {
        tipoLocal.setCodigo('D');
        if (nOrdem == 1) {
            diretorio.setCodDirPai(0);
        } else {
            diretorio.setCodDirPai(DiretorioBO::retCodDirPai(abaLocal.getCodigo(),
                    diretorio.getCaminhoPai(), listaLocal));
        }
    } else {
        tipoLocal.setCodigo('A');
        diretorio.setCodDirPai(DiretorioBO::retCodDirPai(abaLocal.getCodigo(),
                diretorio.getCaminhoPai(), listaLocal));
    }    
    abaLocal.setNome(_T(""));
    diretorio.setAba(abaLocal);
    diretorio.setNomePai(_T(""));
	tamanho = diretorio.getTamanho();
    diretorio.setTamanhoFormatado(Rotinas::MontaTamanho(tamanho));
    if (tipoLocal.getCodigo() == 'D') {
		tipoLocal.setNome(Rotinas::lerStr(STR_TIPOLISTA_DIRETORIO));
    } else {
		tipoLocal.setNome(Rotinas::lerStr(STR_TIPOLISTA_ARQUIVO));
    }
	diretorio.setTipo(tipoLocal);
    diretorio.setModificadoFormatado(Rotinas::formataDate(
            Rotinas::FORMATO_DATAHORA, diretorio.getModificado()));
    diretorio.setCaminhoOriginal(sDiretorio);

    nOrdem++;

    dirOrdem->setOrdem(nOrdem);

    return diretorio;
}

void DiretorioBO::atribuiListaDiretorio(int nAba, int nCodDirRaiz,
        const CString &sNomeDirRaiz, const CString &sDiretorio, 
		CList<Diretorio, Diretorio&> *listaLocal,
        Arquivo info, DiretorioOrdem *dirOrdem, IProgressoLog progressoLog) {
    Diretorio diretorio;
    Progresso pb;
	pb.log = _T("");

    if (Rotinas::FileExists(sDiretorio)) {
		diretorio = DiretorioBO::atribuiDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz,
                sDiretorio, false, *listaLocal, info,
                dirOrdem);
		listaLocal->AddTail(diretorio);

        if (progressoLog != NULL) {
            pb.log = sDiretorio;
            progressoLog(pb);
        }
    } else if (Rotinas::DirectoryExists(sDiretorio)) {
        if (info.getNome()!="." && info.getNome()!="..") {
            diretorio = DiretorioBO::atribuiDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz,
                    sDiretorio, true, *listaLocal, info,
                    dirOrdem);
			listaLocal->AddTail(diretorio);

            if (progressoLog != NULL) {
                pb.log = sDiretorio;
                progressoLog(pb);
            }

			DiretorioBO::ImportarDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz, sDiretorio,
                    listaLocal, dirOrdem, progressoLog);
        }
    }

}

void DiretorioBO::ImportarDiretorio(int nAba, int nCodDirRaiz,
        const CString &sNomeDirRaiz, const CString &sDiretorio, 
		CList<Diretorio, Diretorio&> *listaLocal,
        DiretorioOrdem *dirOrdem, IProgressoLog progressoLog) {
	Arquivo info;
    CString sCaminho, sSeparador, arquivo = _T("");
	CFileFind finder;
	BOOL bAchou;
	
    if (Rotinas::SubString(sDiretorio, sDiretorio.GetLength(), 1) == Rotinas::BARRA_NORMAL) {
        sSeparador = _T("");
    } else {
		sSeparador = Rotinas::BARRA_NORMAL;
    }

    sCaminho = sDiretorio + sSeparador + _T("*.*");

	bAchou = finder.FindFile(sCaminho);
	while (bAchou) {
		bAchou = finder.FindNextFile();

		if (finder.IsDots()) {
			continue;
		}

		sCaminho = finder.GetFilePath();
		info = Rotinas::FileInfoToArquivo(finder);

		DiretorioBO::atribuiListaDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz,
			sCaminho, listaLocal, info, dirOrdem,
			progressoLog);
	}

	finder.Close();
}

BOOL DiretorioBO::verificaCodDir(int nAba, const CString &sDiretorio,
        const CList<Diretorio, Diretorio&> &listaLocal) {
	POSITION pos;
	Diretorio diretorio;

    if (sDiretorio.GetLength() > 0) {
		for (int i = 0; i < listaLocal.GetSize(); ++i) {
			pos = listaLocal.FindIndex(i);
			diretorio = listaLocal.GetAt(pos);

            if (diretorio.getAba().getCodigo() == nAba) {
                if (diretorio.getOrdem() == 1) {
                    if (diretorio.getCodDirPai() == 0) {
                        if (diretorio.getCaminho() == sDiretorio) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

int DiretorioBO::retMaxCodDir(int nAba, const CList<Diretorio, Diretorio&> &listaLocal) {
    int nMaior = -1;
	POSITION pos;
    Diretorio diretorio;

	for (int i = 0; i < listaLocal.GetSize(); ++i) {
		pos = listaLocal.FindIndex(i);
		diretorio = listaLocal.GetAt(pos);

		if (diretorio.getAba().getCodigo() == nAba) {
            if (diretorio.getCodigo() > nMaior) {
                nMaior = diretorio.getCodigo();
            }
        }
    }
    return nMaior + 1;
}

CString DiretorioBO::diretorioToSQL(Diretorio diretorio, BOOL bInsert) {
    CString sSQL = _T("");

    if (bInsert) {
        sSQL = _T("insert into Diretorios(aba, cod, ordem, coddirpai, nome, " \
               "tam, tipo, modificado, atributos, caminho) values(");
    }
	
    sSQL += Rotinas::FromInt(diretorio.getAba().getCodigo()) + _T(",");
	sSQL += Rotinas::FromInt(diretorio.getCodigo()) + _T(",");
	sSQL += Rotinas::FromInt(diretorio.getOrdem()) + _T(",");
	sSQL += Rotinas::FromInt(diretorio.getCodDirPai()) + _T(",");
    sSQL += Rotinas::QuotedStr(diretorio.getNome()) + _T(",");
	sSQL += Rotinas::FromLongLong(diretorio.getTamanho()) + _T(",");
    sSQL += Rotinas::QuotedStr(diretorio.getTipo().getCodigo()) + _T(",");
    sSQL += Rotinas::QuotedStr(diretorio.getModificadoFormatado()) + _T(",");
    sSQL += Rotinas::QuotedStr(diretorio.getAtributos()) + _T(",");
    sSQL += Rotinas::QuotedStr(diretorio.getCaminho()) + _T(",");

    if (bInsert) {
        sSQL += _T(")");
    }

    return sSQL;
}

void DiretorioBO::salvarDiretorio(const CList<Diretorio, Diretorio&> &listaDiretorio,
        IProgressoLog progressoLog) {
	POSITION pos;
    Diretorio diretorio;
    Progresso pb;
    pb.minimo = 0;
    pb.maximo = listaDiretorio.GetSize() - 1;
    pb.posicao = 0;
    pb.passo = 1;
	pb.log = _T("");
	CString sdir = Rotinas::lerStr(STR_TIPOLISTA_DIRETORIO);

	for (int i = 0; i < listaDiretorio.GetSize(); ++i) {
		pos = listaDiretorio.FindIndex(i);
		diretorio = listaDiretorio.GetAt(pos);

        DiretorioDAO::getInstancia()->incluir(diretorio);
        pb.log = Rotinas::FromInt(i + 1) + 
			_T(" - Salvando ") + sdir + ": " + diretorio.getCaminho();
		
        pb.posicao = i;

        if (progressoLog != NULL) {
            progressoLog(pb);
        }
    }
}

BOOL DiretorioBO::excluirDiretorio(Aba aba, const CString &sCaminho) {
   return DiretorioDAO::getInstancia()->excluir(aba, sCaminho);
}

void DiretorioBO::excluirListaDiretorio(CList<Diretorio, Diretorio&> *listaDiretorio,
        Aba aba, const CString &sCaminho) {
	CString scaminho = sCaminho;
	POSITION pos;
    Diretorio diretorio;
	int conta = 0;

	for (int i = 0; i < listaDiretorio->GetSize(); ++i) {
		pos = listaDiretorio->FindIndex(i);
		diretorio = listaDiretorio->GetAt(pos);

        if (diretorio.getAba().getCodigo() == aba.getCodigo()) {
            if (Rotinas::Trim(scaminho).GetLength() > 0) {
                if (Rotinas::StartsStr(diretorio.getCaminho(), scaminho)) {
					listaDiretorio->RemoveAt(pos);
                }
            } else {
				listaDiretorio->RemoveAt(pos);
            }
        }

		
    }

}

CString DiretorioBO::diretorioToCSV(Diretorio diretorio) {
    CString sCSV = _T("\"");

    sCSV += diretorio.getAba().getNome() + _T("\";\"");
    sCSV += diretorio.getNome() + _T("\";\"");
    sCSV += Rotinas::FromLongLong(diretorio.getTamanho()) + _T("\";\"");
    sCSV += diretorio.getTamanhoFormatado() + _T("\";\"");
    sCSV += diretorio.getTipo().getNome() + _T("\";\"");
    sCSV += diretorio.getModificadoFormatado() + _T("\";\"");
    sCSV += diretorio.getAtributos() + _T("\";\"");
    sCSV += diretorio.getCaminho() + _T("\"");

    return sCSV;
}

CString DiretorioBO::diretorioToXML(Diretorio diretorio) {
    CString sXML, sCR, sTAB, sTAB2;

    sTAB = _T("\t");
    sTAB2 = _T("\t\t");
    sCR = _T("\n");

    sXML = sTAB + _T("<arquivo>") + sCR;

    sXML += sTAB2 + _T("<aba>") + Rotinas::FromInt(diretorio.getAba().getCodigo()) +
            _T("</aba>") + sCR;
    sXML += sTAB2 + _T("<nomeAba>") + diretorio.getAba().getNome() +
            _T("</nomeAba>") + sCR;
    sXML += sTAB2 + _T("<codigo>") + Rotinas::FromInt(diretorio.getCodigo()) +
		_T("</codigo>") + sCR;
    sXML += sTAB2 + _T("<ordem>") + Rotinas::FromInt(diretorio.getOrdem()) +
		_T("</ordem>") + sCR;
    sXML += sTAB2 + _T("<nome>") + diretorio.getNome() + _T("</nome>") + sCR;
    sXML += sTAB2 + _T("<tamanho>") + Rotinas::FromLongLong(diretorio.getTamanho()) +
		_T("</tamanho>") + sCR;
    sXML += sTAB2 + _T("<tipo>") + diretorio.getTipo().getCodigo() +
		_T("</tipo>") + sCR;
    sXML += sTAB2 + _T("<modificado>") + diretorio.getModificadoFormatado() +
		_T("</modificado>") + sCR;
    sXML += sTAB2 + _T("<atributos>") + diretorio.getAtributos() +
		_T("</atributos>") + sCR;
    sXML += sTAB2 + _T("<codDirPai>") + Rotinas::FromInt(diretorio.getCodDirPai()) +
		_T("</codDirPai>") + sCR;
    sXML += sTAB2 + _T("<caminho>") + diretorio.getCaminho() +
		_T("</caminho>") + sCR;

    sXML += sTAB + _T("</arquivo>");

    return sXML;
}

CString DiretorioBO::diretorioToTXT(Diretorio diretorio) {
    CString sTXT, sTAB;

    sTAB = _T("\t");
    sTXT = _T("");
    sTXT += diretorio.getAba().getNome() + sTAB;
    sTXT += diretorio.getNome() + sTAB;
    sTXT += Rotinas::FromLongLong(diretorio.getTamanho()) + sTAB;
    sTXT += diretorio.getTamanhoFormatado() + sTAB;
    sTXT += diretorio.getTipo().getNome() + sTAB;
    sTXT += diretorio.getModificadoFormatado() + sTAB;
    sTXT += diretorio.getAtributos() + sTAB;
    sTXT += diretorio.getCaminho();

    return sTXT;
}

CString DiretorioBO::diretorioToHTML(Diretorio diretorio) {
    CString sHTML, sCR, sTAB, sTAB2;

    sTAB = _T("\t");
    sTAB2 = _T("\t\t");
    sCR = _T("\n");

    sHTML = sTAB + _T("<tr>") + sCR;

    sHTML += sTAB2 + _T("<td>") + diretorio.getAba().getNome() + _T("</td>") + sCR;
    sHTML += sTAB2 + _T("<td>") + diretorio.getNome() + _T("</td>") + sCR;
    sHTML += sTAB2 + _T("<td>") + Rotinas::FromLongLong(diretorio.getTamanho()) + _T("</td>") + sCR;
    sHTML += sTAB2 + _T("<td>") + Rotinas::StringReplaceAll(
            diretorio.getTamanhoFormatado(), _T(" "), _T("&nbsp;")) + _T("</td>") + sCR;
    sHTML += sTAB2 + _T("<td>") + diretorio.getTipo().getNome() + _T("</td>") + sCR;
    sHTML += sTAB2 + _T("<td>") + Rotinas::StringReplaceAll(
		diretorio.getModificadoFormatado(), _T(" "), _T("&nbsp;")) + _T("</td>") + sCR;
    sHTML += sTAB2 + _T("<td>") + diretorio.getAtributos() + _T("</td>") + sCR;
    sHTML += sTAB2 + _T("<td>") + diretorio.getCaminho() + _T("</td>") + sCR;

    sHTML += sTAB + _T("</tr>");
    return sHTML;
}

void DiretorioBO::exportarDiretorio(TipoExportar tipo, Aba aba,
        const CString &sNomeArquivo, IProgressoLog progressoLog) {
    CString sTexto = _T(""), sCR, sTAB, sTAB2, sSQL, sCondicaoTotal;
    Aba abaLocal;
	POSITION pos;
    Diretorio diretorio;
    CStringList listaLocal;
    CList<Diretorio, Diretorio&>* listaDiretorio = new CList<Diretorio, Diretorio&>();

    sTAB = _T("\t");
    sTAB2 = _T("\t\t");
    sCR = _T("\n");

    sCondicaoTotal = _T(" where aba=") + Rotinas::FromInt(aba.getCodigo());
    sSQL = DiretorioBO::SQL_CONSULTA_ARQUIVO + sCondicaoTotal + _T(" order by 1, 2, 3");
    listaDiretorio = DiretorioBO::carregarDiretorio(sSQL, sCondicaoTotal, progressoLog);

    switch (tipo) {
        case teCSV: {
            sTexto = _T("\"Aba\";\"Nome\";\"TamanhoBytes\";\"Tamanho\";" \
                     "\"Tipo\";\"Modificado\";\"Atributos\";\"Caminho\"");
        }
        break;
        case teHTML: {
            sTexto = _T("<!DOCTYPE html>") + sCR;
            sTexto += _T("<html>") + sCR;
            sTexto += _T("<body>") + sCR;
            sTexto += _T("<table border=\"1\" cellpadding=\"5\" cellspacing=\"0\">"
                   ) + sCR;
            sTexto += sTAB + _T("<tr>") + sCR;
            sTexto += sTAB2 + _T("<th>Aba</th>") + sCR;
            sTexto += sTAB2 + _T("<th>Nome</th>") + sCR;
            sTexto += sTAB2 + _T("<th>Tamanho</th>") + sCR;
            sTexto += sTAB2 + _T("<th>Tamanho Formatado</th>") + sCR;
            sTexto += sTAB2 + _T("<th>Tipo</th>") + sCR;
            sTexto += sTAB2 + _T("<th>Modificado</th>") + sCR;
            sTexto += sTAB2 + _T("<th>Atributos</th>") + sCR;
            sTexto += sTAB2 + _T("<th>Caminho</th>") + sCR;
            sTexto += sTAB + _T("</tr>");
        }
        break;
        case teXML: {
            sTexto = _T("<diretorio>");
        }
        break;
        case teSQL: {
			diretorio = listaDiretorio->GetHead();
            abaLocal.setCodigo(diretorio.getAba().getCodigo());
            abaLocal.setNome(diretorio.getAba().getNome());
            sTexto = AbaBO::getInstancia()->abaToSQL(abaLocal);
        }
        break;
        case teTXT: {
        }
    }
	listaLocal.AddTail(sTexto);

	for (int i = 0; i < listaDiretorio->GetSize(); ++i) {
		pos = listaDiretorio->FindIndex(i);
		diretorio = listaDiretorio->GetAt(pos);

        if (diretorio.getAba().getCodigo() == aba.getCodigo()) {
            if (tipo == teTXT) {
                sTexto = DiretorioBO::diretorioToTXT(diretorio);
            } else if (tipo == teCSV) {
                sTexto = DiretorioBO::diretorioToCSV(diretorio);
            } else if (tipo == teHTML) {
                sTexto = DiretorioBO::diretorioToHTML(diretorio);
            } else if (tipo == teXML) {
                sTexto = DiretorioBO::diretorioToXML(diretorio);
            } else if (tipo == teSQL) {
                sTexto = DiretorioBO::diretorioToSQL(diretorio, TRUE) + _T(";");
            }

			listaLocal.AddTail(sTexto);
        }
    }

    if (tipo == teHTML) {
        sTexto += sCR + _T("</table>") + sCR;
        sTexto += _T("</body>") + sCR;
        sTexto += _T("</html>") + sCR;
    } else if (tipo == teXML) {
        sTexto = _T("</diretorio>");
    }
	listaLocal.AddTail(sTexto);

    Rotinas::SListSaveToFile(listaLocal, sNomeArquivo);

	listaDiretorio->RemoveAll();
	delete listaDiretorio;
}

BOOL DiretorioBO::criarTabelaDiretorios() {
    return DiretorioDAO::getInstancia()->criarTabela();
}

int DiretorioBO::XMLParaDiretorio(const CString &sTexto, int nArquivo,
        DiretorioXML *diretorioXML) {
	CString sTagInicio = _T("");
	CString sValor = _T("");
	CString sTagFim = _T("");
    int resultado;

    resultado = nArquivo;

    if (Rotinas::Pos(_T(">"), sTexto) > 0) {
        sTagInicio = Rotinas::SubString(sTexto, 1, Rotinas::Pos(_T(">"), sTexto));
    }
    if ((Rotinas::Pos(_T(">"), sTexto) > 0) && (Rotinas::Pos(_T("</"), sTexto) > 1)) {
        sValor = Rotinas::SubString(sTexto, Rotinas::Pos(_T(">"), sTexto) + 1,
			Rotinas::Pos(_T("</"), sTexto) - Rotinas::Pos(_T(">"), sTexto) - 1);
    }
    if (Rotinas::LastDelimiter(_T(">"), sTexto) > 0) {
        sTagFim = Rotinas::SubString(sTexto,
			Rotinas::LastDelimiter(_T("<"), sTexto),
			Rotinas::LastDelimiter(_T(">"), sTexto));
    }

    if ((nArquivo == 1) && (sTagInicio != _T("<arquivo>"))) {
        resultado = -1;
    }
    if ((nArquivo == 2) && (sTagInicio != _T("<aba>"))
            && (sTagFim != _T("</aba>"))) {
        resultado = -1;
    }
    if ((nArquivo == 3) && (sTagInicio != _T("<nomeAba>"))
            && (sTagFim != _T("</nomeAba>"))) {
        resultado = -1;
    }
    if ((nArquivo == 4) && (sTagInicio == _T("<codigo>"))
            && (sTagFim == _T("</codigo>"))) {
        diretorioXML->getDiretorio()->setCodigo(Rotinas::ToInt(sValor));
    }
    if ((nArquivo == 5) && (sTagInicio == _T("<ordem>"))
            && (sTagFim == _T("</ordem>"))) {
        diretorioXML->getDiretorio()->setOrdem(Rotinas::ToInt(sValor));
    }
    if ((nArquivo == 6) && (sTagInicio == _T("<nome>"))
            && (sTagFim == _T("</nome>"))) {
        diretorioXML->getDiretorio()->setNome(sValor);
    }
    if ((nArquivo == 7) && (sTagInicio == _T("<tamanho>"))
            && (sTagFim == _T("</tamanho>"))) {
        diretorioXML->getDiretorio()->setTamanho(Rotinas::ToLong(sValor));
    }
    if ((nArquivo == 8) && (sTagInicio == _T("<tipo>"))
            && (sTagFim == _T("</tipo>"))) {
		const char* stipo = Rotinas::StringToChar(sValor);
        diretorioXML->getDiretorio()->getTipo().setCodigo(stipo[0]);
    }
    if ((nArquivo == 9) && (sTagInicio == _T("<modificado>"))
            && (sTagFim == _T("</modificado>"))) {
        diretorioXML->getDiretorio()->setModificado(Rotinas::StringToDate(sValor));
    }
    if ((nArquivo == 10) && (sTagInicio == _T("<atributos>"))
            && (sTagFim == _T("</atributos>"))) {
        diretorioXML->getDiretorio()->setAtributos(sValor);
    }
    if ((nArquivo == 11) && (sTagInicio == _T("<codDirPai>"))
            && (sTagFim == _T("</codDirPai>"))) {
        diretorioXML->getDiretorio()->setCodDirPai(Rotinas::ToInt(sValor));
    }
    if ((nArquivo == 12) && (sTagInicio == _T("<caminho>"))
            && (sTagFim == _T("</caminho>"))) {
        diretorioXML->getDiretorio()->setCaminho(sValor);
    }
    if ((nArquivo == 13) && (sTagInicio != _T("</arquivo>"))) {
        resultado = -1;
    }
    if (sTagInicio == _T("</diretorio>")) {
        resultado = -3;
    }

    return resultado;
}

int DiretorioBO::importarDiretorioViaXML(Aba aba, const CString &sNomeArquivo,
        const CList<Diretorio, Diretorio&> &listaDirPai,
        IProgressoLog progressoLog) {
    CString sTexto, sTexto1;
    int nArquivo, resultado;
	POSITION pos;
    CStringList* listalocal = new CStringList();
    DiretorioXML diretorioXML;
    CList<Diretorio, Diretorio&>* listaDiretorio = new CList<Diretorio, Diretorio&>();

    resultado = 0;
    listalocal = Rotinas::SListLoadFromFile(sNomeArquivo);
	CString item0 = listalocal->GetHead();

    if (listalocal!=NULL && item0 != _T("<diretorio>")) {
        resultado = -1;
    } else {
        nArquivo = 0;
		diretorioXML.setDiretorio(new Diretorio());

		for (int i = 0; i < listalocal->GetSize(); ++i) {
			pos = listalocal->FindIndex(i);
			sTexto1 = listalocal->GetAt(pos);

            sTexto = Rotinas::Trim(sTexto1);
            nArquivo = DiretorioBO::XMLParaDiretorio(sTexto, nArquivo, &diretorioXML);

            if (nArquivo == -1) {
                resultado = -1;
                break;
            } else if (nArquivo == 13) {
                nArquivo = 1;
                diretorioXML.getDiretorio()->setAba(aba);
				listaDiretorio->AddTail(*(diretorioXML.getDiretorio()));

                if (DiretorioBO::verificaCodDir(aba.getCodigo(),
                        diretorioXML.getDiretorio()->getCaminho(),
                        listaDirPai)) {
                    resultado = -2;
                    break;
                }

				diretorioXML.setDiretorio(new Diretorio());
            } else if (nArquivo == -3) {
                resultado = nArquivo;
            } else {
                nArquivo++;
            }
        }
    }

	DiretorioBO::salvarDiretorio(*listaDiretorio, progressoLog);
	listaDiretorio->RemoveAll();
	listalocal->RemoveAll();

	delete listaDiretorio;
	delete listalocal;

    return resultado;
}

BOOL DiretorioBO::carregarSubDiretorios(const CString &sDiretorio,
	CStringList &listaLocal) {
    CString sCaminho, sSeparador, arquivo;
	CFileFind finder;
	BOOL bAchou;
	int ntamlista;

    if (Rotinas::SubString(sDiretorio, sDiretorio.GetLength(), 1) ==
            Rotinas::BARRA_NORMAL) {
        sSeparador = _T("");
    } else {
		sSeparador = Rotinas::BARRA_NORMAL;
    }

    sCaminho = sDiretorio + sSeparador + _T("*.*");

	bAchou = finder.FindFile(sCaminho);
	while (bAchou) {
		bAchou = finder.FindNextFile();

		if (finder.IsDots()) {
			continue;
		}

		sCaminho = finder.GetFilePath();

		if (Rotinas::DirectoryExists(sCaminho)) {
			listaLocal.AddTail(sCaminho);
		}
	}
	finder.Close();

	ntamlista = listaLocal.GetSize();

    return (ntamlista > 0);
}

BOOL DiretorioBO::carregarArquivos(const CString &sDiretorio,
        CStringList &listaLocal) {
    CString sCaminho, sSeparador, arquivo;
	CFileFind finder;
	BOOL bAchou;
	int ntamlista;

    if (Rotinas::SubString(sDiretorio, sDiretorio.GetLength(), 1) ==
		Rotinas::BARRA_NORMAL) {
        sSeparador = _T("");
    } else {
		sSeparador = Rotinas::BARRA_NORMAL;
    }

	sCaminho = sDiretorio + sSeparador + _T("*.*");

	bAchou = finder.FindFile(sCaminho);
	while (bAchou) {
		bAchou = finder.FindNextFile();

		if (finder.IsDots()) {
			continue;
		}

		sCaminho = finder.GetFilePath();

		if (Rotinas::FileExists(sCaminho)) {
			listaLocal.AddTail(sCaminho);
		}		
	}
	finder.Close();

	ntamlista = listaLocal.GetSize();

	return (ntamlista > 0);
}

BOOL DiretorioBO::carregarTodosArquivos(const CString &sDiretorio,
        CStringList &listaLocal) {
	CString sCaminho, sSeparador, arquivo;
	CFileFind finder;
	BOOL bAchou;
	int ntamlista;

	if (Rotinas::SubString(sDiretorio, sDiretorio.GetLength(), 1) ==
		Rotinas::BARRA_NORMAL) {
		sSeparador = _T("");
	}
	else {
		sSeparador = Rotinas::BARRA_NORMAL;
	}

	sCaminho = sDiretorio + sSeparador;
	arquivo = Rotinas::ExtractFilePath(sCaminho);

	if (Rotinas::DirectoryExists(sCaminho)) {
		sCaminho = sDiretorio + sSeparador + arquivo;

		if (Rotinas::FileExists(sCaminho)) {
			listaLocal.AddTail(sCaminho);
		}
		else if (Rotinas::DirectoryExists(sCaminho)) {
			if (arquivo != _T(".") && arquivo != _T("..")) {
				carregarTodosArquivos(sCaminho, listaLocal);
			}
		}

		sCaminho = sDiretorio + sSeparador + _T("*.*");

		bAchou = finder.FindFile(sCaminho);
		while (bAchou) {
			bAchou = finder.FindNextFile();

			if (finder.IsDots()) {
				continue;
			}

			sCaminho = finder.GetFilePath();

			if (Rotinas::FileExists(sCaminho)) {
				listaLocal.AddTail(sCaminho);
			}
			else if (Rotinas::DirectoryExists(sCaminho)) {
				if (arquivo != _T(".") && arquivo != _T("..")) {
					carregarTodosArquivos(sCaminho, listaLocal);
				}
			}

		}
		finder.Close();
	}

	ntamlista = listaLocal.GetSize();

	return (ntamlista > 0);
}

CList<Diretorio, Diretorio&>* DiretorioBO::itensFilhos(const CList<Diretorio, Diretorio&> &lista_pai,
        int aba, int codDirPai, int codigo) {
	CList<Diretorio, Diretorio&>* lista = new CList<Diretorio, Diretorio&>();
	POSITION pos;
    Diretorio diretorio;

	for (int i = 0; i < lista_pai.GetSize(); ++i) {
		pos = lista_pai.FindIndex(i);
		diretorio = lista_pai.GetAt(pos);

        if (diretorio.getAba().getCodigo() == aba) {
            if (diretorio.getCodDirPai() == codDirPai) {
                if (diretorio.getCodigo() == codigo) {
					lista->AddTail(diretorio);
                }
            }
        }
    }
    return lista;
}

}
}
