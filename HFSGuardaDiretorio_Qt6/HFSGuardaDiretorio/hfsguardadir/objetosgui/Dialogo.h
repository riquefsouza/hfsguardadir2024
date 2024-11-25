#ifndef DIALOGO_H
#define DIALOGO_H

#include <QString>
#include <QMessageBox>
#include <QInputDialog>

namespace hfsguardadir {

namespace objetosgui {

class Dialogo
{
public:
    Dialogo();

    static void mensagemErro(QWidget *pai, const QString &recurso, const QString &texto);
    static void mensagemErro(QWidget *pai, const QString &recurso);
    static void mensagemInfo(QWidget *pai, const QString &recurso);
    static QMessageBox::StandardButton confirma(QWidget *pai, const QString &recurso);
    static QString entrada(QWidget *pai, const QString &recurso);
    static QString entrada(QWidget *pai, const QString &recurso,
        const QString &valorInicial);
};

}
}

#endif // DIALOGO_H
