#include "Rotinas.h"

#include "Windows.h"
#include <wx/mstream.h>
#include <wx/stdpaths.h>
#include <wx/dir.h>

using namespace hfsguardadir::objetos;

namespace hfsguardadir {

namespace comum {

Rotinas* Rotinas::instancia = NULL;

const wxString Rotinas::HFSGUARDADIR = "HFSGuardaDir";
const wxString Rotinas::FORMATO_DATA = "%d/%m/%Y";
const wxString Rotinas::FORMATO_HORA = "%H:%M:%S";
const wxString Rotinas::FORMATO_DATAHORA = "%d/%m/%Y %H:%M:%S";
const wxString Rotinas::FORMATO_DHARQUIVO = "%Y-%m-%d_%H_%M_%S";
const wxString Rotinas::EXTENSAO_BMP = "bmp";
const wxString Rotinas::EXTENSAO_ICO = "ico";
const wxString Rotinas::EXTENSAO_GIF = "gif";
const wxString Rotinas::EXTENSAO_JPEG = "jpg";
const wxString Rotinas::EXTENSAO_PNG = "png";
const wxString Rotinas::EXTENSAO_TIFF = "tif";

Rotinas::Rotinas()
{
	arquivoIcone = Rotinas::getImagem("ARQUIVO");
	cdouroIcone = Rotinas::getImagem("CDOURO");
	diretorioIcone = Rotinas::getImagem("DIRETORIO");
	dirabertoIcone = Rotinas::getImagem("DIRABERTO");
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

wxSQLite3Database* Rotinas::getConexao() {
	return &dbConexao;
}

bool Rotinas::Conectar(wxString &banco) {
    ConexaoParams cp;
    cp.setNome(wxString("SQLITE"));
    cp.setUrl(banco);
    return Conectar(cp);
}

bool Rotinas::Conectar(ConexaoParams cp) {

    dbConexao.Open(cp.getUrl());

    if (!dbConexao.IsOpen())
    {
		wxLogDebug("Erro: conexao falhou");
		return false;
    }
    else
    {
		wxLogDebug("Database: conexao ok");
    }

    return true;
}

void Rotinas::Desconectar() {
	dbConexao.Close();
}

bool Rotinas::criarVisao(const wxString &visao) {
    wxString sSQL;

    sSQL = "create view " + visao + " as " \
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

    return execConsulta(sSQL);
}

void Rotinas::mostrarErro(wxSQLite3Exception& excecao, const wxString &titulo) {
	wxLogDebug("ERRO %s: %s", titulo, excecao.GetMessage());
	wxMessageBox(excecao.GetMessage(), titulo, wxOK | wxCENTRE | wxICON_ERROR);
}

bool Rotinas::execConsulta(const wxString &sSQL) {
	wxSQLite3Statement stmt;
	int ret;
	
	try {
		dbConexao.Begin();
		stmt = dbConexao.PrepareStatement(sSQL);
		ret = stmt.ExecuteUpdate();
		dbConexao.Commit();
	}
	catch (wxSQLite3Exception& e) {
		try	{
			dbConexao.Rollback();
			mostrarErro(e, wxT("Rotinas::execConsulta"));
		}
		catch (wxSQLite3Exception& e2) {
			mostrarErro(e2, wxT("Rotinas::execConsulta"));
		}		
	}

	return (ret > 0);
}

wxString Rotinas::AppDirPath() {
	wxString caminho = wxStandardPaths::Get().GetExecutablePath();

	return ExtractFilePath(caminho);
}

wxString Rotinas::Trim(const wxString &texto) {
	wxString stexto = texto;
	return stexto.Trim(true).Trim(false);
}

int Rotinas::LastDelimiter(const wxString &subtexto, const wxString &texto) {
	wxString::size_type loc = texto.find_last_of(subtexto);
	if (loc != wxString::npos)
		return (loc + 1);
	else
		return -1;
}

int Rotinas::LastDelimiter(const wxChar &subtexto, const wxString &texto) {
	wxString::size_type loc = texto.find_last_of(subtexto);
	if (loc != wxString::npos)
		return (loc + 1);
	else
		return -1;
}

int Rotinas::Pos(const wxString &subtexto, const wxString &texto) {
    return texto.Find(subtexto) + 1;
}

int Rotinas::Pos(const wxChar &subtexto, const wxString &texto) {
    return texto.Find(subtexto) + 1;
}

bool Rotinas::StartsStr(const wxString &subtexto, const wxString &texto) {
    return texto.StartsWith(subtexto);
}

bool Rotinas::ContainsStr(const wxString &texto, const wxString &subtexto) {
    return (Pos(subtexto, texto) > 0);
}

bool Rotinas::EndsStr(const wxString &subtexto, const wxString &texto) {
    //return (LastDelimiter(subtexto, texto) > 0);
	return texto.EndsWith(subtexto);
}

wxString Rotinas::SubString(const wxString &texto, int inicio, int tamanho) {
	unsigned int ntam = (inicio + tamanho - 1);

    if (ntam > texto.length()) {
        tamanho = texto.length();
    } else {
        tamanho = ntam;
    }
    return texto.Mid(inicio - 1, tamanho);
}

wxString Rotinas::StringReplaceAll(const wxString &texto, const wxString &velho,
        const wxString &novo){
    wxString txt = texto;
	txt.Replace(velho, novo, true);
    return txt;
}

wxString Rotinas::IntToStr(int valor)
{
	//wxString stexto = wxString::Format(wxT("%i"),valor);
	wxString stexto;
	stexto << valor;
	return stexto;
}

int Rotinas::StrToInt(const wxString &texto)
{
	wxString stexto = texto;
	long nvalor;
	if (stexto.ToLong(&nvalor))
		return nvalor;
	else
		return -1;
}

wxULongLong Rotinas::StrToLong(const wxString &texto)
{
	wxString stexto = texto;
	long long nvalor;
	if (stexto.ToLongLong(&nvalor))
		return nvalor;
	else
		return -1;
}

wxString Rotinas::DoubleToStr(const double valor)
{
	wxString stexto = wxNumberFormatter::ToString(valor, 40,
		wxNumberFormatter::Style_NoTrailingZeroes);
	return stexto;
}

wxString Rotinas::QuotedStr(const wxString &texto){
    return "'" + texto + "'";
}

wxString Rotinas::QuotedStr(const wxChar &texto){
    return "'" + wxString(texto) + "'";
}

wxString Rotinas::formataDate(const wxString &formato, const wxDateTime &dt) {
	wxString ds = "";
	
	if (dt.IsValid()) {
		ds = dt.Format(formato);
	}

    return ds;
}

wxDateTime Rotinas::StringToDate(const wxString &sData) {
    wxDateTime data;
	
    if (Trim(sData).length() > 0) {
		data.ParseDateTime(sData);
    }
    return data;
}

wxString Rotinas::FormatLong(long valor) {
    wxString texto;

    texto = wxString::Format("%lu", valor);
    
    return texto;
}

wxString Rotinas::FormatDouble(long double valor) {
    wxString texto;

    texto = wxString::Format("%4.2Lf", valor);

    return texto;
}

wxString Rotinas::MontaTamanhoBig(long double nTam) {
	long long nUmKilo, nUmMega, nUmGiga, nUmTera, nUmPeta;

	nUmKilo = 1024;
	nUmMega = nUmKilo * nUmKilo;
	nUmGiga = nUmMega * nUmKilo;
	nUmTera = nUmGiga * nUmKilo;
	nUmPeta = nUmTera * nUmKilo;

	if (nTam < nUmKilo) {
		return FormatDouble(nTam) + " Byte(s)";
	}
	else if (nTam > nUmKilo && nTam < nUmMega) {
		nTam = nTam / nUmKilo;
		return FormatDouble(nTam) + " KByte(s)";
	}
	else if (nTam > nUmMega && nTam < nUmGiga) {
		nTam = nTam / nUmMega;
		return FormatDouble(nTam) + " MByte(s)";
	}
	else if (nTam > nUmGiga && nTam < nUmTera) {
		nTam = nTam / nUmGiga;
		return FormatDouble(nTam) + " GByte(s)";
	}
	else if (nTam > nUmTera && nTam < nUmPeta) {
		nTam = nTam / nUmTera;
		return FormatDouble(nTam) + " TByte(s)";
	}
	else {
		nTam = nTam / nUmPeta;
		return FormatDouble(nTam) + " PByte(s)";
	}
}

wxString Rotinas::MontaTamanho(long long nTam) {
	if (nTam > 0) {
		return MontaTamanhoBig(nTam);
	}
	else {
		return "";
	}
}

wxString Rotinas::testaNull(const wxString &res) {
    return (res.empty() ? "" : Trim(res));
}

wxString Rotinas::trocaSeparador(const wxString &texto) {
    wxString txt = texto;
    if (texto.length() > 0) {
        txt.Replace(BARRA_NORMAL, BARRA_INVERTIDA, true);
    }
    return txt;
}

wxString Rotinas::ExtractFilePath(const wxString &sCaminho) {
    wxString retorno;

	wxFileName info(sCaminho);
    retorno = info.GetPath();

    return retorno;
}

wxString Rotinas::ExtractFileName(const wxString &sCaminho) {
    wxString retorno;

	wxFileName info(sCaminho);
	retorno = info.GetFullName();

    return retorno;
}

bool Rotinas::FileExists(const wxString &sNomeArquivo) {
	wxFileName info(sNomeArquivo);
	return info.FileExists();
}

bool Rotinas::DirectoryExists(const wxString &sNomeArquivo) {
	return wxDir::Exists(sNomeArquivo);
}

bool Rotinas::DeleteFromFile(const wxString &sNomeArquivo) {
    return wxRemoveFile(sNomeArquivo);
}

void Rotinas::SaveToFile(wxMemoryBuffer &imagem, const wxString &sNomeArquivo) {
    wxFile file(sNomeArquivo, wxFile::write);
	void* buffer = imagem.GetWriteBuf(imagem.GetBufSize());
	size_t iWrite = file.Write(buffer, imagem.GetBufSize());
	file.Flush();	
	imagem.UngetWriteBuf(iWrite);
	file.Close();
}

wxMemoryBuffer Rotinas::LoadFromFile(const wxString &sNomeArquivo) {
    wxMemoryBuffer imagem;

	wxFile file(sNomeArquivo, wxFile::read);
	wxFileOffset tamFile = file.Length();
	void* buffer = imagem.GetAppendBuf(tamFile);
	size_t iRead = file.Read(buffer, tamFile);
	imagem.UngetAppendBuf(iRead);
    file.Close();

    return imagem;
}

wxString Rotinas::getRecurso(const wxString &chave) {
	if (chave == "HFSGuardaDir.ValidaJavaVersao") return wxT("Esta vers\u00e3o do JAVA n\u00e3o \u00e9 suportada pelo programa.");
	if (chave == "HFSGuardaDir.ErroInicial") return wxT("Ocorreu um erro no aplicativo!");
	if (chave == "HFSGuardaDir.ValidaArquivoConf") return wxT("Arquivo de configura\u00e7\u00e3o n\u00e3o existe!\nAs configura\u00e7\u00f5es padr\u00e3o ser\u00e3o usadas!");

	if (chave == "Tabela.nome") return wxT("Nome");
	if (chave == "Tabela.tamanho") return wxT("Tamanho");
	if (chave == "Tabela.tipo") return wxT("Tipo");
	if (chave == "Tabela.modificado") return wxT("Modificado");
	if (chave == "Tabela.atributos") return wxT("Atributos");
	if (chave == "Tabela.caminho") return wxT("Caminho");
	if (chave == "Tabela.aba") return wxT("Aba");

	if (chave == "Aba.codigo") return wxT("C\u00f3digo:");
	if (chave == "Aba.nome") return wxT("Nome:");

	if (chave == "Tipo.codigo") return wxT("C\u00f3digo:");
	if (chave == "Tipo.nome") return wxT("Nome:");

	if (chave == "TipoLista.arquivo") return wxT("Arquivo");
	if (chave == "TipoLista.diretorio") return wxT("Diret\u00f3rio");

	if (chave == "ConexaoParams.nome") return wxT("Nome:");
	if (chave == "ConexaoParams.driver") return wxT("Driver:");
	if (chave == "ConexaoParams.url") return wxT("URL:");
	if (chave == "ConexaoParams.login") return wxT("Login:");
	if (chave == "ConexaoParams.senha") return wxT("Senha:");

	if (chave == "Parametro.desktop") return wxT("Desktop:");
	if (chave == "Parametro.javaVersao") return wxT("Java Vers\u00e3o:");
	if (chave == "Parametro.diretorioUsuario") return wxT("Diret\u00f3rio do usu\u00e1rio:");
	if (chave == "Parametro.diretorioSistema") return wxT("Diret\u00f3rio do sistema:");
	if (chave == "Parametro.arquivoConfiguracao") return wxT("Arquivo de configura\u00e7\u00e3o:");
	if (chave == "Parametro.lookAndFeel") return wxT("lookAndFeel:");
	if (chave == "Parametro.localidadeLingua") return wxT("L\u00edngua:");
	if (chave == "Parametro.localidadePais") return wxT("Pa\u00eds:");
	if (chave == "Parametro.versao") return wxT("Vers\u00e3o:");

	if (chave == "Diretorio.aba") return wxT("Aba:");
	if (chave == "Diretorio.codigo") return wxT("C\u00f3digo:");
	if (chave == "Diretorio.ordem") return wxT("Ordem:");
	if (chave == "Diretorio.nome") return wxT("Nome:");
	if (chave == "Diretorio.tamanho") return wxT("Tamanho:");
	if (chave == "Diretorio.tipo") return wxT("Tipo:");
	if (chave == "Diretorio.modificado") return wxT("Modificado:");
	if (chave == "Diretorio.atributos") return wxT("Atributos:");
	if (chave == "Diretorio.codDirPai") return wxT("C\u00f3digo Diret\u00f3rio Pai:");
	if (chave == "Diretorio.caminho") return wxT("Caminho:");

	if (chave == "Extensao.codigo") return wxT("C\u00f3digo:");
	if (chave == "Extensao.nome") return wxT("Extens\u00e3o:");
	if (chave == "Extensao.icone") return wxT("\u00cdcone:");
	if (chave == "Extensao.arquivo") return wxT("arquivo(file)");
	if (chave == "Extensao.diretorio") return wxT("diretorio(directory)");
	if (chave == "Extensao.zip") return wxT(".zip");

	if (chave == "FrmPrincipal.titulo") return wxT("HFSGuardaDiretorio 2.0 - Catalogador de Diret\u00f3rios");
	if (chave == "FrmPrincipal.barraStatus1") return wxT("Quantidade Total: , Tamanho Total:");
	if (chave == "FrmPrincipal.btnImportarDiretorio") return wxT("Importar Diret\u00f3rio");
	if (chave == "FrmPrincipal.btnPesquisa") return wxT("Pesquisar");
	if (chave == "FrmPrincipal.Aba1") return wxT("DISCO1");
	if (chave == "FrmPrincipal.menuAba") return wxT("Aba");
	if (chave == "FrmPrincipal.menuIncluirNovaAba") return wxT("Incluir Nova Aba");
	if (chave == "FrmPrincipal.menuDiretorio") return wxT("Diret\u00f3rio");
	if (chave == "FrmPrincipal.menuAlterarNomeAbaAtiva") return wxT("Alterar Nome da Aba Ativa");
	if (chave == "FrmPrincipal.menuExcluirAbaAtiva") return wxT("Excluir Aba Ativa");
	if (chave == "FrmPrincipal.menuImportarDiretorio") return wxT("Importar Diret\u00f3rio");
	if (chave == "FrmPrincipal.menuImportarSubDiretorios") return wxT("Importar SubDiret\u00f3rios");
	if (chave == "FrmPrincipal.menuCompararDiretorios") return wxT("Comparar Diret\u00f3rios");
	if (chave == "FrmPrincipal.menuCadastrarExtensaoArquivo") return wxT("Cadastrar Extens\u00e3o de Arquivo");
	if (chave == "FrmPrincipal.menuExpandirDiretorios") return wxT("Expandir Diret\u00f3rios");
	if (chave == "FrmPrincipal.menuColapsarDiretorios") return wxT("Colapsar Diret\u00f3rios");
	if (chave == "FrmPrincipal.menuExportarDiretoriosAbaAtiva") return wxT("Exportar Diret\u00f3rios da Aba Ativa");
	if (chave == "FrmPrincipal.menuTXT") return wxT("TXT");
	if (chave == "FrmPrincipal.menuCSV") return wxT("CSV");
	if (chave == "FrmPrincipal.menuHTML") return wxT("HTML");
	if (chave == "FrmPrincipal.menuXML") return wxT("XML");
	if (chave == "FrmPrincipal.menuSQL") return wxT("SQL");
	if (chave == "FrmPrincipal.menuImportarDiretoriosViaXML") return wxT("Importar Diret\u00f3rios Via XML");
	if (chave == "FrmPrincipal.menuGravarLogImportacao") return wxT("Gravar Log da Importa\u00e7\u00e3o");
	if (chave == "FrmPrincipal.menuVisao") return wxT("Vis\u00e3o");
	if (chave == "FrmPrincipal.menuMostrarOcultarArvoreDirAbaAtiva") return wxT("Mostrar/Ocultar \u00c1rvore de diret\u00f3rios da Aba Ativa");
	if (chave == "FrmPrincipal.menuMostrarOcultarListaItensPesquisados") return wxT("Mostrar/Ocultar lista de itens pesquisados");
	if (chave == "FrmPrincipal.menuSobre") return wxT("Sobre");
	if (chave == "FrmPrincipal.TamMaxPesquisa") return wxT("A pesquisa s\u00f3 \u00e9 feita com pelo menos 2 caracteres!");
	if (chave == "FrmPrincipal.DigitaNomeDiretorio") return wxT("Este diret\u00f3rio n\u00e3o possui um nome.\nDigite o nome do diret\u00f3rio!");
	if (chave == "FrmPrincipal.ValidaNomeDiretorio") return wxT("Nenhum nome de diret\u00f3rio informado!");
	if (chave == "FrmPrincipal.ErroSalvarArquivo") return wxT("Ocorreu um erro ao salvar o arquivo.");
	if (chave == "FrmPrincipal.SucessoExportar") return wxT("Exporta\u00e7\u00e3o realizada com sucesso!");
	if (chave == "FrmPrincipal.ExcluirDiretorioSelecionado") return wxT("Tem Certeza, que voc\u00ea deseja excluir este diret\u00f3rio, isto implicar\u00e1 na destrui\u00e7\u00e3o de todos os seus items catalogados?");
	if (chave == "FrmPrincipal.ImportacaoNaoRealizada") return wxT("Importa\u00e7\u00e3o n\u00e3o realizada!");
	if (chave == "FrmPrincipal.DiretorioExisteCatalogo") return wxT("Este diret\u00f3rio j\u00e1 existe no cat\u00e1logo!");
	if (chave == "FrmPrincipal.ImportacaoRealizada") return wxT("Importa\u00e7\u00e3o realizada com sucesso!");
	if (chave == "FrmPrincipal.ErroAbrirDir") return wxT("Um erro ocorreu. Nenhum diret\u00f3rio foi escolhido.");
	if (chave == "FrmPrincipal.DirImportacaoSucesso") return wxT("Importa\u00e7\u00e3o do(s) diret\u00f3rio(s) realizada com sucesso!");
	if (chave == "FrmPrincipal.DigitaIncluirNovaAba") return wxT("Digite o Nome da Nova Aba?");
	if (chave == "FrmPrincipal.DigitaAlterarNomeAba") return wxT("Digite o Novo Nome da Aba Ativa?");
	if (chave == "FrmPrincipal.ConfirmaExcluirAba") return wxT("Tem Certeza, que voc\u00ea deseja excluir esta aba, \nisto implicar\u00e1 na destrui\u00e7\u00e3o de todos os seus itens catalogados?");
	if (chave == "FrmPrincipal.ValidaExcluirAba") return wxT("A primeira Aba n\u00e3o pode ser exclu\u00edda!");
	if (chave == "FrmPrincipal.menuSobreCatalogador") return wxT("Sobre o Catalogador");
	if (chave == "FrmPrincipal.menuIdioma") return wxT("Idioma");
	if (chave == "FrmPrincipal.menuPortugues") return wxT("Portugu\u00eas [Portuguese]");
	if (chave == "FrmPrincipal.menuIngles") return wxT("Ingl\u00eas [English]");
	if (chave == "FrmPrincipal.menuEspanhol") return wxT("Espanhol [Spanish]");
	if (chave == "FrmPrincipal.menuFrances") return wxT("Franc\u00eas [French]");
	if (chave == "FrmPrincipal.menuItaliano") return wxT("Italiano [Italian]");
	if (chave == "FrmPrincipal.menuAlemao") return wxT("Alem\u00e3o [German]");
	if (chave == "FrmPrincipal.menuJapones") return wxT("Japon\u00eas [Japanese]");
	if (chave == "FrmPrincipal.menuCoreano") return wxT("Coreano [Korean]");
	if (chave == "FrmPrincipal.menuChinesTradicional") return wxT("Chin\u00eas Tradicional [Traditional Chinese]");
	if (chave == "FrmPrincipal.menuExcluirDiretorioSelecionado") return wxT("Excluir Diret\u00f3rio Selecionado");
	if (chave == "FrmPrincipal.menuInformacoesDiretorioArquivo") return wxT("Informa\u00e7\u00f5es do Diret\u00f3rio / Arquivo");

	if (chave == "FrmSobre.titulo") return wxT("Sobre o Catalogador");
	if (chave == "FrmSobre.label1") return wxT("HFSGuardaDir 2.0 - Catalogador de Diret\u00f3rios");
	if (chave == "FrmSobre.label2") return wxT("Desenvolvido em Java com Swing, Vers\u00e3o: 2.0");
	if (chave == "FrmSobre.label3") return wxT("Por Henrique Figueiredo de Souza");
	if (chave == "FrmSobre.label4") return wxT("Todos os direitos reservados, 2015");
	if (chave == "FrmSobre.Propriedade") return wxT("Propriedade");
	if (chave == "FrmSobre.Valor") return wxT("Valor");

	if (chave == "FrmSplash.label1") return wxT("HFSGuardaDiretorio 2.0");
	if (chave == "FrmSplash.label2") return wxT("Catalogador de Diret\u00f3rios");

	if (chave == "FrmCompararDiretorio.titulo") return wxT("Comparar Diret\u00f3rios");
	if (chave == "FrmCompararDiretorio.btnCompararDiretorios") return wxT("Comparar Diret\u00f3rios");
	if (chave == "FrmCompararDiretorio.btnSalvarLog") return wxT("Salvar Log");
	if (chave == "FrmCompararDiretorio.barraStatus1") return wxT("Total de diferen\u00e7as encontradas:");
	if (chave == "FrmCompararDiretorio.panelDiretorio1") return wxT("Diret\u00f3rio 1");
	if (chave == "FrmCompararDiretorio.labDiferencasEncontradas") return wxT("Diferen\u00e7as Encontradas");
	if (chave == "FrmCompararDiretorio.panelDiretorio2") return wxT("Diret\u00f3rio 2");
	if (chave == "FrmCompararDiretorio.NenhumaDiferencaEncontrada") return wxT("Nenhuma diferen\u00e7a encontrada!");
	if (chave == "FrmCompararDiretorio.DiretoriosNaoSelecionados") return wxT("Diret\u00f3rios n\u00e3o selecionados!");
	if (chave == "FrmCompararDiretorio.LogSalvoMemoDirSistema") return wxT("Log salvo no mesmo diret\u00f3rio do sistema!");

	if (chave == "FrmCadExtensao.titulo") return wxT("Cadastro de Extens\u00e3o de Arquivo");
	if (chave == "FrmCadExtensao.extensao") return wxT("Extens\u00e3o");
	if (chave == "FrmCadExtensao.icone") return wxT("\u00cdcone");
	if (chave == "FrmCadExtensao.btnIncluir") return wxT("Incluir");
	if (chave == "FrmCadExtensao.btnExcluir") return wxT("Excluir");
	if (chave == "FrmCadExtensao.menuExtensao") return wxT("Extens\u00e3o");
	if (chave == "FrmCadExtensao.menuExportarTodos") return wxT("Exportar Todos");
	if (chave == "FrmCadExtensao.menuImportarTodos") return wxT("Importar Todos");
	if (chave == "FrmCadExtensao.menuIncluirExtensao") return wxT("Incluir Extens\u00e3o");
	if (chave == "FrmCadExtensao.menuExcluirExtensao") return wxT("Excluir Extens\u00e3o");
	if (chave == "FrmCadExtensao.menuExcluirTodasExtensoes") return wxT("Excluir Todas Extens\u00f5es");
	if (chave == "FrmCadExtensao.menuExportarIcone") return wxT("Exportar para \u00cdcone");
	if (chave == "FrmCadExtensao.menuExportarGIF") return wxT("Exportar para GIF");
	if (chave == "FrmCadExtensao.menuExportarJPEG") return wxT("Exportar para JPEG");
	if (chave == "FrmCadExtensao.menuExportarPNG") return wxT("Exportar para PNG");
	if (chave == "FrmCadExtensao.menuExportarTIFF") return wxT("Exportar para TIFF");
	if (chave == "FrmCadExtensao.menuImportarIconesArquivos") return wxT("Importar \u00cdcones dos Arquivos");
	if (chave == "FrmCadExtensao.menuExtrairIconesArquivos") return wxT("Extrair \u00cdcones dos Arquivos");
	if (chave == "FrmCadExtensao.ExtensaoJaCadastrada") return wxT("Extens\u00e3o j\u00e1 existe cadastrada!");
	if (chave == "FrmCadExtensao.ExtensaoSalvaSucesso") return wxT("Extens\u00e3o salva com sucesso!");
	if (chave == "FrmCadExtensao.ExtensaoCertezaExcluir") return wxT("Tem Certeza, que voc\u00ea deseja excluir esta extens\u00e3o?");
	if (chave == "FrmCadExtensao.ExtensaoCertezaTodosExcluir") return wxT("Tem Certeza, que voc\u00ea deseja excluir todas as extens\u00f5es?");
	if (chave == "FrmCadExtensao.ExtensaoExcluidaSucesso") return wxT("Extens\u00e3o exclu\u00edda com sucesso!");
	if (chave == "FrmCadExtensao.ExtensoesExcluidasSucesso") return wxT("Extens\u00f5es exclu\u00eddas com sucesso!");
	if (chave == "FrmCadExtensao.ExportarExtensao") return wxT("\u00cdcones salvos no mesmo diret\u00f3rio do sistema!");
	if (chave == "FrmCadExtensao.menuExportarBitmap") return wxT("Exportar para Bitmap");

	if (chave == "FrmInfoDiretorio.titulo") return wxT("Informa\u00e7\u00f5es do Diret\u00f3rio / Arquivo");
	if (chave == "FrmInfoDiretorio.panelLegenda") return wxT("Legenda dos Atributos");
	if (chave == "FrmInfoDiretorio.labArquivoComum") return wxT("[ARQ] - Arquivo comum");
	if (chave == "FrmInfoDiretorio.labArquivoOculto") return wxT("[HID] - Arquivo Oculto");
	if (chave == "FrmInfoDiretorio.labArquivoSistema") return wxT("[SYS] - Arquivo de Sistema");
	if (chave == "FrmInfoDiretorio.labDiretorio") return wxT("[DIR] - Diret\u00f3rio");
	if (chave == "FrmInfoDiretorio.labVolumeID") return wxT("[VOL] - Volume ID");
	if (chave == "FrmInfoDiretorio.labArquivoSomenteLeitura") return wxT("[ROL] - Arquivo Somente Leitura");
	if (chave == "FrmInfoDiretorio.item") return wxT("Item");
	if (chave == "FrmInfoDiretorio.descricao") return wxT("Descri\u00e7\u00e3o");

	if (chave == "FrmImportarDiretorio.titulo") return wxT("Importando Diret\u00f3rio");
	if (chave == "FrmImportarDiretorio.barraStatus1") return wxT("Total de linhas sendo processadas:");
	if (chave == "FrmImportarDiretorio.DiretorioExisteCatalogo") return wxT("O diret\u00f3rio j\u00e1 existe no cat\u00e1logo!");

	if (chave == "Dialogo.info") return wxT("Informa\u00e7\u00e3o");
	if (chave == "Dialogo.erro") return wxT("Erro");
	if (chave == "Dialogo.confirma") return wxT("Confirma");
	if (chave == "Dialogo.entrada") return wxT("Informa");
	if (chave == "Dialogo.yesButtonText") return wxT("Sim");
	if (chave == "Dialogo.yesButtonMnemonic") return wxT("S");
	if (chave == "Dialogo.cancelButtonText") return wxT("Cancelar");
	if (chave == "Dialogo.cancelButtonMnemonic") return wxT("C");
	if (chave == "Dialogo.noButtonText") return wxT("N\u00e3o");
	if (chave == "Dialogo.noButtonMnemonic") return wxT("N");
	if (chave == "Dialogo.okButtonText") return wxT("OK");
	if (chave == "Dialogo.okButtonMnemonic") return wxT("O");

	if (chave == "EscolhaArquivo.ApproveButtonText") return wxT("Escolha o Diret\u00f3rio");
	if (chave == "EscolhaArquivo.ApproveButtonMnemonic") return wxT("D");
	if (chave == "EscolhaArquivo.ApproveButtonToolTipText") return wxT("Confirme a escolha do diret\u00f3rio.");
	if (chave == "EscolhaArquivo.lookInLabelMnemonic") return wxT("E");
	if (chave == "EscolhaArquivo.lookInLabelText") return wxT("Examinar em");
	if (chave == "EscolhaArquivo.saveInLabelMnemonic") return wxT("S");
	if (chave == "EscolhaArquivo.saveInLabelText") return wxT("Salvar em");
	if (chave == "EscolhaArquivo.upFolderToolTipText") return wxT("Um n\u00edvel acima");
	if (chave == "EscolhaArquivo.upFolderAccessibleName") return wxT("Um n\u00edvel acima");
	if (chave == "EscolhaArquivo.homeFolderToolTipText") return wxT("Desktop");
	if (chave == "EscolhaArquivo.homeFolderAccessibleName") return wxT("Desktop");
	if (chave == "EscolhaArquivo.newFolderToolTipText") return wxT("Criar nova pasta");
	if (chave == "EscolhaArquivo.newFolderAccessibleName") return wxT("Criar nova pasta");
	if (chave == "EscolhaArquivo.listViewButtonToolTipText") return wxT("Lista");
	if (chave == "EscolhaArquivo.listViewButtonAccessibleName") return wxT("Lista");
	if (chave == "EscolhaArquivo.detailsViewButtonToolTipText") return wxT("Detalhes");
	if (chave == "EscolhaArquivo.detailsViewButtonAccessibleName") return wxT("Detalhes");
	if (chave == "EscolhaArquivo.fileNameLabelMnemonic") return wxT("N");
	if (chave == "EscolhaArquivo.fileNameLabelText") return wxT("Nome do arquivo");
	if (chave == "EscolhaArquivo.filesOfTypeLabelMnemonic") return wxT("A");
	if (chave == "EscolhaArquivo.filesOfTypeLabelText") return wxT("Arquivos do tipo");
	if (chave == "EscolhaArquivo.fileNameHeaderText") return wxT("Nome");
	if (chave == "EscolhaArquivo.fileSizeHeaderText") return wxT("Tamanho");
	if (chave == "EscolhaArquivo.fileTypeHeaderText") return wxT("Tipo");
	if (chave == "EscolhaArquivo.fileDateHeaderText") return wxT("Data");
	if (chave == "EscolhaArquivo.fileAttrHeaderText") return wxT("Atributos");
	if (chave == "EscolhaArquivo.cancelButtonText") return wxT("Cancelar");
	if (chave == "EscolhaArquivo.cancelButtonMnemonic") return wxT("C");
	if (chave == "EscolhaArquivo.cancelButtonToolTipText") return wxT("Cancelar");
	if (chave == "EscolhaArquivo.openButtonText") return wxT("Abrir");
	if (chave == "EscolhaArquivo.openButtonMnemonic") return wxT("A");
	if (chave == "EscolhaArquivo.openButtonToolTipText") return wxT("Abrir");
	if (chave == "EscolhaArquivo.saveButtonText") return wxT("Salvar");
	if (chave == "EscolhaArquivo.saveButtonMnemonic") return wxT("S");
	if (chave == "EscolhaArquivo.saveButtonToolTipText") return wxT("Salvar");
	if (chave == "EscolhaArquivo.updateButtonText") return wxT("Alterar");
	if (chave == "EscolhaArquivo.updateButtonMnemonic") return wxT("A");
	if (chave == "EscolhaArquivo.updateButtonToolTipText") return wxT("Alterar");
	if (chave == "EscolhaArquivo.helpButtonText") return wxT("Ajuda");
	if (chave == "EscolhaArquivo.helpButtonMnemonic") return wxT("A");
	if (chave == "EscolhaArquivo.helpButtonToolTipText") return wxT("Ajuda");
	if (chave == "EscolhaArquivo.acceptAllFileFilterText") return wxT("Todos os arquivos (*.*)");
	if (chave == "EscolhaArquivo.filtroTXT") return wxT("Arquivo TXT (*.txt)");
	if (chave == "EscolhaArquivo.filtroCSV") return wxT("Arquivo CSV (*.csv)");
	if (chave == "EscolhaArquivo.filtroHTML") return wxT("Arquivo HTML (*.html)");
	if (chave == "EscolhaArquivo.filtroXML") return wxT("Arquivo XML (*.xml)");
	if (chave == "EscolhaArquivo.filtroSQL") return wxT("Arquivo SQL (*.sql)");
	if (chave == "EscolhaArquivo.filtroBMP") return wxT("Arquivo BMP (*.bmp)");
	if (chave == "EscolhaArquivo.filtroICO") return wxT("Arquivo ICO (*.ico)");
	if (chave == "EscolhaArquivo.filtroGIF") return wxT("Arquivo GIF (*.gif)");
	if (chave == "EscolhaArquivo.filtroPNG") return wxT("Arquivo JPEG (*.png)");
	if (chave == "EscolhaArquivo.filtroJPG") return wxT("Arquivo PNG (*.jpg)");
	if (chave == "EscolhaArquivo.filtroTIF") return wxT("Arquivo TIFF (*.tif)");
	if (chave == "EscolhaArquivo.todosDiretorios") return wxT("Todos os diret\u00f3rios");

    return chave;
}

wxImage Rotinas::getImagem(const wxString &arquivo) {
    wxImage imagem;
	wxBitmap bmp(arquivo);
	imagem = bmp.ConvertToImage();
	
    return imagem;
}

wxMemoryBuffer Rotinas::getImagemByteArray(const wxString &arquivo) {
	wxMemoryBuffer bArray;
	//wxImage imagem(arquivo);
	wxImage imagem = getImagem(arquivo);

	if (imagem.IsOk()) {
		bArray = ImageToMemoryBuffer(imagem, wxBITMAP_TYPE_BMP);
	}

    return bArray;
}

wxMemoryBuffer Rotinas::ImageToMemoryBuffer(const wxImage &image, wxBitmapType formato){
	wxMemoryBuffer membuffer;
	wxMemoryOutputStream ostream;

	if (!image.SaveFile(ostream, formato))
		return membuffer;

	if (ostream.IsOk()) {
		wxStreamBuffer* streambuffer = ostream.GetOutputStreamBuffer();		
		//wxFileOffset tam = ostream.GetLength();

		if (streambuffer->HasBuffer()){
			size_t tam = streambuffer->GetBufferSize();
			streambuffer->SetIntPosition(0);

			void* buffer = membuffer.GetAppendBuf(tam);
			size_t iRead = streambuffer->Read(buffer, tam);
			membuffer.UngetAppendBuf(iRead);
		}
	}
	return membuffer;
}

wxImage Rotinas::MemoryBufferToImage(const wxMemoryBuffer &membuffer, wxBitmapType formato){
	wxImage image;
	
	if (!membuffer.IsEmpty()) {
		wxMemoryInputStream istream(membuffer.GetData(), membuffer.GetDataLen());

		if (istream.IsOk()) {
			if (!image.LoadFile(istream, formato))
				return image;
		}
	}


	return image;
}

wxMemoryBuffer Rotinas::BmpParaImagem(const wxMemoryBuffer &imagemBMP, const wxString &formato){
	//wxBitmap bmp;
	//wxImage imagem = bmp.ConvertToImage();
	wxMemoryBuffer saida;
	//= ImageToMemoryBuffer(imagemBMP, wxBITMAP_TYPE_BMP);
	
    return saida;
}


bool Rotinas::SListSaveToFile(const wxArrayString &lista, const wxString &sNomeArquivo) {
	wxString linha;
	wxTextFile arquivo;

	if (arquivo.Create(sNomeArquivo)) {
		if (arquivo.Open(sNomeArquivo)) {
			for (unsigned int i = 0; i < lista.size(); i++) {
				linha = lista[i];
				arquivo.AddLine(linha);
				arquivo.Write();
			}
			arquivo.Close();
		}
		else {
			return false;
		}
	} 
	else {
		return false;	
	}

    return true;
}

wxArrayString Rotinas::SListLoadFromFile(const wxString &sNomeArquivo) {
	wxString linha;
	wxTextFile arquivo;
	wxArrayString lista;

	if (arquivo.Open(sNomeArquivo)) {
		for (linha = arquivo.GetFirstLine(); !arquivo.Eof();
			linha = arquivo.GetNextLine()) {
			lista.Add(linha);
		}
		arquivo.Close();
	}

    return lista;
}

wxArrayString Rotinas::SListSeparador(const wxString &texto, const wxChar &separador) {
	wxArrayString lista;

    if (texto.Contains(separador)) {
        wxString pedaco = "";
        for (unsigned int i = 0; i < texto.length(); i++) {
            pedaco += texto[i];
            if (texto[i] == separador) {
                lista.Add(pedaco.Mid(0, pedaco.length() - 1));
                pedaco = "";
            }
        }
        lista.Add(pedaco);
	}
	else {
		lista.Add(texto);
	}

    return lista;
}

wxString Rotinas::SListTexto(const wxArrayString &lista) {
	wxString texto = "";

	if (!lista.IsEmpty()) {
		for (unsigned int i = 0; i < lista.size(); i++) {
			texto += lista[i];
		}
	}

	return texto;
}

wxImage Rotinas::extrairIconeArquivo(const wxString &sNomeArquivo) {
	wxImage imagem;
	wxIcon *wxicone;
	WORD filtro = 0;

	//wchar_t * arquivo = (wchar_t *) sNomeArquivo.operator const wchar_t *();
	wxicone = new wxIcon(sNomeArquivo);
	//HINSTANCE hInstance = GetModuleHandle(NULL);	
	//HICON icone = ExtractAssociatedIcon(hInstance, arquivo, &filtro);
	
	//wxicone.SetHICON(icone);
	wxBitmap bmp(*wxicone, wxBitmapTransparency_Always);
	imagem = bmp.ConvertToImage();
		
	return imagem;
}

wxArrayString Rotinas::listarArquivosDiretorios(const wxString &sDiretorio) {
	wxArrayString lista;
	wxString sCaminho, arquivo;

	/*
	if (wxDir::Exists(sDiretorio)) {
		wxDir::GetAllFiles(sDiretorio, &lista, wxEmptyString, wxDIR_DEFAULT | wxDIR_NO_FOLLOW);
	}
	*/

	wxDir dir(sDiretorio);
	if (dir.GetFirst(&arquivo, wxEmptyString, wxDIR_DEFAULT | wxDIR_NO_FOLLOW)) {
		sCaminho = dir.GetNameWithSep() + arquivo;
		lista.Add(sCaminho);
		
		while (dir.GetNext(&arquivo)) {
			sCaminho = dir.GetNameWithSep() + arquivo;
			lista.Add(sCaminho);
		}
	}
	dir.Close();
	
	return lista;
}

void Rotinas::testar() {
	wxString sApp = Rotinas::AppDirPath();
	wxString sDir = "    c:\\ago%ra\\CAMINHO\\teste.olha.depois    ";

	wxArrayString listaDir = Rotinas::listarArquivosDiretorios("c:/Temp");
	for (unsigned int i = 0; i < listaDir.size(); i++)
	{
		wxLogDebug("listarArquivosDiretorios[%d]: %s", i, listaDir[i]);
	}

	wxLogDebug("sDir: [%s]", sDir);

	wxLogDebug("AppDirPath: %s", sApp);
	wxLogDebug("FileExists: %s", Rotinas::FileExists(sApp) ? "true" : "false");
	wxLogDebug("DirectoryExists: %s", Rotinas::DirectoryExists(sApp) ? "true" : "false");	
	wxLogDebug("ExtractFilePath: %s", Rotinas::ExtractFilePath(sApp));
	wxLogDebug("ExtractFileName: %s", Rotinas::ExtractFileName(sApp));

	wxLogDebug("Length(): %d", sDir.Len());
	wxLogDebug("Trim(): %s", Rotinas::Trim(sDir));
	wxLogDebug("tamanho Trim(): %d", Rotinas::Trim(sDir).Len());
	wxLogDebug("LowerCase(): %s", sDir.Lower());
	wxLogDebug("UpperCase(): %s", sDir.Upper());
	wxLogDebug("Pos('.'): %d", Rotinas::Pos(".", sDir));
	wxLogDebug("LastDelimiter('.'): %d", Rotinas::LastDelimiter(".", sDir));
	wxLogDebug("QuotedStr(): %s", Rotinas::QuotedStr(sDir));
	wxLogDebug("IntToStr(245789): %s", Rotinas::IntToStr(245789));
	wxLogDebug("StrToInt() --> 245789: %d", Rotinas::StrToInt("245789"));
	wxLogDebug("StrToLong() --> 4200155136: %llu", Rotinas::StrToLong("4200155136").GetValue());
	wxLogDebug("DoubleToStr(15.557878): %s", Rotinas::DoubleToStr(15.557878));
	
	wxLogDebug("SubString(): %s", Rotinas::SubString(sDir, 8, 6));
	wxLogDebug("StringReplaceAll(): %s", Rotinas::StringReplaceAll(sDir, "\\", "@"));
	wxLogDebug("trocaSeparador(): %s", Rotinas::trocaSeparador(sDir));
	wxLogDebug("testaNull(NULL): %s", Rotinas::testaNull(wxEmptyString));
	
	wxLogDebug("StartsStr(JOGOS2_DVDS/TESTE): %s", Rotinas::StartsStr("DVD", "JOGOS2_DVDS/TESTE") ? "true" : "false");
	wxLogDebug("StartsStr(DVDSJOGOS2_/TESTE): %s", Rotinas::StartsStr("DVD", "DVDSJOGOS2_/TESTE") ? "true" : "false");

	wxLogDebug("ContainsStr(JOGOS2_DVDS/TESTE): %s", (Rotinas::ContainsStr("DVDSJOGOS2_/TESTE", "DVDSJOGOS2_/TESTE") ? "true" : "false"));
	wxLogDebug("EndsStr(TESTE, JOGOS2_DVDS/TESTE): %s", (Rotinas::EndsStr("TESTE", "DVDSJOGOS2_/TESTE") ? "true" : "false"));

	wxLogDebug("formataDate(): %s", Rotinas::formataDate(Rotinas::FORMATO_DATAHORA, wxDateTime::Now()));
	wxDateTime dt = Rotinas::StringToDate("03/02/2017 15:23:32");
	wxLogDebug("StringToDate(03/02/2017 15:23:32): %s", dt.Format(Rotinas::FORMATO_DATAHORA));

	wxLogDebug("FormatLong(4200155136): %s", Rotinas::FormatLong(4200155136));
	wxLogDebug("FormatDouble(15.544878): %s", Rotinas::FormatDouble(15.544878));
	wxLogDebug("FormatDouble(15.547878): %s", Rotinas::FormatDouble(15.547878));
	wxLogDebug("FormatDouble(15.557878): %s", Rotinas::FormatDouble(15.557878));
	wxLogDebug("FormatDouble(15.567878): %s", Rotinas::FormatDouble(15.567878));

	wxLogDebug("MontaTamanho() --> 3.91 GB: %s", Rotinas::MontaTamanho(4200155136));
	wxLogDebug("MontaTamanho() --> 3.50 GB: %s", Rotinas::MontaTamanho(3757244416));
	wxLogDebug("MontaTamanho() --> 2.29 GB: %s", Rotinas::MontaTamanho(2455207936));
	wxLogDebug("MontaTamanho() --> 888.18 PB: %s", Rotinas::MontaTamanhoBig(999999999999999999.9999));
		
	wxArrayString lista;

	lista = Rotinas::SListSeparador(sDir, '\\');

	for (unsigned int i = 0; i < lista.size(); i++)
	{
		wxLogDebug("SListSeparador[%d]: %s", i, lista[i]);
	}
	
	wxString arquivo = Rotinas::ExtractFilePath(sApp) + "\\exemplo.txt";
	wxLogDebug("arquivo: %s", arquivo);

	if (Rotinas::SListSaveToFile(lista, arquivo)) {

		if (Rotinas::FileExists(arquivo)) {

			lista = Rotinas::SListLoadFromFile(arquivo);
			for (unsigned int i = 0; i < lista.GetCount(); i++) {
				wxLogDebug("SListLoadFromFile[%d]: %s", i, lista[i]);
			}

			if (Rotinas::DeleteFromFile(arquivo)) {
				if (!Rotinas::FileExists(arquivo)) {
					wxLogDebug("DeleteFromFile: OK");
				}
			}
			else {
				wxLogDebug("DeleteFromFile: FALHOU");
			}

		}

	}


	wxString arqMemoria, arqImagem, arqImagem2;
	wxImage imagem = Rotinas::extrairIconeArquivo(sApp);
	if (imagem.IsOk()) {
		wxLogDebug("extrairIconeArquivo OK");

		
		wxMemoryBuffer mbuf = Rotinas::ImageToMemoryBuffer(imagem, wxBITMAP_TYPE_BMP);
		if (!mbuf.IsEmpty()) {
			wxLogDebug("ImageToMemoryBuffer OK");
		}
		else {
			wxLogDebug("ImageToMemoryBuffer FALHOU");
		}

		wxImage imgbuf = Rotinas::MemoryBufferToImage(mbuf, wxBITMAP_TYPE_BMP);
		if (imgbuf.IsOk()) {
			wxLogDebug("MemoryBufferToImage OK");

			arqMemoria = Rotinas::ExtractFilePath(sApp) + "\\memoria.bmp";
			wxLogDebug("arquivo de imagem da Memoria: %s", arqMemoria);

			if (imagem.SaveFile(arqMemoria, wxBITMAP_TYPE_BMP)) {
				wxLogDebug("arquivo de imagem da Memoria SALVO");
			}
			else {
				wxLogDebug("arquivo de imagem da Memoria FALHOU");
			}
		}
		else {
			wxLogDebug("MemoryBufferToImage FALHOU");
		}
		

		arqImagem = Rotinas::ExtractFilePath(sApp) + "\\exemplo.bmp";
		wxLogDebug("arquivo da imagem: %s", arqImagem);

		if (imagem.SaveFile(arqImagem, wxBITMAP_TYPE_BMP)) {

			if (Rotinas::FileExists(arqImagem)) {
				wxLogDebug("arquivo da imagem SALVO");

				wxMemoryBuffer buf = Rotinas::LoadFromFile(arqImagem);
				if (!buf.IsEmpty()) {
					wxLogDebug("LoadFromFile OK");

					arqImagem2 = Rotinas::ExtractFilePath(sApp) + "\\exemplo2.bmp";
					wxLogDebug("arquivo da imagem a ser salva: %s", arqImagem2);

					Rotinas::SaveToFile(buf, arqImagem2);
					if (Rotinas::FileExists(arqImagem2)) {
						wxLogDebug("SaveToFile SALVO");
					}
					else {
						wxLogDebug("SaveToFile FALHOU");
					}
				}
				else {
					wxLogDebug("LoadFromFile FALHOU");
				}
			}
			else
			{
				wxLogDebug("arquivo da imagem FALHOU");
			}
		}

	}
	else {
		wxLogDebug("extrairIconeArquivo FALHOU");
	}

	Rotinas::DeleteFromFile(arqMemoria);
	Rotinas::DeleteFromFile(arqImagem);
	Rotinas::DeleteFromFile(arqImagem2);

}

}
}
