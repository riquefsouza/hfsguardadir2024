#include "DiretorioBO.h"
#include "../../resource.h"
#include "../objetosdao/DiretorioDAO.h"
#include "../objetosbo/AbaBO.h"

GString *DiretorioBO_sqlConsultaArquivo() {
	return g_string_new("select aba, cod, " \
		"ordem, coddirpai, nome, tam, tipo, modificado, atributos, " \
		"caminho, nomeaba, nomepai, caminhopai from consultaarquivo");
}

ListaDiretorio DiretorioBO_carregarDiretorio(GString *sSQL,
    GString *sCondicaoTotal, IProgressoLog progressoLog) {

    return DiretorioDAO_consultarTudo(
                sSQL, sCondicaoTotal, progressoLog);
}

GString *DiretorioBO_removerDrive(GString *sDiretorio) {
	GString *sArq = sDiretorio;
	GString *drive = g_string_new(":");
	gboolean bAchou = FALSE;

    if (sArq->len > 0) {
        if (Rotinas_ContainsStr(Rotinas_UpperCase(sArq),
			Rotinas_UpperCase(drive))) {
                bAchou = TRUE;
        }
    }
    sArq = Rotinas_trocaSeparador(sArq);
    if (bAchou) {
        sArq = Rotinas_SubString(sArq, drive->len+3, sArq->len);
    }
	return sArq;
}

int DiretorioBO_retCodDirPai(int nAba, GString *sDiretorio,
                              ListaDiretorio listaLocal) {
	guint tamlista = ListaDiretorio_conta(listaLocal);
    Diretorio diretorio = Diretorio_new();

	for (unsigned int i = 0; i < tamlista; i++) {
		diretorio = ListaDiretorio_pesquisaItemOrd(listaLocal, i);

        if (diretorio->aba->codigo == nAba) {
            if (g_string_equal(diretorio->caminho, sDiretorio)) {
                return diretorio->ordem;
            }
        }
    }
    return 0;
}

Diretorio DiretorioBO_atribuiDiretorio(int nAba, int nCodDirRaiz,
        GString *sNomeDirRaiz, GString *sDiretorio, gboolean bDiretorio,
        ListaDiretorio listaLocal, Arquivo arquivo,
        DiretorioOrdem *dirOrdem) {
    int nOrdem = (*dirOrdem)->ordem;
    Diretorio diretorio = Diretorio_new();
    GString *sCaminho; //, *sDir;
	long long tamanho;

    sCaminho = DiretorioBO_removerDrive(sDiretorio);

    if ((sCaminho->len > 0) && (sNomeDirRaiz->len > 0)) {
        if (Rotinas_cStartsStr(sCaminho->str, sNomeDirRaiz->str)) {
            sCaminho = Rotinas_SubString(sCaminho, sNomeDirRaiz->len+2,
                        sCaminho->len);
            //sDir = Rotinas_SubString(sDiretorio, sNomeDirRaiz->len+2, sDiretorio->len);
        } else {
            sCaminho = Rotinas_concatenar1(sNomeDirRaiz, Rotinas_BARRA_INVERTIDA, sCaminho->str);
            //sDir = Rotinas_concatenar1(sNomeDirRaiz, Rotinas_BARRA_INVERTIDA, sDiretorio->str);
        }
    }

	diretorio->aba->codigo = nAba;
    diretorio->codigo = nCodDirRaiz;
    diretorio->ordem = nOrdem;
    diretorio->arquivo->nome = g_string_new(arquivo->nome->str);
    diretorio->arquivo->tamanho = arquivo->tamanho;
	diretorio->arquivo->modificado = arquivo->modificado;
    diretorio->arquivo->atributos = arquivo->atributos;

    if (sDiretorio->len==0) {
        diretorio->caminho = g_string_new(arquivo->nome->str);
		diretorio->caminhoPai = g_string_new("");
    } else {
        diretorio->caminho = g_string_new(sCaminho->str);
        diretorio->caminhoPai = Rotinas_SubString(diretorio->caminho, 1,
                Rotinas_cLastDelimiter(Rotinas_BARRA_INVERTIDA,
                        diretorio->caminho->str) - 1);
    }

    if (bDiretorio) {
		diretorio->tipo->codigo = 'D';
        if (nOrdem == 1) {
            diretorio->codDirPai = 0;
        } else {
            diretorio->codDirPai = DiretorioBO_retCodDirPai(diretorio->aba->codigo,
                    diretorio->caminhoPai, listaLocal);
        }
    } else {
		diretorio->tipo->codigo = 'A';
        diretorio->codDirPai = DiretorioBO_retCodDirPai(diretorio->aba->codigo,
                diretorio->caminhoPai, listaLocal);
    }
	diretorio->aba->nome = g_string_new("");
    diretorio->nomePai = g_string_new("");
	tamanho = diretorio->arquivo->tamanho;
    diretorio->tamanhoFormatado = Rotinas_MontaTamanho(tamanho);
    if (diretorio->tipo->codigo == 'D') {
		diretorio->tipo->nome = Rotinas_getRecurso("TipoLista.diretorio");
    } else {
		diretorio->tipo->nome = Rotinas_getRecurso("TipoLista.arquivo");
    }
    diretorio->modificadoFormatado = Rotinas_formataDate(
            Rotinas_FORMATO_DATAHORA, diretorio->arquivo->modificado);
    diretorio->caminhoOriginal = g_string_new(sDiretorio->str);

    nOrdem++;

    (*dirOrdem)->ordem = nOrdem;

    return diretorio;
}

void DiretorioBO_atribuiListaDiretorio(int nAba, int nCodDirRaiz,
        GString *sNomeDirRaiz, GString *sDiretorio, ListaDiretorio *listaLocal,
        Arquivo info, DiretorioOrdem *dirOrdem, IProgressoLog progressoLog) {
    Diretorio diretorio;
	GString *ponto = g_string_new(".");
	GString *pponto = g_string_new("..");
    Progresso pb;
	pb.log = g_string_new("");

    if (Rotinas_FileExists(sDiretorio)) {
		diretorio = DiretorioBO_atribuiDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz,
                sDiretorio, false, *listaLocal, info,
                dirOrdem);
		*listaLocal = ListaDiretorio_insere(*listaLocal, diretorio,
			diretorio->ordem-1);

        if (progressoLog != NULL) {
            pb.log = g_string_new(sDiretorio->str);
            progressoLog(pb);
        }
    } else if (Rotinas_DirectoryExists(sDiretorio)) {
        if (!g_string_equal(info->nome, ponto) && !g_string_equal(info->nome, pponto)) {
            diretorio = DiretorioBO_atribuiDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz,
                    sDiretorio, true, *listaLocal, info,
                    dirOrdem);
			*listaLocal = ListaDiretorio_insere(*listaLocal, diretorio,
				diretorio->ordem-1);

            if (progressoLog != NULL) {
                pb.log = g_string_new(sDiretorio->str);
                progressoLog(pb);
            }

			DiretorioBO_ImportarDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz, sDiretorio,
                    listaLocal, dirOrdem, progressoLog);
        }
    }

}

void DiretorioBO_ImportarDiretorio(int nAba, int nCodDirRaiz,
        GString *sNomeDirRaiz, GString *sDiretorio, ListaDiretorio *listaLocal,
        DiretorioOrdem *dirOrdem, IProgressoLog progressoLog) {
	Arquivo info;
    GString *sCaminho; //, *sSeparador;
/*
    if (g_string_equal(Rotinas_SubString(sDiretorio,
            sDiretorio->len, 1), g_string_new(Rotinas_BARRA_NORMAL))) {
        sSeparador = g_string_new("");
    } else {
		sSeparador = g_string_new(Rotinas_BARRA_NORMAL);
    }
*/
	ListaString listaDir = Rotinas_listarArquivosDiretorios(sDiretorio);
	guint tamlistaDir = ListaString_conta(listaDir);
	for (unsigned int i = 0; i < tamlistaDir; i++)
	{
		sCaminho = ListaString_pesquisaItemOrd(listaDir, i);
		info = Rotinas_FileInfoToArquivo(sCaminho);
		DiretorioBO_atribuiListaDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz,
			sCaminho, listaLocal, info, dirOrdem,
			progressoLog);
	}
}

gboolean DiretorioBO_verificaCodDir(int nAba, GString *sDiretorio,
        ListaDiretorio listaLocal) {
	guint tamlista = ListaDiretorio_conta(listaLocal);
	Diretorio diretorio = Diretorio_new();

    if (sDiretorio->len > 0) {
		for (unsigned int i = 0; i < tamlista; i++) {
			diretorio = ListaDiretorio_pesquisaItemOrd(listaLocal, i);

            if (diretorio->aba->codigo == nAba) {
                if (diretorio->ordem == 1) {
                    if (diretorio->codDirPai == 0) {
                        if (g_string_equal(diretorio->caminho, sDiretorio)) {
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
	guint tamlista = ListaDiretorio_conta(listaLocal);
    Diretorio diretorio = Diretorio_new();

	for (unsigned int i = 0; i < tamlista; i++) {
		diretorio = ListaDiretorio_pesquisaItemOrd(listaLocal, i);

		if (diretorio->aba->codigo == nAba) {
            if (diretorio->codigo > nMaior) {
                nMaior = diretorio->codigo;
            }
        }
    }
    return nMaior + 1;
}

GString *DiretorioBO_diretorioToSQL(Diretorio diretorio, gboolean bInsert) {
    GString *sSQL = g_string_new("");

    if (bInsert) {
        sSQL = g_string_new("insert into Diretorios(aba, cod, ordem, coddirpai, nome, " \
               "tam, tipo, modificado, atributos, caminho) values(");
    }

    sSQL = Rotinas_concatenar2(sSQL, Rotinas_IntToStr(diretorio->aba->codigo), ",");
	sSQL = Rotinas_concatenar2(sSQL, Rotinas_IntToStr(diretorio->codigo), ",");
	sSQL = Rotinas_concatenar2(sSQL, Rotinas_IntToStr(diretorio->ordem), ",");
	sSQL = Rotinas_concatenar2(sSQL, Rotinas_IntToStr(diretorio->codDirPai), ",");
    sSQL = Rotinas_concatenar2(sSQL, Rotinas_QuotedStr(diretorio->arquivo->nome), ",");
	sSQL = Rotinas_concatenar2(sSQL, Rotinas_LongLongToStr(diretorio->arquivo->tamanho), ",");
    sSQL = Rotinas_concatenar2(sSQL, Rotinas_QuotedChar(diretorio->tipo->codigo), ",");
    sSQL = Rotinas_concatenar2(sSQL, Rotinas_QuotedStr(diretorio->modificadoFormatado), ",");
    sSQL = Rotinas_concatenar2(sSQL, Rotinas_QuotedStr(diretorio->arquivo->atributos), ",");
    sSQL = Rotinas_concatenar2(sSQL, Rotinas_QuotedStr(diretorio->caminho), ",");

    if (bInsert) {
        sSQL = g_string_append(sSQL,")");
    }

    return sSQL;
}

void DiretorioBO_salvarDiretorio(ListaDiretorio listaDiretorio,
        IProgressoLog progressoLog) {
	guint tamlista = ListaDiretorio_conta(listaDiretorio);
	Diretorio diretorio = Diretorio_new();
	Progresso pb;
    pb.minimo = 0;
    pb.maximo = tamlista - 1;
    pb.posicao = 0;
    pb.passo = 1;
	GString *sdir = Rotinas_getRecurso("TipoLista.diretorio");

	for (unsigned int i = 0; i < tamlista; i++) {
		diretorio = ListaDiretorio_pesquisaItemOrd(listaDiretorio, i);

        DiretorioDAO_incluir(diretorio);
		pb.log = g_string_new("");
        g_string_append_printf(pb.log, "%s - Salvando %s: %s",
			Rotinas_IntToStr(i + 1)->str, sdir->str, diretorio->caminho->str);

        pb.posicao = i;

        if (progressoLog != NULL) {
            progressoLog(pb);
        }
    }
}

gboolean DiretorioBO_excluirDiretorio(Aba aba, GString *sCaminho) {
   return DiretorioDAO_excluir(aba, sCaminho);
}

void DiretorioBO_excluirListaDiretorio(ListaDiretorio *listaDiretorio,
        Aba aba, GString *sCaminho) {
	guint tamlista = ListaDiretorio_conta(*listaDiretorio);
	Diretorio diretorio = Diretorio_new();
	//int conta = 0;

	for (unsigned int i = 0; i < tamlista; i++) {
		diretorio = ListaDiretorio_pesquisaItemOrd(*listaDiretorio, i);

        if (diretorio->aba->codigo == aba->codigo) {
            if (Rotinas_Trim(sCaminho)->len > 0) {
                if (Rotinas_cStartsStr(diretorio->caminho->str, sCaminho->str)) {
					ListaDiretorio_removeItem(listaDiretorio, diretorio);
                }
            } else {
				ListaDiretorio_removeItem(listaDiretorio, diretorio);
            }
        }


    }

}

GString *DiretorioBO_diretorioToCSV(Diretorio diretorio) {
    GString *sCSV = g_string_new("\"");

    sCSV = Rotinas_concatenar2(sCSV, diretorio->aba->nome, "\";\"");
    sCSV = Rotinas_concatenar2(sCSV, diretorio->arquivo->nome, "\";\"");
    sCSV = Rotinas_concatenar2(sCSV, Rotinas_LongLongToStr(diretorio->arquivo->tamanho), "\";\"");
    sCSV = Rotinas_concatenar2(sCSV, diretorio->tamanhoFormatado, "\";\"");
    sCSV = Rotinas_concatenar2(sCSV, diretorio->tipo->nome, "\";\"");
    sCSV = Rotinas_concatenar2(sCSV, diretorio->modificadoFormatado, "\";\"");
    sCSV = Rotinas_concatenar2(sCSV, diretorio->arquivo->atributos, "\";\"");
    sCSV = Rotinas_concatenar2(sCSV, diretorio->caminho, "\"");

    return sCSV;
}

GString *DiretorioBO_diretorioToXML(Diretorio diretorio) {
    GString *sXML, *sCR, *sTAB, *sTAB2, *sCodigo;

    sTAB = g_string_new("\t");
    sTAB2 = g_string_new("\t\t");
    sCR = g_string_new("\n");
	sCodigo = g_string_new("");

    sXML = Rotinas_concatenar1(sTAB, "<arquivo>", sCR->str);

    sXML = Rotinas_concatenar4(sXML, sTAB2, "<aba>", Rotinas_IntToStr(diretorio->aba->codigo)->str,
            "</aba>", sCR->str);
    sXML = Rotinas_concatenar4(sXML, sTAB2, "<nomeAba>", diretorio->aba->nome->str,
            "</nomeAba>", sCR->str);
    sXML = Rotinas_concatenar4(sXML, sTAB2, "<codigo>", Rotinas_IntToStr(diretorio->codigo)->str,
            "</codigo>", sCR->str);
    sXML = Rotinas_concatenar4(sXML, sTAB2, "<ordem>", Rotinas_IntToStr(diretorio->ordem)->str,
            "</ordem>", sCR->str);
    sXML = Rotinas_concatenar4(sXML, sTAB2, "<nome>", diretorio->arquivo->nome->str, "</nome>", sCR->str);
    sXML = Rotinas_concatenar4(sXML, sTAB2, "<tamanho>", Rotinas_LongLongToStr(diretorio->arquivo->tamanho)->str,
            "</tamanho>", sCR->str);
	sCodigo = g_string_append_c_inline(sCodigo, diretorio->tipo->codigo);
    sXML = Rotinas_concatenar4(sXML, sTAB2, "<tipo>", sCodigo->str,
            "</tipo>", sCR->str);
    sXML = Rotinas_concatenar4(sXML, sTAB2, "<modificado>", diretorio->modificadoFormatado->str,
            "</modificado>", sCR->str);
    sXML = Rotinas_concatenar4(sXML, sTAB2, "<atributos>", diretorio->arquivo->atributos->str,
            "</atributos>", sCR->str);
    sXML = Rotinas_concatenar4(sXML, sTAB2, "<codDirPai>", Rotinas_IntToStr(diretorio->codDirPai)->str,
            "</codDirPai>", sCR->str);
    sXML = Rotinas_concatenar4(sXML, sTAB2, "<caminho>", diretorio->caminho->str,
            "</caminho>", sCR->str);

    sXML = Rotinas_concatenar2(sXML, sTAB, "</arquivo>");

    return sXML;
}

GString *DiretorioBO_diretorioToTXT(Diretorio diretorio) {
    GString *sTXT, *sTAB;

    sTAB = g_string_new("\t");
    sTXT = g_string_new("");
    sTXT = Rotinas_concatenar2(sTXT, diretorio->aba->nome, sTAB->str);
    sTXT = Rotinas_concatenar2(sTXT, diretorio->arquivo->nome, sTAB->str);
    sTXT = Rotinas_concatenar2(sTXT, Rotinas_LongLongToStr(diretorio->arquivo->tamanho), sTAB->str);
    sTXT = Rotinas_concatenar2(sTXT, diretorio->tamanhoFormatado, sTAB->str);
    sTXT = Rotinas_concatenar2(sTXT, diretorio->tipo->nome, sTAB->str);
    sTXT = Rotinas_concatenar2(sTXT, diretorio->modificadoFormatado, sTAB->str);
    sTXT = Rotinas_concatenar2(sTXT, diretorio->arquivo->atributos, sTAB->str);
    sTXT = Rotinas_concatenar(sTXT->str, diretorio->caminho->str);

    return sTXT;
}

GString *DiretorioBO_diretorioToHTML(Diretorio diretorio) {
    GString *sHTML, *sCR, *sTAB, *sTAB2;

    sTAB = g_string_new("\t");
    sTAB2 = g_string_new("\t\t");
    sCR = g_string_new("\n");

    sHTML = Rotinas_concatenar1(sTAB, "<tr>", sCR->str);

    sHTML = Rotinas_concatenar4(sHTML, sTAB2, "<td>", diretorio->aba->nome->str, "</td>", sCR->str);
    sHTML = Rotinas_concatenar4(sHTML, sTAB2, "<td>", diretorio->arquivo->nome->str, "</td>", sCR->str);
    sHTML = Rotinas_concatenar4(sHTML, sTAB2, "<td>", Rotinas_LongLongToStr(diretorio->arquivo->tamanho)->str, "</td>", sCR->str);
    sHTML = Rotinas_concatenar4(sHTML, sTAB2, "<td>", Rotinas_cReplaceAll(
            diretorio->tamanhoFormatado->str, " ", "&nbsp;"), "</td>", sCR->str);
    sHTML = Rotinas_concatenar4(sHTML, sTAB2, "<td>", diretorio->tipo->nome->str, "</td>", sCR->str);
    sHTML = Rotinas_concatenar4(sHTML, sTAB2, "<td>", Rotinas_cReplaceAll(
		diretorio->modificadoFormatado->str, " ", "&nbsp;"), "</td>", sCR->str);
    sHTML = Rotinas_concatenar4(sHTML, sTAB2, "<td>", diretorio->arquivo->atributos->str, "</td>", sCR->str);
    sHTML = Rotinas_concatenar4(sHTML, sTAB2, "<td>", diretorio->caminho->str, "</td>", sCR->str);

    sHTML = Rotinas_concatenar2(sHTML, sTAB, "</tr>");
    return sHTML;
}

void DiretorioBO_exportarDiretorio(TipoExportar tipo, Aba aba,
        GString *sNomeArquivo, IProgressoLog progressoLog) {
    GString *sTexto = g_string_new(""), *sCR, *sTAB, *sTAB2, *sSQL, *sCondicaoTotal;
    Aba abaLocal = Aba_new();
    Diretorio diretorio;
	guint tamlista;
	gint posicao = 0;
	ListaString listaLocal = ListaString_inicia();
    ListaDiretorio listaDiretorio;

    sTAB = g_string_new("\t");
    sTAB2 = g_string_new("\t\t");
    sCR = g_string_new("\n");

    sCondicaoTotal = Rotinas_concatenar(" where aba=", Rotinas_IntToStr(aba->codigo)->str);
    sSQL = Rotinas_concatenar2(DiretorioBO_sqlConsultaArquivo(), sCondicaoTotal, " order by 1, 2, 3");
    listaDiretorio = DiretorioBO_carregarDiretorio(sSQL, sCondicaoTotal, progressoLog);

    switch (tipo) {
        case teCSV: {
            sTexto = g_string_new("\"Aba\";\"Nome\";\"TamanhoBytes\";\"Tamanho\";" \
                     "\"Tipo\";\"Modificado\";\"Atributos\";\"Caminho\"");
        }
        break;
        case teHTML: {
            sTexto = Rotinas_concatenar("<!DOCTYPE html>", sCR->str);
            sTexto = Rotinas_concatenar1(sTexto, "<html>", sCR->str);
            sTexto = Rotinas_concatenar1(sTexto, "<body>", sCR->str);
            sTexto = Rotinas_concatenar1(sTexto, "<table border=\"1\" cellpadding=\"5\" cellspacing=\"0\">"
                   , sCR->str);
            sTexto = Rotinas_concatenar3(sTexto, sTAB, "<tr>", sCR->str);
            sTexto = Rotinas_concatenar3(sTexto, sTAB2, "<th>Aba</th>", sCR->str);
            sTexto = Rotinas_concatenar3(sTexto, sTAB2, "<th>Nome</th>", sCR->str);
            sTexto = Rotinas_concatenar3(sTexto, sTAB2, "<th>Tamanho</th>", sCR->str);
            sTexto = Rotinas_concatenar3(sTexto, sTAB2, "<th>Tamanho Formatado</th>", sCR->str);
            sTexto = Rotinas_concatenar3(sTexto, sTAB2, "<th>Tipo</th>", sCR->str);
            sTexto = Rotinas_concatenar3(sTexto, sTAB2, "<th>Modificado</th>", sCR->str);
            sTexto = Rotinas_concatenar3(sTexto, sTAB2, "<th>Atributos</th>", sCR->str);
            sTexto = Rotinas_concatenar3(sTexto, sTAB2, "<th>Caminho</th>", sCR->str);
            sTexto = Rotinas_concatenar2(sTexto, sTAB, "</tr>");
        }
        break;
        case teXML: {
            sTexto = g_string_new("<diretorio>");
        }
        break;
        case teSQL: {
            diretorio = ListaDiretorio_pesquisaItemOrd(listaDiretorio, 0);
            abaLocal->codigo = diretorio->aba->codigo;
            abaLocal->nome = g_string_new(diretorio->aba->nome->str);
            sTexto = AbaBO_abaToSQL(abaLocal);
        }
        break;
        case teTXT: {
        }
    }
	listaLocal = ListaString_insere(listaLocal, sTexto, posicao);
	posicao++;

	tamlista = ListaDiretorio_conta(listaDiretorio);
	for (unsigned int i = 0; i < tamlista; i++) {
		diretorio = ListaDiretorio_pesquisaItemOrd(listaDiretorio, i);

        if (diretorio->aba->codigo == aba->codigo) {
            if (tipo == teTXT) {
                sTexto = DiretorioBO_diretorioToTXT(diretorio);
            } else if (tipo == teCSV) {
                sTexto = DiretorioBO_diretorioToCSV(diretorio);
            } else if (tipo == teHTML) {
                sTexto = DiretorioBO_diretorioToHTML(diretorio);
            } else if (tipo == teXML) {
                sTexto = DiretorioBO_diretorioToXML(diretorio);
            } else if (tipo == teSQL) {
                sTexto = Rotinas_concatenar(DiretorioBO_diretorioToSQL(diretorio, TRUE)->str, ";");
            }

			listaLocal = ListaString_insere(listaLocal, sTexto, posicao);
			posicao++;
        }
    }

    if (tipo == teHTML) {
        sTexto = Rotinas_concatenar3(sTexto, sCR, "</table>", sCR->str);
        sTexto = Rotinas_concatenar1(sTexto, "</body>", sCR->str);
        sTexto = Rotinas_concatenar1(sTexto, "</html>", sCR->str);
    } else if (tipo == teXML) {
        sTexto = g_string_new("</diretorio>");
    }
	listaLocal = ListaString_insere(listaLocal, sTexto, posicao);
	posicao++;

    Rotinas_SListSaveToFile(listaLocal, sNomeArquivo);

	ListaDiretorio_removeTodos(&listaDiretorio);

}

gboolean DiretorioBO_criarTabelaDiretorios() {
    return DiretorioDAO_criarTabela();
}

int DiretorioBO_XMLParaDiretorio(GString *sTexto, int nArquivo,
        DiretorioXML *diretorioXML) {
	GString *sTagInicio = g_string_new("");
	GString *sValor = g_string_new("");
	GString *sTagFim = g_string_new("");
    int resultado;

    resultado = nArquivo;

    if (Rotinas_cPos(">", sTexto->str) > 0) {
        sTagInicio = Rotinas_SubString(sTexto, 1, Rotinas_cPos(">", sTexto->str));
    }
    if ((Rotinas_cPos(">", sTexto->str) > 0) && (Rotinas_cPos("</", sTexto->str) > 1)) {
        sValor = Rotinas_SubString(sTexto, Rotinas_cPos(">", sTexto->str) + 1,
			Rotinas_cPos("</", sTexto->str) - Rotinas_cPos(">", sTexto->str) - 1);
    }
    if (Rotinas_cLastDelimiter(">", sTexto->str) > 0) {
        sTagFim = Rotinas_SubString(sTexto,
			Rotinas_cLastDelimiter("<", sTexto->str),
			Rotinas_cLastDelimiter(">", sTexto->str));
    }

    if ((nArquivo == 1) && (!Rotinas_comparar(sTagInicio, "<arquivo>"))) {
        resultado = -1;
    }
    if ((nArquivo == 2) && (!Rotinas_comparar(sTagInicio, "<aba>"))
            && (!Rotinas_comparar(sTagFim, "</aba>"))) {
        // diretorio->aba->codigo = Rotinas_StrToInt(sValor);
        resultado = -1;
    }
    if ((nArquivo == 3) && (!Rotinas_comparar(sTagInicio, "<nomeAba>"))
            && (!Rotinas_comparar(sTagFim, "</nomeAba>"))) {
        // diretorio->aba->nome = sValor;
        resultado = -1;
    }
    if ((nArquivo == 4) && (Rotinas_comparar(sTagInicio, "<codigo>"))
            && (Rotinas_comparar(sTagFim, "</codigo>"))) {
        (*diretorioXML).diretorio->codigo = Rotinas_StrToInt(sValor);
    }
    if ((nArquivo == 5) && (Rotinas_comparar(sTagInicio, "<ordem>"))
            && (Rotinas_comparar(sTagFim, "</ordem>"))) {
        (*diretorioXML).diretorio->ordem = Rotinas_StrToInt(sValor);
    }
    if ((nArquivo == 6) && (Rotinas_comparar(sTagInicio, "<nome>"))
            && (Rotinas_comparar(sTagFim, "</nome>"))) {
        (*diretorioXML).diretorio->arquivo->nome = g_string_new(sValor->str);
    }
    if ((nArquivo == 7) && (Rotinas_comparar(sTagInicio, "<tamanho>"))
            && (Rotinas_comparar(sTagFim, "</tamanho>"))) {
        (*diretorioXML).diretorio->arquivo->tamanho = Rotinas_StrToLong(sValor);
    }
    if ((nArquivo == 8) && (Rotinas_comparar(sTagInicio, "<tipo>"))
            && (Rotinas_comparar(sTagFim, "</tipo>"))) {
        (*diretorioXML).diretorio->tipo->codigo = sValor->str[0];
    }
    if ((nArquivo == 9) && (Rotinas_comparar(sTagInicio, "<modificado>"))
            && (Rotinas_comparar(sTagFim, "</modificado>"))) {
        (*diretorioXML).diretorio->arquivo->modificado =
                Rotinas_StringToDate(sValor);
    }
    if ((nArquivo == 10) && (Rotinas_comparar(sTagInicio, "<atributos>"))
            && (Rotinas_comparar(sTagFim, "</atributos>"))) {
        (*diretorioXML).diretorio->arquivo->atributos = g_string_new(sValor->str);
    }
    if ((nArquivo == 11) && (Rotinas_comparar(sTagInicio, "<codDirPai>"))
            && (Rotinas_comparar(sTagFim, "</codDirPai>"))) {
        (*diretorioXML).diretorio->codDirPai = Rotinas_StrToInt(sValor);
    }
    if ((nArquivo == 12) && (Rotinas_comparar(sTagInicio, "<caminho>"))
            && (Rotinas_comparar(sTagFim, "</caminho>"))) {
        (*diretorioXML).diretorio->caminho = g_string_new(sValor->str);
    }
    if ((nArquivo == 13) && (!Rotinas_comparar(sTagInicio, "</arquivo>"))) {
        resultado = -1;
    }
    if (Rotinas_comparar(sTagInicio, "</diretorio>")) {
        resultado = -3;
    }

    return resultado;
}

int DiretorioBO_importarDiretorioViaXML(Aba aba, GString *sNomeArquivo,
        ListaDiretorio listaDirPai,
        IProgressoLog progressoLog) {
    GString *sTexto = g_string_new(""), *sTexto1 = g_string_new("");
    int nArquivo, resultado;
    ListaString listalocal = ListaString_inicia();
    DiretorioXML diretorioXML;
    ListaDiretorio listaDiretorio = ListaDiretorio_inicia();
	guint tamlista;
	gint posicao = 0;

    resultado = 0;
    listalocal = Rotinas_SListLoadFromFile(sNomeArquivo);
	GString *item0 = ListaString_pesquisaItemOrd(listalocal, 0);

    if (listalocal!=NULL && !Rotinas_comparar(item0, "<diretorio>")) {
        resultado = -1;
    } else {
        nArquivo = 0;

		tamlista = ListaString_conta(listalocal);
		for (unsigned int i = 0; i < tamlista; i++) {
			sTexto1 = ListaString_pesquisaItemOrd(listalocal, i);
            sTexto =  Rotinas_Trim(sTexto1);

			diretorioXML.diretorio = Diretorio_new();
            nArquivo = DiretorioBO_XMLParaDiretorio(sTexto, nArquivo, &diretorioXML);

            if (nArquivo == -1) {
                resultado = -1;
                break;
            } else if (nArquivo == 13) {
                nArquivo = 1;
                diretorioXML.diretorio->aba = Aba_copiar(aba);
				listaDiretorio = ListaDiretorio_insere(listaDiretorio, diretorioXML.diretorio, posicao);
				posicao++;

                if (DiretorioBO_verificaCodDir(aba->codigo,
                        diretorioXML.diretorio->caminho,
                        listaDirPai)) {
                    resultado = -2;
                    break;
                }

				//diretorioXML->diretorio = Diretorio_new();
            } else if (nArquivo == -3) {
                resultado = nArquivo;
            } else {
                nArquivo++;
            }
        }
    }

	DiretorioBO_salvarDiretorio(listaDiretorio, progressoLog);
	ListaDiretorio_removeTodos(&listaDiretorio);

    return resultado;
}

gboolean DiretorioBO_carregarSubDiretorios(GString *sDiretorio,
	ListaString listaLocal) {
    GString *sCaminho; //, *sSeparador;
	int ntamlista;
	gint posicao = 0;
/*
    if (Rotinas_comparar(Rotinas_SubString(sDiretorio, sDiretorio->len, 1),
            Rotinas_BARRA_NORMAL)) {
        sSeparador = g_string_new("");
    } else {
		sSeparador = g_string_new(Rotinas_BARRA_NORMAL);
    }
*/
	ListaString listaDir = Rotinas_listarArquivosDiretorios(sDiretorio);
	guint tamlistaDir = ListaString_conta(listaDir);
	for (unsigned int i = 0; i < tamlistaDir; i++)
	{
		sCaminho = ListaString_pesquisaItemOrd(listaDir, i);

		if (Rotinas_DirectoryExists(sCaminho)) {
			listaLocal = ListaString_insere(listaLocal, sCaminho, posicao);
			posicao++;
		}
	}

	ntamlista = ListaString_conta(listaLocal);

    return (ntamlista > 0);
}

gboolean DiretorioBO_carregarArquivos(GString *sDiretorio,
        ListaString listaLocal) {
    GString *sCaminho; //, *sSeparador;
	int ntamlista;
	gint posicao = 0;
/*
    if (Rotinas_comparar(Rotinas_SubString(sDiretorio, sDiretorio->len, 1),
		Rotinas_BARRA_NORMAL)) {
        sSeparador = g_string_new("");
    } else {
		sSeparador = g_string_new(Rotinas_BARRA_NORMAL);
    }
*/
	ListaString listaDir = Rotinas_listarArquivosDiretorios(sDiretorio);
	guint tamlistaDir = ListaString_conta(listaDir);
	for (unsigned int i = 0; i < tamlistaDir; i++)
	{
		sCaminho = ListaString_pesquisaItemOrd(listaDir, i);

		if (Rotinas_FileExists(sCaminho)) {
			listaLocal = ListaString_insere(listaLocal, sCaminho, posicao);
			posicao++;
		}
	}

	ntamlista = ListaString_conta(listaLocal);

	return (ntamlista > 0);
}

gboolean DiretorioBO_carregarTodosArquivos(GString *sDiretorio,
        ListaString listaLocal) {
	GString *sCaminho, *sSeparador, *arquivo;
	GString *ponto = g_string_new(".");
	GString *pponto = g_string_new("..");
	int ntamlista;
	gint posicao = 0;

	if (Rotinas_comparar(Rotinas_SubString(sDiretorio, sDiretorio->len, 1),
		Rotinas_BARRA_NORMAL)) {
		sSeparador = g_string_new("");
	}
	else {
		sSeparador = g_string_new(Rotinas_BARRA_NORMAL);
	}

	sCaminho = Rotinas_concatenar(sDiretorio->str, sSeparador->str);
	arquivo = Rotinas_ExtractFilePath(sCaminho);

	if (Rotinas_DirectoryExists(sCaminho)) {
		sCaminho = Rotinas_concatenar2(sDiretorio, sSeparador, arquivo->str);

		if (Rotinas_FileExists(sCaminho)) {
			listaLocal = ListaString_insere(listaLocal, sCaminho, posicao);
			posicao++;
		}
		else if (Rotinas_DirectoryExists(sCaminho)) {
			if (!g_string_equal(arquivo, ponto) && !g_string_equal(arquivo, pponto)) {
				DiretorioBO_carregarTodosArquivos(sCaminho, listaLocal);
			}
		}

		ListaString listaDir = Rotinas_listarArquivosDiretorios(sDiretorio);
		guint tamlistaDir = ListaString_conta(listaDir);
		for (unsigned int i = 0; i < tamlistaDir; i++)
		{
			sCaminho = ListaString_pesquisaItemOrd(listaDir, i);

			if (Rotinas_FileExists(sCaminho)) {
				listaLocal = ListaString_insere(listaLocal, sCaminho, posicao);
				posicao++;
			}
			else if (Rotinas_DirectoryExists(sCaminho)) {
				if (!g_string_equal(arquivo, ponto) && !g_string_equal(arquivo, pponto)) {
					DiretorioBO_carregarTodosArquivos(sCaminho, listaLocal);
				}
			}
		}
	}

	ntamlista = ListaString_conta(listaLocal);

	return (ntamlista > 0);
}

ListaDiretorio DiretorioBO_itensFilhos(ListaDiretorio lista_pai,
        int aba, int codDirPai, int codigo) {
    ListaDiretorio lista = ListaDiretorio_inicia();
    Diretorio diretorio = Diretorio_new();
	guint tamlista = ListaDiretorio_conta(lista_pai);
	gint posicao = 0;

	for (unsigned int i = 0; i < tamlista; i++) {
		diretorio = ListaDiretorio_pesquisaItemOrd(lista_pai, i);

        if (diretorio->aba->codigo == aba) {
            if (diretorio->codDirPai == codDirPai) {
                if (diretorio->codigo == codigo) {
					lista = ListaDiretorio_insere(lista, diretorio, posicao);
					posicao++;
                }
            }
        }
    }
    return lista;
}
