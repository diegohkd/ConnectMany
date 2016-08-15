#include "botaographic.h"

BotaoGraphic::BotaoGraphic(QString nome, QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    setPixmap(QPixmap(":/images/Apresentacao/rsc/botao.png"));

    // desenha o texto
    text = new QGraphicsTextItem(nome, this);
    text->setDefaultTextColor(Qt::white);
    int x = 55 - text->boundingRect().width()/2;
    int y = 15 - text->boundingRect().height()/2;
    text->setPos(x,y);

    // ativa responsividade a hover events
    setAcceptHoverEvents(true);
}

void BotaoGraphic::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit clicked();
}

void BotaoGraphic::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    setPixmap(QPixmap(":/images/Apresentacao/rsc/botao_2.png"));
}

void BotaoGraphic::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    setPixmap(QPixmap(":/images/Apresentacao/rsc/botao.png"));
}
