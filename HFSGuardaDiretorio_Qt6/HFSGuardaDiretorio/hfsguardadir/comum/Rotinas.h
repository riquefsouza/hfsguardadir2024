#ifndef ROTINAS_H
#define ROTINAS_H

#include <QString>
#include <QtSql>

#include "hfsguardadir/objetos/ConexaoParams.h"

using namespace hfsguardadir::objetos;

namespace hfsguardadir {

namespace comum {

enum TipoExportar {
    teTXT, teCSV, teHTML, teXML, teSQL
};

enum TipoExportarExtensao {
    teNUL, teBMP, teICO, teGIF, teJPG, tePNG, teTIF
};

struct Progresso {
    int minimo;
    int maximo;
    int posicao;
    int passo;
    QString log;
};

typedef void IProgressoLog(Progresso);

class Rotinas
{
private:
    QSqlDatabase dbConexao;
    Rotinas();
    Rotinas(Rotinas const&);
    Rotinas& operator=(Rotinas const&);
    static Rotinas* instancia;

public:
	QIcon arquivoIcone;
	QIcon cdouroIcone;
	QIcon diretorioIcone;
	QIcon dirabertoIcone;

    static const QString HFSGUARDADIR;

    static const char BARRA_NORMAL = '\\';
    static const char BARRA_INVERTIDA = '/';

    static const QString FORMATO_DATA;
    static const QString FORMATO_DATAHORA;
    static const QString FORMATO_DHARQUIVO;
    static const QString EXTENSAO_BMP;
    static const QString EXTENSAO_ICO;
    static const QString EXTENSAO_GIF;
    static const QString EXTENSAO_JPEG;
    static const QString EXTENSAO_PNG;
    static const QString EXTENSAO_TIFF;

    static Rotinas* getInstancia();

    static void CentralizaWidget(QWidget *widget);

    static int LastDelimiter(const QString &subtexto, const QString &texto);
    static int LastDelimiter(char subtexto, const QString &texto);
    static int Pos(const QString &subtexto, const QString &texto);
    static int Pos(char subtexto, const QString &texto);
    static bool StartsStr(const QString &subtexto, const QString &texto);
    static bool ContainsStr(const QString &texto, const QString &subtexto);
    static bool EndsStr(const QString &subtexto, const QString &texto);
    static QString SubString(const QString &texto, int inicio, int tamanho);
    static QString StringReplaceAll(const QString &texto, const QString &velho,
            const QString &novo);
    static QString QuotedStr(const QString &texto);
    static QString QuotedStr(char texto);
    static QString formataDate(const QString &formato, const QDateTime &dt);
    static QDateTime StringToDate(const QString &sData);
    static QString FormatLong(long valor);
    static QString FormatDouble(long double valor);

	static QString MontaTamanhoBig(long double nTam);
	static QString MontaTamanho(long long nTam);

    static QString testaNull(const QString &res);
    static QString trocaSeparador(const QString &texto);
    static QString ExtractFilePath(const QString &sCaminho);
    static QString ExtractFileName(const QString &sCaminho);
    static bool FileExists(const QString &sNomeArquivo);
    static bool DirectoryExists(const QString &sNomeArquivo);
    static bool DeleteFromFile(const QString &sNomeArquivo);
    static void SaveToFile(const QByteArray &imagem, const QString &sNomeArquivo);
    static QByteArray LoadFromFile(const QString &sNomeArquivo);
    static QString getRecurso(const QString &chave);
    static QIcon getImagem(const QString &arquivo);
    static QByteArray getImagemByteArray(const QString &arquivo);

    QSqlDatabase getConexao();
    void Conectar(QString &banco);
    QSqlDatabase Conectar(ConexaoParams cp);
    void Desconectar();
    void Desconectar(QSqlDatabase con);
    bool criarVisao(const QString &visao);
    bool execConsulta(const QString &sSQL);

    static QString iconeToBase64(const QIcon &icone, int tamanho);
    static QByteArray QImageToQByteArray(const QImage &image);
    static QImage QByteArrayToQImage(const QByteArray &bArray);
    static QPixmap QByteArrayToQPixmap(const QByteArray &bArray, const QString &formato);
    static QByteArray QPixmapToQByteArray(const QPixmap &pixmap, const QString &formato);

    static QByteArray ArquivoToQByteArray(const QString &arquivo, int tamanho, const QString &formato);
    static QByteArray BmpParaImagem(const QByteArray &imagemBMP, const QString &formato);

    static bool SListSaveToFile(const QStringList &lista, const QString &sNomeArquivo);
    static QStringList SListLoadFromFile(const QString &sNomeArquivo);
    static QStringList SListSeparador(const QString &texto, const char separador);

    //static QPixmap extrairIconeArquivo(const QString &sNomeArquivo);
	static QStringList listarArquivosDiretorios(const QString &sDiretorio);

	void testar();
};

}
}

#endif // ROTINAS_H
