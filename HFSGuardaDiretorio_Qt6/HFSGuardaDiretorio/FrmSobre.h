#ifndef FRMSOBRE_H
#define FRMSOBRE_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class FrmSobre;
}
QT_END_NAMESPACE

class FrmSobre : public QDialog
{
    Q_OBJECT

public:
    explicit FrmSobre(QWidget *parent = 0);
    ~FrmSobre();

private:
    Ui::FrmSobre *ui;
};

#endif // FRMSOBRE_H
