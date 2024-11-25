#include "stdafx.h"

#include <iostream>
#include <Gdiplusheaders.h>
#include <Gdiplus.h>

#include "HFSGuardaDiretorio.h"
#include "FrmPrincipal.h"
#include "resource.h"
#include "Rotinas.h"

using namespace hfsguardadir::objetos;

namespace hfsguardadir {

namespace comum {

Rotinas* Rotinas::instancia = NULL;

const CString Rotinas::HFSGUARDADIR = _T("HFSGuardaDir");
const CString Rotinas::FORMATO_DATA = _T("%d/%m/%Y");
const CString Rotinas::FORMATO_HORA = _T("%H:%M:%S");
const CString Rotinas::FORMATO_DATAHORA = _T("%d/%m/%Y %H:%M:%S");
const CString Rotinas::FORMATO_DHARQUIVO = _T("%Y-%m-%d_%H_%M_%S");
const CString Rotinas::EXTENSAO_BMP = _T("bmp");
const CString Rotinas::EXTENSAO_ICO = _T("ico");
const CString Rotinas::EXTENSAO_GIF = _T("gif");
const CString Rotinas::EXTENSAO_JPEG = _T("jpg");
const CString Rotinas::EXTENSAO_PNG = _T("png");
const CString Rotinas::EXTENSAO_TIFF = _T("tif");

sqlite3* dbConexao;

Rotinas::Rotinas()
{
	
}

Rotinas::Rotinas(Rotinas const&){

}

Rotinas& Rotinas::operator=(Rotinas const&){
    return *instancia;
}

Rotinas* Rotinas::getInstancia() {
    if (!instancia) {
        instancia = new Rotinas();
    }
    return instancia;
}

char* Rotinas::StringToChar(const CString &texto) {
	char* valor = (char*) malloc(TAM_MAX_STR);

	valor[0] = '\0';
	strcpy_s(valor, TAM_MAX_STR, CT2CA(texto));

	return valor;
}

LPWSTR Rotinas::NewStr(INT ntam)
{
	LPWSTR strlocal;

	strlocal = LPWSTR(GlobalAlloc(GPTR, ntam));
	strlocal[0] = '\0';

	return strlocal;
}

LPWSTR Rotinas::NewStr()
{
	return NewStr(TAM_MAX_STR);
}

CString Rotinas::lerStr(UINT nId)
{
	CString sValor;
	LPWSTR sTemp;

	sTemp = NewStr();
	LoadString(AfxGetApp()->m_hInstance, nId, sTemp, TAM_MAX_STR);
	sValor = sTemp;

	return sValor;
}

CString Rotinas::retTexto(CWnd* cwnd)
{
	LPWSTR sTemp;

	sTemp = NewStr();
	cwnd->GetWindowText(sTemp, TAM_MAX_STR);

	return sTemp;
}

BOOL Rotinas::VerificaInstancia(LPTSTR sNomeClasse, LPTSTR sNomeJanela)
{
	CWnd *pWndAnterior, *pWndFilha;

	if (pWndAnterior = CWnd::FindWindow(sNomeClasse, sNomeJanela))
	{
		pWndFilha = pWndAnterior->GetLastActivePopup();

		AfxMessageBox(lerStr(STR_APPEXEC),
			MB_ICONEXCLAMATION | MB_OK, 0);

		if (pWndAnterior->IsIconic())
			pWndAnterior->ShowWindow(SW_RESTORE);

		pWndFilha->SetForegroundWindow();

		return FALSE;
	}
	return TRUE;
}

VOID Rotinas::criaImageLists(CImageList *imageList16, CImageList *imageList32) {
	imageList16->Create(16, 16, ILC_COLOR8 | ILC_MASK, 3, 0);
	imageList32->Create(32, 32, ILC_COLOR8 | ILC_MASK, 3, 0);
		
	CBitmap *hbmDIRETORIO, *hbmARQUIVO, *hbmDIRABERTO, *mascara = NULL;
	hbmDIRETORIO = new CBitmap();
	hbmARQUIVO = new CBitmap();
	hbmDIRABERTO = new CBitmap();

	hbmDIRETORIO->LoadBitmapW(MAKEINTRESOURCE(DIRETORIO));
	hbmARQUIVO->LoadBitmapW(MAKEINTRESOURCE(ARQUIVO));
	hbmDIRABERTO->LoadBitmapW(MAKEINTRESOURCE(DIRABERTO));
	
	imageList16->Add(hbmDIRETORIO, mascara);
	imageList16->Add(hbmARQUIVO, mascara);
	imageList16->Add(hbmDIRABERTO, mascara);

	CBitmap *hbmDIRETORIO32, *hbmARQUIVO32, *hbmDIRABERTO32;
	hbmDIRETORIO32 = new CBitmap();
	hbmARQUIVO32 = new CBitmap(); 
	hbmDIRABERTO32 = new CBitmap();

	hbmDIRETORIO32->LoadBitmapW(MAKEINTRESOURCE(DIRETORIO32));
	hbmARQUIVO32->LoadBitmapW(MAKEINTRESOURCE(ARQUIVO32));
	hbmDIRABERTO32->LoadBitmapW(MAKEINTRESOURCE(DIRABERTO32));
	
	imageList32->Add(hbmDIRETORIO32, mascara);
	imageList32->Add(hbmARQUIVO32, mascara);
	imageList32->Add(hbmDIRABERTO32, mascara);

	DeleteObject(hbmDIRETORIO);
	DeleteObject(hbmARQUIVO);
	DeleteObject(hbmDIRABERTO);
	DeleteObject(hbmDIRETORIO32);
	DeleteObject(hbmARQUIVO32);
	DeleteObject(hbmDIRABERTO32);
	DeleteObject(mascara);

	delete hbmDIRETORIO;
	delete hbmARQUIVO;
	delete hbmDIRABERTO;
	delete hbmDIRETORIO32;
	delete hbmARQUIVO32;
	delete hbmDIRABERTO32;
	delete mascara;
}

CTime Rotinas::DataHoraNow() {
	SYSTEMTIME sTempo;

	//GetSystemTime(&sTempo);
	GetLocalTime(&sTempo);

	return CTime(sTempo);
}

CString Rotinas::formataDate(const CString &formato, const CTime &dt) {
	CString ds = _T("");

	ds = dt.Format(formato);

	return ds;
}

CTime Rotinas::StringToDate(const CString &sData) {
	CTime *data;
	CString texto = sData;
	CString parte;
	int pos1 = 0, pos2 = 0, ano = 0, mes = 0, dia = 0;
	int hora = 0, min = 0, seg = 0;

	if (Rotinas::Trim(texto).GetLength() > 0) {

		if (sData.Find('/') > 0) {
			pos1 = sData.Find('/');
			parte = texto.Mid(pos1-2, pos1);
			dia = StrToInt(parte);

			pos2 = sData.Find('/', pos1+1);
			parte = texto.Mid(pos1+1, pos2-pos1-1);
			mes = StrToInt(parte);

			parte = texto.Mid(pos2+1, 4);
			ano = StrToInt(parte);

			if (ano < 1970)
				ano = 1970;
		}

		if (sData.Find(':') > 0) {
			pos1 = sData.Find(':');
			parte = texto.Mid(pos1-2, 2);
			hora = StrToInt(parte);

			pos2 = sData.Find(':', pos1+1);
			parte = texto.Mid(pos1+1, pos2-pos1-1);
			min = StrToInt(parte);

			parte = texto.Mid(pos2+1, 2);
			seg = StrToInt(parte);
		}
		data = new CTime(ano, mes, dia, hora, min, seg);
	}
	return *data;
}

CEdit* Rotinas::criaEdit(CWnd pai, INT id, LPTSTR sTexto,
	INT x, INT y, INT largura,
	BOOL bHabilitado, INT nMaxTam, BOOL bComSenha, BOOL bSoNumero)
{
	CEdit* edit;
	DWORD nEstilo;
	RECT rect;

	nEstilo = WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_BORDER | ES_LEFT;
	if (bHabilitado == FALSE) nEstilo += WS_DISABLED;
	if (bComSenha) nEstilo += ES_PASSWORD;
	if (bSoNumero) nEstilo += ES_NUMBER;

	rect.left = x;
	rect.top = y;
	rect.right = largura;
	rect.bottom = rect.top + 21;

	edit = new CEdit();
	edit->Create(nEstilo, rect, &pai, id);
	edit->SetWindowTextW(sTexto);
	CFont* fonte = new CFont();
	fonte->CreateStockObject(DEFAULT_GUI_FONT);
	edit->SetFont(fonte);
	edit->SetLimitText(nMaxTam);

	return edit;
}

sqlite3* Rotinas::getConexao() {
	return dbConexao;
}

BOOL Rotinas::BancoConectar(const CString &sFonteDeDados)
{
	const char* fonte = StringToChar(sFonteDeDados);

	const int ret = sqlite3_open_v2(fonte, &dbConexao, SQLITE_OPEN_READWRITE, NULL);
	if (SQLITE_OK != ret)
	{
		BancoMostrarErro("Rotinas_BancoConectar");
		sqlite3_close(dbConexao);
		return FALSE;
	}
	return TRUE;
}

VOID Rotinas::BancoDesconectar()
{
	const int ret = sqlite3_close(dbConexao);
	(void)ret;
}

VOID Rotinas::BancoMostrarErro(const char* titulo) {
	int errcode = sqlite3_errcode(dbConexao);
	//int exterrcode = sqlite3_extended_errcode(dbConexao);
	char* errmsg = (char*)sqlite3_errmsg(dbConexao);
	//const char* errstr = sqlite3_errstr(dbConexao);

	CString sErro = CString(titulo);
		
	sErro.Format(_T("ERRO: %d - %s"), errcode, CString(errmsg));
	OutputDebugString(sErro);
	MessageBox(NULL, sErro, _T("Banco Mostrar Erro"), MB_ICONERROR | MB_OK);
}

INT Rotinas::BancoExec(const CString &sSQL)
{
	const char* sql = Rotinas::StringToChar(sSQL);
	const int ret = sqlite3_exec(dbConexao, sql, NULL, NULL, NULL);
	if (SQLITE_OK != ret)
	{
		BancoMostrarErro("Rotinas_BancoExec");
	}
	return sqlite3_changes(dbConexao);
}

BOOL Rotinas::BancoPasso(sqlite3_stmt* pstmt) {
	BOOL mbOk = FALSE;

	const int ret = sqlite3_step(pstmt);

	if (SQLITE_ROW == ret) {
		mbOk = TRUE;
	}
	else if (SQLITE_DONE == ret) {
		mbOk = FALSE;
	}
	else {
		BancoMostrarErro("Rotinas_BancoPasso");
		mbOk = FALSE;
	}

	return mbOk;
}

INT Rotinas::BancoExecPasso(sqlite3_stmt* pstmt, int ret, const char* titulo) {
	int res = 0;

	if (ret == SQLITE_OK) {
		if (sqlite3_step(pstmt) == SQLITE_DONE) {
			res = sqlite3_changes(getConexao());
		}
	}
	else {
		BancoMostrarErro(titulo);
	}

	return res;
}

CString Rotinas::Trim(const CString &texto) {
	CString rtexto = texto;
	return rtexto.Trim();
}

CString Rotinas::LowerCase(const CString &texto){
	CString rtexto = texto;
	return rtexto.MakeLower();
}

CString Rotinas::UpperCase(const CString &texto){
	CString rtexto = texto;
	return rtexto.MakeUpper();
}

int Rotinas::LastIndexOf(const CString &texto, const CString &subtexto)
{
	int inicio = texto.Find(subtexto.GetString());

	if (inicio >= 0)
	{
		while (inicio < texto.GetLength())
		{
			int indice = texto.Find(subtexto.GetString(), inicio + 1);
			if (indice >= 0)
				inicio = indice;
			else
				break;
		}
	}

	return inicio;
}

int Rotinas::LastDelimiter(const CString &subtexto, const CString &texto) {
	int npos = -1;
	int retorno = texto.Find(subtexto);

	if (retorno != -1) {
		retorno++;
		npos = retorno;

		do {
			retorno = texto.Find(subtexto, npos);
			if (retorno != -1) {
				npos = retorno + 1;
			}
				
		} while (retorno != -1);
	}
	else {
		npos = retorno;
	}

	return npos;
}

int Rotinas::LastDelimiter(char subtexto, const CString &texto) {
    return texto.ReverseFind(subtexto) + 1;
}

int Rotinas::Pos(const CString &subtexto, const CString &texto) {
	int npos = texto.FindOneOf(subtexto.GetString()) + 1;
	return npos;
}

int Rotinas::Pos(LPCWSTR subtexto, const CString &texto) {
	int npos = texto.FindOneOf(subtexto) + 1;
	return npos;
}

bool Rotinas::StartsStr(const CString &subtexto, const CString &texto) {
    return (texto.FindOneOf(subtexto.GetString()) == 0);
}

bool Rotinas::ContainsStr(const CString &texto, const CString &subtexto) {
	return (texto.Find(subtexto.GetString()) >= 0);
}

bool Rotinas::EndsStr(const CString &texto, const CString &subtexto) {
	return (LastDelimiter(subtexto, texto) > 0);
}

CString Rotinas::SubString(const CString &texto, int inicio, int tamanho) {
    if ((inicio + tamanho - 1) > texto.GetLength()) {
        tamanho = texto.GetLength();
    } else {
        tamanho = inicio + tamanho - 1;
    }
    return texto.Mid(inicio - 1, tamanho);
}

CString Rotinas::StringReplaceAll(const CString &texto, const CString &velho,
        const CString &novo){
    CString txt = texto;

	txt.Replace(velho, novo);

	return txt;
}

CString Rotinas::QuotedStr(const CString &texto){
    return _T("'") + texto + _T("'");
}

CString Rotinas::QuotedStr(char texto){
    return _T("'") + CString(texto) + _T("'");
}

CString Rotinas::FromInt(int valor) {
	CString texto;

	texto.Format(_T("%d"), valor);

	return texto;
}

CString Rotinas::FromULong(unsigned long valor) {
    CString texto;

    //texto = texto.sprintf("%lu", valor);
    texto.Format(_T("%lu"), valor);

    return texto;
}

CString Rotinas::FromLongLong(long long valor) {
	CString texto;

	texto.Format(_T("%lld"), valor);

	return texto;
}

CString Rotinas::FromLongDouble(long double valor) {
    CString texto;

    //texto = CString::sprintf("%4.2Lf", valor);
	texto.Format(_T("%4.2Lf"), valor);

    return texto;
}

int Rotinas::ToInt(const CString& valor) {
	return _tstoi(valor);
}

long Rotinas::ToLong(const CString& valor) {
	return _tstol(valor);
}

long long Rotinas::ToLongLong(const CString& valor) {
	return _tstoll(valor);
}

unsigned long Rotinas::ToULong(const CString& valor) {
	return _tstol(valor);
}

unsigned long long Rotinas::ToULongLong(const CString& valor) {
	return _tstoll(valor);
}
VOID Rotinas::copiaBitmap(CWnd pai, INT idBMP, RECT rc)
{
	CDC *hDC;
	CDC *hDCMem;
	PAINTSTRUCT ps;
	CBitmap *hBMP;
	
	hDC = pai.BeginPaint(&ps);
	hDCMem = new CDC();
	hDC->CreateCompatibleDC(hDCMem);
	if (hDCMem != NULL)
	{
		hBMP = new CBitmap();
		hBMP->LoadBitmapW(MAKEINTRESOURCE(idBMP));
		hDCMem->SelectObject(hBMP);
		hDC->BitBlt(rc.left, rc.top, rc.right, rc.bottom, hDCMem, 0, 0, SRCCOPY);
		hDCMem->DeleteDC();
	}
	pai.EndPaint(&ps);
}

HBITMAP Rotinas::BitmapToHBitmap(const BITMAP bmp) {
	HDC hDC = GetDC(NULL);
	HDC hDCMem = CreateCompatibleDC(hDC);
	HBITMAP hBMP = CreateBitmapIndirect(&bmp);
	SelectObject(hDCMem, hBMP);
	return hBMP;
}

void Rotinas::setBarraProgresso(CProgressCtrl *pb, int nMin, int nMax, int nPasso) {
	int nPosicao = 0;

	pb->SetRange32(nMin, nMax);
	pb->SetStep(nPasso);
	pb->SetPos(nPosicao);
}

bool Rotinas::criarVisao(const CString &visao) {
	CString sSQL;

	sSQL = _T("create view ") + visao + _T(" as ") \
		"SELECT d.aba,d.cod,d.ordem,d.coddirpai,d.nome,d.tam,d.tipo,d.modificado," \
		"d.atributos,d.caminho" \
		",(select nome as nomeaba from Abas where cod=d.aba) as nomeaba" \
		",(select nome as nomepai from Diretorios where cod=d.cod " \
		"  and ordem=d.coddirpai and aba=d.aba) as nomepai" \
		",(select caminho as caminhopai from Diretorios where cod=d.cod " \
		" and ordem=d.coddirpai and aba=d.aba) as caminhopai " \
		"FROM Diretorios d ";

	if (visao == "consultadirpai")
		sSQL += "where d.tipo='D' and d.coddirpai = 0";
	else if (visao == "consultadirfilho")
		sSQL += "where d.tipo='D' and d.coddirpai > 0";
	
	return (Rotinas::getInstancia()->BancoExec(sSQL) > 0);
}

CString Rotinas::MontaTamanhoBig(long double nTam) {
	long long nUmKilo, nUmMega, nUmGiga, nUmTera, nUmPeta;

	nUmKilo = 1024;
	nUmMega = nUmKilo * nUmKilo;
	nUmGiga = nUmMega * nUmKilo;
	nUmTera = nUmGiga * nUmKilo;
	nUmPeta = nUmTera * nUmKilo;

	if (nTam < nUmKilo) {
		return FromLongDouble(nTam) + _T(" Byte(s)");
	}
	else if (nTam > nUmKilo && nTam < nUmMega) {
		nTam = nTam / nUmKilo;
		return FromLongDouble(nTam) + _T(" KByte(s)");
	}
	else if (nTam > nUmMega && nTam < nUmGiga) {
		nTam = nTam / nUmMega;
		return FromLongDouble(nTam) + _T(" MByte(s)");
	}
	else if (nTam > nUmGiga && nTam < nUmTera) {
		nTam = nTam / nUmGiga;
		return FromLongDouble(nTam) + _T(" GByte(s)");
	}
	else if (nTam > nUmTera && nTam < nUmPeta) {
		nTam = nTam / nUmTera;
		return FromLongDouble(nTam) + _T(" TByte(s)");
	}
	else {
		nTam = nTam / nUmPeta;
		return FromLongDouble(nTam) + _T(" PByte(s)");
	}
}

CString Rotinas::MontaTamanho(long long nTam) {
	if (nTam > 0) {
		return MontaTamanhoBig((long double)nTam);
	}
	else {
		return _T("");
	}
}

CString Rotinas::testaNull(const char* res) {
    return (res == NULL ? _T("") : Rotinas::Trim(CString(res)));
}

CString Rotinas::trocaSeparador(const CString &texto) {
    CString res = _T(""), txt = texto;
    if (texto.GetLength() > 0) {
		txt.Replace(BARRA_NORMAL, BARRA_INVERTIDA);
		res = txt;
    }
    return res;
}

CString Rotinas::AppDirPath() {
	TCHAR cCaminho[MAX_PATH];
	GetModuleFileName(AfxGetApp()->m_hInstance, cCaminho, MAX_PATH);

	CString sCaminho(cCaminho);

	return sCaminho;
}

CString Rotinas::AppDirName() {
	TCHAR cCaminho[MAX_PATH];
	GetModuleFileName(AfxGetApp()->m_hInstance, cCaminho, MAX_PATH);

	CString sCaminho(cCaminho);
	sCaminho = sCaminho.Left(sCaminho.ReverseFind(_T('\\'))+1);

	return sCaminho;
}

CString Rotinas::AppFileName() {
	TCHAR cNome[MAX_PATH];
	GetModuleFileName(AfxGetApp()->m_hInstance, cNome, MAX_PATH);

	CString sNome(cNome);
	int pos = LastIndexOf(sNome, _T("\\")) + 2;
	sNome = SubString(sNome, pos, sNome.GetLength());

	return sNome;
}

CString Rotinas::ExtractFilePath(const CString &sCaminho) {
	CString caminho(sCaminho);
	caminho = caminho.Left(caminho.ReverseFind(_T('\\')) + 1);

	return caminho;
}

CString Rotinas::ExtractFileName(const CString &sCaminho) {
    CString retorno;

	CFile info(sCaminho, CFile::modeRead);
	retorno = info.GetFileName();

    return retorno;
}

bool Rotinas::FileExists(const CString &sNomeArquivo) {
	DWORD atributos = GetFileAttributes(sNomeArquivo.GetString());

	if (atributos == INVALID_FILE_ATTRIBUTES) {
		return false;
	}
	if (atributos & FILE_ATTRIBUTE_DIRECTORY) {
		return false;
	}
	if (atributos & FILE_ATTRIBUTE_ARCHIVE) {
		return true;
	}

	return false;
}

bool Rotinas::DirectoryExists(const CString &sNomeArquivo) {
	DWORD atributos = GetFileAttributes(sNomeArquivo.GetString());

	if (atributos == INVALID_FILE_ATTRIBUTES) {
		return false;
	}
	if (atributos & FILE_ATTRIBUTE_DIRECTORY) {
		return true;
	}
	if (atributos & FILE_ATTRIBUTE_ARCHIVE) {
		return false;
	}

	return false;
}

bool Rotinas::DeleteFromFile(const CString &sNomeArquivo) {
	//return DeleteFile(sNomeArquivo);

	try	{
		CFile::Remove(sNomeArquivo.GetString());
	} 
	catch (CFileException* pEx) {
		//TRACE(_T("Arquivo nao pode ser removido\n"), sNomeArquivo.GetString());		
		LPTSTR erro[255];
		pEx->GetErrorMessage(*erro, 255);
		pEx->Delete();
		return false;
	}
	return true;
}

Arquivo Rotinas::FileInfoToArquivo(const CFileFind &finder) {
	CString sAtributos = _T("");
	Arquivo arquivo;
	CTime modificado;
	
	arquivo.setNome(finder.GetFileName());
	arquivo.setTamanho(finder.GetLength());
	if (finder.GetLastWriteTime(modificado)) {
		arquivo.setModificado(modificado);
	}
	else {
		arquivo.setModificado(CTime::GetCurrentTime());
	}
	
	if (finder.IsReadOnly()) sAtributos += "[ROL]";
	if (finder.IsHidden()) sAtributos += "[HID]";
	if (finder.IsSystem()) sAtributos += "[SYS]";
	if (finder.IsDirectory()) sAtributos += "[DIR]";
	if (finder.IsArchived()) sAtributos += "[ARQ]";
		
	arquivo.setAtributos(sAtributos);

	return arquivo;
}

void Rotinas::SaveToFile(const CByteArray &imagem, const CString &sNomeArquivo) {
	CFile cfile;

	try {
		cfile.Open(sNomeArquivo.GetString(), CFile::modeCreate |
			CFile::modeWrite);
		//char pbufWrite[100];
		//memset(pbufWrite, 'a', sizeof(pbufWrite));				
		cfile.Write(imagem.GetData(), imagem.GetSize());
		cfile.Flush();
		cfile.Close();
	}
	catch (CFileException* pEx) {
		//TRACE(_T("Arquivo nao pode ser salvo\n"), sNomeArquivo.GetString());		
		//pEx->GetErrorMessage()
		pEx->Delete();
	}
}

CByteArray* Rotinas::LoadFromFile(const CString &sNomeArquivo) {
    CByteArray *imagem;
	CFile cfile;

	imagem = new CByteArray();
	try {
		cfile.Open(sNomeArquivo.GetString(), CFile::modeRead);
		//char pbufRead[100];
		//cfile.Read(pbufRead, sizeof(pbufRead));
		cfile.Read(imagem->GetData(), imagem->GetSize());
		cfile.Close();
	}
	catch (CFileException* pEx) {
		//TRACE(_T("Arquivo nao pode ser lido\n"), sNomeArquivo.GetString());		
		//pEx->GetErrorMessage()
		pEx->Delete();
	}

    return imagem;
}

CString Rotinas::getRecurso(const CString &chave) {
	if (chave == "HFSGuardaDir.ValidaJavaVersao") return _T("Esta vers\u00e3o do JAVA n\u00e3o \u00e9 suportada pelo programa.");
	if (chave == "HFSGuardaDir.ErroInicial") return _T("Ocorreu um erro no aplicativo!");
	if (chave == "HFSGuardaDir.ValidaArquivoConf") return _T("Arquivo de configura\u00e7\u00e3o n\u00e3o existe!\nAs configura\u00e7\u00f5es padr\u00e3o ser\u00e3o usadas!");

	if (chave == "Tabela.nome") return _T("Nome");
	if (chave == "Tabela.tamanho") return _T("Tamanho");
	if (chave == "Tabela.tipo") return _T("Tipo");
	if (chave == "Tabela.modificado") return _T("Modificado");
	if (chave == "Tabela.atributos") return _T("Atributos");
	if (chave == "Tabela.caminho") return _T("Caminho");
	if (chave == "Tabela.aba") return _T("Aba");

	if (chave == "Aba.codigo") return _T("C\u00f3digo:");
	if (chave == "Aba.nome") return _T("Nome:");

	if (chave == "Tipo.codigo") return _T("C\u00f3digo:");
	if (chave == "Tipo.nome") return _T("Nome:");

	if (chave == "TipoLista.arquivo") return _T("Arquivo");
	if (chave == "TipoLista.diretorio") return _T("Diret\u00f3rio");

	if (chave == "ConexaoParams.nome") return _T("Nome:");
	if (chave == "ConexaoParams.driver") return _T("Driver:");
	if (chave == "ConexaoParams.url") return _T("URL:");
	if (chave == "ConexaoParams.login") return _T("Login:");
	if (chave == "ConexaoParams.senha") return _T("Senha:");

	if (chave == "Parametro.desktop") return _T("Desktop:");
	if (chave == "Parametro.javaVersao") return _T("Java Vers\u00e3o:");
	if (chave == "Parametro.diretorioUsuario") return _T("Diret\u00f3rio do usu\u00e1rio:");
	if (chave == "Parametro.diretorioSistema") return _T("Diret\u00f3rio do sistema:");
	if (chave == "Parametro.arquivoConfiguracao") return _T("Arquivo de configura\u00e7\u00e3o:");
	if (chave == "Parametro.lookAndFeel") return _T("lookAndFeel:");
	if (chave == "Parametro.localidadeLingua") return _T("L\u00edngua:");
	if (chave == "Parametro.localidadePais") return _T("Pa\u00eds:");
	if (chave == "Parametro.versao") return _T("Vers\u00e3o:");

	if (chave == "Diretorio.aba") return _T("Aba:");
	if (chave == "Diretorio.codigo") return _T("C\u00f3digo:");
	if (chave == "Diretorio.ordem") return _T("Ordem:");
	if (chave == "Diretorio.nome") return _T("Nome:");
	if (chave == "Diretorio.tamanho") return _T("Tamanho:");
	if (chave == "Diretorio.tipo") return _T("Tipo:");
	if (chave == "Diretorio.modificado") return _T("Modificado:");
	if (chave == "Diretorio.atributos") return _T("Atributos:");
	if (chave == "Diretorio.codDirPai") return _T("C\u00f3digo Diret\u00f3rio Pai:");
	if (chave == "Diretorio.caminho") return _T("Caminho:");

	if (chave == "Extensao.codigo") return _T("C\u00f3digo:");
	if (chave == "Extensao.nome") return _T("Extens\u00e3o:");
	if (chave == "Extensao.icone") return _T("\u00cdcone:");
	if (chave == "Extensao.arquivo") return _T("arquivo(file)");
	if (chave == "Extensao.diretorio") return _T("diretorio(directory)");
	if (chave == "Extensao.zip") return _T(".zip");

	if (chave == "FrmPrincipal.titulo") return _T("HFSGuardaDiretorio 2.0 - Catalogador de Diret\u00f3rios");
	if (chave == "FrmPrincipal.barraStatus1") return _T("Quantidade Total: , Tamanho Total:");
	if (chave == "FrmPrincipal.btnImportarDiretorio") return _T("Importar Diret\u00f3rio");
	if (chave == "FrmPrincipal.btnPesquisa") return _T("Pesquisar");
	if (chave == "FrmPrincipal.Aba1") return _T("DISCO1");
	if (chave == "FrmPrincipal.menuAba") return _T("Aba");
	if (chave == "FrmPrincipal.menuIncluirNovaAba") return _T("Incluir Nova Aba");
	if (chave == "FrmPrincipal.menuDiretorio") return _T("Diret\u00f3rio");
	if (chave == "FrmPrincipal.menuAlterarNomeAbaAtiva") return _T("Alterar Nome da Aba Ativa");
	if (chave == "FrmPrincipal.menuExcluirAbaAtiva") return _T("Excluir Aba Ativa");
	if (chave == "FrmPrincipal.menuImportarDiretorio") return _T("Importar Diret\u00f3rio");
	if (chave == "FrmPrincipal.menuImportarSubDiretorios") return _T("Importar SubDiret\u00f3rios");
	if (chave == "FrmPrincipal.menuCompararDiretorios") return _T("Comparar Diret\u00f3rios");
	if (chave == "FrmPrincipal.menuCadastrarExtensaoArquivo") return _T("Cadastrar Extens\u00e3o de Arquivo");
	if (chave == "FrmPrincipal.menuExpandirDiretorios") return _T("Expandir Diret\u00f3rios");
	if (chave == "FrmPrincipal.menuColapsarDiretorios") return _T("Colapsar Diret\u00f3rios");
	if (chave == "FrmPrincipal.menuExportarDiretoriosAbaAtiva") return _T("Exportar Diret\u00f3rios da Aba Ativa");
	if (chave == "FrmPrincipal.menuTXT") return _T("TXT");
	if (chave == "FrmPrincipal.menuCSV") return _T("CSV");
	if (chave == "FrmPrincipal.menuHTML") return _T("HTML");
	if (chave == "FrmPrincipal.menuXML") return _T("XML");
	if (chave == "FrmPrincipal.menuSQL") return _T("SQL");
	if (chave == "FrmPrincipal.menuImportarDiretoriosViaXML") return _T("Importar Diret\u00f3rios Via XML");
	if (chave == "FrmPrincipal.menuGravarLogImportacao") return _T("Gravar Log da Importa\u00e7\u00e3o");
	if (chave == "FrmPrincipal.menuVisao") return _T("Vis\u00e3o");
	if (chave == "FrmPrincipal.menuMostrarOcultarArvoreDirAbaAtiva") return _T("Mostrar/Ocultar \u00c1rvore de diret\u00f3rios da Aba Ativa");
	if (chave == "FrmPrincipal.menuMostrarOcultarListaItensPesquisados") return _T("Mostrar/Ocultar lista de itens pesquisados");
	if (chave == "FrmPrincipal.menuSobre") return _T("Sobre");
	if (chave == "FrmPrincipal.TamMaxPesquisa") return _T("A pesquisa s\u00f3 \u00e9 feita com pelo menos 2 caracteres!");
	if (chave == "FrmPrincipal.DigitaNomeDiretorio") return _T("Este diret\u00f3rio n\u00e3o possui um nome.\nDigite o nome do diret\u00f3rio!");
	if (chave == "FrmPrincipal.ValidaNomeDiretorio") return _T("Nenhum nome de diret\u00f3rio informado!");
	if (chave == "FrmPrincipal.ErroSalvarArquivo") return _T("Ocorreu um erro ao salvar o arquivo.");
	if (chave == "FrmPrincipal.SucessoExportar") return _T("Exporta\u00e7\u00e3o realizada com sucesso!");
	if (chave == "FrmPrincipal.ExcluirDiretorioSelecionado") return _T("Tem Certeza, que voc\u00ea deseja excluir este diret\u00f3rio, isto implicar\u00e1 na destrui\u00e7\u00e3o de todos os seus items catalogados?");
	if (chave == "FrmPrincipal.ImportacaoNaoRealizada") return _T("Importa\u00e7\u00e3o n\u00e3o realizada!");
	if (chave == "FrmPrincipal.DiretorioExisteCatalogo") return _T("Este diret\u00f3rio j\u00e1 existe no cat\u00e1logo!");
	if (chave == "FrmPrincipal.ImportacaoRealizada") return _T("Importa\u00e7\u00e3o realizada com sucesso!");
	if (chave == "FrmPrincipal.ErroAbrirDir") return _T("Um erro ocorreu. Nenhum diret\u00f3rio foi escolhido.");
	if (chave == "FrmPrincipal.DirImportacaoSucesso") return _T("Importa\u00e7\u00e3o do(s) diret\u00f3rio(s) realizada com sucesso!");
	if (chave == "FrmPrincipal.DigitaIncluirNovaAba") return _T("Digite o Nome da Nova Aba?");
	if (chave == "FrmPrincipal.DigitaAlterarNomeAba") return _T("Digite o Novo Nome da Aba Ativa?");
	if (chave == "FrmPrincipal.ConfirmaExcluirAba") return _T("Tem Certeza, que voc\u00ea deseja excluir esta aba, \nisto implicar\u00e1 na destrui\u00e7\u00e3o de todos os seus itens catalogados?");
	if (chave == "FrmPrincipal.ValidaExcluirAba") return _T("A primeira Aba n\u00e3o pode ser exclu\u00edda!");
	if (chave == "FrmPrincipal.menuSobreCatalogador") return _T("Sobre o Catalogador");
	if (chave == "FrmPrincipal.menuIdioma") return _T("Idioma");
	if (chave == "FrmPrincipal.menuPortugues") return _T("Portugu\u00eas [Portuguese]");
	if (chave == "FrmPrincipal.menuIngles") return _T("Ingl\u00eas [English]");
	if (chave == "FrmPrincipal.menuEspanhol") return _T("Espanhol [Spanish]");
	if (chave == "FrmPrincipal.menuFrances") return _T("Franc\u00eas [French]");
	if (chave == "FrmPrincipal.menuItaliano") return _T("Italiano [Italian]");
	if (chave == "FrmPrincipal.menuAlemao") return _T("Alem\u00e3o [German]");
	if (chave == "FrmPrincipal.menuJapones") return _T("Japon\u00eas [Japanese]");
	if (chave == "FrmPrincipal.menuCoreano") return _T("Coreano [Korean]");
	if (chave == "FrmPrincipal.menuChinesTradicional") return _T("Chin\u00eas Tradicional [Traditional Chinese]");
	if (chave == "FrmPrincipal.menuExcluirDiretorioSelecionado") return _T("Excluir Diret\u00f3rio Selecionado");
	if (chave == "FrmPrincipal.menuInformacoesDiretorioArquivo") return _T("Informa\u00e7\u00f5es do Diret\u00f3rio / Arquivo");

	if (chave == "FrmSobre.titulo") return _T("Sobre o Catalogador");
	if (chave == "FrmSobre.label1") return _T("HFSGuardaDir 2.0 - Catalogador de Diret\u00f3rios");
	if (chave == "FrmSobre.label2") return _T("Desenvolvido em Java com Swing, Vers\u00e3o: 2.0");
	if (chave == "FrmSobre.label3") return _T("Por Henrique Figueiredo de Souza");
	if (chave == "FrmSobre.label4") return _T("Todos os direitos reservados, 2015");
	if (chave == "FrmSobre.Propriedade") return _T("Propriedade");
	if (chave == "FrmSobre.Valor") return _T("Valor");

	if (chave == "FrmSplash.label1") return _T("HFSGuardaDiretorio 2.0");
	if (chave == "FrmSplash.label2") return _T("Catalogador de Diret\u00f3rios");

	if (chave == "FrmCompararDiretorio.titulo") return _T("Comparar Diret\u00f3rios");
	if (chave == "FrmCompararDiretorio.btnCompararDiretorios") return _T("Comparar Diret\u00f3rios");
	if (chave == "FrmCompararDiretorio.btnSalvarLog") return _T("Salvar Log");
	if (chave == "FrmCompararDiretorio.barraStatus1") return _T("Total de diferen\u00e7as encontradas:");
	if (chave == "FrmCompararDiretorio.panelDiretorio1") return _T("Diret\u00f3rio 1");
	if (chave == "FrmCompararDiretorio.labDiferencasEncontradas") return _T("Diferen\u00e7as Encontradas");
	if (chave == "FrmCompararDiretorio.panelDiretorio2") return _T("Diret\u00f3rio 2");
	if (chave == "FrmCompararDiretorio.NenhumaDiferencaEncontrada") return _T("Nenhuma diferen\u00e7a encontrada!");
	if (chave == "FrmCompararDiretorio.DiretoriosNaoSelecionados") return _T("Diret\u00f3rios n\u00e3o selecionados!");
	if (chave == "FrmCompararDiretorio.LogSalvoMemoDirSistema") return _T("Log salvo no mesmo diret\u00f3rio do sistema!");

	if (chave == "FrmCadExtensao.titulo") return _T("Cadastro de Extens\u00e3o de Arquivo");
	if (chave == "FrmCadExtensao.extensao") return _T("Extens\u00e3o");
	if (chave == "FrmCadExtensao.icone") return _T("\u00cdcone");
	if (chave == "FrmCadExtensao.btnIncluir") return _T("Incluir");
	if (chave == "FrmCadExtensao.btnExcluir") return _T("Excluir");
	if (chave == "FrmCadExtensao.menuExtensao") return _T("Extens\u00e3o");
	if (chave == "FrmCadExtensao.menuExportarTodos") return _T("Exportar Todos");
	if (chave == "FrmCadExtensao.menuImportarTodos") return _T("Importar Todos");
	if (chave == "FrmCadExtensao.menuIncluirExtensao") return _T("Incluir Extens\u00e3o");
	if (chave == "FrmCadExtensao.menuExcluirExtensao") return _T("Excluir Extens\u00e3o");
	if (chave == "FrmCadExtensao.menuExcluirTodasExtensoes") return _T("Excluir Todas Extens\u00f5es");
	if (chave == "FrmCadExtensao.menuExportarIcone") return _T("Exportar para \u00cdcone");
	if (chave == "FrmCadExtensao.menuExportarGIF") return _T("Exportar para GIF");
	if (chave == "FrmCadExtensao.menuExportarJPEG") return _T("Exportar para JPEG");
	if (chave == "FrmCadExtensao.menuExportarPNG") return _T("Exportar para PNG");
	if (chave == "FrmCadExtensao.menuExportarTIFF") return _T("Exportar para TIFF");
	if (chave == "FrmCadExtensao.menuImportarIconesArquivos") return _T("Importar \u00cdcones dos Arquivos");
	if (chave == "FrmCadExtensao.menuExtrairIconesArquivos") return _T("Extrair \u00cdcones dos Arquivos");
	if (chave == "FrmCadExtensao.ExtensaoJaCadastrada") return _T("Extens\u00e3o j\u00e1 existe cadastrada!");
	if (chave == "FrmCadExtensao.ExtensaoSalvaSucesso") return _T("Extens\u00e3o salva com sucesso!");
	if (chave == "FrmCadExtensao.ExtensaoCertezaExcluir") return _T("Tem Certeza, que voc\u00ea deseja excluir esta extens\u00e3o?");
	if (chave == "FrmCadExtensao.ExtensaoCertezaTodosExcluir") return _T("Tem Certeza, que voc\u00ea deseja excluir todas as extens\u00f5es?");
	if (chave == "FrmCadExtensao.ExtensaoExcluidaSucesso") return _T("Extens\u00e3o exclu\u00edda com sucesso!");
	if (chave == "FrmCadExtensao.ExtensoesExcluidasSucesso") return _T("Extens\u00f5es exclu\u00eddas com sucesso!");
	if (chave == "FrmCadExtensao.ExportarExtensao") return _T("\u00cdcones salvos no mesmo diret\u00f3rio do sistema!");
	if (chave == "FrmCadExtensao.menuExportarBitmap") return _T("Exportar para Bitmap");

	if (chave == "FrmInfoDiretorio.titulo") return _T("Informa\u00e7\u00f5es do Diret\u00f3rio / Arquivo");
	if (chave == "FrmInfoDiretorio.panelLegenda") return _T("Legenda dos Atributos");
	if (chave == "FrmInfoDiretorio.labArquivoComum") return _T("[ARQ] - Arquivo comum");
	if (chave == "FrmInfoDiretorio.labArquivoOculto") return _T("[HID] - Arquivo Oculto");
	if (chave == "FrmInfoDiretorio.labArquivoSistema") return _T("[SYS] - Arquivo de Sistema");
	if (chave == "FrmInfoDiretorio.labDiretorio") return _T("[DIR] - Diret\u00f3rio");
	if (chave == "FrmInfoDiretorio.labVolumeID") return _T("[VOL] - Volume ID");
	if (chave == "FrmInfoDiretorio.labArquivoSomenteLeitura") return _T("[ROL] - Arquivo Somente Leitura");
	if (chave == "FrmInfoDiretorio.item") return _T("Item");
	if (chave == "FrmInfoDiretorio.descricao") return _T("Descri\u00e7\u00e3o");

	if (chave == "FrmImportarDiretorio.titulo") return _T("Importando Diret\u00f3rio");
	if (chave == "FrmImportarDiretorio.barraStatus1") return _T("Total de linhas sendo processadas:");
	if (chave == "FrmImportarDiretorio.DiretorioExisteCatalogo") return _T("O diret\u00f3rio j\u00e1 existe no cat\u00e1logo!");

	if (chave == "Dialogo.info") return _T("Informa\u00e7\u00e3o");
	if (chave == "Dialogo.erro") return _T("Erro");
	if (chave == "Dialogo.confirma") return _T("Confirma");
	if (chave == "Dialogo.entrada") return _T("Informa");
	if (chave == "Dialogo.yesButtonText") return _T("Sim");
	if (chave == "Dialogo.yesButtonMnemonic") return _T("S");
	if (chave == "Dialogo.cancelButtonText") return _T("Cancelar");
	if (chave == "Dialogo.cancelButtonMnemonic") return _T("C");
	if (chave == "Dialogo.noButtonText") return _T("N\u00e3o");
	if (chave == "Dialogo.noButtonMnemonic") return _T("N");
	if (chave == "Dialogo.okButtonText") return _T("OK");
	if (chave == "Dialogo.okButtonMnemonic") return _T("O");

	if (chave == "EscolhaArquivo.ApproveButtonText") return _T("Escolha o Diret\u00f3rio");
	if (chave == "EscolhaArquivo.ApproveButtonMnemonic") return _T("D");
	if (chave == "EscolhaArquivo.ApproveButtonToolTipText") return _T("Confirme a escolha do diret\u00f3rio.");
	if (chave == "EscolhaArquivo.lookInLabelMnemonic") return _T("E");
	if (chave == "EscolhaArquivo.lookInLabelText") return _T("Examinar em");
	if (chave == "EscolhaArquivo.saveInLabelMnemonic") return _T("S");
	if (chave == "EscolhaArquivo.saveInLabelText") return _T("Salvar em");
	if (chave == "EscolhaArquivo.upFolderToolTipText") return _T("Um n\u00edvel acima");
	if (chave == "EscolhaArquivo.upFolderAccessibleName") return _T("Um n\u00edvel acima");
	if (chave == "EscolhaArquivo.homeFolderToolTipText") return _T("Desktop");
	if (chave == "EscolhaArquivo.homeFolderAccessibleName") return _T("Desktop");
	if (chave == "EscolhaArquivo.newFolderToolTipText") return _T("Criar nova pasta");
	if (chave == "EscolhaArquivo.newFolderAccessibleName") return _T("Criar nova pasta");
	if (chave == "EscolhaArquivo.listViewButtonToolTipText") return _T("Lista");
	if (chave == "EscolhaArquivo.listViewButtonAccessibleName") return _T("Lista");
	if (chave == "EscolhaArquivo.detailsViewButtonToolTipText") return _T("Detalhes");
	if (chave == "EscolhaArquivo.detailsViewButtonAccessibleName") return _T("Detalhes");
	if (chave == "EscolhaArquivo.fileNameLabelMnemonic") return _T("N");
	if (chave == "EscolhaArquivo.fileNameLabelText") return _T("Nome do arquivo");
	if (chave == "EscolhaArquivo.filesOfTypeLabelMnemonic") return _T("A");
	if (chave == "EscolhaArquivo.filesOfTypeLabelText") return _T("Arquivos do tipo");
	if (chave == "EscolhaArquivo.fileNameHeaderText") return _T("Nome");
	if (chave == "EscolhaArquivo.fileSizeHeaderText") return _T("Tamanho");
	if (chave == "EscolhaArquivo.fileTypeHeaderText") return _T("Tipo");
	if (chave == "EscolhaArquivo.fileDateHeaderText") return _T("Data");
	if (chave == "EscolhaArquivo.fileAttrHeaderText") return _T("Atributos");
	if (chave == "EscolhaArquivo.cancelButtonText") return _T("Cancelar");
	if (chave == "EscolhaArquivo.cancelButtonMnemonic") return _T("C");
	if (chave == "EscolhaArquivo.cancelButtonToolTipText") return _T("Cancelar");
	if (chave == "EscolhaArquivo.openButtonText") return _T("Abrir");
	if (chave == "EscolhaArquivo.openButtonMnemonic") return _T("A");
	if (chave == "EscolhaArquivo.openButtonToolTipText") return _T("Abrir");
	if (chave == "EscolhaArquivo.saveButtonText") return _T("Salvar");
	if (chave == "EscolhaArquivo.saveButtonMnemonic") return _T("S");
	if (chave == "EscolhaArquivo.saveButtonToolTipText") return _T("Salvar");
	if (chave == "EscolhaArquivo.updateButtonText") return _T("Alterar");
	if (chave == "EscolhaArquivo.updateButtonMnemonic") return _T("A");
	if (chave == "EscolhaArquivo.updateButtonToolTipText") return _T("Alterar");
	if (chave == "EscolhaArquivo.helpButtonText") return _T("Ajuda");
	if (chave == "EscolhaArquivo.helpButtonMnemonic") return _T("A");
	if (chave == "EscolhaArquivo.helpButtonToolTipText") return _T("Ajuda");
	if (chave == "EscolhaArquivo.acceptAllFileFilterText") return _T("Todos os arquivos (*.*)");
	if (chave == "EscolhaArquivo.filtroTXT") return _T("Arquivo TXT (*.txt)");
	if (chave == "EscolhaArquivo.filtroCSV") return _T("Arquivo CSV (*.csv)");
	if (chave == "EscolhaArquivo.filtroHTML") return _T("Arquivo HTML (*.html)");
	if (chave == "EscolhaArquivo.filtroXML") return _T("Arquivo XML (*.xml)");
	if (chave == "EscolhaArquivo.filtroSQL") return _T("Arquivo SQL (*.sql)");
	if (chave == "EscolhaArquivo.filtroBMP") return _T("Arquivo BMP (*.bmp)");
	if (chave == "EscolhaArquivo.filtroICO") return _T("Arquivo ICO (*.ico)");
	if (chave == "EscolhaArquivo.filtroGIF") return _T("Arquivo GIF (*.gif)");
	if (chave == "EscolhaArquivo.filtroPNG") return _T("Arquivo JPEG (*.png)");
	if (chave == "EscolhaArquivo.filtroJPG") return _T("Arquivo PNG (*.jpg)");
	if (chave == "EscolhaArquivo.filtroTIF") return _T("Arquivo TIFF (*.tif)");
	if (chave == "EscolhaArquivo.todosDiretorios") return _T("Todos os diret\u00f3rios");

    return chave;
}


HBITMAP Rotinas::iconeToBitmapFromID(WORD idIcone, int largura, int altura) {

	HICON hIcon = (HICON)LoadImage(theApp.m_hInstance,
		MAKEINTRESOURCEW(idIcone), IMAGE_ICON, largura, altura, 0);
	ICONINFO iconinfo;
	GetIconInfo(hIcon, &iconinfo);
	HBITMAP hBitmap = iconinfo.hbmColor;

	return hBitmap;
}

HBITMAP Rotinas::iconeToBitmap(HICON hIcon, int tamanho) {
	HDC hDC = GetDC(NULL);
	HDC hMemDC = CreateCompatibleDC(hDC);
	HBITMAP hMemBmp = CreateCompatibleBitmap(hDC, tamanho, tamanho);
	//HBITMAP hMemBmp = CreateCompatibleBitmap(hDC,
	//GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON));
	HBITMAP hResultBmp = NULL;
	HGDIOBJ hOrgBMP = SelectObject(hMemDC, hMemBmp);

	DrawIconEx(hMemDC, 0, 0, hIcon, tamanho, tamanho, 0, NULL, DI_NORMAL);
	//DrawIcon(hMemDC, 0, 0, hIcon);

	//SetStretchBltMode(hMemDC, COLORONCOLOR);
	//StretchBlt(hMemDC, 0, 0, 16, 16, hMemDC, 0, 0, 32, 32, SRCCOPY);

	hResultBmp = hMemBmp;
	hMemBmp = NULL;

	SelectObject(hMemDC, hOrgBMP);
	DeleteDC(hMemDC);
	ReleaseDC(NULL, hDC);
	//DestroyIcon(hIcon);

	return hResultBmp;
}

HBITMAP Rotinas::extrairIconeArquivo(const CString &sNomeArquivo, int tamanho) {
	WORD filtro = 0;
	//WORD indice;

	//HINSTANCE hInstance = GetModuleHandle(NULL);
	HICON icone = ExtractAssociatedIcon(theApp.m_hInstance, (LPWSTR)sNomeArquivo.GetString(), &filtro);
	//HICON icone = ExtractAssociatedIconEx(g_hInstancia, sNomeArquivo.wstr, &indice, &filtro);
	HBITMAP hbmp = iconeToBitmap(icone, tamanho);

	return hbmp;
}

HBITMAP Rotinas::HBitmapFromBlob(void* blob, long larguraAltura) {

	BITMAPINFO bmi;
	ZeroMemory(&bmi, sizeof(BITMAPINFO));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biHeight = larguraAltura;
	bmi.bmiHeader.biWidth = larguraAltura;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biSizeImage = 1078;

	HDC dc = CreateCompatibleDC(NULL);
	HBITMAP hbitmap = CreateDIBSection(dc, &bmi, DIB_RGB_COLORS, &blob, NULL, 0);
	//HBITMAP hbitmap = CreateBitmap(larguraAltura, larguraAltura, 1, 32, blob);

	return hbitmap;
}

BITMAP Rotinas::BitmapFromBlob(void* blob, long larguraAltura) {
	BITMAP bitmap;
	HBITMAP hbitmap = Rotinas::HBitmapFromBlob(blob, larguraAltura);
	int error = GetObject(hbitmap, sizeof(BITMAP), &bitmap);

	return bitmap;
}

HBITMAP Rotinas::HBitmapLoadFromFile(const CString &sNomeArquivo) {
	HBITMAP hbm = 0;

	hbm = (HBITMAP)LoadImage(0, sNomeArquivo.GetString(), IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	return hbm;
}

BITMAP Rotinas::BitmapLoadFromFile(const CString &sNomeArquivo) {
	HBITMAP hbm = 0;
	BITMAP bitmap;

	hbm = (HBITMAP)LoadImage(0, sNomeArquivo.GetString(), IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	int error = GetObject(hbm, sizeof(BITMAP), &bitmap);

	return bitmap;
}

BOOL Rotinas::FileExists2(const CString &sNomeArquivo) {
	HFILE hFile;
	OFSTRUCT ofstruct;
	BOOL retorno = FALSE;
	const char* arquivo = Rotinas::StringToChar(sNomeArquivo);

	hFile = OpenFile(arquivo, &ofstruct, OF_EXIST);
	if (hFile != HFILE_ERROR) {
		retorno = TRUE;
	}
	CloseHandle((HANDLE)hFile);
	return retorno;
}

BOOL Rotinas::SaveTextToFile(const CString &sTexto, const CString &sNomeArquivo) {
	BOOL ret = FALSE;
	HANDLE hFile;

	const char* DataBuffer = Rotinas::StringToChar(sTexto);
	DWORD dwBytesToWrite = (DWORD)strlen(DataBuffer);
	DWORD dwBytesWritten = 0;
	BOOL bErrorFlag = FALSE;

	hFile = CreateFile(sNomeArquivo.GetString(), GENERIC_WRITE, 0, NULL,
		CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile != INVALID_HANDLE_VALUE) {
		bErrorFlag = WriteFile(hFile, DataBuffer, dwBytesToWrite, &dwBytesWritten, NULL);

		if (bErrorFlag == FALSE) {
			printf("Erro\n");
		}
		else if (dwBytesWritten != dwBytesToWrite) {
			printf("Erro\n");
		}
		else {
			ret = TRUE;
		}
	}
	CloseHandle(hFile);
	return ret;
}

bool Rotinas::SListSaveToFile(const CStringList &lista, const CString &sNomeArquivo) {
	CStdioFile cfile;
	CString linha;
	POSITION pos;

	try {
		cfile.Open(sNomeArquivo.GetString(), CFile::modeCreate |
			CFile::modeWrite | CFile::typeText);

		for (int i = 0; i < lista.GetSize(); ++i) {
			pos = lista.FindIndex(i);
			linha = lista.GetAt(pos);
			cfile.WriteString(linha + "\n");
			cfile.Flush();
		}
		cfile.Close();
	}
	catch (CFileException* pEx) {
		//TRACE(_T("Arquivo nao pode ser salvo\n"), sNomeArquivo.GetString());		
		//pEx->GetErrorMessage()
		pEx->Delete();
		return false;
	}
    return true;
}

CStringList* Rotinas::SListLoadFromFile(const CString &sNomeArquivo) {
    CStringList *lista;
	CStdioFile cfile;
	CString linha;
	ULONGLONG npos = 0, nfim;

	lista = new CStringList();
	try {
		cfile.Open(sNomeArquivo.GetString(), CFile::modeRead | CFile::typeText);
		cfile.SeekToBegin();
		nfim = cfile.SeekToEnd();
		cfile.SeekToBegin();
		while (npos < nfim) {
			if (cfile.ReadString(linha)) {
				lista->AddTail(linha);

				//npos = cfile.Seek(linha.GetLength(), CFile::current);
				npos = cfile.Seek(0, CFile::current);
			}
		}
		cfile.Close();
	}
	catch (CFileException* pEx) {
		//TRACE(_T("Arquivo nao pode ser lido\n"), sNomeArquivo.GetString());		
		//pEx->GetErrorMessage()
		pEx->Delete();
	}

    return lista;
}

CStringList* Rotinas::SListSeparador(const CString &texto, const char separador) {
    CStringList *lista;
	CString pedaco = _T("");

	lista = new CStringList();

    if (texto.Find(separador) > 0) {        
        for (int i = 0; i < texto.GetLength(); i++) {
            pedaco += texto[i];
            if (texto[i] == separador) {
                lista->AddTail(pedaco.Mid(0, pedaco.GetLength() - 1));
                pedaco = _T("");
            }
        }
        lista->AddTail(pedaco);
	}
	else {
		lista->AddTail(texto);
	}

    return lista;
}

CString Rotinas::SListTexto(const CStringList &lista) {	
	CString linha = _T("");
	POSITION pos;
	UINT ntamlista = lista.GetSize();
	
	if (ntamlista > 0) {
		for (int i = 0; i < lista.GetSize(); ++i) {
			pos = lista.FindIndex(i);
			linha += lista.GetAt(pos);
		}
	}

	return linha;
}

CStringList* Rotinas::SListInverter(const CStringList &lista) {
	CStringList *nlista = new CStringList();
	CString item;
	POSITION pos;

	for (int i = lista.GetSize() - 1; i >=0 ; --i) {
		pos = lista.FindIndex(i);
		item = lista.GetAt(pos);

		nlista->AddTail(item);
	}

	return nlista;
}

CBitmap& Rotinas::extrairIconeArquivo(const CString &sNomeArquivo) {
	WORD filtro = 0;
	CBitmap *bmp;

	//HINSTANCE hInstance = GetModuleHandle(NULL);
	HICON icone = ExtractAssociatedIcon(AfxGetApp()->m_hInstance, 
		(LPWSTR)sNomeArquivo.GetString(), &filtro);
	HBITMAP hbmp = iconeToBitmap(icone, 32);
	bmp = CBitmap::FromHandle(hbmp);

	return *bmp;
}

CStringList* Rotinas::listarArquivosDiretorios(const CString &sDiretorio) {
	CStringList *lista;
	CFileFind finder;
	BOOL bAchou;
	CString sCaminho;
	CString sdir = sDiretorio;
	
	lista = new CStringList();

	if (DirectoryExists(sDiretorio)) {
		sdir += _T("\\*.*");

		bAchou = finder.FindFile(sdir);

		while (bAchou) {
			bAchou = finder.FindNextFile();

			if (finder.IsDots()) {
				continue;
			}

			if (finder.IsDirectory()) {
				sCaminho = finder.GetFilePath();
				lista->AddTail(sCaminho);
				//se for buscar subdiretorio
				//listarArquivosDiretorios(sCaminho);
			} else {
				sCaminho = finder.GetFilePath();
				lista->AddTail(sCaminho);
			}
		}
		finder.Close();
	}
	
	return lista;
}

BOOL Rotinas::BlobSaveToFile(const void* blob, size_t tamanho, const CString &sNomeArquivo) {
	BOOL ret = TRUE;
	FILE* fp;
	errno_t erro;
	const char* arquivo = Rotinas::StringToChar(sNomeArquivo);

	erro = fopen_s(&fp, arquivo, "wb");

	if (NULL != fp)
	{
		size_t ntamanho = fwrite(blob, tamanho, 1, fp);

		if (ntamanho == tamanho) {
			ret = FALSE;
		}

		fclose(fp);
	}
	else
	{
		ret = FALSE;
	}

	return ret;
}

long Rotinas::BlobLoadFromFile(const CString &sNomeArquivo, void** blob) {
	long ret = 0;
	FILE* fp;
	errno_t erro;
	//	long tamanho;
	const char* arquivo = Rotinas::StringToChar(sNomeArquivo);

	erro = fopen_s(&fp, arquivo, "rb");

	if (NULL != fp)
	{
		/*
		fseek(fp, 0L, SEEK_END);
		tamanho = ftell(fp);
		//fseek(fp, 0L, SEEK_SET);
		rewind(fp);
		*/

		const size_t tamanho = 16 * 1024;
		char buffer[tamanho];
		//char* buffer = (char*)malloc(tamanho);
		buffer[0] = '\0';

		*blob = &buffer;

		size_t ntamanho = fread(*blob, sizeof(char), tamanho, fp);
		buffer[ntamanho] = '\0';
		fclose(fp);

		ret = ntamanho;
	}

	return ret;

}

VOID Rotinas::errhandler(LPCWSTR erro, HWND hwd) {
	erro = lstrcat(_T("ERRO: Rotinas_BitmapSaveToFile: "), erro);
	MessageBox(hwd, erro, _T("Erro"), MB_ICONERROR | MB_OK);
}

PBITMAPINFO Rotinas::CreateHBitmapInfoStruct(HWND hwnd, HBITMAP hBmp)
{
	BITMAP bmp;
	PBITMAPINFO pbmi;
	WORD    cClrBits;

	// Retrieve the bitmap color format, width, and height.  
	if (!GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp))
		Rotinas::errhandler(_T("GetObject"), hwnd);

	// Convert the color format to a count of bits.  
	cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel);
	if (cClrBits == 1)
		cClrBits = 1;
	else if (cClrBits <= 4)
		cClrBits = 4;
	else if (cClrBits <= 8)
		cClrBits = 8;
	else if (cClrBits <= 16)
		cClrBits = 16;
	else if (cClrBits <= 24)
		cClrBits = 24;
	else cClrBits = 32;

	// Allocate memory for the BITMAPINFO structure. (This structure  
	// contains a BITMAPINFOHEADER structure and an array of RGBQUAD  
	// data structures.)  

	if (cClrBits < 24)
		pbmi = (PBITMAPINFO)LocalAlloc(LPTR,
			sizeof(BITMAPINFOHEADER) +
			sizeof(RGBQUAD) * (1 << cClrBits));

	// There is no RGBQUAD array for these formats: 24-bit-per-pixel or 32-bit-per-pixel 

	else
		pbmi = (PBITMAPINFO)LocalAlloc(LPTR,
			sizeof(BITMAPINFOHEADER));

	// Initialize the fields in the BITMAPINFO structure.  

	pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pbmi->bmiHeader.biWidth = bmp.bmWidth;
	pbmi->bmiHeader.biHeight = bmp.bmHeight;
	pbmi->bmiHeader.biPlanes = bmp.bmPlanes;
	pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel;
	if (cClrBits < 24)
		pbmi->bmiHeader.biClrUsed = (1 << cClrBits);

	// If the bitmap is not compressed, set the BI_RGB flag.  
	pbmi->bmiHeader.biCompression = BI_RGB;

	// Compute the number of bytes in the array of color  
	// indices and store the result in biSizeImage.  
	// The width must be DWORD aligned unless the bitmap is RLE 
	// compressed. 
	pbmi->bmiHeader.biSizeImage = ((pbmi->bmiHeader.biWidth * cClrBits + 31) & ~31) / 8
		* pbmi->bmiHeader.biHeight;
	// Set biClrImportant to 0, indicating that all of the  
	// device colors are important.  
	pbmi->bmiHeader.biClrImportant = 0;
	return pbmi;
}

void Rotinas::CriarHBitmapFile(HWND hwnd, LPTSTR pszFile, PBITMAPINFO pbi,
	HBITMAP hBMP, HDC hDC)
{

	HANDLE hf;                 // file handle  
	BITMAPFILEHEADER hdr;       // bitmap file-header  
	PBITMAPINFOHEADER pbih;     // bitmap info-header  
	LPBYTE lpBits;              // memory pointer  
	DWORD dwTotal;              // total count of bytes  
	DWORD cb;                   // incremental count of bytes  
	BYTE *hp;                   // byte pointer  
	DWORD dwTmp;

	pbih = (PBITMAPINFOHEADER)pbi;
	lpBits = (LPBYTE)GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);

	if (!lpBits)
		Rotinas::errhandler(_T("GlobalAlloc"), hwnd);

	// Retrieve the color table (RGBQUAD array) and the bits
	// (array of palette indices) from the DIB.
	if (!GetDIBits(hDC, hBMP, 0, (WORD)pbih->biHeight, lpBits, pbi,
		DIB_RGB_COLORS))
	{
		Rotinas::errhandler(_T("GetDIBits"), hwnd);
	}

	// Create the .BMP file.  
	hf = CreateFile(pszFile,
		GENERIC_READ | GENERIC_WRITE,
		(DWORD)0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		(HANDLE)NULL);
	if (hf == INVALID_HANDLE_VALUE)
		Rotinas::errhandler(_T("CreateFile"), hwnd);
	hdr.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M"  
								// Compute the size of the entire file.  
	hdr.bfSize = (DWORD)(sizeof(BITMAPFILEHEADER) +
		pbih->biSize + pbih->biClrUsed
		* sizeof(RGBQUAD) + pbih->biSizeImage);
	hdr.bfReserved1 = 0;
	hdr.bfReserved2 = 0;

	// Compute the offset to the array of color indices.  
	hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) +
		pbih->biSize + pbih->biClrUsed
		* sizeof(RGBQUAD);

	// Copy the BITMAPFILEHEADER into the .BMP file.  
	if (!WriteFile(hf, (LPVOID)&hdr, sizeof(BITMAPFILEHEADER),
		(LPDWORD)&dwTmp, NULL))
	{
		Rotinas::errhandler(_T("WriteFile"), hwnd);
	}

	// Copy the BITMAPINFOHEADER and RGBQUAD array into the file.  
	if (!WriteFile(hf, (LPVOID)pbih, sizeof(BITMAPINFOHEADER)
		+ pbih->biClrUsed * sizeof(RGBQUAD),
		(LPDWORD)&dwTmp, (NULL)))
		Rotinas::errhandler(_T("WriteFile"), hwnd);

	// Copy the array of color indices into the .BMP file.  
	dwTotal = cb = pbih->biSizeImage;
	hp = lpBits;
	if (!WriteFile(hf, (LPSTR)hp, (int)cb, (LPDWORD)&dwTmp, NULL))
		Rotinas::errhandler(_T("WriteFile"), hwnd);

	// Close the .BMP file.  
	if (!CloseHandle(hf))
		Rotinas::errhandler(_T("CloseHandle"), hwnd);

	// Free memory.  
	GlobalFree((HGLOBAL)lpBits);
}

BOOL Rotinas::HBitmapSaveToFile(HBITMAP hBMP, const CString &sNomeArquivo) {
	HDC hDC = GetDC(NULL);
	HDC hDCMem = CreateCompatibleDC(hDC);
	PBITMAPINFO pbi = Rotinas::CreateHBitmapInfoStruct(0, hBMP);
	Rotinas::CriarHBitmapFile(0, (LPTSTR)sNomeArquivo.GetString(), pbi, hBMP, hDC);
	return Rotinas::FileExists(sNomeArquivo);
}

CBitmap* Rotinas::BlobToBitmap(const void* blobBmp, int tamanhoBmp, CImageList *imageList) {
	BITMAP bmp;
	//HBITMAP hbmp;
	CBitmap *cbmp = NULL, *mascara = NULL;

	CString app = Rotinas::AppDirName();
	CString arquivo = _T("temp.bmp");
	arquivo = app + arquivo;

	if (Rotinas::BlobSaveToFile(blobBmp, tamanhoBmp, arquivo)) {
		bmp = Rotinas::BitmapLoadFromFile(arquivo);
		cbmp = new CBitmap();
		cbmp->CreateBitmapIndirect(&bmp);
		imageList->Add(cbmp, mascara);		
	}
	//remove(arquivo);
	Rotinas::DeleteFromFile(arquivo);

	DeleteObject(mascara);
	delete mascara;

	return cbmp;
}

CBitmap* Rotinas::HBitmapToBitmap(HBITMAP hBMP, CImageList *imageList) {
	BITMAP bmp;
	CBitmap *cbmp = NULL, *mascara = NULL;

	CString app = Rotinas::AppDirName();
	CString arquivo = _T("temp.bmp");
	arquivo = app + arquivo;

	if (Rotinas::HBitmapSaveToFile(hBMP, arquivo)) {
		bmp = Rotinas::BitmapLoadFromFile(arquivo);
		cbmp = new CBitmap();
		cbmp->CreateBitmapIndirect(&bmp);
		imageList->Add(cbmp, mascara);
	}
	//remove(arquivo);
	Rotinas::DeleteFromFile(arquivo);

	DeleteObject(mascara);
	delete mascara;

	return cbmp;
}

int Rotinas::BitmapToBlob(CBitmap* cbmp, void** blobBmp) {
	BITMAP bmp;
	CString app = Rotinas::AppDirName();
	CString arquivo = _T("temp.bmp");
	arquivo = app + arquivo;

	cbmp->GetBitmap(&bmp);
	HBITMAP hBMP = CreateBitmapIndirect(&bmp);

	if (Rotinas::HBitmapSaveToFile(hBMP, arquivo)) {
		return Rotinas::BlobLoadFromFile(arquivo, blobBmp);
	}

	return -1;
}

void Rotinas::testar(){
	CString saida = _T("");
	CString sApp = Rotinas::AppDirPath();
	CString sAppDir = Rotinas::AppDirName();
	CString sAppFile = Rotinas::AppFileName();
	CString sDir = _T("    c:\\ago%ra\\CAMINHO\\teste.olha.depois    ");

	CStringList *listaDir = Rotinas::listarArquivosDiretorios(_T("c:\\Temp"));
	for (int i = 0; i < listaDir->GetSize(); i++)
	{
		saida.Format(_T("listarArquivosDiretorios[%d]: %s\n"), i, listaDir->GetAt(listaDir->FindIndex(i)));
		OutputDebugString(saida);
	}
	listaDir->RemoveAll();
	delete listaDir;
	
	saida.Format(_T("sDir: [%s]\n"), sDir); OutputDebugString(saida);
	saida.Format(_T("AppDirPath: %s\n"), sApp); OutputDebugString(saida);
	saida.Format(_T("FileExists: %s\n"), (Rotinas::FileExists(sApp) ? _T("true") : _T("false"))); OutputDebugString(saida);
	saida.Format(_T("DirectoryExists: %s\n"), (Rotinas::DirectoryExists(sAppDir) ? _T("true") : _T("false"))); OutputDebugString(saida);
	saida.Format(_T("ExtractFilePath: %s\n"), Rotinas::ExtractFilePath(sApp)); OutputDebugString(saida);
	saida.Format(_T("ExtractFileName: %s\n"), Rotinas::ExtractFileName(sApp)); OutputDebugString(saida);

	saida.Format(_T("Length(): %d\n"), lstrlen(sDir)); OutputDebugString(saida);
	saida.Format(_T("Trim(): [%s]\n"), Rotinas::Trim(sDir)); OutputDebugString(saida);
	saida.Format(_T("tamanho Trim(): %d\n"), Rotinas::Trim(sDir).GetLength()); OutputDebugString(saida);
	saida.Format(_T("LowerCase(): %s\n"), Rotinas::LowerCase(sDir)); OutputDebugString(saida);
	saida.Format(_T("UpperCase(): %s\n"), Rotinas::UpperCase(sDir)); OutputDebugString(saida);
	saida.Format(_T("Pos('.'): %d\n"), Rotinas::Pos(_T("."), sDir)); OutputDebugString(saida);
	saida.Format(_T("LastDelimiter('.'): %d\n"), Rotinas::LastDelimiter(_T("."), sDir)); OutputDebugString(saida);
	saida.Format(_T("QuotedStr(): %s\n"), Rotinas::QuotedStr(sDir)); OutputDebugString(saida);
	saida.Format(_T("IntToStr(245789): %s\n"), Rotinas::FromInt(245789)); OutputDebugString(saida);
	saida.Format(_T("StrToInt() --> 245789: %d\n"), Rotinas::ToInt(_T("245789"))); OutputDebugString(saida);
	saida.Format(_T("StrToLong() --> 4200155136: %llu\n"), Rotinas::ToULongLong(_T("4200155136"))); OutputDebugString(saida);
	saida.Format(_T("DoubleToStr(15.557878): %s\n"), Rotinas::FromLongDouble(15.557878)); OutputDebugString(saida);

	saida.Format(_T("SubString(): %s\n"), Rotinas::SubString(sDir, 8, 6)); OutputDebugString(saida);
	saida.Format(_T("StringReplaceAll(): [%s]\n"), Rotinas::StringReplaceAll(sDir, _T("\\"), _T("@"))); OutputDebugString(saida);
	saida.Format(_T("trocaSeparador(): [%s]\n"), Rotinas::trocaSeparador(sDir)); OutputDebugString(saida);
	saida.Format(_T("testaNull(NULL): %s\n"), Rotinas::testaNull(NULL)); OutputDebugString(saida);

	saida.Format(_T("StartsStr(DVD, JOGOS2_DVDS/TESTE): %s\n"), (Rotinas::StartsStr(_T("DVD"), _T("JOGOS2_DVDS/TESTE")) ? _T("true") : _T("false"))); OutputDebugString(saida);
	saida.Format(_T("StartsStr(DVD, DVDSJOGOS2_/TESTE): %s\n"), (Rotinas::StartsStr(_T("DVD"), _T("DVDSJOGOS2_/TESTE")) ? _T("true") : _T("false"))); OutputDebugString(saida);

	saida.Format(_T("ContainsStr(JOGOS2_DVDS/TESTE): %s\n"), (Rotinas::ContainsStr(_T("DVDSJOGOS2_/TESTE"), _T("DVDSJOGOS2_/TESTE")) ? _T("true") : _T("false")));
	OutputDebugString(saida);
	saida.Format(_T("EndsStr(JOGOS2_DVDS/TESTE, TESTE): %s\n"), (Rotinas::EndsStr(_T("DVDSJOGOS2_/TESTE"), _T("TESTE")) ? _T("true") : _T("false")));
	OutputDebugString(saida);

	saida.Format(_T("formataDate(): %s\n"), Rotinas::formataDate(Rotinas::FORMATO_DATAHORA, Rotinas::DataHoraNow()));
	OutputDebugString(saida);
	CTime dt = Rotinas::StringToDate(_T("03/02/2017 15:23:32"));
	saida.Format(_T("StringToDate(03/02/2017 15:23:32): %s\n"), Rotinas::formataDate(Rotinas::FORMATO_DATAHORA, dt));
	OutputDebugString(saida);

	saida.Format(_T("FormatLong(4200155136): %s\n"), Rotinas::FromULong(4200155136)); OutputDebugString(saida);
	saida.Format(_T("FormatDouble(15.544878): %s\n"), Rotinas::FromLongDouble(15.544878)); OutputDebugString(saida);
	saida.Format(_T("FormatDouble(15.547878): %s\n"), Rotinas::FromLongDouble(15.547878)); OutputDebugString(saida);
	saida.Format(_T("FormatDouble(15.557878): %s\n"), Rotinas::FromLongDouble(15.557878)); OutputDebugString(saida);
	saida.Format(_T("FormatDouble(15.567878): %s\n"), Rotinas::FromLongDouble(15.567878)); OutputDebugString(saida);

	saida.Format(_T("MontaTamanho() --> 3.91 GB: %s\n"), Rotinas::MontaTamanho(4200155136)); OutputDebugString(saida);
	saida.Format(_T("MontaTamanho() --> 3.50 GB: %s\n"), Rotinas::MontaTamanho(3757244416)); OutputDebugString(saida);
	saida.Format(_T("MontaTamanho() --> 2.29 GB: %s\n"), Rotinas::MontaTamanho(2455207936)); OutputDebugString(saida);
	saida.Format(_T("MontaTamanho() --> 888.18 PB: %s\n"), Rotinas::MontaTamanhoBig(999999999999999999.9999)); 
	OutputDebugString(saida);
	
	CStringList *lista;
	CString linha = _T("");
	POSITION pos;

	lista = Rotinas::SListSeparador(sDir, '\\');

	for (int i = 0; i < lista->GetSize(); i++)
	{
		pos = lista->FindIndex(i);
		linha = lista->GetAt(pos);

		saida.Format(_T("SListSeparador[%d]: %s\n"), i, linha); OutputDebugString(saida);
	}

	CString arquivo = Rotinas::ExtractFilePath(sApp);
	arquivo += _T("exemplo.txt");

	saida.Format(_T("arquivo: %s\n"), arquivo); OutputDebugString(saida);

	//Rotinas::SaveToFile(_T("TESTE"), arquivo);
	
	if (Rotinas::SListSaveToFile(*lista, arquivo)) {

		if (Rotinas::FileExists(arquivo)) {

			lista = Rotinas::SListLoadFromFile(arquivo);

			for (int i = 0; i < lista->GetSize(); i++)
			{
				pos = lista->FindIndex(i);
				linha = lista->GetAt(pos);
				saida.Format(_T("SListLoadFromFile[%d]: %s\n"), i, linha); OutputDebugString(saida);
			}

			if (Rotinas::DeleteFromFile(arquivo)) {
				if (!Rotinas::FileExists(arquivo)) {
					saida.Format(_T("DeleteFromFile: OK\n"));
					OutputDebugString(saida);
				}
			}
			else {
				saida.Format(_T("DeleteFromFile: FALHOU\n")); OutputDebugString(saida);
			}

		}

	}

	lista->RemoveAll();
	delete lista;
}

}
}
