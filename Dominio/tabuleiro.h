#ifndef TABULEIRO_H
#define TABULEIRO_H

#include "nodo.h"

#include <QVector>
#include <QPointF>

class Tabuleiro{
public:
    // inicialização
    Tabuleiro();
    Tabuleiro(int linhas=0, int colunas=0, unsigned short total_pecas_alinhadas_pra_ganhar=0);

    // destrutor
    ~Tabuleiro();

    // interação com o tabuleiro
    int inserePeca(Peca * peca, int coluna);
    int qtdPecasColuna(int coluna);
    void limpaTabuleiro();

    // getters and setters
    int getLinhas();
    void setLinhas(int linhas);
    int getColunas();
    void setColunas(int colunas);
    QVector<int> getTamanho_colunas() const;
    void setTamanho_colunas(const QVector<int> &value);
    int getTamanhoNodo();
    QVector<QPointF> getPontoInicialEFinalAlinhamento() const;
    void setPontoInicialEFinalAlinhamento(const QVector<QPointF> &value);

private:
    // interação com o tabuleiro
    void criaNodos();
    bool atualizaNodosAposInsercao(int coluna, Peca * peca);
    void setPecaInicialEFinalAlinhamento(int coluna, int linha, QString direcao);

    int linhas, colunas;                                // qtd de linhas e colunas do tabuleiro
    QVector < QVector<Nodo *> > nodos;                  // armazena todos nodos. É um vetor de vetor de colunas
    QVector<int> tamanho_colunas;                       // qtd de peças em cada coluna
    unsigned short total_colunas_cheias;                // total de colunas que não tem espaço para colocar mais peças
    unsigned short total_pecas_alinhadas_pra_ganhar;    // total de peças que é preciso alinhas pra ganhar
    QVector<QPointF> pontoInicialEFinalAlinhamento;     // armazena o ponto inicial e final do alinhamento feito pelo jogador vencedor

};

#endif // TABULEIRO_H
