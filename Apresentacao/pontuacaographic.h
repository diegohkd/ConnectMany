#ifndef PONTUACAOGRAPHIC
#define PONTUACAOGRAPHIC

#include <QGraphicsTextItem>
#include <QFont>

class PontuacaoGraphic: public QGraphicsTextItem{
public:
    // inicialização
    PontuacaoGraphic(QGraphicsItem * parent=0);

    // alterações da pontuação
    void incrementa();
    void zerar();

    // getter
    int getPontuacao();
private:
    int pontuacao;      // armazena a pontuação
};

#endif // PONTUACAOGRAPHIC

