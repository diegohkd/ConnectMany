#ifndef SETADECOLUNAGRAPHIC
#define SETADECOLUNAGRAPHIC

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>

class SetaDeColunaGraphic: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    // inicialização
    SetaDeColunaGraphic(int coluna, QGraphicsItem* parent=NULL);

    // interação com mouse
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
signals:
    void clicked(int coluna);
private:
    int coluna; // índice da coluna
};

#endif // SETADECOLUNAGRAPHIC

