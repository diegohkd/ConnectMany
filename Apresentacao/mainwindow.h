#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "jogoview.h"

#include <QMainWindow>
#include <QColorDialog>
#include <QColor>
#include <QBrush>
#include <QImage>
#include <QGraphicsPixmapItem>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    // destrutor
    ~MainWindow();

public slots:
    void criarNovoJogo();
private slots:

    void on_pb_cor_jogador_1_clicked();

    void on_pb_cor_jogador_2_clicked();

    void on_pb_iniciar_jogo_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
