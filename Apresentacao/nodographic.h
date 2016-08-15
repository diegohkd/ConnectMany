#ifndef NODOGRAPHIC
#define NODOGRAPHIC

#include <QGraphicsPixmapItem>

class NodoGraphic: public QObject, public QGraphicsPixmapItem{
public:
    // inicialização
    NodoGraphic(QGraphicsItem* parent=NULL);
};

#endif // NODOGRAPHIC

