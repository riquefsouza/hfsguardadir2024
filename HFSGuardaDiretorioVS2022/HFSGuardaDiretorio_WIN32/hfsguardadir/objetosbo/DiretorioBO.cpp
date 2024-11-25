#include "stdafx.h"

#include "DiretorioBO.h"
#include "resource.h"
#include "hfsguardadir/objetosdao/DiretorioDAO.h"
#include "hfsguardadir/objetosbo/AbaBO.h"

const String DiretorioBO_SQL_CONSULTA_ARQUIVO = String_iniciar("select aba, cod, " \
            "ordem, coddirpai, nome, tam, tipo, modificado, atributos, " \
            "caminho, nomeaba, nomepai, caminhopai from consultaarquivo");

ListaDiretorio DiretorioBO_carregarDiretorio(
        String sSQL, IProgressoLog progressoLog) {
    return DiretorioDAO_consultarTudo(sSQL, String_iniciar(""), progressoLog);
}

ListaDiretorio DiretorioBO_carregarDiretorio(String sSQL,
    String sCondicaoTotal, IProgressoLog progressoLog) {

    return DiretorioDAO_consultarTudo(
                sSQL, sCondicaoTotal, progressoLog);
}


String DiretorioBO_removerDrive(String sDiretorio) {
	String sArq = sDiretorio;
	String drive = String_iniciar(':');
	BOOL bAchou = FALSE;

	/*
	WCHAR drives[512];
	drives[0] = '\0';
	if (GetLogicalDriveStrings(511, drives)) {
		drive = String_iniciar(drives[0]);
	}
	*/

    if (sArq.length > 0) {
        if (String_cContainsStr(String_UpperCase(sArq).str,
			String_UpperCase(drive).str)) {
                bAchou = TRUE;
        }
    }
    sArq = Rotinas_trocaSeparador(sArq);
    if (bAchou) {
        sArq = String_SubString(sArq, drive.length+3, sArq.length);
    }	
	return sArq;
}

int DiretorioBO_retCodDirPai(int nAba, String sDiretorio,
                              ListaDiretorio listaLocal) {
	ListaDiretorio local;
    Diretorio diretorio;

	for (local = listaLocal; local != NULL; local = local->proximo) {
		diretorio = local->diretorio;

        if (diretorio.aba.codigo == nAba) {
            if (String_comparar(diretorio.caminho, sDiretorio)) {
                return diretorio.ordem;
            }
        }
    }
    return 0;
}

Diretorio DiretorioBO_atribuiDiretorio(int nAba, int nCodDirRaiz,
        String sNomeDirRaiz, String sDiretorio, BOOL bDiretorio,
        ListaDiretorio listaLocal, Arquivo arquivo,
        DiretorioOrdem *dirOrdem) {
    int nOrdem = dirOrdem->ordem;
    Diretorio diretorio;
    String sCaminho, sDir;
	long long tamanho;

    Aba abaLocal;
    Tipo tipoLocal;

    sCaminho = DiretorioBO_removerDrive(sDiretorio);

    if ((sCaminho.length > 0) && (sNomeDirRaiz.length > 0)) {
        if (String_cStartsStr(sCaminho.str, sNomeDirRaiz.str)) {
            sCaminho = String_SubString(sCaminho, sNomeDirRaiz.length+2,
                        sCaminho.length);
            sDir = String_SubString(sDiretorio, sNomeDirRaiz.length+2,
                            sDiretorio.length);
        } else {
            sCaminho = String_concatenar(sNomeDirRaiz, Rotinas_BARRA_INVERTIDA, sCaminho);
            sDir = String_concatenar(sNomeDirRaiz, Rotinas_BARRA_INVERTIDA, sDiretorio);
        }
    }

    abaLocal.codigo = nAba;
    diretorio.codigo = nCodDirRaiz;
    diretorio.ordem = nOrdem;
    diretorio.arquivo.nome = String_copiar(arquivo.nome);
    diretorio.arquivo.tamanho = arquivo.tamanho;
	diretorio.arquivo.modificado = arquivo.modificado;	
    diretorio.arquivo.atributos = arquivo.atributos;

    if (sDiretorio.length==0) {
        diretorio.caminho = String_copiar(arquivo.nome);
		diretorio.caminhoPai = String_limpar();
    } else {
        diretorio.caminho = String_copiar(sCaminho);
        diretorio.caminhoPai = String_SubString(diretorio.caminho, 1,
                String_cLastDelimiter(Rotinas_BARRA_INVERTIDA.str,
                        diretorio.caminho.str) - 1);
    }

    if (bDiretorio) {
        tipoLocal.codigo = 'D';
        if (nOrdem == 1) {
            diretorio.codDirPai = 0;
        } else {
            diretorio.codDirPai = DiretorioBO_retCodDirPai(abaLocal.codigo,
                    diretorio.caminhoPai, listaLocal);
        }
    } else {
        tipoLocal.codigo = 'A';
        diretorio.codDirPai = DiretorioBO_retCodDirPai(abaLocal.codigo,
                diretorio.caminhoPai, listaLocal);
    }    
    abaLocal.nome = String_iniciar("");
    diretorio.aba = Aba_copiar(abaLocal);
    diretorio.nomePai = String_iniciar("");
	tamanho = diretorio.arquivo.tamanho;
    diretorio.tamanhoFormatado = Rotinas_MontaTamanho(tamanho);
    if (tipoLocal.codigo == 'D') {
		tipoLocal.nome = String_iniciar(Rotinas_lerStr(STR_TIPOLISTA_DIRETORIO));
    } else {
		tipoLocal.nome = String_iniciar(Rotinas_lerStr(STR_TIPOLISTA_ARQUIVO));
    }
	diretorio.tipo = Tipo_copiar(tipoLocal);
    diretorio.modificadoFormatado = Rotinas_formataDate(
            Rotinas_FORMATO_DATAHORA, diretorio.arquivo.modificado);
    diretorio.caminhoOriginal = String_iniciar(sDiretorio);

    nOrdem++;

    dirOrdem->ordem = nOrdem;

    return diretorio;
}

void DiretorioBO_atribuiListaDiretorio(int nAba, int nCodDirRaiz,
        String sNomeDirRaiz, String sDiretorio, ListaDiretorio *listaLocal,
        Arquivo info, DiretorioOrdem *dirOrdem, IProgressoLog progressoLog) {
    Diretorio diretorio;
    Progresso pb;
	pb.log = String_iniciar("");

    if (Rotinas_FileExists(sDiretorio)) {
		diretorio = DiretorioBO_atribuiDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz,
                sDiretorio, false, *listaLocal, info,
                dirOrdem);
		ListaDiretorio_insereFim(listaLocal, diretorio);

        if (progressoLog != NULL) {
            pb.log = String_copiar(sDiretorio);
            progressoLog(pb);
        }
    } else if (Rotinas_DirectoryExists(sDiretorio)) {
        if (!String_comparar(info.nome, ".") && !String_comparar(info.nome, "..")) {
            diretorio = DiretorioBO_atribuiDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz,
                    sDiretorio, true, *listaLocal, info,
                    dirOrdem);
			ListaDiretorio_insereFim(listaLocal, diretorio);

            if (progressoLog != NULL) {
                pb.log = String_copiar(sDiretorio);
                progressoLog(pb);
            }

			DiretorioBO_ImportarDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz, sDiretorio,
                    listaLocal, dirOrdem, progressoLog);
        }
    }

}

void DiretorioBO_ImportarDiretorio(int nAba, int nCodDirRaiz,
        String sNomeDirRaiz, String sDiretorio, ListaDiretorio *listaLocal,
        DiretorioOrdem *dirOrdem, IProgressoLog progressoLog) {
	Arquivo info;
    String sCaminho, sSeparador, arquivo = String_iniciar("");
	WIN32_FIND_DATA finder;
	HANDLE hFile;
	
    if (String_comparar(String_SubString(sDiretorio,
            sDiretorio.length, 1), Rotinas_BARRA_NORMAL)) {
        sSeparador = String_iniciar("");
    } else {
		sSeparador = String_iniciar(Rotinas_BARRA_NORMAL);
    }

    sCaminho = String_concatenar(sDiretorio, sSeparador, "*.*");

	hFile = FindFirstFile(sCaminho.wstr, &finder);
	if (hFile != INVALID_HANDLE_VALUE) {
		do {
			arquivo = String_copiar(finder.cFileName);

			if (String_comparar(arquivo, ".") ||
				String_comparar(arquivo, "..")) {
				continue;
			}

			sCaminho = String_concatenar(sDiretorio, sSeparador, arquivo);
			info = Rotinas_FileInfoToArquivo(finder);

			DiretorioBO_atribuiListaDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz,
				sCaminho, listaLocal, info, dirOrdem,
				progressoLog);
		} while (FindNextFile(hFile, &finder) != 0);
		
	}

	FindClose(hFile);
}

BOOL DiretorioBO_verificaCodDir(int nAba, String sDiretorio,
        ListaDiretorio listaLocal) {
	ListaDiretorio local;
	Diretorio diretorio;

    if (sDiretorio.length > 0) {
		for (local = listaLocal; local != NULL; local = local->proximo) {
			diretorio = local->diretorio;

            if (diretorio.aba.codigo == nAba) {
                if (diretorio.ordem == 1) {
                    if (diretorio.codDirPai == 0) {
                        if (String_comparar(diretorio.caminho, sDiretorio)) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

int DiretorioBO_retMaxCodDir(int nAba, ListaDiretorio listaLocal) {
    int nMaior = -1;
	ListaDiretorio local;
    Diretorio diretorio;

	for (local = listaLocal; local != NULL; local = local->proximo) {
		diretorio = local->diretorio;

		if (diretorio.aba.codigo == nAba) {
            if (diretorio.codigo > nMaior) {
                nMaior = diretorio.codigo;
            }
        }
    }
    return nMaior + 1;
}

String DiretorioBO_diretorioToSQL(Diretorio diretorio, BOOL bInsert) {
    String sSQL = String_iniciar("");

    if (bInsert) {
        sSQL = String_copiar("insert into Diretorios(aba, cod, ordem, coddirpai, nome, " \
               "tam, tipo, modificado, atributos, caminho) values(");
    }
	
    sSQL = String_concatenar(sSQL, String_FromInt(diretorio.aba.codigo), ",");
	sSQL = String_concatenar(sSQL, String_FromInt(diretorio.codigo), ",");
	sSQL = String_concatenar(sSQL, String_FromInt(diretorio.ordem), ",");
	sSQL = String_concatenar(sSQL, String_FromInt(diretorio.codDirPai), ",");
    sSQL = String_concatenar(sSQL, String_QuotedStr(diretorio.arquivo.nome), ",");
	sSQL = String_concatenar(sSQL, String_FromLongLong(diretorio.arquivo.tamanho), ",");
    sSQL = String_concatenar(sSQL, String_QuotedStr(diretorio.tipo.codigo), ",");
    sSQL = String_concatenar(sSQL, String_QuotedStr(diretorio.modificadoFormatado), ",");
    sSQL = String_concatenar(sSQL, String_QuotedStr(diretorio.arquivo.atributos), ",");
    sSQL = String_concatenar(sSQL, String_QuotedStr(diretorio.caminho), ",");

    if (bInsert) {
        sSQL = String_concatenar(sSQL,")");
    }

    return sSQL;
}

void DiretorioBO_salvarDiretorio(ListaDiretorio listaDiretorio,
        IProgressoLog progressoLog) {
	ListaDiretorio local;
    Diretorio diretorio;
    Progresso pb;
    pb.minimo = 0;
    pb.maximo = ListaDiretorio_conta(listaDiretorio) - 1;
    pb.posicao = 0;
    pb.passo = 1;
	pb.log = String_iniciar("");
	String sdir = String_iniciar(Rotinas_lerStr(STR_TIPOLISTA_DIRETORIO));

	int i = 0;
	for (local = listaDiretorio; local != NULL; local = local->proximo) {
		diretorio = local->diretorio;

        DiretorioDAO_incluir(diretorio);
        pb.log = String_concatenar(String_FromInt(i + 1), 4, 
			" - Salvando ", sdir.str, ": ", diretorio.caminho.str);
		
        pb.posicao = i;
		i++;

        if (progressoLog != NULL) {
            progressoLog(pb);
        }
    }
}

BOOL DiretorioBO_excluirDiretorio(Aba aba, String sCaminho) {
   return DiretorioDAO_excluir(aba, sCaminho);
}

void DiretorioBO_excluirListaDiretorio(ListaDiretorio *listaDiretorio,
        Aba aba, String sCaminho) {
	ListaDiretorio local;
    Diretorio diretorio;
	int conta = 0;

	for (local = *listaDiretorio; local != NULL; local = local->proximo) {
		diretorio = local->diretorio;

        if (diretorio.aba.codigo == aba.codigo) {
            if (String_Trim(sCaminho).length > 0) {
                if (String_cStartsStr(diretorio.caminho.str, sCaminho.str)) {
					ListaDiretorio_removeItem(listaDiretorio, diretorio, TRUE);
                }
            } else {
				ListaDiretorio_removeItem(&local, diretorio, TRUE);
            }
        }

		
    }

}

String DiretorioBO_diretorioToCSV(Diretorio diretorio) {
    String sCSV = String_iniciar("\"");

    sCSV = String_concatenar(sCSV, diretorio.aba.nome, "\";\"");
    sCSV = String_concatenar(sCSV, diretorio.arquivo.nome, "\";\"");
    sCSV = String_concatenar(sCSV, String_FromLongLong(diretorio.arquivo.tamanho), "\";\"");
    sCSV = String_concatenar(sCSV, diretorio.tamanhoFormatado, "\";\"");
    sCSV = String_concatenar(sCSV, diretorio.tipo.nome, "\";\"");
    sCSV = String_concatenar(sCSV, diretorio.modificadoFormatado, "\";\"");
    sCSV = String_concatenar(sCSV, diretorio.arquivo.atributos, "\";\"");
    sCSV = String_concatenar(sCSV, diretorio.caminho, "\"");

    return sCSV;
}

String DiretorioBO_diretorioToXML(Diretorio diretorio) {
    String sXML, sCR, sTAB, sTAB2;

    sTAB = String_iniciar("\t");
    sTAB2 = String_iniciar("\t\t");
    sCR = String_iniciar("\n");

    sXML = String_concatenar(sTAB, 2, "<arquivo>", sCR.str);

    sXML = String_concatenar(sXML, 5, sTAB2.str, "<aba>", String_FromInt(diretorio.aba.codigo).str,
            "</aba>", sCR.str);
    sXML = String_concatenar(sXML, 5, sTAB2.str, "<nomeAba>", diretorio.aba.nome.str,
            "</nomeAba>", sCR.str);
    sXML = String_concatenar(sXML, 5, sTAB2.str, "<codigo>", String_FromInt(diretorio.codigo).str,
            "</codigo>", sCR.str);
    sXML = String_concatenar(sXML, 5, sTAB2.str, "<ordem>", String_FromInt(diretorio.ordem).str,
            "</ordem>", sCR.str);
    sXML = String_concatenar(sXML, 5, sTAB2.str, "<nome>", diretorio.arquivo.nome.str, "</nome>", sCR.str);
    sXML = String_concatenar(sXML, 5, sTAB2.str, "<tamanho>", String_FromLongLong(diretorio.arquivo.tamanho),
            "</tamanho>", sCR.str);
    sXML = String_concatenar(sXML, 5, sTAB2.str, "<tipo>", diretorio.tipo.codigo,
            "</tipo>", sCR.str);
    sXML = String_concatenar(sXML, 5, sTAB2.str, "<modificado>", diretorio.modificadoFormatado.str,
            "</modificado>", sCR.str);
    sXML = String_concatenar(sXML, 5, sTAB2.str, "<atributos>", diretorio.arquivo.atributos.str,
            "</atributos>", sCR.str);
    sXML = String_concatenar(sXML, 5, sTAB2.str, "<codDirPai>", String_FromInt(diretorio.codDirPai).str,
            "</codDirPai>", sCR.str);
    sXML = String_concatenar(sXML, 5, sTAB2.str, "<caminho>", diretorio.caminho.str,
            "</caminho>", sCR.str);

    sXML = String_concatenar(sXML, sTAB, "</arquivo>");

    return sXML;
}

String DiretorioBO_diretorioToTXT(Diretorio diretorio) {
    String sTXT, sTAB;

    sTAB = String_iniciar("\t");
    sTXT = String_iniciar("");
    sTXT = String_concatenar(sTXT, diretorio.aba.nome, sTAB);
    sTXT = String_concatenar(sTXT, diretorio.arquivo.nome, sTAB);
    sTXT = String_concatenar(sTXT, String_FromLongLong(diretorio.arquivo.tamanho), sTAB);
    sTXT = String_concatenar(sTXT, diretorio.tamanhoFormatado, sTAB);
    sTXT = String_concatenar(sTXT, diretorio.tipo.nome, sTAB);
    sTXT = String_concatenar(sTXT, diretorio.modificadoFormatado, sTAB);
    sTXT = String_concatenar(sTXT, diretorio.arquivo.atributos, sTAB);
    sTXT = String_concatenar(sTXT, diretorio.caminho);

    return sTXT;
}

String DiretorioBO_diretorioToHTML(Diretorio diretorio) {
    String sHTML, sCR, sTAB, sTAB2;

    sTAB = String_iniciar("\t");
    sTAB2 = String_iniciar("\t\t");
    sCR = String_iniciar("\n");

    sHTML = String_concatenar(sTAB, 2, "<tr>", sCR.str);

    sHTML = String_concatenar(sHTML, 5, sTAB2.str, "<td>", diretorio.aba.nome.str, "</td>", sCR.str);
    sHTML = String_concatenar(sHTML, 5, sTAB2.str, "<td>", diretorio.arquivo.nome.str, "</td>", sCR.str);
    sHTML = String_concatenar(sHTML, 5, sTAB2.str, "<td>", String_FromLongLong(diretorio.arquivo.tamanho).str, "</td>", sCR.str);
    sHTML = String_concatenar(sHTML, 5, sTAB2.str, "<td>", String_ReplaceAll(
            diretorio.tamanhoFormatado, " ", "&nbsp;").str, "</td>", sCR.str);
    sHTML = String_concatenar(sHTML, 5, sTAB2.str, "<td>", diretorio.tipo.nome.str, "</td>", sCR.str);
    sHTML = String_concatenar(sHTML, 5, sTAB2.str, "<td>", String_ReplaceAll(
		diretorio.modificadoFormatado, " ", "&nbsp;").str, "</td>", sCR.str);
    sHTML = String_concatenar(sHTML, 5, sTAB2.str, "<td>", diretorio.arquivo.atributos.str, "</td>", sCR.str);
    sHTML = String_concatenar(sHTML, 5, sTAB2.str, "<td>", diretorio.caminho.str, "</td>", sCR.str);

    sHTML = String_concatenar(sHTML, sTAB, "</tr>");
    return sHTML;
}

void DiretorioBO_exportarDiretorio(TipoExportar tipo, Aba aba,
        String sNomeArquivo, IProgressoLog progressoLog) {
    String sTexto = String_iniciar(""), sCR, sTAB, sTAB2, sSQL, sCondicaoTotal;
    Aba abaLocal;
    Diretorio diretorio;
    ListaString listaLocal = ListaString_inicia();
    ListaDiretorio listaDiretorio, local;

    sTAB = String_iniciar("\t");
    sTAB2 = String_iniciar("\t\t");
    sCR = String_iniciar("\n");

    sCondicaoTotal = String_concatenar(" where aba=", String_FromInt(aba.codigo));
    sSQL = String_concatenar(DiretorioBO_SQL_CONSULTA_ARQUIVO, sCondicaoTotal, " order by 1, 2, 3");
    listaDiretorio = DiretorioBO_carregarDiretorio(sSQL, sCondicaoTotal, progressoLog);

    switch (tipo) {
        case teCSV: {
            sTexto = String_copiar("\"Aba\";\"Nome\";\"TamanhoBytes\";\"Tamanho\";" \
                     "\"Tipo\";\"Modificado\";\"Atributos\";\"Caminho\"");
        }
        break;
        case teHTML: {
            sTexto = String_concatenar("<!DOCTYPE html>", sCR);
            sTexto = String_concatenar(sTexto, 2, "<html>", sCR.str);
            sTexto = String_concatenar(sTexto, 2, "<body>", sCR.str);
            sTexto = String_concatenar(sTexto, 2, "<table border=\"1\" cellpadding=\"5\" cellspacing=\"0\">"
                   , sCR.str);
            sTexto = String_concatenar(sTexto, 3, sTAB, "<tr>", sCR.str);
            sTexto = String_concatenar(sTexto, 3, sTAB2, "<th>Aba</th>", sCR.str);
            sTexto = String_concatenar(sTexto, 3, sTAB2, "<th>Nome</th>", sCR.str);
            sTexto = String_concatenar(sTexto, 3, sTAB2, "<th>Tamanho</th>", sCR.str);
            sTexto = String_concatenar(sTexto, 3, sTAB2, "<th>Tamanho Formatado</th>", sCR.str);
            sTexto = String_concatenar(sTexto, 3, sTAB2, "<th>Tipo</th>", sCR.str);
            sTexto = String_concatenar(sTexto, 3, sTAB2, "<th>Modificado</th>", sCR.str);
            sTexto = String_concatenar(sTexto, 3, sTAB2, "<th>Atributos</th>", sCR.str);
            sTexto = String_concatenar(sTexto, 3, sTAB2, "<th>Caminho</th>", sCR.str);
            sTexto = String_concatenar(sTexto, sTAB, "</tr>");
        }
        break;
        case teXML: {
            sTexto = String_copiar("<diretorio>");
        }
        break;
        case teSQL: {
            diretorio = *(ListaDiretorio_pesquisaItemOrd(listaDiretorio, 0));
            abaLocal.codigo = diretorio.aba.codigo;
            abaLocal.nome = String_copiar(diretorio.aba.nome);
            sTexto = AbaBO_abaToSQL(abaLocal);
        }
        break;
        case teTXT: {
        }
    }
	ListaString_insereFim(&listaLocal, sTexto);

	for (local = listaDiretorio; local != NULL; local = local->proximo) {
		diretorio = local->diretorio;

        if (diretorio.aba.codigo == aba.codigo) {
            if (tipo == teTXT) {
                sTexto = DiretorioBO_diretorioToTXT(diretorio);
            } else if (tipo == teCSV) {
                sTexto = DiretorioBO_diretorioToCSV(diretorio);
            } else if (tipo == teHTML) {
                sTexto = DiretorioBO_diretorioToHTML(diretorio);
            } else if (tipo == teXML) {
                sTexto = DiretorioBO_diretorioToXML(diretorio);
            } else if (tipo == teSQL) {
                sTexto = String_concatenar(DiretorioBO_diretorioToSQL(diretorio, TRUE), ";");
            }

			ListaString_insereFim(&listaLocal, sTexto);
        }
    }

    if (tipo == teHTML) {
        sTexto = String_concatenar(sTexto, 3, sCR.str, "</table>", sCR.str);
        sTexto = String_concatenar(sTexto, 2, "</body>", sCR.str);
        sTexto = String_concatenar(sTexto, 2, "</html>", sCR.str);
    } else if (tipo == teXML) {
        sTexto = String_copiar("</diretorio>");
    }
	ListaString_insereFim(&listaLocal, sTexto);

    Rotinas_SListSaveToFile(listaLocal, sNomeArquivo);

	ListaDiretorio_removeTodos(&listaDiretorio);
	ListaDiretorio_libera(&listaDiretorio);
}

BOOL DiretorioBO_criarTabelaDiretorios() {
    return DiretorioDAO_criarTabela();
}

int DiretorioBO_XMLParaDiretorio(String sTexto, int nArquivo,
        DiretorioXML *diretorioXML) {
	String sTagInicio = String_iniciar("");
	String sValor = String_iniciar("");
	String sTagFim = String_iniciar("");
    int resultado;

    resultado = nArquivo;

    if (String_cPos(">", sTexto.str) > 0) {
        sTagInicio = String_SubString(sTexto, 1, String_cPos(">", sTexto.str));
    }
    if ((String_cPos(">", sTexto.str) > 0) && (String_cPos("</", sTexto.str) > 1)) {
        sValor = String_SubString(sTexto, String_cPos(">", sTexto.str) + 1,
			String_cPos("</", sTexto.str) - String_cPos(">", sTexto.str) - 1);
    }
    if (String_cLastDelimiter(">", sTexto.str) > 0) {
        sTagFim = String_SubString(sTexto,
			String_cLastDelimiter("<", sTexto.str),
			String_cLastDelimiter(">", sTexto.str));
    }

    if ((nArquivo == 1) && (!String_comparar(sTagInicio, "<arquivo>"))) {
        resultado = -1;
    }
    if ((nArquivo == 2) && (!String_comparar(sTagInicio, "<aba>"))
            && (!String_comparar(sTagFim, "</aba>"))) {
        // diretorio.aba.codigo = StrToInt(sValor);
        resultado = -1;
    }
    if ((nArquivo == 3) && (!String_comparar(sTagInicio, "<nomeAba>"))
            && (!String_comparar(sTagFim, "</nomeAba>"))) {
        // diretorio.aba.nome = sValor;
        resultado = -1;
    }
    if ((nArquivo == 4) && (String_comparar(sTagInicio, "<codigo>"))
            && (String_comparar(sTagFim, "</codigo>"))) {
        diretorioXML->diretorio.codigo = String_ToInt(sValor);
    }
    if ((nArquivo == 5) && (String_comparar(sTagInicio, "<ordem>"))
            && (String_comparar(sTagFim, "</ordem>"))) {
        diretorioXML->diretorio.ordem = String_ToInt(sValor);
    }
    if ((nArquivo == 6) && (String_comparar(sTagInicio, "<nome>"))
            && (String_comparar(sTagFim, "</nome>"))) {
        diretorioXML->diretorio.arquivo.nome = String_copiar(sValor);
    }
    if ((nArquivo == 7) && (String_comparar(sTagInicio, "<tamanho>"))
            && (String_comparar(sTagFim, "</tamanho>"))) {
        diretorioXML->diretorio.arquivo.tamanho = String_ToLong(sValor);
    }
    if ((nArquivo == 8) && (String_comparar(sTagInicio, "<tipo>"))
            && (String_comparar(sTagFim, "</tipo>"))) {
        diretorioXML->diretorio.tipo.codigo = sValor.str[0];
    }
    if ((nArquivo == 9) && (String_comparar(sTagInicio, "<modificado>"))
            && (String_comparar(sTagFim, "</modificado>"))) {
        diretorioXML->diretorio.arquivo.modificado = 
                Rotinas_StringToDate(sValor);
    }
    if ((nArquivo == 10) && (String_comparar(sTagInicio, "<atributos>"))
            && (String_comparar(sTagFim, "</atributos>"))) {
        diretorioXML->diretorio.arquivo.atributos = String_copiar(sValor);
    }
    if ((nArquivo == 11) && (String_comparar(sTagInicio, "<codDirPai>"))
            && (String_comparar(sTagFim, "</codDirPai>"))) {
        diretorioXML->diretorio.codDirPai = String_ToInt(sValor);
    }
    if ((nArquivo == 12) && (String_comparar(sTagInicio, "<caminho>"))
            && (String_comparar(sTagFim, "</caminho>"))) {
        diretorioXML->diretorio.caminho = String_copiar(sValor);
    }
    if ((nArquivo == 13) && (!String_comparar(sTagInicio, "</arquivo>"))) {
        resultado = -1;
    }
    if (String_comparar(sTagInicio, "</diretorio>")) {
        resultado = -3;
    }

    return resultado;
}

int DiretorioBO_importarDiretorioViaXML(Aba aba, String sNomeArquivo,
        ListaDiretorio listaDirPai,
        IProgressoLog progressoLog) {
    String sTexto, sTexto1;
    int nArquivo, resultado;
    ListaString listalocal = ListaString_inicia(), local;
    DiretorioXML diretorioXML;
    ListaDiretorio listaDiretorio = ListaDiretorio_inicia();

    resultado = 0;
    listalocal = Rotinas_SListLoadFromFile(sNomeArquivo);
	String item0 = ListaString_pesquisaItemOrd(listalocal, 0);

    if (listalocal!=NULL && !String_comparar(item0, "<diretorio>")) {
        resultado = -1;
    } else {
        nArquivo = 0;

		for (local = listalocal; local != NULL; local = local->proximo) {
			sTexto1 = local->str;
            sTexto =  String_Trim(sTexto1);
            nArquivo = DiretorioBO_XMLParaDiretorio(sTexto, nArquivo, &diretorioXML);

            if (nArquivo == -1) {
                resultado = -1;
                break;
            } else if (nArquivo == 13) {
                nArquivo = 1;
                diretorioXML.diretorio.aba = Aba_copiar(aba);
				ListaDiretorio_insereFim(&listaDiretorio, diretorioXML.diretorio);

                if (DiretorioBO_verificaCodDir(aba.codigo,
                        diretorioXML.diretorio.caminho,
                        listaDirPai)) {
                    resultado = -2;
                    break;
                }

				//diretorioXML.diretorio = Diretorio_new();
            } else if (nArquivo == -3) {
                resultado = nArquivo;
            } else {
                nArquivo++;
            }
        }
    }

	DiretorioBO_salvarDiretorio(listaDiretorio, progressoLog);

	ListaDiretorio_removeTodos(&listaDiretorio);
	ListaString_removeTodos(&listalocal);

	ListaDiretorio_libera(&listaDiretorio);
	ListaString_libera(&listalocal);

    return resultado;
}

BOOL DiretorioBO_carregarSubDiretorios(String sDiretorio,
	ListaString listaLocal) {
    String sCaminho, sSeparador, arquivo;
	WIN32_FIND_DATA finder;
	HANDLE hFile;
	int ntamlista;

    if (String_comparar(String_SubString(sDiretorio, sDiretorio.length, 1),
            Rotinas_BARRA_NORMAL)) {
        sSeparador = String_iniciar("");
    } else {
		sSeparador = String_iniciar(Rotinas_BARRA_NORMAL);
    }

    sCaminho = String_concatenar(sDiretorio, sSeparador, "*.*");
		
	hFile = FindFirstFile(sCaminho.wstr, &finder);
	if (hFile != INVALID_HANDLE_VALUE) {
		 do {
			arquivo = String_copiar(finder.cFileName);

			if (String_comparar(arquivo, ".") ||
				String_comparar(arquivo, "..")) {
				continue;
			}

			sCaminho = String_concatenar(sDiretorio, sSeparador, arquivo);

			if (Rotinas_DirectoryExists(sCaminho)) {
				ListaString_insereFim(&listaLocal, sCaminho);
			}
		} while (FindNextFile(hFile, &finder) != 0);
	}
	FindClose(hFile);    

	ntamlista = ListaString_conta(listaLocal);

    return (ntamlista > 0);
}

BOOL DiretorioBO_carregarArquivos(String sDiretorio,
        ListaString listaLocal) {
    String sCaminho, sSeparador, arquivo;
	WIN32_FIND_DATA finder;
	HANDLE hFile;
	int ntamlista;

    if (String_comparar(String_SubString(sDiretorio, sDiretorio.length, 1),
		Rotinas_BARRA_NORMAL)) {
        sSeparador = String_iniciar("");
    } else {
		sSeparador = String_iniciar(Rotinas_BARRA_NORMAL);
    }

	sCaminho = String_concatenar(sDiretorio, sSeparador, "*.*");

	hFile = FindFirstFile(sCaminho.wstr, &finder);
	if (hFile != INVALID_HANDLE_VALUE) {

		do {
			arquivo = String_copiar(finder.cFileName);

			if (String_comparar(arquivo, ".") ||
				String_comparar(arquivo, "..")) {
				continue;
			}

			sCaminho = String_concatenar(sDiretorio, sSeparador, arquivo);

			if (Rotinas_FileExists(sCaminho)) {
				ListaString_insereFim(&listaLocal, sCaminho);
			}
		} while (FindNextFile(hFile, &finder) != 0);
	}
	FindClose(hFile);

	ntamlista = ListaString_conta(listaLocal);

	return (ntamlista > 0);
}

BOOL DiretorioBO_carregarTodosArquivos(String sDiretorio,
        ListaString listaLocal) {
	String sCaminho, sSeparador, arquivo;
	WIN32_FIND_DATA finder;
	HANDLE hFile;
	int ntamlista;

	if (String_comparar(String_SubString(sDiretorio, sDiretorio.length, 1),
		Rotinas_BARRA_NORMAL)) {
		sSeparador = String_iniciar("");
	}
	else {
		sSeparador = String_iniciar(Rotinas_BARRA_NORMAL);
	}

	sCaminho = String_concatenar(sDiretorio, sSeparador);
	arquivo = Rotinas_ExtractFilePath(sCaminho);

	if (Rotinas_DirectoryExists(sCaminho)) {
		sCaminho = String_concatenar(sDiretorio, sSeparador, arquivo);

		if (Rotinas_FileExists(sCaminho)) {
			ListaString_insereFim(&listaLocal, sCaminho);
		}
		else if (Rotinas_DirectoryExists(sCaminho)) {
			if (!String_comparar(arquivo, ".") && !String_comparar(arquivo, "..")) {
				DiretorioBO_carregarTodosArquivos(sCaminho, listaLocal);
			}
		}

		sCaminho = String_concatenar(sDiretorio, sSeparador, "*.*");

		hFile = FindFirstFile(sCaminho.wstr, &finder);
		if (hFile != INVALID_HANDLE_VALUE) {

			do {
				arquivo = String_copiar(finder.cFileName);

				if (String_comparar(arquivo, ".") ||
					String_comparar(arquivo, "..")) {
					continue;
				}

				sCaminho = String_concatenar(sDiretorio, sSeparador, arquivo);

				if (Rotinas_FileExists(sCaminho)) {
					ListaString_insereFim(&listaLocal, sCaminho);
				}
				else if (Rotinas_DirectoryExists(sCaminho)) {
					if (!String_comparar(arquivo, ".") && !String_comparar(arquivo, "..")) {
						DiretorioBO_carregarTodosArquivos(sCaminho, listaLocal);
					}
				}
			} while (FindNextFile(hFile, &finder) != 0);
		}
		FindClose(hFile);
	}

	ntamlista = ListaString_conta(listaLocal);

	return (ntamlista > 0);
}

ListaDiretorio DiretorioBO_itensFilhos(ListaDiretorio lista_pai,
        int aba, int codDirPai, int codigo) {
    ListaDiretorio local, lista = ListaDiretorio_inicia();
    Diretorio diretorio;

	for (local = lista_pai; local != NULL; local = local->proximo) {
		diretorio = local->diretorio;

        if (diretorio.aba.codigo == aba) {
            if (diretorio.codDirPai == codDirPai) {
                if (diretorio.codigo == codigo) {
					ListaDiretorio_insereFim(&lista, diretorio);
                }
            }
        }
    }
    return lista;
}
