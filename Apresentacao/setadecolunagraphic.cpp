#include "setadecolunagraphic.h"

SetaDeColunaGraphic::SetaDeColunaGraphic(int coluna, QGraphicsItem* parent): QGraphicsPixmapItem(parent){
    this->coluna = coluna;

    // desenha o retângulo
    setPos(0,0);
    setPixmap(QPixmap(":/images/Apresentacao/rsc/seta.png"));

    // desenha seta
    QGraphicsPixmapItem * seta = new QGraphicsPixmapItem(this);
    seta->setPixmap(QPixmap(":/images/Apresentacao/rsc/seta_coluna.png"));
    seta->setScale(0.1);
    seta->setPos(10,2.5);

    // desenha efeito de transparência
    QGraphicsPixmapItem * brilho = new QGraphicsPixmapItem(this);
    brilho->setPixmap(QPixmap(":/images/Apresentacao/rsc/seta_brilho.png"));
    brilho->setPos(0,0);

    // ativar responsividade a hover events
    setAcceptHoverEvents(true);
}

void SetaDeColunaGraphic::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit clicked(coluna);
}

void SetaDeColunaGraphic::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    setPixmap(QPixmap(":/images/Apresentacao/rsc/seta_selecionada.png"));
}

void SetaDeColunaGraphic::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    setPixmap(QPixmap(":/images/Apresentacao/rsc/seta.png"));
}
