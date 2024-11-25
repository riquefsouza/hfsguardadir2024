QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    FrmCadExtensao.cpp \
    FrmCompararDiretorio.cpp \
    FrmImportarDiretorio.cpp \
    FrmInfoDiretorio.cpp \
    FrmSobre.cpp \
    FrmSplash.cpp \
    hfsguardadir/catalogador/Catalogador.cpp \
    hfsguardadir/catalogador/RotuloRaiz.cpp \
    hfsguardadir/comum/DiretorioXML.cpp \
    hfsguardadir/comum/Rotinas.cpp \
    hfsguardadir/objetos/Aba.cpp \
    hfsguardadir/objetos/Arquivo.cpp \
    hfsguardadir/objetos/ConexaoParams.cpp \
    hfsguardadir/objetos/Diretorio.cpp \
    hfsguardadir/objetos/DiretorioOrdem.cpp \
    hfsguardadir/objetos/Extensao.cpp \
    hfsguardadir/objetos/Importar.cpp \
    hfsguardadir/objetos/Tipo.cpp \
    hfsguardadir/objetosbo/AbaBO.cpp \
    hfsguardadir/objetosbo/DiretorioBO.cpp \
    hfsguardadir/objetosbo/ExtensaoBO.cpp \
    hfsguardadir/objetosbo/ImportarBO.cpp \
    hfsguardadir/objetosdao/AbaDAO.cpp \
    hfsguardadir/objetosdao/DiretorioDAO.cpp \
    hfsguardadir/objetosdao/ExtensaoDAO.cpp \
    hfsguardadir/objetosdao/VisaoDAO.cpp \
    hfsguardadir/objetosgui/Arvore.cpp \
    hfsguardadir/objetosgui/Dialogo.cpp \
    hfsguardadir/objetosgui/EscolhaArquivo.cpp \
    hfsguardadir/objetosgui/Tabela.cpp \
    main.cpp \
    FrmPrincipal.cpp

HEADERS += \
    FrmCadExtensao.h \
    FrmCompararDiretorio.h \
    FrmImportarDiretorio.h \
    FrmInfoDiretorio.h \
    FrmPrincipal.h \
    FrmSobre.h \
    FrmSplash.h \
    hfsguardadir/catalogador/Catalogador.h \
    hfsguardadir/catalogador/RotuloRaiz.h \
    hfsguardadir/comum/DiretorioXML.h \
    hfsguardadir/comum/Rotinas.h \
    hfsguardadir/objetos/Aba.h \
    hfsguardadir/objetos/Arquivo.h \
    hfsguardadir/objetos/ConexaoParams.h \
    hfsguardadir/objetos/Diretorio.h \
    hfsguardadir/objetos/DiretorioOrdem.h \
    hfsguardadir/objetos/Extensao.h \
    hfsguardadir/objetos/Importar.h \
    hfsguardadir/objetos/Tipo.h \
    hfsguardadir/objetosbo/AbaBO.h \
    hfsguardadir/objetosbo/DiretorioBO.h \
    hfsguardadir/objetosbo/ExtensaoBO.h \
    hfsguardadir/objetosbo/ImportarBO.h \
    hfsguardadir/objetosdao/AbaDAO.h \
    hfsguardadir/objetosdao/DiretorioDAO.h \
    hfsguardadir/objetosdao/ExtensaoDAO.h \
    hfsguardadir/objetosdao/VisaoDAO.h \
    hfsguardadir/objetosgui/Arvore.h \
    hfsguardadir/objetosgui/Dialogo.h \
    hfsguardadir/objetosgui/EscolhaArquivo.h \
    hfsguardadir/objetosgui/Tabela.h

FORMS += \
    FrmCadExtensao.ui \
    FrmCompararDiretorio.ui \
    FrmImportarDiretorio.ui \
    FrmInfoDiretorio.ui \
    FrmPrincipal.ui \
    FrmSobre.ui \
    FrmSplash.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES += \
    imagens/Abrir.bmp \
    imagens/Abrir32.bmp \
    imagens/Fechar.bmp \
    imagens/Fechar32.bmp \
    imagens/FotoRosto.bmp \
    imagens/arquivo.bmp \
    imagens/arquivo.gif \
    imagens/arquivo32.bmp \
    imagens/cdouro.bmp \
    imagens/cdouro.gif \
    imagens/cdprata.bmp \
    imagens/cdprata.gif \
    imagens/dir-aberto.gif \
    imagens/diretorio.gif \
    imagens/grandeicons.bmp \
    imagens/listaicons.bmp \
    imagens/relatorioicons.bmp \
    imagens/smallicons.bmp \
    imagens/splash.bmp \
    imagens/zip.bmp \
    imagens/zip32.bmp
