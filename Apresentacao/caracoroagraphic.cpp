#include "caracoroagraphic.h"

CaraCoroaGraphic::CaraCoroaGraphic(int cara, QGraphicsItem* parent): QGraphicsPixmapItem(parent){
    this->cara = cara;

    // atualiza imagem do botão
    setPos(0, 0);
    setPixmap(QPixmap(":/images/Apresentacao/rsc/moeda.png"));

    // inicializa imagem da moeda
    QGraphicsPixmapItem * moeda = new QGraphicsPixmapItem(this);
    if(cara == 0)
        moeda->setPixmap(QPixmap(":/images/Apresentacao/rsc/cara.png"));
    else
        moeda->setPixmap(QPixmap(":/images/Apresentacao/rsc/coroa.png"));
    moeda->setScale(0.5);
    moeda->setPos(9,9);

    // ativar responsividade a hover events
    setAcceptHoverEvents(true);
}

void CaraCoroaGraphic::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit clicked(cara);
}

void CaraCoroaGraphic::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    setPixmap(QPixmap(":/images/Apresentacao/rsc/moeda_selecionada.png"));
    emit mudouMoeda(cara);
}

void CaraCoroaGraphic::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    setPixmap(QPixmap(":/images/Apresentacao/rsc/moeda.png"));
}
