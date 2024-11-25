#include "stdafx.h"
#include "resource.h"
#include "hfsguardadir\objetosgui\EscolhaArquivo.h"
#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosgui {

EscolhaArquivo::EscolhaArquivo()
{
}


EscolhaArquivo::~EscolhaArquivo()
{
}

CString EscolhaArquivo::getTextoExtensao(const CString &extensao) {
	CString ext = extensao;
	ext = Rotinas::LowerCase(ext);

	if (ext == "txt") return Rotinas::lerStr(STR_ESCOLHAARQUIVO_FILTROTXT);
	if (ext == "csv") return Rotinas::lerStr(STR_ESCOLHAARQUIVO_FILTROCSV);
	if (ext == "html") return Rotinas::lerStr(STR_ESCOLHAARQUIVO_FILTROHTML);
	if (ext == "xml") return Rotinas::lerStr(STR_ESCOLHAARQUIVO_FILTROXML);
	if (ext == "sql") return Rotinas::lerStr(STR_ESCOLHAARQUIVO_FILTROSQL);
	if (ext == "bmp") return Rotinas::lerStr(STR_ESCOLHAARQUIVO_FILTROBMP);
	if (ext == "ico") return Rotinas::lerStr(STR_ESCOLHAARQUIVO_FILTROICO);
	if (ext == "jpg") return Rotinas::lerStr(STR_ESCOLHAARQUIVO_FILTROJPG);
	if (ext == "gif") return Rotinas::lerStr(STR_ESCOLHAARQUIVO_FILTROGIF);
	if (ext == "png") return Rotinas::lerStr(STR_ESCOLHAARQUIVO_FILTROPNG);
	if (ext == "tif") return Rotinas::lerStr(STR_ESCOLHAARQUIVO_FILTROTIF);
	return Rotinas::lerStr(STR_ESCOLHAARQUIVO_ACCEPTALLFILEFILTERTEXT);
}

CString EscolhaArquivo::abrirDiretorio(CWnd *pai) {
	CString diretorio = _T(""), titulo;

	TCHAR path[MAX_PATH];
	WCHAR cCaminho[MAX_PATH];

	path[0] = '\0';	
	cCaminho[0] = '\0';

	DWORD dwRet = GetCurrentDirectory(MAX_PATH, cCaminho);

	BROWSEINFO bi = { 0 };
	titulo = Rotinas::lerStr(STR_ESCOLHAARQUIVO_APPROVEBUTTONTEXT);
	bi.lpszTitle = titulo.GetString();
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

		diretorio = path;
	}

	return diretorio;
}

CString EscolhaArquivo::abrirArquivo(CWnd *pai) {
	CString filtro = Rotinas::lerStr(STR_ESCOLHAARQUIVO_ACCEPTALLFILEFILTERTEXT);
	filtro += "\0*.*\0";

	return EscolhaArquivo::abrirArquivo(pai, _T(""), filtro);
}

CString EscolhaArquivo::abrirArquivo(CWnd *pai, const CString &arquivo, const CString &extensao) {
	//Rotinas_lerStr(STR_ESCOLHAARQUIVO_OPENBUTTONTEXT)

	CString sarquivo;
	OPENFILENAME ofn;
	WCHAR szFile[TAM_MAX_STR];

	CString filtro = EscolhaArquivo::getTextoExtensao(extensao);
	filtro += "\0*.*\0";

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = filtro.GetString();
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	//if (ofn.lpstrFile != NULL && lstrlen(ofn.lpstrFile) > 0)
	if (GetOpenFileName(&ofn))
		sarquivo = ofn.lpstrFile;
	else
		sarquivo = _T("");

	return sarquivo;
}

CString EscolhaArquivo::salvarArquivo(CWnd *pai, const CString &arquivo, const CString &extensao) {
	//Rotinas_lerStr(STR_ESCOLHAARQUIVO_SAVEBUTTONTEXT)

	CString sarquivo;
	OPENFILENAME ofn;

	CString filtro = EscolhaArquivo::getTextoExtensao(extensao);
	filtro += "\0*.*\0";

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = (LPWSTR)arquivo.GetString();
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(arquivo.GetString());
	ofn.lpstrFilter = filtro.GetString();
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	//if (ofn.lpstrFile != NULL && lstrlen(ofn.lpstrFile) > 0)
	if (GetSaveFileName(&ofn))
		sarquivo = ofn.lpstrFile;
	else
		sarquivo = _T("");

	return sarquivo;
}

}
}
