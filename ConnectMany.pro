#-------------------------------------------------
#
# Project created by QtCreator 2015-12-09T22:44:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ConnectMany
TEMPLATE = app


SOURCES += main.cpp\
        Apresentacao/mainwindow.cpp \
    Dominio/jogador.cpp \
    Apresentacao/jogoview.cpp \
    Dominio/jogo.cpp \
    Dominio/nodo.cpp \
    Dominio/peca.cpp \
    Dominio/tabuleiro.cpp \
    Dominio/contador.cpp \
    Apresentacao/nodographic.cpp \
    Apresentacao/pecagraphic.cpp \
    Apresentacao/pontuacaographic.cpp \
    Apresentacao/caracoroamenugraphic.cpp \
    Apresentacao/caracoroagraphic.cpp \
    Apresentacao/setadecolunagraphic.cpp \
    Apresentacao/botaographic.cpp \
    Apresentacao/displaydeinfographic.cpp

HEADERS  += \
    Dominio/jogador.h \
    Dominio/jogo.h \
    Dominio/nodo.h \
    Dominio/peca.h \
    Dominio/tabuleiro.h \
    Dominio/contador.h \
    Apresentacao/caracoroagraphic.h \
    Apresentacao/caracoroamenugraphic.h \
    Apresentacao/jogoview.h \
    Apresentacao/mainwindow.h \
    Apresentacao/nodographic.h \
    Apresentacao/pecagraphic.h \
    Apresentacao/pontuacaographic.h \
    Apresentacao/setadecolunagraphic.h \
    Apresentacao/botaographic.h \
    Apresentacao/displaydeinfographic.h

FORMS    += Apresentacao/mainwindow.ui

DISTFILES += \
    ConnectMany.pro.user

RESOURCES += \
    rsc.qrc

