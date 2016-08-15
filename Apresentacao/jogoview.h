#ifndef JOGOVIEW_H
#define JOGOVIEW_H

#include "../Dominio/jogo.h"
#include "botaographic.h"
#include "pontuacaographic.h"
#include "setadecolunagraphic.h"
#include "pecagraphic.h"
#include "nodographic.h"
#include "pecagraphic.h"
#include "caracoroamenugraphic.h"
#include "displaydeinfographic.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVector>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QSignalMapper>
#include <QMessageBox>
#include <QTimer>

class JogoView: public QGraphicsView{
    Q_OBJECT
public:
    // inicialização
    JogoView(QWidget * parent=NULL);

    // destrutor
    ~JogoView();

    // getters e setters
    bool getEspera() const;
    void setEspera(bool value);

public slots:
    // criação da interface
    void inicializaInterfaceDeUsuario();

    // execução do jogo
    void colunaClicada(int coluna);
    void novoJogoClicado();
    void zerarPlacarClicado();
    void fimAnimacao();
    void piscaPecas();
    void processaVitoriaOuEmpate();
signals:
    void novoJogo();
private:
    // criação da interface
    void criaPlacar();
    void criaBotaoNovoJogo();
    void criaBotaoZerarPlacar();
    void criaMsgJogadorDaVez();
    void criaSetasDasColunas();
    void criaNodos();

    // execução do jogo
    void limpaJogo();
    void setMsgJogadorDaVez(QString msg);
    void animacaoVitoria();

    QGraphicsScene * scene;                         // scene que armazena informação e objetos a serem desenhadas na tela
    PontuacaoGraphic * pontuacao1, * pontuacao2;    // pontuação de cada jogador
    QVector <QVector <PecaGraphic * > > pecas;      // vetor bi-dimensional que armazena os objetos de interface das peças
    bool espera, vitoria, empate;                   /* - espera=true se for pra desabilitar interação do usuário com a interface
                                                       - vitoria=true se o jogador atual tiver ganhado a partida
                                                       - empate=true se tiver dado empate*/
    QGraphicsTextItem * msgJogadorDaVez;            // objeto de interface que informa o jogador atual
    QTimer * timer;                                 // timer usado para as animações dos objetos de interface
    QVector<PecaGraphic * > pecas_alinhadas;        // vetor com as peças alinhadas do jogador vencedor. Usado pra fazer animação das peças alinhadas
    int count_piscadas;                             // contador de qtas vezes as peças alinhadas já "piscaram", pra mostrar quais peças foram alinhadas
    CaraCoroaMenuGraphic * menu;                    // menu para escolher quem começa o jogo
};

#endif // JOGOVIEW_H
