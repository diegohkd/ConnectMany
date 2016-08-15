#ifndef BOTAOGRAPHIC
#define BOTAOGRAPHIC

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>

class BotaoGraphic: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    // inicialização
    BotaoGraphic(QString nome, QGraphicsItem* parent=NULL);

    // interação com mouse
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
signals:
    void clicked();
private:
    QGraphicsTextItem * text;   // texto interno do botão
};

#endif // BOTAOGRAPHIC

