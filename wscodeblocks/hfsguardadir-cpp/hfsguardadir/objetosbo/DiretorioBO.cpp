#include "DiretorioBO.h"
//#include "resource.h"
#include "../objetosdao/DiretorioDAO.h"
#include "../objetosbo/AbaBO.h"

using namespace hfsguardadir::objetosdao;
using namespace hfsguardadir::objetosbo;

namespace hfsguardadir {

namespace objetosbo {

const std::string DiretorioBO::SQL_CONSULTA_ARQUIVO = "select aba, cod, " \
            "ordem, coddirpai, nome, tam, tipo, modificado, atributos, " \
            "caminho, nomeaba, nomepai, caminhopai from consultaarquivo";

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

std::vector<Diretorio> DiretorioBO::carregarDiretorio(
        const std::string &sSQL, IProgressoLog progressoLog) {
    return DiretorioDAO::getInstancia()->consultarTudo(sSQL, "", progressoLog);
}

std::vector<Diretorio> DiretorioBO::carregarDiretorio(const std::string &sSQL,
	const std::string &sCondicaoTotal, IProgressoLog progressoLog) {

    return DiretorioDAO::getInstancia()->consultarTudo(
                sSQL, sCondicaoTotal, progressoLog);
}


std::string DiretorioBO::removerDrive(const std::string &sDiretorio) {
	std::string sArq = sDiretorio;
	std::string drive = ":";
	bool bAchou = false;

    if (sArq.length() > 0) {
        if (Rotinas::ContainsStr(Rotinas::UpperCase(sArq),
			Rotinas::UpperCase(drive))) {
                bAchou = true;
        }
    }
    sArq = Rotinas::trocaSeparador(sArq);
    if (bAchou) {
        sArq = Rotinas::SubString(sArq, drive.length()+3, sArq.length());
    }
	return sArq;
}

int DiretorioBO::retCodDirPai(int nAba, const std::string &sDiretorio,
                              const std::vector<Diretorio> &listaLocal) {
    Diretorio diretorio;

	for (unsigned int i = 0; i < listaLocal.size(); ++i) {
		diretorio = listaLocal.at(i);

        if (diretorio.getAba().getCodigo() == nAba) {
            if (diretorio.getCaminho() == sDiretorio) {
                return diretorio.getOrdem();
            }
        }
    }
    return 0;
}

Diretorio DiretorioBO::atribuiDiretorio(int nAba, int nCodDirRaiz,
        const std::string &sNomeDirRaiz, const std::string &sDiretorio, bool bDiretorio,
        const std::vector<Diretorio>  &listaLocal, Arquivo arquivo,
        DiretorioOrdem *dirOrdem) {
    int nOrdem = dirOrdem->getOrdem();
    Diretorio diretorio;
    std::string sCaminho, sDir;
	long long tamanho;

    Aba abaLocal;
    Tipo tipoLocal;

    sCaminho = removerDrive(sDiretorio);

    if ((sCaminho.length() > 0) && (sNomeDirRaiz.length() > 0)) {
        if (Rotinas::StartsStr(sCaminho, sNomeDirRaiz)) {
            sCaminho = Rotinas::SubString(sCaminho, sNomeDirRaiz.length()+2,
                        sCaminho.length());
            sDir = Rotinas::SubString(sDiretorio, sNomeDirRaiz.length()+2,
                            sDiretorio.length());
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

    if (sDiretorio.length()==0) {
        diretorio.setCaminho(arquivo.getNome());
		diretorio.setCaminhoPai("");
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
    abaLocal.setNome("");
    diretorio.setAba(abaLocal);
    diretorio.setNomePai("");
	tamanho = diretorio.getTamanho();
    diretorio.setTamanhoFormatado(Rotinas::MontaTamanho(tamanho));
    if (tipoLocal.getCodigo() == 'D') {
		tipoLocal.setNome(Rotinas::getRecurso("TipoLista.diretorio"));
    } else {
		tipoLocal.setNome(Rotinas::getRecurso("TipoLista.arquivo"));
    }
	diretorio.setTipo(tipoLocal);
    diretorio.setModificadoFormatado(diretorio.getModificado().FormatDateTime(
            Rotinas::FORMATO_DATAHORA));
    diretorio.setCaminhoOriginal(sDiretorio);

    nOrdem++;

    dirOrdem->setOrdem(nOrdem);

    return diretorio;
}

void DiretorioBO::atribuiListaDiretorio(int nAba, int nCodDirRaiz,
        const std::string &sNomeDirRaiz, const std::string &sDiretorio,
		std::vector<Diretorio> *listaLocal,
        Arquivo info, DiretorioOrdem *dirOrdem, IProgressoLog progressoLog) {
    Diretorio diretorio;
    Progresso pb;
	pb.log = "";

    if (Rotinas::FileExists(sDiretorio)) {
		diretorio = DiretorioBO::atribuiDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz,
                sDiretorio, false, *listaLocal, info,
                dirOrdem);
		listaLocal->push_back(diretorio);

        if (progressoLog != NULL) {
            pb.log = sDiretorio;
            progressoLog(pb);
        }
    } else if (Rotinas::DirectoryExists(sDiretorio)) {
        if (info.getNome()!="." && info.getNome()!="..") {
            diretorio = DiretorioBO::atribuiDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz,
                    sDiretorio, true, *listaLocal, info,
                    dirOrdem);
			listaLocal->push_back(diretorio);

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
        const std::string &sNomeDirRaiz, const std::string &sDiretorio,
		std::vector<Diretorio> *listaLocal,
        DiretorioOrdem *dirOrdem, IProgressoLog progressoLog) {
	Arquivo info;
    std::string sCaminho, sSeparador, arquivo = "";

    if (Rotinas::SubString(sDiretorio, sDiretorio.length(), 1) == Rotinas::BARRA_NORMAL) {
        sSeparador = "";
    } else {
		sSeparador = Rotinas::BARRA_NORMAL;
    }

	std::vector<std::string> listaDir = Rotinas::cListarArquivosDiretorios(sDiretorio);
	for (unsigned int i = 0; i < listaDir.size(); i++)
	{
		sCaminho = listaDir.at(i);
		info = Rotinas::FileInfoToArquivo(sCaminho);
		atribuiListaDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz,
			sCaminho, listaLocal, info, dirOrdem, progressoLog);
	}

}

bool DiretorioBO::verificaCodDir(int nAba, const std::string &sDiretorio,
        const std::vector<Diretorio>  &listaLocal) {

	Diretorio diretorio;

    if (sDiretorio.length() > 0) {
		for (unsigned int i = 0; i < listaLocal.size(); ++i) {
			diretorio = listaLocal.at(i);

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

int DiretorioBO::retMaxCodDir(int nAba, const std::vector<Diretorio>  &listaLocal) {
    int nMaior = -1;
    Diretorio diretorio;

	for (unsigned int i = 0; i < listaLocal.size(); ++i) {
		diretorio = listaLocal.at(i);

		if (diretorio.getAba().getCodigo() == nAba) {
            if (diretorio.getCodigo() > nMaior) {
                nMaior = diretorio.getCodigo();
            }
        }
    }
    return nMaior + 1;
}

std::string DiretorioBO::diretorioToSQL(Diretorio diretorio, bool bInsert) {
    std::string sSQL = "";
	std::string stipo;

    if (bInsert) {
        sSQL = "insert into Diretorios(aba, cod, ordem, coddirpai, nome, " \
               "tam, tipo, modificado, atributos, caminho) values(";
    }

    sSQL += diretorio.getAba().getCodigo() + ",";
	sSQL += diretorio.getCodigo() + ",";
	sSQL += diretorio.getOrdem() + ",";
	sSQL += diretorio.getCodDirPai() + ",";
    sSQL += Rotinas::QuotedStr(diretorio.getNome()) + ",";
	sSQL += diretorio.getTamanho() + ",";
	stipo = diretorio.getTipo().getCodigo();
    sSQL += Rotinas::QuotedStr(stipo) + ",";
    sSQL += Rotinas::QuotedStr(diretorio.getModificadoFormatado()) + ",";
    sSQL += Rotinas::QuotedStr(diretorio.getAtributos()) + ",";
    sSQL += Rotinas::QuotedStr(diretorio.getCaminho()) + ",";

    if (bInsert) {
        sSQL += ")";
    }

    return sSQL;
}

void DiretorioBO::salvarDiretorio(const std::vector<Diretorio>  &listaDiretorio,
        IProgressoLog progressoLog) {

    Diretorio diretorio;
    Progresso pb;
    pb.minimo = 0;
    pb.maximo = listaDiretorio.size() - 1;
    pb.posicao = 0;
    pb.passo = 1;
	pb.log = "";
	std::string sdir = Rotinas::getRecurso("TipoLista.diretorio");

	for (unsigned int i = 0; i < listaDiretorio.size(); ++i) {
		diretorio = listaDiretorio.at(i);

        DiretorioDAO::getInstancia()->incluir(diretorio);
        pb.log = Rotinas::IntToStr(i + 1) + " - Salvando " + sdir + ": " + diretorio.getCaminho();

        pb.posicao = i;

        if (progressoLog != NULL) {
            progressoLog(pb);
        }
    }
}

bool DiretorioBO::excluirDiretorio(Aba aba, const std::string &sCaminho) {
   return DiretorioDAO::getInstancia()->excluir(aba, sCaminho);
}

void DiretorioBO::excluirListaDiretorio(std::vector<Diretorio> listaDiretorio,
        Aba aba, const std::string &sCaminho) {
	std::string scaminho = sCaminho;

    Diretorio diretorio;

	for (unsigned int i = 0; i < listaDiretorio.size(); ++i) {
		diretorio = listaDiretorio.at(i);

        if (diretorio.getAba().getCodigo() == aba.getCodigo()) {
            if (Rotinas::Trim(scaminho).length() > 0) {
                if (Rotinas::StartsStr(diretorio.getCaminho(), scaminho)) {
					listaDiretorio.erase(listaDiretorio.begin() + i);
                }
            } else {
				listaDiretorio.erase(listaDiretorio.begin() + i);
            }
        }


    }

}

std::string DiretorioBO::diretorioToCSV(Diretorio diretorio) {
    std::string sCSV = "\"";

    sCSV += diretorio.getAba().getNome() + "\";\"";
    sCSV += diretorio.getNome() + "\";\"";
    sCSV += diretorio.getTamanho() + "\";\"";
    sCSV += diretorio.getTamanhoFormatado() + "\";\"";
    sCSV += diretorio.getTipo().getNome() + "\";\"";
    sCSV += diretorio.getModificadoFormatado() + "\";\"";
    sCSV += diretorio.getAtributos() + "\";\"";
    sCSV += diretorio.getCaminho() + "\"";

    return sCSV;
}

std::string DiretorioBO::diretorioToXML(Diretorio diretorio) {
    std::string sXML, sCR, sTAB, sTAB2;

    sTAB = "\t";
    sTAB2 = "\t\t";
    sCR = "\n";

    sXML = sTAB + "<arquivo>" + sCR;

    sXML += sTAB2 + "<aba>" + Rotinas::IntToStr(diretorio.getAba().getCodigo()) +
            "</aba>" + sCR;
    sXML += sTAB2 + "<nomeAba>" + diretorio.getAba().getNome() +
            "</nomeAba>" + sCR;
    sXML += sTAB2 + "<codigo>" + Rotinas::IntToStr(diretorio.getCodigo()) +
		"</codigo>" + sCR;
    sXML += sTAB2 + "<ordem>" + Rotinas::IntToStr(diretorio.getOrdem()) +
		"</ordem>" + sCR;
    sXML += sTAB2 + "<nome>" + diretorio.getNome() + "</nome>" + sCR;
    sXML += sTAB2 + "<tamanho>" + Rotinas::LongLongToStr(diretorio.getTamanho()) +
		"</tamanho>" + sCR;
    sXML += sTAB2 + "<tipo>" + diretorio.getTipo().getCodigo() +
		"</tipo>" + sCR;
    sXML += sTAB2 + "<modificado>" + diretorio.getModificadoFormatado() +
		"</modificado>" + sCR;
    sXML += sTAB2 + "<atributos>" + diretorio.getAtributos() +
		"</atributos>" + sCR;
    sXML += sTAB2 + "<codDirPai>" + Rotinas::IntToStr(diretorio.getCodDirPai()) +
		"</codDirPai>" + sCR;
    sXML += sTAB2 + "<caminho>" + diretorio.getCaminho() +
		"</caminho>" + sCR;

    sXML += sTAB + "</arquivo>";

    return sXML;
}

std::string DiretorioBO::diretorioToTXT(Diretorio diretorio) {
    std::string sTXT, sTAB;

    sTAB = "\t";
    sTXT = "";
    sTXT += diretorio.getAba().getNome() + sTAB;
    sTXT += diretorio.getNome() + sTAB;
    sTXT += Rotinas::LongLongToStr(diretorio.getTamanho()) + sTAB;
    sTXT += diretorio.getTamanhoFormatado() + sTAB;
    sTXT += diretorio.getTipo().getNome() + sTAB;
    sTXT += diretorio.getModificadoFormatado() + sTAB;
    sTXT += diretorio.getAtributos() + sTAB;
    sTXT += diretorio.getCaminho();

    return sTXT;
}

std::string DiretorioBO::diretorioToHTML(Diretorio diretorio) {
    std::string sHTML, sCR, sTAB, sTAB2;

    sTAB = "\t";
    sTAB2 = "\t\t";
    sCR = "\n";

    sHTML = sTAB + "<tr>" + sCR;

    sHTML += sTAB2 + "<td>" + diretorio.getAba().getNome() + "</td>" + sCR;
    sHTML += sTAB2 + "<td>" + diretorio.getNome() + "</td>" + sCR;
    sHTML += sTAB2 + "<td>" + Rotinas::LongLongToStr(diretorio.getTamanho()) + "</td>" + sCR;
    sHTML += sTAB2 + "<td>" + Rotinas::ReplaceAll(
            diretorio.getTamanhoFormatado(), " ", "&nbsp;") + "</td>" + sCR;
    sHTML += sTAB2 + "<td>" + diretorio.getTipo().getNome() + "</td>" + sCR;
    sHTML += sTAB2 + "<td>" + Rotinas::ReplaceAll(
		diretorio.getModificadoFormatado(), " ", "&nbsp;") + "</td>" + sCR;
    sHTML += sTAB2 + "<td>" + diretorio.getAtributos() + "</td>" + sCR;
    sHTML += sTAB2 + "<td>" + diretorio.getCaminho() + "</td>" + sCR;

    sHTML += sTAB + "</tr>";
    return sHTML;
}

void DiretorioBO::exportarDiretorio(TipoExportar tipo, Aba aba,
        const std::string &sNomeArquivo, IProgressoLog progressoLog) {
    std::string sTexto = "", sCR, sTAB, sTAB2, sSQL, sCondicaoTotal;
    Aba abaLocal;

    Diretorio diretorio;
    std::vector<std::string> listaLocal;
    std::vector<Diretorio> listaDiretorio;

    sTAB = "\t";
    sTAB2 = "\t\t";
    sCR = "\n";

    sCondicaoTotal = " where aba=" + Rotinas::IntToStr(aba.getCodigo());
    sSQL = DiretorioBO::SQL_CONSULTA_ARQUIVO + sCondicaoTotal + " order by 1, 2, 3";
    listaDiretorio = DiretorioBO::carregarDiretorio(sSQL, sCondicaoTotal, progressoLog);

    switch (tipo) {
        case teCSV: {
            sTexto = "\"Aba\";\"Nome\";\"TamanhoBytes\";\"Tamanho\";" \
                     "\"Tipo\";\"Modificado\";\"Atributos\";\"Caminho\"";
        }
        break;
        case teHTML: {
            sTexto = "<!DOCTYPE html>" + sCR;
            sTexto += "<html>" + sCR;
            sTexto += "<body>" + sCR;
            sTexto += "<table border=\"1\" cellpadding=\"5\" cellspacing=\"0\">"
                    + sCR;
            sTexto += sTAB + "<tr>" + sCR;
            sTexto += sTAB2 + "<th>Aba</th>" + sCR;
            sTexto += sTAB2 + "<th>Nome</th>" + sCR;
            sTexto += sTAB2 + "<th>Tamanho</th>" + sCR;
            sTexto += sTAB2 + "<th>Tamanho Formatado</th>" + sCR;
            sTexto += sTAB2 + "<th>Tipo</th>" + sCR;
            sTexto += sTAB2 + "<th>Modificado</th>" + sCR;
            sTexto += sTAB2 + "<th>Atributos</th>" + sCR;
            sTexto += sTAB2 + "<th>Caminho</th>" + sCR;
            sTexto += sTAB + "</tr>";
        }
        break;
        case teXML: {
            sTexto = "<diretorio>";
        }
        break;
        case teSQL: {
			diretorio = listaDiretorio.at(0);
            abaLocal.setCodigo(diretorio.getAba().getCodigo());
            abaLocal.setNome(diretorio.getAba().getNome());
            sTexto = AbaBO::getInstancia()->abaToSQL(abaLocal);
        }
        break;
        case teTXT: {
        }
    }
	listaLocal.push_back(sTexto);

	for (unsigned int i = 0; i < listaDiretorio.size(); ++i) {
		diretorio = listaDiretorio.at(i);

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
                sTexto = DiretorioBO::diretorioToSQL(diretorio, true) + ";";
            }

			listaLocal.push_back(sTexto);
        }
    }

    if (tipo == teHTML) {
        sTexto += sCR + "</table>" + sCR;
        sTexto += "</body>" + sCR;
        sTexto += "</html>" + sCR;
    } else if (tipo == teXML) {
        sTexto = "</diretorio>";
    }
	listaLocal.push_back(sTexto);

    Rotinas::SListSaveToFile(listaLocal, sNomeArquivo);

	listaDiretorio.clear();
}

bool DiretorioBO::criarTabelaDiretorios() {
    return DiretorioDAO::getInstancia()->criarTabela();
}

int DiretorioBO::XMLParaDiretorio(const std::string &sTexto, int nArquivo,
        DiretorioXML *diretorioXML) {
	std::string sTagInicio = "";
	std::string sValor = "";
	std::string sTagFim = "";
    int resultado;

    resultado = nArquivo;

    if (Rotinas::Pos(">", sTexto) > 0) {
        sTagInicio = Rotinas::SubString(sTexto, 1, Rotinas::Pos(">", sTexto));
    }
    if ((Rotinas::Pos(">", sTexto) > 0) && (Rotinas::Pos("</", sTexto) > 1)) {
        sValor = Rotinas::SubString(sTexto, Rotinas::Pos(">", sTexto) + 1,
			Rotinas::Pos("</", sTexto) - Rotinas::Pos(">", sTexto) - 1);
    }
    if (Rotinas::LastDelimiter(">", sTexto) > 0) {
        sTagFim = Rotinas::SubString(sTexto,
			Rotinas::LastDelimiter("<", sTexto),
			Rotinas::LastDelimiter(">", sTexto));
    }

    if ((nArquivo == 1) && (sTagInicio != "<arquivo>")) {
        resultado = -1;
    }
    if ((nArquivo == 2) && (sTagInicio != "<aba>")
            && (sTagFim != "</aba>")) {
        resultado = -1;
    }
    if ((nArquivo == 3) && (sTagInicio != "<nomeAba>")
            && (sTagFim != "</nomeAba>")) {
        resultado = -1;
    }
    if ((nArquivo == 4) && (sTagInicio == "<codigo>")
            && (sTagFim == "</codigo>")) {
        diretorioXML->getDiretorio()->setCodigo(Rotinas::StrToInt(sValor));
    }
    if ((nArquivo == 5) && (sTagInicio == "<ordem>")
            && (sTagFim == "</ordem>")) {
        diretorioXML->getDiretorio()->setOrdem(Rotinas::StrToInt(sValor));
    }
    if ((nArquivo == 6) && (sTagInicio == "<nome>")
            && (sTagFim == "</nome>")) {
        diretorioXML->getDiretorio()->setNome(sValor);
    }
    if ((nArquivo == 7) && (sTagInicio == "<tamanho>")
            && (sTagFim == "</tamanho>")) {
        diretorioXML->getDiretorio()->setTamanho(Rotinas::StrToULongLong(sValor));
    }
    if ((nArquivo == 8) && (sTagInicio == "<tipo>")
            && (sTagFim == "</tipo>")) {
		const char* stipo = sValor.c_str();
        diretorioXML->getDiretorio()->getTipo().setCodigo(stipo[0]);
    }
    if ((nArquivo == 9) && (sTagInicio == "<modificado>")
            && (sTagFim == "</modificado>")) {
        diretorioXML->getDiretorio()->setModificado(DateTime::StrToDateTime(sValor));
    }
    if ((nArquivo == 10) && (sTagInicio == "<atributos>")
            && (sTagFim == "</atributos>")) {
        diretorioXML->getDiretorio()->setAtributos(sValor);
    }
    if ((nArquivo == 11) && (sTagInicio == "<codDirPai>")
            && (sTagFim == "</codDirPai>")) {
        diretorioXML->getDiretorio()->setCodDirPai(Rotinas::StrToInt(sValor));
    }
    if ((nArquivo == 12) && (sTagInicio == "<caminho>")
            && (sTagFim == "</caminho>")) {
        diretorioXML->getDiretorio()->setCaminho(sValor);
    }
    if ((nArquivo == 13) && (sTagInicio != "</arquivo>")) {
        resultado = -1;
    }
    if (sTagInicio == "</diretorio>") {
        resultado = -3;
    }

    return resultado;
}

int DiretorioBO::importarDiretorioViaXML(Aba aba, const std::string &sNomeArquivo,
        const std::vector<Diretorio>  &listaDirPai,
        IProgressoLog progressoLog) {
    std::string sTexto, sTexto1;
    int nArquivo, resultado;

    std::vector<std::string> listalocal;
    DiretorioXML diretorioXML;
    std::vector<Diretorio> listaDiretorio;

    resultado = 0;
    listalocal = Rotinas::SListLoadFromFile(sNomeArquivo);
	std::string item0 = listalocal.at(0);

    if (!listalocal.empty() && item0 != "<diretorio>") {
        resultado = -1;
    } else {
        nArquivo = 0;
		diretorioXML.setDiretorio(new Diretorio());

		for (unsigned int i = 0; i < listalocal.size(); ++i) {
			sTexto1 = listalocal.at(i);

            sTexto = Rotinas::Trim(sTexto1);
            nArquivo = DiretorioBO::XMLParaDiretorio(sTexto, nArquivo, &diretorioXML);

            if (nArquivo == -1) {
                resultado = -1;
                break;
            } else if (nArquivo == 13) {
                nArquivo = 1;
                diretorioXML.getDiretorio()->setAba(aba);
				listaDiretorio.push_back(*(diretorioXML.getDiretorio()));

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

	DiretorioBO::salvarDiretorio(listaDiretorio, progressoLog);
	listaDiretorio.clear();
	listalocal.clear();

    return resultado;
}

bool DiretorioBO::carregarSubDiretorios(const std::string &sDiretorio,
	std::vector<std::string> &listaLocal) {
    std::string sCaminho, sSeparador, arquivo;

    if (Rotinas::SubString(sDiretorio, sDiretorio.length(), 1) ==
            Rotinas::BARRA_NORMAL) {
        sSeparador = "";
    } else {
		sSeparador = Rotinas::BARRA_NORMAL;
    }

	std::vector<std::string> listaDir = Rotinas::cListarArquivosDiretorios(sDiretorio);
	for (unsigned int i = 0; i < listaDir.size(); i++)
	{
		sCaminho = listaDir.at(i);

		if (Rotinas::DirectoryExists(sCaminho)) {
			listaLocal.push_back(sCaminho);
		}
	}

	return (listaLocal.size() > 0);
}

bool DiretorioBO::carregarArquivos(const std::string &sDiretorio,
        std::vector<std::string> &listaLocal) {
    std::string sCaminho, sSeparador, arquivo;

    if (Rotinas::SubString(sDiretorio, sDiretorio.length(), 1) ==
		Rotinas::BARRA_NORMAL) {
        sSeparador = "";
    } else {
		sSeparador = Rotinas::BARRA_NORMAL;
    }

	std::vector<std::string> listaDir = Rotinas::cListarArquivosDiretorios(sDiretorio);
	for (unsigned int i = 0; i < listaDir.size(); i++)
	{
		sCaminho = listaDir.at(i);

		if (Rotinas::FileExists(sCaminho)) {
			listaLocal.push_back(sCaminho);
		}
	}

	return (listaLocal.size() > 0);
}

bool DiretorioBO::carregarTodosArquivos(const std::string &sDiretorio,
        std::vector<std::string> &listaLocal) {
	std::string sCaminho, sSeparador, arquivo;
	std::string ponto = ".";
	std::string pponto = "..";

	if (Rotinas::SubString(sDiretorio, sDiretorio.length(), 1) ==
		Rotinas::BARRA_NORMAL) {
		sSeparador = "";
	}
	else {
		sSeparador = Rotinas::BARRA_NORMAL;
	}

	sCaminho = sDiretorio + sSeparador;
	arquivo = Rotinas::ExtractFilePath(sCaminho);

	if (Rotinas::DirectoryExists(sCaminho)) {
		sCaminho = sDiretorio + sSeparador + arquivo;

		if (Rotinas::FileExists(sCaminho)) {
			listaLocal.push_back(sCaminho);
		}
		else if (Rotinas::DirectoryExists(sCaminho)) {
			if (arquivo!=ponto && arquivo!=pponto) {
				DiretorioBO::carregarTodosArquivos(sCaminho, listaLocal);
			}
		}

		std::vector<std::string> listaDir = Rotinas::cListarArquivosDiretorios(sDiretorio);
		for (unsigned int i = 0; i < listaDir.size(); i++)
		{
			sCaminho = listaDir.at(i);

			if (Rotinas::FileExists(sCaminho)) {
				listaLocal.push_back(sCaminho);
			}
			else if (Rotinas::DirectoryExists(sCaminho)) {
				if (arquivo != ponto && arquivo != pponto) {
					DiretorioBO::carregarTodosArquivos(sCaminho, listaLocal);
				}
			}
		}
	}

	return (listaLocal.size() > 0);

}

std::vector<Diretorio> DiretorioBO::itensFilhos(const std::vector<Diretorio> &lista_pai,
        int aba, int codDirPai, int codigo) {
	std::vector<Diretorio> lista;
    Diretorio diretorio;

	for (unsigned int i = 0; i < lista_pai.size(); ++i) {
		diretorio = lista_pai.at(i);

        if (diretorio.getAba().getCodigo() == aba) {
            if (diretorio.getCodDirPai() == codDirPai) {
                if (diretorio.getCodigo() == codigo) {
					lista.push_back(diretorio);
                }
            }
        }
    }
    return lista;
}

}
}
