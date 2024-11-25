#include "DiretorioBO.h"

#include <wx/dir.h>

#include "hfsguardadir/objetosdao/DiretorioDAO.h"
#include "hfsguardadir/objetosbo/AbaBO.h"

using namespace hfsguardadir::objetosdao;
using namespace hfsguardadir::objetosbo;

namespace hfsguardadir {

namespace objetosbo {

const wxString DiretorioBO::SQL_CONSULTA_ARQUIVO = "select aba, cod, " \
            "ordem, coddirpai, nome, tam, tipo, modificado, atributos, " \
            "caminho, nomeaba, nomepai, caminhopai from consultaarquivo";

DiretorioBO* DiretorioBO::instancia = NULL;

DiretorioBO::DiretorioBO()
{

}

DiretorioBO::DiretorioBO(DiretorioBO const&){

}

DiretorioBO& DiretorioBO::operator=(DiretorioBO const&){
    return *instancia;
}

DiretorioBO* DiretorioBO::getInstancia() {
    if (!instancia) {
        instancia = new DiretorioBO();
    }
    return instancia;
}

wxVector<Diretorio> DiretorioBO::carregarDiretorio(
        const wxString &sSQL, IProgressoLog progressoLog) {
    return DiretorioDAO::getInstancia()->consultarTudo(
                sSQL, wxString(""), progressoLog);
}

wxVector<Diretorio> DiretorioBO::carregarDiretorio(const wxString &sSQL,
    const wxString &sCondicaoTotal, IProgressoLog progressoLog) {

    return DiretorioDAO::getInstancia()->consultarTudo(
                sSQL, sCondicaoTotal, progressoLog);
}

wxString DiretorioBO::removerDrive(wxString &sDiretorio) {
	wxFileName info(sDiretorio);
	wxString drive = info.GetVolume();
    int i = 0;
    bool bAchou = false;
    wxString sArq = Rotinas::testaNull(sDiretorio);

    if (sArq.length() > 0) {
        if (sArq.Upper().Contains(drive.Upper())) {
                bAchou = true;
        }
    }
    sArq = Rotinas::trocaSeparador(sArq);
    if (bAchou) {
        return sArq.Mid(drive.length()+2);
    } else {
        return sArq;
    }
}

wxString DiretorioBO::arquivoAtributos(wxFileName &info) {
    wxString sAtributos = "";

    if (!info.IsDirWritable() && !info.IsFileWritable()) {
        sAtributos += "[ROL]";
    }
	/*
    if (info.isHidden()) {
        sAtributos += "[HID]";
    }
	*/
    if (info.IsDir()) {
        sAtributos += "[DIR]";
    }
    if (!info.IsDir()) {
        sAtributos += "[ARQ]";
    }

    return sAtributos;
}

int DiretorioBO::retCodDirPai(int nAba, wxString &sDiretorio,
                              wxVector<Diretorio> listaLocal) {
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
        wxString &sNomeDirRaiz, wxString &sDiretorio, bool bDiretorio,
        wxVector<Diretorio> listaLocal, Arquivo arquivo,
        DiretorioOrdem *dirOrdem) {
    int nOrdem = dirOrdem->getOrdem();
    Diretorio diretorio;
    wxString sCaminho, sDir;
    wxFileName fCaminho;
	wxLongLong tamanho;
	wxDateTime dtAcesso, dtModificacao, dtCriacao;

    Aba abaLocal;
    Tipo tipoLocal;

    sCaminho = removerDrive(sDiretorio);
    if (sDiretorio.length() > 0){
		fCaminho.Assign(sDiretorio);
    }

    if ((sCaminho.length() > 0) && (sNomeDirRaiz.length() > 0)) {
        if (Rotinas::StartsStr(sNomeDirRaiz, sCaminho)) {
            sCaminho = Rotinas::SubString(sCaminho, sNomeDirRaiz.length()+2,
                        sCaminho.length());
            sDir = Rotinas::SubString(sDiretorio, sNomeDirRaiz.length()+2,
                            sDiretorio.length());
            fCaminho.Assign(sDir);
        } else {
            sCaminho = sNomeDirRaiz + Rotinas::BARRA_INVERTIDA + sCaminho;
            sDir = sNomeDirRaiz + Rotinas::BARRA_INVERTIDA + sDiretorio;
            fCaminho.Assign(sDir);
        }
    }

    abaLocal.setCodigo(nAba);
    diretorio.setCodigo(nCodDirRaiz);
    diretorio.setOrdem(nOrdem);
    diretorio.setNome(arquivo.getNome());
    diretorio.setTamanho(arquivo.getTamanho());
	diretorio.setModificado(arquivo.getModificado());    
    diretorio.setAtributos(arquivoAtributos(fCaminho));

    if (sDiretorio.IsEmpty()) {
        diretorio.setCaminho(arquivo.getNome());
        diretorio.setCaminhoPai(wxString(""));
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
            diretorio.setCodDirPai(retCodDirPai(abaLocal.getCodigo(),
                    diretorio.getCaminhoPai(), listaLocal));
        }
    } else {
        tipoLocal.setCodigo('A');
        diretorio.setCodDirPai(retCodDirPai(abaLocal.getCodigo(),
                diretorio.getCaminhoPai(), listaLocal));
    }    
    abaLocal.setNome(wxString(""));
    diretorio.setAba(abaLocal);
    diretorio.setNomePai(wxString(""));
	tamanho = diretorio.getTamanho();
    diretorio.setTamanhoFormatado(Rotinas::MontaTamanho(tamanho.GetValue()));
    if (tipoLocal.getCodigo() == 'D') {
		tipoLocal.setNome(wxString("Diretório"));
    } else {
		tipoLocal.setNome(wxString("Arquivo"));
    }
	diretorio.setTipo(tipoLocal);
    diretorio.setModificadoFormatado(Rotinas::formataDate(
            Rotinas::FORMATO_DATAHORA, diretorio.getModificado()));
    diretorio.setCaminhoOriginal(sDiretorio);

    nOrdem++;

    dirOrdem->setOrdem(nOrdem);

    return diretorio;
}

Arquivo DiretorioBO::wxFileNameToArquivo(wxFileName &info) {
    Arquivo arquivo;
	//wxDateTime dtAcesso, dtModificacao, dtCriacao;

    arquivo.setNome(info.GetName());
    arquivo.setTamanho(info.GetSize());	

	/*
	if (wxDir::Exists(info.GetFullPath())) {
		info.GetTimes(&dtAcesso, &dtModificacao, &dtCriacao);
		if (dtCriacao.IsValid()) {
			arquivo.setModificado(dtCriacao);
		}
	} 
	else {
		arquivo.setModificado(info.GetModificationTime());
	}
	*/

	if (wxDir::Exists(info.GetFullPath())) {
		arquivo.setModificado(wxDateTime::Now());
	}
	else {
		if (info.GetModificationTime().IsValid()) {
			arquivo.setModificado(info.GetModificationTime());
		}
		else {
			arquivo.setModificado(wxDateTime::Now());
		}

	}
	

    arquivo.setAtributos(arquivoAtributos(info));
    return arquivo;
}

void DiretorioBO::atribuiListaDiretorio(int nAba, int nCodDirRaiz,
        wxString &sNomeDirRaiz, wxString &sDiretorio, wxVector<Diretorio> *listaLocal,
        wxFileName &info, DiretorioOrdem *dirOrdem, IProgressoLog progressoLog) {
    Diretorio diretorio;
    Progresso pb;

    if (Rotinas::FileExists(sDiretorio)) {
		diretorio = atribuiDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz,
                sDiretorio, false, *listaLocal, wxFileNameToArquivo(info),
                dirOrdem);
        listaLocal->push_back(diretorio);

        if (progressoLog != NULL) {
            pb.log = sDiretorio;
            progressoLog(pb);
        }
    } else if (Rotinas::DirectoryExists(sDiretorio)) {
        if ((info.GetName() != ".") && (info.GetName() != "..")) {
            diretorio = atribuiDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz,
                    sDiretorio, true, *listaLocal, wxFileNameToArquivo(info),
                    dirOrdem);
            listaLocal->push_back(diretorio);

            if (progressoLog != NULL) {
                pb.log = sDiretorio;
                progressoLog(pb);
            }

            ImportarDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz, sDiretorio,
                    listaLocal, dirOrdem, progressoLog);
        }
    }

}

void DiretorioBO::ImportarDiretorio(int nAba, int nCodDirRaiz,
        wxString &sNomeDirRaiz, wxString &sDiretorio, wxVector<Diretorio> *listaLocal,
        DiretorioOrdem *dirOrdem, IProgressoLog progressoLog) {
	wxFileName info;
    wxString sCaminho, sSeparador, arquivo;
	
    if (Rotinas::SubString(sDiretorio,
            sDiretorio.length(), 1) == wxFileName::GetPathSeparator()) {
        sSeparador = "";
    } else {
		sSeparador = wxFileName::GetPathSeparator();
    }

    sCaminho = sDiretorio + sSeparador;

	wxDir dir(sCaminho);   
	if (dir.GetFirst(&arquivo, wxEmptyString, wxDIR_DEFAULT | wxDIR_NO_FOLLOW)) {
		sCaminho = dir.GetNameWithSep() + arquivo;
		//sCaminho = sDiretorio + sSeparador + arquivo;
		info.Assign(sCaminho);
		atribuiListaDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz,
			sCaminho, listaLocal, info, dirOrdem,
			progressoLog);

		while (dir.GetNext(&arquivo)) {
			sCaminho = dir.GetNameWithSep() + arquivo;			
			//sCaminho = sDiretorio + sSeparador + arquivo;
			info.Assign(sCaminho);
			atribuiListaDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz,
				sCaminho, listaLocal, info, dirOrdem,
				progressoLog);			
        }
    }

	dir.Close();
}

bool DiretorioBO::verificaCodDir(int nAba, wxString &sDiretorio,
        wxVector<Diretorio> listaLocal) {
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

int DiretorioBO::retMaxCodDir(int nAba, wxVector<Diretorio> listaLocal) {
    int nMaior = -1;
    Diretorio diretorio;

	for (unsigned int i = 0; i < listaLocal.size(); i++)	{
		diretorio = listaLocal[i];
        
        if (diretorio.getAba().getCodigo() == nAba) {
            if (diretorio.getCodigo() > nMaior) {
                nMaior = diretorio.getCodigo();
            }
        }
    }
    return nMaior + 1;
}

wxString DiretorioBO::diretorioToSQL(Diretorio diretorio, bool bInsert) {
    wxString sSQL = "";

    if (bInsert) {
        sSQL = "insert into Diretorios(aba, cod, ordem, coddirpai, nome, " \
               "tam, tipo, modificado, atributos, caminho) values(";
    }

    sSQL += diretorio.getAba().getCodigo() + ",";
    sSQL += diretorio.getCodigo() + ",";
    sSQL += diretorio.getOrdem() + ",";
    sSQL += diretorio.getCodDirPai() + ",";
    sSQL += Rotinas::QuotedStr(diretorio.getNome()) + ",";
    sSQL += diretorio.getTamanho().ToString() + ",";
    sSQL += Rotinas::QuotedStr(diretorio.getTipo().getCodigo()) + ",";
    sSQL += Rotinas::QuotedStr(diretorio.getModificadoFormatado()) + ",";
    sSQL += Rotinas::QuotedStr(diretorio.getAtributos()) + ",";
    sSQL += Rotinas::QuotedStr(diretorio.getCaminho());

    if (bInsert) {
        sSQL += ")";
    }

    return sSQL;
}

void DiretorioBO::salvarDiretorio(wxVector<Diretorio> listaDiretorio,
        IProgressoLog progressoLog) {
    Diretorio diretorio;
    Progresso pb;
    pb.minimo = 0;
    pb.maximo = listaDiretorio.size() - 1;
    pb.posicao = 0;
    pb.passo = 1;

    for (unsigned int i = 0; i < listaDiretorio.size(); i++) {
        diretorio = listaDiretorio.at(i);

        DiretorioDAO::getInstancia()->incluir(diretorio);
        pb.log = wxString::Format("%d",i + 1) + wxString(" - Salvando Diret\u00f3rio: ")
                + diretorio.getCaminho();
		
        pb.posicao = i;

        if (progressoLog != NULL) {
            progressoLog(pb);
        }
    }
}

bool DiretorioBO::excluirDiretorio(Aba aba, const wxString &sCaminho) {
   return DiretorioDAO::getInstancia()->excluir(aba, sCaminho);
}

void DiretorioBO::excluirListaDiretorio(wxVector<Diretorio> listaDiretorio,
        Aba aba, const wxString &sCaminho) {
    Diretorio diretorio;

    for (int i = listaDiretorio.size() - 1; i >= 0; i--) {
        diretorio = listaDiretorio.at(i);

        if (diretorio.getAba().getCodigo() == aba.getCodigo()) {
            if (Rotinas::Trim(sCaminho).length() > 0) {
                if (Rotinas::StartsStr(sCaminho, diretorio.getCaminho())) {
                    listaDiretorio.erase(&listaDiretorio[i]);
                }
            } else {
				listaDiretorio.erase(&listaDiretorio[i]);
            }
        }
    }

}

wxString DiretorioBO::diretorioToCSV(Diretorio diretorio) {
    wxString sCSV;

    sCSV = "\"";

    sCSV += diretorio.getAba().getNome() + "\";\"";
    sCSV += diretorio.getNome() + "\";\"";
    sCSV += diretorio.getTamanho().ToString() + "\";\"";
    sCSV += diretorio.getTamanhoFormatado() + "\";\"";
    sCSV += diretorio.getTipo().getNome() + "\";\"";
    sCSV += diretorio.getModificadoFormatado() + "\";\"";
    sCSV += diretorio.getAtributos() + "\";\"";
    sCSV += diretorio.getCaminho() + "\"";

    return sCSV;
}

wxString DiretorioBO::diretorioToXML(Diretorio diretorio) {
    wxString sXML, sCR, sTAB, sTAB2;

    sTAB = "\t";
    sTAB2 = "\t\t";
    sCR = "\n";

    sXML = sTAB + "<arquivo>" + sCR;

    sXML += sTAB2 + "<aba>" << diretorio.getAba().getCodigo()
            + "</aba>" + sCR;
    sXML += sTAB2 + "<nomeAba>" + diretorio.getAba().getNome()
            + "</nomeAba>" + sCR;
    sXML += sTAB2 + "<codigo>" << diretorio.getCodigo()
            + "</codigo>" + sCR;
    sXML += sTAB2 + "<ordem>" << diretorio.getOrdem()
            + "</ordem>" + sCR;
    sXML += sTAB2 + "<nome>" + diretorio.getNome() + "</nome>" + sCR;
    sXML += sTAB2 + "<tamanho>" + diretorio.getTamanho().ToString()
            + "</tamanho>" + sCR;
    sXML += sTAB2 + "<tipo>" + diretorio.getTipo().getCodigo()
            + "</tipo>" + sCR;
    sXML += sTAB2 + "<modificado>" + diretorio.getModificadoFormatado()
            + "</modificado>" + sCR;
    sXML += sTAB2 + "<atributos>" + diretorio.getAtributos()
            + "</atributos>" + sCR;
    sXML += sTAB2 + "<codDirPai>" << diretorio.getCodDirPai()
            + "</codDirPai>" + sCR;
    sXML += sTAB2 + "<caminho>" + diretorio.getCaminho()
            + "</caminho>" + sCR;

    sXML += sTAB + "</arquivo>";

    return sXML;
}

wxString DiretorioBO::diretorioToTXT(Diretorio diretorio) {
    wxString sTXT, sTAB;

    sTAB = "\t";
    sTXT = "";
    sTXT += diretorio.getAba().getNome() + sTAB;
    sTXT += diretorio.getNome() + sTAB;
    sTXT += diretorio.getTamanho().ToString() + sTAB;
    sTXT += diretorio.getTamanhoFormatado() + sTAB;
    sTXT += diretorio.getTipo().getNome() + sTAB;
    sTXT += diretorio.getModificadoFormatado() + sTAB;
    sTXT += diretorio.getAtributos() + sTAB;
    sTXT += diretorio.getCaminho();

    return sTXT;
}

wxString DiretorioBO::diretorioToHTML(Diretorio diretorio) {
    wxString sHTML, sCR, sTAB, sTAB2;

    sTAB = "\t";
    sTAB2 = "\t\t";
    sCR = "\n";

    sHTML = sTAB + "<tr>" + sCR;

    sHTML += sTAB2 + "<td>" + diretorio.getAba().getNome() + "</td>" + sCR;
    sHTML += sTAB2 + "<td>" + diretorio.getNome() + "</td>" + sCR;
    sHTML += sTAB2 + "<td>" + diretorio.getTamanho().ToString() + "</td>" + sCR;
    sHTML += sTAB2 + "<td>" + Rotinas::StringReplaceAll(
            diretorio.getTamanhoFormatado(), wxString(" "), wxString("&nbsp;")) + "</td>" + sCR;
    sHTML += sTAB2 + "<td>" + diretorio.getTipo().getNome() + "</td>" + sCR;
    sHTML += sTAB2 + "<td>"
            + Rotinas::StringReplaceAll(diretorio.getModificadoFormatado(),
                    wxString(" "), wxString("&nbsp;")) + "</td>" + sCR;
    sHTML += sTAB2 + "<td>" + diretorio.getAtributos() + "</td>" + sCR;
    sHTML += sTAB2 + "<td>" + diretorio.getCaminho() + "</td>" + sCR;

    sHTML += sTAB + "</tr>";
    return sHTML;
}

void DiretorioBO::exportarDiretorio(TipoExportar tipo, Aba aba,
        wxString &sNomeArquivo, IProgressoLog progressoLog) {
    wxString sTexto = "", sCR, sTAB, sTAB2, sSQL, sCondicaoTotal;
    Aba abaLocal;
    Diretorio diretorio;
    wxArrayString listaLocal;
    wxVector<Diretorio> listaDiretorio;

    sTAB = "\t";
    sTAB2 = "\t\t";
    sCR = "\n";

    sCondicaoTotal = " where aba=" + aba.getCodigo();
    sSQL = SQL_CONSULTA_ARQUIVO + sCondicaoTotal + " order by 1, 2, 3";
    listaDiretorio = carregarDiretorio(sSQL, sCondicaoTotal, progressoLog);

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
    listaLocal.Add(sTexto);

    for (unsigned int i = 0; i < listaDiretorio.size(); i++) {
        diretorio = listaDiretorio.at(i);

        if (diretorio.getAba().getCodigo() == aba.getCodigo()) {
            if (tipo == teTXT) {
                sTexto = diretorioToTXT(diretorio);
            } else if (tipo == teCSV) {
                sTexto = diretorioToCSV(diretorio);
            } else if (tipo == teHTML) {
                sTexto = diretorioToHTML(diretorio);
            } else if (tipo == teXML) {
                sTexto = diretorioToXML(diretorio);
            } else if (tipo == teSQL) {
                sTexto = diretorioToSQL(diretorio, true) + ";";
            }

            listaLocal.Add(sTexto);
        }
    }

    if (tipo == teHTML) {
        sTexto += sCR + "</table>" + sCR;
        sTexto += "</body>" + sCR;
        sTexto += "</html>" + sCR;
    } else if (tipo == teXML) {
        sTexto = "</diretorio>";
    }
    listaLocal.Add(sTexto);

    Rotinas::SListSaveToFile(listaLocal, sNomeArquivo);

    listaDiretorio.clear();

}

bool DiretorioBO::criarTabelaDiretorios() {
    return DiretorioDAO::getInstancia()->criarTabela();
}

int DiretorioBO::XMLParaDiretorio(wxString sTexto, int nArquivo,
        DiretorioXML *diretorioXML) {
    wxString sTagInicio = "", sValor = "", sTagFim = "";
    int resultado;

    resultado = nArquivo;

    if (Rotinas::Pos('>', sTexto) > 0) {
        sTagInicio = Rotinas::SubString(sTexto, 1, Rotinas::Pos('>', sTexto));
    }
    if ((Rotinas::Pos('>', sTexto) > 0) && (Rotinas::Pos(wxString("</"), sTexto) > 1)) {
        sValor = Rotinas::SubString(sTexto, Rotinas::Pos('>', sTexto) + 1,
                Rotinas::Pos(wxString("</"), sTexto) - Rotinas::Pos('>', sTexto) - 1);
    }
    if (Rotinas::LastDelimiter('>', sTexto) > 0) {
        sTagFim = Rotinas::SubString(sTexto,
                Rotinas::LastDelimiter('<', sTexto),
                Rotinas::LastDelimiter('>', sTexto));
    }

    if ((nArquivo == 1) && (sTagInicio != "<arquivo>")) {
        resultado = -1;
    }
    if ((nArquivo == 2) && (sTagInicio != "<aba>")
            && (sTagFim != "</aba>")) {
        // diretorio.aba.codigo = StrToInt(sValor);
        resultado = -1;
    }
    if ((nArquivo == 3) && (sTagInicio != "<nomeAba>")
            && (sTagFim != "</nomeAba>")) {
        // diretorio.aba.nome = sValor;
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
        diretorioXML->getDiretorio()->setTamanho(Rotinas::StrToLong(sValor));
    }
    if ((nArquivo == 8) && (sTagInicio == "<tipo>")
            && (sTagFim == "</tipo>")) {
        diretorioXML->getDiretorio()->getTipo().setCodigo(sValor.at(0));
    }
    if ((nArquivo == 9) && (sTagInicio == "<modificado>")
            && (sTagFim == "</modificado>")) {
        diretorioXML->getDiretorio()->setModificado(
                Rotinas::StringToDate(sValor));
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

int DiretorioBO::importarDiretorioViaXML(Aba aba, wxString &sNomeArquivo,
        wxVector<Diretorio> listaDirPai,
        IProgressoLog progressoLog) {
    wxString sTexto, sTexto1;
    int nArquivo, resultado;
    wxArrayString listaLocal;
    DiretorioXML diretorioXML;
    wxVector<Diretorio> listaDiretorio;

    resultado = 0;
    listaLocal = Rotinas::SListLoadFromFile(sNomeArquivo);

    if (!listaLocal.IsEmpty() && listaLocal[0] != "<diretorio>") {
        resultado = -1;
    } else {
        nArquivo = 0;

        for (unsigned int i = 0; i < listaLocal.size(); i++) {
            sTexto1 = listaLocal[i];
            sTexto =  Rotinas::Trim(sTexto1);
            nArquivo = XMLParaDiretorio(sTexto, nArquivo, &diretorioXML);

            if (nArquivo == -1) {
                resultado = -1;
                break;
            } else if (nArquivo == 13) {
                nArquivo = 1;
                diretorioXML.getDiretorio()->setAba(aba);
                listaDiretorio.push_back(*diretorioXML.getDiretorio());

                if (verificaCodDir(aba.getCodigo(),
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

    salvarDiretorio(listaDiretorio, progressoLog);
    listaDiretorio.clear();

    return resultado;
}

bool DiretorioBO::carregarSubDiretorios(const wxString &sDiretorio,
	wxArrayString listaLocal) {
    wxString sCaminho, sSeparador, arquivo;

    if (Rotinas::SubString(sDiretorio, sDiretorio.length(), 1)
            == wxFileName::GetPathSeparator()) {
        sSeparador = "";
    } else {
        sSeparador = wxFileName::GetPathSeparator();
    }

    sCaminho = sDiretorio + sSeparador;
		
	wxDir dir(sCaminho);
	if (wxDir::Exists(sCaminho)) {
		if (dir.GetFirst(&arquivo, wxEmptyString, wxDIR_DEFAULT | wxDIR_NO_FOLLOW)) {
			sCaminho = dir.GetNameWithSep() + arquivo;
			//sCaminho = sDiretorio + sSeparador + arquivo;
			if (Rotinas::DirectoryExists(sCaminho)) {
				listaLocal.Add(sCaminho);
			}

			while (dir.GetNext(&arquivo)) {
				sCaminho = dir.GetNameWithSep() + arquivo;
				//sCaminho = sDiretorio + sSeparador + arquivo;
				if (Rotinas::DirectoryExists(sCaminho)) {
					listaLocal.Add(sCaminho);
				}
			}
        }
		dir.Close();
    }

    return (listaLocal.size() > 0);
}

bool DiretorioBO::carregarArquivos(const wxString &sDiretorio,
        wxArrayString listaLocal) {
    wxString sCaminho, sSeparador, arquivo;

    if (Rotinas::SubString(sDiretorio, sDiretorio.length(), 1)
		== wxFileName::GetPathSeparator()) {
        sSeparador = "";
    } else {
        sSeparador = wxFileName::GetPathSeparator();
    }

    sCaminho = sDiretorio + sSeparador;

	wxDir dir(sCaminho);
	if (wxDir::Exists(sCaminho)) {
		if (dir.GetFirst(&arquivo, wxEmptyString, wxDIR_DEFAULT | wxDIR_NO_FOLLOW)) {
			sCaminho = dir.GetNameWithSep() + arquivo;
			//sCaminho = sDiretorio + sSeparador + arquivo;
			if (Rotinas::FileExists(sCaminho)) {
				listaLocal.Add(sCaminho);
			}

			while (dir.GetNext(&arquivo)) {
				sCaminho = dir.GetNameWithSep() + arquivo;
				//sCaminho = sDiretorio + sSeparador + arquivo;
				if (Rotinas::FileExists(sCaminho)) {
					listaLocal.Add(sCaminho);
				}
			}
		}
		dir.Close();
	}

    return (listaLocal.size() > 0);
}

bool DiretorioBO::carregarTodosArquivos(const wxString &sDiretorio,
        wxArrayString listaLocal) {
	wxString sCaminho, sSeparador, arquivo;

    if (Rotinas::SubString(sDiretorio, sDiretorio.length(), 1)
            == wxFileName::GetPathSeparator()) {
        sSeparador = "";
    } else {
        sSeparador = wxFileName::GetPathSeparator();
    }

    sCaminho = sDiretorio + sSeparador;

	wxDir dir(sCaminho);
	if (wxDir::Exists(sCaminho)) {
		sCaminho = dir.GetNameWithSep() + arquivo;
		//sCaminho = sDiretorio + sSeparador + arquivo;

        if (Rotinas::FileExists(sCaminho)) {
            listaLocal.Add(sCaminho);
        } else if (Rotinas::DirectoryExists(sCaminho)) {
            if (arquivo != "." && arquivo != "..") {
                carregarTodosArquivos(sCaminho, listaLocal);
            }
        }

		if (dir.GetFirst(&arquivo, wxEmptyString, wxDIR_DEFAULT | wxDIR_NO_FOLLOW)) {
			sCaminho = dir.GetNameWithSep() + arquivo;
			//sCaminho = sDiretorio + sSeparador + arquivo;
			if (Rotinas::FileExists(sCaminho)) {
				listaLocal.Add(sCaminho);
			} else if (Rotinas::DirectoryExists(sCaminho)) {
				//if (arquivo != "." && arquivo != "..") {
					carregarTodosArquivos(sCaminho, listaLocal);
				//}
			}

			while (dir.GetNext(&arquivo)) {
				sCaminho = dir.GetNameWithSep() + arquivo;
				//sCaminho = sDiretorio + sSeparador + arquivo;
				if (Rotinas::FileExists(sCaminho)) {
					listaLocal.Add(sCaminho);
				}
				else if (Rotinas::DirectoryExists(sCaminho)) {
					//if (arquivo != "." && arquivo != "..") {
					carregarTodosArquivos(sCaminho, listaLocal);
					//}
				}
			}
		}
		dir.Close();
    }

    return (listaLocal.size() > 0);
}

wxVector<Diretorio> DiretorioBO::itensFilhos(wxVector<Diretorio> lista_pai,
        int aba, int codDirPai, int codigo) {
    wxVector<Diretorio> lista;
    Diretorio diretorio;

    for (unsigned int i = 0; i < lista_pai.size(); i++) {
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
