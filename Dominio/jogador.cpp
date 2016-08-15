#include "jogador.h"

Jogador::Jogador(){

}

Jogador::Jogador(QString nome, QColor cor, int id){
    this->nome = nome;
    this->cor = cor;
    this->id = id;
}

/* -------------------------------------
 * |                                   |
 * |        GETTERS AND SETTERS        |
 * |                                   |
 * -------------------------------------*/
QString Jogador::getNome(){
    return nome;
}
void Jogador::setNome(const QString &nome){
    this->nome = nome;
}

QColor Jogador::getCor(){
    return cor;
}
void Jogador::setCor(const QColor &cor){
    this->cor = cor;
}
int Jogador::getId() const{
    return id;
}

void Jogador::setId(int value){
    id = value;
}

