#include "./Apresentacao/mainwindow.h"
#include <QApplication>

/*
TODO LIST:
- esperar a peça chegar no final antes de piscar as bolas
- melhorar animação de remoção das peças
- mudar titulo do jogo
- criar signal q desativa hover com objetos
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
