#ifndef PECAGRAPHIC
#define PECAGRAPHIC

#include <QGraphicsEllipseItem>
#include <QGraphicsPixmapItem>
#include <QPointF>
#include <QTimer>
#include <QColor>
#include <QBrush>

class PecaGraphic: public QObject, public QGraphicsEllipseItem{
    Q_OBJECT
public:
    // inicialização
    PecaGraphic(QColor cor, int largura, QPointF pontoDestino, QGraphicsItem *parent=0);

    // destrutor
    ~PecaGraphic();

    // inicia animações
    void comecaAnimacao();
    void jogaFora(bool ultima);

public slots:
    void move();
    void moveUp();
signals:
    void stopped();
    void stoppedLast();
private:
    QGraphicsPixmapItem * efeito;   // efeito gráfico aplicado no objeto de interface da peça
    QPointF pontoDestino;           // ponto destino da peça durante animação
    QTimer * timer;                 // timer usado pra criar animação
    bool ultima;                    // indica se é a última peça sendo removida do tabuleiro
};

#endif // PECAGRAPHIC

