#include "tabuleiro.h"

Tabuleiro::Tabuleiro(){
}

Tabuleiro::Tabuleiro(int linhas, int colunas, unsigned short total_pecas_alinhadas_pra_ganhar){
    this->linhas = linhas;
    this->colunas = colunas;
    this->total_pecas_alinhadas_pra_ganhar = total_pecas_alinhadas_pra_ganhar;
    total_colunas_cheias = 0;

    // seta todos tamanhos das colunas
    for(int i = 0; i < colunas; i++)
        tamanho_colunas.push_back(0);

    // inicialização dos nodos
    criaNodos();
}

Tabuleiro::~Tabuleiro(){
    nodos.clear();
}

/*
Argumentos:
peca: peça a ser colocada
coluna: coluna onde o jogador está tentando inserir a peça

Retorno:
 0: peça inserida
 1: peça inserida e vitória do jogador
-1: coluna cheia
-2: empate do jogo
*/
int Tabuleiro::inserePeca(Peca *peca, int coluna){

    // verifica se não tem espaço na coluna
    if(tamanho_colunas[coluna] == colunas + 1)
        return -1;

    // insere peça
    tamanho_colunas[coluna]++;
    nodos[coluna][linhas - tamanho_colunas[coluna]]->setPeca(peca);

    // verifica vitória (precisa ser antes de verificar empate)
    bool ganhou = atualizaNodosAposInsercao(coluna, peca);
    if(ganhou)
        return 1;

    // verifica se encheu coluna
    if(tamanho_colunas[coluna] == linhas)
        total_colunas_cheias++;

    // verifica se deu empate
    if(total_colunas_cheias == colunas)
        return -2;

    // peça inserida
    return 0;
}

int Tabuleiro::qtdPecasColuna(int coluna){
    return tamanho_colunas[coluna];
}

void Tabuleiro::limpaTabuleiro(){
    // remove as peças de cada coluna
    for(int j = 0; j < nodos.size(); j++){
        int tamanho_coluna = tamanho_colunas[j];
        for(int i = linhas-1; i >= linhas - tamanho_coluna; i--){
            nodos[j][i]->removePeca();
        }
        tamanho_colunas[j] = 0;
    }

    // nenhuma coluna cheia
    total_colunas_cheias = 0;
}

/*
Retorno:
true:  vitória
false: peça inserida
*/
bool Tabuleiro::atualizaNodosAposInsercao(int coluna, Peca *peca){
    int linha = linhas - tamanho_colunas[coluna];
    Contador * n_pecas_alinhadas = new Contador(0);

    // atualiza horizontal
    nodos[coluna][linha]->setAlinhados_horizontal(new Contador(1));
    if(coluna != 0){
        // atualiza vizinhos a esquerda
         Nodo * esq = nodos[coluna][linha]->getVizinho_esq();
        if(esq->getPeca() != NULL && esq->getPeca()->getCor().name() == peca->getCor().name()){
            n_pecas_alinhadas = esq->getAlinhados_horizontal();
            n_pecas_alinhadas->setContagem(n_pecas_alinhadas->getContagem()+1);
            esq->setAlinhados_horizontal(n_pecas_alinhadas);
            nodos[coluna][linha]->setAlinhados_horizontal(esq->getAlinhados_horizontal());
        }
    }
    if(coluna != colunas-1){
        // atualiza vizinhos a direita
        Nodo * dir = nodos[coluna][linha]->getVizinho_dir();
        if(dir->getPeca() != NULL && dir->getPeca()->getCor().name() == peca->getCor().name()){
            n_pecas_alinhadas = dir->getAlinhados_horizontal();
            n_pecas_alinhadas->setContagem(n_pecas_alinhadas->getContagem() + nodos[coluna][linha]->getAlinhados_horizontal()->getContagem());
            dir->setAlinhados_horizontal(n_pecas_alinhadas);
            nodos[coluna][linha]->setAlinhados_horizontal(dir->getAlinhados_horizontal());
        }
    }
    // verifica se vitória
    if(n_pecas_alinhadas->getContagem() >= total_pecas_alinhadas_pra_ganhar){
        // seta peça inicial e peça final do alinhamento
        setPecaInicialEFinalAlinhamento(coluna, linha, "horizontal");

        return true;
    }

    // atualiza vertical
    nodos[coluna][linha]->setAlinhados_vertical(new Contador(1));
    n_pecas_alinhadas = new Contador(0);
    if(linha != 0){
        // atualiza vizinhos de cima
        Nodo * superior = nodos[coluna][linha]->getVizinho_superior();
        if(superior->getPeca() != NULL && superior->getPeca()->getCor().name() == peca->getCor().name()){
            n_pecas_alinhadas = superior->getAlinhados_vertical();
            n_pecas_alinhadas->setContagem(n_pecas_alinhadas->getContagem()+1);
            superior->setAlinhados_vertical(n_pecas_alinhadas);
            nodos[coluna][linha]->setAlinhados_vertical(superior->getAlinhados_vertical());
        }
    }
    if(linha != linhas-1){
        // atualiza vizinhos de baixo
        Nodo * inferior = nodos[coluna][linha]->getVizinho_inferior();
        if(inferior->getPeca() != NULL && inferior->getPeca()->getCor().name() == peca->getCor().name()){
            n_pecas_alinhadas = inferior->getAlinhados_vertical();
            n_pecas_alinhadas->setContagem(n_pecas_alinhadas->getContagem() + nodos[coluna][linha]->getAlinhados_vertical()->getContagem());
            inferior->setAlinhados_vertical(n_pecas_alinhadas);
            nodos[coluna][linha]->setAlinhados_vertical(inferior->getAlinhados_vertical());
        }
    }
    // verifica se vitória
    if(n_pecas_alinhadas->getContagem() >= total_pecas_alinhadas_pra_ganhar){
        // seta peça inicial e peça final do alinhamento
        setPecaInicialEFinalAlinhamento(coluna, linha, "vertical");

        return true;
    }

    // atualiza diagonal
    nodos[coluna][linha]->setAlinhados_diagonal(new Contador(1));
    n_pecas_alinhadas = new Contador(0);
    if(coluna != 0 && linha != 0){
        // atualiza vizinhos superior esquerda
        Nodo * superior_esq = nodos[coluna][linha]->getVizinho_superior_esq();
        if(superior_esq->getPeca() != NULL && superior_esq->getPeca()->getCor().name() == peca->getCor().name()){
            n_pecas_alinhadas = superior_esq->getAlinhados_diagonal();
            n_pecas_alinhadas->setContagem(n_pecas_alinhadas->getContagem()+1);
            superior_esq->setAlinhados_diagonal(n_pecas_alinhadas);
            nodos[coluna][linha]->setAlinhados_diagonal(superior_esq->getAlinhados_diagonal());
        }
    }
    if(linha != linhas-1 && coluna != colunas-1){
        // atualiza vizinhos inferior direita
        Nodo * inferior_dir = nodos[coluna][linha]->getVizinho_inferior_dir();
        if(inferior_dir->getPeca() != NULL && inferior_dir->getPeca()->getCor().name() == peca->getCor().name()){
            n_pecas_alinhadas = inferior_dir->getAlinhados_diagonal();
            n_pecas_alinhadas->setContagem(n_pecas_alinhadas->getContagem() + nodos[coluna][linha]->getAlinhados_diagonal()->getContagem());
            inferior_dir->setAlinhados_diagonal(n_pecas_alinhadas);
            nodos[coluna][linha]->setAlinhados_diagonal(inferior_dir->getAlinhados_diagonal());
        }
    }
    // verifica se vitória
    if(n_pecas_alinhadas->getContagem() >= total_pecas_alinhadas_pra_ganhar){
        // seta peça inicial e peça final do alinhamento
        setPecaInicialEFinalAlinhamento(coluna, linha, "diagonal");

        return true;
    }

    // atualiza diagonal invertida
    nodos[coluna][linha]->setAlinhados_diagonal_invertida(new Contador(1));
    n_pecas_alinhadas = new Contador(0);
    if(coluna != 0 && linha != linhas-1){
        // atualiza vizinhos inferior esquerda
        Nodo * inferior_esq = nodos[coluna][linha]->getVizinho_inferior_esq();
        if(inferior_esq->getPeca() != NULL && inferior_esq->getPeca()->getCor().name() == peca->getCor().name()){
            n_pecas_alinhadas = inferior_esq->getAlinhados_diagonal_invertida();
            n_pecas_alinhadas->setContagem(n_pecas_alinhadas->getContagem() + 1);
            inferior_esq->setAlinhados_diagonal_invertida(n_pecas_alinhadas);
            nodos[coluna][linha]->setAlinhados_diagonal_invertida(inferior_esq->getAlinhados_diagonal_invertida());
        }
    }
    if(linha != 0 && coluna != colunas-1){
        // atualiza vizinhos superior direita
        Nodo * superior_dir = nodos[coluna][linha]->getVizinho_superior_dir();
        if(superior_dir->getPeca() != NULL && superior_dir->getPeca()->getCor().name() == peca->getCor().name()){
            n_pecas_alinhadas = superior_dir->getAlinhados_diagonal_invertida();
            n_pecas_alinhadas->setContagem(n_pecas_alinhadas->getContagem() + nodos[coluna][linha]->getAlinhados_diagonal_invertida()->getContagem());
            superior_dir->setAlinhados_diagonal_invertida(n_pecas_alinhadas);
            nodos[coluna][linha]->setAlinhados_diagonal_invertida(superior_dir->getAlinhados_diagonal_invertida());
        }
    }
    // verifica se vitória
    if(n_pecas_alinhadas->getContagem() >= total_pecas_alinhadas_pra_ganhar){
        // seta peça inicial e peça final do alinhamento
        setPecaInicialEFinalAlinhamento(coluna, linha, "diagonal_invertida");

        return true;
    }

    return false;
}

void Tabuleiro::setPecaInicialEFinalAlinhamento(int coluna, int linha, QString direcao){
    // inicializa indices do ponto inicial e final
    int xInicial = linha;
    int yInicial = coluna;
    int xFinal = linha;
    int yFinal = coluna;

    Nodo * nodoBase = nodos[coluna][linha];
    if(direcao == "vertical"){
        // busca ponto inicial indo pra cima
        Nodo * atual = nodoBase->getVizinho_superior();
        while(atual != NULL && atual->getPeca() != NULL && atual->getPeca()->getCor().name() == nodoBase->getPeca()->getCor().name()){
            xInicial--;
            atual = atual->getVizinho_superior();
        }

        // busca ponto final indo para baixo
        atual = nodoBase->getVizinho_inferior();
        while(atual != NULL && atual->getPeca() != NULL && atual->getPeca()->getCor().name() == nodoBase->getPeca()->getCor().name()){
            xFinal++;
            atual = atual->getVizinho_inferior();
        }

        // atualiza pontos
        pontoInicialEFinalAlinhamento.push_back(QPointF(xInicial, yInicial));
        pontoInicialEFinalAlinhamento.push_back(QPointF(xFinal, yFinal));
        return;
    }

    if(direcao == "horizontal"){
        // busca ponto inicial indo pra esquerda
        Nodo * atual = nodoBase->getVizinho_esq();
        while(atual != NULL && atual->getPeca() != NULL && atual->getPeca()->getCor().name() == nodoBase->getPeca()->getCor().name()){
            yInicial--;
            atual = atual->getVizinho_esq();
        }

        // busca ponto final indo para a direita
        atual = nodoBase->getVizinho_dir();
        while(atual != NULL && atual->getPeca() != NULL && atual->getPeca()->getCor().name() == nodoBase->getPeca()->getCor().name()){
            yFinal++;
            atual = atual->getVizinho_dir();
        }

        // atualiza pontos
        pontoInicialEFinalAlinhamento.push_back(QPointF(xInicial, yInicial));
        pontoInicialEFinalAlinhamento.push_back(QPointF(xFinal, yFinal));
        return;
    }

    if(direcao == "diagonal_invertida"){
        // busca ponto inicial indo pra diagonal inferior esquerda
        Nodo * atual = nodoBase->getVizinho_inferior_esq();
        while(atual != NULL && atual->getPeca() != NULL && atual->getPeca()->getCor().name() == nodoBase->getPeca()->getCor().name()){
            xInicial++;
            yInicial--;
            atual = atual->getVizinho_inferior_esq();
        }

        // busca ponto final indo para a diagonal superior direita
        atual = nodoBase->getVizinho_superior_dir();
        while(atual != NULL && atual->getPeca() != NULL && atual->getPeca()->getCor().name() == nodoBase->getPeca()->getCor().name()){
            xFinal--;
            yFinal++;
            atual = atual->getVizinho_superior_dir();
        }

        // atualiza pontos
        pontoInicialEFinalAlinhamento.push_back(QPointF(xInicial, yInicial));
        pontoInicialEFinalAlinhamento.push_back(QPointF(xFinal, yFinal));
        return;
    }

    if(direcao == "diagonal"){
        // busca ponto inicial indo pra diagonal superior esquerda
        Nodo * atual = nodoBase->getVizinho_superior_esq();
        while(atual != NULL && atual->getPeca() != NULL && atual->getPeca()->getCor().name() == nodoBase->getPeca()->getCor().name()){
            xInicial--;
            yInicial--;
            atual = atual->getVizinho_superior_esq();
        }

        // busca ponto final indo para a diagonal inferior direita
        atual = nodoBase->getVizinho_inferior_dir();
        while(atual != NULL && atual->getPeca() != NULL && atual->getPeca()->getCor().name() == nodoBase->getPeca()->getCor().name()){
            xFinal++;
            yFinal++;
            atual = atual->getVizinho_inferior_dir();
        }

        // atualiza pontos
        pontoInicialEFinalAlinhamento.push_back(QPointF(xInicial, yInicial));
        pontoInicialEFinalAlinhamento.push_back(QPointF(xFinal, yFinal));
        return;
    }
}
QVector<QPointF> Tabuleiro::getPontoInicialEFinalAlinhamento() const
{
    return pontoInicialEFinalAlinhamento;
}

void Tabuleiro::setPontoInicialEFinalAlinhamento(const QVector<QPointF> &value)
{
    pontoInicialEFinalAlinhamento = value;
}


/* -------------------------------------
 * |                                   |
 * |           INICIALIZACAO           |
 * |                                   |
 * -------------------------------------*/
void Tabuleiro::criaNodos(){
    for(int i = 0; i < colunas; i++){
        // nova linha
        QVector<Nodo *> coluna;
        for(int j = 0; j < linhas; j++){
            coluna.push_back(new Nodo());
        }
        nodos.push_back(coluna);
    }

    // Atualiza ponteiros dos nodos das bordas primeiro (para evitar muitos 'if's' dentro de um 'for')

    // atualiza nodos da linha 0
    nodos[0][0]->setVizinho_dir(nodos[1][0]);
    nodos[0][0]->setVizinho_inferior(nodos[1][0]);
    nodos[0][0]->setVizinho_inferior_dir(nodos[1][0]);
    int i = 1;
    for(; i < colunas - 1; i++){
        nodos[i][0]->setVizinho_esq(nodos[i-1][0]);
        nodos[i][0]->setVizinho_inferior_esq(nodos[i-1][1]);
        nodos[i][0]->setVizinho_inferior(nodos[i][1]);
        nodos[i][0]->setVizinho_inferior_dir(nodos[i+1][1]);
        nodos[i][0]->setVizinho_dir(nodos[i+1][0]);
    }
    nodos[i][0]->setVizinho_esq(nodos[i-1][0]);
    nodos[i][0]->setVizinho_inferior_esq(nodos[i-1][1]);
    nodos[i][0]->setVizinho_inferior(nodos[i][1]);

    // atualiza nodos da última linha
    nodos[0][linhas-1]->setVizinho_superior(nodos[0][linhas-2]);
    nodos[0][linhas-1]->setVizinho_superior_dir(nodos[1][linhas-2]);
    nodos[0][linhas-1]->setVizinho_dir(nodos[1][linhas-1]);
    i = 1;
    for(; i < colunas - 1; i++){
        nodos[i][linhas-1]->setVizinho_esq(nodos[i-1][linhas-1]);
        nodos[i][linhas-1]->setVizinho_superior_esq(nodos[i-1][linhas-2]);
        nodos[i][linhas-1]->setVizinho_superior(nodos[i][linhas-2]);
        nodos[i][linhas-1]->setVizinho_superior_dir(nodos[i+1][linhas-2]);
        nodos[i][linhas-1]->setVizinho_dir(nodos[i+1][linhas-1]);
    }
    nodos[i][linhas-1]->setVizinho_esq(nodos[i-1][linhas-1]);
    nodos[i][linhas-1]->setVizinho_superior_esq(nodos[i-1][linhas-2]);
    nodos[i][linhas-1]->setVizinho_superior(nodos[i][linhas-2]);

    // atualiza nodos da primeira coluna
    for(int i = 1; i < linhas - 1; i++){
        nodos[0][i]->setVizinho_superior(nodos[0][i-1]);
        nodos[0][i]->setVizinho_superior_dir(nodos[1][i-1]);
        nodos[0][i]->setVizinho_dir(nodos[1][i]);
        nodos[0][i]->setVizinho_inferior_dir(nodos[1][i+1]);
        nodos[0][i]->setVizinho_inferior(nodos[0][i+1]);
    }

    // atualiza nodos da última coluna
    for(int i = 1; i < linhas - 1; i++){
        nodos[colunas-1][i]->setVizinho_superior(nodos[colunas-1][i-1]);
        nodos[colunas-1][i]->setVizinho_superior_esq(nodos[colunas-2][i-1]);
        nodos[colunas-1][i]->setVizinho_esq(nodos[colunas-2][i]);
        nodos[colunas-1][i]->setVizinho_inferior_esq(nodos[colunas-2][i+1]);
        nodos[colunas-1][i]->setVizinho_inferior(nodos[colunas-1][i+1]);
    }

    // atualiza os nodos internos
    for(int j = 1; j < colunas-1; j++){
        for(int i = 1; i < linhas-1; i++){
            nodos[j][i]->setVizinho_esq(nodos[j-1][i]);
            nodos[j][i]->setVizinho_inferior_esq(nodos[j-1][i+1]);
            nodos[j][i]->setVizinho_inferior(nodos[j][i+1]);
            nodos[j][i]->setVizinho_inferior_dir(nodos[j+1][i+1]);
            nodos[j][i]->setVizinho_dir(nodos[j+1][i]);
            nodos[j][i]->setVizinho_superior_dir(nodos[j+1][i-1]);
            nodos[j][i]->setVizinho_superior(nodos[j][i-1]);
            nodos[j][i]->setVizinho_superior_esq(nodos[j-1][i-1]);
        }
    }
}

/* -------------------------------------
 * |                                   |
 * |        GETTERS AND SETTERS        |
 * |                                   |
 * -------------------------------------*/

int Tabuleiro::getLinhas(){
    return linhas;
}

int Tabuleiro::getColunas()
{
    return colunas;
}
