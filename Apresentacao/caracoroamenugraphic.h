#ifndef CARACOROAMENUGRAPHIC
#define CARACOROAMENUGRAPHIC

#include "caracoroagraphic.h"
#include "botaographic.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QSignalMapper>
#include <QFont>

class CaraCoroaMenuGraphic: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    // inicialização
    CaraCoroaMenuGraphic(QString nomeJogador1, QString nomeJogador2, QGraphicsItem* parent=NULL);

    // getters e setters
    bool getJogador1_comeca() const;
    void setJogador1_comeca(bool value);

public slots:
    void mudaPosSeta(int coluna);
    void moedaEscolhida(int coluna);
    void comecarJogo();
signals:
    void jogadorFoiEscolhido();
private:
    CaraCoroaGraphic *cara, *coroa; // objeto de interface das moedas cara e coroa
    QGraphicsTextItem * text;       // texto para passar informação ao usuário (p.e. quem começa)
    QGraphicsPixmapItem * seta;     // objeto de interface da seta que indica a moeda a ser escolhida
    bool jogador1_comeca;           // =true se jogador 1 foi escolhido para começar
    QString nome1, nome2;           // nome dos jogadores
    BotaoGraphic * botao;                  // botão para dar início ao jogo após ter escolhido quem começa
};

#endif // CARACOROAMENUGRAPHIC

