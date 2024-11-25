#include "stdafx.h"

#include <windows.h>
#include <commdlg.h>
#include <ShellAPI.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "HFSGuardaDiretorio.h"
#include "FrmPrincipal.h"
#include "ListaString.h"
#include "resource.h"
#include "Rotinas.h"

String Rotinas_HFSGUARDADIR = String_iniciar("HFSGuardaDir");

String Rotinas_BARRA_NORMAL = String_iniciar("\\");
String Rotinas_BARRA_INVERTIDA = String_iniciar("/");

String Rotinas_FORMATO_DATA = String_iniciar("dd/MM/yyyy");
String Rotinas_FORMATO_HORA = String_iniciar("HH:mm:ss");
String Rotinas_FORMATO_DATAHORA = String_iniciar("dd/MM/yyyy HH:mm:ss");
String Rotinas_FORMATO_DHARQUIVO = String_iniciar("yyyy-MM-dd_HH_mm_ss");
String Rotinas_EXTENSAO_BMP = String_iniciar("bmp");
String Rotinas_EXTENSAO_ICO = String_iniciar("ico");
String Rotinas_EXTENSAO_GIF = String_iniciar("gif");
String Rotinas_EXTENSAO_JPEG = String_iniciar("jpg");
String Rotinas_EXTENSAO_PNG = String_iniciar("png");
String Rotinas_EXTENSAO_TIFF = String_iniciar("tif");

sqlite3* dbConexao;


LPWSTR Rotinas_NewStr(INT ntam)
{
	LPWSTR strlocal;

	strlocal = LPWSTR(GlobalAlloc(GPTR, ntam));
	//strlocal[0] = '\0';

	return strlocal;
}

LPWSTR Rotinas_NewStr()
{
	return Rotinas_NewStr(TAM_MAX_STR);
}
/*
const char* Rotinas_LPCWSTRToCharArray(LPCWSTR stexto)
{
	const char* cs = (const char*)GlobalAlloc(GPTR, TAM_MAX_STR);
	//LPCWSTR retorno = stexto;
	if (WideCharToMultiByte(0, 0, stexto, lstrlen(stexto), (LPSTR)cs, lstrlen(stexto), NULL, NULL) > 0)
		return cs;
	else
		return NULL;
}

LPCWSTR Rotinas_CharArrayToLPCWSTR(char* stexto)
{
	const char* cs = stexto;
	LPWSTR retorno = Rotinas_NewStr();

	if (MultiByteToWideChar(0, 0, (LPCCH)cs, strlen(cs), retorno, strlen(cs)) > 0) {
		return retorno;
	}
	else
		return NULL;
}
//---------------------------------------------------------------------------
int Rotinas_LastIndexOf(LPCWSTR texto, WCHAR alvo)
{
	int retorno = -1;
	int tamanho = lstrlen(texto);

	if (tamanho > 0)
	{
		for (unsigned int i = 0; texto[i] != '\0'; i++)
		{
			if (texto[i] == alvo)
			{
				retorno = i;
			}
		}
	}
	return retorno;
}
//---------------------------------------------------------------------------
LPWSTR Rotinas_Trim(LPCWSTR texto)
{
	LPWSTR retorno = Rotinas_NewStr();
	unsigned int j = 0, inicio = 0, fim = 0;
	WCHAR compara;
	int tamanho = lstrlen(texto);

	if (tamanho > 0)
	{
		for (unsigned int i = 0; texto[i] != '\0'; i++) {
			compara = texto[i];
			if (!isspace(compara)) {
				inicio = i;
				fim = lstrlen(texto);
				break;
			}
		}

		for (unsigned int i = (lstrlen(texto) - 1); i >= 0; i--) {
			compara = texto[i];
			if (isspace(compara)) {
				fim = i;
			}
			else {
				break;
			}
		}
		
		for (unsigned int i = inicio; i < fim; i++) {
			retorno[j] = texto[i];
			j++;
		}
		retorno[j] = '\0';
	}
	return retorno;
}
//---------------------------------------------------------------------------
LPWSTR Rotinas_LowerCase(LPCWSTR texto)
{
	LPWSTR retorno = Rotinas_NewStr();
	unsigned int j = 0;
	int tamanho = lstrlen(texto);

	if (tamanho > 0)
	{
		for (unsigned int i = 0; texto[i] != '\0'; i++)
		{
			retorno[j] = tolower(texto[i]);
			j++;
		}
		retorno[j] = '\0';
	}
	return retorno;
}
//---------------------------------------------------------------------------
LPWSTR Rotinas_UpperCase(LPCWSTR texto)
{
	LPWSTR retorno = Rotinas_NewStr();
	unsigned int j = 0;
	int tamanho = lstrlen(texto);

	if (tamanho > 0)
	{
		for (unsigned int i = 0; texto[i] != '\0'; i++)
		{
			retorno[j] = toupper(texto[i]);
			j++;
		}
		retorno[j] = '\0';
	}
	return retorno;
}
//---------------------------------------------------------------------------
int Rotinas_Pos(LPCWSTR subtexto, LPCWSTR texto)
{
	//LPCWSTR retorno = strstr(texto, subtexto);
	LPCWSTR retorno = wcsstr(texto, subtexto);
	//if (retorno == NULL)
	if (lstrlen(retorno)==0)
		return -1;
	else
		return (retorno - texto) + 1;
}
//---------------------------------------------------------------------------
BOOL Rotinas_StartsStr(LPCWSTR sub, LPCWSTR texto)
{
	//if (strncmp(texto, sub, lstrlen(sub)) == 0)
	if (wcsncmp(texto, sub, lstrlen(sub)) == 0)
		return TRUE;
	else
		return FALSE;
}
//---------------------------------------------------------------------------
BOOL Rotinas_ContainsStr(LPCWSTR texto, LPCWSTR subtexto) {
	return (Rotinas_Pos(subtexto, texto) > 0);
}
//---------------------------------------------------------------------------
BOOL Rotinas_EndsStr(LPCWSTR texto, LPCWSTR subtexto) {
	return (Rotinas_LastDelimiter(subtexto, texto) > 0);
}
//---------------------------------------------------------------------------
int Rotinas_LastDelimiter(LPCWSTR sub, LPCWSTR texto)
{
	LPWSTR textolocal = Rotinas_NewStr();
	LPCWSTR parte;	
	int retorno = -1, tamparte = 0;
	int tamanho = lstrlen(texto);	
	LPWSTR next_token;

	if (tamanho > 0)
	{
		retorno = 0;		
		//strcpy_s(textolocal, tamanho, texto);
		//wcscpy_s(textolocal, tamanho, texto);
		lstrcpy(textolocal, texto);
		//parte = strtok_s(textolocal, sub, &next_token);
		parte = wcstok_s(textolocal, sub, &next_token);
		while (parte != NULL)
		{
			tamparte = lstrlen(parte) + 1;
			retorno += tamparte;
			//parte = strtok_s(NULL, sub, &next_token);
			parte = wcstok_s(NULL, sub, &next_token);
		}
		retorno -= tamparte;
	}

	return retorno;
}
//---------------------------------------------------------------------------
LPWSTR Rotinas_strndup(LPCWSTR texto, size_t tamanho)
{
	LPWSTR retorno = Rotinas_NewStr(tamanho);
	LPWSTR fim = (LPWSTR)wmemchr(texto, 0, tamanho);

	if (fim)
	{
		tamanho = fim - texto + 1;
	}

	//retorno = Rotinas_NewStr(tamanho);

	if (tamanho)
	{
		wmemcpy(retorno, texto, tamanho - 1);
		retorno[tamanho - 1] = '\0';
	}
	return retorno;
}
//---------------------------------------------------------------------------
LPWSTR Rotinas_SubString(LPCWSTR texto, int inicio, int tamanho)
{
	LPWSTR retorno = Rotinas_NewStr(tamanho);
	int tamtexto = lstrlen(texto);

	if (tamtexto > 0)
	{
		retorno = Rotinas_strndup(texto + inicio - 1, tamanho + 1);
	}
	return retorno;
}
//---------------------------------------------------------------------------
LPWSTR Rotinas_IntToStr(int valor)
{
	LPWSTR retorno;
	int tamanho = 30;

	retorno = Rotinas_NewStr(tamanho);
	//sprintf_s(retorno, tamanho, "%d", valor);
	wsprintf(retorno, _T("%d"), valor);

	return retorno;
}
//---------------------------------------------------------------------------
int String_ToInt(LPCWSTR texto) {
	//return atoi((const char*)texto);
	return _wtoi(texto);
}
//---------------------------------------------------------------------------
LPWSTR Rotinas_QuotedStr(LPCWSTR texto)
{
	LPWSTR retorno = Rotinas_NewStr();
	int tamanho = lstrlen(texto);

	//retorno = Rotinas_NewStr(tamanho + 2);
	//sprintf_s(retorno, tamanho, "'%s'", texto);
	wsprintf(retorno, _T("'%s'"), texto);
	return retorno;
}
//---------------------------------------------------------------------------
LPWSTR Rotinas_StringReplaceAll(LPCWSTR texto,
	LPCWSTR velho, LPCWSTR novo)
{
	LPWSTR retorno = Rotinas_NewStr();
	LPWSTR textolocal = Rotinas_NewStr();
	unsigned int j = 0;
	int tamanho = lstrlen(texto);
	int tamvelho = lstrlen(velho);
	int tamnovo = lstrlen(novo);
	int tamfinal = 0, tamparte = 0;
	LPWSTR next_token;
	LPWSTR parte;
	
	if (tamanho > 0)
	{		
		//textolocal = Rotinas_NewStr(tamanho);
		//strcpy_s(textolocal, tamanho, texto);
		lstrcpy(textolocal, texto);
		//parte = strstr(textolocal, velho);
		parte = wcsstr(textolocal, velho);
		while (parte != NULL)
		{
			j++;
			//strcpy_s(textolocal, tamanho, parte + 1);
			//lstrcpy(textolocal, parte + 1);
			wcscpy_s(textolocal, tamanho, parte + 1);
			//parte = strstr(textolocal, velho);			
			parte = wcsstr(textolocal, velho);
		}
		tamfinal = (tamanho - (j*tamvelho)) + (j*tamnovo);
		//retorno = Rotinas_NewStr(tamfinal);

		//strcpy_s(textolocal, tamanho, texto);
		lstrcpy(textolocal, texto);
		//parte = strtok_s(textolocal, velho, &next_token);
		parte = wcstok_s(textolocal, velho, &next_token);
		while (parte != NULL)
		{
			tamparte = lstrlen(parte);
			//strncat_s(retorno, tamfinal + 1, parte, tamparte);
			wcsncat_s(retorno, tamfinal + 1, parte, tamparte);
			//parte = strtok_s(NULL, velho, &next_token);
			parte = wcstok_s(NULL, velho, &next_token);

			if (parte != NULL)
			{
				//strncat_s(retorno, tamfinal + 1, novo, tamnovo);
				wcsncat_s(retorno, tamfinal + 1, novo, tamnovo);
			}
		}
	}
	else
	{
		retorno = Rotinas_NewStr(tamanho);
		//strcpy_s(retorno, tamanho, texto);
		lstrcpy(retorno, texto);
	}
	
	return retorno;
}
// ---------------------------------------------------------------------------
LPWSTR Rotinas_FormatLong(const unsigned long valor)
{
	LPWSTR retorno = Rotinas_NewStr(40);

	//sprintf_s(retorno, tamanho, "%lu", valor);
	swprintf_s(retorno, 40, _T("%lu"), valor);

	return retorno;
}
// ---------------------------------------------------------------------------
LPWSTR Rotinas_FormatDouble(const long double valor)
{
	LPWSTR retorno = Rotinas_NewStr(40);
	//double lvalor = valor;

	//sprintf_s(retorno, tamanho, "%4.2Lf", lvalor);
	swprintf_s(retorno, 40, _T("%4.2Lf"), valor);

	return retorno;
}
// ---------------------------------------------------------------------------
unsigned long long Rotinas_StrToLong(LPCWSTR texto)
{
	LPWSTR pEnd;
	//return strtoll(texto, &pEnd, 10);
	unsigned long long num = wcstoull(texto, &pEnd, 10);
	
	return num;
}
// ---------------------------------------------------------------------------
LPWSTR Rotinas_DoubleToStr(const double valor)
{
	LPWSTR retorno = Rotinas_NewStr(40);
	//sprintf_s(retorno, 40, "%4.2f", valor);
	swprintf_s(retorno, 40, _T("%4.2f"), valor);

	return retorno;
}
// ---------------------------------------------------------------------------
double Rotinas_StrToDouble(LPCWSTR texto)
{
	LPWSTR pEnd;
	//return strtod(texto, &pEnd);
	double num = wcstod(texto, &pEnd);

	return num;
}
// ---------------------------------------------------------------------------

LPWSTR Rotinas_formataDate(LPCWSTR formato, DateTime dt) {
	LPWSTR ds = Rotinas_NewStr();

	DateTime_FormatDateTime(dt, formato, ds);

	return ds;
}
// ---------------------------------------------------------------------------
DateTime Rotinas_StringToDate(LPCWSTR sData) {
	DateTime data;

	if (lstrlen(Rotinas_Trim(sData)) > 0) {
		data = DateTime_StrToDateTime(sData);
	}
	return data;
}
// ---------------------------------------------------------------------------
*/



INT Rotinas_RegistrarClasseForm(WNDCLASSEX WndClassEx, WNDPROC WndFrmProc, 
  LPCTSTR sNomeClasse) 
{
   WndClassEx.lpfnWndProc     = WndFrmProc;
   WndClassEx.lpszMenuName    = NULL;
   WndClassEx.lpszClassName   = sNomeClasse; 
   WndClassEx.hbrBackground   = (HBRUSH)(COLOR_3DFACE+1);
   WndClassEx.cbWndExtra      = 4;

   if(!RegisterClassEx(&WndClassEx))
   {
      MessageBox(0, Rotinas_lerStr(STR_NREGTELA), _T("Erro"), MB_ICONERROR | MB_OK);
      return -1;
   }
   return TRUE;
}

HWND Rotinas_ChamarForm(HWND hwnd, LPCTSTR sTituloForm, LPCTSTR sNomeClasse, 
                HWND hMDICliente, INT largura, INT altura)
{
  MDICREATESTRUCT mcs;
  HWND hTelaFilha;
  
  mcs.szTitle = sTituloForm;
  mcs.szClass = sNomeClasse;
  mcs.hOwner  = (HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE);
  mcs.x = CW_USEDEFAULT;
  mcs.y = CW_USEDEFAULT;
  mcs.cx = largura;
  mcs.cy = altura;
//  mcs.style = MDIS_ALLCHILDSTYLES;
  //mcs.style = g_hTelaAtiva && IsZoomed(g_hTelaAtiva) ? WS_MAXIMIZE : 0;
  mcs.style = WS_MAXIMIZE;

  hTelaFilha = (HWND)(UINT)SendMessage(hMDICliente, WM_MDICREATE, 0, 
    (LPARAM)(LPMDICREATESTRUCT)&mcs);  
  
  if(!hTelaFilha)
    MessageBox(hwnd, Rotinas_lerStr(STR_NCCRIATELA), 
        _T("Erro"), MB_ICONERROR | MB_OK);

  return hTelaFilha;
}

HWND Rotinas_ChamarDlgNaoModal(HWND hwnd, LPCTSTR sNomeDialog, DLGPROC lpDlgProc)
{
HWND hLocal;                       
  hLocal = CreateDialog((HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE), 
                        sNomeDialog, hwnd, lpDlgProc);  
  if (!hLocal)
     MessageBox(hwnd, Rotinas_lerStr(STR_NCCRIATELA), 
          _T("Erro"), MB_ICONERROR | MB_OK);
  else 
    ShowWindow(hLocal, SW_SHOW);
    
return hLocal;
}

VOID Rotinas_CentralizaTela(HWND hWnd)
{
RECT rect, rectTela;
INT hFrm, wFrm, hTela, wTela;

GetWindowRect(hWnd, &rect);
GetWindowRect(GetDesktopWindow(), &rectTela);

hFrm = rect.bottom - rect.top;
wFrm = rect.right - rect.left;

hTela = rectTela.bottom - rectTela.top;
wTela = rectTela.right - rectTela.left;

MoveWindow(hWnd, abs((wTela - wFrm) / 2), abs((hTela - hFrm)/2), 
        wFrm, hFrm, TRUE);
}

VOID Rotinas_criaImageLists(HWND hwnd, HIMAGELIST *imageList16, HIMAGELIST *imageList32) {
	*imageList16 = ImageList_Create(16, 16, ILC_COLOR8 | ILC_MASK, 3, 0);
	*imageList32 = ImageList_Create(32, 32, ILC_COLOR8 | ILC_MASK, 3, 0);

	HINSTANCE hi = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
	HBITMAP hbmDIRETORIO = LoadBitmap(hi, MAKEINTRESOURCE(DIRETORIO));
	HBITMAP hbmARQUIVO = LoadBitmap(hi, MAKEINTRESOURCE(ARQUIVO));
	HBITMAP hbmDIRABERTO = LoadBitmap(hi, MAKEINTRESOURCE(DIRABERTO));
	ImageList_Add(*imageList16, hbmDIRETORIO, NULL);
	ImageList_Add(*imageList16, hbmARQUIVO, NULL);
	ImageList_Add(*imageList16, hbmDIRABERTO, NULL);

	HBITMAP hbmDIRETORIO32 = LoadBitmap(hi, MAKEINTRESOURCE(DIRETORIO32));
	HBITMAP hbmARQUIVO32 = LoadBitmap(hi, MAKEINTRESOURCE(ARQUIVO32));
	HBITMAP hbmDIRABERTO32 = LoadBitmap(hi, MAKEINTRESOURCE(DIRABERTO32));
	ImageList_Add(*imageList32, hbmDIRETORIO32, NULL);
	ImageList_Add(*imageList32, hbmARQUIVO32, NULL);
	ImageList_Add(*imageList32, hbmDIRABERTO32, NULL);

	DeleteObject(hbmDIRETORIO);
	DeleteObject(hbmARQUIVO);
	DeleteObject(hbmDIRABERTO);
	DeleteObject(hbmDIRETORIO32);
	DeleteObject(hbmARQUIVO32);
	DeleteObject(hbmDIRABERTO32);
}

SYSTEMTIME Rotinas_DataHoraNow() {
	SYSTEMTIME sTempo;
	
	//GetSystemTime(&sTempo);
	GetLocalTime(&sTempo);

	return sTempo;
}

BOOL Rotinas_DataHoraComparar(SYSTEMTIME st1, SYSTEMTIME st2) {
	return (st1.wDay == st2.wDay &&
		st1.wMonth == st2.wMonth &&
		st1.wYear == st2.wYear &&
		st1.wHour == st2.wHour &&
		st1.wMinute == st2.wMinute &&
		st1.wSecond == st2.wSecond);
}

String Rotinas_formataDate(String formato, SYSTEMTIME sTempo) {	
	String sData = String_iniciar("");
	String sHora = String_iniciar("");
	String sDataHora = String_iniciar("");
	LCID local_id = LOCALE_USER_DEFAULT; //LOCALE_SYSTEM_DEFAULT;

	String sFrmtData = String_iniciar("dd/MM/yyyy");
	String sFrmtHora = String_iniciar("HH:mm:ss");

	if (String_comparar(formato, Rotinas_FORMATO_DATAHORA)) {
		GetDateFormat(local_id, 0, &sTempo, sFrmtData.wstr, sData.wstr, TAM_MAX_STR);
		GetTimeFormat(local_id, 0, &sTempo, sFrmtHora.wstr, sHora.wstr, TAM_MAX_STR);
		sData = String_copiar(sData.wstr);
		sHora = String_copiar(sHora.wstr);
		sDataHora = String_concatenar(sData, String_iniciar(" "), sHora);
	}
	if (String_comparar(formato, Rotinas_FORMATO_DHARQUIVO)) {
		GetDateFormat(local_id, 0, &sTempo, _T("yyyy-MM-dd"), sData.wstr, TAM_MAX_STR);
		GetTimeFormat(local_id, 0, &sTempo, _T("hh_mm_ss"), sHora.wstr, TAM_MAX_STR);
		sData = String_copiar(sData.wstr);
		sHora = String_copiar(sHora.wstr);
		sDataHora = String_concatenar(sData, String_iniciar("_"), sHora);
	}
	if (String_comparar(formato, Rotinas_FORMATO_DATA)) {
		GetDateFormat(local_id, 0, &sTempo, sFrmtData.wstr, sData.wstr, TAM_MAX_STR);
		sData = String_copiar(sData.wstr);
		sDataHora = String_concatenar(sDataHora, sData);
	}
	if (String_comparar(formato, Rotinas_FORMATO_HORA)) {
		GetTimeFormat(local_id, 0, &sTempo, sFrmtHora.wstr, sHora.wstr, TAM_MAX_STR);
		sHora = String_copiar(sHora.wstr);
		sDataHora = String_concatenar(sDataHora, sHora);
	}

	return sDataHora;
}

SYSTEMTIME Rotinas_StringToDate(String sData) {
	SYSTEMTIME sTempo{};
	String parte = String_iniciar("");
	String texto = String_Trim(sData);
	int pos1 = 0, pos2 = 0;

	if (texto.length > 0) {
		if (String_cPos("/", sData.str) > 0) {
			pos1 = String_cFind("/", sData.str, 0);
			parte = String_SubString(texto, pos1 - 1, pos1);
			sTempo.wDay = String_ToInt(parte);

			pos2 = String_cFind("/", sData.str, pos1 + 1);
			parte = String_SubString(texto, pos1 + 2, pos2 - pos1 - 1);
			sTempo.wMonth = String_ToInt(parte);

			parte = String_SubString(texto, pos2 + 2, 4);
			sTempo.wYear = String_ToInt(parte);

			if (sTempo.wYear < 1970)
				sTempo.wYear = 1970;
		}

		if (String_cPos(":", sData.str) > 0) {
			pos1 = String_cFind(":", sData.str, 0);
			parte = String_SubString(texto, pos1 - 1, 2);
			sTempo.wHour = String_ToInt(parte);

			pos2 = String_cFind(":", sData.str, pos1 + 1);
			parte = String_SubString(texto, pos1 + 2, pos2 - pos1 - 1);
			sTempo.wMinute = String_ToInt(parte);

			parte = String_SubString(texto, pos2 + 2, 2);
			sTempo.wSecond = String_ToInt(parte);
		}
		sTempo.wMilliseconds = 0;
	}
	return sTempo;
}

/*
LPTSTR Rotinas_FormataDataHoraStr(SYSTEMTIME sTempo, LPTSTR sFrmtData, 
    LPTSTR sFrmtHora)
{ LPTSTR sDataHora;
  TCHAR sData[TAM_MAX_STR], sHora[TAM_MAX_STR];  
  LCID local_id;

sDataHora = Rotinas_NewStr();

//local_id = MAKELCID(
//    MAKELANGID(LANG_PORTUGUESE, SUBLANG_PORTUGUESE_BRAZILIAN), SORT_DEFAULT);
local_id = LOCALE_SYSTEM_DEFAULT; //LOCALE_USER_DEFAULT

if (lstrlen(sFrmtData) > 0)
  GetDateFormat(local_id, 0, &sTempo, sFrmtData, sData, TAM_MAX_STR);
if (lstrlen(sFrmtHora) > 0)
  GetTimeFormat(local_id, 0, &sTempo, sFrmtHora, sHora, TAM_MAX_STR);

if (lstrlen(sFrmtData) > 0 && lstrlen(sFrmtHora) > 0)
  wsprintf(sDataHora, _T("%s %s"), sData, sHora);
else if (lstrlen(sFrmtData) > 0)
  wsprintf(sDataHora, _T("%s"), sData);
else if (lstrlen(sFrmtHora) > 0)
  wsprintf(sDataHora, _T("%s"), sHora);

  return sDataHora;
}

LPTSTR Rotinas_retDataHoraStr(BOOL bData, BOOL bHora)
{ LPTSTR sDataHora, sFormatoData, sFormatoHora, sVazio;
  SYSTEMTIME sTempo;
  
  sFormatoData = Rotinas_NewStr();
  lstrcpy(sFormatoData, _T("dd/MM/yyyy"));

  sFormatoHora = Rotinas_NewStr();
  lstrcpy(sFormatoHora, _T("HH:mm:ss"));

  sVazio = Rotinas_NewStr(2);
  lstrcpy(sFormatoHora, _T(""));

  GetSystemTime(&sTempo);
if (bData && bHora)
  sDataHora = Rotinas_FormataDataHoraStr(sTempo, sFormatoData, sFormatoHora);
else if (bData)
  sDataHora = Rotinas_FormataDataHoraStr(sTempo, sFormatoData, sVazio);
else if (bHora)
  sDataHora = Rotinas_FormataDataHoraStr(sTempo, sVazio, sFormatoHora);

return sDataHora;
}

LPTSTR Rotinas_ConverteDataHoraStr(LPTSTR sDTHR, BOOL DMY_ou_YMD, 
    LPTSTR sFrmtData, LPTSTR sFrmtHora)
{ LPTSTR sDataHora;
  SYSTEMTIME sTempo;

if (lstrlen(sFrmtData) > 0) {
  if (DMY_ou_YMD) {
	  
    sTempo.wDay = String_ToInt(Rotinas_SubString(sDTHR,1,2));
    sTempo.wMonth = String_ToInt(Rotinas_SubString(sDTHR,4,2));
    sTempo.wYear = String_ToInt(Rotinas_SubString(sDTHR,7,4));
  } else {
    sTempo.wYear = String_ToInt(Rotinas_SubString(sDTHR,1,4));
    sTempo.wMonth = String_ToInt(Rotinas_SubString(sDTHR,6,2));
    sTempo.wDay = String_ToInt(Rotinas_SubString(sDTHR,9,2));
  }
}
if (lstrlen(sFrmtHora) > 0) {
  sTempo.wHour = String_ToInt(Rotinas_SubString(sDTHR,12,2));
  sTempo.wMinute = String_ToInt(Rotinas_SubString(sDTHR,15,2));
  sTempo.wSecond = String_ToInt(Rotinas_SubString(sDTHR,18,2));
  sTempo.wMilliseconds = 0;
}
sDataHora = Rotinas_FormataDataHoraStr(sTempo,sFrmtData,sFrmtHora);
return sDataHora;
}
*/

String Rotinas_retTexto(HWND hwnd)
{
	String sValor = String_iniciar("");
	GetWindowText(hwnd, sValor.wstr, TAM_MAX_STR);
	sValor = String_copiar(sValor.wstr);

	return sValor;
}

LPWSTR Rotinas_lerStr(UINT nId)
{
	LPWSTR sValor = Rotinas_NewStr();
	LoadString(g_hInstancia, nId, sValor, TAM_MAX_STR);

	return sValor;
}
/*
HWND Rotinas_criaBotao(HWND hwnd, LPTSTR sTexto, INT id, INT x, INT y, 
    BOOL bHabilitado)
{ 
HWND hwndBotao;
DWORD nEstilo;

nEstilo = WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_TEXT; 
if (bHabilitado==FALSE) nEstilo += WS_DISABLED;

hwndBotao = CreateWindowEx(WS_EX_LEFT, _T("BUTTON"), sTexto,
    nEstilo, x, y, 75, 25, hwnd, (HMENU)id, 
    (HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

SendMessage(hwndBotao, WM_SETFONT, 
(WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));         
  
return hwndBotao;    
}

HWND Rotinas_criaRotulo(HWND hwnd, LPTSTR sTexto, INT id, INT x, INT y,
INT largura)
{
HWND hwndRotulo;
DWORD nEstilo;

nEstilo = WS_VISIBLE | WS_CHILD;

hwndRotulo = CreateWindowEx(WS_EX_LEFT, _T("STATIC"), sTexto,
nEstilo, x, y, largura, 21, hwnd, (HMENU)id,
(HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

SendMessage(hwndRotulo, WM_SETFONT,
(WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));

return hwndRotulo;
}
*/

HWND Rotinas_criaEdit(HWND hwnd, INT id, LPTSTR sTexto,
	INT x, INT y, INT largura, 
    BOOL bHabilitado, INT nMaxTam, BOOL bComSenha, BOOL bSoNumero)
{ 
HWND hwndEdit;
DWORD nEstilo;

nEstilo = WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_BORDER | ES_LEFT;
if (bHabilitado==FALSE) nEstilo += WS_DISABLED;
if (bComSenha) nEstilo += ES_PASSWORD;
if (bSoNumero) nEstilo += ES_NUMBER;

hwndEdit = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), sTexto,
    nEstilo, x, y, largura, 21, hwnd, (HMENU)id, 
    (HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

SendMessage(hwndEdit, WM_SETFONT,
(WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));

SendMessage(hwndEdit, EM_SETLIMITTEXT,(WPARAM) nMaxTam, 0);

return hwndEdit;
}


sqlite3* Rotinas_getConexao() {
	return dbConexao;
}

BOOL Rotinas_BancoConectar(String sFonteDeDados)
{
	const int ret = sqlite3_open_v2(sFonteDeDados.str, &dbConexao, SQLITE_OPEN_READWRITE, NULL);
	if (SQLITE_OK != ret)
	{
		Rotinas_BancoMostrarErro("Rotinas_BancoConectar");
		sqlite3_close(dbConexao);
		return FALSE;
	}
	return TRUE;
}

VOID Rotinas_BancoDesconectar()
{
	const int ret = sqlite3_close(dbConexao);
	(void)ret;
}

VOID Rotinas_BancoMostrarErro(const char* titulo) {
	int errcode = sqlite3_errcode(dbConexao);
	//int exterrcode = sqlite3_extended_errcode(dbConexao);
	char* errmsg = (char*)sqlite3_errmsg(dbConexao);	
	//const char* errstr = sqlite3_errstr(dbConexao);
	String sErro = String_iniciar(titulo);
	//wsprintf(sErro, _T("ERRO: %d - %s"), errcode, sErrMsg);
	sErro = String_concatenar(sErro, 4, "ERRO: ", String_cFromInt(errcode), " - ", errmsg);	
	OutputDebugString(sErro.wstr);
	MessageBox(NULL, sErro.wstr, _T("Banco Mostrar Erro"), MB_ICONERROR | MB_OK);
}

INT Rotinas_BancoExec(String sSQL)
{
	const int ret = sqlite3_exec(dbConexao, sSQL.str, NULL, NULL, NULL);
	if (SQLITE_OK != ret)
	{
		Rotinas_BancoMostrarErro("Rotinas_BancoExec");
	}
	return sqlite3_changes(dbConexao);
}

BOOL Rotinas_BancoPasso(sqlite3_stmt* pstmt) {
	BOOL mbOk = FALSE;

	const int ret = sqlite3_step(pstmt);

	if (SQLITE_ROW == ret) {
		mbOk = TRUE;
	} else if (SQLITE_DONE == ret) {
		mbOk = FALSE;
	} else {
		Rotinas_BancoMostrarErro("Rotinas_BancoPasso");
		mbOk = FALSE;
	}

	return mbOk;
}

INT Rotinas_BancoExecPasso(sqlite3_stmt* pstmt, int ret, const char* titulo) {
	int res = 0;

	if (ret == SQLITE_OK) {
		if (sqlite3_step(pstmt) == SQLITE_DONE) {
			res = sqlite3_changes(Rotinas_getConexao());
		}
	}
	else {
		Rotinas_BancoMostrarErro(titulo);
	}

	return res;
}
/*
VOID Rotinas_AdicionaItemLista(HWND lstLista,
     ListaString *slCodLista, HWND sCampoCodigo, HWND sCampoDesc)
{
String sItems, sCodigo, sDesc;

sItems = String_iniciar("");
sCodigo = String_iniciar("");
sDesc = String_iniciar("");

if (GetWindowTextLength(sCampoDesc) > 0) {

 GetWindowText(sCampoCodigo, sCodigo.wstr, TAM_MAX_STR);
 GetWindowText(sCampoDesc, sDesc.wstr, TAM_MAX_STR);

 //wsprintf(sItems, _T("%s%s%s"), sCodigo, " - ", sDesc);
 sItems = String_concatenar(sItems, 3, sCodigo.str, " - ", sDesc.str);

 if (SendMessage(lstLista, LB_FINDSTRING, 0, (LPARAM) sItems.wstr)==LB_ERR)
 { 
	ListaString_insereFim(slCodLista, sCodigo);
	SendMessage(lstLista, LB_ADDSTRING, 0, (LPARAM) sItems.wstr);
 }
 SetWindowText(sCampoCodigo, _T(""));
 SetWindowText(sCampoDesc, _T(""));
}

}

VOID Rotinas_RemoveItemLista(HWND lstLista, ListaString *slCodLista)
{
INT nSelIndice;

 if (SendMessage(lstLista, LB_GETCOUNT, 0, 0) > 0) {   
   nSelIndice = SendMessage(lstLista, LB_GETCURSEL, 0, 0);
   //if (nSelIndice != LB_ERR) {
   if (SendMessage(lstLista, LB_GETSEL, (WPARAM) nSelIndice, 0) > 0) {
	   ListaString_removeItemOrd(slCodLista, nSelIndice, TRUE);
	   SendMessage(lstLista, LB_DELETESTRING, (WPARAM) nSelIndice, 0);
   }	
 }
}

VOID Rotinas_AdicionaValoresLista(String sTextoSql, HWND lstLista, ListaString *slCodLista)
{
	
  ListaMString Campos, local;
  String sItems, sCodigo;

  sItems = Rotinas_alocaString();
  sCodigo = Rotinas_alocaString();

  SendMessage(lstLista, LB_RESETCONTENT,0,0);
  (*slCodLista) = ListaString_inicia();

  if (Rotinas_ConsultaDadosLista(gConexao, &Campos, sTextoSql)) {
	  for (local = Campos; local != NULL; local = local->proximo) {	
	    ListaStr_insereFim(slCodLista, local->str[0]);
	    wsprintf(sItems, "%s - %s", local->str[0], local->str[1]);
	    SendMessage(lstLista, LB_ADDSTRING, 0, (LPARAM) sItems);		
	  }      
  }
  ListaString_liberaM(Campos);
  ListaString_liberaM(local);
  
}
*/

VOID Rotinas_copiaBitmap(HWND hwnd, INT idBMP, RECT rc)
{
HDC hDC; 
HDC hDCMem; 
PAINTSTRUCT ps; 
HBITMAP hBMP; 
       
hDC = BeginPaint(hwnd, &ps);            
hDCMem = CreateCompatibleDC(hDC); 
if (hDCMem != NULL) 
{ 
  hBMP = LoadBitmap((HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),
    MAKEINTRESOURCE(idBMP));	
  SelectObject(hDCMem, hBMP);  
  BitBlt(hDC, rc.left, rc.top, rc.right, rc.bottom, hDCMem, 0, 0, SRCCOPY); 
  DeleteDC(hDCMem); 
}            
EndPaint(hwnd, &ps); 
}                

HBITMAP Rotinas_BitmapToHBitmap(const BITMAP bmp) {
	HDC hDC = GetDC(NULL);
	HDC hDCMem = CreateCompatibleDC(hDC);
	HBITMAP hBMP = CreateBitmapIndirect(&bmp);
	SelectObject(hDCMem, hBMP);
	
	/*
	HBITMAP hBMP = CreateBitmap(
		bmp.bmWidth,
		bmp.bmHeight,
		bmp.bmPlanes,
		bmp.bmBitsPixel,
		bmp.bmBits
	);
	*/

	return hBMP;
}


HWND Rotinas_pegaBarraProgresso(HWND hwnd, int nIDDlgItem, int nMin, int nMax, int nPasso) {
	int nPosicao = 0;

	HWND hPb = GetDlgItem(hwnd, nIDDlgItem);

	SendMessage(hPb, PBM_SETRANGE, 0, MAKELPARAM(nMin, nMax));
	SendMessage(hPb, PBM_SETSTEP, nPasso, 0);
	SendMessage(hPb, PBM_SETPOS, nPosicao, 0);

	return hPb;
}

BOOL Rotinas_criarVisao(String visao) {
	String sSQL = String_iniciar("");

	sSQL= String_concatenar(sSQL, 3,
	"create view ", visao.str, " as " \
		"SELECT d.aba,d.cod,d.ordem,d.coddirpai,d.nome,d.tam,d.tipo,d.modificado," \
		"d.atributos,d.caminho" \
		",(select nome as nomeaba from Abas where cod=d.aba) as nomeaba" \
		",(select nome as nomepai from Diretorios where cod=d.cod " \
		"  and ordem=d.coddirpai and aba=d.aba) as nomepai" \
		",(select caminho as caminhopai from Diretorios where cod=d.cod " \
		" and ordem=d.coddirpai and aba=d.aba) as caminhopai " \
		"FROM Diretorios d ");

	if (String_comparar(visao, "consultadirpai"))
		sSQL = String_concatenar(sSQL, "where d.tipo='D' and d.coddirpai = 0");
	else if (String_comparar(visao, "consultadirfilho"))
		sSQL = String_concatenar(sSQL, "where d.tipo='D' and d.coddirpai > 0");
		
	return Rotinas_BancoExec(sSQL);
}

String Rotinas_MontaTamanhoBig(long double nTam) {
	String fmt;
	String ret = String_iniciar("");
	long long nUmKilo, nUmMega, nUmGiga, nUmTera, nUmPeta;

	nUmKilo = 1024;
	nUmMega = nUmKilo * nUmKilo;
	nUmGiga = nUmMega * nUmKilo;
	nUmTera = nUmGiga * nUmKilo;
	nUmPeta = nUmTera * nUmKilo;

	if (nTam < nUmKilo) {		
		fmt = String_FromLongDouble(nTam);
		ret = String_concatenar(fmt, " Byte(s)");
		return ret;
	}
	else if (nTam > nUmKilo && nTam < nUmMega) {
		nTam = nTam / nUmKilo;
		fmt = String_FromLongDouble(nTam);
		ret = String_concatenar(fmt, " KByte(s)");
		return ret;
	}
	else if (nTam > nUmMega && nTam < nUmGiga) {
		nTam = nTam / nUmMega;
		fmt = String_FromLongDouble(nTam);
		ret = String_concatenar(fmt, " MByte(s)");
		return ret;
	}
	else if (nTam > nUmGiga && nTam < nUmTera) {
		nTam = nTam / nUmGiga;
		fmt = String_FromLongDouble(nTam);
		ret = String_concatenar(fmt, " GByte(s)");
		return ret;
	}
	else if (nTam > nUmTera && nTam < nUmPeta) {
		nTam = nTam / nUmTera;
		fmt = String_FromLongDouble(nTam);
		ret = String_concatenar(fmt, " TByte(s)");
		return ret;
	}
	else {
		nTam = nTam / nUmPeta;
		fmt = String_FromLongDouble(nTam);
		ret = String_concatenar(fmt, " PByte(s)");
		return ret;
	}
}

String Rotinas_MontaTamanho(long long nTam) {
	String ret = String_iniciar("");

	if (nTam > 0) {
		return Rotinas_MontaTamanhoBig((long double)nTam);
	}
	else {
		return ret;
	}
}


String Rotinas_testaNull(const char* res) {
	return (res == NULL ? String_limpar() : String_iniciar(String_cTrim(res)));
}

String Rotinas_trocaSeparador(String texto) {
	String retorno = String_iniciar("");

	if (texto.length > 0) {
		retorno = String_ReplaceAll(texto, Rotinas_BARRA_NORMAL.str, Rotinas_BARRA_INVERTIDA.str);
	}

	return retorno;
}

String Rotinas_AppDirPath() {
	String sCaminho = String_iniciar("");
	GetModuleFileName(g_hInstancia, sCaminho.wstr, MAX_PATH);
	sCaminho = String_iniciar(sCaminho.wstr);
	return sCaminho;
}

String Rotinas_AppDirName() {
	String sCaminho = String_iniciar("");
	GetModuleFileName(g_hInstancia, sCaminho.wstr, MAX_PATH);

	sCaminho = String_iniciar(sCaminho.wstr);
	int pos = String_cLastIndexOf(sCaminho.str, '\\') + 1;
	sCaminho = String_SubString(sCaminho, 1, pos);

	return sCaminho;
}

String Rotinas_AppFileName() {
	String sCaminho = String_iniciar("");
	GetModuleFileName(g_hInstancia, sCaminho.wstr, MAX_PATH);

	sCaminho = String_iniciar(sCaminho.wstr);
	int pos = String_cLastIndexOf(sCaminho.str, '\\') + 2;
	sCaminho = String_SubString(sCaminho, pos, sCaminho.length);

	return sCaminho;
}

String Rotinas_ExtractFileName(String sCaminho){
	int pos = String_cLastIndexOf(sCaminho.str, '\\') + 2;
	sCaminho = String_SubString(sCaminho, pos, sCaminho.length);

	return sCaminho;
}

String Rotinas_ExtractFilePath(String sCaminho)
{
	/*
	WCHAR cCaminho[MAX_PATH];
	DWORD  tamanho = lstrlen(sCaminho);

	DWORD dwRet = GetCurrentDirectory(tamanho, cCaminho);

	if (dwRet != 0) {
		lstrcpy(retorno, cCaminho);
	}
	*/
	int pos = String_cLastIndexOf(sCaminho.str, '\\') + 1;
	sCaminho = String_SubString(sCaminho, 1, pos);

	return sCaminho;
}

BOOL Rotinas_FileExists(String sNomeArquivo)
{
	DWORD atributos = GetFileAttributes(sNomeArquivo.wstr);

	if (atributos == INVALID_FILE_ATTRIBUTES) {
		return FALSE;
	}
	if (atributos & FILE_ATTRIBUTE_ARCHIVE) {
		return TRUE;
	}

	return FALSE;
}

BOOL Rotinas_DirectoryExists(String sNomeArquivo)
{
	DWORD atributos = GetFileAttributes(sNomeArquivo.wstr);

	if (atributos == INVALID_FILE_ATTRIBUTES) {
		return FALSE;
	}
	if (atributos & FILE_ATTRIBUTE_DIRECTORY) {
		return TRUE;
	}

	return FALSE;
}

BOOL Rotinas_DeleteFromFile(String sNomeArquivo) {
	return DeleteFile(sNomeArquivo.wstr);
}

Arquivo Rotinas_FileInfoToArquivo(WIN32_FIND_DATA finder) {
	String sAtributos = String_iniciar("");
	Arquivo arquivo;
	DWORD atributos = 0; //tamanho = 0
	//FILETIME ftCriacao, ftAcesso, ftEscrita;
	SYSTEMTIME stUTC, stLocal;
		
	//arquivo.nome = String_copiar(Rotinas_ExtractFileName(sNomeArquivo));
	arquivo.nome = String_iniciar(finder.cFileName);

	//tamanho = GetFileSize(hFile, &tamanho);	
	if (finder.nFileSizeHigh != 0)
		arquivo.tamanho = finder.nFileSizeHigh;
	else
		arquivo.tamanho = finder.nFileSizeLow;
	
	/*
	if (GetFileTime(hFile, &ftCriacao, &ftAcesso, &ftEscrita)) {
		FileTimeToSystemTime(&ftEscrita, &stUTC);
		SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
		arquivo.modificado = stLocal;
	}
	else {
		arquivo.modificado = Rotinas_DataHoraNow();
	}
	*/	
	FileTimeToSystemTime(&finder.ftLastWriteTime, &stUTC);
	SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
	arquivo.modificado = stLocal;
	
	//atributos = GetFileAttributes(sNomeArquivo.wstr);
	atributos = finder.dwFileAttributes;

	if (atributos != INVALID_FILE_ATTRIBUTES) {
		if (atributos & FILE_ATTRIBUTE_READONLY) 
			sAtributos = String_concatenar(sAtributos, "[ROL]");
		if (atributos & FILE_ATTRIBUTE_HIDDEN) 
			sAtributos = String_concatenar(sAtributos, "[HID]");
		if (atributos & FILE_ATTRIBUTE_SYSTEM) 
			sAtributos = String_concatenar(sAtributos, "[SYS]");
		if (atributos & FILE_ATTRIBUTE_DIRECTORY) 
			sAtributos = String_concatenar(sAtributos, "[DIR]");
		if (atributos & FILE_ATTRIBUTE_ARCHIVE) 
			sAtributos = String_concatenar(sAtributos, "[ARQ]");
		
		arquivo.atributos = String_copiar(sAtributos);
	}
	else {
		arquivo.atributos = String_limpar();
	}

	return arquivo;
}

HBITMAP Rotinas_iconeToBitmapFromID(WORD idIcone, int largura, int altura) {

	HICON hIcon = (HICON)LoadImage(g_hInstancia,
		MAKEINTRESOURCEW(idIcone), IMAGE_ICON, largura, altura, 0);
	ICONINFO iconinfo;
	GetIconInfo(hIcon, &iconinfo);
	HBITMAP hBitmap = iconinfo.hbmColor;

	return hBitmap;
}

HBITMAP Rotinas_iconeToBitmap(HICON hIcon, int tamanho) {
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

HBITMAP Rotinas_extrairIconeArquivo(String sNomeArquivo, int tamanho) {
	WORD filtro = 0;
	//WORD indice;

	//HINSTANCE hInstance = GetModuleHandle(NULL);
	HICON icone = ExtractAssociatedIcon(g_hInstancia, sNomeArquivo.wstr, &filtro);
	//HICON icone = ExtractAssociatedIconEx(g_hInstancia, sNomeArquivo.wstr, &indice, &filtro);
	HBITMAP hbmp = Rotinas_iconeToBitmap(icone, tamanho);

	return hbmp;
}

HBITMAP Rotinas_HBitmapFromBlob(void* blob, long larguraAltura) {
	
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

BITMAP Rotinas_BitmapFromBlob(void* blob, long larguraAltura) {
	BITMAP bitmap;
	HBITMAP hbitmap = Rotinas_HBitmapFromBlob(blob, larguraAltura);
	int error = GetObject(hbitmap, sizeof(BITMAP), &bitmap);

	return bitmap;
}

HBITMAP Rotinas_HBitmapLoadFromFile(String sNomeArquivo) {
	HBITMAP hbm = 0;

	hbm = (HBITMAP)LoadImage(0, sNomeArquivo.wstr, IMAGE_BITMAP, 0, 0, 
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	return hbm;
}

BITMAP Rotinas_BitmapLoadFromFile(String sNomeArquivo) {
	HBITMAP hbm = 0;
	BITMAP bitmap;

	hbm = (HBITMAP)LoadImage(0, sNomeArquivo.wstr, IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	int error = GetObject(hbm, sizeof(BITMAP), &bitmap);

	return bitmap;
}

BOOL Rotinas_FileExists2(String sNomeArquivo) {
	HFILE hFile;
	OFSTRUCT ofstruct{};
	BOOL retorno = FALSE;

	hFile = OpenFile(sNomeArquivo.str, &ofstruct, OF_EXIST);
	if (hFile != HFILE_ERROR) {
		retorno = TRUE;
	}
	CloseHandle((HANDLE)hFile);
	return retorno;
}

BOOL Rotinas_SaveTextToFile(String sTexto, String sNomeArquivo) {
	BOOL ret = FALSE;
	HANDLE hFile;
		
	const char* DataBuffer = sTexto.str;
	DWORD dwBytesToWrite = (DWORD)strlen(DataBuffer);
	DWORD dwBytesWritten = 0;
	BOOL bErrorFlag = FALSE;

	hFile = CreateFile(sNomeArquivo.wstr, GENERIC_WRITE, 0, NULL, 
		CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);                

	if (hFile != INVALID_HANDLE_VALUE) {
		bErrorFlag = WriteFile(hFile, DataBuffer, dwBytesToWrite, &dwBytesWritten, NULL);

		if (bErrorFlag == FALSE) {
			printf("Erro\n");
		} else if (dwBytesWritten != dwBytesToWrite) {
			printf("Erro\n");
		} else {
			ret = TRUE;
		}
	}
	CloseHandle(hFile);
	return ret;
}

BOOL Rotinas_SListSaveToFile(ListaString lista, String sNomeArquivo) {
	BOOL ret = FALSE;
	HANDLE hFile;
	ListaString local;
	String linha = String_iniciar("");
	const char* DataBuffer;
	DWORD dwBytesToWrite = 0;
	DWORD dwBytesWritten = 0;
	BOOL bErrorFlag = FALSE;

	hFile = CreateFile(sNomeArquivo.wstr, GENERIC_WRITE, 0, NULL,
		CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile != INVALID_HANDLE_VALUE) {
		for (local = lista; local != NULL; local = local->proximo) {
			linha = String_concatenar(local->str, "\n");

			DataBuffer = linha.str;
			dwBytesToWrite = (DWORD)strlen(DataBuffer);

			bErrorFlag = WriteFile(hFile, DataBuffer, dwBytesToWrite, &dwBytesWritten, NULL);

			if (bErrorFlag == FALSE) {
				break;
			}
			else if (dwBytesWritten != dwBytesToWrite) {
				break;
			}
			else {
				ret = TRUE;
			}
		}	
	}
	CloseHandle(hFile);
	return ret;
}

ListaString Rotinas_SListLoadFromFile(String sNomeArquivo) {
	ListaString lista = ListaString_inicia();
	HANDLE hFile;
	String linha;
	char DataBuffer[TAM_MAX_STR];
	DWORD dwBytesToRead = 0;
	DWORD dwBytesReaded = 0;
	BOOL bErrorFlag = FALSE;

	hFile = CreateFile(sNomeArquivo.wstr, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile != INVALID_HANDLE_VALUE) {
		dwBytesToRead = GetFileSize(hFile, &dwBytesToRead);

		DataBuffer[0] = '\0';

		bErrorFlag = ReadFile(hFile, DataBuffer, dwBytesToRead, &dwBytesReaded, NULL);

		if (bErrorFlag == TRUE && dwBytesReaded == dwBytesToRead) {		
			linha = String_iniciar(DataBuffer);
			lista = Rotinas_SListSeparador(linha, '\n');
		}		
	}
	CloseHandle(hFile);

	return lista;
}

ListaString Rotinas_SListSeparador(String texto, char separador) {
	ListaString lista = ListaString_inicia();
	String pedaco = String_iniciar("");
	String sepa = String_iniciar(separador);
	String parte = String_iniciar("");
	
	if (String_cContainsStr(texto.str, sepa.str)) {
		for (unsigned int i = 0; i < texto.length; i++) {
			pedaco = String_concatenar(pedaco, texto.str[i]);

			if (texto.str[i] == separador) {
				parte = String_SubString(pedaco, 1, pedaco.length-1);
				ListaString_insereFim(&lista, parte);
				pedaco = String_limpar();
			}
		}
		
		if (pedaco.length > 0) {
			ListaString_insereFim(&lista, pedaco);
		}
	}
	else {
		ListaString_insereFim(&lista, texto);
	}

	return lista;
}

String Rotinas_SListTexto(ListaString lista) {
	ListaString local;
	String texto = String_iniciar("");
	UINT ntamlista = ListaString_conta(lista);

	if (ntamlista > 0) {
		for (local = lista; local != NULL; local = local->proximo) {
			texto = String_concatenar(texto, local->str);
		}
	}

	return texto;
}

ListaString Rotinas_listarArquivosDiretorios(String sDiretorio) {
	ListaString lista = ListaString_inicia();
	WIN32_FIND_DATA finder;
	HANDLE hFile;
	String sCaminho = String_iniciar("");
	String sdir = String_iniciar(sDiretorio.str);

	if (Rotinas_DirectoryExists(sDiretorio)) {
		sdir = String_concatenar(sdir, "\\*.*");

		hFile = FindFirstFile(sdir.wstr, &finder);
		
		if (hFile != INVALID_HANDLE_VALUE) {

			do {

				if (lstrcmp(finder.cFileName, _T(".")) == 0
					|| lstrcmp(finder.cFileName, _T("..")) == 0) {
					continue;
				}

				if (finder.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
					sCaminho = String_copiar(finder.cFileName);
					ListaString_insereFim(&lista, sCaminho);
					//se for buscar subdiretorio
					//listarArquivosDiretorios(sCaminho);
				}
				else {
					sCaminho = String_copiar(finder.cFileName);
					ListaString_insereFim(&lista, sCaminho);
				}
			} while (FindNextFile(hFile, &finder) != 0);

		} else {
			//if (GetLastError() == ERROR_FILE_NOT_FOUND)			
		}		

		FindClose(hFile);
	}

	return lista;
}

BOOL Rotinas_BlobSaveToFile(const void* blob, size_t tamanho, String sNomeArquivo) {
	BOOL ret = TRUE;
	FILE* fp;
	errno_t erro;

	erro = fopen_s(&fp, sNomeArquivo.str, "wb");
	
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

long Rotinas_BlobLoadFromFile(String sNomeArquivo, void** blob) {
	long ret = 0;
	FILE* fp;
	errno_t erro;
//	long tamanho;
	
	erro = fopen_s(&fp, sNomeArquivo.str, "rb");

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

VOID Rotinas_errhandler(LPCWSTR erro, HWND hwd) {	
	erro = lstrcat(const_cast<LPTSTR>(TEXT("ERRO: Rotinas_BitmapSaveToFile: ")), erro);
	MessageBox(hwd, erro, _T("Erro"), MB_ICONERROR | MB_OK);
}

PBITMAPINFO Rotinas_CreateHBitmapInfoStruct(HWND hwnd, HBITMAP hBmp)
{
	BITMAP bmp;
	PBITMAPINFO pbmi;
	WORD    cClrBits;

	// Retrieve the bitmap color format, width, and height.  
	if (!GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp))
		Rotinas_errhandler(_T("GetObject"), hwnd);

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

void Rotinas_CriarHBitmapFile(HWND hwnd, LPTSTR pszFile, PBITMAPINFO pbi,
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
		Rotinas_errhandler(_T("GlobalAlloc"), hwnd);

	// Retrieve the color table (RGBQUAD array) and the bits
	// (array of palette indices) from the DIB.
	if (!GetDIBits(hDC, hBMP, 0, (WORD)pbih->biHeight, lpBits, pbi, 
		DIB_RGB_COLORS))
	{
		Rotinas_errhandler(_T("GetDIBits"), hwnd);
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
		Rotinas_errhandler(_T("CreateFile"), hwnd);
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
		Rotinas_errhandler(_T("WriteFile"), hwnd);
	}

	// Copy the BITMAPINFOHEADER and RGBQUAD array into the file.  
	if (!WriteFile(hf, (LPVOID)pbih, sizeof(BITMAPINFOHEADER)
		+ pbih->biClrUsed * sizeof(RGBQUAD),
		(LPDWORD)&dwTmp, (NULL)))
		Rotinas_errhandler(_T("WriteFile"), hwnd);

	// Copy the array of color indices into the .BMP file.  
	dwTotal = cb = pbih->biSizeImage;
	hp = lpBits;
	if (!WriteFile(hf, (LPSTR)hp, (int)cb, (LPDWORD)&dwTmp, NULL))
		Rotinas_errhandler(_T("WriteFile"), hwnd);

	// Close the .BMP file.  
	if (!CloseHandle(hf))
		Rotinas_errhandler(_T("CloseHandle"), hwnd);

	// Free memory.  
	GlobalFree((HGLOBAL)lpBits);
}

BOOL Rotinas_HBitmapSaveToFile(HBITMAP hBMP, String sNomeArquivo) {
	HDC hDC = GetDC(NULL);
	HDC hDCMem = CreateCompatibleDC(hDC);
	PBITMAPINFO pbi = Rotinas_CreateHBitmapInfoStruct(0, hBMP);
	Rotinas_CriarHBitmapFile(0, sNomeArquivo.wstr, pbi, hBMP, hDC);
	return Rotinas_FileExists(sNomeArquivo);
}

BITMAP Rotinas_BlobToBitmap(const void* blobBmp, int tamanhoBmp, HIMAGELIST *imageList) {
	BITMAP bmp;
	HBITMAP hbmp;

	String app = Rotinas_AppDirName();
	String arquivo = String_iniciar("temp.bmp");
	arquivo = String_concatenar(app, arquivo);

	if (Rotinas_BlobSaveToFile(blobBmp, tamanhoBmp, arquivo)) {
		hbmp = Rotinas_HBitmapLoadFromFile(arquivo);
		ImageList_Add(*imageList, hbmp, NULL);
		bmp = Rotinas_BitmapLoadFromFile(arquivo);
	}
	remove(arquivo.str);

	return bmp;
}

BITMAP Rotinas_HBitmapToBitmap(HBITMAP hBMP, HIMAGELIST *imageList) {
	BITMAP bmp;

	String app = Rotinas_AppDirName();
	String arquivo = String_iniciar("temp.bmp");
	arquivo = String_concatenar(app, arquivo);

	if (Rotinas_HBitmapSaveToFile(hBMP, arquivo)) {
		ImageList_Add(*imageList, hBMP, NULL);
		bmp = Rotinas_BitmapLoadFromFile(arquivo);
	}
	remove(arquivo.str);

	return bmp;
}

int Rotinas_BitmapToBlob(BITMAP bmp, void** blobBmp) {
	String app = Rotinas_AppDirName();
	String arquivo = String_iniciar("temp.bmp");
	arquivo = String_concatenar(app, arquivo);

	HBITMAP hBMP = CreateBitmapIndirect(&bmp);

	if (Rotinas_HBitmapSaveToFile(hBMP, arquivo)) {
		return Rotinas_BlobLoadFromFile(arquivo, blobBmp);
	}

	return -1;
}

VOID Rotinas_testar() {
	String saida = String_iniciar("");
	String sApp = Rotinas_AppDirPath();
	String sDir = String_iniciar("");
	sDir = String_copiar("    c:\\ago%ra\\CAMINHO\\teste.olha.depois    ");

	/*
	ListaString listaDir, localDir;
	WCHAR linhaDir[TAM_MAX_STR] = _T("");

	listaDir = Rotinas_listarArquivosDiretorios(_T("c:\\Temp"));

	unsigned int nlinha = 0;
	for (localDir = listaDir; localDir != NULL; localDir = localDir->proximo)
	{
		lstrcpy(linhaDir, localDir->str);
		wsprintf(saida, _T("listarArquivosDiretorios[%d]: %s\n"), nlinha, linhaDir);
		OutputDebugString(saida);
		nlinha++;
	}
	ListaString_removeTodos(listaDir);	
	listaDir = NULL;

	wsprintf(saida, _T("sDir: [%s]\n"), sDir); OutputDebugString(saida);
	wsprintf(saida, _T("AppDirPath: %s\n"), sApp); OutputDebugString(saida);
	wsprintf(saida, _T("FileExists: %s\n"), (Rotinas_FileExists(sApp) ? _T("true") : _T("false"))); OutputDebugString(saida);
	wsprintf(saida, _T("DirectoryExists: %s\n"), (Rotinas_DirectoryExists(sApp) ? _T("true") : _T("false"))); OutputDebugString(saida);
	wsprintf(saida, _T("ExtractFilePath: %s\n"), Rotinas_ExtractFilePath(sApp)); OutputDebugString(saida);
	wsprintf(saida, _T("ExtractFileName: %s\n"), Rotinas_ExtractFileName(sApp)); OutputDebugString(saida);

	swprintf_s(saida, 40, _T("Length(): %d\n"), lstrlen(sDir)); OutputDebugString(saida);
	LPWSTR sTrim = Rotinas_Trim(sDir);
	wsprintf(saida, _T("Trim(): [%s]\n"), sTrim); OutputDebugString(saida);
	swprintf_s(saida, 40, _T("tamanho Trim(): %d\n"), lstrlen(sTrim)); OutputDebugString(saida);
	wsprintf(saida, _T("LowerCase(): %s\n"), Rotinas_LowerCase(sDir)); OutputDebugString(saida);
	wsprintf(saida, _T("UpperCase(): %s\n"), Rotinas_UpperCase(sDir)); OutputDebugString(saida);
	wsprintf(saida, _T("Pos('.'): %d\n"), Rotinas_Pos(_T("."), sDir)); OutputDebugString(saida);
	swprintf_s(saida, 40, _T("LastDelimiter('.'): %d\n"), Rotinas_LastDelimiter(_T("."), sDir)); OutputDebugString(saida);
	wsprintf(saida, _T("QuotedStr(): %s\n"), Rotinas_QuotedStr(sDir)); OutputDebugString(saida);
	wsprintf(saida, _T("IntToStr(245789): %s\n"), Rotinas_IntToStr(245789)); OutputDebugString(saida);
	swprintf_s(saida, 40, _T("StrToInt() --> 245789: %d\n"), String_ToInt(_T("245789"))); OutputDebugString(saida);
	swprintf_s(saida, 40, _T("StrToLong() --> 4200155136: %llu\n"), Rotinas_StrToLong(_T("4200155136"))); OutputDebugString(saida);
	wsprintf(saida, _T("DoubleToStr(15.557878): %s\n"), Rotinas_DoubleToStr(15.557878)); OutputDebugString(saida);

	wsprintf(saida, _T("SubString(): %s\n"), Rotinas_SubString(sDir, 8, 6)); OutputDebugString(saida);
	wsprintf(saida, _T("StringReplaceAll(): [%s]\n"), Rotinas_StringReplaceAll(sDir, _T("\\"), _T("@"))); 
//	OutputDebugString(saida);
	wsprintf(saida, _T("trocaSeparador(): [%s]\n"), Rotinas_trocaSeparador(sDir)); 
//	OutputDebugString(saida);
	wsprintf(saida, _T("testaNull(NULL): %s\n"), Rotinas_testaNull(NULL)); OutputDebugString(saida);

	wsprintf(saida, _T("StartsStr(DVD, JOGOS2_DVDS/TESTE): %s\n"), (Rotinas_StartsStr(_T("DVD"), _T("JOGOS2_DVDS/TESTE")) ? _T("true") : _T("false"))); OutputDebugString(saida);
	wsprintf(saida, _T("StartsStr(DVD, DVDSJOGOS2_/TESTE): %s\n"), (Rotinas_StartsStr(_T("DVD"), _T("DVDSJOGOS2_/TESTE")) ? _T("true") : _T("false"))); OutputDebugString(saida);

	wsprintf(saida, _T("ContainsStr(JOGOS2_DVDS/TESTE): %s\n"), (Rotinas_ContainsStr(_T("DVDSJOGOS2_/TESTE"), _T("DVDSJOGOS2_/TESTE")) ? _T("true") : _T("false"))); 
//	OutputDebugString(saida);
	wsprintf(saida, _T("EndsStr(TESTE, JOGOS2_DVDS/TESTE): %s\n"), (Rotinas_EndsStr(_T("TESTE"), _T("DVDSJOGOS2_/TESTE")) ? _T("true") : _T("false"))); 
//	OutputDebugString(saida);

	wsprintf(saida, _T("formataDate(): %s\n"), Rotinas_formataDate(Rotinas_FORMATO_DATAHORA, Rotinas_DataHoraNow())); 
//	OutputDebugString(saida);
	SYSTEMTIME dt = Rotinas_StringToDate(_T("03/02/2017 15:23:32"));
	wsprintf(saida, _T("StringToDate(03/02/2017 15:23:32): %s\n"), Rotinas_formataDate(Rotinas_FORMATO_DATAHORA, dt)); 
	OutputDebugString(saida);

	wsprintf(saida, _T("FormatLong(4200155136): %s\n"), Rotinas_FormatLong(4200155136));
//	OutputDebugString(saida);
	wsprintf(saida, _T("FormatDouble(15.544878): %s\n"), Rotinas_FormatDouble(15.544878));
//	OutputDebugString(saida);
	wsprintf(saida, _T("FormatDouble(15.547878): %s\n"), Rotinas_FormatDouble(15.547878)); 
//	OutputDebugString(saida);
	wsprintf(saida, _T("FormatDouble(15.557878): %s\n"), Rotinas_FormatDouble(15.557878)); 
//	OutputDebugString(saida);
	wsprintf(saida, _T("FormatDouble(15.567878): %s\n"), Rotinas_FormatDouble(15.567878)); 
//	OutputDebugString(saida);

	wsprintf(saida, _T("MontaTamanho() --> 3.91 GB: %s\n"), Rotinas_MontaTamanho(4200155136)); OutputDebugString(saida);
	wsprintf(saida, _T("MontaTamanho() --> 3.50 GB: %s\n"), Rotinas_MontaTamanho(3757244416)); OutputDebugString(saida);
	wsprintf(saida, _T("MontaTamanho() --> 2.29 GB: %s\n"), Rotinas_MontaTamanho(2455207936)); OutputDebugString(saida);
	//wsprintf(saida, _T("MontaTamanho() --> 888.18 PB: %s\n"), Rotinas_MontaTamanhoBig(999999999999999999.9999)); 
	//OutputDebugString(saida);
	*/
	ListaString lista, local;
	String linha = String_iniciar("");

	lista = Rotinas_SListSeparador(sDir, '\\');

	UINT tamlista = ListaString_conta(lista);
	
	unsigned int i = 0;
	for (local = lista; local != NULL; local = local->proximo)
	{
		linha = String_copiar(local->str);
		wsprintf(saida.wstr, _T("SListSeparador[%d]: %s\n"), i, linha); OutputDebugString(saida.wstr);
		i++;
	}

	String arquivo = Rotinas_ExtractFilePath(sApp);
	arquivo = String_concatenar(arquivo, "exemplo.txt");

	wsprintf(saida.wstr, _T("arquivo: %s\n"), arquivo); OutputDebugString(saida.wstr);

	//Rotinas_SaveToFile(_T("TESTE"), arquivo);

	
	if (Rotinas_SListSaveToFile(lista, arquivo)) {

		if (Rotinas_FileExists(arquivo)) {

			lista = Rotinas_SListLoadFromFile(arquivo);

			UINT tamlista = ListaString_conta(lista);

			unsigned int i = 0;
			for (local = lista; local != NULL; local = local->proximo){
				linha = String_copiar(local->str);
				wsprintf(saida.wstr, _T("SListLoadFromFile[%d]: %s\n"), i, linha); OutputDebugString(saida.wstr);
				i++;
			}

			if (Rotinas_DeleteFromFile(arquivo)) {
				if (!Rotinas_FileExists(arquivo)) {
					wsprintf(saida.wstr, _T("DeleteFromFile: OK\n"));
					OutputDebugString(saida.wstr);
				}
			}
			else {
				wsprintf(saida.wstr, _T("DeleteFromFile: FALHOU\n")); OutputDebugString(saida.wstr);
			}

		}

	}

	ListaString_removeTodos(&lista);
	ListaString_libera(&lista);
}
