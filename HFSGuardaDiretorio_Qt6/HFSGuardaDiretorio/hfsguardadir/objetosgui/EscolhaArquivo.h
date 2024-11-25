#ifndef ESCOLHAARQUIVO_H
#define ESCOLHAARQUIVO_H

#include <QFileDialog>

namespace hfsguardadir {

namespace objetosgui {

class EscolhaArquivo
{
private:
	EscolhaArquivo();
	static QString getTextoExtensao(const QString &extensao);

public:    
    static QString abrirDiretorio(QWidget *parent);
	static QString abrirArquivo(QWidget *parent);
	static QString abrirArquivo(QWidget *parent, const QString &arquivo, const QString &extensao);
	static QString salvarArquivo(QWidget *parent, const QString &arquivo, const QString &extensao);

};

}
}

#endif // ESCOLHAARQUIVO_H
