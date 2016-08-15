#include "peca.h"

Peca::Peca(QColor cor){
    this->cor = cor;
}

/* -------------------------------------
 * |                                   |
 * |        GETTERS AND SETTERS        |
 * |                                   |
 * -------------------------------------*/
QColor Peca::getCor() const
{
    return cor;
}

void Peca::setCor(const QColor &value)
{
    cor = value;
}



