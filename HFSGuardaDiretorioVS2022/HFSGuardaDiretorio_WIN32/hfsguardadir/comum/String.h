#ifndef STRING_H
#define STRING_H

#define TAM_MAX_STR 512

struct SString {
	CHAR str[TAM_MAX_STR];
	WCHAR wstr[TAM_MAX_STR];
	unsigned int length;
};
typedef struct SString String;

String String_concatenar(String lstring, const char* string);
String String_concatenar(String lstring, String string1, const char* string);
String String_concatenar(const char* string, String lstring);
String String_concatenar(String lstring, String string);
String String_concatenar(String lstring, String string1, String string2);
String String_concatenar(String lstring, const char caracter);
String String_concatenar(String string, unsigned int qtd, ...);
String String_copiar(String string);
String String_copiar(const char* string);
String String_copiar(LPCWSTR string);
String String_copiar(const char caracter);
BOOL String_comparar(String string1, String string2);
BOOL String_comparar(String string1, const char* string2);
BOOL String_comparar(String string1, LPCWSTR string2);
String String_limpar();
String String_iniciar(const char caracter);
String String_iniciar(const char* string);
String String_iniciar(String string);
String String_iniciar(LPCWSTR string);
void String_finalizar(String *lstring);

String String_Trim(String lstring);
String String_LowerCase(String lstring);
String String_UpperCase(String lstring);
String String_QuotedStr(String lstring);
String String_QuotedStr(const char caracter);
String String_SubString(String texto, int inicio, int tamanho);
String String_ReplaceAll(String texto,
	const char* velho, const char* novo);
String String_FromInt(int valor);
String String_FromULong(unsigned long valor);
String String_FromLongLong(long long valor);
String String_FromDouble(double valor);
String String_FromLongDouble(long double valor);
int String_ToInt(String texto);
long String_ToLong(String texto);
long long String_ToLongLong(String texto);
double String_ToDouble(String texto);
long double String_ToLongDouble(String texto);

// ---------------------------------------------------------------------------
char* String_cNewStr(unsigned int tamanho);
void String_cFreeStr(char* texto);
char* String_cWCharToChar(const wchar_t* origem);
int String_cLastIndexOf(const char* texto, const char alvo);
char* String_cTrim(const char* texto);
char* String_cLowerCase(const char* texto);
char* String_cUpperCase(const char* texto);
int String_cPos(const char* subtexto, const char* texto);
int String_cFind(const char* subtexto, const char* texto, int posInicial);
BOOL String_cStartsStr(const char* sub, const char* texto);
BOOL String_cContainsStr(const char* texto, const char* subtexto);
BOOL String_cEndsStr(const char* texto, const char* subtexto);
int String_cLastDelimiter(const char* sub, const char* texto);
char* String_cStrndup(const char* texto, size_t tamanho);
char* String_cSubString(const char* texto, int inicio, int tamanho);
char* String_cQuotedStr(const char* texto);
char* String_cReplaceAll(const char* texto,
	const char* velho, const char* novo);
char* String_cFromInt(int valor);
char* String_cFromULong(const unsigned long valor);
char* String_cFromLongLong(const long long valor);
char* String_cFromDouble(const double valor);
char* String_cFromLongDouble(const long double valor);
int String_cToInt(const char* texto);
long String_cToLong(const char* texto);
long long String_cToLongLong(const char* texto);
double String_cToDouble(const char* texto);
long double String_cToLongDouble(const char* texto);
BOOL String_cSomenteNumero(const char* texto);
// ---------------------------------------------------------------------------
void String_testar();

#endif
