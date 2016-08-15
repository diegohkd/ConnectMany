#ifndef JOGADOR_H
#define JOGADOR_H

#include <QString>
#include <QColor>

class Jogador{
public:
    // inicialização
    Jogador();
    Jogador(QString, QColor, int id);

    // getters and setters
    QString getNome();
    void setNome(const QString &value);
    QColor getCor();
    void setCor(const QColor &value);
    int getId() const;
    void setId(int value);

private:
    QString nome;   // nome do jogador
    QColor cor;     // cor das peças do jogador
    int id;         // =1 se for jogador 1, =2 se for jogador 2
};

#endif // JOGADOR_H
