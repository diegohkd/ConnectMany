#include "jogo.h"

Jogo::Jogo(){

}

Jogo::Jogo(unsigned short pecas_necessarias_pra_ganhar){
    this->pecas_necessarias_pra_ganhar = pecas_necessarias_pra_ganhar;
    jogador_da_vez = jogador1;

    // set random seed
    srand((unsigned)time(NULL));
}

/* -------------------------------------
 * |                                   |
 * |         EXECUÇÃO DO JOGO          |
 * |                                   |
 * -------------------------------------*/
/*
Argumentos:
coluna: coluna onde o jogador está tentando inserir a peça

Retorno:
 0: peça inserida
 1: peça inserida e vitória do jogador
-1: coluna cheia
-2: empate do jogo
*/
int Jogo::efetuaJogada(int coluna){
    Peca * peca = new Peca(jogador_da_vez->getCor());

    // tenta inserir peça
    int retorno = tabuleiro->inserePeca(peca, coluna);

    return retorno;
}

void Jogo::trocaJogador(){
    if(jogador_da_vez == jogador1)
        jogador_da_vez = jogador2;
    else
        jogador_da_vez = jogador1;
}

void Jogo::limpaTabuleiro(){
    tabuleiro->limpaTabuleiro();
}

/* -------------------------------------
 * |                                   |
 * |           INICIALIZACAO           |
 * |                                   |
 * -------------------------------------*/

/*
 * Retorno:
 *  0: OK!
 * -1: erro - nomes iguais
 * -2: erro - cores iguais
*/
int Jogo::createJogadores(const QString &nome1, const QColor &cor1, const QString &nome2, const QColor &cor2){
    // verifica se nomes sao iguais
    if(nome1 == nome2)
        return -1;

    // verifica se cores sao iguais
    if(cor1.name() == cor2.name())
        return -2;

    jogador1 = new Jogador(nome1, cor1, 1);
    jogador2 = new Jogador(nome2, cor2, 2);
    return 0;
}

void Jogo::createTabuleiro(int linhas, int colunas, unsigned short total_pecas_alinhadas_pra_ganhar){
    tabuleiro = new Tabuleiro(linhas, colunas, total_pecas_alinhadas_pra_ganhar);
}

Jogo::~Jogo(){
    delete jogador1;
    delete jogador2;
    delete jogador_da_vez;
    delete tabuleiro;
}

/* -------------------------------------
 * |                                   |
 * |       GETTERS AND SETTERS         |
 * |                                   |
 * -------------------------------------*/
QString Jogo::getNomeJogador1(){
    return jogador1->getNome();
}
QString Jogo::getNomeJogador2(){
    return jogador2->getNome();
}

QColor Jogo::getCorJogador1(){
    return jogador1->getCor();
}
QColor Jogo::getCorJogador2(){
    return jogador2->getCor();
}

QColor Jogo::getCorJogadorAtual(){
    return jogador_da_vez->getCor();
}

/*int Jogo::getTamanhoNodo(){
    return tabuleiro->getTamanhoNodo();
}*/

int Jogo::getColunas(){
    return tabuleiro->getColunas();
}

int Jogo::getLinhas(){
    return tabuleiro->getLinhas();
}

int Jogo::getTotalPecasColuna(int coluna){
    return tabuleiro->qtdPecasColuna(coluna);
}

int Jogo::getNumeroJogadorAtual(){
    return jogador_da_vez->getId();
}

QString Jogo::getNomeJogador_atual(){
    return jogador_da_vez->getNome();
}

void Jogo::setJogadorEscolhido(bool ehJogador1)
{
    if(ehJogador1)
        jogador_da_vez = jogador1;
    else
        jogador_da_vez = jogador2;
}

QVector<QPointF> Jogo::pontoInicialEFinalAlinhamento(){
    return tabuleiro->getPontoInicialEFinalAlinhamento();
}

void Jogo::setPontoInicialEFinalAlinhamento(QVector<QPointF> pontos)
{
    tabuleiro->setPontoInicialEFinalAlinhamento(pontos);
}


