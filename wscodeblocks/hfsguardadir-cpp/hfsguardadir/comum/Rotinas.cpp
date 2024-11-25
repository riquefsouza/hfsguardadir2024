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

#include <unistd.h>
//#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>
//#include <tchar.h>

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
	int tamanho = wcslen(origem);
#ifndef __GNUC__
	size_t numCharsConvertidos;
#endif

	if (tamanho > 0)
	{
#ifdef __GNUC__
		wcstombs(destino, origem, tamanho);
#else
		wcstombs_s(&numCharsConvertidos, destino, sizeof destino, origem, tamanho);
#endif
	}
	return destino;
}

int Rotinas::cLastIndexOf(const char* texto, const char alvo)
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

char* Rotinas::cTrim(const char* texto)
{
	unsigned int j = 0, inicio = 0, fim = 0;
	unsigned char compara;
	int tamanho = strlen(texto);
	char* retorno = Rotinas::cNewStr(TAM_MAX_STR);

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

char* Rotinas::cLowerCase(const char* texto)
{
	unsigned int i = 0;
	unsigned int j = 0;
	const int tamanho = strlen(texto);
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
	int tamanho = strlen(texto);
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

int Rotinas::cPos(const char* subtexto, const char* texto)
{
	const char* retorno = strstr(texto, subtexto);
	if (retorno == NULL)
		return -1;
	else
		return (retorno - texto) + 1;
}

int Rotinas::cFind(const char* subtexto, const char* texto, int posInicial)
{
	int tamtexto = strlen(texto);
	char* stexto = Rotinas::cStrndup(texto + posInicial, tamtexto + 1);

	const char* retorno = strstr(stexto, subtexto);
	if (retorno == NULL)
		return -1;
	else
		return (retorno - stexto + posInicial);
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

int Rotinas::cLastDelimiter(const char* sub, const char* texto)
{
	char* parte;
	int retorno = -1, tamparte = 0;
	int tamanho = strlen(texto);
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

char* Rotinas::cSubString(const char* texto, int inicio, int tamanho)
{
	char* retorno = NULL;
	int tamtexto = strlen(texto);

	if (tamtexto > 0)
	{
		retorno = Rotinas::cStrndup(texto + inicio - 1, tamanho + 1);
	}
	return retorno;
}

char* Rotinas::cQuotedStr(const char* texto)
{
	char* retorno;
	int tamanho = strlen(texto) + 4;

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
	int tamanho = strlen(texto);
	//int tamvelho = strlen(velho);
	int tamnovo = strlen(novo);
	int tamparte = 0;
	//int tamfinal = 0;
#ifndef __GNUC__
	char *next_token = NULL;
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
		//tamfinal = (tamanho - (j*tamvelho)) + (j*tamnovo);
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
	int tamanho = strlen(texto);

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
char* Rotinas::NewStr(unsigned int tamanho)
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
	int tamanho = wcslen(origem);
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
	int tamanho = strlen(origem);
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

int Rotinas::Pos(const std::string &subtexto, const std::string &texto) {
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

int Rotinas::LastDelimiter(const std::string &subtexto, const std::string &texto) {
	std::string::size_type loc = texto.find_last_of(subtexto);
	if (loc != std::string::npos)
		return (loc + 1);
	else
		return -1;
}

std::string Rotinas::SubString(const std::string &texto, int inicio, int tamanho) {
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

	if (access(sNomeArquivo.c_str(), 0) == 0) {
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

	if (access(sNomeArquivo.c_str(), 0) == 0) {
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
	if (strcmp(chave, "HFSGuardaDir.ErroInicial")==0) return "Ocorreu um erro no aplicativo!";

	if (strcmp(chave, "Tabela.nome")==0) return "Nome";
	if (strcmp(chave, "Tabela.tamanho")==0) return "Tamanho";
	if (strcmp(chave, "Tabela.tipo")==0) return "Tipo";
	if (strcmp(chave, "Tabela.modificado")==0) return "Modificado";
	if (strcmp(chave, "Tabela.atributos")==0) return "Atributos";
	if (strcmp(chave, "Tabela.caminho")==0) return "Caminho";
	if (strcmp(chave, "Tabela.aba")==0) return "Aba";

	if (strcmp(chave, "Aba.codigo")==0) return "Código:";
	if (strcmp(chave, "Aba.nome")==0) return "Nome:";

	if (strcmp(chave, "Tipo.codigo")==0) return "Código:";
	if (strcmp(chave, "Tipo.nome")==0) return "Nome:";

	if (strcmp(chave, "TipoLista.arquivo")==0) return "Arquivo";
	if (strcmp(chave, "TipoLista.diretorio")==0) return "Diretório";

	if (strcmp(chave, "ConexaoParams.nome")==0) return "Nome:";
	if (strcmp(chave, "ConexaoParams.driver")==0) return "Driver:";
	if (strcmp(chave, "ConexaoParams.url")==0) return "URL:";
	if (strcmp(chave, "ConexaoParams.login")==0) return "Login:";
	if (strcmp(chave, "ConexaoParams.senha")==0) return "Senha:";

	if (strcmp(chave, "Diretorio.aba")==0) return "Aba:";
	if (strcmp(chave, "Diretorio.codigo")==0) return "Código:";
	if (strcmp(chave, "Diretorio.ordem")==0) return "Ordem:";
	if (strcmp(chave, "Diretorio.nome")==0) return "Nome:";
	if (strcmp(chave, "Diretorio.tamanho")==0) return "Tamanho:";
	if (strcmp(chave, "Diretorio.tipo")==0) return "Tipo:";
	if (strcmp(chave, "Diretorio.modificado")==0) return "Modificado:";
	if (strcmp(chave, "Diretorio.atributos")==0) return "Atributos:";
	if (strcmp(chave, "Diretorio.codDirPai")==0) return "Código Diretório Pai:";
	if (strcmp(chave, "Diretorio.caminho")==0) return "Caminho:";

	if (strcmp(chave, "Extensao.codigo")==0) return "Código:";
	if (strcmp(chave, "Extensao.nome")==0) return "Extensão:";
	if (strcmp(chave, "Extensao.icone")==0) return "Ícone:";
	if (strcmp(chave, "Extensao.arquivo")==0) return "arquivo(file)";
	if (strcmp(chave, "Extensao.diretorio")==0) return "diretorio(directory)";
	if (strcmp(chave, "Extensao.zip")==0) return ".zip";

	if (strcmp(chave, "FrmPrincipal.titulo")==0) return "HFSGuardaDiretorio 2.0 - Catalogador de Diretórios";
	if (strcmp(chave, "FrmPrincipal.barraStatus1")==0) return "Quantidade Total: , Tamanho Total:";
	if (strcmp(chave, "FrmPrincipal.btnImportarDiretorio")==0) return "Importar Diretório";
	if (strcmp(chave, "FrmPrincipal.btnPesquisa")==0) return "Pesquisar";
	if (strcmp(chave, "FrmPrincipal.Aba1")==0) return "DISCO1";
	if (strcmp(chave, "FrmPrincipal.menuAba")==0) return "Aba";
	if (strcmp(chave, "FrmPrincipal.menuIncluirNovaAba")==0) return "Incluir Nova Aba";
	if (strcmp(chave, "FrmPrincipal.menuDiretorio")==0) return "Diretório";
	if (strcmp(chave, "FrmPrincipal.menuAlterarNomeAbaAtiva")==0) return "Alterar Nome da Aba Ativa";
	if (strcmp(chave, "FrmPrincipal.menuExcluirAbaAtiva")==0) return "Excluir Aba Ativa";
	if (strcmp(chave, "FrmPrincipal.menuImportarDiretorio")==0) return "Importar Diretório";
	if (strcmp(chave, "FrmPrincipal.menuImportarSubDiretorios")==0) return "Importar SubDiretórios";
	if (strcmp(chave, "FrmPrincipal.menuCompararDiretorios")==0) return "Comparar Diretórios";
	if (strcmp(chave, "FrmPrincipal.menuCadastrarExtensaoArquivo")==0) return "Cadastrar Extensão de Arquivo";
	if (strcmp(chave, "FrmPrincipal.menuExpandirDiretorios")==0) return "Expandir Diretórios";
	if (strcmp(chave, "FrmPrincipal.menuColapsarDiretorios")==0) return "Colapsar Diretórios";
	if (strcmp(chave, "FrmPrincipal.menuExportarDiretoriosAbaAtiva")==0) return "Exportar Diretórios da Aba Ativa";
	if (strcmp(chave, "FrmPrincipal.menuTXT")==0) return "TXT";
	if (strcmp(chave, "FrmPrincipal.menuCSV")==0) return "CSV";
	if (strcmp(chave, "FrmPrincipal.menuHTML")==0) return "HTML";
	if (strcmp(chave, "FrmPrincipal.menuXML")==0) return "XML";
	if (strcmp(chave, "FrmPrincipal.menuSQL")==0) return "SQL";
	if (strcmp(chave, "FrmPrincipal.menuImportarDiretoriosViaXML")==0) return "Importar Diretórios Via XML";
	if (strcmp(chave, "FrmPrincipal.menuGravarLogImportacao")==0) return "Gravar Log da Importação";
	if (strcmp(chave, "FrmPrincipal.menuVisao")==0) return "Visão";
	if (strcmp(chave, "FrmPrincipal.menuMostrarOcultarArvoreDirAbaAtiva")==0) return "Mostrar/Ocultar Árvore de diretórios da Aba Ativa";
	if (strcmp(chave, "FrmPrincipal.menuMostrarOcultarListaItensPesquisados")==0) return "Mostrar/Ocultar lista de itens pesquisados";
	if (strcmp(chave, "FrmPrincipal.menuSobre")==0) return "Sobre";
	if (strcmp(chave, "FrmPrincipal.TamMaxPesquisa")==0) return "A pesquisa só é feita com pelo menos 2 caracteres!";
	if (strcmp(chave, "FrmPrincipal.DigitaNomeDiretorio")==0) return "Este diretório não possui um nome.\nDigite o nome do diretório!";
	if (strcmp(chave, "FrmPrincipal.ValidaNomeDiretorio")==0) return "Nenhum nome de diretório informado!";
	if (strcmp(chave, "FrmPrincipal.ErroSalvarArquivo")==0) return "Ocorreu um erro ao salvar o arquivo.";
	if (strcmp(chave, "FrmPrincipal.SucessoExportar")==0) return "Exportação realizada com sucesso!";
	if (strcmp(chave, "FrmPrincipal.ExcluirDiretorioSelecionado")==0) return "Tem Certeza, que você deseja excluir este diretório, isto implicará na destruição de todos os seus items catalogados?";
	if (strcmp(chave, "FrmPrincipal.ImportacaoNaoRealizada")==0) return "Importação não realizada!";
	if (strcmp(chave, "FrmPrincipal.DiretorioExisteCatalogo")==0) return "Este diretório já existe no catálogo!";
	if (strcmp(chave, "FrmPrincipal.ImportacaoRealizada")==0) return "Importação realizada com sucesso!";
	if (strcmp(chave, "FrmPrincipal.ErroAbrirDir")==0) return "Um erro ocorreu. Nenhum diretório foi escolhido.";
	if (strcmp(chave, "FrmPrincipal.DirImportacaoSucesso")==0) return "Importação do(s) diretório(s) realizada com sucesso!";
	if (strcmp(chave, "FrmPrincipal.DigitaIncluirNovaAba")==0) return "Digite o Nome da Nova Aba?";
	if (strcmp(chave, "FrmPrincipal.DigitaAlterarNomeAba")==0) return "Digite o Novo Nome da Aba Ativa?";
	if (strcmp(chave, "FrmPrincipal.ConfirmaExcluirAba")==0) return "Tem Certeza, que você deseja excluir esta aba, \nisto implicará na destruição de todos os seus itens catalogados?";
	if (strcmp(chave, "FrmPrincipal.ValidaExcluirAba")==0) return "A primeira Aba não pode ser excluída!";
	if (strcmp(chave, "FrmPrincipal.menuSobreCatalogador")==0) return "Sobre o Catalogador";
	if (strcmp(chave, "FrmPrincipal.menuIdioma")==0) return "Idioma";
	if (strcmp(chave, "FrmPrincipal.menuPortugues")==0) return "Português [Portuguese]";
	if (strcmp(chave, "FrmPrincipal.menuIngles")==0) return "Inglês [English]";
	if (strcmp(chave, "FrmPrincipal.menuEspanhol")==0) return "Espanhol [Spanish]";
	if (strcmp(chave, "FrmPrincipal.menuFrances")==0) return "Francês [French]";
	if (strcmp(chave, "FrmPrincipal.menuItaliano")==0) return "Italiano [Italian]";
	if (strcmp(chave, "FrmPrincipal.menuAlemao")==0) return "Alemão [German]";
	if (strcmp(chave, "FrmPrincipal.menuJapones")==0) return "Japonês [Japanese]";
	if (strcmp(chave, "FrmPrincipal.menuCoreano")==0) return "Coreano [Korean]";
	if (strcmp(chave, "FrmPrincipal.menuChinesTradicional")==0) return "Chinês Tradicional [Traditional Chinese]";
	if (strcmp(chave, "FrmPrincipal.menuExcluirDiretorioSelecionado")==0) return "Excluir Diretório Selecionado";
	if (strcmp(chave, "FrmPrincipal.menuInformacoesDiretorioArquivo")==0) return "Informações do Diretório / Arquivo";

	if (strcmp(chave, "FrmSobre.titulo")==0) return "Sobre o Catalogador";
	if (strcmp(chave, "FrmSobre.label1")==0) return "HFSGuardaDir 2.0 - Catalogador de Diretórios";
	if (strcmp(chave, "FrmSobre.label2")==0) return "Desenvolvido em Java com Swing, Versão: 2.0";
	if (strcmp(chave, "FrmSobre.label3")==0) return "Por Henrique Figueiredo de Souza";
	if (strcmp(chave, "FrmSobre.label4")==0) return "Todos os direitos reservados, 2015";
	if (strcmp(chave, "FrmSobre.Propriedade")==0) return "Propriedade";
	if (strcmp(chave, "FrmSobre.Valor")==0) return "Valor";

	if (strcmp(chave, "FrmSplash.label1")==0) return "HFSGuardaDiretorio 2.0";
	if (strcmp(chave, "FrmSplash.label2")==0) return "Catalogador de Diretórios";

	if (strcmp(chave, "FrmCompararDiretorio.titulo")==0) return "Comparar Diretórios";
	if (strcmp(chave, "FrmCompararDiretorio.btnCompararDiretorios")==0) return "Comparar Diretórios";
	if (strcmp(chave, "FrmCompararDiretorio.btnSalvarLog")==0) return "Salvar Log";
	if (strcmp(chave, "FrmCompararDiretorio.barraStatus1")==0) return "Total de diferenças encontradas:";
	if (strcmp(chave, "FrmCompararDiretorio.panelDiretorio1")==0) return "Diretório 1";
	if (strcmp(chave, "FrmCompararDiretorio.labDiferencasEncontradas")==0) return "Diferenças Encontradas";
	if (strcmp(chave, "FrmCompararDiretorio.panelDiretorio2")==0) return "Diretório 2";
	if (strcmp(chave, "FrmCompararDiretorio.NenhumaDiferencaEncontrada")==0) return "Nenhuma diferença encontrada!";
	if (strcmp(chave, "FrmCompararDiretorio.DiretoriosNaoSelecionados")==0) return "Diretórios não selecionados!";
	if (strcmp(chave, "FrmCompararDiretorio.LogSalvoMemoDirSistema")==0) return "Log salvo no mesmo diretório do sistema!";

	if (strcmp(chave, "FrmCadExtensao.titulo")==0) return "Cadastro de Extensão de Arquivo";
	if (strcmp(chave, "FrmCadExtensao.extensao")==0) return "Extensão";
	if (strcmp(chave, "FrmCadExtensao.icone")==0) return "Ícone";
	if (strcmp(chave, "FrmCadExtensao.btnIncluir")==0) return "Incluir";
	if (strcmp(chave, "FrmCadExtensao.btnExcluir")==0) return "Excluir";
	if (strcmp(chave, "FrmCadExtensao.menuExtensao")==0) return "Extensão";
	if (strcmp(chave, "FrmCadExtensao.menuExportarTodos")==0) return "Exportar Todos";
	if (strcmp(chave, "FrmCadExtensao.menuImportarTodos")==0) return "Importar Todos";
	if (strcmp(chave, "FrmCadExtensao.menuIncluirExtensao")==0) return "Incluir Extensão";
	if (strcmp(chave, "FrmCadExtensao.menuExcluirExtensao")==0) return "Excluir Extensão";
	if (strcmp(chave, "FrmCadExtensao.menuExcluirTodasExtensoes")==0) return "Excluir Todas Extensões";
	if (strcmp(chave, "FrmCadExtensao.menuExportarIcone")==0) return "Exportar para Ícone";
	if (strcmp(chave, "FrmCadExtensao.menuExportarGIF")==0) return "Exportar para GIF";
	if (strcmp(chave, "FrmCadExtensao.menuExportarJPEG")==0) return "Exportar para JPEG";
	if (strcmp(chave, "FrmCadExtensao.menuExportarPNG")==0) return "Exportar para PNG";
	if (strcmp(chave, "FrmCadExtensao.menuExportarTIFF")==0) return "Exportar para TIFF";
	if (strcmp(chave, "FrmCadExtensao.menuImportarIconesArquivos")==0) return "Importar Ícones dos Arquivos";
	if (strcmp(chave, "FrmCadExtensao.menuExtrairIconesArquivos")==0) return "Extrair Ícones dos Arquivos";
	if (strcmp(chave, "FrmCadExtensao.ExtensaoJaCadastrada")==0) return "Extensão já existe cadastrada!";
	if (strcmp(chave, "FrmCadExtensao.ExtensaoSalvaSucesso")==0) return "Extensão salva com sucesso!";
	if (strcmp(chave, "FrmCadExtensao.ExtensaoCertezaExcluir")==0) return "Tem Certeza, que você deseja excluir esta extensão?";
	if (strcmp(chave, "FrmCadExtensao.ExtensaoCertezaTodosExcluir")==0) return "Tem Certeza, que você deseja excluir todas as extensões?";
	if (strcmp(chave, "FrmCadExtensao.ExtensaoExcluidaSucesso")==0) return "Extensão excluída com sucesso!";
	if (strcmp(chave, "FrmCadExtensao.ExtensoesExcluidasSucesso")==0) return "Extensões excluídas com sucesso!";
	if (strcmp(chave, "FrmCadExtensao.ExportarExtensao")==0) return "Ícones salvos no mesmo diretório do sistema!";
	if (strcmp(chave, "FrmCadExtensao.menuExportarBitmap")==0) return "Exportar para Bitmap";

	if (strcmp(chave, "FrmInfoDiretorio.titulo")==0) return "Informações do Diretório / Arquivo";
	if (strcmp(chave, "FrmInfoDiretorio.panelLegenda")==0) return "Legenda dos Atributos";
	if (strcmp(chave, "FrmInfoDiretorio.labArquivoComum")==0) return "[ARQ] - Arquivo comum";
	if (strcmp(chave, "FrmInfoDiretorio.labArquivoOculto")==0) return "[HID] - Arquivo Oculto";
	if (strcmp(chave, "FrmInfoDiretorio.labArquivoSistema")==0) return "[SYS] - Arquivo de Sistema";
	if (strcmp(chave, "FrmInfoDiretorio.labDiretorio")==0) return "[DIR] - Diretório";
	if (strcmp(chave, "FrmInfoDiretorio.labVolumeID")==0) return "[VOL] - Volume ID";
	if (strcmp(chave, "FrmInfoDiretorio.labArquivoSomenteLeitura")==0) return "[ROL] - Arquivo Somente Leitura";
	if (strcmp(chave, "FrmInfoDiretorio.item")==0) return "Item";
	if (strcmp(chave, "FrmInfoDiretorio.descricao")==0) return "Descrição";

	if (strcmp(chave, "FrmImportarDiretorio.titulo")==0) return "Importando Diretório";
	if (strcmp(chave, "FrmImportarDiretorio.barraStatus1")==0) return "Total de linhas sendo processadas:";
	if (strcmp(chave, "FrmImportarDiretorio.DiretorioExisteCatalogo")==0) return "O diretório já existe no catálogo!";

	if (strcmp(chave, "Dialogo.info")==0) return "Informação";
	if (strcmp(chave, "Dialogo.erro")==0) return "Erro";
	if (strcmp(chave, "Dialogo.confirma")==0) return "Confirma";
	if (strcmp(chave, "Dialogo.entrada")==0) return "Informa";
	if (strcmp(chave, "Dialogo.yesButtonText")==0) return "Sim";
	if (strcmp(chave, "Dialogo.yesButtonMnemonic")==0) return "S";
	if (strcmp(chave, "Dialogo.cancelButtonText")==0) return "Cancelar";
	if (strcmp(chave, "Dialogo.cancelButtonMnemonic")==0) return "C";
	if (strcmp(chave, "Dialogo.noButtonText")==0) return "Não";
	if (strcmp(chave, "Dialogo.noButtonMnemonic")==0) return "N";
	if (strcmp(chave, "Dialogo.okButtonText")==0) return "OK";
	if (strcmp(chave, "Dialogo.okButtonMnemonic")==0) return "O";

	if (strcmp(chave, "EscolhaArquivo.ApproveButtonText")==0) return "Escolha o Diretório";
	if (strcmp(chave, "EscolhaArquivo.ApproveButtonMnemonic")==0) return "D";
	if (strcmp(chave, "EscolhaArquivo.ApproveButtonToolTipText")==0) return "Confirme a escolha do diretório.";
	if (strcmp(chave, "EscolhaArquivo.lookInLabelMnemonic")==0) return "E";
	if (strcmp(chave, "EscolhaArquivo.lookInLabelText")==0) return "Examinar em";
	if (strcmp(chave, "EscolhaArquivo.saveInLabelMnemonic")==0) return "S";
	if (strcmp(chave, "EscolhaArquivo.saveInLabelText")==0) return "Salvar em";
	if (strcmp(chave, "EscolhaArquivo.upFolderToolTipText")==0) return "Um nível acima";
	if (strcmp(chave, "EscolhaArquivo.upFolderAccessibleName")==0) return "Um nível acima";
	if (strcmp(chave, "EscolhaArquivo.homeFolderToolTipText")==0) return "Desktop";
	if (strcmp(chave, "EscolhaArquivo.homeFolderAccessibleName")==0) return "Desktop";
	if (strcmp(chave, "EscolhaArquivo.newFolderToolTipText")==0) return "Criar nova pasta";
	if (strcmp(chave, "EscolhaArquivo.newFolderAccessibleName")==0) return "Criar nova pasta";
	if (strcmp(chave, "EscolhaArquivo.listViewButtonToolTipText")==0) return "Lista";
	if (strcmp(chave, "EscolhaArquivo.listViewButtonAccessibleName")==0) return "Lista";
	if (strcmp(chave, "EscolhaArquivo.detailsViewButtonToolTipText")==0) return "Detalhes";
	if (strcmp(chave, "EscolhaArquivo.detailsViewButtonAccessibleName")==0) return "Detalhes";
	if (strcmp(chave, "EscolhaArquivo.fileNameLabelMnemonic")==0) return "N";
	if (strcmp(chave, "EscolhaArquivo.fileNameLabelText")==0) return "Nome do arquivo";
	if (strcmp(chave, "EscolhaArquivo.filesOfTypeLabelMnemonic")==0) return "A";
	if (strcmp(chave, "EscolhaArquivo.filesOfTypeLabelText")==0) return "Arquivos do tipo";
	if (strcmp(chave, "EscolhaArquivo.fileNameHeaderText")==0) return "Nome";
	if (strcmp(chave, "EscolhaArquivo.fileSizeHeaderText")==0) return "Tamanho";
	if (strcmp(chave, "EscolhaArquivo.fileTypeHeaderText")==0) return "Tipo";
	if (strcmp(chave, "EscolhaArquivo.fileDateHeaderText")==0) return "Data";
	if (strcmp(chave, "EscolhaArquivo.fileAttrHeaderText")==0) return "Atributos";
	if (strcmp(chave, "EscolhaArquivo.cancelButtonText")==0) return "Cancelar";
	if (strcmp(chave, "EscolhaArquivo.cancelButtonMnemonic")==0) return "C";
	if (strcmp(chave, "EscolhaArquivo.cancelButtonToolTipText")==0) return "Cancelar";
	if (strcmp(chave, "EscolhaArquivo.openButtonText")==0) return "Abrir";
	if (strcmp(chave, "EscolhaArquivo.openButtonMnemonic")==0) return "A";
	if (strcmp(chave, "EscolhaArquivo.openButtonToolTipText")==0) return "Abrir";
	if (strcmp(chave, "EscolhaArquivo.saveButtonText")==0) return "Salvar";
	if (strcmp(chave, "EscolhaArquivo.saveButtonMnemonic")==0) return "S";
	if (strcmp(chave, "EscolhaArquivo.saveButtonToolTipText")==0) return "Salvar";
	if (strcmp(chave, "EscolhaArquivo.updateButtonText")==0) return "Alterar";
	if (strcmp(chave, "EscolhaArquivo.updateButtonMnemonic")==0) return "A";
	if (strcmp(chave, "EscolhaArquivo.updateButtonToolTipText")==0) return "Alterar";
	if (strcmp(chave, "EscolhaArquivo.helpButtonText")==0) return "Ajuda";
	if (strcmp(chave, "EscolhaArquivo.helpButtonMnemonic")==0) return "A";
	if (strcmp(chave, "EscolhaArquivo.helpButtonToolTipText")==0) return "Ajuda";
	if (strcmp(chave, "EscolhaArquivo.acceptAllFileFilterText")==0) return "Todos os arquivos (*.*)";
	if (strcmp(chave, "EscolhaArquivo.filtroTXT")==0) return "Arquivo TXT (*.txt)";
	if (strcmp(chave, "EscolhaArquivo.filtroCSV")==0) return "Arquivo CSV (*.csv)";
	if (strcmp(chave, "EscolhaArquivo.filtroHTML")==0) return "Arquivo HTML (*.html)";
	if (strcmp(chave, "EscolhaArquivo.filtroXML")==0) return "Arquivo XML (*.xml)";
	if (strcmp(chave, "EscolhaArquivo.filtroSQL")==0) return "Arquivo SQL (*.sql)";
	if (strcmp(chave, "EscolhaArquivo.filtroBMP")==0) return "Arquivo BMP (*.bmp)";
	if (strcmp(chave, "EscolhaArquivo.filtroICO")==0) return "Arquivo ICO (*.ico)";
	if (strcmp(chave, "EscolhaArquivo.filtroGIF")==0) return "Arquivo GIF (*.gif)";
	if (strcmp(chave, "EscolhaArquivo.filtroPNG")==0) return "Arquivo JPEG (*.png)";
	if (strcmp(chave, "EscolhaArquivo.filtroJPG")==0) return "Arquivo PNG (*.jpg)";
	if (strcmp(chave, "EscolhaArquivo.filtroTIF")==0) return "Arquivo TIFF (*.tif)";
	if (strcmp(chave, "EscolhaArquivo.todosDiretorios")==0) return "Todos os diretórios";

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
		do {
            ep = readdir(dp);

			nome = ep->d_name;
			//ep->d_namlen
			//ep->d_reclen
			//if (ep->d_type == DT_DIR) {}
			if (nome != ponto && nome != pponto) {
				nome = dir + nome;
				lista.push_back(nome);
			}
		} while (ep != NULL);

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

	if (access(sNomeArquivo.c_str(), 0) == 0) {
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
	unsigned int ntamlista = lista.size();

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
	//errno_t erro;

	//erro = fopen_s(&fp, sNomeArquivo.c_str(), "wb");
	fp =fopen(sNomeArquivo.c_str(), "wb");

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

long Rotinas::BlobLoadFromFile(const std::string &sNomeArquivo, void** blob) {
	long ret = 0;
	FILE* fp;
#ifndef __GNUC__
    errno_t erro;
	size_t tamanho = 16 * 1024;
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

		size_t ntamanho = fread(*blob, sizeof(char), 16 * 1024, fp);
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

ImagemBuffer Rotinas::BlobToPixbuf(const void* blob, int tamanho) {
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
int Rotinas::PixbufToBlob(ImagemBuffer pixbuf, void** blob, const std::string &formato) {

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
	long ntamanho = BlobLoadFromFile(sImgArq, &blob);

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
		//OutputDebugString(CharToWChar("BlobToPixbuf OK\n"));

		blob = NULL;
		int ntamanho2 = PixbufToBlob(pixbuf, &blob, EXTENSAO_BMP);
		if (ntamanho2 > 0 && blob != NULL) {
			//OutputDebugString(CharToWChar("PixbufToBlob OK\n"));
			std::cout << "PixbufToBlob OK" << std::endl;
		}

		if (PixbufToArquivo(pixbuf, "cdprata.bmp", EXTENSAO_BMP)) {
			//OutputDebugString(CharToWChar("PixbufToArquivo OK\n"));
			std::cout << "PixbufToArquivo OK" << std::endl;
		}
	}

	pixbuf = imagemToPixbuf("diretorio.bmp");
	if (pixbuf.buffer != NULL) {
		//OutputDebugString(CharToWChar("imagemToPixbuf OK\n"));
		std::cout << "imagemToPixbuf OK" << std::endl;

		if (PixbufToArquivo(pixbuf, "cdprata.gif", EXTENSAO_GIF)) {
			//OutputDebugString(CharToWChar("PixbufToArquivo OK\n"));
			std::cout << "PixbufToArquivo OK" << std::endl;
		}
	}

	pixbuf = ArquivoToPixbuf(sImgArq);
	if (pixbuf.buffer != NULL) {
		//OutputDebugString(CharToWChar("ArquivoToPixbuf OK\n"));
		std::cout << "ArquivoToPixbuf OK" << std::endl;

		if (PixbufToArquivo(pixbuf, "cdprata.jpg", EXTENSAO_JPEG)) {
			//OutputDebugString(CharToWChar("PixbufToArquivo OK\n"));
			std::cout << "PixbufToArquivo OK" << std::endl;
		}
	}


	std::vector<std::string> listaDir = cListarArquivosDiretorios("/home/hfs");
	//std::vector<std::string> listaDir = listarArquivosDiretorios("c:\\VM");

	unsigned int tamlistaDir = listaDir.size();
	std::string linhaDir = "";
	for (unsigned int i = 0; i < tamlistaDir; i++)
	{
		linhaDir = listaDir.at(i);

		Arquivo arq = FileInfoToArquivo(linhaDir);

		std::snprintf(saida, TAM_MAX_STR, "cListarArquivosDiretorios[%d]: %s, %s\n", i, linhaDir.c_str(), arq.getNome().c_str());
		//OutputDebugString(CharToWChar(saida));
		std::cout << saida << std::endl;
	}



	std::snprintf(saida, TAM_MAX_STR, "sDir: [%s]\n", sDir.c_str()); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "AppPath: %s\n", sApp.c_str()); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "FileExists: %s\n", (FileExists(sApp) ? "true" : "false")); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "DirectoryExists: %s\n", (DirectoryExists(sAppDir) ? "true" : "false")); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "ExtractFilePath: %s\n", ExtractFilePath(sApp).c_str()); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "ExtractFileName: %s\n", ExtractFileName(sApp).c_str()); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));

	std::snprintf(saida, TAM_MAX_STR, "Length(): %llu\n", sDir.length()); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "Trim(): [%s]\n", Trim(sDir).c_str()); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "tamanho Trim(): %llu\n", Trim(sDir).length()); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "LowerCase(): %s\n", LowerCase(sDir).c_str()); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "UpperCase(): %s\n", UpperCase(sDir).c_str()); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "Pos('.'): %d\n", Pos(".", sDir)); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "LastDelimiter('.'): %d\n", LastDelimiter(".", sDir)); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "QuotedStr(): %s\n", QuotedStr(sDir).c_str()); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "IntToStr(245789): %s\n", IntToStr(245789).c_str()); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "StrToInt() --> 245789: %d\n", StrToInt("245789")); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "StrToLong() --> 4200155136: %llu\n", StrToULongLong("4200155136")); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "DoubleToStr(15.557878): %s\n", DoubleToStr(15.557878).c_str()); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));

	std::snprintf(saida, TAM_MAX_STR, "SubString(): %s\n", SubString(sDir, 8, 6).c_str()); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "ReplaceAll(): [%s]\n", ReplaceAll(sDir, "\\", "@").c_str()); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "trocaSeparador(): [%s]\n", trocaSeparador(sDir).c_str()); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "testaNull(NULL): %s\n", testaNull(NULL).c_str()); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));

	std::snprintf(saida, TAM_MAX_STR, "StartsStr(DVD, JOGOS2_DVDS/TESTE): %s\n", (StartsStr("DVD", "JOGOS2_DVDS/TESTE") ? "true" : "false")); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "StartsStr(DVD, DVDSJOGOS2_/TESTE): %s\n", (StartsStr("DVD", "DVDSJOGOS2_/TESTE") ? "true" : "false")); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));

	std::snprintf(saida, TAM_MAX_STR, "ContainsStr(JOGOS2_DVDS/TESTE): %s\n", (ContainsStr("DVDSJOGOS2_/TESTE", "DVDSJOGOS2_/TESTE") ? "true" : "false")); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "EndsStr(TESTE, JOGOS2_DVDS/TESTE): %s\n", (EndsStr("TESTE", "DVDSJOGOS2_/TESTE") ? "true" : "false")); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));

	DateTime dt1 = DateTime::Now();
	std::snprintf(saida, TAM_MAX_STR, "formataDate(): %s\n", dt1.FormatDateTime(FORMATO_DATAHORA).c_str()); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));
	DateTime dt2 = DateTime::StrToDateTime("03/02/2017 15:23:32");
	std::snprintf(saida, TAM_MAX_STR, "StringToDate(03/02/2017 15:23:32): %s\n", dt2.FormatDateTime(FORMATO_DATAHORA).c_str()); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));

	std::snprintf(saida, TAM_MAX_STR, "FormatLong(4200155136): %s\n", ULongToStr(4200155136).c_str()); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "FormatDouble(15.544878): %s\n", DoubleToStr(15.544878).c_str()); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "FormatDouble(15.547878): %s\n", DoubleToStr(15.547878).c_str()); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "FormatDouble(15.557878): %s\n", DoubleToStr(15.557878).c_str()); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "FormatDouble(15.567878): %s\n", DoubleToStr(15.567878).c_str()); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));

	std::snprintf(saida, TAM_MAX_STR, "MontaTamanho() --> 3.91 GB: %s\n", MontaTamanho(4200155136).c_str()); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "MontaTamanho() --> 3.50 GB: %s\n", MontaTamanho(3757244416).c_str()); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "MontaTamanho() --> 2.29 GB: %s\n", MontaTamanho(2455207936).c_str()); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "MontaTamanho() --> 888.18 PB: %s\n", MontaTamanhoBig(999999999999999999.9999).c_str()); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));

	std::vector<std::string> lista;
	std::string linha = "";

	lista = SListSeparador(sDir, '\\');

	unsigned int tamlista = lista.size();

	for (unsigned int i = 0; i < tamlista; i++)
	{
		linha = lista.at(i);
		std::snprintf(saida, TAM_MAX_STR, "SListSeparador[%d]: %s\n", i, linha.c_str()); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));
	}

	std::string arquivo = ExtractFilePath(sApp);
	arquivo += "exemplo.txt";

	std::snprintf(saida, TAM_MAX_STR, "arquivo: %s\n", arquivo.c_str()); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));

	if (SListSaveToFile(lista, arquivo)) {

		if (FileExists(arquivo)) {

			lista = SListLoadFromFile(arquivo);
			tamlista = lista.size();

			for (unsigned int i = 0; i < tamlista; i++) {
				linha = lista.at(i);
				std::snprintf(saida, TAM_MAX_STR, "SListLoadFromFile[%d]: %s\n", i, linha.c_str()); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));
			}

			if (DeleteFromFile(arquivo)) {
				if (!FileExists(arquivo)) {
					std::snprintf(saida, TAM_MAX_STR, "DeleteFromFile: OK\n"); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));
				}
			}
			else {
				std::snprintf(saida, TAM_MAX_STR, "DeleteFromFile: FALHOU\n"); std::cout << saida << std::endl; //OutputDebugString(CharToWChar(saida));
			}

		}

	}

}



}
}
