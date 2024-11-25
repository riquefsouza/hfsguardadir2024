#include "Rotinas.h"

//#include <QtWin>

#include <QApplication>
#include <QScreen>
#include <QtSql>
#include <QImageWriter>

using namespace hfsguardadir::objetos;

namespace hfsguardadir {

namespace comum {

Rotinas* Rotinas::instancia = NULL;

const QString Rotinas::HFSGUARDADIR = "HFSGuardaDir";
const QString Rotinas::FORMATO_DATA = "dd/MM/yyyy";
const QString Rotinas::FORMATO_DATAHORA = "dd/MM/yyyy HH:mm:ss";
const QString Rotinas::FORMATO_DHARQUIVO = "yyyy-MM-dd_HH_mm_ss";
const QString Rotinas::EXTENSAO_BMP = "bmp";
const QString Rotinas::EXTENSAO_ICO = "ico";
const QString Rotinas::EXTENSAO_GIF = "gif";
const QString Rotinas::EXTENSAO_JPEG = "jpg";
const QString Rotinas::EXTENSAO_PNG = "png";
const QString Rotinas::EXTENSAO_TIFF = "tif";

Rotinas::Rotinas()
{
	arquivoIcone = Rotinas::getImagem("arquivo.bmp");
	cdouroIcone = Rotinas::getImagem("cdouro.bmp");
	diretorioIcone = Rotinas::getImagem("Fechar.bmp");
	dirabertoIcone = Rotinas::getImagem("Abrir.bmp");
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

void Rotinas::CentralizaWidget(QWidget *widget)
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  sg = screen->geometry();
    int x = (sg.width() - widget->width()) / 2;
    int y = (sg.height() - widget->height()) / 2;
    widget->move(x, y);
}

QSqlDatabase Rotinas::getConexao() {
    return dbConexao;
}

void Rotinas::Conectar(QString &banco) {
    ConexaoParams cp;
    cp.setNome(QString("QSQLITE"));
    cp.setUrl(banco);
    dbConexao = Conectar(cp);
}

QSqlDatabase Rotinas::Conectar(ConexaoParams cp) {

    QSqlDatabase db = QSqlDatabase::addDatabase(cp.getNome());
    db.setDatabaseName(cp.getUrl());

    if (!db.open())
    {
      qDebug() << "Erro: conexao falhou";
    }
    else
    {
      qDebug() << "Database: conexao ok";
    }

    return db;
}

void Rotinas::Desconectar() {
    Desconectar(dbConexao);
}

void Rotinas::Desconectar(QSqlDatabase con) {
	con.close();
}

bool Rotinas::criarVisao(const QString &visao) {
    QString sSQL;

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

bool Rotinas::execConsulta(const QString &sSQL) {
    QSqlQuery query;
    query.prepare(sSQL);
    return query.exec();
}

int Rotinas::LastDelimiter(const QString &subtexto, const QString &texto) {
    return texto.lastIndexOf(subtexto) + 1;
}

int Rotinas::LastDelimiter(char subtexto, const QString &texto) {
    return texto.lastIndexOf(subtexto) + 1;
}

int Rotinas::Pos(const QString &subtexto, const QString &texto) {
    return texto.indexOf(subtexto) + 1;
}

int Rotinas::Pos(char subtexto, const QString &texto) {
    return texto.indexOf(subtexto) + 1;
}

bool Rotinas::StartsStr(const QString &subtexto, const QString &texto) {
    return texto.startsWith(subtexto);
}

bool Rotinas::ContainsStr(const QString &texto, const QString &subtexto) {
    return (Pos(subtexto, texto) > 0);
}

bool Rotinas::EndsStr(const QString &subtexto, const QString &texto) {
    return (LastDelimiter(subtexto, texto) > 0);
}

QString Rotinas::SubString(const QString &texto, int inicio, int tamanho) {
    if ((inicio + tamanho - 1) > texto.length()) {
        tamanho = texto.length();
    } else {
        tamanho = inicio + tamanho - 1;
    }
    return texto.mid(inicio - 1, tamanho);
}

QString Rotinas::StringReplaceAll(const QString &texto, const QString &velho,
        const QString &novo){
    QString txt = texto;
    return txt.replace(velho, novo);
}

QString Rotinas::QuotedStr(const QString &texto){
    return "'" + texto + "'";
}

QString Rotinas::QuotedStr(char texto){
    return "'" + QString(texto) + "'";
}

QString Rotinas::formataDate(const QString &formato, const QDateTime &dt) {
    QString ds = "";
	
	ds = dt.toString(formato);

    return ds;
}

QDateTime Rotinas::StringToDate(const QString &sData) {
    QDateTime data;

    if (sData.trimmed().length() > 0) {
        if (sData.trimmed().length() == 10)
			data = QDateTime::fromString(sData, Rotinas::FORMATO_DATA);
        else
			data = QDateTime::fromString(sData, Rotinas::FORMATO_DATAHORA);
    }
    return data;
}

QString Rotinas::FormatLong(long valor) {
    QString texto;

    texto = texto.asprintf("%lu", valor);
    //texto = QString::number(valor);

    return texto;
}

QString Rotinas::FormatDouble(long double valor) {
    QString texto;

    //texto = QString::sprintf("%4.2Lf", valor);
    texto = QString::number(valor, 'f', 2 );

    return texto;
}

QString Rotinas::MontaTamanhoBig(long double nTam) {
	qlonglong nUmKilo, nUmMega, nUmGiga, nUmTera, nUmPeta;

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

QString Rotinas::MontaTamanho(long long nTam) {
	if (nTam > 0) {
		return MontaTamanhoBig(nTam);
	}
	else {
		return "";
	}
}

QString Rotinas::testaNull(const QString &res) {
    return (res.isNull() ? "" : res.trimmed());
}

QString Rotinas::trocaSeparador(const QString &texto) {
    QString res = "", txt = texto;
    if (texto.length() > 0) {
        res = txt.replace(BARRA_NORMAL, BARRA_INVERTIDA);
    }
    return res;
}

QString Rotinas::ExtractFilePath(const QString &sCaminho) {
    QString retorno;

    QFileInfo info(sCaminho);
    retorno = info.absolutePath();

    return retorno;
}

QString Rotinas::ExtractFileName(const QString &sCaminho) {
    QString retorno;

    QFileInfo info(sCaminho);
    retorno = info.fileName();

    return retorno;
}

bool Rotinas::FileExists(const QString &sNomeArquivo) {
    QFileInfo info(sNomeArquivo);
    if (info.exists()) {
        return info.isFile();
    } else
        return false;
}

bool Rotinas::DirectoryExists(const QString &sNomeArquivo) {
    QFileInfo info(sNomeArquivo);
    if (info.exists()) {
        return info.isDir();
    } else
        return false;
}

bool Rotinas::DeleteFromFile(const QString &sNomeArquivo) {
    QFile file(sNomeArquivo);
    return file.remove();
}

void Rotinas::SaveToFile(const QByteArray &imagem, const QString &sNomeArquivo) {
    QFile file(sNomeArquivo);
    file.open(QIODevice::WriteOnly);
    file.write(imagem);
    file.close();
}

QByteArray Rotinas::LoadFromFile(const QString &sNomeArquivo) {
    QByteArray imagem;

    QFile file(sNomeArquivo);
    file.open(QIODevice::ReadOnly);
    imagem = file.readAll();
    file.close();

    return imagem;
}

QString Rotinas::getRecurso(const QString &chave) {
	if (chave == "HFSGuardaDir.ValidaJavaVersao") return QString::fromStdWString(L"Esta vers\u00e3o do JAVA n\u00e3o \u00e9 suportada pelo programa.");
	if (chave == "HFSGuardaDir.ErroInicial") return QString::fromStdWString(L"Ocorreu um erro no aplicativo!");
	if (chave == "HFSGuardaDir.ValidaArquivoConf") return QString::fromStdWString(L"Arquivo de configura\u00e7\u00e3o n\u00e3o existe!\nAs configura\u00e7\u00f5es padr\u00e3o ser\u00e3o usadas!");

	if (chave == "Tabela.nome") return QString::fromStdWString(L"Nome");
	if (chave == "Tabela.tamanho") return QString::fromStdWString(L"Tamanho");
	if (chave == "Tabela.tipo") return QString::fromStdWString(L"Tipo");
	if (chave == "Tabela.modificado") return QString::fromStdWString(L"Modificado");
	if (chave == "Tabela.atributos") return QString::fromStdWString(L"Atributos");
	if (chave == "Tabela.caminho") return QString::fromStdWString(L"Caminho");
	if (chave == "Tabela.aba") return QString::fromStdWString(L"Aba");

	if (chave == "Aba.codigo") return QString::fromStdWString(L"C\u00f3digo:");
	if (chave == "Aba.nome") return QString::fromStdWString(L"Nome:");

	if (chave == "Tipo.codigo") return QString::fromStdWString(L"C\u00f3digo:");
	if (chave == "Tipo.nome") return QString::fromStdWString(L"Nome:");

	if (chave == "TipoLista.arquivo") return QString::fromStdWString(L"Arquivo");
	if (chave == "TipoLista.diretorio") return QString::fromStdWString(L"Diret\u00f3rio");

	if (chave == "ConexaoParams.nome") return QString::fromStdWString(L"Nome:");
	if (chave == "ConexaoParams.driver") return QString::fromStdWString(L"Driver:");
	if (chave == "ConexaoParams.url") return QString::fromStdWString(L"URL:");
	if (chave == "ConexaoParams.login") return QString::fromStdWString(L"Login:");
	if (chave == "ConexaoParams.senha") return QString::fromStdWString(L"Senha:");

	if (chave == "Parametro.desktop") return QString::fromStdWString(L"Desktop:");
	if (chave == "Parametro.javaVersao") return QString::fromStdWString(L"Java Vers\u00e3o:");
	if (chave == "Parametro.diretorioUsuario") return QString::fromStdWString(L"Diret\u00f3rio do usu\u00e1rio:");
	if (chave == "Parametro.diretorioSistema") return QString::fromStdWString(L"Diret\u00f3rio do sistema:");
	if (chave == "Parametro.arquivoConfiguracao") return QString::fromStdWString(L"Arquivo de configura\u00e7\u00e3o:");
	if (chave == "Parametro.lookAndFeel") return QString::fromStdWString(L"lookAndFeel:");
	if (chave == "Parametro.localidadeLingua") return QString::fromStdWString(L"L\u00edngua:");
	if (chave == "Parametro.localidadePais") return QString::fromStdWString(L"Pa\u00eds:");
	if (chave == "Parametro.versao") return QString::fromStdWString(L"Vers\u00e3o:");

	if (chave == "Diretorio.aba") return QString::fromStdWString(L"Aba:");
	if (chave == "Diretorio.codigo") return QString::fromStdWString(L"C\u00f3digo:");
	if (chave == "Diretorio.ordem") return QString::fromStdWString(L"Ordem:");
	if (chave == "Diretorio.nome") return QString::fromStdWString(L"Nome:");
	if (chave == "Diretorio.tamanho") return QString::fromStdWString(L"Tamanho:");
	if (chave == "Diretorio.tipo") return QString::fromStdWString(L"Tipo:");
	if (chave == "Diretorio.modificado") return QString::fromStdWString(L"Modificado:");
	if (chave == "Diretorio.atributos") return QString::fromStdWString(L"Atributos:");
	if (chave == "Diretorio.codDirPai") return QString::fromStdWString(L"C\u00f3digo Diret\u00f3rio Pai:");
	if (chave == "Diretorio.caminho") return QString::fromStdWString(L"Caminho:");

	if (chave == "Extensao.codigo") return QString::fromStdWString(L"C\u00f3digo:");
	if (chave == "Extensao.nome") return QString::fromStdWString(L"Extens\u00e3o:");
	if (chave == "Extensao.icone") return QString::fromStdWString(L"\u00cdcone:");
	if (chave == "Extensao.arquivo") return QString::fromStdWString(L"arquivo(file)");
	if (chave == "Extensao.diretorio") return QString::fromStdWString(L"diretorio(directory)");
	if (chave == "Extensao.zip") return QString::fromStdWString(L".zip");

	if (chave == "FrmPrincipal.titulo") return QString::fromStdWString(L"HFSGuardaDiretorio 2.0 - Catalogador de Diret\u00f3rios");
	if (chave == "FrmPrincipal.barraStatus1") return QString::fromStdWString(L"Quantidade Total: , Tamanho Total:");
	if (chave == "FrmPrincipal.btnImportarDiretorio") return QString::fromStdWString(L"Importar Diret\u00f3rio");
	if (chave == "FrmPrincipal.btnPesquisa") return QString::fromStdWString(L"Pesquisar");
	if (chave == "FrmPrincipal.Aba1") return QString::fromStdWString(L"DISCO1");
	if (chave == "FrmPrincipal.menuAba") return QString::fromStdWString(L"Aba");
	if (chave == "FrmPrincipal.menuIncluirNovaAba") return QString::fromStdWString(L"Incluir Nova Aba");
	if (chave == "FrmPrincipal.menuDiretorio") return QString::fromStdWString(L"Diret\u00f3rio");
	if (chave == "FrmPrincipal.menuAlterarNomeAbaAtiva") return QString::fromStdWString(L"Alterar Nome da Aba Ativa");
	if (chave == "FrmPrincipal.menuExcluirAbaAtiva") return QString::fromStdWString(L"Excluir Aba Ativa");
	if (chave == "FrmPrincipal.menuImportarDiretorio") return QString::fromStdWString(L"Importar Diret\u00f3rio");
	if (chave == "FrmPrincipal.menuImportarSubDiretorios") return QString::fromStdWString(L"Importar SubDiret\u00f3rios");
	if (chave == "FrmPrincipal.menuCompararDiretorios") return QString::fromStdWString(L"Comparar Diret\u00f3rios");
	if (chave == "FrmPrincipal.menuCadastrarExtensaoArquivo") return QString::fromStdWString(L"Cadastrar Extens\u00e3o de Arquivo");
	if (chave == "FrmPrincipal.menuExpandirDiretorios") return QString::fromStdWString(L"Expandir Diret\u00f3rios");
	if (chave == "FrmPrincipal.menuColapsarDiretorios") return QString::fromStdWString(L"Colapsar Diret\u00f3rios");
	if (chave == "FrmPrincipal.menuExportarDiretoriosAbaAtiva") return QString::fromStdWString(L"Exportar Diret\u00f3rios da Aba Ativa");
	if (chave == "FrmPrincipal.menuTXT") return QString::fromStdWString(L"TXT");
	if (chave == "FrmPrincipal.menuCSV") return QString::fromStdWString(L"CSV");
	if (chave == "FrmPrincipal.menuHTML") return QString::fromStdWString(L"HTML");
	if (chave == "FrmPrincipal.menuXML") return QString::fromStdWString(L"XML");
	if (chave == "FrmPrincipal.menuSQL") return QString::fromStdWString(L"SQL");
	if (chave == "FrmPrincipal.menuImportarDiretoriosViaXML") return QString::fromStdWString(L"Importar Diret\u00f3rios Via XML");
	if (chave == "FrmPrincipal.menuGravarLogImportacao") return QString::fromStdWString(L"Gravar Log da Importa\u00e7\u00e3o");
	if (chave == "FrmPrincipal.menuVisao") return QString::fromStdWString(L"Vis\u00e3o");
	if (chave == "FrmPrincipal.menuMostrarOcultarArvoreDirAbaAtiva") return QString::fromStdWString(L"Mostrar/Ocultar \u00c1rvore de diret\u00f3rios da Aba Ativa");
	if (chave == "FrmPrincipal.menuMostrarOcultarListaItensPesquisados") return QString::fromStdWString(L"Mostrar/Ocultar lista de itens pesquisados");
	if (chave == "FrmPrincipal.menuSobre") return QString::fromStdWString(L"Sobre");
	if (chave == "FrmPrincipal.TamMaxPesquisa") return QString::fromStdWString(L"A pesquisa s\u00f3 \u00e9 feita com pelo menos 2 caracteres!");
	if (chave == "FrmPrincipal.DigitaNomeDiretorio") return QString::fromStdWString(L"Este diret\u00f3rio n\u00e3o possui um nome.\nDigite o nome do diret\u00f3rio!");
	if (chave == "FrmPrincipal.ValidaNomeDiretorio") return QString::fromStdWString(L"Nenhum nome de diret\u00f3rio informado!");
	if (chave == "FrmPrincipal.ErroSalvarArquivo") return QString::fromStdWString(L"Ocorreu um erro ao salvar o arquivo.");
	if (chave == "FrmPrincipal.SucessoExportar") return QString::fromStdWString(L"Exporta\u00e7\u00e3o realizada com sucesso!");
	if (chave == "FrmPrincipal.ExcluirDiretorioSelecionado") return QString::fromStdWString(L"Tem Certeza, que voc\u00ea deseja excluir este diret\u00f3rio, isto implicar\u00e1 na destrui\u00e7\u00e3o de todos os seus items catalogados?");
	if (chave == "FrmPrincipal.ImportacaoNaoRealizada") return QString::fromStdWString(L"Importa\u00e7\u00e3o n\u00e3o realizada!");
	if (chave == "FrmPrincipal.DiretorioExisteCatalogo") return QString::fromStdWString(L"Este diret\u00f3rio j\u00e1 existe no cat\u00e1logo!");
	if (chave == "FrmPrincipal.ImportacaoRealizada") return QString::fromStdWString(L"Importa\u00e7\u00e3o realizada com sucesso!");
	if (chave == "FrmPrincipal.ErroAbrirDir") return QString::fromStdWString(L"Um erro ocorreu. Nenhum diret\u00f3rio foi escolhido.");
	if (chave == "FrmPrincipal.DirImportacaoSucesso") return QString::fromStdWString(L"Importa\u00e7\u00e3o do(s) diret\u00f3rio(s) realizada com sucesso!");
	if (chave == "FrmPrincipal.DigitaIncluirNovaAba") return QString::fromStdWString(L"Digite o Nome da Nova Aba?");
	if (chave == "FrmPrincipal.DigitaAlterarNomeAba") return QString::fromStdWString(L"Digite o Novo Nome da Aba Ativa?");
	if (chave == "FrmPrincipal.ConfirmaExcluirAba") return QString::fromStdWString(L"Tem Certeza, que voc\u00ea deseja excluir esta aba, \nisto implicar\u00e1 na destrui\u00e7\u00e3o de todos os seus itens catalogados?");
	if (chave == "FrmPrincipal.ValidaExcluirAba") return QString::fromStdWString(L"A primeira Aba n\u00e3o pode ser exclu\u00edda!");
	if (chave == "FrmPrincipal.menuSobreCatalogador") return QString::fromStdWString(L"Sobre o Catalogador");
	if (chave == "FrmPrincipal.menuIdioma") return QString::fromStdWString(L"Idioma");
	if (chave == "FrmPrincipal.menuPortugues") return QString::fromStdWString(L"Portugu\u00eas [Portuguese]");
	if (chave == "FrmPrincipal.menuIngles") return QString::fromStdWString(L"Ingl\u00eas [English]");
	if (chave == "FrmPrincipal.menuEspanhol") return QString::fromStdWString(L"Espanhol [Spanish]");
	if (chave == "FrmPrincipal.menuFrances") return QString::fromStdWString(L"Franc\u00eas [French]");
	if (chave == "FrmPrincipal.menuItaliano") return QString::fromStdWString(L"Italiano [Italian]");
	if (chave == "FrmPrincipal.menuAlemao") return QString::fromStdWString(L"Alem\u00e3o [German]");
	if (chave == "FrmPrincipal.menuJapones") return QString::fromStdWString(L"Japon\u00eas [Japanese]");
	if (chave == "FrmPrincipal.menuCoreano") return QString::fromStdWString(L"Coreano [Korean]");
	if (chave == "FrmPrincipal.menuChinesTradicional") return QString::fromStdWString(L"Chin\u00eas Tradicional [Traditional Chinese]");
	if (chave == "FrmPrincipal.menuExcluirDiretorioSelecionado") return QString::fromStdWString(L"Excluir Diret\u00f3rio Selecionado");
	if (chave == "FrmPrincipal.menuInformacoesDiretorioArquivo") return QString::fromStdWString(L"Informa\u00e7\u00f5es do Diret\u00f3rio / Arquivo");

	if (chave == "FrmSobre.titulo") return QString::fromStdWString(L"Sobre o Catalogador");
	if (chave == "FrmSobre.label1") return QString::fromStdWString(L"HFSGuardaDir 2.0 - Catalogador de Diret\u00f3rios");
	if (chave == "FrmSobre.label2") return QString::fromStdWString(L"Desenvolvido em Java com Swing, Vers\u00e3o: 2.0");
	if (chave == "FrmSobre.label3") return QString::fromStdWString(L"Por Henrique Figueiredo de Souza");
	if (chave == "FrmSobre.label4") return QString::fromStdWString(L"Todos os direitos reservados, 2015");
	if (chave == "FrmSobre.Propriedade") return QString::fromStdWString(L"Propriedade");
	if (chave == "FrmSobre.Valor") return QString::fromStdWString(L"Valor");

	if (chave == "FrmSplash.label1") return QString::fromStdWString(L"HFSGuardaDiretorio 2.0");
	if (chave == "FrmSplash.label2") return QString::fromStdWString(L"Catalogador de Diret\u00f3rios");

	if (chave == "FrmCompararDiretorio.titulo") return QString::fromStdWString(L"Comparar Diret\u00f3rios");
	if (chave == "FrmCompararDiretorio.btnCompararDiretorios") return QString::fromStdWString(L"Comparar Diret\u00f3rios");
	if (chave == "FrmCompararDiretorio.btnSalvarLog") return QString::fromStdWString(L"Salvar Log");
	if (chave == "FrmCompararDiretorio.barraStatus1") return QString::fromStdWString(L"Total de diferen\u00e7as encontradas:");
	if (chave == "FrmCompararDiretorio.panelDiretorio1") return QString::fromStdWString(L"Diret\u00f3rio 1");
	if (chave == "FrmCompararDiretorio.labDiferencasEncontradas") return QString::fromStdWString(L"Diferen\u00e7as Encontradas");
	if (chave == "FrmCompararDiretorio.panelDiretorio2") return QString::fromStdWString(L"Diret\u00f3rio 2");
	if (chave == "FrmCompararDiretorio.NenhumaDiferencaEncontrada") return QString::fromStdWString(L"Nenhuma diferen\u00e7a encontrada!");
	if (chave == "FrmCompararDiretorio.DiretoriosNaoSelecionados") return QString::fromStdWString(L"Diret\u00f3rios n\u00e3o selecionados!");
	if (chave == "FrmCompararDiretorio.LogSalvoMemoDirSistema") return QString::fromStdWString(L"Log salvo no mesmo diret\u00f3rio do sistema!");

	if (chave == "FrmCadExtensao.titulo") return QString::fromStdWString(L"Cadastro de Extens\u00e3o de Arquivo");
	if (chave == "FrmCadExtensao.extensao") return QString::fromStdWString(L"Extens\u00e3o");
	if (chave == "FrmCadExtensao.icone") return QString::fromStdWString(L"\u00cdcone");
	if (chave == "FrmCadExtensao.btnIncluir") return QString::fromStdWString(L"Incluir");
	if (chave == "FrmCadExtensao.btnExcluir") return QString::fromStdWString(L"Excluir");
	if (chave == "FrmCadExtensao.menuExtensao") return QString::fromStdWString(L"Extens\u00e3o");
	if (chave == "FrmCadExtensao.menuExportarTodos") return QString::fromStdWString(L"Exportar Todos");
	if (chave == "FrmCadExtensao.menuImportarTodos") return QString::fromStdWString(L"Importar Todos");
	if (chave == "FrmCadExtensao.menuIncluirExtensao") return QString::fromStdWString(L"Incluir Extens\u00e3o");
	if (chave == "FrmCadExtensao.menuExcluirExtensao") return QString::fromStdWString(L"Excluir Extens\u00e3o");
	if (chave == "FrmCadExtensao.menuExcluirTodasExtensoes") return QString::fromStdWString(L"Excluir Todas Extens\u00f5es");
	if (chave == "FrmCadExtensao.menuExportarIcone") return QString::fromStdWString(L"Exportar para \u00cdcone");
	if (chave == "FrmCadExtensao.menuExportarGIF") return QString::fromStdWString(L"Exportar para GIF");
	if (chave == "FrmCadExtensao.menuExportarJPEG") return QString::fromStdWString(L"Exportar para JPEG");
	if (chave == "FrmCadExtensao.menuExportarPNG") return QString::fromStdWString(L"Exportar para PNG");
	if (chave == "FrmCadExtensao.menuExportarTIFF") return QString::fromStdWString(L"Exportar para TIFF");
	if (chave == "FrmCadExtensao.menuImportarIconesArquivos") return QString::fromStdWString(L"Importar \u00cdcones dos Arquivos");
	if (chave == "FrmCadExtensao.menuExtrairIconesArquivos") return QString::fromStdWString(L"Extrair \u00cdcones dos Arquivos");
	if (chave == "FrmCadExtensao.ExtensaoJaCadastrada") return QString::fromStdWString(L"Extens\u00e3o j\u00e1 existe cadastrada!");
	if (chave == "FrmCadExtensao.ExtensaoSalvaSucesso") return QString::fromStdWString(L"Extens\u00e3o salva com sucesso!");
	if (chave == "FrmCadExtensao.ExtensaoCertezaExcluir") return QString::fromStdWString(L"Tem Certeza, que voc\u00ea deseja excluir esta extens\u00e3o?");
	if (chave == "FrmCadExtensao.ExtensaoCertezaTodosExcluir") return QString::fromStdWString(L"Tem Certeza, que voc\u00ea deseja excluir todas as extens\u00f5es?");
	if (chave == "FrmCadExtensao.ExtensaoExcluidaSucesso") return QString::fromStdWString(L"Extens\u00e3o exclu\u00edda com sucesso!");
	if (chave == "FrmCadExtensao.ExtensoesExcluidasSucesso") return QString::fromStdWString(L"Extens\u00f5es exclu\u00eddas com sucesso!");
	if (chave == "FrmCadExtensao.ExportarExtensao") return QString::fromStdWString(L"\u00cdcones salvos no mesmo diret\u00f3rio do sistema!");
	if (chave == "FrmCadExtensao.menuExportarBitmap") return QString::fromStdWString(L"Exportar para Bitmap");

	if (chave == "FrmInfoDiretorio.titulo") return QString::fromStdWString(L"Informa\u00e7\u00f5es do Diret\u00f3rio / Arquivo");
	if (chave == "FrmInfoDiretorio.panelLegenda") return QString::fromStdWString(L"Legenda dos Atributos");
	if (chave == "FrmInfoDiretorio.labArquivoComum") return QString::fromStdWString(L"[ARQ] - Arquivo comum");
	if (chave == "FrmInfoDiretorio.labArquivoOculto") return QString::fromStdWString(L"[HID] - Arquivo Oculto");
	if (chave == "FrmInfoDiretorio.labArquivoSistema") return QString::fromStdWString(L"[SYS] - Arquivo de Sistema");
	if (chave == "FrmInfoDiretorio.labDiretorio") return QString::fromStdWString(L"[DIR] - Diret\u00f3rio");
	if (chave == "FrmInfoDiretorio.labVolumeID") return QString::fromStdWString(L"[VOL] - Volume ID");
	if (chave == "FrmInfoDiretorio.labArquivoSomenteLeitura") return QString::fromStdWString(L"[ROL] - Arquivo Somente Leitura");
	if (chave == "FrmInfoDiretorio.item") return QString::fromStdWString(L"Item");
	if (chave == "FrmInfoDiretorio.descricao") return QString::fromStdWString(L"Descri\u00e7\u00e3o");

	if (chave == "FrmImportarDiretorio.titulo") return QString::fromStdWString(L"Importando Diret\u00f3rio");
	if (chave == "FrmImportarDiretorio.barraStatus1") return QString::fromStdWString(L"Total de linhas sendo processadas:");
	if (chave == "FrmImportarDiretorio.DiretorioExisteCatalogo") return QString::fromStdWString(L"O diret\u00f3rio j\u00e1 existe no cat\u00e1logo!");

	if (chave == "Dialogo.info") return QString::fromStdWString(L"Informa\u00e7\u00e3o");
	if (chave == "Dialogo.erro") return QString::fromStdWString(L"Erro");
	if (chave == "Dialogo.confirma") return QString::fromStdWString(L"Confirma");
	if (chave == "Dialogo.entrada") return QString::fromStdWString(L"Informa");
	if (chave == "Dialogo.yesButtonText") return QString::fromStdWString(L"Sim");
	if (chave == "Dialogo.yesButtonMnemonic") return QString::fromStdWString(L"S");
	if (chave == "Dialogo.cancelButtonText") return QString::fromStdWString(L"Cancelar");
	if (chave == "Dialogo.cancelButtonMnemonic") return QString::fromStdWString(L"C");
	if (chave == "Dialogo.noButtonText") return QString::fromStdWString(L"N\u00e3o");
	if (chave == "Dialogo.noButtonMnemonic") return QString::fromStdWString(L"N");
	if (chave == "Dialogo.okButtonText") return QString::fromStdWString(L"OK");
	if (chave == "Dialogo.okButtonMnemonic") return QString::fromStdWString(L"O");

	if (chave == "EscolhaArquivo.ApproveButtonText") return QString::fromStdWString(L"Escolha o Diret\u00f3rio");
	if (chave == "EscolhaArquivo.ApproveButtonMnemonic") return QString::fromStdWString(L"D");
	if (chave == "EscolhaArquivo.ApproveButtonToolTipText") return QString::fromStdWString(L"Confirme a escolha do diret\u00f3rio.");
	if (chave == "EscolhaArquivo.lookInLabelMnemonic") return QString::fromStdWString(L"E");
	if (chave == "EscolhaArquivo.lookInLabelText") return QString::fromStdWString(L"Examinar em");
	if (chave == "EscolhaArquivo.saveInLabelMnemonic") return QString::fromStdWString(L"S");
	if (chave == "EscolhaArquivo.saveInLabelText") return QString::fromStdWString(L"Salvar em");
	if (chave == "EscolhaArquivo.upFolderToolTipText") return QString::fromStdWString(L"Um n\u00edvel acima");
	if (chave == "EscolhaArquivo.upFolderAccessibleName") return QString::fromStdWString(L"Um n\u00edvel acima");
	if (chave == "EscolhaArquivo.homeFolderToolTipText") return QString::fromStdWString(L"Desktop");
	if (chave == "EscolhaArquivo.homeFolderAccessibleName") return QString::fromStdWString(L"Desktop");
	if (chave == "EscolhaArquivo.newFolderToolTipText") return QString::fromStdWString(L"Criar nova pasta");
	if (chave == "EscolhaArquivo.newFolderAccessibleName") return QString::fromStdWString(L"Criar nova pasta");
	if (chave == "EscolhaArquivo.listViewButtonToolTipText") return QString::fromStdWString(L"Lista");
	if (chave == "EscolhaArquivo.listViewButtonAccessibleName") return QString::fromStdWString(L"Lista");
	if (chave == "EscolhaArquivo.detailsViewButtonToolTipText") return QString::fromStdWString(L"Detalhes");
	if (chave == "EscolhaArquivo.detailsViewButtonAccessibleName") return QString::fromStdWString(L"Detalhes");
	if (chave == "EscolhaArquivo.fileNameLabelMnemonic") return QString::fromStdWString(L"N");
	if (chave == "EscolhaArquivo.fileNameLabelText") return QString::fromStdWString(L"Nome do arquivo");
	if (chave == "EscolhaArquivo.filesOfTypeLabelMnemonic") return QString::fromStdWString(L"A");
	if (chave == "EscolhaArquivo.filesOfTypeLabelText") return QString::fromStdWString(L"Arquivos do tipo");
	if (chave == "EscolhaArquivo.fileNameHeaderText") return QString::fromStdWString(L"Nome");
	if (chave == "EscolhaArquivo.fileSizeHeaderText") return QString::fromStdWString(L"Tamanho");
	if (chave == "EscolhaArquivo.fileTypeHeaderText") return QString::fromStdWString(L"Tipo");
	if (chave == "EscolhaArquivo.fileDateHeaderText") return QString::fromStdWString(L"Data");
	if (chave == "EscolhaArquivo.fileAttrHeaderText") return QString::fromStdWString(L"Atributos");
	if (chave == "EscolhaArquivo.cancelButtonText") return QString::fromStdWString(L"Cancelar");
	if (chave == "EscolhaArquivo.cancelButtonMnemonic") return QString::fromStdWString(L"C");
	if (chave == "EscolhaArquivo.cancelButtonToolTipText") return QString::fromStdWString(L"Cancelar");
	if (chave == "EscolhaArquivo.openButtonText") return QString::fromStdWString(L"Abrir");
	if (chave == "EscolhaArquivo.openButtonMnemonic") return QString::fromStdWString(L"A");
	if (chave == "EscolhaArquivo.openButtonToolTipText") return QString::fromStdWString(L"Abrir");
	if (chave == "EscolhaArquivo.saveButtonText") return QString::fromStdWString(L"Salvar");
	if (chave == "EscolhaArquivo.saveButtonMnemonic") return QString::fromStdWString(L"S");
	if (chave == "EscolhaArquivo.saveButtonToolTipText") return QString::fromStdWString(L"Salvar");
	if (chave == "EscolhaArquivo.updateButtonText") return QString::fromStdWString(L"Alterar");
	if (chave == "EscolhaArquivo.updateButtonMnemonic") return QString::fromStdWString(L"A");
	if (chave == "EscolhaArquivo.updateButtonToolTipText") return QString::fromStdWString(L"Alterar");
	if (chave == "EscolhaArquivo.helpButtonText") return QString::fromStdWString(L"Ajuda");
	if (chave == "EscolhaArquivo.helpButtonMnemonic") return QString::fromStdWString(L"A");
	if (chave == "EscolhaArquivo.helpButtonToolTipText") return QString::fromStdWString(L"Ajuda");
	if (chave == "EscolhaArquivo.acceptAllFileFilterText") return QString::fromStdWString(L"Todos os arquivos (*.*)");
	if (chave == "EscolhaArquivo.filtroTXT") return QString::fromStdWString(L"Arquivo TXT (*.txt)");
	if (chave == "EscolhaArquivo.filtroCSV") return QString::fromStdWString(L"Arquivo CSV (*.csv)");
	if (chave == "EscolhaArquivo.filtroHTML") return QString::fromStdWString(L"Arquivo HTML (*.html)");
	if (chave == "EscolhaArquivo.filtroXML") return QString::fromStdWString(L"Arquivo XML (*.xml)");
	if (chave == "EscolhaArquivo.filtroSQL") return QString::fromStdWString(L"Arquivo SQL (*.sql)");
	if (chave == "EscolhaArquivo.filtroBMP") return QString::fromStdWString(L"Arquivo BMP (*.bmp)");
	if (chave == "EscolhaArquivo.filtroICO") return QString::fromStdWString(L"Arquivo ICO (*.ico)");
	if (chave == "EscolhaArquivo.filtroGIF") return QString::fromStdWString(L"Arquivo GIF (*.gif)");
	if (chave == "EscolhaArquivo.filtroPNG") return QString::fromStdWString(L"Arquivo JPEG (*.png)");
	if (chave == "EscolhaArquivo.filtroJPG") return QString::fromStdWString(L"Arquivo PNG (*.jpg)");
	if (chave == "EscolhaArquivo.filtroTIF") return QString::fromStdWString(L"Arquivo TIFF (*.tif)");
	if (chave == "EscolhaArquivo.todosDiretorios") return QString::fromStdWString(L"Todos os diret\u00f3rios");

    return chave;
}

QIcon Rotinas::getImagem(const QString &arquivo) {
    QString arq = ":/imagens/" + arquivo;
    QIcon icone(arq);

    return icone;
}

QByteArray Rotinas::getImagemByteArray(const QString &arquivo) {
    QString arq = ":/imagens/" + arquivo;
    return LoadFromFile(arq);
}

QString Rotinas::iconeToBase64(const QIcon &icone, int tamanho){
    QImage image(icone.pixmap(tamanho, tamanho).toImage());
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    image.save(&buffer, "PNG");
    QString iconBase64 = QString::fromLatin1(byteArray.toBase64().data());
    return iconBase64;
}

QByteArray Rotinas::QImageToQByteArray(const QImage &image){
	QByteArray bArray;
    QBuffer buffer(&bArray);
    buffer.open(QIODevice::WriteOnly);

    QDataStream out(&buffer);
    out << image;

    buffer.close();

	return bArray;
}

QImage Rotinas::QByteArrayToQImage(const QByteArray &bArray){
	QByteArray byteArray = bArray;
	QImage image;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::ReadOnly);

    QDataStream in(&buffer);
    in >> image;

    buffer.close();

	return image;
}

QPixmap Rotinas::QByteArrayToQPixmap(const QByteArray &bArray, const QString &formato){
	QPixmap pixmap;
	pixmap.loadFromData(bArray, formato.toUpper().toStdString().c_str());
	return pixmap;
}

QByteArray Rotinas::QPixmapToQByteArray(const QPixmap &pixmap, const QString &formato){
	QByteArray bArray;
    QBuffer buffer(&bArray);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, formato.toUpper().toStdString().c_str());
	return bArray;
}

QByteArray Rotinas::ArquivoToQByteArray(const QString &arquivo, int tamanho, const QString &formato){
    QByteArray imagemSaida;
    QImage img;
    QImageWriter writer(arquivo, formato.toUpper().toStdString().c_str());
    writer.write(img);

    QImage img2 = img.scaled(tamanho, tamanho, Qt::KeepAspectRatio); // | Qt::SmoothTransformation);

	imagemSaida = QImageToQByteArray(img2);

    return imagemSaida;
}

QByteArray Rotinas::BmpParaImagem(const QByteArray &imagemBMP, const QString &formato){
	QPixmap pixmap = QByteArrayToQPixmap(imagemBMP, "BMP");
	QByteArray saida = QPixmapToQByteArray(pixmap, formato);
    return saida;
}

bool Rotinas::SListSaveToFile(const QStringList &lista, const QString &sNomeArquivo) {
    QFile fOut(sNomeArquivo);

    if (fOut.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream texto(&fOut);
        for (int i = 0; i < lista.size(); ++i) {
          texto << lista.at(i) << '\n';
        }
    } else {
        qDebug() << "erro abrindo arquivo de saida";
        return false;
    }
    fOut.close();

    return true;
}

QStringList Rotinas::SListLoadFromFile(const QString &sNomeArquivo) {
    QStringList lista;
    QFile fIn(sNomeArquivo);

    if (fIn.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream texto(&fIn);
        while (!texto.atEnd()) {
            lista += texto.readLine();
        }
    } else {
        qDebug() << "erro abrindo arquivo de saida";
        return lista;
    }
    fIn.close();

    return lista;
}

QStringList Rotinas::SListSeparador(const QString &texto, const char separador) {
    QStringList lista;

    if (texto.indexOf(separador) > 0) {
        QString pedaco = "";
        for (int i = 0; i < texto.length(); i++) {
            pedaco += texto[i];
            if (texto[i] == separador) {
                lista.append(pedaco.mid(0, pedaco.length() - 1));
                pedaco = "";
            }
        }
        lista.append(pedaco);
	}
	else {
		lista.append(texto);
	}

    return lista;
}

/*
QPixmap Rotinas::extrairIconeArquivo(const QString &sNomeArquivo) {
    WORD filtro = 0;
	wchar_t *arquivo = new wchar_t[sNomeArquivo.size() + 1];
	arquivo[0] = '\0';

	sNomeArquivo.toWCharArray(arquivo);
			
    HINSTANCE hInstance = GetModuleHandle(NULL);
    HICON icone = ExtractAssociatedIcon(hInstance, arquivo, &filtro);

    QPixmap pixmap = QtWin::fromHICON(icone);

	arquivo[sNomeArquivo.size()] = 0;
	delete[] arquivo;

	return pixmap;
}
*/

QStringList Rotinas::listarArquivosDiretorios(const QString &sDiretorio) {
	QDir qdir;
	QStringList lista;
	QString sCaminho;
	QFileInfo info;

	qdir.setPath(sDiretorio);
	if (qdir.exists()) {
		if (!qdir.entryInfoList().isEmpty()) {
			
			for (int i = 0; i < qdir.entryInfoList().size(); ++i) {
				info = qdir.entryInfoList().at(i);
				if (info.fileName() != "." && info.fileName() != "..") {
					sCaminho = sDiretorio + QDir::separator() + info.fileName();
					lista.append(sCaminho);
				}
			}
		}
	}
	
	return lista;
}


void Rotinas::testar(){
	QString sApp = qApp->applicationFilePath();
	QString sDir = "    c:\\ago%ra\\CAMINHO\\teste.olha.depois    ";

	QStringList listaDir = Rotinas::listarArquivosDiretorios("c:/Temp");
	for (int i = 0; i < listaDir.size(); i++)
	{
		qDebug() << "listarArquivosDiretorios[" << i << "]: " << listaDir[i];
	}

	qDebug() << "sDir: [" << sDir << "]";

	qDebug() << "AppDirPath: " << sApp;
	qDebug() << "FileExists: " << (Rotinas::FileExists(sApp) ? "true" : "false");
	qDebug() << "DirectoryExists: " << (Rotinas::DirectoryExists(sApp) ? "true" : "false");
	qDebug() << "ExtractFilePath: " << Rotinas::ExtractFilePath(sApp);
	qDebug() << "ExtractFileName: " << Rotinas::ExtractFileName(sApp);

	qDebug() << "Length(): " << sDir.length();
	qDebug() << "Trim(): " << sDir.trimmed();
	qDebug() << "tamanho Trim(): " << sDir.trimmed().length();
	qDebug() << "LowerCase(): " << sDir.toLower();
	qDebug() << "UpperCase(): " << sDir.toUpper();
	qDebug() << "Pos('.'): " << Rotinas::Pos(".", sDir);
	qDebug() << "LastDelimiter('.'): " << Rotinas::LastDelimiter(".", sDir);
	qDebug() << "QuotedStr(): " << Rotinas::QuotedStr(sDir);
	qDebug() << "IntToStr(245789): " << QString::number(245789); //Rotinas::IntToStr(245789);
	
	QString inteiro = "245789";
	qDebug() << "StrToInt() --> 245789: " << inteiro.toInt();   //Rotinas::StrToInt("245789");

	QString longo = "4200155136";
	qDebug() << "StrToLong() --> 4200155136: " << longo.toLongLong();
	qDebug() << "DoubleToStr(15.557878): " << QString::number(15.557878);

	qDebug() << "SubString(): " << Rotinas::SubString(sDir, 8, 6);
	qDebug() << "StringReplaceAll(): " << Rotinas::StringReplaceAll(sDir, "\\", "@");
	qDebug() << "trocaSeparador(): " << Rotinas::trocaSeparador(sDir);
	qDebug() << "testaNull(NULL): " << Rotinas::testaNull(NULL);

	qDebug() << "StartsStr(JOGOS2_DVDS/TESTE): " << (Rotinas::StartsStr("DVD", "JOGOS2_DVDS/TESTE") ? "true" : "false");
	qDebug() << "StartsStr(DVDSJOGOS2_/TESTE): " << (Rotinas::StartsStr("DVD", "DVDSJOGOS2_/TESTE") ? "true" : "false");

    qDebug() << "ContainsStr(JOGOS2_DVDS/TESTE): " << (Rotinas::ContainsStr("DVDSJOGOS2_/TESTE", "DVDSJOGOS2_/TESTE") ? "true" : "false");
    qDebug() << "EndsStr(TESTE, JOGOS2_DVDS/TESTE): " << (Rotinas::EndsStr("TESTE", "DVDSJOGOS2_/TESTE") ? "true" : "false");

	qDebug() << "formataDate(): ", Rotinas::formataDate(Rotinas::FORMATO_DATAHORA, QDateTime::currentDateTime());
	QDateTime dt = Rotinas::StringToDate("03/02/2017 15:23:32");
	qDebug() << "StringToDate(03/02/2017 15:23:32): ", dt.toString(Rotinas::FORMATO_DATAHORA);

	qDebug() << "FormatLong(4200155136): " << Rotinas::FormatLong(4200155136);
	qDebug() << "FormatDouble(15.544878): " << Rotinas::FormatDouble(15.544878);
	qDebug() << "FormatDouble(15.547878): " << Rotinas::FormatDouble(15.547878);
	qDebug() << "FormatDouble(15.557878): " << Rotinas::FormatDouble(15.557878);
	qDebug() << "FormatDouble(15.567878): " << Rotinas::FormatDouble(15.567878);

	qDebug() << "MontaTamanho() --> 3.91 GB: " << Rotinas::MontaTamanho(4200155136);
	qDebug() << "MontaTamanho() --> 3.50 GB: " << Rotinas::MontaTamanho(3757244416);
	qDebug() << "MontaTamanho() --> 2.29 GB: " << Rotinas::MontaTamanho(2455207936);
	qDebug() << "MontaTamanho() --> 888.18 PB: " << Rotinas::MontaTamanhoBig(999999999999999999.9999);

	QStringList lista;

	lista = Rotinas::SListSeparador(sDir, '\\');

    for (int i = 0; i < lista.size(); i++)
	{
		qDebug() << "SListSeparador[]: " << i << lista[i];
	}

	QString arquivo = Rotinas::ExtractFilePath(sApp) + "\\exemplo.txt";
	qDebug() << "arquivo: " << arquivo;

	if (Rotinas::SListSaveToFile(lista, arquivo)) {

		if (Rotinas::FileExists(arquivo)) {

			lista = Rotinas::SListLoadFromFile(arquivo);
            for (int i = 0; i < lista.size(); i++) {
				qDebug() << "SListLoadFromFile[]: " << i << lista[i];
			}

			if (Rotinas::DeleteFromFile(arquivo)) {
				if (!Rotinas::FileExists(arquivo)) {
					qDebug() << "DeleteFromFile: OK";
				}
			}
			else {
				qDebug() << "DeleteFromFile: FALHOU";
			}

		}

	}


	QString arqMemoria, arqImagem, arqImagem2;
    QPixmap icone; //Rotinas::extrairIconeArquivo(sApp);
	QImage imagem = icone.toImage();
	
	if (!imagem.isNull()) {
		qDebug() << "extrairIconeArquivo OK";
		
		QByteArray mbuf = Rotinas::QImageToQByteArray(imagem);
		if (!mbuf.isEmpty()) {
			qDebug() << "ImageToMemoryBuffer OK";
		}
		else {
			qDebug() << "ImageToMemoryBuffer FALHOU";
		}

		QImage imgbuf = Rotinas::QByteArrayToQImage(mbuf);
		if (!imgbuf.isNull()) {
			qDebug() << "MemoryBufferToImage OK";

			arqMemoria = Rotinas::ExtractFilePath(sApp) + "\\memoria.bmp";
			qDebug() << "arquivo de imagem da Memoria: " << arqMemoria;

			if (imagem.save(arqMemoria, "BMP")) {
				qDebug() << "arquivo de imagem da Memoria SALVO";
			}
			else {
				qDebug() << "arquivo de imagem da Memoria FALHOU";
			}
		}
		else {
			qDebug() << "MemoryBufferToImage FALHOU";
		}


		arqImagem = Rotinas::ExtractFilePath(sApp) + "\\exemplo.bmp";
		qDebug() << "arquivo da imagem: " << arqImagem;

		if (imagem.save(arqImagem, "BMP")) {

			if (Rotinas::FileExists(arqImagem)) {
				qDebug() << "arquivo da imagem SALVO";

				QByteArray buf = Rotinas::LoadFromFile(arqImagem);
				if (!buf.isEmpty()) {
					qDebug() << "LoadFromFile OK";

					arqImagem2 = Rotinas::ExtractFilePath(sApp) + "\\exemplo2.bmp";
					qDebug() << "arquivo da imagem a ser salva: " << arqImagem2;

					Rotinas::SaveToFile(buf, arqImagem2);
					if (Rotinas::FileExists(arqImagem2)) {
						qDebug() << "SaveToFile SALVO";
					}
					else {
						qDebug() << "SaveToFile FALHOU";
					}
				}
				else {
					qDebug() << "LoadFromFile FALHOU";
				}
			}
			else
			{
				qDebug() << "arquivo da imagem FALHOU";
			}
		}

	}
	else {
		qDebug() << "extrairIconeArquivo FALHOU";
	}

	Rotinas::DeleteFromFile(arqMemoria);
	Rotinas::DeleteFromFile(arqImagem);
	Rotinas::DeleteFromFile(arqImagem2);

}

}
}
