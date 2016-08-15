#include "mainwindow.h"

Jogo * jogo;
JogoView * jogo_view;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // inicializa tamanho fixo da tela
    this->setFixedSize(800, 600);

    // inicializa fundo da tela
    QImage img(":/images/Apresentacao/rsc/bg_menu.jpg");
    QImage img2 = img.scaled(771, 545, Qt::KeepAspectRatio);
    ui->label_bg->setPixmap(QPixmap::fromImage(img2));

    ui->label_bg->show();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::criarNovoJogo(){
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pb_cor_jogador_1_clicked(){
    // mostra menu de cores padrão do Qt e busca cor selecionada pelo jogador 1
    QColor c = QColorDialog::getColor(Qt::red, this);
    QString color = c.name().toUpper();
    color = "background-color:" + color + ";";

    // muda amostra de cor do jogador 1
    ui->widget_cor_jogador_1->setStyleSheet(color);
}

void MainWindow::on_pb_cor_jogador_2_clicked(){
    // mostra menu de cores padrão do Qt e busca cor selecionada pelo jogador 2
    QColor c = QColorDialog::getColor(Qt::blue, this);
    QString color = c.name().toUpper();
    color = "background-color:" + color + ";";

    // muda amostra de cor do jogador
    ui->widget_cor_jogador_2->setStyleSheet(color);
}

void MainWindow::on_pb_iniciar_jogo_clicked(){
    // inicializa o jogo
    jogo = new Jogo(ui->spinBox_pecas_alinhadas->value());

    // cria jogadorer
    QString nome1 = ui->lineEdit_nome_jogador_1->text();
    QString nome2 = ui->lineEdit_nome_jogador_2->text();
    QColor cor1(ui->widget_cor_jogador_1->palette().color(QWidget::backgroundRole()));
    QColor cor2(ui->widget_cor_jogador_2->palette().color(QWidget::backgroundRole()));

    // verifica se jogadores têm nomes e/ou cores iguais
    int retorno = jogo->createJogadores(nome1, cor1, nome2, cor2);
    if(retorno == -1){
        QMessageBox messageBox;
        messageBox.critical(0,"Erro","Jogadores com mesmo nome!");
        messageBox.setFixedSize(500,200);
        return;
    }
    if(retorno == -2){
        QMessageBox messageBox;
        messageBox.critical(0,"Erro","Jogadores com mesma cor!");
        messageBox.setFixedSize(500,200);
        return;
    }

    // Cria tabuleiro
    int linhas = ui->spinBox_linhas->value();
    int colunas = ui->spinBox_colunas->value();
    int pecas_alinhadas = ui->spinBox_pecas_alinhadas->value();

    // verifica se a qtd de peças alinhadas pra ganhar o jogo é menor
    // que um dos lados do tabuleiro
    if(pecas_alinhadas > linhas && pecas_alinhadas > colunas){
        QMessageBox messageBox;
        messageBox.critical(0,"Erro","Quantidade de peças para alinhar muita pequena!\nEscolha uma quantidade menor ou igual "
                                     "que pelo menos um dos lados do tabuleiro");
        messageBox.setFixedSize(500,200);
        return;
    }

    jogo->createTabuleiro(linhas, colunas, pecas_alinhadas);

    // cria e executa interface do jogo
    jogo_view = new JogoView(this);

    // cria sinal pra o jogo_avisar qd for pra criar um jogo novo
    connect(jogo_view, SIGNAL(novoJogo()), this, SLOT(criarNovoJogo()));

    // troca widget atual para o que contém a interface do jogo rodando
    ui->stackedWidget->insertWidget(1, jogo_view);
    ui->stackedWidget->setCurrentIndex(1);
}



