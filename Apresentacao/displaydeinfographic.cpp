#include "displaydeinfographic.h"

DisplayDeInfoGraphic::DisplayDeInfoGraphic(QString textoInfo, QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    // inicializa imagem do display
    setPos(0,0);
    setPixmap(QPixmap(":/images/Apresentacao/rsc/display.png"));

    texto = new QGraphicsTextItem(textoInfo, this);
    texto->setFont(QFont("times",24));
    texto->setDefaultTextColor(Qt::white);
    int x = boundingRect().x() + (boundingRect().width() - texto->boundingRect().width())/2 ;
    int y = 20;
    texto->setPos(x,y);

    botao = new BotaoGraphic("Ok", this);
    x = boundingRect().x() + (boundingRect().width() - botao->boundingRect().width())/2 ;
    y = 70;
    botao->setPos(x,y);

    connect(botao, SIGNAL(clicked()), this, SLOT(fim()));
}

void DisplayDeInfoGraphic::fim(){
    emit ok_clicked();
    delete this;
}
