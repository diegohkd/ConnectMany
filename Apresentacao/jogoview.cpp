#include "jogoview.h"

extern Jogo * jogo;

JogoView::JogoView(QWidget *parent){
    // inicializa scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);
    setScene(scene);

    // faz não permitir criar scroll bar
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // inicializa tamanho da view pra ser igual da scene
    setFixedSize(800,600);

    // inicializa imagem de fundo
    QImage img(":/images/Apresentacao/rsc/bg.png");
    setBackgroundBrush(QBrush(img));

    // inicializa vetor de peças (QGraphicsItem's)
    for(int i = 0; i < jogo->getColunas(); i++){
        QVector<PecaGraphic *> coluna;
        pecas.push_back(coluna);
    }

    espera = false;
    vitoria = false;
    empate = false;

    // cria interface para verificar quem começa o jogo
    menu = new CaraCoroaMenuGraphic(jogo->getNomeJogador1(), jogo->getNomeJogador2());
    menu->setPos(265,165);
    scene->addItem(menu);

    // cria signal para inicializar interface do jogo após ter sido selecionado o jogador
    connect(menu, SIGNAL(jogadorFoiEscolhido()), this, SLOT(inicializaInterfaceDeUsuario()));

    show();
}

JogoView::~JogoView(){
    delete scene;
    delete pontuacao1;
    delete pontuacao2;
    pecas.clear();
    delete msgJogadorDaVez;
    delete timer;
    pecas_alinhadas.clear();
    delete menu;
}

/* -------------------------------------
 * |                                   |
 * |         EXECUÇÃO DO JOGO          |
 * |                                   |
 * -------------------------------------*/
void JogoView::colunaClicada(int coluna){
    // só faz algo se não estiver ocorrendo alguma animação
    if(espera == false){

        // efetua a jogada
        int retorno = jogo->efetuaJogada(coluna);

        // se a peça foi inserida, então cria animação da peça sendo inserida
        PecaGraphic * peca;
        if(retorno == 0 || retorno == 1 || retorno == -2){
            // calcula posiçao inicial da peça
            int largura = 40;
            double xCentro = width()/2;
            double largura_tabuleiro = jogo->getColunas() * largura;
            double xColuna = xCentro - largura_tabuleiro/2;

            double xInicial = xColuna + ((coluna)*40) + 6.5 - 0.5;
            double yInicial = 110;

            // calcula posição final da peça
            int linhas = jogo->getLinhas();
            int total_pecas_coluna = jogo->getTotalPecasColuna(coluna);
            double yFinal = yInicial + (linhas - total_pecas_coluna)*40 + 25 + 6.5 - 0.5;
            double xFinal = xInicial;

            // cria e adiciona peça a scene
            peca = new PecaGraphic(jogo->getCorJogadorAtual(), 27, QPointF(xFinal, yFinal));
            peca->setZValue(-1);
            peca->setPos(xInicial,yInicial);
            scene->addItem(peca);

            // cria signals para verificar se deu vitória ou empate, e para congelar interação
            // enquanto animação da remoção de peças ocorre
            //connect(peca,SIGNAL(stopped()),this,SLOT(verificaEmpate()));
            connect(peca,SIGNAL(stoppedLast()),this,SLOT(fimAnimacao()));

            // insere peça em 'peças' pra ser removida posteriormente
            pecas[coluna].push_back(peca);

            // inicia animação
            peca->comecaAnimacao();
        }

        // se vitória
        if(retorno == 1){
            espera = true;
            animacaoVitoria();
        }

        // se deu empate
        if(retorno == -2){
            espera = true;
            empate = true;

            // avisa o usuário q deu empate
            DisplayDeInfoGraphic *display = new DisplayDeInfoGraphic("Empate!");
            display->setPos(265,165);
            scene->addItem(display);

            connect(display, SIGNAL(ok_clicked()), this, SLOT(processaVitoriaOuEmpate()));
        }

        // troca jogador se a peça tiver sido inserida
        if(retorno != -1 && retorno != 1 && retorno != -2){
            jogo->trocaJogador();
            setMsgJogadorDaVez("Vez de " + jogo->getNomeJogador_atual());
        }
    }
}

void JogoView::novoJogoClicado(){
    // verifica se não tem alguma animação ocorrendo
    if(espera == false){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Novo Jogo", "Tem certeza que deseja encerrar esse jogo?",
                                        QMessageBox::Yes|QMessageBox::No);
        // se jogador confirmar novo jogo, emite signal para executar novo jogo
        if (reply == QMessageBox::Yes)
            emit novoJogo();
    }

}

void JogoView::zerarPlacarClicado(){
    // verifica se não tem alguma animação ocorrendo
    if(espera == false){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Zerar Placar", "Tem certeza que deseja zerar o placar?",
                                        QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            pontuacao1->zerar();
            pontuacao2->zerar();
        }
    }
}

void JogoView::fimAnimacao(){
    espera = false;
}

void JogoView::piscaPecas(){
    // de acordo com a contagem de vezes que já "piscou" as peças alinhadas
    // vai alterando as cores das peças
    if(count_piscadas == 0){
        QBrush brush;
        for(int i = 0; i < pecas_alinhadas.size(); i++){
            brush.setStyle(Qt::SolidPattern);
            brush.setColor(QColor(Qt::yellow));
            pecas_alinhadas[i]->setBrush(brush);
        }
        count_piscadas++;
        return;
    }
    if(count_piscadas == 1){
        QBrush brush;
        for(int i = 0; i < pecas_alinhadas.size(); i++){
            brush.setStyle(Qt::SolidPattern);
            brush.setColor(QColor(Qt::black));
            pecas_alinhadas[i]->setBrush(brush);
        }
        count_piscadas++;
        return;
    }
    if(count_piscadas == 2){
        QBrush brush;
        for(int i = 0; i < pecas_alinhadas.size(); i++){
            brush.setStyle(Qt::SolidPattern);
            brush.setColor(QColor(Qt::yellow));
            pecas_alinhadas[i]->setBrush(brush);
        }
        count_piscadas++;
        return;
    }
    // fim das piscadas
    if(count_piscadas == 3){
        QBrush brush;
        for(int i = 0; i < pecas_alinhadas.size(); i++){
            brush.setStyle(Qt::SolidPattern);
            brush.setColor(QColor(Qt::black));
            pecas_alinhadas[i]->setBrush(brush);
        }
        count_piscadas = 0;
        vitoria = true;
        timer->stop();

        // avisa o usuário qual jogador venceu a partida
        DisplayDeInfoGraphic *display = new DisplayDeInfoGraphic("Vitória de " + jogo->getNomeJogador_atual());
        display->setPos(265,165);
        scene->addItem(display);

        connect(display, SIGNAL(ok_clicked()), this, SLOT(processaVitoriaOuEmpate()));
    }
}

void JogoView::processaVitoriaOuEmpate(){

    // troca jogador
    jogo->trocaJogador();

    // se jogador atual venceu a partida, incrementa sua pontuação
    if(vitoria){
        int jogador_id = jogo->getNumeroJogadorAtual();
        if(jogador_id == 1){
            pontuacao2->incrementa();
        }else
            pontuacao1->incrementa();
    }

    // limpa tabuleiro
    limpaJogo();

    // atualiza objeto gráfico que indica o jogador da vez
    setMsgJogadorDaVez("Vez de " + jogo->getNomeJogador_atual());
}

void JogoView::limpaJogo(){

    // remove do tabuleiro todas os objetos gráficos de peça
    int colunas = pecas.size();
    for(int j = 0; j < colunas; j++){
        int qtd_pecas = pecas[j].size();
        for(int i = 0; i < qtd_pecas; i++){
            // pega peça atual
            PecaGraphic * peca = pecas[j].last();
            pecas[j].pop_back();

            // verifica se a peça é a última, se sim, então faz
            // ela avisar qd terminar sua animação
            // TODO - a última peça removida não será necessariamente
            //        a última a terminar sua animação
            if(j == colunas && i == qtd_pecas)
                peca->jogaFora(true);
            else
                peca->jogaFora(false);

        }
    }

    // remove todas peças do vetor de peças
    for(int i = 0; i < jogo->getColunas(); i++){
        pecas[i].clear();
    }

    // remove peças alinhadas
    pecas_alinhadas.clear();

    // jogo remove peças
    jogo->limpaTabuleiro();

    vitoria = false;
    empate = false;
}

void JogoView::animacaoVitoria(){
    // busca pontos inicial e final que indica indices da primeira e última peça alinhada
    QVector<QPointF> pontos = jogo->pontoInicialEFinalAlinhamento();

    int linhas = jogo->getLinhas();

    int x1 = pontos[0].x();
    int y1 = pontos[0].y();
    int x2 = pontos[1].x();
    int y2 = pontos[1].y();

    // atualiza vetor de peças alinhadas pra criar animação posteriormente

    // busca peças se estiverem alinhadas horizontalmente
    if(x1 == x2){
        for(int j = y1; j < y2 + 1; j++)
            pecas_alinhadas.push_back(pecas[j][linhas - x1 - 1]);
    }
    // busca peças se estiverem alinhadas verticalmente
    if(y1 == y2){
        for(int i = x1; i < x2 + 1; i++)
            pecas_alinhadas.push_back(pecas[y1][linhas - i - 1]);
    }
    // busca peças se estiverem alinhadas na diagonal
    if(x1 > x2 && y1 < y2){
        for(int i = x1, j = y1; i >= x2; i--, j++)
            pecas_alinhadas.push_back(pecas[j][linhas - i - 1]);
    }
    // busca peças se estiverem alinhadas na diagonal invertida
    if(x1 < x2 && y1 < y2){
        for(int i = x1, j = y1; i < x2 + 1; i++, j++)
            pecas_alinhadas.push_back(pecas[j][linhas - i - 1]);
    }

    // reseta variáveis
    count_piscadas = 0;
    pontos.clear();
    jogo->setPontoInicialEFinalAlinhamento(pontos);

    // da inicio a animação
    QBrush brush;
    for(int i = 0; i < pecas_alinhadas.size(); i++){
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(QColor(Qt::black));
        pecas_alinhadas[i]->setBrush(brush);
    }

    // cria timer para realizar animação
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(piscaPecas()));

    // start the timer
    timer->start(500);
}

void JogoView::setMsgJogadorDaVez(QString msg){
    msgJogadorDaVez->setPlainText(msg);
    msgJogadorDaVez->setPos(655 - msgJogadorDaVez->boundingRect().width()/2, 49);
}

bool JogoView::getEspera() const
{
    return espera;
}

void JogoView::setEspera(bool value)
{
    espera = value;
}

/* -------------------------------------
 * |                                   |
 * |       CRIAÇÃO DA INTERFACE        |
 * |                                   |
 * -------------------------------------*/
void JogoView::inicializaInterfaceDeUsuario(){
    // após ter definido o jogador que começa, atualiza jogador atual
    bool jogador1 = menu->getJogador1_comeca();
    jogo->setJogadorEscolhido(jogador1);

    // Cria placar
    criaPlacar();

    // cria botao Novo Jogo
    criaBotaoNovoJogo();

    // cria botao Zerar Placar
    criaBotaoZerarPlacar();

    // cria as setas de todas colunas
    criaSetasDasColunas();

    // cria os nodos
    criaNodos();

    // cria msg para usuário
    criaMsgJogadorDaVez();
}

void JogoView::criaPlacar(){
    // cria placar jogador 1
    // cria retângulo do nome do jogador 1
    QGraphicsPixmapItem * retanguloNome_jogador = new QGraphicsPixmapItem();
    retanguloNome_jogador->setPixmap(QPixmap(":/images/Apresentacao/rsc/placar.png"));
    retanguloNome_jogador->setPos(290,15);

    // cria texto com nome do jogador 1
    QGraphicsTextItem * nomeJogador1;
    nomeJogador1 = new QGraphicsTextItem(jogo->getNomeJogador1(), retanguloNome_jogador);
    nomeJogador1->setDefaultTextColor(Qt::white);
    nomeJogador1->setFont(QFont("times",20));
    int x = (retanguloNome_jogador->boundingRect().width() - nomeJogador1->boundingRect().width())/2 + retanguloNome_jogador->boundingRect().x();
    int y = (retanguloNome_jogador->boundingRect().height() - nomeJogador1->boundingRect().height())/2 + retanguloNome_jogador->boundingRect().y();
    nomeJogador1->setPos(x,y);

    // cria retângulo pontuacao jogador 1
    QGraphicsRectItem * retanguloPontuacaoJogador1 = new QGraphicsRectItem();
    retanguloPontuacaoJogador1->setRect(290,50,110,35);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);
    retanguloPontuacaoJogador1->setBrush(brush);

    // cria pontuação jogador 1
    pontuacao1 = new PontuacaoGraphic(retanguloPontuacaoJogador1);
    x = (retanguloNome_jogador->boundingRect().width() - pontuacao1->boundingRect().width())/2 + retanguloPontuacaoJogador1->rect().x();
    y = (retanguloNome_jogador->boundingRect().height() - pontuacao1->boundingRect().height())/2 + retanguloPontuacaoJogador1->rect().y();
    pontuacao1->setPos(x,y);

    scene->addItem(retanguloNome_jogador);
    scene->addItem(retanguloPontuacaoJogador1);

    // cria placar jogador 2
    // cria retângulo do nome do jogador 2
    QGraphicsPixmapItem * retanguloNome_jogador2 = new QGraphicsPixmapItem();
    retanguloNome_jogador2->setPixmap(QPixmap(":/images/Apresentacao/rsc/placar.png"));
    retanguloNome_jogador2->setPos(400,15);

    // cria texto com nome do jogador
    QGraphicsTextItem * nomeJogador2;
    nomeJogador2 = new QGraphicsTextItem(jogo->getNomeJogador2(), retanguloNome_jogador2);
    nomeJogador2->setDefaultTextColor(Qt::white);
    nomeJogador2->setFont(QFont("times",20));
    x = (retanguloNome_jogador2->boundingRect().width() - nomeJogador2->boundingRect().width())/2 + retanguloNome_jogador2->boundingRect().x();
    y = (retanguloNome_jogador2->boundingRect().height() - nomeJogador2->boundingRect().height())/2 + retanguloNome_jogador2->boundingRect().y();
    nomeJogador2->setPos(x,y);

    // cria retângulo pontuacao jogador 1
    QGraphicsRectItem * retanguloPontuacaoJogador2 = new QGraphicsRectItem();
    retanguloPontuacaoJogador2->setRect(400,50,110,35);
    retanguloPontuacaoJogador2->setBrush(brush);

    // cria pontuação jogador 1
    pontuacao2 = new PontuacaoGraphic(retanguloPontuacaoJogador2);
    x = (retanguloNome_jogador2->boundingRect().width() - pontuacao1->boundingRect().width())/2 + retanguloPontuacaoJogador2->rect().x();
    y = (retanguloNome_jogador2->boundingRect().height() - pontuacao1->boundingRect().height())/2 + retanguloPontuacaoJogador2->rect().y();
    pontuacao2->setPos(x,y);

    scene->addItem(retanguloNome_jogador2);
    scene->addItem(retanguloPontuacaoJogador2);
}

void JogoView::criaBotaoNovoJogo(){
    BotaoGraphic * botaoNovo_jogo = new BotaoGraphic(QString("Novo Jogo"));
    int xBotaoNovo_jogo = 20;
    int yBotaoNovo_jogo = 15;
    botaoNovo_jogo->setPos(xBotaoNovo_jogo,yBotaoNovo_jogo);
    connect(botaoNovo_jogo, SIGNAL(clicked()), this, SLOT(novoJogoClicado()));
    scene->addItem(botaoNovo_jogo);
}

void JogoView::criaBotaoZerarPlacar(){
    BotaoGraphic * botaoZerar_placar = new BotaoGraphic(QString("Zerar Placar"));
    int xBotaoZerar_placar = 20;
    int yBotaoZerar_placar = 55;
    botaoZerar_placar->setPos(xBotaoZerar_placar, yBotaoZerar_placar);
    connect(botaoZerar_placar, SIGNAL(clicked()), this, SLOT(zerarPlacarClicado()));
    scene->addItem(botaoZerar_placar);
}

void JogoView::criaMsgJogadorDaVez(){
    // cria retângulo onde ficará localizado o texto
    QGraphicsRectItem * retangulo = new QGraphicsRectItem();
    retangulo->setRect(550,49,230,35);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);
    retangulo->setBrush(brush);

    // inicializa objeto gráfico que indica de quem é a vez
    msgJogadorDaVez = new QGraphicsTextItem();

    msgJogadorDaVez->setPlainText("Vez de " + jogo->getNomeJogador_atual());
    msgJogadorDaVez->setFont(QFont("times",24));
    msgJogadorDaVez->setDefaultTextColor(Qt::black);
    msgJogadorDaVez->setPos(655 - msgJogadorDaVez->boundingRect().width()/2, 49);

    scene->addItem(retangulo);
    scene->addItem(msgJogadorDaVez);
}

void JogoView::criaSetasDasColunas(){
    int largura = 40;

    // calcula posição (x) inicial da primeira seta
    double xCentro = width()/2;
    double largura_tabuleiro = jogo->getColunas() * largura;
    double x = xCentro - largura_tabuleiro/2;

    // cria todas setas e cria signals para cada uma poder responder ao clique de mouse, passando
    // o índice da coluna que foi clicada junto ao signal
    QSignalMapper* signalMapper = new QSignalMapper (this) ;
    for(int i = 0; i < jogo->getColunas(); i++){
        SetaDeColunaGraphic * seta = new SetaDeColunaGraphic(i);
        seta->setPos(x,110);
        connect (seta, SIGNAL(clicked(int)), signalMapper, SLOT(map()));
        signalMapper->setMapping (seta, i) ;
        scene->addItem(seta);
        x = x + largura;
    }
    connect (signalMapper, SIGNAL(mapped(int)), this, SLOT(colunaClicada(int))) ;
}

void JogoView::criaNodos(){
    // calcula x e y do primeiro nodo
    int largura = 40;
    double xCentro = width()/2;
    double largura_tabuleiro = jogo->getColunas() * largura;
    double xOriginal = xCentro - largura_tabuleiro/2;
    double y = 135;

    // cria todos os nodos do tabuleiro
    for(int i = 0; i < jogo->getLinhas(); i++){
        double x = xOriginal;
        for(int j = 0; j < jogo->getColunas(); j++){
            NodoGraphic * nodo = new NodoGraphic();
            nodo->setPos(x,y);
            scene->addItem(nodo);
            x = x + largura;
        }
        y = y + largura;
    }
}
