#include "stdafx.h"

#include <Commdlg.h>
#include <shlobj.h>

#include "resource.h"
#include "EscolhaArquivo.h"
#include "hfsguardadir/comum/Rotinas.h"

String EscolhaArquivo_getTextoExtensao(String extensao) {
	if (String_comparar(String_LowerCase(extensao),"txt")) return String_iniciar(Rotinas_lerStr(STR_ESCOLHAARQUIVO_FILTROTXT));
	if (String_comparar(String_LowerCase(extensao),"csv")) return String_iniciar(Rotinas_lerStr(STR_ESCOLHAARQUIVO_FILTROCSV));
	if (String_comparar(String_LowerCase(extensao),"html")) return String_iniciar(Rotinas_lerStr(STR_ESCOLHAARQUIVO_FILTROHTML));
	if (String_comparar(String_LowerCase(extensao),"xml")) return String_iniciar(Rotinas_lerStr(STR_ESCOLHAARQUIVO_FILTROXML));
	if (String_comparar(String_LowerCase(extensao),"sql")) return String_iniciar(Rotinas_lerStr(STR_ESCOLHAARQUIVO_FILTROSQL));
	if (String_comparar(String_LowerCase(extensao),"bmp")) return String_iniciar(Rotinas_lerStr(STR_ESCOLHAARQUIVO_FILTROBMP));
	if (String_comparar(String_LowerCase(extensao),"ico")) return String_iniciar(Rotinas_lerStr(STR_ESCOLHAARQUIVO_FILTROICO));
	if (String_comparar(String_LowerCase(extensao),"jpg")) return String_iniciar(Rotinas_lerStr(STR_ESCOLHAARQUIVO_FILTROJPG));
	if (String_comparar(String_LowerCase(extensao),"gif")) return String_iniciar(Rotinas_lerStr(STR_ESCOLHAARQUIVO_FILTROGIF));
	if (String_comparar(String_LowerCase(extensao),"png")) return String_iniciar(Rotinas_lerStr(STR_ESCOLHAARQUIVO_FILTROPNG));
	if (String_comparar(String_LowerCase(extensao),"tif")) return String_iniciar(Rotinas_lerStr(STR_ESCOLHAARQUIVO_FILTROTIF));
	return String_iniciar(Rotinas_lerStr(STR_ESCOLHAARQUIVO_ACCEPTALLFILEFILTERTEXT));
}

/*
static int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{

	if (uMsg == BFFM_INITIALIZED)
	{
		std::string tmp = (const char *)lpData;
		std::cout << "path: " << tmp << std::endl;
		SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
	}

	return 0;
}
*/

String EscolhaArquivo_abrirDiretorio(HWND pai) {
	String diretorio = String_iniciar("");

	TCHAR path[MAX_PATH];

	WCHAR cCaminho[MAX_PATH];
	DWORD dwRet = GetCurrentDirectory(MAX_PATH, cCaminho);

	BROWSEINFO bi = { 0 };
	bi.lpszTitle = Rotinas_lerStr(STR_ESCOLHAARQUIVO_APPROVEBUTTONTEXT);
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
	//bi.lpfn = BrowseCallbackProc;
	bi.lParam = (LPARAM)cCaminho;

	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

	if (pidl != 0)
	{
		SHGetPathFromIDList(pidl, path);

		//free memory used
		IMalloc * imalloc = 0;
		if (SUCCEEDED(SHGetMalloc(&imalloc)))
		{
			imalloc->Free(pidl);
			imalloc->Release();
		}

		diretorio = String_copiar(path);
	}

	return diretorio;
}

String EscolhaArquivo_abrirArquivo(HWND pai) {
	String filtro = String_iniciar(Rotinas_lerStr(STR_ESCOLHAARQUIVO_ACCEPTALLFILEFILTERTEXT));
	filtro = String_concatenar(filtro, "\0*.*\0");
	
	return EscolhaArquivo_abrirArquivo(pai, String_iniciar(""), filtro);
}

String EscolhaArquivo_abrirArquivo(HWND pai, String arquivo, String extensao) {
//Rotinas_lerStr(STR_ESCOLHAARQUIVO_OPENBUTTONTEXT)

	String sarquivo;
	OPENFILENAME ofn;
	WCHAR szFile[TAM_MAX_STR];

	String filtro = EscolhaArquivo_getTextoExtensao(extensao);
	filtro = String_concatenar(filtro, "\0*.*\0");

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = filtro.wstr;
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	//if (ofn.lpstrFile != NULL && lstrlen(ofn.lpstrFile) > 0)
	if (GetOpenFileName(&ofn))
		sarquivo = String_iniciar(ofn.lpstrFile);
	else
		sarquivo = String_iniciar("");

	return sarquivo;
}

String EscolhaArquivo_salvarArquivo(HWND pai, String arquivo, String extensao) {
//Rotinas_lerStr(STR_ESCOLHAARQUIVO_SAVEBUTTONTEXT)

	OPENFILENAME ofn;

	String filtro = EscolhaArquivo_getTextoExtensao(extensao);
	filtro = String_concatenar(filtro, "\0*.*\0");

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = arquivo.wstr;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(arquivo.wstr);
	ofn.lpstrFilter = filtro.wstr;
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	//if (ofn.lpstrFile != NULL && lstrlen(ofn.lpstrFile) > 0)
	if (GetSaveFileName(&ofn))
		arquivo = String_iniciar(ofn.lpstrFile);
	else
		arquivo = String_iniciar("");

	return arquivo;
}
