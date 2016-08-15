#ifndef CARACOROAGRAPHIC
#define CARACOROAGRAPHIC

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>

class CaraCoroaGraphic: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    // inicialização
    CaraCoroaGraphic(int cara, QGraphicsItem* parent=NULL);

    // interação com mouse
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
signals:
    void clicked(int cara);
    void mudouMoeda(int cara);
private:
    int cara;       // =0 se for cara, =1 se for coroa (precisa ser int pq o signal usado usa int)
};

#endif // CARACOROAGRAPHIC

