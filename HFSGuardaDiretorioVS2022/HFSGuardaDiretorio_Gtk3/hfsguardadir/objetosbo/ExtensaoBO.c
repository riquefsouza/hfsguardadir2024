#include <stdio.h>
#include "ExtensaoBO.h"
#include "resource.h"
#include "hfsguardadir/objetosdao/ExtensaoDAO.h"
#include "hfsguardadir/objetosbo/DiretorioBO.h"
#include "FrmPrincipal.h"

GdkPixbuf* ExtensaoBO_diretorioBMP;
GdkPixbuf* ExtensaoBO_arquivoBMP;

GdkPixbuf* ExtensaoBO_DiretorioXPM;
GdkPixbuf* ExtensaoBO_ArquivoXPM;
GdkPixbuf* ExtensaoBO_DirAbertoXPM;
GdkPixbuf* ExtensaoBO_CDOuroXPM;
GdkPixbuf* ExtensaoBO_Diretorio32XPM;
GdkPixbuf* ExtensaoBO_Arquivo32XPM;
GdkPixbuf* ExtensaoBO_DirAberto32XPM;

void ExtensaoBO_iniciar()
{
	ExtensaoBO_diretorioBMP = Rotinas_imagemToPixbuf("diretorio.gif");
	ExtensaoBO_arquivoBMP = Rotinas_imagemToPixbuf("arquivo.gif");

	#ifdef __GNUC__
		ExtensaoBO_DiretorioXPM = Rotinas_XPMToPixbuf(XPM_DIRETORIO);
		ExtensaoBO_ArquivoXPM = Rotinas_XPMToPixbuf(XPM_ARQUIVO);
		ExtensaoBO_DirAbertoXPM = Rotinas_XPMToPixbuf(XPM_DIR_ABERTO);
		ExtensaoBO_CDOuroXPM = Rotinas_XPMToPixbuf(XPM_CDOURO);
		ExtensaoBO_Diretorio32XPM = Rotinas_XPMToPixbuf(XPM_DIRETORIO32);
		ExtensaoBO_Arquivo32XPM = Rotinas_XPMToPixbuf(XPM_ARQUIVO32);
		ExtensaoBO_DirAberto32XPM = Rotinas_XPMToPixbuf(XPM_DIR_ABERTO32);
	#else
		ExtensaoBO_DiretorioXPM = Rotinas_imagemToPixbuf("diretorio.gif");
		ExtensaoBO_ArquivoXPM = Rotinas_imagemToPixbuf("arquivo.gif");
		ExtensaoBO_DirAbertoXPM = Rotinas_imagemToPixbuf("dir-aberto.gif");
		ExtensaoBO_CDOuroXPM = Rotinas_imagemToPixbuf("cdouro.gif");
		ExtensaoBO_Diretorio32XPM = Rotinas_imagemToPixbuf("diretorio32.gif");
		ExtensaoBO_Arquivo32XPM = Rotinas_imagemToPixbuf("arquivo32.gif");
		ExtensaoBO_DirAberto32XPM = Rotinas_imagemToPixbuf("dir-aberto32.gif");
	#endif
}


ListaExtensao ExtensaoBO_carregarExtensao(IProgressoLog progressoLog) {
    return ExtensaoDAO_consultarTudo(progressoLog);
}

int ExtensaoBO_retMaxCodExtensao(ListaExtensao listaLocal) {
	guint tamlista = ListaExtensao_conta(listaLocal);
	Extensao extensao = Extensao_new();
	int nMaior = 0;
    	
	for (unsigned int i = 0; i < tamlista; i++) {
		extensao = ListaExtensao_pesquisaItemOrd(listaLocal, i);

        if (extensao->codigo > nMaior) {
            nMaior = extensao->codigo;
        }
    }
    return nMaior + 1;
}

gboolean ExtensaoBO_existeExtensao(GString* sExtensao, ListaExtensao listaLocal) {
	guint tamlista = ListaExtensao_conta(listaLocal);
	Extensao extensao = Extensao_new();

    if (Rotinas_Trim(sExtensao)->len > 0) {
		for (unsigned int i = 0; i < tamlista; i++) {
			extensao = ListaExtensao_pesquisaItemOrd(listaLocal, i);

            if (g_string_equal(Rotinas_LowerCase(Rotinas_Trim(extensao->nome)),
				Rotinas_LowerCase(Rotinas_Trim(sExtensao)))) {
                return true;
            }
        }
    }
    return false;
}

gboolean ExtensaoBO_incluirExtensao(Extensao extensao) {
    return ExtensaoDAO_incluir(extensao);
}

gboolean ExtensaoBO_SalvarExtensao(ListaExtensao listaExtensao,
	GString* sNomeDiretorio, GString* sCaminhoOriginal, ListaString log) {
	GString* sExtensao = g_string_new("");
    Extensao extensao = Extensao_new();
	GString* slog = g_string_new("");
	GdkPixbuf *pixbuf16, *pixbuf32;

    if (Rotinas_cEndsStr(sNomeDiretorio->str, ".")) {
        sExtensao = Rotinas_SubString(sNomeDiretorio,
                Rotinas_cLastDelimiter(".", sNomeDiretorio->str) + 1,
                sNomeDiretorio->len);
        if (!ExtensaoBO_existeExtensao(sExtensao, listaExtensao)) {
            extensao->codigo = ExtensaoBO_retMaxCodExtensao(listaExtensao);
            extensao->nome = Rotinas_LowerCase(sExtensao);
            extensao->ordem = ListaExtensao_conta(listaExtensao)+1;

			pixbuf16 = Rotinas_extrairPixbufArquivo(sCaminhoOriginal, 16);
			if (pixbuf16 != NULL) {
				extensao->bmp16 = gdk_pixbuf_copy(pixbuf16);

				pixbuf32 = Rotinas_extrairPixbufArquivo(sCaminhoOriginal, 32);
				if (pixbuf32 != NULL) {
					extensao->bmp32 = gdk_pixbuf_copy(pixbuf32);

					ExtensaoBO_incluirExtensao(extensao);
					listaExtensao = ListaExtensao_insere(listaExtensao, extensao, extensao->ordem - 1);
					log = ListaString_insere(log,
						Rotinas_concatenar("Salvando Extensão: ", extensao->nome->str),
						extensao->ordem - 1);
				}
				g_object_unref(pixbuf16);
				g_object_unref(pixbuf32);

				return TRUE;
			}
        }
    }

    return FALSE;
}

void ExtensaoBO_salvarExtensoes(ListaDiretorio listaDiretorio,
        ListaExtensao listaExtensao, IProgressoLog progressoLog) {
	guint tamlista = ListaDiretorio_conta(listaDiretorio);
	Diretorio diretorio = Diretorio_new();
	ListaString log = ListaString_inicia();
    Progresso pb;	

    pb.minimo = 0;
    pb.maximo = ListaDiretorio_conta(listaDiretorio) - 1;
    pb.posicao = 0;
    pb.passo = 1;
	pb.log = g_string_new("");


	for (unsigned int i = 0; i < tamlista; i++) {
		diretorio = ListaDiretorio_pesquisaItemOrd(listaDiretorio, i);

        if (diretorio->tipo->codigo == 'A') {
			ExtensaoBO_SalvarExtensao(listaExtensao, diretorio->arquivo->nome,
                    diretorio->caminhoOriginal, log);
            if (ListaString_conta(log) > 0){
				pb.log = ListaString_pesquisaItemOrd(log, 0);
				ListaString_removeTodos(&log);
            }
        }

        pb.posicao++;

        if (progressoLog != NULL) {
            progressoLog(pb);
        }
    }
}

gboolean ExtensaoBO_excluirExtensao(ListaExtensao listaExtensao, int codigo) {
	guint tamlista = ListaExtensao_conta(listaExtensao);
	Extensao extensao = Extensao_new();

    if (ExtensaoDAO_excluir(codigo)) {
		for (unsigned int i = 0; i < tamlista; i++) {
			extensao = ListaExtensao_pesquisaItemOrd(listaExtensao, i);
			
			if (extensao->codigo == codigo) {
				ListaExtensao_removeItem(&listaExtensao, extensao);
                break;
            }
        }
        return true;
    } else {
        return false;
    }
}

gboolean ExtensaoBO_excluirTodasExtensoes(ListaExtensao listaExtensao) {
    if (ExtensaoDAO_excluirTudo()) {
		ListaExtensao_removeTodos(&listaExtensao);
        return true;
    } else {
        return false;
    }
}

gboolean ExtensaoBO_criarTabelaExtensoes() {
    return ExtensaoDAO_criarTabela();
}

int ExtensaoBO_indiceExtensao(ListaExtensao lista, GString* nomeExtensao) {
	guint tamlista = ListaExtensao_conta(lista);
	Extensao extensao = Extensao_new();

    nomeExtensao = Rotinas_SubString(nomeExtensao,
            Rotinas_cLastDelimiter(".", nomeExtensao->str) + 1,
            nomeExtensao->len);
	    
	for (unsigned int i = 0; i < tamlista; i++) {
		extensao = ListaExtensao_pesquisaItemOrd(lista, i);

        if (g_string_equal(Rotinas_LowerCase(Rotinas_Trim(extensao->nome)),
			Rotinas_LowerCase(Rotinas_Trim(nomeExtensao)))) {
            return (extensao->ordem + 2);
        }
    }
    return -1;
}

GdkPixbuf* ExtensaoBO_pixbufExtensao(ListaExtensao lista, const GString* nomeExtensao) {
	guint tamlista = ListaExtensao_conta(lista);
	Extensao extensao = Extensao_new();
	GdkPixbuf *pixbuf = NULL;

	nomeExtensao = Rotinas_SubString(nomeExtensao,
		Rotinas_cLastDelimiter(".", nomeExtensao->str) + 1,
		nomeExtensao->len);

	for (unsigned int i = 0; i < tamlista; i++) {
		extensao = ListaExtensao_pesquisaItemOrd(lista, i);

		if (g_string_equal(Rotinas_LowerCase(Rotinas_Trim(extensao->nome)), 
			Rotinas_LowerCase(Rotinas_Trim(nomeExtensao)))) {		
			return extensao->bmp16;
		}
	}
	return ExtensaoBO_ArquivoXPM;
}

Extensao ExtensaoBO_pegaExtensaoPorOrdem(ListaExtensao lista, int ordem) {
	guint tamlista = ListaExtensao_conta(lista);
	Extensao extensao = Extensao_new();

	for (unsigned int i = 0; i < tamlista; i++) {
		extensao = ListaExtensao_pesquisaItemOrd(lista, i);

        if (extensao->ordem == ordem) {
            return extensao;
        }
    }
    return NULL;
}

Extensao ExtensaoBO_pegaExtensaoPorCodigo(ListaExtensao lista, int codigo) {
	guint tamlista = ListaExtensao_conta(lista);
	Extensao extensao = Extensao_new();

	for (unsigned int i = 0; i < tamlista; i++) {
		extensao = ListaExtensao_pesquisaItemOrd(lista, i);

        if (extensao->codigo == codigo) {
            return extensao;
        }
    }
    return NULL;
}

Extensao ExtensaoBO_pegaExtensaoPorNome(ListaExtensao lista,
        const GString* nome, const GString* tipo) {
	guint tamlista = ListaExtensao_conta(lista);
	Extensao extensao = Extensao_new();

    if (g_string_equal(tipo, Rotinas_getRecurso("TipoLista.diretorio"))){
		extensao->bmp16 = gdk_pixbuf_copy(ExtensaoBO_DiretorioXPM);
		extensao->bmp32 = gdk_pixbuf_copy(ExtensaoBO_Diretorio32XPM);
    } else {
        if (tamlista > 0) {
			for (unsigned int i = 0; i < tamlista; i++) {
				extensao = ListaExtensao_pesquisaItemOrd(lista, i);

                if (g_string_equal(Rotinas_LowerCase(extensao->nome), 
					Rotinas_LowerCase(nome))) {
                    return extensao;
                }
            }
        }
        if (g_string_equal(tipo, Rotinas_getRecurso("TipoLista.arquivo"))) {
			extensao->bmp16 = gdk_pixbuf_copy(ExtensaoBO_ArquivoXPM);
			extensao->bmp32 = gdk_pixbuf_copy(ExtensaoBO_Arquivo32XPM);
		}
    }
    return extensao;
}

gboolean ExtensaoBO_ExportarExtensao(TipoExportarExtensao tipo,
        ListaExtensao listaExtensao) {
	guint tamlista = ListaExtensao_conta(listaExtensao);
	Extensao extensao = Extensao_new();
	GString* sCaminho = g_string_new("");
	GString* sImg16 = g_string_new("");
	GString* sImg32 = g_string_new("");
	GString* sExtensao = g_string_new("");
	GString* ponto = g_string_new(".");

    if (tamlista > 0) {
		sCaminho = g_string_append(Rotinas_AppDirPath(), Rotinas_BARRA_INVERTIDA);

        if (tipo == teBMP) {
            sExtensao = g_string_append(ponto, Rotinas_EXTENSAO_BMP);
        } else if (tipo == teICO) {
			sExtensao = g_string_append(ponto, Rotinas_EXTENSAO_ICO);
        } else if (tipo == teGIF) {
			sExtensao = g_string_append(ponto, Rotinas_EXTENSAO_GIF);
        } else if (tipo == teJPG) {
			sExtensao = g_string_append(ponto, Rotinas_EXTENSAO_JPEG);
        } else if (tipo == tePNG) {
			sExtensao = g_string_append(ponto, Rotinas_EXTENSAO_PNG);
        } else if (tipo == teTIF) {
			sExtensao = g_string_append(ponto, Rotinas_EXTENSAO_TIFF);
        } else {
            sExtensao = g_string_new(".img");
        }

		for (unsigned int i = 0; i < tamlista; i++) {
			extensao = ListaExtensao_pesquisaItemOrd(listaExtensao, i);

			sImg16 = Rotinas_concatenar3(sCaminho, extensao->nome, "16", sExtensao->str);
            if (Rotinas_FileExists(sImg16)) {
                Rotinas_DeleteFromFile(sImg16);
            }

			sImg32 = Rotinas_concatenar3(sCaminho, extensao->nome, "32", sExtensao->str);
            if (Rotinas_FileExists(sImg32)) {
                Rotinas_DeleteFromFile(sImg32);
            }

            switch (tipo) {
                case teBMP: {
                    Rotinas_PixbufToArquivo(extensao->bmp16, sImg16->str, Rotinas_EXTENSAO_BMP);
					Rotinas_PixbufToArquivo(extensao->bmp32, sImg32->str, Rotinas_EXTENSAO_BMP);
                }
                break;
                case teICO: {
                    if (extensao->bmp16!=NULL)
						Rotinas_PixbufToArquivo(extensao->bmp16, sImg16->str, Rotinas_EXTENSAO_ICO);
                    if (extensao->bmp32!=NULL)
						Rotinas_PixbufToArquivo(extensao->bmp32, sImg32->str, Rotinas_EXTENSAO_ICO);
                }
                break;
                case teGIF: {
					if (extensao->bmp16 != NULL)
						Rotinas_PixbufToArquivo(extensao->bmp16, sImg16->str, Rotinas_EXTENSAO_GIF);
					if (extensao->bmp32 != NULL)
						Rotinas_PixbufToArquivo(extensao->bmp32, sImg32->str, Rotinas_EXTENSAO_GIF);
				}
                break;
                case teJPG: {
					if (extensao->bmp16 != NULL)
						Rotinas_PixbufToArquivo(extensao->bmp16, sImg16->str, Rotinas_EXTENSAO_JPEG);
					if (extensao->bmp32 != NULL)
						Rotinas_PixbufToArquivo(extensao->bmp32, sImg32->str, Rotinas_EXTENSAO_JPEG);
				}
                break;
                case tePNG: {
					if (extensao->bmp16 != NULL)
						Rotinas_PixbufToArquivo(extensao->bmp16, sImg16->str, Rotinas_EXTENSAO_PNG);
					if (extensao->bmp32 != NULL)
						Rotinas_PixbufToArquivo(extensao->bmp32, sImg32->str, Rotinas_EXTENSAO_PNG);
				}
                break;
                case teTIF: {
					if (extensao->bmp16 != NULL)
						Rotinas_PixbufToArquivo(extensao->bmp16, sImg16->str, Rotinas_EXTENSAO_TIFF);
					if (extensao->bmp32 != NULL)
						Rotinas_PixbufToArquivo(extensao->bmp32, sImg32->str, Rotinas_EXTENSAO_TIFF);
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

void ExtensaoBO_ImportarExtensao(GString* caminho,
        ListaExtensao listaExtensao) {
	
	GString* sArquivo = g_string_new("");
	Extensao extensao = Extensao_new();
	ListaString listaArquivos = ListaString_inicia();
	ListaString log = ListaString_inicia();
	guint tamlista;
		
    if (DiretorioBO_carregarArquivos(caminho, listaArquivos)) {
		
		tamlista = ListaString_conta(listaArquivos);
		for (unsigned int i = 0; i < tamlista; i++) {
			sArquivo = ListaString_pesquisaItemOrd(listaArquivos, i);

			ExtensaoBO_SalvarExtensao(listaExtensao, Rotinas_ExtractFileName(sArquivo),
                    sArquivo, log);
        }
    }
	

}

void ExtensaoBO_ExtrairExtensao(GString* caminho, ListaExtensao listaExtensao) {
	
	GString* sArquivo = g_string_new("");
	ListaString listaArquivos = ListaString_inicia();
	ListaString log = ListaString_inicia();
	guint tamlista;

    if (DiretorioBO_carregarTodosArquivos(caminho, listaArquivos)) {

		tamlista = ListaString_conta(listaArquivos);
		for (unsigned int i = 0; i < tamlista; i++) {
			sArquivo = ListaString_pesquisaItemOrd(listaArquivos, i);

			ExtensaoBO_SalvarExtensao(listaExtensao, Rotinas_ExtractFileName(sArquivo),
                    sArquivo, log);
        }
    }
	
}
