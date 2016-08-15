#ifndef DISPLAYDEINFOGRAPHIC
#define DISPLAYDEINFOGRAPHIC

#include "botaographic.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QFont>

class DisplayDeInfoGraphic: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    DisplayDeInfoGraphic(QString texto, QGraphicsItem *parent=NULL);
public slots:
    void fim();
signals:
    void ok_clicked();
private:
    QGraphicsTextItem * texto;      // texto para passar informação ao usuário
    BotaoGraphic * botao;           // botão para dar continuidade
};

#endif // DISPLAYDEINFOGRAPHIC

