#include "stdafx.h"

#include <stdio.h>
#include "ExtensaoBO.h"
#include "resource.h"
#include "hfsguardadir/objetosdao/ExtensaoDAO.h"
#include "hfsguardadir/objetosbo/DiretorioBO.h"
#include "FrmPrincipal.h"

BITMAP diretorioBMP, diretorio32BMP;
BITMAP arquivoBMP, arquivo32BMP;

/*
void ExtensaoBO_iniciar(HWND hwnd)
{
	HINSTANCE hi = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);

	HBITMAP diretorioHBMP = LoadBitmap(hi, MAKEINTRESOURCE(DIRETORIO));
	int error = GetObject(diretorioHBMP, sizeof(HBITMAP), &diretorioBMP);

	HBITMAP arquivoHBMP = LoadBitmap(hi, MAKEINTRESOURCE(ARQUIVO));
	error = GetObject(arquivoHBMP, sizeof(BITMAP), &arquivoBMP);

	HBITMAP diretorio32HBMP = LoadBitmap(hi, MAKEINTRESOURCE(DIRETORIO32));
	error = GetObject(diretorio32HBMP, sizeof(BITMAP), &diretorio32BMP);

	HBITMAP arquivo32HBMP = LoadBitmap(hi, MAKEINTRESOURCE(ARQUIVO32));
	error = GetObject(arquivo32HBMP, sizeof(BITMAP), &arquivo32BMP);
}
*/

ListaExtensao ExtensaoBO_carregarExtensao(IProgressoLog progressoLog) {
    return ExtensaoDAO_consultarTudo(progressoLog);
}

int ExtensaoBO_retMaxCodExtensao(ListaExtensao listaLocal) {
	ListaExtensao local;
	int nMaior = 0;
    Extensao extensao;

	for (local = listaLocal; local != NULL; local = local->proximo) {
		extensao = local->extensao;

        if (extensao.codigo > nMaior) {
            nMaior = extensao.codigo;
        }
    }
    return nMaior + 1;
}

BOOL ExtensaoBO_existeExtensao(String sExtensao, ListaExtensao listaLocal) {
	ListaExtensao local;
    Extensao extensao;

    if (String_Trim(sExtensao).length > 0) {
		for (local = listaLocal; local != NULL; local = local->proximo) {
			extensao = local->extensao;

            if (String_comparar(String_LowerCase(String_Trim(extensao.nome)),
				String_LowerCase(String_Trim(sExtensao)))) {
                return true;
            }
        }
    }
    return false;
}

BOOL ExtensaoBO_incluirExtensao(Extensao extensao) {
    return ExtensaoDAO_incluir(extensao);
}

BOOL ExtensaoBO_SalvarExtensao(ListaExtensao listaExtensao,
	String sNomeDiretorio, String sCaminhoOriginal, ListaString log) {
	String sExtensao = String_iniciar("");
    Extensao extensao;
	HBITMAP bmp;
	String slog = String_iniciar("");
	
    if (String_cEndsStr(sNomeDiretorio.str, ".")) {
        sExtensao = String_SubString(sNomeDiretorio,
                String_cLastDelimiter(".", sNomeDiretorio.str) + 1,
                sNomeDiretorio.length);
        if (!ExtensaoBO_existeExtensao(sExtensao, listaExtensao)) {
            extensao.codigo = ExtensaoBO_retMaxCodExtensao(listaExtensao);
            extensao.nome = String_LowerCase(sExtensao);
            extensao.ordem = ListaExtensao_conta(listaExtensao)+1;

			bmp = Rotinas_extrairIconeArquivo(sCaminhoOriginal, 16);
			if (bmp != NULL) {
				extensao.bmp16 = Rotinas_HBitmapToBitmap(bmp, &FrmPrincipal.imageList16);

				bmp = Rotinas_extrairIconeArquivo(sCaminhoOriginal, 32);
				if (bmp != NULL) {
					extensao.bmp32 = Rotinas_HBitmapToBitmap(bmp, &FrmPrincipal.imageList32);
				}
				
				ExtensaoBO_incluirExtensao(extensao);
				ListaExtensao_insereFim(&listaExtensao, extensao);
				slog = String_concatenar("Salvando Extensão: ", extensao.nome);
				ListaString_insereFim(&log, slog);
				return true;
			}
        }
    }

    return false;
}

void ExtensaoBO_salvarExtensoes(ListaDiretorio listaDiretorio,
        ListaExtensao listaExtensao, IProgressoLog progressoLog) {
	ListaDiretorio local;
    ListaString log = ListaString_inicia();
    Diretorio diretorio;
    Progresso pb;	

    pb.minimo = 0;
    pb.maximo = ListaDiretorio_conta(listaDiretorio) - 1;
    pb.posicao = 0;
    pb.passo = 1;
	pb.log = String_iniciar("");

	for (local = listaDiretorio; local != NULL; local = local->proximo) {
		diretorio = local->diretorio;

        if (diretorio.tipo.codigo == 'A') {
			ExtensaoBO_SalvarExtensao(listaExtensao, diretorio.arquivo.nome,
                    diretorio.caminhoOriginal, log);
            if (ListaString_conta(log) > 0){
				pb.log = String_copiar(ListaString_pesquisaItemOrd(log, 0));
				ListaString_removeTodos(&log);
            }
        }

        pb.posicao++;

        if (progressoLog != NULL) {
            progressoLog(pb);
        }
    }
}

BOOL ExtensaoBO_excluirExtensao(ListaExtensao listaExtensao, int codigo) {
	ListaExtensao local;
    Extensao extensao;

    if (ExtensaoDAO_excluir(codigo)) {
		for (local = listaExtensao; local != NULL; local = local->proximo) {
			extensao = local->extensao;
			
			if (extensao.codigo == codigo) {
				ListaExtensao_removeItem(&listaExtensao, extensao, TRUE);
                break;
            }
        }
        return true;
    } else {
        return false;
    }
}

BOOL ExtensaoBO_excluirTodasExtensoes(ListaExtensao listaExtensao) {
    if (ExtensaoDAO_excluirTudo()) {
		ListaExtensao_removeTodos(&listaExtensao);
        return true;
    } else {
        return false;
    }
}

BOOL ExtensaoBO_criarTabelaExtensoes() {
    return ExtensaoDAO_criarTabela();
}

int ExtensaoBO_indiceExtensao(ListaExtensao lista, String nomeExtensao) {
	ListaExtensao local;
	Extensao extensao;

    nomeExtensao = String_SubString(nomeExtensao,
            String_cLastDelimiter(".", nomeExtensao.str) + 1,
            nomeExtensao.length);
	    
	for (local = lista; local != NULL; local = local->proximo) {
		extensao = local->extensao;

        if (String_comparar(String_LowerCase(String_Trim(extensao.nome)),
			String_LowerCase(String_Trim(nomeExtensao)))) {
            return (extensao.ordem + 2);
        }
    }
    return -1;
}

Extensao* ExtensaoBO_pegaExtensaoPorOrdem(ListaExtensao lista, int ordem) {
	ListaExtensao local;
    Extensao *extensao = new Extensao();

	for (local = lista; local != NULL; local = local->proximo) {
		*extensao = local->extensao;

        if (extensao->ordem == ordem) {
            return extensao;
        }
    }
    return NULL;
}

Extensao* ExtensaoBO_pegaExtensaoPorCodigo(ListaExtensao lista, int codigo) {
	ListaExtensao local;
    Extensao *extensao = new Extensao();

	for (local = lista; local != NULL; local = local->proximo) {
		*extensao = local->extensao;

        if (extensao->codigo == codigo) {
            return extensao;
        }
    }
    return NULL;
}

Extensao ExtensaoBO_pegaExtensaoPorNome(ListaExtensao lista,
        String nome, String tipo) {
	ListaExtensao local;
    Extensao extensao;

    if (String_comparar(tipo, Rotinas_lerStr(STR_TIPOLISTA_DIRETORIO))){
		extensao.bmp16 = diretorioBMP;
		extensao.bmp32 = diretorio32BMP;
    } else {
        if (ListaExtensao_conta(lista) > 0) {
			for (local = lista; local != NULL; local = local->proximo) {
				extensao = local->extensao;

                if (String_comparar(String_LowerCase(extensao.nome), 
					String_LowerCase(nome))) {
                    return extensao;
                }
            }
        }
        if (String_comparar(tipo, Rotinas_lerStr(STR_TIPOLISTA_ARQUIVO))) {
			extensao.bmp16 = arquivoBMP;
			extensao.bmp32 = arquivo32BMP;
        }
    }
    return extensao;
}

BOOL ExtensaoBO_ExportarExtensao(TipoExportarExtensao tipo,
        ListaExtensao listaExtensao) {
	ListaExtensao local;
    Extensao extensao;
	String sCaminho = String_iniciar("");
	String sImg16 = String_iniciar("");
	String sImg32 = String_iniciar("");
	String sExtensao = String_iniciar("");

    if (ListaExtensao_conta(listaExtensao) > 0) {
		sCaminho = String_concatenar(Rotinas_AppDirPath(), Rotinas_BARRA_INVERTIDA);

        if (tipo == teBMP) {
            sExtensao = String_concatenar(".", Rotinas_EXTENSAO_BMP);
        } else if (tipo == teICO) {
			sExtensao = String_concatenar(".", Rotinas_EXTENSAO_ICO);
        } else if (tipo == teGIF) {
			sExtensao = String_concatenar(".", Rotinas_EXTENSAO_GIF);
        } else if (tipo == teJPG) {
			sExtensao = String_concatenar(".", Rotinas_EXTENSAO_JPEG);
        } else if (tipo == tePNG) {
			sExtensao = String_concatenar(".", Rotinas_EXTENSAO_PNG);
        } else if (tipo == teTIF) {
			sExtensao = String_concatenar(".", Rotinas_EXTENSAO_TIFF);
        } else {
            sExtensao = String_copiar(".img");
        }

		for (local = listaExtensao; local != NULL; local = local->proximo) {
			extensao = local->extensao;

			sImg16 = String_concatenar(sCaminho, 3, extensao.nome.str, "16", sExtensao.str);
            if (Rotinas_FileExists(sImg16)) {
                Rotinas_DeleteFromFile(sImg16);
            }

			sImg32 = String_concatenar(sCaminho, 3, extensao.nome.str, "32", sExtensao.str);
            if (Rotinas_FileExists(sImg32)) {
                Rotinas_DeleteFromFile(sImg32);
            }

            switch (tipo) {
                case teBMP: {
                    //Rotinas_BlobSaveToFile(extensao.bmp16, 16, sImg16);
                    //Rotinas_BlobSaveToFile(extensao.bmp32, 16, sImg32);
                }
                break;
				/*
                case teICO: {
                    if (extensao.bmp16!=NULL) {
                        Rotinas_SaveToFile(
                                Rotinas_BmpParaImagem(extensao.bmp16,
                                Rotinas_EXTENSAO_ICO), sImg16);
                    }
                    if (extensao.bmp32!=NULL) {
                        Rotinas_SaveToFile(
                                Rotinas_BmpParaImagem(extensao.bmp32,
                                Rotinas_EXTENSAO_ICO), sImg32);
                    }
                }
                break;
                case teGIF: {
                    Rotinas_SaveToFile(extensao.getGif16(), sImg16);
                    Rotinas_SaveToFile(extensao.getGif32(), sImg32);
                }
                break;
                case teJPG: {
                    if (!extensao.bmp16.IsEmpty()) {
                        Rotinas_SaveToFile(
                                Rotinas_BmpParaImagem(extensao.bmp16,
                                Rotinas_EXTENSAO_JPEG), sImg16);
                    }
                    if (!extensao.bmp32.IsEmpty()) {
                        Rotinas_SaveToFile(
                                Rotinas_BmpParaImagem(extensao.bmp32,
                                Rotinas_EXTENSAO_JPEG), sImg32);
                    }
                }
                break;
                case tePNG: {
                    if (!extensao.bmp16.IsEmpty()) {
                        Rotinas_SaveToFile(
                                Rotinas_BmpParaImagem(extensao.bmp16,
                                Rotinas_EXTENSAO_PNG), sImg16);
                    }
                    if (!extensao.bmp32.IsEmpty()) {
                        Rotinas_SaveToFile(
                                Rotinas_BmpParaImagem(extensao.bmp32,
                                Rotinas_EXTENSAO_PNG), sImg32);
                    }
                }
                break;
                case teTIF: {
                    if (!extensao.bmp16.IsEmpty()) {
                        Rotinas_SaveToFile(
                                Rotinas_BmpParaImagem(extensao.bmp16,
                                Rotinas_EXTENSAO_TIFF), sImg16);
                    }
                    if (!extensao.bmp32.IsEmpty()) {
                        Rotinas_SaveToFile(
                                Rotinas_BmpParaImagem(extensao.bmp32,
                                Rotinas_EXTENSAO_TIFF), sImg32);
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

void ExtensaoBO_ImportarExtensao(String caminho,
        ListaExtensao listaExtensao) {
	
	String sArquivo = String_iniciar("");
	ListaString local;
	ListaString listaArquivos = ListaString_inicia();
	ListaString log = ListaString_inicia();
		
    if (DiretorioBO_carregarArquivos(caminho, listaArquivos)) {

		for (local = listaArquivos; local != NULL; local = local->proximo) {
			sArquivo = String_copiar(local->str);

			ExtensaoBO_SalvarExtensao(listaExtensao, Rotinas_ExtractFileName(sArquivo),
                    sArquivo, log);
        }
    }
	

}

void ExtensaoBO_ExtrairExtensao(String caminho, ListaExtensao listaExtensao) {
	
	String sArquivo = String_iniciar("");
	ListaString local;
	ListaString listaArquivos = ListaString_inicia();
	ListaString log = ListaString_inicia();

    if (DiretorioBO_carregarTodosArquivos(caminho, listaArquivos)) {
		for (local = listaArquivos; local != NULL; local = local->proximo) {
			sArquivo = String_copiar(local->str);

			ExtensaoBO_SalvarExtensao(listaExtensao, Rotinas_ExtractFileName(sArquivo),
                    sArquivo, log);
        }
    }
	
}
