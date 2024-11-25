#include "stdafx.h"

#include "String.h"

#include <stdio.h>
#include <stdarg.h>
#include <locale.h>

String String_concatenar(String lstring, String string) {

	strcat_s(lstring.str, TAM_MAX_STR, string.str);
	lstring.length = strlen(lstring.str);
	lstrcat(lstring.wstr, string.wstr);
	return lstring;
}

String String_concatenar(String lstring, String string1, String string2) {
	return String_concatenar(lstring, 2, string1.str, string2.str);
}

String String_concatenar(String lstring, const char caracter) {
	String rstring = String_iniciar(caracter);
	lstring = String_concatenar(lstring, rstring);

	return lstring;
}

String String_copiar(String string) {
	String lstring = String_limpar();

	strcpy_s(lstring.str, TAM_MAX_STR, string.str);
	lstring.length = string.length;
	lstrcpy(lstring.wstr, string.wstr);
	return lstring;
}

String String_copiar(const char* string) {
	String rstring = String_iniciar(string);
	return rstring;
}

String String_copiar(LPCWSTR string) {
	String rstring = String_iniciar(string);
	return rstring;
}

String String_copiar(const char caracter) {
	String rstring = String_iniciar(caracter);
	return rstring;
}

BOOL String_comparar(String string1, String string2) {
	return (string1.length == string2.length &&
			strcmp(string1.str, string2.str) == 0);
}

BOOL String_comparar(String string1, const char* string2) {
	return (string1.length == strlen(string2) &&
		strcmp(string1.str, string2) == 0);
}

BOOL String_comparar(String string1, LPCWSTR string2) {
	return (string1.length == lstrlen(string2) &&
		lstrcmp(string1.wstr, string2) == 0);
}

String String_limpar() {
	String lstring;

	lstring.str[0] = '\0';
	lstring.wstr[0] = '\0';
	lstring.length = 0;
	return lstring;
}

String String_iniciarRestante(String lstring) {
	lstring.length = strlen(lstring.str);
	
	if (MultiByteToWideChar(0, 0, lstring.str, TAM_MAX_STR, lstring.wstr, TAM_MAX_STR) <= 0) {
		lstring.wstr[0] = '\0';
	}

	return lstring;
}

String String_iniciar(const char caracter) {
	CHAR str[TAM_MAX_STR];
	
	str[0] = caracter;
	str[1] = '\0';
	String lstring = String_iniciar(str);
	
	return lstring;
}

String String_iniciar(const char* string) {
	String lstring = String_limpar();

	if (strlen(string) > 0) {
		strcpy_s(lstring.str, TAM_MAX_STR, string);

		return String_iniciarRestante(lstring);
	}
	else {
		return lstring;
	}
}

String String_iniciar(String string) {
	String lstring = String_limpar();

	if (string.length > 0) {
		lstring = String_copiar(string);

		return lstring;
	}
	else {
		return lstring;
	}
}

String String_iniciar(LPCWSTR string) {
	String lstring = String_limpar();

	//if (WideCharToMultiByte(0, 0, string, TAM_MAX_STR, lstring.str, TAM_MAX_STR, NULL, NULL) <= 0) {
		char* texto = String_cWCharToChar(string);
		strcpy_s(lstring.str, TAM_MAX_STR, texto);
	//}
	lstring = String_iniciar(lstring.str);

	return lstring;
}

String String_concatenar(String lstring, const char* string) {

	strcat_s(lstring.str, TAM_MAX_STR, string);

	return String_iniciarRestante(lstring);

	return lstring;
}

String String_concatenar(String lstring, String string1, const char* string) {
	return String_concatenar(lstring, 2, string1.str, string);
}

String String_concatenar(const char* string, String lstring) {
	char local[TAM_MAX_STR];
	strcpy_s(local, TAM_MAX_STR, string);
	strcat_s(local, TAM_MAX_STR, lstring.str);

	lstring = String_iniciar(local);

	return lstring;
}

String String_concatenar(String string, unsigned int qtd, ...)
{
	unsigned int i;
	char* valor;
	va_list vl;
	
	va_start(vl, qtd);

	for (i = 0; i < qtd; i++)
	{
		valor = va_arg(vl, char*);
		string = String_concatenar(string, valor);
	}
	va_end(vl);

	return string;
}

void String_finalizar(String *lstring) {
	lstring->str[0] = '\0';
	lstring->wstr[0] = '\0';
	lstring->length = 0;
}

String String_Trim(String lstring) {
	String rstring = String_limpar();

	strcpy_s(rstring.str, TAM_MAX_STR, String_cTrim(lstring.str));
	rstring.length = strlen(rstring.str);

	if (MultiByteToWideChar(0, 0, rstring.str, TAM_MAX_STR, rstring.wstr, TAM_MAX_STR) <= 0) {
		rstring.wstr[0] = '\0';
	}

	return rstring;
}

String String_LowerCase(String lstring) {
	String rstring = String_limpar();
	
	strcpy_s(rstring.str, TAM_MAX_STR, String_cLowerCase(lstring.str));
	rstring.length = strlen(rstring.str);

	if (MultiByteToWideChar(0, 0, rstring.str, TAM_MAX_STR, rstring.wstr, TAM_MAX_STR) <= 0) {
		rstring.wstr[0] = '\0';
	}

	return rstring;
}

String String_UpperCase(String lstring) {
	String rstring = String_limpar();

	strcpy_s(rstring.str, TAM_MAX_STR, String_cUpperCase(lstring.str));
	rstring.length = strlen(rstring.str);

	if (MultiByteToWideChar(0, 0, rstring.str, TAM_MAX_STR, rstring.wstr, TAM_MAX_STR) <= 0) {
		rstring.wstr[0] = '\0';
	}

	return rstring;
}

String String_QuotedStr(String lstring) {
	String rstring = String_limpar();

	strcpy_s(rstring.str, TAM_MAX_STR, String_cQuotedStr(lstring.str));
	rstring.length = strlen(rstring.str);

	if (MultiByteToWideChar(0, 0, rstring.str, TAM_MAX_STR, rstring.wstr, TAM_MAX_STR) <= 0) {
		rstring.wstr[0] = '\0';
	}

	return rstring;
}

String String_QuotedStr(const char caracter) {
	String rstring = String_iniciar(caracter);
	return String_QuotedStr(rstring);
}

String String_SubString(String lstring, int inicio, int tamanho) {
	char* cvalor = String_cSubString(lstring.str, inicio, tamanho);
	lstring = String_iniciar(cvalor);
	return lstring;
}

String String_ReplaceAll(String lstring, const char* velho, const char* novo) {
	char* cvalor = String_cReplaceAll(lstring.str, velho, novo);
	lstring = String_iniciar(cvalor);
	return lstring;
}

String String_FromInt(int valor) {
	char* cvalor = String_cFromInt(valor);
	String lstring = String_iniciar(cvalor);
	return lstring;
}

String String_FromULong(unsigned long valor) {
	char* cvalor = String_cFromULong(valor);
	String lstring = String_iniciar(cvalor);
	return lstring;
}

String String_FromLongLong(long long valor) {
	char* cvalor = String_cFromLongLong(valor);
	String lstring = String_iniciar(cvalor);
	return lstring;
}

String String_FromDouble(double valor) {
	char* cvalor = String_cFromDouble(valor);
	String lstring = String_iniciar(cvalor);
	return lstring;
}

String String_FromLongDouble(long double valor) {
	char* cvalor = String_cFromLongDouble(valor);
	String lstring = String_iniciar(cvalor);
	return lstring;
}

int String_ToInt(String lstring) {
	lstring = String_Trim(lstring);

	if (String_cSomenteNumero(lstring.str)) {
		return String_cToInt(lstring.str);
	}

	return 0;
}

long String_ToLong(String lstring) {
	lstring = String_Trim(lstring);

	if (String_cSomenteNumero(lstring.str)) {
		return String_cToLong(lstring.str);
	}

	return 0;
}

long long String_ToLongLong(String lstring) {
	lstring = String_Trim(lstring);

	if (String_cSomenteNumero(lstring.str)) {
		return String_cToLongLong(lstring.str);
	}

	return 0;
}

double String_ToDouble(String lstring) {
	lstring = String_Trim(lstring);

	if (String_cSomenteNumero(lstring.str)) {
		return String_cToDouble(lstring.str);
	}

	return 0;
}

long double String_ToLongDouble(String lstring) {
	lstring = String_Trim(lstring);

	if (String_cSomenteNumero(lstring.str)) {
		return String_cToLongDouble(lstring.str);
	}

	return 0;
}



// ---------------------------------------------------------------------------

char* String_cNewStr(unsigned int tamanho)
{
	char *retorno;

	//retorno = (char*)GlobalAlloc(GPTR, tamanho);
	retorno = (char*)malloc(tamanho);
	retorno[0] = '\0';
	
	return retorno;
}

void String_cFreeStr(char* texto)
{
	//GlobalFree(texto);
	free(texto);
}

char* String_cWCharToChar(const wchar_t* origem)
{
	char* destino = String_cNewStr(TAM_MAX_STR);
	int tamanho = wcslen(origem);
	size_t numCharsConvertidos;

	destino[0] = '\0';

	if (tamanho > 0)
	{
		//wcstombs(destino, origem, tamanho);
		wcstombs_s(&numCharsConvertidos, destino, TAM_MAX_STR, origem, TAM_MAX_STR);
	}
	return destino;
}

int String_cLastIndexOf(const char* texto, const char alvo)
{
	unsigned int i;
	int retorno = -1;
	int tamanho = strlen(texto);

	if (tamanho > 0)
	{
		for (i = 0; texto[i] != '\0'; i++)
		{
			if (texto[i] == alvo)
			{
				retorno = i;
			}
		}
	}
	return retorno;
}

char* String_cTrim(const char* texto)
{
	unsigned int j = 0, inicio = 0, fim = 0;
	unsigned char compara;
	int tamanho = strlen(texto);
	char* retorno = String_cNewStr(TAM_MAX_STR);

	if (tamanho > 0)
	{
		for (unsigned int i = 0; texto[i] != '\0'; i++) {
			compara = (unsigned char)texto[i];
			if (!isspace(compara)) {
				inicio = i;
				fim = strlen(texto);
				break;
			}
		}

		for (unsigned int i = (strlen(texto) - 1); i >= 0; i--) {
			compara = (unsigned char)texto[i];
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

char* String_cLowerCase(const char* texto)
{
	unsigned int i = 0;
	unsigned int j = 0;
	const int tamanho = strlen(texto);
	char* retorno = String_cNewStr(TAM_MAX_STR);
	
	if (tamanho > 0)
	{		
		for (i = 0; texto[i] != '\0'; i++)
		{
			retorno[j] = tolower(texto[i]);
			j++;
		}
		retorno[j] = '\0';
	}
	return retorno;
}

char* String_cUpperCase(const char* texto)
{
	char* retorno = NULL;
	unsigned int i = 0;
	unsigned int j = 0;
	int tamanho = strlen(texto);
	retorno = String_cNewStr(TAM_MAX_STR);

	if (tamanho > 0)
	{		
		for (i = 0; texto[i] != '\0'; i++)
		{
			retorno[j] = toupper(texto[i]);
			j++;
		}
		retorno[j] = '\0';
	}
	return retorno;
}

int String_cPos(const char* subtexto, const char* texto)
{
	const char* retorno = strstr(texto, subtexto);
	if (retorno == NULL)
		return -1;
	else
		return (retorno - texto) + 1;
}

int String_cFind(const char* subtexto, const char* texto, int posInicial)
{
	int tamtexto = strlen(texto);
	char* stexto = String_cStrndup(texto + posInicial, tamtexto + 1);

	const char* retorno = strstr(stexto, subtexto);
	if (retorno == NULL)
		return -1;
	else
		return (retorno - stexto + posInicial);
}

BOOL String_cStartsStr(const char* sub, const char* texto)
{
	if (strncmp(texto, sub, strlen(sub)) == 0)
		return TRUE;
	else
		return FALSE;
}

BOOL String_cContainsStr(const char* texto, const char* subtexto)
{
	return (String_cPos(subtexto, texto) > 0);
}

BOOL String_cEndsStr(const char* texto, const char* subtexto)
{
	return (String_cLastDelimiter(subtexto, texto) > 0);
}

int String_cLastDelimiter(const char* sub, const char* texto)
{
	char* parte;
	int retorno = -1, tamparte = 0;
	int tamanho = strlen(texto);
	char* textolocal = String_cNewStr(TAM_MAX_STR);
	char *next_token;

	if (tamanho > 0)
	{
		retorno = 0;		
		strcpy_s(textolocal, TAM_MAX_STR, texto);
		parte = strtok_s(textolocal, sub, &next_token);
		while (parte != NULL)
		{
			tamparte = strlen(parte) + 1;
			retorno += tamparte;
			parte = strtok_s(NULL, sub, &next_token);
		}
		retorno -= tamparte;
	}
	return retorno;
}

char* String_cStrndup(const char* texto, size_t tamanho)
{
	char* retorno;
	char* fim = (char*)memchr(texto, 0, tamanho);

	if (fim)
	{
		tamanho = fim - texto + 1;
	}

	retorno = String_cNewStr(tamanho);

	if (tamanho)
	{
		memcpy(retorno, texto, tamanho - 1);
		retorno[tamanho - 1] = '\0';
	}
	return retorno;
}

char* String_cSubString(const char* texto, int inicio, int tamanho)
{
	char* retorno = NULL;
	int tamtexto = strlen(texto);

	if (tamtexto > 0)
	{
		retorno = String_cStrndup(texto + inicio - 1, tamanho + 1);
	}
	return retorno;
}

char* String_cQuotedStr(const char* texto)
{
	char* retorno;
	int tamanho = strlen(texto) + 4;

	retorno = String_cNewStr(tamanho);
	sprintf_s(retorno, tamanho, "'%s'", texto);
	return retorno;
}


char* String_cReplaceAll(const char* texto,
	const char* velho, const char* novo)
{
	char *retorno, *parte, *textolocal;
	unsigned int j = 0;
	int tamanho = strlen(texto);
	int tamvelho = strlen(velho);
	int tamnovo = strlen(novo);
	int tamfinal = 0, tamparte = 0;
	char *next_token;

	if (tamanho > 0)
	{
		textolocal = String_cNewStr(TAM_MAX_STR);
		strcpy_s(textolocal, TAM_MAX_STR, texto);
		parte = strstr(textolocal, velho);
		while (parte != NULL)
		{
			j++;
			strcpy_s(textolocal, TAM_MAX_STR, parte + 1);
			parte = strstr(textolocal, velho);
		}
		tamfinal = (tamanho - (j*tamvelho)) + (j*tamnovo);
		retorno = String_cNewStr(TAM_MAX_STR);

		strcpy_s(textolocal, TAM_MAX_STR, texto);
		parte = strtok_s(textolocal, velho, &next_token);
		while (parte != NULL)
		{
			tamparte = strlen(parte);
			strncat_s(retorno, tamfinal + 1, parte, tamparte);
			parte = strtok_s(NULL, velho, &next_token);

			if (parte != NULL)
			{
				strncat_s(retorno, tamfinal + 1, novo, tamnovo);
			}
		}
	}
	else
	{
		retorno = String_cNewStr(TAM_MAX_STR);
		strcpy_s(retorno, TAM_MAX_STR, texto);
	}
	return retorno;
}

char* String_cFromInt(int valor)
{
	char* retorno;
	int tamanho = 30;

	retorno = String_cNewStr(tamanho);
	sprintf_s(retorno, tamanho, "%d", valor);

	return retorno;
}

int String_cToInt(const char* texto)
{
	return atoi(texto);
}

char* String_cFromULong(const unsigned long valor)
{
	char* retorno;
	int tamanho = 40;

	retorno = String_cNewStr(tamanho);	
	sprintf_s(retorno, tamanho, "%lu", valor);

	return retorno;
}

char* String_cFromLongLong(const long long valor)
{
	char* retorno;
	int tamanho = 40;

	retorno = String_cNewStr(tamanho);	
	sprintf_s(retorno, tamanho, "%lld", valor);

	return retorno;
}

char* String_cFromLongDouble(const long double valor)
{
	char* retorno;
	int tamanho = 40;

	retorno = String_cNewStr(tamanho);	
	sprintf_s(retorno, tamanho, "%4.2Lf", valor);

	return retorno;
}

long String_cToLong(const char* texto)
{
	char* pEnd = String_cNewStr(TAM_MAX_STR);
	return strtol(texto, &pEnd, 10);
}

long long String_cToLongLong(const char* texto)
{
	char* pEnd = String_cNewStr(TAM_MAX_STR);
	return strtoll(texto, &pEnd, 10);
}

char* String_cFromDouble(const double valor)
{
	char* retorno;
	int tamanho = 40;

	retorno = String_cNewStr(tamanho);	
	sprintf_s(retorno, tamanho, "%4.2f", valor);

	return retorno;
}

double String_cToDouble(const char* texto)
{
	char* pEnd = String_cNewStr(TAM_MAX_STR);
	return strtod(texto, &pEnd);
}

long double String_cToLongDouble(const char* texto)
{
	char* pEnd = String_cNewStr(TAM_MAX_STR);
	return strtold(texto, &pEnd);
}

BOOL String_cSomenteNumero(const char* texto)
{
	BOOL retorno = TRUE;
	unsigned int i = 0;
	unsigned int j = 0;
	int tamanho = strlen(texto);

	if (tamanho > 0)
	{
		for (i = 0; texto[i] != '\0'; i++)
		{
			if (isascii(texto[i])) {
				if (!isdigit(texto[i]) && texto[i] != '.') {
					retorno = FALSE;
					break;
				}
			}
			else {
				retorno = FALSE;
				break;
			}
		}
	}
	return retorno;
}
// ---------------------------------------------------------------------------

void String_testar() {
	WCHAR saida[TAM_MAX_STR];
	saida[0] = '\0';
	String sDir = String_iniciar("    c:\\ago%ra\\CAMINHO\\teste.olha.depois    ");
	String sTrim = String_Trim(sDir);

	String sConca = String_concatenar(sTrim, 2, "alfa", "beta");
	sConca = String_concatenar(sTrim, sTrim);

	wsprintf(saida, _T("sDir: [%s]\n"), sDir.wstr); OutputDebugString(saida);
	swprintf_s(saida, 40, _T("Length(): %d\n"), sDir.length); OutputDebugString(saida);
	wsprintf(saida, _T("Trim(): [%s]\n"), sTrim.wstr); OutputDebugString(saida);
	swprintf_s(saida, 40, _T("tamanho Trim(): %d\n"), sTrim.length); OutputDebugString(saida);
	String sLower = String_LowerCase(sDir);
	wsprintf(saida, _T("LowerCase(): %s\n"), sLower.wstr); OutputDebugString(saida);
	String sUpper = String_UpperCase(sDir);
	wsprintf(saida, _T("UpperCase(): %s\n"), sUpper.wstr); OutputDebugString(saida);
	wsprintf(saida, _T("Pos('.'): %d\n"), String_cPos(".", sDir.str)); OutputDebugString(saida);
	String sQuoted = String_QuotedStr(sDir);
	wsprintf(saida, _T("QuotedStr(): %s\n"), sQuoted.wstr); OutputDebugString(saida);
	wsprintf(saida, _T("IntToStr(245789): %s\n"), String_FromInt(245789).wstr); OutputDebugString(saida);
	swprintf_s(saida, 40, _T("StrToInt() --> 245789: %d\n"), String_cToInt("245789")); OutputDebugString(saida);
 	long long nlongo = String_cToLongLong("4200155136");
	swprintf_s(saida, TAM_MAX_STR, _T("StrToLongLong() --> 4200155136: %lld\n"), nlongo); 
	OutputDebugString(saida);
	wsprintf(saida, _T("DoubleToStr(15.557878): %s\n"), String_FromDouble(15.557878).wstr); OutputDebugString(saida);

	wsprintf(saida, _T("SubString(): %s\n"), String_SubString(sDir, 8, 6).wstr); OutputDebugString(saida);
	wsprintf(saida, _T("StringReplaceAll(): [%s]\n"), String_ReplaceAll(sDir, "\\", "@").wstr);
	OutputDebugString(saida);

	wsprintf(saida, _T("StartsStr(DVD, JOGOS2_DVDS/TESTE): %s\n"), (String_cStartsStr("JOGOS2_DVDS/TESTE", "DVD") ? _T("true") : _T("false"))); OutputDebugString(saida);
	wsprintf(saida, _T("StartsStr(DVD, DVDSJOGOS2_/TESTE): %s\n"), (String_cStartsStr("DVDSJOGOS2_/TESTE", "DVD") ? _T("true") : _T("false"))); OutputDebugString(saida);

	wsprintf(saida, _T("ContainsStr(JOGOS2_DVDS/TESTE): %s\n"), (String_cContainsStr("DVDSJOGOS2_/TESTE", "DVDSJOGOS2_/TESTE") ? _T("true") : _T("false")));
	OutputDebugString(saida);
	wsprintf(saida, _T("EndsStr(TESTE, JOGOS2_DVDS/TESTE): %s\n"), (String_cEndsStr("DVDSJOGOS2_/TESTE", "TESTE") ? _T("true") : _T("false")));
	OutputDebugString(saida);

	wsprintf(saida, _T("FormatLong(4200155136): %s\n"), String_FromULong(4200155136).wstr);
	OutputDebugString(saida);
	wsprintf(saida, _T("FormatDouble(15.544878): %s\n"), String_FromDouble(15.544878).wstr);
	OutputDebugString(saida);
	wsprintf(saida, _T("FormatDouble(15.547878): %s\n"), String_FromDouble(15.547878).wstr);
	OutputDebugString(saida);
	wsprintf(saida, _T("FormatDouble(15.557878): %s\n"), String_FromDouble(15.557878).wstr);
	OutputDebugString(saida);
	wsprintf(saida, _T("FormatDouble(15.567878): %s\n"), String_FromDouble(15.567878).wstr);
	OutputDebugString(saida);
	
	String_finalizar(&sDir);
	String_finalizar(&sTrim);

}
