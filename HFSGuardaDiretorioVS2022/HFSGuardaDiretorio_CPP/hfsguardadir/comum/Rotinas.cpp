#include "Rotinas.h"

#include "dirent.h"

#include <cwchar>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <ctime>
#include <cerrno>

#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>

#include <algorithm>
#include <functional>
#include <string>
#include <locale>
#include <codecvt>

#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <tchar.h>

#include "stdbool.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "ctype.h"
#include "locale.h"

namespace hfsguardadir {

namespace comum {

// ---------------------------------------------------------------------------
Rotinas* Rotinas::instancia = NULL;
Argumento Rotinas::argumentos;

const std::string Rotinas::HFSGUARDADIR = "HFSGuardaDir";
const std::string Rotinas::BARRA_NORMAL = "\\";
const std::string Rotinas::BARRA_INVERTIDA = "/";
const std::string Rotinas::FORMATO_DATA = "%d/%m/%Y";
const std::string Rotinas::FORMATO_HORA = "%H:%M:%S";
const std::string Rotinas::FORMATO_DATAHORA = "%d/%m/%Y %H:%M:%S";
const std::string Rotinas::FORMATO_DHARQUIVO = "%Y-%m-%d_%H_%M_%S";
const std::string Rotinas::EXTENSAO_BMP = "bmp";
const std::string Rotinas::EXTENSAO_ICO = "ico";
const std::string Rotinas::EXTENSAO_GIF = "gif";
const std::string Rotinas::EXTENSAO_JPEG = "jpeg";
const std::string Rotinas::EXTENSAO_PNG = "png";
const std::string Rotinas::EXTENSAO_TIFF = "tiff";

sqlite3* dbConexao;
// ---------------------------------------------------------------------------
Rotinas::Rotinas() { 

}

Rotinas::Rotinas(Rotinas const&) {

}

Rotinas& Rotinas::operator=(Rotinas const&) {
	return *instancia;
}

Rotinas* Rotinas::getInstancia() {
	if (!instancia) {
		instancia = new Rotinas();
	}
	return instancia;
}
// ---------------------------------------------------------------------------

sqlite3* Rotinas::getConexao() {
	return dbConexao;
}

bool Rotinas::BancoConectar(const std::string &sFonteDeDados)
{
	const int ret = sqlite3_open_v2(sFonteDeDados.c_str(),
		&dbConexao, SQLITE_OPEN_READWRITE, NULL);
	if (SQLITE_OK != ret)
	{
		BancoMostrarErro("Rotinas_BancoConectar");
		sqlite3_close(dbConexao);
		return false;
	}
	return true;
}

void Rotinas::BancoDesconectar()
{
	const int ret = sqlite3_close(dbConexao);
	(void)ret;
}

void Rotinas::BancoMostrarErro(const char* titulo) {
	int errcode = sqlite3_errcode(dbConexao);
	//int exterrcode = sqlite3_extended_errcode(dbConexao);
	char* errmsg = (char*)sqlite3_errmsg(dbConexao);
	//const char* errstr = sqlite3_errstr(dbConexao);

	char* sErro = NewStr();
	std::snprintf(sErro, TAM_MAX_STR, "ERRO: %d - %s", errcode, errmsg);
#ifndef __GNUC__
	OutputDebugString(CharToWChar(sErro));
#endif
	std::cerr << "Banco Mostrar Erro: " << sErro << std::endl;
}

int Rotinas::BancoExec(const std::string &sSQL)
{
	const int ret = sqlite3_exec(dbConexao, sSQL.c_str(), NULL, NULL, NULL);
	if (SQLITE_OK != ret)
	{
		BancoMostrarErro("Rotinas_BancoExec");
	}
	return sqlite3_changes(dbConexao);
}

bool Rotinas::BancoPasso(sqlite3_stmt* pstmt) {
	bool mbOk = false;

	const int ret = sqlite3_step(pstmt);

	if (SQLITE_ROW == ret) {
		mbOk = true;
	}
	else if (SQLITE_DONE == ret) {
		mbOk = false;
	}
	else {
		BancoMostrarErro("Rotinas_BancoPasso");
		mbOk = false;
	}

	return mbOk;
}

int Rotinas::BancoExecPasso(sqlite3_stmt* pstmt, int ret, const char* titulo) {
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

//---------------------------------------------------------------------------
//	FUNCOES C PURO
//---------------------------------------------------------------------------
char* Rotinas::cNewStr(unsigned long long tamanho)
{
	char *retorno;

	retorno = (char*)malloc((std::size_t)tamanho);
	retorno[0] = '\0';

	return retorno;
}

void Rotinas::cFreeStr(char* texto)
{
	free(texto);
}

char* Rotinas::cWCharToChar(const wchar_t* origem)
{
	char* destino = Rotinas::cNewStr(TAM_MAX_STR);
	size_t tamanho = wcslen(origem);
#ifndef __GNUC__
	size_t numCharsConvertidos;
#endif

	destino[0] = '\0';

	if (tamanho > 0)
	{
#ifdef __GNUC__
		wcstombs(destino, origem, tamanho);
#else
		wcstombs_s(&numCharsConvertidos, destino, sizeof destino, origem, tamanho);
		//wcstombs_s(&numCharsConvertidos, destino, TAM_MAX_STR, origem, TAM_MAX_STR);
#endif
	}
	return destino;
}

int Rotinas::cLastIndexOf(const char* texto, const char alvo)
{
	unsigned int i;
	int retorno = -1;
	size_t tamanho = strlen(texto);

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

char* Rotinas::cTrim(const char* texto)
{
	size_t j = 0, inicio = 0, fim = 0;
	unsigned char compara;
	size_t tamanho = strlen(texto);
	char* retorno = Rotinas::cNewStr(TAM_MAX_STR);

	if (tamanho > 0)
	{
		for (size_t i = 0; texto[i] != '\0'; i++) {
			compara = (unsigned char)texto[i];
			if (!isspace(compara)) {
				inicio = i;
				fim = strlen(texto);
				break;
			}
		}

		for (size_t i = (strlen(texto) - 1); i >= 0; i--) {
			compara = (unsigned char)texto[i];
			if (isspace(compara)) {
				fim = i;
			}
			else {
				break;
			}
		}

		for (size_t i = inicio; i < fim; i++) {
			retorno[j] = texto[i];
			j++;
		}
		retorno[j] = '\0';
	}
	return retorno;
}

char* Rotinas::cLowerCase(const char* texto)
{
	unsigned int i = 0;
	unsigned int j = 0;
	const size_t tamanho = strlen(texto);
	char* retorno = Rotinas::cNewStr(TAM_MAX_STR);

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

char* Rotinas::cUpperCase(const char* texto)
{
	char* retorno = NULL;
	unsigned int i = 0;
	unsigned int j = 0;
	size_t tamanho = strlen(texto);
	retorno = Rotinas::cNewStr(TAM_MAX_STR);

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

size_t Rotinas::cPos(const char* subtexto, const char* texto)
{
	const char* retorno = strstr(texto, subtexto);
	if (retorno == NULL)
		return -1;
	else
		return (retorno - texto) + 1;
}

int Rotinas::cFind(const char* subtexto, const char* texto, int posInicial)
{
	size_t tamtexto = strlen(texto);
	char* stexto = Rotinas::cStrndup(texto + posInicial, tamtexto + 1);

	const char* retorno = strstr(stexto, subtexto);
	if (retorno == NULL)
		return -1;
	else
		return (int)(retorno - stexto + posInicial);
}

bool Rotinas::cStartsStr(const char* sub, const char* texto)
{
	if (strncmp(texto, sub, strlen(sub)) == 0)
		return true;
	else
		return false;
}

bool Rotinas::cContainsStr(const char* texto, const char* subtexto)
{
	return (Rotinas::cPos(subtexto, texto) > 0);
}

bool Rotinas::cEndsStr(const char* texto, const char* subtexto)
{
	return (Rotinas::cLastDelimiter(subtexto, texto) > 0);
}

size_t Rotinas::cLastDelimiter(const char* sub, const char* texto)
{
	char* parte;
	size_t retorno = -1, tamparte = 0;
	size_t tamanho = strlen(texto);
	char* textolocal = Rotinas::cNewStr(TAM_MAX_STR);
#ifndef __GNUC__
	char* next_token = NULL;
#endif

	if (tamanho > 0)
	{
		retorno = 0;
#ifdef __GNUC__
		strcpy(textolocal, texto);
		parte = strtok(textolocal, sub);
#else
		strcpy_s(textolocal, TAM_MAX_STR, texto);
		parte = strtok_s(textolocal, sub, &next_token);
#endif
		while (parte != NULL)
		{
			tamparte = strlen(parte) + 1;
			retorno += tamparte;
#ifdef __GNUC__
			parte = strtok(NULL, sub);
#else
			parte = strtok_s(NULL, sub, &next_token);
#endif
		}
		retorno -= tamparte;
	}
	return retorno;
}

char* Rotinas::cStrndup(const char* texto, size_t tamanho)
{
	char* retorno;
	char* fim = (char*)memchr(texto, 0, tamanho);

	if (fim)
	{
		tamanho = fim - texto + 1;
	}

	retorno = Rotinas::cNewStr(tamanho);

	if (tamanho)
	{
		memcpy(retorno, texto, tamanho - 1);
		retorno[tamanho - 1] = '\0';
	}
	return retorno;
}

char* Rotinas::cSubString(const char* texto, int inicio, size_t tamanho)
{
	char* retorno = NULL;
	size_t tamtexto = strlen(texto);

	if (tamtexto > 0)
	{
		retorno = Rotinas::cStrndup(texto + inicio - 1, tamanho + 1);
	}
	return retorno;
}

char* Rotinas::cQuotedStr(const char* texto)
{
	char* retorno;
	size_t tamanho = strlen(texto) + 4;

	retorno = Rotinas::cNewStr(tamanho);
#ifdef __GNUC__
	sprintf(retorno, "'%s'", texto);
#else
	sprintf_s(retorno, tamanho, "'%s'", texto);
#endif
	return retorno;
}


char* Rotinas::cReplaceAll(const char* texto,
	const char* velho, const char* novo)
{
	char *retorno, *parte, *textolocal;
	unsigned int j = 0;
	size_t tamanho = strlen(texto);
	size_t tamvelho = strlen(velho);
	size_t tamnovo = strlen(novo);
	size_t tamfinal = 0, tamparte = 0;
#ifndef __GNUC__
	char* next_token = NULL;
#endif

	if (tamanho > 0)
	{
		textolocal = Rotinas::cNewStr(TAM_MAX_STR);
#ifdef __GNUC__
		strcpy(textolocal, texto);
#else
		strcpy_s(textolocal, TAM_MAX_STR, texto);
#endif
		parte = strstr(textolocal, velho);
		while (parte != NULL)
		{
			j++;
#ifdef __GNUC__
			strcpy(textolocal, parte + 1);
#else
			strcpy_s(textolocal, TAM_MAX_STR, parte + 1);
#endif
			parte = strstr(textolocal, velho);
		}
		tamfinal = (tamanho - (j*tamvelho)) + (j*tamnovo);
		retorno = Rotinas::cNewStr(TAM_MAX_STR);

#ifdef __GNUC__
		strcpy(textolocal, texto);
		parte = strtok(textolocal, velho);
#else
		strcpy_s(textolocal, TAM_MAX_STR, texto);
		parte = strtok_s(textolocal, velho, &next_token);
#endif
		while (parte != NULL)
		{
			tamparte = strlen(parte);
#ifdef __GNUC__
			strncat(retorno, parte, tamparte);
			parte = strtok(NULL, velho);
#else
			strncat_s(retorno, tamfinal + 1, parte, tamparte);
			parte = strtok_s(NULL, velho, &next_token);
#endif
			if (parte != NULL)
			{
#ifdef __GNUC__
				strncat(retorno, novo, tamnovo);
#else
				strncat_s(retorno, tamfinal + 1, novo, tamnovo);
#endif
			}
		}
	}
	else
	{
		retorno = Rotinas::cNewStr(TAM_MAX_STR);
#ifdef __GNUC__
		strcpy(retorno, texto);
#else
		strcpy_s(retorno, TAM_MAX_STR, texto);
#endif
	}
	return retorno;
}

char* Rotinas::cFromInt(int valor)
{
	char* retorno;
	int tamanho = 30;

	retorno = Rotinas::cNewStr(tamanho);
#ifdef __GNUC__
	sprintf(retorno, "%d", valor);
#else
	sprintf_s(retorno, tamanho, "%d", valor);
#endif
	return retorno;
}

int Rotinas::cToInt(const char* texto)
{
	return atoi(texto);
}

char* Rotinas::cFromULong(const unsigned long valor)
{
	char* retorno;
	int tamanho = 40;

	retorno = Rotinas::cNewStr(tamanho);
#ifdef __GNUC__
	sprintf(retorno, "%lu", valor);
#else
	sprintf_s(retorno, tamanho, "%lu", valor);
#endif
	return retorno;
}

char* Rotinas::cFromLongLong(const long long valor)
{
	char* retorno;
	int tamanho = 40;

	retorno = Rotinas::cNewStr(tamanho);
#ifdef __GNUC__
	sprintf(retorno, "%lld", valor);
#else
	sprintf_s(retorno, tamanho, "%lld", valor);
#endif

	return retorno;
}

char* Rotinas::cFromLongDouble(const long double valor)
{
	char* retorno;
	int tamanho = 40;

	retorno = Rotinas::cNewStr(tamanho);
#ifdef __GNUC__
	sprintf(retorno, "%4.2Lf", valor);
#else
	sprintf_s(retorno, tamanho, "%4.2Lf", valor);
#endif

	return retorno;
}

long Rotinas::cToLong(const char* texto)
{
	char* pEnd = Rotinas::cNewStr(TAM_MAX_STR);
	return strtol(texto, &pEnd, 10);
}

long long Rotinas::cToLongLong(const char* texto)
{
	char* pEnd = Rotinas::cNewStr(TAM_MAX_STR);
	return strtoll(texto, &pEnd, 10);
}

char* Rotinas::cFromDouble(const double valor)
{
	char* retorno;
	int tamanho = 40;

	retorno = Rotinas::cNewStr(tamanho);
#ifdef __GNUC__
	sprintf(retorno, "%4.2f", valor);
#else
	sprintf_s(retorno, tamanho, "%4.2f", valor);
#endif
	return retorno;
}

double Rotinas::cToDouble(const char* texto)
{
	char* pEnd = Rotinas::cNewStr(TAM_MAX_STR);
	return strtod(texto, &pEnd);
}

long double Rotinas::cToLongDouble(const char* texto)
{
	char* pEnd = Rotinas::cNewStr(TAM_MAX_STR);
	return strtold(texto, &pEnd);
}

bool Rotinas::cSomenteNumero(const char* texto)
{
	bool retorno = true;
	unsigned int i = 0;
	unsigned int j = 0;
	size_t tamanho = strlen(texto);

	if (tamanho > 0)
	{
		for (i = 0; texto[i] != '\0'; i++)
		{
			if (isascii(texto[i])) {
				if (!isdigit(texto[i]) && texto[i] != '.') {
					retorno = false;
					break;
				}
			}
			else {
				retorno = false;
				break;
			}
		}
	}
	return retorno;
}


//---------------------------------------------------------------------------
//	FUNCOES C++
//---------------------------------------------------------------------------
char* Rotinas::NewStr(size_t tamanho)
{
	char *retorno;

	retorno = new char[tamanho];
	retorno[0] = '\0';

	return retorno;
}

char* Rotinas::NewStr()
{
	return NewStr(TAM_MAX_STR);
}

char* Rotinas::WCharToChar(const wchar_t* origem)
{
	char* destino = NewStr();
	size_t tamanho = wcslen(origem);
#ifndef __GNUC__
	size_t numCharsConvertidos;
#endif

	if (tamanho > 0) {
#ifdef __GNUC__
		std::setlocale(LC_ALL, "pt_BR.utf8");
		std::wcstombs(destino, origem, TAM_MAX_STR);
#else
		wcstombs_s(&numCharsConvertidos, destino, TAM_MAX_STR, origem, TAM_MAX_STR);
#endif
	}
	return destino;
}

wchar_t* Rotinas::CharToWChar(const char* origem)
{
	wchar_t* destino = new wchar_t[TAM_MAX_STR];
	destino[0] = '\0';
	size_t tamanho = strlen(origem);
#ifndef __GNUC__
	size_t numCharsConvertidos;
#endif

	if (tamanho > 0) {
#ifdef __GNUC__
		std::setlocale(LC_ALL, "pt_BR.utf8");
		std::mbstowcs(destino, origem, TAM_MAX_STR);
#else
		mbstowcs_s(&numCharsConvertidos, destino, TAM_MAX_STR, origem, TAM_MAX_STR);
#endif
	}
	return destino;
}

std::string Rotinas::WStringToString(const std::wstring &origem)
{
#ifdef __GNUC__
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.to_bytes(origem);
#else
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, origem.c_str(), -1, NULL, 0, NULL, NULL);
	std::string str(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, origem.c_str(), -1, &str[0], size_needed, NULL, NULL);
	return str;
#endif
}

std::wstring Rotinas::StringToWString(const std::string &origem)
{
#ifdef __GNUC__
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(origem);
#else
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, origem.c_str(), -1, NULL, 0);
	std::wstring wstr(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, origem.c_str(), -1, &wstr[0], size_needed);
	return wstr;
#endif
}

void Rotinas::setArgumentos(int argc, char *argv[]) {	
	argumentos.quantidade = argc;
	//for (int i = 0; i < argc; i++)
	//{
	argumentos.texto = argv[0];
	//}	
}

std::string Rotinas::AppDirPath() {
	return argumentos.texto;
}

std::string Rotinas::AppDirName() {
	std::string path = argumentos.texto;
	path = ExtractFilePath(path);

	return path;
}

std::string Rotinas::AppFileName() {
	std::string path = argumentos.texto;
	path = ExtractFileName(path);

	return path;
}

std::string Rotinas::TrimLeft(const std::string &texto)
{
	std::string stexto = texto;

	stexto.erase(stexto.begin(), std::find_if(stexto.begin(), stexto.end(),
		std::not_fn(static_cast<int(*)(int)>(std::isspace))));
	return stexto;
}

std::string Rotinas::TrimRight(const std::string &texto)
{
	std::string stexto = texto;

	stexto.erase(std::find_if(stexto.rbegin(), stexto.rend(),
		std::not_fn(static_cast<int(*)(int)>(std::isspace))).base(), stexto.end());

	return stexto;
}

std::string Rotinas::Trim(const std::string &texto) {
	return TrimLeft(TrimRight(texto));
}

std::string Rotinas::LowerCase(const std::string &texto) {
	std::string stexto = texto;

	std::transform(stexto.begin(), stexto.end(), stexto.begin(), ::tolower);
	return stexto;
}

std::string Rotinas::UpperCase(const std::string &texto) {
	std::string stexto = texto;

	std::transform(stexto.begin(), stexto.end(), stexto.begin(), ::toupper);
	return stexto;
}

size_t Rotinas::Pos(const std::string &subtexto, const std::string &texto) {
	std::string::size_type loc = texto.find(subtexto, 0);
	if (loc != std::string::npos)
		return (loc + 1);
	else
		return -1;
}

bool Rotinas::StartsStr(const std::string &subtexto, const std::string &texto) {
	return subtexto.length() <= texto.length()
		&& std::equal(subtexto.begin(), subtexto.end(), texto.begin());
}

bool Rotinas::ContainsStr(const std::string &texto, const std::string &subtexto) {
	return (Pos(subtexto, texto) > 0);
}

bool Rotinas::EndsStr(const std::string &texto, const std::string &subtexto) {
	return (LastDelimiter(subtexto, texto) > 0);
}

size_t Rotinas::LastDelimiter(const std::string &subtexto, const std::string &texto) {
	std::string::size_type loc = texto.find_last_of(subtexto);
	if (loc != std::string::npos)
		return (loc + 1);
	else
		return -1;
}

std::string Rotinas::SubString(const std::string &texto, size_t inicio, size_t tamanho) {
	/*
	if ((inicio + tamanho - 1) > texto.length()) {
		tamanho = texto.length();
	}
	else {
		tamanho = inicio + tamanho - 1;
	}
	*/
	return texto.substr(inicio - 1, tamanho);
}

std::string Rotinas::IntToStr(int valor) {
	std::stringstream ss;
	ss << valor;
	return ss.str();
}

int Rotinas::StrToInt(const std::string &texto) {
	return atoi(texto.c_str());
}

std::string Rotinas::QuotedStr(const std::string &texto) {
	std::stringstream ss;
	ss << "'" << texto << "'";
	return ss.str();
}

std::string Rotinas::QuotedChar(const char caracter) {
	std::stringstream ss;
	ss << "'" << caracter << "'";
	return ss.str();
}

std::string Rotinas::ReplaceAll(const std::string &texto,
	const std::string &velho, const std::string &novo) {
	std::string stexto = texto;
	size_t pos = 0;
	while ((pos = stexto.find(velho, pos)) != std::string::npos)
	{
		stexto.replace(pos, velho.length(), novo);
		pos += novo.length();
	}
	return stexto;
}
/*
std::string Rotinas::formataDate(const std::string formato, const DateTime* dt) {
	gchar* temp;
	std::string ds;

	temp = g_date_time_format((GDateTime*)dt, formato.c_str());
	ds = temp;

	return ds;
}

DateTime* Rotinas::StringToDate(const std::string &sData) {
	GDateTime* data;
	gint pos1 = 0, pos2 = 0, ano = 0, mes = 0, dia = 0, hora = 0, minuto = 0;
	gdouble segundos = 0;
	std::string sdh = Trim(sData);
	std::string parte, texto = sdh;

	if (sdh.length() > 0) {

		if (sdh.find('/') != -1) {
			pos1 = sdh.find('/');
			parte = texto.substr(pos1 - 2, pos1);
			dia = StrToInt(parte);

			pos2 = sdh.find('/', pos1 + 1);
			parte = texto.substr(pos1 + 1, pos2 - pos1 - 1);
			mes = StrToInt(parte);

			parte = texto.substr(pos2 + 1, 4);
			ano = StrToInt(parte);

			if (ano < 1970)
				ano = 1970;
		}

		if (sdh.find(':') != -1) {
			pos1 = sdh.find(':');
			parte = texto.substr(pos1 - 2, 2);
			hora = StrToInt(parte);

			pos2 = sdh.find(':', pos1 + 1);
			parte = texto.substr(pos1 + 1, pos2 - pos1 - 1);
			minuto = StrToInt(parte);

			parte = texto.substr(pos2 + 1, 2);
			segundos = StrToDouble(parte);
		}

		data = g_date_time_new_local(
			ano, mes, dia, hora, minuto, segundos);
	}

	return data;
}

GDateTime* Rotinas::DataHoraNow() {
	return g_date_time_new_now_local();
}

GDateTime* Rotinas::RawToDataHora(const time_t rawTempo)
{
	struct tm infoTempo;
	GDateTime* data;
	gint ano = 0, mes = 0, dia = 0, hora = 0, minuto = 0;
	gdouble segundos = 0;

	localtime_s((struct tm * const)&infoTempo, &rawTempo);

	dia = infoTempo.tm_mday;
	mes = infoTempo.tm_mon + 1;
	ano = infoTempo.tm_year + 1900;
	hora = infoTempo.tm_hour;
	minuto = infoTempo.tm_min;
	segundos = infoTempo.tm_sec;

	data = g_date_time_new_local(
		ano, mes, dia, hora, minuto, segundos);

	return data;
}
*/

std::string Rotinas::ULongToStr(const unsigned long valor) {
	char *retorno = new char[40];
	std::snprintf(retorno, 40, "%lu", valor);
	return retorno;

	/*
	std::stringstream ss;
	ss.precision(40);
	ss << valor;
	return ss.str();
	*/
}

std::string Rotinas::LongLongToStr(const long long valor) {
	char *retorno = new char[40];
	std::snprintf(retorno, 40, "%lld", valor);
	return retorno;

	/*
	std::stringstream ss;
	ss.precision(40);
	ss << valor;
	return ss.str();
	*/
}

std::string Rotinas::LongDoubleToStr(const long double valor) {
	char *retorno = new char[40];
	std::snprintf(retorno, 40, "%4.2Lf", valor);
	return retorno;

	/*
	std::stringstream ss;
	ss.precision(40);
	ss << valor;
	return ss.str();
	*/
}

unsigned long long Rotinas::StrToULongLong(const std::string &texto) {
	char* temp;
	unsigned long long valor = strtoull(texto.c_str(), &temp, 10);
	return valor;
}

std::string Rotinas::DoubleToStr(const double valor) {
	char *retorno = new char[40];
	std::snprintf(retorno, 40, "%4.2f", valor);
	return retorno;

	/*
	std::stringstream ss;
	ss.precision(40);	
	ss << valor;
	return ss.str();
	*/
}

double Rotinas::StrToDouble(const std::string &texto) {
	char* temp;
	double	valor = strtod(texto.c_str(), &temp);
	return valor;
}


std::string Rotinas::MontaTamanhoBig(long double nTam) {
	long long nUmKilo, nUmMega, nUmGiga, nUmTera, nUmPeta;

	nUmKilo = 1024;
	nUmMega = nUmKilo * nUmKilo;
	nUmGiga = nUmMega * nUmKilo;
	nUmTera = nUmGiga * nUmKilo;
	nUmPeta = nUmTera * nUmKilo;

	if (nTam < nUmKilo) {
		return LongDoubleToStr(nTam) + " Byte(s)";
	}
	else if (nTam > nUmKilo && nTam < nUmMega) {
		nTam = nTam / nUmKilo;
		return LongDoubleToStr(nTam) + " KByte(s)";
	}
	else if (nTam > nUmMega && nTam < nUmGiga) {
		nTam = nTam / nUmMega;
		return LongDoubleToStr(nTam) + " MByte(s)";
	}
	else if (nTam > nUmGiga && nTam < nUmTera) {
		nTam = nTam / nUmGiga;
		return LongDoubleToStr(nTam) + " GByte(s)";
	}
	else if (nTam > nUmTera && nTam < nUmPeta) {
		nTam = nTam / nUmTera;
		return LongDoubleToStr(nTam) + " TByte(s)";
	}
	else {
		nTam = nTam / nUmPeta;
		return LongDoubleToStr(nTam) + " PByte(s)";
	}
}

std::string Rotinas::MontaTamanho(long long nTam) {
	if (nTam > 0) {
		return MontaTamanhoBig((long double)nTam);
	}
	else {
		return "";
	}
}

std::string Rotinas::testaNull(char *res) {
	return (res == NULL ? "" : Trim(res));
}

std::string Rotinas::trocaSeparador(const std::string &texto) {
	std::string txt = texto;
	if (texto.length() > 0) {
		txt = ReplaceAll(texto, BARRA_NORMAL, BARRA_INVERTIDA);
	}
	return txt;
}

bool Rotinas::testaSeparadorArquivo(const std::string &sDir) {
	std::string sdir = SubString(sDir, sDir.length(), 1);
	if (sdir == BARRA_INVERTIDA	|| sdir == BARRA_NORMAL) {
		return true;
	}
	else {
		return false;
	}
}

std::string Rotinas::ExtractFilePath(const std::string &sCaminho) {
	std::string retorno = sCaminho;

	const size_t indice = retorno.find_last_of("\\/");
	if (std::string::npos != indice)
	{
		retorno.erase(indice + 1, retorno.length());
	}

	return retorno;
}

std::string Rotinas::ExtractFileName(const std::string &sCaminho) {
	std::string retorno = sCaminho;

	const size_t indice = retorno.find_last_of("\\/");
	if (std::string::npos != indice)
	{
		retorno.erase(0, indice + 1);
	}

	return retorno;
}

bool Rotinas::FileExists(const std::string &sNomeArquivo) {
	struct stat fileInfo;

	if (_access(sNomeArquivo.c_str(), 0) == 0) {
		stat(sNomeArquivo.c_str(), &fileInfo);

		if ((fileInfo.st_mode & S_IFMT) == S_IFDIR)
			return false; //diretorio
		else
			return true; //arquivo
	}

	return false;
}

bool Rotinas::DirectoryExists(const std::string &sNomeArquivo) {
	struct stat fileInfo;

	if (_access(sNomeArquivo.c_str(), 0) == 0) {
		stat(sNomeArquivo.c_str(), &fileInfo);

		if ((fileInfo.st_mode & S_IFMT) == S_IFDIR)
			return true; //diretorio
		else
			return false; //arquivo
	}

	return false;
}

bool Rotinas::DeleteFromFile(const std::string &sNomeArquivo) {
	return (std::remove(sNomeArquivo.c_str()) == 0);
}

std::string Rotinas::getRecurso(const char* chave) {
	if (chave == "HFSGuardaDir.ErroInicial") return "Ocorreu um erro no aplicativo!";

	if (chave == "Tabela.nome") return "Nome";
	if (chave == "Tabela.tamanho") return "Tamanho";
	if (chave == "Tabela.tipo") return "Tipo";
	if (chave == "Tabela.modificado") return "Modificado";
	if (chave == "Tabela.atributos") return "Atributos";
	if (chave == "Tabela.caminho") return "Caminho";
	if (chave == "Tabela.aba") return "Aba";

	if (chave == "Aba.codigo") return "Código:";
	if (chave == "Aba.nome") return "Nome:";

	if (chave == "Tipo.codigo") return "Código:";
	if (chave == "Tipo.nome") return "Nome:";

	if (chave == "TipoLista.arquivo") return "Arquivo";
	if (chave == "TipoLista.diretorio") return "Diretório";

	if (chave == "ConexaoParams.nome") return "Nome:";
	if (chave == "ConexaoParams.driver") return "Driver:";
	if (chave == "ConexaoParams.url") return "URL:";
	if (chave == "ConexaoParams.login") return "Login:";
	if (chave == "ConexaoParams.senha") return "Senha:";

	if (chave == "Diretorio.aba") return "Aba:";
	if (chave == "Diretorio.codigo") return "Código:";
	if (chave == "Diretorio.ordem") return "Ordem:";
	if (chave == "Diretorio.nome") return "Nome:";
	if (chave == "Diretorio.tamanho") return "Tamanho:";
	if (chave == "Diretorio.tipo") return "Tipo:";
	if (chave == "Diretorio.modificado") return "Modificado:";
	if (chave == "Diretorio.atributos") return "Atributos:";
	if (chave == "Diretorio.codDirPai") return "Código Diretório Pai:";
	if (chave == "Diretorio.caminho") return "Caminho:";

	if (chave == "Extensao.codigo") return "Código:";
	if (chave == "Extensao.nome") return "Extensão:";
	if (chave == "Extensao.icone") return "Ícone:";
	if (chave == "Extensao.arquivo") return "arquivo(file)";
	if (chave == "Extensao.diretorio") return "diretorio(directory)";
	if (chave == "Extensao.zip") return ".zip";

	if (chave == "FrmPrincipal.titulo") return "HFSGuardaDiretorio 2.0 - Catalogador de Diretórios";
	if (chave == "FrmPrincipal.barraStatus1") return "Quantidade Total: , Tamanho Total:";
	if (chave == "FrmPrincipal.btnImportarDiretorio") return "Importar Diretório";
	if (chave == "FrmPrincipal.btnPesquisa") return "Pesquisar";
	if (chave == "FrmPrincipal.Aba1") return "DISCO1";
	if (chave == "FrmPrincipal.menuAba") return "Aba";
	if (chave == "FrmPrincipal.menuIncluirNovaAba") return "Incluir Nova Aba";
	if (chave == "FrmPrincipal.menuDiretorio") return "Diretório";
	if (chave == "FrmPrincipal.menuAlterarNomeAbaAtiva") return "Alterar Nome da Aba Ativa";
	if (chave == "FrmPrincipal.menuExcluirAbaAtiva") return "Excluir Aba Ativa";
	if (chave == "FrmPrincipal.menuImportarDiretorio") return "Importar Diretório";
	if (chave == "FrmPrincipal.menuImportarSubDiretorios") return "Importar SubDiretórios";
	if (chave == "FrmPrincipal.menuCompararDiretorios") return "Comparar Diretórios";
	if (chave == "FrmPrincipal.menuCadastrarExtensaoArquivo") return "Cadastrar Extensão de Arquivo";
	if (chave == "FrmPrincipal.menuExpandirDiretorios") return "Expandir Diretórios";
	if (chave == "FrmPrincipal.menuColapsarDiretorios") return "Colapsar Diretórios";
	if (chave == "FrmPrincipal.menuExportarDiretoriosAbaAtiva") return "Exportar Diretórios da Aba Ativa";
	if (chave == "FrmPrincipal.menuTXT") return "TXT";
	if (chave == "FrmPrincipal.menuCSV") return "CSV";
	if (chave == "FrmPrincipal.menuHTML") return "HTML";
	if (chave == "FrmPrincipal.menuXML") return "XML";
	if (chave == "FrmPrincipal.menuSQL") return "SQL";
	if (chave == "FrmPrincipal.menuImportarDiretoriosViaXML") return "Importar Diretórios Via XML";
	if (chave == "FrmPrincipal.menuGravarLogImportacao") return "Gravar Log da Importação";
	if (chave == "FrmPrincipal.menuVisao") return "Visão";
	if (chave == "FrmPrincipal.menuMostrarOcultarArvoreDirAbaAtiva") return "Mostrar/Ocultar Árvore de diretórios da Aba Ativa";
	if (chave == "FrmPrincipal.menuMostrarOcultarListaItensPesquisados") return "Mostrar/Ocultar lista de itens pesquisados";
	if (chave == "FrmPrincipal.menuSobre") return "Sobre";
	if (chave == "FrmPrincipal.TamMaxPesquisa") return "A pesquisa só é feita com pelo menos 2 caracteres!";
	if (chave == "FrmPrincipal.DigitaNomeDiretorio") return "Este diretório não possui um nome.\nDigite o nome do diretório!";
	if (chave == "FrmPrincipal.ValidaNomeDiretorio") return "Nenhum nome de diretório informado!";
	if (chave == "FrmPrincipal.ErroSalvarArquivo") return "Ocorreu um erro ao salvar o arquivo.";
	if (chave == "FrmPrincipal.SucessoExportar") return "Exportação realizada com sucesso!";
	if (chave == "FrmPrincipal.ExcluirDiretorioSelecionado") return "Tem Certeza, que você deseja excluir este diretório, isto implicará na destruição de todos os seus items catalogados?";
	if (chave == "FrmPrincipal.ImportacaoNaoRealizada") return "Importação não realizada!";
	if (chave == "FrmPrincipal.DiretorioExisteCatalogo") return "Este diretório já existe no catálogo!";
	if (chave == "FrmPrincipal.ImportacaoRealizada") return "Importação realizada com sucesso!";
	if (chave == "FrmPrincipal.ErroAbrirDir") return "Um erro ocorreu. Nenhum diretório foi escolhido.";
	if (chave == "FrmPrincipal.DirImportacaoSucesso") return "Importação do(s) diretório(s) realizada com sucesso!";
	if (chave == "FrmPrincipal.DigitaIncluirNovaAba") return "Digite o Nome da Nova Aba?";
	if (chave == "FrmPrincipal.DigitaAlterarNomeAba") return "Digite o Novo Nome da Aba Ativa?";
	if (chave == "FrmPrincipal.ConfirmaExcluirAba") return "Tem Certeza, que você deseja excluir esta aba, \nisto implicará na destruição de todos os seus itens catalogados?";
	if (chave == "FrmPrincipal.ValidaExcluirAba") return "A primeira Aba não pode ser excluída!";
	if (chave == "FrmPrincipal.menuSobreCatalogador") return "Sobre o Catalogador";
	if (chave == "FrmPrincipal.menuIdioma") return "Idioma";
	if (chave == "FrmPrincipal.menuPortugues") return "Português [Portuguese]";
	if (chave == "FrmPrincipal.menuIngles") return "Inglês [English]";
	if (chave == "FrmPrincipal.menuEspanhol") return "Espanhol [Spanish]";
	if (chave == "FrmPrincipal.menuFrances") return "Francês [French]";
	if (chave == "FrmPrincipal.menuItaliano") return "Italiano [Italian]";
	if (chave == "FrmPrincipal.menuAlemao") return "Alemão [German]";
	if (chave == "FrmPrincipal.menuJapones") return "Japonês [Japanese]";
	if (chave == "FrmPrincipal.menuCoreano") return "Coreano [Korean]";
	if (chave == "FrmPrincipal.menuChinesTradicional") return "Chinês Tradicional [Traditional Chinese]";
	if (chave == "FrmPrincipal.menuExcluirDiretorioSelecionado") return "Excluir Diretório Selecionado";
	if (chave == "FrmPrincipal.menuInformacoesDiretorioArquivo") return "Informações do Diretório / Arquivo";

	if (chave == "FrmSobre.titulo") return "Sobre o Catalogador";
	if (chave == "FrmSobre.label1") return "HFSGuardaDir 2.0 - Catalogador de Diretórios";
	if (chave == "FrmSobre.label2") return "Desenvolvido em Java com Swing, Versão: 2.0";
	if (chave == "FrmSobre.label3") return "Por Henrique Figueiredo de Souza";
	if (chave == "FrmSobre.label4") return "Todos os direitos reservados, 2015";
	if (chave == "FrmSobre.Propriedade") return "Propriedade";
	if (chave == "FrmSobre.Valor") return "Valor";

	if (chave == "FrmSplash.label1") return "HFSGuardaDiretorio 2.0";
	if (chave == "FrmSplash.label2") return "Catalogador de Diretórios";

	if (chave == "FrmCompararDiretorio.titulo") return "Comparar Diretórios";
	if (chave == "FrmCompararDiretorio.btnCompararDiretorios") return "Comparar Diretórios";
	if (chave == "FrmCompararDiretorio.btnSalvarLog") return "Salvar Log";
	if (chave == "FrmCompararDiretorio.barraStatus1") return "Total de diferenças encontradas:";
	if (chave == "FrmCompararDiretorio.panelDiretorio1") return "Diretório 1";
	if (chave == "FrmCompararDiretorio.labDiferencasEncontradas") return "Diferenças Encontradas";
	if (chave == "FrmCompararDiretorio.panelDiretorio2") return "Diretório 2";
	if (chave == "FrmCompararDiretorio.NenhumaDiferencaEncontrada") return "Nenhuma diferença encontrada!";
	if (chave == "FrmCompararDiretorio.DiretoriosNaoSelecionados") return "Diretórios não selecionados!";
	if (chave == "FrmCompararDiretorio.LogSalvoMemoDirSistema") return "Log salvo no mesmo diretório do sistema!";

	if (chave == "FrmCadExtensao.titulo") return "Cadastro de Extensão de Arquivo";
	if (chave == "FrmCadExtensao.extensao") return "Extensão";
	if (chave == "FrmCadExtensao.icone") return "Ícone";
	if (chave == "FrmCadExtensao.btnIncluir") return "Incluir";
	if (chave == "FrmCadExtensao.btnExcluir") return "Excluir";
	if (chave == "FrmCadExtensao.menuExtensao") return "Extensão";
	if (chave == "FrmCadExtensao.menuExportarTodos") return "Exportar Todos";
	if (chave == "FrmCadExtensao.menuImportarTodos") return "Importar Todos";
	if (chave == "FrmCadExtensao.menuIncluirExtensao") return "Incluir Extensão";
	if (chave == "FrmCadExtensao.menuExcluirExtensao") return "Excluir Extensão";
	if (chave == "FrmCadExtensao.menuExcluirTodasExtensoes") return "Excluir Todas Extensões";
	if (chave == "FrmCadExtensao.menuExportarIcone") return "Exportar para Ícone";
	if (chave == "FrmCadExtensao.menuExportarGIF") return "Exportar para GIF";
	if (chave == "FrmCadExtensao.menuExportarJPEG") return "Exportar para JPEG";
	if (chave == "FrmCadExtensao.menuExportarPNG") return "Exportar para PNG";
	if (chave == "FrmCadExtensao.menuExportarTIFF") return "Exportar para TIFF";
	if (chave == "FrmCadExtensao.menuImportarIconesArquivos") return "Importar Ícones dos Arquivos";
	if (chave == "FrmCadExtensao.menuExtrairIconesArquivos") return "Extrair Ícones dos Arquivos";
	if (chave == "FrmCadExtensao.ExtensaoJaCadastrada") return "Extensão já existe cadastrada!";
	if (chave == "FrmCadExtensao.ExtensaoSalvaSucesso") return "Extensão salva com sucesso!";
	if (chave == "FrmCadExtensao.ExtensaoCertezaExcluir") return "Tem Certeza, que você deseja excluir esta extensão?";
	if (chave == "FrmCadExtensao.ExtensaoCertezaTodosExcluir") return "Tem Certeza, que você deseja excluir todas as extensões?";
	if (chave == "FrmCadExtensao.ExtensaoExcluidaSucesso") return "Extensão excluída com sucesso!";
	if (chave == "FrmCadExtensao.ExtensoesExcluidasSucesso") return "Extensões excluídas com sucesso!";
	if (chave == "FrmCadExtensao.ExportarExtensao") return "Ícones salvos no mesmo diretório do sistema!";
	if (chave == "FrmCadExtensao.menuExportarBitmap") return "Exportar para Bitmap";

	if (chave == "FrmInfoDiretorio.titulo") return "Informações do Diretório / Arquivo";
	if (chave == "FrmInfoDiretorio.panelLegenda") return "Legenda dos Atributos";
	if (chave == "FrmInfoDiretorio.labArquivoComum") return "[ARQ] - Arquivo comum";
	if (chave == "FrmInfoDiretorio.labArquivoOculto") return "[HID] - Arquivo Oculto";
	if (chave == "FrmInfoDiretorio.labArquivoSistema") return "[SYS] - Arquivo de Sistema";
	if (chave == "FrmInfoDiretorio.labDiretorio") return "[DIR] - Diretório";
	if (chave == "FrmInfoDiretorio.labVolumeID") return "[VOL] - Volume ID";
	if (chave == "FrmInfoDiretorio.labArquivoSomenteLeitura") return "[ROL] - Arquivo Somente Leitura";
	if (chave == "FrmInfoDiretorio.item") return "Item";
	if (chave == "FrmInfoDiretorio.descricao") return "Descrição";

	if (chave == "FrmImportarDiretorio.titulo") return "Importando Diretório";
	if (chave == "FrmImportarDiretorio.barraStatus1") return "Total de linhas sendo processadas:";
	if (chave == "FrmImportarDiretorio.DiretorioExisteCatalogo") return "O diretório já existe no catálogo!";

	if (chave == "Dialogo.info") return "Informação";
	if (chave == "Dialogo.erro") return "Erro";
	if (chave == "Dialogo.confirma") return "Confirma";
	if (chave == "Dialogo.entrada") return "Informa";
	if (chave == "Dialogo.yesButtonText") return "Sim";
	if (chave == "Dialogo.yesButtonMnemonic") return "S";
	if (chave == "Dialogo.cancelButtonText") return "Cancelar";
	if (chave == "Dialogo.cancelButtonMnemonic") return "C";
	if (chave == "Dialogo.noButtonText") return "Não";
	if (chave == "Dialogo.noButtonMnemonic") return "N";
	if (chave == "Dialogo.okButtonText") return "OK";
	if (chave == "Dialogo.okButtonMnemonic") return "O";

	if (chave == "EscolhaArquivo.ApproveButtonText") return "Escolha o Diretório";
	if (chave == "EscolhaArquivo.ApproveButtonMnemonic") return "D";
	if (chave == "EscolhaArquivo.ApproveButtonToolTipText") return "Confirme a escolha do diretório.";
	if (chave == "EscolhaArquivo.lookInLabelMnemonic") return "E";
	if (chave == "EscolhaArquivo.lookInLabelText") return "Examinar em";
	if (chave == "EscolhaArquivo.saveInLabelMnemonic") return "S";
	if (chave == "EscolhaArquivo.saveInLabelText") return "Salvar em";
	if (chave == "EscolhaArquivo.upFolderToolTipText") return "Um nível acima";
	if (chave == "EscolhaArquivo.upFolderAccessibleName") return "Um nível acima";
	if (chave == "EscolhaArquivo.homeFolderToolTipText") return "Desktop";
	if (chave == "EscolhaArquivo.homeFolderAccessibleName") return "Desktop";
	if (chave == "EscolhaArquivo.newFolderToolTipText") return "Criar nova pasta";
	if (chave == "EscolhaArquivo.newFolderAccessibleName") return "Criar nova pasta";
	if (chave == "EscolhaArquivo.listViewButtonToolTipText") return "Lista";
	if (chave == "EscolhaArquivo.listViewButtonAccessibleName") return "Lista";
	if (chave == "EscolhaArquivo.detailsViewButtonToolTipText") return "Detalhes";
	if (chave == "EscolhaArquivo.detailsViewButtonAccessibleName") return "Detalhes";
	if (chave == "EscolhaArquivo.fileNameLabelMnemonic") return "N";
	if (chave == "EscolhaArquivo.fileNameLabelText") return "Nome do arquivo";
	if (chave == "EscolhaArquivo.filesOfTypeLabelMnemonic") return "A";
	if (chave == "EscolhaArquivo.filesOfTypeLabelText") return "Arquivos do tipo";
	if (chave == "EscolhaArquivo.fileNameHeaderText") return "Nome";
	if (chave == "EscolhaArquivo.fileSizeHeaderText") return "Tamanho";
	if (chave == "EscolhaArquivo.fileTypeHeaderText") return "Tipo";
	if (chave == "EscolhaArquivo.fileDateHeaderText") return "Data";
	if (chave == "EscolhaArquivo.fileAttrHeaderText") return "Atributos";
	if (chave == "EscolhaArquivo.cancelButtonText") return "Cancelar";
	if (chave == "EscolhaArquivo.cancelButtonMnemonic") return "C";
	if (chave == "EscolhaArquivo.cancelButtonToolTipText") return "Cancelar";
	if (chave == "EscolhaArquivo.openButtonText") return "Abrir";
	if (chave == "EscolhaArquivo.openButtonMnemonic") return "A";
	if (chave == "EscolhaArquivo.openButtonToolTipText") return "Abrir";
	if (chave == "EscolhaArquivo.saveButtonText") return "Salvar";
	if (chave == "EscolhaArquivo.saveButtonMnemonic") return "S";
	if (chave == "EscolhaArquivo.saveButtonToolTipText") return "Salvar";
	if (chave == "EscolhaArquivo.updateButtonText") return "Alterar";
	if (chave == "EscolhaArquivo.updateButtonMnemonic") return "A";
	if (chave == "EscolhaArquivo.updateButtonToolTipText") return "Alterar";
	if (chave == "EscolhaArquivo.helpButtonText") return "Ajuda";
	if (chave == "EscolhaArquivo.helpButtonMnemonic") return "A";
	if (chave == "EscolhaArquivo.helpButtonToolTipText") return "Ajuda";
	if (chave == "EscolhaArquivo.acceptAllFileFilterText") return "Todos os arquivos (*.*)";
	if (chave == "EscolhaArquivo.filtroTXT") return "Arquivo TXT (*.txt)";
	if (chave == "EscolhaArquivo.filtroCSV") return "Arquivo CSV (*.csv)";
	if (chave == "EscolhaArquivo.filtroHTML") return "Arquivo HTML (*.html)";
	if (chave == "EscolhaArquivo.filtroXML") return "Arquivo XML (*.xml)";
	if (chave == "EscolhaArquivo.filtroSQL") return "Arquivo SQL (*.sql)";
	if (chave == "EscolhaArquivo.filtroBMP") return "Arquivo BMP (*.bmp)";
	if (chave == "EscolhaArquivo.filtroICO") return "Arquivo ICO (*.ico)";
	if (chave == "EscolhaArquivo.filtroGIF") return "Arquivo GIF (*.gif)";
	if (chave == "EscolhaArquivo.filtroPNG") return "Arquivo JPEG (*.png)";
	if (chave == "EscolhaArquivo.filtroJPG") return "Arquivo PNG (*.jpg)";
	if (chave == "EscolhaArquivo.filtroTIF") return "Arquivo TIFF (*.tif)";
	if (chave == "EscolhaArquivo.todosDiretorios") return "Todos os diretórios";

	return chave;
}

// ---------------------------------------------------------------------------

std::vector<std::string> Rotinas::cListarArquivosDiretorios(const std::string &sDiretorio) {
	std::vector<std::string> lista;
	std::string nome, dir = sDiretorio;
	std::string ponto = ".";
	std::string pponto = "..";
	DIR *dp;
	struct dirent *ep;

	if (!testaSeparadorArquivo(dir)) {
		dir += BARRA_INVERTIDA;
	}

	dp = opendir(sDiretorio.c_str());
	if (dp != NULL) {
		while (ep = readdir(dp)) {
			nome = ep->d_name;
			//ep->d_namlen
			//ep->d_reclen
			//if (ep->d_type == DT_DIR) {}
			if (nome != ponto && nome != pponto) {
				nome = dir + nome;
				lista.push_back(nome);
			}
		}

		(void)closedir(dp);
	}
	else {
		perror("nao consigo abrir o diretorio");
	}

	return lista;
}

Arquivo Rotinas::FileInfoToArquivo(const std::string &sNomeArquivo) {
	struct stat fileInfo;
	DateTime datahora;
	std::string sAtributos = "";
	Arquivo arquivo;

	arquivo.setNome(ExtractFileName(sNomeArquivo));

	if (_access(sNomeArquivo.c_str(), 0) == 0) {
		stat(sNomeArquivo.c_str(), &fileInfo);

		datahora = DateTime::RawToDateTime(fileInfo.st_mtime);
						
		if ((fileInfo.st_mode & S_IFMT) == S_IFDIR)
			sAtributos += "[DIR]";
		else
			sAtributos += "[ARQ]";

		//S_IREAD S_IWRITE			
		if ((fileInfo.st_mode & S_IFMT) != S_IWUSR) {
			sAtributos += "[ROL]";
		}

		arquivo.setTamanho(fileInfo.st_size);
		arquivo.setModificado(datahora);
		arquivo.setAtributos(sAtributos);
	}
	else {
		arquivo.setTamanho(0);
		arquivo.setModificado(DateTime::Now());
		arquivo.setAtributos("");
	}

	return arquivo;
}

bool Rotinas::SListSaveToFile(const std::vector<std::string> lista, const std::string &sNomeArquivo) {
	std::fstream arquivo;
	std::ofstream fs;
	std::string linha;

	fs.open(sNomeArquivo.c_str(), std::ofstream::out);

	if (fs.is_open()) {
		for (unsigned int i = 0; i < lista.size(); i++) {
			linha = lista.at(i);
			fs << linha << std::endl;
		}
		fs.close();
		return true;
	}
	else {
		return false;
	}
}

std::vector<std::string> Rotinas::SListLoadFromFile(const std::string &sNomeArquivo) {
	std::ifstream fs;
	std::string linha;
	std::vector<std::string> lista;

	fs.open(sNomeArquivo.c_str());

	if (fs.is_open()) {
		while (std::getline(fs, linha)) {
			lista.push_back(linha);
		}
		fs.close();
	}

	return lista;
}

std::vector<std::string> Rotinas::SListSeparador(const std::string &texto, const char separador) {
	std::vector<std::string> lista;
	std::string stexto = texto, substr, pedaco, sep;
	sep = separador;

	if (ContainsStr(stexto, sep)) {
		pedaco = "";
		for (unsigned int i = 0; i < stexto.length(); i++) {
			pedaco += stexto[i];
			if (stexto[i] == separador) {
				substr = SubString(pedaco, 1, pedaco.length() - 1);
				lista.push_back(substr);
				pedaco = "";
			}
		}
		lista.push_back(pedaco);
	}
	else {
		lista.push_back(stexto);
	}

	return lista;
}

std::string Rotinas::SListTexto(const std::vector<std::string> lista) {
	std::string linha = "";
	std::string texto = "";
	size_t ntamlista = lista.size();

	if (ntamlista > 0) {
		for (unsigned int i = 0; i < ntamlista; i++) {
			linha = lista.at(i);
			texto += linha;
		}
	}
	return texto;
}

bool Rotinas::BlobSaveToFile(const void* blob, size_t tamanho, const std::string &sNomeArquivo) {
	bool ret = true;
	FILE* fp;
	errno_t erro;

	erro = fopen_s(&fp, sNomeArquivo.c_str(), "wb");

	if (NULL != fp)
	{
		size_t ntamanho = fwrite(blob, tamanho, 1, fp);

		if (ntamanho == tamanho) {
			ret = false;
		}

		fclose(fp);
	}
	else
	{
		ret = false;
	}

	return ret;
}

size_t Rotinas::BlobLoadFromFile(const std::string &sNomeArquivo, void** blob) {
	size_t ret = 0;
	FILE* fp;
#ifndef __GNUC__
	errno_t erro;
	size_t tamanho = 16384; //16 * 1024;
	char* buffer;

	erro = fopen_s(&fp, sNomeArquivo.c_str(), "rb");
#else
	fp = fopen(sNomeArquivo.c_str(), "rb");
#endif

	if (NULL != fp)
	{
		/*
		fseek(fp, 0L, SEEK_END);
		tamanho = ftell(fp);
		//fseek(fp, 0L, SEEK_SET);
		rewind(fp);
		*/

#ifndef __GNUC__
		buffer = NewStr(tamanho);
#else
		char buffer[16 * 1024];
		buffer[0] = '\0';
#endif
		*blob = &buffer;

		size_t ntamanho = fread(*blob, sizeof(char), tamanho, fp);
		buffer[ntamanho] = '\0';
		fclose(fp);

		ret = ntamanho;
	}

	return ret;
}

// ---------------------------------------------------------------------------

ImagemBuffer Rotinas::XPMToPixbuf(const char** xpm) {
	ImagemBuffer pxb;// = Gdk::Pixbuf::create_from_xpm_data(xpm);
	return pxb;
}

ImagemBuffer Rotinas::imagemToPixbuf(const std::string &sNomeImagem) {
	ImagemBuffer pixbuf;

	std::string caminho = Rotinas::AppDirName();
	caminho += "imagens/" + sNomeImagem;

	pixbuf = ArquivoToPixbuf(caminho);

	return pixbuf;
}

ImagemBuffer Rotinas::ArquivoToPixbuf(const std::string &sArquivo) {
	ImagemBuffer pixbuf;
	long size;

	try {
		std::ifstream infile(sArquivo, std::ifstream::binary);
		
		infile.seekg(0, infile.end);
		size = (long)infile.tellg();
		infile.seekg(0);

		pixbuf.tamanho = size;
		pixbuf.buffer = new char[size];

		infile.read(pixbuf.buffer, size);

		infile.close();
	}
	catch (std::exception& e)
	{
		pixbuf.tamanho = -1;
		pixbuf.buffer = NULL;

		std::cerr << "ArquivoToPixbuf Erro: " << e.what() << std::endl;
	}

	return pixbuf;
}

//formatos = "jpeg", "tiff", "png", "ico" or "bmp"
bool Rotinas::PixbufToArquivo(ImagemBuffer pixbuf, 
	const std::string &sArquivo, const std::string &formato) {
	bool bSalvou = false;

	try {
		std::ofstream outfile(sArquivo, std::ofstream::binary);

		outfile.write(pixbuf.buffer, pixbuf.tamanho);
		outfile.flush();

		//delete[] pixbuf.buffer;

		outfile.close();

		bSalvou = true;
	}
	catch (std::exception& e)
	{
		std::cerr << "PixbufToArquivo Erro: " << e.what() << std::endl;
	}

	return bSalvou;
}

ImagemBuffer Rotinas::BlobToPixbuf(const void* blob, size_t tamanho) {
	ImagemBuffer pixbuf;

	try {
		pixbuf.tamanho = tamanho;
		pixbuf.buffer = new char[tamanho];
		pixbuf.buffer[0] = '\0';

		memcpy(pixbuf.buffer, blob, tamanho);
		pixbuf.buffer[tamanho] = '\0';

	}
	catch (std::exception& e)
	{
		pixbuf.tamanho = -1;
		pixbuf.buffer = NULL;

		std::cerr << "ArquivoToPixbuf Erro: " << e.what() << std::endl;
	}

	return pixbuf;
}

//formatos = "jpeg", "tiff", "png", "ico" or "bmp"
size_t Rotinas::PixbufToBlob(ImagemBuffer pixbuf, void** blob, const std::string &formato) {

	try {
		*blob = new char[pixbuf.tamanho];
		memcpy(*blob, pixbuf.buffer, pixbuf.tamanho);
	}
	catch (std::exception& e)
	{
		pixbuf.tamanho = -1;
		pixbuf.buffer = NULL;

		std::cerr << "ArquivoToPixbuf Erro: " << e.what() << std::endl;
	}
	
	return pixbuf.tamanho;
}

ImagemBuffer Rotinas::extrairPixbufArquivo(const std::string &sCaminho, int tamanho) {
	ImagemBuffer pixbuf;

	return pixbuf;
}


void Rotinas::testar() {
	char *saida = NewStr();
	std::string sApp = AppDirPath();
	std::string sAppDir = AppDirName();
	std::string sAppFile = AppFileName();

	std::string sDir = "    c:\\ago%ra\\CAMINHO\\teste.olha.depois    ";
	
	ImagemBuffer pixbuf;
	pixbuf.buffer = NULL;
	pixbuf.tamanho = -1;

	void *blob = NULL;
	std::string sImgArq = sAppDir + "imagens/diretorio.bmp";
	size_t ntamanho = BlobLoadFromFile(sImgArq, &blob);
	
	/*
	pixbuf = extrairPixbufArquivo(argumentos.texto, 32);
	if (pixbuf.buffer != NULL) {
		OutputDebugString(CharToWChar("extrairPixbufArquivo OK"));

		if (PixbufToArquivo(pixbuf, "C:\\Temp\\blob\\dir32.bmp", EXTENSAO_BMP)) {
			OutputDebugString(CharToWChar("PixbufToArquivo OK"));
		}
	}
	*/
	
	
	pixbuf = BlobToPixbuf(blob, ntamanho);
	if (pixbuf.buffer != NULL) {
		OutputDebugString(CharToWChar("BlobToPixbuf OK\n"));

		blob = NULL;
		size_t ntamanho2 = PixbufToBlob(pixbuf, &blob, EXTENSAO_BMP);
		if (ntamanho2 > 0 && blob != NULL) {
			OutputDebugString(CharToWChar("PixbufToBlob OK\n"));
		}

		if (PixbufToArquivo(pixbuf, "C:\\Temp\\blob\\dir.bmp", EXTENSAO_BMP)) {
			OutputDebugString(CharToWChar("PixbufToArquivo OK\n"));
		}
	}

	pixbuf = imagemToPixbuf("diretorio.bmp");
	if (pixbuf.buffer != NULL) {
		OutputDebugString(CharToWChar("imagemToPixbuf OK\n"));

		if (PixbufToArquivo(pixbuf, "C:\\Temp\\blob\\dir.gif", EXTENSAO_GIF)) {
			OutputDebugString(CharToWChar("PixbufToArquivo OK\n"));
		}
	}

	pixbuf = ArquivoToPixbuf(sImgArq);
	if (pixbuf.buffer != NULL) {
		OutputDebugString(CharToWChar("ArquivoToPixbuf OK\n"));

		if (PixbufToArquivo(pixbuf, "C:\\Temp\\blob\\dir.jpg", EXTENSAO_JPEG)) {
			OutputDebugString(CharToWChar("PixbufToArquivo OK\n"));
		}
	}
	
		
	std::vector<std::string> listaDir = cListarArquivosDiretorios("c:\\VM");
	//std::vector<std::string> listaDir = listarArquivosDiretorios("c:\\VM");

	size_t tamlistaDir = listaDir.size();
	std::string linhaDir = "";
	for (unsigned int i = 0; i < tamlistaDir; i++)
	{
		linhaDir = listaDir.at(i);

		Arquivo arq = FileInfoToArquivo(linhaDir);

		std::snprintf(saida, TAM_MAX_STR, "cListarArquivosDiretorios[%d]: %s, %s\n", i, linhaDir.c_str(), arq.getNome().c_str());
		OutputDebugString(CharToWChar(saida));
	}
	


	std::snprintf(saida, TAM_MAX_STR, "sDir: [%s]\n", sDir.c_str()); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "AppPath: %s\n", sApp.c_str()); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "FileExists: %s\n", (FileExists(sApp) ? "true" : "false")); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "DirectoryExists: %s\n", (DirectoryExists(sAppDir) ? "true" : "false")); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "ExtractFilePath: %s\n", ExtractFilePath(sApp).c_str()); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "ExtractFileName: %s\n", ExtractFileName(sApp).c_str()); OutputDebugString(CharToWChar(saida));

	std::snprintf(saida, TAM_MAX_STR, "Length(): %llu\n", sDir.length()); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "Trim(): [%s]\n", Trim(sDir).c_str()); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "tamanho Trim(): %llu\n", Trim(sDir).length()); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "LowerCase(): %s\n", LowerCase(sDir).c_str()); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "UpperCase(): %s\n", UpperCase(sDir).c_str()); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "Pos('.'): %llu\n", Pos(".", sDir)); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "LastDelimiter('.'): %llu\n", LastDelimiter(".", sDir)); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "QuotedStr(): %s\n", QuotedStr(sDir).c_str()); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "IntToStr(245789): %s\n", IntToStr(245789).c_str()); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "StrToInt() --> 245789: %d\n", StrToInt("245789")); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "StrToLong() --> 4200155136: %llu\n", StrToULongLong("4200155136")); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "DoubleToStr(15.557878): %s\n", DoubleToStr(15.557878).c_str()); OutputDebugString(CharToWChar(saida));

	std::snprintf(saida, TAM_MAX_STR, "SubString(): %s\n", SubString(sDir, 8, 6).c_str()); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "ReplaceAll(): [%s]\n", ReplaceAll(sDir, "\\", "@").c_str()); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "trocaSeparador(): [%s]\n", trocaSeparador(sDir).c_str()); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "testaNull(NULL): %s\n", testaNull(NULL).c_str()); OutputDebugString(CharToWChar(saida));

	std::snprintf(saida, TAM_MAX_STR, "StartsStr(DVD, JOGOS2_DVDS/TESTE): %s\n", (StartsStr("DVD", "JOGOS2_DVDS/TESTE") ? "true" : "false")); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "StartsStr(DVD, DVDSJOGOS2_/TESTE): %s\n", (StartsStr("DVD", "DVDSJOGOS2_/TESTE") ? "true" : "false")); OutputDebugString(CharToWChar(saida));

	std::snprintf(saida, TAM_MAX_STR, "ContainsStr(JOGOS2_DVDS/TESTE): %s\n", (ContainsStr("DVDSJOGOS2_/TESTE", "DVDSJOGOS2_/TESTE") ? "true" : "false")); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "EndsStr(TESTE, JOGOS2_DVDS/TESTE): %s\n", (EndsStr("TESTE", "DVDSJOGOS2_/TESTE") ? "true" : "false")); OutputDebugString(CharToWChar(saida));

	DateTime dt1 = DateTime::Now();
	std::snprintf(saida, TAM_MAX_STR, "formataDate(): %s\n", dt1.FormatDateTime(FORMATO_DATAHORA).c_str()); OutputDebugString(CharToWChar(saida));
	DateTime dt2 = DateTime::StrToDateTime("03/02/2017 15:23:32");
	std::snprintf(saida, TAM_MAX_STR, "StringToDate(03/02/2017 15:23:32): %s\n", dt2.FormatDateTime(FORMATO_DATAHORA).c_str()); OutputDebugString(CharToWChar(saida));

	std::snprintf(saida, TAM_MAX_STR, "FormatLong(4200155136): %s\n", ULongToStr(4200155136).c_str()); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "FormatDouble(15.544878): %s\n", DoubleToStr(15.544878).c_str()); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "FormatDouble(15.547878): %s\n", DoubleToStr(15.547878).c_str()); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "FormatDouble(15.557878): %s\n", DoubleToStr(15.557878).c_str()); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "FormatDouble(15.567878): %s\n", DoubleToStr(15.567878).c_str()); OutputDebugString(CharToWChar(saida));

	std::snprintf(saida, TAM_MAX_STR, "MontaTamanho() --> 3.91 GB: %s\n", MontaTamanho(4200155136).c_str()); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "MontaTamanho() --> 3.50 GB: %s\n", MontaTamanho(3757244416).c_str()); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "MontaTamanho() --> 2.29 GB: %s\n", MontaTamanho(2455207936).c_str()); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "MontaTamanho() --> 888.18 PB: %s\n", MontaTamanhoBig(999999999999999999.9999).c_str()); OutputDebugString(CharToWChar(saida));

	std::vector<std::string> lista;
	std::string linha = "";

	lista = SListSeparador(sDir, '\\');

	size_t tamlista = lista.size();

	for (unsigned int i = 0; i < tamlista; i++)
	{
		linha = lista.at(i);
		std::snprintf(saida, TAM_MAX_STR, "SListSeparador[%d]: %s\n", i, linha.c_str()); OutputDebugString(CharToWChar(saida));
	}

	std::string arquivo = ExtractFilePath(sApp);
	arquivo += "exemplo.txt";

	std::snprintf(saida, TAM_MAX_STR, "arquivo: %s\n", arquivo.c_str()); OutputDebugString(CharToWChar(saida));

	if (SListSaveToFile(lista, arquivo)) {

		if (FileExists(arquivo)) {

			lista = SListLoadFromFile(arquivo);
			tamlista = lista.size();

			for (unsigned int i = 0; i < tamlista; i++) {
				linha = lista.at(i);
				std::snprintf(saida, TAM_MAX_STR, "SListLoadFromFile[%d]: %s\n", i, linha.c_str()); OutputDebugString(CharToWChar(saida));
			}

			if (DeleteFromFile(arquivo)) {
				if (!FileExists(arquivo)) {
					std::snprintf(saida, TAM_MAX_STR, "DeleteFromFile: OK\n"); OutputDebugString(CharToWChar(saida));
				}
			}
			else {
				std::snprintf(saida, TAM_MAX_STR, "DeleteFromFile: FALHOU\n"); OutputDebugString(CharToWChar(saida));
			}

		}

	}

}



}
}
