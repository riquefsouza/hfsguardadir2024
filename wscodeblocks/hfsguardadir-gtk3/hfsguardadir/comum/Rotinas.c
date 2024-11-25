#include "Rotinas.h"
#include "../../FrmPrincipal.h"

#include "dirent.h"
// ---------------------------------------------------------------------------
sqlite3* dbConexao;
Argumento argumentos;
// ---------------------------------------------------------------------------
gchar* Rotinas_retLocale(const gchar *sTexto) {
GString *sTemp = g_string_new("");
gsize nBytesLidos, nBytesGravados;
GError *nErroOcorrido = NULL;

g_string_assign(sTemp, g_locale_from_utf8(sTexto, (TAM_MAX_STR * 4),
        &nBytesLidos, &nBytesGravados, &nErroOcorrido));

if (sTemp->str==NULL)
  g_string_assign(sTemp, sTexto);

return sTemp->str;
}
// ---------------------------------------------------------------------------
#ifdef __GNUC__
gchar* Rotinas_retUTF8(const gchar *sTexto) {
    GString* sTemp = g_string_new("");

    if (sTexto != NULL){
        g_string_assign(sTemp, sTexto);
    }

    return sTemp->str;
}
#else
gchar* Rotinas_retUTF8(const gchar *sTexto) {
	GString* sTemp = g_string_new("");

	if (sTexto != NULL) {
		gsize nBytesLidos, nBytesGravados;
		GError* nErroOcorrido = NULL;
		gssize tamanho = strlen(sTexto);

		g_string_assign(sTemp, g_locale_to_utf8(sTexto, tamanho,
			&nBytesLidos, &nBytesGravados, &nErroOcorrido));

		//g_print("nBytesLidos = %d\n", nBytesLidos);
		//g_print("nBytesGravados = %d\n", nBytesGravados);

		if (nErroOcorrido != NULL) {
			switch (nErroOcorrido->code) {
			case G_CONVERT_ERROR_NO_CONVERSION:
				g_print("nErroOcorrido = G_CONVERT_ERROR_NO_CONVERSION\n");
				break;
			case G_CONVERT_ERROR_ILLEGAL_SEQUENCE:
				g_print("nErroOcorrido = G_CONVERT_ERROR_ILLEGAL_SEQUENCE\n");
				break;
			case G_CONVERT_ERROR_FAILED:
				g_print("nErroOcorrido = G_CONVERT_ERROR_FAILED\n");
				break;
			case G_CONVERT_ERROR_PARTIAL_INPUT:
				g_print("nErroOcorrido = G_CONVERT_ERROR_PARTIAL_INPUT\n");
				break;
			case G_CONVERT_ERROR_BAD_URI:
				g_print("nErroOcorrido = G_CONVERT_ERROR_BAD_URI\n");
				break;
			case G_CONVERT_ERROR_NOT_ABSOLUTE_PATH:
				g_print("nErroOcorrido = G_CONVERT_ERROR_NOT_ABSOLUTE_PATH\n");
				break;
			default:
				g_print("nErroOcorrido = %d\n", nErroOcorrido->code);
			}
		}

		if (sTemp->str == NULL)
			g_string_assign(sTemp, sTexto);
	}
	return sTemp->str;
}
#endif // __GNUC__

double Rotinas_calculaProgresso(int nMaximo, int nProgresso) {
	nMaximo += 1;
	nProgresso += 1;

	double valor = (double)nProgresso / (double)nMaximo;

	if (valor >= 0 && valor <= 1) {
		return valor;
	}
	else {
		return 0;
	}
}

GdkPixbuf* Rotinas_XPMToPixbuf(const char** xpm)
{
	GdkPixbuf* pxb = gdk_pixbuf_new_from_xpm_data(xpm);
	return pxb;
}

GdkPixbuf* Rotinas_imagemToPixbuf(const char* sNomeImagem) {
	GdkPixbuf *pixbuf = NULL;

	GString* caminho = Rotinas_AppDirPath();
	caminho = g_string_append(caminho, "imagens/");
	caminho = g_string_append(caminho, sNomeImagem);

	GError *erro = NULL;
	pixbuf = gdk_pixbuf_new_from_file(caminho->str, &erro);
	g_error_free(erro);

	return pixbuf;
}

GdkPixbuf* Rotinas_ArquivoToPixbuf(const char* sArquivo) {
	GdkPixbuf *pixbuf = NULL;
	GError *erro = NULL;

	pixbuf = gdk_pixbuf_new_from_file(sArquivo, &erro);
	g_error_free(erro);

	return pixbuf;
}

//formatos = "jpeg", "tiff", "png", "ico" or "bmp"
gboolean Rotinas_PixbufToArquivo(GdkPixbuf* pixbuf, const char* sArquivo, const char* formato) {
	GError *erro = NULL;
	gboolean bSalvou;

	bSalvou = gdk_pixbuf_save(pixbuf, sArquivo, formato, &erro, NULL);
		//"jpeg", &erro, "quality", "100", NULL)) {

	if (bSalvou) {

		g_error_free(erro);
	}

	return bSalvou;
}

GdkPixbuf* Rotinas_BlobToPixbuf(const void* blob, gssize tamanho) {
	GdkPixbuf *pixbuf;
	GMemoryInputStream* mgis;
	GDestroyNotify destroy = NULL;
	GCancellable *cancelavel = NULL;
	GError *erro = NULL;

	mgis = G_MEMORY_INPUT_STREAM(g_memory_input_stream_new());
	g_memory_input_stream_add_data(mgis, blob, tamanho, destroy);

	pixbuf = gdk_pixbuf_new_from_stream(G_INPUT_STREAM(mgis), cancelavel, &erro);

	g_input_stream_close(G_INPUT_STREAM(mgis), cancelavel, &erro);

	return pixbuf;
}

//formatos = "jpeg", "tiff", "png", "ico" or "bmp"
gsize Rotinas_PixbufToBlob(GdkPixbuf* pixbuf, void** blob, const char* formato) {
	//GCancellable *cancelavel = NULL;
	GError *erro = NULL;
	//GOutputStream *gos = NULL;
	//GMemoryOutputStream *gmos = NULL;
	gboolean bSalvou;
	gsize ntamanho = 0;

	bSalvou = gdk_pixbuf_save_to_buffer(pixbuf, (gchar**)blob, &ntamanho, formato, &erro, NULL);
	//"jpeg", &erro, "quality", "100", NULL)) {

	if (bSalvou) {
		return ntamanho;
	}
	return 0;
}

GdkPixbuf* Rotinas_extrairPixbufArquivo(const GString* sCaminho, int tamanho) {
	GIcon* icone;
	GFile* garquivo;
	GFileInfo* info;
	GCancellable *cancelavel = NULL;
	GError *erro = NULL;
	GtkImage *imagem = NULL;
	GdkPixbuf *pixbuf = NULL; //GdkPixbuf *pixbuf2 = NULL;

	garquivo = g_file_new_for_path(sCaminho->str);
	if (garquivo != NULL) {
		info = g_file_query_info(garquivo, "*",
			G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS, cancelavel, &erro);
		icone = g_file_info_get_icon(info);
		imagem = GTK_IMAGE(gtk_image_new_from_gicon(icone, GTK_ICON_SIZE_BUTTON));
		//pixbuf = gdk_pixbuf_copy(imagem->data.pixbuf.pixbuf);
		pixbuf = gtk_image_get_pixbuf(imagem);
		//pixbuf2 = gdk_pixbuf_scale_simple(pixbuf, tamanho, tamanho, GDK_INTERP_BILINEAR);
		//pixbuf2 = gdk_pixbuf_copy(pixbuf);

		g_object_unref(info);
		g_object_unref(garquivo);
	}

	return pixbuf;
}


sqlite3* Rotinas_getConexao() {
	return dbConexao;
}

gboolean Rotinas_BancoConectar(GString *sFonteDeDados)
{
	const int ret = sqlite3_open_v2(sFonteDeDados->str, &dbConexao, SQLITE_OPEN_READWRITE, NULL);
	if (SQLITE_OK != ret)
	{
		Rotinas_BancoMostrarErro("Rotinas_BancoConectar");
		sqlite3_close(dbConexao);
		return FALSE;
	}
	return TRUE;
}

void Rotinas_BancoDesconectar()
{
	const int ret = sqlite3_close(dbConexao);
	(void)ret;
}

void Rotinas_BancoMostrarErro(const char* titulo) {
	int errcode = sqlite3_errcode(dbConexao);
	//int exterrcode = sqlite3_extended_errcode(dbConexao);
	char* errmsg = (char*)sqlite3_errmsg(dbConexao);
	//const char* errstr = sqlite3_errstr(dbConexao);
	GString *sErro = g_string_new(titulo);
	//wsprintf(sErro, _T("ERRO: %d - %s"), errcode, errmsg);
	g_string_printf(sErro, "ERRO: %d - %s", errcode, errmsg);
	//OutputDebugString((LPCWSTR)sErro->str);
	//MessageBox(NULL, sErro->str, _T("Banco Mostrar Erro"), MB_ICONERROR | MB_OK);
}

int Rotinas_BancoExec(GString *sSQL)
{
	const int ret = sqlite3_exec(dbConexao, sSQL->str, NULL, NULL, NULL);
	if (SQLITE_OK != ret)
	{
		Rotinas_BancoMostrarErro("Rotinas_BancoExec");
	}
	return sqlite3_changes(dbConexao);
}

gboolean Rotinas_BancoPasso(sqlite3_stmt* pstmt) {
	gboolean mbOk = FALSE;

	const int ret = sqlite3_step(pstmt);

	if (SQLITE_ROW == ret) {
		mbOk = TRUE;
	}
	else if (SQLITE_DONE == ret) {
		mbOk = FALSE;
	}
	else {
		Rotinas_BancoMostrarErro("Rotinas_BancoPasso");
		mbOk = FALSE;
	}

	return mbOk;
}

int Rotinas_BancoExecPasso(sqlite3_stmt* pstmt, int ret, const char* titulo) {
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

void Rotinas_argumentos(int argc, char *argv[]) {
	argumentos.quantidade = argc;
	//for (int i = 0; i < argc; i++)
	//{
		argumentos.texto = g_string_new(argv[0]);
	//}
}

GString* Rotinas_AppDirPath() {
//	GString* dir = g_string_new(g_get_current_dir());
//	GString* nome = g_string_new(g_get_prgname());
//	GString* app = g_string_new(g_get_application_name());
	GString* path = argumentos.texto;
	path = Rotinas_ExtractFilePath(path);
	path = g_string_append(path, Rotinas_BARRA_INVERTIDA);

	return path;
}

GString* Rotinas_concatenar(const char* string1, const char* string2) {
	GString* txt = g_string_new(string1);
	txt = g_string_append(txt, string2);
	return txt;
}

GString* Rotinas_concatenar1(const GString* string1, const char* string2, const char* string3) {
	GString* txt = g_string_new(string1->str);
	txt = g_string_append(txt, string2);
	txt = g_string_append(txt, string3);
	return txt;
}

GString* Rotinas_concatenar2(const GString* string1, const GString* string2, const char* string3) {
	GString* txt = g_string_new(string1->str);
	txt = g_string_append(txt, string2->str);
	txt = g_string_append(txt, string3);
	return txt;
}

GString* Rotinas_concatenar3(const GString* string1, const GString* string2, const char* string3, const char* string4) {
	GString* txt = g_string_new(string1->str);
	txt = g_string_append(txt, string2->str);
	txt = g_string_append(txt, string3);
	txt = g_string_append(txt, string4);
	return txt;
}

GString* Rotinas_concatenar4(const GString* string1, const GString* string2, const char* string3, const char* string4,
	const char* string5, const char* string6) {
	GString* txt = g_string_new(string1->str);
	txt = g_string_append(txt, string2->str);
	txt = g_string_append(txt, string3);
	txt = g_string_append(txt, string4);
	txt = g_string_append(txt, string5);
	txt = g_string_append(txt, string6);
	return txt;
}

gboolean Rotinas_comparar(const GString* string1, const char* string2) {
	return g_string_equal(string1, g_string_new(string2));
}

GString* Rotinas_LowerCase(const GString *texto) {
	GString *txt = g_string_new(texto->str);
	return g_string_ascii_down(txt);
}

GString* Rotinas_UpperCase(const GString *texto) {
	GString *txt = g_string_new(texto->str);
	return g_string_ascii_up(txt);
}

GString* Rotinas_Trim(const GString *texto)
{
	GString *retorno = g_string_new("");
	gsize j = 0, inicio = 0, fim = 0;
	unsigned char compara;
	int tamanho = (int)texto->len;

	if (tamanho > 0)
	{
		retorno = g_string_sized_new(tamanho);

		for (gsize i = 0; texto->str[i] != '\0'; i++) {
			compara = (unsigned char)texto->str[i];
			if (!isspace(compara)) {
				inicio = i;
				fim = texto->len;
				break;
			}
		}

		for (gsize i = (texto->len - 1); i >= 0; i--) {
			compara = (unsigned char)texto->str[i];
			if (isspace(compara)) {
				fim = i;
			}
			else {
				break;
			}
		}

		for (gsize i = inicio; i < fim; i++) {
			retorno->str[j] = texto->str[i];
			j++;
		}
		retorno->str[j] = '\0';
		retorno->len = j;
		retorno->allocated_len = j;
	}
	return retorno;
}

int Rotinas_Pos(const GString* subtexto, const GString* texto) {
	return Rotinas_cPos(subtexto->str, texto->str);
}

gboolean Rotinas_StartsStr(const GString* sub, const GString* texto) {
	return g_str_has_prefix(texto->str, sub->str);
}

gboolean Rotinas_ContainsStr(const GString* texto, const GString* subtexto){
	//return g_strv_contains(texto->str, subtexto->str);
	return (Rotinas_Pos(subtexto, texto) > 0);
}

gboolean Rotinas_EndsStr(const GString* texto, const GString* subtexto) {
	return g_str_has_suffix(subtexto->str, texto->str);
}

int Rotinas_LastDelimiter(const GString* sub, const GString* texto) {
	return Rotinas_cLastDelimiter(sub->str, texto->str);
}

GString* Rotinas_SubString(const GString* texto, gsize inicio, gsize tamanho) {
	GString* retorno = g_string_new("");
	gchar* temp;
	size_t tamtexto = strlen(texto->str);

	if (tamtexto > 0)
	{
		temp = g_strndup(texto->str + inicio - 1, tamanho);
		retorno = g_string_new(temp);
	}
	return retorno;
}

GString* Rotinas_IntToStr(int valor) {
	GString *retorno = g_string_sized_new(40);
	g_string_printf(retorno, "%d", valor);
	return retorno;
}

int Rotinas_StrToInt(const GString* texto) {
	gchar* temp;
	gint64	valor = g_ascii_strtoll(texto->str, &temp, 10);
	return (int)valor;
}

GString* Rotinas_QuotedStr(const GString* texto) {
	GString *retorno = g_string_new("");
	g_string_printf(retorno, "'%s'", texto->str);
	return retorno;
}

GString* Rotinas_QuotedChar(const char caracter) {
	GString *retorno = g_string_new("");
	g_string_printf(retorno, "'%c'", caracter);
	return retorno;
}

GString* Rotinas_ReplaceAll(const GString* texto,
	const GString* velho, const GString* novo) {

	gchar* temp = Rotinas_cReplaceAll(texto->str, velho->str, novo->str);

	return g_string_new(temp);
}

GString* Rotinas_formataDate(const gchar* formato, const GDateTime* dt) {
	gchar* temp;
	GString* ds;

	temp = g_date_time_format((GDateTime*)dt, formato);
	ds = g_string_new(temp);

	return ds;
}

GDateTime* Rotinas_StringToDate(const GString* sData) {

	GDateTime* data = NULL;
	gint ano = 0, mes = 0, dia = 0, hora = 0, minuto = 0;
	gdouble segundos = 0;
	GString* sdh = Rotinas_Trim(sData);
	gchar* temp;
	size_t tamtexto = strlen(sdh->str);

	if (tamtexto > 0) {

		if (tamtexto >= 10) {
			temp = g_strndup(sdh->str, 2);
			dia = Rotinas_cStrToInt(temp);

			temp = g_strndup(sdh->str + 3, 2);
			mes = Rotinas_cStrToInt(temp);

			temp = g_strndup(sdh->str + 6, 4);
			ano = Rotinas_cStrToInt(temp);
		}

		if (tamtexto == 19) {
			temp = g_strndup(sdh->str + 11, 2);
			hora = Rotinas_cStrToInt(temp);

			temp = g_strndup(sdh->str + 14, 2);
			minuto = Rotinas_cStrToInt(temp);

			temp = g_strndup(sdh->str + 17, 2);
			segundos = Rotinas_cStrToDouble(temp);
		}

		data = g_date_time_new_local(
			ano, mes, dia, hora, minuto, segundos);
	}

	return data;
}

GDateTime* Rotinas_DataHoraNow() {
	GDateTime* data = g_date_time_new_now_local();
	return data;
}

GString* Rotinas_ULongToStr(const unsigned long valor) {
	GString *retorno = g_string_sized_new(40);
	g_string_printf(retorno, "%lu", valor);
	return retorno;
}

GString* Rotinas_LongLongToStr(const long long valor) {
	GString *retorno = g_string_sized_new(40);
	g_string_printf(retorno, "%lld", valor);
	return retorno;
}

GString* Rotinas_LongDoubleToStr(const long double valor) {
	GString *retorno = g_string_sized_new(40);
	g_string_printf(retorno, "%4.2Lf", valor);
	return retorno;
}

guint64 Rotinas_StrToLong(const GString* texto) {
	gchar* temp;
	guint64	valor = g_ascii_strtoull(texto->str, &temp, 10);
	return valor;
}

GString* Rotinas_DoubleToStr(const double valor)
{
	GString *retorno = g_string_sized_new(40);
	g_string_printf(retorno, "%4.2f", valor);
	return retorno;
}

gdouble Rotinas_StrToDouble(const GString* texto)
{
	gchar* temp;
	gdouble	valor = g_strtod(texto->str, &temp);
	return valor;
}

// ---------------------------------------------------------------------------

gchar* Rotinas_cNewStr(unsigned int tamanho)
{
	gchar *retorno = NULL;

	retorno = (gchar*)malloc(tamanho);
	if (retorno != NULL) {
		retorno[0] = '\0';
	}

	return retorno;
}

gchar* Rotinas_cWCharToChar(const wchar_t* origem)
{
	gchar* destino = Rotinas_cNewStr(1);
	size_t tamanho = wcslen(origem);
#ifndef __GNUC__
	size_t numCharsConvertidos;
#endif
	//tamanho = sizeof(origem)/sizeof(wchar_t);

	if (tamanho > 0)
	{
		destino = Rotinas_cNewStr(tamanho);

#ifdef __GNUC__
		wcstombs(destino, origem, tamanho);
#else
		wcstombs_s(&numCharsConvertidos, destino, sizeof destino, origem, tamanho);
#endif

		destino[tamanho] = '\0';
		return destino;
	}
	return destino;
}

int Rotinas_cLastIndexOf(const gchar* texto, const char alvo)
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

gchar* Rotinas_cTrim(const gchar* texto)
{
	gchar* retorno = NULL;
	size_t j = 0, inicio = 0, fim = 0;
	unsigned char compara;
	size_t tamanho = strlen(texto);

	if (tamanho > 0)
	{
		retorno = Rotinas_cNewStr(tamanho);

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

gchar* Rotinas_cLowerCase(const gchar* texto)
{
	gchar* retorno = NULL;
	unsigned int i = 0;
	unsigned int j = 0;
	size_t tamanho = strlen(texto);

	if (tamanho > 0)
	{
		retorno = Rotinas_cNewStr(tamanho);
		for (i = 0; texto[i] != '\0'; i++)
		{
			retorno[j] = tolower(texto[i]);
			j++;
		}
		retorno[j] = '\0';
	}
	return retorno;
}

gchar* Rotinas_cUpperCase(const gchar* texto)
{
	gchar* retorno = NULL;
	unsigned int i = 0;
	unsigned int j = 0;
	size_t tamanho = strlen(texto);

	if (tamanho > 0)
	{
		retorno = Rotinas_cNewStr(tamanho);
		for (i = 0; texto[i] != '\0'; i++)
		{
			retorno[j] = toupper(texto[i]);
			j++;
		}
		retorno[j] = '\0';
	}
	return retorno;
}

int Rotinas_cPos(const gchar* subtexto, const gchar* texto)
{
	const gchar* retorno = strstr(texto, subtexto);
	if (retorno == NULL)
		return -1;
	else
		return (int)((retorno - texto) + 1);
}

gboolean Rotinas_cStartsStr(const gchar* sub, const gchar* texto)
{
	if (strncmp(texto, sub, strlen(sub)) == 0)
		return TRUE;
	else
		return FALSE;
}

gboolean Rotinas_cContainsStr(const gchar* texto, const gchar* subtexto)
{
	return (Rotinas_cPos(subtexto, texto) > 0);
}

gboolean Rotinas_cEndsStr(const gchar* texto, const gchar* subtexto)
{
	return (Rotinas_cLastDelimiter(subtexto, texto) > 0);
}

int Rotinas_cLastDelimiter(const gchar* sub, const gchar* texto)
{
	gchar* parte;
	int retorno = -1, tamparte = 0;
	int tamanho = strlen(texto);
	gchar* textolocal;
#ifndef __GNUC__
	gchar *next_token = NULL;
#endif

	if (tamanho > 0)
	{
		retorno = 0;
		textolocal = Rotinas_cNewStr(tamanho);
		g_stpcpy(textolocal, texto);
#ifdef __GNUC__
        parte = strtok(textolocal, sub);
#else
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

gchar* Rotinas_cstrndup(const gchar* texto, size_t tamanho)
{
	gchar* retorno;
	gchar* fim = (gchar*)memchr(texto, 0, tamanho);

	if (fim)
	{
		tamanho = fim - texto + 1;
	}

	retorno = Rotinas_cNewStr(tamanho);

	if (tamanho)
	{
		memcpy(retorno, texto, tamanho - 1);
		retorno[tamanho - 1] = '\0';
	}
	return retorno;
}

gchar* Rotinas_cSubString(const gchar* texto, int inicio, int tamanho)
{
	gchar* retorno = NULL;
	size_t tamtexto = strlen(texto);

	if (tamtexto > 0)
	{
		retorno = Rotinas_cstrndup(texto + inicio - 1, tamanho + 1);
	}
	return retorno;
}

gchar* Rotinas_cIntToStr(int valor)
{
	gchar* retorno;
	int tamanho = 40;

	retorno = Rotinas_cNewStr(tamanho);
#ifdef __GNUC__
	sprintf(retorno, "%d", valor);
#else
	sprintf_s(retorno, tamanho, "%d", valor);
#endif
	return retorno;
}

int Rotinas_cStrToInt(const gchar* texto)
{
	return atoi(texto);
}

gchar* Rotinas_cQuotedStr(const gchar* texto)
{
	gchar* retorno;
	size_t tamanho = strlen(texto) + 4;

	retorno = Rotinas_cNewStr(tamanho);
#ifdef __GNUC__
	sprintf(retorno, "'%s'", texto);
#else
	sprintf_s(retorno, tamanho, "'%s'", texto);
#endif
	return retorno;
}


gchar* Rotinas_cReplaceAll(const gchar* texto,
	const gchar* velho, const gchar* novo)
{
	gchar *retorno, *parte, *textolocal;
	unsigned int j = 0;
	size_t tamanho = strlen(texto);
	size_t tamvelho = strlen(velho);
	size_t tamnovo = strlen(novo);
	size_t tamfinal = 0, tamparte = 0;
#ifndef __GNUC__
	gchar *next_token = NULL;
#endif

	if (tamanho > 0)
	{
		textolocal = Rotinas_cNewStr(tamanho);
		g_stpcpy(textolocal, texto);
		parte = strstr(textolocal, velho);
		while (parte != NULL)
		{
			j++;
			g_stpcpy(textolocal, parte + 1);
			parte = strstr(textolocal, velho);
		}
		tamfinal = (tamanho - (j*tamvelho)) + (j*tamnovo);
		retorno = Rotinas_cNewStr(tamfinal);

		g_stpcpy(textolocal, texto);
#ifdef __GNUC__
        parte = strtok(textolocal, velho);
#else
		parte = strtok_s(textolocal, velho, &next_token);
#endif
		while (parte != NULL)
		{
			tamparte = strlen(parte);
#ifdef __GNUC__
			strncat(retorno, parte, tamparte);
			parte = strtok(NULL, velho);
#else
			strncat_s(retorno, tamfinal+1, parte, tamparte);
			parte = strtok_s(NULL, velho, &next_token);
#endif
			if (parte != NULL)
			{
#ifdef __GNUC__
				strncat(retorno, novo, tamnovo);
#else
				strncat_s(retorno, tamfinal+1, novo, tamnovo);
#endif
			}
		}
	}
	else
	{
		retorno = Rotinas_cNewStr(tamanho);
		g_stpcpy(retorno, texto);
	}
	return retorno;
}

gchar* Rotinas_cFormatLong(const unsigned long valor)
{
	gchar* retorno;
	int tamanho = 40;

	retorno = Rotinas_cNewStr(tamanho);
#ifdef __GNUC__
    sprintf(retorno, "%lu", valor);
#else
	sprintf_s(retorno, tamanho, "%lu", valor);
#endif
	return retorno;
}

gchar* Rotinas_cFormatDouble(const long double valor)
{
	gchar* retorno;
	int tamanho = 40;

	retorno = Rotinas_cNewStr(tamanho);

#ifdef __GNUC__
    double num = round(valor * 100.0L) / 100.0L;
	sprintf(retorno, "%4.2f", num);
#else
	sprintf_s(retorno, tamanho, "%4.2Lf", valor);
#endif

	return retorno;
}

long long Rotinas_cStrToLong(const gchar* texto)
{
	gchar* pEnd;
	return strtoll(texto, &pEnd, 10);
}

gchar* Rotinas_cDoubleToStr(const double valor)
{
	gchar* retorno;
	int tamanho = 40;

	retorno = Rotinas_cNewStr(tamanho);
#ifdef __GNUC__
	sprintf(retorno, "%4.2f", valor);
#else
	sprintf_s(retorno, tamanho, "%4.2f", valor);
#endif
	return retorno;
}

gdouble Rotinas_cStrToDouble(const gchar* texto)
{
	gchar* pEnd;
	return strtod(texto, &pEnd);
}

// ---------------------------------------------------------------------------

GString* Rotinas_MontaTamanhoBig(long double nTam) {
	gchar* fmt;
	GString *ret = g_string_new("");
	long long nUmKilo, nUmMega, nUmGiga, nUmTera, nUmPeta;

	nUmKilo = 1024;
	nUmMega = nUmKilo * nUmKilo;
	nUmGiga = nUmMega * nUmKilo;
	nUmTera = nUmGiga * nUmKilo;
	nUmPeta = nUmTera * nUmKilo;

	if (nTam < nUmKilo) {
		fmt = Rotinas_cFormatDouble(nTam);
		ret = Rotinas_concatenar(fmt, " Byte(s)");
		return ret;
	}
	else if (nTam > nUmKilo && nTam < nUmMega) {
		nTam = nTam / nUmKilo;
		fmt = Rotinas_cFormatDouble(nTam);
		ret = Rotinas_concatenar(fmt, " KByte(s)");
		return ret;
	}
	else if (nTam > nUmMega && nTam < nUmGiga) {
		nTam = nTam / nUmMega;
		fmt = Rotinas_cFormatDouble(nTam);
		ret = Rotinas_concatenar(fmt, " MByte(s)");
		return ret;
	}
	else if (nTam > nUmGiga && nTam < nUmTera) {
		nTam = nTam / nUmGiga;
		fmt = Rotinas_cFormatDouble(nTam);
		ret = Rotinas_concatenar(fmt, " GByte(s)");
		return ret;
	}
	else if (nTam > nUmTera && nTam < nUmPeta) {
		nTam = nTam / nUmTera;
		fmt = Rotinas_cFormatDouble(nTam);
		ret = Rotinas_concatenar(fmt, " TByte(s)");
		return ret;
	}
	else {
		nTam = nTam / nUmPeta;
		fmt = Rotinas_cFormatDouble(nTam);
		ret = Rotinas_concatenar(fmt, " PByte(s)");
		return ret;
	}
}

GString* Rotinas_MontaTamanho(long long nTam) {
	if (nTam > 0) {
		return Rotinas_MontaTamanhoBig((long double)nTam);
	}
	else {
		return g_string_new("");
	}
}


GString* Rotinas_testaNull(char *res) {
	return (res == NULL ? g_string_new("") : g_string_new(Rotinas_cTrim(res)));
}

GString* Rotinas_trocaSeparador(const GString *texto) {
	gchar *txt;
	GString *retorno = g_string_new("");

	if (texto->len > 0) {
		txt = Rotinas_cReplaceAll(texto->str, Rotinas_BARRA_NORMAL, Rotinas_BARRA_INVERTIDA);
		retorno = g_string_new(txt);
	}

	return retorno;
}

gboolean Rotinas_testaSeparadorArquivo(const GString* sDir) {
	GString* sdir = Rotinas_SubString(sDir, sDir->len, 1);
	if (Rotinas_comparar(sdir, Rotinas_BARRA_INVERTIDA)
		|| Rotinas_comparar(sdir, Rotinas_BARRA_NORMAL)) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

GString* Rotinas_ExtractFilePath(const GString *sCaminho) {
	gchar *caminho = g_path_get_dirname(sCaminho->str);
	GString *retorno = g_string_new(caminho);
	return retorno;
}

#ifdef G_OS_WIN32
GString* Rotinas_ExtractFilePathWindows(const GString *sCaminho)
{
	GString *retorno = g_string_new("");
	DWORD tamanho = (DWORD)sCaminho->len;
	gchar *caminho = Rotinas_cNewStr(256);

	DWORD dwRet = GetCurrentDirectory(tamanho, caminho);

	if (dwRet != 0) {
		retorno = g_string_new(caminho);
	}
	return retorno;
}

gboolean Rotinas_FileExistsWindows(const GString *sNomeArquivo)
{
	DWORD atributos = GetFileAttributesA(sNomeArquivo->str);

	if (atributos == INVALID_FILE_ATTRIBUTES) {
		return FALSE;
	}
	if (atributos & FILE_ATTRIBUTE_ARCHIVE) {
		return TRUE;
	}

	return FALSE;
}

gboolean Rotinas_DirectoryExistsWindows(const GString *sNomeArquivo)
{
	DWORD atributos = GetFileAttributes(sNomeArquivo->str);

	if (atributos == INVALID_FILE_ATTRIBUTES) {
		return FALSE;
	}
	if (atributos & FILE_ATTRIBUTE_DIRECTORY) {
		return TRUE;
	}

	return FALSE;
}

gboolean Rotinas_DeleteFromFileWindows(const GString *sNomeArquivo) {
	return DeleteFile(sNomeArquivo->str);
}

#else
gboolean Rotinas_FileExistsLinux(const GString *sNomeArquivo) {
	return g_file_test(sNomeArquivo->str, G_FILE_TEST_EXISTS);
}

gboolean Rotinas_DirectoryExistsLinux(const GString *sNomeArquivo) {
	return g_file_test(sNomeArquivo->str, G_FILE_TEST_EXISTS & G_FILE_TEST_IS_DIR);
}
#endif

GString* Rotinas_ExtractFileName(const GString *sCaminho) {
	gchar *caminho = g_path_get_basename(sCaminho->str);
	GString *retorno = g_string_new(caminho);
	return retorno;
}

gboolean Rotinas_FileExists(const GString *sNomeArquivo) {
//	FILE *arquivo;
	/*
	GFile *garquivo;
	GFileInfo *info;
	GCancellable *cancelavel = NULL;
	GError *erro = NULL;
	goffset tamArquivo;
	*/

#ifdef G_OS_WIN32
	return Rotinas_FileExistsWindows(sNomeArquivo);
#else
	GFile *arquivo = g_file_new_for_path(sNomeArquivo->str);
	GCancellable *cancelavel = NULL;
	return g_file_query_exists(arquivo, cancelavel);
#endif
/*
	garquivo = g_file_new_for_path(sNomeArquivo->str);

	info = g_file_query_info(garquivo, "*", G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS, cancelavel, &erro);

	if (info != NULL) {
		tamArquivo = g_file_info_get_size(info);
		g_object_unref(info);
		g_object_unref(garquivo);

		if (tamArquivo > 0) {
			return TRUE;
		}
	}

	return FALSE;
	*/
}

gboolean Rotinas_DirectoryExists(const GString *sNomeArquivo) {
#ifdef G_OS_WIN32
	return Rotinas_DirectoryExistsWindows(sNomeArquivo);
#else
    return Rotinas_DirectoryExistsLinux(sNomeArquivo);
#endif
}

gboolean Rotinas_DeleteFromFile(const GString *sNomeArquivo) {
	//return (g_remove(sNomeArquivo->str) == 0);

	GFile *garquivo = g_file_new_for_path(sNomeArquivo->str);
	GCancellable *cancelavel = g_cancellable_new();
	GError *erro = NULL;

	gboolean ret = g_file_delete(garquivo, cancelavel, &erro);

	if (erro != NULL) {
		fprintf(stderr, "Erro: %s\n", erro->message);
		g_error_free(erro);
	}

	return ret;
}

GString* Rotinas_getRecurso(const char* chave) {

	if (strcmp(chave, "HFSGuardaDir.ErroInicial") == 0) return g_string_new("Ocorreu um erro no aplicativo!");

	if (strcmp(chave, "Tabela.nome") == 0) return g_string_new("Nome");
	if (strcmp(chave, "Tabela.tamanho") == 0) return g_string_new("Tamanho");
	if (strcmp(chave, "Tabela.tipo") == 0) return g_string_new("Tipo");
	if (strcmp(chave, "Tabela.modificado") == 0) return g_string_new("Modificado");
	if (strcmp(chave, "Tabela.atributos") == 0) return g_string_new("Atributos");
	if (strcmp(chave, "Tabela.caminho") == 0) return g_string_new("Caminho");
	if (strcmp(chave, "Tabela.aba") == 0) return g_string_new("Aba");

	if (strcmp(chave, "Aba.codigo") == 0) return g_string_new("Código:");
	if (strcmp(chave, "Aba.nome") == 0) return g_string_new("Nome:");

	if (strcmp(chave, "Tipo.codigo") == 0) return g_string_new("Código:");
	if (strcmp(chave, "Tipo.nome") == 0) return g_string_new("Nome:");

	if (strcmp(chave, "TipoLista.arquivo") == 0) return g_string_new("Arquivo");
	if (strcmp(chave, "TipoLista.diretorio") == 0) return g_string_new(Rotinas_retUTF8("Diretório"));

	if (strcmp(chave, "ConexaoParams.nome") == 0) return g_string_new("Nome:");
	if (strcmp(chave, "ConexaoParams.driver") == 0) return g_string_new("Driver:");
	if (strcmp(chave, "ConexaoParams.url") == 0) return g_string_new("URL:");
	if (strcmp(chave, "ConexaoParams.login") == 0) return g_string_new("Login:");
	if (strcmp(chave, "ConexaoParams.senha") == 0) return g_string_new("Senha:");

	if (strcmp(chave, "Diretorio.aba") == 0) return g_string_new("Aba:");
	if (strcmp(chave, "Diretorio.codigo") == 0) return g_string_new("Código:");
	if (strcmp(chave, "Diretorio.ordem") == 0) return g_string_new("Ordem:");
	if (strcmp(chave, "Diretorio.nome") == 0) return g_string_new("Nome:");
	if (strcmp(chave, "Diretorio.tamanho") == 0) return g_string_new("Tamanho:");
	if (strcmp(chave, "Diretorio.tipo") == 0) return g_string_new("Tipo:");
	if (strcmp(chave, "Diretorio.modificado") == 0) return g_string_new("Modificado:");
	if (strcmp(chave, "Diretorio.atributos") == 0) return g_string_new("Atributos:");
	if (strcmp(chave, "Diretorio.codDirPai") == 0) return g_string_new("Código Diretório Pai:");
	if (strcmp(chave, "Diretorio.caminho") == 0) return g_string_new("Caminho:");

	if (strcmp(chave, "Extensao.codigo") == 0) return g_string_new("Código:");
	if (strcmp(chave, "Extensao.nome") == 0) return g_string_new("Extensão:");
	if (strcmp(chave, "Extensao.icone") == 0) return g_string_new("Ícone:");
	if (strcmp(chave, "Extensao.arquivo") == 0) return g_string_new("arquivo(file)");
	if (strcmp(chave, "Extensao.diretorio") == 0) return g_string_new("diretorio(directory)");
	if (strcmp(chave, "Extensao.zip") == 0) return g_string_new(".zip");

	if (strcmp(chave, "FrmPrincipal.titulo") == 0) return g_string_new("HFSGuardaDiretorio 2.0 - Catalogador de Diretórios");
	if (strcmp(chave, "FrmPrincipal.barraStatus1") == 0) return g_string_new("Quantidade Total: , Tamanho Total:");
	if (strcmp(chave, "FrmPrincipal.btnImportarDiretorio") == 0) return g_string_new("Importar Diretório");
	if (strcmp(chave, "FrmPrincipal.btnPesquisa") == 0) return g_string_new("Pesquisar");
	if (strcmp(chave, "FrmPrincipal.Aba1") == 0) return g_string_new("DISCO1");
	if (strcmp(chave, "FrmPrincipal.menuAba") == 0) return g_string_new("Aba");
	if (strcmp(chave, "FrmPrincipal.menuIncluirNovaAba") == 0) return g_string_new("Incluir Nova Aba");
	if (strcmp(chave, "FrmPrincipal.menuDiretorio") == 0) return g_string_new("Diretório");
	if (strcmp(chave, "FrmPrincipal.menuAlterarNomeAbaAtiva") == 0) return g_string_new("Alterar Nome da Aba Ativa");
	if (strcmp(chave, "FrmPrincipal.menuExcluirAbaAtiva") == 0) return g_string_new("Excluir Aba Ativa");
	if (strcmp(chave, "FrmPrincipal.menuImportarDiretorio") == 0) return g_string_new("Importar Diretório");
	if (strcmp(chave, "FrmPrincipal.menuImportarSubDiretorios") == 0) return g_string_new("Importar SubDiretórios");
	if (strcmp(chave, "FrmPrincipal.menuCompararDiretorios") == 0) return g_string_new("Comparar Diretórios");
	if (strcmp(chave, "FrmPrincipal.menuCadastrarExtensaoArquivo") == 0) return g_string_new("Cadastrar Extensão de Arquivo");
	if (strcmp(chave, "FrmPrincipal.menuExpandirDiretorios") == 0) return g_string_new("Expandir Diretórios");
	if (strcmp(chave, "FrmPrincipal.menuColapsarDiretorios") == 0) return g_string_new("Colapsar Diretórios");
	if (strcmp(chave, "FrmPrincipal.menuExportarDiretoriosAbaAtiva") == 0) return g_string_new("Exportar Diretórios da Aba Ativa");
	if (strcmp(chave, "FrmPrincipal.menuTXT") == 0) return g_string_new("TXT");
	if (strcmp(chave, "FrmPrincipal.menuCSV") == 0) return g_string_new("CSV");
	if (strcmp(chave, "FrmPrincipal.menuHTML") == 0) return g_string_new("HTML");
	if (strcmp(chave, "FrmPrincipal.menuXML") == 0) return g_string_new("XML");
	if (strcmp(chave, "FrmPrincipal.menuSQL") == 0) return g_string_new("SQL");
	if (strcmp(chave, "FrmPrincipal.menuImportarDiretoriosViaXML") == 0) return g_string_new("Importar Diretórios Via XML");
	if (strcmp(chave, "FrmPrincipal.menuGravarLogImportacao") == 0) return g_string_new("Gravar Log da Importação");
	if (strcmp(chave, "FrmPrincipal.menuVisao") == 0) return g_string_new("Visão");
	if (strcmp(chave, "FrmPrincipal.menuMostrarOcultarArvoreDirAbaAtiva") == 0) return g_string_new("Mostrar/Ocultar Árvore de diretórios da Aba Ativa");
	if (strcmp(chave, "FrmPrincipal.menuMostrarOcultarListaItensPesquisados") == 0) return g_string_new("Mostrar/Ocultar lista de itens pesquisados");
	if (strcmp(chave, "FrmPrincipal.menuSobre") == 0) return g_string_new("Sobre");
	if (strcmp(chave, "FrmPrincipal.TamMaxPesquisa") == 0) return g_string_new("A pesquisa só é feita com pelo menos 2 caracteres!");
	if (strcmp(chave, "FrmPrincipal.DigitaNomeDiretorio") == 0) return g_string_new("Este diretório não possui um nome.\nDigite o nome do diretório!");
	if (strcmp(chave, "FrmPrincipal.ValidaNomeDiretorio") == 0) return g_string_new("Nenhum nome de diretório informado!");
	if (strcmp(chave, "FrmPrincipal.ErroSalvarArquivo") == 0) return g_string_new("Ocorreu um erro ao salvar o arquivo.");
	if (strcmp(chave, "FrmPrincipal.SucessoExportar") == 0) return g_string_new("Exportação realizada com sucesso!");
	if (strcmp(chave, "FrmPrincipal.ExcluirDiretorioSelecionado") == 0) return g_string_new("Tem Certeza, que você deseja excluir este diretório, isto implicará na destruição de todos os seus items catalogados?");
	if (strcmp(chave, "FrmPrincipal.ImportacaoNaoRealizada") == 0) return g_string_new("Importação não realizada!");
	if (strcmp(chave, "FrmPrincipal.DiretorioExisteCatalogo") == 0) return g_string_new("Este diretório já existe no catálogo!");
	if (strcmp(chave, "FrmPrincipal.ImportacaoRealizada") == 0) return g_string_new("Importação realizada com sucesso!");
	if (strcmp(chave, "FrmPrincipal.ErroAbrirDir") == 0) return g_string_new("Um erro ocorreu. Nenhum diretório foi escolhido.");
	if (strcmp(chave, "FrmPrincipal.DirImportacaoSucesso") == 0) return g_string_new("Importação do(s) diretório(s) realizada com sucesso!");
	if (strcmp(chave, "FrmPrincipal.DigitaIncluirNovaAba") == 0) return g_string_new("Digite o Nome da Nova Aba?");
	if (strcmp(chave, "FrmPrincipal.DigitaAlterarNomeAba") == 0) return g_string_new("Digite o Novo Nome da Aba Ativa?");
	if (strcmp(chave, "FrmPrincipal.ConfirmaExcluirAba") == 0) return g_string_new("Tem Certeza, que você deseja excluir esta aba, \nisto implicará na destruição de todos os seus itens catalogados?");
	if (strcmp(chave, "FrmPrincipal.ValidaExcluirAba") == 0) return g_string_new("A primeira Aba não pode ser excluída!");
	if (strcmp(chave, "FrmPrincipal.menuSobreCatalogador") == 0) return g_string_new("Sobre o Catalogador");
	if (strcmp(chave, "FrmPrincipal.menuIdioma") == 0) return g_string_new("Idioma");
	if (strcmp(chave, "FrmPrincipal.menuPortugues") == 0) return g_string_new("Português [Portuguese]");
	if (strcmp(chave, "FrmPrincipal.menuIngles") == 0) return g_string_new("Inglês [English]");
	if (strcmp(chave, "FrmPrincipal.menuEspanhol") == 0) return g_string_new("Espanhol [Spanish]");
	if (strcmp(chave, "FrmPrincipal.menuFrances") == 0) return g_string_new("Francês [French]");
	if (strcmp(chave, "FrmPrincipal.menuItaliano") == 0) return g_string_new("Italiano [Italian]");
	if (strcmp(chave, "FrmPrincipal.menuAlemao") == 0) return g_string_new("Alemão [German]");
	if (strcmp(chave, "FrmPrincipal.menuJapones") == 0) return g_string_new("Japonês [Japanese]");
	if (strcmp(chave, "FrmPrincipal.menuCoreano") == 0) return g_string_new("Coreano [Korean]");
	if (strcmp(chave, "FrmPrincipal.menuChinesTradicional") == 0) return g_string_new("Chinês Tradicional [Traditional Chinese]");
	if (strcmp(chave, "FrmPrincipal.menuExcluirDiretorioSelecionado") == 0) return g_string_new("Excluir Diretório Selecionado");
	if (strcmp(chave, "FrmPrincipal.menuInformacoesDiretorioArquivo") == 0) return g_string_new("Informações do Diretório / Arquivo");

	if (strcmp(chave, "FrmSobre.titulo") == 0) return g_string_new("Sobre o Catalogador");
	if (strcmp(chave, "FrmSobre.label1") == 0) return g_string_new("HFSGuardaDir 2.0 - Catalogador de Diretórios");
	if (strcmp(chave, "FrmSobre.label2") == 0) return g_string_new("Desenvolvido em Java com Swing, Versão: 2.0");
	if (strcmp(chave, "FrmSobre.label3") == 0) return g_string_new("Por Henrique Figueiredo de Souza");
	if (strcmp(chave, "FrmSobre.label4") == 0) return g_string_new("Todos os direitos reservados, 2015");
	if (strcmp(chave, "FrmSobre.Propriedade") == 0) return g_string_new("Propriedade");
	if (strcmp(chave, "FrmSobre.Valor") == 0) return g_string_new("Valor");

	if (strcmp(chave, "FrmSplash.label1") == 0) return g_string_new("HFSGuardaDiretorio 2.0");
	if (strcmp(chave, "FrmSplash.label2") == 0) return g_string_new("Catalogador de Diretórios");

	if (strcmp(chave, "FrmCompararDiretorio.titulo") == 0) return g_string_new("Comparar Diretórios");
	if (strcmp(chave, "FrmCompararDiretorio.btnCompararDiretorios") == 0) return g_string_new("Comparar Diretórios");
	if (strcmp(chave, "FrmCompararDiretorio.btnSalvarLog") == 0) return g_string_new("Salvar Log");
	if (strcmp(chave, "FrmCompararDiretorio.barraStatus1") == 0) return g_string_new(Rotinas_retUTF8("Total de diferenças encontradas:"));
	if (strcmp(chave, "FrmCompararDiretorio.panelDiretorio1") == 0) return g_string_new("Diretório 1");
	if (strcmp(chave, "FrmCompararDiretorio.labDiferencasEncontradas") == 0) return g_string_new("Diferenças Encontradas");
	if (strcmp(chave, "FrmCompararDiretorio.panelDiretorio2") == 0) return g_string_new("Diretório 2");
	if (strcmp(chave, "FrmCompararDiretorio.NenhumaDiferencaEncontrada") == 0) return g_string_new("Nenhuma diferença encontrada!");
	if (strcmp(chave, "FrmCompararDiretorio.DiretoriosNaoSelecionados") == 0) return g_string_new("Diretórios não selecionados!");
	if (strcmp(chave, "FrmCompararDiretorio.LogSalvoMemoDirSistema") == 0) return g_string_new("Log salvo no mesmo diretório do sistema!");

	if (strcmp(chave, "FrmCadExtensao.titulo") == 0) return g_string_new("Cadastro de Extensão de Arquivo");
	if (strcmp(chave, "FrmCadExtensao.extensao") == 0) return g_string_new("Extensão");
	if (strcmp(chave, "FrmCadExtensao.icone") == 0) return g_string_new("Ícone");
	if (strcmp(chave, "FrmCadExtensao.btnIncluir") == 0) return g_string_new("Incluir");
	if (strcmp(chave, "FrmCadExtensao.btnExcluir") == 0) return g_string_new("Excluir");
	if (strcmp(chave, "FrmCadExtensao.menuExtensao") == 0) return g_string_new("Extensão");
	if (strcmp(chave, "FrmCadExtensao.menuExportarTodos") == 0) return g_string_new("Exportar Todos");
	if (strcmp(chave, "FrmCadExtensao.menuImportarTodos") == 0) return g_string_new("Importar Todos");
	if (strcmp(chave, "FrmCadExtensao.menuIncluirExtensao") == 0) return g_string_new("Incluir Extensão");
	if (strcmp(chave, "FrmCadExtensao.menuExcluirExtensao") == 0) return g_string_new("Excluir Extensão");
	if (strcmp(chave, "FrmCadExtensao.menuExcluirTodasExtensoes") == 0) return g_string_new("Excluir Todas Extensões");
	if (strcmp(chave, "FrmCadExtensao.menuExportarIcone") == 0) return g_string_new("Exportar para Ícone");
	if (strcmp(chave, "FrmCadExtensao.menuExportarGIF") == 0) return g_string_new("Exportar para GIF");
	if (strcmp(chave, "FrmCadExtensao.menuExportarJPEG") == 0) return g_string_new("Exportar para JPEG");
	if (strcmp(chave, "FrmCadExtensao.menuExportarPNG") == 0) return g_string_new("Exportar para PNG");
	if (strcmp(chave, "FrmCadExtensao.menuExportarTIFF") == 0) return g_string_new("Exportar para TIFF");
	if (strcmp(chave, "FrmCadExtensao.menuImportarIconesArquivos") == 0) return g_string_new("Importar Ícones dos Arquivos");
	if (strcmp(chave, "FrmCadExtensao.menuExtrairIconesArquivos") == 0) return g_string_new("Extrair Ícones dos Arquivos");
	if (strcmp(chave, "FrmCadExtensao.ExtensaoJaCadastrada") == 0) return g_string_new("Extensão já existe cadastrada!");
	if (strcmp(chave, "FrmCadExtensao.ExtensaoSalvaSucesso") == 0) return g_string_new("Extensão salva com sucesso!");
	if (strcmp(chave, "FrmCadExtensao.ExtensaoCertezaExcluir") == 0) return g_string_new("Tem Certeza, que você deseja excluir esta extensão?");
	if (strcmp(chave, "FrmCadExtensao.ExtensaoCertezaTodosExcluir") == 0) return g_string_new("Tem Certeza, que você deseja excluir todas as extensões?");
	if (strcmp(chave, "FrmCadExtensao.ExtensaoExcluidaSucesso") == 0) return g_string_new("Extensão excluída com sucesso!");
	if (strcmp(chave, "FrmCadExtensao.ExtensoesExcluidasSucesso") == 0) return g_string_new("Extensões excluídas com sucesso!");
	if (strcmp(chave, "FrmCadExtensao.ExportarExtensao") == 0) return g_string_new("Ícones salvos no mesmo diretório do sistema!");
	if (strcmp(chave, "FrmCadExtensao.menuExportarBitmap") == 0) return g_string_new("Exportar para Bitmap");

	if (strcmp(chave, "FrmInfoDiretorio.titulo") == 0) return g_string_new("Informações do Diretório / Arquivo");
	if (strcmp(chave, "FrmInfoDiretorio.panelLegenda") == 0) return g_string_new("Legenda dos Atributos");
	if (strcmp(chave, "FrmInfoDiretorio.labArquivoComum") == 0) return g_string_new("[ARQ] - Arquivo comum");
	if (strcmp(chave, "FrmInfoDiretorio.labArquivoOculto") == 0) return g_string_new("[HID] - Arquivo Oculto");
	if (strcmp(chave, "FrmInfoDiretorio.labArquivoSistema") == 0) return g_string_new("[SYS] - Arquivo de Sistema");
	if (strcmp(chave, "FrmInfoDiretorio.labDiretorio") == 0) return g_string_new("[DIR] - Diretório");
	if (strcmp(chave, "FrmInfoDiretorio.labVolumeID") == 0) return g_string_new("[VOL] - Volume ID");
	if (strcmp(chave, "FrmInfoDiretorio.labArquivoSomenteLeitura") == 0) return g_string_new("[ROL] - Arquivo Somente Leitura");
	if (strcmp(chave, "FrmInfoDiretorio.item") == 0) return g_string_new("Item");
	if (strcmp(chave, "FrmInfoDiretorio.descricao") == 0) return g_string_new("Descrição");

	if (strcmp(chave, "FrmImportarDiretorio.titulo") == 0) return g_string_new("Importando Diretório");
	if (strcmp(chave, "FrmImportarDiretorio.barraStatus1") == 0) return g_string_new("Total de linhas sendo processadas:");
	if (strcmp(chave, "FrmImportarDiretorio.DiretorioExisteCatalogo") == 0) return g_string_new("O diretório já existe no catálogo!");

	if (strcmp(chave, "Dialogo.info") == 0) return g_string_new("Informação");
	if (strcmp(chave, "Dialogo.erro") == 0) return g_string_new("Erro");
	if (strcmp(chave, "Dialogo.confirma") == 0) return g_string_new("Confirma");
	if (strcmp(chave, "Dialogo.entrada") == 0) return g_string_new("Informa");
	if (strcmp(chave, "Dialogo.yesButtonText") == 0) return g_string_new("Sim");
	if (strcmp(chave, "Dialogo.yesButtonMnemonic") == 0) return g_string_new("S");
	if (strcmp(chave, "Dialogo.cancelButtonText") == 0) return g_string_new("Cancelar");
	if (strcmp(chave, "Dialogo.cancelButtonMnemonic") == 0) return g_string_new("C");
	if (strcmp(chave, "Dialogo.noButtonText") == 0) return g_string_new("Não");
	if (strcmp(chave, "Dialogo.noButtonMnemonic") == 0) return g_string_new("N");
	if (strcmp(chave, "Dialogo.okButtonText") == 0) return g_string_new("OK");
	if (strcmp(chave, "Dialogo.okButtonMnemonic") == 0) return g_string_new("O");

	if (strcmp(chave, "EscolhaArquivo.ApproveButtonText") == 0) return g_string_new("Escolha o Diretório");
	if (strcmp(chave, "EscolhaArquivo.ApproveButtonMnemonic") == 0) return g_string_new("D");
	if (strcmp(chave, "EscolhaArquivo.ApproveButtonToolTipText") == 0) return g_string_new("Confirme a escolha do diretório.");
	if (strcmp(chave, "EscolhaArquivo.lookInLabelMnemonic") == 0) return g_string_new("E");
	if (strcmp(chave, "EscolhaArquivo.lookInLabelText") == 0) return g_string_new("Examinar em");
	if (strcmp(chave, "EscolhaArquivo.saveInLabelMnemonic") == 0) return g_string_new("S");
	if (strcmp(chave, "EscolhaArquivo.saveInLabelText") == 0) return g_string_new("Salvar em");
	if (strcmp(chave, "EscolhaArquivo.upFolderToolTipText") == 0) return g_string_new("Um nível acima");
	if (strcmp(chave, "EscolhaArquivo.upFolderAccessibleName") == 0) return g_string_new("Um nível acima");
	if (strcmp(chave, "EscolhaArquivo.homeFolderToolTipText") == 0) return g_string_new("Desktop");
	if (strcmp(chave, "EscolhaArquivo.homeFolderAccessibleName") == 0) return g_string_new("Desktop");
	if (strcmp(chave, "EscolhaArquivo.newFolderToolTipText") == 0) return g_string_new("Criar nova pasta");
	if (strcmp(chave, "EscolhaArquivo.newFolderAccessibleName") == 0) return g_string_new("Criar nova pasta");
	if (strcmp(chave, "EscolhaArquivo.listViewButtonToolTipText") == 0) return g_string_new("Lista");
	if (strcmp(chave, "EscolhaArquivo.listViewButtonAccessibleName") == 0) return g_string_new("Lista");
	if (strcmp(chave, "EscolhaArquivo.detailsViewButtonToolTipText") == 0) return g_string_new("Detalhes");
	if (strcmp(chave, "EscolhaArquivo.detailsViewButtonAccessibleName") == 0) return g_string_new("Detalhes");
	if (strcmp(chave, "EscolhaArquivo.fileNameLabelMnemonic") == 0) return g_string_new("N");
	if (strcmp(chave, "EscolhaArquivo.fileNameLabelText") == 0) return g_string_new("Nome do arquivo");
	if (strcmp(chave, "EscolhaArquivo.filesOfTypeLabelMnemonic") == 0) return g_string_new("A");
	if (strcmp(chave, "EscolhaArquivo.filesOfTypeLabelText") == 0) return g_string_new("Arquivos do tipo");
	if (strcmp(chave, "EscolhaArquivo.fileNameHeaderText") == 0) return g_string_new("Nome");
	if (strcmp(chave, "EscolhaArquivo.fileSizeHeaderText") == 0) return g_string_new("Tamanho");
	if (strcmp(chave, "EscolhaArquivo.fileTypeHeaderText") == 0) return g_string_new("Tipo");
	if (strcmp(chave, "EscolhaArquivo.fileDateHeaderText") == 0) return g_string_new("Data");
	if (strcmp(chave, "EscolhaArquivo.fileAttrHeaderText") == 0) return g_string_new("Atributos");
	if (strcmp(chave, "EscolhaArquivo.cancelButtonText") == 0) return g_string_new("Cancelar");
	if (strcmp(chave, "EscolhaArquivo.cancelButtonMnemonic") == 0) return g_string_new("C");
	if (strcmp(chave, "EscolhaArquivo.cancelButtonToolTipText") == 0) return g_string_new("Cancelar");
	if (strcmp(chave, "EscolhaArquivo.openButtonText") == 0) return g_string_new("Abrir");
	if (strcmp(chave, "EscolhaArquivo.openButtonMnemonic") == 0) return g_string_new("A");
	if (strcmp(chave, "EscolhaArquivo.openButtonToolTipText") == 0) return g_string_new("Abrir");
	if (strcmp(chave, "EscolhaArquivo.saveButtonText") == 0) return g_string_new("Salvar");
	if (strcmp(chave, "EscolhaArquivo.saveButtonMnemonic") == 0) return g_string_new("S");
	if (strcmp(chave, "EscolhaArquivo.saveButtonToolTipText") == 0) return g_string_new("Salvar");
	if (strcmp(chave, "EscolhaArquivo.updateButtonText") == 0) return g_string_new("Alterar");
	if (strcmp(chave, "EscolhaArquivo.updateButtonMnemonic") == 0) return g_string_new("A");
	if (strcmp(chave, "EscolhaArquivo.updateButtonToolTipText") == 0) return g_string_new("Alterar");
	if (strcmp(chave, "EscolhaArquivo.helpButtonText") == 0) return g_string_new("Ajuda");
	if (strcmp(chave, "EscolhaArquivo.helpButtonMnemonic") == 0) return g_string_new("A");
	if (strcmp(chave, "EscolhaArquivo.helpButtonToolTipText") == 0) return g_string_new("Ajuda");
	if (strcmp(chave, "EscolhaArquivo.acceptAllFileFilterText") == 0) return g_string_new("Todos os arquivos (*.*)");
	if (strcmp(chave, "EscolhaArquivo.filtroTXT") == 0) return g_string_new("Arquivo TXT (*.txt)");
	if (strcmp(chave, "EscolhaArquivo.filtroCSV") == 0) return g_string_new("Arquivo CSV (*.csv)");
	if (strcmp(chave, "EscolhaArquivo.filtroHTML") == 0) return g_string_new("Arquivo HTML (*.html)");
	if (strcmp(chave, "EscolhaArquivo.filtroXML") == 0) return g_string_new("Arquivo XML (*.xml)");
	if (strcmp(chave, "EscolhaArquivo.filtroSQL") == 0) return g_string_new("Arquivo SQL (*.sql)");
	if (strcmp(chave, "EscolhaArquivo.filtroBMP") == 0) return g_string_new("Arquivo BMP (*.bmp)");
	if (strcmp(chave, "EscolhaArquivo.filtroICO") == 0) return g_string_new("Arquivo ICO (*.ico)");
	if (strcmp(chave, "EscolhaArquivo.filtroGIF") == 0) return g_string_new("Arquivo GIF (*.gif)");
	if (strcmp(chave, "EscolhaArquivo.filtroPNG") == 0) return g_string_new("Arquivo JPEG (*.png)");
	if (strcmp(chave, "EscolhaArquivo.filtroJPG") == 0) return g_string_new("Arquivo PNG (*.jpg)");
	if (strcmp(chave, "EscolhaArquivo.filtroTIF") == 0) return g_string_new("Arquivo TIFF (*.tif)");
	if (strcmp(chave, "EscolhaArquivo.todosDiretorios") == 0) return g_string_new("Todos os diretórios");

	return g_string_new(chave);
}

// ---------------------------------------------------------------------------

gboolean Rotinas_SListSaveToFile(const ListaString lista, const GString* sNomeArquivo) {
	gboolean ret = FALSE;
	GFile *garquivo;
	GOutputStream *gos;
	GFileOutputStream *fos;
	gsize bytesEscritos = 0;
	gchar *texto, *nomeArquivo;
	GCancellable *cancelavel = NULL;
	GError *erro = NULL;

	GString* linha = g_string_new("");
	GString* conteudo = g_string_new("");
	guint tamlista = ListaString_conta(lista);

	if (tamlista > 0) {

		for (unsigned int i = 0; i < tamlista; i++) {
			linha = ListaString_pesquisaItemOrd(lista, i);
			conteudo = g_string_append(conteudo, linha->str);
			conteudo = g_string_append(conteudo, "\n");
		}

		if (conteudo->len > 0) {
			nomeArquivo = sNomeArquivo->str;
			texto = conteudo->str;

			garquivo = g_file_new_for_path(nomeArquivo);
			fos = g_file_append_to(garquivo, G_FILE_CREATE_NONE, cancelavel, &erro);
			gos = (GOutputStream *)fos;
			g_output_stream_write_all(gos, texto, conteudo->len, &bytesEscritos, cancelavel, &erro);
			g_output_stream_close(gos, cancelavel, &erro);

			g_error_free(erro);
			g_free(texto);
			g_string_free(conteudo, TRUE);
			g_object_unref(garquivo);
			g_object_unref(fos);

			ret = TRUE;
		}

	}

	return ret;
}

ListaString Rotinas_SListLoadFromFile(const GString* sNomeArquivo) {
	GFile *garquivo;
	GInputStream *gis;
	GFileInputStream *fis;
	GFileInfo *info;
	gsize tamArquivo;
	gsize tamtexto;
	gsize bytesLidos = 0;
	gint posicao = 0;
	ListaString lista = ListaString_inicia();
	GString *pedaco, *substr;
	gchar *texto, *nomeArquivo;
	GCancellable *cancelavel = NULL;
	GError *erro = NULL;

	//GString* linha = g_string_new("");

	nomeArquivo = sNomeArquivo->str;

	garquivo = g_file_new_for_path(nomeArquivo);

	info = g_file_query_info(garquivo, "*", G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS, cancelavel, &erro);

	if (info != NULL) {
		tamArquivo = (gsize)g_file_info_get_size(info);
		g_object_unref(info);

		texto = Rotinas_cNewStr((unsigned int)tamArquivo);

		fis = g_file_read(garquivo, cancelavel, &erro);
		gis = (GInputStream *)fis;
		g_input_stream_read_all(gis, texto, tamArquivo, &bytesLidos, cancelavel, &erro);
		g_input_stream_close(gis, cancelavel, &erro);

		if (bytesLidos > 0) {
			pedaco = g_string_new("");
			tamtexto = strlen(texto);
			for (unsigned int i = 0; i < tamtexto; i++) {
				pedaco = g_string_append_c_inline(pedaco, texto[i]);
				if (texto[i] == '\n') {
					substr = Rotinas_SubString(pedaco, 1, pedaco->len - 1);
					lista = ListaString_insere(lista, substr, posicao);
					pedaco = g_string_truncate(pedaco, 0);
					posicao++;
				}
			}
			//g_string_free(pedaco, FALSE);
			//g_string_free(substr, FALSE);
		}

		g_error_free(erro);
		g_free(texto);
		g_object_unref(garquivo);
		g_object_unref(fis);

	}
	else {
		return NULL;
	}

	return lista;
}

ListaString Rotinas_SListSeparador(const GString* texto, const gchar separador) {
	ListaString lista = ListaString_inicia();
	GString *pedaco, *substr;
	GString* sep = g_string_new("");
	gint posicao = 0;
	sep = g_string_append_c_inline(sep, separador);

	if (Rotinas_ContainsStr(texto, sep)) {
		pedaco = g_string_new("");
		for (unsigned int i = 0; i < texto->len; i++) {
			pedaco = g_string_append_c_inline(pedaco, texto->str[i]);
			if (texto->str[i] == separador) {
				substr = Rotinas_SubString(pedaco, 1, pedaco->len-1);
				lista = ListaString_insere(lista, substr, posicao);
				pedaco = g_string_truncate(pedaco, 0);
				posicao++;
			}
		}
		lista = ListaString_insere(lista, pedaco, posicao);
	}
	else {
		lista = ListaString_insere(lista, (GString*)texto, posicao);
	}

	//g_string_free(pedaco, FALSE);
	//g_string_free(substr, FALSE);
	g_string_free(sep, TRUE);

	return lista;
}

GString* Rotinas_SListTexto(const ListaString lista) {
	GString* linha = g_string_new("");
	GString* texto = g_string_new("");
	guint ntamlista = ListaString_conta(lista);

	if (ntamlista > 0) {
		for (unsigned int i = 0; i < ntamlista; i++) {
			linha = ListaString_pesquisaItemOrd(lista, i);
			texto = g_string_append(texto, linha->str);
		}
	}
	return texto;
}

gboolean Rotinas_BlobSaveToFile(const void* blob, size_t tamanho, const GString* sNomeArquivo) {
	gboolean ret = TRUE;
	FILE* fp;

#ifdef __GNUC__
	fp = fopen(sNomeArquivo->str, "wb");
#else
    errno_t erro;
	erro = fopen_s(&fp, sNomeArquivo->str, "wb");
#endif
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

long long Rotinas_BlobLoadFromFile(const GString* sNomeArquivo, void** blob) {
	long long ret = 0;
	FILE* fp;
	//	long tamanho;

#ifdef __GNUC__
	fp = fopen(sNomeArquivo->str, "rb");
#else
    errno_t erro;
	erro = fopen_s(&fp, sNomeArquivo->str, "rb");
#endif

	if (NULL != fp)
	{
		/*
		fseek(fp, 0L, SEEK_END);
		tamanho = ftell(fp);
		//fseek(fp, 0L, SEEK_SET);
		rewind(fp);
		*/
#ifdef __GNUC__
        char buffer[16 * 1024];
        buffer[0] = '\0';
#else
		const size_t tamanho = 16 * 1024;
		char* buffer = (char*)malloc(tamanho);
#endif
		*blob = &buffer;

		size_t ntamanho = fread(*blob, sizeof(char), 16 * 1024, fp);
		buffer[ntamanho] = '\0';
		fclose(fp);

		ret = ntamanho;
	}

	return ret;

}

Arquivo Rotinas_FileInfoToArquivo(const GString *sCaminho) {
	Arquivo arq = Arquivo_new();
	GFileInfo* info = g_file_info_new();
	GCancellable *cancelavel = NULL;
	GError *erro = NULL;
	GFile *garquivo;
	GFileType tipo;
	const char* nome;
	GDateTime *tempoGArquivo;
	goffset tamanhoGArquivo;
	//GIcon* icone;

	garquivo = g_file_new_for_path(sCaminho->str);

	if (garquivo != NULL) {
		info = g_file_query_info(garquivo, "*",
			G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS, cancelavel, &erro);

		tipo = g_file_info_get_file_type(info);
		nome = g_file_info_get_name(info);
		tempoGArquivo = g_file_info_get_modification_date_time(info);
		tamanhoGArquivo = g_file_info_get_size(info);

		//icone = g_file_info_get_icon(info);

		//char** lista = g_file_info_list_attributes(info, NULL);
		//char* item = lista[0];

		arq->nome = g_string_new(nome);
		arq->tamanho = tamanhoGArquivo;
		arq->modificado = tempoGArquivo; //g_date_time_new_from_unix_local(&tempoGArquivo);

		//"[ROL]" e "[SYS]"

		if (g_file_info_get_is_hidden(info)) {
			arq->atributos = g_string_append(arq->atributos, "[HID]");
		}
		if (tipo == G_FILE_TYPE_DIRECTORY) {
			arq->atributos = g_string_append(arq->atributos, "[DIR]");
		}
		if (tipo == G_FILE_TYPE_REGULAR) {
			arq->atributos = g_string_append(arq->atributos, "[ARQ]");
		}


	}

	return arq;
}

ListaString Rotinas_cListarArquivosDiretorios(const char* sDiretorio) {
	ListaString lista = ListaString_inicia();
	gint posicao = 0;
	GString *nome, *dir = g_string_new(sDiretorio);
	GString *ponto = g_string_new(".");
	GString *pponto = g_string_new("..");
	DIR *dp;
	struct dirent *ep;

	if (!Rotinas_testaSeparadorArquivo(dir)) {
		dir = g_string_append(dir, Rotinas_BARRA_INVERTIDA);
	}

	dp = opendir(sDiretorio);
	if (dp != NULL)	{

		do {
            ep = readdir(dp);

			nome = g_string_new(ep->d_name);
			//ep->d_namlen
			//ep->d_reclen
			//if (ep->d_type == DT_DIR) {}
			if (!g_string_equal(nome, ponto) && !g_string_equal(nome, pponto)) {
				nome = Rotinas_concatenar(dir->str, nome->str);
				lista = ListaString_insere(lista, nome, posicao);
				posicao++;
			}
		} while (ep != NULL);

		(void)closedir(dp);
	}
	else {
		perror("nao consigo abrir o diretorio");
	}

	return lista;
}

ListaString Rotinas_listarArquivosDiretorios(const GString* sDiretorio) {
	ListaString lista = ListaString_inicia();
	GFile *gdiretorio;
	//GFile *garquivo;
	GCancellable *cancelavel = NULL;
	GError *erro = NULL;
	GFileEnumerator* filhos;
	GFileInfo *info;
	//GFileType tipo;
	const char* nome;
	gint posicao = 0;
	GString *dir = g_string_new(sDiretorio->str);
	//GString *ponto = g_string_new(".");
	//GString *pponto = g_string_new("..");
	GString *nomeGArquivo;
	//GDateTime *tempoGArquivo;
	//goffset tamanhoGArquivo;

	if (!Rotinas_testaSeparadorArquivo(sDiretorio)) {
		dir = g_string_append(dir, Rotinas_BARRA_INVERTIDA);
	}

	gdiretorio = g_file_new_for_path(sDiretorio->str);

	filhos = g_file_enumerate_children(gdiretorio,
		"standard::name, standard::type", G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS, cancelavel, &erro);

	if (filhos != NULL) {
		info = g_file_enumerator_next_file(filhos, cancelavel, &erro);

		while (info != NULL) {
			//tipo = g_file_info_get_file_type(info);
			nome = g_file_info_get_name(info);
			//garquivo = g_file_get_child(gdiretorio, nome);

			//tempoGArquivo = g_file_info_get_modification_date_time(info);
			//tamanhoGArquivo = g_file_info_get_size(info);

			//if (tipo == G_FILE_TYPE_REGULAR) {}
			//else if (tipo == G_FILE_TYPE_DIRECTORY) {}

		//	if (!g_string_equal(nomeGArquivo, ponto) &&
			//	!g_string_equal(nomeGArquivo, pponto)) {
				nomeGArquivo = Rotinas_concatenar(dir->str, nome);
				lista = ListaString_insere(lista, nomeGArquivo, posicao);
				posicao++;
			//}

			info = g_file_enumerator_next_file(filhos, cancelavel, &erro);
		}
	}

	return lista;
}


wchar_t* Rotinas_charArrayToLPCWSTR(const char* charArray)
{
	int tamanho = (int)strlen(charArray);
	int count = MultiByteToWideChar(CP_ACP, 0, charArray, tamanho, NULL, 0);
	//wchar_t* wString = new wchar_t[4096];
	wchar_t* wString = (wchar_t*)malloc(count);
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, count);
	return wString;
}

gchar** Rotinas_criarArrayDeString(const gchar* texto) {
	int numStrings = 1;
	size_t tamanhoString = strlen(texto) + 1;
	// Aloca memória para o array de ponteiros
	gchar** array = g_malloc(numStrings * sizeof(gchar*));

	// Aloca memória para cada string
	int i = 0;
	//for (int i = 0; i < numStrings; i++) {
		array[i] = g_malloc(tamanhoString * sizeof(gchar));
		//sprintf_s(array[i], tamanhoString, "%s", texto);
		g_snprintf(array[i], (gulong)tamanhoString, "%s", texto);
	//}

	return array;
}

void Rotinas_testar() {
	GString *saida = g_string_new("");
	GString *sApp = Rotinas_AppDirPath();
	GString *sDir = g_string_new("    c:\\ago%ra\\CAMINHO\\teste.olha.depois    ");

	//GCancellable *cancelavel = NULL;
	//GError *erro = NULL;
	//GFile *garquivo;
	//GInputStream *gis;
	//GFileInputStream *fis;
	//GDataInputStream *dis;
	GdkPixbuf * pixbuf = NULL;
	//gsize bytesLidos = 0;

	void *blob = NULL;
	GString *sImgArq = g_string_new("cdprata.bmp");
	size_t ntamanho = Rotinas_BlobLoadFromFile(sImgArq, &blob);

	pixbuf = Rotinas_extrairPixbufArquivo(argumentos.texto, 32);
	if (pixbuf != NULL) {
		//OutputDebugString("Rotinas_extrairPixbufArquivo OK");
		printf("%s\n", "Rotinas_extrairPixbufArquivo OK");

		if (Rotinas_PixbufToArquivo(pixbuf, "cdprata.bmp", Rotinas_EXTENSAO_BMP)) {
			//OutputDebugString("Rotinas_PixbufToArquivo OK");
			printf("%s\n", "Rotinas_PixbufToArquivo OK");
		}
	}

	pixbuf = Rotinas_BlobToPixbuf(blob, ntamanho);
	if (pixbuf != NULL){
		//OutputDebugString("Rotinas_BlobToPixbuf OK");
		printf("%s\n", "Rotinas_BlobToPixbuf OK");

		blob = NULL;
		gsize ntamanho2 = Rotinas_PixbufToBlob(pixbuf, &blob, Rotinas_EXTENSAO_BMP);
		if (ntamanho2 > 0 && blob != NULL) {
			//OutputDebugString("Rotinas_PixbufToBlob OK");
			printf("%s\n", "Rotinas_PixbufToBlob OK");
		}

		if (Rotinas_PixbufToArquivo(pixbuf, "cdprata.bmp", Rotinas_EXTENSAO_BMP)) {
			//OutputDebugString("Rotinas_PixbufToArquivo OK");
			printf("%s\n", "Rotinas_PixbufToArquivo OK");
		}
	}
	//gdk_pixbuf_unref(pixbuf);
	g_object_unref(pixbuf);
	pixbuf = NULL;



	pixbuf = Rotinas_imagemToPixbuf("diretorio.bmp");
	if (pixbuf != NULL) {
		//OutputDebugString("Rotinas_imagemToPixbuf OK");
		printf("%s\n", "Rotinas_imagemToPixbuf OK");

		if (Rotinas_PixbufToArquivo(pixbuf, "cdprata.gif", Rotinas_EXTENSAO_GIF)) {
			//OutputDebugString("Rotinas_PixbufToArquivo OK");
			printf("%s\n", "Rotinas_PixbufToArquivo OK");
		}
	}
	//gdk_pixbuf_unref(pixbuf);
	g_object_unref(pixbuf);
	pixbuf = NULL;

	pixbuf = Rotinas_ArquivoToPixbuf(sImgArq->str);
	if (pixbuf != NULL) {
		//OutputDebugString("Rotinas_ArquivoToPixbuf OK");
		printf("%s\n", "Rotinas_ArquivoToPixbuf OK");

		if (Rotinas_PixbufToArquivo(pixbuf, "cdprata.jpg", Rotinas_EXTENSAO_JPEG)) {
			//OutputDebugString("Rotinas_PixbufToArquivo OK");
			printf("%s\n", "Rotinas_PixbufToArquivo OK");
		}
	}
	//gdk_pixbuf_unref(pixbuf);
	g_object_unref(pixbuf);
	pixbuf = NULL;





	/*
	guchar *buffer = Rotinas_cNewStr(16 * 1024);//[16 * 1024];
	buffer[0] = '\0';
	buffer = blob;
	buffer[ntamanho] = '\0';

	//int tam = strlen(&buffer);
	int stride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, 16);
	pixbuf = gdk_pixbuf_new_from_data(buffer, GDK_COLORSPACE_RGB, FALSE, 8, 16, 16, stride, NULL, NULL);
	if (!gdk_pixbuf_save(pixbuf, "c:\\andarDIR\\HFSGuardaDiretorio_Gtk2_C-vs2015\\HFSGuardaDiretorio\\Debug\\imagens\\diretorio.png",
		"png", &erro, NULL)) {
		//"jpeg", &erro, "quality", "100", NULL)) {
		OutputDebugString(erro->message);
	}


	garquivo = g_file_new_for_path(sImgArq->str);
	if (garquivo != NULL) {
		fis = g_file_read(garquivo, cancelavel, &erro);
		gis = (GInputStream *)fis;

		pixbuf = gdk_pixbuf_new_from_stream(gis, cancelavel, &erro);

		if (!gdk_pixbuf_save(pixbuf, "c:\\andarDIR\\HFSGuardaDiretorio_Gtk2_C-vs2015\\HFSGuardaDiretorio\\Debug\\imagens\\diretorio.png",
			"png", &erro, NULL)) {
			//"jpeg", &erro, "quality", "100", NULL)) {
			OutputDebugString(erro->message);
		}

		g_object_unref(fis);
	}
	g_object_unref(garquivo);




	GSList *formats = gdk_pixbuf_get_formats();
	GSList *writable_formats = NULL;
	g_slist_foreach (formats, add_if_writable, &writable_formats);
	g_slist_free (formats);

	gchar *contents;
	gchar *contents_encode;
	gsize length;
	g_file_get_contents ("/home/hughsie/.color/icc/L225W.icm", &contents, &length, NULL);
	contents_encode = g_base64_encode ((const guchar *) contents, length);
	gdk_pixbuf_save (pixbuf, handle, "png", &error, "icc-profile", contents_encode, NULL);

	GError *erro = NULL;

	GtkWidget *wimg = gtk_image_new_from_file("C:/andarDIR/HFSGuardaDiretorio_Gtk2_C-vs2015/HFSGuardaDiretorio/Debug/imagens/diretorio.gif");

	GtkImage *img = GTK_IMAGE(wimg);

	if (img != NULL) {
		GtkImageType tipo = gtk_image_get_storage_type(img);

		switch (tipo)
		{
		case GTK_IMAGE_EMPTY: {OutputDebugString("GTK_IMAGE_EMPTY"); } break;
		case GTK_IMAGE_PIXMAP: {OutputDebugString("GTK_IMAGE_PIXMAP"); } break;
		case GTK_IMAGE_IMAGE: {OutputDebugString("GTK_IMAGE_IMAGE"); } break;
		case GTK_IMAGE_PIXBUF: {OutputDebugString("GTK_IMAGE_PIXBUF"); } break;
		case GTK_IMAGE_STOCK: {OutputDebugString("GTK_IMAGE_STOCK"); } break;
		case GTK_IMAGE_ICON_SET: {OutputDebugString("GTK_IMAGE_ICON_SET"); } break;
		case GTK_IMAGE_ANIMATION: {OutputDebugString("GTK_IMAGE_ANIMATION"); } break;
		case GTK_IMAGE_ICON_NAME: {OutputDebugString("GTK_IMAGE_ICON_NAME"); } break;
		case GTK_IMAGE_GICON: {OutputDebugString("GTK_IMAGE_GICON"); } break;
		default:
			break;
		}

		//gint psize = gtk_image_get_pixel_size(img);
		//if (psize == -1) {
			//GdkPixbuf *pixbuf = gtk_image_get_pixbuf(img);

			GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("C:/andarDIR/HFSGuardaDiretorio_Gtk2_C-vs2015/HFSGuardaDiretorio/Debug/imagens/diretorio.gif", &erro);


			guchar *pixels = gdk_pixbuf_get_pixels(pixbuf);
			int width = gdk_pixbuf_get_width(pixbuf);


			//GdkPixbuf* pxb = gdk_pixbuf_new_from_xpm_data(XPM_DIRETORIO);
			//pixels = gdk_pixbuf_get_pixels(pxb);
			//width = gdk_pixbuf_get_width(pxb);

			if (!gdk_pixbuf_save(pixbuf, "c:\\andarDIR\\HFSGuardaDiretorio_Gtk2_C-vs2015\\HFSGuardaDiretorio\\Debug\\imagens\\diretorio.png",
				"png", &erro, NULL)) {
				//"jpeg", &erro, "quality", "100", NULL)) {
				OutputDebugString(erro->message);
			}

			if (erro != NULL) {
				OutputDebugString(erro->message);
			}
			g_error_free(erro);
		//}

	}


	*/
	ListaString listaDir = Rotinas_cListarArquivosDiretorios("c:\\VM");
	//ListaString listaDir = Rotinas_listarArquivosDiretorios(g_string_new("c:\\VM"));
	//GSList *listaDir = gdk_pixbuf_get_formats();

	guint tamlistaDir = ListaString_conta(listaDir);
	GString* linhaDir = g_string_new("");
	for (unsigned int i = 0; i < tamlistaDir; i++)
	{
		linhaDir = ListaString_pesquisaItemOrd(listaDir, i);

		Arquivo arq = Rotinas_FileInfoToArquivo(linhaDir);

		g_string_printf(saida, "cListarArquivosDiretorios[%d]: %s, %s\n", i, linhaDir->str, arq->nome->str);
		//g_string_printf(saida, "cListarArquivosDiretorios[%d]: %s\n", i, linhaDir->str);
		//OutputDebugString(saida->str);
		printf("%s\n", saida->str);
	}

	ListaString local;
	unsigned int i = 0;
	listaDir = ListaString_inverter(listaDir);
	tamlistaDir = ListaString_conta(listaDir);
	for (local = listaDir; local != NULL; local = local->next) {
		linhaDir = local->data;

		g_string_printf(saida, "cListarArquivosDiretorios[%d]: %s\n", i, linhaDir->str);
		//OutputDebugString(saida->str);
		printf("%s\n", saida->str);
		i++;
	}

	GString* item = g_string_new("wxWidgets-3.0.2.7z");

	if (ListaString_pesquisaItem(listaDir, item)) {
		ListaString_removeItem(&listaDir, item);
		tamlistaDir = ListaString_conta(listaDir);
		ListaString_removeItemOrd(&listaDir, tamlistaDir-1);
		ListaString_removeTodos(&listaDir);
		tamlistaDir = ListaString_conta(listaDir);
		ListaString_libera(&listaDir);
	}



	g_string_printf(saida, "sDir: [%s]\n", sDir->str); printf("%s\n", saida->str); //OutputDebugString(saida->str);
	g_string_printf(saida, "AppDirPath: %s\n", sApp->str); printf("%s\n", saida->str); //OutputDebugString(saida->str);
	g_string_printf(saida, "FileExists: %s\n", (Rotinas_FileExists(sApp) ? "true" : "false")); printf("%s\n", saida->str); //OutputDebugString(saida->str);
	g_string_printf(saida, "DirectoryExists: %s\n", (Rotinas_DirectoryExists(sApp) ? "true" : "false")); printf("%s\n", saida->str); //OutputDebugString(saida->str);
	g_string_printf(saida, "ExtractFilePath: %s\n", Rotinas_ExtractFilePath(sApp)->str); printf("%s\n", saida->str); //OutputDebugString(saida->str);
	g_string_printf(saida, "ExtractFileName: %s\n", Rotinas_ExtractFileName(sApp)->str); printf("%s\n", saida->str); //OutputDebugString(saida->str);

	g_string_printf(saida, "Length(): %lu\n", (long unsigned int)sDir->len); printf("%s\n", saida->str); //OutputDebugString(saida->str);
	GString *sTrim = Rotinas_Trim(sDir);
	g_string_printf(saida, "Trim(): [%s]\n", sTrim->str); printf("%s\n", saida->str); //OutputDebugString(saida->str);
	g_string_printf(saida, "tamanho Trim(): %lu\n", (long unsigned int)sTrim->len); printf("%s\n", saida->str); //OutputDebugString(saida->str);
	g_string_printf(saida, "LowerCase(): %s\n", Rotinas_LowerCase(sDir)->str); printf("%s\n", saida->str); //OutputDebugString(saida->str);
	g_string_printf(saida, "UpperCase(): %s\n", Rotinas_UpperCase(sDir)->str); printf("%s\n", saida->str); //OutputDebugString(saida->str);
	g_string_printf(saida, "Pos('.'): %d\n", Rotinas_Pos(g_string_new("."), sDir)); printf("%s\n", saida->str); //OutputDebugString(saida->str);
	g_string_printf(saida, "LastDelimiter('.'): %d\n", Rotinas_LastDelimiter(g_string_new("."), sDir)); printf("%s\n", saida->str); //OutputDebugString(saida->str);
	g_string_printf(saida, "QuotedStr(): %s\n", Rotinas_cQuotedStr(sDir->str)); printf("%s\n", saida->str); //OutputDebugString(saida->str);
	g_string_printf(saida, "IntToStr(245789): %s\n", Rotinas_IntToStr(245789)->str); printf("%s\n", saida->str); //OutputDebugString(saida->str);
	g_string_printf(saida, "StrToInt() --> 245789: %d\n", Rotinas_StrToInt(g_string_new("245789"))); printf("%s\n", saida->str); //OutputDebugString(saida->str);
	g_string_printf(saida, "StrToLong() --> 4200155136: %lu\n", (long unsigned int)Rotinas_StrToLong(g_string_new("4200155136"))); printf("%s\n", saida->str); //OutputDebugString(saida->str);
	g_string_printf(saida, "DoubleToStr(15.557878): %s\n", Rotinas_DoubleToStr(15.557878)->str); printf("%s\n", saida->str); //OutputDebugString(saida->str);

	g_string_printf(saida, "SubString(): %s\n", Rotinas_SubString(sDir, 8, 6)->str); printf("%s\n", saida->str); //OutputDebugString(saida->str);
	g_string_printf(saida, "cStringReplaceAll(): [%s]\n", Rotinas_cReplaceAll(sDir->str, "\\", "@")); printf("%s\n", saida->str); //OutputDebugString(saida->str);
	g_string_printf(saida, "trocaSeparador(): [%s]\n", Rotinas_trocaSeparador(sDir)->str); printf("%s\n", saida->str); //OutputDebugString(saida->str);
	g_string_printf(saida, "testaNull(NULL): %s\n", Rotinas_testaNull(NULL)->str); printf("%s\n", saida->str); //OutputDebugString(saida->str);

	g_string_printf(saida, "StartsStr(DVD, JOGOS2_DVDS/TESTE): %s\n", (Rotinas_StartsStr(g_string_new("DVD"), g_string_new("JOGOS2_DVDS/TESTE")) ? "true" : "false")); printf("%s\n", saida->str); //OutputDebugString(saida->str);
	g_string_printf(saida, "StartsStr(DVD, DVDSJOGOS2_/TESTE): %s\n", (Rotinas_StartsStr(g_string_new("DVD"), g_string_new("DVDSJOGOS2_/TESTE")) ? "true" : "false")); printf("%s\n", saida->str); //OutputDebugString(saida->str);

	g_string_printf(saida, "ContainsStr(JOGOS2_DVDS/TESTE): %s\n", (Rotinas_ContainsStr(g_string_new("DVDSJOGOS2_/TESTE"), g_string_new("DVDSJOGOS2_/TESTE")) ? "true" : "false")); printf("%s\n", saida->str); //OutputDebugString(saida->str);
	g_string_printf(saida, "EndsStr(TESTE, JOGOS2_DVDS/TESTE): %s\n", (Rotinas_EndsStr(g_string_new("TESTE"), g_string_new("DVDSJOGOS2_/TESTE")) ? "true" : "false")); printf("%s\n", saida->str); //OutputDebugString(saida->str);

	g_string_printf(saida, "formataDate(): %s\n", Rotinas_formataDate(Rotinas_FORMATO_DATAHORA, g_date_time_new_now_local())->str); printf("%s\n", saida->str); //OutputDebugString(saida->str);
	GDateTime* dt = Rotinas_StringToDate(g_string_new("03/02/2017 15:23:32"));
	g_string_printf(saida, "StringToDate(03/02/2017 15:23:32): %s\n", g_date_time_format(dt, Rotinas_FORMATO_DATAHORA)); printf("%s\n", saida->str); //OutputDebugString(saida->str);

	g_string_printf(saida, "FormatLong(4200155136): %s\n", Rotinas_ULongToStr(4200155136)->str); printf("%s\n", saida->str); //OutputDebugString(saida->str);
	g_string_printf(saida, "FormatDouble(15.544878): %s\n", Rotinas_DoubleToStr(15.544878)->str); printf("%s\n", saida->str); //OutputDebugString(saida->str);
	g_string_printf(saida, "FormatDouble(15.547878): %s\n", Rotinas_DoubleToStr(15.547878)->str); printf("%s\n", saida->str); //OutputDebugString(saida->str);
	g_string_printf(saida, "FormatDouble(15.557878): %s\n", Rotinas_DoubleToStr(15.557878)->str); printf("%s\n", saida->str); //OutputDebugString(saida->str);
	g_string_printf(saida, "FormatDouble(15.567878): %s\n", Rotinas_DoubleToStr(15.567878)->str); printf("%s\n", saida->str); //OutputDebugString(saida->str);

	g_string_printf(saida, "MontaTamanho() --> 3.91 GB: %s\n", Rotinas_MontaTamanho(4200155136)->str); printf("%s\n", saida->str); //OutputDebugString(saida->str);
	g_string_printf(saida, "MontaTamanho() --> 3.50 GB: %s\n", Rotinas_MontaTamanho(3757244416)->str); printf("%s\n", saida->str); //OutputDebugString(saida->str);
	g_string_printf(saida, "MontaTamanho() --> 2.29 GB: %s\n", Rotinas_MontaTamanho(2455207936)->str); printf("%s\n", saida->str); //OutputDebugString(saida->str);
	g_string_printf(saida, "MontaTamanho() --> 888.18 PB: %s\n", Rotinas_MontaTamanhoBig(999999999999999999.9999)->str); printf("%s\n", saida->str); //OutputDebugString(saida->str);

	ListaString lista;
	GString* linha = g_string_new("");

	lista = Rotinas_SListSeparador(sDir, '\\');

	guint tamlista = ListaString_conta(lista);

	for (unsigned int i = 0; i < tamlista; i++)
	{
		linha = ListaString_pesquisaItemOrd(lista, i);
		g_string_printf(saida, "SListSeparador[%d]: %s\n", i, linha->str); printf("%s\n", saida->str); //OutputDebugString(saida->str);
	}

	GString* arquivo = Rotinas_ExtractFilePath(sApp);
	arquivo = g_string_append(arquivo, "\\exemplo.txt");

	g_string_printf(saida, "arquivo: %s\n", arquivo->str); printf("%s\n", saida->str); //OutputDebugString(saida->str);

	if (Rotinas_SListSaveToFile(lista, arquivo)) {

		if (Rotinas_FileExists(arquivo)) {

			lista = Rotinas_SListLoadFromFile(arquivo);
			tamlista = ListaString_conta(lista);

			for (unsigned int i = 0; i < tamlista; i++) {
				linha = ListaString_pesquisaItemOrd(lista, i);
				g_string_printf(saida, "SListLoadFromFile[%d]: %s\n", i, linha->str); printf("%s\n", saida->str); //OutputDebugString(saida->str);
			}

			if (Rotinas_DeleteFromFile(arquivo)) {
				if (!Rotinas_FileExists(arquivo)) {
					g_string_printf(saida, "DeleteFromFile: OK\n"); printf("%s\n", saida->str); //OutputDebugString(saida->str);
				}
			}
			else {
				g_string_printf(saida, "DeleteFromFile: FALHOU\n"); printf("%s\n", saida->str); //OutputDebugString(saida->str);
			}

		}

	}

}

