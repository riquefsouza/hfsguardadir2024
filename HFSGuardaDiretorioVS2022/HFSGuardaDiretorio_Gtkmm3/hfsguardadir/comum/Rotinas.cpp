#include "Rotinas.h"

#include <io.h>
#include "dirent.h"

#include <functional>
#include <clocale>

namespace hfsguardadir {

namespace comum {

// ---------------------------------------------------------------------------
Rotinas* Rotinas::instancia = NULL;
Argumento Rotinas::argumentos;

const Glib::ustring Rotinas::HFSGUARDADIR = "HFSGuardaDir";
const Glib::ustring Rotinas::BARRA_NORMAL = "\\";
const Glib::ustring Rotinas::BARRA_INVERTIDA = "/";
const Glib::ustring Rotinas::FORMATO_DATA = "%d/%m/%Y";
const Glib::ustring Rotinas::FORMATO_HORA = "%H:%M:%S";
const Glib::ustring Rotinas::FORMATO_DATAHORA = "%d/%m/%Y %H:%M:%S";
const Glib::ustring Rotinas::FORMATO_DHARQUIVO = "%Y-%m-%d_%H_%M_%S";
const Glib::ustring Rotinas::EXTENSAO_BMP = "bmp";
const Glib::ustring Rotinas::EXTENSAO_ICO = "ico";
const Glib::ustring Rotinas::EXTENSAO_GIF = "gif";
const Glib::ustring Rotinas::EXTENSAO_JPEG = "jpeg";
const Glib::ustring Rotinas::EXTENSAO_PNG = "png";
const Glib::ustring Rotinas::EXTENSAO_TIFF = "tiff";

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
void Rotinas::MsgDlg(Glib::ustring sMensagem, 
	Glib::ustring sTitulo, Gtk::MessageType tipo) {

  Gtk::MessageDialog dialog(retUTF8(sMensagem), false,
   tipo, Gtk::BUTTONS_OK, true);
  dialog.set_title(sTitulo);
  dialog.set_position(Gtk::WIN_POS_CENTER);
  //dialog.set_has_separator(false);
  dialog.run();
}

Glib::ustring Rotinas::retLocale(Glib::ustring sTexto) {
  //return Glib::locale_from_utf8(sTexto);
	return sTexto;
}

Glib::ustring Rotinas::retUTF8(Glib::ustring sTexto) {
  //return Glib::locale_to_utf8(sTexto);
	return sTexto;
}

Glib::ustring Rotinas::retUTF8(char* sTexto) {
	//if (sTexto == NULL)
		//return "";
	//else 
		//return Glib::locale_to_utf8(sTexto);	
	return sTexto;
}

double Rotinas::calculaProgresso(int nMaximo, int nProgresso) {
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


// ---------------------------------------------------------------------------

sqlite3* Rotinas::getConexao() {
	return dbConexao;
}

bool Rotinas::BancoConectar(const Glib::ustring &sFonteDeDados)
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

	OutputDebugString(CharToWChar(sErro));
	MsgDlg(sErro, "Banco Mostrar Erro", Gtk::MESSAGE_ERROR);
}

int Rotinas::BancoExec(const Glib::ustring &sSQL)
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
	size_t numCharsConvertidos;

	if (tamanho > 0) {
		//std::setlocale(LC_ALL, "pt_BR.utf8");
		//std::wcstombs(destino, origem, TAM_MAX_STR);
		wcstombs_s(&numCharsConvertidos, destino, TAM_MAX_STR, origem, TAM_MAX_STR);
	}
	return destino;
}

wchar_t* Rotinas::CharToWChar(const char* origem)
{
	wchar_t* destino = new wchar_t[TAM_MAX_STR];
	destino[0] = '\0';
	int tamanho = strlen(origem);
	size_t numCharsConvertidos;

	if (tamanho > 0) {
		//std::setlocale(LC_ALL, "pt_BR.utf8");
		//std::mbstowcs_s(destino, origem, TAM_MAX_STR);
		mbstowcs_s(&numCharsConvertidos, destino, TAM_MAX_STR, origem, TAM_MAX_STR);
	}
	return destino;
}

std::string Rotinas::WStringToString(const std::wstring &origem)
{
	std::string destino;
	destino.assign(origem.begin(), origem.end());
	return destino;
}

std::wstring Rotinas::StringToWString(const std::string &origem)
{
	std::wstring destino;
	destino.assign(origem.begin(), origem.end());
	return destino;
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
		std::not1(std::ptr_fun<int, int>(std::isspace))));
	return stexto;
}

std::string Rotinas::TrimRight(const std::string &texto)
{
	std::string stexto = texto;

	stexto.erase(std::find_if(stexto.rbegin(), stexto.rend(),
		std::not1(std::ptr_fun<int, int>(std::isspace))).base(), stexto.end());

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

Glib::ustring Rotinas::formataDate(const Glib::ustring formato, const GDateTime* dt) {
	gchar* temp;
	Glib::ustring ds;

	temp = g_date_time_format((GDateTime*)dt, formato.c_str());
	ds = temp;

	return ds;
}

GDateTime* Rotinas::StringToDate(const Glib::ustring &sData) {
	GDateTime* data = NULL;
	gint pos1 = 0, pos2 = 0, ano = 0, mes = 0, dia = 0, hora = 0, minuto = 0;
	gdouble segundos = 0;
	Glib::ustring sdh = Trim(sData);
	Glib::ustring parte, texto = sdh;

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

guint64 Rotinas::StrToLong(const std::string &texto) {
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

gdouble Rotinas::StrToDouble(const std::string &texto) {
	char* temp;
	double	valor = strtod(texto.c_str(), &temp);
	return valor;
}


Glib::ustring Rotinas::MontaTamanhoBig(long double nTam) {
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

Glib::ustring Rotinas::MontaTamanho(long long nTam) {
	if (nTam > 0) {
		return MontaTamanhoBig((long double)nTam);
	}
	else {
		return "";
	}
}

Glib::ustring Rotinas::testaNull(char *res) {
	return (res == NULL ? "" : Trim(res));
}

Glib::ustring Rotinas::trocaSeparador(const Glib::ustring &texto) {
	std::string txt = texto;
	if (texto.length() > 0) {
		txt = ReplaceAll(texto, BARRA_NORMAL, BARRA_INVERTIDA);
	}
	return txt;
}

bool Rotinas::testaSeparadorArquivo(const Glib::ustring &sDir) {
	Glib::ustring sdir = SubString(sDir, sDir.length(), 1);
	if (sdir == BARRA_INVERTIDA	|| sdir == BARRA_NORMAL) {
		return true;
	}
	else {
		return false;
	}
}

std::string Rotinas::ExtractFilePath(const std::string &sCaminho) {
	//return Glib::path_get_dirname(sCaminho);

	std::string retorno = sCaminho;

	const size_t indice = retorno.find_last_of("\\/");
	if (std::string::npos != indice)
	{
		retorno.erase(indice + 1, retorno.length());
	}

	return retorno;
}

std::string Rotinas::ExtractFileName(const std::string &sCaminho) {
	//return Glib::path_get_basename(sCaminho);

	std::string retorno = sCaminho;

	const size_t indice = retorno.find_last_of("\\/");
	if (std::string::npos != indice)
	{
		retorno.erase(0, indice + 1);
	}

	return retorno;
}

bool Rotinas::FileExists(const Glib::ustring &sNomeArquivo) {
	struct stat fileInfo;

	if (_access(sNomeArquivo.c_str(), 0) == 0) {
		stat(sNomeArquivo.c_str(), &fileInfo);

		if ((fileInfo.st_mode & S_IFMT) == S_IFDIR)
			return false; //diretorio
		else
			return true; //arquivo
	}

	return false;
	
	//return Glib::file_test(sNomeArquivo, Glib::FileTest::FILE_TEST_EXISTS);
}

bool Rotinas::DirectoryExists(const Glib::ustring &sNomeArquivo) {
	struct stat fileInfo;

	if (_access(sNomeArquivo.c_str(), 0) == 0) {
		stat(sNomeArquivo.c_str(), &fileInfo);

		if ((fileInfo.st_mode & S_IFMT) == S_IFDIR)
			return true; //diretorio
		else
			return false; //arquivo
	}

	return false;


	//return Glib::file_test(sNomeArquivo, Glib::FileTest::FILE_TEST_EXISTS & 
		//Glib::FileTest::FILE_TEST_IS_DIR);
}

bool Rotinas::DeleteFromFile(const Glib::ustring &sNomeArquivo) {
	return (std::remove(sNomeArquivo.c_str()) == 0);
}

Glib::ustring Rotinas::getRecurso(const char* chave) {
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
	if (chave == "TipoLista.diretorio") return retUTF8("Diretório");

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
	if (chave == "FrmCompararDiretorio.barraStatus1") return retUTF8("Total de diferenças encontradas:");
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

std::vector<Glib::ustring> Rotinas::cListarArquivosDiretorios(const Glib::ustring &sDiretorio) {
	std::vector<Glib::ustring> lista;
	Glib::ustring nome, dir = sDiretorio;
	Glib::ustring ponto = ".";
	Glib::ustring pponto = "..";
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

Arquivo Rotinas::FileInfoToArquivo2(const Glib::ustring &sCaminho) {
	Arquivo arq;
	Glib::RefPtr<Gio::FileInfo> info;
	Glib::RefPtr<Gio::File> garquivo;
	Gio::FileType tipo;
	std::string nome;
	Glib::TimeVal tempoGArquivo;
	GDateTime* gdatahora;
	goffset tamanhoGArquivo;
	Glib::ustring atributos = "";
	//GIcon* icone;
	
	garquivo = Gio::File::create_for_path(sCaminho);

	if (garquivo != NULL) {
		info = garquivo->query_info("*", Gio::FILE_QUERY_INFO_NOFOLLOW_SYMLINKS);

		tipo = info->get_file_type();
		//nome = info->get_name();
		nome = ExtractFileName(sCaminho);

		tempoGArquivo = info->modification_time();
		tamanhoGArquivo = info->get_size();

		//icone = info->get_icon();
		//char** lista = info->list_attributes(NULL);
		//char* item = lista[0];

		arq.setNome(nome);
		arq.setTamanho(tamanhoGArquivo);
		
		gdatahora = g_date_time_new_from_timeval_local(&tempoGArquivo);
		//arq.setModificado(DateTime(gdatahora));
		arq.setModificado(gdatahora);

		//"[ROL]" e "[SYS]"

		if (info->is_hidden()) {
			atributos += "[HID]";
		}
		if (tipo == G_FILE_TYPE_DIRECTORY) {
			atributos += "[DIR]";
		}
		if (tipo == G_FILE_TYPE_REGULAR) {
			atributos += "[ARQ]";
		}

		arq.setAtributos(atributos);
	}

	return arq;
}

Arquivo Rotinas::FileInfoToArquivo(const std::string &sNomeArquivo) {
	struct stat fileInfo;
	GDateTime* gdatahora;
	std::string sAtributos = "";
	Arquivo arquivo;

	arquivo.setNome(ExtractFileName(sNomeArquivo));

	if (_access(sNomeArquivo.c_str(), 0) == 0) {
		stat(sNomeArquivo.c_str(), &fileInfo);

		gdatahora = RawToDataHora(fileInfo.st_mtime);

				
		if ((fileInfo.st_mode & S_IFMT) == S_IFDIR)
			sAtributos += "[DIR]";
		else
			sAtributos += "[ARQ]";

		//S_IREAD S_IWRITE			
		if ((fileInfo.st_mode & S_IFMT) != S_IWUSR) {
			sAtributos += "[ROL]";
		}

		arquivo.setTamanho(fileInfo.st_size);
		arquivo.setModificado(gdatahora);
		arquivo.setAtributos(sAtributos);
	}
	else {
		arquivo.setTamanho(0);
		arquivo.setModificado(DataHoraNow());
		arquivo.setAtributos("");
	}

	return arquivo;
}

bool Rotinas::SListSaveToFile(const std::vector<Glib::ustring> lista, const Glib::ustring &sNomeArquivo) {
	bool ret = false;
	Glib::RefPtr<Gio::File> garquivo;
	Glib::RefPtr<Gio::OutputStream> gos;
	Glib::RefPtr<Gio::FileOutputStream> fos;
	gsize bytesEscritos = 0;

	Glib::ustring linha = "";
	Glib::ustring conteudo = "";
	guint tamlista = lista.size();

	if (tamlista > 0) {

		for (unsigned int i = 0; i < tamlista; i++) {
			linha = lista.at(i);
			conteudo += linha + "\n";
		}

		if (conteudo.length() > 0) {
			garquivo = Gio::File::create_for_path(sNomeArquivo);

			fos = garquivo->append_to(Gio::FILE_CREATE_NONE);
			gos = (Glib::RefPtr<Gio::OutputStream>)fos;
			gos->write_all(conteudo, bytesEscritos);
			gos->close();

			ret = true;
		}

	}

	return ret;
}

std::vector<Glib::ustring> Rotinas::SListLoadFromFile(const Glib::ustring &sNomeArquivo) {
	Glib::RefPtr<Gio::File> garquivo;
	Glib::RefPtr<Gio::InputStream> gis;
	Glib::RefPtr<Gio::FileInputStream> fis;
	Glib::RefPtr<Gio::FileInfo> info;
	gsize tamArquivo;
	gsize tamtexto;
	gsize bytesLidos = 0;
	std::vector<Glib::ustring> lista;
	Glib::ustring pedaco, substr;
	Glib::ustring linha = "";
	gchar *texto;

	garquivo = Gio::File::create_for_path(sNomeArquivo);
	info = garquivo->query_info("*", Gio::FILE_QUERY_INFO_NOFOLLOW_SYMLINKS);

	if (info != NULL) {
		tamArquivo = (gsize)info->get_size();

		texto = NewStr(tamArquivo);
		texto[0] = '\0';

		fis = garquivo->read();
		gis = (Glib::RefPtr<Gio::InputStream>)fis;
		gis->read_all(texto, tamArquivo, bytesLidos);
		gis->close();

		if (bytesLidos > 0) {
			pedaco = "";
			tamtexto = strlen(texto);
			for (unsigned int i = 0; i < tamtexto; i++) {
				pedaco += texto[i];
				if (texto[i] == '\n') {
					substr = SubString(pedaco, 1, pedaco.length() - 1);
					lista.push_back(substr);
					pedaco = "";
				}
			}
		}

		delete texto;
	}

	return lista;
}

std::vector<Glib::ustring> Rotinas::SListSeparador(const Glib::ustring &texto, const gchar separador) {
	std::vector<Glib::ustring> lista;
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

Glib::ustring Rotinas::SListTexto(const std::vector<Glib::ustring> lista) {
	Glib::ustring linha = "";
	Glib::ustring texto = "";
	guint ntamlista = lista.size();

	if (ntamlista > 0) {
		for (unsigned int i = 0; i < ntamlista; i++) {
			linha = lista.at(i);
			texto += linha;
		}
	}
	return texto;
}

bool Rotinas::BlobSaveToFile(const void* blob, size_t tamanho, const Glib::ustring &sNomeArquivo) {
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

long Rotinas::BlobLoadFromFile(const Glib::ustring &sNomeArquivo, void** blob) {
	long ret = 0;
	FILE* fp;
	errno_t erro;
	//size_t tamanho = 16 * 1024;
	//char* buffer;

	erro = fopen_s(&fp, sNomeArquivo.c_str(), "rb");

	if (NULL != fp)
	{
		/*
		fseek(fp, 0L, SEEK_END);
		tamanho = ftell(fp);
		//fseek(fp, 0L, SEEK_SET);
		rewind(fp);
		*/

		//buffer = NewStr(tamanho);
		char buffer[16 * 1024];
		buffer[0] = '\0';

		*blob = &buffer;

		size_t ntamanho = fread(*blob, sizeof(char), 16 * 1024, fp);
		buffer[ntamanho] = '\0';
		fclose(fp);

		ret = ntamanho;
	}

	return ret;
}

std::vector<Glib::ustring> Rotinas::listarArquivosDiretorios(const Glib::ustring &sDiretorio) {
	std::vector<Glib::ustring> lista;
	Glib::RefPtr<Gio::File> gdiretorio;
	Glib::RefPtr<Gio::FileEnumerator> filhos;
	Glib::RefPtr<Gio::FileInfo> info;
	Gio::FileType tipo;
	Glib::ustring dir = sDiretorio;
	Glib::ustring nome, nomeGArquivo;
	GTimeVal tempoGArquivo;
	goffset tamanhoGArquivo;

	if (!testaSeparadorArquivo(sDiretorio)) {
		dir += BARRA_INVERTIDA;
	}

	gdiretorio = Gio::File::create_for_path(sDiretorio);

	filhos = gdiretorio->enumerate_children(
		"standard::name, standard::type", 
		Gio::FILE_QUERY_INFO_NOFOLLOW_SYMLINKS);

	if (filhos != NULL) {
		info = filhos->next_file();

		while (info != NULL) {
			tipo = info->get_file_type();
			nome = info->get_name();
			
			tempoGArquivo = info->modification_time();
			tamanhoGArquivo = info->get_size();

			nomeGArquivo = dir + nome;
			lista.push_back(nomeGArquivo);

			info = filhos->next_file();
		}
	}

	return lista;
}

// ---------------------------------------------------------------------------

Glib::RefPtr<Gdk::Pixbuf> Rotinas::XPMToPixbuf(const char** xpm) {
	Glib::RefPtr<Gdk::Pixbuf> pxb = Gdk::Pixbuf::create_from_xpm_data(xpm);
	return pxb;
}

Glib::RefPtr<Gdk::Pixbuf> Rotinas::imagemToPixbuf(const Glib::ustring &sNomeImagem) {
	Glib::RefPtr<Gdk::Pixbuf> pixbuf;

	Glib::ustring caminho = Rotinas::AppDirName();
	caminho += "imagens/" + sNomeImagem;

	pixbuf = Gdk::Pixbuf::create_from_file(caminho);

	return pixbuf;
}

Glib::RefPtr<Gdk::Pixbuf> Rotinas::ArquivoToPixbuf(const Glib::ustring &sArquivo) {
	Glib::RefPtr<Gdk::Pixbuf> pixbuf;

	pixbuf = Gdk::Pixbuf::create_from_file(sArquivo);

	return pixbuf;
}

//formatos = "jpeg", "tiff", "png", "ico" or "bmp"
bool Rotinas::PixbufToArquivo(Glib::RefPtr<Gdk::Pixbuf> pixbuf, 
	const Glib::ustring &sArquivo, const Glib::ustring &formato) {
	bool bSalvou;

	try {
		pixbuf->save(sArquivo, formato);
		//"jpeg", &erro, "quality", "100", NULL)) {
		bSalvou = true;
	}
	//catch (const Glib::FileError&) {
	//	bSalvou = false;
	//}
	catch (const Gdk::PixbufError&) {
		bSalvou = false;
	}

	return bSalvou;
}

Glib::RefPtr<Gdk::Pixbuf> Rotinas::BlobToPixbuf(const void* blob, int tamanho) {
	Glib::RefPtr<Gdk::Pixbuf> pixbuf;
	Glib::RefPtr<Gio::MemoryInputStream> mgis;
	mgis = Gio::MemoryInputStream::create();

	mgis->add_data(blob, tamanho);
	pixbuf = Gdk::Pixbuf::create_from_stream(mgis);
	mgis->close();
	return pixbuf;
}

//formatos = "jpeg", "tiff", "png", "ico" or "bmp"
gsize Rotinas::PixbufToBlob(Glib::RefPtr<Gdk::Pixbuf> pixbuf, void*& blob, const Glib::ustring &formato) {
	GOutputStream *gos = NULL;
	GMemoryOutputStream *gmos = NULL;
	gboolean bSalvou;
	gsize ntamanho = 0;
	try {
		pixbuf->save_to_buffer((gchar*&)blob, ntamanho, formato);
		//"jpeg", &erro, "quality", "100", NULL)) {
		bSalvou = true;
	}
	//catch (const Glib::FileError&) {
	//	bSalvou = false;
	//}
	catch (const Gdk::PixbufError&) {
		bSalvou = false;
	}

	if (bSalvou) {
		return ntamanho;
	}
	return 0;
}

Glib::RefPtr<Gdk::Pixbuf> Rotinas::extrairPixbufArquivo(const Glib::ustring &sCaminho, int tamanho) {
	Glib::RefPtr<Gio::Icon> icone;
	Glib::RefPtr<Gio::File> garquivo;
	Glib::RefPtr<Gio::FileInfo> info;
	Gtk::Image *imagem = NULL;
	Glib::RefPtr<Gdk::Pixbuf> pixbuf, pixbuf2;

	garquivo = Gio::File::create_for_path(sCaminho);
	if (garquivo != NULL) {
		info = garquivo->query_info("*", Gio::FILE_QUERY_INFO_NOFOLLOW_SYMLINKS);

		icone = info->get_icon();
		
		//imagem = new Gtk::Image(icone, Gtk::ICON_SIZE_BUTTON);
		//imagem = GTK_IMAGE(gtk_image_new_from_gicon(icone, GTK_ICON_SIZE_BUTTON));
		//pixbuf = gdk_pixbuf_copy(imagem->data.pixbuf.pixbuf);
		pixbuf = imagem->get_pixbuf();
		pixbuf2 = pixbuf->scale_simple(tamanho, tamanho, Gdk::INTERP_BILINEAR);
		//pixbuf2 = gdk_pixbuf_copy(pixbuf);
	}

	return pixbuf;
}


void Rotinas::testar() {
	char *saida = NewStr();
	std::string sApp = AppDirPath();
	std::string sAppDir = AppDirName();
	std::string sAppFile = AppFileName();

	Glib::ustring sDir = "    c:\\ago%ra\\CAMINHO\\teste.olha.depois    ";
	/*
	Glib::RefPtr<Gdk::Pixbuf> pixbuf;

	void *blob = NULL;
	Glib::ustring sImgArq = "C:/andarDIR/HFSGuardaDiretorio_gtkmm2-vs2015/HFSGuardaDiretorio/Debug/imagens/diretorio.bmp";
	size_t ntamanho = BlobLoadFromFile(sImgArq, &blob);
	*/

	/*
	pixbuf = extrairPixbufArquivo(argumentos.texto, 32);
	if (pixbuf != NULL) {
		OutputDebugString(CharToWChar("extrairPixbufArquivo OK"));

		if (PixbufToArquivo(pixbuf, "C:\\Temp\\blob\\dir32.bmp", EXTENSAO_BMP)) {
			OutputDebugString(CharToWChar("PixbufToArquivo OK"));
		}
	}
	*/
	
	/*
	pixbuf = BlobToPixbuf(blob, ntamanho);
	if (pixbuf != NULL) {
		OutputDebugString(CharToWChar("BlobToPixbuf OK\n"));

		blob = NULL;
		gsize ntamanho2 = PixbufToBlob(pixbuf, blob, EXTENSAO_BMP);
		if (ntamanho2 > 0 && blob != NULL) {
			OutputDebugString(CharToWChar("PixbufToBlob OK\n"));
		}

		if (PixbufToArquivo(pixbuf, "C:\\Temp\\blob\\dir.bmp", EXTENSAO_BMP)) {
			OutputDebugString(CharToWChar("PixbufToArquivo OK\n"));
		}
	}

	pixbuf = imagemToPixbuf("diretorio.bmp");
	if (pixbuf != NULL) {
		OutputDebugString(CharToWChar("imagemToPixbuf OK\n"));

		if (PixbufToArquivo(pixbuf, "C:\\Temp\\blob\\dir.gif", EXTENSAO_GIF)) {
			OutputDebugString(CharToWChar("PixbufToArquivo OK\n"));
		}
	}

	pixbuf = ArquivoToPixbuf(sImgArq);
	if (pixbuf != NULL) {
		OutputDebugString(CharToWChar("ArquivoToPixbuf OK\n"));

		if (PixbufToArquivo(pixbuf, "C:\\Temp\\blob\\dir.jpg", EXTENSAO_JPEG)) {
			OutputDebugString(CharToWChar("PixbufToArquivo OK\n"));
		}
	}
	*/
		
	std::vector<Glib::ustring> listaDir = cListarArquivosDiretorios("c:\\VM");
	//std::vector<Glib::ustring> listaDir = listarArquivosDiretorios("c:\\VM");
	//GSList *listaDir = gdk_pixbuf_get_formats();

	guint tamlistaDir = listaDir.size();
	Glib::ustring linhaDir = "";
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

	std::snprintf(saida, TAM_MAX_STR, "Length(): %d\n", sDir.length()); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "Trim(): [%s]\n", Trim(sDir).c_str()); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "tamanho Trim(): %d\n", Trim(sDir).length()); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "LowerCase(): %s\n", LowerCase(sDir).c_str()); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "UpperCase(): %s\n", UpperCase(sDir).c_str()); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "Pos('.'): %d\n", Pos(".", sDir)); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "LastDelimiter('.'): %d\n", LastDelimiter(".", sDir)); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "QuotedStr(): %s\n", QuotedStr(sDir).c_str()); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "IntToStr(245789): %s\n", IntToStr(245789).c_str()); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "StrToInt() --> 245789: %d\n", StrToInt("245789")); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "StrToLong() --> 4200155136: %llu\n", StrToLong("4200155136")); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "DoubleToStr(15.557878): %s\n", DoubleToStr(15.557878).c_str()); OutputDebugString(CharToWChar(saida));

	std::snprintf(saida, TAM_MAX_STR, "SubString(): %s\n", SubString(sDir, 8, 6).c_str()); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "ReplaceAll(): [%s]\n", ReplaceAll(sDir, "\\", "@").c_str()); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "trocaSeparador(): [%s]\n", trocaSeparador(sDir).c_str()); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "testaNull(NULL): %s\n", testaNull(NULL).c_str()); OutputDebugString(CharToWChar(saida));

	std::snprintf(saida, TAM_MAX_STR, "StartsStr(DVD, JOGOS2_DVDS/TESTE): %s\n", (StartsStr("DVD", "JOGOS2_DVDS/TESTE") ? "true" : "false")); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "StartsStr(DVD, DVDSJOGOS2_/TESTE): %s\n", (StartsStr("DVD", "DVDSJOGOS2_/TESTE") ? "true" : "false")); OutputDebugString(CharToWChar(saida));

	std::snprintf(saida, TAM_MAX_STR, "ContainsStr(JOGOS2_DVDS/TESTE): %s\n", (ContainsStr("DVDSJOGOS2_/TESTE", "DVDSJOGOS2_/TESTE") ? "true" : "false")); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "EndsStr(TESTE, JOGOS2_DVDS/TESTE): %s\n", (EndsStr("TESTE", "DVDSJOGOS2_/TESTE") ? "true" : "false")); OutputDebugString(CharToWChar(saida));

	std::snprintf(saida, TAM_MAX_STR, "formataDate(): %s\n", formataDate(FORMATO_DATAHORA, DataHoraNow()).c_str()); OutputDebugString(CharToWChar(saida));
	GDateTime* dt = StringToDate("03/02/2017 15:23:32");
	std::snprintf(saida, TAM_MAX_STR, "StringToDate(03/02/2017 15:23:32): %s\n", formataDate(FORMATO_DATAHORA, dt).c_str()); OutputDebugString(CharToWChar(saida));

	std::snprintf(saida, TAM_MAX_STR, "FormatLong(4200155136): %s\n", ULongToStr(4200155136).c_str()); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "FormatDouble(15.544878): %s\n", DoubleToStr(15.544878).c_str()); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "FormatDouble(15.547878): %s\n", DoubleToStr(15.547878).c_str()); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "FormatDouble(15.557878): %s\n", DoubleToStr(15.557878).c_str()); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "FormatDouble(15.567878): %s\n", DoubleToStr(15.567878).c_str()); OutputDebugString(CharToWChar(saida));

	std::snprintf(saida, TAM_MAX_STR, "MontaTamanho() --> 3.91 GB: %s\n", MontaTamanho(4200155136).c_str()); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "MontaTamanho() --> 3.50 GB: %s\n", MontaTamanho(3757244416).c_str()); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "MontaTamanho() --> 2.29 GB: %s\n", MontaTamanho(2455207936).c_str()); OutputDebugString(CharToWChar(saida));
	std::snprintf(saida, TAM_MAX_STR, "MontaTamanho() --> 888.18 PB: %s\n", MontaTamanhoBig(999999999999999999.9999).c_str()); OutputDebugString(CharToWChar(saida));

	std::vector<Glib::ustring> lista;
	Glib::ustring linha = "";

	lista = SListSeparador(sDir, '\\');

	guint tamlista = lista.size();

	for (unsigned int i = 0; i < tamlista; i++)
	{
		linha = lista.at(i);
		std::snprintf(saida, TAM_MAX_STR, "SListSeparador[%d]: %s\n", i, linha.c_str()); OutputDebugString(CharToWChar(saida));
	}

	std::string arquivo = ExtractFilePath(sApp);
	arquivo += "\\exemplo.txt";

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
