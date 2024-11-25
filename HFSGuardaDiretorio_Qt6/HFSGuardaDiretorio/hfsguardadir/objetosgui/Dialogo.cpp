#include "Dialogo.h"

#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosgui {

Dialogo::Dialogo()
{

}

void Dialogo::mensagemErro(QWidget *pai, const QString &recurso, const QString &texto) {
    QMessageBox::warning(pai, Rotinas::getRecurso("Dialogo.erro"),
                         Rotinas::getRecurso(recurso) + " " + texto);

    qDebug() << "warning: " << Rotinas::getRecurso(recurso) + " " + texto;
}

void Dialogo::mensagemErro(QWidget *pai, const QString &recurso) {
    mensagemErro(pai, recurso, QString(""));
}

void Dialogo::mensagemInfo(QWidget *pai, const QString &recurso) {
    QMessageBox::information(pai, Rotinas::getRecurso("Dialogo.info"),
                             Rotinas::getRecurso(recurso));
    qDebug() << "info: " << Rotinas::getRecurso(recurso);
}

QMessageBox::StandardButton Dialogo::confirma(QWidget *pai, const QString &recurso) {
    return QMessageBox::question(pai, Rotinas::getRecurso("Dialogo.confirma")
                          , Rotinas::getRecurso(recurso),
                          QMessageBox::Yes | QMessageBox::No);
}

QString Dialogo::entrada(QWidget *pai, const QString &recurso) {
    return QInputDialog::getText(pai, Rotinas::getRecurso("Dialogo.entrada"),
                                 Rotinas::getRecurso(recurso));
}

QString Dialogo::entrada(QWidget *pai, const QString &recurso,
        const QString &valorInicial) {
    bool bOk;

    QString texto = QInputDialog::getText(pai, Rotinas::getRecurso("Dialogo.entrada"),
                                 Rotinas::getRecurso(recurso),
                                 QLineEdit::Normal,valorInicial,&bOk);

     if (bOk && !texto.isEmpty()){
         return texto;
     } else {
         return "";
     }
}

}
}
