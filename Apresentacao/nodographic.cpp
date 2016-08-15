#include "nodographic.h"

NodoGraphic::NodoGraphic(QGraphicsItem* parent): QGraphicsPixmapItem(parent){
    setPixmap(QPixmap(":/images/Apresentacao/rsc/nodo.png"));
}
