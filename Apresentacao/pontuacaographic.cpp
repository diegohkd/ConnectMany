#include "pontuacaographic.h"

PontuacaoGraphic::PontuacaoGraphic(QGraphicsItem *parent): QGraphicsTextItem(parent){
    // inicializa pontuação
    pontuacao = 0;

    // desenha o texto
    setPlainText(QString::number(pontuacao) + QString(" vitórias"));
    setDefaultTextColor(Qt::black);
    setFont(QFont("times",24));
}

void PontuacaoGraphic::incrementa(){
    pontuacao++;
    if(pontuacao != 1)
        setPlainText(QString::number(pontuacao) + QString(" vitórias"));
    else
        setPlainText(QString::number(pontuacao) + QString(" vitória"));
}

int PontuacaoGraphic::getPontuacao(){
    return pontuacao;
}

void PontuacaoGraphic::zerar(){
    pontuacao = 0;
    setPlainText(QString::number(pontuacao) + QString(" vitórias"));
}

