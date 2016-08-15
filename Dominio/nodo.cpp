#include "nodo.h"

Nodo::Nodo(){
    peca = NULL;

    vizinho_esq = NULL;
    vizinho_inferior_esq = NULL;
    vizinho_inferior = NULL;
    vizinho_inferior_dir = NULL;
    vizinho_dir = NULL;
    vizinho_superior_dir = NULL;
    vizinho_superior = NULL;
    vizinho_superior_esq = NULL;

    alinhados_horizontal = new Contador(0);
    alinhados_vertical = new Contador(0);
    alinhados_diagonal = new Contador(0);
    alinhados_diagonal_invertida = new Contador(0);
}

Nodo::~Nodo(){
    delete peca;
    delete vizinho_esq;
    delete vizinho_inferior_esq;
    delete vizinho_inferior;
    delete vizinho_inferior_dir;
    delete vizinho_dir;
    delete vizinho_superior_dir;
    delete vizinho_superior;
    delete vizinho_superior_esq;
    delete alinhados_horizontal;
    delete alinhados_vertical;
    delete alinhados_diagonal;
    delete alinhados_diagonal_invertida;
}

void Nodo::removePeca(){
    if(peca != NULL){
        delete peca;
        peca = NULL;
    }
}

/* -------------------------------------
 * |                                   |
 * |        GETTERS AND SETTERS        |
 * |                                   |
 * -------------------------------------*/
Peca *Nodo::getPeca(){
    return peca;
}
void Nodo::setPeca(Peca *value){
    peca = value;
}
Nodo *Nodo::getVizinho_esq() const
{
    return vizinho_esq;
}

void Nodo::setVizinho_esq(Nodo *value)
{
    vizinho_esq = value;
}
Nodo *Nodo::getVizinho_inferior_esq() const
{
    return vizinho_inferior_esq;
}

void Nodo::setVizinho_inferior_esq(Nodo *value)
{
    vizinho_inferior_esq = value;
}
Nodo *Nodo::getVizinho_inferior() const
{
    return vizinho_inferior;
}

void Nodo::setVizinho_inferior(Nodo *value)
{
    vizinho_inferior = value;
}
Nodo *Nodo::getVizinho_inferior_dir() const
{
    return vizinho_inferior_dir;
}

void Nodo::setVizinho_inferior_dir(Nodo *value)
{
    vizinho_inferior_dir = value;
}
Nodo *Nodo::getVizinho_dir() const
{
    return vizinho_dir;
}

void Nodo::setVizinho_dir(Nodo *value)
{
    vizinho_dir = value;
}
Nodo *Nodo::getVizinho_superior_dir() const
{
    return vizinho_superior_dir;
}

void Nodo::setVizinho_superior_dir(Nodo *value)
{
    vizinho_superior_dir = value;
}
Nodo *Nodo::getVizinho_superior() const
{
    return vizinho_superior;
}

void Nodo::setVizinho_superior(Nodo *value)
{
    vizinho_superior = value;
}
Nodo *Nodo::getVizinho_superior_esq() const
{
    return vizinho_superior_esq;
}

void Nodo::setVizinho_superior_esq(Nodo *value)
{
    vizinho_superior_esq = value;
}
Contador *Nodo::getAlinhados_horizontal() const
{
    return alinhados_horizontal;
}

void Nodo::setAlinhados_horizontal(Contador *value)
{
    alinhados_horizontal = value;
}
Contador *Nodo::getAlinhados_vertical() const
{
    return alinhados_vertical;
}

void Nodo::setAlinhados_vertical(Contador *value)
{
    alinhados_vertical = value;
}
Contador *Nodo::getAlinhados_diagonal() const
{
    return alinhados_diagonal;
}

void Nodo::setAlinhados_diagonal(Contador *value)
{
    alinhados_diagonal = value;
}
Contador *Nodo::getAlinhados_diagonal_invertida() const
{
    return alinhados_diagonal_invertida;
}

void Nodo::setAlinhados_diagonal_invertida(Contador *value)
{
    alinhados_diagonal_invertida = value;
}









