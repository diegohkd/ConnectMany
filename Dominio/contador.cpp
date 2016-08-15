#include "contador.h"

Contador::Contador(int contagem){
    this->contagem = contagem;
}

/* -------------------------------------
 * |                                   |
 * |        GETTERS AND SETTERS        |
 * |                                   |
 * -------------------------------------*/
int Contador::getContagem() const{
    return contagem;
}

void Contador::setContagem(int value){
    contagem = value;
}


