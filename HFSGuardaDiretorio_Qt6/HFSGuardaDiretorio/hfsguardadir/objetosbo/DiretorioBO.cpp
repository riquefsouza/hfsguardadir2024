#include "DiretorioBO.h"

#include "hfsguardadir/objetosdao/DiretorioDAO.h"
#include "hfsguardadir/objetosbo/AbaBO.h"

using namespace hfsguardadir::objetosdao;
using namespace hfsguardadir::objetosbo;

namespace hfsguardadir {

namespace objetosbo {

const QString DiretorioBO::SQL_CONSULTA_ARQUIVO = "select aba, cod, " \
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

QList<Diretorio> DiretorioBO::carregarDiretorio(
        const QString &sSQL, IProgressoLog progressoLog) {
    return DiretorioDAO::getInstancia()->consultarTudo(
                sSQL, QString(""), progressoLog);
}

QList<Diretorio> DiretorioBO::carregarDiretorio(const QString &sSQL,
    const QString &sCondicaoTotal, IProgressoLog progressoLog) {

    return DiretorioDAO::getInstancia()->consultarTudo(
                sSQL, sCondicaoTotal, progressoLog);
}

QString DiretorioBO::removerDrive(QString &sDiretorio) {
    QList<QStorageInfo> drives = QStorageInfo::mountedVolumes();
    int i = 0;
    bool bAchou = false;
    QString sArq = Rotinas::testaNull(sDiretorio);

    if (sArq.length() > 0) {
        for (i = 0; i < drives.length(); i++) {
            if (sArq.toUpper().contains(
                    drives.at(i).rootPath().toUpper())) {
                bAchou = true;
                break;
            }
        }
    }
    sArq = Rotinas::trocaSeparador(sArq);
    if (bAchou) {
        return sArq.mid(drives.at(i).rootPath().length());
    } else {
        return sArq;
    }
}

QString DiretorioBO::arquivoAtributos(QFileInfo &info) {
    QString sAtributos = "";

    if (!info.isWritable()) {
        sAtributos += "[ROL]";
    }
    if (info.isHidden()) {
        sAtributos += "[HID]";
    }
    if (info.isDir()) {
        sAtributos += "[DIR]";
    }
    if (info.isFile()) {
        sAtributos += "[ARQ]";
    }

    return sAtributos;
}

int DiretorioBO::retCodDirPai(int nAba, QString &sDiretorio,
                              QList<Diretorio> listaLocal) {
    Diretorio diretorio;

    for (int i = 0; i < listaLocal.size(); ++i) {
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
        QString sNomeDirRaiz, QString sDiretorio, bool bDiretorio,
        QList<Diretorio> listaLocal, Arquivo arquivo,
        DiretorioOrdem *dirOrdem) {
    int nOrdem = dirOrdem->getOrdem();
    Diretorio diretorio;
    QString sCaminho, sDir;
    QFileInfo fCaminho;

    Aba abaLocal;
    Tipo tipoLocal;

    sCaminho = removerDrive(sDiretorio);
    if (sDiretorio.length() > 0){
        fCaminho.setFile(sDiretorio);
    }

    if ((sCaminho.length() > 0) && (sNomeDirRaiz.length() > 0)) {
        if (Rotinas::StartsStr(sNomeDirRaiz, sCaminho)) {
            sCaminho = Rotinas::SubString(sCaminho, sNomeDirRaiz.length()+2,
                        sCaminho.length());
            sDir = Rotinas::SubString(sDiretorio, sNomeDirRaiz.length()+2,
                            sDiretorio.length());
            fCaminho.setFile(sDir);
        } else {
            sCaminho = sNomeDirRaiz + Rotinas::BARRA_INVERTIDA + sCaminho;
            sDir = sNomeDirRaiz + Rotinas::BARRA_INVERTIDA + sDiretorio;
            fCaminho.setFile(sDir);
        }
    }

    abaLocal.setCodigo(nAba);
    diretorio.setCodigo(nCodDirRaiz);
    diretorio.setOrdem(nOrdem);
    diretorio.setNome(arquivo.getNome());
    diretorio.setTamanho(arquivo.getTamanho());
    diretorio.setModificado(arquivo.getModificado());
    diretorio.setAtributos(arquivoAtributos(fCaminho));

    if (sDiretorio.isEmpty()) {
        diretorio.setCaminho(arquivo.getNome());
        diretorio.setCaminhoPai(QString(""));
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
    abaLocal.setNome(QString(""));
    diretorio.setAba(abaLocal);
    diretorio.setNomePai(QString(""));
    diretorio.setTamanhoFormatado(Rotinas::MontaTamanho(diretorio.getTamanho()));
    if (tipoLocal.getCodigo() == 'D') {
		tipoLocal.setNome(QString("Diretório"));
    } else {
		tipoLocal.setNome(QString("Arquivo"));
    }
	diretorio.setTipo(tipoLocal);
    diretorio.setModificadoFormatado(Rotinas::formataDate(
            Rotinas::FORMATO_DATAHORA, diretorio.getModificado()));
    diretorio.setCaminhoOriginal(sDiretorio);

    nOrdem++;

    dirOrdem->setOrdem(nOrdem);

    return diretorio;
}

Arquivo DiretorioBO::QFileInfoToArquivo(QFileInfo &info) {
    Arquivo arquivo;

    arquivo.setNome(info.fileName());
    arquivo.setTamanho(info.size());
    arquivo.setModificado(info.lastModified());
    arquivo.setAtributos(arquivoAtributos(info));
    return arquivo;
}

void DiretorioBO::atribuiListaDiretorio(int nAba, int nCodDirRaiz,
        QString &sNomeDirRaiz, QString &sDiretorio, QList<Diretorio> *listaLocal,
        QFileInfo &info, DiretorioOrdem *dirOrdem, IProgressoLog progressoLog) {
    Diretorio diretorio;
    Progresso pb;

    if (Rotinas::FileExists(sDiretorio)) {
        diretorio = atribuiDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz,
                sDiretorio, false, *listaLocal, QFileInfoToArquivo(info),
                dirOrdem);
        listaLocal->append(diretorio);

        if (progressoLog != NULL) {
            pb.log = sDiretorio;
            progressoLog(pb);
        }
    } else if (Rotinas::DirectoryExists(sDiretorio)) {
        if ((info.fileName() != ".") && (info.fileName() != "..")) {
            diretorio = atribuiDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz,
                    sDiretorio, true, *listaLocal, QFileInfoToArquivo(info),
                    dirOrdem);
            listaLocal->append(diretorio);

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
        QString sNomeDirRaiz, QString sDiretorio, QList<Diretorio> *listaLocal,
        DiretorioOrdem *dirOrdem, IProgressoLog progressoLog) {
    QDir qdir;
    QString sCaminho, sSeparador;
	QFileInfoList listaInfo;

    if (Rotinas::SubString(sDiretorio,
            sDiretorio.length(), 1) == QDir::separator()) {
        sSeparador = "";
    } else {
        sSeparador = QDir::separator();
    }

    sCaminho = sDiretorio + sSeparador;

    qdir.setPath(sCaminho);
    if (qdir.exists()) {
		listaInfo = qdir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries);

        if (!listaInfo.isEmpty()) {
            QFileInfo info;
            for (int i = 0; i < listaInfo.size(); ++i) {
                info = listaInfo.at(i);

				if (info.fileName() != "." && info.fileName() != "..")
				{
					sCaminho = sDiretorio + sSeparador + info.fileName();
					atribuiListaDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz,
						sCaminho, listaLocal, info, dirOrdem,
						progressoLog);
				}
            }
        }
    }
}

bool DiretorioBO::verificaCodDir(int nAba, QString &sDiretorio,
        QList<Diretorio> listaLocal) {
    Diretorio diretorio;

    if (sDiretorio.length() > 0) {
        for (int i = 0; i < listaLocal.size(); ++i) {
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

int DiretorioBO::retMaxCodDir(int nAba, QList<Diretorio> listaLocal) {
    int nMaior = -1;
    Diretorio diretorio;

    foreach (Diretorio diretorio, listaLocal) {
        
        if (diretorio.getAba().getCodigo() == nAba) {
            if (diretorio.getCodigo() > nMaior) {
                nMaior = diretorio.getCodigo();
            }
        }
    }
    return nMaior + 1;
}

QString DiretorioBO::diretorioToSQL(Diretorio diretorio, bool bInsert) {
    QString sSQL = "";

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
    sSQL += Rotinas::QuotedStr(diretorio.getTipo().getCodigo()) + ",";
    sSQL += Rotinas::QuotedStr(diretorio.getModificadoFormatado()) + ",";
    sSQL += Rotinas::QuotedStr(diretorio.getAtributos()) + ",";
    sSQL += Rotinas::QuotedStr(diretorio.getCaminho());

    if (bInsert) {
        sSQL += ")";
    }

    return sSQL;
}

void DiretorioBO::salvarDiretorio(QList<Diretorio> listaDiretorio,
        IProgressoLog progressoLog) {
    Diretorio diretorio;
    Progresso pb;
    pb.minimo = 0;
    pb.maximo = listaDiretorio.size() - 1;
    pb.posicao = 0;
    pb.passo = 1;

    for (int i = 0; i < listaDiretorio.size(); i++) {
        diretorio = listaDiretorio.at(i);

        DiretorioDAO::getInstancia()->incluir(diretorio);
        pb.log = QString::number(i + 1) + QString(" - Salvando Diretório: ")
                + diretorio.getCaminho();

        pb.posicao = i;

        if (progressoLog != NULL) {
            progressoLog(pb);
        }
    }
}

bool DiretorioBO::excluirDiretorio(Aba aba, const QString sCaminho) {
   return DiretorioDAO::getInstancia()->excluir(aba, sCaminho);
}

void DiretorioBO::excluirListaDiretorio(QList<Diretorio> listaDiretorio,
        Aba aba, const QString sCaminho) {
    Diretorio diretorio;

    for (int i = listaDiretorio.size() - 1; i >= 0; i--) {
        diretorio = listaDiretorio.at(i);

        if (diretorio.getAba().getCodigo() == aba.getCodigo()) {
            if (sCaminho.trimmed().length() > 0) {
                if (Rotinas::StartsStr(sCaminho, diretorio.getCaminho())) {
                    listaDiretorio.removeAt(i);
                }
            } else {
                listaDiretorio.removeAt(i);
            }
        }
    }

}

QString DiretorioBO::diretorioToCSV(Diretorio diretorio) {
    QString sCSV;

    sCSV = "\"";

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

QString DiretorioBO::diretorioToXML(Diretorio diretorio) {
    QString sXML, sCR, sTAB, sTAB2;

    sTAB = "\t";
    sTAB2 = "\t\t";
    sCR = "\n";

    sXML = sTAB + "<arquivo>" + sCR;

    sXML += sTAB2 + "<aba>" + QString::number(diretorio.getAba().getCodigo())
            + "</aba>" + sCR;
    sXML += sTAB2 + "<nomeAba>" + diretorio.getAba().getNome()
            + "</nomeAba>" + sCR;
    sXML += sTAB2 + "<codigo>" + QString::number(diretorio.getCodigo())
            + "</codigo>" + sCR;
    sXML += sTAB2 + "<ordem>" + QString::number(diretorio.getOrdem())
            + "</ordem>" + sCR;
    sXML += sTAB2 + "<nome>" + diretorio.getNome() + "</nome>" + sCR;
    sXML += sTAB2 + "<tamanho>" + QString::number(diretorio.getTamanho())
            + "</tamanho>" + sCR;
    sXML += sTAB2 + "<tipo>" + diretorio.getTipo().getCodigo()
            + "</tipo>" + sCR;
    sXML += sTAB2 + "<modificado>" + diretorio.getModificadoFormatado()
            + "</modificado>" + sCR;
    sXML += sTAB2 + "<atributos>" + diretorio.getAtributos()
            + "</atributos>" + sCR;
    sXML += sTAB2 + "<codDirPai>" + QString::number(diretorio.getCodDirPai())
            + "</codDirPai>" + sCR;
    sXML += sTAB2 + "<caminho>" + diretorio.getCaminho()
            + "</caminho>" + sCR;

    sXML += sTAB + "</arquivo>";

    return sXML;
}

QString DiretorioBO::diretorioToTXT(Diretorio diretorio) {
    QString sTXT, sTAB;

    sTAB = "\t";
    sTXT = "";
    sTXT += diretorio.getAba().getNome() + sTAB;
    sTXT += diretorio.getNome() + sTAB;
    sTXT += QString::number(diretorio.getTamanho()) + sTAB;
    sTXT += diretorio.getTamanhoFormatado() + sTAB;
    sTXT += diretorio.getTipo().getNome() + sTAB;
    sTXT += diretorio.getModificadoFormatado() + sTAB;
    sTXT += diretorio.getAtributos() + sTAB;
    sTXT += diretorio.getCaminho();

    return sTXT;
}

QString DiretorioBO::diretorioToHTML(Diretorio diretorio) {
    QString sHTML, sCR, sTAB, sTAB2;

    sTAB = "\t";
    sTAB2 = "\t\t";
    sCR = "\n";

    sHTML = sTAB + "<tr>" + sCR;

    sHTML += sTAB2 + "<td>" + diretorio.getAba().getNome() + "</td>" + sCR;
    sHTML += sTAB2 + "<td>" + diretorio.getNome() + "</td>" + sCR;
    sHTML += sTAB2 + "<td>" + QString::number(diretorio.getTamanho()) + "</td>" + sCR;
    sHTML += sTAB2 + "<td>" + Rotinas::StringReplaceAll(
            diretorio.getTamanhoFormatado(), QString(" "), QString("&nbsp;")) + "</td>" + sCR;
    sHTML += sTAB2 + "<td>" + diretorio.getTipo().getNome() + "</td>" + sCR;
    sHTML += sTAB2 + "<td>"
            + Rotinas::StringReplaceAll(diretorio.getModificadoFormatado(),
                    QString(" "), QString("&nbsp;")) + "</td>" + sCR;
    sHTML += sTAB2 + "<td>" + diretorio.getAtributos() + "</td>" + sCR;
    sHTML += sTAB2 + "<td>" + diretorio.getCaminho() + "</td>" + sCR;

    sHTML += sTAB + "</tr>";
    return sHTML;
}

void DiretorioBO::exportarDiretorio(TipoExportar tipo, Aba aba,
        QString sNomeArquivo, IProgressoLog progressoLog) {
    QString sTexto = "", sCR, sTAB, sTAB2, sSQL, sCondicaoTotal;
    Aba abaLocal;
    Diretorio diretorio;
    QStringList listaLocal;
    QList<Diretorio> listaDiretorio;

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
    listaLocal.append(sTexto);

    for (int i = 0; i < listaDiretorio.size(); i++) {
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

            listaLocal.append(sTexto);
        }
    }

    if (tipo == teHTML) {
        sTexto += sCR + "</table>" + sCR;
        sTexto += "</body>" + sCR;
        sTexto += "</html>" + sCR;
    } else if (tipo == teXML) {
        sTexto = "</diretorio>";
    }
    listaLocal.append(sTexto);

    Rotinas::SListSaveToFile(listaLocal, sNomeArquivo);

    listaDiretorio.clear();

}

bool DiretorioBO::criarTabelaDiretorios() {
    return DiretorioDAO::getInstancia()->criarTabela();
}

int DiretorioBO::XMLParaDiretorio(QString sTexto, int nArquivo,
        DiretorioXML *diretorioXML) {
    QString sTagInicio = "", sValor = "", sTagFim = "";
    int resultado;

    resultado = nArquivo;

    if (Rotinas::Pos('>', sTexto) > 0) {
        sTagInicio = Rotinas::SubString(sTexto, 1, Rotinas::Pos('>', sTexto));
    }
    if ((Rotinas::Pos('>', sTexto) > 0) && (Rotinas::Pos(QString("</"), sTexto) > 1)) {
        sValor = Rotinas::SubString(sTexto, Rotinas::Pos('>', sTexto) + 1,
                Rotinas::Pos(QString("</"), sTexto) - Rotinas::Pos('>', sTexto) - 1);
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
        diretorioXML->getDiretorio()->setCodigo(sValor.toInt());
    }
    if ((nArquivo == 5) && (sTagInicio == "<ordem>")
            && (sTagFim == "</ordem>")) {
        diretorioXML->getDiretorio()->setOrdem(sValor.toInt());
    }
    if ((nArquivo == 6) && (sTagInicio == "<nome>")
            && (sTagFim == "</nome>")) {
        diretorioXML->getDiretorio()->setNome(sValor);
    }
    if ((nArquivo == 7) && (sTagInicio == "<tamanho>")
            && (sTagFim == "</tamanho>")) {
        diretorioXML->getDiretorio()->setTamanho(sValor.toLong());
    }
    if ((nArquivo == 8) && (sTagInicio == "<tipo>")
            && (sTagFim == "</tipo>")) {
        diretorioXML->getDiretorio()->getTipo().setCodigo(sValor.at(0).toLatin1());
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
        diretorioXML->getDiretorio()->setCodDirPai(sValor.toInt());
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

int DiretorioBO::importarDiretorioViaXML(Aba aba, QString sNomeArquivo,
        QList<Diretorio> listaDirPai,
        IProgressoLog progressoLog) {
    QString sTexto, sTexto1;
    int nArquivo, resultado;
    QStringList listaLocal;
    DiretorioXML diretorioXML;
    QList<Diretorio> listaDiretorio;

    resultado = 0;
    listaLocal = Rotinas::SListLoadFromFile(sNomeArquivo);

    if (listaLocal.at(0) != "<diretorio>") {
        resultado = -1;
    } else {
        nArquivo = 0;

        for (int i = 0; i < listaLocal.size(); i++) {
            sTexto1 = listaLocal.at(i);
            sTexto = sTexto1.trimmed();
            nArquivo = XMLParaDiretorio(sTexto, nArquivo, &diretorioXML);

            if (nArquivo == -1) {
                resultado = -1;
                break;
            } else if (nArquivo == 13) {
                nArquivo = 1;
                diretorioXML.getDiretorio()->setAba(aba);
                listaDiretorio.append(*diretorioXML.getDiretorio());

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

bool DiretorioBO::carregarSubDiretorios(QString sDiretorio,
        QStringList listaLocal) {
    QDir qdir;
    QString sCaminho, sSeparador;

    if (Rotinas::SubString(sDiretorio, sDiretorio.length(), 1)
            == QDir::separator()) {
        sSeparador = "";
    } else {
        sSeparador = QDir::separator();
    }

    sCaminho = sDiretorio + sSeparador;

    qdir.setPath(sCaminho);
    if (qdir.exists()) {
        if (!qdir.entryInfoList().isEmpty()) {
            QFileInfo info;
            for (int i = 0; i < qdir.entryInfoList().size(); ++i) {
                info = qdir.entryInfoList().at(i);

                sCaminho = sDiretorio + sSeparador + info.fileName();

                if (info.isDir()) {
                    if (Rotinas::DirectoryExists(sCaminho)) {
                        if (info.fileName() != "." && info.fileName() != "..") {
                            listaLocal.append(sCaminho);
                        }
                    }
                }
            }
        }
    }

    return (listaLocal.size() > 0);
}

bool DiretorioBO::carregarArquivos(QString sDiretorio,
        QStringList listaLocal) {
    QDir qdir;
    QString sCaminho, sSeparador;

    if (Rotinas::SubString(sDiretorio, sDiretorio.length(), 1)
            == QDir::separator()) {
        sSeparador = "";
    } else {
        sSeparador = QDir::separator();
    }

    sCaminho = sDiretorio + sSeparador;

    qdir.setPath(sCaminho);
    if (qdir.exists()) {
        if (!qdir.entryInfoList().isEmpty()) {
            QFileInfo info;
            for (int i = 0; i < qdir.entryInfoList().size(); ++i) {
                info = qdir.entryInfoList().at(i);

                sCaminho = sDiretorio + sSeparador + info.fileName();

                if (info.isFile()) {
                    if (Rotinas::FileExists(sCaminho)) {
                        if (info.fileName() != "." && info.fileName() != "..") {
                            listaLocal.append(sCaminho);
                        }
                    }
                }
            }
        }
    }

    return (listaLocal.size() > 0);
}

bool DiretorioBO::carregarTodosArquivos(QString sDiretorio,
        QStringList listaLocal) {
    QDir qdir;
    QString sCaminho, sSeparador;

    if (Rotinas::SubString(sDiretorio, sDiretorio.length(), 1)
            == QDir::separator()) {
        sSeparador = "";
    } else {
        sSeparador = QDir::separator();
    }

    sCaminho = sDiretorio + sSeparador;

    qdir.setPath(sCaminho);
    QFileInfo infoDir(sCaminho);
    if (qdir.exists()) {
        sCaminho = sDiretorio + sSeparador + infoDir.fileName();

        if (Rotinas::FileExists(sCaminho)) {
            listaLocal.append(sCaminho);
        } else if (Rotinas::DirectoryExists(sCaminho)) {
            if (infoDir.fileName() != "." && infoDir.fileName() != "..") {
                carregarTodosArquivos(sCaminho, listaLocal);
            }
        }

        if (!qdir.entryInfoList().isEmpty()) {
            QFileInfo info;
            for (int i = 0; i < qdir.entryInfoList().size(); ++i) {
                info = qdir.entryInfoList().at(i);

                sCaminho = sDiretorio + sSeparador + info.fileName();

                if (Rotinas::FileExists(sCaminho)) {
                    listaLocal.append(sCaminho);
                } else if (Rotinas::DirectoryExists(sCaminho)) {
                    if (info.fileName() != "." && info.fileName() != "..") {
                        carregarTodosArquivos(sCaminho, listaLocal);
                    }
                }
            }
        }
    }

    return (listaLocal.size() > 0);
}

QList<Diretorio> DiretorioBO::itensFilhos(QList<Diretorio> lista_pai,
        int aba, int codDirPai, int codigo) {
    QList<Diretorio> lista;
    Diretorio diretorio;

    for (int i = 0; i < lista_pai.size(); i++) {
        diretorio = lista_pai.at(i);

        if (diretorio.getAba().getCodigo() == aba) {
            if (diretorio.getCodDirPai() == codDirPai) {
                if (diretorio.getCodigo() == codigo) {
                    lista.append(diretorio);
                }
            }
        }
    }
    return lista;
}


}
}
