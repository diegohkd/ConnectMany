#include "pecagraphic.h"

PecaGraphic::PecaGraphic(QColor cor, int largura, QPointF pontoDestino, QGraphicsItem *parent): QObject(), QGraphicsEllipseItem(parent){
    this->pontoDestino = pontoDestino;

    // inicializa retângulo da peça
    setRect(0,0,largura,largura);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(cor);
    setBrush(brush);

    // desenha efeito de transparência
    efeito = new QGraphicsPixmapItem(this);
    efeito->setPixmap(QPixmap(":/images/Apresentacao/rsc/peca.png"));
    efeito->setScale(0.1);
}

PecaGraphic::~PecaGraphic(){
    delete timer;
}

void PecaGraphic::comecaAnimacao(){
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    // start the timer
    timer->start(1);
}

void PecaGraphic::jogaFora(bool ultima){
    this->ultima = ultima;
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(moveUp()));

    // start the timer
    timer->start(2);
}

void PecaGraphic::move(){
    if (pos().y() < pontoDestino.y()){
        setPos(x(),y()+1);
    }
    else{
        // chegou ao destino final, então emite signal
        timer->stop();
        emit stopped();
    }

}

void PecaGraphic::moveUp(){
    if (pos().y() > 110){
        setPos(x(),y()-1);
    }
    else{
        // chegou ao destino final, então emite signal
        timer->stop();

        emit stoppedLast();
    }
}


