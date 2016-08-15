#ifndef JOGO_H
#define JOGO_H

#include "jogador.h"
#include "tabuleiro.h"

class Jogo{
public:
    // inicialização
    Jogo();
    Jogo(unsigned short pecas_necessarias_pra_ganhar);
    int createJogadores(const QString &nome1, const QColor &cor1, const QString &nome2, const QColor &cor2);
    void createTabuleiro(int linhas, int colunas, unsigned short total_pecas_alinhadas_pra_ganhar);

    // destrutor
    ~Jogo();

    // execução do jogo
    int efetuaJogada(int coluna);
    void trocaJogador();
    void limpaTabuleiro();

    // getters e setters
    QString getNomeJogador1();
    QString getNomeJogador2();
    QColor getCorJogador1();
    QColor getCorJogador2();
    QColor getCorJogadorAtual();
    int getTamanhoNodo();
    int getColunas();
    int getLinhas();
    int getTotalPecasColuna(int coluna);
    int getNumeroJogadorAtual();
    QString getNomeJogador_atual();
    void setJogadorEscolhido(bool jogador1);
    QVector<QPointF> pontoInicialEFinalAlinhamento();
    void setPontoInicialEFinalAlinhamento(QVector<QPointF> pontos);

private:
    Jogador * jogador1, * jogador2, * jogador_da_vez;   // jogadores 1 e 2, e jogador atual
    Tabuleiro * tabuleiro;                              // tabuleiro do jogo
    unsigned short pecas_necessarias_pra_ganhar;        // qtd necessária de peças pra alinhar pra ganhar a partida
};

#endif // JOGO_H
