//---------------------------------------------------------------------------
#ifndef FuncoesH
#define FuncoesH
//---------------------------------------------------------------------------
#include <cwchar>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "stdio.h"
#include "string.h"
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include <sstream>
//---------------------------------------------------------------------------
//	FUNCOES C PURO
//---------------------------------------------------------------------------
static inline char* cNewStr(unsigned int tamanho)
{
	char *retorno;

	retorno = (char*)malloc(tamanho);
	retorno[0]='\0';

	return retorno;
}
//---------------------------------------------------------------------------
static inline char* cWCharToChar(const wchar_t* origem)
{
    char *destino = cNewStr(1);
    int tamanho = wcslen(origem);

    //tamanho = sizeof(origem)/sizeof(wchar_t);

    if (tamanho > 0)
    {
        destino = cNewStr(tamanho);
        wcstombs(destino, origem, tamanho);
        destino[tamanho]='\0';
        return destino;
    }
    return destino;
}
//---------------------------------------------------------------------------
static inline int cLastIndexOf(const char* texto, const char alvo)
{
	int retorno = -1;
	int tamanho = strlen(texto);

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
static inline char* cTrim(const char *texto)
{
    char *retorno;
    unsigned int j = 0;
    unsigned char compara;
    int tamanho = strlen(texto);

	if (tamanho > 0)
    {
        retorno = cNewStr(tamanho);
        for (unsigned int i = 0; texto[i] != '\0'; i++)
        {
            compara = (unsigned char) texto[i];
            if (!isspace(compara))
            {
                retorno[j] = texto[i];
                j++;
            }
        }
        retorno[j] = '\0';
    }
    return retorno;
}
//---------------------------------------------------------------------------
static inline char* cLowerCase(const char *texto)
{
    char *retorno;
    unsigned int j = 0;
    int tamanho = strlen(texto);

    if (tamanho > 0)
    {
        retorno = cNewStr(tamanho);
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
static inline char* cUpperCase(const char *texto)
{
    char *retorno;
    unsigned int j = 0;
    int tamanho = strlen(texto);

	if (tamanho > 0)
    {
        retorno = cNewStr(tamanho);
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
static inline int pos(const char *subtexto, const char *texto)
{
    const char *retorno = strstr(texto, subtexto);
    if (retorno == NULL)
        return -1;
    else
        return (retorno - texto) + 1;
}
//---------------------------------------------------------------------------
static inline int cLastDelimiter(const char *sub, const char *texto)
{
    const char *parte;
    int retorno = -1, tamparte;
    int tamanho = strlen(texto);
    char *textolocal;

    if (tamanho > 0)
    {
        retorno = 0;
        textolocal = cNewStr(tamanho);
        strcpy(textolocal, texto);
        parte = strtok(textolocal, sub);
        while (parte != NULL)
        {
            tamparte = strlen(parte)+1;
            retorno += tamparte;
            parte = strtok(NULL, sub);
        }
        retorno -= tamparte;
	}
    return retorno;
}
//---------------------------------------------------------------------------
static inline char* cstrndup(const char *texto, size_t tamanho)
{
    char *retorno;
    char *fim = (char *) memchr(texto, 0, tamanho);

    if (fim)
    {
        tamanho = fim - texto + 1;
    }

    retorno = cNewStr(tamanho);

    if (tamanho)
    {
        memcpy(retorno, texto, tamanho-1);
        retorno[tamanho-1] = '\0';
    }
    return retorno;
}
//---------------------------------------------------------------------------
static inline char* cSubString(const char *texto, int inicio, int tamanho)
{
    char *retorno;
    int tamtexto = strlen(texto);

    if (tamtexto > 0)
    {
        retorno = cstrndup(texto + inicio - 1, tamanho + 1);
    }
    return retorno;
}
//---------------------------------------------------------------------------
static inline char* cIntToStr(int valor)
{
    char *retorno;
    int tamanho = 30;

    retorno = cNewStr(tamanho);
	sprintf(retorno, "%d", valor);

    return retorno;
}
//---------------------------------------------------------------------------
static inline char* cQuotedStr(const char *texto)
{
    char *retorno;
    int tamanho = strlen(texto);

    retorno = cNewStr(tamanho+2);
    sprintf(retorno, "'%s'", texto);
    return retorno;
}
//---------------------------------------------------------------------------
static inline char* cStringReplaceAll(const char *texto,
                                     const char* velho, const char* novo)
{
    char *retorno, *parte, *textolocal;
    unsigned int j = 0;
    int tamanho = strlen(texto);
    int tamvelho = strlen(velho);
    int tamnovo = strlen(novo);
    int tamfinal = 0, tamparte = 0;

    if (tamanho > 0)
    {
        textolocal = cNewStr(tamanho);
        strcpy(textolocal, texto);
        parte = strstr(textolocal, velho);
        while (parte != NULL)
        {
            j++;
            strcpy(textolocal, parte+1);
            parte = strstr(textolocal, velho);
        }
        tamfinal = (tamanho-(j*tamvelho))+(j*tamnovo);
        retorno = cNewStr(tamfinal);

        strcpy(textolocal, texto);
        parte = strtok(textolocal, velho);
        while (parte != NULL)
		{
            tamparte = strlen(parte);
            strncat(retorno, parte, tamparte);
            parte = strtok(NULL, velho);

            if (parte!=NULL)
            {
                strncat(retorno, novo, tamnovo);
            }
        }
    }
    else
    {
        retorno = cNewStr(tamanho);
        strcpy(retorno, texto);
    }
    return retorno;
}
//---------------------------------------------------------------------------
//	FUNCOES C++
//---------------------------------------------------------------------------
static inline void* cppGetMemory(unsigned int tamanho){
    return malloc(tamanho);
}
//---------------------------------------------------------------------------
static inline char* cppNewStr(unsigned int tamanho)
{
	char *retorno;

	retorno = new char[tamanho];
	retorno[0]='\0';

	return retorno;
}
//---------------------------------------------------------------------------
static inline char* cppWCharToChar(const wchar_t* origem)
{
	char *destino = cppNewStr(1);
	int tamanho = wcslen(origem);
	//int tamanho = sizeof(origem)/sizeof(wchar_t);

	if (tamanho > 0)
	{
		destino = cppNewStr(tamanho);
		wcstombs(destino, origem, tamanho);
		destino[tamanho]='\0';
		return destino;
	}
	return destino;
}
//---------------------------------------------------------------------------
static inline std::string cppWStringToString(const std::wstring origem)
{
	std::string destino;
	destino.assign(origem.begin(), origem.end());
	return destino;
}
//---------------------------------------------------------------------------
static inline String cppWideStringToString(const WideString origem){
  wchar_t* wchr_origem = origem.c_bstr();
  std::string temp = cppWStringToString(wchr_origem);

  char* chr_destino;
  int tamanho = temp.length();
  chr_destino = cppNewStr(tamanho);

  strcpy(chr_destino, temp.c_str());

  String destino = chr_destino;

  return destino;
}
//---------------------------------------------------------------------------
static inline std::string cppTrimLeft(const std::string texto)
{
	std::string stexto = texto;

	stexto.erase(stexto.begin(), std::find_if(stexto.begin(), stexto.end(),
                            std::not1(std::ptr_fun<int, int>(std::isspace))));
    return stexto;
}
//---------------------------------------------------------------------------
static inline std::string cppTrimRight(const std::string texto)
{
	std::string stexto = texto;

	stexto.erase(std::find_if(stexto.rbegin(), stexto.rend(),
	 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), stexto.end());

	return texto;
}
//---------------------------------------------------------------------------
static inline std::string cppTrim(const std::string texto)
{
	return cppTrimLeft(cppTrimRight(texto));
}
//---------------------------------------------------------------------------
static inline std::string cppLowerCase(const std::string texto)
{
	std::string stexto = texto;

	std::transform(stexto.begin(), stexto.end(), stexto.begin(), ::tolower);
	return stexto;
}
//---------------------------------------------------------------------------
static inline std::string cppUpperCase(const std::string texto)
{
	std::string stexto = texto;

	std::transform(stexto.begin(), stexto.end(), stexto.begin(), ::toupper);
	return stexto;
}
//---------------------------------------------------------------------------
static inline int cppPos(const std::string sub, const std::string texto)
{
	std::string::size_type loc = texto.find( sub, 0 );
	if( loc != std::string::npos )
		return (loc+1);
	else
		return -1;
}
//---------------------------------------------------------------------------
static inline int cppLastDelimiter(const std::string sub,
	const std::string texto)
{
	std::string::size_type loc = texto.find_last_of( sub );
	if( loc != std::string::npos )
		return (loc+1);
	else
		return -1;
}
//---------------------------------------------------------------------------
static inline std::string cppSubString(const std::string texto,
	int inicio, int tamanho)
{
	return texto.substr(inicio-1, tamanho);
}
//---------------------------------------------------------------------------
static inline std::string cppIntToStr(int valor)
{
	std::stringstream ss;
	ss << valor;
	return ss.str();
}
//---------------------------------------------------------------------------
static inline std::string cppInt64ToStr(__int64 valor)
{
	std::stringstream ss;
	ss << valor;
	return ss.str();
}
//---------------------------------------------------------------------------
static inline int cppStrToInt(const std::string texto)
{
	return atoi(texto.c_str());
}
//---------------------------------------------------------------------------
/*
std::istringstream &operator >>(std::istringstream &iss, __int64 &n)
{
	sscanf(iss.str().c_str(), "%I64d", &n);
	return iss;
}
*/
template <typename T> bool stringToInt64(T &t, const std::string &s,
	std::ios_base & (*f)(std::ios_base&))
{
	std::istringstream iss(s);
	iss >> f, iss >> t;
	return !iss.fail();
}

static inline __int64 cppStrToInt64(const std::string texto)
{
	__int64 retorno;
	bool bConverteu = stringToInt64<__int64>(retorno, texto, std::dec);
	if (bConverteu) {
		return retorno;
	} else
		return -1;
}
//---------------------------------------------------------------------------
static inline std::string cppQuotedStr(const std::string texto)
{
	std::stringstream ss;
	ss << "'" << texto << "'";
	return ss.str();
}
//---------------------------------------------------------------------------
static inline std::string cppStringReplaceAll(const std::string texto,
        const std::string velho, const std::string novo)
{
	std::string stexto = texto;
    size_t pos = 0;
	while ((pos = stexto.find(velho, pos)) != std::string::npos)
	{
		stexto.replace(pos, velho.length(), novo);
		pos += novo.length();
	}
	return stexto;
}
//---------------------------------------------------------------------------
/*
std::wstring TSQLiteDatabase::str_to_wstr(const std::string& str)
{
	std::wostringstream wstm;
	const std::ctype<wchar_t>& ctfacet =
						std::use_facet< std::ctype<wchar_t> >( wstm.getloc() ) ;
	for( size_t i=0 ; i < str.size() ; ++i )
			  wstm << ctfacet.widen( str[i] ) ;
	return wstm.str() ;
}
// ---------------------------------------------------------------------------
std::string TSQLiteDatabase::wstr_to_str(const std::wstring& str)
{
	std::ostringstream stm ;
	const std::ctype<char>& ctfacet =
						 std::use_facet< std::ctype<char> >( stm.getloc() ) ;
	for( size_t i=0 ; i < str.size() ; ++i )
				  stm << ctfacet.narrow( str[i], 0 ) ;
	return stm.str() ;
}
*/
// ---------------------------------------------------------------------------
#endif
