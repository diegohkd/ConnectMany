#include "caracoroamenugraphic.h"

CaraCoroaMenuGraphic::CaraCoroaMenuGraphic(QString nomeJogador1, QString nomeJogador2, QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    nome1 = nomeJogador1;
    nome2 = nomeJogador2;

    // inicializa imagem do menu
    setPos(0,0);
    setPixmap(QPixmap(":/images/Apresentacao/rsc/menu_moeda.png"));

    // inicializa moedas
    cara = new CaraCoroaGraphic(0, this);
    cara->setPos(6,80);

    coroa = new CaraCoroaGraphic(1, this);
    coroa->setPos(136,80);

    // cria signals para qd clica em uma moeda e para qd muda a moeda selecionada
    QSignalMapper* signalMapper = new QSignalMapper (this) ;

    connect (cara, SIGNAL(clicked(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping (cara, 0) ;
    connect (coroa, SIGNAL(clicked(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping (coroa, 1) ;

    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(moedaEscolhida(int)));

    signalMapper = new QSignalMapper (this) ;

    connect (cara, SIGNAL(mudouMoeda(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping (cara, 0) ;
    connect (coroa, SIGNAL(mudouMoeda(int)), signalMapper, SLOT(map()));
    signalMapper->setMapping (coroa, 1) ;
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(mudaPosSeta(int)));

    // desenha flecha
    seta = new QGraphicsPixmapItem(this);
    seta->setPixmap(QPixmap(":/images/Apresentacao/rsc/seta_moeda.png"));
    seta->setScale(0.1);
    seta->setPos(50,46);

    // desenha nome jogador
    text = new QGraphicsTextItem(nomeJogador1, this);
    text->setFont(QFont("times",24));
    text->setDefaultTextColor(Qt::white);
    int x = boundingRect().width()/2 - text->boundingRect().width()/2 - 68;
    int y = 14;
    text->setPos(x,y);

    // set random seed
    srand((unsigned)time(NULL));
}

void CaraCoroaMenuGraphic::mudaPosSeta(int cara){
    // faz a seta apontar pra moeda correta
    if(cara == 1){
        seta->setPos(boundingRect().x()+180,46);
        int x = boundingRect().width()/2 - text->boundingRect().width()/2 +50;
        text->setPos(x + 12,14);
    }else{
        seta->setPos(50,46);
        int x = boundingRect().width()/2 - text->boundingRect().width()/2 - 68;
        int y = 14;
        text->setPos(x,y);
    }

}

void CaraCoroaMenuGraphic::moedaEscolhida(int escolheu_cara){
    // remove seta
    delete seta;

    // lança moeda
    int x = rand() % 2;

    if(x == 1){
        // sorteou coroa

        // remove cara
        delete cara;

        // centraliza a moeda sorteada
        coroa->setPos(boundingRect().x()+75, 80);
        coroa->setAcceptHoverEvents(false);
        coroa->blockSignals(true);

        // declara e inicializa texto avisando que deu coroa
        QGraphicsTextItem * temp = new QGraphicsTextItem("Deu Coroa!", this);
        temp->setFont(QFont("times",24));
        temp->setDefaultTextColor(Qt::white);
        int x = boundingRect().width()/2 - temp->boundingRect().width()/2;
        temp->setPos(x,30);
    }else{
        // sorteou cara

        // remove coroa
        delete coroa;

        // centraliza moeda sorteada
        cara->setPos(boundingRect().x()+75, 80);
        cara->setAcceptHoverEvents(false);
        cara->blockSignals(true);

        // declara e inicializa texto avisando que deu cara
        QGraphicsTextItem * temp = new QGraphicsTextItem("Deu Cara!", this);
        temp->setFont(QFont("times",24));
        temp->setDefaultTextColor(Qt::white);
        int x = boundingRect().width()/2 - temp->boundingRect().width()/2;
        temp->setPos(x,30);
    }

    // verifica jogador que começa, e desenha texto
    if(x == escolheu_cara){
        // jogador 1 começa
        jogador1_comeca = true;

        // atualiza texto indicando que jogador 1 começa
        text->setPlainText(nome1 + " começa!");
        int x = boundingRect().width()/2 - text->boundingRect().width()/2;
        text->setPos(x,210);
    }
    else{
        // jogador 2 começa
        jogador1_comeca = false;

        // atualiza texto indicando que jogador 2 começa
        text->setPlainText(nome2 + " começa!");
        int x = boundingRect().width()/2 - text->boundingRect().width()/2;
        text->setPos(x,210);
    }

    // cria botão pra dar inicio ao jogo
    botao = new BotaoGraphic("Iniciar Jogo", this);
    int xPos = boundingRect().x() + boundingRect().width()/2 - botao->boundingRect().width()/2;
    botao->setPos(xPos,300);
    connect(botao, SIGNAL(clicked()), this, SLOT(comecarJogo()));

}

void CaraCoroaMenuGraphic::comecarJogo(){
    emit jogadorFoiEscolhido();
    delete this;
}

bool CaraCoroaMenuGraphic::getJogador1_comeca() const{
    return jogador1_comeca;
}

void CaraCoroaMenuGraphic::setJogador1_comeca(bool value){
    jogador1_comeca = value;
}

